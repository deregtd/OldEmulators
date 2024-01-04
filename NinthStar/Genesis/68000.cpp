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

#include "68000.h"
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

c68000::c68000()
{
}

void c68000::Reset()
{
	PC = (MemGet(0x1FFD)<<8) | MemGet(0x1FFC);		//Jump to Reset Vector at $FFFC
	P = 0x20;		//??
	SetI();
	SetD();			//Set Decimal Mode
}

void c68000::IRQ()
{
	if (P & FLAG_I) return;	//If Interrupt Disable Flag On, Don't NMI
	
	ClrB();					//Clear Break Flag (?)

	Push((PC >> 8));		//Push Program Counter
	Push((PC & 0xFF));		//	Hi/Low
	Push(P);				//Push Processor Flags

	*Clockticks += 7*3;
	PC = (MemGet(0x1FFF)<<8) | MemGet(0x1FFE);		//Jump to IRQ Vector at $FFFE
}

void c68000::ExecOp()
{
	Op = MemGet(PC);
}

void c68000::ErrorIns()
{
	char tpc[40];
	sprintf(tpc,"Invalid Opcode: %02X",Op);
	MessageBox(NULL, tpc, "0wn3d", MB_OK);
	gData->Main->Stop = true;
}
