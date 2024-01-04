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

#ifndef cNESH
#define cNESH

#include <assert.h>

#include <commdlg.h>

#include "NES/2A03.h"
#include "NES/NES_PPU.h"
#include "NES/NES_PPU_Pixel.h"
#include "NES/NES_PPU_Scanline.h"
#include "NES/NES_PPU_Tile.h"
#include "NES/NES_GFX.h"
#include "NES/NES_Debugger.h"
#include "NES/NES_States.h"
#include "NES/NES_MapperInterface.h"
#include "NES/NES_Handlers.h"

#include "EmuBase.h"

#include "Resource.h"

class cNES : public cEmuBase {
	public :
		cNES();
		
		void SaveSettings()
		{
			HKEY SettingsBase;
			if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\NinthStar\\NES\\", 0, KEY_ALL_ACCESS, &SettingsBase) > 0)
				RegCreateKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\NinthStar\\NES\\", 0, "NinthStarClass", REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &SettingsBase, NULL);

			RegSetValueEx(SettingsBase, "SoundEnabled", 0, REG_DWORD, (unsigned char *) &SoundEnabled, 4);
			RegSetValueEx(SettingsBase, "DoubleSize", 0, REG_DWORD, (unsigned char *) &DoubleSize, 4);
			RegSetValueEx(SettingsBase, "aFSkip", 0, REG_DWORD, (unsigned char *) &GFX->aFSkip, 4);
			RegSetValueEx(SettingsBase, "Mode3D", 0, REG_DWORD, (unsigned char *) &GFX->Mode3D, 4);
			RegSetValueEx(SettingsBase, "PPUMode", 0, REG_DWORD, (unsigned char *) &PPUMode, 4);
			RegSetValueEx(SettingsBase, "CPUMode", 0, REG_DWORD, (unsigned char *) &CPUMode, 4);
			RegSetValueEx(SettingsBase, "Keys", 0, REG_BINARY, (unsigned char *) &Controllers->Buttons[0][0], sizeof(Controllers->Buttons));
			RegCloseKey(SettingsBase);
		}

		void LoadSettings();

		void Release()
		{
			SaveSettings();

			(GetProcAddress(MapperDllInst,"Unload_DLL"))();
			FreeLibrary(MapperDllInst);

			delete Controllers;
			delete GFX;
			delete CPU;
			delete PPU;
			delete Sprite;
			delete Debugger;
			delete States;
	
			delete this;
		}

		void OpenFile(char *toopen);
		bool OpenFileiNES(char *toopen);
		bool OpenFileUNIF(char *toopen);
		void Run();
		void PowerOn();
		void Reset();

		void UpdateInterface();

		void RePaint()
		{	GFX->RePaint(); }

		void IRQ()
		{	CPU->IRQ(); }

		void SetCPUMode(int NewMode)
		{
			double CPUClock = 21442080;//21477272.727272727272;
			if (NewMode == 0)	//NTSC
			{
				PPU->SLEndFrame = 262;
				GFX->WantFPS = 60;
				GFX->LoadPalette(0);
				CPU->APU->WantFPS = 60;
			} else {		//PAL
				PPU->SLEndFrame = 312;
				GFX->WantFPS = 50;
				GFX->LoadPalette(1);
				CPU->APU->WantFPS = 50;
			}
			TicksPerLine = (int) (CPUClock/GFX->WantFPS)/PPU->SLEndFrame;
		}

		void EmuMsg(DWORD Message, DWORD Data1, DWORD Data2);

		int ShortSL;

		c2A03 *CPU;
		cNES_PPU *PPU;
		cNES_Sprite *Sprite;
		cNES_GFX *GFX;
		cNES_Debugger *Debugger;
		cNES_States *States;
		cNES_Controllers *Controllers;

