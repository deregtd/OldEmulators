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
#include "NES_Debugger.h"

#include "..\Global.h"

const unsigned char CharSC[8] = {
	0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01
};

cNES_Debugger *Debugger;

cNES_PPU	*tPPU;
c2A03		*tCPU;

#define		FLAG_N				0x80
#define		FLAG_V				0x40
#define		FLAG_B				0x10
#define		FLAG_I				0x04
#define		FLAG_D				0x08
#define		FLAG_Z				0x02
#define		FLAG_C				0x01

BYTE TraceAddyMode[256]=
{//     0    1   2    3   4   5   6   7   8   9    A   B   C    D    E    F
		Imp ,Idx,ERA ,ERA,ERA,Zp ,Zp ,ERA,Imp,ImmA,Imp,ERA,ERA ,Abs ,Abs ,ERA,	//0x00
        Rel ,Idy,ERA ,ERA,ERA,Zpx,Zpx,ERA,Imp,Absy,Imp,ERA,ERA ,Absx,Absx,ERA,  //0x10
		Abs ,Idx,ERA ,ERA,Zp ,Zp ,Zp ,ERA,Imp,ImmA,Imp,ERA,Abs ,Abs ,Abs ,ERA,	//0x20
		Rel ,Idy,ERA ,ERA,ERA,Zpx,Zpx,ERA,Imp,Absy,ERA,ERA,ERA ,Absx,Absx,ERA,	//0x30
		Imp ,Idx,ERA ,ERA,ERA,Zp ,Zp ,ERA,Imp,ImmA,Imp,ERA,Abs ,Abs ,Abs ,ERA,	//0x40
		Rel ,Idy,ERA ,ERA,ERA,Zpx,Zpx,ERA,Imp,Absy,ERA,ERA,ERA ,Absx,Absx,ERA,	//0x50
		Imp ,Idx,ERA ,ERA,ERA,Zp ,Zp ,ERA,Imp,ImmA,Imp,ERA,Ind ,Abs ,Abs ,ERA,	//0x60
		Rel ,Idy,ERA ,ERA,ERA,Zpx,Zpx,ERA,Imp,Absy,ERA,ERA,ERA ,Absx,Absx,ERA,	//0x70
		ERA ,Idx,ERA ,ERA,Zp ,Zp ,Zp ,ERA,Imp,ImmA,Imp,ERA,Abs ,Abs ,Abs ,ERA,	//0x80
		Rel ,Idy,ERA ,ERA,Zpx,Zpx,Zpy,ERA,Imp,Absy,Imp,ERA,ERA ,Absx,ERA ,ERA,	//0x90
		ImmA,Idx,ImmA,ERA,Zp ,Zp ,Zp ,ERA,Imp,ImmA,Imp,ERA,Abs ,Abs ,Abs ,ERA,	//0xA0
		Rel ,Idy,ERA ,ERA,Zpx,Zpx,Zpy,ERA,Imp,Absy,Imp,ERA,Absx,Absx,Absy,ERA,	//0xB0
		ImmA,Idx,ERA ,ERA,Zp ,Zp ,Zp ,ERA,Imp,ImmA,Imp,ERA,Abs ,Abs ,Abs ,ERA,	//0xC0
		Rel ,Idy,ERA ,ERA,ERA,Zpx,Zpx,ERA,Imp,Absy,ERA,ERA,ERA ,Absx,Absx,ERA,	//0xD0
		ImmA,Idx,ERA ,ERA,Zp ,Zp ,Zp ,ERA,Imp,ImmA,Imp,ERA,Abs ,Abs ,Abs ,ERA,	//0xE0
		Rel ,Idy,ERA ,ERA,ERA,Zpx,Zpx,ERA,Imp,Absy,ERA,ERA,ERA ,Absx,Absx,ERA	//0xF0
};

char TraceArr[256][16] = {
"BRK ","ORA ","Bad ","Bad ","Bad ","ORA ","ASL ","Bad ","PHP ","ORA ","ASLA","Bad ","Bad ","ORA ","ASL ","Bad ", //00
"BPL ","ORA ","Bad ","Bad ","Bad ","ORA ","ASL ","Bad ","CLC ","ORA ","Bad ","Bad ","Bad ","ORA ","ASL ","Bad ", //10
"JSR ","AND ","Bad ","Bad ","BIT ","AND ","ROL ","Bad ","PLP ","AND ","ROLA","Bad ","BIT ","AND ","ROL ","Bad ", //20
"BMI ","AND ","Bad ","Bad ","Bad ","AND ","ROL ","Bad ","SEC ","AND ","Bad ","Bad ","Bad ","AND ","ROL ","Bad ", //30
"RTI ","EOR ","Bad ","Bad ","Bad ","EOR ","LSR ","Bad ","PHA ","EOR ","LSRA","Bad ","JMP ","EOR ","LSR ","Bad ", //40
"BVC ","EOR ","Bad ","Bad ","Bad ","EOR ","LSR ","Bad ","CLI ","EOR ","Bad ","Bad ","Bad ","EOR ","LSR ","Bad ", //50
"RTS ","ADC ","Bad ","Bad ","Bad ","ADC ","ROR ","Bad ","PLA ","ADC ","RORA","Bad ","JMP ","ADC ","ROR ","Bad ", //60
"BVS ","ADC ","Bad ","Bad ","Bad ","ADC ","ROR ","Bad ","SEI ","ADC ","Bad ","Bad ","Bad ","ADC ","ROR ","Bad ", //70
"Bad ","STA ","Bad ","Bad ","STY ","STA ","STX ","Bad ","DEY ","STA ","TXA ","Bad ","STY ","STA ","STX ","Bad ", //80
"BCC ","STA ","Bad ","Bad ","STY ","STA ","STX ","Bad ","TYA ","STA ","TXS ","Bad ","Bad ","STA ","Bad ","Bad ", //90
"LDY ","LDA ","LDX ","Bad ","LDY ","LDA ","LDX ","Bad ","TAY ","LDA ","TAX ","Bad ","LDY ","LDA ","LDX ","Bad ", //A0
"BCS ","LDA ","Bad ","Bad ","LDY ","LDA ","LDX ","Bad ","CLV ","LDA ","TSX ","Bad ","LDY ","LDA ","LDX ","Bad ", //B0
"CPY ","CMP ","Bad ","Bad ","CPY ","CMP ","DEC ","Bad ","INY ","CMP ","DEX ","Bad ","CPY ","CMP ","DEC ","Bad ", //C0
"BNE ","CMP ","Bad ","Bad ","Bad ","CMP ","DEC ","Bad ","CLD ","CMP ","Bad ","Bad ","Bad ","CMP ","DEC ","Bad ", //D0
"CPX ","SBC ","Bad ","Bad ","CPX ","SBC ","INC ","Bad ","INX ","SBC ","NOP ","Bad ","CPX ","SBC ","INC ","Bad ", //E0
"BEQ ","SBC ","Bad ","Bad ","Bad ","SBC ","INC ","Bad ","SED ","SBC ","Bad ","Bad ","Bad ","SBC ","INC ","Bad "  //F0
};

