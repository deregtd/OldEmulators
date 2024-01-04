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
#include "NES.h"

#include "Global.h"

unsigned char Ticks2A03[256]=
{
    7,6,2,2,2,3,5,2,3,2,2,2,2,4,6,2,
    2,5,2,2,2,4,6,2,2,4,2,2,2,4,6,2,
    6,6,2,2,3,3,5,2,4,2,2,2,4,4,6,2,
    2,5,2,2,2,4,6,2,2,4,2,2,2,4,6,2,
    6,6,2,2,2,3,5,2,3,2,2,2,3,4,6,2,
    2,5,2,2,2,4,6,2,2,4,2,2,2,4,6,2,
    6,6,2,2,2,3,5,2,4,2,2,2,5,4,6,2,
    2,5,2,2,2,4,6,2,2,4,2,2,2,4,6,2,
    2,6,2,2,3,3,3,2,2,2,2,2,4,4,4,2,
    2,5,2,2,4,4,4,2,2,4,2,2,2,4,2,2,
    2,6,2,2,3,3,3,2,2,2,2,2,4,4,4,2,
    2,5,2,2,4,4,4,2,2,4,2,2,4,4,4,2,
    2,6,2,2,3,3,5,2,2,2,2,2,4,4,6,2,
    2,5,2,2,2,4,6,2,2,4,2,2,2,4,6,2,
    2,6,2,2,3,3,5,2,2,2,2,2,4,4,6,2,
    2,5,2,2,2,4,6,2,2,4,2,2,2,4,6,2
};

cNES *NES;

cNES::cNES()
{
	NES = this;
	
	if (Ticks2A03[0xFF] == 2)
		for (int i=0;i<256;i++)
			Ticks2A03[i] *= 12;

	GFX = new cNES_GFX();
	PPU = NULL;
	CPU = new c2A03();
//	CPU->Clockticks = &Clockticks;
	CPU->RAM = &RAM[0];
	Sprite = new cNES_Sprite();
	Debugger = new cNES_Debugger();
	States = new cNES_States();
	Controllers = new cNES_Controllers(gData->hInst, gData->MainWnd);
	States->pCPU = CPU;
	States->pGFX = GFX;
	States->pControllers = Controllers;
	States->SRAM_Size = &SRAM_Size;
	States->SRAM = &SRAM[0][0];
	Debugger->CPU = CPU;
	memcpy(&Debugger->FixedPalette,&GFX->FixedPalette,sizeof(GFX->FixedPalette));
	SetPPUMode(1);
	Debugger->DoubleSize = 0;
	Debugger->SetMode(0);
	Controllers->StateSlot = &States->SelSlot;

	char tpo[40];
    sprintf(tpo,"NinthStar - NES - Stopped");
	SetWindowText(gData->MainWnd,tpo);

	Stopped = true;
	Stop = false;
	SRAMHWEnabled = false;
	NeedQuit = false;
	NeedDie = false;
	
	SetCPUMode(0);		//Start with NTSC

	GFX->ReLoad(gData->Width, gData->Height, GFX->Mode3D);
}
void cNES::PowerOn()
{
	ZeroMemory(&RAM[0],sizeof(RAM));
	ZeroMemory(&SRAM[0],sizeof(SRAM));
	ZeroMemory(&Sprite->Sprite[0],sizeof(Sprite->Sprite));
	
	CPU->A = 0; CPU->X = 0; CPU->Y = 0; CPU->SP = 0xFF; CPU->P = 0x20;		//Reset Registers
	PPU->StatusReg = 0;
	PPU->ControlReg[0] = 0; PPU->ControlReg[1] = 0;
	PPU->HVTog = true;
	ShortSL = 0;

	if (MapperInfo)
		if (MapperInfo->InitMapper)
			MapperInfo->InitMapper(&MapperParam, 1);

	Reset();
}

void cNES::Reset()
{
	CPU->ReadHandler[0] = &RAMReader;	CPU->WriteHandler[0] = &RAMWriter;
	CPU->ReadHandler[1] = &RAMReader;	CPU->WriteHandler[1] = &RAMWriter;

	CPU->ReadHandler[2] = &PPUReader;	CPU->WriteHandler[2] = &PPUWriter;
	CPU->ReadHandler[3] = &PPUReader;	CPU->WriteHandler[3] = &PPUWriter;

	CPU->ReadHandler[4] = &Regs4kReader;	CPU->WriteHandler[4] = &Regs4kWriter;

	for (int i=0x5;i<0x10;i++)
	{
		CPU->ReadHandler[i] = &PRGReader;
		CPU->WriteHandler[i] = &PRGWriter;
		PRGPointer[i] = &PRG[0][0];
	}

	for (int i=8;i<12;i++)
		NES->PPU->Writable[i] = true;

	if (MapperInfo)
	{
		if (MapperInfo->UnloadMapper)
			MapperInfo->UnloadMapper();
		if (MapperInfo->InitMapper)
			MapperInfo->InitMapper(&MapperParam, 0);
	}

	Debugger->TraceOffset = -1;

	CPU->Reset();
	CPU->APU->Reset();

	CPU->Clockticks = 0;
	LastTicks = 0;
	PPU->SLnum = 0;
	PPU->Xnum = 0;

	bool tpb = Debugger->Logging;
	Debugger->Logging = false;
	if (Debugger->Enabled)
		Debugger->Update();
	Debugger->Logging = tpb;
}

void cNES::OpenFile(char * FileName)
{
	Stop = true;

	SRAMHWEnabled = SRAMEnabled;
	States->SRAMHWEnabled = SRAMHWEnabled;
	ZeroMemory(SRAMFileName,sizeof(SRAMFileName));
	strcat(SRAMFileName,FileName);
	SRAMFileName[strlen(SRAMFileName)-3] = 0x0;
	ZeroMemory(States->FileNameBase,sizeof(States->FileNameBase));
	strcat(States->FileNameBase, SRAMFileName);			//Save Filename Base to States Class
	char TPLSTFN[256];
	strcpy(TPLSTFN, States->FileNameBase);
	strcat(SRAMFileName,"sav");
	strcat(TPLSTFN,"lst");

	FILE *tpfile = fopen(TPLSTFN, "rt");
	if (tpfile)
	{
		fseek(tpfile, 0, SEEK_END);
		if (ftell(tpfile) > 26)
		{
			fseek(tpfile, 0, SEEK_SET);
			char tpchr[256];
			char tpchr2[8];
			char tpchr3[18];
			unsigned short TpAddy;
			unsigned short TpByte;
			while (!feof(tpfile))
			{
				tpchr[0] = 0;tpchr2[0] = 0;tpchr3[0] = 0; TpAddy = 0xCCCC; TpByte = 0xCCCC;
				fgets(tpchr,256,tpfile);
				sscanf(tpchr,"%4s   %04X",tpchr3,&TpAddy);
				
				if (TpAddy & 0x8000)
				{
					TpAddy -= 0x8000;
					sscanf(tpchr,"%4s   %4s %02X",tpchr3,tpchr3,&TpByte);
					if ((TpByte < 0x100) & (TpByte > 0))		//Hack...
					{
						strcpy(Debugger->TraceComment[TpAddy],tpchr+24);
						Debugger->TraceComment[TpAddy][31] = 0;
						char *tpp = strrchr(Debugger->TraceComment[TpAddy],0) - 1;
						*tpp = 0;
					}
				}
			}
		}
	}

	*Debugger->NTabChanged = true;
	*Debugger->PalChanged = true;
	*Debugger->PatChanged = true;

	bool LoadRet;
	char *tpn = FileName + strlen(FileName) - 4;
	if (stricmp(tpn, ".NES") == 0) LoadRet = OpenFileiNES(FileName);
	else if (stricmp(tpn, ".UNF") == 0) LoadRet = OpenFileUNIF(FileName);
	else if (stricmp(tpn, "UNIF") == 0) LoadRet = OpenFileUNIF(FileName);
	else LoadRet = false;

	delete []FileName;

	if (!LoadRet)
	{
		MapperInfo = NULL;
		States->MapperInfo = MapperInfo;
		return;
	}

	PPU->TileHandler = MapperInfo->TileHandler;

	PowerOn();

	if (Debugger->Enabled)
		Debugger->Update();
}

