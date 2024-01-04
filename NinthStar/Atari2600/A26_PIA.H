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

#ifndef A26_PIA_H
#define A26_PIA_H

#include <dinput.h>
#include <stdio.h>

class cA26_PIA {
	public:
		cA26_PIA();

		~cA26_PIA()
		{
			for (int i=0;i<16;i++)
				if (pDID[i])
				{	pDID[i]->Unacquire();	pDID[i]->Release();	}
			
			pDI->Release();
		}

		void WriteRegister(short Addy, unsigned char Val)
		{
			switch (Addy)
			{
			case 0x281:
				SWACNT = Val;
				break;
			case 0x294:
				FullInterval = 1*3;
				CurrInterval = 1*3;
				Looped = false;
				Counter = Val;
				break;
			case 0x295:
				FullInterval = 8*3;
				CurrInterval = 8*3;
				Looped = false;
				Counter = Val;
				break;
			case 0x296:
				FullInterval = 64*3;
				CurrInterval = 64*3;
				Looped = false;
				Counter = Val;
				break;
			case 0x297:
				FullInterval = 1024*3;
				CurrInterval = 1024*3;
				Looped = false;
				Counter = Val;
				break;
			}
		}

		unsigned char ReadRegister(short Addy)
		{
			switch (Addy)
			{
			case 0x280:
				return(SWCHA & (~SWACNT));
			case 0x282:			//Console Switches
				return(SWCHB);		//Return switches released + color
			case 0x284:			//PIA Counter Read
				return(Counter);
			default:
				return(0);
			}
		}

		unsigned char SWCHA, SWACNT, SWCHB;
		unsigned char INPT4, INPT5;
		unsigned char *VBLANK;

		int *Clockticks;

		short FullInterval;
		short CurrInterval;
		unsigned char Counter;
		bool Looped;
		
		int Buttons[2][32];
	
		int		Paddles;

		void	SetKeys(int Keys[4][32]);
		void	Acquire(int DeviceNum);
		void	UnAcquire(int DeviceNum);
		void	UpdateInput();
		void	OpenConfig();

		bool					DeviceUsed[16];
		int						NumDevices;

		friend BOOL CALLBACK A26_EnumJoysticksCallback(const DIDEVICEINSTANCE* pdidInstance, VOID* pContext);
		friend BOOL CALLBACK A26_ControllerProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
		friend void A26_UpdateConfigBox();
		friend void A26_UpdateKeyList();

	private:
		LPDIRECTINPUT8			pDI;
		LPDIRECTINPUTDEVICE8	pDID[16];
		int						DeviceType[16];
		char					DeviceName[16][64];
		int						NumButtons[16];

};

#define	CT_KEYBOARD			1
#define CT_JOYSTICK			2

#endif