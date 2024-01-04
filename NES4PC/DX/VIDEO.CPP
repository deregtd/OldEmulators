//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#include <math.h>
#include <mem.h>
#include <ddraw.h>
#pragma hdrstop

#include "Defines.h"
#include "video.h"
//---------------------------------------------------------------------------
//#define newchr
//---------------------------------------------------------------------------
const int arrmax = 61440, arrmax2 = 2*arrmax, arrmax3 = 3*arrmax;

extern int FPSnum;

//extern COLORREF BGCol;
extern bool BkPTA, SpPTA, BGVis, SprVis, SSize, SprClip, BGClip, CPURunning, Spr0Occ;
extern bool ScLnSprCnt, FakeSLUsing;
extern LBYTE NTabAdr, ScanLineFake;
extern MemSt Mem;
TMemo *StatusMemo,*TracerMemo;
bool TakeSnap;

extern BYTE tmpBYTE;
extern bool PALMode;
//---------------------------------------------------------------------------
PALETTEENTRY SystemPalEntry[68] = {

   {0x80,0x80,0x80}, {0x00,0x00,0xBB}, {0x37,0x00,0xBF}, {0x84,0x00,0xA6},
   {0xBB,0x00,0x6A}, {0xB7,0x00,0x1E}, {0xB3,0x00,0x00}, {0x91,0x26,0x00},
   {0x7B,0x2B,0x00}, {0x00,0x3E,0x00}, {0x00,0x48,0x0D}, {0x00,0x3C,0x22},
   {0x00,0x2F,0x66}, {0x00,0x00,0x00}, {0x05,0x05,0x05}, {0x05,0x05,0x05},

   {0xC8,0xC8,0xC8}, {0x00,0x59,0xFF}, {0x44,0x3C,0xFF}, {0xB7,0x33,0xCC},
   {0xFF,0x33,0xAA}, {0xFF,0x37,0x5E}, {0xFF,0x37,0x1A}, {0xD5,0x4B,0x00},
   {0xC4,0x62,0x00}, {0x3C,0x7B,0x00}, {0x1E,0x84,0x15}, {0x00,0x95,0x66},
   {0x00,0x84,0xC4}, {0x11,0x11,0x11}, {0x09,0x09,0x09}, {0x09,0x09,0x09},

   {0xFF,0xFF,0xFF}, {0x00,0x95,0xFF}, {0x6F,0x84,0xFF}, {0xD5,0x6F,0xFF},
   {0xFF,0x77,0xCC}, {0xFF,0x6F,0x99}, {0xFF,0x7B,0x59}, {0xFF,0x91,0x5F},
   {0xFF,0xA2,0x33}, {0xA6,0xBF,0x00}, {0x51,0xD9,0x6A}, {0x4D,0xD5,0xAE},
   {0x00,0xD9,0xFF}, {0x66,0x66,0x66}, {0x0D,0x0D,0x0D}, {0x0D,0x0D,0x0D},

   {0xFF,0xFF,0xFF}, {0x84,0xBF,0xFF}, {0xBB,0xBB,0xFF}, {0xD0,0xBB,0xFF},
   {0xFF,0xBF,0xEA}, {0xFF,0xBF,0xCC}, {0xFF,0xC4,0xB7}, {0xFF,0xCC,0xAE},
   {0xFF,0xD9,0xA2}, {0xCC,0xE1,0x99}, {0xAE,0xEE,0xB7}, {0xAA,0xF7,0xEE},
   {0xB3,0xEE,0xFF}, {0xDD,0xDD,0xDD}, {0x11,0x11,0x11}, {0x11,0x11,0x11},

   {0,0,0},{255,0,0},{0,255,0},{0,0,255}
};

COLORREF Palette[68];

unsigned char bitnumsp[2][8] = {
	{ 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01 },
	{ 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 }
};
//---------------------------------------------------------------------------
int coldepth = 0;
unsigned char BMParray[983040];
TForm *VWFORM, *VWFORMbig;

