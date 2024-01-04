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

#include "Col_Controllers.h"

#include "..\NinthStar.h"

#include "..\Global.h"

HWND Col_ConfigWnd;
int Col_SelectedPlayer;

extern char KeyLookup[256][16];

cCol_Controllers *Conts;

cCol_Controllers::cCol_Controllers(HINSTANCE hInst, HWND hWnd)
{
	Conts = this;
	
	for (int i=0;i<16;i++) pDID[i] = NULL;

	ZeroMemory(&Buttons[0][0],sizeof(Buttons));
	
	DirectInput8Create(hInst, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&pDI, NULL); 
	pDI->CreateDevice(GUID_SysKeyboard, &pDID[0], NULL);
	pDID[0]->SetDataFormat(&c_dfDIKeyboard);
	pDID[0]->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	sprintf(Conts->DeviceName[0],"Keyboard");
	DeviceType[0] = CT_KEYBOARD;
	NumDevices = 1;

	pDI->EnumDevices(DI8DEVCLASS_GAMECTRL, Col_EnumJoysticksCallback, NULL, DIEDFL_ATTACHEDONLY);
}

void cCol_Controllers::SetKeys(int Keys[2][32])
{
	memcpy(&Buttons[0][0], &Keys[0][0], sizeof(Buttons));

	for (int i=0;i<16;i++)
		DeviceUsed[i] = false;

	for (int i=0;i<2;i++)
		for (int h=0;h<32;h++)
			DeviceUsed[(Keys[i][h] & 0x000F0000) >> 16] = true;
}

void cCol_Controllers::Acquire(int DeviceNum)
{	pDID[DeviceNum]->Acquire(); }

void cCol_Controllers::UnAcquire(int DeviceNum)
{	pDID[DeviceNum]->Unacquire(); }

void cCol_Controllers::UpdateInput()
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

/*	if (KBBuffer[DIK_1] & 0x80) *StateSlot = 1;
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
		for (i=0;i<4;i++)
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
	}*/
}

BOOL CALLBACK Col_EnumJoysticksCallback(const DIDEVICEINSTANCE* pdidInstance, VOID* pContext)
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

void cCol_Controllers::OpenConfig()
{
	Col_ConfigWnd = CreateDialog(gData->hInst, (LPCTSTR) IDD_COL_CONTROLLERS, gData->MainWnd, Col_ControllerProc);
	ShowWindow(Col_ConfigWnd, SW_SHOW);

	HWND TPWND = GetDlgItem(Col_ConfigWnd, IDC_COL_CONTROLLERS_PLAYER_COMBO);
	char tps[20];
	sprintf(tps, "Controller 1"); SendMessage(TPWND, CB_ADDSTRING, 0, (LPARAM) &tps);
	sprintf(tps, "Controller 2"); SendMessage(TPWND, CB_ADDSTRING, 0, (LPARAM) &tps);
	
	SendMessage(TPWND, CB_SETCURSEL, 0, 0);
	
	UpdateConfigBox();

	Col_SelectedPlayer = 0;
}

BOOL CALLBACK Col_ControllerProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	switch (uMsg)
	{
		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
/*			switch (wmId)
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
			};*/
			break;
	}

	return false;
}

