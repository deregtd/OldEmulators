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

#ifndef GFXH
#define GFXH

#include <d3d8.h>
//#include <d3dx8core.h>

class cNES_GFX {
	public :
		cNES_GFX();
		
		~cNES_GFX()
		{
			if( D3DTEX != NULL )
				D3DTEX->Release();

			if( D3DVB != NULL )
				D3DVB->Release();

			if( pD3DS != NULL )
				pD3DS->Release();

			if( pD3DD != NULL )
				pD3DD->Release();

			if( pD3D != NULL )
				pD3D->Release();
		}

		void DrawScreen();
		void SetDoubleSize(bool DS);
		
		void ReLoad(short Width, short Height, int NewMode);
		void RePaint();
		void LoadPalette(int PalNum);

		unsigned long FixedPalette[512];
		char Depth;
		bool CM555;
		char TextDisp[40];
		int ShowTextCounter;
		
		HDC VWHDC;
		HDC MemHDC;
		HBITMAP VWBMP;
		unsigned char *DrawArray;

		//FPS
		LARGE_INTEGER ClockFreq;
		long ClockFreqVblank;
		LARGE_INTEGER LastClockVal;
		int FPSnum, FPSCnt, FSkip;
		int aFSkip;

		int Pitch;

		int Mode3D;
		int	FilterMode;

		int WantFPS;

	private :
		int aFPScnt, aFPSnum;
		
		//DX 8.0+
		LPDIRECT3D8					pD3D;
		D3DPRESENT_PARAMETERS		D3DPP;
		D3DDISPLAYMODE				D3DDM;
		LPDIRECT3DVERTEXBUFFER8		D3DVB;
		LPDIRECT3DTEXTURE8			D3DTEX;
		LPDIRECT3DSURFACE8			pD3DS;
		LPDIRECT3DDEVICE8			pD3DD;
};

#endif