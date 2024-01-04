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

#ifndef NES_PPUH
#define NES_PPUH

#include "NES_GFX.h"
#include "NES_MapperInterface.h"
#include "2A03.h"

#define		MT_CHR		1
#define		MT_NTAB		2
#define		MT_NTABM	3
#define		MT_PAL		4

class cNES_Sprite {
	public:
		cNES_Sprite() {
		}
};

class cNES_PPU {
	public :
		cNES_PPU()
		{
		}
		~cNES_PPU()
		{
		}

		void MemSet(unsigned short Addy, unsigned char Val)
		{
			Addy &= 0x3FFF;

			switch (MType[Addy])
			{
				case MT_CHR :
					if (Val != *(CHRPointer[(Addy & 0x3C00) >> 10] + (Addy & 0x3ff))) PatChanged = true;
					*(CHRPointer[(Addy & 0x3C00) >> 10] + (Addy & 0x3ff)) = Val;
					break;
				case MT_NTAB :
					if (Val != *(CHRPointer[(Addy & 0x3C00) >> 10] + (Addy & 0x3ff))) NTabChanged = true;
					*(CHRPointer[(Addy & 0x3C00) >> 10] + (Addy & 0x3ff)) = Val;
					break;
				case MT_NTABM :
					if (Val != *(CHRPointer[((Addy & 0x3C00) >> 10) - 4] + (Addy & 0x3ff))) NTabChanged = true;
					*(CHRPointer[((Addy & 0x3C00) >> 10) - 4] + (Addy & 0x3ff)) = Val;
					break;
				case MT_PAL :
					Val &= 0x3F;
					if ((Addy & 0x3) == 0)
					{
						if (Val != Palette[0][Addy & 0x0F]) { PalChanged = true; PatChanged = true; NTabChanged = true; }
						Palette[0][Addy & 0x0F] = Val;
						Palette[1][Addy & 0x0F] = Val;
					} else {
						if (Val != Palette[(Addy & 0x0010) >> 4][Addy & 0x000F])  { PalChanged = true; PatChanged = true; NTabChanged = true; }
						Palette[(Addy & 0x0010) >> 4][Addy & 0x000F] = Val;
					}
					break;
				default :
//					MessageBox(NULL,"Invalid PPU Mem Type - Write", "0wn3d", MB_OK);
					break;
			};
		}

		unsigned char MemGet(unsigned short Addy)
		{
			switch (MType[Addy & 0x3FFF])
			{
				case MT_CHR :
					return(*(CHRPointer[(Addy & 0x3C00) >> 10] + (Addy & 0x3ff)));
				case MT_NTAB :
					return(*(CHRPointer[(Addy & 0x3C00) >> 10] + (Addy & 0x3ff)));
				case MT_NTABM :
					return(*(CHRPointer[((Addy & 0x3C00) >> 10) - 4] + (Addy & 0x3ff)));
				case MT_PAL :
					return(*(CHRPointer[((Addy & 0x3C00) >> 10) - 4] + (Addy & 0x3ff)));
				default :
//					MessageBox(NULL,"Invalid PPU Mem Type - Read", "0wn3d", MB_OK);
					return(0);
			};
		}

		virtual void DrawPixels(char NumPixels) { }
		virtual void FrameDone() { }
		virtual void Scanline() { }

