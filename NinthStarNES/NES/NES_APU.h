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

#ifndef CAPU_H
#define CAPU_H

#include <windows.h>
#include <mmsystem.h>
#include <dsound.h>

class cNES_APU {
	public:
		cNES_APU           (HWND hWnd)	// Only Constructor
		{
		}
		~cNES_APU          ()			// Default destructor
		{
		}

		void GetSoundRegisters	(unsigned char * StoreHere) { }
		void SetSoundRegisters	(unsigned char GetFromHere[0x16]) { }
		void VBlank				(void) { } // VBlank notifcation
		void SoundOFF			(void) { }	// Turns the sound off ( ROM Close )
		void SoundON			(void) { } // Turns the sound on  ( ROM Open  )
		void Reset				(void) { } // Resets the sound registers
        void Config				(HWND hWnd, HINSTANCE hInstance) { }   // Opens sound configuration dialog
		
		unsigned char			WantFPS;

		void WriteReg(int Addy, BYTE Val) { }
		BYTE Read4015()
		{
			return(0);
		}

	private:
};

#endif