		unsigned char RAM[0x800];
		unsigned char SRAM[0x10][0x1000];
		bool SRAMEnabled;
		int	SRAM_Size;
		unsigned char PRG[0x400][0x1000];	//256 4k pages
		unsigned char *PRGPointer[16];
		bool Writable[16];

		int PRGMask, CHRMask;
		
		HINSTANCE MapperDllInst;
		TDLL_Info * MapperDllInfo;
		TMapper_Info * MapperInfo;
		TMapperParam MapperParam;

		void LoadMapperDLL(int Num);

		friend int RAMReader(int Bank, int Addy);
		friend void RAMWriter(int Bank, int Addy, int Val);

		friend int PPUReader(int Bank, int Addy);
		friend void PPUWriter(int Bank, int Addy, int Val);

		friend int Regs4kReader(int Bank, int Addy);
		friend void Regs4kWriter(int Bank, int Addy, int Val);

		friend int PRGReader(int Bank, int Addy);
		friend void PRGWriter(int Bank, int Addy, int Val);

		friend void Map_SetWriteHandler(int Page, TWriteFunc New);
		friend void Map_SetReadHandler(int Page, TReadFunc New);
		friend TWriteFunc Map_GetWriteHandler(int Page);
		friend TReadFunc Map_GetReadHandler(int Page);

		friend void	Map_SetPRG_ROM4(int Where, int What);
		friend void	Map_SetPRG_ROM8(int Where, int What);
		friend void	Map_SetPRG_ROM16(int Where, int What);
		friend void	Map_SetPRG_ROM32(int Where, int What);
		friend int		Map_GetPRG_ROM4(int Where);	/* -1 if no ROM mapped */
		friend void	Map_SetPRG_RAM4(int Where, int What);
		friend void	Map_SetPRG_RAM8(int Where, int What);
		friend void	Map_SetPRG_RAM16(int Where, int What);
		friend void	Map_SetPRG_RAM32(int Where, int What);
		friend int		Map_GetPRG_RAM4(int Where);	/* -1 if no RAM mapped */
		friend void *	Map_GetPRG_Ptr4(int Where);

		friend void	Map_SetPRG_OB4(int Where);	/* Open bus */

		friend void	Map_SetCHR_ROM1(int Where, int What);
		friend void	Map_SetCHR_ROM2(int Where, int What);
		friend void	Map_SetCHR_ROM4(int Where, int What);
		friend void	Map_SetCHR_ROM8(int Where, int What);
		friend int		Map_GetCHR_ROM1(int Where);	/* -1 if no ROM mapped */
		friend void	Map_SetCHR_RAM1(int Where, int What);
		friend void	Map_SetCHR_RAM2(int Where, int What);
		friend void	Map_SetCHR_RAM4(int Where, int What);
		friend void	Map_SetCHR_RAM8(int Where, int What);
		friend int		Map_GetCHR_RAM1(int Where);	/* -1 if no RAM mapped */
		friend void *	Map_GetCHR_Ptr1(int Where);

		friend void	Map_Mirror_H();
		friend void	Map_Mirror_V();
		friend void	Map_Mirror_4();
		friend void	Map_Mirror_S0();
		friend void	Map_Mirror_S1();
		friend void	Map_Mirror_Custom(int M1, int M2, int M3, int M4);

		friend void	Map_Set_SRAMSize(int Size);	/* Sets the size of the SRAM (in bytes) and clears PRG_RAM */
		friend void	Map_Save_SRAM();	/* Saves SRAM to disk */
		friend void	Map_Load_SRAM();	/* Loads SRAM from disk */

		friend void	Map_DbgOut(char *ToSay);
		friend void	Map_MMC5_UpdateAttributeCache();

	private :
		void SetPPUMode(int PPUNum);

		int	DoubleSize, SoundEnabled, PPUMode, CPUMode;

		int	TicksPerLine;

		bool SRAMHWEnabled;
		FILE *SRAMFile;
		char SRAMFileName[256];
};

#endif