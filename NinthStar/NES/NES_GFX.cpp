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

#include "NES_GFX.h"

#include "..\Global.h"
#include <d3d8.h>

COLORREF Palette[512];

struct CUSTOMVERTEX
{
    FLOAT x, y, z, rhw; // The transformed position for the vertex.
    DWORD color;        // The vertex color.
	FLOAT       tu, tv;   // The texture coordinates.
};

// The custom FVF, which describes the custom vertex structure.
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)

int NES_PalIt = 0;

void cNES_GFX::LoadPalette(int PalNum)
{
	NES_PalIt = PalNum;
	
	double EmphChanges[8][3] = {
		{ 1, 1, 1 },
		{ 1.239, .915, .743 },
		{ .794, 1.086, .882 },
		{ 1.019, .980, .653 },
		{ .905, 1.026, 1.277 },
		{ 1.023, .908, .979 },
		{ .741, .987, 1.001 },
		{ .750, .750, .750 }
	};

	COLORREF cPalette[2][64] = {
		{	//NTSC
			0x808080, 0x003da6, 0x0012b0, 0x440096,
			0xa1005e, 0xc70028, 0xba0600, 0x8c1700,
			0x5c2f00, 0x104500, 0x054a00, 0x00472e,
			0x004166, 0x000000, 0x050505, 0x050505,

			0xc7c7c7, 0x0077ff, 0x2155ff, 0x8237fa,
			0xeb2fb5, 0xff2950, 0xff2200, 0xd63200,
			0xc46200, 0x358000, 0x058f00, 0x008a55,
			0x0099cc, 0x212121, 0x090909, 0x090909,

			0xffffff, 0x0fd7ff, 0x69a2ff, 0xd480ff,
			0xff45f3, 0xff618b, 0xff8833, 0xff9c12,
			0xfabc20, 0x9fe30e, 0x2bf035, 0x0cf0a4,
			0x05fbff, 0x5e5e5e, 0x0d0d0d, 0x0d0d0d,

			0xffffff, 0xa6fcff, 0xb3ecff, 0xdaabeb,
			0xffa8f9, 0xffabb3, 0xffd2b0, 0xffefa6,
			0xfff79c, 0xd7e895, 0xa6edaf, 0xa2f2da,
			0x99fffc, 0xdddddd, 0x111111, 0x111111
		},
		{	//PAL
			0x5B5B5B, 0x0000B4, 0x0000A0, 0x3D00B1, 
			0x690074, 0x5B0000, 0x5F0000, 0x411800, 
			0x102F00, 0x084A08, 0x006700, 0x004212, 
			0x00286D, 0x000000, 0x000000, 0x000000, 

			0xE7D5C4, 0x0040FF, 0x220EDC, 0x6B47FF, 
			0x9F00D7, 0xD70A68, 0xC80000, 0xB15400, 
			0x5B6A00, 0x038C00, 0x009900, 0x00A22C, 
			0x0072A4, 0x000000, 0x000000, 0x000000, 
		
			0xF8F8F8, 0x64B4FF, 0x8EABFF, 0xC55BFF, 
			0xF248FF, 0xFF49DF, 0xFF6D48, 0xE2A749, 
			0xFFE000, 0x75E300, 0x8AE571, 0x2EB878, 
			0x13E2E5, 0x787878, 0x000000, 0x000000, 
			
			0xFFFFFF, 0xBEF2FF, 0xB8B8F8, 0xD8B8F8, 
			0xFFB6FF, 0xFFC3FF, 0xFFD1C7, 0xFFE6C8, 
			0xF8ED88, 0xDDFF83, 0xB8F8B8, 0xD7F8F5, 
			0xC5FFFF, 0xF8D8F8, 0x000000, 0x000000
		}
	};


	HDC tdc = GetWindowDC(GetDesktopWindow());
	unsigned short RV, GV, BV;
	for (int i=0;i<0x200;i++)
	{
		RV = (unsigned short) ((cPalette[PalNum][i&0x03f] & 0xFF0000) >> 16);
		RV = (unsigned short) (((double) RV) * EmphChanges[(i & 0x1C0) >> 6][0]);
		if (RV > 0xFF) RV = 0xFF;
		GV = (unsigned short) ((cPalette[PalNum][i&0x03f] & 0x00FF00) >> 8);
		GV = (unsigned short) (((double) GV) * EmphChanges[(i & 0x1C0) >> 6][1]);
		if (GV > 0xFF) GV = 0xFF;
		BV = (unsigned short) ((cPalette[PalNum][i&0x03f] & 0x0000FF) >> 0);
		BV = (unsigned short) (((double) BV) * EmphChanges[(i & 0x1C0) >> 6][2]);
		if (BV > 0xFF) BV = 0xFF;
		
		Palette[i] = BV | (GV << 8) | (RV << 16);

		switch (Depth)
		{
			case 2 :	//16-Bit Color
				{
					BV >>= 3;
					GV >>= (CM555) ? 3 : 2;
					RV >>= 3;
					FixedPalette[i] = (RV << ((CM555) ? 10 : 11)) | (GV << 5) | (BV << 0);
				}
				break;
			case 4 :	//32-Bit Color
				FixedPalette[i] = Palette[i];
				break;
			default :
				MessageBox(gData->MainWnd, "Sorry, Your Color Depth is Not Supported!", "Fatal Error", MB_OK);
				break;
		}
	}
	ReleaseDC(GetDesktopWindow(), tdc);
}

