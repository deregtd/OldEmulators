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

#include "A26_TIA.h"
#include "..\Global.h"

void cA26_TIA::Scanline()
{
	SLnum++;

	ZeroMemory(&OType[0],sizeof(OType));

	if ((SLnum >= 40) && (SLnum < 232))
	{
		DrawBackground();
		if (CTRLPF & 4)
		{
			DrawPlayer(0);
			DrawMissile(0);
			DrawPlayer(1);
			DrawMissile(1);
			DrawPlayfield(0, 0);
			DrawPlayfield(1, CTRLPF & 1);
			DrawBall();
		} else {
			DrawPlayfield(0, 0);
			DrawPlayfield(1, CTRLPF & 1);
			DrawBall();
			DrawPlayer(0);
			DrawMissile(0);
			DrawPlayer(1);
			DrawMissile(1);
		}
	}

	for (int i=0;i<160;i++)
	{
		if (OType[i] & OT_M0)
		{
			if (OType[i] & OT_P0)
				CXM0P |= 0x40;
			if (OType[i] & OT_P1)
				CXM0P |= 0x80;

			if (OType[i] & OT_BL) 
				CXM0FB |= 0x40;
			if (OType[i] & OT_PF) 
				CXM0FB |= 0x80;

			if (OType[i] & OT_M1) 
				CXPPMM |= 0x40;
		}

		if (OType[i] & OT_M1)
		{
			if (OType[i] & OT_P0) 
				CXM1P |= 0x80;
			if (OType[i] & OT_P1) 
				CXM1P |= 0x40;

			if (OType[i] & OT_BL) 
				CXM1FB |= 0x40;
			if (OType[i] & OT_PF) 
				CXM1FB |= 0x80;
		}

		if (OType[i] & OT_P0)
		{
			if (OType[i] & OT_BL) 
				CXP0FB |= 0x40;
			if (OType[i] & OT_PF) 
				CXP0FB |= 0x80;

			if (OType[i] & OT_P1) 
				CXPPMM |= 0x80;
		}

		if (OType[i] & OT_P1)
		{
			if (OType[i] & OT_BL) 
				CXP1FB |= 0x40;
			if (OType[i] & OT_PF) 
				CXP1FB |= 0x80;
		}

		if ((OType[i] & OT_BL) && (OType[i] & OT_PF))
			CXBLPF |= 0x80;
	}
}

void cA26_TIA::DrawBall()
{
	if (!(ENABL & 2))
		return;
	
	if (VDELBL & 1)
	{
		VDELBL &= ~0x01;
		return;
	}

	unsigned char * pThisPixel;
	int IncSize = (pGFX->Mode3D) ? 1 : pGFX->Depth;

	pThisPixel = pGFX->DrawArray + ((SLnum - 40)*pGFX->Pitch) + (BPos*IncSize);

	int BalSize;
	switch (CTRLPF & 0x30)
	{
	case 0x00:	BalSize = 1; break;
	case 0x10:	BalSize = 2; break;
	case 0x20:	BalSize = 4; break;
	case 0x30:	BalSize = 8; break;
	}

	for (int x=0;x<BalSize;x++)
	{
		if (pGFX->Mode3D)
		{
			*pThisPixel = COLOUPF;
		} else {
			if (pGFX->Depth == 2)
				*((unsigned short *) pThisPixel) = (unsigned short) pGFX->FixedPalette[COLOUPF];
			else
				*((unsigned long *) pThisPixel) = pGFX->FixedPalette[COLOUPF];
		}
		OType[BPos+x] |= OT_BL;

		pThisPixel += IncSize;
	}
}

void cA26_TIA::DrawBackground()
{
	unsigned char * pThisPixel = pGFX->DrawArray + ((SLnum - 40)*pGFX->Pitch);
	int IncSize = (pGFX->Mode3D) ? 1 : pGFX->Depth;
	
	for (int i=0;i<160;i++)
	{
		if (pGFX->Mode3D)
		{
			*pThisPixel = COLOUBK;
		} else {
			if (pGFX->Depth == 2)
				*((unsigned short *) pThisPixel) = (unsigned short) pGFX->FixedPalette[COLOUBK];
			else
				*((unsigned long *) pThisPixel) = pGFX->FixedPalette[COLOUBK];
		}

		pThisPixel += IncSize;
	}
}