		void UpdateSprites()
		{
			if (!UpdateSprVector)
				return;

			UpdateSprVector = 0;

			ZeroMemory(LeftSprVector, sizeof(LeftSprVector));
			ZeroMemory(RightSprVector, sizeof(RightSprVector));
			ZeroMemory(LeftSprPriVector, sizeof(LeftSprPriVector));
			ZeroMemory(RightSprPriVector, sizeof(RightSprPriVector));
			ZeroMemory(SpriteCnt, sizeof(SpriteCnt));

			unsigned long tpv = 1;
			for (int i=0;i<128;i+=4)
			{
				LeftSprVector[Sprite[i]] |= tpv;
				LeftSprVector[Sprite[i]+1] |= tpv;
				LeftSprVector[Sprite[i]+2] |= tpv;
				LeftSprVector[Sprite[i]+3] |= tpv;
				LeftSprVector[Sprite[i]+4] |= tpv;
				LeftSprVector[Sprite[i]+5] |= tpv;
				LeftSprVector[Sprite[i]+6] |= tpv;
				LeftSprVector[Sprite[i]+7] |= tpv;
				if (Sprite[i+2] & 0x20)
				{
					LeftSprPriVector[Sprite[i]] |= tpv;
					LeftSprPriVector[Sprite[i]+1] |= tpv;
					LeftSprPriVector[Sprite[i]+2] |= tpv;
					LeftSprPriVector[Sprite[i]+3] |= tpv;
					LeftSprPriVector[Sprite[i]+4] |= tpv;
					LeftSprPriVector[Sprite[i]+5] |= tpv;
					LeftSprPriVector[Sprite[i]+6] |= tpv;
					LeftSprPriVector[Sprite[i]+7] |= tpv;
				}
				SpriteCnt[Sprite[i]]++;
				SpriteCnt[Sprite[i]+1]++;
				SpriteCnt[Sprite[i]+2]++;
				SpriteCnt[Sprite[i]+3]++;
				SpriteCnt[Sprite[i]+4]++;
				SpriteCnt[Sprite[i]+5]++;
				SpriteCnt[Sprite[i]+6]++;
				SpriteCnt[Sprite[i]+7]++;
				
				tpv <<= 1;
			}
			tpv = 1;
			
			for (int i=128;i<256;i+=4)
			{
				RightSprVector[Sprite[i]] |= tpv;
				RightSprVector[Sprite[i]+1] |= tpv;
				RightSprVector[Sprite[i]+2] |= tpv;
				RightSprVector[Sprite[i]+3] |= tpv;
				RightSprVector[Sprite[i]+4] |= tpv;
				RightSprVector[Sprite[i]+5] |= tpv;
				RightSprVector[Sprite[i]+6] |= tpv;
				RightSprVector[Sprite[i]+7] |= tpv;
				if (Sprite[i+2] & 0x20)
				{
					RightSprPriVector[Sprite[i]] |= tpv;
					RightSprPriVector[Sprite[i]+1] |= tpv;
					RightSprPriVector[Sprite[i]+2] |= tpv;
					RightSprPriVector[Sprite[i]+3] |= tpv;
					RightSprPriVector[Sprite[i]+4] |= tpv;
					RightSprPriVector[Sprite[i]+5] |= tpv;
					RightSprPriVector[Sprite[i]+6] |= tpv;
					RightSprPriVector[Sprite[i]+7] |= tpv;
				}
				SpriteCnt[Sprite[i]]++;
				SpriteCnt[Sprite[i]+1]++;
				SpriteCnt[Sprite[i]+2]++;
				SpriteCnt[Sprite[i]+3]++;
				SpriteCnt[Sprite[i]+4]++;
				SpriteCnt[Sprite[i]+5]++;
				SpriteCnt[Sprite[i]+6]++;
				SpriteCnt[Sprite[i]+7]++;

				tpv <<= 1;
			}
		}
		
		TTileHandler	TileHandler;

		cNES_GFX *pGFX;
		unsigned char Sprite[0x100];
		unsigned char SprAddr;

		char MType[0x4000];

		unsigned long FixedPalette[512];

		unsigned long LeftSprVector[240], RightSprVector[240];
		unsigned long LeftSprPriVector[240], RightSprPriVector[240];
		unsigned char SpriteCnt[240];
		int UpdateSprVector;

		unsigned char CHR[0x400][0x400];
		unsigned char CHR_RAM[0x20][0x400];
		bool			Writable[12];
		unsigned char * CHRPointer[12];

		unsigned char Palette[2][0x10];
	
		unsigned char ppuLatch, ppuReadLatch;
		
		unsigned char ControlReg[2];
		unsigned char StatusReg;
		bool HVTog;			//2005/2006 Toggle

		unsigned short VRAMAddr, IntReg;
		unsigned char			 IntX, IntXBak;

		int EmphVal;

		short SLnum;
		short Xnum;

		bool DiscoveredSprites;

		bool NTabChanged, PalChanged, PatChanged;

		int SLEndFrame;

		unsigned char SprBuff[32];
		bool Spr0InLine;
		char SprCount;
};

#endif