BYTE bytes[256]=
{
  1,2,1,1,1,2,2,1,1,2,1,1,1,3,3,1,
  2,2,1,1,1,2,2,1,1,3,1,1,1,3,3,1,
  3,2,1,1,2,2,2,1,1,2,1,1,3,3,3,1,
  2,2,1,1,1,2,2,1,1,3,1,1,1,3,3,1,
  1,2,1,1,1,2,2,1,1,2,1,1,3,3,3,1,
  2,2,1,1,1,2,2,1,1,3,1,1,1,3,3,1,
  1,2,1,1,1,2,2,1,1,2,1,1,3,3,3,1,
  2,2,1,1,1,2,2,1,1,3,1,1,1,3,3,1,
  1,2,1,1,2,2,2,1,1,1,1,1,3,3,3,1,
  2,2,1,1,2,2,2,1,1,3,1,1,1,3,1,1,
  2,2,2,1,2,2,2,1,1,2,1,1,3,3,3,1,
  2,2,1,1,2,2,2,1,1,3,1,1,3,3,3,1,
  2,2,1,1,2,2,2,1,1,2,1,1,3,3,3,1,
  2,2,1,1,1,2,2,1,1,3,1,1,1,3,3,1,
  2,2,1,1,2,2,2,1,1,2,1,1,3,3,3,1,
  2,2,1,1,1,2,2,1,1,3,1,1,1,3,3,1
};

unsigned char PatPal[4] = { 0x0D, 0x3C, 0x2A, 0x30 };

#define		VMemory(Addy)		*(PPU->CHRPointer[(Addy & 0x1C00) >> 10] + (Addy & 0x03FF))

short WindowPoses[2][32] = {
	//SingleSize Mode
	{
		256+8, 240+24+128+24,//Palette
		256+8, 240+24,		//Pattern
		0, 240+48,			//Dumps L/T
		256+8, 32+24+128,	//Dumps W/H
		256+8, 0,			//Name Tables
		256+8+256+8, 32+24+128+48,//Trace L/T
		256+8, 32+24+128+48+8,//Trace W/H
		256+8+256+8, 0,		//Registers L/T
		256+8, 32+24+128+48,	//Registers W/H
		0, 0		//MemView L/T
	},
	//DoubleSize Mode
	{
		0, 480+48+128+24,	//Palette
		0, 480+48,			//Pattern
		256+8, 480+48,		//Dumps L/T
		256, 32+24+128+24,	//Dumps W/H
		512+8, 0,			//Name Tables
		512+8+244, 480+24,//Trace L/T
		256+4, 32+24+128+48,//Trace W/H
		512+8, 480+24,		//Registers L/T
		244, 32+24+128+48,	//Registers W/H
		0, 0		//MemView L/T
	}
};

cNES_Debugger::cNES_Debugger()
{
	HDC TpHDC = GetDC(gData->MainWnd);
	//Palette
	PaletteDC = CreateCompatibleDC(TpHDC);
	PaletteBMP = CreateCompatibleBitmap(TpHDC,256,32);
	//Pattern Tables
	PatternDC = CreateCompatibleDC(TpHDC);
	PatternBMP = CreateCompatibleBitmap(TpHDC,256,128);
	//Name Tables
	NameDC = CreateCompatibleDC(TpHDC);
	//Trace Window
	TraceDC = CreateCompatibleDC(TpHDC);
	//Register Window
	RegDC = CreateCompatibleDC(TpHDC);

	ReleaseDC(gData->MainWnd,TpHDC);

	ZeroMemory(&BreakP, sizeof(BreakP));
	TraceOffset = -1;

	PatPalBase = 0;

	Logging = false;

	FontWidth = 7;
	FontHeight = 10;
	
	ZeroMemory(&TraceComment, sizeof(TraceComment));

	HDC tdc = GetWindowDC(GetDesktopWindow());
	Depth = (GetDeviceCaps(tdc,BITSPIXEL) >> 3);
	ReleaseDC(GetDesktopWindow(), tdc);
}

void cNES_Debugger::DPrint(char * A, int B)
{
	if (Logging)
		fwrite(A,1,B,LogFile);
}