bool cNES::OpenFileiNES(char *toopen)
{
	FILE *in;
	unsigned char HeaderBs[4];		//Header Bytes

	//Filename to open is in the "FileName" char!
	in = fopen(toopen, "rb");
	unsigned long tph, matchh=0x1a53454e;	//Look for NES text in rom.
	fread(&tph,4,1,in);
	if (tph != matchh)
		return(false);
	fread(&HeaderBs[0],4,1,in);

	unsigned char Dummy[0x200];		//0x200 for trainer
	fread(&Dummy,8,1,in);			//Bytes 8-15, dummy bytes...
	
	if (HeaderBs[2] & 0x04)
		fread(&Dummy[0],0x200,1,in);	//Trainer

	fread(&PRG,HeaderBs[0]*0x4000,1,in);		//Read in PRG Data
	fread(&PPU->CHR,HeaderBs[1]*0x2000,1,in);		//Read in CHR Data

	unsigned char MapperNum;
	if ((HeaderBs[3] & 0x0F) > 0)	//Bad Header
		MapperNum = ((HeaderBs[2] & 0xF0) >> 4);
	else							//Proper Header
		MapperNum = ((HeaderBs[2] & 0xF0) >> 4) | (HeaderBs[3] & 0xF0);
	States->MapperNum = MapperNum;

	fclose(in);

	SRAMEnabled = (HeaderBs[2] & 0x02) ? true : false;

	LoadMapperDLL(1);
	MapperParam.Flags = HeaderBs[2] | (HeaderBs[3] << 8);
	MapperParam.PRG_ROM_Size = HeaderBs[0] * 0x4000;
	MapperParam.CHR_ROM_Size = HeaderBs[1] * 0x2000;
	PRGMask = (HeaderBs[0] << 2) - 1;
	CHRMask = (HeaderBs[1] << 3) - 1;
	States->CHRBlocks = HeaderBs[1] << 3;

	bool p2Found = false; for (int p2=1;p2 < 0x10000000;p2 <<= 1) if (p2 == HeaderBs[0]) p2Found = true; if (!p2Found) PRGMask = 0xffffffff;

	MapperInfo = MapperDllInfo->LoadMapper(MapperNum);
	if (!MapperInfo)
	{
		MessageBox(gData->MainWnd, "Mapper Not Supported", "Error", MB_OK);
		return(false);
	}

	States->MapperInfo = MapperInfo;

	return(true);
}

bool cNES::OpenFileUNIF(char *toopen)
{
	States->MapperNum = 0xffff;

	char BlockSig[5];
	BlockSig[4] = 0;
	unsigned long BlockHeader[2];
	unsigned char Empty[0x80000];
	
	FILE *in = fopen(toopen,"rb");
	if (!in)
		return(false);

	char SNSSSig[5];
	SNSSSig[4] = 0;
	fread(&SNSSSig[0],1,4,in);
	if (strcmp(SNSSSig,"UNIF") != 0)
	{
		fclose(in);
		return(false);
	}

	fread(&Empty[0],1,28,in);

	char BoardName[64];

	unsigned char *tPRG[0x10], *tCHR[0x10];
	int PRGSize[0x10], CHRSize[0x10];
	
	for (int i=0;i<0x10;i++)
	{	tPRG[i] = 0; tCHR[i] = 0; }

	LoadMapperDLL(2);

	MapperParam.Flags = 0;
	while (!feof(in))
	{
		fread(&BlockSig[0],1,4,in);
		fread(&BlockHeader[1],1,4,in);
		if (feof(in))
			continue;
		
		if (strcmp(BlockSig,"MAPR") == 0) {
			fread(&BoardName[0],1,BlockHeader[1],in);
		} else if (strcmp(BlockSig,"TVCI") == 0) {
			unsigned char tp;
			fread(&tp,1,1,in);
			if (tp == 0) SetCPUMode(0);
			if (tp == 1) SetCPUMode(1);
			if (tp == 2) SetCPUMode(0);
		} else if (strcmp(BlockSig,"BATR") == 0) {
			unsigned char tp;
			fread(&tp,1,1,in);
			MapperParam.Flags |= (tp) ? 2 : 0;
		} else if (strcmp(BlockSig,"MIRR") == 0) {
			unsigned char tp;
			fread(&tp,1,1,in);
			MapperParam.Flags |= (tp & 0x0F) << 8;
		} else if (strcmp(BlockSig,"PRG0") == 0) { PRGSize[0x0] = BlockHeader[1]; tPRG[0x0] = (unsigned char *) malloc(BlockHeader[1]); fread(tPRG[0x0], 1, BlockHeader[1], in);
		} else if (strcmp(BlockSig,"PRG1") == 0) { PRGSize[0x1] = BlockHeader[1]; tPRG[0x1] = (unsigned char *) malloc(BlockHeader[1]); fread(tPRG[0x1], 1, BlockHeader[1], in);
		} else if (strcmp(BlockSig,"PRG2") == 0) { PRGSize[0x2] = BlockHeader[1]; tPRG[0x2] = (unsigned char *) malloc(BlockHeader[1]); fread(tPRG[0x2], 1, BlockHeader[1], in);
		} else if (strcmp(BlockSig,"PRG3") == 0) { PRGSize[0x3] = BlockHeader[1]; tPRG[0x3] = (unsigned char *) malloc(BlockHeader[1]); fread(tPRG[0x3], 1, BlockHeader[1], in);
		} else if (strcmp(BlockSig,"PRG4") == 0) { PRGSize[0x4] = BlockHeader[1]; tPRG[0x4] = (unsigned char *) malloc(BlockHeader[1]); fread(tPRG[0x4], 1, BlockHeader[1], in);
		} else if (strcmp(BlockSig,"PRG5") == 0) { PRGSize[0x5] = BlockHeader[1]; tPRG[0x5] = (unsigned char *) malloc(BlockHeader[1]); fread(tPRG[0x5], 1, BlockHeader[1], in);
		} else if (strcmp(BlockSig,"PRG6") == 0) { PRGSize[0x6] = BlockHeader[1]; tPRG[0x6] = (unsigned char *) malloc(BlockHeader[1]); fread(tPRG[0x6], 1, BlockHeader[1], in);
		} else if (strcmp(BlockSig,"PRG7") == 0) { PRGSize[0x7] = BlockHeader[1]; tPRG[0x7] = (unsigned char *) malloc(BlockHeader[1]); fread(tPRG[0x7], 1, BlockHeader[1], in);
		} else if (strcmp(BlockSig,"PRG8") == 0) { PRGSize[0x8] = BlockHeader[1]; tPRG[0x8] = (unsigned char *) malloc(BlockHeader[1]); fread(tPRG[0x8], 1, BlockHeader[1], in);
		} else if (strcmp(BlockSig,"PRG9") == 0) { PRGSize[0x9] = BlockHeader[1]; tPRG[0x9] = (unsigned char *) malloc(BlockHeader[1]); fread(tPRG[0x9], 1, BlockHeader[1], in);
		} else if (strcmp(BlockSig,"PRGA") == 0) { PRGSize[0xA] = BlockHeader[1]; tPRG[0xA] = (unsigned char *) malloc(BlockHeader[1]); fread(tPRG[0xA], 1, BlockHeader[1], in);
		} else if (strcmp(BlockSig,"PRGB") == 0) { PRGSize[0xB] = BlockHeader[1]; tPRG[0xB] = (unsigned char *) malloc(BlockHeader[1]); fread(tPRG[0xB], 1, BlockHeader[1], in);
		} else if (strcmp(BlockSig,"PRGC") == 0) { PRGSize[0xC] = BlockHeader[1]; tPRG[0xC] = (unsigned char *) malloc(BlockHeader[1]); fread(tPRG[0xC], 1, BlockHeader[1], in);
		} else if (strcmp(BlockSig,"PRGD") == 0) { PRGSize[0xD] = BlockHeader[1]; tPRG[0xD] = (unsigned char *) malloc(BlockHeader[1]); fread(tPRG[0xD], 1, BlockHeader[1], in);
		} else if (strcmp(BlockSig,"PRGE") == 0) { PRGSize[0xE] = BlockHeader[1]; tPRG[0xE] = (unsigned char *) malloc(BlockHeader[1]); fread(tPRG[0xE], 1, BlockHeader[1], in);
		} else if (strcmp(BlockSig,"PRGF") == 0) { PRGSize[0xF] = BlockHeader[1]; tPRG[0xF] = (unsigned char *) malloc(BlockHeader[1]); fread(tPRG[0xF], 1, BlockHeader[1], in);
		} else if (strcmp(BlockSig,"CHR0") == 0) { CHRSize[0x0] = BlockHeader[1]; tCHR[0x0] = (unsigned char *) malloc(BlockHeader[1]); fread(tCHR[0x0], 1, BlockHeader[1], in);
		} else if (strcmp(BlockSig,"CHR1") == 0) { CHRSize[0x1] = BlockHeader[1]; tCHR[0x1] = (unsigned char *) malloc(BlockHeader[1]); fread(tCHR[0x1], 1, BlockHeader[1], in);
		} else if (strcmp(BlockSig,"CHR2") == 0) { CHRSize[0x2] = BlockHeader[1]; tCHR[0x2] = (unsigned char *) malloc(BlockHeader[1]); fread(tCHR[0x2], 1, BlockHeader[1], in);
		} else if (strcmp(BlockSig,"CHR3") == 0) { CHRSize[0x3] = BlockHeader[1]; tCHR[0x3] = (unsigned char *) malloc(BlockHeader[1]); fread(tCHR[0x3], 1, BlockHeader[1], in);
		} else if (strcmp(BlockSig,"CHR4") == 0) { CHRSize[0x4] = BlockHeader[1]; tCHR[0x4] = (unsigned char *) malloc(BlockHeader[1]); fread(tCHR[0x4], 1, BlockHeader[1], in);
		} else if (strcmp(BlockSig,"CHR5") == 0) { CHRSize[0x5] = BlockHeader[1]; tCHR[0x5] = (unsigned char *) malloc(BlockHeader[1]); fread(tCHR[0x5], 1, BlockHeader[1], in);
		} else if (strcmp(BlockSig,"CHR6") == 0) { CHRSize[0x6] = BlockHeader[1]; tCHR[0x6] = (unsigned char *) malloc(BlockHeader[1]); fread(tCHR[0x6], 1, BlockHeader[1], in);
		} else if (strcmp(BlockSig,"CHR7") == 0) { CHRSize[0x7] = BlockHeader[1]; tCHR[0x7] = (unsigned char *) malloc(BlockHeader[1]); fread(tCHR[0x7], 1, BlockHeader[1], in);
		} else if (strcmp(BlockSig,"CHR8") == 0) { CHRSize[0x8] = BlockHeader[1]; tCHR[0x8] = (unsigned char *) malloc(BlockHeader[1]); fread(tCHR[0x8], 1, BlockHeader[1], in);
		} else if (strcmp(BlockSig,"CHR9") == 0) { CHRSize[0x9] = BlockHeader[1]; tCHR[0x9] = (unsigned char *) malloc(BlockHeader[1]); fread(tCHR[0x9], 1, BlockHeader[1], in);
		} else if (strcmp(BlockSig,"CHRA") == 0) { CHRSize[0xA] = BlockHeader[1]; tCHR[0xA] = (unsigned char *) malloc(BlockHeader[1]); fread(tCHR[0xA], 1, BlockHeader[1], in);
		} else if (strcmp(BlockSig,"CHRB") == 0) { CHRSize[0xB] = BlockHeader[1]; tCHR[0xB] = (unsigned char *) malloc(BlockHeader[1]); fread(tCHR[0xB], 1, BlockHeader[1], in);
		} else if (strcmp(BlockSig,"CHRC") == 0) { CHRSize[0xC] = BlockHeader[1]; tCHR[0xC] = (unsigned char *) malloc(BlockHeader[1]); fread(tCHR[0xC], 1, BlockHeader[1], in);
		} else if (strcmp(BlockSig,"CHRD") == 0) { CHRSize[0xD] = BlockHeader[1]; tCHR[0xD] = (unsigned char *) malloc(BlockHeader[1]); fread(tCHR[0xD], 1, BlockHeader[1], in);
		} else if (strcmp(BlockSig,"CHRE") == 0) { CHRSize[0xE] = BlockHeader[1]; tCHR[0xE] = (unsigned char *) malloc(BlockHeader[1]); fread(tCHR[0xE], 1, BlockHeader[1], in);
		} else if (strcmp(BlockSig,"CHRF") == 0) { CHRSize[0xF] = BlockHeader[1]; tCHR[0xF] = (unsigned char *) malloc(BlockHeader[1]); fread(tCHR[0xF], 1, BlockHeader[1], in);
		} else {
			fread(&Empty[0],1,BlockHeader[1],in);
		}
	}

	unsigned char *PRGPoint = &PRG[0][0], *CHRPoint = &PPU->CHR[0][0];
	
	for (int i=0;i<0x10;i++)
	{
		if (tPRG[i])
		{
			memcpy(PRGPoint, tPRG[i], PRGSize[i]);
			PRGPoint += PRGSize[i];
			free(tPRG[i]);
		}
		if (tCHR[i])
		{
			memcpy(CHRPoint, tCHR[i], CHRSize[i]);
			CHRPoint += CHRSize[i];
			free(tCHR[i]);
		}
	}

	fclose(in);

	MapperParam.PRG_ROM_Size = PRGPoint - &PRG[0][0];
	MapperParam.CHR_ROM_Size = CHRPoint - &PPU->CHR[0][0];
	PRGMask = (MapperParam.PRG_ROM_Size / 0x1000) - 1;
	CHRMask = (MapperParam.CHR_ROM_Size / 0x400) - 1;
	States->CHRBlocks = CHRMask + 1;
	bool p2Found = false; for (int p2=1;p2 < 0x10000000;p2 <<= 1) if (p2 == MapperParam.PRG_ROM_Size) p2Found = true; if (!p2Found) PRGMask = 0xffffffff;

	MapperInfo = MapperDllInfo->LoadMapper_ByBoard(BoardName);
	if (!MapperInfo)
	{
		MessageBox(gData->MainWnd, "Mapper Not Supported", "Error", MB_OK);
		return(false);
	}

	States->MapperInfo = MapperInfo;

	return(true);
}

