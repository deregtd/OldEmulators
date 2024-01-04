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
bool cm555;
short ww = 256, wh = 256, wwh = ww/2, whh = wh/2;
//---------------------------------------------------------------------------
HPALETTE SystemPal;
LOGPALETTE SystemLogPal;
//---------------------------------------------------------------------------
PALETTEENTRY SystemPalEntry[68] = {
{ 0x5B, 0x5B, 0x5B }, { 0x0, 0x0, 0xB4 }, { 0x0, 0x0, 0xA0 }, { 0x3D, 0x0, 0xB1 }, 
{ 0x69, 0x0, 0x74 }, { 0x5B, 0x0, 0x0 }, { 0x5F, 0x0, 0x0 }, { 0x41, 0x18, 0x0 }, 
{ 0x10, 0x2F, 0x0 }, { 0x8, 0x4A, 0x8 }, { 0x0, 0x67, 0x0 }, { 0x0, 0x42, 0x12 }, 
{ 0x0, 0x28, 0x6D }, { 0x0, 0x0, 0x0 }, { 0x0, 0x0, 0x0 }, { 0x0, 0x0, 0x0 },
{ 0xE0, 0xC3, 0xA1 }, { 0x0, 0x40, 0xFF }, { 0x22, 0xE, 0xDC }, { 0x6B, 0x47, 0xFF }, 
{ 0x9F, 0x0, 0xD7 }, { 0xD7, 0xA, 0x68 }, { 0xBC, 0x19, 0x0 }, { 0xB1, 0x54, 0x0 }, 
{ 0x5B, 0x6A, 0x0 }, { 0x3, 0x8C, 0x0 }, { 0x0, 0xAB, 0x0 }, { 0x0, 0x88, 0x2C }, 
{ 0x0, 0x72, 0xA4 }, { 0x0, 0x0, 0x0 }, { 0x0, 0x0, 0x0 }, { 0x0, 0x0, 0x0 }, 
{ 0xF8, 0xF8, 0xF8 }, { 0x3C, 0xAB, 0xFF }, { 0x81, 0x79, 0xFF }, { 0xC5, 0x5B, 0xFF }, 
{ 0xF2, 0x48, 0xFF }, { 0xFF, 0x49, 0xDF }, { 0xFF, 0x6D, 0x47 }, { 0xF7, 0x8C, 0x0 },
{ 0xB7, 0xE0, 0x0 }, { 0x75, 0xE3, 0x0 }, { 0x2B, 0xF4, 0x3 }, { 0x2E, 0xB8, 0x78 },
{ 0x18, 0xE2, 0xE5 }, { 0x78, 0x78, 0x78 }, { 0x0, 0x0, 0x0 }, { 0x0, 0x0, 0x0 },
{ 0xFF, 0xFF, 0xFF }, { 0xBE, 0xF2, 0xFF }, { 0xB8, 0xB8, 0xF8 }, { 0xD8, 0xB8, 0xF8 }, 
{ 0xFF, 0xB6, 0xFF }, { 0xFF, 0xC3, 0xFF }, { 0xFF, 0xD1, 0xC7 }, { 0xFF, 0xDA, 0x9A }, 
{ 0xF8, 0xED, 0x88 }, { 0xDD, 0xFF, 0x83 }, { 0xB8, 0xF8, 0xB8 }, { 0xAC, 0xF8, 0xF5 },
{ 0xB0, 0xFF, 0xFF }, { 0xF8, 0xD8, 0xF8 }, { 0x0, 0x0, 0x0 }, { 0x0, 0x0, 0x0 },

/* Conte
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
*/
   {0,0,0},{255,0,0},{0,255,0},{0,0,255}
};
COLORREF Palette[68] = {

   {0x7F7F7F}, {0x0000BB}, {0x3700BF}, {0x8400A6},
   {0xBB006A}, {0xB70022}, {0xB31E00}, {0x912600},
   {0x7B2B00}, {0x004400}, {0x00480D}, {0x005948},
   {0x004891}, {0x000000}, {0x050505}, {0x050505},
   {0xC8C8C8}, {0x0059FF}, {0x6600FF}, {0xB733CC},
   {0xFF338C}, {0xFF3C5E}, {0xFF371A}, {0xD54B00},
   {0xC46200}, {0x597B00}, {0x1E8415}, {0x00957B},
   {0x0099D9}, {0x111111}, {0x090909}, {0x090909},
   {0xFFFFFF}, {0x00AAFF}, {0x8080FF}, {0xD56FFF},
   {0xFF77C4}, {0xFF7799}, {0xFF7B62}, {0xFF8C59},
   {0xFFA22B}, {0xBBC800}, {0x51D96A}, {0x4DD5AE},
   {0x15EAFF}, {0x666666}, {0x0D0D0D}, {0x0D0D0D},
   {0xFFFFFF}, {0xAEC8FF}, {0xBBBBFF}, {0xDDB3EA},
   {0xFFB7EA}, {0xFFB3CC}, {0xFFC4B7}, {0xFFCCAE},
   {0xFFD9A2}, {0xCCE199}, {0xAEEEB7}, {0xAAF2CC},
   {0xA2EEFF}, {0xDDDDDD}, {0x111111}, {0x111111},

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
//---------------------------------------------------------------------------
RECT WindowRect;
extern bool Windowed;
HRESULT hres;
LPDIRECTDRAW lpDD;
LPDIRECTDRAW7 lpDD7;
DDSURFACEDESC2 ddsd2;
LPDIRECTDRAWSURFACE7 lpDDSPrim7, lpDDSBack7;
unsigned char *picarray;
unsigned short int *picarray16;
unsigned int *picarray32;
//---------------------------------------------------------------------------
/*
void DXPset(short int x,short int y,unsigned long color)
{
	if (!color) return;

	if (coldepth == 2) {
			if (cm555) picarray16[x + (y * (ddsd2.lPitch >> 1))] = ((color & 0xF80000) >> 19) | ((color & 0x00F800) >> 6) | ((color & 0xF8) << 7);
			else picarray16[x + (y * (ddsd2.lPitch >> 1))] = ((color & 0xF80000) >> 19) | ((color & 0x00FC00) >> 5) | ((color & 0xF8) << 8);
	} else if (coldepth == 3) {
			picarray[3*(x+(y*ddsd2.lPitch))] = GetBValue(color);
			picarray[3*(x+(y*ddsd2.lPitch))+1] = GetGValue(color);
			picarray[3*(x+(y*ddsd2.lPitch))+2] = GetRValue(color);
	} else if (coldepth == 4) {
			picarray32[x+(y * (ddsd2.lPitch >> 2))] = ((color & 0x0000FF) << 16) | (color & 0x00FF00) | ((color & 0xFF0000) >> 16);
	}
}

void DXClear()
{
	if (coldepth == 4)
		setmem(picarray32,ww*wh*4,0);
	else if (coldepth == 2)
		setmem(picarray16,ww*wh*2,0);
	else
		setmem(picarray,ww*wh*3,0);
}

bool DXRender()
{
	if FAILED(DXUnlock())
		return(false);
if (Windowed) {
	hres = lpDDSPrim7->Blt(&WindowRect,lpDDSBack7,NULL,NULL,NULL);
	if (hres != DD_OK)
	{
		MB("Blt: Error", "Error");
		return(false);
	}
} else {
	hres = lpDDSPrim7->Flip(NULL,DDFLIP_WAIT);
	switch (hres)
	{
		case DD_OK :
			break;
		case DDERR_SURFACELOST :
			lpDDSPrim7->Restore();
			lpDDSPrim7->Flip(NULL,DDFLIP_WAIT);
			break;
		case DDERR_SURFACEBUSY :
			break;
		default :
			return(false);
	}
}
	if FAILED(DXLock())
		return(false);

	return(true);
}

bool DXOpen()
{
if (Windowed) {
	hres = lpDD7->SetCooperativeLevel(NULL, DDSCL_NORMAL);
} else {
	hres = lpDD7->SetCooperativeLevel(VWFORM->Handle, DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN | DDSCL_ALLOWREBOOT);
}

if (!Windowed) {
	hres = lpDD7->SetDisplayMode(ww,wh,8,0,0);
}

	ddsd2.dwSize = sizeof(ddsd2);
		ddsd2.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
        ddsd2.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
        ddsd2.dwWidth = ww;
		ddsd2.dwHeight = wh;
		hres = lpDD7->CreateSurface(&ddsd2, &lpDDSBack7, NULL);
		if (hres != DD_OK) { MB("CreateSurface: Back Surface", "Error"); return(false); }

	ddsd2.dwSize = sizeof(ddsd2);
if (Windowed) {
	ddsd2.dwFlags = DDSD_CAPS;
	ddsd2.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
} else {
	ddsd2.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
	ddsd2.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP | DDSCAPS_COMPLEX;
	ddsd2.dwBackBufferCount = 1;
}

	hres = lpDD7->CreateSurface(&ddsd2, &lpDDSPrim7, NULL);
	if (hres != DD_OK) { MB("CreateSurface: Front Surface", "Error"); return(false); }

if (!Windowed) {
	ddsd2.ddsCaps.dwCaps = DDSCAPS_BACKBUFFER;
	hres = lpDDSPrim7->GetAttachedSurface(&ddsd2.ddsCaps, &lpDDSBack7);
	if (hres != DD_OK) { MB("GetAttachedSurface: Back Surface", "Error"); return(false); }
}

	ddsd2.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
	ddsd2.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
	ddsd2.dwWidth = ww;
	ddsd2.dwHeight = wh;

	if FAILED(DXLock()) { MB("Failed on DXLock", "Error"); return(false); }

	return(true);
}

void DXClose()
{
	DXUnlock();

	if (lpDD7)
	{
		if (lpDDSBack7) { lpDDSBack7->Release(); lpDDSBack7 = NULL; }
		if (lpDDSPrim7) { lpDDSPrim7->Release(); lpDDSPrim7 = NULL; }
		lpDD7->Release();
		lpDD7 = NULL;
	}
}

bool DXLock()
{
        hres = lpDDSBack7->Lock(NULL, &ddsd2, DDLOCK_SURFACEMEMORYPTR | DDLOCK_WAIT, NULL);
        switch (hres) {
                case DD_OK:
						if (coldepth == 2)
							picarray16 = (unsigned short int *) ddsd2.lpSurface;
						else if (coldepth == 4)
                        	picarray32 = (unsigned int *) ddsd2.lpSurface;
						else
                        	picarray = (unsigned char *) ddsd2.lpSurface;
                        return(true);
                case DDERR_SURFACELOST:
                        lpDDSBack7->Restore();
						lpDDSBack7->Lock(NULL, &ddsd2, DDLOCK_SURFACEMEMORYPTR | DDLOCK_WAIT, NULL);
						if (coldepth == 2)
							picarray16 = (unsigned short int *) ddsd2.lpSurface;
						else if (coldepth == 4)
                        	picarray32 = (unsigned int *) ddsd2.lpSurface;
						else
							picarray = (unsigned char *) ddsd2.lpSurface;
                        return(true);
                case DDERR_SURFACEBUSY:
//						MB("Lock Error: Surface Busy", "Error");
//						LastError = "Lock: Surface Busy";
						return(false);
				case DDERR_WASSTILLDRAWING:
//                        MB("Lock: Still Blitting Surface", "Error");
//						LastError = "Lock: Still Drawing";
						return(false);
				default:
//                        MB("Lock Error: Unhandled", "Error");
//						LastError = "Other Lock Error";
						return(false);
        };
}

bool DXUnlock()
{
        hres = lpDDSBack7->Unlock(NULL);
        switch (hres) {
                case DD_OK:
                        return(true);
                case DDERR_SURFACELOST:
                        lpDDSBack7->Restore();
                        return(true);
                case DDERR_NOTLOCKED:
						return(true);
                default :
//						LastError = "Unlock: Other Error";
//                        MB("Unlock: Unknown Error", "Error");
						return(false);
		};
}
*/

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
		setmem(&BMParray[0],245760,NearestPalEntry[Mem.ImagePalette[0]]);
	}
}

