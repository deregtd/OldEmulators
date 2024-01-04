//---------------------------------------------------------------------------
#include <math.h>
#include <mem.h>
#pragma hdrstop

#include "Defines.h"
#include "video.h"
//---------------------------------------------------------------------------
short int YMax;
const int arrmax = 61440, arrmax2 = 2*arrmax, arrmax3 = 3*arrmax;

extern int FPSnum;

//extern COLORREF BGCol;
extern bool BkPTA, SpPTA, BGVis, SprVis, SSize, SprClip, BGClip, CPURunning, Spr0Occ;
extern bool ScLnSprCnt, FakeSLUsing;
extern LBYTE NTabAdr, ScanLineFake;
extern MemSt Mem;
TMemo *StatusMemo,*TracerMemo;
bool TakeSnap;

extern MMC4St MMC4;
extern BYTE tmpBYTE;

//LBYTE SlAddr[4][512][512];
//LBYTE SlAddrC[4][512][512];
//BYTE SlAddrCS[512][512];
//---------------------------------------------------------------------------
HPALETTE SystemPal;
LOGPALETTE SystemLogPal;
//---------------------------------------------------------------------------
PALETTEENTRY SystemPalEntry[68] = {
	{0x7F,0x7F,0x7F},{0xFF,0x00,0x00},{0xBF,0x00,0x00},{0xBF,0x2B,0x47},
	{0x87,0x00,0x97},{0x23,0x00,0xAB},{0x00,0x13,0xAB},{0x00,0x17,0x8B},
	{0x00,0x30,0x53},{0x00,0x78,0x00},{0x00,0x6B,0x00},{0x00,0x5B,0x00},
	{0x58,0x43,0x00},{0x00,0x00,0x00},{0x00,0x00,0x00},{0x00,0x00,0x00},
	{0xBF,0xBF,0xBF},{0xF8,0x78,0x00},{0xF8,0x58,0x00},{0xFF,0x47,0x6B},
	{0xCD,0x00,0xDB},{0x5B,0x00,0xE7},{0x00,0x38,0xF8},{0x13,0x5F,0xE7},
	{0x00,0x7F,0xAF},{0x00,0xB8,0x00},{0x00,0xAB,0x00},{0x47,0xAB,0x00},
	{0x8B,0x8B,0x00},{0x00,0x00,0x00},{0x00,0x00,0x00},{0x00,0x00,0x00},
	{0xF8,0xF8,0xF8},{0xFF,0xBF,0x3F},{0xFF,0x88,0x6B},{0xF8,0x78,0x98},
	{0xF8,0x78,0xF8},{0x98,0x58,0xF8},{0x58,0x78,0xF8},{0x47,0xA3,0xFF},
	{0x00,0xB8,0xF8},{0x18,0xF8,0xB8},{0x57,0xDB,0x5B},{0x98,0xF8,0x58},
	{0xDB,0xEB,0x00},{0x78,0x78,0x78},{0x00,0x00,0x00},{0x00,0x00,0x00},
	{0xFF,0xFF,0xFF},{0xFF,0xE7,0xA7},{0xF8,0xB8,0xB8},{0xF8,0xB8,0xD8},
	{0xF8,0xB8,0xF8},{0xC3,0xA7,0xFB},{0xB0,0xD0,0xF0},{0xAB,0xE3,0xFF},
	{0x7B,0xDB,0xFB},{0x78,0xF8,0xD8},{0xB8,0xF8,0xB8},{0xD8,0xF8,0xB8},
	{0xFF,0xFF,0x00},{0xF8,0xD8,0xF8},{0x00,0x00,0x00},{0x00,0x00,0x00},

	{0,0,0},{255,0,0},{0,255,0},{0,0,255}
};
COLORREF Palette[68] = {
	0x7F7F7F, 0xFF0000, 0xBF0000, 0xBF2B47, 0x870097, 0x2300AB, 0x0013AB, 0x00178B,
	0x003053, 0x007800, 0x006B00, 0x005B00, 0x584300, 0x000000, 0x000000, 0x000000,
	0xBFBFBF, 0xF87800, 0xF85800, 0xFF476B, 0xCD00DB, 0x5B00E7, 0x0038F8, 0x135FE7,
	0x007FAF, 0x00B800, 0x00AB00, 0x47AB00, 0x8B8B00, 0x000000, 0x000000, 0x000000,
	0xF8F8F8, 0xFFBF3F, 0xFF886B, 0xF87898, 0xF878F8, 0x9858F8, 0x5878F8, 0x47A3FF,
	0x00B8F8, 0x18F8B8, 0x57DB5B, 0x98F858, 0xDBEB00, 0x787878, 0x000000, 0x000000,
	0xFFFFFF, 0xFFE7A7, 0xF8B8B8, 0xF8B8D8, 0xF8B8F8, 0xC3A7FB, 0xB0D0F0, 0xABE3FF,
	0x7BDBFB, 0x78F8D8, 0xB8F8B8, 0xD8F8B8, 0xFFFF00, 0xF8D8F8, 0x000000, 0x000000,

	cblack, cred, cgreen, cblue
};
unsigned char NearestPalEntry[68];
unsigned char bitnumsp[2][8] = {
	{ 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01 },
	{ 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 }
};
//---------------------------------------------------------------------------
int coldepth = 0;
unsigned char BMParray[983040];
TRect ScrRect;
HWND VWHWND, VWHWNDbig;
HDC VWHDC, VWHDCbig;
HDC MemHDC, MemHDCbig;
HBITMAP VWBMP, VWBMPbig;
TForm *VWFORM, *VWFORMbig;
//---------------------------------------------------------------------------
int frameskip = 1;
unsigned char curframe;
extern short int ScanLine;
unsigned char GraphicsEngine;
//---------------------------------------------------------------------------
void PrepTileline()
{
	curframe++;
	if (curframe < frameskip) return;

	if (coldepth == 4)
	{
		unsigned char BV = GetBValue(Palette[Mem.ImagePalette[0]]), GV = GetGValue(Palette[Mem.ImagePalette[0]]), RV = GetRValue(Palette[Mem.ImagePalette[0]]);
		for (int i=0;i<983040;i+=4)
		{
			BMParray[i] = BV;
			BMParray[i+1] = GV;
			BMParray[i+2] = RV;
			BMParray[i+3] = 0;
		}
	} else if (coldepth == 3) {
		unsigned char BV = GetBValue(Palette[Mem.ImagePalette[0]]), GV = GetGValue(Palette[Mem.ImagePalette[0]]), RV = GetRValue(Palette[Mem.ImagePalette[0]]);
		for (int i=0;i<737280;i+=3)
		{
			BMParray[i] = BV;
			BMParray[i+1] = GV;
			BMParray[i+2] = RV;
		}
	} else if (coldepth == 2) {
		unsigned char V1 = (BYTE) (((BYTE) (GetBValue(Palette[Mem.ImagePalette[0]])/8))+(((BYTE) (GetGValue(Palette[Mem.ImagePalette[0]])/4)) << 5));
		   unsigned char V2 = (BYTE) ((((BYTE) (GetGValue(Palette[Mem.ImagePalette[0]])/4))>>3)+(((BYTE) (GetRValue(Palette[Mem.ImagePalette[0]])/8))<<3));
		for (int i=0;i<491520;i+=2)
		{
			BMParray[i] = V1;
			BMParray[i+1] = V2;
		}
	} else if (coldepth == 1) {
//		setmem(&BMParray[0],245760,Mem.ImagePalette[0]);
		setmem(&BMParray[0],245760,NearestPalEntry[Mem.ImagePalette[0]]);
	}

	if (GraphicsEngine == 1)
	{
		if (SprVis)
		{
			if (SSize)
			{
				for (int spr=252;spr>=0;spr-=4)
				{
					if (bit5(Mem.Sprite[spr+2]))
					{
						drawspritebasic(Mem.Sprite[spr + 3], Mem.Sprite[spr] + 1, (BYTE) (Mem.Sprite[spr + 2] & 3), (LBYTE) ((SpPTA << 12) | (Mem.Sprite[spr + 1] << 4)-0x10), bit7(Mem.Sprite[spr + 2]), bit6(Mem.Sprite[spr + 2]));
						drawspritebasic(Mem.Sprite[spr + 3], Mem.Sprite[spr] + 9, (BYTE) (Mem.Sprite[spr + 2] & 3), (LBYTE) ((SpPTA << 12) | (Mem.Sprite[spr + 1] << 4)), bit7(Mem.Sprite[spr + 2]), bit6(Mem.Sprite[spr + 2]));
					}
				}
			} else {
				for (int spr=252;spr>=0;spr-=4)
					if (bit5(Mem.Sprite[spr+2]))
						drawspritebasic(Mem.Sprite[spr + 3], Mem.Sprite[spr] + 1, (BYTE) (Mem.Sprite[spr + 2] & 3), (LBYTE) ((SpPTA << 12) | (Mem.Sprite[spr + 1] << 4)), bit7(Mem.Sprite[spr + 2]), bit6(Mem.Sprite[spr + 2]));
			}
		}
	}
}

