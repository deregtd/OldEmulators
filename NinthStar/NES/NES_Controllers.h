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

#ifndef CONTROLLERS_H
#define CONTROLLERS_H

#include "NES_Handlers.h"
#include "dinput.h"

#define KEY_NES_A			0
#define KEY_NES_B			1
#define KEY_NES_SELECT		2
#define KEY_NES_START		3
#define KEY_NES_UP			4
#define KEY_NES_DOWN		5
#define KEY_NES_LEFT		6
#define KEY_NES_RIGHT		7

class cNES_Controller {
	public :
		cNES_Controller();

		unsigned char Read();
		unsigned long Bits;
		char BitPtr;
		unsigned char Strobe;
	
	private:
};

class cNES_Controllers {
	public:
		cNES_Controllers(HINSTANCE hInst, HWND hWnd);

		~cNES_Controllers()
		{
			for (int i=0;i<4;i++)
				delete Cont[i];
			
			for (int i=0;i<16;i++)
				if (pDID[i])
				{	pDID[i]->Unacquire();	pDID[i]->Release();	}
			
			pDI->Release();
		}
		
		void Write(unsigned char Val)
		{
			int tps = Cont[0]->Strobe;
			Cont[0]->Strobe = (Val & 1);
			if ((Cont[0]->Strobe == 0) && (tps == 1))		//Strobage
			{ Cont[0]->BitPtr = 0; Cont[1]->BitPtr = 0; }
		}

		void SetKeys(int Keys[4][32]);
		void OpenConfig();

		void UpdateInput();
		void Acquire(int DeviceNum);
		void UnAcquire(int DeviceNum);

		cNES_Controller *Cont[4];

		int *StateSlot;

		int ContType[2];

		int Buttons[4][32];		//VirtKeys for both joypads

		bool					DeviceUsed[16];
		int						NumDevices;
		
		friend BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE* pdidInstance, VOID* pContext);
		friend BOOL CALLBACK ControllerProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
		friend void UpdateConfigBox();
		friend void UpdateKeyList();

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