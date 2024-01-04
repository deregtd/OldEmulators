//---------------------------------------------------------------------------
#include <mem.h>
#pragma hdrstop

#include "main.h"
#include "video.h"
#include "audio.h"
#include "6502.h"
//---------------------------------------------------------------------------
//Information Arrays
//---------------------------------------------------------------------------
BYTE addressmode[256]=
{// 0    1   2    3   4   5   6   7   8   9    A   B   C    D    E    F
	Imp ,Idx,ERA ,ERA,Imp,Zp ,Zp ,ERA,Imp,ImmA,Acc,ERA,ERA ,Abs ,Abs ,ERA,	//0x00
	Rel ,Idy,ERA ,ERA,ERA,Zpx,Zpx,ERA,Imp,Absy,ERA,ERA,ERA ,Absx,Absx,ERA,	//0x10
	Abs ,Idx,ERA ,ERA,Zp ,Zp ,Zp ,ERA,Imp,ImmA,Acc,ERA,Abs ,Abs ,Abs ,ERA,	//0x20
	Rel ,Idy,ERA ,ERA,ERA,Zpx,Zpx,ERA,Imp,Absy,ERA,ERA,ERA ,Absx,Absx,ERA,	//0x30
	Imp ,Idx,ERA ,ERA,ERA,Zp ,Zp ,ERA,Imp,ImmA,Acc,ERA,Abs ,Abs ,Abs ,ERA,	//0x40
	Rel ,Idy,ERA ,ERA,Imp,Zpx,Zpx,ERA,Imp,Absy,ERA,ERA,ERA ,Absx,Absx,ERA,	//0x50
	Imp ,Idx,ERA ,ERA,ERA,Zp ,Zp ,ERA,Imp,ImmA,Acc,ERA,Ind ,Abs ,Abs ,ERA,	//0x60
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

BYTE instruc[256]=
{//	0	1	2	3	4	5	6	7	8	9	A	B	C	D	E	F
	BRK,ORA,ERO,ERO,ERO,ORA,ASL,ERO,PHP,ORA,ASL,ERO,ERO,ORA,ASL,ERO,	//0x00
	BPL,ORA,ERO,ERO,ERO,ORA,ASL,ERO,CLC,ORA,ERO,ERO,ERO,ORA,ASL,ERO,	//0x10
	JSR,AND,ERO,ERO,BIT,AND,ROL,ERO,PLP,AND,ROL,ERO,BIT,AND,ROL,ERO,	//0x20
	BMI,AND,ERO,ERO,ERO,AND,ROL,ERO,SEC,AND,ERO,ERO,ERO,AND,ROL,ERO,	//0x30
	RTI,EOR,ERO,ERO,ERO,EOR,LSR,ERO,PHA,EOR,LSR,ERO,JMP,EOR,LSR,ERO,	//0x40
	BVC,EOR,ERO,ERO,ERO,EOR,LSR,ERO,CLI,EOR,ERO,ERO,ERO,EOR,LSR,ERO,	//0x50
	RTS,ADC,ERO,ERO,ERO,ADC,ROR,ERO,PLA,ADC,ROR,ERO,JMP,ADC,ROR,ERO,	//0x60
	BVS,ADC,ERO,ERO,ERO,ADC,ROR,ERO,SEI,ADC,ERO,ERO,ERO,ADC,ROR,ERO,	//0x70
	ERO,STA,ERO,ERO,STY,STA,STX,ERO,DEY,STA,TXA,ERO,STY,STA,STX,ERO,	//0x80
	BCC,STA,ERO,ERO,STY,STA,STX,ERO,TYA,STA,TXS,ERO,ERO,STA,ERO,ERO,	//0x90
	LDY,LDA,LDX,ERO,LDY,LDA,LDX,ERO,TAY,LDA,TAX,ERO,LDY,LDA,LDX,ERO,	//0xA0
	BCS,LDA,ERO,ERO,LDY,LDA,LDX,ERO,CLV,LDA,TSX,ERO,LDY,LDA,LDX,ERO,	//0xB0
	CPY,CMP,ERO,ERO,CPY,CMP,DEC,ERO,INY,CMP,DEX,ERO,CPY,CMP,DEC,ERO,	//0xC0
	BNE,CMP,ERO,ERO,ERO,CMP,DEC,ERO,CLD,CMP,ERO,ERO,ERO,CMP,DEC,ERO,	//0xD0
	CPX,SBC,ERO,ERO,CPX,SBC,INC,ERO,INX,SBC,NOP,ERO,CPX,SBC,INC,ERO,	//0xE0
	BEQ,SBC,ERO,ERO,ERO,SBC,INC,ERO,SED,SBC,ERO,ERO,ERO,SBC,INC,ERO		//0xF0
};

BYTE ticks[256]=
{
	7,6,0,0,2,3,5,0,3,2,2,0,0,4,6,0,
	3,5,0,0,0,4,6,0,2,4,0,0,0,4,7,0,
	6,6,0,0,3,3,5,0,4,2,2,0,4,4,6,0,
	3,5,0,0,0,4,6,0,2,4,2,0,0,4,7,0,
	6,6,0,0,0,3,5,0,3,2,2,0,3,4,6,0,
	3,5,0,0,0,4,6,0,2,4,0,0,0,4,7,0,
	6,6,0,0,0,3,5,0,4,2,2,0,5,4,6,0,
	3,5,0,0,0,4,6,0,2,4,0,0,0,4,7,0,
	0,6,0,0,3,3,3,0,2,2,2,0,4,4,4,0,
	3,5,0,0,4,4,4,0,2,4,2,0,0,4,0,0,
	2,6,2,0,3,3,3,0,2,2,2,0,4,4,4,0,
	3,5,0,0,4,4,4,0,2,4,2,0,4,4,4,0,
	2,6,0,0,3,3,5,0,2,2,2,0,4,4,6,0,
	3,5,0,0,0,4,6,0,2,4,0,0,0,4,7,0,
	2,6,0,0,3,3,5,0,2,2,2,0,4,4,6,0,
	3,5,0,0,0,4,6,0,2,4,0,0,0,4,7,0
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
	1,2,1,1,2,2,2,1,1,2,1,1,3,3,3,1,
	2,2,1,1,2,2,2,1,1,3,1,1,1,3,1,1,
	2,2,2,1,2,2,2,1,1,2,1,1,3,3,3,1,
	2,2,1,1,2,2,2,1,1,3,1,1,3,3,3,1,
	2,2,1,1,2,2,2,1,1,2,1,1,3,3,3,1,
	2,2,1,1,1,2,2,1,1,3,1,1,1,3,3,1,
	2,2,1,1,2,2,2,1,1,2,1,1,3,3,3,1,
	2,2,1,1,1,2,2,1,1,3,1,1,1,3,3,1
};

AnsiString Mn[57] = {"ADC","AND","ASL","BCC","BCS","BEQ","BIT","BMI","BNE","BPL","BRK","BVC",
"BVS","CLC","CLD","CLI","CLV","CMP","CPX","CPY","DEC","DEX","DEY","EOR","INC","INX","INY",
"JMP","JSR","LDA","LDX","LDY","LSR","NOP","ORA","PHA","PHP","PLA","PLP","ROL","ROR","RTI","RTS",
"SBC","SEC","SED","SEI","STA","STX","STY","TAX","TAY","TSX","TXA","TXS","TYA",
"Unknown"
};

AnsiString RegInfoLow[0x08] = { "PPUCtrl1","PPUCtrl2","PPUStat","SPRAddr","SPRIO","BgScroll","VRAMAddr","VRAMIO" };
AnsiString RegInfoHigh[0x18] = { "pAPUP1C1","pAPUP1C2","pAPUP1F1","pAPUP1F2","pAPUP2C1","pAPUP2C2","pAPUP2F1","pAPUP2F2","pAPUTC1","pAPUTC2","pAPUTF1","pAPUTF2","pAPUNC1","pAPUNC2","pAPUNF1","pAPUNF2","pAPUDMCC","pAPUDMCV","pAPUDMCA","pAPUDMCDL","SPRDMA","pAPUStCh","Joypad1","Joypad2" };

AnsiString MapperInfo[100] = {
"No Mapper", "MMC1", "UNROM", "CNROM", "MMC3", "MMC5", "FFE F4xxx", "AOROM",		//0-7
"FFE F3xxx", "MMC2", "MMC4", "Color Dreams", "", "", "", "100-in-1", "Bandai",		//8-16
"FFE F8xxx", "Jaleco SS8806", "Namcot 106", "", "Konami VRC4", "Konami VRC2 type A",//17-22
"Konami VRC2 type B", "Konami VRC6", "", "", "", "", "", "", "", "Irem G-101",		//23-32
"Taito TC0190", "Nina-1", "", "", "", "", "", "", "", "", "", "", "", "", "", "",	//33-48
"", "", "", "", "", "",	"", "", "", "", "", "", "", "", "",	"Tengen RAMBO-1",		//49-64
"Irem H-3001", "GNROM", "", "Sunsoft Mapper #4", "Sunsoft FME-7", "", "Camerica",	//63-71
"", "", "", "", "", "", "Irem 74HC161/32", "", "", "", "", "", "", "", "", "", "",	//72-88
"", "", "HK-SF3","","","","","","","","VS. System"									//89-99
};
extern BYTE LengthInfo[64];
extern LBYTE PlayDataRate[16];
//---------------------------------------------------------------------------
//Register Variables
//---------------------------------------------------------------------------
//Temporary Vars:
BYTE tmp, tmpBYTE;
LBYTE tmpLBYTE;
short int tmpshortint;
bool tmpbool;
//Debug-Related Vars
bool DebuggingTrace, DebuggingRegs, HaltOnNMI, HaltOnBadOp;
unsigned char tmpframes;
extern unsigned char GraphicsEngine;
extern bool Autoframeskip;
extern int FPSnum, Autoframeskipmax, frameskip;
extern TForm *VWFORM;
extern BYTE bitnumsp[2][8];
//Game Genie
int GGCodeNum;
GGCodeSt GGCode[50];
//Internal CPU

//BYTE SP;
LBYTE SP;

BYTE X, Y;
LBYTE PC;
int Clockticks, TU;
char TU2;
bool NMIonVBlank,NMIonSprHit,SSize,BkPTA,SpPTA,PPUAdrI,SprVis,BGVis,SprClip,BGClip,DispType;
bool VBlankOcc,Spr0Occ,ScLnSprCnt,VRAMWrFlg, VFirstRead, SFirstRead, CPURunning, TUMode;
LBYTE NTabAdr = 0x2000;
//unsigned long BGCol = cwhite;
CCRSt CCR;
MemSt Mem;
//Timing
short int LineRate,LineTotal,ScanLine,VBScanLine,MaxScanLine,MHBValue;
float LineTicks, LineTickCount, CPUSpeed;
bool VBlanking, MHBUsing;
int VBCount, VBSec, NMIClockTicks, LineTickCountInt;
extern short int YMax;
//Joystick
extern int JP1A, JP1B, JP1Select, JP1Start, JP1Up, JP1Down, JP1Left, JP1Right;
extern int JP2A, JP2B, JP2Select, JP2Start, JP2Up, JP2Down, JP2Left, JP2Right;
JoypadSt Joy;
extern COLORREF Palette[68];
//Sound
PulseChanSt PulseChan[2];
TriChanSt TriChan;
NoiseChanSt NoiseChan;
DCMChanSt DCMChan;
extern BYTE bWAVE[32];
extern struct _SNDChan SNDChannels[5];
//ROM
FILE * SRAMFileWr, * SRAMFileRd;
bool ROMTrainer;
MMC1St MMC1;
MMC3St MMC3;

//FPS
extern LARGE_INTEGER ClockFreq;
extern long ClockFreqVblank;
LARGE_INTEGER LastClockVal;
//---------------------------------------------------------------------------
//NES Emulator Setup
//---------------------------------------------------------------------------
void NewCPUMode(short int NTSCMode)
{
	if (NTSCMode == 1) {
		CPUSpeed = 1789772.5;
		VBSec = 60;
		YMax = 224;
		LineRate = 15720;
		VBScanLine = 240;
		MaxScanLine = 262;
	} else if (NTSCMode == 0) {
		CPUSpeed = 1773447.4;
		VBSec = 50;
		YMax = 240;
		LineRate = 15600;
		VBScanLine = 240;
		MaxScanLine = 312;
	}
	LineTicks = CPUSpeed / LineRate;
	ClockFreqVblank = (int) (ClockFreq.QuadPart / VBSec);
}
void Setup(TForm *tf, TForm *df, TMemo *ta, TMemo *tb)
{
	Joy.PaddlePosition = 172;
	Joy.UpdateSig();
	DebuggingTrace = false;
	DebuggingRegs = false;
	Mem.SetupPointers();

	VideoSetup(tf,df,ta,tb);
	AudioSetup(tf);
}

void __fastcall Shutdown()
{
	CPURunning = false;

	if (Mem.SRAMEnabled)
	{
		WriteSRAM();
		fclose(SRAMFileRd);
		fclose(SRAMFileWr);
	}
	
	VideoShutdown();
	AudioShutdown();
}
//---------------------------------------------------------------------------
//6502 General Commands
//---------------------------------------------------------------------------
void __fastcall exec6502()
{
	register BYTE opcode;
	while (CPURunning) {
		opcode = *Mem.Main[PC];
		Addrmode((BYTE) addressmode[opcode]);
		PC += bytes[opcode];
		ExecOp((BYTE) instruc[opcode]);
		Clockticks += ticks[opcode];
		if (Clockticks >= LineTickCountInt) HBlank();
		UpdateUI();
	}
}

void HBlank()
{
	ScanLine++;
	LineTickCount += LineTicks;
	LineTickCountInt = (int) LineTickCount;
	if (ScanLine == MaxScanLine) { VBlanking = false; ScanLine = 0; PrepTileline(); }
	MHBUsing = false;

	if (Mem.MapperNum == 4)
	{
		if (!VBlanking)
		{
			MMC3.IRQCounter--;
			if (MMC3.IRQCounter == 0)
			{
				if (MMC3.IRQEnable) irq6502();
				MMC3.IRQEnable = false;
			}
		}
	}

	if (GraphicsEngine == 2)
	{
		if (!VBlanking) DrawScanline();
	} else if (GraphicsEngine == 1) {
		if ((!VBlanking) && (ScanLine % 8 == 0)) DrawTileline();
	}

	unsigned char SSizeNew = (BYTE) ((SSize << 3) + 1);
	if ((bit5(Mem.Sprite[2])) && (Mem.Sprite[0] - 7 <= ScanLine) && (Mem.Sprite[0] + SSizeNew > ScanLine))
	{
		bool hflip = bit6(Mem.Sprite[2]);
		unsigned char ydiff = (BYTE) (ScanLine - (Mem.Sprite[0] - 7));
		short int addr = (short int) ((Mem.Sprite[1] - SSize + bit3(ydiff)) << 4);
		if (bit7(Mem.Sprite[2])) addr |= (LBYTE) (7 - (ydiff & 7));
			else addr |= (BYTE) (ydiff & 7);

		for (unsigned char xx=0;xx<8;xx++)
		{
			unsigned char col = (BYTE) (((bool) (Mem.PatternTable[SpPTA][addr | 8] & bitnumsp[hflip][xx]) << 1) | (bool) (Mem.PatternTable[SpPTA][addr] & bitnumsp[hflip][xx]));
			if (col) Spr0Occ = true;
		}
	}

	if (ScanLine == VBScanLine)
	{
		for (int i=0;i<2;i++)
		{
			if (PulseChan[i].Enabled)
			{
				if (PulseChan[i].LengthLeft > 0)
				{
					if ((PulseChan[i].VolFade == 0) && (PulseChan[i].Volume > 0))  PulseChan[i].Volume--;
					if ((PulseChan[i].VolFade == 1) && (PulseChan[i].Volume < 15)) PulseChan[i].Volume++;
					SNDChannels[i].bVol = PulseChan[i].Volume;
					PulseChan[i].LengthLeft--;
				} else if (!PulseChan[i].Loop) {
					if ((PulseChan[i].VolFade == 0) && (PulseChan[i].Volume > 0))  PulseChan[i].Volume--;
					if ((PulseChan[i].VolFade == 1) && (PulseChan[i].Volume < 15)) PulseChan[i].Volume++;
					SNDChannels[i].bVol = PulseChan[i].Volume;
				} else { SNDChannels[i].bVol = 0; }
			} else { SNDChannels[i].bVol = 0; }
		}
		StartFrm->SoundLengthLeftInfo->Caption = AnsiString(PulseChan[0].LengthLeft) + AnsiString("   ") + AnsiString(PulseChan[1].LengthLeft);

		tmpframes++;
		if (tmpframes >= (VBSec >> 1))
		{
			LARGE_INTEGER tmpval; int tmpval2;
			QueryPerformanceCounter(&tmpval);

			tmpval2 = (int) (tmpval.QuadPart - LastClockVal.QuadPart);
			FPSnum = ((VBSec >> 1) * ((int) ClockFreq.QuadPart)) / (tmpval2);

			if (Autoframeskip)
			{
				if (FPSnum > VBSec + 5) frameskip--;
				if (FPSnum < VBSec - 5) frameskip++;

				if (frameskip < 1) frameskip = 1;
				if (frameskip > Autoframeskipmax) frameskip = (BYTE) Autoframeskipmax;
			}

			StartFrm->FrameskipSlider->Position = (short int) frameskip;
			StartFrm->FPSInfo->Caption = FPSnum;

			QueryPerformanceCounter(&LastClockVal);

			tmpframes = 0;
		}

		if (Joy.type[1] == jpZapper)
		{
			if ((Joy.ZapperX < 0) || (Joy.ZapperX > 256) || (Joy.ZapperY < 0) || (Joy.ZapperY > YMax))
			{
				Joy.ZapperSpriteInCrosshair = false;
			} else {
				Joy.ZapperSpriteInCrosshair = false;
				tmpLBYTE = 0;
				while ((tmpLBYTE < 256) && (!Joy.ZapperSpriteInCrosshair))
				{
					unsigned char SprX, SprY;
					SprX = Mem.Sprite[tmpLBYTE + 3];
					SprY = (BYTE) (Mem.Sprite[tmpLBYTE] + 1);
					if ((Joy.ZapperX >= SprX) && (Joy.ZapperX <= SprX + 7) && (Joy.ZapperY >= SprY) && (Joy.ZapperY <= SprY + 7))
						Joy.ZapperSpriteInCrosshair = true;
					tmpLBYTE += (BYTE) 4;
				}
			}
		}

		FPSnum++;
		if (GraphicsEngine == 0)
		{
			DrawScreen();
		} else {
			FinishTileline();
		}
		if (NMIonVBlank) nmi6502();
		VBlanking = true;
		Spr0Occ = false;
		VBlankOcc = true;
	}
}

void __fastcall nmi6502()
{
//	PC++;
	PushPC();
	PushP();
	CCR.I = true;
	PC = (LBYTE) (Get16Bit(NMIVector));

	if (HaltOnNMI)
	{
		tprinto("NMI!  Halting!");
		DebuggingTrace = true;
		DebuggingRegs = true;
		CPURunning = false;
	}
}

void __fastcall irq6502()
{
	if (CCR.I) return;
//	CPURunning = false; tprinto("IRQ");
//	PC++;
	PushPC();
	PushP();
	CCR.I = true;
	PC = (LBYTE) (Get16Bit(IRQVector));
}

void __fastcall reset6502()
{
	bool DontSwapVRAM = false;
	switch (Mem.MapperNum) {
		case 0 :
			Mem.PRGPageNumNew[0] = 0; Mem.PRGPageNumNew[1] = 1;
			Mem.PRGPageNumNew[2] = (BYTE) (Mem.PRGPagesA - 2); Mem.PRGPageNumNew[3] = (BYTE) (Mem.PRGPagesA - 1);

			Mem.CHRPageNumNew[0] = 0; Mem.CHRPageNumNew[1] = 1; Mem.CHRPageNumNew[2] = 2;
			Mem.CHRPageNumNew[3] = 3; Mem.CHRPageNumNew[4] = 4; Mem.CHRPageNumNew[5] = 5;
			Mem.CHRPageNumNew[6] = 6; Mem.CHRPageNumNew[7] = 7;
			break;
		case 1 :
			Mem.PRGPageNumNew[0] = 0; Mem.PRGPageNumNew[1] = 1;
			Mem.PRGPageNumNew[2] = (BYTE) (Mem.PRGPagesA - 2); Mem.PRGPageNumNew[3] = (BYTE) (Mem.PRGPagesA - 1);

			Mem.CHRPageNumNew[0] = 0; Mem.CHRPageNumNew[1] = 1; Mem.CHRPageNumNew[2] = 2;
			Mem.CHRPageNumNew[3] = 3; Mem.CHRPageNumNew[4] = 4; Mem.CHRPageNumNew[5] = 5;
			Mem.CHRPageNumNew[6] = 6; Mem.CHRPageNumNew[7] = 7;
			break;
		case 2 :
			Mem.PRGPageNumNew[0] = 0; Mem.PRGPageNumNew[1] = 1;
			Mem.PRGPageNumNew[2] = (BYTE) (Mem.PRGPagesA - 2); Mem.PRGPageNumNew[3] = (BYTE) (Mem.PRGPagesA - 1);

			Mem.CHRPageNumNew[0] = 0; Mem.CHRPageNumNew[1] = 1; Mem.CHRPageNumNew[2] = 2;
			Mem.CHRPageNumNew[3] = 3; Mem.CHRPageNumNew[4] = 4; Mem.CHRPageNumNew[5] = 5;
			Mem.CHRPageNumNew[6] = 6; Mem.CHRPageNumNew[7] = 7;
			break;
		case 3 :
			Mem.PRGPageNumNew[0] = 0; Mem.PRGPageNumNew[1] = 1;
			Mem.PRGPageNumNew[2] = (BYTE) (Mem.PRGPagesA - 2); Mem.PRGPageNumNew[3] = (BYTE) (Mem.PRGPagesA - 1);

			Mem.CHRPageNumNew[0] = 0; Mem.CHRPageNumNew[1] = 1; Mem.CHRPageNumNew[2] = 2;
			Mem.CHRPageNumNew[3] = 3; Mem.CHRPageNumNew[4] = 4; Mem.CHRPageNumNew[5] = 5;
			Mem.CHRPageNumNew[6] = 6; Mem.CHRPageNumNew[7] = 7;
			break;
		case 4 :
			Mem.PRGPageNumNew[0] = 0; Mem.PRGPageNumNew[1] = 1;
			Mem.PRGPageNumNew[2] = (BYTE) (Mem.PRGPagesA - 2); Mem.PRGPageNumNew[3] = (BYTE) (Mem.PRGPagesA - 1);

			Mem.CHRPageNumNew[0] = 0; Mem.CHRPageNumNew[1] = 1; Mem.CHRPageNumNew[2] = 2;
			Mem.CHRPageNumNew[3] = 3; Mem.CHRPageNumNew[4] = 4; Mem.CHRPageNumNew[5] = 5;
			Mem.CHRPageNumNew[6] = 6; Mem.CHRPageNumNew[7] = 7;
			break;
		case 5 :
			Mem.PRGPageNumNew[0] = (BYTE) (Mem.PRGPagesA - 1); Mem.PRGPageNumNew[1] = Mem.PRGPageNumNew[0];
			Mem.PRGPageNumNew[2] = Mem.PRGPageNumNew[0]; Mem.PRGPageNumNew[3] = Mem.PRGPageNumNew[0];

// vvv Unknown vvv
			Mem.CHRPageNumNew[0] = 0; Mem.CHRPageNumNew[1] = 1; Mem.CHRPageNumNew[2] = 2;
			Mem.CHRPageNumNew[3] = 3; Mem.CHRPageNumNew[4] = 4; Mem.CHRPageNumNew[5] = 5;
			Mem.CHRPageNumNew[6] = 6; Mem.CHRPageNumNew[7] = 7;
// ^^^ Unknown ^^^
			break;
		case 6 :
// vvv Unknown vvv
			Mem.PRGPageNumNew[0] = 0; Mem.PRGPageNumNew[1] = 1;
			Mem.PRGPageNumNew[2] = 2; Mem.PRGPageNumNew[3] = 3;

			Mem.CHRPageNumNew[0] = 0; Mem.CHRPageNumNew[1] = 1; Mem.CHRPageNumNew[2] = 2;
			Mem.CHRPageNumNew[3] = 3; Mem.CHRPageNumNew[4] = 4; Mem.CHRPageNumNew[5] = 5;
			Mem.CHRPageNumNew[6] = 6; Mem.CHRPageNumNew[7] = 7;
// ^^^ Unknown ^^^
			break;
		case 7 :
			Mem.PRGPageNumNew[0] = 0; Mem.PRGPageNumNew[1] = 1;
			Mem.PRGPageNumNew[2] = 2; Mem.PRGPageNumNew[3] = 3;

			Mem.CHRPageNumNew[0] = 0; Mem.CHRPageNumNew[1] = 1; Mem.CHRPageNumNew[2] = 2;
			Mem.CHRPageNumNew[3] = 3; Mem.CHRPageNumNew[4] = 4; Mem.CHRPageNumNew[5] = 5;
			Mem.CHRPageNumNew[6] = 6; Mem.CHRPageNumNew[7] = 7;
			break;
		case 8 :
			Mem.PRGPageNumNew[0] = 0; Mem.PRGPageNumNew[1] = 1;
			Mem.PRGPageNumNew[2] = 2; Mem.PRGPageNumNew[3] = 3;

			Mem.CHRPageNumNew[0] = 0; Mem.CHRPageNumNew[1] = 1; Mem.CHRPageNumNew[2] = 2;
			Mem.CHRPageNumNew[3] = 3; Mem.CHRPageNumNew[4] = 4; Mem.CHRPageNumNew[5] = 5;
			Mem.CHRPageNumNew[6] = 6; Mem.CHRPageNumNew[7] = 7;
			break;
		case 9 :
			Mem.PRGPageNumNew[0] = 0; Mem.PRGPageNumNew[1] = (BYTE) (Mem.PRGPagesA - 3);
			Mem.PRGPageNumNew[2] = (BYTE) (Mem.PRGPagesA - 2); Mem.PRGPageNumNew[3] = (BYTE) (Mem.PRGPagesA - 1);

// vvv Unknown vvv
			Mem.CHRPageNumNew[0] = 0; Mem.CHRPageNumNew[1] = 1; Mem.CHRPageNumNew[2] = 2;
			Mem.CHRPageNumNew[3] = 3; Mem.CHRPageNumNew[4] = 4; Mem.CHRPageNumNew[5] = 5;
			Mem.CHRPageNumNew[6] = 6; Mem.CHRPageNumNew[7] = 7;
// ^^^ Unknown ^^^
			break;
		case 10 :
			Mem.PRGPageNumNew[0] = 0; Mem.PRGPageNumNew[1] = 1;
			Mem.PRGPageNumNew[2] = (BYTE) (Mem.PRGPagesA - 2); Mem.PRGPageNumNew[3] = (BYTE) (Mem.PRGPagesA - 1);

// vvv Unknown vvv
			Mem.CHRPageNumNew[0] = 0; Mem.CHRPageNumNew[1] = 1; Mem.CHRPageNumNew[2] = 2;
			Mem.CHRPageNumNew[3] = 3; Mem.CHRPageNumNew[4] = 4; Mem.CHRPageNumNew[5] = 5;
			Mem.CHRPageNumNew[6] = 6; Mem.CHRPageNumNew[7] = 7;
// ^^^ Unknown ^^^
			break;
		case 11 :
			Mem.PRGPageNumNew[0] = 0; Mem.PRGPageNumNew[1] = 1;
			Mem.PRGPageNumNew[2] = 2; Mem.PRGPageNumNew[3] = 3;

			Mem.CHRPageNumNew[0] = 0; Mem.CHRPageNumNew[1] = 1; Mem.CHRPageNumNew[2] = 2;
			Mem.CHRPageNumNew[3] = 3; Mem.CHRPageNumNew[4] = 4; Mem.CHRPageNumNew[5] = 5;
			Mem.CHRPageNumNew[6] = 6; Mem.CHRPageNumNew[7] = 7;
			break;
		case 15 :
			Mem.PRGPageNumNew[0] = 0; Mem.PRGPageNumNew[1] = 1;
			Mem.PRGPageNumNew[2] = 2; Mem.PRGPageNumNew[3] = 3;

			Mem.CHRPageNumNew[0] = 0; Mem.CHRPageNumNew[1] = 1; Mem.CHRPageNumNew[2] = 2;
			Mem.CHRPageNumNew[3] = 3; Mem.CHRPageNumNew[4] = 4; Mem.CHRPageNumNew[5] = 5;
			Mem.CHRPageNumNew[6] = 6; Mem.CHRPageNumNew[7] = 7;
			break;
		case 16 :
			Mem.PRGPageNumNew[0] = 0; Mem.PRGPageNumNew[1] = 1;
			Mem.PRGPageNumNew[2] = (BYTE) (Mem.PRGPagesA - 2); Mem.PRGPageNumNew[3] = (BYTE) (Mem.PRGPagesA - 1);

// vvv Unknown vvv
			Mem.CHRPageNumNew[0] = 0; Mem.CHRPageNumNew[1] = 1; Mem.CHRPageNumNew[2] = 2;
			Mem.CHRPageNumNew[3] = 3; Mem.CHRPageNumNew[4] = 4; Mem.CHRPageNumNew[5] = 5;
			Mem.CHRPageNumNew[6] = 6; Mem.CHRPageNumNew[7] = 7;
// ^^^ Unknown ^^^
			break;
		case 17 :
			Mem.PRGPageNumNew[0] = 0; Mem.PRGPageNumNew[1] = 1;
			Mem.PRGPageNumNew[2] = (BYTE) (Mem.PRGPagesA - 2); Mem.PRGPageNumNew[3] = (BYTE) (Mem.PRGPagesA - 1);

// vvv Unknown vvv
			Mem.CHRPageNumNew[0] = 0; Mem.CHRPageNumNew[1] = 1; Mem.CHRPageNumNew[2] = 2;
			Mem.CHRPageNumNew[3] = 3; Mem.CHRPageNumNew[4] = 4; Mem.CHRPageNumNew[5] = 5;
			Mem.CHRPageNumNew[6] = 6; Mem.CHRPageNumNew[7] = 7;
// ^^^ Unknown ^^^
			break;
		case 18 :
			Mem.PRGPageNumNew[0] = 0; Mem.PRGPageNumNew[1] = 1;
			Mem.PRGPageNumNew[2] = (BYTE) (Mem.PRGPagesA - 2); Mem.PRGPageNumNew[3] = (BYTE) (Mem.PRGPagesA - 1);

// vvv Unknown vvv
			Mem.CHRPageNumNew[0] = 0; Mem.CHRPageNumNew[1] = 1; Mem.CHRPageNumNew[2] = 2;
			Mem.CHRPageNumNew[3] = 3; Mem.CHRPageNumNew[4] = 4; Mem.CHRPageNumNew[5] = 5;
			Mem.CHRPageNumNew[6] = 6; Mem.CHRPageNumNew[7] = 7;
// ^^^ Unknown ^^^
			break;
		case 19 :
			Mem.PRGPageNumNew[0] = 0; Mem.PRGPageNumNew[1] = 1;
			Mem.PRGPageNumNew[2] = (BYTE) (Mem.PRGPagesA - 2); Mem.PRGPageNumNew[3] = (BYTE) (Mem.PRGPagesA - 1);

			Mem.CHRPageNumNew[0] = (BYTE) (Mem.PRGPagesA - 8); Mem.CHRPageNumNew[1] = (BYTE) (Mem.CHRPageNumNew[0] + 1); Mem.CHRPageNumNew[2] = (BYTE) (Mem.CHRPageNumNew[0] + 2);
			Mem.CHRPageNumNew[3] = (BYTE) (Mem.CHRPageNumNew[0] + 3); Mem.CHRPageNumNew[4] = (BYTE) (Mem.CHRPageNumNew[0] + 4); Mem.CHRPageNumNew[5] = (BYTE) (Mem.CHRPageNumNew[0] + 5);
			Mem.CHRPageNumNew[6] = (BYTE) (Mem.CHRPageNumNew[0] + 6); Mem.CHRPageNumNew[7] = (BYTE) (Mem.CHRPageNumNew[0] + 7);
			break;
		case 21 :
			Mem.PRGPageNumNew[0] = 0; Mem.PRGPageNumNew[1] = 1;
			Mem.PRGPageNumNew[2] = (BYTE) (Mem.PRGPagesA - 2); Mem.PRGPageNumNew[3] = (BYTE) (Mem.PRGPagesA - 1);

// vvv Unknown vvv
			Mem.CHRPageNumNew[0] = 0; Mem.CHRPageNumNew[1] = 1; Mem.CHRPageNumNew[2] = 2;
			Mem.CHRPageNumNew[3] = 3; Mem.CHRPageNumNew[4] = 4; Mem.CHRPageNumNew[5] = 5;
			Mem.CHRPageNumNew[6] = 6; Mem.CHRPageNumNew[7] = 7;
// ^^^ Unknown ^^^
			break;
		case 22 :
			Mem.PRGPageNumNew[0] = 0; Mem.PRGPageNumNew[1] = 1;
			Mem.PRGPageNumNew[2] = (BYTE) (Mem.PRGPagesA - 2); Mem.PRGPageNumNew[3] = (BYTE) (Mem.PRGPagesA - 1);

			Mem.CHRPageNumNew[0] = 0; Mem.CHRPageNumNew[1] = 1; Mem.CHRPageNumNew[2] = 2;
			Mem.CHRPageNumNew[3] = 3; Mem.CHRPageNumNew[4] = 4; Mem.CHRPageNumNew[5] = 5;
			Mem.CHRPageNumNew[6] = 6; Mem.CHRPageNumNew[7] = 7;
			break;
		case 23 :
			Mem.PRGPageNumNew[0] = 0; Mem.PRGPageNumNew[1] = 1;
			Mem.PRGPageNumNew[2] = (BYTE) (Mem.PRGPagesA - 2); Mem.PRGPageNumNew[3] = (BYTE) (Mem.PRGPagesA - 1);

// vvv Unknown vvv
			Mem.CHRPageNumNew[0] = 0; Mem.CHRPageNumNew[1] = 1; Mem.CHRPageNumNew[2] = 2;
			Mem.CHRPageNumNew[3] = 3; Mem.CHRPageNumNew[4] = 4; Mem.CHRPageNumNew[5] = 5;
			Mem.CHRPageNumNew[6] = 6; Mem.CHRPageNumNew[7] = 7;
// ^^^ Unknown ^^^
			break;
		case 24 :
			Mem.PRGPageNumNew[0] = 0; Mem.PRGPageNumNew[1] = 1;
			Mem.PRGPageNumNew[2] = (BYTE) (Mem.PRGPagesA - 2); Mem.PRGPageNumNew[3] = (BYTE) (Mem.PRGPagesA - 1);

//			Mem.CHRPageNumNew[0] = 0; Mem.CHRPageNumNew[1] = 1; Mem.CHRPageNumNew[2] = 2;
//			Mem.CHRPageNumNew[3] = 3; Mem.CHRPageNumNew[4] = 4; Mem.CHRPageNumNew[5] = 5;
//			Mem.CHRPageNumNew[6] = 6; Mem.CHRPageNumNew[7] = 7;
			DontSwapVRAM = true;
			break;
		case 32 :
			Mem.PRGPageNumNew[0] = 0; Mem.PRGPageNumNew[1] = 1;
			Mem.PRGPageNumNew[2] = (BYTE) (Mem.PRGPagesA - 2); Mem.PRGPageNumNew[3] = (BYTE) (Mem.PRGPagesA - 1);

// vvv Unknown vvv
			Mem.CHRPageNumNew[0] = 0; Mem.CHRPageNumNew[1] = 1; Mem.CHRPageNumNew[2] = 2;
			Mem.CHRPageNumNew[3] = 3; Mem.CHRPageNumNew[4] = 4; Mem.CHRPageNumNew[5] = 5;
			Mem.CHRPageNumNew[6] = 6; Mem.CHRPageNumNew[7] = 7;
// ^^^ Unknown ^^^
			break;
		case 33 :
			Mem.PRGPageNumNew[0] = 0; Mem.PRGPageNumNew[1] = 1;
			Mem.PRGPageNumNew[2] = (BYTE) (Mem.PRGPagesA - 2); Mem.PRGPageNumNew[3] = (BYTE) (Mem.PRGPagesA - 1);

// vvv Unknown vvv
			Mem.CHRPageNumNew[0] = 0; Mem.CHRPageNumNew[1] = 1; Mem.CHRPageNumNew[2] = 2;
			Mem.CHRPageNumNew[3] = 3; Mem.CHRPageNumNew[4] = 4; Mem.CHRPageNumNew[5] = 5;
			Mem.CHRPageNumNew[6] = 6; Mem.CHRPageNumNew[7] = 7;
// ^^^ Unknown ^^^
			break;
		case 34 :
			Mem.PRGPageNumNew[0] = 0; Mem.PRGPageNumNew[1] = 1;
			Mem.PRGPageNumNew[2] = 2; Mem.PRGPageNumNew[3] = 3;

			Mem.CHRPageNumNew[0] = 0; Mem.CHRPageNumNew[1] = 1; Mem.CHRPageNumNew[2] = 2;
			Mem.CHRPageNumNew[3] = 3; Mem.CHRPageNumNew[4] = 4; Mem.CHRPageNumNew[5] = 5;
			Mem.CHRPageNumNew[6] = 6; Mem.CHRPageNumNew[7] = 7;
			break;
		case 64 :
			Mem.PRGPageNumNew[0] = (BYTE) (Mem.PRGPagesA - 1); Mem.PRGPageNumNew[0];
			Mem.PRGPageNumNew[2] = Mem.PRGPageNumNew[0]; Mem.PRGPageNumNew[3] = Mem.PRGPageNumNew[0];

			Mem.CHRPageNumNew[0] = 0; Mem.CHRPageNumNew[1] = 1; Mem.CHRPageNumNew[2] = 2;
			Mem.CHRPageNumNew[3] = 3; Mem.CHRPageNumNew[4] = 4; Mem.CHRPageNumNew[5] = 5;
			Mem.CHRPageNumNew[6] = 6; Mem.CHRPageNumNew[7] = 7;
			break;
		case 65 :
			Mem.PRGPageNumNew[0] = 0; Mem.PRGPageNumNew[1] = 1;
			Mem.PRGPageNumNew[2] = (BYTE) (Mem.PRGPagesA - 2); Mem.PRGPageNumNew[3] = (BYTE) (Mem.PRGPagesA - 1);

// vvv Unknown vvv
			Mem.CHRPageNumNew[0] = 0; Mem.CHRPageNumNew[1] = 1; Mem.CHRPageNumNew[2] = 2;
			Mem.CHRPageNumNew[3] = 3; Mem.CHRPageNumNew[4] = 4; Mem.CHRPageNumNew[5] = 5;
			Mem.CHRPageNumNew[6] = 6; Mem.CHRPageNumNew[7] = 7;
// ^^^ Unknown ^^^
			break;
		case 66 :
			Mem.PRGPageNumNew[0] = 0; Mem.PRGPageNumNew[1] = 1;
			Mem.PRGPageNumNew[2] = 2; Mem.PRGPageNumNew[3] = 3;

			Mem.CHRPageNumNew[0] = 0; Mem.CHRPageNumNew[1] = 1; Mem.CHRPageNumNew[2] = 2;
			Mem.CHRPageNumNew[3] = 3; Mem.CHRPageNumNew[4] = 4; Mem.CHRPageNumNew[5] = 5;
			Mem.CHRPageNumNew[6] = 6; Mem.CHRPageNumNew[7] = 7;
			break;
		case 68 :
			Mem.PRGPageNumNew[0] = 0; Mem.PRGPageNumNew[1] = 1;
			Mem.PRGPageNumNew[2] = (BYTE) (Mem.PRGPagesA - 2); Mem.PRGPageNumNew[3] = (BYTE) (Mem.PRGPagesA - 1);

// vvv Unknown vvv
			Mem.CHRPageNumNew[0] = 0; Mem.CHRPageNumNew[1] = 1; Mem.CHRPageNumNew[2] = 2;
			Mem.CHRPageNumNew[3] = 3; Mem.CHRPageNumNew[4] = 4; Mem.CHRPageNumNew[5] = 5;
			Mem.CHRPageNumNew[6] = 6; Mem.CHRPageNumNew[7] = 7;
// ^^^ Unknown ^^^
			break;
		case 69 :
// vvv Unknown vvv
			Mem.PRGPageNumNew[0] = 0; Mem.PRGPageNumNew[1] = 1;
			Mem.PRGPageNumNew[2] = 2;
// ^^^ Unknown ^^^
			Mem.PRGPageNumNew[3] = (BYTE) (Mem.PRGPagesA - 1);

// vvv Unknown vvv
			Mem.CHRPageNumNew[0] = 0; Mem.CHRPageNumNew[1] = 1; Mem.CHRPageNumNew[2] = 2;
			Mem.CHRPageNumNew[3] = 3; Mem.CHRPageNumNew[4] = 4; Mem.CHRPageNumNew[5] = 5;
			Mem.CHRPageNumNew[6] = 6; Mem.CHRPageNumNew[7] = 7;
// ^^^ Unknown ^^^
			break;
		case 71 :
			Mem.PRGPageNumNew[0] = 0; Mem.PRGPageNumNew[1] = 1;
			Mem.PRGPageNumNew[2] = (BYTE) (Mem.PRGPagesA - 2); Mem.PRGPageNumNew[3] = (BYTE) (Mem.PRGPagesA - 1);

			Mem.CHRPageNumNew[0] = 0; Mem.CHRPageNumNew[1] = 1; Mem.CHRPageNumNew[2] = 2;
			Mem.CHRPageNumNew[3] = 3; Mem.CHRPageNumNew[4] = 4; Mem.CHRPageNumNew[5] = 5;
			Mem.CHRPageNumNew[6] = 6; Mem.CHRPageNumNew[7] = 7;
			break;
		case 78 :
			Mem.PRGPageNumNew[0] = 0; Mem.PRGPageNumNew[1] = 1;
			Mem.PRGPageNumNew[2] = (BYTE) (Mem.PRGPagesA - 2); Mem.PRGPageNumNew[3] = (BYTE) (Mem.PRGPagesA - 1);

// vvv Possible vvv
			Mem.CHRPageNumNew[0] = 0; Mem.CHRPageNumNew[1] = 1; Mem.CHRPageNumNew[2] = 2;
			Mem.CHRPageNumNew[3] = 3; Mem.CHRPageNumNew[4] = 4; Mem.CHRPageNumNew[5] = 5;
			Mem.CHRPageNumNew[6] = 6; Mem.CHRPageNumNew[7] = 7;
// ^^^ Possible ^^^
			break;
		case 91 :
			Mem.PRGPageNumNew[0] = (BYTE) (Mem.PRGPagesA - 2); Mem.PRGPageNumNew[1] = (BYTE) (Mem.PRGPagesA - 1);
			Mem.PRGPageNumNew[2] = (BYTE) (Mem.PRGPagesA - 2); Mem.PRGPageNumNew[3] = (BYTE) (Mem.PRGPagesA - 1);

// vvv Unknown vvv
			Mem.CHRPageNumNew[0] = 0; Mem.CHRPageNumNew[1] = 1; Mem.CHRPageNumNew[2] = 2;
			Mem.CHRPageNumNew[3] = 3; Mem.CHRPageNumNew[4] = 4; Mem.CHRPageNumNew[5] = 5;
			Mem.CHRPageNumNew[6] = 6; Mem.CHRPageNumNew[7] = 7;
// ^^^ Unknown ^^^
			break;
		case 99 :
			Mem.PRGPageNumNew[0] = 0; Mem.PRGPageNumNew[1] = 1;
			Mem.PRGPageNumNew[2] = (BYTE) (Mem.PRGPagesA - 2); Mem.PRGPageNumNew[3] = (BYTE) (Mem.PRGPagesA - 1);

			Mem.CHRPageNumNew[0] = 0; Mem.CHRPageNumNew[1] = 1; Mem.CHRPageNumNew[2] = 2;
			Mem.CHRPageNumNew[3] = 3; Mem.CHRPageNumNew[4] = 4; Mem.CHRPageNumNew[5] = 5;
			Mem.CHRPageNumNew[6] = 6; Mem.CHRPageNumNew[7] = 7;
	};

	memcpy(&Mem.PRGPageNum[0], &Mem.PRGPageNumNew[0], 4);
	memcpy(&Mem.CHRPageNum[0], &Mem.CHRPageNumNew[0], 8);

	memcpy(&Mem.PRGROMLow[0],&Mem.PRGPage[Mem.PRGPageNumNew[0]][0],0x2000);
	memcpy(&Mem.PRGROMLow[0x2000],&Mem.PRGPage[Mem.PRGPageNumNew[1]][0],0x2000);
	memcpy(&Mem.PRGROMHigh[0],&Mem.PRGPage[Mem.PRGPageNumNew[2]][0],0x2000);
	memcpy(&Mem.PRGROMHigh[0x2000],&Mem.PRGPage[Mem.PRGPageNumNew[3]][0],0x2000);
	UpdateGGCodes();

	if (!DontSwapVRAM)
	{
		memcpy(&Mem.PatternTable[0][0], &Mem.CHRPage[Mem.CHRPageNumNew[0]][0], 0x400);
		memcpy(&Mem.PatternTable[0][0x400], &Mem.CHRPage[Mem.CHRPageNumNew[1]][0], 0x400);
		memcpy(&Mem.PatternTable[0][0x800], &Mem.CHRPage[Mem.CHRPageNumNew[2]][0], 0x400);
		memcpy(&Mem.PatternTable[0][0xC00], &Mem.CHRPage[Mem.CHRPageNumNew[3]][0], 0x400);
		memcpy(&Mem.PatternTable[1][0], &Mem.CHRPage[Mem.CHRPageNumNew[4]][0], 0x400);
		memcpy(&Mem.PatternTable[1][0x400], &Mem.CHRPage[Mem.CHRPageNumNew[5]][0], 0x400);
		memcpy(&Mem.PatternTable[1][0x800], &Mem.CHRPage[Mem.CHRPageNumNew[6]][0], 0x400);
		memcpy(&Mem.PatternTable[1][0xC00], &Mem.CHRPage[Mem.CHRPageNumNew[7]][0], 0x400);
	}

	setmem(Mem.Main[0], 0x800, 0x00);

	for (int i=0x2000;i<0x4000;i++)
		*Mem.PPU[i] = 0x00;
	setmem(&Mem.Sprite[0x00], 0x100, 0x00);

//SP = 0xFF;
SP = 0x1FF;

	A = 0; X = 0; Y = 0;
	PC = (LBYTE) (Get16Bit(ResetVector));
	CCR.C = false; CCR.Z = false; CCR.B = false; CCR.I = true; CCR.D = true; CCR.V = false; CCR.N = false;
	Mem.BgScrollX = 0; Mem.BgScrollY = 0;
	Mem.VRAMAddress = 0; Mem.SPRAddress = 0;
	NTabAdr = 0x2000;
	ScanLine = 0;
	LineTickCount = 0;
	LineTickCountInt = 0;

//	BGCol = cblack;
	VBCount = NMIClockTicks;

	Clockticks = 7;
	Joy.Count[0] = 0; Joy.Count[1] = 0;
	Joy.Strobe[0] = 0; Joy.Strobe[1] = 0;
	setmem(&Joy.Bits[0][0], 48, 0);

	PulseChan[0].Enabled = false;
	PulseChan[1].Enabled = false;
	TriChan.Enabled = false;
	NoiseChan.Enabled = false;
	DCMChan.Enabled = false;
}
//---------------------------------------------------------------------------
//Game Genie Stuff
//---------------------------------------------------------------------------
void __fastcall UpdateGGCodes()
{
	for (int i=0;i<GGCodeNum;i++)
	{
		if (GGCode[i].CompareValueEnabled) {
			if (*Mem.Main[GGCode[i].Address] == GGCode[i].CompareValue)
				*Mem.Main[GGCode[i].Address] = GGCode[i].Value;
		} else {
			*Mem.Main[GGCode[i].Address] = GGCode[i].Value;
		}
	}
}
//---------------------------------------------------------------------------
//Memory Accessing Commands
//---------------------------------------------------------------------------
BYTE __fastcall MemoryTUGet()
{
	if (TU == 0x10000) { return(A); }

	register BYTE ToRet;
	switch (TU) {
		case PPUStat :
			ToRet = (BYTE) ((VBlankOcc << 7) | (Spr0Occ << 6) | (ScLnSprCnt << 5) | (VRAMWrFlg << 4));
			VBlankOcc = false;
			Mem.BgScrollUsing = false;
			break;
		case SPRIO :
			ToRet = Mem.Sprite[Mem.SPRAddress];
			if (!SFirstRead) Mem.SPRAddress++; else SFirstRead = false;
			Mem.SPRAddress++;
			break;
		case VRAMIO :
			ToRet = *Mem.PPU[Mem.VRAMAddress & 0x3FFF];
			if (!VFirstRead) Mem.VRAMAddress++; else VFirstRead = false;
			break;
		case pAPUStCh :
			if (PulseChan[0].LengthLeft) ToRet |= 0x01;
			if (PulseChan[1].LengthLeft) ToRet |= 0x02;
			if (TriChan.Enabled) ToRet |= 0x04;
			if (NoiseChan.Enabled) ToRet |= 0x08;
			if (DCMChan.Enabled) ToRet |= 0x10;
			break;
		case Joypad1 :
			ToRet = Joy.Get(0);
			break;
		case Joypad2 :
			ToRet = Joy.Get(1);
			break;

		default :
			if ((TU >= 0x6000) && (TU < 0x8000))
			{
				if (Mem.SRAMEnabled)
				{
					ToRet = *Mem.Main[TU];
					tprint(AnsiString("SRAM Read (E): ") + IntToHex(TU & 0x1FFF,4) + AnsiString(" - ") + IntToHex(ToRet,2));
				} else {
					ToRet = 0;
					tprint(AnsiString("SRAM Read (D): ") + IntToHex(TU & 0x1FFF,4));
				}
			} else {
				ToRet = *Mem.Main[TU];
			}
			break;
	};
	if (DebuggingTrace)
	{
		if ((TU >= 0x2000) && (TU <= 0x2007)) dprint(AnsiString("        RegRead: ") + RegInfoLow[TU & 0xFF] + AnsiString(", ToRet = ") + IntToHex(ToRet,2) + AnsiString(" (") + AnsiString(ToBin(ToRet)) + AnsiString(")"));
		if ((TU >= 0x4000) && (TU <= 0x4017)) dprint(AnsiString("        RegRead: ") + RegInfoHigh[TU & 0xFF] + AnsiString(", ToRet = ") + IntToHex(ToRet,2) + AnsiString(" (") + AnsiString(ToBin(ToRet)) + AnsiString(")"));
	}
	return(ToRet);
}

void __fastcall MemoryTUEquals(register BYTE ta)
{
	if (TU == 0x10000) { A = ta; return; }

	if (DebuggingTrace)
	{
		if ((TU >= 0x2000) && (TU <= 0x2007)) dprint(AnsiString("        RegWrite: ") + RegInfoLow[TU & 0xFF] + AnsiString(": ") + IntToHex(ta,2) + AnsiString(" (") + AnsiString(ToBin(ta)) + AnsiString(")"));
		if ((TU >= 0x4000) && (TU <= 0x4017)) dprint(AnsiString("        RegWrite: ") + RegInfoHigh[TU & 0xFF] + AnsiString(": ") + IntToHex(ta,2) + AnsiString(" (") + AnsiString(ToBin(ta)) + AnsiString(")"));
	}
	switch (TU) {
		case PPUCtrl1 :
			NMIonVBlank = ta & 0x80;
			SSize = ta & 0x20;
			BkPTA = ta & 0x10;
			SpPTA = ta & 0x08;
			PPUAdrI = ta & 0x04;
			NTabAdr = (short int) (0x2000 | (((ta & 0x02) + bit0(ta)) << 10));
			break;
		case PPUCtrl2 :
//			if (bit5(ta)) { BGCol = cred; }
//			else if (bit6(ta)) { BGCol = cblue; }
//			else if (bit7(ta)) { BGCol = cgreen; }
//			else { BGCol = cblack; }
			SprVis = ta & 0x10;
			BGVis = ta & 0x08;
			SprClip = ta & 0x04;
			BGClip = ta & 0x02;
			DispType = ta & 0x01;
			break;
		case SPRAddr :
			Mem.SPRAddress = ta;
			SFirstRead = true;
			tprint(AnsiString("SPRAddress = ") + IntToHex(Mem.SPRAddress,2));
			break;
		case SPRIO :
			Mem.Sprite[Mem.SPRAddress] = ta;
			tprint(AnsiString("SPRMemory[") + IntToHex(Mem.SPRAddress,2) + AnsiString("] = ") + IntToHex(ta,2));
			Mem.SPRAddress++;
			break;
		case BgScroll :
			if (Mem.BgScrollUsing == false) {
				Mem.BgScrollUsing = true;
				Mem.BgScrollX = ta;
			} else {
				Mem.BgScrollUsing = false;
				Mem.BgScrollY = ta;
				if (Mem.BgScrollY >= 0xF0)
				{
					Mem.BgScrollY = 0;
//					Mem.BgScrollY = (short int) (240 - Mem.BgScrollY);
					tprint(AnsiString("Negative Y Scroll: ") + AnsiString(ta));
				}
				tprint(AnsiString("Scroll(") + IntToHex(Mem.BgScrollX,2) + AnsiString(", ") + IntToHex(Mem.BgScrollY,2) + AnsiString(")"));
			}
//			if (LineTickCountInt - Clockticks > 85)
//			{
//				if (!MHBUsing) {
//					MHBUsing = true;
//					MHBValue = (short int) (ta << 8);
//				} else {
//					MHBUsing = false;
//					MHBValue |= ta;
//					tprint(AnsiString("Mid-HBlank VRAM Write: Scanline: ") + AnsiString(ScanLine) + AnsiString(", Val = ") + IntToHex(MHBValue,4) + AnsiString(" (") + ToBin((BYTE) ((MHBValue & 0xFF00) >> 8)) + ToBin((BYTE) (MHBValue & 0xFF)) + AnsiString(")"));
//					NTabAdr = (short int) ((MHBValue & 0x0C00) | 0x2000);
//					Mem.BgScrollX = (unsigned char) ((MHBValue & 0x1F) << 3);
//					Mem.BgScrollY = 0;
//					ScanLine = (short int) (((MHBValue & 0x03E0) >> 2) | ((MHBValue & 0x3000) >> 12));
//				}
//			}
			break;
		case VRAMAddr :
			if (!Mem.VRAMAddrUsing) {
				Mem.VRAMAddrUsing = true;
				Mem.VRAMAddrHigh = (BYTE) (ta & 0x3F);
			} else {
				Mem.VRAMAddrUsing = false;
				Mem.VRAMAddress = (short int) (((Mem.VRAMAddrHigh << 8) | ta));
				VFirstRead = true;
				tprint(AnsiString("VRAMAddress = ") + IntToHex(Mem.VRAMAddress,4));
			}
			break;
		case VRAMIO :
			tprint(AnsiString("VRAM[") + IntToHex(Mem.VRAMAddress & 0x3FFF,4) + AnsiString("] = ") + IntToHex(ta,2));
			*Mem.PPU[Mem.VRAMAddress & 0x3FFF] = ta;
			if (PPUAdrI) Mem.VRAMAddress += (short int) 32; else Mem.VRAMAddress++;
			break;
		case pAPUP1C1 :
			SNDChannels[0].bWaveDuty = (BYTE) ((ta & 0xC0) >> 6);
			PulseChan[0].Loop = bit5(ta);

			if (bit4(ta))
			{
				PulseChan[0].Volume = (BYTE) (ta & 0x0F);
				PulseChan[0].VolFade = 2;
			} else {
				tprint(AnsiString("Envelope[1]: ") + ToBinC(ta,0,4));
				PulseChan[0].Volume = (BYTE) (ta & 0x0F);
				PulseChan[0].VolFade = 0;
			}
			SNDChannels[0].bVol = PulseChan[0].Volume;
			break;
		case pAPUP1C2 :
			break;
		case pAPUP1F1 :
			SNDChannels[0].dwFreq = (LBYTE) ((SNDChannels[0].dwFreq | 0xFF) & (0x700 | ta));
			break;
		case pAPUP1F2 :
			PulseChan[0].LengthLeft = LengthInfo[(ta & 0xF8) >> 3];
			SNDChannels[0].dwFreq = (LBYTE) ((ta & 0x07) << 8) | (LBYTE) (SNDChannels[0].dwFreq & 0xFF);
			break;
		case pAPUP2C1 :
			SNDChannels[1].bWaveDuty = (BYTE) ((ta & 0xC0) >> 6);
			PulseChan[1].Loop = bit5(ta);

			if (bit4(ta))
			{
				PulseChan[1].Volume = (BYTE) (ta & 0x0F);
				PulseChan[1].VolFade = 2;
			} else {
				tprint(AnsiString("Envelope[2]: ") + ToBinC(ta,0,4));
				PulseChan[1].Volume = (BYTE) (ta & 0x0F);
				PulseChan[1].VolFade = 0;
			}
			SNDChannels[1].bVol = PulseChan[1].Volume;
			break;
		case pAPUP2C2 :
			break;
		case pAPUP2F1 :
			SNDChannels[1].dwFreq = (LBYTE) ((SNDChannels[1].dwFreq | 0xFF) & (0x700 | ta));
			break;
		case pAPUP2F2 :
			PulseChan[1].LengthLeft = LengthInfo[(ta & 0xF8) >> 3];
			SNDChannels[1].dwFreq = (LBYTE) ((ta & 0x07) << 8) | (LBYTE) (SNDChannels[1].dwFreq & 0xFF);
			break;

		case pAPUTC1 :
//			tprinto(AnsiString("Tri C1:") + ToBin(ta));
			break;
		case pAPUTC2 :
//			tprinto(AnsiString("Tri C2:") + ToBin(ta));
			break;
		case pAPUTF1 :
//			tprinto(AnsiString("Tri F1:") + ToBin(ta));
			break;
		case pAPUTF2 :
//			tprinto(AnsiString("Tri F2:") + ToBin(ta));
			break;

		case pAPUNC1 :
//			tprinto(AnsiString("Noise C1:") + ToBin(ta));
			break;
		case pAPUNC2 :
//			tprinto(AnsiString("Noise C2:") + ToBin(ta));
			break;
		case pAPUNF1 :
//			tprinto(AnsiString("Noise F1:") + ToBin(ta));
			break;
		case pAPUNF2 :
//			tprinto(AnsiString("Noise F2:") + ToBin(ta));
			break;

		case pAPUDMCC :
			DCMChan.Loop = bit6(ta);
			DCMChan.IRQGen = bit7(ta);
			DCMChan.PlaybackRate = PlayDataRate[ta & 0x0F];
			break;
		case pAPUDMCV :
			DCMChan.Volume = (BYTE) ((ta & 0x7E) >> 1);
			DCMChan.DataBusBit = bit0(ta);
			break;
		case pAPUDMCA :
			DCMChan.Address = (LBYTE) (0xC000 | (ta << 6));
			break;
		case pAPUDMCDL :
			DCMChan.BitLength = (LBYTE) ((ta << 7) | 1);
			break;
		case SPRDMA :
			tprint(AnsiString("SpriteMem = Memory[") + IntToHex(ta,2) + AnsiString("xx]"));

//			for (tmpLBYTE=(ta << 8);tmpLBYTE<(ta << 8) + 0xFF;tmpLBYTE++)
//				Mem.Sprite[tmpLBYTE & 0xFF] = *Mem.Main[tmpLBYTE];
			memcpy(&Mem.Sprite[0],Mem.Main[ta << 8],0x100);
			break;
		case pAPUStCh :
			PulseChan[0].Enabled = bit0(ta);
			PulseChan[1].Enabled = bit1(ta);
			TriChan.Enabled = bit2(ta);
			NoiseChan.Enabled = bit3(ta);
			DCMChan.Enabled = bit4(ta);
			break;
		case Joypad1 :
			Joy.SetStrobe(0, bit0(ta));
			if (Mem.MapperNum == 99)
			{
				Mem.CHRPageNumNew[0] = (BYTE) (bit2(ta) << 3);
				Mem.CHRPageNumNew[1] = (BYTE) (Mem.CHRPageNumNew[0] + 1);
				Mem.CHRPageNumNew[2] = (BYTE) (Mem.CHRPageNumNew[0] + 2); Mem.CHRPageNumNew[3] = (BYTE) (Mem.CHRPageNumNew[0] + 3);
				Mem.CHRPageNumNew[4] = (BYTE) (Mem.CHRPageNumNew[0] + 4); Mem.CHRPageNumNew[5] = (BYTE) (Mem.CHRPageNumNew[0] + 5);
				Mem.CHRPageNumNew[6] = (BYTE) (Mem.CHRPageNumNew[0] + 6); Mem.CHRPageNumNew[7] = (BYTE) (Mem.CHRPageNumNew[0] + 7);

				Mem.UpdateCHRPointers();
			}
			break;
		case Joypad2 :
			Joy.SetStrobe(1, bit0(ta));
			break;

		default :
			if ((TU >= 0x6000) && (TU < 0x8000))
			{
				if (Mem.SRAMEnabled)
				{
					tprint(AnsiString("SRAM Write (E): ") + IntToHex(TU & 0x1FFF,4) + AnsiString(" - ") + IntToHex(ta,2));
					*Mem.Main[TU] = ta;
				} else {
					tprint(AnsiString("SRAM Write (D): ") + IntToHex(TU & 0x1FFF,4) + AnsiString(" - ") + IntToHex(ta,2));
				}
			} else if (TU < 0x6000) {
				*Mem.Main[TU] = ta;
			}

			switch (Mem.MapperNum) {
				case 0 :
					return;
				case 1 :
					if (TU < 0x8000) return;

					tprint(AnsiString("MMC1: Write: ") + IntToHex(TU,4) + AnsiString(" - ") + IntToHex(ta,2) + AnsiString("! Clockticks: ") + AnsiString(Clockticks));

					if (bit7(ta)) { MMC1.ArrayPtr = 0; MMC1.Array = 0; return; }
					MMC1.Array |= (BYTE) ((ta & 0x01) << MMC1.ArrayPtr);
					MMC1.ArrayPtr++;
					if (MMC1.ArrayPtr == 5)
					{
						MMC1.UpdateReg((BYTE) ((TU & 0x7000) >> 13));
						tprint(AnsiString("MMC1: Reg[") + AnsiString((TU & 0x7000) >> 13) + AnsiString("] = ") + IntToHex(MMC1.Reg[(TU & 0x7000) >> 13],2) + AnsiString(" (") + ToBin(MMC1.Reg[(TU & 0x7000) >> 13]) + AnsiString(")"));
						return;
					}
					return;
				case 2 :
					if (TU < 0x8000) return;

					Mem.PRGPageNumNew[0] = (BYTE) ((ta << 1) & Mem.PRGBitMask);
					Mem.PRGPageNumNew[1] = (BYTE) (Mem.PRGPageNumNew[0] + 1);

					Mem.UpdatePRGPointers();
					UpdateGGCodes();
					tprint(AnsiString("UNROM: PRGpg[0,1] = ") + AnsiString(Mem.PRGPageNumNew[0]) + AnsiString(",") + AnsiString(Mem.PRGPageNumNew[1]) + AnsiString(", TA = ") + IntToHex(ta,2) + AnsiString("(") + ToBin(ta) + AnsiString(")"));
					return;
				case 3 :
					if (TU < 0x8000) return;
					tmpLBYTE = (LBYTE) (((ta & 7) << 3) & Mem.CHRBitMask);
					Mem.CHRPageNumNew[0] = tmpLBYTE; Mem.CHRPageNumNew[1] = (LBYTE) (tmpLBYTE + 1); Mem.CHRPageNumNew[2] = (LBYTE) (tmpLBYTE + 2);
					Mem.CHRPageNumNew[3] = (LBYTE) (tmpLBYTE + 3); Mem.CHRPageNumNew[4] = (LBYTE) (tmpLBYTE + 4); Mem.CHRPageNumNew[5] = (LBYTE) (tmpLBYTE + 5);
					Mem.CHRPageNumNew[6] = (LBYTE) (tmpLBYTE + 6); Mem.CHRPageNumNew[7] = (LBYTE) (tmpLBYTE + 7);
					Mem.UpdateCHRPointers();
					tprint(AnsiString("CNROM: CHRpg[0-7] = ") + AnsiString(tmpLBYTE) + AnsiString("-") + AnsiString(tmpLBYTE + 7));
					return;
				case 4 :
					if (TU < 0x8000) return;

					if (TU == 0x8000)
					{
						MMC3.Command = (BYTE) (ta & 0x07);
						MMC3.PRGSelect = bit6(ta);
						MMC3.CHRSelect = bit7(ta);
						tprint(AnsiString("MMC3: Command# = ") + AnsiString(MMC3.Command) + AnsiString(", PRGSel = ") + AnsiString((BYTE) bit6(ta)) + AnsiString(", CHRSel = ") + AnsiString((BYTE) bit7(ta)));
						return;
					}
					if (TU == 0x8001)
					{
						switch (MMC3.Command) {
							case 0 :
								tmpBYTE = (BYTE) (MMC3.CHRSelect << 2);
								Mem.CHRPageNumNew[tmpBYTE] = (LBYTE) ((ta & 0xFE) & Mem.CHRBitMask);
								Mem.CHRPageNumNew[tmpBYTE + 1] = (LBYTE) (Mem.CHRPageNumNew[tmpBYTE] + 1);
								Mem.UpdateCHRPointers();
								tprint(AnsiString("MMC3: CHRpg[") + AnsiString(0 + (MMC3.CHRSelect << 2)) + AnsiString("] = ") + AnsiString(ta));
								tprint(AnsiString("MMC3: CHRpg[") + AnsiString(1 + (MMC3.CHRSelect << 2)) + AnsiString("] = ") + AnsiString(ta+1));
								return;
							case 1 :
								tmpBYTE = (BYTE) ((MMC3.CHRSelect << 2) + 2);
								Mem.CHRPageNumNew[tmpBYTE] = (LBYTE) ((ta & 0xFE) & Mem.CHRBitMask);
								Mem.CHRPageNumNew[tmpBYTE + 1] = (LBYTE) (Mem.CHRPageNumNew[tmpBYTE] + 1);
								Mem.UpdateCHRPointers();
								tprint(AnsiString("MMC3: CHRpg[") + AnsiString(2 + (MMC3.CHRSelect << 2)) + AnsiString("] = ") + AnsiString(ta));
								tprint(AnsiString("MMC3: CHRpg[") + AnsiString(3 + (MMC3.CHRSelect << 2)) + AnsiString("] = ") + AnsiString(ta+1));
								return;
							case 2 :
								Mem.CHRPageNumNew[4^(MMC3.CHRSelect << 2)] = (LBYTE) (ta & Mem.CHRBitMask);
								Mem.UpdateCHRPointers();
								tprint(AnsiString("MMC3: CHRpg[") + AnsiString(4 ^ (MMC3.CHRSelect << 2)) + AnsiString("] = ") + AnsiString(ta));
								return;
							case 3 :
								Mem.CHRPageNumNew[5^(MMC3.CHRSelect << 2)] = (LBYTE) (ta & Mem.CHRBitMask);
								Mem.UpdateCHRPointers();
								tprint(AnsiString("MMC3: CHRpg[") + AnsiString(5 ^ (MMC3.CHRSelect << 2)) + AnsiString("] = ") + AnsiString(ta));
								return;
							case 4 :
								Mem.CHRPageNumNew[6^(MMC3.CHRSelect << 2)] = (LBYTE) (ta & Mem.CHRBitMask);
								Mem.UpdateCHRPointers();
								tprint(AnsiString("MMC3: CHRpg[") + AnsiString(6 ^ (MMC3.CHRSelect << 2)) + AnsiString("] = ") + AnsiString(ta));
								return;
							case 5 :
								Mem.CHRPageNumNew[7^(MMC3.CHRSelect << 2)] = (LBYTE) (ta & Mem.CHRBitMask);
								Mem.UpdateCHRPointers();
								tprint(AnsiString("MMC3: CHRpg[") + AnsiString(7 ^ (MMC3.CHRSelect << 2)) + AnsiString("] = ") + AnsiString(ta));
								return;
							case 6 :
								Mem.PRGPageNumNew[MMC3.PRGSelect] = (BYTE) (ta & Mem.PRGBitMask);
								Mem.UpdatePRGPointers();
								UpdateGGCodes();
								tprint(AnsiString("MMC3: PRGpg[") + AnsiString(0 + MMC3.PRGSelect) + AnsiString("] = ") + AnsiString(ta));
								return;
							case 7 :
								Mem.PRGPageNumNew[1+MMC3.PRGSelect] = (BYTE) (ta & Mem.PRGBitMask);
								Mem.UpdatePRGPointers();
								UpdateGGCodes();
								tprint(AnsiString("MMC3: PRGpg[") + AnsiString(1 + MMC3.PRGSelect) + AnsiString("] = ") + AnsiString(ta));
								return;
						};
					}
					if (TU == 0xA000)	//May be inaccurate
					{
						if (bit0(ta))
						{
							Mem.UpdateNameTablePointers(0, 0, 2, 2);
						} else {
							Mem.UpdateNameTablePointers(0, 1, 0, 1);
						}
						tprint(AnsiString("MMC3: MirrorChange: ") + AnsiString((bit0(ta)) ? "Horizontal" : "Vertical"));
						return;
					}
					if (TU == 0xA001)	{
						Mem.SRAMEnabled = bit7(ta);
						tprint(AnsiString("MMC3: SRAM = ") + AnsiString((bit7(ta)) ? "On" : "Off"));
						return;
					}
					if (TU == 0xC000)	{
						MMC3.IRQCounter = ta;
						tprint(AnsiString("MMC3: IRQCounter = ") + AnsiString(ta));
						return;
					}
					if (TU == 0xC001)   {
						MMC3.IRQLatch = ta;
						tprint(AnsiString("MMC3: IRQLatch = ") + AnsiString(ta));
						return;
					}
					if (TU == 0xE000)
					{
						MMC3.IRQEnable = false;
						MMC3.IRQCounter = MMC3.IRQLatch;
						tprint(AnsiString("MMC3: IRQEnabled = false"));
						tprint(AnsiString("MMC3: IRQCounter = IRQLatch (") + AnsiString(ta) + AnsiString(")"));
						return;
					}
					if (TU == 0xE001)	{
						MMC3.IRQEnable = true;
						tprint(AnsiString("MMC3: IRQEnabled = true"));
						return;
					}
					return;
				case 7 :
					if (TU < 0x8000) return;

					ta = (BYTE) ((ta & 0x0F) & Mem.PRGBitMask);
					if ((ta << 2) != Mem.PRGPageNumNew[0])
					{
						Mem.PRGPageNumNew[0] = (BYTE) (ta << 2); Mem.PRGPageNumNew[1] = (BYTE) (Mem.PRGPageNumNew[0] + 1);
						Mem.PRGPageNumNew[2] = (BYTE) (Mem.PRGPageNumNew[0] + 2); Mem.PRGPageNumNew[3] = (BYTE) (Mem.PRGPageNumNew[0] + 3);
						Mem.UpdatePRGPointers();
						UpdateGGCodes();
					}
					tprint(AnsiString("AOROM: PRGpg[0-3] = ") + AnsiString(ta) + AnsiString("-") + AnsiString(ta+3));

					Mem.UpdateNameTablePointers(bit4(ta),bit4(ta),bit4(ta),bit4(ta));
					tprint(AnsiString("AOROM: MirrorFrom = ") + IntToHex(0x2000 + (bit4(ta) << 10),4));
					return;
				case 8 :
					if (TU < 0x8000) return;

					Mem.PRGPageNumNew[0] = (BYTE) ((((ta & 0xF8) >> 3) << 1) & Mem.PRGBitMask);
					Mem.PRGPageNumNew[1] = (BYTE) (Mem.PRGPageNumNew[0] + 1);

					Mem.CHRPageNumNew[0] = (BYTE) (((ta & 0x07) << 3) & Mem.CHRBitMask);
					Mem.CHRPageNumNew[1] = (BYTE) (Mem.CHRPageNumNew[0] + 1);
					Mem.CHRPageNumNew[2] = (BYTE) (Mem.CHRPageNumNew[0] + 2); Mem.CHRPageNumNew[3] = (BYTE) (Mem.CHRPageNumNew[0] + 3);
					Mem.CHRPageNumNew[4] = (BYTE) (Mem.CHRPageNumNew[0] + 4); Mem.CHRPageNumNew[5] = (BYTE) (Mem.CHRPageNumNew[0] + 5);
					Mem.CHRPageNumNew[6] = (BYTE) (Mem.CHRPageNumNew[0] + 6); Mem.CHRPageNumNew[7] = (BYTE) (Mem.CHRPageNumNew[0] + 7);

					Mem.UpdateCHRPRGPointers();
					UpdateGGCodes();
					tprint(AnsiString("GNROM: PRG = ") + AnsiString(Mem.PRGPageNumNew[0]) + AnsiString(", CHR = ") + AnsiString(Mem.CHRPageNumNew[0] >> 3) + AnsiString(", ta = ") + IntToHex(ta,2));
					return;
				case 11 :
					if (TU < 0x8000) return;

					Mem.PRGPageNumNew[0] = (BYTE) (((ta & (BYTE) 0x03) << 2) & Mem.PRGBitMask);
					Mem.PRGPageNumNew[1] = (BYTE) (Mem.PRGPageNumNew[0] + 1);
					Mem.PRGPageNumNew[2] = (BYTE) (Mem.PRGPageNumNew[0] + 2); Mem.PRGPageNumNew[3] = (BYTE) (Mem.PRGPageNumNew[0] + 3);

					Mem.CHRPageNumNew[0] = (BYTE) ((((ta & 0xF0) >> 4) << 3) & Mem.CHRBitMask);
					Mem.CHRPageNumNew[1] = (BYTE) (Mem.CHRPageNumNew[0] + 1);
					Mem.CHRPageNumNew[2] = (BYTE) (Mem.CHRPageNumNew[0] + 2); Mem.CHRPageNumNew[3] = (BYTE) (Mem.CHRPageNumNew[0] + 3);
					Mem.CHRPageNumNew[4] = (BYTE) (Mem.CHRPageNumNew[0] + 4); Mem.CHRPageNumNew[5] = (BYTE) (Mem.CHRPageNumNew[0] + 5);
					Mem.CHRPageNumNew[6] = (BYTE) (Mem.CHRPageNumNew[0] + 6); Mem.CHRPageNumNew[7] = (BYTE) (Mem.CHRPageNumNew[0] + 7);

					Mem.UpdateCHRPRGPointers();
					UpdateGGCodes();
					tprint(AnsiString("ClrDrms: PRG = ") + AnsiString(Mem.PRGPageNumNew[0]) + AnsiString(", CHR = ") + AnsiString(Mem.CHRPageNumNew[0] >> 3));
					return;
				case 24 :
					return;
				case 34 :
					if (TU < 0x7FFD) return;

					if ((TU == 0x7FFD) || (TU >= 0x8000))
					{
						Mem.PRGPageNumNew[0] = (BYTE) ((ta << 2) & Mem.PRGBitMask);
						Mem.PRGPageNumNew[1] = (BYTE) (Mem.PRGPageNumNew[0] + 1);

						Mem.UpdatePRGPointers();
						UpdateGGCodes();
						tprint(AnsiString("Nina-1: PRG[Low] = ") + AnsiString(Mem.PRGPageNumNew[0]) + AnsiString(", ta = ") + IntToHex(ta,2));
					}
					if (TU == 0x7FFE)
					{
						Mem.CHRPageNumNew[0] = (BYTE) ((ta << 2) & Mem.CHRBitMask);
						Mem.CHRPageNumNew[1] = (BYTE) (Mem.CHRPageNumNew[0] + 1);
						Mem.CHRPageNumNew[2] = (BYTE) (Mem.CHRPageNumNew[0] + 2); Mem.CHRPageNumNew[3] = (BYTE) (Mem.CHRPageNumNew[0] + 3);

						Mem.UpdateCHRPointers();
						tprint(AnsiString("Nina-1: CHR[Low] = ") + AnsiString(Mem.CHRPageNumNew[0]) + AnsiString(", ta = ") + IntToHex(ta,2));
					}
					if (TU == 0x7FFF)
					{
						Mem.CHRPageNumNew[4] = (BYTE) ((ta << 2) & Mem.CHRBitMask);
						Mem.CHRPageNumNew[5] = (BYTE) (Mem.CHRPageNumNew[4] + 1);
						Mem.CHRPageNumNew[6] = (BYTE) (Mem.CHRPageNumNew[4] + 2); Mem.CHRPageNumNew[7] = (BYTE) (Mem.CHRPageNumNew[4] + 3);

						Mem.UpdateCHRPointers();
						tprint(AnsiString("Nina-1: CHR[High] = ") + AnsiString(Mem.CHRPageNumNew[4]) + AnsiString(", ta = ") + IntToHex(ta,2));
					}
					return;
				case 64 :
					if (TU < 0x8000) return;

					if (TU == 0x8000)
					{
						MMC3.Command = (BYTE) (ta & 0x0F);
						MMC3.PRGSelect = bit6(ta);
						MMC3.CHRSelect = bit7(ta);
						tprint(AnsiString("RAMBO-1: Command# = ") + AnsiString(MMC3.Command) + AnsiString(", PRGSel = ") + AnsiString((BYTE) bit6(ta)) + AnsiString(", CHRSel = ") + AnsiString((BYTE) bit7(ta)));
						return;
					}
					if (TU == 0x8001)
					{
						switch (MMC3.Command) {
							case 0 :
								tmpBYTE = (BYTE) (MMC3.CHRSelect << 2);
								Mem.CHRPageNumNew[tmpBYTE] = (LBYTE) ((ta & 0xFE) & Mem.CHRBitMask);
								Mem.CHRPageNumNew[tmpBYTE + 1] = (LBYTE) (Mem.CHRPageNumNew[tmpBYTE] + 1);
								Mem.UpdateCHRPointers();
								tprint(AnsiString("RAMBO-1: CHRpg[") + AnsiString(0 + (MMC3.CHRSelect << 2)) + AnsiString("] = ") + AnsiString(ta));
								tprint(AnsiString("RAMBO-1: CHRpg[") + AnsiString(1 + (MMC3.CHRSelect << 2)) + AnsiString("] = ") + AnsiString(ta+1));
								return;
							case 1 :
								tmpBYTE = (BYTE) ((MMC3.CHRSelect << 2) + 2);
								Mem.CHRPageNumNew[tmpBYTE] = (LBYTE) ((ta & 0xFE) & Mem.CHRBitMask);
								Mem.CHRPageNumNew[tmpBYTE + 1] = (LBYTE) (Mem.CHRPageNumNew[tmpBYTE] + 1);

								Mem.UpdateCHRPointers();
								tprint(AnsiString("RAMBO-1: CHRpg[") + AnsiString(2 + (MMC3.CHRSelect << 2)) + AnsiString("] = ") + AnsiString(ta));
								tprint(AnsiString("RAMBO-1: CHRpg[") + AnsiString(3 + (MMC3.CHRSelect << 2)) + AnsiString("] = ") + AnsiString(ta+1));
								return;
							case 2 :
								Mem.CHRPageNumNew[4^(MMC3.CHRSelect << 2)] = (LBYTE) (ta & Mem.CHRBitMask);
								Mem.UpdateCHRPointers();
								tprint(AnsiString("RAMBO-1: CHRpg[") + AnsiString(4 ^ (MMC3.CHRSelect << 2)) + AnsiString("] = ") + AnsiString(ta));
								return;
							case 3 :
								Mem.CHRPageNumNew[5^(MMC3.CHRSelect << 2)] = (LBYTE) (ta & Mem.CHRBitMask);
								Mem.UpdateCHRPointers();
								tprint(AnsiString("RAMBO-1: CHRpg[") + AnsiString(5 ^ (MMC3.CHRSelect << 2)) + AnsiString("] = ") + AnsiString(ta));
								return;
							case 4 :
								Mem.CHRPageNumNew[6^(MMC3.CHRSelect << 2)] = (LBYTE) (ta & Mem.CHRBitMask);
								Mem.UpdateCHRPointers();
								tprint(AnsiString("RAMBO-1: CHRpg[") + AnsiString(6 ^ (MMC3.CHRSelect << 2)) + AnsiString("] = ") + AnsiString(ta));
								return;
							case 5 :
								Mem.CHRPageNumNew[7^(MMC3.CHRSelect << 2)] = (LBYTE) (ta & Mem.CHRBitMask);
								Mem.UpdateCHRPointers();
								tprint(AnsiString("RAMBO-1: CHRpg[") + AnsiString(7 ^ (MMC3.CHRSelect << 2)) + AnsiString("] = ") + AnsiString(ta));
								return;
							case 6 :
								Mem.PRGPageNumNew[MMC3.PRGSelect] = (BYTE) (ta & Mem.PRGBitMask);
								Mem.UpdatePRGPointers();
								UpdateGGCodes();
								tprint(AnsiString("RAMBO-1: PRGpg[") + AnsiString(0 + MMC3.PRGSelect) + AnsiString("] = ") + AnsiString(ta));
								return;
							case 7 :
								Mem.PRGPageNumNew[1+MMC3.PRGSelect] = (BYTE) (ta & Mem.PRGBitMask);
								Mem.UpdatePRGPointers();
								UpdateGGCodes();
								tprint(AnsiString("RAMBO-1: PRGpg[") + AnsiString(1 + MMC3.PRGSelect) + AnsiString("] = ") + AnsiString(ta));
								return;
							case 8 :
								Mem.CHRPageNumNew[1] = (LBYTE) (ta & Mem.CHRBitMask);
								Mem.UpdateCHRPointers();
								tprint(AnsiString("RAMBO-1: CHRpg[") + AnsiString(1) + AnsiString("] = ") + AnsiString(ta));
								return;
							case 9 :
								Mem.CHRPageNumNew[3] = (LBYTE) (ta & Mem.CHRBitMask);
								Mem.UpdateCHRPointers();
								tprint(AnsiString("RAMBO-1: CHRpg[") + AnsiString(3) + AnsiString("] = ") + AnsiString(ta));
								return;
							case 15 :
								if (MMC3.PRGSelect)
								{
									Mem.PRGPageNumNew[0] = (BYTE) (ta & Mem.PRGBitMask);
								} else {
									Mem.PRGPageNumNew[2] = (BYTE) (ta & Mem.PRGBitMask);
								}
								Mem.UpdatePRGPointers();
								UpdateGGCodes();
								tprint(AnsiString("RAMBO-1: PRGpg[") + AnsiString((MMC3.PRGSelect) ? "0" : "2") + AnsiString("] = ") + AnsiString(ta));
								return;
						};
					}
					if (TU == 0xA000)	//May be inaccurate
					{
						if (bit0(ta))
						{
							Mem.UpdateNameTablePointers(0, 0, 2, 2);
						} else {
							Mem.UpdateNameTablePointers(0, 1, 0, 1);
						}
						tprint(AnsiString("RAMBO-1: MirrorChange: ") + AnsiString((bit0(ta)) ? "Horizontal" : "Vertical"));
						return;
					}
					return;
				case 66 :
					if (TU < 0x8000) return;

					Mem.PRGPageNumNew[0] = (BYTE) (((ta & 0xF0) >> 2) & Mem.PRGBitMask);
					Mem.PRGPageNumNew[1] = (BYTE) (Mem.PRGPageNumNew[0] + 1);
					Mem.PRGPageNumNew[2] = (BYTE) (Mem.PRGPageNumNew[0] + 2); Mem.PRGPageNumNew[3] = (BYTE) (Mem.PRGPageNumNew[0] + 3);

					Mem.CHRPageNumNew[0] = (BYTE) (((ta & 0x0F) << 3) & Mem.CHRBitMask);
					Mem.CHRPageNumNew[1] = (BYTE) (Mem.CHRPageNumNew[0] + 1);
					Mem.CHRPageNumNew[2] = (BYTE) (Mem.CHRPageNumNew[0] + 2); Mem.CHRPageNumNew[3] = (BYTE) (Mem.CHRPageNumNew[0] + 3);
					Mem.CHRPageNumNew[4] = (BYTE) (Mem.CHRPageNumNew[0] + 4); Mem.CHRPageNumNew[5] = (BYTE) (Mem.CHRPageNumNew[0] + 5);
					Mem.CHRPageNumNew[6] = (BYTE) (Mem.CHRPageNumNew[0] + 6); Mem.CHRPageNumNew[7] = (BYTE) (Mem.CHRPageNumNew[0] + 7);

					Mem.UpdateCHRPRGPointers();
					UpdateGGCodes();
					tprint(AnsiString("GNROM: PRG = ") + AnsiString(Mem.PRGPageNumNew[0]) + AnsiString(", CHR = ") + AnsiString(Mem.CHRPageNumNew[0] >> 3) + AnsiString(", ta = ") + IntToHex(ta,2));
					return;
				case 71 :
					if (TU < 0x8000) return;

					if (TU < 0xC000)
					{
						//Unknown
						tprinto(AnsiString("Camerica: Write to Unknown Area!  ta = ") + IntToHex(ta,2) + AnsiString(", addr = ") + IntToHex(TU,4));
					} else {
						Mem.PRGPageNumNew[0] = (BYTE) ((ta << 1) & Mem.PRGBitMask);
						Mem.PRGPageNumNew[1] = (BYTE) (Mem.PRGPageNumNew[0] + 1);
						Mem.UpdatePRGPointers();
						UpdateGGCodes();
						tprint(AnsiString("Camerica: PRGpg[0,1] = ") + AnsiString(Mem.PRGPageNumNew[0]) + AnsiString(",") + AnsiString(Mem.PRGPageNumNew[0] + 1) + AnsiString(", ta = ") + IntToHex(ta,2));
					}
					return;
			};
	};
}
//---------------------------------------------------------------------------
//Addressing Modes
//---------------------------------------------------------------------------
void __fastcall Addrmode(register BYTE adrmode)
{
	switch (adrmode) {
		case ImmA:	//Immediate - #nn
			TU = *Mem.Main[PC+1]; TUMode = tmVal;
			break;
		case Abs:	//Absolute - nnnn
			TU = (LBYTE) (Get16Bit(PC + 1));
			TUMode = tmAddr;
			break;
		case Zp:	//Zero-Page - nn
			TU = *Mem.Main[PC+1];
            TUMode = tmAddr;
			break;
		case Ind:	//Indirect Absolute - (nnnn)
			TU = (*Mem.Main[PC+2] << 8) + *Mem.Main[PC+1];
			TU = (*Mem.Main[(TU & 0xFF00) | (BYTE) (*Mem.Main[PC+1] + 1)] << 8) | *Mem.Main[TU];
			//W/O CPU BugFix: TU = (*Mem.Main[TU+1] << 8) + *Mem.Main[TU];
			TUMode = tmAddr;
			break;
		case Absx:	//Absolute Indexed, X - nnnn,X
			TU = (*Mem.Main[PC+2] << 8) + *Mem.Main[PC+1] + X;
			TUMode = tmAddr;
			break;
		case Absy:	//Absolute Indexed, Y - nnnn,Y
			TU = (*Mem.Main[PC+2] << 8) + *Mem.Main[PC+1] + Y;
			TUMode = tmAddr;
			break;
		case Zpx:	//Zero-Page Indexed, X - nn,X
			TU = (LBYTE) (*Mem.Main[PC+1] + X); TUMode = tmAddr;
			break;
		case Zpy:	//Zero-Page Indexed, Y - nn,Y
			TU = (LBYTE) (*Mem.Main[PC+1] + Y); TUMode = tmAddr;
			break;
		case Idx:	//Indexed Indirect - (nn,X)
			TU = *Mem.Main[PC+1] + X;
			TU = (LBYTE) (Get16Bit(TU));
			TUMode = tmAddr;
			break;
		case Idy:	//Indirect Indexed - (nn),Y
			TU = *Mem.Main[PC+1];
			TU = (*Mem.Main[TU+1] << 8) + *Mem.Main[TU] + Y;
			TUMode = tmAddr;
        	break;
		case Rel:	//Relative - nn
			TU2 = (char) (*Mem.Main[PC+1]);
			break;
		case Acc:	//Accumulator - A
			TU = 0x10000; TUMode = tmAddr;
			break;
		case ERA:
			if (HaltOnBadOp) CPURunning = false;
			Application->ProcessMessages();
			if (!DebuggingTrace)
			{
				dprinto(IntToHex(PC,4) + AnsiString("    ") + IntToHex(*Mem.Main[PC],2) + AnsiString("        Bad Opcode!"));
				Application->ProcessMessages();
			}
			break;
	}

	if (!DebuggingTrace) return;

	Application->ProcessMessages();

	AnsiString PCAS = IntToHex(PC,4) + AnsiString("    ");
	AnsiString TBAS = IntToHex(*Mem.Main[PC],2);
	AnsiString NBAS = IntToHex(*Mem.Main[PC+1],2);
	AnsiString NB2AS = IntToHex(*Mem.Main[PC+2],2);
	AnsiString TIAS = Mn[instruc[*Mem.Main[PC]]];

	switch (adrmode) {
		case ImmA:
			dprint(PCAS + TBAS + NBAS + AnsiString("      ") + TIAS + AnsiString(" #$") + NBAS);
            break;
		case Abs:
			dprint(PCAS + TBAS + NBAS + NB2AS + AnsiString("    ") + TIAS + AnsiString(" $") + NB2AS + NBAS);
            break;
		case Zp:
			dprint(PCAS + TBAS + NBAS + AnsiString("      ") + TIAS + AnsiString(" $00") + NBAS);
			break;
		case Imp:
			dprint(PCAS + TBAS + AnsiString("        ") + TIAS);
			break;
		case Ind:
			dprint(PCAS + TBAS + NBAS + NB2AS + AnsiString("    ") + TIAS + AnsiString(" ($") + NB2AS + NBAS + AnsiString(")"));
			break;
		case Absx:
			dprint(PCAS + TBAS + NBAS + NB2AS + AnsiString("    ") + TIAS + AnsiString(" $") + NB2AS + NBAS + AnsiString(", X"));
            break;
		case Absy:
			dprint(PCAS + TBAS + NBAS + NB2AS + AnsiString("    ") + TIAS + AnsiString(" $") + NB2AS + NBAS + AnsiString(", Y"));
            break;
		case Zpx:
			dprint(PCAS + TBAS + NBAS + AnsiString("      ") + TIAS + AnsiString(" $00") + NBAS + AnsiString(", X"));
			break;
		case Zpy:
			dprint(PCAS + TBAS + NBAS + AnsiString("      ") + TIAS + AnsiString(" $00") + NBAS + AnsiString(", Y"));
            break;
		case Idx:
			dprint(PCAS + TBAS + NBAS + AnsiString("      ") + TIAS + AnsiString(" ($") + NBAS + AnsiString(", X)"));
			break;
		case Idy:
			dprint(PCAS + TBAS + NBAS + AnsiString("      ") + TIAS + AnsiString(" ($") + NBAS + AnsiString("), Y"));
			break;
		case Rel:
			dprint(PCAS + TBAS + NBAS + AnsiString("      ") + TIAS + (bit7(*Mem.Main[PC+1]) ? AnsiString(" -$") : AnsiString(" $")) + IntToHex( abs(((char) (*Mem.Main[PC+1]))),2 ) );
            break;
		case Acc:
			dprint(PCAS + TBAS + AnsiString("        ") + TIAS + AnsiString(" A"));
			break;
		default :
			dprint(PCAS + TBAS + AnsiString("        Bad Opcode!"));
			break;
	}
}
//---------------------------------------------------------------------------
//Instructions
//---------------------------------------------------------------------------
void __fastcall ExecOp(register BYTE opcode)
{
	switch (opcode) {
		case ADC :
			tmpBYTE = TUVal();
			tmpshortint = (short int) (A + tmpBYTE + CCR.C);
			CCR.C = (tmpshortint > 0xFF);

			if (bit7(tmpBYTE) != bit7(A)) { CCR.V = false; }	//Signs Diff
			else {
				short int tmpshortint2 = (short int) (((char) A) + ((char) tmpBYTE) + CCR.C);
				if (bit7(tmpBYTE)) {		//Signs Neg
					if (tmpshortint2 < -128) CCR.V = true; else CCR.V = false;
				} else {					//Signs Pos
					if (tmpshortint2 > 127) CCR.V = true; else CCR.V = false;
				}
			}

			A = (BYTE) (tmpshortint);

			checkacc(A);
			break;
		case AND :
			A &= TUVal();
			checkacc(A);
			break;
		case ASL :
			tmpBYTE = MemoryTUGet();
			CCR.C = bit7(tmpBYTE);
			tmpBYTE <<= 1;
			checkacc(tmpBYTE)
			MemoryTUEquals(tmpBYTE);
			break;
		case BCC :
			if (!CCR.C) PC += TU2;
			break;
		case BCS :
			if (CCR.C) PC += TU2;
			break;
		case BEQ :
			if (CCR.Z) PC += TU2;
			break;
		case BIT :
			tmpBYTE = MemoryTUGet();
			CCR.N = bit7(tmpBYTE);
			CCR.V = bit6(tmpBYTE);
			tmpBYTE &= A;
			CCR.Z = (tmpBYTE == 0);
			break;
		case BMI :
			if (CCR.N) PC += TU2;
			break;
		case BNE :
			if (!CCR.Z) PC += TU2;
			break;
		case BPL :
			if (!CCR.N) PC += TU2;
			break;
		case BRK :
			PushPC();
			CCR.B = true;
			PushP();
			CCR.I = true;
			PC = (LBYTE) (Get16Bit(IRQVector));
			break;
		case BVC :
			if (!CCR.V) PC += TU2;
			break;
		case BVS :
			if (CCR.V) PC += TU2;
			break;
		case CLC :
			CCR.C = false;
			break;
		case CLD :
			CCR.D = false;
			break;
		case CLI :
			CCR.I = false;
			break;
		case CLV :
			CCR.V = false;
			break;
		case CMP :
			tmpshortint = (short int) (A - TUVal());
			checkacc(tmpshortint);
			CCR.C = (tmpshortint >= 0);
			break;
		case CPX :
			tmpshortint = (short int) (X - TUVal());
			checkacc(tmpshortint);
			CCR.C = (tmpshortint >= 0);
			break;
		case CPY :
			tmpshortint = (short int) (Y - TUVal());
			checkacc(tmpshortint);
			CCR.C = (tmpshortint >= 0);
			break;
		case DEC :
			tmpBYTE = MemoryTUGet();
			tmpBYTE--;
			checkacc(tmpBYTE);
			MemoryTUEquals(tmpBYTE);
			break;
		case DEX :
			X--;
			checkacc(X);
			break;
		case DEY :
			Y--;
			checkacc(Y);
			break;
		case EOR :
			A ^= TUVal();
            checkacc(A);
			break;
		case INC :
			tmpBYTE = MemoryTUGet();
			tmpBYTE++;
			checkacc(tmpBYTE);
			MemoryTUEquals(tmpBYTE);
			break;
		case INX :
			X++;
			checkacc(X);
			break;
		case INY :
			Y++;
			checkacc(Y);
			break;
		case JMP :
			PC = (LBYTE) (TU);
			break;
		case JSR :
			PushPC();
			PC = (LBYTE) (TU);
			break;
		case LDA :
			A = TUVal();
			checkacc(A);
			break;
		case LDX :
			X = TUVal();
			checkacc(X);
			break;
		case LDY :
			Y = TUVal();
			checkacc(Y);
			break;
		case LSR :
			tmpBYTE = MemoryTUGet();
			CCR.C = bit0(tmpBYTE);
			tmpBYTE >>= 1;
			CCR.N = false;
			CCR.Z = (tmpBYTE == 0);
			MemoryTUEquals(tmpBYTE);
			break;
		case ORA :
			A |= TUVal();
			checkacc(A);
			break;
		case PHA :
//			Mem.Stack[SP] = A;
			*Mem.Main[SP] = A;
			SP--;
			break;
		case PHP :
//			Mem.Stack[SP] = CCR.GetCCR();
			*Mem.Main[SP] = CCR.GetCCR();
			SP--;
			break;
		case PLA :
			SP++;
//			A = Mem.Stack[SP];
			A = *Mem.Main[SP];
			checkacc(A);
			break;
		case PLP :
			SP++;
//			CCR.MakeCCR(Mem.Stack[SP]);
			CCR.MakeCCR(*Mem.Main[SP]);
			break;
		case ROL :
			tmpBYTE = MemoryTUGet();
			if (CCR.C) {
				CCR.C = bit7(tmpBYTE);
				tmpBYTE <<= 1;
                tmpBYTE |= 1;
			} else {
				CCR.C = bit7(tmpBYTE);
				tmpBYTE <<= 1;
			}
			checkacc(tmpBYTE);
			MemoryTUEquals(tmpBYTE);
			break;
		case ROR :
			tmpBYTE = MemoryTUGet();
			if (CCR.C) {
				CCR.C = bit0(tmpBYTE);
				tmpBYTE >>= 1;
				tmpBYTE |= 0x80;
			} else {
				CCR.C = bit0(tmpBYTE);
				tmpBYTE >>= 1;
			}
			checkacc(tmpBYTE);
			MemoryTUEquals(tmpBYTE);
			break;
		case RTI :
			PullP();
			PullPC();
			break;
		case RTS :
			PullPC();
			break;
		case SBC :
			tmpBYTE = TUVal();
			tmpshortint = (short int) (A - tmpBYTE - (CCR.C ^ true));
			CCR.C = !(tmpshortint < 0);

			if (bit7(tmpBYTE) != bit7(A)) { CCR.V = false; }	//Signs Diff
			else {
				short int tmpshortint2 = (short int) (((char) A) - ((char) tmpBYTE) - (CCR.C ^ true));
				if (bit7(tmpBYTE)) {		//Signs Neg
					if (tmpshortint2 < -128) CCR.V = true; else CCR.V = false;
				} else {					//Signs Pos
					if (tmpshortint2 > 127) CCR.V = true; else CCR.V = false;
				}
			}

			A = (BYTE) (tmpshortint);
			checkacc(A);
			break;
		case SEC :
			CCR.C = true;
			break;
		case SED :
			CCR.D = true;
			break;
		case SEI :
        	CCR.I = true;
			break;
		case STA :
			MemoryTUEquals(A);
			break;
		case STX :
			MemoryTUEquals(X);
			break;
		case STY :
			MemoryTUEquals(Y);
			break;
		case TAX :
			X = A;
            checkacc(X);
			break;
		case TAY :
			Y = A;
            checkacc(Y);
			break;
		case TSX :
			X = SP;
			checkacc(X);
			break;
		case TXA :
			A = X;
			checkacc(A);
			break;
		case TXS :
			SP = (LBYTE) (X | (LBYTE) 0x100);
			break;
		case TYA :
			A = Y;
			checkacc(Y);
			break;
	}
}
//---------------------------------------------------------------------------
//Shortcut Commands
//---------------------------------------------------------------------------
char * __fastcall ToBin(BYTE tc)
{
	char * tmpvar = "00000000";
	if (tc & 1) { tmpvar[7] = 49; } else { tmpvar[7] = 48; }
	if (tc & 2) { tmpvar[6] = 49; } else { tmpvar[6] = 48; }
	if (tc & 4) { tmpvar[5] = 49; } else { tmpvar[5] = 48; }
	if (tc & 8) { tmpvar[4] = 49; } else { tmpvar[4] = 48; }
	if (tc & 16) { tmpvar[3] = 49; } else { tmpvar[3] = 48; }
	if (tc & 32) { tmpvar[2] = 49; } else { tmpvar[2] = 48; }
	if (tc & 64) { tmpvar[1] = 49; } else { tmpvar[1] = 48; }
	if (tc & 128) { tmpvar[0] = 49; } else { tmpvar[0] = 48; }
	return(tmpvar);
}
AnsiString ToBinC(BYTE tc, BYTE sb, BYTE eb)
{
	AnsiString tmpvar;
	for (int i=sb;i<=eb;i++)
		if (bit(tc,eb - i)) tmpvar += "1"; else tmpvar += "0";
	return(tmpvar);
}
//---------------------------------------------------------------------------

