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

#ifndef H68000
#define H68000

#define RT_ERROR		0
#define RT_PRG			1
#define RT_RAM			2
#define RT_MAPPER		3

#define WT_ERROR		0
#define WT_RAM			1
#define WT_MAPPER		2

class c68000 {
	public :
		c68000();
		~c68000()
		{
		}

		inline unsigned char MemGet(unsigned short Addy)
		{
			switch (RType[Addy])
			{
			case RT_PRG:
				return(PRG[Addy]);
			case RT_RAM:
				return(RAM[0]);
			default:
				return(0);
			}
			return(0);
		}
		inline void MemSet(unsigned short Addy, unsigned char Val)
		{
			switch (WType[Addy])
			{
			case WT_RAM:
				RAM[0] = Val;
				break;
			}
		}

		unsigned char RAM[0x1000];	//?
		
		void Reset();
		void NMI();
		void IRQ();

		void ExecOp();
		
		unsigned char PRG[0x10000];

		unsigned short PC;
		unsigned char A, X, Y, SP, P;

		unsigned char Op;

		int *Clockticks;

		char	RType[0x2000], WType[0x2000];

		char	MapperType;

	private :
		void ErrorIns();
};

#endif