HRESULT hres;
LPDIRECTDRAW lpDD;
LPDIRECTDRAW4 lpDD4;
DDSURFACEDESC2 ddsd2;
LPDIRECTDRAWSURFACE4 lpDDSPrim4, lpDDSBack4;
RECT WindowRect;
unsigned char *picarray;

unsigned char NearestPalEntry[68];
//---------------------------------------------------------------------------
int frameskip = 1;
unsigned char curframe;
extern short int ScanLine;
//---------------------------------------------------------------------------
void PrepTileline()
{
	curframe++;
	if (curframe < frameskip) return;

        DXLock();
}

void FinishTileline()
{
	if (curframe < frameskip) return;
	curframe = 0;

        DXUnlock();
        DXRender();
/*
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

                        if (PALMode) fwrite(&header[1][0], 1, 54, snap); else fwrite(&header[0][0], 1, 54, snap);

                        for (int i=768*232 + (8-(!PALMode << 3))*768;i>(8-(PALMode << 3))*768;i-=768)
				fwrite(&BMParray[i], 1, 768, snap);

			fclose(snap);
		} else if (coldepth == 1) {
			PALETTEENTRY tmpst[256];
//			GetSystemPaletteEntries(MemHDC,0,256,&tmpst[0]);

			FILE * snap = fopen("snapshot.bmp","wb");

                        if (PALMode) fwrite(&header[0][0], 1, 54, snap); else fwrite(&header[1][0], 1, 54, snap);

                        for (int i=256*232 + (8-(!PALMode << 3))*256;i>(8-(PALMode << 3))*256;i-=256)
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
*/
}

