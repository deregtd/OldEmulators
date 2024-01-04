/*
NinthStar - A portable Win32 NES Emulator written in C++
Copyright (C) 2000  David de Regt

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

For a copy of the GNU General Public License, go to:
http://www.gnu.org/copyleft/gpl.html#SEC1
*/

#include "stdafx.h"

#include "NES_Controllers.h"

#include "..\NinthStar.h"

#include "..\Global.h"

HWND ConfigWnd;
int SelectedPlayer;

char KeyLookup[256][16] = {
	"Nothing", "Escape", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "- (Keyboard)", "=", "Backspace", "Tab",
	"Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P", "[", "]", "Return", "Left Control", "A", "S",
	"D", "F", "G", "H", "J", "K", "L", ";", "'", "Grave (?)", "Left Shift", "\\", "Z", "X", "C", "V",
	"B", "N", "M", ", (Keyboard)", ". (Keyboard)", "/ (Keyboard)", "Right Shift", "*", "Left Alt", "Space", "Caps Lock", "F1", "F2", "F3", "F4", "F5",
	"F6", "F7", "F8", "F9", "F10", "Num Lock", "Scroll Lock", "Numpad 7", "Numpad 8", "Numpad 9", "- (Numpad)", "Numpad 4", "Numpad 5", "Numpad 6", "+ (Numpad)", "Numpad 1",
	"Numpad 2", "Numpad 3", "Numpad 0", ". (Numpad)", "", "", "OEM 102", "F11", "F12", "", "", "", "", "", "", "",
	"", "", "", "", "F13", "F14", "F15", "", "", "", "", "", "", "", "", "", 
	"(JPN) Kana", "", "", "(PRTG) Abnt_C1", "", "", "", "", "", "(JPN) Convert", "", "(JPN) NoConvert", "", "(JPN) Yen", "(JPN) Abnt_C2", "", 
	"", "", "", "", "", "", "", "", "", "", "", "", "", "(PC98) =", "", "",
	"Previous Track", "(PC98) AT", "(PC98) Colon", "(PC98) Underln", "(JPN) Kanji", "(PC98) Stop", "(AX) AX", "(J3100) Unlabel", "", "Next Track", "", "", "Numpad Enter", "Right Control", "", "",
	"Mute", "Calculator", "Play/Pause", "", "Media Stop", "", "", "", "", "", "", "", "", "", "Volume Down", "",
	"Volume Up", "", "Web Home", ", (Numpad)", "", "/ (Numpad)", "", "SysRq", "Right Alt", "", "", "", "", "", "", "",
	"", "", "", "", "", "Pause", "", "Home", "Up Arrow", "PgUp", "", "Left Arrow", "", "Right Arrow", "", "End", 
	"Down Arrow", "PgDown", "Insert", "Delete", "", "", "", "", "", "", "", "Left Win Key", "Right Win Key", "App Menu Key", "Power Button", "Sleep Button",
	"", "", "", "Wake Key", "", "Web Search", "Web Favorites", "Web Refresh", "Web Stop", "Web Forward", "Web Back", "My Computer", "Mail", "Media Select"
};

cNES_Controllers *Conts;

cNES_Controller::cNES_Controller()
{
	Bits = 0;
	BitPtr = 0;
}

unsigned char cNES_Controller::Read()
{
	unsigned char ToRet = 0;
	ToRet |= (Bits >> BitPtr) & 1;
	ToRet |= 0x40;		//Internal Vertical Clock Signal !?
//	ToRet |= 0x10;		//No Zapper Yet...  Button Always Released for Now...

	BitPtr++;
	if (BitPtr == 32) BitPtr = 0;	//24?

	return(ToRet);
}

cNES_Controllers::cNES_Controllers(HINSTANCE hInst, HWND hWnd)
{
	Conts = this;
	
	for (int i=0;i<4;i++)
		Cont[i] = new cNES_Controller();

	for (int i=0;i<16;i++) pDID[i] = NULL;

	ZeroMemory(&Buttons[0][0],sizeof(Buttons));
	
	DirectInput8Create(hInst, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&pDI, NULL); 
	pDI->CreateDevice(GUID_SysKeyboard, &pDID[0], NULL);
	pDID[0]->SetDataFormat(&c_dfDIKeyboard);
	pDID[0]->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	sprintf(Conts->DeviceName[0],"Keyboard");
	DeviceType[0] = CT_KEYBOARD;
	NumDevices = 1;

	pDI->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoysticksCallback, NULL, DIEDFL_ATTACHEDONLY);
}

void cNES_Controllers::SetKeys(int Keys[4][32])
{
	memcpy(&Buttons[0][0], &Keys[0][0], sizeof(Buttons));

	for (int i=0;i<16;i++)
		DeviceUsed[i] = false;

	for (int i=0;i<4;i++)
		for (int h=0;h<32;h++)
			DeviceUsed[(Keys[i][h] & 0x000F0000) >> 16] = true;
}

