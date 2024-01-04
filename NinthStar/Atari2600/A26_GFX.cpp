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

#include "A26_GFX.h"

#include "..\Global.h"
#include <d3d8.h>

COLORREF PaletteBaseA26[256] =
{
  /* Grey */
  0x0, 0x1c1c1c, 0x393939, 0x595959, 
  0x797979, 0x929292, 0xababab, 0xbcbcbc, 
  0xcdcdcd, 0xd9d9d9, 0xe6e6e6, 0xececec, 
  0xf2f2f2, 0xf8f8f8, 0xffffff, 0xffffff, 
  
  /* Gold */
  0x391701, 0x5e2304, 0x833008, 0xa54716, 
  0xc85f24, 0xe37820, 0xff911d, 0xffab1d, 
  0xffc51d, 0xffce34, 0xffd84c, 0xffe651, 
  0xfff456, 0xfff977, 0xffff98, 0xffff98, 
  
  /* Orange */
  0x451904, 0x721e11, 0x9f241e, 0xb33a20, 
  0xc85122, 0xe36920, 0xff811e, 0xff8c25, 
  0xff982c, 0xffae38, 0xffc545, 0xffc559, 
  0xffc66d, 0xffd587, 0xffe4a1, 0xffe4a1, 
  
  /* Red Orange */
  0x4a1704, 0x7e1a0d, 0xb21d17, 0xc82119, 
  0xdf251c, 0xec3b38, 0xfa5255, 0xfc6161, 
  0xff706e, 0xff7f7e, 0xff8f8f, 0xff9d9e, 
  0xffabad, 0xffb9bd, 0xffc7ce, 0xffc7ce, 

  /* Pink */
  0x50568, 0x3b136d, 0x712272, 0x8b2a8c, 
  0xa532a6, 0xb938ba, 0xcd3ecf, 0xdb47dd, 
  0xea51eb, 0xf45ff5, 0xfe6dff, 0xfe7afd, 
  0xff87fb, 0xff95fd, 0xffa4ff, 0xffa4ff, 

  /* Purple */
  0x280479, 0x400984, 0x590f90, 0x70249d, 
  0x8839aa, 0xa441c3, 0xc04adc, 0xd054ed, 
  0xe05eff, 0xe96dff, 0xf27cff, 0xf88aff, 
  0xff98ff, 0xfea1ff, 0xfeabff, 0xfeabff, 

  /* Blue Purple */
  0x35088a, 0x420aad, 0x500cd0, 0x6428d0, 
  0x7945d0, 0x8d4bd4, 0xa251d9, 0xb058ec, 
  0xbe60ff, 0xc56bff, 0xcc77ff, 0xd183ff, 
  0xd790ff, 0xdb9dff, 0xdfaaff, 0xdfaaff, 

  /* Blue */
  0x51e81, 0x626a5, 0x82fca, 0x263dd4, 
  0x444cde, 0x4f5aee, 0x5a68ff, 0x6575ff, 
  0x7183ff, 0x8091ff, 0x90a0ff, 0x97a9ff, 
  0x9fb2ff, 0xafbeff, 0xc0cbff, 0xc0cbff, 

  /* Blue */
  0xc048b, 0x2218a0, 0x382db5, 0x483ec7, 
  0x584fda, 0x6159ec, 0x6b64ff, 0x7a74ff, 
  0x8a84ff, 0x918eff, 0x9998ff, 0xa5a3ff, 
  0xb1aeff, 0xb8b8ff, 0xc0c2ff, 0xc0c2ff, 

  /* Light Blue */
  0x1d295a, 0x1d3876, 0x1d4892, 0x1c5cac, 
  0x1c71c6, 0x3286cf, 0x489bd9, 0x4ea8ec, 
  0x55b6ff, 0x70c7ff, 0x8cd8ff, 0x93dbff, 
  0x9bdfff, 0xafe4ff, 0xc3e9ff, 0xc3e9ff, 

  /* Turquoise */
  0x2f4302, 0x395202, 0x446103, 0x417a12, 
  0x3e9421, 0x4a9f2e, 0x57ab3b, 0x5cbd55, 
  0x61d070, 0x69e27a, 0x72f584, 0x7cfa8d, 
  0x87ff97, 0x9affa6, 0xadffb6, 0xadffb6, 

  /* Green blue */
  0xa4108, 0xd540a, 0x10680d, 0x137d0f, 
  0x169212, 0x19a514, 0x1cb917, 0x1ec919, 
  0x21d91b, 0x47e42d, 0x6ef040, 0x78f74d, 
  0x83ff5b, 0x9aff7a, 0xb2ff9a, 0xb2ff9a, 

  /* Green */
  0x4410b, 0x5530e, 0x66611, 0x77714, 
  0x88817, 0x99b1a, 0xbaf1d, 0x48c41f, 
  0x86d922, 0x8fe924, 0x99f927, 0xa8fc41, 
  0xb7ff5b, 0xc9ff6e, 0xdcff81, 0xdcff81, 

  /* Yellow Green */
  0x2350f, 0x73f15, 0xc4a1c, 0x2d5f1e, 
  0x4f7420, 0x598324, 0x649228, 0x82a12e, 
  0xa1b034, 0xa9c13a, 0xb2d241, 0xc4d945, 
  0xd6e149, 0xe4f04e, 0xf2ff53, 0xf2ff53, 

  /* Orange Green */
  0x263001, 0x243803, 0x234005, 0x51541b, 
  0x806931, 0x978135, 0xaf993a, 0xc2a73e, 
  0xd5b543, 0xdbc03d, 0xe1cb38, 0xe2d836, 
  0xe3e534, 0xeff258, 0xfbff7d, 0xfbff7d, 

  /* Light Orange */
  0x401a02, 0x581f05, 0x702408, 0x8d3a13, 
  0xab511f, 0xb56427, 0xbf7730, 0xd0853a, 
  0xe19344, 0xeda04e, 0xf9ad58, 0xfcb75c, 
  0xffc160, 0xffc671, 0xffcb83, 0xffcb83,
};

