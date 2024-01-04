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

#include "2A03.h"
#include <stdio.h>
#include "..\Global.h"

#define		MemGet(Addy)		ReadHandler[(Addy) >> 12]((Addy) >> 12, (Addy) & 0xfff)
#define		MemSet(Addy, Val)	WriteHandler[(Addy) >> 12]((Addy) >> 12, (Addy) & 0xfff, Val)

#define		Push(Byte)			{ MemSet(0x100 | SP, Byte); SP--; }
#define		Pull(Var)			{ SP++; Var = MemGet(0x100 | SP); }
#define		PullPC()			{ SP++; PC = MemGet(0x100 | SP); SP++; PC |= MemGet(0x100 | SP) << 8; }

#define		Check(Byte)			{ if (Byte & 0x80) SetN(); else ClrN(); if (Byte == 0) SetZ(); else ClrZ(); }

#define		FLAG_N				0x80
#define		FLAG_V				0x40
#define		FLAG_B				0x10
#define		FLAG_I				0x04
#define		FLAG_D				0x08
#define		FLAG_Z				0x02
#define		FLAG_C				0x01

#define		SetN()				P |= FLAG_N
#define		SetV()				P |= FLAG_V
#define		SetB()				P |= FLAG_B
#define		SetD()				P |= FLAG_D
#define		SetI()				P |= FLAG_I
#define		SetZ()				P |= FLAG_Z
#define		SetC()				P |= FLAG_C

#define		ClrN()				P &= ~FLAG_N
#define		ClrV()				P &= ~FLAG_V
#define		ClrB()				P &= ~FLAG_B
#define		ClrD()				P &= ~FLAG_D
#define		ClrI()				P &= ~FLAG_I
#define		ClrZ()				P &= ~FLAG_Z
#define		ClrC()				P &= ~FLAG_C

#define		BRANCHIF(A)			\
		TSB = (char) MemGet(PC + 1); \
		\
		if (A) { \
			TPPC = CPU->PC & 0xFF00; \
			PC += 2; \
			if ((CPU->PC & 0xFF00) != TPPC) \
				CPU->Clockticks += 1*12; \
			PC += TSB; \
			Clockticks += 1*12; \
		} else PC += 2; \
		\
		Clockticks += 24;


int TPPC;
unsigned short int TU;		//To Use - Address Holder Variable
unsigned char TB, TV;		//Temp Byte - 8-bit Holder Variable
char TSB;					//Temp Signed Byte - For Relative Jumps
short TS;				//Temp Short - 16-bit Holder Variables for Compare Insts

c2A03 *CPU;

c2A03::c2A03()
{
	CPU = this;
	
	APU = new cNES_APU(gData->MainWnd);
}

void c2A03::Reset()
{
	PC = (MemGet(0xFFFD)<<8) | MemGet(0xFFFC);		//Jump to Reset Vector at $FFFC
	P = 0x20;		//??
	SetI();
	SetD();											//Set Decimal Mode

	Clockticks += (7*12);
}

void c2A03::IRQ()
{
	if (P & FLAG_I) return;	//If Interrupt Disable Flag On, Don't NMI
	
	ClrB();					//Clear Break Flag (?)

	Push((PC >> 8));		//Push Program Counter
	Push((PC & 0xFF));		//	Hi/Low
	Push(P);				//Push Processor Flags

	Clockticks += (7*12);
	PC = (MemGet(0xFFFF)<<8) | MemGet(0xFFFE);		//Jump to IRQ Vector at $FFFE
}

void c2A03::NMI()
{
	ClrB();					//Clear Break Flag (?)

	Push((PC >> 8));		//Push Program Counter
	Push((PC & 0xFF));		//	Hi/Low
	Push(P);				//Push Processor Flags

//	SetI();					//Set Interrupt Flag

	Clockticks += (7*12);
	PC = (MemGet(0xFFFB)<<8) | MemGet(0xFFFA);		//Jump to NMI Vector at $FFFA
}