cNES_GFX::cNES_GFX()
{
	D3DTEX = NULL;
	D3DVB = NULL;
	pD3DD = NULL;
	pD3D = NULL;
	pD3DS = NULL;

	Mode3D = false;

	FPSnum = 0;
	
	HDC tdc = GetWindowDC(GetDesktopWindow());
	Depth = (GetDeviceCaps(tdc,BITSPIXEL) >> 3);
	if ((Depth != 2) && (Depth != 4))
	{
		MessageBox(gData->MainWnd, "Sorry, Your Color Depth is Not Supported!", "Fatal uNF kthxbyekiddie", MB_OK);
		return;
	}

	ReleaseDC(GetDesktopWindow(), tdc);
	
	CM555 = false; if (GetNearestColor(tdc,0x007D00) == 32768) CM555 = true;

	FPSCnt = 0;
	aFPScnt = 0;
	aFPSnum = 0;
	FSkip = 0;
	aFSkip = true;

	QueryPerformanceFrequency(&ClockFreq);

	pD3D = Direct3DCreate8( D3D_SDK_VERSION );

	FilterMode = D3DTEXF_LINEAR;

	LoadPalette(0);
}

void cNES_GFX::RePaint()
{
	if (pD3DS)
		pD3DS->UnlockRect();

	pD3DD->Present(NULL, NULL, NULL, NULL);
	pD3DD->Present(NULL, NULL, NULL, NULL);

	if (pD3DS)
	{
		D3DLOCKED_RECT tpr;
		pD3DS->LockRect(&tpr, NULL, D3DLOCK_NOSYSLOCK);

		DrawArray = (unsigned char *) tpr.pBits;
		Pitch = tpr.Pitch;
	}
}

