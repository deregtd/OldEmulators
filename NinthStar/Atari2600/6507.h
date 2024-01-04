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

#ifndef H6507
#define H6507

#include "A26_TIA.h"
#include "A26_PIA.h"

#define RT_ERROR		0
#define RT_PRG			1
#define RT_RAM			2
#define RT_MAPPER		3
#define RT_PIAREGISTER	4
#define RT_TIAREGISTER	5

#define WT_ERROR		0
#define WT_RAM			1
#define WT_MAPPER		2
#define WT_PIAREGISTER	3
#define WT_TIAREGISTER	4

#define MT_2k		1
#define MT_4k		2
#define MT_6k		3
#define MT_8kF8		4
#define MT_8kFE		5
#define MT_8kE0		6
#define MT_8k3F		7
#define MT_12k		8
#define MT_16kF6	9
#define MT_16kE7	10
#define MT_32k		11
#define MT_64k		12
#define Unk			13


class c6507 {
	public :
		c6507();
		~c6507()
		{
		}

		inline unsigned char MemGet(unsigned short Addy)
		{
			Addy &= 0x1FFF;
			int i;
			switch (RType[Addy])
			{
			case RT_PRG:
				return(PRG[PageNum[((Addy & 0xF00) >> 10)]][Addy & 0x3FF]);
			case RT_RAM:
				return(RAM[Addy & 0x7F]);
			case RT_PIAREGISTER:
				return(pPIA->ReadRegister(Addy));
			case RT_TIAREGISTER:
				return(pTIA->ReadRegister(Addy & 0xFF));
			case RT_MAPPER:
				switch (MapperType)
				{
				case MT_8kF8:
					switch (Addy)
					{
					case 0x1FF8:
						for (i=0;i<4;i++)
							PageNum[i] = i;
						break;
					case 0x1FF9:
						for (i=0;i<4;i++)
							PageNum[i] = 4 | i;
						break;
					}
					break;
				case MT_16kF6:
					switch (Addy)
					{
					case 0x1FF6:
						for (i=0;i<4;i++)
							PageNum[i] = i;
						break;
					case 0x1FF7:
						for (i=0;i<4;i++)
							PageNum[i] = 4 | i;
						break;
					case 0x1FF8:
						for (i=0;i<4;i++)
							PageNum[i] = 8 | i;
						break;
					case 0x1FF9:
						for (i=0;i<4;i++)
							PageNum[i] = 12 | i;
						break;
					}
					break;
				}
				return(PRG[PageNum[((Addy & 0xF00) >> 10)]][Addy & 0x3FF]);
			default:
				return(0);
			}
			return(0);
		}
		inline void MemSet(unsigned short Addy, unsigned char Val)
		{
			Addy &= 0x1FFF;
			int i;
			switch (WType[Addy])
			{
			case WT_RAM:
				RAM[Addy & 0x7F] = Val;
				break;
			case WT_PIAREGISTER:
				pPIA->WriteRegister(Addy, Val);
				break;
			case WT_TIAREGISTER:
				pTIA->WriteRegister(Addy & 0xFF, Val);
				break;
			case WT_MAPPER:
				switch (MapperType)
				{
				case MT_8kF8:
					switch (Addy)
					{
					case 0x1FF8:
						for (i=0;i<4;i++)
							PageNum[i] = i;
						break;
					case 0x1FF9:
						for (i=0;i<4;i++)
							PageNum[i] = 4 | i;
						break;
					}
					break;
				case MT_16kF6:
					switch (Addy)
					{
					case 0x1FF6:
						for (i=0;i<4;i++)
							PageNum[i] = i;
						break;
					case 0x1FF7:
						for (i=0;i<4;i++)
							PageNum[i] = 4 | i;
						break;
					case 0x1FF8:
						for (i=0;i<4;i++)
							PageNum[i] = 8 | i;
						break;
					case 0x1FF9:
						for (i=0;i<4;i++)
							PageNum[i] = 12 | i;
						break;
					}
					break;
				}
				break;
			}
		}

		unsigned char RAM[0x80];
		
		void Reset();
		void NMI();
		void IRQ();

		void ExecOp();
		
		char PageNum[4];
		unsigned char PRG[0x40][0x400];	//64 1k pages

		unsigned short PC:13;
		unsigned char A, X, Y, SP, P;

		unsigned char Op;

		int *Clockticks, *TicksToCount;

		cA26_TIA *pTIA;
		cA26_PIA *pPIA;

		char	RType[0x2000], WType[0x2000];

		char	MapperType;

	private :
		void ErrorIns();

		unsigned char BCD_LUT[256], BCD_LUT_R[256];
};

#endif