void cNES::Run()
{
	int i;

	Debugger->TraceOffset = -1;

	Stopped = false;

	for (i=0;i<Controllers->NumDevices;i++)
		if (Controllers->DeviceUsed[i]) Controllers->Acquire(i);

	if (!Stop)
		if (SoundEnabled)
			CPU->APU->SoundON();

	bool HBYet = false;
	int TPPC;
	do
	{
		if (Debugger->Enabled)
			Debugger->AddInst();

		TPPC = CPU->PC & 0xFF00;
		CPU->ExecOp();
		if ((CPU->PC & 0xFF00) != TPPC)
			CPU->Clockticks += 1*12;
	
		while (CPU->Clockticks >= ((ShortSL && (!PPU->SLnum)) ? TicksPerLine - 4 : TicksPerLine))		//Scanline
		{
			HBYet = false;
			PPU->Scanline();
			CPU->Clockticks -= ((ShortSL && (!PPU->SLnum)) ? TicksPerLine - 4 : TicksPerLine);
			LastTicks -= ((ShortSL && (!PPU->SLnum)) ? TicksPerLine - 4 : TicksPerLine);

			if (PPU->SLnum == 241)
			{
				if (Debugger->Enabled)
					Debugger->UpdateGraphics();
				PPU->FrameDone();
				CPU->APU->VBlank();
				Controllers->UpdateInput();
			} else if (PPU->SLnum == 242) {			//NMI at 241 (?)
				if (PPU->ControlReg[0] & 0x80)
					CPU->NMI();
			} else if (!PPU->SLnum) {
				ShortSL ^= 1;
				
				if (States->NeedSave)
					States->SaveState();
				if (States->NeedLoad)
					States->LoadState();

				MSG msg;
				if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
					if (!TranslateAccelerator(gData->MainWnd, gData->hAccelTable, &msg)) 
					{
						TranslateMessage(&msg);
						DispatchMessage(&msg);
					}
			}
		}
		
		if (PPUMode == 1)	//Pixel
		{
			char Pixels2Draw = CPU->Clockticks - LastTicks;
			LastTicks += Pixels2Draw & 0xFC;
			if ((PPU->SLnum < 241) && (PPU->SLnum))
//				if (PPU->Xnum < 256)
				if (PPU->Xnum < 264)
					PPU->DrawPixels(Pixels2Draw >> 2);
				if ((CPU->Clockticks >= 1024) && (!PPU->DiscoveredSprites))
					PPU->DiscoverSprites();
		}

		if ((CPU->Clockticks >= 1024) && (!HBYet))
		{
			HBYet = true;
			if (MapperInfo->HBlank)
				if (MapperInfo->HBlank(PPU->SLnum, PPU->ControlReg[1])) IRQ();
		}

		if (Debugger->Enabled)
			Debugger->Update();

	}	while (!Stop);

	CPU->APU->SoundOFF();

	for (i=0;i<Controllers->NumDevices;i++)
		if (Controllers->DeviceUsed[i]) Controllers->UnAcquire(i);

	char tpo[40];
    sprintf(tpo,"NinthStar - NES - Stopped");
	SetWindowText(gData->MainWnd,tpo);

	Stopped = true;

	if (NeedQuit)
		SendMessage(gData->MainWnd, WM_TEMPDESTROY, 0, 0);
	else if (NeedDie)
		this->Release();
}

