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
		char Filters[] = "NES ROMs (*.NES;*.UNIF;*.UNF)\0*.NES;*.UNIF;*.UNF\0Atari 2600 ROMs (*.BIN)\0*.BIN\0Sega Genesis ROMs (*.BIN;*.SMD)\0*.BIN;*.SMD\0Coleco ROMs (*.ROM)\0*.ROM\0\0";
		ofn.lpstrFilter = (char *) &Filters[0];
		ofn.lpstrCustomFilter = NULL;
//Add default Filename Here!
		ofn.nFilterIndex = 1;
		sprintf(FileName,"c:\\roms\\*.nes;*.unif;*.unf");
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
		
		if (_stricmp(Ext,"NES") == 0)
			ofn.nFilterIndex = 1;	//NES
		else if (_stricmp(Ext,"UNF") == 0)
			ofn.nFilterIndex = 1;	//NES
		else if (_stricmp(Ext,"NIF") == 0)
			ofn.nFilterIndex = 1;	//NES
		else if (_stricmp(Ext,"BIN") == 0) {
			FILE *in = fopen(FileName,"rb"); fseek(in, 0, SEEK_END); int flen = ftell(in); fclose(in);
			if (flen < 16*1024)			ofn.nFilterIndex = 2;	//Atari 2600
			else if (flen > 64*1024)	ofn.nFilterIndex = 3;	//Genesis
			else {
				int tpr = MessageBox(MainWnd, "AutoDistinguish (tm) Failed!\nIs this file a Genesis ROM or an Atari 2600 ROM?\n\nGenesis = Yes\nAtari 2600 = No", "Genesis or Atari 2600?", MB_YESNO);
				if (tpr == IDNO)			ofn.nFilterIndex = 2;	//Atari 2600
				else if (tpr == IDYES)		ofn.nFilterIndex = 3;	//Genesis
				else						return;
			}
		} else if (_stricmp(Ext,"SMD") == 0)
			ofn.nFilterIndex = 3;	//Genesis
		else if (_stricmp(Ext,"ROM") == 0)
			ofn.nFilterIndex = 4;	//Coleco
	}
	
	if (Main)
	{	Main->Stop = true; Main->NeedDie = true; Main->Release(); }

	PlaySnow = false;

	switch (ofn.nFilterIndex)
	{
	case 1 :	Main = new cNES(); break;
	case 2 :	Main = new cAtari2600(); break;
	case 3 :	Main = new cGenesis(); break;
	case 4 :	Main = new cColeco(); break;
	}

	Main->LoadSettings();

	Main->OpenFile(FileName);
}