void cNES_Controllers::Acquire(int DeviceNum)
{	pDID[DeviceNum]->Acquire(); }

void cNES_Controllers::UnAcquire(int DeviceNum)
{	pDID[DeviceNum]->Unacquire(); }

void cNES_Controllers::UpdateInput()
{
	char     KBBuffer[256];
	ZeroMemory(&KBBuffer[0],sizeof(KBBuffer));
	DIJOYSTATE2 JoyState[16];
	ZeroMemory(&JoyState,sizeof(JoyState));
	
	HRESULT hrt;
	hrt = pDID[0]->GetDeviceState(sizeof(KBBuffer),(LPVOID)&KBBuffer);
	if ((hrt == DIERR_INPUTLOST) || (hrt == DIERR_NOTACQUIRED))
	{	Acquire(0); ZeroMemory(&KBBuffer[0],sizeof(KBBuffer)); }

	for (int i=1;i<NumDevices;i++)
		if (DeviceUsed[i])
		{
			switch (DeviceType[i])
			{
			case CT_JOYSTICK:
				hrt = pDID[i]->Poll();
				if ((hrt == DIERR_INPUTLOST) || (hrt == DIERR_NOTACQUIRED))
				{	Acquire(i); }

				hrt = pDID[i]->GetDeviceState(sizeof(DIJOYSTATE2), &JoyState[i]);
				if ((hrt == DIERR_INPUTLOST) || (hrt == DIERR_NOTACQUIRED))
				{	Acquire(i); ZeroMemory(&JoyState[i],sizeof(DIJOYSTATE2)); }
				break;
			}
		}

	if (KBBuffer[DIK_1] & 0x80) *StateSlot = 1;
	if (KBBuffer[DIK_2] & 0x80) *StateSlot = 2;
	if (KBBuffer[DIK_3] & 0x80) *StateSlot = 3;
	if (KBBuffer[DIK_4] & 0x80) *StateSlot = 4;
	if (KBBuffer[DIK_5] & 0x80) *StateSlot = 5;
	if (KBBuffer[DIK_6] & 0x80) *StateSlot = 6;
	if (KBBuffer[DIK_7] & 0x80) *StateSlot = 7;
	if (KBBuffer[DIK_8] & 0x80) *StateSlot = 8;
	if (KBBuffer[DIK_9] & 0x80) *StateSlot = 9;
	if (KBBuffer[DIK_0] & 0x80) *StateSlot = 0;

	int DevNum;
	for (int p=0;p<2;p++)
	{
		//Buttons
		Cont[p]->Bits = 0;
		for (int i=0;i<4;i++)
		{
			DevNum = (Buttons[p][i] & 0x000F0000) >> 16;
			switch (DeviceType[DevNum]) {
				case CT_KEYBOARD: if (KBBuffer[Buttons[p][i] & 0xFF] & 0x80) Cont[p]->Bits |= (1 << i); break;
				case CT_JOYSTICK: if (JoyState[DevNum].rgbButtons[Buttons[p][i] & 0x7F] & 0x80) Cont[p]->Bits |= (1 << i); break;
			}
		}

		//Arrows
		DevNum = (Buttons[p][4] & 0x000F0000) >> 16;		//Up
		switch (DeviceType[DevNum]) {
			case CT_KEYBOARD: if (KBBuffer[Buttons[p][4] & 0xFF] & 0x80) Cont[p]->Bits |= 0x10; break;
			case CT_JOYSTICK: if (JoyState[DevNum].lY < 0x4000) Cont[p]->Bits |= 0x10; break;
		}
		DevNum = (Buttons[p][5] & 0x000F0000) >> 16;		//Down
		switch (DeviceType[DevNum]) {
			case CT_KEYBOARD: if (KBBuffer[Buttons[p][5] & 0xFF] & 0x80) Cont[p]->Bits |= 0x20; break;
			case CT_JOYSTICK: if (JoyState[DevNum].lY > 0xC000) Cont[p]->Bits |= 0x20; break;
		}
		DevNum = (Buttons[p][6] & 0x000F0000) >> 16;		//Left
		switch (DeviceType[DevNum]) {
			case CT_KEYBOARD: if (KBBuffer[Buttons[p][6] & 0xFF] & 0x80) Cont[p]->Bits |= 0x40; break;
			case CT_JOYSTICK: if (JoyState[DevNum].lX < 0x4000) Cont[p]->Bits |= 0x40; break;
		}
		DevNum = (Buttons[p][7] & 0x000F0000) >> 16;		//Right
		switch (DeviceType[DevNum]) {
			case CT_KEYBOARD: if (KBBuffer[Buttons[p][7] & 0xFF] & 0x80) Cont[p]->Bits |= 0x80; break;
			case CT_JOYSTICK: if (JoyState[DevNum].lX > 0xC000) Cont[p]->Bits |= 0x80; break;
		}
	}
}

BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE* pdidInstance, VOID* pContext)
{
    HRESULT hr;

    // Obtain an interface to the enumerated joystick.
    hr = Conts->pDI->CreateDevice(pdidInstance->guidInstance, &Conts->pDID[Conts->NumDevices], NULL);
    if(FAILED(hr)) 
        return DIENUM_CONTINUE;

	Conts->pDID[Conts->NumDevices]->SetDataFormat(&c_dfDIJoystick2);
	Conts->pDID[Conts->NumDevices]->SetCooperativeLevel(gData->MainWnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND);
	Conts->DeviceType[Conts->NumDevices] = CT_JOYSTICK;
	
	sprintf(Conts->DeviceName[Conts->NumDevices],"%s",pdidInstance->tszProductName);

	DIDEVCAPS tpc;
	tpc.dwSize = sizeof(tpc);
	Conts->pDID[Conts->NumDevices]->GetCapabilities(&tpc);
	Conts->NumButtons[Conts->NumDevices] = tpc.dwButtons;

	Conts->NumDevices++;

    return DIENUM_CONTINUE;
}

void cNES_Controllers::OpenConfig()
{
	ConfigWnd = CreateDialog(gData->hInst, (LPCTSTR) IDD_NES_CONTROLLERS, gData->MainWnd, ControllerProc);
	ShowWindow(ConfigWnd, SW_SHOW);

	HWND TPWND = GetDlgItem(ConfigWnd, IDC_NES_CONTROLLERS_PLAYER_COMBO);
	char tps[20];
	sprintf(tps, "Controller 1"); SendMessage(TPWND, CB_ADDSTRING, 0, (LPARAM) &tps);
	sprintf(tps, "Controller 2"); SendMessage(TPWND, CB_ADDSTRING, 0, (LPARAM) &tps);
//	sprintf(tps, "Controller 3"); SendMessage(TPWND, CB_ADDSTRING, 0, (LPARAM) &tps);
//	sprintf(tps, "Controller 4"); SendMessage(TPWND, CB_ADDSTRING, 0, (LPARAM) &tps);
	
	SendMessage(TPWND, CB_SETCURSEL, 0, 0);
	
	UpdateConfigBox();

	SelectedPlayer = 0;
}

