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

#include "A26_PIA.h"

#include "..\Global.h"

extern char KeyLookup[256][16];

HWND A26_ConfigWnd;
int A26_SelectedPlayer;

cA26_PIA *PIA;

cA26_PIA::cA26_PIA()
{
	PIA = this;
	Paddles = 0;
	
	FullInterval = 1*3;
	CurrInterval = 1*3;
	Looped = false;
	Counter = 0xFF;

	SWCHB = 1 | 2 | 8;

	for (int i=0;i<16;i++) pDID[i] = NULL;

	ZeroMemory(&Buttons[0][0],sizeof(Buttons));

	DirectInput8Create(gData->hInst, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&pDI, NULL); 
	pDI->CreateDevice(GUID_SysKeyboard, &pDID[0], NULL);
	pDID[0]->SetDataFormat(&c_dfDIKeyboard);
	pDID[0]->SetCooperativeLevel(gData->MainWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	sprintf(DeviceName[0],"Keyboard");
	DeviceType[0] = CT_KEYBOARD;
	NumDevices = 1;

	pDI->EnumDevices(DI8DEVCLASS_GAMECTRL, A26_EnumJoysticksCallback, NULL, DIEDFL_ATTACHEDONLY);
}

void cA26_PIA::SetKeys(int Keys[4][32])
{
	memcpy(&Buttons[0][0], &Keys[0][0], sizeof(Buttons));

	for (int i=0;i<16;i++)
		DeviceUsed[i] = false;

	for (int i=0;i<2;i++)
		for (int h=0;h<32;h++)
			DeviceUsed[(Keys[i][h] & 0x000F0000) >> 16] = true;
}

void cA26_PIA::Acquire(int DeviceNum)
{	pDID[DeviceNum]->Acquire(); }

void cA26_PIA::UnAcquire(int DeviceNum)
{	pDID[DeviceNum]->Unacquire(); }

void cA26_PIA::UpdateInput()
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

	SWCHB &= ~0x03;
	if (!(KBBuffer[DIK_HOME] & 0x80)) SWCHB |= 1;
	if (!(KBBuffer[DIK_PGUP] & 0x80)) SWCHB |= 2;

/*	if (KBBuffer[DIK_1] & 0x80) *StateSlot = 1;
	if (KBBuffer[DIK_2] & 0x80) *StateSlot = 2;
	if (KBBuffer[DIK_3] & 0x80) *StateSlot = 3;
	if (KBBuffer[DIK_4] & 0x80) *StateSlot = 4;
	if (KBBuffer[DIK_5] & 0x80) *StateSlot = 5;
	if (KBBuffer[DIK_6] & 0x80) *StateSlot = 6;
	if (KBBuffer[DIK_7] & 0x80) *StateSlot = 7;
	if (KBBuffer[DIK_8] & 0x80) *StateSlot = 8;
	if (KBBuffer[DIK_9] & 0x80) *StateSlot = 9;
	if (KBBuffer[DIK_0] & 0x80) *StateSlot = 0;*/

	int DevNum;
	int PLim = (Paddles) ? 4 : 2;
	SWCHA = 0;
	int PSpot[4] = { 0x80, 0x40, 0x8, 0x4 };
	bool BC;
	for (int p=0;p<PLim;p++)
	{
		//Buttons
		if (Paddles)
		{
			DevNum = (Buttons[p][0] & 0x000F0000) >> 16;
			switch (DeviceType[DevNum]) {
				case CT_KEYBOARD: if (KBBuffer[Buttons[p][0] & 0xFF] & 0x80) SWCHA |= PSpot[p]; break;
				case CT_JOYSTICK: if (JoyState[DevNum].rgbButtons[Buttons[p][0] & 0x7F] & 0x80) SWCHA |= PSpot[p]; break;
			}
		} else {
			DevNum = (Buttons[p][0] & 0x000F0000) >> 16;
			BC = false;
			switch (DeviceType[DevNum]) {
				case CT_KEYBOARD: if (KBBuffer[Buttons[p][0] & 0xFF] & 0x80) BC = true; break;
				case CT_JOYSTICK: if (JoyState[DevNum].rgbButtons[Buttons[p][0] & 0x7F] & 0x80) BC = true; break;
			}
			if (*VBLANK & 0x40)
			{
				if (BC) ((p) ? INPT5 : INPT4) = 0;
			} else {
				if (BC) {
					((p) ? INPT5 : INPT4) = 0x80;
				} else {
					((p) ? INPT5 : INPT4) = 0;
				}
			}
		}

/*		//Arrows
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
		}*/
	}
}

