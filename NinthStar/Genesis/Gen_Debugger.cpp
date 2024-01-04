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
#include "Gen_Debugger.h"

#include "..\Global.h"

cGen_Debugger *Debugger;

c68000		*tCPU;

#define		FLAG_N				0x80
#define		FLAG_V				0x40
#define		FLAG_B				0x10
#define		FLAG_I				0x04
#define		FLAG_D				0x08
#define		FLAG_Z				0x02
#define		FLAG_C				0x01


short GenWindowPoses[2][32] = {
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

cGen_Debugger::cGen_Debugger()
{
	HDC TpHDC = GetDC(gData->MainWnd);
	//Trace Window
	TraceDC = CreateCompatibleDC(TpHDC);
	//Register Window
	RegDC = CreateCompatibleDC(TpHDC);

	ReleaseDC(gData->MainWnd,TpHDC);

	ZeroMemory(&BreakP, sizeof(BreakP));
	TraceOffset = -1;

	Logging = false;

	FontWidth = 7;
	FontHeight = 10;
	
	ZeroMemory(&TraceComment, sizeof(TraceComment));

	Debugger = this;

	HDC tdc = GetWindowDC(GetDesktopWindow());
	Depth = (GetDeviceCaps(tdc,BITSPIXEL) >> 3);
	ReleaseDC(GetDesktopWindow(), tdc);
}

void cGen_Debugger::DPrint(char * A, int B)
{
	if (Logging)
		fwrite(A,1,B,LogFile);
	fflush(LogFile);
}

void cGen_Debugger::SetMode(int NewMode)
{
	Mode = NewMode;
	Enabled = (Mode > 0) ? true : false;

	HDC TpHDC = GetDC(gData->MainWnd);

	SetWindowPos(gData->MainWnd,HWND_TOP,0,0,0,0,SWP_NOSIZE);		//Move Main Window to (0,0)
	//Release Handles - Assume Mode 0
	DestroyWindow(DumpWnd);
	ReleaseDC(TraceWnd, TraceWDC);			//Trace
	DestroyWindow(TraceWnd);
	DeleteObject(TraceBMP);
	if (gData->Main != 0)
	{
		TraceBMP = CreateCompatibleBitmap(TpHDC,GenWindowPoses[DoubleSize][DW_TRC_WIDTH]-8,GenWindowPoses[DoubleSize][DW_TRC_HEIGHT]-24);
		SelectObject(TraceDC,TraceBMP);
	}
	DestroyWindow(RegWnd);					//Registers
	if (gData->Main != 0)
	{
		RegBMP = CreateCompatibleBitmap(TpHDC,GenWindowPoses[DoubleSize][DW_REG_WIDTH]-8,GenWindowPoses[DoubleSize][DW_REG_HEIGHT]-24);
		SelectObject(RegDC,RegBMP);
	}

	ReleaseDC(gData->MainWnd,TpHDC);

	if (Mode >= 1) {	//Dumps
		//Dumps
		DumpWnd = CreateDialog(gData->hInst, (LPCTSTR) IDD_DUMPS, gData->MainWnd, GenDumpProc);
		SetWindowPos(DumpWnd,HWND_TOP,GenWindowPoses[DoubleSize][DW_DMP_LEFT],GenWindowPoses[DoubleSize][DW_DMP_TOP],GenWindowPoses[DoubleSize][DW_DMP_WIDTH],GenWindowPoses[DoubleSize][DW_DMP_HEIGHT],SWP_SHOWWINDOW);
	}
	if (Mode >= 3) {	// + Registers
		//Registers
		RegWnd = CreateDialog(gData->hInst, (LPCTSTR) IDD_REGISTERS, gData->MainWnd, GenRegProc);
		SetWindowPos(RegWnd,HWND_TOP,GenWindowPoses[DoubleSize][DW_REG_LEFT],GenWindowPoses[DoubleSize][DW_REG_TOP],GenWindowPoses[DoubleSize][DW_REG_WIDTH],GenWindowPoses[DoubleSize][DW_REG_HEIGHT],SWP_SHOWWINDOW);
		RegWDC = GetDC(RegWnd);
		//Trace Window
		TraceWnd = CreateDialog(gData->hInst, (LPCTSTR) IDD_TRACE, gData->MainWnd, GenTraceProc);
		SetWindowPos(TraceWnd,HWND_TOP,GenWindowPoses[DoubleSize][DW_TRC_LEFT],GenWindowPoses[DoubleSize][DW_TRC_TOP],GenWindowPoses[DoubleSize][DW_TRC_WIDTH],GenWindowPoses[DoubleSize][DW_TRC_HEIGHT],SWP_SHOWWINDOW);
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

void cGen_Debugger::StartLogging()
{
	Logging = true;
	LogFile = fopen("c:\\debug.txt","w");
}

void cGen_Debugger::StopLogging()
{
	fclose(LogFile);
	Logging = false;
}

unsigned char cGen_Debugger::TraceMem(unsigned short Addy)
{
	return(CPU->MemGet(Addy));			//LELELELE
}

void cGen_Debugger::DrawTraceLine(unsigned short Addy, short y)
{
	y -= 3;
	AddyLine[y/FontHeight] = Addy;
	
	char tpc[40] = { 0 };
	sprintf(tpc, "%04X  ", Addy);				//PC

	char tpc2[30] = { 0 };						//Add Addy Mode Stuff

/*	switch (TraceAddyModeGen[TraceMem(Addy)])	
	{
	case ImmA : sprintf(tpc2,"%02X %02X     %s#$%02X", TraceMem(Addy), TraceMem(Addy + 1), TraceArrGen[TraceMem(Addy)], TraceMem(Addy + 1)); break;
	case Abs : sprintf(tpc2,"%02X %02X %02X  %s$%04X", TraceMem(Addy), TraceMem(Addy + 1), TraceMem(Addy + 2), TraceArrGen[TraceMem(Addy)], TraceMem(Addy + 1) | (TraceMem(Addy + 2) << 8)); break;
	case Zp : sprintf(tpc2,"%02X %02X     %s$%02X", TraceMem(Addy), TraceMem(Addy + 1), TraceArrGen[TraceMem(Addy)], TraceMem(Addy + 1)); break;
	case Acc : sprintf(tpc2,"%02X        %sA", TraceMem(Addy), TraceArrGen[TraceMem(Addy)]); break;
	case Imp : sprintf(tpc2,"%02X        %s", TraceMem(Addy), TraceArrGen[TraceMem(Addy)]); break;
	case ERA : sprintf(tpc2,"%02X        %s", TraceMem(Addy), TraceArrGen[TraceMem(Addy)]); break;
	case Ind : sprintf(tpc2,"%02X %02X %02X  %s($%04X)", TraceMem(Addy), TraceMem(Addy + 1), TraceMem(Addy + 2), TraceArrGen[TraceMem(Addy)], TraceMem(Addy + 1) | (TraceMem(Addy + 2) << 8)); break;
	case Absx : sprintf(tpc2,"%02X %02X %02X  %s$%04X,X", TraceMem(Addy), TraceMem(Addy + 1), TraceMem(Addy + 2), TraceArrGen[TraceMem(Addy)], TraceMem(Addy + 1) | (TraceMem(Addy + 2) << 8)); break;
	case Absy : sprintf(tpc2,"%02X %02X %02X  %s$%04X,Y", TraceMem(Addy), TraceMem(Addy + 1), TraceMem(Addy + 2), TraceArrGen[TraceMem(Addy)], TraceMem(Addy + 1) | (TraceMem(Addy + 2) << 8)); break;
	case Zpx : sprintf(tpc2,"%02X %02X     %s$%02X,X", TraceMem(Addy), TraceMem(Addy + 1), TraceArrGen[TraceMem(Addy)], TraceMem(Addy + 1)); break;
	case Zpy : sprintf(tpc2,"%02X %02X     %s$%02X,Y", TraceMem(Addy), TraceMem(Addy + 1), TraceArrGen[TraceMem(Addy)], TraceMem(Addy + 1)); break;
	case Idx : sprintf(tpc2,"%02X %02X     %s($%02X,X)", TraceMem(Addy), TraceMem(Addy + 1), TraceArrGen[TraceMem(Addy)], TraceMem(Addy + 1)); break;
	case Idy : sprintf(tpc2,"%02X %02X     %s($%02X),Y", TraceMem(Addy), TraceMem(Addy + 1), TraceArrGen[TraceMem(Addy)], TraceMem(Addy + 1)); break;
	case Rel :
		if (TraceMem(Addy + 1) & 0x80)
		{
			BYTE TpRelVal = ~TraceMem(Addy + 1) + 1;
			sprintf(tpc2,"%02X %02X     %s$%04X", TraceMem(Addy), TraceMem(Addy + 1), TraceArrGen[TraceMem(Addy)], Addy + 2 - TpRelVal);
		} else {
			sprintf(tpc2,"%02X %02X     %s$%04X", TraceMem(Addy), TraceMem(Addy + 1), TraceArrGen[TraceMem(Addy)], Addy + 2 + TraceMem(Addy + 1));
		}
		break;
	};

	strcat(tpc, tpc2);

	if (BreakP[Addy])
	{
		HBRUSH RBrush = CreateSolidBrush(RGB(255,0,0));
		RECT trect;
		trect.left = 0;
		trect.top = y+3;
		trect.right = GenWindowPoses[DoubleSize][DW_TRC_WIDTH];
		trect.bottom = y+FontHeight+3;
		FillRect(TraceDC, &trect, RBrush);
		DeleteObject(RBrush);
	}*/

	TextOut(TraceDC, 1, y, tpc, strlen(tpc));
}

void cGen_Debugger::Update()
{
	if (Logging)
	{
//		sprintf(&Out2[0],"A:%02X X:%02X Y:%02X P:%02X SP:%02X\n\0",CPU->A,CPU->X,CPU->Y,CPU->P,CPU->SP);
		DPrint(&Out1[0],strlen(Out1));
		DPrint(&Out2[0],strlen(Out2));
	}
	if (Mode >= 3)
	{
		//Check for BreakPoint
		if (BreakP[CPU->PC])
			gData->Main->Stop = true;

		if (gData->Main->Stop)	//Only while stepping
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
			trect.right = GenWindowPoses[DoubleSize][DW_REG_WIDTH];
			trect.bottom = GenWindowPoses[DoubleSize][DW_REG_HEIGHT];
			FillRect(RegDC, &trect, WBrush);

			trect.left = 0;
			trect.top = 0;
			trect.right = GenWindowPoses[DoubleSize][DW_TRC_WIDTH];
			trect.bottom = GenWindowPoses[DoubleSize][DW_TRC_HEIGHT];
			FillRect(TraceDC, &trect, WBrush);
			DeleteObject(WBrush);

//			char tpc[40];
//			sprintf(tpc,"PC: %04X",CPU->PC);		TextOut(RegDC, 1, 0, tpc, strlen(tpc));
//			sprintf(tpc,"A: %02X",CPU->A);		TextOut(RegDC, 1, 1*FontHeight, tpc, strlen(tpc));
//			sprintf(tpc,"X: %02X",CPU->X);		TextOut(RegDC, 1, 2*FontHeight, tpc, strlen(tpc));
//			sprintf(tpc,"Y: %02X",CPU->Y);		TextOut(RegDC, 1, 3*FontHeight, tpc, strlen(tpc));
//			sprintf(tpc,"SP: %02X",CPU->SP);		TextOut(RegDC, 1, 4*FontHeight, tpc, strlen(tpc));
//			sprintf(tpc,"P: %02X", CPU->P);		TextOut(RegDC, 1, 5*FontHeight, tpc, strlen(tpc));
/*			sprintf(tpc,"->");
			if (CPU->P & FLAG_N) strcat(tpc,"N"); else strcat(tpc," ");
			if (CPU->P & FLAG_V) strcat(tpc,"V"); else strcat(tpc," ");
			strcat(tpc," ");
			if (CPU->P & FLAG_B) strcat(tpc,"B"); else strcat(tpc," ");
			if (CPU->P & FLAG_I) strcat(tpc,"I"); else strcat(tpc," ");
			if (CPU->P & FLAG_D) strcat(tpc,"D"); else strcat(tpc," ");
			if (CPU->P & FLAG_Z) strcat(tpc,"Z"); else strcat(tpc," ");
			if (CPU->P & FLAG_C) strcat(tpc,"C"); else strcat(tpc," ");
			TextOut(RegDC, 1, 6*FontHeight, tpc, strlen(tpc));*/

//			sprintf(tpc,"ScanLine: %i", TIA->SLnum);	TextOut(RegDC, 1, 8*FontHeight, tpc, strlen(tpc));

			int i;
//			sprintf(tpc,"CPU Pages:");			TextOut(RegDC, 1, 12*FontHeight, tpc, strlen(tpc));
//			for (i=0;i<4;i++)
//			{ sprintf(tpc,"%02X",CPU->PageNum[i]); TextOut(RegDC, i*24, 13*FontHeight, tpc, strlen(tpc)); }

			BitBlt(RegWDC,0,0,GenWindowPoses[DoubleSize][DW_REG_WIDTH],GenWindowPoses[DoubleSize][DW_REG_HEIGHT],RegDC,0,0,SRCCOPY);

			//Add Disasm
			for (i=0;i<64;i++)
				AddyLine[i] = -1;

			unsigned short StartAddy;
			StartAddy = (TraceOffset == -1) ? CPU->PC : TraceOffset;
			int StartY = 10*FontHeight;
			StartY = StartY - (StartY % FontHeight);
		
			unsigned short CurrAddy = StartAddy;
			short MaxY = GenWindowPoses[DoubleSize][DW_TRC_HEIGHT]-24;
			MaxY = (int) (MaxY/FontHeight)*FontHeight;	//Little hack to make it scroll nicely
			if (!((MaxY/FontHeight) & 1))		// "
				MaxY+=FontHeight;				// "
			for (int CurrY=StartY; CurrY<MaxY; CurrY+=FontHeight)
			{
				DrawTraceLine(CurrAddy, CurrY);
//				CurrAddy += Bytes6507[TraceMem(CurrAddy)];
			}
			CurrAddy = StartAddy-0x100;
			unsigned short BackAddies[0x100];
			int FoundPtr = 0xFF;
			for (int TpVal=0;TpVal<0x100;TpVal++)
			{
				BackAddies[TpVal] = CurrAddy;
//				CurrAddy += Bytes6507[TraceMem(CurrAddy)];
				if (CurrAddy == StartAddy) FoundPtr = TpVal;
			}
			
			CurrAddy = BackAddies[FoundPtr--];
			for (int CurrY=StartY-FontHeight; CurrY>=0; CurrY-=FontHeight)
			{
				DrawTraceLine(CurrAddy, CurrY);
				CurrAddy = BackAddies[FoundPtr--];
				CurrAddy &= 0x1FFF;
			}

			MoveToEx(TraceDC, 1, StartY, NULL);
			LineTo(TraceDC, GenWindowPoses[DoubleSize][DW_TRC_WIDTH], StartY);

			MoveToEx(TraceDC, 1, StartY+FontHeight, NULL);
			LineTo(TraceDC, GenWindowPoses[DoubleSize][DW_TRC_WIDTH], StartY+FontHeight);

			BitBlt(TraceWDC,0,0,GenWindowPoses[DoubleSize][DW_TRC_WIDTH],GenWindowPoses[DoubleSize][DW_TRC_HEIGHT],TraceDC,0,0,SRCCOPY);
		}
	}
}

void cGen_Debugger::AddInst()
{
	if (Logging)
	{
		ZeroMemory(&Out1, sizeof(Out1));

		unsigned short Addy = CPU->PC;
		sprintf(Out1, "%04X    %02X", Addy, TraceMem(Addy));				//PC
		
		char tpc2[30] = { 0 };						//Add Addy Mode Stuff

/*		switch (TraceAddyModeGen[TraceMem(Addy)])	
		{
		case ImmA : sprintf(tpc2," %02X      %s#$%02X      ", TraceMem(Addy + 1), TraceArrGen[TraceMem(Addy)], TraceMem(Addy + 1)); break;
		case Abs : sprintf(tpc2," %02X %02X   %s$%04X     ", TraceMem(Addy + 1), TraceMem(Addy + 2), TraceArrGen[TraceMem(Addy)], TraceMem(Addy + 1) | (TraceMem(Addy + 2) << 8)); break;
		case Zp : sprintf(tpc2," %02X      %s$%02X       ", TraceMem(Addy + 1), TraceArrGen[TraceMem(Addy)], TraceMem(Addy + 1)); break;
		case Acc : sprintf(tpc2,"         %sA         ", TraceArrGen[TraceMem(Addy)]); break;
		case Imp : sprintf(tpc2,"         %s          ", TraceArrGen[TraceMem(Addy)]); break;
		case ERA : sprintf(tpc2,"         %s          ", TraceArrGen[TraceMem(Addy)]); break;
		//Add Comments for Addy pointed to/Actual Addy on These
		case Ind : sprintf(tpc2," %02X %02X   %s($%04X)   ", TraceMem(Addy + 1), TraceMem(Addy + 2), TraceArrGen[TraceMem(Addy)], TraceMem(Addy + 1) | (TraceMem(Addy + 2) << 8)); break;
		case Absx : sprintf(tpc2," %02X %02X   %s$%04X,X   ", TraceMem(Addy + 1), TraceMem(Addy + 2), TraceArrGen[TraceMem(Addy)], TraceMem(Addy + 1) | (TraceMem(Addy + 2) << 8)); break;
		case Absy : sprintf(tpc2," %02X %02X   %s$%04X,Y   ", TraceMem(Addy + 1), TraceMem(Addy + 2), TraceArrGen[TraceMem(Addy)], TraceMem(Addy + 1) | (TraceMem(Addy + 2) << 8)); break;
		case Zpx : sprintf(tpc2," %02X      %s$%02X,X    ", TraceMem(Addy + 1), TraceArrGen[TraceMem(Addy)], TraceMem(Addy + 1)); break;
		case Zpy : sprintf(tpc2," %02X      %s$%02X,Y    ", TraceMem(Addy + 1), TraceArrGen[TraceMem(Addy)], TraceMem(Addy + 1)); break;
		case Idx : sprintf(tpc2," %02X      %s($%02X,X)   ", TraceMem(Addy + 1), TraceArrGen[TraceMem(Addy)], TraceMem(Addy + 1)); break;
		case Idy : sprintf(tpc2," %02X      %s($%02X),Y   ", TraceMem(Addy + 1), TraceArrGen[TraceMem(Addy)], TraceMem(Addy + 1)); break;
		case Rel :
			if (TraceMem(Addy + 1) & 0x80)
			{
				BYTE TpRelVal = ~TraceMem(Addy + 1) + 1;
				sprintf(tpc2," %02X      %s-$%02X      ", TraceMem(Addy + 1), TraceArrGen[TraceMem(Addy)], TpRelVal);	//Is this Right?...
			} else {
				sprintf(tpc2," %02X      %s$%02X       ", TraceMem(Addy + 1), TraceArrGen[TraceMem(Addy)], TraceMem(Addy + 1));
			}
			break;
		};*/
		strcat(Out1, tpc2);
	}
}

BOOL CALLBACK GenDumpProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
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
				case IDC_START_LOGGING:
					Debugger->StartLogging();
					break;
				case IDC_STOP_LOGGING:
					Debugger->StopLogging();
					break;
			}
			
			break;
	}
	
	return false;
}

BOOL CALLBACK GenTraceProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_PAINT:
			BitBlt(Debugger->TraceWDC,0,0,GenWindowPoses[Debugger->DoubleSize][DW_TRC_WIDTH],GenWindowPoses[Debugger->DoubleSize][DW_TRC_HEIGHT],Debugger->TraceDC,0,0,SRCCOPY);
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
				if ((xPos > 0) && (xPos < GenWindowPoses[Debugger->DoubleSize][DW_TRC_WIDTH]) && (yPos > 0) && (yPos < GenWindowPoses[Debugger->DoubleSize][DW_TRC_HEIGHT]))
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

BOOL CALLBACK GenRegProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_PAINT:
		BitBlt(Debugger->RegWDC,0,0,GenWindowPoses[Debugger->DoubleSize][DW_REG_WIDTH],GenWindowPoses[Debugger->DoubleSize][DW_REG_HEIGHT],Debugger->RegDC,0,0,SRCCOPY);
		break;
	}
	return false;
}
