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

#ifndef COL_CONTROLLERS_H
#define COL_CONTROLLERS_H

#include "dinput.h"

/*#define KEY_NES_A			0
#define KEY_NES_B			1
#define KEY_NES_SELECT		2
#define KEY_NES_START		3
#define KEY_NES_UP			4
#define KEY_NES_DOWN		5
#define KEY_NES_LEFT		6
#define KEY_NES_RIGHT		7*/

class cCol_Controllers {
	public:
		cCol_Controllers(HINSTANCE hInst, HWND hWnd);

		~cCol_Controllers()
		{
			for (int i=0;i<16;i++)
				if (pDID[i])
				{	pDID[i]->Unacquire();	pDID[i]->Release();	}
			
			pDI->Release();
		}
		
		void SetKeys(int Keys[2][32]);
		void OpenConfig();

		void UpdateInput();
		void Acquire(int DeviceNum);
		void UnAcquire(int DeviceNum);

//		int *StateSlot;

		int ContType[2];

		int Buttons[2][32];		//VirtKeys for both joypads

		bool					DeviceUsed[16];
		int						NumDevices;
		
		friend BOOL CALLBACK Col_EnumJoysticksCallback(const DIDEVICEINSTANCE* pdidInstance, VOID* pContext);
		friend BOOL CALLBACK Col_ControllerProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
		friend void Col_UpdateConfigBox();
		friend void Col_UpdateKeyList();

	private :
		LPDIRECTINPUT8			pDI;
		LPDIRECTINPUTDEVICE8	pDID[16];
		int						DeviceType[16];
		char					DeviceName[16][64];
		int						NumButtons[16];
};


#define	CT_KEYBOARD			1
#define CT_JOYSTICK			2



#endif