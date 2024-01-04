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
#include "Genesis.h"

#include "Global.h"

cGenesis::cGenesis()
{
	CPU = new c68000();
	CPU->Clockticks = &Clockticks;
	
	GFX = new cGen_GFX();

	Debugger = new cGen_Debugger();
	Debugger->CPU = CPU;
	Debugger->SetMode(0);

	char tpo[40];
    sprintf(tpo,"NinthStar - Genesis - Stopped");
	SetWindowText(gData->MainWnd,tpo);
	
	Stopped = true;
	Stop = false;
	NeedQuit = false;
	NeedDie = false;
}

void cGenesis::PowerOn()
{

	Reset();
}

void cGenesis::Reset()
{
	Debugger->TraceOffset = -1;

	CPU->Reset();

	Clockticks = 0;

	bool tpb = Debugger->Logging;
	Debugger->Logging = false;
	if (Debugger->Enabled)
		Debugger->Update();
	Debugger->Logging = tpb;
}

void cGenesis::OpenFile(char * FileName)
{
	Stop = true;

	FILE *in = fopen(FileName,"rb");

	char Ext[4];
	memcpy(&Ext[0],FileName + (strlen(FileName)-3),3);
	Ext[3] = 0;

	fseek(in, 0, SEEK_END);
	int flen = ftell(in);
	fseek(in, 0, SEEK_SET);

	if (_stricmp(Ext,"BIN") == 0)
	{
		fread(&CPU->PRG,flen,1,in);		//Read in PRG Data
	} else if (_stricmp(Ext,"SMD") == 0) {
		unsigned char *tpa = new unsigned char(flen-0x200);
		fseek(in, 0x200, SEEK_SET);
		fread(tpa,flen-0x200,1,in);		//Read in PRG Data
		
		for (int i=0;i<flen;i+=0x4000)
			for (int p=0;p<0x2000;p++)
			{
				CPU->PRG[i + (p << 1)] = tpa[i+p];
				CPU->PRG[i + (p << 1) + 1] = tpa[i+p+0x2000];
			}
		
		delete tpa;
	}

	fclose(in);

	PowerOn();

	if (Debugger->Enabled)
		Debugger->Update();

	delete []FileName;
}

void cGenesis::Run()
{
	Debugger->TraceOffset = -1;

	Stopped = false;

	do
	{
		if (Debugger->Enabled)
			Debugger->AddInst();

		CPU->ExecOp();
		
		if (Debugger->Enabled)
			Debugger->Update();
		
		MSG msg;
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (!TranslateAccelerator(gData->MainWnd, gData->hAccelTable, &msg)) 
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
	} while (!Stop);

	char tpo[40];
    sprintf(tpo,"NinthStar - Genesis - Stopped");
	SetWindowText(gData->MainWnd,tpo);

	Stopped = true;

	if (NeedQuit)
		SendMessage(gData->MainWnd, WM_TEMPDESTROY, 0, 0);
	else if (NeedDie)
		this->Release();
}

void cGenesis::UpdateInterface()
{
	GFX->ReLoad(gData->Width, gData->Height, GFX->Mode3D);
	Debugger->DoubleSize = DoubleSize;
	Debugger->SetMode(Debugger->Mode);
}