void FinishTileline()
{
	if (curframe < frameskip) return;
	curframe = 0;

	SetBitmapBits(VWBMP,arrmax*coldepth,&BMParray);
	SelectObject(MemHDC,VWBMP);
	if (PALMode)
		BitBlt(VWHDC,0,0,256,240,MemHDC,0,0,SRCCOPY);
	else
		BitBlt(VWHDC,0,8,256,224,MemHDC,0,8,SRCCOPY);

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
			GetSystemPaletteEntries(MemHDC,0,256,&tmpst[0]);

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
}

void DrawScanline()
{
	if (curframe < frameskip) return;

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
//							DXPset((short int) (Mem.Sprite[spr+3] + xx),ScanLine,Mem.SpritePalette[((Mem.Sprite[spr+2] & 3) << 2) | col]);
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
//							DXPset((short int) (Mem.Sprite[spr+3] + xx),ScanLine,Mem.SpritePalette[((Mem.Sprite[spr+2] & 3) << 2) | col]);
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
//					DXPset((short int) (x - Mem.BgScrollX),ScanLine,Mem.ImagePalette[(((*Mem.PPU[0x3C0 | NameTable | ((TileYM30 & 0x1C) << 1) | ((TileX & 0x1F) >> 2)] >> ((bit1(TileX) + (TileYM30 & 2)) << 1)) & 3) << 2) | col]);
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
//						DXPset((short int) (x + xx - Mem.BgScrollX),ScanLine,Mem.ImagePalette[(((*Mem.PPU[0x3C0 | NameTable | ((TileYM30 & 0x1C) << 1) | ((TileX & 0x1F) >> 2)] >> ((bit1(TileX) + (TileYM30 & 2)) << 1)) & 3) << 2) | col]);
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
//					DXPset((short int) (x - Mem.BgScrollX),ScanLine,Mem.ImagePalette[(((*Mem.PPU[0x3C0 | NameTable | ((TileYM30 & 0x1C) << 1) | ((TileX & 0x1F) >> 2)] >> ((bit1(TileX) + (TileYM30 & 2)) << 1)) & 3) << 2) | col]);
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
//						DXPset((short int) (x + xx - Mem.BgScrollX),ScanLine,Mem.ImagePalette[(((*Mem.PPU[0x3C0 | NameTable | ((TileYM30 & 0x1C) << 1) | ((TileX & 0x1F) >> 2)] >> ((bit1(TileX) + (TileYM30 & 2)) << 1)) & 3) << 2) | col]);
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
//							DXPset((short int) (Mem.Sprite[spr+3] + xx),ScanLine,Mem.SpritePalette[((Mem.Sprite[spr+2] & 3) << 2) | col]);
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
//							DXPset((short int) (Mem.Sprite[spr+3] + xx),ScanLine,Mem.SpritePalette[((Mem.Sprite[spr+2] & 3) << 2) | col]);
							pset((short int) (Mem.Sprite[spr+3] + xx),ScanLine,Mem.SpritePalette[((Mem.Sprite[spr+2] & 3) << 2) | col]);
					}
				}