void DrawTileline()
{
	if (curframe < frameskip) return;

	if (BGVis)
	{
		unsigned char ColBk;
		short int y = (short int) ((((ScanLine >> 5) & 7) << 5));
		BYTE yy = (short int) ((ScanLine >> 3) & 3);;
		for (short int x=0;x<8;x++)
		{
			ColBk = *Mem.PPU[NTabAdr + 0x3C0 + (y >> 2) + x];
			for (BYTE xx=0;xx<4;xx++)
			{
				drawbacktilebasic((x << 5) + (xx << 3),y + (yy << 3),(BYTE) ((ColBk >> ((bit1(xx) + (yy & 2)) << 1)) & 3),(LBYTE) (*Mem.PPU[NTabAdr + ((y << 2) + (yy << 5)) + ((x << 2) + xx)] << 4));
			}
		}
	}
}

void FinishTileline()
{
	if (curframe < frameskip) return;
	curframe = 0;

	if (GraphicsEngine == 1)
	{
		if (SprVis)
		{
			if (SSize)
			{
				for (int spr=252;spr>=0;spr-=4)
				{
					if (!bit5(Mem.Sprite[spr+2]))
					{
						drawspritebasic(Mem.Sprite[spr + 3], Mem.Sprite[spr] + 1, (BYTE) (Mem.Sprite[spr + 2] & 3), (LBYTE) ((SpPTA << 12) | (Mem.Sprite[spr + 1] << 4)-0x10), bit7(Mem.Sprite[spr + 2]), bit6(Mem.Sprite[spr + 2]));
						drawspritebasic(Mem.Sprite[spr + 3], Mem.Sprite[spr] + 9, (BYTE) (Mem.Sprite[spr + 2] & 3), (LBYTE) ((SpPTA << 12) | (Mem.Sprite[spr + 1] << 4)), bit7(Mem.Sprite[spr + 2]), bit6(Mem.Sprite[spr + 2]));
					}
				}
			} else {
				for (int spr=252;spr>=0;spr-=4)
					if (!bit5(Mem.Sprite[spr+2]))
						drawspritebasic(Mem.Sprite[spr + 3], Mem.Sprite[spr] + 1, (BYTE) (Mem.Sprite[spr + 2] & 3), (LBYTE) ((SpPTA << 12) | (Mem.Sprite[spr + 1] << 4)), bit7(Mem.Sprite[spr + 2]), bit6(Mem.Sprite[spr + 2]));
			}
		}
	}
	if (GraphicsEngine == 2)
	{
		SetBitmapBits(VWBMP,arrmax*coldepth,&BMParray);
		SelectObject(MemHDC,VWBMP);
		BitBlt(VWHDC,0,8-((YMax-224) >> 1),256,YMax,MemHDC,0,0,SRCCOPY);

		if (TakeSnap)
		{
			BYTE header[2][54] = {
				{
					0x42, 0x4D, 0x36, 0xD0, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00, 0x00, 0x28, 0x00,
					0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x01, 0x00, 0x18, 0x00, 0x00, 0x00,
					0x00, 0x00, 0x00, 0xD0, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
					0x00, 0x00, 0x00, 0x00, 0x00, 0x00
				},
				{
					0x42, 0x4D, 0x36, 0xD0, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00, 0x00, 0x28, 0x00,
					0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0x01, 0x00, 0x18, 0x00, 0x00, 0x00,
					0x00, 0x00, 0x00, 0xD0, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
					0x00, 0x00, 0x00, 0x00, 0x00, 0x00
				}
			};

			if (coldepth == 3)
			{
				FILE * snap = fopen("snapshot.bmp","wb");

				if (YMax == 240) fwrite(&header[0][0], 1, 54, snap); else fwrite(&header[1][0], 1, 54, snap);

				for (int i=768*YMax + (8-((YMax-224) >> 1))*768;i>(8-((YMax-224) >> 1))*768;i-=768)
					fwrite(&BMParray[i], 1, 768, snap);

				fclose(snap);
			} else if (coldepth == 1) {
				PALETTEENTRY tmpst[256];
				GetSystemPaletteEntries(MemHDC,0,256,&tmpst[0]);

				FILE * snap = fopen("snapshot.bmp","wb");

				if (YMax == 240) fwrite(&header[0][0], 1, 54, snap); else fwrite(&header[1][0], 1, 54, snap);

				for (int i=256*YMax + (8-((YMax-224) >> 1))*256;i>(8-((YMax-224) >> 1))*256;i-=256)
				{
					for (int h=0;h<256;h++)
					{
						fwrite(&tmpst[BMParray[i+h]].peBlue, 1, 1, snap);
						fwrite(&tmpst[BMParray[i+h]].peGreen, 1, 1, snap);
						fwrite(&tmpst[BMParray[i+h]].peRed, 1, 1, snap);
					}
				}

				fclose(snap);
			} else {
				Application->MessageBox("Screenshots can only be taken in 8-bit or 24-bit color!", "NES4PC Error", MB_OK);
			}

			TakeSnap = false;
		}
	} else if (GraphicsEngine == 1) {
		render();
	}
}