BOOL CALLBACK A26_EnumJoysticksCallback(const DIDEVICEINSTANCE* pdidInstance, VOID* pContext)
{
    HRESULT hr;

    // Obtain an interface to the enumerated joystick.
    hr = PIA->pDI->CreateDevice(pdidInstance->guidInstance, &PIA->pDID[PIA->NumDevices], NULL);
    if(FAILED(hr)) 
        return DIENUM_CONTINUE;

	PIA->pDID[PIA->NumDevices]->SetDataFormat(&c_dfDIJoystick2);
	PIA->pDID[PIA->NumDevices]->SetCooperativeLevel(gData->MainWnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND);
	PIA->DeviceType[PIA->NumDevices] = CT_JOYSTICK;
	
	sprintf(PIA->DeviceName[PIA->NumDevices],"%s",pdidInstance->tszProductName);

	DIDEVCAPS tpc;
	tpc.dwSize = sizeof(tpc);
	PIA->pDID[PIA->NumDevices]->GetCapabilities(&tpc);
	PIA->NumButtons[PIA->NumDevices] = tpc.dwButtons;

	PIA->NumDevices++;

    return DIENUM_CONTINUE;
}

void cA26_PIA::OpenConfig()
{
	A26_ConfigWnd = CreateDialog(gData->hInst, (LPCTSTR) IDD_A26_CONTROLLERS, gData->MainWnd, A26_ControllerProc);
	ShowWindow(A26_ConfigWnd, SW_SHOW);

	HWND TPWND = GetDlgItem(A26_ConfigWnd, IDC_A26_CONTROLLERS_PLAYER_COMBO);
	char tps[20];
	sprintf(tps, "Paddle/Joystick 1"); SendMessage(TPWND, CB_ADDSTRING, 0, (LPARAM) &tps);
	sprintf(tps, "Paddle/Joystick 2"); SendMessage(TPWND, CB_ADDSTRING, 0, (LPARAM) &tps);
	sprintf(tps, "Paddle 3"); SendMessage(TPWND, CB_ADDSTRING, 0, (LPARAM) &tps);
	sprintf(tps, "Paddle 4"); SendMessage(TPWND, CB_ADDSTRING, 0, (LPARAM) &tps);
	
	SendMessage(TPWND, CB_SETCURSEL, 0, 0);
	
	A26_UpdateConfigBox();

	A26_SelectedPlayer = 0;
}