//                                if (SprNum == 8) spr = -4;
			}
		}
	}
        ScLnSprCnt = (SprNum > 8);
}
/*
void __fastcall drawspritebasic(int x,int y,unsigned char ColUp,unsigned short int address, bool vflip, bool hflip)
{
	x += 7;

	if ((!SprClip) && (x < 15)) return;

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
//                                        col = (BYTE) (bit(Mem.PatternTable[(bool) (address & 0x1000)][(address & 0xfff)+i], h) + (bit(Mem.PatternTable[(bool) (address & 0x1000)][(address & 0xfff)+i+8], h) << 1));
                                        col = (BYTE) (bit(*Mem.PPU[address+i], h) + (bit(*Mem.PPU[address+i+8], h) << 1));
					if (col)
						pset((short int) (x-7+h),(short int) (y+7-i),*Mem.PPU[0x3F10 | (ColUp + col)]);
				}
			} else {
				for (unsigned char h=0;h<8;h++)
				{
                                        col = (BYTE) (bit(*Mem.PPU[address+i], h) + (bit(*Mem.PPU[address+i+8], h) << 1));
//                                        col = (BYTE) (bit(Mem.PatternTable[(bool) (address & 0x1000)][(address & 0xfff)+i], h) + (bit(Mem.PatternTable[(bool) (address & 0x1000)][(address & 0xfff)+i+8], h) << 1));
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
                                        col = (BYTE) (bit(*Mem.PPU[address+i], h) + (bit(*Mem.PPU[address+i+8], h) << 1));
//                                        col = (BYTE) (bit(Mem.PatternTable[(bool) (address & 0x1000)][(address & 0xfff)+i], h) + (bit(Mem.PatternTable[(bool) (address & 0x1000)][(address & 0xfff)+i+8], h) << 1));
					if (col)
						pset((short int) (x-7+h),(short int) (y+i),*Mem.PPU[0x3F10 | (ColUp + col)]);
				}
			} else {
				for (unsigned char h=0;h<8;h++)
				{
                                        col = (BYTE) (bit(*Mem.PPU[address+i], h) + (bit(*Mem.PPU[address+i+8], h) << 1));
//                                        col = (BYTE) (bit(Mem.PatternTable[(bool) (address & 0x1000)][(address & 0xfff)+i], h) + (bit(Mem.PatternTable[(bool) (address & 0x1000)][(address & 0xfff)+i+8], h) << 1));
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
//                        col = (BYTE) (bit(Mem.PatternTable[BkPTA][address+i], h) + (bit(Mem.PatternTable[BkPTA][address+i+8], h) << 1));
                        col = (BYTE) (bit(*Mem.PPU[(BkPTA << 12) | address | i], h) + (bit(*Mem.PPU[(BkPTA << 12) | address | i | 8], h) << 1));
			if (col) pset((short int) (x-h),(short int) (y+i),*Mem.PPU[0x3F00 | (ColUp + col)]);
	}	}
}
*/