void DrawScanline()
{
	if (curframe < frameskip) return;

	register short int addr;
	unsigned char SSizeNew = (BYTE) ((SSize << 3) + 1);
	unsigned char SprNum = 0;

	if (!FakeSLUsing) ScanLineFake = ScanLine;

	if (SprVis)
	{
		for (short int spr=252;spr>=0;spr-=(BYTE) 4)
		{
			if ((bit5(Mem.Sprite[spr+2])) && (Mem.Sprite[spr] - 7 <= ScanLineFake) && (Mem.Sprite[spr] + SSizeNew > ScanLineFake))
			{
				SprNum++;
				if (SSize)
				{
					bool hflip = bit6(Mem.Sprite[spr+2]);
					char ydiff = (BYTE) (ScanLineFake - (Mem.Sprite[spr] - 7));

					if (bit7(Mem.Sprite[spr+2]))
					{
						if (bit3(ydiff))
						{
							addr = (short int) ((Mem.Sprite[spr+1] & 0xFE) << 4);
						} else {
							addr = (short int) (((Mem.Sprite[spr+1] & 0xFE) + 1) << 4);
						}
						addr |= (LBYTE) (7 - (ydiff & 0x7));
					} else {
						if (bit3(ydiff))
						{
							addr = (short int) (((Mem.Sprite[spr+1] & 0xFE) + 1) << 4);
						} else {
							addr = (short int) ((Mem.Sprite[spr+1] & 0xFE) << 4);
						}
						addr |= (BYTE) (ydiff & 0x7);
					}

				if (Mem.MapperNum == 9)
				{
					tmpBYTE = (BYTE) (addr >> 4);
					if ((tmpBYTE == 0xFD) || (tmpBYTE == 0xFE))
					{
						MMC4.Latch[BkPTA] = tmpBYTE;
//						tprinto(AnsiString("Latch ")+AnsiString(BkPTA) + AnsiString(" = ") + IntToHex(tmpBYTE,2));
					}
				}

					for (unsigned char xx=0;xx<8;xx++)
					{
						unsigned char col = (BYTE) (((bool) (Mem.PatternTable[bit0(Mem.Sprite[spr+1])][addr | 8] & bitnumsp[hflip][xx]) << 1) | (bool) (Mem.PatternTable[bit0(Mem.Sprite[spr+1])][addr] & bitnumsp[hflip][xx]));
						if (col)
							pset((short int) (Mem.Sprite[spr+3] + xx),ScanLine,Mem.SpritePalette[((Mem.Sprite[spr+2] & 3) << 2) | col]);
					}
				} else {
					bool hflip = bit6(Mem.Sprite[spr+2]);
					char ydiff = (BYTE) (ScanLineFake - (Mem.Sprite[spr] - 7));
					addr = (short int) (Mem.Sprite[spr+1] << 4);
					if (bit7(Mem.Sprite[spr+2])) addr |= (LBYTE) (7 - (ydiff & 0x7));
						else addr |= (BYTE) (ydiff & 0x7);

				if (Mem.MapperNum == 9)
				{
					tmpBYTE = (BYTE) (addr >> 4);
					if ((tmpBYTE == 0xFD) || (tmpBYTE == 0xFE))
					{
						MMC4.Latch[BkPTA] = tmpBYTE;
//						tprinto(AnsiString("Latch ")+AnsiString(BkPTA) + AnsiString(" = ") + IntToHex(tmpBYTE,2));
					}
				}

					for (unsigned char xx=0;xx<8;xx++)
					{
						unsigned char col = (BYTE) (((bool) (Mem.PatternTable[SpPTA][addr | 8] & bitnumsp[hflip][xx]) << 1) | (bool) (Mem.PatternTable[SpPTA][addr] & bitnumsp[hflip][xx]));
						if (col)
							pset((short int) (Mem.Sprite[spr+3] + xx),ScanLine,Mem.SpritePalette[((Mem.Sprite[spr+2] & 3) << 2) | col]);
					}
				}
				if (SprNum == 8) spr = -4;
			}
		}
	}
	if (BGVis)
	{
		register unsigned char TileX;
		short int SLTmp = (short int) (ScanLineFake + Mem.BgScrollY);
		register unsigned char TileY = (BYTE) ((SLTmp >> 3) + 1);
		unsigned char NTY = (BYTE) (((bool) (TileY >= 30) ^ (bool) (NTabAdr & 0x800)) << 1);

		unsigned char TileYM30 = (BYTE) (TileY % 30);
		unsigned char TileYDiff = (BYTE) (SLTmp & 7);

		bool NTabAdrBl = (bool) (NTabAdr & 0x400);
		unsigned char SLHead = (BYTE) (Mem.BgScrollX & 0xF8);

		if (SLHead < Mem.BgScrollX)
		{
			unsigned short int SLFoot = (LBYTE) ((Mem.BgScrollX + 256) & 0x1F8);
			for (short int x=Mem.BgScrollX;x<(SLHead + 8);x++)
			{
				TileX = (BYTE) (x >> 3);
				short int NameTable = (LBYTE) (((NTY | (bit5(TileX) ^ NTabAdrBl)) << 10) | 0x2000);
				addr = (short int) ((*Mem.PPU[NameTable | (TileYM30 << 5) | (TileX & 0x1F)] << 4) | TileYDiff);

				if (Mem.MapperNum == 9)
				{
					tmpBYTE = (BYTE) (addr >> 4);
					if ((tmpBYTE == 0xFD) || (tmpBYTE == 0xFE))
					{
						MMC4.Latch[BkPTA] = tmpBYTE;
//						tprinto(AnsiString("Latch ")+AnsiString(BkPTA) + AnsiString(" = ") + IntToHex(tmpBYTE,2));
					}
				}

				unsigned char bitnum = bitnumsp[0][x & 7];
				unsigned char col = (BYTE) (((bool) (Mem.PatternTable[BkPTA][addr | 8] & bitnum) << 1) | (bool) (Mem.PatternTable[BkPTA][addr] & bitnum));
				if (col)
					pset((short int) (x - Mem.BgScrollX),ScanLine,Mem.ImagePalette[(((*Mem.PPU[0x3C0 | NameTable | ((TileYM30 & 0x1C) << 1) | ((TileX & 0x1F) >> 2)] >> ((bit1(TileX) + (TileYM30 & 2)) << 1)) & 3) << 2) | col]);
			}

			for (short int x=(LBYTE) (SLHead+8);x<SLFoot;x+=(BYTE) 8)
			{
				TileX = (BYTE) (x >> 3);
				short int NameTable = (LBYTE) (((NTY | (bit5(TileX) ^ NTabAdrBl)) << 10) | 0x2000);
				addr = (short int) ((*Mem.PPU[NameTable | (TileYM30 << 5) | (TileX & 0x1F)] << 4) | TileYDiff);

				if (Mem.MapperNum == 9)
				{
					tmpBYTE = (BYTE) (addr >> 4);
					if ((tmpBYTE == 0xFD) || (tmpBYTE == 0xFE))
					{
						MMC4.Latch[BkPTA] = tmpBYTE;
//						tprinto(AnsiString("Latch ")+AnsiString(BkPTA) + AnsiString(" = ") + IntToHex(tmpBYTE,2));
					}
				}

				for (unsigned char xx=0;xx<8;xx++)
				{
					unsigned char bitnum = (BYTE) (0x80 >> xx);
					unsigned char col = (BYTE) (((bool) (Mem.PatternTable[BkPTA][addr | 8] & bitnum) << 1) | (bool) (Mem.PatternTable[BkPTA][addr] & bitnum));
					if (col)
						pset((short int) (x + xx - Mem.BgScrollX),ScanLine,Mem.ImagePalette[(((*Mem.PPU[0x3C0 | NameTable | ((TileYM30 & 0x1C) << 1) | ((TileX & 0x1F) >> 2)] >> ((bit1(TileX) + (TileYM30 & 2)) << 1)) & 3) << 2) | col]);
				}
			}

			for (short int x=SLFoot;x<Mem.BgScrollX + 256;x++)
			{
				TileX = (BYTE) (x >> 3);
				short int NameTable = (LBYTE) (((NTY | (bit5(TileX) ^ NTabAdrBl)) << 10) | 0x2000);
				addr = (short int) ((*Mem.PPU[NameTable | (TileYM30 << 5) | (TileX & 0x1F)] << 4) | TileYDiff);

				if (Mem.MapperNum == 9)
				{
					tmpBYTE = (BYTE) (addr >> 4);
					if ((tmpBYTE == 0xFD) || (tmpBYTE == 0xFE))
					{
						MMC4.Latch[BkPTA] = tmpBYTE;
//						tprinto(AnsiString("Latch ")+AnsiString(BkPTA) + AnsiString(" = ") + IntToHex(tmpBYTE,2));
					}
				}

				unsigned char bitnum = bitnumsp[0][x & 7];
				unsigned char col = (BYTE) (((bool) (Mem.PatternTable[BkPTA][addr | 8] & bitnum) << 1) | (bool) (Mem.PatternTable[BkPTA][addr] & bitnum));
				if (col)
					pset((short int) (x - Mem.BgScrollX),ScanLine,Mem.ImagePalette[(((*Mem.PPU[0x3C0 | NameTable | ((TileYM30 & 0x1C) << 1) | ((TileX & 0x1F) >> 2)] >> ((bit1(TileX) + (TileYM30 & 2)) << 1)) & 3) << 2) | col]);
			}
		} else {

			for (short int x=Mem.BgScrollX;x<Mem.BgScrollX + 256;x+=(BYTE) 8)
			{
				TileX = (BYTE) (x >> 3);
				short int NameTable = (LBYTE) (((NTY | (bit5(TileX) ^ NTabAdrBl)) << 10) | 0x2000);
				addr = (short int) ((*Mem.PPU[NameTable | (TileYM30 << 5) | (TileX & 0x1F)] << 4) | TileYDiff);

				if (Mem.MapperNum == 9)
				{
					tmpBYTE = (BYTE) (addr >> 4);
					if ((tmpBYTE == 0xFD) || (tmpBYTE == 0xFE))
					{
						MMC4.Latch[BkPTA] = tmpBYTE;
//						tprinto(AnsiString("Latch ")+AnsiString(BkPTA) + AnsiString(" = ") + IntToHex(tmpBYTE,2));
					}
				}

				for (unsigned char xx=0;xx<8;xx++)
				{
					unsigned char bitnum = bitnumsp[0][xx];
					unsigned char col = (BYTE) (((bool) (Mem.PatternTable[BkPTA][addr | 8] & bitnum) << 1) | (bool) (Mem.PatternTable[BkPTA][addr] & bitnum));
					if (col)
						pset((short int) (x + xx - Mem.BgScrollX),ScanLine,Mem.ImagePalette[(((*Mem.PPU[0x3C0 | NameTable | ((TileYM30 & 0x1C) << 1) | ((TileX & 0x1F) >> 2)] >> ((bit1(TileX) + (TileYM30 & 2)) << 1)) & 3) << 2) | col]);
				}
			}
		}
//		register unsigned char NTabN = (BYTE) (((BYTE) (NTabAdr >> 10)) & 3);
//		short int SLTmp = (short int) (ScanLine + Mem.BgScrollY);
//		unsigned char TileYDiff = (BYTE) (SLTmp & 7);
//		for (short int x=Mem.BgScrollX;x<(Mem.BgScrollX | 0x100);x++)
//		{
//			addr = (short int) ((*Mem.PPU[SlAddr[NTabN][x][SLTmp]] << 4) | TileYDiff);
//			unsigned char bitnum = bitnumsp[0][x & 7];
//			unsigned char col = (BYTE) (((bool) (Mem.PatternTable[BkPTA][addr | 8] & bitnum) << 1) | (bool) (Mem.PatternTable[BkPTA][addr] & bitnum));
//			if (col)
//				pset((short int) (x - Mem.BgScrollX),ScanLine,Mem.ImagePalette[(((*Mem.PPU[SlAddrC[NTabN][x][SLTmp]] >> SlAddrCS[x][SLTmp]) & 3) << 2) | col]);
//		}
	}
	if ((SprVis) && (SprNum < 8))
	{
		for (short int spr=252;spr>=0;spr-=(BYTE) 4)
		{
			if ((!bit5(Mem.Sprite[spr+2])) && (Mem.Sprite[spr] - 7 <= ScanLineFake) && (Mem.Sprite[spr] + SSizeNew > ScanLineFake))
			{
				SprNum++;
				if (SSize)
				{
					bool hflip = bit6(Mem.Sprite[spr+2]);
					char ydiff = (BYTE) (ScanLineFake - (Mem.Sprite[spr] - 7));

					if (bit7(Mem.Sprite[spr+2]))
					{
						if (bit3(ydiff))
						{
							addr = (short int) ((Mem.Sprite[spr+1] & 0xFE) << 4);
						} else {
							addr = (short int) (((Mem.Sprite[spr+1] & 0xFE) + 1) << 4);
						}
						addr |= (LBYTE) (7 - (ydiff & 0x7));
					} else {
						if (bit3(ydiff))
						{
							addr = (short int) (((Mem.Sprite[spr+1] & 0xFE) + 1) << 4);
						} else {
							addr = (short int) ((Mem.Sprite[spr+1] & 0xFE) << 4);
						}
						addr |= (BYTE) (ydiff & 0x7);
					}

				if (Mem.MapperNum == 9)
				{
					tmpBYTE = (BYTE) (addr >> 4);
					if ((tmpBYTE == 0xFD) || (tmpBYTE == 0xFE))
					{
						MMC4.Latch[BkPTA] = tmpBYTE;
//						tprinto(AnsiString("Latch ")+AnsiString(BkPTA) + AnsiString(" = ") + IntToHex(tmpBYTE,2));
					}
				}

					for (unsigned char xx=0;xx<8;xx++)
					{
						unsigned char col = (BYTE) (((bool) (Mem.PatternTable[bit0(Mem.Sprite[spr+1])][addr | 8] & bitnumsp[hflip][xx]) << 1) | (bool) (Mem.PatternTable[bit0(Mem.Sprite[spr+1])][addr] & bitnumsp[hflip][xx]));
						if (col)
							pset((short int) (Mem.Sprite[spr+3] + xx),ScanLine,Mem.SpritePalette[((Mem.Sprite[spr+2] & 3) << 2) | col]);
					}
				} else {
					bool hflip = bit6(Mem.Sprite[spr+2]);
					char ydiff = (BYTE) (ScanLineFake - (Mem.Sprite[spr] - 7));
					addr = (short int) (Mem.Sprite[spr+1] << 4);
					if (bit7(Mem.Sprite[spr+2])) addr |= (LBYTE) (7 - (ydiff & 0x7));
						else addr |= (BYTE) (ydiff & 0x7);

				if (Mem.MapperNum == 9)
				{
					tmpBYTE = (BYTE) (addr >> 4);
					if ((tmpBYTE == 0xFD) || (tmpBYTE == 0xFE))
					{
						MMC4.Latch[BkPTA] = tmpBYTE;
//						tprinto(AnsiString("Latch ")+AnsiString(BkPTA) + AnsiString(" = ") + IntToHex(tmpBYTE,2));
					}
				}

					for (unsigned char xx=0;xx<8;xx++)
					{
						unsigned char col = (BYTE) (((bool) (Mem.PatternTable[SpPTA][addr | 8] & bitnumsp[hflip][xx]) << 1) | (bool) (Mem.PatternTable[SpPTA][addr] & bitnumsp[hflip][xx]));
						if (col)
							pset((short int) (Mem.Sprite[spr+3] + xx),ScanLine,Mem.SpritePalette[((Mem.Sprite[spr+2] & 3) << 2) | col]);
					}
				}
				if (SprNum == 8) spr = -4;
			}
		}
	}
	ScLnSprCnt = (SprNum >= 8);
}

