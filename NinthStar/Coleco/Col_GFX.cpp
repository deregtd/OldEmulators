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

#include "Col_GFX.h"

#include "..\Global.h"
#include <d3d8.h>

COLORREF ColecoPalette[16] = {
   {0xFFFFFF}, {0xAEC8FF}, {0xBBBBFF}, {0xDDB3EA},
   {0xFFB7EA}, {0xFFB3CC}, {0xFFC4B7}, {0xFFCCAE},
   {0xFFD9A2}, {0xCCE199}, {0xAEEEB7}, {0xAAF2CC},
   {0xA2EEFF}, {0xDDDDDD}, {0x111111}, {0x111111}
};

COLORREF ColPalette[16];

struct CUSTOMVERTEX
{
    FLOAT x, y, z, rhw; // The transformed position for the vertex.
    DWORD color;        // The vertex color.
	FLOAT       tu, tv;   // The texture coordinates.
};

// The custom FVF, which describes the custom vertex structure.
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)

void cCol_GFX::LoadPalette(int PalNum)
{
	HDC tdc = GetWindowDC(GetDesktopWindow());
	for (int i=0;i<16;i++)
	{
		ColPalette[i] = (ColecoPalette[i] & 0x00FF00) | ((ColecoPalette[i] & 0xFF0000) >> 16) | ((ColecoPalette[i] & 0x0000FF) << 16);
		switch (Depth)
		{
			case 2 :	//16-Bit Color
				{
					if (GetNearestColor(tdc,0x007D00) == 32768) CM555 = true;
					COLORREF tpc = ColPalette[i];
					unsigned char Rtpc = (BYTE) ((tpc & 0x0000FF) >> 2);
					unsigned char Gtpc = (BYTE) (((tpc & 0x00FF00) >> 8) >> 2);
					unsigned char Btpc = (BYTE) (((tpc & 0xFF0000) >> 16) >> 2);

					Btpc >>= 1;
					Rtpc >>= 1;
					FixedPalette[i] = (Rtpc << 11) | (Gtpc << 5) | (Btpc << 0);
				}
				break;
			case 4 :	//32-Bit Color
				FixedPalette[i] = (ColPalette[i] & 0x00FF00) | ((ColPalette[i] & 0xFF0000) >> 16) | ((ColPalette[i] & 0x0000FF) << 16);
				break;
			default :
				MessageBox(gData->MainWnd, "Sorry, Your Color Depth is Not Supported!", "Fatal Error", MB_OK);
				break;
		}
	}
	ReleaseDC(GetDesktopWindow(), tdc);

	ReLoad(gData->Width, gData->Height, Mode3D);
}

cCol_GFX::cCol_GFX()
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
	ReleaseDC(GetDesktopWindow(), tdc);

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

void cCol_GFX::RePaint()
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

void cCol_GFX::ReLoad(short Width, short Height, bool NewMode)
{
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
		HRESULT rst = pD3DD->CreateTexture(256, 256, 1, NULL, D3DFMT_P8, D3DPOOL_MANAGED, &D3DTEX);
	
		PALETTEENTRY TPAL[256];
		for (int i=0;i<256;i++)
		{
			TPAL[i].peRed = (BYTE) ((ColPalette[i & 0x3F] & 0x0000FF) >> 0);
			TPAL[i].peGreen = (BYTE) ((ColPalette[i & 0x3F] & 0x00FF00) >> 8);
			TPAL[i].peBlue = (BYTE) ((ColPalette[i & 0x3F] & 0xFF0000) >> 16);
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

void cCol_GFX::DrawScreen()
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
					Sleep(SlwDwn);
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
			sprintf(tpo,"NinthStar - Coleco - %i FPS (%i SlwDwn)",FPSnum,SlwDwn);
		else
			sprintf(tpo,"NinthStar - Coleco - %i FPS (%i FSkip)",FPSnum,FSkip);
		SetWindowText(gData->MainWnd,tpo);
	}

	if (ShowTextCounter > 0)
		ShowTextCounter--;
}