BOOL CALLBACK ControllerProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	switch (uMsg)
	{
		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId)
			{
			case IDC_NES_CNT_AUTOCONFIGTO:		//Autoconfigure!
				{
					int DevToConf = SendMessage(GetDlgItem(hwndDlg,IDC_NES_CNT_AUTOCONFIGCOMBO), CB_GETCURSEL, 0, 0);
					switch (SelectedPlayer)
					{
					case 0 :
						if (strcmp(Conts->DeviceName[DevToConf],"Keyboard") == 0)
						{
							Conts->Buttons[0][KEY_NES_A] = DIK_Z;
							Conts->Buttons[0][KEY_NES_B] = DIK_X;
							Conts->Buttons[0][KEY_NES_SELECT] = DIK_C;
							Conts->Buttons[0][KEY_NES_START] = DIK_V;
							Conts->Buttons[0][KEY_NES_UP] = DIK_UP;
							Conts->Buttons[0][KEY_NES_DOWN] = DIK_DOWN;
							Conts->Buttons[0][KEY_NES_LEFT] = DIK_LEFT;
							Conts->Buttons[0][KEY_NES_RIGHT] = DIK_RIGHT;
							UpdateConfigBox();
							SendMessage(GetDlgItem(hwndDlg,IDC_NES_CNT_AUTOCONFIGCOMBO), CB_SETCURSEL, DevToConf, 0);
							Conts->SetKeys(Conts->Buttons); 
							break;
						}

						if (strcmp(Conts->DeviceName[DevToConf],"Gravis GamePad Pro (GamePort)") == 0)
						{
							Conts->Buttons[0][KEY_NES_A] = 0x00000002 | (DevToConf << 16);
							Conts->Buttons[0][KEY_NES_B] = 0x00000001 | (DevToConf << 16);
							Conts->Buttons[0][KEY_NES_SELECT] = 0x00000008 | (DevToConf << 16);
							Conts->Buttons[0][KEY_NES_START] = 0x00000009 | (DevToConf << 16);
							Conts->Buttons[0][KEY_NES_UP] = 0x00000000 | (DevToConf << 16);
							Conts->Buttons[0][KEY_NES_DOWN] = 0x00000000 | (DevToConf << 16);
							Conts->Buttons[0][KEY_NES_LEFT] = 0x00000000 | (DevToConf << 16);
							Conts->Buttons[0][KEY_NES_RIGHT] = 0x00000000 | (DevToConf << 16);
							UpdateConfigBox();
							SendMessage(GetDlgItem(hwndDlg,IDC_NES_CNT_AUTOCONFIGCOMBO), CB_SETCURSEL, DevToConf, 0);
							Conts->SetKeys(Conts->Buttons); 
							break;
						}

						if (strcmp(Conts->DeviceName[DevToConf],"Gravis GamePad Pro") == 0)
						{
							Conts->Buttons[0][KEY_NES_A] = 0x00000002 | (DevToConf << 16);
							Conts->Buttons[0][KEY_NES_B] = 0x00000001 | (DevToConf << 16);
							Conts->Buttons[0][KEY_NES_SELECT] = 0x00000008 | (DevToConf << 16);
							Conts->Buttons[0][KEY_NES_START] = 0x00000009 | (DevToConf << 16);
							Conts->Buttons[0][KEY_NES_UP] = 0x00000000 | (DevToConf << 16);
							Conts->Buttons[0][KEY_NES_DOWN] = 0x00000000 | (DevToConf << 16);
							Conts->Buttons[0][KEY_NES_LEFT] = 0x00000000 | (DevToConf << 16);
							Conts->Buttons[0][KEY_NES_RIGHT] = 0x00000000 | (DevToConf << 16);
							UpdateConfigBox();
							SendMessage(GetDlgItem(hwndDlg,IDC_NES_CNT_AUTOCONFIGCOMBO), CB_SETCURSEL, DevToConf, 0);
							Conts->SetKeys(Conts->Buttons); 
							break;
						}

						if (strcmp(Conts->DeviceName[DevToConf],"Interact Gaming Device") == 0)
						{
							Conts->Buttons[0][KEY_NES_A] = 0x00000004 | (DevToConf << 16);
							Conts->Buttons[0][KEY_NES_B] = 0x00000003 | (DevToConf << 16);
							Conts->Buttons[0][KEY_NES_SELECT] = 0x00000000 | (DevToConf << 16);
							Conts->Buttons[0][KEY_NES_START] = 0x00000001 | (DevToConf << 16);
							Conts->Buttons[0][KEY_NES_UP] = 0x00000000 | (DevToConf << 16);
							Conts->Buttons[0][KEY_NES_DOWN] = 0x00000000 | (DevToConf << 16);
							Conts->Buttons[0][KEY_NES_LEFT] = 0x00000000 | (DevToConf << 16);
							Conts->Buttons[0][KEY_NES_RIGHT] = 0x00000000 | (DevToConf << 16);
							UpdateConfigBox();
							SendMessage(GetDlgItem(hwndDlg,IDC_NES_CNT_AUTOCONFIGCOMBO), CB_SETCURSEL, DevToConf, 0);
							Conts->SetKeys(Conts->Buttons); 
							break;
						}

						if (strcmp(Conts->DeviceName[DevToConf],"Xterminator Digital Gamepad") == 0)
						{
							Conts->Buttons[0][KEY_NES_A] = 0x00000001 | (DevToConf << 16);
							Conts->Buttons[0][KEY_NES_B] = 0x00000000 | (DevToConf << 16);
							Conts->Buttons[0][KEY_NES_SELECT] = 0x00000003 | (DevToConf << 16);
							Conts->Buttons[0][KEY_NES_START] = 0x00000009 | (DevToConf << 16);
							Conts->Buttons[0][KEY_NES_UP] = 0x00000000 | (DevToConf << 16);
							Conts->Buttons[0][KEY_NES_DOWN] = 0x00000000 | (DevToConf << 16);
							Conts->Buttons[0][KEY_NES_LEFT] = 0x00000000 | (DevToConf << 16);
							Conts->Buttons[0][KEY_NES_RIGHT] = 0x00000000 | (DevToConf << 16);
							UpdateConfigBox();
							SendMessage(GetDlgItem(hwndDlg,IDC_NES_CNT_AUTOCONFIGCOMBO), CB_SETCURSEL, DevToConf, 0);
							Conts->SetKeys(Conts->Buttons); 
							break;
						}

						MessageBox(hwndDlg,"Sorry, Device Not Supported Yet!","N0p3",MB_OK);
						break;
					case 1 :
						if (strcmp(Conts->DeviceName[DevToConf],"Keyboard") == 0)
						{
							Conts->Buttons[1][KEY_NES_A] = DIK_U;
							Conts->Buttons[1][KEY_NES_B] = DIK_I;
							Conts->Buttons[1][KEY_NES_SELECT] = DIK_O;
							Conts->Buttons[1][KEY_NES_START] = DIK_P;
							Conts->Buttons[1][KEY_NES_UP] = DIK_HOME;
							Conts->Buttons[1][KEY_NES_DOWN] = DIK_END;
							Conts->Buttons[1][KEY_NES_LEFT] = DIK_DELETE;
							Conts->Buttons[1][KEY_NES_RIGHT] = DIK_NEXT;		//Page Down?
							UpdateConfigBox();
							SendMessage(GetDlgItem(hwndDlg,IDC_NES_CNT_AUTOCONFIGCOMBO), CB_SETCURSEL, DevToConf, 0);
							Conts->SetKeys(Conts->Buttons); 
							break;
						}

						if (strcmp(Conts->DeviceName[DevToConf],"Gravis GamePad Pro (GamePort)") == 0)
						{
							Conts->Buttons[1][KEY_NES_A] = 0x00000001 | (DevToConf << 16);
							Conts->Buttons[1][KEY_NES_B] = 0x00000002 | (DevToConf << 16);
							Conts->Buttons[1][KEY_NES_SELECT] = 0x00000008 | (DevToConf << 16);
							Conts->Buttons[1][KEY_NES_START] = 0x00000009 | (DevToConf << 16);
							Conts->Buttons[1][KEY_NES_UP] = 0x00000000 | (DevToConf << 16);
							Conts->Buttons[1][KEY_NES_DOWN] = 0x00000000 | (DevToConf << 16);
							Conts->Buttons[1][KEY_NES_LEFT] = 0x00000000 | (DevToConf << 16);
							Conts->Buttons[1][KEY_NES_RIGHT] = 0x00000000 | (DevToConf << 16);
							UpdateConfigBox();
							SendMessage(GetDlgItem(hwndDlg,IDC_NES_CNT_AUTOCONFIGCOMBO), CB_SETCURSEL, DevToConf, 0);
							Conts->SetKeys(Conts->Buttons); 
							break;
						}

						if (strcmp(Conts->DeviceName[DevToConf],"Gravis GamePad Pro") == 0)
						{
							Conts->Buttons[1][KEY_NES_A] = 0x00000002 | (DevToConf << 16);
							Conts->Buttons[1][KEY_NES_B] = 0x00000001 | (DevToConf << 16);
							Conts->Buttons[1][KEY_NES_SELECT] = 0x00000008 | (DevToConf << 16);
							Conts->Buttons[1][KEY_NES_START] = 0x00000009 | (DevToConf << 16);
							Conts->Buttons[1][KEY_NES_UP] = 0x00000000 | (DevToConf << 16);
							Conts->Buttons[1][KEY_NES_DOWN] = 0x00000000 | (DevToConf << 16);
							Conts->Buttons[1][KEY_NES_LEFT] = 0x00000000 | (DevToConf << 16);
							Conts->Buttons[1][KEY_NES_RIGHT] = 0x00000000 | (DevToConf << 16);
							UpdateConfigBox();
							SendMessage(GetDlgItem(hwndDlg,IDC_NES_CNT_AUTOCONFIGCOMBO), CB_SETCURSEL, DevToConf, 0);
							Conts->SetKeys(Conts->Buttons); 
							break;
						}

						if (strcmp(Conts->DeviceName[DevToConf],"Interact Gaming Device") == 0)
						{
							Conts->Buttons[1][KEY_NES_A] = 0x00000004 | (DevToConf << 16);
							Conts->Buttons[1][KEY_NES_B] = 0x00000003 | (DevToConf << 16);
							Conts->Buttons[1][KEY_NES_SELECT] = 0x00000000 | (DevToConf << 16);
							Conts->Buttons[1][KEY_NES_START] = 0x00000001 | (DevToConf << 16);
							Conts->Buttons[1][KEY_NES_UP] = 0x00000000 | (DevToConf << 16);
							Conts->Buttons[1][KEY_NES_DOWN] = 0x00000000 | (DevToConf << 16);
							Conts->Buttons[1][KEY_NES_LEFT] = 0x00000000 | (DevToConf << 16);
							Conts->Buttons[1][KEY_NES_RIGHT] = 0x00000000 | (DevToConf << 16);
							UpdateConfigBox();
							SendMessage(GetDlgItem(hwndDlg,IDC_NES_CNT_AUTOCONFIGCOMBO), CB_SETCURSEL, DevToConf, 0);
							Conts->SetKeys(Conts->Buttons); 
							break;
						}

						if (strcmp(Conts->DeviceName[DevToConf],"Xterminator Digital Gamepad") == 0)
						{
							Conts->Buttons[1][KEY_NES_A] = 0x00000001 | (DevToConf << 16);
							Conts->Buttons[1][KEY_NES_B] = 0x00000000 | (DevToConf << 16);
							Conts->Buttons[1][KEY_NES_SELECT] = 0x00000003 | (DevToConf << 16);
							Conts->Buttons[1][KEY_NES_START] = 0x00000009 | (DevToConf << 16);
							Conts->Buttons[1][KEY_NES_UP] = 0x00000000 | (DevToConf << 16);
							Conts->Buttons[1][KEY_NES_DOWN] = 0x00000000 | (DevToConf << 16);
							Conts->Buttons[1][KEY_NES_LEFT] = 0x00000000 | (DevToConf << 16);
							Conts->Buttons[1][KEY_NES_RIGHT] = 0x00000000 | (DevToConf << 16);
							UpdateConfigBox();
							SendMessage(GetDlgItem(hwndDlg,IDC_NES_CNT_AUTOCONFIGCOMBO), CB_SETCURSEL, DevToConf, 0);
							Conts->SetKeys(Conts->Buttons); 
							break;
						}

						MessageBox(hwndDlg,"Sorry, Device Not Supported Yet!","N0p3",MB_OK);
						break;
					}
				}
				break;
			case ID_CONTROLLERDIALOG_OK:
				DestroyWindow(hwndDlg);
				break;
			case IDC_NES_CONTROLLERS_PLAYER_COMBO:
				if (wmEvent == CBN_SELCHANGE)
				{
					SelectedPlayer = SendMessage((HWND) lParam, CB_GETCURSEL, 0, 0);
					UpdateConfigBox();
				}
				break;
			case IDC_NES_CNT_A_DEVICE:		if (wmEvent == CBN_SELCHANGE) UpdateKeyList(); break;
			case IDC_NES_CNT_B_DEVICE:		if (wmEvent == CBN_SELCHANGE) UpdateKeyList(); break;
			case IDC_NES_CNT_SEL_DEVICE:	if (wmEvent == CBN_SELCHANGE) UpdateKeyList(); break;
			case IDC_NES_CNT_STR_DEVICE:	if (wmEvent == CBN_SELCHANGE) UpdateKeyList(); break;
			case IDC_NES_CNT_UP_DEVICE:		if (wmEvent == CBN_SELCHANGE) UpdateKeyList(); break;
			case IDC_NES_CNT_DOWN_DEVICE:	if (wmEvent == CBN_SELCHANGE) UpdateKeyList(); break;
			case IDC_NES_CNT_LEFT_DEVICE:	if (wmEvent == CBN_SELCHANGE) UpdateKeyList(); break;
			case IDC_NES_CNT_RIGHT_DEVICE:	if (wmEvent == CBN_SELCHANGE) UpdateKeyList(); break;
			
			case IDC_NES_CNT_A_KEY:		if (wmEvent == CBN_SELCHANGE) { Conts->Buttons[SelectedPlayer][KEY_NES_A] = SendMessage((HWND) lParam, CB_GETCURSEL, 0, 0) | (SendMessage(GetDlgItem(hwndDlg,IDC_NES_CNT_A_DEVICE), CB_GETCURSEL, 0, 0) << 16); Conts->SetKeys(Conts->Buttons); } break;
			case IDC_NES_CNT_B_KEY:		if (wmEvent == CBN_SELCHANGE) { Conts->Buttons[SelectedPlayer][KEY_NES_B] = SendMessage((HWND) lParam, CB_GETCURSEL, 0, 0) | (SendMessage(GetDlgItem(hwndDlg,IDC_NES_CNT_B_DEVICE), CB_GETCURSEL, 0, 0) << 16); Conts->SetKeys(Conts->Buttons); } break;
			case IDC_NES_CNT_SEL_KEY:	if (wmEvent == CBN_SELCHANGE) { Conts->Buttons[SelectedPlayer][KEY_NES_SELECT] = SendMessage((HWND) lParam, CB_GETCURSEL, 0, 0) | (SendMessage(GetDlgItem(hwndDlg,IDC_NES_CNT_SEL_DEVICE), CB_GETCURSEL, 0, 0) << 16); Conts->SetKeys(Conts->Buttons); } break;
			case IDC_NES_CNT_STR_KEY:	if (wmEvent == CBN_SELCHANGE) { Conts->Buttons[SelectedPlayer][KEY_NES_START] = SendMessage((HWND) lParam, CB_GETCURSEL, 0, 0) | (SendMessage(GetDlgItem(hwndDlg,IDC_NES_CNT_STR_DEVICE), CB_GETCURSEL, 0, 0) << 16); Conts->SetKeys(Conts->Buttons); } break;
			case IDC_NES_CNT_UP_KEY:	if (wmEvent == CBN_SELCHANGE) { Conts->Buttons[SelectedPlayer][KEY_NES_UP] = SendMessage((HWND) lParam, CB_GETCURSEL, 0, 0) | (SendMessage(GetDlgItem(hwndDlg,IDC_NES_CNT_UP_DEVICE), CB_GETCURSEL, 0, 0) << 16); Conts->SetKeys(Conts->Buttons); } break;
			case IDC_NES_CNT_DOWN_KEY:	if (wmEvent == CBN_SELCHANGE) { Conts->Buttons[SelectedPlayer][KEY_NES_DOWN] = SendMessage((HWND) lParam, CB_GETCURSEL, 0, 0) | (SendMessage(GetDlgItem(hwndDlg,IDC_NES_CNT_DOWN_DEVICE), CB_GETCURSEL, 0, 0) << 16); Conts->SetKeys(Conts->Buttons); } break;
			case IDC_NES_CNT_LEFT_KEY:	if (wmEvent == CBN_SELCHANGE) { Conts->Buttons[SelectedPlayer][KEY_NES_LEFT] = SendMessage((HWND) lParam, CB_GETCURSEL, 0, 0) | (SendMessage(GetDlgItem(hwndDlg,IDC_NES_CNT_LEFT_DEVICE), CB_GETCURSEL, 0, 0) << 16); Conts->SetKeys(Conts->Buttons); } break;
			case IDC_NES_CNT_RIGHT_KEY:	if (wmEvent == CBN_SELCHANGE) { Conts->Buttons[SelectedPlayer][KEY_NES_RIGHT] = SendMessage((HWND) lParam, CB_GETCURSEL, 0, 0) | (SendMessage(GetDlgItem(hwndDlg,IDC_NES_CNT_RIGHT_DEVICE), CB_GETCURSEL, 0, 0) << 16); Conts->SetKeys(Conts->Buttons); } break;
			};
			break;
	}

	return false;
}

