//---------------------------------------------------------------------------
#ifndef MappersH
#define MappersH

#include "Defines.h"
#pragma hdrstop
//---------------------------------------------------------------------------
extern MemSt Mem;
extern int Clockticks;
extern bool DebuggingTrace;
extern BYTE curframe, BMParray[983040];
extern int frameskip, coldepth;
extern short int YMax;
extern LBYTE NTabAdr;
extern bool BkPTA, CPURunning;
extern COLORREF Palette[68];

struct MMC1St { //M1St
	unsigned char Array,ArrayPtr,Reg[4];

	bool PRGSwitch;	//false = C000, true = 8000
	bool PRGSwitchSize;	//false = both into 0x8000, true = 16k into (PRGSwitch)
	bool VROMSwitchSize;	//false = both into 0x0000, true = 4k into 0x0000 & 0x1000
	bool PRGPageSwitch; //false = first 256k, true = second 256k

	void __fastcall UpdateReg(unsigned char regnum)
	{
                LBYTE tpbt;
		Reg[regnum] = Array;
		ArrayPtr = 0; Array = 0;
		switch (regnum) {
			case 0 :
				switch (Reg[0] & 0x03) {
                                        case 0 :        Mem.UpdateNameTablePointers(0,0,0,0); /*tprint(AnsiString("MMC1: MirrorChange: Single"));*/ break;
                                        case 1 :        Mem.UpdateNameTablePointers(1,1,1,1); /*tprint(AnsiString("MMC1: MirrorChange: Single"));*/ break;
                                        case 2 :        Mem.UpdateNameTablePointers(MrVert); /*tprint(AnsiString("MMC1: MirrorChange: Vertical"));*/ break;
                                        case 3 :        Mem.UpdateNameTablePointers(MrHorz); /*tprint(AnsiString("MMC1: MirrorChange: Horizontal"));*/ break;
				};
				PRGSwitch = bit2(Reg[0]);
                                PRGSwitchSize = bit3(Reg[0]);
                                VROMSwitchSize = bit4(Reg[0]);
                                return;
			case 1 :
                                if (VROMSwitchSize) {
                                        tpbt = (LBYTE) (((Reg[1] & 0x0F) << 2) & Mem.CHRBitMask);
                                        Mem.CHRPageNumNew[0] = tpbt; Mem.CHRPageNumNew[1] = (LBYTE) (tpbt + 1);
                                        Mem.CHRPageNumNew[2] = (LBYTE) (tpbt + 2); Mem.CHRPageNumNew[3] = (LBYTE) (tpbt + 3);
//                                        tprint(AnsiString("MMC1: CHRpg[0-3] = ") + AnsiString(tpbt) + AnsiString("-") + AnsiString(tpbt+3));
                                } else {
                                        tpbt = (LBYTE) (((Reg[1] & 0x0F) << 2) & Mem.CHRBitMask);
					Mem.CHRPageNumNew[0] = tpbt; Mem.CHRPageNumNew[1] = (LBYTE) (tpbt + 1);
					Mem.CHRPageNumNew[2] = (LBYTE) (tpbt + 2); Mem.CHRPageNumNew[3] = (LBYTE) (tpbt + 3);
					Mem.CHRPageNumNew[4] = (LBYTE) (tpbt + 4); Mem.CHRPageNumNew[5] = (LBYTE) (tpbt + 5);
					Mem.CHRPageNumNew[6] = (LBYTE) (tpbt + 6); Mem.CHRPageNumNew[7] = (LBYTE) (tpbt + 7);
//                                        tprint(AnsiString("MMC1: CHRpg[0-7] = ") + AnsiString(tpbt) + AnsiString("-") + AnsiString(tpbt+7));
                                }

				Mem.UpdateCHRPointers();
				PRGPageSwitch = bit4(Reg[1]);
                                return;
			case 2 :
                                if (VROMSwitchSize)
                                {
					tpbt = (LBYTE) (((Reg[2] & 0x0F) << 2) & Mem.CHRBitMask);
					Mem.CHRPageNumNew[4] = tpbt; Mem.CHRPageNumNew[5] = (LBYTE) (tpbt + 1);
					Mem.CHRPageNumNew[6] = (LBYTE) (tpbt + 2); Mem.CHRPageNumNew[7] = (LBYTE) (tpbt + 3);
					Mem.UpdateCHRPointers();
//                                        tprint(AnsiString("MMC1: CHRpg[4-7] = ") + AnsiString(Mem.CHRPageNum[4]) + AnsiString("-") + AnsiString(Mem.CHRPageNum[7]));
                                }
				return;
			case 3 :
                                if (!PRGSwitchSize) {   //false = 32
                                        tpbt = (BYTE) ((((Reg[3] & 0x0F) | (PRGPageSwitch << 4)) << 1) & Mem.PRGBitMask);
                                        Mem.PRGPageNum[0] = tpbt; Mem.PRGPageNum[1] = (LBYTE) (tpbt + 1);
                                        Mem.PRGPageNum[2] = (LBYTE) (tpbt + 2); Mem.PRGPageNum[3] = (LBYTE) (tpbt + 3);
//                                        tprint(AnsiString("MMC1: PRGpg[0-3] = ") + AnsiString(tpbt) + AnsiString("-") + AnsiString(tpbt+3));
				} else {
                                        tpbt = (BYTE) ((((Reg[3] & 0x0F) | (PRGPageSwitch << 4)) << 1) & Mem.PRGBitMask);
					if (PRGSwitch) {
                                                Mem.PRGPageNum[0] = tpbt; Mem.PRGPageNum[1] = (LBYTE) (tpbt + 1);
//                                                tprint(AnsiString("MMC1: PRGpg[0-1] = ") + AnsiString(tpbt) + AnsiString("-") + AnsiString(tpbt+1));
					} else {
                                                Mem.PRGPageNum[2] = tpbt; Mem.PRGPageNum[3] = (LBYTE) (tpbt + 1);
//                                                tprint(AnsiString("MMC1: PRGpg[2-3] = ") + AnsiString(tpbt) + AnsiString("-") + AnsiString(tpbt+1));
					}
				}
				UpdateGGCodes();
/*
                                if (PRGPageSwitch)
                                {
                                        Application->MessageBox("Bit 4 Set, Register 1","Debug Message",MB_OK);

                                        if (PRGSwitch) Application->MessageBox("PRGSwitch","Debug Message",MB_OK);
                                        if (PRGSwitchSize) Application->MessageBox("PRGSwitchSize","Debug Message",MB_OK);
                                }
*/
				return;
		};
	}
};
struct MMC3St { //M4St
	unsigned char Command, IRQCounter, IRQLatch;
	bool IRQEnable, PRGSelect, CHRSelect;
};
/*
struct MMC4St { //M9St + M10St
	unsigned char Latch[2];
};
*/
struct M16St {
        LBYTE IRQCounter;
        bool IRQEnabled;
};
struct M17St {
        LBYTE IRQCounter;
        bool IRQEnabled;
};
struct M24St {
        unsigned char Tmp;
        unsigned char IRQLatch;
        unsigned char IRQCounter;
        bool IRQEnable;
};
struct M90St {
	bool CHRSwitch[2]; 
	bool SLEnabled;
	BYTE CounterVal;
	BYTE CounterLatch;
};
struct M22in1St { //M230St
	BYTE Resets;
	bool ContraMode;
};

//---------------------------------------------------------------------------
#endif
