//---------------------------------------------------------------------------
#include <mem.h>

#pragma hdrstop

#include "main.h"
#include "video.h"
#include "audio.h"
#include "6502.h"

//---------------------------------------------------------------------------
//Feature Defines
//---------------------------------------------------------------------------
//#define LogIt

//#define Breakpoints
#define BPVal 57300

//#define NewP
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

AnsiString MapperInfo[256] = {
"No Mapper", "MMC1", "UNROM", "CNROM", "MMC3", "MMC5", "FFE F4xxx", "AOROM",		//0-7
"FFE F3xxx", "MMC2", "MMC4", "Color Dreams", "", "", "", "100-in-1", "Bandai",		//8-16
"FFE F8xxx", "Jaleco SS8806", "Namcot 106", "", "Konami VRC4", "Konami VRC2 type A",//17-22
"Konami VRC2 type B", "Konami VRC6", "", "", "", "", "", "", "", "Irem G-101",		//23-32
"Taito TC0190", "Nina-1", "", "", "", "", "", "", "", "", "", "", "", "", "", "",	//33-48
"", "", "", "", "", "",	"", "", "", "", "", "", "", "", "",	"Tengen RAMBO-1",		//49-64
"Irem H-3001", "GNROM", "", "Sunsoft Mapper #4", "Sunsoft FME-7", "", "Camerica",	//63-71
"", "", "", "", "", "", "Irem 74HC161/32", "", "", "", "", "", "", "", "", "", "",	//72-88
"", "", "HK-SF3","","","","","","","","VS. System",									//89-99
"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", //100-120
"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", //121-141
"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", //142-162
"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", //163-183
"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", //184-204
"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", //205-225
"", "", "", "", "22-in-1", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", //226-246
"", "", "", "", "", "", "", "", ""													//247-255
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
BYTE X, Y, SP;
LBYTE PC;
int Clockticks, TU;
char TU2;
bool NMIonVBlank,NMIonSprHit,SSize,BkPTA,SpPTA,PPUAdrI,SprVis,BGVis,SprClip,BGClip,DispType;
bool VBlankOcc,Spr0Occ,ScLnSprCnt,VRAMWrFlg, VFirstRead, SFirstRead, CPURunning, TUMode;
LBYTE NTabAdr = 0x2000;
//unsigned long BGCol = cwhite;

#ifdef NewP
BYTE P;
#else
CCRSt CCR;
#endif

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
MMC4St MMC4;
M22in1St M22in1;
Bandai16St Bandai16;

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
#ifdef LogIt
	FILE * logit = fopen("output.log", "wb");
#endif
	while (CPURunning) {
		while (Clockticks < LineTickCountInt) {
			opcode = *Mem.Main[PC];
			Addrmode((BYTE) addressmode[opcode]);
			PC += bytes[opcode];
			ExecOp((BYTE) instruc[opcode]);
			Clockticks += ticks[opcode];
#ifdef LogIt
		tmpBYTE = (BYTE) (PC >> 8);
		fwrite(&tmpBYTE, 1, 1, logit);
		tmpBYTE = (BYTE) (PC & 0xFF);
		fwrite(&tmpBYTE, 1, 1, logit);
		fwrite(&A, 1, 1, logit);
		fwrite(&X, 1, 1, logit);
		fwrite(&Y, 1, 1, logit);
		fwrite(&P, 1, 1, logit);
#endif

#ifdef Breakpoints
		if (Clockticks > BPVal) CPURunning = false;
#endif
		}
		HBlank();
	}
#ifdef LogIt
	fclose(logit);
#endif
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
		if ((!VBlanking) && (BGVis))
		{
			MMC3.IRQCounter--;
		}
		if (MMC3.IRQCounter == 0)
		{
//			tprinto("MMC3: Timer = 0!");
			if (MMC3.IRQEnable)
			{
				irq6502();
				tprint("MMC3: IRQ from Scanline Timer!");
			}
			MMC3.IRQCounter = 0xFF;
//			MMC3.IRQEnable = false;
		}
	} else if (Mem.MapperNum == 24) {
		MMC3.IRQCounter++;
		if (MMC3.IRQCounter == 0xFF)
		{
			if (MMC3.IRQEnable) irq6502();
			MMC3.IRQCounter = 0;
//			MMC3.IRQEnable = false;
		}
	}

	if (GraphicsEngine == 2)
	{
		if (!VBlanking) DrawScanline();
	} else if (GraphicsEngine == 1) {
		if ((!VBlanking) && (ScanLine % 8 == 0)) DrawTileline();
	}

	unsigned char SSizeNew = (BYTE) ((SSize << 3) + 1);

	if ((bit5(Mem.Sprite[2])) && (Mem.Sprite[0] - 7 <= (ScanLine - 1)) && (Mem.Sprite[0] + SSizeNew > (ScanLine - 1)))
	{
		bool hflip = bit6(Mem.Sprite[2]);
		unsigned char ydiff = (BYTE) ((ScanLine - 1) - (Mem.Sprite[0] - 7));
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
		Application->ProcessMessages();

		for (int i=0;i<2;i++)
		{
			if (PulseChan[i].Enabled)
			{
				if (PulseChan[i].LengthLeft > 0)
				{
					if ((PulseChan[i].VolFade == 0) && (PulseChan[i].Volume > 0))  PulseChan[i].Volume-=PulseChan[i].FadeSpeed;
					if ((PulseChan[i].VolFade == 1) && (PulseChan[i].Volume < 15)) PulseChan[i].Volume+=PulseChan[i].FadeSpeed;
					SNDChannels[i].bVol = PulseChan[i].Volume;
					PulseChan[i].LengthLeft--;
//					PulseChan[i].Enabled = (bool) (PulseChan[i].LengthLeft);
				} else if (PulseChan[i].Loop) {
					if ((PulseChan[i].VolFade == 0) && (PulseChan[i].Volume > 0))  PulseChan[i].Volume-=PulseChan[i].FadeSpeed;
					if ((PulseChan[i].VolFade == 1) && (PulseChan[i].Volume < 15)) PulseChan[i].Volume+=PulseChan[i].FadeSpeed;
					SNDChannels[i].bVol = PulseChan[i].Volume;
				} else { SNDChannels[i].bVol = 0; }
			} else { SNDChannels[i].bVol = 0; }
		}
		if (DCMChan.Enabled)
		{
			if (DCMChan.BitPointer > (DCMChan.BitLength >> 3))
			{
				if (DCMChan.Loop)
				{
					SNDChannels[4].bVol = DCMChan.Volume;
					DCMChan.BitPointer = 0;
				} else {
					SNDChannels[4].bVol = 0;
					if (DCMChan.IRQGen) irq6502();
				}
			} else {
				SNDChannels[4].bVol = DCMChan.Volume;
			}
		} else { SNDChannels[4].bVol = 0; }

		tmpframes++;
		if (tmpframes >= (VBSec >> 1))
		{
			LARGE_INTEGER tmpval; int tmpval2;
			QueryPerformanceCounter(&tmpval);

			tmpval2 = (int) (tmpval.QuadPart - LastClockVal.QuadPart);
			FPSnum = ((VBSec >> 1) * ((int) ClockFreq.QuadPart)) / (tmpval2);

			if (Autoframeskip)
			{
				if (FPSnum > VBSec + 8) frameskip--;
				if (FPSnum < VBSec - 8) frameskip++;

				if (frameskip < 1) frameskip = 1;
				if (frameskip > Autoframeskipmax) frameskip = (BYTE) Autoframeskipmax;
			}

			StartFrm->FrameskipSlider->Position = (short int) frameskip;
//			StartFrm->FPSInfo->Caption = FPSnum;
			StartFrm->Caption = AnsiString("NES4PC - FPS: ") + AnsiString(FPSnum) + AnsiString(", Skip: ") + AnsiString(frameskip);
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
//	tprinto("NMI!");

//	PC++;
	PushPC();
	PushP();

#ifdef NewP

	P |= I_Flag;

#else

	CCR.I = true;

#endif

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
//	tprinto("IRQ!");

#ifdef NewP

	if (P & I_Flag) return;

#else

	if (CCR.I) return;

#endif

//	CPURunning = false; tprinto("IRQ");
//	PC++;
	PushPC();
	PushP();

#ifdef NewP

	P |= I_Flag;

#else

	CCR.I = true;

#endif

	PC = (LBYTE) (Get16Bit(IRQVector));
}

void HardBoot()
{
	for (int i=0;i<8;i++) Mem.CHRPageNum[i] = 99;
	for (int i=0;i<8;i++) Mem.CHRPageNumNew[i] = 99;
	for (int i=0;i<4;i++) Mem.PRGPageNum[i] = 99;
	for (int i=0;i<4;i++) Mem.PRGPageNumNew[i] = 99;

	switch (Mem.MapperNum) {
		case 230 :
			switch (M22in1.Resets) {
				case 0 : M22in1.ContraMode = true; M22in1.Resets = 1; break;
				case 1 : M22in1.ContraMode = false; M22in1.Resets = 2; break;
				case 2 : M22in1.ContraMode = true; M22in1.Resets = 3; break;
				case 3 : M22in1.ContraMode = false; M22in1.Resets = 4; break;
				case 4 : M22in1.ContraMode = false; M22in1.Resets = 0; break;
			};
			if (M22in1.ContraMode)
			{
				Mem.PRGPageNumNew[0] = 0; Mem.PRGPageNumNew[1] = 1;
				Mem.PRGPageNumNew[2] = 14; Mem.PRGPageNumNew[3] = 15;
				tprinto("22in1(C): Contra Mode");
			} else {
				Mem.PRGPageNumNew[0] = 16; Mem.PRGPageNumNew[1] = 17;
				Mem.PRGPageNumNew[2] = 78; Mem.PRGPageNumNew[3] = 79;
				tprinto("22in1(2): 22in1 Mode");
			}
			Mem.UpdatePRGPointers();
			break;
	};

	for (int i=0x0000;i<0x6000;i++)
		*Mem.Main[i] = 0x00;
	for (int i=0x2000;i<0x4000;i++)
		*Mem.PPU[i] = 0x00;
	setmem(&Mem.Sprite[0x00], 0x100, 0x00);
	SP = 0xFF;
#ifdef NewP
	P = 0x20;
#endif
	A = 0; X = 0; Y = 0;

	Mem.BgScrollX = 0; Mem.BgScrollY = 0;
	Mem.VRAMAddress = 0; Mem.SPRAddress = 0;
	NTabAdr = 0x2000;
	ScanLine = 0;
	LineTickCount = 0;
	LineTickCountInt = 0;
	NMIonVBlank = false; NMIonSprHit = false; SSize = false; BkPTA = false; SpPTA = false;
	Spr0Occ = false; VBlankOcc = false; PPUAdrI = false; SprVis = false; BGVis = false;
	SprClip = false; BGClip = false; DispType = false; ScLnSprCnt = false; VRAMWrFlg = false;
	VFirstRead = false; SFirstRead = false; TUMode = false;
	NTabAdr = 0x2000;

	MMC3.Command = 0; MMC3.IRQCounter = 0; MMC3.IRQLatch = 0;
	MMC3.IRQEnable = false; MMC3.PRGSelect = false; MMC3.CHRSelect = false;
	MMC1.Array = 0; MMC1.ArrayPtr = 0;
	MMC1.Reg[0] = 0; MMC1.Reg[1] = 0; MMC1.Reg[2] = 0; MMC1.Reg[3] = 0;
	MMC1.PRGSwitch = false; MMC1.PRGSwitchSize = false; MMC1.VROMSwitchSize = false;
	MMC1.PRGPageSwitch = false;

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
	PulseChan[0].Volume = 0;
	PulseChan[1].Volume = 0;
	PulseChan[0].LengthLeft = 0;
	PulseChan[1].LengthLeft = 0;
	PulseChan[0].Loop = false;
	PulseChan[1].Loop = false;

	reset6502();
}

void __fastcall reset6502()
{
	bool DontSwapVRAM = false, DontSwapPRG = false;

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

// vvv Unknown vvv
//			MMC3.IRQCounter = 0xFF;
// ^^^ Unknown ^^^
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
			MMC4.Latch[0] = 0xFE;
			MMC4.Latch[1] = 0xFE;
			break;
		case 10 :
			Mem.PRGPageNumNew[0] = 0; Mem.PRGPageNumNew[1] = 1;
			Mem.PRGPageNumNew[2] = (BYTE) (Mem.PRGPagesA - 2); Mem.PRGPageNumNew[3] = (BYTE) (Mem.PRGPagesA - 1);

// vvv Unknown vvv
			Mem.CHRPageNumNew[0] = 0; Mem.CHRPageNumNew[1] = 1; Mem.CHRPageNumNew[2] = 2;
			Mem.CHRPageNumNew[3] = 3; Mem.CHRPageNumNew[4] = 4; Mem.CHRPageNumNew[5] = 5;
			Mem.CHRPageNumNew[6] = 6; Mem.CHRPageNumNew[7] = 7;
// ^^^ Unknown ^^^
			MMC4.Latch[0] = 0xFE;
			MMC4.Latch[1] = 0xFE;
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

			Mem.CHRPageNumNew[0] = 0; Mem.CHRPageNumNew[1] = 1; Mem.CHRPageNumNew[2] = 2;
			Mem.CHRPageNumNew[3] = 3; Mem.CHRPageNumNew[4] = 4; Mem.CHRPageNumNew[5] = 5;
			Mem.CHRPageNumNew[6] = 6; Mem.CHRPageNumNew[7] = 7;

			DontSwapVRAM = true;
			break;
		case 17 :
			Mem.PRGPageNumNew[0] = 0; Mem.PRGPageNumNew[1] = 1;
			Mem.PRGPageNumNew[2] = (BYTE) (Mem.PRGPagesA - 2); Mem.PRGPageNumNew[3] = (BYTE) (Mem.PRGPagesA - 1);

			Mem.CHRPageNumNew[0] = 0; Mem.CHRPageNumNew[1] = 1; Mem.CHRPageNumNew[2] = 2;
			Mem.CHRPageNumNew[3] = 3; Mem.CHRPageNumNew[4] = 4; Mem.CHRPageNumNew[5] = 5;
			Mem.CHRPageNumNew[6] = 6; Mem.CHRPageNumNew[7] = 7;

			DontSwapVRAM = true;
			break;
		case 18 :
			Mem.PRGPageNumNew[0] = 0; Mem.PRGPageNumNew[1] = 1;
			Mem.PRGPageNumNew[2] = (BYTE) (Mem.PRGPagesA - 2); Mem.PRGPageNumNew[3] = (BYTE) (Mem.PRGPagesA - 1);

			Mem.CHRPageNumNew[0] = 0; Mem.CHRPageNumNew[1] = 1; Mem.CHRPageNumNew[2] = 2;
			Mem.CHRPageNumNew[3] = 3; Mem.CHRPageNumNew[4] = 4; Mem.CHRPageNumNew[5] = 5;
			Mem.CHRPageNumNew[6] = 6; Mem.CHRPageNumNew[7] = 7;

			DontSwapVRAM = true;
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

			Mem.CHRPageNumNew[0] = 0; Mem.CHRPageNumNew[1] = 1; Mem.CHRPageNumNew[2] = 2;
			Mem.CHRPageNumNew[3] = 3; Mem.CHRPageNumNew[4] = 4; Mem.CHRPageNumNew[5] = 5;
			Mem.CHRPageNumNew[6] = 6; Mem.CHRPageNumNew[7] = 7;

			DontSwapVRAM = true;
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

			Mem.CHRPageNumNew[0] = 0; Mem.CHRPageNumNew[1] = 1; Mem.CHRPageNumNew[2] = 2;
			Mem.CHRPageNumNew[3] = 3; Mem.CHRPageNumNew[4] = 4; Mem.CHRPageNumNew[5] = 5;
			Mem.CHRPageNumNew[6] = 6; Mem.CHRPageNumNew[7] = 7;

			DontSwapVRAM = true;
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

			Mem.CHRPageNumNew[0] = 0; Mem.CHRPageNumNew[1] = 1; Mem.CHRPageNumNew[2] = 2;
			Mem.CHRPageNumNew[3] = 3; Mem.CHRPageNumNew[4] = 4; Mem.CHRPageNumNew[5] = 5;
			Mem.CHRPageNumNew[6] = 6; Mem.CHRPageNumNew[7] = 7;

			DontSwapVRAM = true;
			break;
		case 33 :
			Mem.PRGPageNumNew[0] = 0; Mem.PRGPageNumNew[1] = 1;
			Mem.PRGPageNumNew[2] = (BYTE) (Mem.PRGPagesA - 2); Mem.PRGPageNumNew[3] = (BYTE) (Mem.PRGPagesA - 1);

			Mem.CHRPageNumNew[0] = 0; Mem.CHRPageNumNew[1] = 1; Mem.CHRPageNumNew[2] = 2;
			Mem.CHRPageNumNew[3] = 3; Mem.CHRPageNumNew[4] = 4; Mem.CHRPageNumNew[5] = 5;
			Mem.CHRPageNumNew[6] = 6; Mem.CHRPageNumNew[7] = 7;

			DontSwapVRAM = true;
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

			Mem.CHRPageNumNew[0] = 0; Mem.CHRPageNumNew[1] = 1; Mem.CHRPageNumNew[2] = 2;
			Mem.CHRPageNumNew[3] = 3; Mem.CHRPageNumNew[4] = 4; Mem.CHRPageNumNew[5] = 5;
			Mem.CHRPageNumNew[6] = 6; Mem.CHRPageNumNew[7] = 7;

			DontSwapVRAM = true;
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

			Mem.CHRPageNumNew[0] = 0; Mem.CHRPageNumNew[1] = 1; MemMThd     ‡MTrk  ´ ˇA ˇT`     ˇX ˇQf: ∞ ∞d ∞
7 ∞  ¿I ¬< ≤ ±d ±
7 ±  ¡G ± µ ¥x ¥
Z ¥  ƒ9 ¥ ≥n ≥
F ≥  √8 ≥ ≤x ≤
K ≤  ª
F ª  ÀX ª ∫u ∫
7 ∫  4 ∫ ∏n ∏
( ∏  » ∏ ∑n ∑
# ∑  «. ∑ ∂d ∂
- ∂ ∆/ ∂ µx µ
Z µ  ≈? ø ø
d ø œ0 ø æ} æ
 æ Œ1 æ Ωn Ω
K Ω  Õ- Ω ºx º
7 º  Ã  º ªdd}   ˜éû@<ö4Hñ(Xü47Å(Ü(@9ûC7,é@@ÅGéC@û@>ñ(>ÅXûC>é@@Å3Ü(@0û@AéC@	ö;@ä4@ÅDûC>é@@ÅYû@CéC@ñ(:ÅZûC>-é@@\Ü(@Aè4@"ü.Jó.>ñ.j û>;ö:DéC@ä;@TÜ.@ó260á.@ûA<é>@Zó5CPá2@Gû>Có:3ñ.6éA@ á5@xó>0Ü.@á:@)ûA>é>@ZóA0Åû>CóF0ö5@éA@
áA@á>@ ä:@ÅóA+.áF@ûAAé>@bó>$láA@ û>Pó:6 ñ.:éA@2á>@xó5CÜ.@á:@ûAAé>@]ó2>á5@jû>Gñ+Xä5@ü+SûF6éA@ö7@á2@ó+Oè.@ÅÜ+@=ûCMéF@
é>@ÅJéC@	ü>+ûFGû><ñ+CÅTûCCé>@éF@AÜ+@ÅûFJû><éC@?è>@má+@9éF@ûCEé>@ÅWéC@ ü>4ûFTû>7ñ+pÜ+@eéF@ûCJ
é>@Åbè+@ü&JûEJû><	éC@	ö9@ñ2jä7@cÜ2@ è>@Xé>@ûAC)éE@Å:ü>Cû>>ûE9éA@ñ2CÅÜ2@8é>@ûA<éE@Å\ûE6û>9éA@Åè>@WûAEéE@é>@ÅWü>CéA@ûE7 û>>ñ2+Å@Ü2@ûACé>@éE@ÅQü"Sè&@ûF6û>A
ö:@ñ.XéA@ä9@[è>@*Ü.@AûAAé>@éF@Å,ü>9ûFCû>9ñ.:éA@Å(Ü.@,é>@ûAAéF@ÅOûFEû>>öA@éA@ä:@iè>@QûAEé>@éF@ÅZü>'û>EûFMñ.+éA@Å!Ü.@*ûA>éF@	é>@ÅgûGJû@C ü(NäA@	ñ(jéA@ö@=	ó(6è"@?è>@Gó,66Ü(@ûD>á(@é@@ éG@Zó/>Já,@@ûG6û@<éD@ó4>ñ(O)á/@zó863ûD7á4@éG@é@@Ió;0
á8@!Ü(@`û@>ûGA	ö;=	ó@3ä@@éD@á;@~ó;:;éG@ûD<á@@é@@Ió8>%á;@cûGE	û@;éD@ñ()
ó46á8@yÜ(@ó/03á4@ûD>é@@éG@Qó,:á/@`ü%J
ûITéD@û@E
ñ1jö==è(@ó%Oä;@3á,@cÜ1@ûD7é@@éI@ÅFû@<ûITéD@ñ1Oü89ÅPéI@ûD<é@@ÅPéD@ûIJ û@;Kè8@Ü1@kéI@ûD>á%@é@@ÅZûIGû@A ü81éD@ñ1&Å<Ü1@ûD<é@@éI@Åä=@$ü,NûGAè%@û@7ö?=éD@ñ,XÅ
è8@.Ü,@ûD7éG@é@@Å\ü8(
ûG; û@CéD@ñ,6ÅSûDCéG@é@@ZÜ,@Å û?AéD@ ûG<ÅMéG@è8@ûDEé?@ÅFéD@ûG;û?Gñ,mÜ,@@é?@:ûD>éG@ÅéD@>ü+Fí7Hè,@ö7@ñ+Xä?@ÅÜ+@ÇHñ+3ÇÜ+@ÅCí>HÇ7@ö>7gä7@Çuñ+$ÅÜ+@Ç4ü%Fí=Hñ1X
Ç>@ö==è+@ä>@\Ü1@ÇYñ1-ÅwÜ1@Å@Ç=@í8>ö8H;ä=@É*ñ16Å
Ü1@Åxœ,8è%@ü"Uô1ñ.jí:>Œ,ä8@ö:Dû:Ç8@<â1@xÜ.@Çñ.ÇxÜ.@2êI6öA=ö==ä:@É^ñ.&ÅÜ.@4êF:ÄI@	ö:=ä=@Å.é:@ÄF@äA@êBCöB0û1ö6D ñ)Xpä:@gû:Ü)@é1@ÅUû=ñ)6é:@Åè"@.ûB"0é=@ÅÜ)@5öC5ûF-ê?3ÄB@äB@	éB@ö3=/ä6@Å+ûC".éF@ÅBû? =éC@Å/û:í86Ç:@>é?@yê=0öA=ü.?Ä?@äC@	û:ö:@ ô1é:@ñ.Xä3@ í::Ç8@Å+â1@rÜ.@Å=ñ.3Ç1Ü.@Å öI,ö=@ä:@ÖCä=@ö:=Å'œ04öB3öF5ä:@ü*Kö6@ñ*û1(äA@è.@Ä=@é:@ÅÜ*@û:%;é1@Å=ñ* û=%(é:@ÅÜ*@"ûB%.é=@ÅäI@äB@öK=ü'Fè*@öC:ûF)ñ'Xö3DéB@4ä6@ÅûC-Ü'@éF@nÇ:@mû?-ñ'éC@ÅÜ'@?û: \äF@
é?@äK@RäC@
è'@é:@î1/î%/ö1Hü%Cä3@áÑ%@î,/ î8/Ñ1@ö8@Åä1@Üî+2î76Ñ8@Ñ,@ö7HVä8@ÜJî%/î1/Ñ+@Ñ7@
ö1DÅ$ä7@Üñ-Xü!Yä1@î(2 î4/
è%@ö4@Ñ1@Ñ%@Å`Ü-@Åkñ-Å'Ü-@Ç	íGC:ñ-	êG-ÅÜ-@ÖpíF:êF)ÇG@ÄG@ÜpÇF@ í@0ÄF@ê@áÑ(@Ñ4@,ü4/è!@ûLÇè4@Å9éL@ûOü47Åpè4@Åoü4,ûLéO@õL-ö;H&ä4@ÅHè4@Å7éL@ûOü42ÇÇ@@Ä@@è4@Åü.9éO@ ûL%ö:7ãL@ä;@õM$Çè.@[éL@ûMü.-Ç-è.@Å ûJéM@ü./ö5@	ä:@Ç6è.@Å ûMéJ@ü.1ÇãM@è.@Å ûJä5@éM@ö7Dü+JÇè+@ÅAûOü+,=éJ@Çè+@ÅûJéO@ü+4Ç-è+@Å"ûOü+9RéJ@Ågè+@ÅéO@ûJ
ü2+ö9D>ä7@Çè2@iûMéJ@ü2,ÇPè2@yûJéM@ü2/ÇXè2@sûMü2/éJ@Çè2@ÅíA6%ü.4ûJéM@ ö:7(ä9@Ç'è.@YéJ@	ûMí::
ü.7ÇA@Çè.@ÅöF,ûJõR"íA0éM@ü.7Ç:@öA5+ä:@Çè.@Uí:-ÇA@ûMéJ@ ü.=Çwè.@<äA@í@&	Ç:@õS3ãR@öG7ûLäF@ü(1ö@D
éM@Ç$è(@zí;:"ûPü(@Ç@@éL@ÇEè(@{í@>Ç;@ öD3ü(9ûLéP@ö;HäG@ä@@Å{è(@Åí;>ûPü(4éL@Ç@@Ç*è(@Å
í83ä;@ Ç;@éP@õUûLãS@ü19í=Jö=@Ç^è1@rü17 ûPéL@RÇ8@Å^è1@ÅéP@í@"ûLü1;ÇKè1@ÅûPéL@ü19OÇ@@ÅZè1@oãU@íBí;H	Ç=@ü#>éP@öB: ûKü/9äD@ö?3Åä=@Å?è/@hûNéK@ü/1Éè#@=ü#:ûKéN@ÇYè/@qûNéK@ ü/7ÇPè/@äB@è#@ÇB@ä?@Ç;@Aû:û>ü+;ö7Dû7JéN@Å{è+@Åü+1Ç:è+@Å&ü+;ö>7öC5Uä7@Å`è+@Åü+9ÇKè+@Åü%;ö=:ä>@ öDH%äC@é>@ û=	é:@ û5	û8	é7@Çè%@zü%=Çè%@ÅLü19ö8:ä=@õP>ÇAè1@oü19Çjè1@uü.4õR>	ãP@é8@ û:ö:=öA.;äD@(ä8@Å+è.@Åü.4ÉvöI3]äA@Çè.@mü.9ÇPè.@Pä:@;ü)@	äI@û8öD:û<ö<:	ãR@é:@õT32é=@Å!è)@Å\ü)@ÉöM3täD@Åè)@Å5ü)9ÇGè)@?ãT@UûAü)7ûDé5@ é8@ö=:	é<@*ä<@Å_è)@Å5ü)9ÉEöD%8ö80bä=@äM@Åè)@ÅTü),Çè)@ÅIü'+"ö7='ä8@Åiè'@Å2ü')ÇäD@è'@Å>ü%,ö1=.ä7@Åpè%@Å.ü%,Ç-è%@véA@,ûE	û@	ü!,éD@ö47#ä1@Ågè!@Å#ü!9Ñ#õS Åfè!@Å.ü!;Çè!@ÅXü!;+õRãS@Å è!@Çü!;ÉVõLé@@ éE@vãR@uè!@Å]ü!-1ä4@Ånè!@nãL@}  ˜ ˇ/                                                                ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠≠µ≠