void Col_UpdateConfigBox()
{
/*	HWND TPWND;
	
	TPWND = GetDlgItem(ConfigWnd, IDC_NES_CNT_A_DEVICE);
	SendMessage(TPWND, CB_RESETCONTENT,0,0);
	for (int i=0;i<Conts->NumDevices;i++) SendMessage(TPWND, CB_ADDSTRING, 0, (LPARAM) &Conts->DeviceName[i]);
	SendMessage(TPWND, CB_SETCURSEL, (Conts->Buttons[SelectedPlayer][KEY_NES_A] & 0x000F0000) >> 16, 0);
	TPWND = GetDlgItem(ConfigWnd, IDC_NES_CNT_B_DEVICE);
	SendMessage(TPWND, CB_RESETCONTENT,0,0);
	for (i=0;i<Conts->NumDevices;i++) SendMessage(TPWND, CB_ADDSTRING, 0, (LPARAM) &Conts->DeviceName[i]);
	SendMessage(TPWND, CB_SETCURSEL, (Conts->Buttons[SelectedPlayer][KEY_NES_B] & 0x000F0000) >> 16, 0);
	TPWND = GetDlgItem(ConfigWnd, IDC_NES_CNT_SEL_DEVICE);
	SendMessage(TPWND, CB_RESETCONTENT,0,0);
	for (i=0;i<Conts->NumDevices;i++) SendMessage(TPWND, CB_ADDSTRING, 0, (LPARAM) &Conts->DeviceName[i]);
	SendMessage(TPWND, CB_SETCURSEL, (Conts->Buttons[SelectedPlayer][KEY_NES_SELECT] & 0x000F0000) >> 16, 0);
	TPWND = GetDlgItem(ConfigWnd, IDC_NES_CNT_STR_DEVICE);
	SendMessage(TPWND, CB_RESETCONTENT,0,0);
	for (i=0;i<Conts->NumDevices;i++) SendMessage(TPWND, CB_ADDSTRING, 0, (LPARAM) &Conts->DeviceName[i]);
	SendMessage(TPWND, CB_SETCURSEL, (Conts->Buttons[SelectedPlayer][KEY_NES_START] & 0x000F0000) >> 16, 0);
	
	TPWND = GetDlgItem(ConfigWnd, IDC_NES_CNT_UP_DEVICE);
	SendMessage(TPWND, CB_RESETCONTENT,0,0);
	for (i=0;i<Conts->NumDevices;i++) SendMessage(TPWND, CB_ADDSTRING, 0, (LPARAM) &Conts->DeviceName[i]);
	SendMessage(TPWND, CB_SETCURSEL, (Conts->Buttons[SelectedPlayer][KEY_NES_UP] & 0x000F0000) >> 16, 0);
	TPWND = GetDlgItem(ConfigWnd, IDC_NES_CNT_DOWN_DEVICE);
	SendMessage(TPWND, CB_RESETCONTENT,0,0);
	for (i=0;i<Conts->NumDevices;i++) SendMessage(TPWND, CB_ADDSTRING, 0, (LPARAM) &Conts->DeviceName[i]);
	SendMessage(TPWND, CB_SETCURSEL, (Conts->Buttons[SelectedPlayer][KEY_NES_DOWN] & 0x000F0000) >> 16, 0);
	TPWND = GetDlgItem(ConfigWnd, IDC_NES_CNT_LEFT_DEVICE);
	SendMessage(TPWND, CB_RESETCONTENT,0,0);
	for (i=0;i<Conts->NumDevices;i++) SendMessage(TPWND, CB_ADDSTRING, 0, (LPARAM) &Conts->DeviceName[i]);
	SendMessage(TPWND, CB_SETCURSEL, (Conts->Buttons[SelectedPlayer][KEY_NES_LEFT] & 0x000F0000) >> 16, 0);
	TPWND = GetDlgItem(ConfigWnd, IDC_NES_CNT_RIGHT_DEVICE);
	SendMessage(TPWND, CB_RESETCONTENT,0,0);
	for (i=0;i<Conts->NumDevices;i++) SendMessage(TPWND, CB_ADDSTRING, 0, (LPARAM) &Conts->DeviceName[i]);
	SendMessage(TPWND, CB_SETCURSEL, (Conts->Buttons[SelectedPlayer][KEY_NES_RIGHT] & 0x000F0000) >> 16, 0);
	
	TPWND = GetDlgItem(ConfigWnd, IDC_NES_CNT_AUTOCONFIGCOMBO);
	SendMessage(TPWND, CB_RESETCONTENT,0,0);
	for (i=0;i<Conts->NumDevices;i++) SendMessage(TPWND, CB_ADDSTRING, 0, (LPARAM) &Conts->DeviceName[i]);
	SendMessage(TPWND, CB_SETCURSEL, Conts->NumDevices-1, 0);*/
	
	Col_UpdateKeyList();
}

void Col_UpdateKeyList()
{
/*	HWND TPWND[8] =
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
	}*/
}