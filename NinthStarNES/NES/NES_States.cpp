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
#include "NES_States.h"

#include "NES_APU.h"

#include "..\Global.h"

#define MSBSwapShort(ShortVar)	ShortVar = (((ShortVar & 0xFF00) >> 8) | ((ShortVar & 0x00FF) << 8))
#define MSBSwapLong(LongVar)	LongVar = (((LongVar & 0xFF000000) >> 24) | ((LongVar & 0x00FF0000) >> 8) | ((LongVar & 0x0000FF00) << 8) | ((LongVar & 0x000000FF) << 24))

cNES_States::cNES_States()
{
	SelSlot = 0;
	NeedSave = false;
	NeedLoad = false;
}

void cNES_States::SetSlot(int Slot)
{
	SelSlot = Slot;

	pGFX->ShowTextCounter = 40;
	sprintf(pGFX->TextDisp,"State Selected: %i", Slot);
}

void cNES_States::SaveState()
{
	NeedSave = false;
	char tpchr[80];
	ZeroMemory(tpchr,80);
	sprintf(tpchr,"%sss%i",FileNameBase,SelSlot);

	FILE *out = fopen(tpchr,"w+b");

	unsigned int tpi;
	unsigned short tps;
	BYTE tpb;

	int NumBlocks = 0;
	char tpc[5]="SNSS";
	fwrite(tpc,1,4,out);
	tpi = MSBSwapLong(NumBlocks);
	fwrite(&tpi,1,4,out);
	
	//Write BASR Block
	NumBlocks++;
		//Header
	sprintf(tpc,"BASR");
	fwrite(tpc,1,4,out);
	tpi = 1;
	MSBSwapLong(tpi);
	fwrite(&tpi,1,4,out);
	tpi = 0x1931;
	MSBSwapLong(tpi);
	fwrite(&tpi,1,4,out);
		//Data
	fwrite(&pCPU->A,1,1,out);
	fwrite(&pCPU->X,1,1,out);
	fwrite(&pCPU->Y,1,1,out);
	fwrite(&pCPU->P,1,1,out);
	fwrite(&pCPU->SP,1,1,out);
	tps = pCPU->PC;
	MSBSwapShort(tps);
	fwrite(&tps,1,2,out);
	fwrite(&pPPU->ControlReg[0],1,2,out);
	fwrite(pCPU->RAM,1,0x800,out);
	fwrite(&pPPU->Sprite[0],1,0x100,out);
	for (int i=8;i<12;i++)
		fwrite(pPPU->CHRPointer[i], 1, 0x400, out);
	fwrite(&pPPU->Palette[0][0],1,0x20,out);
	for (int i=8;i<12;i++)
	{
		unsigned char tpa = (pPPU->CHRPointer[i] - pPPU->CHR_RAM[0x10 + i - 8]) >> 10;
		fwrite(&tpa,1,1,out);
	}
	tps = pPPU->VRAMAddr;
	MSBSwapShort(tps);
	fwrite(&tps,1,2,out);
	fwrite(&pPPU->SprAddr,1,1,out);
	fwrite(&pPPU->IntX,1,1,out);

	if (!CHRBlocks)
	{
		//Write VRAM Block
		NumBlocks++;
			//Header
		sprintf(tpc,"VRAM");	//Block
		fwrite(tpc,1,4,out);
		tpi = 1;				//Version
		MSBSwapLong(tpi);
		fwrite(&tpi,1,4,out);
//work on length shit...
//this is just a hack for 99% of games...
		tpi = 0x2000;			//Length
		MSBSwapLong(tpi);
		fwrite(&tpi,1,4,out);
			//Data
		fwrite(&pPPU->CHR_RAM[0][0],1,0x2000,out);
	}

	if (SRAMHWEnabled)
	{
		//Write SRAM Block
		NumBlocks++;
			//Header
		sprintf(tpc,"SRAM");	//Block
		fwrite(tpc,1,4,out);
		tpi = 1;				//Version
		MSBSwapLong(tpi);
		fwrite(&tpi,1,4,out);
		tpi = *SRAM_Size;			//Length
		MSBSwapLong(tpi);
		fwrite(&tpi,1,4,out);
			//Data
//		tpb = (*SRAMEnabled) ? 1 : 0;
//hack...
		tpb = 1;
		fwrite(&tpb,1,1,out);
		fwrite(SRAM,1,*SRAM_Size,out);
	}

	if (MapperNum > 0)
	{
		//Write SRAM Block
		NumBlocks++;
			//Header
		sprintf(tpc,"MPRD");	//Block
		fwrite(tpc,1,4,out);
		tpi = 1;				//Version
		MSBSwapLong(tpi);
		fwrite(&tpi,1,4,out);
		tpi = 0x98;				//Length
		MSBSwapLong(tpi);
		fwrite(&tpi,1,4,out);
			//Data
		short tpss[8];
		for (int i=0;i<4;i++)
		{ tpss[i] = Map_GetPRG_ROM4(8 + (i << 1)) >> 1; MSBSwapShort(tpss[i]); }
		fwrite(&tpss[0],4,2,out);
		for (int i=0;i<8;i++)
		{ if (pPPU->Writable[i]) tpss[i] = Map_GetCHR_RAM1(i); else tpss[i] = Map_GetCHR_ROM1(i); MSBSwapShort(tpss[i]); }
		fwrite(&tpss[0],8,2,out);
		unsigned char TPMD[0x80];
		if (MapperInfo->SaveMI)
			MapperInfo->SaveMI(TPMD);
		fwrite(&TPMD[0],1,0x80,out);
	}

	//Write CNTR Block
	NumBlocks++;
		//Header
	sprintf(tpc,"CNTR");	//Block
	fwrite(tpc,1,4,out);
	tpi = 1;				//Version
	MSBSwapLong(tpi);
	fwrite(&tpi,1,4,out);
	tpi = 0x11;				//Length
	MSBSwapLong(tpi);
	fwrite(&tpi,1,4,out);
		//Data
	tpb = 0;
	fwrite(&tpb,1,1,out);
	fwrite(&tpb,1,1,out);
	fwrite(&pControllers->Cont[0]->BitPtr,1,1,out);
	fwrite(&pControllers->Cont[1]->BitPtr,1,1,out);
	fwrite(&pControllers->Cont[0]->Strobe,1,1,out);
	tps = 0;
	MSBSwapShort(tps);
	fwrite(&tps,1,2,out);
	tpi = pControllers->Cont[0]->Bits;
	MSBSwapLong(tpi);
	fwrite(&tpi,1,4,out);
	tpb = 1;
	fwrite(&tpb,1,1,out);
	tpi = pControllers->Cont[1]->Bits;
	MSBSwapLong(tpi);
	fwrite(&tpi,1,4,out);
	fwrite(&tpb,1,1,out);

	//Write SOUN Block
	NumBlocks++;
		//Header
	sprintf(tpc,"SOUN");	//Block
	fwrite(tpc,1,4,out);
	tpi = 1;				//Version
	MSBSwapLong(tpi);
	fwrite(&tpi,1,4,out);
	tpi = 0x16;				//Length
	MSBSwapLong(tpi);
	fwrite(&tpi,1,4,out);
		//Data
	unsigned char tpk[0x16];
	pCPU->APU->GetSoundRegisters(&tpk[0]);
	fwrite(&tpk[0],1,0x16,out);

	//Write final NumBlocks
	fseek(out, 4, SEEK_SET);
	tpi = MSBSwapLong(NumBlocks);
	fwrite(&tpi,1,4,out);
	fclose(out);

	pGFX->ShowTextCounter = 40;
	sprintf(pGFX->TextDisp,"State Saved: %i", SelSlot);
}