void __fastcall DrawScreen()
{
	curframe++;
	if (curframe < frameskip) return;
	curframe = 0;

	if (coldepth == 4)
	{
		unsigned char BV = GetBValue(Palette[Mem.ImagePalette[0]]), GV = GetGValue(Palette[Mem.ImagePalette[0]]), RV = GetRValue(Palette[Mem.ImagePalette[0]]);
		for (int i=0;i<983040;i+=4)
		{
			BMParray[i] = BV;
			BMParray[i+1] = GV;
			BMParray[i+2] = RV;
			BMParray[i+3] = 0;
		}
	} else if (coldepth == 3) {
		unsigned char BV = GetBValue(Palette[Mem.ImagePalette[0]]), GV = GetGValue(Palette[Mem.ImagePalette[0]]), RV = GetRValue(Palette[Mem.ImagePalette[0]]);
		for (int i=0;i<737280;i+=3)
		{
			BMParray[i] = BV;
			BMParray[i+1] = GV;
			BMParray[i+2] = RV;
		}
	} else if (coldepth == 2) {
		unsigned char V1 = (BYTE) (((BYTE) (GetBValue(Palette[Mem.ImagePalette[0]])/8))+(((BYTE) (GetGValue(Palette[Mem.ImagePalette[0]])/4)) << 5));
		   unsigned char V2 = (BYTE) ((((BYTE) (GetGValue(Palette[Mem.ImagePalette[0]])/4))>>3)+(((BYTE) (GetRValue(Palette[Mem.ImagePalette[0]])/8))<<3));
		for (int i=0;i<491520;i+=2)
		{
			BMParray[i] = V1;
			BMParray[i+1] = V2;
		}
	} else if (coldepth == 1) {
		setmem(&BMParray[0],245760,NearestPalEntry[Mem.ImagePalette[0]]);
	}

	unsigned char ColBk;

	if (SprVis)
	{
		if (SSize)
        {
			for (int spr=252;spr>=0;spr-=4)
			{
				if (bit5(Mem.Sprite[spr+2]))
				{
					drawspritebasic(Mem.Sprite[spr + 3], Mem.Sprite[spr] + 1, (BYTE) (Mem.Sprite[spr + 2] & 3), (LBYTE) ((SpPTA << 12) | (Mem.Sprite[spr + 1] << 4)-0x10), bit7(Mem.Sprite[spr + 2]), bit6(Mem.Sprite[spr + 2]));
					drawspritebasic(Mem.Sprite[spr + 3], Mem.Sprite[spr] + 9, (BYTE) (Mem.Sprite[spr + 2] & 3), (LBYTE) ((SpPTA << 12) | (Mem.Sprite[spr + 1] << 4)), bit7(Mem.Sprite[spr + 2]), bit6(Mem.Sprite[spr + 2]));
				}
			}
		} else {
			for (int spr=252;spr>=0;spr-=4)
				if (bit5(Mem.Sprite[spr+2]))
					drawspritebasic(Mem.Sprite[spr + 3], Mem.Sprite[spr] + 1, (BYTE) (Mem.Sprite[spr + 2] & 3), (LBYTE) ((SpPTA << 12) | (Mem.Sprite[spr + 1] << 4)), bit7(Mem.Sprite[spr + 2]), bit6(Mem.Sprite[spr + 2]));
		}
	}

	if (BGVis)
	{
		for (short int x=0;x<8;x++)
		{
			for (short int y=0;y<8;y++)
			{
				ColBk = *Mem.PPU[NTabAdr + 0x3C0 + (y << 3) + x];
				for (BYTE xx=0;xx<4;xx++)
					for (BYTE yy=0;yy<4;yy++)
						if ((y < 7) || (yy < 2)) drawbacktilebasic((x << 5) + (xx << 3),(y << 5) + (yy << 3),(BYTE) ((ColBk >> ((bit1(xx) + (yy & 2)) << 1)) & 3),(LBYTE) (*Mem.PPU[NTabAdr + ((y << 7) + (yy << 5)) + ((x << 2) + xx)] << 4));
			}
		}

		if (Mem.BgScrollX != 0) {
			for (short int x=0;x<8;x++)
			{
				for (short int y=0;y<8;y++)
				{
					ColBk = *Mem.PPU[0x2000 | ((NTabAdr + 0x7C0) & 0xFFF) + (y << 3) + x];

					for (BYTE xx=0;xx<4;xx++)
						for (BYTE yy=0;yy<4;yy++)
							if ((y < 7) || (yy < 2)) drawbacktilebasic(256 + (x << 5) + (xx << 3),(y << 5) + (yy << 3),(BYTE) ((ColBk >> ((bit1(xx) + (yy & 2)) << 1)) & 3),(LBYTE) (*Mem.PPU[(NTabAdr ^ 0x400) + ((y << 7) + (yy << 5)) + ((x << 2) + xx)] << 4));
				}
			}
		}

		if (Mem.BgScrollY != 0) {
			for (short int x=0;x<8;x++)
			{
				for (short int y=0;y<8;y++)
				{
					ColBk = *Mem.PPU[0x2000 | ((NTabAdr + 0xCC0) & 0xFFF) + (y << 3) + x];

					for (BYTE xx=0;xx<4;xx++)
						for (BYTE yy=0;yy<4;yy++)
							drawbacktilebasic((x << 5) + (xx << 3),YMax + (y << 5) + (yy << 3),(BYTE) ((ColBk >> ((bit1(xx) + (yy & 2)) << 1)) & 3),(LBYTE) (*Mem.PPU[(NTabAdr ^ 0x800) + ((y << 7) + (yy << 5)) + ((x << 2) + xx)] << 4));
				}
			}
        }

		if ((Mem.BgScrollX != 0) && (Mem.BgScrollY != 0)) {
			for (short int x=0;x<8;x++)
			{
				for (short int y=0;y<8;y++)
				{
					ColBk = *Mem.PPU[0x2000 | ((NTabAdr + 0xFC0) & 0xFFF) + (y << 3) + x];

					for (BYTE xx=0;xx<4;xx++)
						for (BYTE yy=0;yy<4;yy++)
							drawbacktilebasic(256 + (x << 5) + (xx << 3),YMax + (y << 5) + (yy << 3),(BYTE) ((ColBk >> ((bit1(xx) + (yy & 2)) << 1)) & 3),(LBYTE) (*Mem.PPU[(NTabAdr ^ 0xC00) + ((y << 7) + (yy << 5)) + ((x << 2) + xx)] << 4));
				}
			}
        }
	}

	if (SprVis)
	{
		if (SSize)
        {
			for (int spr=252;spr>=0;spr-=4)
			{
				if (!bit5(Mem.Sprite[spr+2]))
				{
					drawspritebasic(Mem.Sprite[spr + 3], Mem.Sprite[spr] + 1, (BYTE) (Mem.Sprite[spr + 2] & 3), (LBYTE) ((SpPTA << 12) | (Mem.Sprite[spr + 1] << 4)-0x10), bit7(Mem.Sprite[spr + 2]), bit6(Mem.Sprite[spr + 2]));
					drawspritebasic(Mem.Sprite[spr + 3], Mem.Sprite[spr] + 9, (BYTE) (Mem.Sprite[spr + 2] & 3), (LBYTE) ((SpPTA << 12) | (Mem.Sprite[spr + 1] << 4)), bit7(Mem.Sprite[spr + 2]), bit6(Mem.Sprite[spr + 2]));
				}
			}
		} else {
			for (int spr=252;spr>=0;spr-=4)
				if (!bit5(Mem.Sprite[spr+2]))
					drawspritebasic(Mem.Sprite[spr + 3], Mem.Sprite[spr] + 1, (BYTE) (Mem.Sprite[spr + 2] & 3), (LBYTE) ((SpPTA << 12) | (Mem.Sprite[spr + 1] << 4)), bit7(Mem.Sprite[spr + 2]), bit6(Mem.Sprite[spr + 2]));
		}
	}

	render();
}