void cNES::SetPPUMode(int PPUNum)
{
	cNES_PPU * OldPPU = PPU;

	if (PPUNum == 1)
		PPU = new cNES_PPU_Pixel();
	else if (PPUNum == 2)
		PPU = new cNES_PPU_Scanline();
	else if (PPUNum == 3)
		PPU = new cNES_PPU_Tile();
	else
		return;

	PPU->pGFX = GFX;
	PPU->Sprite = Sprite;
	memcpy(&PPU->FixedPalette,&GFX->FixedPalette,sizeof(GFX->FixedPalette));

	States->pPPU = PPU;
	Debugger->PPU = PPU;
	Debugger->NTabChanged = &PPU->NTabChanged;
	Debugger->PalChanged = &PPU->PalChanged;
	Debugger->PatChanged = &PPU->PatChanged;

	assert(OldPPU != PPU);

	if (OldPPU)
	{
		//Swapping PPUs, Copy Data..
		memcpy(&PPU->CHR[0][0], &OldPPU->CHR[0][0], sizeof(PPU->CHR));
		memcpy(&PPU->CHR_RAM[0][0], &OldPPU->CHR_RAM[0][0], sizeof(PPU->CHR_RAM));
		memcpy(&PPU->Writable[0], &OldPPU->Writable[0], sizeof(PPU->Writable));
		memcpy(&PPU->CHRPointer[0], &OldPPU->CHRPointer[0], sizeof(PPU->CHRPointer));
		memcpy(&PPU->Palette[0][0], &OldPPU->Palette[0][0], sizeof(PPU->Palette));
		memcpy(&PPU->MType[0], &OldPPU->MType[0], sizeof(PPU->MType));

		PPU->ppuLatch = OldPPU->ppuLatch;
		PPU->ppuReadLatch = OldPPU->ppuReadLatch;
		PPU->ControlReg[0] = OldPPU->ControlReg[0]; PPU->ControlReg[1] = OldPPU->ControlReg[1];
		PPU->StatusReg = OldPPU->StatusReg;
		PPU->HVTog = OldPPU->HVTog;
		PPU->VRAMAddr = OldPPU->VRAMAddr; PPU->IntReg = OldPPU->IntReg;
		PPU->IntX = OldPPU->IntX; PPU->IntXBak = OldPPU->IntXBak;
		PPU->EmphVal = OldPPU->EmphVal;
		PPU->SLnum = OldPPU->SLnum; PPU->Xnum = OldPPU->Xnum;
		PPU->DiscoveredSprites = OldPPU->DiscoveredSprites;
		PPU->NTabChanged = OldPPU->NTabChanged; PPU->PalChanged = OldPPU->PalChanged; PPU->PatChanged = OldPPU->PatChanged;
		PPU->SLEndFrame = OldPPU->SLEndFrame;
		memcpy(&PPU->SprBuff[0], &OldPPU->SprBuff[0], sizeof(PPU->SprBuff));
		PPU->Spr0InLine = OldPPU->Spr0InLine; PPU->SprCount = OldPPU->SprCount;

		delete OldPPU;
	}
}

void cNES::UpdateInterface()
{
	GFX->ReLoad(gData->Width, gData->Height, GFX->Mode3D);
	Debugger->DoubleSize = DoubleSize;
	Debugger->SetMode(Debugger->Mode);
}

void cNES::EmuMsg(DWORD Message, DWORD Data1, DWORD Data2)
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
			DoubleSize ^= 1;
			Debugger->DoubleSize = DoubleSize;
			MyMenu = GetMenu(gData->MainWnd);
			if (DoubleSize)
			{		//Check
				SetWindowPos(gData->MainWnd, HWND_TOP, 0, 0, (256*2)+8, (240*2)+48, SWP_SHOWWINDOW);
				gData->Width = 256*2; gData->Height = 240*2;
				CheckMenuItem(MyMenu, ID_OPTIONS_DOUBLESIZEMODE, MF_CHECKED);
			} else {	//Uncheck
				SetWindowPos(gData->MainWnd, HWND_TOP, 0, 0, 256+8, 240+48, SWP_SHOWWINDOW);
				gData->Width = 256; gData->Height = 240;
				CheckMenuItem(MyMenu, ID_OPTIONS_DOUBLESIZEMODE, MF_UNCHECKED);
			}
			break;
		case ID_OPTIONS_AUTOFRAMESKIP:
			GFX->aFSkip ^= true;
			
			MyMenu = GetMenu(gData->MainWnd);
			if (GFX->aFSkip)
			{		//Check
				CheckMenuItem(MyMenu, ID_OPTIONS_AUTOFRAMESKIP, MF_CHECKED);
			} else {	//Uncheck
				CheckMenuItem(MyMenu, ID_OPTIONS_AUTOFRAMESKIP, MF_UNCHECKED);
			}
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
			{		//Check
				CheckMenuItem(MyMenu, ID_OPTIONS_3DHARDWAREACCELERATION, MF_CHECKED);
			} else {	//Uncheck
				CheckMenuItem(MyMenu, ID_OPTIONS_3DHARDWAREACCELERATION, MF_UNCHECKED);
			}
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
		case ID_STATES_SAVESTATE:
			States->NeedSave = true;
			break;
		case ID_STATES_LOADSTATE:
			States->NeedLoad = true;
			if (Stopped)
				States->LoadState();
			break;
		case ID_OPTIONS_CLEARALLBREAKPOINTS:
			ZeroMemory(&Debugger->BreakP,sizeof(Debugger->BreakP));
			break;
		case ID_OPTIONS_SOUNDOPTIONS:
			CPU->APU->Config(gData->MainWnd, gData->hInst);
			break;
		case ID_OPTIONS_SOUNDON:
			if (SoundEnabled ^= true)
				CPU->APU->SoundON();
			else
				CPU->APU->SoundOFF();
			MyMenu = GetMenu(gData->MainWnd);
			if (SoundEnabled)
				CheckMenuItem(MyMenu, ID_OPTIONS_SOUNDON, MF_CHECKED);
			else	//Uncheck
				CheckMenuItem(MyMenu, ID_OPTIONS_SOUNDON, MF_UNCHECKED);
			break;
		case ID_EMULATION_CPUMODE_NTSC:
			SetCPUMode(0);
			GFX->ReLoad(gData->Width, gData->Height, GFX->Mode3D);
			CPUMode = 0;
			MyMenu = GetMenu(gData->MainWnd);
			CheckMenuItem(MyMenu, ID_EMULATION_CPUMODE_NTSC, MF_CHECKED);
			CheckMenuItem(MyMenu, ID_EMULATION_CPUMODE_PAL, MF_UNCHECKED);
			break;
		case ID_EMULATION_CPUMODE_PAL:
			SetCPUMode(1);
			GFX->ReLoad(gData->Width, gData->Height, GFX->Mode3D);
			CPUMode = 1;
			MyMenu = GetMenu(gData->MainWnd);
			CheckMenuItem(MyMenu, ID_EMULATION_CPUMODE_NTSC, MF_UNCHECKED);
			CheckMenuItem(MyMenu, ID_EMULATION_CPUMODE_PAL, MF_CHECKED);
			break;
		case ID_EMULATION_PPUMODE_PIXELBASED:
			SetPPUMode(1);
			PPUMode = 1;
			MyMenu = GetMenu(gData->MainWnd);
			CheckMenuItem(MyMenu, ID_EMULATION_PPUMODE_SCANLINEBASED, MF_UNCHECKED);
			CheckMenuItem(MyMenu, ID_EMULATION_PPUMODE_PIXELBASED, MF_CHECKED);
			CheckMenuItem(MyMenu, ID_EMULATION_PPUMODE_TILEBASED, MF_UNCHECKED);
			break;
		case ID_EMULATION_PPUMODE_SCANLINEBASED:
			SetPPUMode(2);
			PPUMode = 2;
			MyMenu = GetMenu(gData->MainWnd);
			CheckMenuItem(MyMenu, ID_EMULATION_PPUMODE_SCANLINEBASED, MF_CHECKED);
			CheckMenuItem(MyMenu, ID_EMULATION_PPUMODE_PIXELBASED, MF_UNCHECKED);
			CheckMenuItem(MyMenu, ID_EMULATION_PPUMODE_TILEBASED, MF_UNCHECKED);
			break;
		case ID_EMULATION_PPUMODE_TILEBASED:
			SetPPUMode(3);
			PPUMode = 3;
			MyMenu = GetMenu(gData->MainWnd);
			CheckMenuItem(MyMenu, ID_EMULATION_PPUMODE_SCANLINEBASED, MF_UNCHECKED);
			CheckMenuItem(MyMenu, ID_EMULATION_PPUMODE_PIXELBASED, MF_UNCHECKED);
			CheckMenuItem(MyMenu, ID_EMULATION_PPUMODE_TILEBASED, MF_CHECKED);
			break;
		case ID_OPTIONS_CONTROLLERCONFIG:
			Controllers->OpenConfig();
			break;
	}
}