BOOL CALLBACK A26_ControllerProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
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
			case IDC_A26_CNT_AUTOCONFIGTO:		//Autoconfigure!
				{
					int DevToConf = SendMessage(GetDlgItem(hwndDlg,IDC_A26_CNT_AUTOCONFIGCOMBO), CB_GETCURSEL, 0, 0);
				}
				break;
			case ID_CONTROLLERDIALOG_OK:
				DestroyWindow(hwndDlg);
				break;
			case IDC_A26_CONTROLLERS_PLAYER_COMBO:
				if (wmEvent == CBN_SELCHANGE)
				{
					A26_SelectedPlayer = SendMessage((HWND) lParam, CB_GETCURSEL, 0, 0);
					A26_UpdateConfigBox();
				}
				break;
			case IDC_A26_CNT_BUT_DEVICE:	if (wmEvent == CBN_SELCHANGE) A26_UpdateKeyList(); break;
			case IDC_A26_CNT_UP_DEVICE:		if (wmEvent == CBN_SELCHANGE) A26_UpdateKeyList(); break;
			case IDC_A26_CNT_DOWN_DEVICE:	if (wmEvent == CBN_SELCHANGE) A26_UpdateKeyList(); break;
			case IDC_A26_CNT_LEFT_DEVICE:	if (wmEvent == CBN_SELCHANGE) A26_UpdateKeyList(); break;
			case IDC_A26_CNT_RIGHT_DEVICE:	if (wmEvent == CBN_SELCHANGE) A26_UpdateKeyList(); break;
			
			case IDC_A26_CNT_BUT_KEY:	if (wmEvent == CBN_SELCHANGE) { PIA->Buttons[A26_SelectedPlayer][0] = SendMessage((HWND) lParam, CB_GETCURSEL, 0, 0) | (SendMessage(GetDlgItem(hwndDlg,IDC_A26_CNT_BUT_DEVICE), CB_GETCURSEL, 0, 0) << 16); PIA->SetKeys(PIA->Buttons); } break;
			case IDC_A26_CNT_UP_KEY:	if (wmEvent == CBN_SELCHANGE) { PIA->Buttons[A26_SelectedPlayer][4] = SendMessage((HWND) lParam, CB_GETCURSEL, 0, 0) | (SendMessage(GetDlgItem(hwndDlg,IDC_A26_CNT_UP_DEVICE), CB_GETCURSEL, 0, 0) << 16); PIA->SetKeys(PIA->Buttons); } break;
			case IDC_A26_CNT_DOWN_KEY:	if (wmEvent == CBN_SELCHANGE) { PIA->Buttons[A26_SelectedPlayer][5] = SendMessage((HWND) lParam, CB_GETCURSEL, 0, 0) | (SendMessage(GetDlgItem(hwndDlg,IDC_A26_CNT_DOWN_DEVICE), CB_GETCURSEL, 0, 0) << 16); PIA->SetKeys(PIA->Buttons); } break;
			case IDC_A26_CNT_LEFT_KEY:	if (wmEvent == CBN_SELCHANGE) { PIA->Buttons[A26_SelectedPlayer][6] = SendMessage((HWND) lParam, CB_GETCURSEL, 0, 0) | (SendMessage(GetDlgItem(hwndDlg,IDC_A26_CNT_LEFT_DEVICE), CB_GETCURSEL, 0, 0) << 16); PIA->SetKeys(PIA->Buttons); } break;
			case IDC_A26_CNT_RIGHT_KEY:	if (wmEvent == CBN_SELCHANGE) { PIA->Buttons[A26_SelectedPlayer][7] = SendMessage((HWND) lParam, CB_GETCURSEL, 0, 0) | (SendMessage(GetDlgItem(hwndDlg,IDC_A26_CNT_RIGHT_DEVICE), CB_GETCURSEL, 0, 0) << 16); PIA->SetKeys(PIA->Buttons); } break;
			};
			break;
	}

	return false;
}