void cNES_GFX::ReLoad(short Width, short Height, bool NewMode)
{
	HDC tdc = GetWindowDC(GetDesktopWindow());
	Depth = (GetDeviceCaps(tdc,BITSPIXEL) >> 3);
	if ((Depth != 2) && (Depth != 4))
	{
		MessageBox(gData->MainWnd, "Sorry, Your Color Depth is Not Supported!", "Fatal uNF kthxbyekiddie", MB_OK);
		return;
	}

	ReleaseDC(GetDesktopWindow(), tdc);
	LoadPalette(NES_PalIt);

	if( D3DTEX != NULL )
		D3DTEX->Release();
	D3DTEX = NULL;

	if( D3DVB != NULL )
		D3DVB->Release();
	D3DVB = NULL;

	if( pD3DS != NULL )
		pD3DS->Release();
	pD3DS = NULL;

	if( pD3DD != NULL )
		pD3DD->Release();
	pD3DD = NULL;

	Mode3D = NewMode;
	
	pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &D3DDM);
	ZeroMemory(&D3DPP,sizeof(D3DPP));
	D3DPP.BackBufferFormat = D3DDM.Format;
	D3DPP.BackBufferCount = 1;
	D3DPP.SwapEffect = D3DSWAPEFFECT_FLIP;
	if (!Mode3D)
	{
		D3DPP.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
		D3DPP.BackBufferWidth = 256;
		D3DPP.BackBufferHeight = 240;
	} else {
		D3DPP.BackBufferWidth = Width;
		D3DPP.BackBufferHeight = Height;
	}
	D3DPP.Windowed = true;

	HRESULT tpr = pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, gData->MainWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED, &D3DPP, &pD3DD);
	if (!pD3DD)	//No Hardware?  Try Software.
		HRESULT tpr = pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_SW, gData->MainWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED, &D3DPP, &pD3DD);
	if (!pD3DD)	//No Software?  Try Reference.
		HRESULT tpr = pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, gData->MainWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED, &D3DPP, &pD3DD);
	if (!pD3DD)	//Nope?  Bye bye.
		MessageBox(gData->MainWnd, "Direct3D 8 Not Working Properly!", "Error!", MB_OK);

	if (Mode3D)
	{
		if (Depth == 2)
		{
			if (CM555)
				HRESULT rst = pD3DD->CreateTexture(256, 256, 1, NULL, D3DFMT_X1R5G5B5, D3DPOOL_MANAGED, &D3DTEX);
			else
				HRESULT rst = pD3DD->CreateTexture(256, 256, 1, NULL, D3DFMT_R5G6B5, D3DPOOL_MANAGED, &D3DTEX);
		} else if (Depth == 4) {
			HRESULT rst = pD3DD->CreateTexture(256, 256, 1, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &D3DTEX);
		}

		PALETTEENTRY TPAL[256];
		for (int i=0;i<256;i++)
		{
			TPAL[i].peRed = (BYTE) ((Palette[i & 0x3F] & 0x0000FF) >> 0);
			TPAL[i].peGreen = (BYTE) ((Palette[i & 0x3F] & 0x00FF00) >> 8);
			TPAL[i].peBlue = (BYTE) ((Palette[i & 0x3F] & 0xFF0000) >> 16);
			TPAL[i].peFlags = 0;
		}

		pD3DD->SetPaletteEntries(0, &TPAL[0]);
		pD3DD->SetCurrentTexturePalette(0);

		pD3DD->CreateVertexBuffer(6*sizeof(CUSTOMVERTEX), D3DUSAGE_WRITEONLY, D3DFVF_CUSTOMVERTEX, D3DPOOL_MANAGED, &D3DVB);

		BYTE *tpb;
	
		CUSTOMVERTEX g_Vertices[] =
		{
			{ 0,  0, 0.5f, 1.0f, 0xffffffff, 0, 0 }, // x, y, z, rhw, color
			{ Width, 0, 0.5f, 1.0f, 0xffffffff, 1, 0 },
			{  Width, Height, 0.5f, 1.0f, 0xffffffff, 1, .9375 },

			{  Width, Height, 0.5f, 1.0f, 0xffffffff, 1, .9375 },
			{  0, Height, 0.5f, 1.0f, 0xffffffff, 0, .9375 },
			{ 0,  0, 0.5f, 1.0f, 0xffffffff, 0, 0 }
		};

		D3DVB->Lock(0, 0, &tpb, D3DLOCK_NOSYSLOCK);

		memcpy(tpb, g_Vertices, 6*sizeof(CUSTOMVERTEX));

		D3DVB->Unlock();

		pD3DD->SetTexture( 0, D3DTEX );
		pD3DD->SetTextureStageState( 0, D3DTSS_MAGFILTER, FilterMode);
		pD3DD->SetTextureStageState( 0, D3DTSS_MINFILTER, FilterMode);
		pD3DD->SetTextureStageState( 0, D3DTSS_MIPFILTER, FilterMode);

		pD3DD->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0,0,255), 1.0f, 0L );

		D3DVIEWPORT8 tpv = { 0, 0, Width, Height, 0, 1 };
		pD3DD->SetViewport(&tpv);

		D3DLOCKED_RECT tprc;
		D3DTEX->LockRect(0, &tprc, NULL, D3DLOCK_NOSYSLOCK);

		pD3DD->SetStreamSource( 0, D3DVB, sizeof(CUSTOMVERTEX));
		pD3DD->SetVertexShader( D3DFVF_CUSTOMVERTEX );
	} else {
		pD3DD->GetBackBuffer(0, D3DBACKBUFFER_TYPE_MONO, &pD3DS);

		D3DLOCKED_RECT tpr;
		pD3DS->LockRect(&tpr, NULL, D3DLOCK_NOSYSLOCK);

		DrawArray = (unsigned char *) tpr.pBits;
		Pitch = tpr.Pitch;
	}

	FPSCnt = FSkip;
	DrawScreen();
}

