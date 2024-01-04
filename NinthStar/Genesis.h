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

#ifndef cGenesisH
#define cGenesisH

#include <commdlg.h>

#include "EmuBase.h"

#define KEY_GEN_A			0
#define KEY_GEN_B			1
#define KEY_GEN_C			2
#define KEY_GEN_START		3
#define KEY_GEN_UP			4
#define KEY_GEN_DOWN		5
#define KEY_GEN_LEFT		6
#define KEY_GEN_RIGHT		7

#include "Genesis/68000.h"
#include "Genesis/Gen_Debugger.h"
#include "Genesis/Gen_GFX.h"

class cGenesis : public cEmuBase {
	public :
		cGenesis();
		
		void SaveSettings()
		{
			HKEY SettingsBase;
			if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\NinthStar\\Genesis\\", 0, KEY_ALL_ACCESS, &SettingsBase) > 0)
				RegCreateKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\NinthStar\\Genesis\\", 0, "NinthStarClass", REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &SettingsBase, NULL);
			RegSetValueEx(SettingsBase, "SoundEnabled", 0, REG_DWORD, (unsigned char *) &SoundEnabled, 4);
			RegSetValueEx(SettingsBase, "DoubleSize", 0, REG_DWORD, (unsigned char *) &DoubleSize, 4);
			RegSetValueEx(SettingsBase, "aFSkip", 0, REG_DWORD, (unsigned char *) &GFX->aFSkip, 4);
			RegSetValueEx(SettingsBase, "FSkip", 0, REG_DWORD, (unsigned char *) &GFX->FSkip, 4);
			RegSetValueEx(SettingsBase, "Mode3D", 0, REG_DWORD, (unsigned char *) &GFX->Mode3D, 4);
//			RegSetValueEx(SettingsBase, "Keys", 0, REG_BINARY, (unsigned char *) &Keys[0][0], sizeof(Keys));
			RegCloseKey(SettingsBase);
		}

		void LoadSettings();

		void Release()
		{
			SaveSettings();
			
			delete CPU;
			delete GFX;
			delete Debugger;
	
			delete this;
		}

		void OpenFile(char *toopen);
		void Run();
		void PowerOn();
		void Reset();

		void UpdateInterface();

		void RePaint()
		{	GFX->RePaint(); }

		void EmuMsg(DWORD Message, DWORD Data1, DWORD Data2);

		c68000 *CPU;
		cGen_GFX *GFX;
		cGen_Debugger *Debugger;

	private :
		int	DoubleSize, SoundEnabled;
};

#endif