void UpdateConfigBox()
{
	HWND TPWND;
	
	TPWND = GetDlgItem(ConfigWnd, IDC_NES_CNT_A_DEVICE);
	SendMessage(TPWND, CB_RESETCONTENT,0,0);
	for (int i=0;i<Conts->NumDevices;i++) SendMessage(TPWND, CB_ADDSTRING, 0, (LPARAM) &Conts->DeviceName[i]);
	SendMessage(TPWND, CB_SETCURSEL, (Conts->Buttons[SelectedPlayer][KEY_NES_A] & 0x000F0000) >> 16, 0);
	TPWND = GetDlgItem(ConfigWnd, IDC_NES_CNT_B_DEVICE);
	SendMessage(TPWND, CB_RESETCONTENT,0,0);
	for (int i=0;i<Conts->NumDevices;i++) SendMessage(TPWND, CB_ADDSTRING, 0, (LPARAM) &Conts->DeviceName[i]);
	SendMessage(TPWND, CB_SETCURSEL, (Conts->Buttons[SelectedPlayer][KEY_NES_B] & 0x000F0000) >> 16, 0);
	TPWND = GetDlgItem(ConfigWnd, IDC_NES_CNT_SEL_DEVICE);
	SendMessage(TPWND, CB_RESETCONTENT,0,0);
	for (int i=0;i<Conts->NumDevices;i++) SendMessage(TPWND, CB_ADDSTRING, 0, (LPARAM) &Conts->DeviceName[i]);
	SendMessage(TPWND, CB_SETCURSEL, (Conts->Buttons[SelectedPlayer][KEY_NES_SELECT] & 0x000F0000) >> 16, 0);
	TPWND = GetDlgItem(ConfigWnd, IDC_NES_CNT_STR_DEVICE);
	SendMessage(TPWND, CB_RESETCONTENT,0,0);
	for (int i=0;i<Conts->NumDevices;i++) SendMessage(TPWND, CB_ADDSTRING, 0, (LPARAM) &Conts->DeviceName[i]);
	SendMessage(TPWND, CB_SETCURSEL, (Conts->Buttons[SelectedPlayer][KEY_NES_START] & 0x000F0000) >> 16, 0);
	
	TPWND = GetDlgItem(ConfigWnd, IDC_NES_CNT_UP_DEVICE);
	SendMessage(TPWND, CB_RESETCONTENT,0,0);
	for (int i=0;i<Conts->NumDevices;i++) SendMessage(TPWND, CB_ADDSTRING, 0, (LPARAM) &Conts->DeviceName[i]);
	SendMessage(TPWND, CB_SETCURSEL, (Conts->Buttons[SelectedPlayer][KEY_NES_UP] & 0x000F0000) >> 16, 0);
	TPWND = GetDlgItem(ConfigWnd, IDC_NES_CNT_DOWN_DEVICE);
	SendMessage(TPWND, CB_RESETCONTENT,0,0);
	for (int i=0;i<Conts->NumDevices;i++) SendMessage(TPWND, CB_ADDSTRING, 0, (LPARAM) &Conts->DeviceName[i]);
	SendMessage(TPWND, CB_SETCURSEL, (Conts->Buttons[SelectedPlayer][KEY_NES_DOWN] & 0x000F0000) >> 16, 0);
	TPWND = GetDlgItem(ConfigWnd, IDC_NES_CNT_LEFT_DEVICE);
	SendMessage(TPWND, CB_RESETCONTENT,0,0);
	for (int i=0;i<Conts->NumDevices;i++) SendMessage(TPWND, CB_ADDSTRING, 0, (LPARAM) &Conts->DeviceName[i]);
	SendMessage(TPWND, CB_SETCURSEL, (Conts->Buttons[SelectedPlayer][KEY_NES_LEFT] & 0x000F0000) >> 16, 0);
	TPWND = GetDlgItem(ConfigWnd, IDC_NES_CNT_RIGHT_DEVICE);
	SendMessage(TPWND, CB_RESETCONTENT,0,0);
	for (int i=0;i<Conts->NumDevices;i++) SendMessage(TPWND, CB_ADDSTRING, 0, (LPARAM) &Conts->DeviceName[i]);
	SendMessage(TPWND, CB_SETCURSEL, (Conts->Buttons[SelectedPlayer][KEY_NES_RIGHT] & 0x000F0000) >> 16, 0);
	
	TPWND = GetDlgItem(ConfigWnd, IDC_NES_CNT_AUTOCONFIGCOMBO);
	SendMessage(TPWND, CB_RESETCONTENT,0,0);
	for (int i=0;i<Conts->NumDevices;i++) SendMessage(TPWND, CB_ADDSTRING, 0, (LPARAM) &Conts->DeviceName[i]);
	SendMessage(TPWND, CB_SETCURSEL, Conts->NumDevices-1, 0);
	
	UpdateKeyList();
}