void cA26_TIA::DrawMissile(int m)
{
	if (!(ENAM[m] & 2))
		return;

	if (RESMP[m] & 2)
		return;

	unsigned char * pThisPixel;
	int IncSize = (pGFX->Mode3D) ? 1 : pGFX->Depth;
	int MisSize;

	pThisPixel = pGFX->DrawArray + ((SLnum - 40)*pGFX->Pitch) + (MPos[m]*IncSize);

	switch (NUSIZ[m] & 0x30)
	{
	case 0x00:	MisSize = 1; break;
	case 0x10:	MisSize = 2; break;
	case 0x20:	MisSize = 4; break;
	case 0x30:	MisSize = 8; break;
	}

	//Gotta fix this up...  Memcopy = gay kthx
	for (int x=0;x<MisSize;x++)
	{
		if (pGFX->Mode3D)
		{
			*pThisPixel = COLOUP[m];
		} else {
			if (pGFX->Depth == 2)
				*((unsigned short *) pThisPixel) = (unsigned short) pGFX->FixedPalette[COLOUP[m]];
			else
				*((unsigned long *) pThisPixel) = pGFX->FixedPalette[COLOUP[m]];
		}

		OType[MPos[m]+x] |= (m) ? OT_M1 : OT_M0;

		pThisPixel += IncSize;
	}
/*
	if (NUSIZ[m] & 7)
	{
		pThisPixel = pGFX->DrawArray + ((SLnum - 40)*pGFX->Pitch) + (MPos[m]*IncSize);
		switch (NUSIZ[m] & 7)
		{
		case 1 :
			memcpy(pThisPixel + IncSize*16, pThisPixel, IncSize*8);
			break;
		case 2 :
			memcpy(pThisPixel + IncSize*32, pThisPixel, IncSize*8);
			break;
		case 3 :
			memcpy(pThisPixel + IncSize*16, pThisPixel, IncSize*8);
			memcpy(pThisPixel + IncSize*32, pThisPixel, IncSize*8);
			break;
		case 4 :
			memcpy(pThisPixel + IncSize*64, pThisPixel, IncSize*8);
			break;
		case 5 :
			memcpy(pThisPixel + IncSize*8, pThisPixel, IncSize*8);
			break;
		case 6 :
			memcpy(pThisPixel + IncSize*32, pThisPixel, IncSize*8);
			memcpy(pThisPixel + IncSize*64, pThisPixel, IncSize*8);
			break;
		case 7 :
			memcpy(pThisPixel + IncSize*8, pThisPixel, IncSize*8);
			memcpy(pThisPixel + IncSize*16, pThisPixel, IncSize*8);
			memcpy(pThisPixel + IncSize*24, pThisPixel, IncSize*8);
			break;
		}
	}*/
}

void cA26_TIA::DrawPlayer(int p)
{
	if (VDELP[p] & 1)
	{
		VDELP[p] &= ~0x01;
		return;
	}

	int TpB;
	unsigned char * pThisPixel;
	int IncSize = (pGFX->Mode3D) ? 1 : pGFX->Depth;
	pThisPixel = pGFX->DrawArray + ((SLnum - 40)*pGFX->Pitch) + (PPos[p]*IncSize);
	if (REFP[p] & 0x8)
	{
		TpB = 0x01;
		for (int i=0;i<8;i++)
		{
			if (pGFX->Mode3D)
			{
				if (GRP[p] & TpB)
					*pThisPixel = COLOUP[p];
			} else if (GRP[p] & TpB) {
				if (pGFX->Depth == 2)
					*((unsigned short *) pThisPixel) = (unsigned short) pGFX->FixedPalette[COLOUP[p]];
				else
					*((unsigned long *) pThisPixel) = pGFX->FixedPalette[COLOUP[p]];
			}
			if (GRP[p] & TpB)
				OType[PPos[p]+i] |= (p) ? OT_P1 : OT_P0;
			pThisPixel += IncSize;
			TpB <<= 1;
		}
	} else {
		TpB = 0x80;
		for (int i=0;i<8;i++)
		{
			if (pGFX->Mode3D)
			{
				if (GRP[p] & TpB)
					*pThisPixel = COLOUP[p];
			} else if (GRP[p] & TpB) {
				if (pGFX->Depth == 2)
					*((unsigned short *) pThisPixel) = (unsigned short) pGFX->FixedPalette[COLOUP[p]];
				else
					*((unsigned long *) pThisPixel) = pGFX->FixedPalette[COLOUP[p]];
			}
			if (GRP[p] & TpB)
				OType[PPos[p]+i] |= (p) ? OT_P1 : OT_P0;
			pThisPixel += IncSize;
			TpB >>= 1;
		}
	}
}

