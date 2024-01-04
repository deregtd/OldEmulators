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

#ifndef HCOL_Z80
#define HCOL_Z80

#include "Col_Controllers.h"

struct cCol_Z80 {
	public :
		cCol_Z80();
		~cCol_Z80()
		{
		}
		void Reset();
		void NMI();
		void IRQ();

		void ExecOp();

		unsigned char PRG[0x8000];	//256 4k pages

		unsigned char *RAM;

		short *Clockticks;
	
	private:
		void ErrorIns();
};

#endif
