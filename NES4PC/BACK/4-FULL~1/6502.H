//---------------------------------------------------------------------------
#ifndef Unit6502H
#define Unit6502H

#include <memory.h>
#include "Defines.h"
#pragma hdrstop

#include "video.h"
//---------------------------------------------------------------------------
//Processor Type Definitions
//---------------------------------------------------------------------------
typedef unsigned char BYTE;
typedef unsigned short int LBYTE;

#define A Mem.Accum
//---------------------------------------------------------------------------
//System-Used Functions
//---------------------------------------------------------------------------
void NewCPUMode(short int NTSCMode);
void Setup(TForm *tf, TForm *df, TMemo *ta, TMemo *tb);
void __fastcall Shutdown();

void __fastcall exec6502();
void __fastcall reset6502();
void HBlank();
void __fastcall nmi6502();
void __fastcall irq6502();

void __fastcall UpdateGGCodes();

void __fastcall Addrmode(register BYTE adrmode);
void __fastcall ExecOp(register BYTE opcode);

BYTE __fastcall MemoryTUGet();
void __fastcall MemoryTUEquals(register BYTE ta);

char * __fastcall ToBin(BYTE tc);
AnsiString ToBinC(BYTE tc, BYTE sb, BYTE eb);
//---------------------------------------------------------------------------
//Internal 6502 Structures
//---------------------------------------------------------------------------
extern MemSt Mem;
extern int Clockticks;
extern bool DebuggingTrace;
struct CCRSt {
	bool C,Z,I,D,B,V,N;
	BYTE __fastcall GetCCR()
	{ return((BYTE) ((this->N << 7) | (this->V << 6) | (this->B << 4) | (this->D << 3) | (this->I << 2) | (this->Z << 1) | this->C)); }
	void __fastcall MakeCCR(register BYTE mf)
	{ this->N = mf & 0x80; this->V = mf & 0x40; this->B = mf & 0x10; this->D = mf & 0x08; this->I = mf & 0x04; this->Z = mf & 0x02; this->C = mf & 0x01; }
};
extern BYTE curframe, BMParray[983040];
extern int frameskip, coldepth;
extern short int YMax;
extern LBYTE NTabAdr;
extern bool BkPTA, CPURunning;
extern COLORREF Palette[68];
struct JoypadSt {
	unsigned char type[2];
	bool Bits[2][24];
	unsigned char Count[2];
	bool Strobe[2];

	bool PaddleButtPressed;
	unsigned char PaddlePosition;
	bool ZapperButtPressed, ZapperSpriteInCrosshair;
	short int ZapperX, ZapperY;

	bool CoinInsert;

