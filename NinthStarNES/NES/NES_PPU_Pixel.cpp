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

#include "NES_PPU_Pixel.h"
#include "..\NinthStar.h"

//#define		VMemory(Addy)		*(CHRPointer[(Addy & 0x1C00) >> 10] + (Addy & 0x03FF))
#define		VMemory(Addy)		*(CHRPointer[(Addy) >> 10] + (Addy & 0x03FF))

const unsigned char CharSC[8] = {
	0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01
};

void cNES_PPU_Pixel::Scanline()
{
	SLnum++;
	Xnum = 0;
	if (SLnum <= 240) {
		if (ControlReg[1] & 0x18)
		{
			IntX = IntXBak;
			VRAMAddr &= ~0x41F;					//scanline start (if background and sprites are enabled):
			VRAMAddr |= IntReg & 0x041F;		//		v:0000010000011111=t:0000010000011111
		}

		if (ControlReg[1] & 0x18)
		{
			char TPV = (VRAMAddr & 0x7000) >> 12;
			TPV++;
			if (TPV == 8)
			{
				TPV = 0;

				short tpa = ((VRAMAddr & 0x03E0)>>5) | ((VRAMAddr & 0x800) >> 6);
				tpa++;
				if ((tpa & 0x1F) == 0x1E) tpa += 2;
				VRAMAddr &= ~0x0BE0;
				VRAMAddr |= (tpa & 0x20) << 6;
				VRAMAddr |= (tpa & 0x1F) << 5;
			}
			VRAMAddr &= 0x8FFF;						//Add one row to IntY
			VRAMAddr |= TPV << 12;
		}
	}
	if (SLnum == 241)
		StatusReg &= 0xBF;		//Clear VBlank Flag + Sprite 0 Hit Flag
	if (SLnum == SLEndFrame)
	{
		StatusReg &= 0x1F;		//Clear VBlank Flag + Sprite 0 Hit Flag
//		StatusReg &= 0xDF;
		SLnum = 0;
		SprAddr = 0;
		IntX = IntXBak;
		if (ControlReg[1] & 0x18)
			VRAMAddr = IntReg;					//		v=t
		
		UpdateSprites();
	}

//	if (TileHandler(4, 0xfd, 0))
	DiscoveredSprites = false;
}