void UpdateKeyList()
{
	HWND TPWND[8] =
	{
		GetDlgItem(ConfigWnd, IDC_NES_CNT_A_KEY),
		GetDlgItem(ConfigWnd, IDC_NES_CNT_B_KEY),
		GetDlgItem(ConfigWnd, IDC_NES_CNT_SEL_KEY),
		GetDlgItem(ConfigWnd, IDC_NES_CNT_STR_KEY),
		GetDlgItem(ConfigWnd, IDC_NES_CNT_UP_KEY),
		GetDlgItem(ConfigWnd, IDC_NES_CNT_DOWN_KEY),
		GetDlgItem(ConfigWnd, IDC_NES_CNT_LEFT_KEY),
		GetDlgItem(ConfigWnd, IDC_NES_CNT_RIGHT_KEY)
	};
	HWND DevWnd[8] =
	{
		GetDlgItem(ConfigWnd, IDC_NES_CNT_A_DEVICE),
		GetDlgItem(ConfigWnd, IDC_NES_CNT_B_DEVICE),
		GetDlgItem(ConfigWnd, IDC_NES_CNT_SEL_DEVICE),
		GetDlgItem(ConfigWnd, IDC_NES_CNT_STR_DEVICE),
		GetDlgItem(ConfigWnd, IDC_NES_CNT_UP_DEVICE),
		GetDlgItem(ConfigWnd, IDC_NES_CNT_DOWN_DEVICE),
		GetDlgItem(ConfigWnd, IDC_NES_CNT_LEFT_DEVICE),
		GetDlgItem(ConfigWnd, IDC_NES_CNT_RIGHT_DEVICE)
	};
	int DevNum[8] =
	{
		SendMessage(DevWnd[0], CB_GETCURSEL, 0, 0),
		SendMessage(DevWnd[1], CB_GETCURSEL, 0, 0),
		SendMessage(DevWnd[2], CB_GETCURSEL, 0, 0),
		SendMessage(DevWnd[3], CB_GETCURSEL, 0, 0),
		SendMessage(DevWnd[4], CB_GETCURSEL, 0, 0),
		SendMessage(DevWnd[5], CB_GETCURSEL, 0, 0),
		SendMessage(DevWnd[6], CB_GETCURSEL, 0, 0),
		SendMessage(DevWnd[7], CB_GETCURSEL, 0, 0)
	};
	char tps[64]; int bn;

	for (int cur=0;cur<8;cur++)
	{
		SendMessage(TPWND[cur], CB_RESETCONTENT,0,0);
		switch (Conts->DeviceType[DevNum[cur]])
		{
		case CT_KEYBOARD:
			for (bn=0;bn<256;bn++)
			{
				sprintf(tps, "%s", KeyLookup[bn]);
				SendMessage(TPWND[cur], CB_ADDSTRING, 0, (LPARAM) &tps[0]);
			}
			break;
		case CT_JOYSTICK:
			if (cur < 4)
			{
				for (bn=0;bn<Conts->NumButtons[DevNum[cur]];bn++)
				{
					sprintf(tps,"Button %i", bn+1);
					SendMessage(TPWND[cur], CB_ADDSTRING, 0, (LPARAM) &tps[0]);
				}
			} else {
				sprintf(tps,"(Main Axis)", bn+1);
				SendMessage(TPWND[cur], CB_ADDSTRING, 0, (LPARAM) &tps[0]);
			}
			break;
		}

		SendMessage(TPWND[cur], CB_SETCURSEL, Conts->Buttons[SelectedPlayer][cur] & 0x000000FF, 0);
	}
}