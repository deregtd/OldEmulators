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

#include "6507.h"
#include <stdio.h>
#include "..\Global.h"

#define		Push(Byte)			{ MemSet(SP, Byte); SP--; }
#define		Pull(Var)			{ SP++; Var = MemGet(SP); }
#define		PullPC()			{ SP++; PC = MemGet(SP); SP++; PC |= MemGet(SP) << 8; }

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

extern unsigned short int TU;		//To Use - Address Holder Variable
extern unsigned char TB, TV;		//Temp Byte - 8-bit Holder Variable
extern char TSB;					//Temp Signed Byte - For Relative Jumps
extern short TS;				//Temp Short - 16-bit Holder Variables for Compare Insts

c6507::c6507()
{
	unsigned char TP1, TP2;
	for (int i=0;i<256;i++)
	{
		TP1 = i & 0xF;
		TP2 = (i >> 4) & 0xF;
		BCD_LUT[i] = TP1 + (10 * TP2);

		TP1 = i % 10;
		TP2 = (unsigned char) (i / 10);
		BCD_LUT_R[i] = TP1 + (TP2 << 4);
	}
}

void c6507::Reset()
{
	PC = (MemGet(0x1FFD)<<8) | MemGet(0x1FFC);		//Jump to Reset Vector at $FFFC
	P = 0x20;		//??
	SetI();
	SetD();			//Set Decimal Mode
}

void c6507::IRQ()
{
	if (P & FLAG_I) return;	//If Interrupt Disable Flag On, Don't NMI
	
	ClrB();					//Clear Break Flag (?)

	Push((PC >> 8));		//Push Program Counter
	Push((PC & 0xFF));		//	Hi/Low
	Push(P);				//Push Processor Flags

	*TicksToCount += 7*3;
	PC = (MemGet(0x1FFF)<<8) | MemGet(0x1FFE);		//Jump to IRQ Vector at $FFFE
}