void cNES::LoadSettings()
{
	gData->hAccelTable = LoadAccelerators(gData->hInst, (LPCTSTR)IDR_NES_ACCEL);

	HMENU hMenu = LoadMenu(gData->hInst, (LPCTSTR)IDM_NES_MENU);

	int Keys[4][32];
	unsigned long Size;

	//Load Defaults
	GFX->Mode3D = 0;
	DoubleSize = 0;
	SoundEnabled = 1;
	GFX->aFSkip = 1;
	GFX->FSkip = 0;

	CPUMode = 0;
	PPUMode = 1;

	Keys[0][KEY_NES_A] = DIK_Z;
	Keys[0][KEY_NES_B] = DIK_X;
	Keys[0][KEY_NES_SELECT] = DIK_C;
	Keys[0][KEY_NES_START] = DIK_V;
	Keys[0][KEY_NES_UP] = DIK_UP;
	Keys[0][KEY_NES_DOWN] = DIK_DOWN;
	Keys[0][KEY_NES_LEFT] = DIK_LEFT;
	Keys[0][KEY_NES_RIGHT] = DIK_RIGHT;
	Keys[1][KEY_NES_A] = DIK_U;
	Keys[1][KEY_NES_B] = DIK_I;
	Keys[1][KEY_NES_SELECT] = DIK_O;
	Keys[1][KEY_NES_START] = DIK_P;
	Keys[1][KEY_NES_UP] = DIK_HOME;
	Keys[1][KEY_NES_DOWN] = DIK_END;
	Keys[1][KEY_NES_LEFT] = DIK_DELETE;
	Keys[1][KEY_NES_RIGHT] = DIK_NEXT;
	//End Defaults

	HKEY SettingsBase;
	RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\NinthStar\\NES\\", 0, KEY_ALL_ACCESS, &SettingsBase);
	Size=4; RegQueryValueEx(SettingsBase, "SoundEnabled", 0, NULL, (unsigned char *) &SoundEnabled, &Size);
	Size=4; RegQueryValueEx(SettingsBase, "DoubleSize", 0, NULL, (unsigned char *) &DoubleSize, &Size);
	Size=4; RegQueryValueEx(SettingsBase, "FSkip", 0, NULL, (unsigned char *) &GFX->FSkip, &Size);
	Size=4; RegQueryValueEx(SettingsBase, "aFSkip", 0, NULL, (unsigned char *) &GFX->aFSkip, &Size);
	Size=4; RegQueryValueEx(SettingsBase, "Mode3D", 0, NULL, (unsigned char *) &GFX->Mode3D, &Size);
	Size=4; RegQueryValueEx(SettingsBase, "PPUMode", 0, NULL, (unsigned char *) &PPUMode, &Size);
	Size=4; RegQueryValueEx(SettingsBase, "CPUMode", 0, NULL, (unsigned char *) &CPUMode, &Size);
	Size=sizeof(Keys); RegQueryValueEx(SettingsBase, "Keys", 0, NULL, (unsigned char *) &Keys[0][0], &Size);
	RegCloseKey(SettingsBase);

	Controllers->SetKeys(Keys);

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

	Debugger->DoubleSize = DoubleSize;
	if (DoubleSize)
	{		//Check
		gData->Width = 256*2; gData->Height = 240*2;
		CheckMenuItem(hMenu, ID_OPTIONS_DOUBLESIZEMODE, MF_CHECKED);
	} else {	//Uncheck
		gData->Width = 256; gData->Height = 240;
		CheckMenuItem(hMenu, ID_OPTIONS_DOUBLESIZEMODE, MF_UNCHECKED);
	}

	SetPPUMode(PPUMode);

	if (PPUMode == 1)
	{
		CheckMenuItem(hMenu, ID_EMULATION_PPUMODE_SCANLINEBASED, MF_UNCHECKED);
		CheckMenuItem(hMenu, ID_EMULATION_PPUMODE_PIXELBASED, MF_CHECKED);
		CheckMenuItem(hMenu, ID_EMULATION_PPUMODE_TILEBASED, MF_UNCHECKED);
	} else if (PPUMode == 2) {
		CheckMenuItem(hMenu, ID_EMULATION_PPUMODE_SCANLINEBASED, MF_CHECKED);
		CheckMenuItem(hMenu, ID_EMULATION_PPUMODE_PIXELBASED, MF_UNCHECKED);
		CheckMenuItem(hMenu, ID_EMULATION_PPUMODE_TILEBASED, MF_UNCHECKED);
	} else if (PPUMode == 3) {
		CheckMenuItem(hMenu, ID_EMULATION_PPUMODE_SCANLINEBASED, MF_UNCHECKED);
		CheckMenuItem(hMenu, ID_EMULATION_PPUMODE_PIXELBASED, MF_UNCHECKED);
		CheckMenuItem(hMenu, ID_EMULATION_PPUMODE_TILEBASED, MF_CHECKED);
	}

	SetCPUMode(CPUMode);

	if (CPUMode == 0)
	{
		CheckMenuItem(hMenu, ID_EMULATION_CPUMODE_NTSC, MF_CHECKED);
		CheckMenuItem(hMenu, ID_EMULATION_CPUMODE_PAL, MF_UNCHECKED);
	} else if (CPUMode == 1) {
		CheckMenuItem(hMenu, ID_EMULATION_CPUMODE_NTSC, MF_UNCHECKED);
		CheckMenuItem(hMenu, ID_EMULATION_CPUMODE_PAL, MF_CHECKED);
	}
	
	SetMenu(gData->MainWnd, hMenu);

	SetWindowPos(gData->MainWnd, HWND_TOP, 0, 0, gData->Width+8, gData->Height+48, SWP_SHOWWINDOW);
}

//******************************************************************
//*****************************HANDLERS*****************************
//******************************************************************

//RAM Handlers
int RAMReader(int Bank, int Addy)
{
	return(NES->RAM[Addy & 0x07ff]);
}
void RAMWriter(int Bank, int Addy, int Val)
{
	NES->RAM[Addy & 0x07ff] = Val;
}

//PPU Handlers
int PPUReader(int Bank, int Addy)
{
//	Addy &= 0x7;
	BYTE ToRet;
	switch (Addy & 0x07)
	{
	case 0x0 :
		ToRet = NES->PPU->ppuLatch;
		break;
	case 0x1 :
		ToRet = NES->PPU->ppuLatch;
		break;
	case 0x2 :		//PPU Status
		NES->PPU->StatusReg &= 0xE0;
		NES->PPU->StatusReg |= NES->PPU->ppuLatch & 0x1F;
		ToRet = NES->PPU->StatusReg;
		NES->PPU->StatusReg &= 0x7F;		//Clear VBlank Flag
		NES->PPU->HVTog = true;
		break;
	case 0x3 :
		ToRet = NES->PPU->ppuLatch;
		break;
	case 0x4 :
		ToRet = NES->PPU->ppuLatch;
		break;
	case 0x5 :
		ToRet = NES->PPU->ppuLatch;
		break;
	case 0x6 :
		ToRet = NES->PPU->ppuLatch;
		break;
	case 0x7 :
		NES->PPU->ppuLatch = NES->PPU->ppuReadLatch;
		NES->PPU->ppuReadLatch = NES->PPU->MemGet(NES->PPU->VRAMAddr);

		if (NES->PPU->ControlReg[0] & 0x04)
			NES->PPU->VRAMAddr += 32;
		else
			NES->PPU->VRAMAddr ++;

		return(NES->PPU->ppuLatch);
		break;
	}
	return(ToRet);
}
void PPUWriter(int Bank, int Addy, int Val)
{
//	Addy &= 0x7;
	switch (Addy & 0x07)
	{
	case 0x0 :		//PPU Control 1
		NES->PPU->ControlReg[0] = Val;
		NES->PPU->IntReg &= 0xF3FF;				//2000 write:
		NES->PPU->IntReg |= (Val & 3) << 10;	//		t:0000110000000000=d:00000011
		NES->PPU->ppuLatch = Val;
		break;
	case 0x1 :		//PPU Control 2
		NES->PPU->ControlReg[1] = Val;
		NES->PPU->EmphVal = (Val & 0xE0) << 1;
		NES->PPU->ppuLatch = Val;
		break;
	case 0x2 :		//PPU Control 2
		NES->PPU->ppuLatch = Val;
		break;
	case 0x3 :
		NES->PPU->Sprite->SprAddr = Val;
		NES->PPU->ppuLatch = Val;
		break;
	case 0x4 :
		NES->PPU->Sprite->Sprite[NES->PPU->Sprite->SprAddr] = Val;
		NES->PPU->Sprite->SprAddr++;
		NES->PPU->ppuLatch = Val;
		break;
	case 0x5 :
		if (NES->PPU->HVTog)
		{
			NES->PPU->IntReg &= 0xFFE0;				//2005 first write:
			NES->PPU->IntReg |= (Val & 0xF8) >> 3;	//		t:0000000000011111=d:11111000
//			NES->PPU->IntX = Val & 7;				//		x=d:00000111
			NES->PPU->IntXBak = Val & 7;
		} else {
			NES->PPU->IntReg &= 0x8C1F;					//2005 second write:
			NES->PPU->IntReg |= (Val & 0xF8) << 2;		//		t:0000001111100000=d:11111000
			NES->PPU->IntReg |= (Val & 0x07) << 12;		//		t:0111000000000000=d:00000111
		}
		NES->PPU->HVTog ^= true;
		NES->PPU->ppuLatch = Val;
		break;
	case 0x6 :
		if (NES->PPU->HVTog)
		{
			NES->PPU->IntReg &= 0x00FF;				//2006 first write:
			NES->PPU->IntReg |=	(Val & 0x3F) << 8;	//		t:0011111100000000=d:00111111
		} else {
			NES->PPU->IntReg &= 0xFF00;				//2006 second write:
			NES->PPU->IntReg |= Val;				//		t:0000000011111111=d:11111111
			NES->PPU->VRAMAddr = NES->PPU->IntReg;		//		v=t
//			NES->PPU->IntX = 0;						//		x=0 ???
		}
		
		NES->PPU->HVTog ^= true;
		NES->PPU->ppuLatch = Val;
		break;
	case 0x7 :
		NES->PPU->ppuLatch = Val;

		NES->PPU->MemSet(NES->PPU->VRAMAddr, Val);

		if (NES->PPU->ControlReg[0] & 0x04)
			NES->PPU->VRAMAddr += 32;
		else
			NES->PPU->VRAMAddr ++;
		break;
	}
}

int Regs4kReader(int Bank, int Addy)
{
	switch (Addy)
	{
	case 0x015 :
		return(NES->CPU->APU->Read4015());
	case 0x016 :
		return(NES->Controllers->Cont[0]->Read());
	case 0x017 :
		return(NES->Controllers->Cont[1]->Read());
	default:
		return(0);
	}
}