void DrawScanline()
{
	if (curframe < frameskip) return;

        setmem(&picarray[ScanLine * ddsd2.lPitch],ddsd2.ddpfPixelFormat.dwRGBBitCount << 5,Mem.ImagePalette[0]);

        short int addr;
	unsigned char SSizeNew = (BYTE) ((SSize << 3));
	unsigned char SprNum = 0;

	if (!FakeSLUsing) ScanLineFake = ScanLine;

	if (SprVis)
        {
		for (short int spr=252;spr>=0;spr-=(BYTE) 4)
		{
                        if ((bit5(Mem.Sprite[spr+2])) && (Mem.Sprite[spr] + 1 <= ScanLine) && (Mem.Sprite[spr] + 9 + SSizeNew > ScanLine))
			{
				SprNum++;
				if (SSize)
				{
					bool hflip = bit6(Mem.Sprite[spr+2]);
                                        char ydiff = (BYTE) (ScanLine - (Mem.Sprite[spr] + 1));
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

					for (unsigned char xx=0;xx<8;xx++)
					{
#ifdef newchr
                                                unsigned char col = (BYTE) (((bool) (*Mem.PPU[(bit0(Mem.Sprite[spr+1]) << 12) | addr | 8] & bitnumsp[hflip][xx]) << 1) | (bool) (*Mem.PPU[(bit0(Mem.Sprite[spr+1]) << 12) | addr] & bitnumsp[hflip][xx]));
#else
                                                unsigned char col = (BYTE) (((bool) (Mem.PatternTable[bit0(Mem.Sprite[spr+1])][addr | 8] & bitnumsp[hflip][xx]) << 1) | (bool) (Mem.PatternTable[bit0(Mem.Sprite[spr+1])][addr] & bitnumsp[hflip][xx]));
#endif
						if (col)
							pset((short int) (Mem.Sprite[spr+3] + xx),ScanLine,Mem.SpritePalette[((Mem.Sprite[spr+2] & 3) << 2) | col]);
					}
				} else {
					bool hflip = bit6(Mem.Sprite[spr+2]);
                                        char ydiff = (BYTE) (ScanLine - (Mem.Sprite[spr] + 1));
					addr = (short int) (Mem.Sprite[spr+1] << 4);
					if (bit7(Mem.Sprite[spr+2])) addr |= (LBYTE) (7 - (ydiff & 0x7));
						else addr |= (BYTE) (ydiff & 0x7);

					for (unsigned char xx=0;xx<8;xx++)
					{
#ifdef newchr
                                                unsigned char col = (BYTE) (((bool) (*Mem.PPU[(SpPTA << 12) | addr | 8] & bitnumsp[hflip][xx]) << 1) | (bool) (*Mem.PPU[(SpPTA << 12) | addr] & bitnumsp[hflip][xx]));
#else
                                                unsigned char col = (BYTE) (((bool) (Mem.PatternTable[SpPTA][addr | 8] & bitnumsp[hflip][xx]) << 1) | (bool) (Mem.PatternTable[SpPTA][addr] & bitnumsp[hflip][xx]));
#endif
						if (col)
							pset((short int) (Mem.Sprite[spr+3] + xx),ScanLine,Mem.SpritePalette[((Mem.Sprite[spr+2] & 3) << 2) | col]);
					}
				}
//                                if (SprNum == 8) spr = -4;
			}
		}
	}
        if (BGVis)
        {
                unsigned char TileX;
		short int SLTmp = (short int) (ScanLineFake + Mem.BgScrollY);
                unsigned char TileY = (BYTE) (SLTmp >> 3);
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

				unsigned char bitnum = bitnumsp[0][x & 7];
#ifdef newchr
                                unsigned char col = (BYTE) (((bool) (*Mem.PPU[(BkPTA << 12) | addr | 8] & bitnum) << 1) | (bool) (*Mem.PPU[(BkPTA << 12) | addr] & bitnum));
#else
                                unsigned char col = (BYTE) (((bool) (Mem.PatternTable[BkPTA][addr | 8] & bitnum) << 1) | (bool) (Mem.PatternTable[BkPTA][addr] & bitnum));
#endif
				if (col)
                                        pset((short int) (x - Mem.BgScrollX),ScanLine,Mem.ImagePalette[(((*Mem.PPU[0x3C0 | NameTable | ((TileYM30 & 0x1C) << 1) | ((TileX & 0x1F) >> 2)] >> ((bit1(TileX) + (TileYM30 & 2)) << 1)) & 3) << 2) | col]);
			}

			for (short int x=(LBYTE) (SLHead+8);x<SLFoot;x+=(BYTE) 8)
			{
				TileX = (BYTE) (x >> 3);
				short int NameTable = (LBYTE) (((NTY | (bit5(TileX) ^ NTabAdrBl)) << 10) | 0x2000);
                                addr = (short int) ((*Mem.PPU[NameTable | (TileYM30 << 5) | (TileX & 0x1F)] << 4) | TileYDiff);

				for (unsigned char xx=0;xx<8;xx++)
				{
					unsigned char bitnum = (BYTE) (0x80 >> xx);
#ifdef newchr
                                unsigned char col = (BYTE) (((bool) (*Mem.PPU[(BkPTA << 12) | addr | 8] & bitnum) << 1) | (bool) (*Mem.PPU[(BkPTA << 12) | addr] & bitnum));
#else
                                unsigned char col = (BYTE) (((bool) (Mem.PatternTable[BkPTA][addr | 8] & bitnum) << 1) | (bool) (Mem.PatternTable[BkPTA][addr] & bitnum));
#endif
					if (col)
                                                pset((short int) (x + xx - Mem.BgScrollX),ScanLine,Mem.ImagePalette[(((*Mem.PPU[0x3C0 | NameTable | ((TileYM30 & 0x1C) << 1) | ((TileX & 0x1F) >> 2)] >> ((bit1(TileX) + (TileYM30 & 2)) << 1)) & 3) << 2) | col]);
				}
			}

			for (short int x=SLFoot;x<Mem.BgScrollX + 256;x++)
			{
				TileX = (BYTE) (x >> 3);
				short int NameTable = (LBYTE) (((NTY | (bit5(TileX) ^ NTabAdrBl)) << 10) | 0x2000);
				addr = (short int) ((*Mem.PPU[NameTable | (TileYM30 << 5) | (TileX & 0x1F)] << 4) | TileYDiff);

				unsigned char bitnum = bitnumsp[0][x & 7];
#ifdef newchr
                                unsigned char col = (BYTE) (((bool) (*Mem.PPU[(BkPTA << 12) | addr | 8] & bitnum) << 1) | (bool) (*Mem.PPU[(BkPTA << 12) | addr] & bitnum));
#else
                                unsigned char col = (BYTE) (((bool) (Mem.PatternTable[BkPTA][addr | 8] & bitnum) << 1) | (bool) (Mem.PatternTable[BkPTA][addr] & bitnum));
#endif
				if (col)
                                        pset((short int) (x - Mem.BgScrollX),ScanLine,Mem.ImagePalette[(((*Mem.PPU[0x3C0 | NameTable | ((TileYM30 & 0x1C) << 1) | ((TileX & 0x1F) >> 2)] >> ((bit1(TileX) + (TileYM30 & 2)) << 1)) & 3) << 2) | col]);
			}
		} else {

			for (short int x=Mem.BgScrollX;x<Mem.BgScrollX + 256;x+=(BYTE) 8)
			{
				TileX = (BYTE) (x >> 3);
				short int NameTable = (LBYTE) (((NTY | (bit5(TileX) ^ NTabAdrBl)) << 10) | 0x2000);
				addr = (short int) ((*Mem.PPU[NameTable | (TileYM30 << 5) | (TileX & 0x1F)] << 4) | TileYDiff);

				for (unsigned char xx=0;xx<8;xx++)
				{
					unsigned char bitnum = bitnumsp[0][xx];
#ifdef newchr
                                        unsigned char col = (BYTE) (((bool) (*Mem.PPU[(BkPTA << 12) | addr | 8] & bitnum) << 1) | (bool) (*Mem.PPU[(BkPTA << 12) | addr] & bitnum));
#else
                                        unsigned char col = (BYTE) (((bool) (Mem.PatternTable[BkPTA][addr | 8] & bitnum) << 1) | (bool) (Mem.PatternTable[BkPTA][addr] & bitnum));
#endif
					if (col)
                                                pset((short int) (x + xx - Mem.BgScrollX),ScanLine,Mem.ImagePalette[(((*Mem.PPU[0x3C0 | NameTable | ((TileYM30 & 0x1C) << 1) | ((TileX & 0x1F) >> 2)] >> ((bit1(TileX) + (TileYM30 & 2)) << 1)) & 3) << 2) | col]);
				}
			}
		}
        }
        if ((SprVis)/* && (SprNum < 8)*/)
	{
		for (short int spr=252;spr>=0;spr-=(BYTE) 4)
		{
                        if ((!bit5(Mem.Sprite[spr+2])) && (Mem.Sprite[spr] + 1 <= ScanLine) && (Mem.Sprite[spr] + 9 + SSizeNew > ScanLine))
			{
				SprNum++;
				if (SSize)
				{
					bool hflip = bit6(Mem.Sprite[spr+2]);
                                        char ydiff = (BYTE) (ScanLine - (Mem.Sprite[spr] + 1));
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

                                        for (unsigned char xx=0;xx<8;xx++)
					{
#ifdef newchr
                                                unsigned char col = (BYTE) (((bool) (*Mem.PPU[(bit0(Mem.Sprite[spr+1]) << 12) | addr | 8] & bitnumsp[hflip][xx]) << 1) | (bool) (*Mem.PPU[(bit0(Mem.Sprite[spr+1]) << 12) | addr] & bitnumsp[hflip][xx]));
#else
                                                unsigned char col = (BYTE) (((bool) (Mem.PatternTable[bit0(Mem.Sprite[spr+1])][addr | 8] & bitnumsp[hflip][xx]) << 1) | (bool) (Mem.PatternTable[bit0(Mem.Sprite[spr+1])][addr] & bitnumsp[hflip][xx]));
#endif
						if (col)
							pset((short int) (Mem.Sprite[spr+3] + xx),ScanLine,Mem.SpritePalette[((Mem.Sprite[spr+2] & 3) << 2) | col]);
					}
				} else {
					bool hflip = bit6(Mem.Sprite[spr+2]);
                                        char ydiff = (BYTE) (ScanLine - (Mem.Sprite[spr] + 1));
					addr = (short int) (Mem.Sprite[spr+1] << 4);
					if (bit7(Mem.Sprite[spr+2])) addr |= (LBYTE) (7 - (ydiff & 0x7));
						else addr |= (BYTE) (ydiff & 0x7);

					for (unsigned char xx=0;xx<8;xx++)
					{
#ifdef newchr
                                                unsigned char col = (BYTE) (((bool) (*Mem.PPU[(SpPTA << 12) | addr | 8] & bitnumsp[hflip][xx]) << 1) | (bool) (*Mem.PPU[(SpPTA << 12) | addr] & bitnumsp[hflip][xx]));
#else
                                                unsigned char col = (BYTE) (((bool) (Mem.PatternTable[SpPTA][addr | 8] & bitnumsp[hflip][xx]) << 1) | (bool) (Mem.PatternTable[SpPTA][addr] & bitnumsp[hflip][xx]));
#endif
						if (col)
							pset((short int) (Mem.Sprite[spr+3] + xx),ScanLine,Mem.SpritePalette[((Mem.Sprite[spr+2] & 3) << 2) | col]);
					}
				}
//                                if (SprNum == 8) spr = -4;
			}
		}
	}
        ScLnSprCnt = (SprNum > 8);
}