void c6507::ExecOp()
{
	Op = MemGet(PC);
	switch (Op)
	{
	case 0x0:
		PC ++;
		PC++;
		Push(PC >> 8);		//Push Program Counter
		Push(PC & 0xFF);		//	Hi/Low
		SetB();					//Set Break Flag
		Push(P);				//Push Processor Flags
		SetI();					//Set Interrupt Flag
		PC = (MemGet(0xFFFF) << 8) | MemGet(0xFFFE);
		break;
	case 0x1:
		TB = MemGet(PC + 1) + X;
		TU = (MemGet(TB + 1) << 8) | MemGet(TB);

		PC += 2;
    
		A |= MemGet(TU);
		Check(A);
		break;
	case 0x2:
		ErrorIns();
		break;
	case 0x3:
		ErrorIns();
		break;
	case 0x4:
		ErrorIns();
		break;
	case 0x5:
		TU = MemGet(PC + 1);

		PC += 2;
    
		A |= MemGet(TU);
		Check(A);
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
		break;
	case 0x7:
		ErrorIns();
		break;
	case 0x8:
		PC ++;
		Push(P | FLAG_B);
		break;
	case 0x9:
		TU = PC + 1;

		PC += 2;
    
		A |= MemGet(TU);
		Check(A);
		break;
	case 0xA:
		PC ++;
		if (A & 0x80) SetC(); else ClrC();
		A <<= 1;
		Check(A);
		break;
	case 0xB:
		ErrorIns();
		break;
	case 0xC:
		ErrorIns();
		break;
	case 0xD:
		TU = (MemGet(PC + 2) << 8) | MemGet(PC + 1);

		PC += 3;
    
		A |= MemGet(TU);
		Check(A);
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
		break;
	case 0xF:
		ErrorIns();
		break;
	case 0x10:
		TSB = (char) MemGet(PC + 1);

		PC += 2;
		if (!(P & FLAG_N)) { PC += TSB; *TicksToCount += 1*3; }
		break;
	case 0x11:
		TB = MemGet(PC + 1);
		TU = ((MemGet(TB + 1) << 8) | MemGet(TB)) + Y;

		PC += 2;
    
		A |= MemGet(TU);
		Check(A);
		break;
	case 0x12:
		ErrorIns();
		break;
	case 0x13:
		ErrorIns();
		break;
	case 0x14:
		ErrorIns();
		break;
	case 0x15:
		TU = (MemGet(PC + 1) + X) & 0xFF;

		PC += 2;
    
		A |= MemGet(TU);
		Check(A);
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
		break;
	case 0x17:
		ErrorIns();
		break;
	case 0x18:
		PC ++;
		ClrC();
		break;
	case 0x19:
		TU = ((MemGet(PC + 2) << 8) | MemGet(PC + 1)) + Y;

		PC += 3;
    
		A |= MemGet(TU);
		Check(A);
		break;
	case 0x1A:
		ErrorIns();
		break;
	case 0x1B:
		ErrorIns();
		break;
	case 0x1C:
		ErrorIns();
		break;
	case 0x1D:
		TU = ((MemGet(PC + 2) << 8) | MemGet(PC + 1)) + X;

		PC += 3;
    
		A |= MemGet(TU);
		Check(A);
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
		break;
	case 0x1F:
		ErrorIns();
		break;
	case 0x20:
		TU = (MemGet(PC + 2) << 8) | MemGet(PC + 1);

		PC += 3;
		PC--;
		Push(PC >> 8);
		Push(PC & 0xFF);
		PC = TU;
		break;
	case 0x21:
		TB = MemGet(PC + 1) + X;
		TU = (MemGet(TB + 1) << 8) | MemGet(TB);

		PC += 2;
    
		A &= MemGet(TU);
		Check(A);
		break;
	case 0x22:
		ErrorIns();
		break;
	case 0x23:
		ErrorIns();
		break;
	case 0x24:
		TU = MemGet(PC + 1);

		PC += 2;
		TV = MemGet(TU);
    
		if (TV & 0x40) SetV(); else ClrV();
		if (TV & 0x80) SetN(); else ClrN();
		TV &= A;
		if (TV) ClrZ(); else SetZ();
		break;
	case 0x25:
		TU = MemGet(PC + 1);

		PC += 2;
    
		A &= MemGet(TU);
		Check(A);
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
		break;
	case 0x27:
		ErrorIns();
		break;
	case 0x28:
		PC ++;
		Pull(P);
		break;
	case 0x29:
		TU = PC + 1;

		PC += 2;
    
		A &= MemGet(TU);
		Check(A);
		break;
	case 0x2A:
		PC ++;
		TB = P & FLAG_C;
		if (A & 0x80) SetC(); else ClrC();
		A = (A << 1) | TB;
		Check(A);
		break;
	case 0x2B:
		ErrorIns();
		break;
	case 0x2C:
		TU = (MemGet(PC + 2) << 8) | MemGet(PC + 1);

		PC += 3;
		TV = MemGet(TU);
    
		if (TV & 0x40) SetV(); else ClrV();
		if (TV & 0x80) SetN(); else ClrN();
		TV &= A;
		if (TV) ClrZ(); else SetZ();
		break;
	case 0x2D:
		TU = (MemGet(PC + 2) << 8) | MemGet(PC + 1);

		PC += 3;
    
		A &= MemGet(TU);
		Check(A);
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
		break;
	case 0x2F:
		ErrorIns();
		break;
	case 0x30:
		TSB = (char) MemGet(PC + 1);

		PC += 2;
		if (P & FLAG_N) { PC += TSB; *TicksToCount += 1*3; }
		break;
	case 0x31:
		TB = MemGet(PC + 1);
		TU = ((MemGet(TB + 1) << 8) | MemGet(TB)) + Y;

		PC += 2;
    
		A &= MemGet(TU);
		Check(A);
		break;
	case 0x32:
		ErrorIns();
		break;
	case 0x33:
		ErrorIns();
		break;
	case 0x34:
		ErrorIns();
		break;
	case 0x35:
		TU = (MemGet(PC + 1) + X) & 0xFF;

		PC += 2;
    
		A &= MemGet(TU);
		Check(A);
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
		break;
	case 0x37:
		ErrorIns();
		break;
	case 0x38:
		PC ++;
		SetC();
		break;
	case 0x39:
		TU = ((MemGet(PC + 2) << 8) | MemGet(PC + 1)) + Y;

		PC += 3;
    
		A &= MemGet(TU);
		Check(A);
		break;
	case 0x3A:
		ErrorIns();
		break;
	case 0x3B:
		ErrorIns();
		break;
	case 0x3C:
		ErrorIns();
		break;
	case 0x3D:
		TU = ((MemGet(PC + 2) << 8) | MemGet(PC + 1)) + X;

		PC += 3;
    
		A &= MemGet(TU);
		Check(A);
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
		break;
	case 0x3F:
		ErrorIns();
		break;
	case 0x40:
		PC ++;
		Pull(P);
		PullPC();
		break;
	case 0x41:
		TB = MemGet(PC + 1) + X;
		TU = (MemGet(TB + 1) << 8) | MemGet(TB);

		PC += 2;
    
		A ^= MemGet(TU);
		Check(A);
		break;
	case 0x42:
		ErrorIns();
		break;
	case 0x43:
		ErrorIns();
		break;
	case 0x44:
		ErrorIns();
		break;
	case 0x45:
		TU = MemGet(PC + 1);

		PC += 2;
    
		A ^= MemGet(TU);
		Check(A);
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
		break;
	case 0x47:
		ErrorIns();
		break;
	case 0x48:
		PC ++;
		Push(A);
		break;
	case 0x49:
		TU = PC + 1;

		PC += 2;
    
		A ^= MemGet(TU);
		Check(A);
		break;
	case 0x4A:
		PC ++;
		if (A & 0x01) SetC(); else ClrC();
		A >>= 1;
		Check(A);
		break;
	case 0x4B:
		ErrorIns();
		break;
	case 0x4C:
		TU = (MemGet(PC + 2) << 8) | MemGet(PC + 1);

		PC += 3;
		PC = TU;
		break;
	case 0x4D:
		TU = (MemGet(PC + 2) << 8) | MemGet(PC + 1);

		PC += 3;
    
		A ^= MemGet(TU);
		Check(A);
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
		break;
	case 0x4F:
		ErrorIns();
		break;
	case 0x50:
		TSB = (char) MemGet(PC + 1);

		PC += 2;
		if (!(P & FLAG_V)) { PC += TSB; *TicksToCount += 1*3; }
		break;
	case 0x51:
		TB = MemGet(PC + 1);
		TU = ((MemGet(TB + 1) << 8) | MemGet(TB)) + Y;

		PC += 2;
    
		A ^= MemGet(TU);
		Check(A);
		break;
	case 0x52:
		ErrorIns();
		break;
	case 0x53:
		ErrorIns();
		break;
	case 0x54:
		ErrorIns();
		break;
	case 0x55:
		TU = (MemGet(PC + 1) + X) & 0xFF;

		PC += 2;
    
		A ^= MemGet(TU);
		Check(A);
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
		break;
	case 0x57:
		ErrorIns();
		break;
	case 0x58:
		PC ++;
		ClrI();
		break;
	case 0x59:
		TU = ((MemGet(PC + 2) << 8) | MemGet(PC + 1)) + Y;

		PC += 3;
    
		A ^= MemGet(TU);
		Check(A);
		break;
	case 0x5A:
		ErrorIns();
		break;
	case 0x5B:
		ErrorIns();
		break;
	case 0x5C:
		ErrorIns();
		break;
	case 0x5D:
		TU = ((MemGet(PC + 2) << 8) | MemGet(PC + 1)) + X;

		PC += 3;
    
		A ^= MemGet(TU);
		Check(A);
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
		break;
	case 0x5F:
		ErrorIns();
		break;
	case 0x60:
		PC ++;
		PullPC(); PC++;
		break;
	case 0x61:
		TB = MemGet(PC + 1) + X;
		TU = (MemGet(TB + 1) << 8) | MemGet(TB);

		PC += 2;
		TV = MemGet(TU);
    
		if (P & FLAG_D) {
			BYTE TB1 = BCD_LUT[A], TB2 = BCD_LUT[TV];
			TS = TB1 + TB2 + (P & FLAG_C);
			if (TS > 100) SetC(); else ClrC();
			//if (!((TB1 ^ TB2) & 0x80) && ((TB1 ^ TS) & 0x80)) SetV(); else ClrV();
			A = BCD_LUT_R[(BYTE) TS];
			Check(A);
		} else {
			TS = A + TV + (P & FLAG_C);
			if (TS > 0xFF) SetC(); else ClrC();
			if (!((A ^ TV) & 0x80) && ((A ^ TS) & 0x80)) SetV(); else ClrV();
			A = (BYTE) TS;
			Check(A);
		}
		break;
	case 0x62:
		ErrorIns();
		break;
	case 0x63:
		ErrorIns();
		break;
	case 0x64:
		ErrorIns();
		break;
	case 0x65:
		TU = MemGet(PC + 1);

		PC += 2;
		TV = MemGet(TU);
    
		if (P & FLAG_D) {
			BYTE TB1 = BCD_LUT[A], TB2 = BCD_LUT[TV];
			TS = TB1 + TB2 + (P & FLAG_C);
			if (TS > 100) SetC(); else ClrC();
			//if (!((TB1 ^ TB2) & 0x80) && ((TB1 ^ TS) & 0x80)) SetV(); else ClrV();
			A = BCD_LUT_R[(BYTE) TS];
			Check(A);
		} else {
			TS = A + TV + (P & FLAG_C);
			if (TS > 0xFF) SetC(); else ClrC();
			if (!((A ^ TV) & 0x80) && ((A ^ TS) & 0x80)) SetV(); else ClrV();
			A = (BYTE) TS;
			Check(A);
		}
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
		break;
	case 0x67:
		ErrorIns();
		break;
	case 0x68:
		PC ++;
		Pull(A); Check(A);
		break;
	case 0x69:
		TU = PC + 1;

		PC += 2;
		TV = MemGet(TU);
    
		if (P & FLAG_D) {
			BYTE TB1 = BCD_LUT[A], TB2 = BCD_LUT[TV];
			TS = TB1 + TB2 + (P & FLAG_C);
			if (TS > 100) SetC(); else ClrC();
			//if (!((TB1 ^ TB2) & 0x80) && ((TB1 ^ TS) & 0x80)) SetV(); else ClrV();
			A = BCD_LUT_R[(BYTE) TS];
			Check(A);
		} else {
			TS = A + TV + (P & FLAG_C);
			if (TS > 0xFF) SetC(); else ClrC();
			if (!((A ^ TV) & 0x80) && ((A ^ TS) & 0x80)) SetV(); else ClrV();
			A = (BYTE) TS;
			Check(A);
		}
		break;
	case 0x6A:
		PC ++;
		//used to be TSB
		TB = (P & FLAG_C) << 7;
		if (A & 0x1) SetC(); else ClrC();
		A = (A >> 1) | TB;
		Check(A);
		break;
	case 0x6B:
		ErrorIns();
		break;
	case 0x6C:
		TU = (MemGet(PC+2) << 8) |    MemGet(PC+1);
		TU = (MemGet((TU & 0xFF00) | ((TU+1) & 0xFF)) << 8) | MemGet(TU);

		PC = TU;
		break;
	case 0x6D:
		TU = (MemGet(PC + 2) << 8) | MemGet(PC + 1);

		PC += 3;
		TV = MemGet(TU);
    
		if (P & FLAG_D) {
			BYTE TB1 = BCD_LUT[A], TB2 = BCD_LUT[TV];
			TS = TB1 + TB2 + (P & FLAG_C);
			if (TS > 100) SetC(); else ClrC();
			//if (!((TB1 ^ TB2) & 0x80) && ((TB1 ^ TS) & 0x80)) SetV(); else ClrV();
			A = BCD_LUT_R[(BYTE) TS];
			Check(A);
		} else {
			TS = A + TV + (P & FLAG_C);
			if (TS > 0xFF) SetC(); else ClrC();
			if (!((A ^ TV) & 0x80) && ((A ^ TS) & 0x80)) SetV(); else ClrV();
			A = (BYTE) TS;
			Check(A);
		}
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
		break;
	case 0x6F:
		ErrorIns();
		break;
	case 0x70:
		TSB = (char) MemGet(PC + 1);

		PC += 2;
		if (P & FLAG_V) { PC += TSB; *TicksToCount += 1*3; }
		break;
	case 0x71:
		TB = MemGet(PC + 1);
		TU = ((MemGet(TB + 1) << 8) | MemGet(TB)) + Y;

		PC += 2;
		TV = MemGet(TU);
    
		if (P & FLAG_D) {
			BYTE TB1 = BCD_LUT[A], TB2 = BCD_LUT[TV];
			TS = TB1 + TB2 + (P & FLAG_C);
			if (TS > 100) SetC(); else ClrC();
			//if (!((TB1 ^ TB2) & 0x80) && ((TB1 ^ TS) & 0x80)) SetV(); else ClrV();
			A = BCD_LUT_R[(BYTE) TS];
			Check(A);
		} else {
			TS = A + TV + (P & FLAG_C);
			if (TS > 0xFF) SetC(); else ClrC();
			if (!((A ^ TV) & 0x80) && ((A ^ TS) & 0x80)) SetV(); else ClrV();
			A = (BYTE) TS;
			Check(A);
		}
		break;
	case 0x72:
		ErrorIns();
		break;
	case 0x73:
		ErrorIns();
		break;
	case 0x74:
		ErrorIns();
		break;
	case 0x75:
		TU = (MemGet(PC + 1) + X) & 0xFF;

		PC += 2;
		TV = MemGet(TU);
    
		if (P & FLAG_D) {
			BYTE TB1 = BCD_LUT[A], TB2 = BCD_LUT[TV];
			TS = TB1 + TB2 + (P & FLAG_C);
			if (TS > 100) SetC(); else ClrC();
			//if (!((TB1 ^ TB2) & 0x80) && ((TB1 ^ TS) & 0x80)) SetV(); else ClrV();
			A = BCD_LUT_R[(BYTE) TS];
			Check(A);
		} else {
			TS = A + TV + (P & FLAG_C);
			if (TS > 0xFF) SetC(); else ClrC();
			if (!((A ^ TV) & 0x80) && ((A ^ TS) & 0x80)) SetV(); else ClrV();
			A = (BYTE) TS;
			Check(A);
		}
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
		break;
	case 0x77:
		ErrorIns();
		break;
	case 0x78:
		PC ++;
		SetI();
		break;
	case 0x79:
		TU = ((MemGet(PC + 2) << 8) | MemGet(PC + 1)) + Y;

		PC += 3;
		TV = MemGet(TU);
    
		if (P & FLAG_D) {
			BYTE TB1 = BCD_LUT[A], TB2 = BCD_LUT[TV];
			TS = TB1 + TB2 + (P & FLAG_C);
			if (TS > 100) SetC(); else ClrC();
			//if (!((TB1 ^ TB2) & 0x80) && ((TB1 ^ TS) & 0x80)) SetV(); else ClrV();
			A = BCD_LUT_R[(BYTE) TS];
			Check(A);
		} else {
			TS = A + TV + (P & FLAG_C);
			if (TS > 0xFF) SetC(); else ClrC();
			if (!((A ^ TV) & 0x80) && ((A ^ TS) & 0x80)) SetV(); else ClrV();
			A = (BYTE) TS;
			Check(A);
		}
		break;
	case 0x7A:
		ErrorIns();
		break;
	case 0x7B:
		ErrorIns();
		break;
	case 0x7C:
		ErrorIns();
		break;
	case 0x7D:
		TU = ((MemGet(PC + 2) << 8) | MemGet(PC + 1)) + X;

		PC += 3;
		TV = MemGet(TU);
    
		if (P & FLAG_D) {
			BYTE TB1 = BCD_LUT[A], TB2 = BCD_LUT[TV];
			TS = TB1 + TB2 + (P & FLAG_C);
			if (TS > 100) SetC(); else ClrC();
			//if (!((TB1 ^ TB2) & 0x80) && ((TB1 ^ TS) & 0x80)) SetV(); else ClrV();
			A = BCD_LUT_R[(BYTE) TS];
			Check(A);
		} else {
			TS = A + TV + (P & FLAG_C);
			if (TS > 0xFF) SetC(); else ClrC();
			if (!((A ^ TV) & 0x80) && ((A ^ TS) & 0x80)) SetV(); else ClrV();
			A = (BYTE) TS;
			Check(A);
		}
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
		break;
	case 0x7F:
		ErrorIns();
		break;
	case 0x80:
		ErrorIns();
		break;
	case 0x81:
		TB = MemGet(PC + 1) + X;
		TU = (MemGet(TB + 1) << 8) | MemGet(TB);

		PC += 2;
		MemSet(TU, A);
		break;
	case 0x82:
		ErrorIns();
		break;
	case 0x83:
		ErrorIns();
		break;
	case 0x84:
		TU = MemGet(PC + 1);

		PC += 2;
		MemSet(TU, Y);
		break;
	case 0x85:
		TU = MemGet(PC + 1);

		PC += 2;
		MemSet(TU, A);
		break;
	case 0x86:
		TU = MemGet(PC + 1);

		PC += 2;
		MemSet(TU, X);
		break;
	case 0x87:
		ErrorIns();
		break;
	case 0x88:
		PC ++;
		Y--; Check(Y);
		break;
	case 0x89:
		ErrorIns();
		break;
	case 0x8A:
		PC ++;
		A = X; Check(A);
		break;
	case 0x8B:
		ErrorIns();
		break;
	case 0x8C:
		TU = (MemGet(PC + 2) << 8) | MemGet(PC + 1);

		PC += 3;
		MemSet(TU, Y);
		break;
	case 0x8D:
		TU = (MemGet(PC + 2) << 8) | MemGet(PC + 1);

		PC += 3;
		MemSet(TU, A);
		break;
	case 0x8E:
		TU = (MemGet(PC + 2) << 8) | MemGet(PC + 1);

		PC += 3;
		MemSet(TU, X);
		break;
	case 0x8F:
		ErrorIns();
		break;
	case 0x90:
		TSB = (char) MemGet(PC + 1);

		PC += 2;
		if (!(P & FLAG_C)) { PC += TSB; *TicksToCount += 1*3; }
		break;
	case 0x91:
		TB = MemGet(PC + 1);
		TU = ((MemGet(TB + 1) << 8) | MemGet(TB)) + Y;

		PC += 2;
		MemSet(TU, A);
		break;
	case 0x92:
		ErrorIns();
		break;
	case 0x93:
		ErrorIns();
		break;
	case 0x94:
		TU = (MemGet(PC + 1) + X) & 0xFF;

		PC += 2;
		MemSet(TU, Y);
		break;
	case 0x95:
		TU = (MemGet(PC + 1) + X) & 0xFF;

		PC += 2;
		MemSet(TU, A);
		break;
	case 0x96:
		TU = (MemGet(PC + 1) + Y) & 0xFF;

		PC += 2;
		MemSet(TU, X);
		break;
	case 0x97:
		ErrorIns();
		break;
	case 0x98:
		PC ++;
		A = Y; Check(A); 
		break;
	case 0x99:
		TU = ((MemGet(PC + 2) << 8) | MemGet(PC + 1)) + Y;

		PC += 3;
		MemSet(TU, A);
		break;
	case 0x9A:
		PC ++;
		SP = X; Check(SP);		//Check is unknown	
		break;
	case 0x9B:
		ErrorIns();
		break;
	case 0x9C:
		ErrorIns();
		break;
	case 0x9D:
		TU = ((MemGet(PC + 2) << 8) | MemGet(PC + 1)) + X;

		PC += 3;
		MemSet(TU, A);
		break;
	case 0x9E:
		ErrorIns();
		break;
	case 0x9F:
		ErrorIns();
		break;
	case 0xA0:
		TU = PC + 1;

		PC += 2;
		Y = MemGet(TU); Check(Y);
		break;
	case 0xA1:
		TB = MemGet(PC + 1) + X;
		TU = (MemGet(TB + 1) << 8) | MemGet(TB);

		PC += 2;
		A = MemGet(TU); Check(A);
		break;
	case 0xA2:
		TU = PC + 1;

		PC += 2;
		X = MemGet(TU); Check(X);
		break;
	case 0xA3:
		ErrorIns();
		break;
	case 0xA4:
		TU = MemGet(PC + 1);

		PC += 2;
		Y = MemGet(TU); Check(Y);
		break;
	case 0xA5:
		TU = MemGet(PC + 1);

		PC += 2;
		A = MemGet(TU); Check(A);
		break;
	case 0xA6:
		TU = MemGet(PC + 1);

		PC += 2;
		X = MemGet(TU); Check(X);
		break;
	case 0xA7:
		ErrorIns();
		break;
	case 0xA8:
		PC ++;
		Y = A; Check(Y);
		break;
	case 0xA9:
		TU = PC + 1;

		PC += 2;
		A = MemGet(TU); Check(A);
		break;
	case 0xAA:
		PC ++;
		X = A; Check(X);
		break;
	case 0xAB:
		ErrorIns();
		break;
	case 0xAC:
		TU = (MemGet(PC + 2) << 8) | MemGet(PC + 1);

		PC += 3;
		Y = MemGet(TU); Check(Y);
		break;
	case 0xAD:
		TU = (MemGet(PC + 2) << 8) | MemGet(PC + 1);

		PC += 3;
		A = MemGet(TU); Check(A);
		break;
	case 0xAE:
		TU = (MemGet(PC + 2) << 8) | MemGet(PC + 1);

		PC += 3;
		X = MemGet(TU); Check(X);
		break;
	case 0xAF:
		ErrorIns();
		break;
	case 0xB0:
		TSB = (char) MemGet(PC + 1);

		PC += 2;
		if (P & FLAG_C) { PC += TSB; *TicksToCount += 1*3; }
		break;
	case 0xB1:
		TB = MemGet(PC + 1);
		TU = ((MemGet(TB + 1) << 8) | MemGet(TB)) + Y;

		PC += 2;
		A = MemGet(TU); Check(A);
		break;
	case 0xB2:
		ErrorIns();
		break;
	case 0xB3:
		ErrorIns();
		break;
	case 0xB4:
		TU = (MemGet(PC + 1) + X) & 0xFF;

		PC += 2;
		Y = MemGet(TU); Check(Y);
		break;
	case 0xB5:
		TU = (MemGet(PC + 1) + X) & 0xFF;

		PC += 2;
		A = MemGet(TU); Check(A);
		break;
	case 0xB6:
		TU = (MemGet(PC + 1) + Y) & 0xFF;

		PC += 2;
		X = MemGet(TU); Check(X);
		break;
	case 0xB7:
		ErrorIns();
		break;
	case 0xB8:
		PC ++;
		ClrV();
		break;
	case 0xB9:
		TU = ((MemGet(PC + 2) << 8) | MemGet(PC + 1)) + Y;

		PC += 3;
		A = MemGet(TU); Check(A);
		break;
	case 0xBA:
		PC ++;
		X = SP; Check(X);
		break;
	case 0xBB:
		ErrorIns();
		break;
	case 0xBC:
		TU = ((MemGet(PC + 2) << 8) | MemGet(PC + 1)) + X;

		PC += 3;
		Y = MemGet(TU); Check(Y);
		break;
	case 0xBD:
		TU = ((MemGet(PC + 2) << 8) | MemGet(PC + 1)) + X;

		PC += 3;
		A = MemGet(TU); Check(A);
		break;
	case 0xBE:
		TU = ((MemGet(PC + 2) << 8) | MemGet(PC + 1)) + Y;

		PC += 3;
		X = MemGet(TU); Check(X);
		break;
	case 0xBF:
		ErrorIns();
		break;
	case 0xC0:
		TU = PC + 1;

		PC += 2;
    
		TS = Y - MemGet(TU);
		Check(TS);
		if (TS >= 0) SetC(); else ClrC();
		break;
	case 0xC1:
		TB = MemGet(PC + 1) + X;
		TU = (MemGet(TB + 1) << 8) | MemGet(TB);

		PC += 2;
    
		TS = A - MemGet(TU);
		Check(TS);
		if (TS >= 0) SetC(); else ClrC();
		break;
	case 0xC2:
		ErrorIns();
		break;
	case 0xC3:
		ErrorIns();
		break;
	case 0xC4:
		TU = MemGet(PC + 1);

		PC += 2;
    
		TS = Y - MemGet(TU);
		Check(TS);
		if (TS >= 0) SetC(); else ClrC();
		break;
	case 0xC5:
		TU = MemGet(PC + 1);

		PC += 2;
    
		TS = A - MemGet(TU);
		Check(TS);
		if (TS >= 0) SetC(); else ClrC();
		break;
	case 0xC6:
		TU = MemGet(PC + 1);

		PC += 2;
		TV = MemGet(TU);
		MemSet(TU, TV);
		TV--;
		Check(TV);
		MemSet(TU, TV);
		break;
	case 0xC7:
		ErrorIns();
		break;
	case 0xC8:
		PC ++;
		Y++; Check(Y);
		break;
	case 0xC9:
		TU = PC + 1;

		PC += 2;
    
		TS = A - MemGet(TU);
		Check(TS);
		if (TS >= 0) SetC(); else ClrC();
		break;
	case 0xCA:
		PC ++;
		X--; Check(X);
		break;
	case 0xCB:
		ErrorIns();
		break;
	case 0xCC:
		TU = (MemGet(PC + 2) << 8) | MemGet(PC + 1);

		PC += 3;
    
		TS = Y - MemGet(TU);
		Check(TS);
		if (TS >= 0) SetC(); else ClrC();
		break;
	case 0xCD:
		TU = (MemGet(PC + 2) << 8) | MemGet(PC + 1);

		PC += 3;
    
		TS = A - MemGet(TU);
		Check(TS);
		if (TS >= 0) SetC(); else ClrC();
		break;
	case 0xCE:
		TU = (MemGet(PC + 2) << 8) | MemGet(PC + 1);

		PC += 3;
		TV = MemGet(TU);
		MemSet(TU, TV);
		TV--;
		Check(TV);
		MemSet(TU, TV);
		break;
	case 0xCF:
		ErrorIns();
		break;
	case 0xD0:
		TSB = (char) MemGet(PC + 1);

		PC += 2;
		if (!(P & FLAG_Z)) { PC += TSB; *TicksToCount += 1*3; }
		break;
	case 0xD1:
		TB = MemGet(PC + 1);
		TU = ((MemGet(TB + 1) << 8) | MemGet(TB)) + Y;

		PC += 2;
    
		TS = A - MemGet(TU);
		Check(TS);
		if (TS >= 0) SetC(); else ClrC();
		break;
	case 0xD2:
		ErrorIns();
		break;
	case 0xD3:
		ErrorIns();
		break;
	case 0xD4:
		ErrorIns();
		break;
	case 0xD5:
		TU = (MemGet(PC + 1) + X) & 0xFF;

		PC += 2;
    
		TS = A - MemGet(TU);
		Check(TS);
		if (TS >= 0) SetC(); else ClrC();
		break;
	case 0xD6:
		TU = (MemGet(PC + 1) + X) & 0xFF;

		PC += 2;
		TV = MemGet(TU);
		MemSet(TU, TV);
		TV--;
		Check(TV);
		MemSet(TU, TV);
		break;
	case 0xD7:
		ErrorIns();
		break;
	case 0xD8:
		PC ++;
		ClrD();
		break;
	case 0xD9:
		TU = ((MemGet(PC + 2) << 8) | MemGet(PC + 1)) + Y;

		PC += 3;
    
		TS = A - MemGet(TU);
		Check(TS);
		if (TS >= 0) SetC(); else ClrC();
		break;
	case 0xDA:
		ErrorIns();
		break;
	case 0xDB:
		ErrorIns();
		break;
	case 0xDC:
		ErrorIns();
		break;
	case 0xDD:
		TU = ((MemGet(PC + 2) << 8) | MemGet(PC + 1)) + X;

		PC += 3;
    
		TS = A - MemGet(TU);
		Check(TS);
		if (TS >= 0) SetC(); else ClrC();
		break;
	case 0xDE:
		TU = ((MemGet(PC + 2) << 8) | MemGet(PC + 1)) + X;

		PC += 3;
		TV = MemGet(TU);
		MemSet(TU, TV);
		TV--;
		Check(TV);
		MemSet(TU, TV);
		break;
	case 0xDF:
		ErrorIns();
		break;
	case 0xE0:
		TU = PC + 1;

		PC += 2;
    
		TS = X - MemGet(TU);
		Check(TS);
		if (TS >= 0) SetC(); else ClrC();
		break;
	case 0xE1:
		TB = MemGet(PC + 1) + X;
		TU = (MemGet(TB + 1) << 8) | MemGet(TB);

		PC += 2;
		TV = MemGet(TU);
    
		if (P & FLAG_D) {
			BYTE TB1 = BCD_LUT[A], TB2 = BCD_LUT[TV];
			TS = TB1 - TB2 - ((P & FLAG_C) ^ 1);
			if (TS < 0) ClrC(); else SetC();
			//if (((TB1 ^ TB2) & 0x80) && ((TB1 ^ TS) & 0x80)) SetV(); else ClrV();
			A = BCD_LUT_R[(BYTE) TS];
			Check(A);
		} else {
			TS = A - TV - ((P & FLAG_C) ^ 1);
			if (TS < 0) ClrC(); else SetC();
			if (((A ^ TV) & 0x80) && ((A ^ TS) & 0x80)) SetV(); else ClrV();
			A = (BYTE) TS;
			Check(A);
		}
		break;
	case 0xE2:
		ErrorIns();
		break;
	case 0xE3:
		ErrorIns();
		break;
	case 0xE4:
		TU = MemGet(PC + 1);

		PC += 2;
    
		TS = X - MemGet(TU);
		Check(TS);
		if (TS >= 0) SetC(); else ClrC();
		break;
	case 0xE5:
		TU = MemGet(PC + 1);

		PC += 2;
		TV = MemGet(TU);
    
		if (P & FLAG_D) {
			BYTE TB1 = BCD_LUT[A], TB2 = BCD_LUT[TV];
			TS = TB1 - TB2 - ((P & FLAG_C) ^ 1);
			if (TS < 0) ClrC(); else SetC();
			//if (((TB1 ^ TB2) & 0x80) && ((TB1 ^ TS) & 0x80)) SetV(); else ClrV();
			A = BCD_LUT_R[(BYTE) TS];
			Check(A);
		} else {
			TS = A - TV - ((P & FLAG_C) ^ 1);
			if (TS < 0) ClrC(); else SetC();
			if (((A ^ TV) & 0x80) && ((A ^ TS) & 0x80)) SetV(); else ClrV();
			A = (BYTE) TS;
			Check(A);
		}
		break;
	case 0xE6:
		TU = MemGet(PC + 1);

		PC += 2;
		TV = MemGet(TU);
    
		MemSet(TU, TV);
		TV++;
		Check(TV);
		MemSet(TU, TV);
		break;
	case 0xE7:
		ErrorIns();
		break;
	case 0xE8:
		PC ++;
		X++; Check(X);
		break;
	case 0xE9:
		TU = PC + 1;

		PC += 2;
		TV = MemGet(TU);
    
		if (P & FLAG_D) {
			BYTE TB1 = BCD_LUT[A], TB2 = BCD_LUT[TV];
			TS = TB1 - TB2 - ((P & FLAG_C) ^ 1);
			if (TS < 0) ClrC(); else SetC();
			//if (((TB1 ^ TB2) & 0x80) && ((TB1 ^ TS) & 0x80)) SetV(); else ClrV();
			A = BCD_LUT_R[(BYTE) TS];
			Check(A);
		} else {
			TS = A - TV - ((P & FLAG_C) ^ 1);
			if (TS < 0) ClrC(); else SetC();
			if (((A ^ TV) & 0x80) && ((A ^ TS) & 0x80)) SetV(); else ClrV();
			A = (BYTE) TS;
			Check(A);
		}
		break;
	case 0xEA:
		PC ++;
		break;
	case 0xEB:
		ErrorIns();
		break;
	case 0xEC:
		TU = (MemGet(PC + 2) << 8) | MemGet(PC + 1);

		PC += 3;
    
		TS = X - MemGet(TU);
		Check(TS);
		if (TS >= 0) SetC(); else ClrC();
		break;
	case 0xED:
		TU = (MemGet(PC + 2) << 8) | MemGet(PC + 1);

		PC += 3;
		TV = MemGet(TU);
    
		if (P & FLAG_D) {
			BYTE TB1 = BCD_LUT[A], TB2 = BCD_LUT[TV];
			TS = TB1 - TB2 - ((P & FLAG_C) ^ 1);
			if (TS < 0) ClrC(); else SetC();
			//if (((TB1 ^ TB2) & 0x80) && ((TB1 ^ TS) & 0x80)) SetV(); else ClrV();
			A = BCD_LUT_R[(BYTE) TS];
			Check(A);
		} else {
			TS = A - TV - ((P & FLAG_C) ^ 1);
			if (TS < 0) ClrC(); else SetC();
			if (((A ^ TV) & 0x80) && ((A ^ TS) & 0x80)) SetV(); else ClrV();
			A = (BYTE) TS;
			Check(A);
		}
		break;
	case 0xEE:
		TU = (MemGet(PC + 2) << 8) | MemGet(PC + 1);

		PC += 3;
		TV = MemGet(TU);
    
		MemSet(TU, TV);
		TV++;
		Check(TV);
		MemSet(TU, TV);
		break;
	case 0xEF:
		ErrorIns();
		break;
	case 0xF0:
		TSB = (char) MemGet(PC + 1);

		PC += 2;
		if (P & FLAG_Z) { PC += TSB; *TicksToCount += 1*3; }
		break;
	case 0xF1:
		TB = MemGet(PC + 1);
		TU = ((MemGet(TB + 1) << 8) | MemGet(TB)) + Y;

		PC += 2;
		TV = MemGet(TU);
    
		if (P & FLAG_D) {
			BYTE TB1 = BCD_LUT[A], TB2 = BCD_LUT[TV];
			TS = TB1 - TB2 - ((P & FLAG_C) ^ 1);
			if (TS < 0) ClrC(); else SetC();
			//if (((TB1 ^ TB2) & 0x80) && ((TB1 ^ TS) & 0x80)) SetV(); else ClrV();
			A = BCD_LUT_R[(BYTE) TS];
			Check(A);
		} else {
			TS = A - TV - ((P & FLAG_C) ^ 1);
			if (TS < 0) ClrC(); else SetC();
			if (((A ^ TV) & 0x80) && ((A ^ TS) & 0x80)) SetV(); else ClrV();
			A = (BYTE) TS;
			Check(A);
		}
		break;
	case 0xF2:
		ErrorIns();
		break;
	case 0xF3:
		ErrorIns();
		break;
	case 0xF4:
		ErrorIns();
		break;
	case 0xF5:
		TU = (MemGet(PC + 1) + X) & 0xFF;

		PC += 2;
		TV = MemGet(TU);
    
		if (P & FLAG_D) {
			BYTE TB1 = BCD_LUT[A], TB2 = BCD_LUT[TV];
			TS = TB1 - TB2 - ((P & FLAG_C) ^ 1);
			if (TS < 0) ClrC(); else SetC();
			//if (((TB1 ^ TB2) & 0x80) && ((TB1 ^ TS) & 0x80)) SetV(); else ClrV();
			A = BCD_LUT_R[(BYTE) TS];
			Check(A);
		} else {
			TS = A - TV - ((P & FLAG_C) ^ 1);
			if (TS < 0) ClrC(); else SetC();
			if (((A ^ TV) & 0x80) && ((A ^ TS) & 0x80)) SetV(); else ClrV();
			A = (BYTE) TS;
			Check(A);
		}
		break;
	case 0xF6:
		TU = (MemGet(PC + 1) + X) & 0xFF;

		PC += 2;
		TV = MemGet(TU);
    
		MemSet(TU, TV);
		TV++;
		Check(TV);
		MemSet(TU, TV);
		break;
	case 0xF7:
		ErrorIns();
		break;
	case 0xF8:
		PC ++;
		SetD();
		break;
	case 0xF9:
		TU = ((MemGet(PC + 2) << 8) | MemGet(PC + 1)) + Y;

		PC += 3;
		TV = MemGet(TU);
    
		if (P & FLAG_D) {
			BYTE TB1 = BCD_LUT[A], TB2 = BCD_LUT[TV];
			TS = TB1 - TB2 - ((P & FLAG_C) ^ 1);
			if (TS < 0) ClrC(); else SetC();
			//if (((TB1 ^ TB2) & 0x80) && ((TB1 ^ TS) & 0x80)) SetV(); else ClrV();
			A = BCD_LUT_R[(BYTE) TS];
			Check(A);
		} else {
			TS = A - TV - ((P & FLAG_C) ^ 1);
			if (TS < 0) ClrC(); else SetC();
			if (((A ^ TV) & 0x80) && ((A ^ TS) & 0x80)) SetV(); else ClrV();
			A = (BYTE) TS;
			Check(A);
		}
		break;
	case 0xFA:
		ErrorIns();
		break;
	case 0xFB:
		ErrorIns();
		break;
	case 0xFC:
		ErrorIns();
		break;
	case 0xFD:
		TU = ((MemGet(PC + 2) << 8) | MemGet(PC + 1)) + X;

		PC += 3;
		TV = MemGet(TU);
    
		if (P & FLAG_D) {
			BYTE TB1 = BCD_LUT[A], TB2 = BCD_LUT[TV];
			TS = TB1 - TB2 - ((P & FLAG_C) ^ 1);
			if (TS < 0) ClrC(); else SetC();
			//if (((TB1 ^ TB2) & 0x80) && ((TB1 ^ TS) & 0x80)) SetV(); else ClrV();
			A = BCD_LUT_R[(BYTE) TS];
			Check(A);
		} else {
			TS = A - TV - ((P & FLAG_C) ^ 1);
			if (TS < 0) ClrC(); else SetC();
			if (((A ^ TV) & 0x80) && ((A ^ TS) & 0x80)) SetV(); else ClrV();
			A = (BYTE) TS;
			Check(A);
		}
		break;
	case 0xFE:
		TU = ((MemGet(PC + 2) << 8) | MemGet(PC + 1)) + X;

		PC += 3;
		TV = MemGet(TU);
    
		MemSet(TU, TV);
		TV++;
		Check(TV);
		MemSet(TU, TV);
		break;
	case 0xFF:
		ErrorIns();
		break;
	}
}

void c6507::ErrorIns()
{
	char tpc[40];
	sprintf(tpc,"Invalid Opcode: %02X",Op);
	MessageBox(NULL, tpc, "0wn3d", MB_OK);
	gData->Main->Stop = true;
}