void __fastcall drawspritebasic(int x,int y,unsigned char ColUp,unsigned short int address, bool vflip, bool hflip)
{
	x += 7;
	if (GraphicsEngine == 2) {
		if ((!SprClip) && (x < 15)) return;
	} else {
		if ((!SprClip) && (x < Mem.BgScrollX + 1)) return;
	}
	y -= 8;

	ColUp <<= 2;

	unsigned char col;

	if (vflip) {
		for(char i=0;i<8;i++)
		{
			if (hflip)
			{
				for (unsigned char h=0;h<8;h++)
				{
					col = (BYTE) (bit(Mem.PatternTable[(bool) (address & 0x1000)][(address & 0xfff)+i], h) + (bit(Mem.PatternTable[(bool) (address & 0x1000)][(address & 0xfff)+i+8], h) << 1));
					if (col)
						pset((short int) (x-7+h),(short int) (y+7-i),*Mem.PPU[0x3F10 | (ColUp + col)]);
				}
			} else {
				for (unsigned char h=0;h<8;h++)
				{
					col = (BYTE) (bit(Mem.PatternTable[(bool) (address & 0x1000)][(address & 0xfff)+i], h) + (bit(Mem.PatternTable[(bool) (address & 0x1000)][(address & 0xfff)+i+8], h) << 1));
					if (col)
						pset((short int) (x-h),(short int) (y+7-i),*Mem.PPU[0x3F10 | (ColUp + col)]);
				}
			}
		}
	} else {
		for(unsigned char i=0;i<8;i++)
		{
			if (hflip)
			{
				for (unsigned char h=0;h<8;h++)
				{
					col = (BYTE) (bit(Mem.PatternTable[(bool) (address & 0x1000)][(address & 0xfff)+i], h) + (bit(Mem.PatternTable[(bool) (address & 0x1000)][(address & 0xfff)+i+8], h) << 1));
					if (col)
						pset((short int) (x-7+h),(short int) (y+i),*Mem.PPU[0x3F10 | (ColUp + col)]);
				}
			} else {
				for (unsigned char h=0;h<8;h++)
				{
					col = (BYTE) (bit(Mem.PatternTable[(bool) (address & 0x1000)][(address & 0xfff)+i], h) + (bit(Mem.PatternTable[(bool) (address & 0x1000)][(address & 0xfff)+i+8], h) << 1));
					if (col)
						pset((short int) (x-h),(short int) (y+i),*Mem.PPU[0x3F10 | (ColUp + col)]);
				}
			}
		}
	}
}

