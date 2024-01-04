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

#include "Col_Z80.h"
#include <stdio.h>
#include "..\Global.h"

//#define		MemGet(Addy)		Bank[(Addy) >> 12]->ReadHandler((Addy) >> 12, Addy)
//#define		MemGet(Addy)		(((Addy) & 0x8000) ? PRG[Mapper->Map->CPUPage[((Addy) >> 12) - 8]][(Addy) & 0x0FFF] : Bank[(Addy) >> 12]->ReadHandler((Addy) >> 12, (Addy)))
//#define		MemSet(Addy, Val)	Bank[(Addy) >> 12]->WriteHandler((Addy) >> 12, Addy, Val)
#define		MemGet(Addy)		0
#define		MemSet(Addy)		

cCol_Z80::cCol_Z80()
{
}

void cCol_Z80::Reset()
{
}

void cCol_Z80::IRQ()
{
}

void cCol_Z80::NMI()
{
}

void cCol_Z80::ExecOp()
{
//	switch (MemGet(PC))
//	{
//	}
}

void cCol_Z80::ErrorIns()
{
	char tpc[40];
	sprintf(tpc,"Invalid Opcode: %02X",MemGet(PC));
	MessageBox(NULL, tpc, "0wn3d", MB_OK);
	gData->Main->Stop = true;
}