void cNES_Debugger::SetMode(int NewMode)
{
	Debugger = this;

	if (DoubleSize > 1)
		DoubleSize = 1;
	Mode = NewMode;
	Enabled = (Mode > 0) ? true : false;

	HDC TpHDC = GetDC(gData->MainWnd);

	if (NTabChanged)
	{
		*NTabChanged = true;
 		*PalChanged = true;
		*PatChanged = true;
	}
	
	SetWindowPos(gData->MainWnd,HWND_TOP,0,0,0,0,SWP_NOSIZE);		//Move Main Window to (0,0)
	//Release Handles - Assume Mode 0
	DestroyWindow(DumpWnd);
	ReleaseDC(PaletteWnd, PaletteWDC);		//Palette
	DestroyWindow(PaletteWnd);
	ReleaseDC(PatternWnd, PatternWDC);		//Pattern Tables
	DestroyWindow(PatternWnd);
	ReleaseDC(NameWnd, NameWDC);			//Name Tables
	DestroyWindow(NameWnd);
	DeleteObject(NameBMP);
	if (gData->Main != 0)
		NameBMP = CreateCompatibleBitmap(TpHDC,256*(DoubleSize+1),240*(DoubleSize+1));
	ReleaseDC(TraceWnd, TraceWDC);			//Trace
	DestroyWindow(TraceWnd);
	DeleteObject(TraceBMP);
	if (gData->Main != 0)
	{
		TraceBMP = CreateCompatibleBitmap(TpHDC,WindowPoses[DoubleSize][DW_TRC_WIDTH]-8,WindowPoses[DoubleSize][DW_TRC_HEIGHT]-24);
		SelectObject(TraceDC,TraceBMP);
	}
	DestroyWindow(RegWnd);					//Registers
	if (gData->Main != 0)
	{
		RegBMP = CreateCompatibleBitmap(TpHDC,WindowPoses[DoubleSize][DW_REG_WIDTH]-8,WindowPoses[DoubleSize][DW_REG_HEIGHT]-24);
		SelectObject(RegDC,RegBMP);
	}

	ReleaseDC(gData->MainWnd,TpHDC);

	if (Mode >= 1) {	//Palette + Pattern Tables
		//Palette
		PaletteWnd = CreateDialog(gData->hInst, (LPCTSTR) IDD_PALETTE, gData->MainWnd, PaletteProc);
		SetWindowPos(PaletteWnd,HWND_TOP,WindowPoses[DoubleSize][DW_PAL_LEFT],WindowPoses[DoubleSize][DW_PAL_TOP],256+8,32+24,SWP_SHOWWINDOW);
		PaletteWDC = GetDC(PaletteWnd);
		//Pattern Tables
		PatternWnd = CreateDialog(gData->hInst, (LPCTSTR) IDD_PATTERN, gData->MainWnd, PatternProc);
		SetWindowPos(PatternWnd,HWND_TOP,WindowPoses[DoubleSize][DW_PAT_LEFT],WindowPoses[DoubleSize][DW_PAT_TOP],256+8,128+24,SWP_SHOWWINDOW);
		PatternWDC = GetDC(PatternWnd);
		//Dumps
		DumpWnd = CreateDialog(gData->hInst, (LPCTSTR) IDD_DUMPS, gData->MainWnd, DumpProc);
		SetWindowPos(DumpWnd,HWND_TOP,WindowPoses[DoubleSize][DW_DMP_LEFT],WindowPoses[DoubleSize][DW_DMP_TOP],WindowPoses[DoubleSize][DW_DMP_WIDTH],WindowPoses[DoubleSize][DW_DMP_HEIGHT],SWP_SHOWWINDOW);
	}
	if (Mode >= 2) {	// + Name Tables
		//Name Tables
		NameWnd = CreateDialog(gData->hInst, (LPCTSTR) IDD_NAME, gData->MainWnd, NameProc);
		SetWindowPos(NameWnd,HWND_TOP,WindowPoses[DoubleSize][DW_NAM_LEFT],WindowPoses[DoubleSize][DW_NAM_TOP],(DoubleSize+1)*256+8,(DoubleSize+1)*240+24,SWP_SHOWWINDOW);
		NameWDC = GetDC(NameWnd);
	}
	if (Mode >= 3) {	// + Registers
		//Registers
		RegWnd = CreateDialog(gData->hInst, (LPCTSTR) IDD_REGISTERS, gData->MainWnd, RegProc);
		SetWindowPos(RegWnd,HWND_TOP,WindowPoses[DoubleSize][DW_REG_LEFT],WindowPoses[DoubleSize][DW_REG_TOP],WindowPoses[DoubleSize][DW_REG_WIDTH],WindowPoses[DoubleSize][DW_REG_HEIGHT],SWP_SHOWWINDOW);
		RegWDC = GetDC(RegWnd);
		//Trace Window
		TraceWnd = CreateDialog(gData->hInst, (LPCTSTR) IDD_TRACE, gData->MainWnd, TraceProc);
		SetWindowPos(TraceWnd,HWND_TOP,WindowPoses[DoubleSize][DW_TRC_LEFT],WindowPoses[DoubleSize][DW_TRC_TOP],WindowPoses[DoubleSize][DW_TRC_WIDTH],WindowPoses[DoubleSize][DW_TRC_HEIGHT],SWP_SHOWWINDOW);
		TraceWDC = GetDC(TraceWnd);

		//Joint Shit
		HFONT tpf;
		int nHeight = -MulDiv(FontHeight, GetDeviceCaps(RegWDC, LOGPIXELSY), 72);
		tpf = CreateFont(nHeight, FontWidth, 0, 0, 0, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DRAFT_QUALITY, FF_MODERN, "Courier New");
		SelectObject(RegWDC, tpf);
		SelectObject(RegDC, tpf);
		SelectObject(TraceWDC, tpf);
		SelectObject(TraceDC, tpf);
		DeleteObject(tpf);
		SetBkMode(RegDC,TRANSPARENT);
		SetBkMode(TraceDC,TRANSPARENT);
		Update();
	}

	SetFocus(gData->MainWnd);
}