COLORREF PaletteA26[256];

struct CUSTOMVERTEX
{
    FLOAT x, y, z, rhw; // The transformed position for the vertex.
    DWORD color;        // The vertex color.
	FLOAT       tu, tv;   // The texture coordinates.
};

// The custom FVF, which describes the custom vertex structure.
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)

cA26_GFX::cA26_GFX()
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
	
	for (int i=0;i<256;i++)
	{
		PaletteA26[i] = (PaletteBaseA26[i] & 0x00FF00) | ((PaletteBaseA26[i] & 0xFF0000) >> 16) | ((PaletteBaseA26[i] & 0x0000FF) << 16);
	
		switch (Depth)
		{
			case 2 :	//16-Bit Color
				{
					if (GetNearestColor(tdc,0x007D00) == 32768) CM555 = true;
					COLORREF tpc = PaletteA26[i];
					unsigned char Rtpc = (BYTE) ((tpc & 0x0000FF) >> 2);
					unsigned char Gtpc = (BYTE) (((tpc & 0x00FF00) >> 8) >> 2);
					unsigned char Btpc = (BYTE) (((tpc & 0xFF0000) >> 16) >> 2);

					Btpc >>= 1;
					Rtpc >>= 1;
					FixedPalette[i] = (Rtpc << 11) | (Gtpc << 5) | (Btpc << 0);
				}
				break;
			case 4 :	//32-Bit Color
				FixedPalette[i] = (PaletteA26[i] & 0x00FF00) | ((PaletteA26[i] & 0xFF0000) >> 16) | ((PaletteA26[i] & 0x0000FF) << 16);
				break;
			default :
				MessageBox(gData->MainWnd, "Sorry, Your Color Depth is Not Supported!", "Fatal Error", MB_OK);
				break;
		}
	}

	FPSCnt = 0;
	aFPScnt = 0;
	aFPSnum = 0;
	FSkip = 0;
	aFSkip = true;

	QueryPerformanceFrequency(&ClockFreq);

	pD3D = Direct3DCreate8( D3D_SDK_VERSION );
	pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &D3DDM);

	FilterMode = D3DTEXF_LINEAR;

	ReLoad(gData->Width, gData->Height, Mode3D);
}

void cA26_GFX::RePaint()
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

void cA26_GFX::ReLoad(short Width, short Height, bool NewMode)
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
	
	ZeroMemory(&D3DPP,sizeof(D3DPP));
	D3DPP.BackBufferFormat = D3DDM.Format;
	D3DPP.BackBufferCount = 1;
	D3DPP.SwapEffect = D3DSWAPEFFECT_FLIP;
	if (!Mode3D)
	{
		D3DPP.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
		D3DPP.BackBufferWidth = 160;
		D3DPP.BackBufferHeight = 192;
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
			TPAL[i].peRed = (BYTE) ((PaletteA26[i] & 0x0000FF) >> 0);
			TPAL[i].peGreen = (BYTE) ((PaletteA26[i] & 0x00FF00) >> 8);
			TPAL[i].peBlue = (BYTE) ((PaletteA26[i] & 0xFF0000) >> 16);
			TPAL[i].peFlags = 0;
		}

		pD3DD->SetPaletteEntries(0, &TPAL[0]);
		pD3DD->SetCurrentTexturePalette(0);

		pD3DD->CreateVertexBuffer(6*sizeof(CUSTOMVERTEX), D3DUSAGE_WRITEONLY, D3DFVF_CUSTOMVERTEX, D3DPOOL_MANAGED, &D3DVB);

		BYTE *tpb;
	
		CUSTOMVERTEX g_Vertices[] =
		{
			{ 0,  0, 0.5f, 1.0f, 0xffffffff, 0, 0 }, // x, y, z, rhw, color
			{ Width, 0, 0.5f, 1.0f, 0xffffffff, .625, 0 },
			{  Width, Height, 0.5f, 1.0f, 0xffffffff, .625, .75 },

			{  Width, Height, 0.5f, 1.0f, 0xffffffff, .625, .75 },
			{  0, Height, 0.5f, 1.0f, 0xffffffff, 0, .75 },
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

		pD3DD->SetStreamSource( 0, D3DVB, sizeof(CUSTOMVERTEX));
		pD3DD->SetVertexShader( D3DFVF_CUSTOMVERTEX );

		D3DLOCKED_RECT tpr;
		D3DTEX->LockRect(0, &tpr, NULL, D3DLOCK_NOSYSLOCK);

		DrawArray = (unsigned char *) tpr.pBits;
		Pitch = tpr.Pitch;
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

void cA26_GFX::DrawScreen()
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
				if ((FSkip < -1) && (FPSnum > 60))
				{
					FSkip = -1;
					SlwDwn = (aFPSnum-(60*4))/3;
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
			sprintf(tpo,"NinthStar - Atari2600 - %i FPS (%i SlwDwn)",FPSnum,SlwDwn);
		else
			sprintf(tpo,"NinthStar - Atari2600 - %i FPS (%i FSkip)",FPSnum,FSkip);
		SetWindowText(gData->MainWnd,tpo);
	}

	if (ShowTextCounter > 0)
		ShowTextCounter--;
}
