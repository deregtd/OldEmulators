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

#ifndef STATES_H
#define STATES_H

#include "2A03.h"
#include "NES_PPU.h"
#include "NES_Controllers.h"
#include "NES_GFX.h"
#include "NES_Handlers.h"
//#include "NES_MapperInterface.h"

class cNES_States {
	public :
		cNES_States();
		void SetSlot(int Slot);
		void SaveState();
		void LoadState();
		char FileNameBase[80];
		
		c2A03 *pCPU;
		cNES_PPU *pPPU;
		cNES_GFX *pGFX;
		cNES_Controllers *pControllers;

		bool NeedSave, NeedLoad;
		bool SRAMHWEnabled;
		int	*SRAM_Size;
		unsigned char *SRAM;
		TMapperInfo *MapperInfo;
		int CHRBlocks, MapperNum;

		int SelSlot;
};

#endif