void cNES_Debugger::StartLogging()
{
	Logging = true;
	LogFile = fopen("c:\\debug.txt","w");
}

void cNES_Debugger::StopLogging()
{
	fclose(LogFile);
	Logging = false;
}

unsigned char cNES_Debugger::TraceMem(unsigned short Addy)
{
//	return(Bank[Addy >> 12]->ReadHandler(Addy >> 12, Addy));
	return(CPU->ReadHandler[Addy >> 12](Addy >> 12, Addy & 0xFFF));
}

void cNES_Debugger::DrawTraceLine(unsigned short Addy, short y)
{
	y -= 3;
	AddyLine[y/FontHeight] = Addy;
	
//	c2A03 *pC = CPU;
	char tpc[40] = { 0 };
	sprintf(tpc, "%04X  ", Addy);				//PC

	if ((Addy & 0x8000) && (TraceComment[Addy-0x8000][0]))
	{
		strcat(tpc, TraceComment[Addy-0x8000]);
	} else {
		char tpc2[30] = { 0 };						//Add Addy Mode Stuff

		switch (TraceAddyMode[TraceMem(Addy)])	
		{
		case ImmA : sprintf(tpc2,"%02X %02X     %s#$%02X", TraceMem(Addy), TraceMem(Addy + 1), TraceArr[TraceMem(Addy)], TraceMem(Addy + 1)); break;
		case Abs : sprintf(tpc2,"%02X %02X %02X  %s$%04X", TraceMem(Addy), TraceMem(Addy + 1), TraceMem(Addy + 2), TraceArr[TraceMem(Addy)], TraceMem(Addy + 1) | (TraceMem(Addy + 2) << 8)); break;
		case Zp : sprintf(tpc2,"%02X %02X     %s$%02X", TraceMem(Addy), TraceMem(Addy + 1), TraceArr[TraceMem(Addy)], TraceMem(Addy + 1)); break;
		case Acc : sprintf(tpc2,"%02X        %sA", TraceMem(Addy), TraceArr[TraceMem(Addy)]); break;
		case Imp : sprintf(tpc2,"%02X        %s", TraceMem(Addy), TraceArr[TraceMem(Addy)]); break;
		case ERA : sprintf(tpc2,"%02X        %s", TraceMem(Addy), TraceArr[TraceMem(Addy)]); break;
		case Ind : sprintf(tpc2,"%02X %02X %02X  %s($%04X)", TraceMem(Addy), TraceMem(Addy + 1), TraceMem(Addy + 2), TraceArr[TraceMem(Addy)], TraceMem(Addy + 1) | (TraceMem(Addy + 2) << 8)); break;
		case Absx : sprintf(tpc2,"%02X %02X %02X  %s$%04X,X", TraceMem(Addy), TraceMem(Addy + 1), TraceMem(Addy + 2), TraceArr[TraceMem(Addy)], TraceMem(Addy + 1) | (TraceMem(Addy + 2) << 8)); break;
		case Absy : sprintf(tpc2,"%02X %02X %02X  %s$%04X,Y", TraceMem(Addy), TraceMem(Addy + 1), TraceMem(Addy + 2), TraceArr[TraceMem(Addy)], TraceMem(Addy + 1) | (TraceMem(Addy + 2) << 8)); break;
		case Zpx : sprintf(tpc2,"%02X %02X     %s$%02X,X", TraceMem(Addy), TraceMem(Addy + 1), TraceArr[TraceMem(Addy)], TraceMem(Addy + 1)); break;
		case Zpy : sprintf(tpc2,"%02X %02X     %s$%02X,Y", TraceMem(Addy), TraceMem(Addy + 1), TraceArr[TraceMem(Addy)], TraceMem(Addy + 1)); break;
		case Idx : sprintf(tpc2,"%02X %02X     %s($%02X,X)", TraceMem(Addy), TraceMem(Addy + 1), TraceArr[TraceMem(Addy)], TraceMem(Addy + 1)); break;
		case Idy : sprintf(tpc2,"%02X %02X     %s($%02X),Y", TraceMem(Addy), TraceMem(Addy + 1), TraceArr[TraceMem(Addy)], TraceMem(Addy + 1)); break;
		case Rel :
			if (TraceMem(Addy + 1) & 0x80)
			{
				BYTE TpRelVal = ~TraceMem(Addy + 1) + 1;
	//			sprintf(tpc2,"%02X %02X     %s-$%02X", TraceMem(Addy), TraceMem(Addy + 1), TraceArr[TraceMem(Addy)], TpRelVal);	//Is this Right?...
				sprintf(tpc2,"%02X %02X     %s$%04X", TraceMem(Addy), TraceMem(Addy + 1), TraceArr[TraceMem(Addy)], Addy + 2 - TpRelVal);
			} else {
	//			sprintf(tpc2,"%02X %02X     %s$%02X", TraceMem(Addy), TraceMem(Addy + 1), TraceArr[TraceMem(Addy)], TraceMem(Addy + 1));
				sprintf(tpc2,"%02X %02X     %s$%04X", TraceMem(Addy), TraceMem(Addy + 1), TraceArr[TraceMem(Addy)], Addy + 2 + TraceMem(Addy + 1));
			}
			break;
		};

		strcat(tpc, tpc2);
	}

	if (BreakP[Addy])
	{
		HBRUSH RBrush = CreateSolidBrush(RGB(255,0,0));
		RECT trect;
		trect.left = 0;
		trect.top = y+3;
		trect.right = WindowPoses[DoubleSize][DW_TRC_WIDTH];
		trect.bottom = y+FontHeight+3;
		FillRect(TraceDC, &trect, RBrush);
		DeleteObject(RBrush);
	}

	TextOut(TraceDC, 1, y, tpc, strlen(tpc));
}

