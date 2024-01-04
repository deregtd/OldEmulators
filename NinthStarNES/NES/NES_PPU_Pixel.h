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

#ifndef NES_PPU_PIXELH
#define NES_PPU_PIXELH

#include "NES_PPU.h"

class cNES_PPU_Pixel : public cNES_PPU {
	public :
		cNES_PPU_Pixel()
		{
			StatusReg = 0;
			ZeroMemory(&CHR,sizeof(CHR));
			ZeroMemory(&CHR_RAM,sizeof(CHR_RAM));
			ZeroMemory(&Palette,sizeof(Palette));
			ZeroMemory(Sprite, 0x100);
			VRAMAddr = 0;
			SLnum = 0;
			IntReg = 0;
			IntX = 0;
			IntXBak = 0;
			EmphVal = 0;
			HVTog = true;
			ppuLatch = 0;
			ppuReadLatch = 0;

			for (int i=0;i<0x2000;i++)
				MType[i] = MT_CHR;
			for (int i=0x2000;i<0x3000;i++)
				MType[i] = MT_NTAB;
			for (int i=0x3000;i<0x3F00;i++)
				MType[i] = MT_NTABM;
			for (int i=0x3F00;i<0x4000;i++)
				MType[i] = MT_PAL;

			for (int i=0;i<12;i++)
				CHRPointer[i] = &CHR[0][0];
		}
		~cNES_PPU_Pixel()
		{
		}

		void DrawPixels(char NumPixels);
		void FrameDone();
		void DiscoverSprites();
		void Scanline();
};

#endif