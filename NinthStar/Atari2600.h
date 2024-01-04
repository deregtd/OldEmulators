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

#ifndef cAtari2600H
#define cAtari2600H

#include <commdlg.h>

#include "EmuBase.h"

#include "Atari2600/6507.h"
#include "Atari2600/A26_Debugger.h"
#include "Atari2600/A26_TIA.h"
#include "Atari2600/A26_GFX.h"

class cAtari2600 : public cEmuBase {
	public :
		cAtari2600();

		void SaveSettings()
		{
			HKEY SettingsBase;
			if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\NinthStar\\Atari2600\\", 0, KEY_ALL_ACCESS, &SettingsBase) > 0)
				RegCreateKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\NinthStar\\Atari2600\\", 0, "NinthStarClass", REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &SettingsBase, NULL);
			RegSetValueEx(SettingsBase, "SoundEnabled", 0, REG_DWORD, (unsigned char *) &SoundEnabled, 4);
			RegSetValueEx(SettingsBase, "DoubleSize", 0, REG_DWORD, (unsigned char *) &DoubleSize, 4);
			RegSetValueEx(SettingsBase, "aFSkip", 0, REG_DWORD, (unsigned char *) &GFX->aFSkip, 4);
			RegSetValueEx(SettingsBase, "FSkip", 0, REG_DWORD, (unsigned char *) &GFX->FSkip, 4);
			RegSetValueEx(SettingsBase, "Mode3D", 0, REG_DWORD, (unsigned char *) &GFX->Mode3D, 4);
			RegSetValueEx(SettingsBase, "Paddles", 0, REG_DWORD, (unsigned char *) &PIA->Paddles, 4);
			RegCloseKey(SettingsBase);
		}
		
		void LoadSettings();

		void Release()
		{
			SaveSettings();
			
			delete CPU;
			delete TIA;
			delete PIA;
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

		c6507 *CPU;
		cA26_PIA *PIA;
		cA26_TIA *TIA;
		cA26_GFX *GFX;
		cA26_Debugger *Debugger;

		int TicksToCount;

	private :
		int	DoubleSize, SoundEnabled;
};

#define MT_2k		1
#define MT_4k		2
#define MT_6k		3
#define MT_8kF8		4
#define MT_8kFE		5
#define MT_8kE0		6
#define MT_8k3F		7
#define MT_12k		8
#define MT_16kF6	9
#define MT_16kE7	10
#define MT_32k		11
#define MT_64k		12
#define Unk			13

#endif