void cGenesis::EmuMsg(DWORD Message, DWORD Data1, DWORD Data2)
{
	HMENU MyMenu;

	switch (Message)
	{
		case ID_EMULATION_START:
			if (Stopped)
			{
				Stop = false;
				Run();
			} else {
				Stop = true;
			}
			break;
		case ID_EMULATION_STEP:
			if (Stopped)
			{
				Stop = true;
				Run();
			} else {
				Stop = true;
			}
			break;
		case ID_EMULATION_RESET:
			Reset();
			break;
		case ID_EMULATION_STOP:
			Stop = true;
			break;
		case ID_OPTIONS_DOUBLESIZEMODE:
			DoubleSize ^= true;
			MyMenu = GetMenu(gData->MainWnd);
			if (DoubleSize)
			{		//Check
				gData->Width = 320*2; gData->Height = 240*2;
				CheckMenuItem(MyMenu, ID_OPTIONS_DOUBLESIZEMODE, MF_CHECKED);
			} else {	//Uncheck
				gData->Width = 320; gData->Height = 240;
				CheckMenuItem(MyMenu, ID_OPTIONS_DOUBLESIZEMODE, MF_UNCHECKED);
			}
			SetWindowPos(gData->MainWnd, HWND_TOP, 0, 0, gData->Width+8, gData->Height+48, SWP_SHOWWINDOW);
			break;
		case ID_OPTIONS_AUTOFRAMESKIP:
			GFX->aFSkip ^= true;
			MyMenu = GetMenu(gData->MainWnd);
			if (GFX->aFSkip)
				CheckMenuItem(MyMenu, ID_OPTIONS_AUTOFRAMESKIP, MF_CHECKED);
			else	//Uncheck
				CheckMenuItem(MyMenu, ID_OPTIONS_AUTOFRAMESKIP, MF_UNCHECKED);
			break;
		case ID_OPTIONS_DECREASEFRAMESKIP:
			if (--GFX->FSkip < 0) GFX->FSkip = 0;
			break;
		case ID_OPTIONS_INCREASEFRAMESKIP:
			GFX->FSkip++;
			break;
		case ID_OPTIONS_3DHARDWAREACCELERATION:
			GFX->Mode3D ^= true;
			UpdateInterface();
			MyMenu = GetMenu(gData->MainWnd);
			if (GFX->Mode3D)
				CheckMenuItem(MyMenu, ID_OPTIONS_3DHARDWAREACCELERATION, MF_CHECKED);
			else	//Uncheck
				CheckMenuItem(MyMenu, ID_OPTIONS_3DHARDWAREACCELERATION, MF_UNCHECKED);
			break;
		case ID_OPTIONS_FILTERINGMODE_POINTNONE:
			GFX->FilterMode = D3DTEXF_NONE;
			UpdateInterface();
			break;
		case ID_OPTIONS_FILTERINGMODE_LINEAR:
			GFX->FilterMode = D3DTEXF_LINEAR;
			UpdateInterface();
			break;
		case ID_OPTIONS_FILTERINGMODE_CUBIC:
			GFX->FilterMode = D3DTEXF_FLATCUBIC;
			UpdateInterface();
			break;
		case ID_DEBUG_OFF:
			Debugger->SetMode(0);
			MyMenu = GetMenu(gData->MainWnd);
			CheckMenuItem(MyMenu, ID_DEBUG_OFF, MF_CHECKED);
			CheckMenuItem(MyMenu, ID_DEBUG_LOW, MF_UNCHECKED);
			CheckMenuItem(MyMenu, ID_DEBUG_MEDIUM, MF_UNCHECKED);
			CheckMenuItem(MyMenu, ID_DEBUG_HIGH, MF_UNCHECKED);
			break;
		case ID_DEBUG_LOW:
			Debugger->SetMode(1);
			MyMenu = GetMenu(gData->MainWnd);
			CheckMenuItem(MyMenu, ID_DEBUG_OFF, MF_UNCHECKED);
			CheckMenuItem(MyMenu, ID_DEBUG_LOW, MF_CHECKED);
			CheckMenuItem(MyMenu, ID_DEBUG_MEDIUM, MF_UNCHECKED);
			CheckMenuItem(MyMenu, ID_DEBUG_HIGH, MF_UNCHECKED);
			break;
		case ID_DEBUG_MEDIUM:
			Debugger->SetMode(2);
			MyMenu = GetMenu(gData->MainWnd);
			CheckMenuItem(MyMenu, ID_DEBUG_OFF, MF_UNCHECKED);
			CheckMenuItem(MyMenu, ID_DEBUG_LOW, MF_UNCHECKED);
			CheckMenuItem(MyMenu, ID_DEBUG_MEDIUM, MF_CHECKED);
			CheckMenuItem(MyMenu, ID_DEBUG_HIGH, MF_UNCHECKED);
			break;
		case ID_DEBUG_HIGH:
			Debugger->SetMode(3);
			MyMenu = GetMenu(gData->MainWnd);
			CheckMenuItem(MyMenu, ID_DEBUG_OFF, MF_UNCHECKED);
			CheckMenuItem(MyMenu, ID_DEBUG_LOW, MF_UNCHECKED);
			CheckMenuItem(MyMenu, ID_DEBUG_MEDIUM, MF_UNCHECKED);
			CheckMenuItem(MyMenu, ID_DEBUG_HIGH, MF_CHECKED);
			break;
		case ID_OPTIONS_CLEARALLBREAKPOINTS:
			ZeroMemory(&Debugger->BreakP,sizeof(Debugger->BreakP));
			break;
	}
}