void __fastcall renderbig()
{
/*	SetBitmapBits(VWBMP,40960*coldepth,&BMParray);
	SelectObject(MemHDC,VWBMP);
        BitBlt(VWHDC,256,0,256,160,MemHDC,0,0,SRCCOPY);*/
}

void __fastcall renderbig2()
{
/*	SetBitmapBits(VWBMPbig,245760*coldepth,&BMParray);
	SelectObject(MemHDC,VWBMPbig);
	BitBlt(VWHDCbig,0,0,512,480,MemHDC,0,0,SRCCOPY);*/
}

void __fastcall clscreenbig()
{
/*	setmem(&BMParray[0],40960*coldepth,0);*/
}

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
/*		BMParray[x+ (y << 9)] = NearestPalEntry[color];*/
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
//              BMParray[x+ (y << 8)] = NearestPalEntry[color];
	}
}

void __fastcall pset(short int x,short int y,unsigned char color)
{
        if ((x > 255) || (y > 239) || (x < 0) || (y < 0)) return;

//        if (ddsd2.ddpfPixelFormat.dwRGBBitCount == 8) {
                picarray[x + (y * ddsd2.lPitch)] = color;
/*        } else if (coldepth == 3) {
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
*/
}

void DXRender()
{
        hres = lpDDSPrim4->Blt(&WindowRect,lpDDSBack4,NULL,NULL,NULL);
        if (hres != DD_OK)
        {
                MB("Blt: Error", "Error");
                CPURunning = false;
                return;
        }
}

