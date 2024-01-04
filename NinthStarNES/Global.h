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

#ifndef GLOBAL_H
#define GLOBAL_H

#include "NES.h"

#include "resource.h"
#include "stdio.h"

#define WM_TEMPDESTROY		WM_USER+1

class cGlobalData {
	public:
		cGlobalData(HINSTANCE hIn, HWND hWn)
		{
			MainWnd = hWn;
			hInst = hIn;

			hAccelTable = LoadAccelerators(hInst, (LPCTSTR)IDR_NES_ACCEL);
			
			HMENU hMenu = LoadMenu(hInst, (LPCTSTR)IDM_NES_MENU);
			SetMenu(MainWnd, hMenu);

			Width = 320+8;
			Height = 240+48;

			Main = NULL;

			PlaySnow = true;

			//Check for Settings in registry, if not run SaveInitialSettings();
			HKEY SettingsBase;
			if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, "\\SOFTWARE\\NinthStar\\", 0, KEY_ALL_ACCESS, &SettingsBase) == 0)
			{	RegCloseKey(SettingsBase); return; }

			RegCreateKeyEx(HKEY_LOCAL_MACHINE, "\\SOFTWARE\\NinthStar\\", 0, "NinthStarClass", REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &SettingsBase, NULL);
			RegCloseKey(SettingsBase);
		}
		~cGlobalData()
		{
			Main->Release();
		}

		void OpenFile(char * toopen);

		cNES			*Main;

		char			ROMDir[256];
		HINSTANCE		hInst;
		HWND			MainWnd;
		HACCEL			hAccelTable;

		int				Width, Height;

		bool			PlaySnow;
};

extern cGlobalData *gData;

#endif