void A26_UpdateConfigBox()
{
	HWND TPWND;
	
	TPWND = GetDlgItem(A26_ConfigWnd, IDC_A26_CNT_BUT_DEVICE);
	SendMessage(TPWND, CB_RESETCONTENT,0,0);
	for (int i=0;i<PIA->NumDevices;i++) SendMessage(TPWND, CB_ADDSTRING, 0, (LPARAM) &PIA->DeviceName[i]);
	SendMessage(TPWND, CB_SETCURSEL, (PIA->Buttons[A26_SelectedPlayer][0] & 0x000F0000) >> 16, 0);
	
	TPWND = GetDlgItem(A26_ConfigWnd, IDC_A26_CNT_UP_DEVICE);
	SendMessage(TPWND, CB_RESETCONTENT,0,0);
	for (int i=0;i<PIA->NumDevices;i++) SendMessage(TPWND, CB_ADDSTRING, 0, (LPARAM) &PIA->DeviceName[i]);
	SendMessage(TPWND, CB_SETCURSEL, (PIA->Buttons[A26_SelectedPlayer][4] & 0x000F0000) >> 16, 0);
	TPWND = GetDlgItem(A26_ConfigWnd, IDC_A26_CNT_DOWN_DEVICE);
	SendMessage(TPWND, CB_RESETCONTENT,0,0);
	for (int i=0;i<PIA->NumDevices;i++) SendMessage(TPWND, CB_ADDSTRING, 0, (LPARAM) &PIA->DeviceName[i]);
	SendMessage(TPWND, CB_SETCURSEL, (PIA->Buttons[A26_SelectedPlayer][5] & 0x000F0000) >> 16, 0);
	TPWND = GetDlgItem(A26_ConfigWnd, IDC_A26_CNT_LEFT_DEVICE);
	SendMessage(TPWND, CB_RESETCONTENT,0,0);
	for (int i=0;i<PIA->NumDevices;i++) SendMessage(TPWND, CB_ADDSTRING, 0, (LPARAM) &PIA->DeviceName[i]);
	SendMessage(TPWND, CB_SETCURSEL, (PIA->Buttons[A26_SelectedPlayer][6] & 0x000F0000) >> 16, 0);
	TPWND = GetDlgItem(A26_ConfigWnd, IDC_A26_CNT_RIGHT_DEVICE);
	SendMessage(TPWND, CB_RESETCONTENT,0,0);
	for (int i=0;i<PIA->NumDevices;i++) SendMessage(TPWND, CB_ADDSTRING, 0, (LPARAM) &PIA->DeviceName[i]);
	SendMessage(TPWND, CB_SETCURSEL, (PIA->Buttons[A26_SelectedPlayer][7] & 0x000F0000) >> 16, 0);
	
	TPWND = GetDlgItem(A26_ConfigWnd, IDC_A26_CNT_AUTOCONFIGCOMBO);
	SendMessage(TPWND, CB_RESETCONTENT,0,0);
	for (int i=0;i<PIA->NumDevices;i++) SendMessage(TPWND, CB_ADDSTRING, 0, (LPARAM) &PIA->DeviceName[i]);
	SendMessage(TPWND, CB_SETCURSEL, PIA->NumDevices-1, 0);
	
	A26_UpdateKeyList();
}

void A26_UpdateKeyList()
{
	HWND TPWND[5] =
	{
		GetDlgItem(A26_ConfigWnd, IDC_A26_CNT_BUT_KEY),
		GetDlgItem(A26_ConfigWnd, IDC_A26_CNT_UP_KEY),
		GetDlgItem(A26_ConfigWnd, IDC_A26_CNT_DOWN_KEY),
		GetDlgItem(A26_ConfigWnd, IDC_A26_CNT_LEFT_KEY),
		GetDlgItem(A26_ConfigWnd, IDC_A26_CNT_RIGHT_KEY)
	};
	HWND DevWnd[5] =
	{
		GetDlgItem(A26_ConfigWnd, IDC_A26_CNT_BUT_DEVICE),
		GetDlgItem(A26_ConfigWnd, IDC_A26_CNT_UP_DEVICE),
		GetDlgItem(A26_ConfigWnd, IDC_A26_CNT_DOWN_DEVICE),
		GetDlgItem(A26_ConfigWnd, IDC_A26_CNT_LEFT_DEVICE),
		GetDlgItem(A26_ConfigWnd, IDC_A26_CNT_RIGHT_DEVICE)
	};
	int DevNum[5] =
	{
		SendMessage(DevWnd[0], CB_GETCURSEL, 0, 0),
		SendMessage(DevWnd[1], CB_GETCURSEL, 0, 0),
		SendMessage(DevWnd[2], CB_GETCURSEL, 0, 0),
		SendMessage(DevWnd[3], CB_GETCURSEL, 0, 0),
		SendMessage(DevWnd[4], CB_GETCURSEL, 0, 0),
	};
	char tps[64]; int bn;

	for (int cur=0;cur<5;cur++)
	{
		SendMessage(TPWND[cur], CB_RESETCONTENT,0,0);
		switch (PIA->DeviceType[DevNum[cur]])
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
				for (bn=0;bn<PIA->NumButtons[DevNum[cur]];bn++)
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

		SendMessage(TPWND[cur], CB_SETCURSEL, PIA->Buttons[A26_SelectedPlayer][cur] & 0x000000FF, 0);
	}
}