void cNES_Debugger::Update()
{
	if (Logging)
	{
		sprintf(&Out2[0],"A:%02X X:%02X Y:%02X P:%02X SP:%02X\n\0",CPU->A,CPU->X,CPU->Y,CPU->P,CPU->SP);
		DPrint(&Out1[0],strlen(Out1));
		DPrint(&Out2[0],strlen(Out2));
	}
	if (Mode >= 3)
	{
		//Check for BreakPoint
		if (BreakP[CPU->PC])
			gData->Main->Stop = true;

//		if (gData->Main->Stop)	//Only while stepping
		{
			MSG msg;
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				if (!TranslateAccelerator(gData->MainWnd, gData->hAccelTable, &msg)) 
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}

			HBRUSH WBrush = CreateSolidBrush(0xFFFFFF);
			RECT trect;
			trect.left = 0;
			trect.top = 0;
			trect.right = WindowPoses[DoubleSize][DW_REG_WIDTH];
			trect.bottom = WindowPoses[DoubleSize][DW_REG_HEIGHT];
			FillRect(RegDC, &trect, WBrush);

			trect.left = 0;
			trect.top = 0;
			trect.right = WindowPoses[DoubleSize][DW_TRC_WIDTH];
			trect.bottom = WindowPoses[DoubleSize][DW_TRC_HEIGHT];
			FillRect(TraceDC, &trect, WBrush);
			DeleteObject(WBrush);

			char tpc[40];
			sprintf(tpc,"PC: %04X",CPU->PC);		TextOut(RegDC, 1, 0, tpc, strlen(tpc));
			sprintf(tpc,"A: %02X",CPU->A);		TextOut(RegDC, 1, 1*FontHeight, tpc, strlen(tpc));
			sprintf(tpc,"X: %02X",CPU->X);		TextOut(RegDC, 1, 2*FontHeight, tpc, strlen(tpc));
			sprintf(tpc,"Y: %02X",CPU->Y);		TextOut(RegDC, 1, 3*FontHeight, tpc, strlen(tpc));
			sprintf(tpc,"SP: %02X",CPU->SP);		TextOut(RegDC, 1, 4*FontHeight, tpc, strlen(tpc));
			sprintf(tpc,"P: %02X", CPU->P);		TextOut(RegDC, 1, 5*FontHeight, tpc, strlen(tpc));
			sprintf(tpc,"->");
			if (CPU->P & FLAG_N) strcat(tpc,"N"); else strcat(tpc," ");
			if (CPU->P & FLAG_V) strcat(tpc,"V"); else strcat(tpc," ");
			strcat(tpc," ");
			if (CPU->P & FLAG_B) strcat(tpc,"B"); else strcat(tpc," ");
			if (CPU->P & FLAG_I) strcat(tpc,"I"); else strcat(tpc," ");
			if (CPU->P & FLAG_D) strcat(tpc,"D"); else strcat(tpc," ");
			if (CPU->P & FLAG_Z) strcat(tpc,"Z"); else strcat(tpc," ");
			if (CPU->P & FLAG_C) strcat(tpc,"C"); else strcat(tpc," ");
			TextOut(RegDC, 1, 6*FontHeight, tpc, strlen(tpc));

			if (PPU->SLnum < 240)
			{
				if (PPU->Xnum < 256)
					sprintf(tpc,"SLnum: %i, Pixel %i",PPU->SLnum, PPU->Xnum);
				else
					sprintf(tpc,"SLnum: %i, in HBlank",PPU->SLnum);
			} else {
				sprintf(tpc,"SLnum: %i, in VBlank", PPU->SLnum);
			}
			TextOut(RegDC, 1, 7*FontHeight, tpc, strlen(tpc));
			sprintf(tpc,"CPU Ticks: %i/%i", CPU->Clockticks, CPU->Clockticks / 12);		TextOut(RegDC, 1, 8*FontHeight, tpc, strlen(tpc));
			sprintf(tpc,"VRAMAddy: %04X", PPU->VRAMAddr);		TextOut(RegDC, 1, 9*FontHeight, tpc, strlen(tpc));

			int i;
			sprintf(tpc,"CPU Pages:");			TextOut(RegDC, 1, 12*FontHeight, tpc, strlen(tpc));
			for (i=0;i<8;i++)
			{ sprintf(tpc,"%02X",Map_GetPRG_ROM4(i+8));TextOut(RegDC, i*24, 13*FontHeight, tpc, strlen(tpc)); }
			sprintf(tpc,"PPU Pages:");			TextOut(RegDC, 1, 14*FontHeight, tpc, strlen(tpc));
			for (i=0;i<8;i++)
			{ sprintf(tpc,"%03X",Map_GetCHR_ROM1(i)); TextOut(RegDC, i*30, 15*FontHeight, tpc, strlen(tpc)); }

			BitBlt(RegWDC,0,0,WindowPoses[DoubleSize][DW_REG_WIDTH],WindowPoses[DoubleSize][DW_REG_HEIGHT],RegDC,0,0,SRCCOPY);

			//Add Disasm
			for (i=0;i<64;i++)
				AddyLine[i] = -1;

			unsigned short StartAddy;
			StartAddy = (TraceOffset == -1) ? CPU->PC : TraceOffset;
//			short StartY = (WindowPoses[DoubleSize][DW_TRC_HEIGHT]-24) / 2;
			int StartY = 10*FontHeight;
			StartY = StartY - (StartY % FontHeight);
		
			unsigned short CurrAddy = StartAddy;
			short MaxY = WindowPoses[DoubleSize][DW_TRC_HEIGHT]-24;
			MaxY = (int) (MaxY/FontHeight)*FontHeight;	//Little hack to make it scroll nicely
			if (!((MaxY/FontHeight) & 1))		// "
				MaxY+=FontHeight;				// "
			for (int CurrY=StartY; CurrY<MaxY; CurrY+=FontHeight)
			{
				DrawTraceLine(CurrAddy, CurrY);
				CurrAddy += bytes[TraceMem(CurrAddy)];
			}
			CurrAddy = StartAddy-0x100;
			unsigned short BackAddies[0x100];
			int FoundPtr = 0xFF;
			for (int TpVal=0;TpVal<0x100;TpVal++)
			{
				BackAddies[TpVal] = CurrAddy;
				CurrAddy += bytes[TraceMem(CurrAddy)];
				if (CurrAddy == StartAddy) FoundPtr = TpVal;
			}
			
			CurrAddy = BackAddies[FoundPtr--];
			for (int CurrY=StartY-FontHeight; CurrY>=0; CurrY-=FontHeight)
			{
				DrawTraceLine(CurrAddy, CurrY);
				CurrAddy = BackAddies[FoundPtr--];
			}

			MoveToEx(TraceDC, 1, StartY, NULL);
			LineTo(TraceDC, WindowPoses[DoubleSize][DW_TRC_WIDTH], StartY);

			MoveToEx(TraceDC, 1, StartY+FontHeight, NULL);
			LineTo(TraceDC, WindowPoses[DoubleSize][DW_TRC_WIDTH], StartY+FontHeight);

			BitBlt(TraceWDC,0,0,WindowPoses[DoubleSize][DW_TRC_WIDTH],WindowPoses[DoubleSize][DW_TRC_HEIGHT],TraceDC,0,0,SRCCOPY);

			UpdateGraphics();		
		}
	}
}

