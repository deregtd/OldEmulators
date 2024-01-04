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

#ifndef A2600DEBUGGER_H
#define A2600DEBUGGER_H

#include "6507.h"

class cA26_Debugger {
	public:
		cA26_Debugger();
		void SetMode(int NewMode);
		void Update();
		void AddInst();

		void DPrint(char * A, int B);
		void StartLogging();
		void StopLogging();

		bool Enabled;
		int Mode;

		bool	Logging;

		int		FontWidth, FontHeight;

		int		Depth;

		char	TraceComment[0x1000][32];
		
		int				DoubleSize;
		c6507			*CPU;
		cA26_TIA		*TIA;

		//Trace Window
		HDC		TraceWDC;		//  "
		HDC		TraceDC;							//  "
		int		AddyLine[64];
		bool	BreakP[0x10000];
		int		TraceOffset;		//-1 to center on PC, otherwise center on TraceOffset
		//Registers
		HDC		RegWDC;		//  "
		HDC		RegDC;							//  "

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

BOOL CALLBACK A26DumpProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK A26TraceProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK A26RegProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

#define DW_DMP_LEFT		4
#define DW_DMP_TOP		5
#define DW_DMP_WIDTH	6
#define DW_DMP_HEIGHT	7
#define DW_TRC_LEFT		10
#define DW_TRC_TOP		11
#define DW_TRC_WIDTH	12
#define DW_TRC_HEIGHT	13
#define DW_REG_LEFT		14
#define DW_REG_TOP		15
#define DW_REG_WIDTH	16
#define DW_REG_HEIGHT	17

//---------------------------------------------------------------------------
//Definitions - Addressing Modes
//---------------------------------------------------------------------------
#define ImmA					0 //#n
#define Abs						1 //Q
#define Zp						2 //Z
#define Imp						3 //[nothing]
#define Ind						4 //(Q)
#define Absx					5 //Q,X
#define Absy					6 //Q,Y
#define Zpx						7 //Z,X
#define Zpy						8 //Z,Y
#define Idx						9 //(Z,X)
#define Idy						10 //(Z),Y
#define Rel						11 //L
#define Acc						12 //A
#define ERA						13 //Error

#endif