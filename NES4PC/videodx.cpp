//---------------------------------------------------------------------------
//All of these API calls are in the Win95 Programmers Guide (one of the MS
//Help files that came with BCB).
//---------------------------------------------------------------------------

#define MB(a,b)	Application->MessageBox(a,b,MB_OK);
//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#include <math.h>
#include <mem.h>
#include <ddraw.h>
#pragma hdrstop

#include "videodx.h"
//---------------------------------------------------------------------------
extern unsigned short int ww, wh, wwh, whh;
extern AnsiString LastError;

typedef unsigned char BYTE;
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
extern bool cm555;

extern int coldepth;

extern bool Windowed;

HDC tdc;
TForm *VWFORM;
HWND VWHWND;
HDC VWHDC;
HDC MemHDC;
HBITMAP VWBMP;

HRESULT hres;
LPDIRECTDRAW lpDD;
LPDIRECTDRAW7 lpDD7;
extern DDSURFACEDESC2 ddsd2;
LPDIRECTDRAWSURFACE7 lpDDSPrim7, lpDDSBack7;
RECT WindowRect;

extern unsigned char *picarray;
extern unsigned short int *picarray16;
extern unsigned int *picarray32;
//---------------------------------------------------------------------------
void ClearFrame()
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

void pset(short int x,short int y,unsigned long color)
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

bool DXOpen()
{
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
	return(true);
}

void DXClose()
{
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
						LastError = "Lock: Surface Busy";
/*
                        while (hres == DDERR_SURFACEBUSY) {
                                Application->ProcessMessages();
                                hres = lpDDSBack7->Lock(NULL, &ddsd2, DDLOCK_SURFACEMEMORYPTR | DDLOCK_WAIT, NULL);
                        };
                        return(true);
*/
						return(false);
                case DDERR_WASSTILLDRAWING:
//                        MB("Lock: Still Blitting Surface", "Error");
						LastError = "Lock: Still Drawing";
                        return(false);
                default:
//                        MB("Lock Error: Unhandled", "Error");
						LastError = "Other Lock Error";
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
						LastError = "Unlock: Other Error";
//                        MB("Unlock: Unknown Error", "Error");
                        return(false);
        };
}

bool VideoSetup(TForm *nf)
{
	VWFORM = nf;
    VWHWND = VWFORM->Handle;
    VWHDC = GetDC(VWHWND);
    MemHDC = CreateCompatibleDC(VWHDC);
    VWBMP = CreateCompatibleBitmap(VWHDC,ww,wh);

    tdc = GetWindowDC(GetDesktopWindow());
	coldepth = (GetDeviceCaps(tdc,BITSPIXEL) >> 3);

	WindowRect.left = nf->Left + 4;
	WindowRect.right = nf->Left + ww + 4;
	WindowRect.top = nf->Top + 24;
	WindowRect.bottom = nf->Top + wh + 24;

	if (coldepth == 2)
		if (GetNearestColor(tdc,0x007D00) == 32768) cm555 = true;

	hres = DirectDrawCreateEx(NULL, (VOID**)&lpDD7, IID_IDirectDraw7, NULL);
	if (hres != DD_OK) { LastError = "DirectDrawCreateEx Error"; return(false); }

if (Windowed) {
	hres = lpDD7->SetCooperativeLevel(NULL, DDSCL_NORMAL);
} else {
	hres = lpDD7->SetCooperativeLevel(nf->Handle, DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN | DDSCL_ALLOWREBOOT);
}
	if (hres != DD_OK) { LastError = "SetCooperativeLevel (DD7) Error"; return(false); }

if (!Windowed) {
	hres = lpDD7->SetDisplayMode(ww,wh,16,0,0);
	if (hres != DD_OK) { LastError = "SetDisplayMode (DD7) Error"; return(false); }
}

	if FAILED(DXOpen()) { LastError = "Failed on DXOpen"; return(false); }

	if FAILED(DXLock()) { LastError = "Failed on DXLock"; return(false); }

	return(true);
}

void VideoShutdown()
{
	DXUnlock();
	DXClose();

	ReleaseDC(GetDesktopWindow(), tdc);
	ReleaseDC(VWHWND, VWHDC);
	DeleteDC(MemHDC);
	DeleteObject(VWBMP);
}
//---------------------------------------------------------------------------