void __fastcall drawbacktilebasic(int x,int y,unsigned char ColUp,unsigned short int address)
{
	if ((!BGClip) && (x - Mem.BgScrollX < 8)) return;
	unsigned char col;
	x += 7; y -= 8; ColUp <<= 2;
	for(unsigned char i=0;i<8;i++) {
		for (unsigned char h=0;h<8;h++) {
			col = (BYTE) (bit(Mem.PatternTable[BkPTA][address+i], h) + (bit(Mem.PatternTable[BkPTA][address+i+8], h) << 1));
			if (col) pset((short int) (x-h),(short int) (y+i),*Mem.PPU[0x3F00 | (ColUp + col)]);
	}	}
}

void __fastcall render()
{
	short int tx, ty;
	if ((Mem.BgScrollX == 0) && (Mem.BgScrollY == 0))
	{
		SetBitmapBits(VWBMP,arrmax*coldepth,&BMParray);
		SelectObject(MemHDC,VWBMP);
		tx = 0; ty = 0;
	} else if ((Mem.BgScrollX != 0) && (Mem.BgScrollY == 0)) {
		SetBitmapBits(VWBMPbig,arrmax2*coldepth,&BMParray);
		SelectObject(MemHDC,VWBMPbig);
		tx = Mem.BgScrollX; ty = 0;
	} else if ((Mem.BgScrollX == 0) && (Mem.BgScrollY != 0)) {
		SetBitmapBits(VWBMPbig,(arrmax2 << 1)*coldepth,&BMParray);
		SelectObject(MemHDC,VWBMPbig);
		tx = 0; ty = Mem.BgScrollY;
	} else if ((Mem.BgScrollX != 0) && (Mem.BgScrollY != 0)) {
		SetBitmapBits(VWBMPbig,(arrmax2 << 1)*coldepth,&BMParray);
		SelectObject(MemHDC,VWBMPbig);
		tx = Mem.BgScrollX; ty = Mem.BgScrollY;
	}
	BitBlt(VWHDC,0,8-((YMax-224) >> 1),256,YMax,MemHDC,tx,ty,SRCCOPY);
}

