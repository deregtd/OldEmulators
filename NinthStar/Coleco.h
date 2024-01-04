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

#ifndef cCOLECOH
#define cCOLECOH

#include "Coleco/Col_Z80.h"
#include "Coleco/Col_PPU.h"
#include "Coleco/Col_GFX.h"
#include "Coleco/Col_Debugger.h"
#include "Coleco/Col_Controllers.h"

#include "EmuBase.h"

#include "Resource.h"

class cColeco : public cEmuBase {
	public :
		cColeco();
		
		void SaveSettings()
		{
			HKEY SettingsBase;
			if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\NinthStar\\Coleco\\", 0, KEY_ALL_ACCESS, &SettingsBase) > 0)
				RegCreateKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\NinthStar\\Coleco\\", 0, "NinthStarClass", REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &SettingsBase, NULL);

			RegSetValueEx(SettingsBase, "DoubleSize", 0, REG_DWORD, (unsigned char *) &DoubleSize, 4);
			RegSetValueEx(SettingsBase, "aFSkip", 0, REG_DWORD, (unsigned char *) &GFX->aFSkip, 4);
			RegSetValueEx(SettingsBase, "Mode3D", 0, REG_DWORD, (unsigned char *) &GFX->Mode3D, 4);
			RegSetValueEx(SettingsBase, "Keys", 0, REG_BINARY, (unsigned char *) &Controllers->Buttons[0][0], sizeof(Controllers->Buttons));
			RegCloseKey(SettingsBase);
		}

		void LoadSettings();

		void Release()
		{
			SaveSettings();

			delete Controllers;
			delete GFX;
			delete CPU;
			delete PPU;
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

		void IRQ()
		{	CPU->IRQ(); }

		void EmuMsg(DWORD Message, DWORD Data1, DWORD Data2);

		cCol_Z80 *CPU;
		cCol_PPU *PPU;
		cCol_GFX *GFX;
		cCol_Debugger *Debugger;
		cCol_Controllers *Controllers;

	private :
		int	DoubleSize;
};

#endif