void Regs4kWriter(int Bank, int Addy, int Val)
{
	int i;
	switch (Addy) {
	case 0x000 :
//		NES->CPU->APU->Regs[0x00]=Val; NES->CPU->APU->Write4000(Val);
		NES->CPU->APU->WriteReg(Addy, Val);
		break;
	case 0x001 :
//		NES->CPU->APU->Regs[0x01]=Val; NES->CPU->APU->Write4001(Val);
		NES->CPU->APU->WriteReg(Addy, Val);
		break;
	case 0x002 :
//		NES->CPU->APU->Regs[0x02]=Val; NES->CPU->APU->Write4002(Val);
		NES->CPU->APU->WriteReg(Addy, Val);
		break;
	case 0x003 :
//		NES->CPU->APU->Regs[0x03]=Val; NES->CPU->APU->Write4003(Val);
		NES->CPU->APU->WriteReg(Addy, Val);
		break;
	case 0x004 :
//		NES->CPU->APU->Regs[0x04]=Val; NES->CPU->APU->Write4004(Val);
		NES->CPU->APU->WriteReg(Addy, Val);
		break;
	case 0x005 :
//		NES->CPU->APU->Regs[0x05]=Val; NES->CPU->APU->Write4005(Val);
		NES->CPU->APU->WriteReg(Addy, Val);
		break;
	case 0x006 :
//		NES->CPU->APU->Regs[0x06]=Val; NES->CPU->APU->Write4006(Val);
		NES->CPU->APU->WriteReg(Addy, Val);
		break;
	case 0x007 :
//		NES->CPU->APU->Regs[0x07]=Val; NES->CPU->APU->Write4007(Val);
		NES->CPU->APU->WriteReg(Addy, Val);
		break;
	case 0x008 :
//		NES->CPU->APU->Regs[0x08]=Val; NES->CPU->APU->Write4008(Val);
		NES->CPU->APU->WriteReg(Addy, Val);
		break;
	case 0x009 :
//		NES->CPU->APU->Regs[0x09]=Val; NES->CPU->APU->Write4009(Val);
		NES->CPU->APU->WriteReg(Addy, Val);
		break;
	case 0x00A :
//		NES->CPU->APU->Regs[0x0A]=Val; NES->CPU->APU->Write400A(Val);
		NES->CPU->APU->WriteReg(Addy, Val);
		break;
	case 0x00B :
//		NES->CPU->APU->Regs[0x0B]=Val; NES->CPU->APU->Write400B(Val);
		NES->CPU->APU->WriteReg(Addy, Val);
		break;
	case 0x00C :
//		NES->CPU->APU->Regs[0x0C]=Val; NES->CPU->APU->Write400C(Val);
		NES->CPU->APU->WriteReg(Addy, Val);
		break;
	case 0x00D :
//		NES->CPU->APU->Regs[0x0D]=Val; NES->CPU->APU->Write400D(Val);
		NES->CPU->APU->WriteReg(Addy, Val);
		break;
	case 0x00E :
//		NES->CPU->APU->Regs[0x0E]=Val; NES->CPU->APU->Write400E(Val);
		NES->CPU->APU->WriteReg(Addy, Val);
		break;
	case 0x00F :
//		NES->CPU->APU->Regs[0x0F]=Val; NES->CPU->APU->Write400F(Val);
		NES->CPU->APU->WriteReg(Addy, Val);
		break;
	case 0x010 :
//		NES->CPU->APU->Regs[0x10]=Val; NES->CPU->APU->Write4010(Val);
		NES->CPU->APU->WriteReg(Addy, Val);
		break;
	case 0x011 :
//		NES->CPU->APU->Regs[0x11]=Val; NES->CPU->APU->Write4011(Val);
		NES->CPU->APU->WriteReg(Addy, Val);
		break;
	case 0x012 :
//		NES->CPU->APU->Regs[0x12]=Val; NES->CPU->APU->Write4012(Val);
		NES->CPU->APU->WriteReg(Addy, Val);
		break;
	case 0x013 :
//		NES->CPU->APU->Regs[0x13]=Val; NES->CPU->APU->Write4013(Val);
		NES->CPU->APU->WriteReg(Addy, Val);
		break;
	case 0x014 :
		NES->CPU->Clockticks += 6144;
		NES->LastTicks += 6144;
		for (i=(Val << 8);i<((Val+1) << 8);i++)
			NES->PPU->Sprite->Sprite[NES->PPU->Sprite->SprAddr++] = NES->CPU->ReadHandler[i >> 12](i >> 12, i & 0xFFF);
		break;
	case 0x015 :
//		NES->CPU->APU->Regs[0x15]=Val; NES->CPU->APU->Write4015(Val);
		NES->CPU->APU->WriteReg(Addy, Val);
		break;
	case 0x016 :
		NES->Controllers->Write(Val);
		break;
	case 0x017 :
//		NES->Controllers->Cont[1]->Write(Val);
		NES->CPU->APU->WriteReg(Addy, Val);
		break;
	}
}

int PRGReader(int Bank, int Addy)
{
	return(NES->PRGPointer[Bank][Addy]);
}
void PRGWriter(int Bank, int Addy, int Val)
{
	if (NES->Writable[Bank])
		*(NES->PRGPointer[Bank] + Addy) = Val;
}

//******************************************************************************
//*****************************MAPPER DLL FUNCTIONS*****************************
//******************************************************************************

void Map_SetWriteHandler(int Page, TWriteFunc New)
{	NES->CPU->WriteHandler[Page] = New; }

void Map_SetReadHandler(int Page, TReadFunc New)
{	NES->CPU->ReadHandler[Page] = New; }

TWriteFunc Map_GetWriteHandler(int Page)
{	return(NES->CPU->WriteHandler[Page]); }

TReadFunc Map_GetReadHandler(int Page)
{	return(NES->CPU->ReadHandler[Page]); }

//******************************************************************************

void	Map_SetPRG_ROM4(int Where, int What)
{
	NES->PRGPointer[Where+0] = NES->PRG[What+0];	NES->Writable[Where+0] = false;
	What &= NES->PRGMask;
}
void	Map_SetPRG_ROM8(int Where, int What)
{
	What <<= 1;
	What &= NES->PRGMask;
	NES->PRGPointer[Where+0] = NES->PRG[What+0];	NES->Writable[Where+0] = false;
	NES->PRGPointer[Where+1] = NES->PRG[What+1];	NES->Writable[Where+1] = false;
}
void	Map_SetPRG_ROM16(int Where, int What)
{
	What <<= 2;
	What &= NES->PRGMask;
	NES->PRGPointer[Where+0] = NES->PRG[What+0];	NES->Writable[Where+0] = false;
	NES->PRGPointer[Where+1] = NES->PRG[What+1];	NES->Writable[Where+1] = false;
	NES->PRGPointer[Where+2] = NES->PRG[What+2];	NES->Writable[Where+2] = false;
	NES->PRGPointer[Where+3] = NES->PRG[What+3];	NES->Writable[Where+3] = false;
}
void	Map_SetPRG_ROM32(int Where, int What)
{
	What <<= 3;
	What &= NES->PRGMask;
	NES->PRGPointer[Where+0] = NES->PRG[What+0];	NES->Writable[Where+0] = false;
	NES->PRGPointer[Where+1] = NES->PRG[What+1];	NES->Writable[Where+1] = false;
	NES->PRGPointer[Where+2] = NES->PRG[What+2];	NES->Writable[Where+2] = false;
	NES->PRGPointer[Where+3] = NES->PRG[What+3];	NES->Writable[Where+3] = false;
	NES->PRGPointer[Where+4] = NES->PRG[What+4];	NES->Writable[Where+4] = false;
	NES->PRGPointer[Where+5] = NES->PRG[What+5];	NES->Writable[Where+5] = false;
	NES->PRGPointer[Where+6] = NES->PRG[What+6];	NES->Writable[Where+6] = false;
	NES->PRGPointer[Where+7] = NES->PRG[What+7];	NES->Writable[Where+7] = false;
}
int	Map_GetPRG_ROM4(int Where)	/* -1 if no ROM mapped */
{
	int tpi = (NES->PRGPointer[Where] - NES->PRG[0]) >> 12;
	if ((tpi < 0) || (tpi > ((NES->MapperParam.PRG_ROM_Size - 1) >> 12))) return(-1);
	else return(tpi);
}


//******************************************************************************

