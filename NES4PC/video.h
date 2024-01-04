//---------------------------------------------------------------------------
#ifndef videoH
#define videoH
//---------------------------------------------------------------------------
#define cwhite 0xFFFFFF
#define cblack 0x000000
#define cblue 0xFF0000
#define cgreen 0x00FF00
#define cred 0x0000FF
//---------------------------------------------------------------------------
void DXPset(short int x,short int y,unsigned long color);
bool DXRender();
void DXClear();
bool DXOpen();
void DXClose();
bool DXLock();
bool DXUnlock();

void DrawScanline();
void PrepTileline();
void DrawTileline();
void FinishTileline();
void __fastcall DrawScreen();
void __fastcall VideoShutdown();
void UpdateVideoMode();
void __fastcall renderbig2();
void __fastcall renderbig();
void __fastcall render();
void __fastcall clscreenbig2();
void __fastcall clscreenbig();
void __fastcall clscreen();
void psetbig2(int x,int y,unsigned char color);
void __fastcall psetbig(int x,int y,unsigned char color);
void __fastcall pset(short int x,short int y,unsigned char color);
void __fastcall drawspritebasic(int x,int y,unsigned char ColUp,unsigned short int address, bool vflip, bool hflip);
void __fastcall drawbacktilebasic(int x,int y,unsigned char ColUp,unsigned short int address);
void VideoSetup(TForm *nf, RECT trct, TMemo *TrcMem, TMemo *StMem);
void __fastcall dprinto(AnsiString tp);
void __fastcall tprinto(AnsiString tp);

#define dprint(tp)      ;//if (DebuggingTrace) dprinto(tp)
#define tprint(tp)	;//if (DebuggingTrace) tprinto(tp)
#define MB(A, B)	Application->MessageBox(A, B, MB_OK);
//---------------------------------------------------------------------------
#include "6502.h"
//---------------------------------------------------------------------------
#endif