void __fastcall renderbig()
{
	SetBitmapBits(VWBMP,40960*coldepth,&BMParray);
	SelectObject(MemHDC,VWBMP);
	BitBlt(VWHDC,456,244,256,160,MemHDC,0,0,SRCCOPY);
}

void __fastcall renderbig2()
{
	SetBitmapBits(VWBMPbig,245760*coldepth,&BMParray);
	SelectObject(MemHDC,VWBMPbig);
	BitBlt(VWHDCbig,0,0,512,480,MemHDC,0,0,SRCCOPY);
}

void __fastcall clscreen()
{
	if ((Mem.BgScrollX == 0) && (Mem.BgScrollY == 0))
	{
		setmem(&BMParray[0],arrmax*coldepth,0);
	} else if ((Mem.BgScrollX != 0) && (Mem.BgScrollY == 0)) {
		setmem(&BMParray[0],arrmax2*coldepth,0);
	} else if ((Mem.BgScrollX == 0) && (Mem.BgScrollY != 0)) {
		setmem(&BMParray[0],(arrmax2 << 1)*coldepth,0);
	} else if ((Mem.BgScrollX != 0) && (Mem.BgScrollY != 0)) {
		setmem(&BMParray[0],(arrmax2 << 1)*coldepth,0);
	}
}

void __fastcall clscreenbig()
{ setmem(&BMParray[0],40960*coldepth,0); }
void __fastcall clscreenbig2()
{ setmem(&BMParray[0],245760*coldepth,0); }

void psetbig2(int x,int y,unsigned char color)
{
	if (y > 479) return;
	COLORREF tmpcol = Palette[color];

	if (coldepth == 4)
	{
		BMParray[((x +(y << 9)) << 2)] = GetBValue(tmpcol);
		BMParray[((x +(y << 9)) << 2)+1] = GetGValue(tmpcol);
		BMParray[((x +(y << 9)) << 2)+2] = GetRValue(tmpcol);
		BMParray[((x +(y << 9)) << 2)+3] = 0;
	} else if (coldepth == 3) {
		BMParray[3*(x+(y << 9))] = GetBValue(tmpcol);
		BMParray[3*(x+(y << 9))+1] = GetGValue(tmpcol);
		BMParray[3*(x+(y << 9))+2] = GetRValue(tmpcol);
	} else if (coldepth == 2) {
		BMParray[(x << 1)+(y << 10)] = (BYTE) (((BYTE) (GetBValue(tmpcol) >> 3))+(((BYTE) (GetGValue(tmpcol) >> 2)) << 5));
		BMParray[(x << 1)+(y << 10)+1] = (BYTE) ((((BYTE) (GetGValue(tmpcol) >> 2))>>3)+(((BYTE) (GetRValue(tmpcol) >> 3))<<3));
	} else if (coldepth == 1) {
//		BMParray[x+ (y << 9)] = color;
		BMParray[x+ (y << 9)] = NearestPalEntry[color];
	}
}

void __fastcall psetbig(int x,int y,unsigned char color)
{
	COLORREF tmpcol = Palette[color];
	if (coldepth == 4)
	{
		BMParray[((x +(y << 8)) << 2)] = GetBValue(tmpcol);
		BMParray[((x +(y << 8)) << 2)+1] = GetGValue(tmpcol);
		BMParray[((x +(y << 8)) << 2)+2] = GetRValue(tmpcol);
		BMParray[((x +(y << 8)) << 2)+3] = 0;
	} else if (coldepth == 3) {
		BMParray[3*(x+(y << 8))] = GetBValue(tmpcol);
		BMParray[3*(x+(y << 8))+1] = GetGValue(tmpcol);
		BMParray[3*(x+(y << 8))+2] = GetRValue(tmpcol);
	} else if (coldepth == 2) {
		BMParray[(x << 1)+(y << 9)] = (BYTE) (((BYTE) (GetBValue(tmpcol) >> 3))+(((BYTE) (GetGValue(tmpcol) >> 2)) << 5));
		BMParray[(x << 1)+(y << 9)+1] = (BYTE) ((((BYTE) (GetGValue(tmpcol) >> 2))>>3)+(((BYTE) (GetRValue(tmpcol) >> 3))<<3));
	} else if (coldepth == 1) {
//		BMParray[x+ (y << 8)] = color;
		BMParray[x+ (y << 8)] = NearestPalEntry[color];
	}
}

void __fastcall pset(register short int x,register short int y,register unsigned char color)
{
//	if (GraphicsEngine != 2) {
//		if ((Mem.BgScrollX != 0) || (Mem.BgScrollY != 0)) y <<= 1;
//		if ((x > 511) || (y > 479) || (x < 0) || (y < 0)) return;
//	} else {
		if ((x > 255) || (y > 239)) return;
//	}

	if (coldepth == 1) {
//		BMParray[x + (y << 8)] = color;
		BMParray[x + (y << 8)] = NearestPalEntry[color];
	} else if (coldepth == 3) {
		COLORREF tmpcol = Palette[color];
		BMParray[3*(x+(y << 8))] = GetBValue(tmpcol);
		BMParray[3*(x+(y << 8))+1] = GetGValue(tmpcol);
		BMParray[3*(x+(y << 8))+2] = GetRValue(tmpcol);
	} else if (coldepth == 2) {
		COLORREF tmpcol = Palette[color];
		BMParray[(x << 1)+(y << 9)] = (BYTE) (((BYTE) (GetBValue(tmpcol) >> 3))+(((BYTE) (GetGValue(tmpcol) >> 2)) << 5));
		BMParray[(x << 1)+(y << 9)+1] = (BYTE) ((((BYTE) (GetGValue(tmpcol) >> 2))>>3)+(((BYTE) (GetRValue(tmpcol) >> 3))<<3));
	} else if (coldepth == 4) {
		COLORREF tmpcol = Palette[color];
		BMParray[((x+(y << 8)) << 2)] = GetBValue(tmpcol);
		BMParray[((x+(y << 8)) << 2)+1] = GetGValue(tmpcol);
		BMParray[((x+(y << 8)) << 2)+2] = GetRValue(tmpcol);
		BMParray[((x+(y << 8)) << 2)+3] = 0;
	}
}