	void __fastcall UpdateSig()
	{
		switch (type[0]) {
			case jpJoypad :
				Bits[0][16] = true; Bits[0][17] = false; Bits[0][18] = false; Bits[0][19] = false;
				break;
        };

		switch (type[1]) {
			case jpJoypad :
				Bits[1][16] = false; Bits[1][17] = true; Bits[1][18] = false; Bits[1][19] = false;
				break;
			case jpPaddle :
				Bits[1][16] = false; Bits[1][17] = false; Bits[1][18] = false; Bits[1][19] = false;
				break;
			case jpZapper :
				Bits[1][16] = false; Bits[1][17] = false; Bits[1][18] = false; Bits[1][19] = false;
				break;
		};
	}
	void __fastcall SetStrobe(bool JN, bool ss)
	{
		Strobe[JN] = ss;
		if (!Strobe[JN]) Count[JN] = 0;
	}
	BYTE __fastcall Get(bool JN)
	{
		if ((type[1] != jpZapper) || (ZapperX < 0) || (ZapperX > 256) || (ZapperY < 0) || (ZapperY > YMax))
		{
//			ZapperSpriteInCrosshair = false;
		} else {
			unsigned char TileY = (BYTE) (((ZapperY + Mem.BgScrollY) >> 3) + 1);
			unsigned char TileYDiff = (BYTE) ((ZapperY + Mem.BgScrollY) & 7);
			unsigned char NTY = (BYTE) (((TileY >= 30) ^ (bool) (NTabAdr & 0x800)) << 1);
			unsigned char TileYM30 = (BYTE) (TileY % 30);
			bool NTabAdrBl = (bool) (NTabAdr & 0x400);
			unsigned char TileX = (BYTE) ((ZapperX + Mem.BgScrollX) >> 3);
			short int NameTable = (LBYTE) (((NTY | (bit5(TileX) ^ NTabAdrBl)) << 10) | 0x2000);
			short int addr = (short int) ((*Mem.PPU[NameTable | (TileYM30 << 5) | (TileX & 0x1F)] << 4) | TileYDiff);
			unsigned char bitnum = (BYTE) (0x80 >> ((ZapperX) & 7));
			unsigned char col = (BYTE) (((bool) (Mem.PatternTable[BkPTA][addr | 8] & bitnum) << 1) | (bool) (Mem.PatternTable[BkPTA][addr] & bitnum));
			unsigned char colup = (BYTE) (((*Mem.PPU[0x3C0 | NameTable | ((TileYM30 & 0x1C) << 1) | ((TileX & 0x1F) >> 2)] >> ((bit1(TileX) + (TileYM30 & 2)) << 1)) & 3) << 2);
			if (Palette[Mem.ImagePalette[colup | col]] == 0xFFFFFF)
			{
//				ZapperSpriteInCrosshair = true;
			} else {
//				ZapperSpriteInCrosshair = false;
			}
		}

		register unsigned char tmpb = 0;
		if (JN)
		{
			tmpb = 0x40;

			switch (this->type[1]) {
				case jpJoypad :
					tmpb |= (BYTE) (Bits[1][Count[1]] | 0x10);
    	        	break;
				case jpPaddle :
					if (Count[1] < 8)
					{ tmpb |= (BYTE) ((((bool) (bit(PaddlePosition, 7 - Count[1]))) ^ true) << 1); }
					else
					{ tmpb |= (BYTE) Bits[1][Count[1]]; }
					break;
				case jpZapper :
					tmpb |= (BYTE) (((BYTE) ZapperSpriteInCrosshair) << 3);
					tmpb |= (BYTE) ((ZapperButtPressed ^ true) << 4);
					break;
			};
		} else {
			if (type[1] == jpPaddle) tmpb |= (BYTE) (PaddleButtPressed << 1);

			tmpb |= (BYTE) (CoinInsert << 5);
			CoinInsert = false;

			switch (type[0]) {
				case jpJoypad :
					tmpb |= (BYTE) (Bits[0][Count[0]]);

					tmpb |= (BYTE) (((BYTE) ZapperSpriteInCrosshair) << 3);
					tmpb |= (BYTE) ((ZapperButtPressed ^ true) << 4);
					break;
			}
		}

		Count[JN]++;
		if (Count[JN] == 24) Count[JN] = 0;
		return(tmpb);
	}
};

struct GGCodeSt {
	bool CompareValueEnabled;
	unsigned short int Address;
	unsigned char Value;
	unsigned char CompareValue;
};

struct MMC3St {
	unsigned char Command, IRQCounter, IRQLatch;
	bool IRQEnable, PRGSelect, CHRSelect;
};

struct MMC1St {
	unsigned char Array,ArrayPtr,Reg[4];

	bool PRGSwitch;	//false = C000, true = 8000
	bool PRGSwitchSize;	//false = both into 0x8000, true = 16k into (PRGSwitch)
	bool VROMSwitchSize;	//false = both into 0x0000, true = 4k into 0x0000 & 0x1000
	bool PRGPageSwitch; //false = first 256k, true = second 256k

