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

#include "NES_PPU_Scanline.h"
#include "..\NinthStar.h"

#define		VMemory(Addy)		*(CHRPointer[(Addy & 0x1C00) >> 10] + (Addy & 0x03FF))

const unsigned char CharSC[8] = {
	0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01
};

void cNES_PPU_Scanline::Scanline()
{
	//DRAW SCANLINE HERE!!
	//DRAW SCANLINE HERE!!
	//DRAW SCANLINE HERE!!
	//DRAW SCANLINE HERE!!
	//DRAW SCANLINE HERE!!
	//DRAW SCANLINE HERE!!
	//DRAW SCANLINE HERE!!
	//DRAW SCANLINE HERE!!
	//DRAW SCANLINE HERE!!
	//DRAW SCANLINE HERE!!

	SLnum++;
	if (SLnum < 240) {
		if (ControlReg[1] & 0x18)
		{
//<Hax0r>
			IntX = IntXBak;
//</Hax0r>
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
	if (SLnum == SLEndFrame)
	{
		StatusReg &= 0x1F;		//Clear VBlank Flag + Sprite 0 Hit Flag
		SLnum = 0;
		Sprite->SprAddr = 0;
//<Hax0r>
//		IntX &= 0xFF;
		IntX = IntXBak;
//</Hax0r>
		if (ControlReg[1] & 0x18)
			VRAMAddr = IntReg;					//		v=t
	} else if (SLnum == 240)
		StatusReg &= 0xBF;		//Clear VBlank Flag + Sprite 0 Hit Flag


	DiscoveredSprites = false;
}

void cNES_PPU_Scanline::FrameDone()
{
	StatusReg |= 0x80;
	
	pGFX->DrawScreen();
}