void	Map_SetPRG_RAM4(int Where, int What)
{
	NES->PRGPointer[Where+0] = NES->SRAM[What+0];	NES->Writable[Where+0] = true;
}
void	Map_SetPRG_RAM8(int Where, int What)
{
	What <<= 1;
	NES->PRGPointer[Where+0] = NES->SRAM[What+0];	NES->Writable[Where+0] = true;
	NES->PRGPointer[Where+1] = NES->SRAM[What+1];	NES->Writable[Where+1] = true;
}
void	Map_SetPRG_RAM16(int Where, int What)
{
	What <<= 2;
	NES->PRGPointer[Where+0] = NES->SRAM[What+0];	NES->Writable[Where+0] = true;
	NES->PRGPointer[Where+1] = NES->SRAM[What+1];	NES->Writable[Where+1] = true;
	NES->PRGPointer[Where+2] = NES->SRAM[What+2];	NES->Writable[Where+2] = true;
	NES->PRGPointer[Where+3] = NES->SRAM[What+3];	NES->Writable[Where+3] = true;
}
void	Map_SetPRG_RAM32(int Where, int What)
{
	What <<= 3;
	NES->PRGPointer[Where+0] = NES->SRAM[What+0];	NES->Writable[Where+0] = true;
	NES->PRGPointer[Where+1] = NES->SRAM[What+1];	NES->Writable[Where+1] = true;
	NES->PRGPointer[Where+2] = NES->SRAM[What+2];	NES->Writable[Where+2] = true;
	NES->PRGPointer[Where+3] = NES->SRAM[What+3];	NES->Writable[Where+3] = true;
	NES->PRGPointer[Where+4] = NES->SRAM[What+4];	NES->Writable[Where+4] = true;
	NES->PRGPointer[Where+5] = NES->SRAM[What+5];	NES->Writable[Where+5] = true;
	NES->PRGPointer[Where+6] = NES->SRAM[What+6];	NES->Writable[Where+6] = true;
	NES->PRGPointer[Where+7] = NES->SRAM[What+7];	NES->Writable[Where+7] = true;
}
int	Map_GetPRG_RAM4(int Where)	/* -1 if no RAM mapped */
{
	int tpi = (NES->PRGPointer[Where] - NES->SRAM[0]) >> 12;
	if ((tpi < 0) || (tpi > 0xF)) return(-1);
	else return(tpi);
}

//******************************************************************************

void *	Map_GetPRG_Ptr4(int Where)
{
	return(NES->PRGPointer[Where]);
}
void	Map_SetPRG_OB4(int Where)	/* Open bus */
{
	//Deal with openbus later kthx...
}

//******************************************************************************

void	Map_SetCHR_ROM1(int Where, int What)
{
	What &= NES->CHRMask;
	NES->PPU->Writable[Where+0] = false;	NES->PPU->CHRPointer[Where+0] = NES->PPU->CHR[What+0];
	NES->PPU->PatChanged = true;
}
void	Map_SetCHR_ROM2(int Where, int What)
{
	What <<= 1;
	What &= NES->CHRMask;
	NES->PPU->Writable[Where+0] = false;	NES->PPU->CHRPointer[Where+0] = NES->PPU->CHR[What+0];
	NES->PPU->Writable[Where+1] = false;	NES->PPU->CHRPointer[Where+1] = NES->PPU->CHR[What+1];
	NES->PPU->PatChanged = true;
}
void	Map_SetCHR_ROM4(int Where, int What)
{
	What <<= 2;
	What &= NES->CHRMask;
	NES->PPU->Writable[Where+0] = false;	NES->PPU->CHRPointer[Where+0] = NES->PPU->CHR[What+0];
	NES->PPU->Writable[Where+1] = false;	NES->PPU->CHRPointer[Where+1] = NES->PPU->CHR[What+1];
	NES->PPU->Writable[Where+2] = false;	NES->PPU->CHRPointer[Where+2] = NES->PPU->CHR[What+2];
	NES->PPU->Writable[Where+3] = false;	NES->PPU->CHRPointer[Where+3] = NES->PPU->CHR[What+3];
	NES->PPU->PatChanged = true;
}
void	Map_SetCHR_ROM8(int Where, int What)
{
	What <<= 3;
	What &= NES->CHRMask;
	NES->PPU->Writable[Where+0] = false;	NES->PPU->CHRPointer[Where+0] = NES->PPU->CHR[What+0];
	NES->PPU->Writable[Where+1] = false;	NES->PPU->CHRPointer[Where+1] = NES->PPU->CHR[What+1];
	NES->PPU->Writable[Where+2] = false;	NES->PPU->CHRPointer[Where+2] = NES->PPU->CHR[What+2];
	NES->PPU->Writable[Where+3] = false;	NES->PPU->CHRPointer[Where+3] = NES->PPU->CHR[What+3];
	NES->PPU->Writable[Where+4] = false;	NES->PPU->CHRPointer[Where+4] = NES->PPU->CHR[What+4];
	NES->PPU->Writable[Where+5] = false;	NES->PPU->CHRPointer[Where+5] = NES->PPU->CHR[What+5];
	NES->PPU->Writable[Where+6] = false;	NES->PPU->CHRPointer[Where+6] = NES->PPU->CHR[What+6];
	NES->PPU->Writable[Where+7] = false;	NES->PPU->CHRPointer[Where+7] = NES->PPU->CHR[What+7];
	NES->PPU->PatChanged = true;
}
int	Map_GetCHR_ROM1(int Where)	/* -1 if no ROM mapped */
{
	int tpi = (NES->PPU->CHRPointer[Where] - NES->PPU->CHR[0]) >> 10;
	if ((tpi < 0) || (tpi > ((NES->MapperParam.CHR_ROM_Size - 1) >> 10))) return(-1);
	else return(tpi);
}

//******************************************************************************

void	Map_SetCHR_RAM1(int Where, int What)
{
	NES->PPU->Writable[Where+0] = true;	NES->PPU->CHRPointer[Where+0] = NES->PPU->CHR_RAM[What+0];
	NES->PPU->PatChanged = true;
}
void	Map_SetCHR_RAM2(int Where, int What)
{
	What <<= 1;
	NES->PPU->Writable[Where+0] = true;	NES->PPU->CHRPointer[Where+0] = NES->PPU->CHR_RAM[What+0];
	NES->PPU->Writable[Where+1] = true;	NES->PPU->CHRPointer[Where+1] = NES->PPU->CHR_RAM[What+1];
	NES->PPU->PatChanged = true;
}
void	Map_SetCHR_RAM4(int Where, int What)
{
	What <<= 2;
	NES->PPU->Writable[Where+0] = true;	NES->PPU->CHRPointer[Where+0] = NES->PPU->CHR_RAM[What+0];
	NES->PPU->Writable[Where+1] = true;	NES->PPU->CHRPointer[Where+1] = NES->PPU->CHR_RAM[What+1];
	NES->PPU->Writable[Where+2] = true;	NES->PPU->CHRPointer[Where+2] = NES->PPU->CHR_RAM[What+2];
	NES->PPU->Writable[Where+3] = true;	NES->PPU->CHRPointer[Where+3] = NES->PPU->CHR_RAM[What+3];
	NES->PPU->PatChanged = true;
}
void	Map_SetCHR_RAM8(int Where, int What)
{
	What <<= 3;
	NES->PPU->Writable[Where+0] = true;	NES->PPU->CHRPointer[Where+0] = NES->PPU->CHR_RAM[What+0];
	NES->PPU->Writable[Where+1] = true;	NES->PPU->CHRPointer[Where+1] = NES->PPU->CHR_RAM[What+1];
	NES->PPU->Writable[Where+2] = true;	NES->PPU->CHRPointer[Where+2] = NES->PPU->CHR_RAM[What+2];
	NES->PPU->Writable[Where+3] = true;	NES->PPU->CHRPointer[Where+3] = NES->PPU->CHR_RAM[What+3];
	NES->PPU->Writable[Where+4] = true;	NES->PPU->CHRPointer[Where+4] = NES->PPU->CHR_RAM[What+4];
	NES->PPU->Writable[Where+5] = true;	NES->PPU->CHRPointer[Where+5] = NES->PPU->CHR_RAM[What+5];
	NES->PPU->Writable[Where+6] = true;	NES->PPU->CHRPointer[Where+6] = NES->PPU->CHR_RAM[What+6];
	NES->PPU->Writable[Where+7] = true;	NES->PPU->CHRPointer[Where+7] = NES->PPU->CHR_RAM[What+7];
	NES->PPU->PatChanged = true;
}
int	Map_GetCHR_RAM1(int Where)	/* -1 if no ROM mapped */
{
	int tpi = (NES->PPU->CHRPointer[Where] - NES->PPU->CHR_RAM[0]) >> 10;
	if ((tpi < 0) || (tpi > 0x1F)) return(-1);
	else return(tpi);
}

//******************************************************************************

void *	Map_GetCHR_Ptr1(int Where)
{
	return(NES->PPU->CHRPointer[Where]);
}

//******************************************************************************

