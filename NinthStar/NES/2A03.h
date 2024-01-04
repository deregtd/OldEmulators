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

#ifndef H2A03
#define H2A03

#include "NES_Controllers.h"
#include "NES_APU.h"
//#include "NES_Handlers.h"

struct c2A03 {
	public :
		c2A03();
		~c2A03()
		{
			delete APU;
		}
		void Reset();
		void NMI();
		void IRQ();

		void ExecOp();

		unsigned short PC;
		unsigned char A, X, Y, SP, P;

		unsigned char *RAM;

		cNES_APU *APU;

		int Clockticks;
		
		fReadHandler *ReadHandler[0x10];
		fWriteHandler *WriteHandler[0x10];
		
	private:
		void ErrorIns();
};

#endif