void cNES_Debugger::AddInst()
{
	if (Logging)
	{
		ZeroMemory(&Out1, sizeof(Out1));

		unsigned short Addy = CPU->PC;
		sprintf(Out1, "%04X    %02X", Addy, TraceMem(Addy));				//PC
		
		char tpc2[30] = { 0 };						//Add Addy Mode Stuff

		switch (TraceAddyMode[TraceMem(Addy)])	
		{
		case ImmA : sprintf(tpc2," %02X      %s#$%02X      ", TraceMem(Addy + 1), TraceArr[TraceMem(Addy)], TraceMem(Addy + 1)); break;
		case Abs : sprintf(tpc2," %02X %02X   %s$%04X     ", TraceMem(Addy + 1), TraceMem(Addy + 2), TraceArr[TraceMem(Addy)], TraceMem(Addy + 1) | (TraceMem(Addy + 2) << 8)); break;
		case Zp : sprintf(tpc2," %02X      %s$%02X       ", TraceMem(Addy + 1), TraceArr[TraceMem(Addy)], TraceMem(Addy + 1)); break;
		case Acc : sprintf(tpc2,"         %sA         ", TraceArr[TraceMem(Addy)]); break;
		case Imp : sprintf(tpc2,"         %s          ", TraceArr[TraceMem(Addy)]); break;
		case ERA : sprintf(tpc2,"         %s          ", TraceArr[TraceMem(Addy)]); break;
		//Add Comments for Addy pointed to/Actual Addy on These
		case Ind : sprintf(tpc2," %02X %02X   %s($%04X)   ", TraceMem(Addy + 1), TraceMem(Addy + 2), TraceArr[TraceMem(Addy)], TraceMem(Addy + 1) | (TraceMem(Addy + 2) << 8)); break;
		case Absx : sprintf(tpc2," %02X %02X   %s$%04X,X   ", TraceMem(Addy + 1), TraceMem(Addy + 2), TraceArr[TraceMem(Addy)], TraceMem(Addy + 1) | (TraceMem(Addy + 2) << 8)); break;
		case Absy : sprintf(tpc2," %02X %02X   %s$%04X,Y   ", TraceMem(Addy + 1), TraceMem(Addy + 2), TraceArr[TraceMem(Addy)], TraceMem(Addy + 1) | (TraceMem(Addy + 2) << 8)); break;
		case Zpx : sprintf(tpc2," %02X      %s$%02X,X    ", TraceMem(Addy + 1), TraceArr[TraceMem(Addy)], TraceMem(Addy + 1)); break;
		case Zpy : sprintf(tpc2," %02X      %s$%02X,Y    ", TraceMem(Addy + 1), TraceArr[TraceMem(Addy)], TraceMem(Addy + 1)); break;
		case Idx : sprintf(tpc2," %02X      %s($%02X,X)   ", TraceMem(Addy + 1), TraceArr[TraceMem(Addy)], TraceMem(Addy + 1)); break;
		case Idy : sprintf(tpc2," %02X      %s($%02X),Y   ", TraceMem(Addy + 1), TraceArr[TraceMem(Addy)], TraceMem(Addy + 1)); break;
		case Rel :
			if (TraceMem(Addy + 1) & 0x80)
			{
				BYTE TpRelVal = ~TraceMem(Addy + 1) + 1;
				sprintf(tpc2," %02X      %s-$%02X      ", TraceMem(Addy + 1), TraceArr[TraceMem(Addy)], TpRelVal);	//Is this Right?...
			} else {
				sprintf(tpc2," %02X      %s$%02X       ", TraceMem(Addy + 1), TraceArr[TraceMem(Addy)], TraceMem(Addy + 1));
			}
			break;
		};
		strcat(Out1, tpc2);
	}
}

