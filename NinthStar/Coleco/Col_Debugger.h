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

#ifndef COL_DEBUGGER_H
#define COL_DEBUGGER_H

#include "Col_GFX.h"
#include "Col_Z80.h"
#include "Col_PPU.h"

class cCol_Debugger {
	public:
		cCol_Debugger();
		void SetMode(int NewMode);
		void Update();
		void UpdateGraphics();
		void AddInst();

		void DPrint(char * A, int B);
		void StartLogging();
		void StopLogging();

		bool Enabled;
		int Mode;

		bool	Logging;

		int		FontWidth, FontHeight;

		int		Depth;
		unsigned long FixedPalette[256];

		int				DoubleSize;
		cCol_Z80		*CPU;
		cCol_PPU		*PPU;

		int		AddyLine[64];
		bool	BreakP[0x10000];
		int		TraceOffset;		//-1 to center on PC, otherwise center on TraceOffset
		//Registers
		HDC		RegWDC;		//  "
		HDC		RegDC;							//  "
		//Trace
		HDC		TraceWDC;		//  "
		HDC		TraceDC;							//  "

	private:
		//Dumps
		HWND	DumpWnd;
		FILE	*LogFile;
		char	Out1[50], Out2[50];
		//Trace Window
		unsigned char NameArray[(512*480)*4];		//  "
		HWND	TraceWnd;		//Window
		HBITMAP	TraceBMP;							//Off-Screen Window
		void DrawTraceLine(unsigned short Addy, short y);
		unsigned char TraceMem(unsigned short Addy);
		//Registers
		HWND	RegWnd;			//Window
		HBITMAP	RegBMP;							//Off-Screen Window
};

BOOL CALLBACK Col_DumpProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Col_TraceProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Col_RegProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

#define DW_PAL_LEFT		0
#define DW_PAL_TOP		1
#define DW_PAT_LEFT		2
#define DW_PAT_TOP		3
#define DW_DMP_LEFT		4
#define DW_DMP_TOP		5
#define DW_DMP_WIDTH	6
#define DW_DMP_HEIGHT	7
#define DW_NAM_LEFT		8
#define DW_NAM_TOP		9
#define DW_TRC_LEFT		10
#define DW_TRC_TOP		11
#define DW_TRC_WIDTH	12
#define DW_TRC_HEIGHT	13
#define DW_REG_LEFT		14
#define DW_REG_TOP		15
#define DW_REG_WIDTH	16
#define DW_REG_HEIGHT	17
#define DW_MEM_LEFT		18
#define DW_MEM_TOP		19

#endif