void DXOpen()
{
	ddsd2.dwSize = sizeof(ddsd2);
        ddsd2.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
        ddsd2.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
        ddsd2.dwWidth = 256;
        ddsd2.dwHeight = 240;
        hres = lpDD4->CreateSurface(&ddsd2, &lpDDSBack4, NULL);
        if (hres != DD_OK) { MB("CreateSurface: Back Surface", "Error"); return; }

	ddsd2.dwSize = sizeof(ddsd2);
	ddsd2.dwFlags = DDSD_CAPS;
        ddsd2.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
	hres = lpDD4->CreateSurface(&ddsd2, &lpDDSPrim4, NULL);
        if (hres != DD_OK) { MB("CreateSurface: Front Surface", "Error"); return; }

        UpdateVideoMode();
}

void DXClose()
{
        lpDDSPrim4->Release();
        lpDDSBack4->Release();
}

bool DXLock()
{
        hres = lpDDSBack4->Lock(NULL, &ddsd2, DDLOCK_SURFACEMEMORYPTR | DDLOCK_WAIT, NULL);
        switch (hres) {
                case DD_OK:
                        picarray = (unsigned char *) ddsd2.lpSurface;
                        return(true);
                case DDERR_SURFACELOST:
                        lpDDSBack4->Restore();
                        lpDDSBack4->Lock(NULL, &ddsd2, DDLOCK_SURFACEMEMORYPTR | DDLOCK_WAIT, NULL);
                        picarray = (unsigned char *) ddsd2.lpSurface;
                        return(true);
                case DDERR_SURFACEBUSY:
                        while (hres == DDERR_SURFACEBUSY) {
                                Application->ProcessMessages();
                                hres = lpDDSBack4->Lock(NULL, &ddsd2, DDLOCK_SURFACEMEMORYPTR | DDLOCK_WAIT, NULL);
                        };
//                        CPURunning = false;
//                        MB("Lock: Surface Busy", "Error");
                        return(true);
                case DDERR_WASSTILLDRAWING:
                        CPURunning = false;
                        MB("Lock: Still Blitting Surface", "Error");
                        return(false);
                default:
                        CPURunning = false;
                        MB("Lock Error: Unhandled", "Error");
                        return(false);
        };
}