void cNES_Debugger::UpdateGraphics()
{
	char DInc = Depth;
	long PatPtr;
	unsigned char PalVal;
	int MemAddy;
	if (Mode >= 1)
	{
		//Palette
		if (*PalChanged)
		{
			*PalChanged = false;
			int BaseVal;
			for (int z=0;z<16;z++)
				for (int x=0;x<16;x++)
					for (int y=0;y<16;y++)
					{
						BaseVal = ((y << 8) + ((z << 4) + x));
						memcpy(&PaletteArray[BaseVal*Depth],&FixedPalette[PPU->Palette[0][z]],DInc);
						memcpy(&PaletteArray[(BaseVal+0x1000)*Depth],&FixedPalette[PPU->Palette[1][z]],DInc);
					}
		}

		SetBitmapBits(PaletteBMP,DInc*256*32,&PaletteArray);
		SelectObject(PaletteDC,PaletteBMP);
		BitBlt(PaletteWDC,0,0,256,32,PaletteDC,0,0,SRCCOPY);

		//Pattern Tables
		if (*PatChanged)
		{
			PatPal[0] = PPU->Palette[0][0];
			for (int i=1;i<4;i++)
				PatPal[i] = PPU->Palette[(PatPalBase & 4) >> 2][((PatPalBase & 3) << 2) | i];

			*PatChanged = false;
			for (int t=0;t<2;t++)
			{
				for (int y=0;y<16;y++)
				{
					for (int x=0;x<16;x++)
					{
						MemAddy = (t << 12) | (y << 8) | (x << 4);
						for (int sy=0;sy<8;sy++)
						{
							PatPtr = (((y << 3) + sy) << 8) + (t << 7) + (x << 3);
							for (int sx=0;sx<8;sx++)
							{
								PalVal = (VMemory(MemAddy) & CharSC[sx]) >> (7-sx);
								PalVal |= ((VMemory(MemAddy+8) & CharSC[sx]) >> (7-sx)) << 1;
								
								memcpy(&PatternArray[PatPtr*DInc],&FixedPalette[PatPal[PalVal]],DInc);
								PatPtr++;
							}
							MemAddy++;
						}
					}
				}
			}
		}
		SetBitmapBits(PatternBMP,Depth*256*128,&PatternArray);
		SelectObject(PatternDC,PatternBMP);
		BitBlt(PatternWDC,0,0,256,128,PatternDC,0,0,SRCCOPY);
	}
	if (Mode >= 2)
	{
		//Name Tables
		int DS = DoubleSize;
		if (*NTabChanged)
		{
			*NTabChanged = false;
			int TabAddy = 0;
			int AttribTableVal, AttribNum;
			for (int NTy=0;NTy<2;NTy++)
				for (int NTx=0;NTx<2;NTx++)
					for (int TileY=0;TileY<30;TileY++)
						for (int TileX=0;TileX<32;TileX++)
						{
							AttribNum = (((TileX & 2) >> 1) | (TileY & 2)) << 1;
							AttribTableVal = ((*(PPU->CHRPointer[0x08 | NTx | (NTy << 1)] + (0x3C0 | ((TileY >> 2) << 3) | (TileX >> 2)))) & (3 << AttribNum)) >> AttribNum;
							MemAddy = ((PPU->ControlReg[0] & 0x10) << 8) | (*(PPU->CHRPointer[0x08 | NTx | (NTy << 1)] + (TileX | (TileY << 5))) << 4);
							for (int py=0;py<8;py+=2-DS)
							{
								if (DS)
									PatPtr = ((NTy << 9)*240) + (TileY << 12) | (py << 9) | (NTx << 8) | (TileX << 3);
								else
									PatPtr = (((NTy * 120)+(TileY << 2)) << 8) + (py << 7) + (NTx << 7) + (TileX << 2);
								
								for (int px=0;px<8;px+=2-DS)
								{
									PalVal = (VMemory(MemAddy) & CharSC[px]) >> (7-px);
									PalVal |= ((VMemory(MemAddy+8) & CharSC[px]) >> (7-px)) << 1;

									if (PalVal)
									{
										PalVal |= (AttribTableVal << 2);
										memcpy(&NameArray[PatPtr*DInc],&FixedPalette[PPU->Palette[0][PalVal]],DInc);
									} else {
										memcpy(&NameArray[PatPtr*DInc],&FixedPalette[PPU->Palette[0][0]],DInc);
									}
									
									PatPtr++;
								}
								MemAddy++;
							}
						}

			for (int i=0;i<(DS+1)*256;i++)
				memcpy(&NameArray[(((120*(DS+1))<<(8+DS)) + i)*DInc],&FixedPalette[0x41],DInc);
			for (int i=0;i<(DS+1)*240;i++)
				memcpy(&NameArray[(i*(DS+1)*256 + (128*(DS+1)))*DInc],&FixedPalette[0x41],DInc);
		}

		SetBitmapBits(NameBMP,DInc*(256*(DS+1))*(240*(DS+1)),&NameArray);
		SelectObject(NameDC,NameBMP);
		BitBlt(NameWDC,0,0,256*(DS+1),240*(DS+1),NameDC,0,0,SRCCOPY);
	}
}