void __fastcall renderbig()
{
	SetBitmapBits(VWBMP,40960*coldepth,&BMParray);
	SelectObject(MemHDC,VWBMP);
        BitBlt(VWHDC,256,0,256,160,MemHDC,0,0,SRCCOPY);
}

void __fastcall renderbig2()
{
	SetBitmapBits(VWBMPbig,245760*coldepth,&BMParray);
	SelectObject(MemHDC,VWBMPbig);
	BitBlt(VWHDCbig,0,0,512,480,MemHDC,0,0,SRCCOPY);
}

void __fastcall clscreenbig()
{ setmem(&BMParray[0],40960*coldepth,0); }

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
		BMParray[x+ (y << 8)] = NearestPalEntry[color];
	}
}

void __fastcall pset(short int x,short int y,unsigned char color)
{
	if ((x > 255) || (y > 239)) return;

	if (coldepth == 1) {
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

void VideoSetup(TForm *nf, RECT trct, TMemo *TrcMem, TMemo *StMem)
{
        for (int i=0;i<64;i++)
        {
//                Palette[i] = ((Palette[i] & 0xff0000) >> 16) | (Palette[i] & 0x00ff00) | ((Palette[i] & 0x0000ff) << 16);
				Palette[i] = (SystemPalEntry[i].peRed) | (SystemPalEntry[i].peGreen << 8) | (SystemPalEntry[i].peBlue << 16);
		}

	TracerMemo = TrcMem; StatusMemo = StMem;
	VWFORM = nf; //VWFORMbig = df;
	VWHWND = VWFORM->Handle; //VWHWNDbig = VWFORMbig->Handle;
	VWHDC = GetDC(VWHWND); //VWHDCbig = GetDC(VWHWNDbig);
	MemHDC = CreateCompatibleDC(VWHDC); //MemHDCbig = CreateCompatibleDC(VWHDCbig);
	VWBMP = CreateCompatibleBitmap(VWHDC,256,240); //VWBMPbig = CreateCompatibleBitmap(VWHDCbig,512,480);

	HDC tdc = GetWindowDC(GetDesktopWindow());
	coldepth = (GetDeviceCaps(tdc,BITSPIXEL) >> 3);
	ReleaseDC(GetDesktopWindow(), tdc);

	WindowRect.left = nf->Left + 4;
	WindowRect.right = nf->Left + ww + 4;
	WindowRect.top = nf->Top + 24;
	WindowRect.bottom = nf->Top + wh + 24;

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
//	hres = DirectDrawCreateEx(NULL, (VOID**)&lpDD7, IID_IDirectDraw7, NULL);
//	if (hres != DD_OK) { /*LastError = "DirectDrawCreateEx Error"; */return(false); }
}

void UpdateVideoMode()
{
	ReleaseDC(VWHWND, VWHDC); //ReleaseDC(VWHWNDbig, VWHDCbig);
	DeleteDC(MemHDC); //DeleteDC(MemHDCbig);

	DeleteObject(VWBMP);
//	DeleteObject(VWBMPbig);
	DeleteObject(SystemPal);

	VWHDC = GetDC(VWHWND); //VWHDCbig = GetDC(VWHWNDbig);
	MemHDC = CreateCompatibleDC(VWHDC); //MemHDCbig = CreateCompatibleDC(VWHDCbig);
	VWBMP = CreateCompatibleBitmap(VWHDC,256,240); //VWBMPbig = CreateCompatibleBitmap(VWHDCbig,512,480);

	HDC tdc = GetWindowDC(GetDesktopWindow());
	coldepth = (GetDeviceCaps(tdc,BITSPIXEL) >> 3);
	ReleaseDC(GetDesktopWindow(), tdc);

	if (coldepth == 2)
		if (GetNearestColor(tdc,0x007D00) == 32768) cm555 = true;

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
//	DXClose();

	ReleaseDC(VWHWND, VWHDC); //ReleaseDC(VWHWNDbig, VWHDCbig);
	DeleteDC(MemHDC); //DeleteDC(MemHDCbig);

	DeleteObject(VWBMP);
//	DeleteObject(VWBMPbig);
	DeleteObject(SystemPal);

//	VWFORM->Release(); VWFORMbig->Release();
}

void __fastcall dprinto(AnsiString tp)	{ TracerMemo->Lines->Add(tp); }
void __fastcall tprinto(AnsiString tp)	{ StatusMemo->Lines->Add(tp); }
//---------------------------------------------------------------------------