void cA26_TIA::DrawPlayfield(bool Half, bool Flipped)
{
	int TpB;
	unsigned char * pThisPixel;
	int IncSize = (pGFX->Mode3D) ? 1 : pGFX->Depth;
	pThisPixel = pGFX->DrawArray + ((SLnum - 40)*pGFX->Pitch) + (IncSize*80*Half) + (IncSize*79*Flipped);

	unsigned char Col2Draw = (CTRLPF & 2) ? ((Half) ? COLOUP[1] : COLOUP[0]) : COLOUPF;

	if (Flipped) IncSize = -IncSize;
	int OCnt = 80*Half + 79*Flipped, OInc = 1;
	if (Flipped) OInc = -OInc;

	TpB = 0x10;
	for (int i = 4; i < 8; i ++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (pGFX->Mode3D)
			{
				if (PF0 & TpB)
					*pThisPixel = Col2Draw;
			} else if (PF0 & TpB) {
				if (pGFX->Depth == 2)
					*((unsigned short *) pThisPixel) = (unsigned short) pGFX->FixedPalette[Col2Draw];
				else
					*((unsigned long *) pThisPixel) = pGFX->FixedPalette[Col2Draw];
			}
			if (PF0 & TpB)
				OType[OCnt] |= OT_PF;
			OCnt += OInc;
			pThisPixel += IncSize;
		}
		TpB <<= 1;
	}
	TpB = 0x80;
	for (int i = 7; i >= 0; i --)
	{
		for (int x = 0; x < 4; x++)
		{
			if (pGFX->Mode3D)
			{
				if (PF1 & TpB)
					*pThisPixel = Col2Draw;
			} else if (PF1 & TpB) {
				if (pGFX->Depth == 2)
					*((unsigned short *) pThisPixel) = (unsigned short) pGFX->FixedPalette[Col2Draw];
				else
					*((unsigned long *) pThisPixel) = pGFX->FixedPalette[Col2Draw];
			}
			if (PF1 & TpB)
				OType[OCnt] |= OT_PF;
			OCnt += OInc;
			pThisPixel += IncSize;
		}
		TpB >>= 1;
	}
	TpB = 0x01;
	for (int i = 0; i < 8; i ++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (pGFX->Mode3D)
			{
				if (PF2 & TpB)
					*pThisPixel = Col2Draw;
			} else if (PF2 & TpB) {
				if (pGFX->Depth == 2)
					*((unsigned short *) pThisPixel) = (unsigned short) pGFX->FixedPalette[Col2Draw];
				else
					*((unsigned long *) pThisPixel) = pGFX->FixedPalette[Col2Draw];
			}
			if (PF2 & TpB)
				OType[OCnt] |= OT_PF;
			OCnt += OInc;
			pThisPixel += IncSize;
		}
		TpB >>= 1;
	}
}