	void __fastcall UpdateReg(unsigned char regnum)
	{
		register LBYTE tpbt;
		Reg[regnum] = Array;
		ArrayPtr = 0; Array = 0;
		switch (regnum) {
			case 0 :
				switch (Reg[0] & 0x03) {
					case 0 :	Mem.UpdateNameTablePointers(MrNone); tprint(AnsiString("MMC1: MirrorChange: Single")); break;
					case 1 :	Mem.UpdateNameTablePointers(MrNone); tprint(AnsiString("MMC1: MirrorChange: Single")); break;
					case 2 :	Mem.UpdateNameTablePointers(MrVert); tprint(AnsiString("MMC1: MirrorChange: Vertical")); break;
					case 3 :	Mem.UpdateNameTablePointers(MrHorz); tprint(AnsiString("MMC1: MirrorChange: Horizontal")); break;
				};
				PRGSwitch = bit2(Reg[0]);
				PRGSwitchSize = bit3(Reg[0]);
				VROMSwitchSize = bit4(Reg[0]);
				return;
			case 1 :
				tpbt = (LBYTE) (((Reg[1] & 0x0F) << 3) & Mem.CHRBitMask);
				Mem.CHRPageNumNew[0] = tpbt; Mem.CHRPageNumNew[1] = (LBYTE) (tpbt + 1);
				Mem.CHRPageNumNew[2] = (LBYTE) (tpbt + 2); Mem.CHRPageNumNew[3] = (LBYTE) (tpbt + 3);
				if (VROMSwitchSize) {
					tprint(AnsiString("MMC1: CHRpg[0-3] = ") + AnsiString(tpbt) + AnsiString("-") + AnsiString(tpbt+3));
				} else {
					Mem.CHRPageNumNew[4] = (LBYTE) (tpbt + 4); Mem.CHRPageNumNew[5] = (LBYTE) (tpbt + 5);
					Mem.CHRPageNumNew[6] = (LBYTE) (tpbt + 6); Mem.CHRPageNumNew[7] = (LBYTE) (tpbt + 7);
					tprint(AnsiString("MMC1: CHRpg[0-7] = ") + AnsiString(tpbt) + AnsiString("-") + AnsiString(tpbt+7));
				}
				Mem.UpdateCHRPointers();
				PRGPageSwitch = bit4(Reg[1]);
				return;
			case 2 :
				if (VROMSwitchSize)
				{
					tpbt = (LBYTE) (((Reg[2] & 0x0F) << 3) & Mem.CHRBitMask);
					Mem.CHRPageNumNew[4] = tpbt; Mem.CHRPageNumNew[5] = (LBYTE) (tpbt + 1);
					Mem.CHRPageNumNew[6] = (LBYTE) (tpbt + 2); Mem.CHRPageNumNew[7] = (LBYTE) (tpbt + 3);
					Mem.UpdateCHRPointers();
					tprint(AnsiString("MMC1: CHRpg[4-7] = ") + AnsiString(tpbt) + AnsiString("-") + AnsiString(tpbt+3));
				}
				return;
			case 3 :
				if (!PRGSwitchSize) {	//false = 32
					tpbt = (BYTE) (((Reg[3] & 0x0F) | (PRGPageSwitch << 4)) & Mem.PRGBitMask);
					Mem.PRGPageNumNew[0] = tpbt; Mem.PRGPageNumNew[1] = (LBYTE) (tpbt + 1);
					Mem.PRGPageNumNew[2] = (LBYTE) (tpbt + 2); Mem.PRGPageNumNew[3] = (LBYTE) (tpbt + 3);
					Mem.UpdatePRGPointers();
					tprint(AnsiString("MMC1: PRGpg[0-3] = ") + AnsiString(tpbt) + AnsiString("-") + AnsiString(tpbt+3));
				} else {
					tpbt = (BYTE) ((((Reg[3] & 0x0F) | (PRGPageSwitch << 4)) << 1) & Mem.PRGBitMask);
					if (PRGSwitch) {
						Mem.PRGPageNumNew[0] = tpbt; Mem.PRGPageNumNew[1] = (LBYTE) (tpbt + 1);
						tprint(AnsiString("MMC1: PRGpg[0-1] = ") + AnsiString(tpbt) + AnsiString("-") + AnsiString(tpbt+1));
					} else {
						Mem.PRGPageNumNew[2] = tpbt; Mem.PRGPageNumNew[3] = (LBYTE) (tpbt + 1);
						tprint(AnsiString("MMC1: PRGpg[2-3] = ") + AnsiString(tpbt) + AnsiString("-") + AnsiString(tpbt+1));
					}
					Mem.UpdatePRGPointers();
				}
//				Mem.UpdatePRGPointers();
				UpdateGGCodes();
				return;
		};
	}
};                                  
//---------------------------------------------------------------------------
#endif