void c2A03::ExecOp()
{
	switch (MemGet(PC))
	{
	case 0x0:
		*((unsigned short *) &RAM[(SP -= 2) + 0x100 + 1]) = PC + 2;
		SetB();					//Set Break Flag
		Push(P);				//Push Processor Flags
		SetI();					//Set Interrupt Flag
		PC = (MemGet(0xFFFF) << 8) | MemGet(0xFFFE);
		Clockticks += 84;
		break;
	case 0x1:
		TB = MemGet(PC + 1) + X;
		TU = (MemGet(TB + 1) << 8) | MemGet(TB);

		PC += 2;
    
		A |= MemGet(TU);
		Check(A);
		Clockticks += 72;
		break;
	case 0x2:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0x3:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0x4:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0x5:
		TU = MemGet(PC + 1);

		PC += 2;
    
		A |= MemGet(TU);
		Check(A);
		Clockticks += 36;
		break;
	case 0x6:
		TU = MemGet(PC + 1);

		PC += 2;
		TV = MemGet(TU);
    
		MemSet(TU, TV);
		if (TV & 0x80) SetC(); else ClrC();
		TV <<= 1;
		Check(TV);
		MemSet(TU, TV);
		Clockticks += 60;
		break;
	case 0x7:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0x8:
		PC ++;
		Push(P | FLAG_B);
		Clockticks += 36;
		break;
	case 0x9:
		TU = PC + 1;

		PC += 2;
    
		A |= MemGet(TU);
		Check(A);
		Clockticks += 24;
		break;
	case 0xA:
		PC ++;
		if (A & 0x80) SetC(); else ClrC();
		A <<= 1;
		Check(A);
		Clockticks += 24;
		break;
	case 0xB:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0xC:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0xD:
		TU = (MemGet(PC + 2) << 8) | MemGet(PC + 1);

		PC += 3;
    
		A |= MemGet(TU);
		Check(A);
		Clockticks += 48;
		break;
	case 0xE:
		TU = (MemGet(PC + 2) << 8) | MemGet(PC + 1);

		PC += 3;
		TV = MemGet(TU);
    
		MemSet(TU, TV);
		if (TV & 0x80) SetC(); else ClrC();
		TV <<= 1;
		Check(TV);
		MemSet(TU, TV);
		Clockticks += 72;
		break;
	case 0xF:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0x10:
		BRANCHIF(!(P & FLAG_N));
		break;
	case 0x11:
		TB = MemGet(PC + 1);
		TU = ((MemGet(TB + 1) << 8) | MemGet(TB)) + Y;

		PC += 2;
    
		A |= MemGet(TU);
		Check(A);
		Clockticks += 60;
		break;
	case 0x12:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0x13:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0x14:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0x15:
		TU = (MemGet(PC + 1) + X) & 0xFF;

		PC += 2;
    
		A |= MemGet(TU);
		Check(A);
		Clockticks += 48;
		break;
	case 0x16:
		TU = (MemGet(PC + 1) + X) & 0xFF;

		PC += 2;
		TV = MemGet(TU);
    
		MemSet(TU, TV);
		if (TV & 0x80) SetC(); else ClrC();
		TV <<= 1;
		Check(TV);
		MemSet(TU, TV);
		Clockticks += 72;
		break;
	case 0x17:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0x18:
		PC ++;
		ClrC();
		Clockticks += 24;
		break;
	case 0x19:
		TU = ((MemGet(PC + 2) << 8) | MemGet(PC + 1)) + Y;

		PC += 3;
    
		A |= MemGet(TU);
		Check(A);
		Clockticks += 48;
		break;
	case 0x1A:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0x1B:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0x1C:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0x1D:
		TU = ((MemGet(PC + 2) << 8) | MemGet(PC + 1)) + X;

		PC += 3;
    
		A |= MemGet(TU);
		Check(A);
		Clockticks += 48;
		break;
	case 0x1E:
		TU = ((MemGet(PC + 2) << 8) | MemGet(PC + 1)) + X;

		PC += 3;
		TV = MemGet(TU);
    
		MemSet(TU, TV);
		if (TV & 0x80) SetC(); else ClrC();
		TV <<= 1;
		Check(TV);
		MemSet(TU, TV);
		Clockticks += 84;
		break;
	case 0x1F:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0x20:
		*((unsigned short *) &RAM[(SP -= 2) + 0x100 + 1]) = PC + 2;

		PC = (MemGet(PC + 2) << 8) | MemGet(PC + 1);

		Clockticks += 72;
		break;
	case 0x21:
		TB = MemGet(PC + 1) + X;
		TU = (MemGet(TB + 1) << 8) | MemGet(TB);

		PC += 2;
    
		A &= MemGet(TU);
		Check(A);
		Clockticks += 72;
		break;
	case 0x22:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0x23:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0x24:
		TU = MemGet(PC + 1);

		PC += 2;
		TV = MemGet(TU);
    
		if (TV & 0x40) SetV(); else ClrV();
		if (TV & 0x80) SetN(); else ClrN();
		TV &= A;
		if (TV) ClrZ(); else SetZ();
		Clockticks += 36;
		break;
	case 0x25:
		TU = MemGet(PC + 1);

		PC += 2;
    
		A &= MemGet(TU);
		Check(A);
		Clockticks += 36;
		break;
	case 0x26:
		TU = MemGet(PC + 1);

		PC += 2;
		TV = MemGet(TU);
    
		//used to be TSB
		MemSet(TU, TV);
		TB = P & FLAG_C;
		if (TV & 0x80) SetC(); else ClrC();
		TV = (TV << 1) | TB;
		Check(TV);
		MemSet(TU, TV);
		Clockticks += 60;
		break;
	case 0x27:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0x28:
		PC ++;
		Pull(P);
		Clockticks += 48;
		break;
	case 0x29:
		TU = PC + 1;

		PC += 2;
    
		A &= MemGet(TU);
		Check(A);
		Clockticks += 24;
		break;
	case 0x2A:
		PC ++;
		TB = P & FLAG_C;
		if (A & 0x80) SetC(); else ClrC();
		A = (A << 1) | TB;
		Check(A);
		Clockticks += 24;
		break;
	case 0x2B:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0x2C:
		TU = (MemGet(PC + 2) << 8) | MemGet(PC + 1);

		PC += 3;
		TV = MemGet(TU);
    
		if (TV & 0x40) SetV(); else ClrV();
		if (TV & 0x80) SetN(); else ClrN();
		TV &= A;
		if (TV) ClrZ(); else SetZ();
		Clockticks += 48;
		break;
	case 0x2D:
		TU = (MemGet(PC + 2) << 8) | MemGet(PC + 1);

		PC += 3;
    
		A &= MemGet(TU);
		Check(A);
		Clockticks += 48;
		break;
	case 0x2E:
		TU = (MemGet(PC + 2) << 8) | MemGet(PC + 1);

		PC += 3;
		TV = MemGet(TU);
    
		//used to be TSB
		MemSet(TU, TV);
		TB = P & FLAG_C;
		if (TV & 0x80) SetC(); else ClrC();
		TV = (TV << 1) | TB;
		Check(TV);
		MemSet(TU, TV);
		Clockticks += 72;
		break;
	case 0x2F:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0x30:
		BRANCHIF(P & FLAG_N);
		break;
	case 0x31:
		TB = MemGet(PC + 1);
		TU = ((MemGet(TB + 1) << 8) | MemGet(TB)) + Y;

		PC += 2;
    
		A &= MemGet(TU);
		Check(A);
		Clockticks += 60;
		break;
	case 0x32:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0x33:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0x34:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0x35:
		TU = (MemGet(PC + 1) + X) & 0xFF;

		PC += 2;
    
		A &= MemGet(TU);
		Check(A);
		Clockticks += 48;
		break;
	case 0x36:
		TU = (MemGet(PC + 1) + X) & 0xFF;

		PC += 2;
		TV = MemGet(TU);
    
		//used to be TSB
		MemSet(TU, TV);
		TB = P & FLAG_C;
		if (TV & 0x80) SetC(); else ClrC();
		TV = (TV << 1) | TB;
		Check(TV);
		MemSet(TU, TV);
		Clockticks += 72;
		break;
	case 0x37:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0x38:
		PC ++;
		SetC();
		Clockticks += 24;
		break;
	case 0x39:
		TU = ((MemGet(PC + 2) << 8) | MemGet(PC + 1)) + Y;

		PC += 3;
    
		A &= MemGet(TU);
		Check(A);
		Clockticks += 48;
		break;
	case 0x3A:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0x3B:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0x3C:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0x3D:
		TU = ((MemGet(PC + 2) << 8) | MemGet(PC + 1)) + X;

		PC += 3;
    
		A &= MemGet(TU);
		Check(A);
		Clockticks += 48;
		break;
	case 0x3E:
		TU = ((MemGet(PC + 2) << 8) | MemGet(PC + 1)) + X;

		PC += 3;
		TV = MemGet(TU);
    
		//used to be TSB
		MemSet(TU, TV);
		TB = P & FLAG_C;
		if (TV & 0x80) SetC(); else ClrC();
		TV = (TV << 1) | TB;
		Check(TV);
		MemSet(TU, TV);
		Clockticks += 84;
		break;
	case 0x3F:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0x40:
		Pull(P);
		PC = *((unsigned short *) &RAM[(SP += 2) + 0x100 - 1]);
		Clockticks += 72;
		break;
	case 0x41:
		TB = MemGet(PC + 1) + X;
		TU = (MemGet(TB + 1) << 8) | MemGet(TB);

		PC += 2;
    
		A ^= MemGet(TU);
		Check(A);
		Clockticks += 72;
		break;
	case 0x42:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0x43:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0x44:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0x45:
		TU = MemGet(PC + 1);

		PC += 2;
    
		A ^= MemGet(TU);
		Check(A);
		Clockticks += 36;
		break;
	case 0x46:
		TU = MemGet(PC + 1);

		PC += 2;
		TV = MemGet(TU);
    
		MemSet(TU, TV);
		if (TV & 0x01) SetC(); else ClrC();
		TV >>= 1;
		Check(TV);
		MemSet(TU, TV);
		Clockticks += 60;
		break;
	case 0x47:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0x48:
		PC ++;
		Push(A);
		Clockticks += 36;
		break;
	case 0x49:
		TU = PC + 1;

		PC += 2;
    
		A ^= MemGet(TU);
		Check(A);
		Clockticks += 24;
		break;
	case 0x4A:
		PC ++;
		if (A & 0x01) SetC(); else ClrC();
		A >>= 1;
		Check(A);
		Clockticks += 24;
		break;
	case 0x4B:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0x4C:
		PC = (MemGet(PC + 2) << 8) | MemGet(PC + 1);

		Clockticks += 36;
		break;
	case 0x4D:
		TU = (MemGet(PC + 2) << 8) | MemGet(PC + 1);

		PC += 3;
    
		A ^= MemGet(TU);
		Check(A);
		Clockticks += 48;
		break;
	case 0x4E:
		TU = (MemGet(PC + 2) << 8) | MemGet(PC + 1);

		PC += 3;
		TV = MemGet(TU);
    
		MemSet(TU, TV);
		if (TV & 0x01) SetC(); else ClrC();
		TV >>= 1;
		Check(TV);
		MemSet(TU, TV);
		Clockticks += 72;
		break;
	case 0x4F:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0x50:
		BRANCHIF(!(P & FLAG_V));
		break;
	case 0x51:
		TB = MemGet(PC + 1);
		TU = ((MemGet(TB + 1) << 8) | MemGet(TB)) + Y;

		PC += 2;
    
		A ^= MemGet(TU);
		Check(A);
		Clockticks += 60;
		break;
	case 0x52:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0x53:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0x54:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0x55:
		TU = (MemGet(PC + 1) + X) & 0xFF;

		PC += 2;
    
		A ^= MemGet(TU);
		Check(A);
		Clockticks += 48;
		break;
	case 0x56:
		TU = (MemGet(PC + 1) + X) & 0xFF;

		PC += 2;
		TV = MemGet(TU);
    
		MemSet(TU, TV);
		if (TV & 0x01) SetC(); else ClrC();
		TV >>= 1;
		Check(TV);
		MemSet(TU, TV);
		Clockticks += 72;
		break;
	case 0x57:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0x58:
		PC ++;
		ClrI();
		Clockticks += 24;
		break;
	case 0x59:
		TU = ((MemGet(PC + 2) << 8) | MemGet(PC + 1)) + Y;

		PC += 3;
    
		A ^= MemGet(TU);
		Check(A);
		Clockticks += 48;
		break;
	case 0x5A:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0x5B:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0x5C:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0x5D:
		TU = ((MemGet(PC + 2) << 8) | MemGet(PC + 1)) + X;

		PC += 3;
    
		A ^= MemGet(TU);
		Check(A);
		Clockticks += 48;
		break;
	case 0x5E:
		TU = ((MemGet(PC + 2) << 8) | MemGet(PC + 1)) + X;

		PC += 3;
		TV = MemGet(TU);
    
		MemSet(TU, TV);
		if (TV & 0x01) SetC(); else ClrC();
		TV >>= 1;
		Check(TV);
		MemSet(TU, TV);
		Clockticks += 84;
		break;
	case 0x5F:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0x60:
		PC = *((unsigned short *) &RAM[(SP += 2) + 0x100 - 1]) + 1;

		Clockticks += 72;
		break;
	case 0x61:
		TB = MemGet(PC + 1) + X;
		TU = (MemGet(TB + 1) << 8) | MemGet(TB);

		PC += 2;
		TV = MemGet(TU);
    
		TS = A + TV + (P & FLAG_C);
		if (TS > 0xFF) SetC(); else ClrC();
		if (!((A ^ TV) & 0x80) && ((A ^ TS) & 0x80)) SetV(); else ClrV();
		A = (BYTE) TS;			
		Check(A);
		Clockticks += 72;
		break;
	case 0x62:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0x63:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0x64:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0x65:
		TU = MemGet(PC + 1);

		PC += 2;
		TV = MemGet(TU);
    
		TS = A + TV + (P & FLAG_C);
		if (TS > 0xFF) SetC(); else ClrC();
		if (!((A ^ TV) & 0x80) && ((A ^ TS) & 0x80)) SetV(); else ClrV();
		A = (BYTE) TS;			
		Check(A);
		Clockticks += 36;
		break;
	case 0x66:
		TU = MemGet(PC + 1);

		PC += 2;
		TV = MemGet(TU);
    
		//used to be TSB
		MemSet(TU, TV);
		TB = (P & FLAG_C) << 7;
		if (TV & 0x1) SetC(); else ClrC();
		TV = (TV >> 1) | TB;
		Check(TV);
		MemSet(TU, TV);
		Clockticks += 60;
		break;
	case 0x67:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0x68:
		PC ++;
		Pull(A); Check(A);
		Clockticks += 48;
		break;
	case 0x69:
		TU = PC + 1;

		PC += 2;
		TV = MemGet(TU);
    
		TS = A + TV + (P & FLAG_C);
		if (TS > 0xFF) SetC(); else ClrC();
		if (!((A ^ TV) & 0x80) && ((A ^ TS) & 0x80)) SetV(); else ClrV();
		A = (BYTE) TS;			
		Check(A);
		Clockticks += 24;
		break;
	case 0x6A:
		PC ++;
		//used to be TSB
		TB = (P & FLAG_C) << 7;
		if (A & 0x1) SetC(); else ClrC();
		A = (A >> 1) | TB;
		Check(A);
		Clockticks += 24;
		break;
	case 0x6B:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0x6C:
		TU = (MemGet(PC+2) << 8) |    MemGet(PC+1);

		PC = (MemGet((TU & 0xFF00) | ((TU+1) & 0xFF)) << 8) | MemGet(TU);
		Clockticks += 60;
		break;
	case 0x6D:
		TU = (MemGet(PC + 2) << 8) | MemGet(PC + 1);

		PC += 3;
		TV = MemGet(TU);
    
		TS = A + TV + (P & FLAG_C);
		if (TS > 0xFF) SetC(); else ClrC();
		if (!((A ^ TV) & 0x80) && ((A ^ TS) & 0x80)) SetV(); else ClrV();
		A = (BYTE) TS;			
		Check(A);
		Clockticks += 48;
		break;
	case 0x6E:
		TU = (MemGet(PC + 2) << 8) | MemGet(PC + 1);

		PC += 3;
		TV = MemGet(TU);
    
		//used to be TSB
		MemSet(TU, TV);
		TB = (P & FLAG_C) << 7;
		if (TV & 0x1) SetC(); else ClrC();
		TV = (TV >> 1) | TB;
		Check(TV);
		MemSet(TU, TV);
		Clockticks += 72;
		break;
	case 0x6F:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0x70:
		BRANCHIF(P & FLAG_V);
		break;
	case 0x71:
		TB = MemGet(PC + 1);
		TU = ((MemGet(TB + 1) << 8) | MemGet(TB)) + Y;

		PC += 2;
		TV = MemGet(TU);
    
		TS = A + TV + (P & FLAG_C);
		if (TS > 0xFF) SetC(); else ClrC();
		if (!((A ^ TV) & 0x80) && ((A ^ TS) & 0x80)) SetV(); else ClrV();
		A = (BYTE) TS;			
		Check(A);
		Clockticks += 60;
		break;
	case 0x72:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0x73:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0x74:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0x75:
		TU = (MemGet(PC + 1) + X) & 0xFF;

		PC += 2;
		TV = MemGet(TU);
    
		TS = A + TV + (P & FLAG_C);
		if (TS > 0xFF) SetC(); else ClrC();
		if (!((A ^ TV) & 0x80) && ((A ^ TS) & 0x80)) SetV(); else ClrV();
		A = (BYTE) TS;			
		Check(A);
		Clockticks += 48;
		break;
	case 0x76:
		TU = (MemGet(PC + 1) + X) & 0xFF;

		PC += 2;
		TV = MemGet(TU);
    
		//used to be TSB
		MemSet(TU, TV);
		TB = (P & FLAG_C) << 7;
		if (TV & 0x1) SetC(); else ClrC();
		TV = (TV >> 1) | TB;
		Check(TV);
		MemSet(TU, TV);
		Clockticks += 72;
		break;
	case 0x77:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0x78:
		PC ++;
		SetI();
		Clockticks += 24;
		break;
	case 0x79:
		TU = ((MemGet(PC + 2) << 8) | MemGet(PC + 1)) + Y;

		PC += 3;
		TV = MemGet(TU);
    
		TS = A + TV + (P & FLAG_C);
		if (TS > 0xFF) SetC(); else ClrC();
		if (!((A ^ TV) & 0x80) && ((A ^ TS) & 0x80)) SetV(); else ClrV();
		A = (BYTE) TS;			
		Check(A);
		Clockticks += 48;
		break;
	case 0x7A:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0x7B:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0x7C:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0x7D:
		TU = ((MemGet(PC + 2) << 8) | MemGet(PC + 1)) + X;

		PC += 3;
		TV = MemGet(TU);
    
		TS = A + TV + (P & FLAG_C);
		if (TS > 0xFF) SetC(); else ClrC();
		if (!((A ^ TV) & 0x80) && ((A ^ TS) & 0x80)) SetV(); else ClrV();
		A = (BYTE) TS;			
		Check(A);
		Clockticks += 48;
		break;
	case 0x7E:
		TU = ((MemGet(PC + 2) << 8) | MemGet(PC + 1)) + X;

		PC += 3;
		TV = MemGet(TU);
    
		//used to be TSB
		MemSet(TU, TV);
		TB = (P & FLAG_C) << 7;
		if (TV & 0x1) SetC(); else ClrC();
		TV = (TV >> 1) | TB;
		Check(TV);
		MemSet(TU, TV);
		Clockticks += 84;
		break;
	case 0x7F:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0x80:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0x81:
		TB = MemGet(PC + 1) + X;
		TU = (MemGet(TB + 1) << 8) | MemGet(TB);

		PC += 2;
		MemSet(TU, A);
		Clockticks += 72;
		break;
	case 0x82:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0x83:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0x84:
		TU = MemGet(PC + 1);

		PC += 2;
		MemSet(TU, Y);
		Clockticks += 36;
		break;
	case 0x85:
		TU = MemGet(PC + 1);

		PC += 2;
		MemSet(TU, A);
		Clockticks += 36;
		break;
	case 0x86:
		TU = MemGet(PC + 1);

		PC += 2;
		MemSet(TU, X);
		Clockticks += 36;
		break;
	case 0x87:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0x88:
		PC ++;
		Y--; Check(Y);
		Clockticks += 24;
		break;
	case 0x89:
		ErrorIns();
		PC ++;
		Clockticks += 24;
		break;
	case 0x8A:
		PC ++;
		A = X; Check(A);
		Clockticks += 24;
		break;
	case 0x8B:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0x8C:
		TU = (MemGet(PC + 2) << 8) | MemGet(PC + 1);

		PC += 3;
		MemSet(TU, Y);
		Clockticks += 48;
		break;
	case 0x8D:
		TU = (MemGet(PC + 2) << 8) | MemGet(PC + 1);

		PC += 3;
		MemSet(TU, A);
		Clockticks += 48;
		break;
	case 0x8E:
		TU = (MemGet(PC + 2) << 8) | MemGet(PC + 1);

		PC += 3;
		MemSet(TU, X);
		Clockticks += 48;
		break;
	case 0x8F:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0x90:
		BRANCHIF(!(P & FLAG_C));
		break;
	case 0x91:
		TB = MemGet(PC + 1);
		TU = ((MemGet(TB + 1) << 8) | MemGet(TB)) + Y;

		PC += 2;
		MemSet(TU, A);
		Clockticks += 60;
		break;
	case 0x92:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0x93:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0x94:
		TU = (MemGet(PC + 1) + X) & 0xFF;

		PC += 2;
		MemSet(TU, Y);
		Clockticks += 48;
		break;
	case 0x95:
		TU = (MemGet(PC + 1) + X) & 0xFF;

		PC += 2;
		MemSet(TU, A);
		Clockticks += 48;
		break;
	case 0x96:
		TU = (MemGet(PC + 1) + Y) & 0xFF;

		PC += 2;
		MemSet(TU, X);
		Clockticks += 48;
		break;
	case 0x97:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0x98:
		PC ++;
		A = Y; Check(A); 
		Clockticks += 24;
		break;
	case 0x99:
		TU = ((MemGet(PC + 2) << 8) | MemGet(PC + 1)) + Y;

		PC += 3;
		MemSet(TU, A);
		Clockticks += 48;
		break;
	case 0x9A:
		PC ++;
		SP = X; Check(SP);		//Check is unknown	
		Clockticks += 24;
		break;
	case 0x9B:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0x9C:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0x9D:
		TU = ((MemGet(PC + 2) << 8) | MemGet(PC + 1)) + X;

		PC += 3;
		MemSet(TU, A);
		Clockticks += 48;
		break;
	case 0x9E:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0x9F:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0xA0:
		TU = PC + 1;

		PC += 2;
		Y = MemGet(TU); Check(Y);
		Clockticks += 24;
		break;
	case 0xA1:
		TB = MemGet(PC + 1) + X;
		TU = (MemGet(TB + 1) << 8) | MemGet(TB);

		PC += 2;
		A = MemGet(TU); Check(A);
		Clockticks += 72;
		break;
	case 0xA2:
		TU = PC + 1;

		PC += 2;
		X = MemGet(TU); Check(X);
		Clockticks += 24;
		break;
	case 0xA3:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0xA4:
		TU = MemGet(PC + 1);

		PC += 2;
		Y = MemGet(TU); Check(Y);
		Clockticks += 36;
		break;
	case 0xA5:
		TU = MemGet(PC + 1);

		PC += 2;
		A = MemGet(TU); Check(A);
		Clockticks += 36;
		break;
	case 0xA6:
		TU = MemGet(PC + 1);

		PC += 2;
		X = MemGet(TU); Check(X);
		Clockticks += 36;
		break;
	case 0xA7:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0xA8:
		PC ++;
		Y = A; Check(Y);
		Clockticks += 24;
		break;
	case 0xA9:
		TU = PC + 1;

		PC += 2;
		A = MemGet(TU); Check(A);
		Clockticks += 24;
		break;
	case 0xAA:
		PC ++;
		X = A; Check(X);
		Clockticks += 24;
		break;
	case 0xAB:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0xAC:
		TU = (MemGet(PC + 2) << 8) | MemGet(PC + 1);

		PC += 3;
		Y = MemGet(TU); Check(Y);
		Clockticks += 48;
		break;
	case 0xAD:
		TU = (MemGet(PC + 2) << 8) | MemGet(PC + 1);

		PC += 3;
		A = MemGet(TU); Check(A);
		Clockticks += 48;
		break;
	case 0xAE:
		TU = (MemGet(PC + 2) << 8) | MemGet(PC + 1);

		PC += 3;
		X = MemGet(TU); Check(X);
		Clockticks += 48;
		break;
	case 0xAF:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0xB0:
		BRANCHIF(P & FLAG_C);
		break;
	case 0xB1:
		TB = MemGet(PC + 1);
		TU = ((MemGet(TB + 1) << 8) | MemGet(TB)) + Y;

		PC += 2;
		A = MemGet(TU); Check(A);
		Clockticks += 60;
		break;
	case 0xB2:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0xB3:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0xB4:
		TU = (MemGet(PC + 1) + X) & 0xFF;

		PC += 2;
		Y = MemGet(TU); Check(Y);
		Clockticks += 48;
		break;
	case 0xB5:
		TU = (MemGet(PC + 1) + X) & 0xFF;

		PC += 2;
		A = MemGet(TU); Check(A);
		Clockticks += 48;
		break;
	case 0xB6:
		TU = (MemGet(PC + 1) + Y) & 0xFF;

		PC += 2;
		X = MemGet(TU); Check(X);
		Clockticks += 48;
		break;
	case 0xB7:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0xB8:
		PC ++;
		ClrV();
		Clockticks += 24;
		break;
	case 0xB9:
		TU = ((MemGet(PC + 2) << 8) | MemGet(PC + 1)) + Y;

		PC += 3;
		A = MemGet(TU); Check(A);
		Clockticks += 48;
		break;
	case 0xBA:
		PC ++;
		X = SP; Check(X);
		Clockticks += 24;
		break;
	case 0xBB:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0xBC:
		TU = ((MemGet(PC + 2) << 8) | MemGet(PC + 1)) + X;

		PC += 3;
		Y = MemGet(TU); Check(Y);
		Clockticks += 48;
		break;
	case 0xBD:
		TU = ((MemGet(PC + 2) << 8) | MemGet(PC + 1)) + X;

		PC += 3;
		A = MemGet(TU); Check(A);
		Clockticks += 48;
		break;
	case 0xBE:
		TU = ((MemGet(PC + 2) << 8) | MemGet(PC + 1)) + Y;

		PC += 3;
		X = MemGet(TU); Check(X);
		Clockticks += 48;
		break;
	case 0xBF:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0xC0:
		TU = PC + 1;

		PC += 2;
    
		TS = Y - MemGet(TU);
		Check(TS);
		if (TS >= 0) SetC(); else ClrC();
		Clockticks += 24;
		break;
	case 0xC1:
		TB = MemGet(PC + 1) + X;
		TU = (MemGet(TB + 1) << 8) | MemGet(TB);

		PC += 2;
    
		TS = A - MemGet(TU);
		Check(TS);
		if (TS >= 0) SetC(); else ClrC();
		Clockticks += 72;
		break;
	case 0xC2:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0xC3:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0xC4:
		TU = MemGet(PC + 1);

		PC += 2;
    
		TS = Y - MemGet(TU);
		Check(TS);
		if (TS >= 0) SetC(); else ClrC();
		Clockticks += 36;
		break;
	case 0xC5:
		TU = MemGet(PC + 1);

		PC += 2;
    
		TS = A - MemGet(TU);
		Check(TS);
		if (TS >= 0) SetC(); else ClrC();
		Clockticks += 36;
		break;
	case 0xC6:
		TU = MemGet(PC + 1);

		PC += 2;
		TV = MemGet(TU);
		MemSet(TU, TV);
		TV--;
		Check(TV);
		MemSet(TU, TV);
		Clockticks += 60;
		break;
	case 0xC7:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0xC8:
		PC ++;
		Y++; Check(Y);
		Clockticks += 24;
		break;
	case 0xC9:
		TU = PC + 1;

		PC += 2;
    
		TS = A - MemGet(TU);
		Check(TS);
		if (TS >= 0) SetC(); else ClrC();
		Clockticks += 24;
		break;
	case 0xCA:
		PC ++;
		X--; Check(X);
		Clockticks += 24;
		break;
	case 0xCB:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0xCC:
		TU = (MemGet(PC + 2) << 8) | MemGet(PC + 1);

		PC += 3;
    
		TS = Y - MemGet(TU);
		Check(TS);
		if (TS >= 0) SetC(); else ClrC();
		Clockticks += 48;
		break;
	case 0xCD:
		TU = (MemGet(PC + 2) << 8) | MemGet(PC + 1);

		PC += 3;
    
		TS = A - MemGet(TU);
		Check(TS);
		if (TS >= 0) SetC(); else ClrC();
		Clockticks += 48;
		break;
	case 0xCE:
		TU = (MemGet(PC + 2) << 8) | MemGet(PC + 1);

		PC += 3;
		TV = MemGet(TU);
		MemSet(TU, TV);
		TV--;
		Check(TV);
		MemSet(TU, TV);
		Clockticks += 72;
		break;
	case 0xCF:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0xD0:
		BRANCHIF(!(P & FLAG_Z));
		break;
	case 0xD1:
		TB = MemGet(PC + 1);
		TU = ((MemGet(TB + 1) << 8) | MemGet(TB)) + Y;

		PC += 2;
    
		TS = A - MemGet(TU);
		Check(TS);
		if (TS >= 0) SetC(); else ClrC();
		Clockticks += 60;
		break;
	case 0xD2:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0xD3:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0xD4:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0xD5:
		TU = (MemGet(PC + 1) + X) & 0xFF;

		PC += 2;
    
		TS = A - MemGet(TU);
		Check(TS);
		if (TS >= 0) SetC(); else ClrC();
		Clockticks += 48;
		break;
	case 0xD6:
		TU = (MemGet(PC + 1) + X) & 0xFF;

		PC += 2;
		TV = MemGet(TU);
		MemSet(TU, TV);
		TV--;
		Check(TV);
		MemSet(TU, TV);
		Clockticks += 72;
		break;
	case 0xD7:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0xD8:
		PC ++;
		ClrD();
		Clockticks += 24;
		break;
	case 0xD9:
		TU = ((MemGet(PC + 2) << 8) | MemGet(PC + 1)) + Y;

		PC += 3;
    
		TS = A - MemGet(TU);
		Check(TS);
		if (TS >= 0) SetC(); else ClrC();
		Clockticks += 48;
		break;
	case 0xDA:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0xDB:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0xDC:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0xDD:
		TU = ((MemGet(PC + 2) << 8) | MemGet(PC + 1)) + X;

		PC += 3;
    
		TS = A - MemGet(TU);
		Check(TS);
		if (TS >= 0) SetC(); else ClrC();
		Clockticks += 48;
		break;
	case 0xDE:
		TU = ((MemGet(PC + 2) << 8) | MemGet(PC + 1)) + X;

		PC += 3;
		TV = MemGet(TU);
		MemSet(TU, TV);
		TV--;
		Check(TV);
		MemSet(TU, TV);
		Clockticks += 84;
		break;
	case 0xDF:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0xE0:
		TU = PC + 1;

		PC += 2;
    
		TS = X - MemGet(TU);
		Check(TS);
		if (TS >= 0) SetC(); else ClrC();
		Clockticks += 24;
		break;
	case 0xE1:
		TB = MemGet(PC + 1) + X;
		TU = (MemGet(TB + 1) << 8) | MemGet(TB);

		PC += 2;
		TV = MemGet(TU);
    
		TS = A - TV - ((P & FLAG_C) ^ 1);
		if (TS < 0) ClrC(); else SetC();
		if (((A ^ TV) & 0x80) && ((A ^ TS) & 0x80)) SetV(); else ClrV();
		A = (BYTE) TS;
		Check(A);
		Clockticks += 72;
		break;
	case 0xE2:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0xE3:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0xE4:
		TU = MemGet(PC + 1);

		PC += 2;
    
		TS = X - MemGet(TU);
		Check(TS);
		if (TS >= 0) SetC(); else ClrC();
		Clockticks += 36;
		break;
	case 0xE5:
		TU = MemGet(PC + 1);

		PC += 2;
		TV = MemGet(TU);
    
		TS = A - TV - ((P & FLAG_C) ^ 1);
		if (TS < 0) ClrC(); else SetC();
		if (((A ^ TV) & 0x80) && ((A ^ TS) & 0x80)) SetV(); else ClrV();
		A = (BYTE) TS;
		Check(A);
		Clockticks += 36;
		break;
	case 0xE6:
		TU = MemGet(PC + 1);

		PC += 2;
		TV = MemGet(TU);
    
		MemSet(TU, TV);
		TV++;
		Check(TV);
		MemSet(TU, TV);
		Clockticks += 60;
		break;
	case 0xE7:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0xE8:
		PC ++;
		X++; Check(X);
		Clockticks += 24;
		break;
	case 0xE9:
		TU = PC + 1;

		PC += 2;
		TV = MemGet(TU);
    
		TS = A - TV - ((P & FLAG_C) ^ 1);
		if (TS < 0) ClrC(); else SetC();
		if (((A ^ TV) & 0x80) && ((A ^ TS) & 0x80)) SetV(); else ClrV();
		A = (BYTE) TS;
		Check(A);
		Clockticks += 24;
		break;
	case 0xEA:
		PC ++;
		Clockticks += 24;
		break;
	case 0xEB:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0xEC:
		TU = (MemGet(PC + 2) << 8) | MemGet(PC + 1);

		PC += 3;
    
		TS = X - MemGet(TU);
		Check(TS);
		if (TS >= 0) SetC(); else ClrC();
		Clockticks += 48;
		break;
	case 0xED:
		TU = (MemGet(PC + 2) << 8) | MemGet(PC + 1);

		PC += 3;
		TV = MemGet(TU);
    
		TS = A - TV - ((P & FLAG_C) ^ 1);
		if (TS < 0) ClrC(); else SetC();
		if (((A ^ TV) & 0x80) && ((A ^ TS) & 0x80)) SetV(); else ClrV();
		A = (BYTE) TS;
		Check(A);
		Clockticks += 48;
		break;
	case 0xEE:
		TU = (MemGet(PC + 2) << 8) | MemGet(PC + 1);

		PC += 3;
		TV = MemGet(TU);
    
		MemSet(TU, TV);
		TV++;
		Check(TV);
		MemSet(TU, TV);
		Clockticks += 72;
		break;
	case 0xEF:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0xF0:
		BRANCHIF(P & FLAG_Z);
		break;
	case 0xF1:
		TB = MemGet(PC + 1);
		TU = ((MemGet(TB + 1) << 8) | MemGet(TB)) + Y;

		PC += 2;
		TV = MemGet(TU);
    
		TS = A - TV - ((P & FLAG_C) ^ 1);
		if (TS < 0) ClrC(); else SetC();
		if (((A ^ TV) & 0x80) && ((A ^ TS) & 0x80)) SetV(); else ClrV();
		A = (BYTE) TS;
		Check(A);
		Clockticks += 60;
		break;
	case 0xF2:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0xF3:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0xF4:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0xF5:
		TU = (MemGet(PC + 1) + X) & 0xFF;

		PC += 2;
		TV = MemGet(TU);
    
		TS = A - TV - ((P & FLAG_C) ^ 1);
		if (TS < 0) ClrC(); else SetC();
		if (((A ^ TV) & 0x80) && ((A ^ TS) & 0x80)) SetV(); else ClrV();
		A = (BYTE) TS;
		Check(A);
		Clockticks += 48;
		break;
	case 0xF6:
		TU = (MemGet(PC + 1) + X) & 0xFF;

		PC += 2;
		TV = MemGet(TU);
    
		MemSet(TU, TV);
		TV++;
		Check(TV);
		MemSet(TU, TV);
		Clockticks += 72;
		break;
	case 0xF7:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0xF8:
		PC ++;
		SetD();
		Clockticks += 24;
		break;
	case 0xF9:
		TU = ((MemGet(PC + 2) << 8) | MemGet(PC + 1)) + Y;

		PC += 3;
		TV = MemGet(TU);
    
		TS = A - TV - ((P & FLAG_C) ^ 1);
		if (TS < 0) ClrC(); else SetC();
		if (((A ^ TV) & 0x80) && ((A ^ TS) & 0x80)) SetV(); else ClrV();
		A = (BYTE) TS;
		Check(A);
		Clockticks += 48;
		break;
	case 0xFA:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0xFB:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0xFC:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	case 0xFD:
		TU = ((MemGet(PC + 2) << 8) | MemGet(PC + 1)) + X;

		PC += 3;
		TV = MemGet(TU);
    
		TS = A - TV - ((P & FLAG_C) ^ 1);
		if (TS < 0) ClrC(); else SetC();
		if (((A ^ TV) & 0x80) && ((A ^ TS) & 0x80)) SetV(); else ClrV();
		A = (BYTE) TS;
		Check(A);
		Clockticks += 48;
		break;
	case 0xFE:
		TU = ((MemGet(PC + 2) << 8) | MemGet(PC + 1)) + X;

		PC += 3;
		TV = MemGet(TU);
    
		MemSet(TU, TV);
		TV++;
		Check(TV);
		MemSet(TU, TV);
		Clockticks += 84;
		break;
	case 0xFF:
		ErrorIns();
		PC ++;
		Clockticks += 0;
		break;
	}
}

void c2A03::ErrorIns()
{
	char tpc[40];
	sprintf(tpc,"Invalid Opcode: %02X",MemGet(PC));
	MessageBox(NULL, tpc, "0wn3d", MB_OK);
	gData->Main->Stop = true;
}