void cA26_TIA::WriteRegister(unsigned char Addy, unsigned char Val)
{
	switch (Addy)
	{
	case 0x00:		//VSYNC
		if ((VSYNC & 2) && (!(Val & 2)))
			SLnum = 3;
		if ((!(VSYNC & 2)) && (Val & 2))
		{
			SLnum = 0;
			pGFX->DrawScreen();
			pPIA->UpdateInput();
		}
		VSYNC = Val;
		break;
	case 0x01:		//VBLANK
//		if ((VBLANK & 2) && (!(Val & 2)))
//			SLnum = 40;
		if ((!(VBLANK & 2)) && (Val & 2))
			SLnum = 3;

		if (Val & 0x40)
		{ *INPT4 = 0x80; *INPT5 = 0x80; }
		VBLANK = Val;
		break;
	case 0x02:		//WSYNC
		*TicksToCount = 228 - *Clockticks;
		break;
	case 0x03:		//RSYNC
		//Nothing heh...
		break;
	
	case 0x20:		//HMP0
		HMP[0] = Val;
		break;
	case 0x21:		//HMP1
		HMP[1] = Val;
		break;

	case 0x10:		//RESP0
		RESP0 = *Clockticks - 68;
		PPos[0] = RESP0;
		break;

	case 0x11:		//RESP1
		RESP1 = *Clockticks - 68;
		PPos[1] = RESP1;
		break;

	case 0x22:		//HMM0
		HMM[0] = Val;
		break;
	case 0x23:		//HMM1
		HMM[1] = Val;
		break;

	case 0x12:		//RESM0
		RESM0 = *Clockticks - 68;
		MPos[0] = RESM0;
		break;
	case 0x13:		//RESM1
		RESM1 = *Clockticks - 68;
		MPos[1] = RESM1;
		break;

	case 0x24:		//HMBL
		HMBL = Val;
		break;
	case 0x14:		//RESBL
		RESBL = *Clockticks - 68;
		BPos = RESBL;
		break;

	case 0x2A:		//HMOVE
		BPos    = RESBL - ((HMBL   & 0x70) >> 4) + ((HMBL   & 0x80) ? 8 : 0);
		MPos[0] = RESM0 - ((HMM[0] & 0x70) >> 4) + ((HMM[0] & 0x80) ? 8 : 0);
		MPos[1] = RESM1 - ((HMM[1] & 0x70) >> 4) + ((HMM[1] & 0x80) ? 8 : 0);
		PPos[0] = RESP0 - ((HMP[0] & 0x70) >> 4) + ((HMP[0] & 0x80) ? 8 : 0);
		PPos[1] = RESP1 - ((HMP[1] & 0x70) >> 4) + ((HMP[1] & 0x80) ? 8 : 0);
		break;

	case 0x2B:		//HMCLR:
		HMM[0] = 0; HMM[1] = 0; HMBL = 0; HMP[0] = 0; HMP[1] = 0;

		BPos = RESBL;
		MPos[0] = RESM0;
		MPos[1] = RESM1;
		PPos[0] = RESP0;
		PPos[1] = RESP1;
		break;

	case 0x28:		//RESMP0
		RESMP[0] = Val;
		HMM[0] = 0;
		RESM0 = RESP0;
		break;
	case 0x29:		//RESMP1
		RESMP[1] = Val;
		HMM[1] = 0;
		RESM1 = RESP1;
		break;
	
	case 0x2C:		//CXCLR
		CXM0P = 0; CXM1P = 0; CXP0FB = 0; CXP1FB = 0; CXM0FB = 0; CXM1FB = 0; CXBLPF = 0; CXPPMM = 0;
		break;

	case 0x04:		NUSIZ[0] = Val; break;
	case 0x05:		NUSIZ[1] = Val; break;
	case 0x06:		COLOUP[0] = Val; break;
	case 0x07:		COLOUP[1] = Val; break;
	case 0x08:		COLOUPF = Val; break;
	case 0x09:		COLOUBK = Val; break;
	case 0x0A:		CTRLPF = Val; break;
	case 0x0B:		REFP[0] = Val; break;
	case 0x0C:		REFP[1] = Val; break;
	case 0x0D:		PF0 = Val; break;
	case 0x0E:		PF1 = Val; break;
	case 0x0F:		PF2 = Val; break;
	case 0x1B:		GRP[0] = Val; break;
	case 0x1C:		GRP[1] = Val; break;
	case 0x1D:		ENAM[0] = Val; break;
	case 0x1E:		ENAM[1] = Val; break;
	case 0x1F:		ENABL = Val; break;
	case 0x25:		VDELP[0] = Val; break;
	case 0x26:		VDELP[1] = Val; break;
	case 0x27:		VDELBL = Val; break;
	}
}

unsigned char cA26_TIA::ReadRegister(unsigned char Addy)
{
	switch (Addy)
	{
	case 0x00:		return(CXM0P);
	case 0x01:		return(CXM1P);
	case 0x02:		return(CXP0FB);
	case 0x03:		return(CXP1FB);
	case 0x04:		return(CXM0FB);
	case 0x05:		return(CXM1FB);
	case 0x06:		return(CXBLPF);
	case 0x07:		return(CXPPMM);
	
	//Input Regs after this...

	default :
		return(0);
	}
}