void	Map_Mirror_H()
{
	NES->PPU->CHRPointer[0x8] = NES->PPU->CHR_RAM[0x10];	NES->PPU->CHRPointer[0x9] = NES->PPU->CHR_RAM[0x10];
	NES->PPU->CHRPointer[0xA] = NES->PPU->CHR_RAM[0x11];	NES->PPU->CHRPointer[0xB] = NES->PPU->CHR_RAM[0x11];
	NES->PPU->NTabChanged = true;
}
void	Map_Mirror_V()
{
	NES->PPU->CHRPointer[0x8] = NES->PPU->CHR_RAM[0x10];	NES->PPU->CHRPointer[0x9] = NES->PPU->CHR_RAM[0x11];
	NES->PPU->CHRPointer[0xA] = NES->PPU->CHR_RAM[0x10];	NES->PPU->CHRPointer[0xB] = NES->PPU->CHR_RAM[0x11];
	NES->PPU->NTabChanged = true;
}
void	Map_Mirror_4()
{
	NES->PPU->CHRPointer[0x8] = NES->PPU->CHR_RAM[0x10];	NES->PPU->CHRPointer[0x9] = NES->PPU->CHR_RAM[0x11];
	NES->PPU->CHRPointer[0xA] = NES->PPU->CHR_RAM[0x12];	NES->PPU->CHRPointer[0xB] = NES->PPU->CHR_RAM[0x13];
	NES->PPU->NTabChanged = true;
}
void	Map_Mirror_S0()
{
	NES->PPU->CHRPointer[0x8] = NES->PPU->CHR_RAM[0x10];	NES->PPU->CHRPointer[0x9] = NES->PPU->CHR_RAM[0x10];
	NES->PPU->CHRPointer[0xA] = NES->PPU->CHR_RAM[0x10];	NES->PPU->CHRPointer[0xB] = NES->PPU->CHR_RAM[0x10];
	NES->PPU->NTabChanged = true;
}
void	Map_Mirror_S1()
{
	NES->PPU->CHRPointer[0x8] = NES->PPU->CHR_RAM[0x11];	NES->PPU->CHRPointer[0x9] = NES->PPU->CHR_RAM[0x11];
	NES->PPU->CHRPointer[0xA] = NES->PPU->CHR_RAM[0x11];	NES->PPU->CHRPointer[0xB] = NES->PPU->CHR_RAM[0x11];
	NES->PPU->NTabChanged = true;
}
void	Map_Mirror_Custom(int M1, int M2, int M3, int M4)
{
	NES->PPU->CHRPointer[0x8] = NES->PPU->CHR_RAM[0x10|M1];	NES->PPU->CHRPointer[0x9] = NES->PPU->CHR_RAM[0x10|M2];
	NES->PPU->CHRPointer[0xA] = NES->PPU->CHR_RAM[0x10|M3];	NES->PPU->CHRPointer[0xB] = NES->PPU->CHR_RAM[0x10|M4];
	NES->PPU->NTabChanged = true;
}

//******************************************************************************

void	Map_Set_SRAMSize(int Size)	/* Sets the size of the SRAM (in bytes) and clears PRG_RAM */
{
	NES->SRAM_Size = Size;
}
void	Map_Save_SRAM()	/* Saves SRAM to disk */
{
	FILE * SRAMFile = fopen(NES->SRAMFileName,"w+b");

	fwrite(&NES->SRAM[0], 1, NES->SRAM_Size, SRAMFile);

	fclose(SRAMFile);
}
void	Map_Load_SRAM()	/* Loads SRAM from disk */
{
	FILE *SRAMFile = fopen(NES->SRAMFileName,"r+b");
	if (!SRAMFile)
		SRAMFile = fopen(NES->SRAMFileName,"w+b");

	fseek(SRAMFile,0,SEEK_END);
	int filelen = ftell(SRAMFile);
	if (filelen >= NES->SRAM_Size)
	{
		fseek(SRAMFile,0,SEEK_SET);
		fread(&NES->SRAM[0], 1, NES->SRAM_Size, SRAMFile);
	}
	
	fclose(SRAMFile);
}

//******************************************************************************

void	Map_DbgOut(char *ToSay)
{
	int bleh = 4;
}

//******************************************************************************

void	Map_MMC5_UpdateAttributeCache()
{
}

//******************************************************************************

void cNES::LoadMapperDLL(int Num)
{
	MapperDllInst = 0;
	if (Num == 1)	//iNES
	{
		if (!MapperDllInst) MapperDllInst = LoadLibrary("iNES.dll");
		if (!MapperDllInst) MapperDllInst = LoadLibrary("NES_iNES.dll");
		if (!MapperDllInst) MapperDllInst = LoadLibrary("Mappers\\iNES.dll");
		if (!MapperDllInst) MapperDllInst = LoadLibrary("Mappers\\NES_iNES.dll");
		if (!MapperDllInst) MapperDllInst = LoadLibrary("NES_Mappers.dll");
		if (!MapperDllInst) MapperDllInst = LoadLibrary("mappers.dll");
		if (!MapperDllInst) MapperDllInst = LoadLibrary("Mappers\\NES_Mappers.dll");
		if (!MapperDllInst) MapperDllInst = LoadLibrary("Mappers\\mappers.dll");
		if (!MapperDllInst)
		{
			MessageBox(gData->MainWnd, "No Mappers DLL Found!  Erroring...", "kthxuNF", MB_OK);
			return;
		}
		TDLL_Info * (*TPF)(int) = (TDLL_Info * (*)(int))GetProcAddress(MapperDllInst,"Load_DLL");
		MapperDllInfo = TPF(CurrentMapperInterface);
	} else if (Num == 2) {	//UNIF
		if (!MapperDllInst) MapperDllInst = LoadLibrary("UNIF.dll");
		if (!MapperDllInst) MapperDllInst = LoadLibrary("NES_UNIF.dll");
		if (!MapperDllInst) MapperDllInst = LoadLibrary("Mappers\\UNIF.dll");
		if (!MapperDllInst) MapperDllInst = LoadLibrary("Mappers\\NES_UNIF.dll");
		if (!MapperDllInst) MapperDllInst = LoadLibrary("NES_Mappers.dll");
		if (!MapperDllInst) MapperDllInst = LoadLibrary("mappers.dll");
		if (!MapperDllInst) MapperDllInst = LoadLibrary("Mappers\\NES_Mappers.dll");
		if (!MapperDllInst) MapperDllInst = LoadLibrary("Mappers\\mappers.dll");
		if (!MapperDllInst)
		{
			MessageBox(gData->MainWnd, "No Mappers DLL Found!  Erroring...", "kthxuNF", MB_OK);
			return;
		}
		TDLL_Info * (*TPF)(int) = (TDLL_Info * (*)(int))GetProcAddress(MapperDllInst,"Load_DLL");
		MapperDllInfo = TPF(CurrentMapperInterface);
	}

	MapperParam.SetWriteHandler = &Map_SetWriteHandler;
	MapperParam.SetReadHandler = &Map_SetReadHandler;
	MapperParam.GetWriteHandler = &Map_GetWriteHandler;
	MapperParam.GetReadHandler = &Map_GetReadHandler;
	MapperParam.SetPRG_ROM4 = &Map_SetPRG_ROM4;
	MapperParam.SetPRG_ROM8 = &Map_SetPRG_ROM8;
	MapperParam.SetPRG_ROM16 = &Map_SetPRG_ROM16;
	MapperParam.SetPRG_ROM32 = &Map_SetPRG_ROM32;
	MapperParam.GetPRG_ROM4 = &Map_GetPRG_ROM4;
	MapperParam.SetPRG_RAM4 = &Map_SetPRG_RAM4;
	MapperParam.SetPRG_RAM8 = &Map_SetPRG_RAM8;
	MapperParam.SetPRG_RAM16 = &Map_SetPRG_RAM16;
	MapperParam.SetPRG_RAM32 = &Map_SetPRG_RAM32;
	MapperParam.GetPRG_RAM4 = &Map_GetPRG_RAM4;
	MapperParam.GetPRG_Ptr4 = &Map_GetPRG_Ptr4;
	MapperParam.SetPRG_OB4 = &Map_SetPRG_OB4;
	MapperParam.SetCHR_ROM1 = &Map_SetCHR_ROM1;
	MapperParam.SetCHR_ROM2 = &Map_SetCHR_ROM2;
	MapperParam.SetCHR_ROM4 = &Map_SetCHR_ROM4;
	MapperParam.SetCHR_ROM8 = &Map_SetCHR_ROM8;
	MapperParam.GetCHR_ROM1 = &Map_GetCHR_ROM1;
	MapperParam.SetCHR_RAM1 = &Map_SetCHR_RAM1;
	MapperParam.SetCHR_RAM2 = &Map_SetCHR_RAM2;
	MapperParam.SetCHR_RAM4 = &Map_SetCHR_RAM4;
	MapperParam.SetCHR_RAM8 = &Map_SetCHR_RAM8;
	MapperParam.GetCHR_RAM1 = &Map_GetCHR_RAM1;
	MapperParam.GetCHR_Ptr1 = &Map_GetCHR_Ptr1;
	MapperParam.Mirror_H = &Map_Mirror_H;
	MapperParam.Mirror_V = &Map_Mirror_V;
	MapperParam.Mirror_4 = &Map_Mirror_4;
	MapperParam.Mirror_S0 = &Map_Mirror_S0;
	MapperParam.Mirror_S1 = &Map_Mirror_S1;
	MapperParam.Mirror_Custom = &Map_Mirror_Custom;
	MapperParam.Set_SRAMSize = &Map_Set_SRAMSize;
	MapperParam.Save_SRAM = &Map_Save_SRAM;
	MapperParam.Load_SRAM = &Map_Load_SRAM;
	MapperParam.DbgOut = &Map_DbgOut;
	MapperParam.MMC5_UpdateAttributeCache = &Map_MMC5_UpdateAttributeCache;
}

//******************************************************************************