void cNES_PPU_Pixel::DrawPixels(char NumPixels)
{
	short MaxX = Xnum + NumPixels;
//	if (MaxX > 256) MaxX = 256;
	if (MaxX > 264) MaxX = 264;

	if (UpdateSprVector)
		UpdateSprites();

	int i, s;
	unsigned char TSY;
	BYTE midx;
	unsigned char TpTile;
	short PatAddr, PatAddr2;
	char TC;
	BYTE AttribTableVal;
	BYTE Depth = pGFX->Depth;
	unsigned char *pThisPixel;
	bool Spr0SpriteCheck, Spr0BackCheck;

	unsigned long tpit;

	if (pGFX->FPSCnt < pGFX->FSkip)
	{
		for (i=Xnum;i<MaxX;i++)
		{
			Spr0SpriteCheck = false;
			Spr0BackCheck = false;

			if ((ControlReg[1] & 0x10) && ((Xnum >= 8) || (ControlReg[1] & 0x04)))
			{
				for (s=((SprCount-1) << 2);s>=0;s-=4)
				{
					if ((SprBuff[s+2] & 0x20) && (SprBuff[s+3] <= i) && (SprBuff[s+3]+8 > i))
					{
						midx = i-SprBuff[s+3];
						if (SprBuff[s+2] & 0x40)
							midx = 7-midx;		//HFlip
						TSY = SprBuff[s];
						if (SprBuff[s+2] & 0x80)					//VFlip
							if (ControlReg[0] & 0x20)
								TSY = 15 - TSY;
							else
								TSY = 7 - TSY;

						TpTile = SprBuff[s+1];
						PatAddr = 0;
						if (ControlReg[0] & 0x20)
						{
							if (SprBuff[s+1] & 1)
								PatAddr |= 0x1000;
							TpTile &= 0xFE;
						} else {
							PatAddr |= ((ControlReg[0] & 0x08) << 9);
						}
						PatAddr |= ((TpTile + ((TSY & 0x8)>>3)) << 4) + (TSY & 0x07);

						if (!midx)
							if (TileHandler)
								TileHandler((PatAddr & 0x1000) >> 10, TpTile, -1);
						
						if (!(StatusReg & 0x40))
						{
							TC = (VMemory(PatAddr) & CharSC[midx]) >> (7-midx);
							TC |= ((VMemory(PatAddr+8) & CharSC[midx]) >> (7-midx)) << 1;
							if (TC)
								if ((Spr0InLine) && (s == 0))
									Spr0SpriteCheck = true;
						}
					}
				}
			}

			if ((ControlReg[1] & 0x08) && ((Xnum >= 8) || (ControlReg[1] & 0x02)))
			{
				PatAddr = *(CHRPointer[8+((VRAMAddr & 0xC00)>>10)] + (VRAMAddr & 0x3FF));
				PatAddr2 = (PatAddr << 4) | ((VRAMAddr & 0x7000) >> 12) | ((ControlReg[0] & 0x10) << 8);

				if (!IntX)
					if (TileHandler)
						TileHandler((PatAddr2 & 0x1000) >> 10, (unsigned char) PatAddr, VRAMAddr & 0x3FF);

				if (!(StatusReg & 0x40))
				{
					TC = (VMemory(PatAddr2) & CharSC[IntX]) >> (7-IntX);
					TC |= ((VMemory(PatAddr2+8) & CharSC[IntX]) >> (7-IntX)) << 1;
					if (TC)
						Spr0BackCheck = true;
				}
			}

			if ((ControlReg[1] & 0x10) && ((Xnum >= 8) || (ControlReg[1] & 0x04)))
			{
				for (s=((SprCount-1) << 2);s>=0;s-=4)
				{
					if ((!(SprBuff[s+2] & 0x20)) && (SprBuff[s+3] <= i) && (SprBuff[s+3]+8 > i))
					{
						midx = i-SprBuff[s+3];
						if (SprBuff[s+2] & 0x40)
							midx = 7-midx;		//HFlip
						TSY = SprBuff[s];
						if (SprBuff[s+2] & 0x80)					//VFlip
							if (ControlReg[0] & 0x20)
								TSY = 15 - TSY;
							else
								TSY = 7 - TSY;

						TpTile = SprBuff[s+1];
						PatAddr = 0;
						if (ControlReg[0] & 0x20)
						{
							if (SprBuff[s+1] & 1)
								PatAddr |= 0x1000;
							TpTile &= 0xFE;
						} else {
							PatAddr |= ((ControlReg[0] & 0x08) << 9);
						}
						PatAddr |= ((TpTile + ((TSY & 0x8)>>3)) << 4) + (TSY & 0x07);

						if (!midx)
							if (TileHandler)
								TileHandler((PatAddr & 0x1000) >> 10, TpTile, -1);
						
						if (!(StatusReg & 0x40))
						{
							TC = (VMemory(PatAddr) & CharSC[midx]) >> (7-midx);
							TC |= ((VMemory(PatAddr+8) & CharSC[midx]) >> (7-midx)) << 1;
							if (TC)
								if ((Spr0InLine) && (s == 0))
									Spr0SpriteCheck = true;
						}
					}
				}
			}

			if ((Spr0SpriteCheck) && (Spr0BackCheck))
				StatusReg |= 0x40;			//Sprite 0 hit

			Xnum++;

			if (ControlReg[1] & 0x18)
			{
				IntX++;
				if (IntX & 8)
				{
					IntX = 0;
					short tpa = (VRAMAddr & 0x1F) | ((VRAMAddr & 0x400)>>5);
					tpa++;
					VRAMAddr &= ~0x41F;
					VRAMAddr |= (tpa & 0x20) << 5;
					VRAMAddr |= (tpa & 0x1F);
				}
			}
		}
		return;
	}
	
//Possible Optimizations:
//
//Draw front-to-back and don't draw further back if something's already drawn.
//
	int DrawSprites;
	pThisPixel = pGFX->DrawArray + ((SLnum-1)*pGFX->Pitch) + (Xnum*Depth);
	for (i=Xnum;i<MaxX;i++)
	{	
		if (Xnum < 256)
		{
			if (pGFX->Depth == 2)
				*((unsigned short *) pThisPixel) = (unsigned short) FixedPalette[Palette[0][0] | EmphVal];
			else
				*((unsigned long *) pThisPixel) = FixedPalette[Palette[0][0] | EmphVal];
		} else {
			pThisPixel = (unsigned char *) &tpit;
		}
		
		Spr0SpriteCheck = false;
		Spr0BackCheck = false;

		DrawSprites = (Xnum >= 8) | (ControlReg[1] & 0x4);
		if (!(ControlReg[1] & 0x10)) DrawSprites = 0;

		int pSprite;
		unsigned long tVector;
		if (DrawSprites)
		{
			//pSprite = 0x100;
			tVector = RightSprVector[SLnum];
			_asm {
				mov eax, 0x100		//pSprite
				mov edi, tVector
				NextSpr1:
					sub eax,4
					shl edi,1
					jc Draw1
					test eax,eax
					jnz NextSpr1
					jp EndSpr1
				
				Draw1:
					

				EndSpr1:
			}
			for (s=((SprCount-1) << 2);s>=0;s-=4)
			{
				if ((SprBuff[s+2] & 0x20) && (SprBuff[s+3] <= i) && (SprBuff[s+3]+8 > i))
				{
					midx = i-SprBuff[s+3];
					if (SprBuff[s+2] & 0x40)
						midx = 7-midx;		//HFlip
					TSY = SprBuff[s];
					if (SprBuff[s+2] & 0x80)					//VFlip
						if (ControlReg[0] & 0x20)
							TSY = 15 - TSY;
						else
							TSY = 7 - TSY;

					TpTile = SprBuff[s+1];
					PatAddr = 0;
					if (ControlReg[0] & 0x20)
					{
						if (SprBuff[s+1] & 1)
							PatAddr |= 0x1000;
						TpTile &= 0xFE;
					} else {
						PatAddr |= ((ControlReg[0] & 0x08) << 9);
					}
					PatAddr |= ((TpTile + ((TSY & 0x8)>>3)) << 4) + (TSY & 0x07);

					if (!midx)
						if (TileHandler)
							TileHandler((PatAddr & 0x1000) >> 10, TpTile, -1);
							
					TC = (VMemory(PatAddr) & CharSC[midx]) >> (7-midx);
					TC |= ((VMemory(PatAddr+8) & CharSC[midx]) >> (7-midx)) << 1;
					if (TC)
					{
						TC |= (SprBuff[s + 2] & 0x03) << 2;
						if (pGFX->Depth == 2)
							*((unsigned short *) pThisPixel) = (unsigned short) FixedPalette[Palette[1][TC] | EmphVal];
						else
							*((unsigned long *) pThisPixel) = FixedPalette[Palette[1][TC] | EmphVal];
						if ((Spr0InLine) && (s == 0))
							Spr0SpriteCheck = true;
					}
				}
			}
		}

		if ((ControlReg[1] & 0x08) && ((Xnum >= 8) || (ControlReg[1] & 0x02)))
		{
			PatAddr = *(CHRPointer[8+((VRAMAddr & 0xC00)>>10)] + (VRAMAddr & 0x3FF));
			PatAddr2 = (PatAddr << 4) | ((VRAMAddr & 0x7000) >> 12) | ((ControlReg[0] & 0x10) << 8);

			AttribTableVal = (*(CHRPointer[8+((VRAMAddr & 0xC00)>>10)] + (0x3C0 | ((VRAMAddr & 0x1C) >> 2) | ((VRAMAddr & 0x380) >> 4))) >> ((((VRAMAddr & 2) >> 1) | ((VRAMAddr & 0x40) >> 5)) << 1)) & 3;

			if (!IntX)
				if (TileHandler)
					TileHandler((PatAddr2 & 0x1000) >> 10, (unsigned char) PatAddr, VRAMAddr & 0x3FF);

			TC = (VMemory(PatAddr2) & CharSC[IntX]) >> (7-IntX);
			TC |= ((VMemory(PatAddr2+8) & CharSC[IntX]) >> (7-IntX)) << 1;
			if (TC)
			{
				TC |= AttribTableVal << 2;
				if (pGFX->Depth == 2)
					*((unsigned short *) pThisPixel) = (unsigned short) FixedPalette[Palette[0][TC] | EmphVal];
				else
					*((unsigned long *) pThisPixel) = FixedPalette[Palette[0][TC] | EmphVal];
				Spr0BackCheck = true;
			}
		}

		if ((ControlReg[1] & 0x10) && ((Xnum >= 8) || (ControlReg[1] & 0x04)))
		{
			for (s=((SprCount-1) << 2);s>=0;s-=4)
			{
				if ((!(SprBuff[s+2] & 0x20)) && (SprBuff[s+3] <= i) && (SprBuff[s+3]+8 > i))
				{
					midx = i-SprBuff[s+3];
					if (SprBuff[s+2] & 0x40)
						midx = 7-midx;		//HFlip
					TSY = SprBuff[s];
					if (SprBuff[s+2] & 0x80)					//VFlip
						if (ControlReg[0] & 0x20)
							TSY = 15 - TSY;
						else
							TSY = 7 - TSY;

					TpTile = SprBuff[s+1];
					PatAddr = 0;
					if (ControlReg[0] & 0x20)
					{
						if (SprBuff[s+1] & 1)
							PatAddr |= 0x1000;
						TpTile &= 0xFE;
					} else {
						PatAddr |= ((ControlReg[0] & 0x08) << 9);
					}
					PatAddr |= ((TpTile + ((TSY & 0x8)>>3)) << 4) + (TSY & 0x07);

					if (!midx)
						if (TileHandler)
							TileHandler((PatAddr & 0x1000) >> 10, TpTile, -1);
					
					TC = (VMemory(PatAddr) & CharSC[midx]) >> (7-midx);
					TC |= ((VMemory(PatAddr+8) & CharSC[midx]) >> (7-midx)) << 1;
					if (TC)
					{
						TC |= (SprBuff[s + 2] & 0x03) << 2;
						if (pGFX->Depth == 2)
							*((unsigned short *) pThisPixel) = (unsigned short) FixedPalette[Palette[1][TC] | EmphVal];
						else
							*((unsigned long *) pThisPixel) = FixedPalette[Palette[1][TC] | EmphVal];
						if ((Spr0InLine) && (s == 0))
							Spr0SpriteCheck = true;
					}
				}
			}
		}

		if ((Spr0SpriteCheck) && (Spr0BackCheck))
			StatusReg |= 0x40;			//Sprite 0 hit

		pThisPixel += Depth;

		Xnum++;
		if (ControlReg[1] & 0x18)
		{
			IntX++;
			if (IntX & 8)
			{
				IntX = 0;
				short tpa = (VRAMAddr & 0x1F) | ((VRAMAddr & 0x400)>>5);
				tpa++;
				VRAMAddr &= ~0x41F;
				VRAMAddr |= (tpa & 0x20) << 5;
				VRAMAddr |= (tpa & 0x1F);
			}
		}
	}
}

void cNES_PPU_Pixel::FrameDone()
{
	StatusReg |= 0x80;
	
	pGFX->DrawScreen();
}