void cGenesis::LoadSettings()
{
	gData->hAccelTable = LoadAccelerators(gData->hInst, (LPCTSTR)IDR_GEN_ACCEL);

	HMENU hMenu = LoadMenu(gData->hInst, (LPCTSTR)IDM_GEN_MENU);
	
	HKEY SettingsBase;
	unsigned long Size;
	int Keys[4][32];

	//Load Defaults
	GFX->Mode3D = 0;
	DoubleSize = 0;
	SoundEnabled = 1;
	GFX->aFSkip = 1;
	GFX->FSkip = 0;
	Keys[0][KEY_GEN_A] = DIK_Z;
	Keys[0][KEY_GEN_B] = DIK_X;
	Keys[0][KEY_GEN_C] = DIK_C;
	Keys[0][KEY_GEN_START] = DIK_S;
	Keys[0][KEY_GEN_UP] = DIK_UP;
	Keys[0][KEY_GEN_DOWN] = DIK_DOWN;
	Keys[0][KEY_GEN_LEFT] = DIK_LEFT;
	Keys[0][KEY_GEN_RIGHT] = DIK_RIGHT;
	Keys[1][KEY_GEN_A] = DIK_U;
	Keys[1][KEY_GEN_B] = DIK_I;
	Keys[1][KEY_GEN_C] = DIK_O;
	Keys[1][KEY_GEN_START] = DIK_P;
	Keys[1][KEY_GEN_UP] = DIK_HOME;
	Keys[1][KEY_GEN_DOWN] = DIK_END;
	Keys[1][KEY_GEN_LEFT] = DIK_DELETE;
	Keys[1][KEY_GEN_RIGHT] = DIK_NEXT;		//Page Down?
	//End Defaults
	
	RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\NinthStar\\Genesis\\", 0, KEY_ALL_ACCESS, &SettingsBase);
	Size=4; RegQueryValueEx(SettingsBase, "SoundEnabled", 0, NULL, (unsigned char *) &SoundEnabled, &Size);
	Size=4; RegQueryValueEx(SettingsBase, "DoubleSize", 0, NULL, (unsigned char *) &DoubleSize, &Size);
	Size=4; RegQueryValueEx(SettingsBase, "aFSkip", 0, NULL, (unsigned char *) &GFX->aFSkip, &Size);
	Size=4; RegQueryValueEx(SettingsBase, "FSkip", 0, NULL, (unsigned char *) &GFX->FSkip, &Size);
	Size=4; RegQueryValueEx(SettingsBase, "Mode3D", 0, NULL, (unsigned char *) &GFX->Mode3D, &Size);
	Size=sizeof(Keys); RegQueryValueEx(SettingsBase, "Keys", 0, NULL, (unsigned char *) &Keys[0][0], &Size);
	RegCloseKey(SettingsBase);
	
	if (SoundEnabled)
		CheckMenuItem(hMenu, ID_OPTIONS_SOUNDON, MF_CHECKED);
	else
		CheckMenuItem(hMenu, ID_OPTIONS_SOUNDON, MF_UNCHECKED);
	
	if (GFX->Mode3D)
		CheckMenuItem(hMenu, ID_OPTIONS_3DHARDWAREACCELERATION, MF_CHECKED);
	else
		CheckMenuItem(hMenu, ID_OPTIONS_3DHARDWAREACCELERATION, MF_UNCHECKED);
	
	if (GFX->aFSkip)
		CheckMenuItem(hMenu, ID_OPTIONS_AUTOFRAMESKIP, MF_CHECKED);
	else
		CheckMenuItem(hMenu, ID_OPTIONS_AUTOFRAMESKIP, MF_UNCHECKED);

	if (DoubleSize)
	{		//Check
		gData->Width = 320*2; gData->Height = 240*2;
		CheckMenuItem(hMenu, ID_OPTIONS_DOUBLESIZEMODE, MF_CHECKED);
	} else {	//Uncheck
		gData->Width = 320; gData->Height = 240;
		CheckMenuItem(hMenu, ID_OPTIONS_DOUBLESIZEMODE, MF_UNCHECKED);
	}

	SetMenu(gData->MainWnd, hMenu);

	SetWindowPos(gData->MainWnd, HWND_TOP, 0, 0, gData->Width+8, gData->Height+48, SWP_SHOWWINDOW);

//	SetControlConfig(Keys);

	PowerOn();
}