void __fastcall VideoSetup(TForm *nf, TForm *df, TMemo *TrcMem, TMemo *StMem)
{
//	for (int nt=0;nt<4;nt++)
//	{
//		for (int y=0;y<480;y++)
//		{
//			short int addr;
//			unsigned char TileX;
//			unsigned char TileY = (BYTE) (y >> 3);
//			unsigned char NTY = (BYTE) (((TileY >= 30) ^ (bool) ((nt << 10) & 0x800)) << 1);
//			unsigned char TileYM30 = (BYTE) (TileY % 30);

//			for (int x=0;x<512;x++)
//			{
//				TileX = (BYTE) (x >> 3);
//				short int NameTable = (LBYTE) (((NTY | (bit5(TileX) ^ ((nt << 10) & 0x400))) << 10) | 0x2000);
//				addr = (short int) (NameTable | (TileYM30 << 5) | (TileX & 0x1F));
//				SlAddr[nt][x][y] = addr;
//				addr = (short int) (0x3C0 | NameTable | ((TileYM30 & 0x1C) << 1) | ((TileX & 0x1F) >> 2));
//				SlAddrC[nt][x][y] = addr;
//				SlAddrCS[x][y] = (BYTE) ((bit1(TileX) + (TileYM30 & 2)) << 1);
//			}
//		}
//	}

	TracerMemo = TrcMem; StatusMemo = StMem;
	VWFORM = nf; VWFORMbig = df;
	VWHWND = VWFORM->Handle; VWHWNDbig = VWFORMbig->Handle;
	VWHDC = GetDC(VWHWND); VWHDCbig = GetDC(VWHWNDbig);
	MemHDC = CreateCompatibleDC(VWHDC); MemHDCbig = CreateCompatibleDC(VWHDCbig);
	VWBMP = CreateCompatibleBitmap(VWHDC,256,240); VWBMPbig = CreateCompatibleBitmap(VWHDCbig,512,480);

	HDC tdc = GetWindowDC(GetDesktopWindow());
	coldepth = (GetDeviceCaps(tdc,BITSPIXEL) >> 3);
	ReleaseDC(GetDesktopWindow(), tdc);

	if (coldepth == 1)
	{
		SystemLogPal.palVersion = 0x300; SystemLogPal.palNumEntries = 68;
		GetSystemPaletteEntries(MemHDC,0,68,&SystemLogPal.palPalEntry[0]);
		for (int i=0;i<68;i++)
		{
			SystemLogPal.palPalEntry[i].peRed = SystemPalEntry[i].peRed;
			SystemLogPal.palPalEntry[i].peGreen = SystemPalEntry[i].peGreen;
			SystemLogPal.palPalEntry[i].peBlue = SystemPalEntry[i].peBlue;
		}
		SystemPal = CreatePalette(&SystemLogPal);

		SelectPalette(MemHDC, SystemPal, false);
		RealizePalette(MemHDC);

		DeleteObject(SystemPal);

		GetSystemPaletteEntries(MemHDC,0,256,&SystemLogPal.palPalEntry[0]);
		SystemPal = CreatePalette(&SystemLogPal);

		for (int i=0;i<68;i++)
			NearestPalEntry[i] = (BYTE) GetNearestPaletteIndex(SystemPal,Palette[i]);
	} else {
		Application->MessageBox("You are not in 8-bit color.  Emulation will be much slower than in 8-bit color.", "Warning: Color Depth", MB_OK);
	}
}

void UpdateVideoMode()
{
	ReleaseDC(VWHWND, VWHDC); ReleaseDC(VWHWNDbig, VWHDCbig);
	DeleteDC(MemHDC); DeleteDC(MemHDCbig);

	DeleteObject(VWBMP);
	DeleteObject(VWBMPbig);
	DeleteObject(SystemPal);

	VWHDC = GetDC(VWHWND); VWHDCbig = GetDC(VWHWNDbig);
	MemHDC = CreateCompatibleDC(VWHDC); MemHDCbig = CreateCompatibleDC(VWHDCbig);
	VWBMP = CreateCompatibleBitmap(VWHDC,256,240); VWBMPbig = CreateCompatibleBitmap(VWHDCbig,512,480);

	HDC tdc = GetWindowDC(GetDesktopWindow());
	coldepth = (GetDeviceCaps(tdc,BITSPIXEL) >> 3);
	ReleaseDC(GetDesktopWindow(), tdc);

	if (coldepth == 1)
	{
		SystemLogPal.palVersion = 0x300; SystemLogPal.palNumEntries = 68;
		GetSystemPaletteEntries(MemHDC,0,68,&SystemLogPal.palPalEntry[0]);
		for (int i=0;i<68;i++)
		{
			SystemLogPal.palPalEntry[i].peRed = SystemPalEntry[i].peRed;
			SystemLogPal.palPalEntry[i].peGreen = SystemPalEntry[i].peGreen;
			SystemLogPal.palPalEntry[i].peBlue = SystemPalEntry[i].peBlue;
		}
		SystemPal = CreatePalette(&SystemLogPal);

		DeleteObject(SystemPal);

		SelectPalette(MemHDC, SystemPal, false);
		RealizePalette(MemHDC);

		GetSystemPaletteEntries(MemHDC,0,256,&SystemLogPal.palPalEntry[0]);
		SystemPal = CreatePalette(&SystemLogPal);

		for (int i=0;i<68;i++)
			NearestPalEntry[i] = (BYTE) GetNearestPaletteIndex(SystemPal,Palette[i]);
	}
}

void __fastcall VideoShutdown()
{
	ReleaseDC(VWHWND, VWHDC); ReleaseDC(VWHWNDbig, VWHDCbig);
	DeleteDC(MemHDC); DeleteDC(MemHDCbig);

	DeleteObject(VWBMP);
	DeleteObject(VWBMPbig);
	DeleteObject(SystemPal);

//	VWFORM->Release(); VWFORMbig->Release();
}

void __fastcall dprinto(AnsiString tp)	{ TracerMemo->Lines->Add(tp); }
void __fastcall tprinto(AnsiString tp)	{ StatusMemo->Lines->Add(tp); }
//---------------------------------------------------------------------------

