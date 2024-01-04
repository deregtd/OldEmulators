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
#include "Global.h"
#include "resource.h"
#include "NinthStar.h"
#include "NES.h"

#include "time.h"

#define MAX_LOADSTRING 100

// Global Variables:
TCHAR szTitle[MAX_LOADSTRING];								// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];								// The title bar text
cGlobalData * gData;

bool ProperQuit = false;

// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

DWORD ThreadId;
HANDLE ThreadHandle;

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	MSG msg;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadString(hInstance, IDC_NINTHSTAR, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) 
		return FALSE;


	gData->Main->LoadSettings();

	if (__argc > 1)
	{
		gData->OpenFile(__argv[1]);
		gData->Main->Stop = false;
		gData->Main->Run();
		gData->PlaySnow = false;
	}

	if (gData->PlaySnow)
	{
		srand((unsigned int) time(NULL));
		int y,x, TPR;
		HDC tpd = GetDC(gData->MainWnd);

		HDC MemHDC = CreateCompatibleDC(tpd);
		HBITMAP VWBMP = CreateCompatibleBitmap(tpd, gData->Width, gData->Height);
		int Depth = (GetDeviceCaps(tpd,BITSPIXEL) >> 3);
		bool CM555 = false;
		if (GetNearestColor(tpd,0x007D00) == 32768) CM555 = true;

		unsigned char *BMParray = (unsigned char *) malloc(GetDeviceCaps(tpd, VERTRES) * GetDeviceCaps(tpd, HORZRES) * Depth);
		unsigned short *Tptr16;
		unsigned long *Tptr32;
		int w = gData->Width, h = gData->Height;
		while (gData->PlaySnow)
		{
			Tptr16 = (unsigned short *) BMParray;
			Tptr32 = (unsigned long *) BMParray;
			for (y=0;y<h;y++)
			{
				for (x=0;x<w;x++)
				{
					if (Depth == 4) {
						TPR = (int) (256*(((float) rand())/RAND_MAX));
						*Tptr32 = TPR | (TPR << 8) | (TPR << 16);
						Tptr32 ++;
					} else if (Depth == 2) {
						TPR = (int) (32*(((float) rand())/RAND_MAX));
						if (CM555)
							*Tptr16 = TPR | (TPR << 5) | (TPR << 10);
						else
							*Tptr16 = TPR | (TPR << 6) | (TPR << 11);
						Tptr16 ++;
					}
				}
			}
			SetBitmapBits(VWBMP,w*h*Depth,BMParray);
			SelectObject(MemHDC, VWBMP);
			StretchBlt(tpd, 0, 0, gData->Width, gData->Height, MemHDC, 0, 0, w, h, SRCCOPY);

			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				if (!TranslateAccelerator(gData->MainWnd, gData->hAccelTable, &msg)) 
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
				if (msg.message == WM_QUIT)
					gData->PlaySnow = false;
			}
			Sleep(10);
		}
		ReleaseDC(gData->MainWnd, tpd);
		DeleteDC(MemHDC);
		DeleteObject(VWBMP);
		free(BMParray);
	}

	if (msg.message == WM_QUIT)
		return msg.wParam;

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		if (!TranslateAccelerator(msg.hwnd, gData->hAccelTable, &msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage is only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
    wcex.hIcon          = LoadIcon(hInstance, (LPCTSTR)IDI_NINTHSTAR);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = NULL; //(LPCSTR) IDR_DEFMENU;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HANDLE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, 256+8, 48, NULL, NULL, hInstance, NULL);

	if (!hWnd)
		return FALSE;

	gData = new cGlobalData(hInstance, hWnd);
	gData->Main = new cNES(); 

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message) 
	{
		case WM_CREATE:
			break;
		case WM_CLOSE:
			PostMessage(hWnd,WM_TEMPDESTROY,0,0);
			break;
		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			if (wmId == IDM_ABOUT)
			{
				DialogBox(gData->hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
			} else if (wmId == IDM_EXIT) {
				PostMessage(hWnd,WM_TEMPDESTROY,0,0);
			} else if (wmId == IDM_OPEN) {
				gData->OpenFile(0);
			} else {
				gData->Main->EmuMsg(wmId, wParam, lParam);
			}
			break;
		case WM_SIZE:
			if (gData)
			{
				gData->Width = LOWORD(lParam);
				gData->Height = HIWORD(lParam);

				if (gData->Main)
					gData->Main->UpdateInterface();
			}
			break;
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);

			if (gData->Main)
				gData->Main->RePaint();
			
			EndPaint(hWnd, &ps);
			break;
		case WM_DESTROY:
			if (ProperQuit)
			{
				PostQuitMessage(0);
			} else {
				ProperQuit = true;
				if (gData->Main)
				{
					if (gData->Main->Stopped)
					{
						delete gData;
						DestroyWindow(hWnd);
					} else {
						gData->Main->Stop = true;
						gData->Main->NeedQuit = true;
					}
				} else {
					DestroyWindow(hWnd);
				}
			}
			break;
		case WM_TEMPDESTROY:
			ProperQuit = true;
			if (gData->Main)
			{
				if (gData->Main->Stopped)
				{
					delete gData;
					DestroyWindow(hWnd);
				} else {
					gData->Main->Stop = true;
					gData->Main->NeedQuit = true;
				}
			} else {
				DestroyWindow(hWnd);
			}
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}

// Mesage handler for about box.
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
				return TRUE;

		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			break;
	}
    return FALSE;
}