void cNES_States::LoadState()
{
	NeedLoad = false;
	char tpchr[80];
	ZeroMemory(tpchr,80);
	sprintf(tpchr,"%sss%i",FileNameBase,SelSlot);
	
	FILE *in = fopen(tpchr,"rb");
	if (!in)
	{
		pGFX->ShowTextCounter = 40;
		sprintf(pGFX->TextDisp,"Load Failed: %i", SelSlot);
		return;
	}

	char SNSSSig[5];
	SNSSSig[4] = 0;
	fread(&SNSSSig[0],1,4,in);
	if (strcmp(SNSSSig,"SNSS") != 0)
	{
		fclose(in);

		pGFX->ShowTextCounter = 40;
		sprintf(pGFX->TextDisp,"State Load Failed: %i", SelSlot);
		
		return;
	}

	pPPU->SLnum = 0;
	pPPU->Xnum = 0;
	gData->Main->Clockticks = 0;
	gData->Main->LastTicks = 0;

	int NumBlocks;
	fread(&NumBlocks,1,4,in);
	MSBSwapLong(NumBlocks);

	char BlockSig[5];
	BlockSig[4] = 0;
	int BlockHeader[2];
	char EmptyBlock[0x10000];
	
	char mystr[50];
	sprintf(mystr,"State Loaded!\n");

	for (int i=0;i<NumBlocks;i++)
	{
		fread(&BlockSig[0],1,4,in);
		fread(&BlockHeader[0],2,4,in);
		MSBSwapLong(BlockHeader[0]);
		MSBSwapLong(BlockHeader[1]);
		
		if (strcmp(BlockSig,"BASR") == 0) {
			if (BlockHeader[0] == 1)
			{
				fread(&pCPU->A,1,1,in);
				fread(&pCPU->X,1,1,in);
				fread(&pCPU->Y,1,1,in);
				fread(&pCPU->P,1,1,in);
				fread(&pCPU->SP,1,1,in);
				fread(&pCPU->PC,1,2,in);
				MSBSwapShort(pCPU->PC);
				fread(&pPPU->ControlReg[0],1,2,in);
				fread(pCPU->RAM,1,0x800,in);
				fread(&pPPU->Sprite[0],1,0x100,in);
				for (int i=8;i<12;i++)
					fread(&pPPU->CHR_RAM[0x10 + i - 8][0], 1, 0x400, in);
				fread(&pPPU->Palette[0][0],1,0x20,in);
				for (int i=8;i<12;i++)
				{
					unsigned char tpa;
					fread(&tpa,1,1,in);
					pPPU->CHRPointer[i] = (pPPU->CHR_RAM[0x10 + i - 8] + (tpa << 10));
				}
				fread(&pPPU->VRAMAddr,1,2,in);
				MSBSwapShort(pPPU->VRAMAddr);
				fread(&pPPU->SprAddr,1,1,in);
				fread(&pPPU->IntX,1,1,in);
			}
		} else if (strcmp(BlockSig,"VRAM") == 0) {
			if (BlockHeader[0] == 1)
			{
//				fread(&pPPU->CHR[0],1,BlockHeader[1],in);
				fwrite(&pPPU->CHR_RAM[0][0],1,BlockHeader[1],in);
			}
		} else if (strcmp(BlockSig,"SRAM") == 0) {
			if (BlockHeader[0] == 1)
			{
//				fread(&pSRAM->SRAMEnabled,1,1,in);
				fread(&EmptyBlock[0],1,1,in);
				fread(SRAM,BlockHeader[1],1,in);
			}
		} else if (strcmp(BlockSig,"CNTR") == 0) {
			if (BlockHeader[0] == 1)
			{
				fread(&EmptyBlock[0],1,2,in);			//Controller Type
				fread(&pControllers->Cont[0]->BitPtr,1,1,in);
				fread(&pControllers->Cont[1]->BitPtr,1,1,in);
				fread(&pControllers->Cont[0]->Strobe,1,1,in);		//Strobe bit... eh? Only 1?...
				fread(&EmptyBlock[0],1,2,in);			//VS Dip Switches
				fread(&pControllers->Cont[0]->Bits,1,4,in);
				MSBSwapLong(pControllers->Cont[0]->Bits);
				fread(&EmptyBlock[0],1,1,in);			//Repeat Count Krap
				fread(&pControllers->Cont[1]->Bits,1,4,in);
				MSBSwapLong(pControllers->Cont[1]->Bits);
				fread(&EmptyBlock[0],1,1,in);			//Repeat Count Krap

				fread(&EmptyBlock[0],1,BlockHeader[1]-0x11,in);			//Ignore Movie Shit...
			}
		} else if (strcmp(BlockSig,"SOUN") == 0) {
			if (BlockHeader[0] == 1)
			{
				unsigned char tpk[0x16];
				fread(&tpk[0],1,0x16,in);
				pCPU->APU->SetSoundRegisters(tpk);
			}
		} else if (strcmp(BlockSig,"MPRD") == 0) {
			if (BlockHeader[0] == 1)
			{
				unsigned short tps;
				for (int i=0;i<4;i++)
				{	
					fread(&tps,2,1,in);
					MSBSwapShort(tps);
					Map_SetPRG_ROM8(i,tps);
				}
				for (int i=0;i<8;i++)
				{	
					fread(&tps,2,1,in);
					MSBSwapShort(tps);
					if (pPPU->Writable[i])
						Map_SetCHR_RAM1(i,tps);
					else
						Map_SetCHR_ROM1(i,tps);
				}
				unsigned char TPMD[0x80];
				fread(&TPMD[0],1,0x80,in);
				if (MapperInfo->LoadMI)
					MapperInfo->LoadMI(TPMD);
			}
		}
	}

	fclose(in);

	pGFX->ShowTextCounter = 40;
	sprintf(pGFX->TextDisp,"State Loaded: %i", SelSlot);
}
