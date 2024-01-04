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

#ifndef A26_TIA_H
#define A26_TIA_H

#include "A26_GFX.h"
#include "A26_PIA.h"

class cA26_TIA {
	public:
		cA26_TIA()
		{
			VSYNC = 0; VBLANK = 0;
			PF0 = 0; PF1 = 0; PF2 = 0;
			ENABL = 0;
			HMBL = 0; 
			VDELP0 = 0; VDELP1 = 0; VDELBL = 0;
			BPos = 0;
			RESBL = 0; RESM0 = 0; RESM1 = 0; RESP0 = 0; RESP1 = 0;
			
			HMP[0] = 0; HMP[1] = 0;
			GRP[0] = 0; GRP[1] = 0;
			REFP[0] = 0; REFP[1] = 0;
			PPos[0] = 0; PPos[1] = 0;
			NUSIZ[0] = 0; NUSIZ[1] = 0;
			ENAM[0] = 0; ENAM[1] = 0;
			MPos[0] = 0; MPos[1] = 0;
			HMM[0] = 0; HMM[1] = 0;
			COLOUP[0] = 0; COLOUP[1] = 0;
			COLOUPF = 0; COLOUBK = 0;
			RESMP[0] = 0; RESMP[1] = 0;
			VDELP[0] = 0; VDELP[1] = 0;

			CXM0P = 0; CXM1P = 0; CXP0FB = 0; CXP1FB = 0; CXM0FB = 0; CXM1FB = 0; CXBLPF = 0; CXPPMM = 0;
		}
		~cA26_TIA()
		{
		}
	
		void WriteRegister(unsigned char Addy, unsigned char Val);
		unsigned char ReadRegister(unsigned char Addy);
		void Scanline();
		void DrawPlayer(int p);
		void DrawMissile(int m);
		void DrawPlayfield(bool Half, bool Flipped);
		void DrawBackground();
		void DrawBall();

		int *Clockticks, *TicksToCount;
		
		unsigned char *INPT4, *INPT5;

		unsigned char RESBL, RESM0, RESM1, RESP0, RESP1;
		unsigned char VSYNC, VBLANK, PF0, PF1, PF2, CTRLPF;
		unsigned char ENABL;
		unsigned char HMBL, VDELP0, VDELP1, VDELBL, COLOUP[2], COLOUPF, COLOUBK;
		unsigned char REFP[2], PPos[2], MPos[2], GRP[2], NUSIZ[2], ENAM[2], HMP[2], HMM[2], BPos, RESMP[2], VDELP[2];
		unsigned char CXM0P, CXM1P, CXP0FB, CXP1FB, CXM0FB, CXM1FB, CXBLPF, CXPPMM;

		unsigned char	OType[160];

		short SLnum;

		cA26_GFX	*pGFX;
		cA26_PIA	*pPIA;
};

#define		OT_BL		0x01
#define		OT_P0		0x02
#define		OT_P1		0x04
#define		OT_M0		0x08
#define		OT_M1		0x10
#define		OT_PF		0x20

#endif