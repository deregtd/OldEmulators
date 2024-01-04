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

#include "Global.h"

void cGlobalData::OpenFile(char * toopen)
{
	char * FileName = new char[100];
	
	OPENFILENAME ofn;
	
	if (!toopen)
	{
		ZeroMemory(&ofn,sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = MainWnd;
		ofn.hInstance = hInst;
		char Filters[] = "NES ROMs (*.NES;*.UNIF;*.UNF)\0*.NES;*.UNIF;*.UNF\0\0";
		ofn.lpstrFilter = (char *) &Filters[0];
		ofn.lpstrCustomFilter = NULL;
//Add default Filename Here!
		ofn.nFilterIndex = 1;
//		sprintf(FileName,"c:\\roms\\nes\\*.nes;*.unif;*.unf");
		sprintf(FileName,"");
		ofn.lpstrFile = FileName;
		ofn.nMaxFile = 100;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = NULL;
		ofn.lpstrInitialDir = ROMDir;
		ofn.lpstrTitle = "Load ROM";
		ofn.Flags = OFN_FILEMUSTEXIST;
		ofn.lpstrDefExt = NULL;
		ofn.lCustData = NULL;
		ofn.lpfnHook = NULL;
		ofn.lpTemplateName = NULL;
	
		int tpb = GetOpenFileName(&ofn);
		if (tpb == 0)
			return;
	} else {
		strcpy(FileName, toopen);

		char Ext[4];
		memcpy(&Ext[0],FileName + (strlen(FileName)-3),3);
		Ext[3] = 0;
	}
	
	Main->Stop = true;
	Main->NeedDie = true;
	PlaySnow = false;

	Main->OpenFile(FileName);
}