void cNES_GFX::DrawScreen()
{
	FPSCnt++;
	if (FPSCnt > FSkip)
	{
		int SlwDwn = 0;
		FPSCnt = 0;

		if (Mode3D)
		{
			D3DTEX->UnlockRect(0);

			pD3DD->BeginScene();

			pD3DD->DrawPrimitive( D3DPT_TRIANGLELIST, 0, 2 );

			pD3DD->EndScene();

			pD3DD->Present( NULL, NULL, NULL, NULL );

			D3DLOCKED_RECT tpr;
			D3DTEX->LockRect(0, &tpr, NULL, D3DLOCK_NOSYSLOCK);

			DrawArray = (unsigned char *) tpr.pBits;
			Pitch = tpr.Pitch;
		} else {
			pD3DS->UnlockRect();

			pD3DD->Present(NULL, NULL, NULL, NULL);

			D3DLOCKED_RECT tpr;
			pD3DS->LockRect(&tpr, NULL, D3DLOCK_NOSYSLOCK);

			DrawArray = (unsigned char *) tpr.pBits;
			Pitch = tpr.Pitch;
		}

		LARGE_INTEGER tmpval;
		QueryPerformanceCounter(&tmpval);
		int tFPSnum;
		if (FSkip == -1)
			tFPSnum = (int) (((int) ClockFreq.QuadPart) / (tmpval.QuadPart - LastClockVal.QuadPart));
		else
			tFPSnum = (int) ((FSkip+1)*((int) ClockFreq.QuadPart) / (tmpval.QuadPart - LastClockVal.QuadPart));
		QueryPerformanceCounter(&LastClockVal);

		aFPSnum += tFPSnum;
		aFPScnt ++;
		if (aFPScnt == 4)
		{
			FPSnum = aFPSnum / 4;

			if (aFSkip)
			{
				if (FPSnum <= 51)
					FSkip++;
				if (FPSnum >= 69)
					FSkip--;
				if ((FSkip < -1) && (FPSnum > WantFPS))
				{
					FSkip = -1;
					SlwDwn = (aFPSnum-(WantFPS*4))/3;
//					Sleep(SlwDwn);
				}
				if (FSkip > 5) FSkip = 5;
			} else {
				if (FSkip < 0) FSkip = 0;
			}

			aFPScnt = 0;
			aFPSnum = 0;
		}
		
		char tpo[80];
		if (FSkip == -1)
			sprintf(tpo,"NinthStar - NES - %i FPS (%i SlwDwn)",FPSnum,SlwDwn);
		else
			sprintf(tpo,"NinthStar - NES - %i FPS (%i FSkip)",FPSnum,FSkip);
		SetWindowText(gData->MainWnd,tpo);
	}

	if (ShowTextCounter > 0)
		ShowTextCounter--;
}