bool DXUnlock()
{
        hres = lpDDSBack4->Unlock(NULL);
        switch (hres) {
                case DD_OK:
                        return(true);
                case DDERR_SURFACELOST:
                        lpDDSBack4->Restore();
                        return(true);
                case DDERR_NOTLOCKED:
                        return(true);
                default :
                        MB("Unlock: Unknown Error", "Error");
                        CPURunning = false;
                        return(false);
        };
}

void __fastcall VideoSetup(TForm *nf, RECT trct, TMemo *TrcMem, TMemo *StMem)
{
        for (int i=0;i<68;i++)
                Palette[i] = SystemPalEntry[i].peRed | (SystemPalEntry[i].peGreen << 8) | (SystemPalEntry[i].peBlue << 16);

        VWFORM = nf;

        WindowRect.left = nf->Left;
        WindowRect.right = nf->Left + 256;
        WindowRect.top = nf->Top;
        WindowRect.bottom = nf->Top + 240;

	hres = DirectDrawCreate(NULL, &lpDD, NULL);
        if (hres != DD_OK) { MB("DirectDrawCreate Error", "Error"); return; }

        hres = lpDD->SetCooperativeLevel(nf->Handle, DDSCL_NORMAL);
        if (hres != DD_OK) { MB("SetCooperativeLevel Error", "Error"); return; }

	hres = lpDD->QueryInterface(IID_IDirectDraw4, (LPVOID *)&lpDD4);
        if (hres != DD_OK) { MB("Error Querying IDirectDraw4 Interface", "Error"); return; }

        hres = lpDD4->SetCooperativeLevel(nf->Handle, DDSCL_NORMAL);
        if (hres != DD_OK) { MB("SetCooperativeLevel (DD4) Error", "Error"); return; }
}

void UpdateVideoMode()
{
/*
        LOGPALETTE SystemLogPal = { 0x300, 68 };
        HDC VWHDC;
        lpDDSBack4->GetDC(&VWHDC);

        GetSystemPaletteEntries(VWHDC,16,16+68,&SystemLogPal.palPalEntry[0]);
        HPALETTE SystemPal;

        SystemPal = CreatePalette(&SystemLogPal);

        for (int i=0;i<68;i++)
                NearestPalEntry[i] = (BYTE) GetNearestPaletteIndex(SystemPal,Palette[i]);

*/
/*
		for (int i=0;i<68;i++)
		{
			SystemLogPal.palPalEntry[i].peRed = SystemPalEntry[i].peRed;
			SystemLogPal.palPalEntry[i].peGreen = SystemPalEntry[i].peGreen;
			SystemLogPal.palPalEntry[i].peBlue = SystemPalEntry[i].peBlue;
		}
		SystemPal = CreatePalette(&SystemLogPal);

                SelectPalette(VWHDC, SystemPal, false);
                RealizePalette(VWHDC);
*/
/*
        DeleteObject(SystemPal);

        DeleteDC(VWHDC);
*/
}

void __fastcall VideoShutdown()
{
//        lpDD4->Release();
//        lpDD->Release();
}

void __fastcall dprinto(AnsiString tp)	{ TracerMemo->Lines->Add(tp); }
void __fastcall tprinto(AnsiString tp)	{ StatusMemo->Lines->Add(tp); }
//---------------------------------------------------------------------------