BOOL CALLBACK PaletteProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_PAINT:
		BitBlt(Debugger->PaletteWDC,0,0,256,32,Debugger->PaletteDC,0,0,SRCCOPY);
		break;
	}
	return false;
}

BOOL CALLBACK PatternProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_PAINT:
		BitBlt(Debugger->PatternWDC,0,0,256,128,Debugger->PatternDC,0,0,SRCCOPY);
		break;
	case WM_LBUTTONUP:
		Debugger->PatPalBase = (Debugger->PatPalBase + 1) & 7;
		*Debugger->PatChanged = true;
		Debugger->UpdateGraphics();
		break;
	}
	return false;
}

BOOL CALLBACK NameProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_PAINT:
		BitBlt(Debugger->NameWDC,0,0,256*(Debugger->DoubleSize+1),240*(Debugger->DoubleSize+1),Debugger->NameDC,0,0,SRCCOPY);
		break;
	}
	return false;
}

BOOL CALLBACK DumpProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	switch (uMsg)
	{
		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId)
			{
				case IDC_DUMP_PPU_MEM:
					{
						FILE *PPUMemOut = fopen("PPU.Mem","wb");
						int i;
						for (i=0;i<12;i++)
							fwrite(Debugger->PPU->CHRPointer[i],1,0x400,PPUMemOut);
						for (i=0;i<8;i++)
							fwrite(&Debugger->PPU->Palette[0][0],1,0x20,PPUMemOut);
						fclose(PPUMemOut);
					}
					break;
				case IDC_START_LOGGING:
					Debugger->StartLogging();
					break;
				case IDC_STOP_LOGGING:
					Debugger->StopLogging();
					break;
				case IDC_IRQBUTTON:
					Debugger->CPU->IRQ();
					break;
			}
			
			break;
	}
	
	return false;
}

BOOL CALLBACK TraceProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_PAINT:
			BitBlt(Debugger->TraceWDC,0,0,WindowPoses[Debugger->DoubleSize][DW_TRC_WIDTH],WindowPoses[Debugger->DoubleSize][DW_TRC_HEIGHT],Debugger->TraceDC,0,0,SRCCOPY);
			break;
		case WM_KEYDOWN:
			switch (wParam)
			{
				case VK_HOME:		//HAX0R!!!!
					if (Debugger->TraceOffset == -1)
						Debugger->TraceOffset = Debugger->CPU->PC - 0x1000;
					else 
						Debugger->TraceOffset -= 0x1000;

					Debugger->Update();
					break;
				case VK_END:		//HAX0R!!!!
					if (Debugger->TraceOffset == -1)
						Debugger->TraceOffset = Debugger->CPU->PC + 0x1000;
					else 
						Debugger->TraceOffset += 0x1000;
					break;
				case VK_PRIOR:
					{
						int NewAddy = Debugger->AddyLine[0];
						if (NewAddy == Debugger->CPU->PC)
							NewAddy = -1;
						Debugger->TraceOffset = NewAddy;
						Debugger->Update();
					}
					break;
				case VK_UP:
					{
						short MaxAddy = 0;
						for (int i=0;i<64;i++)
						{
							if (Debugger->AddyLine[i] != -1)
							{
								MaxAddy = i;
							}
						}
						int NewAddy = Debugger->AddyLine[(MaxAddy/2) - 1];
						if (NewAddy == Debugger->CPU->PC)
							NewAddy = -1;
						Debugger->TraceOffset = NewAddy;
						Debugger->Update();
					}
					break;
				case VK_DOWN:
					{
						short MaxAddy = 0;
						for (int i=0;i<64;i++)
						{
							if (Debugger->AddyLine[i] != -1)
							{
								MaxAddy = i;
							}
						}
						int NewAddy = Debugger->AddyLine[(MaxAddy/2) + 1];
						if (NewAddy == Debugger->CPU->PC)
							NewAddy = -1;
						Debugger->TraceOffset = NewAddy;
						Debugger->Update();
					}
					break;
				case VK_NEXT:
					{
						short MaxAddy = 0;
						for (int i=0;i<64;i++)
						{
							if (Debugger->AddyLine[i] != -1)
							{
								MaxAddy = i;
							}
						}
						int NewAddy = Debugger->AddyLine[MaxAddy];
						if (NewAddy == Debugger->CPU->PC)
							NewAddy = -1;
						Debugger->TraceOffset = NewAddy;
						Debugger->Update();
					}
					break;
			
			}
			break;
		case WM_LBUTTONDOWN:
			{
				short xPos = LOWORD(lParam);
				short yPos = HIWORD(lParam);
				if ((xPos > 0) && (xPos < WindowPoses[Debugger->DoubleSize][DW_TRC_WIDTH]) && (yPos > 0) && (yPos < WindowPoses[Debugger->DoubleSize][DW_TRC_HEIGHT]))
				{
					Debugger->BreakP[Debugger->AddyLine[-1 + ((yPos-2)/Debugger->FontHeight)]] ^= true;
					bool tpb = gData->Main->Stop;
					gData->Main->Stop = true;
					Debugger->Update();
					gData->Main->Stop = tpb;
					SetFocus(gData->MainWnd);
				}
			}
			break;
	}
	
	return false;
}

BOOL CALLBACK RegProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_PAINT:
		BitBlt(Debugger->RegWDC,0,0,WindowPoses[Debugger->DoubleSize][DW_REG_WIDTH],WindowPoses[Debugger->DoubleSize][DW_REG_HEIGHT],Debugger->RegDC,0,0,SRCCOPY);
		break;
	}
	return false;
}
