//---------------------------------------------------------------------------
//#pragma inline
#include <vcl\vcl.h>
#include <mem.h>
#include <memory.h>
#pragma hdrstop

#include "6502.h"
#include "main.h"
#include "video.h"
//#include "audio.h"
#include "mappers.h"
#include "States.h"
//---------------------------------------------------------------------------
//Feature Defines
//---------------------------------------------------------------------------
#define LogIt
#define TraceMem(Addy)	((PC & 0x8000) ? (Mem.PRGPage[Mem.PRGPageNum[(Addy & 0x6000) >> 13]][Addy & 0x1FFF]) : (*Mem.Main[PC]))


//---------------------------------------------------------------------------
//Information Arrays
//---------------------------------------------------------------------------
BYTE addressmode[256]=
{//     0    1   2    3   4   5   6   7   8   9    A   B   C    D    E    F
		Imp ,Idx,ERA ,ERA,Imp,Zp ,Zp ,ERA,Imp,ImmA,Imp,ERA,ERA ,Abs ,Abs ,ERA,	//0x00
        Rel ,Idy,ERA ,ERA,ERA,Zpx,Zpx,ERA,Imp,Absy,Imp,ERA,ERA ,Absx,Absx,ERA,  //0x10
		Abs ,Idx,ERA ,ERA,Zp ,Zp ,Zp ,ERA,Imp,ImmA,Imp,ERA,Abs ,Abs ,Abs ,ERA,	//0x20
		Rel ,Idy,ERA ,ERA,ERA,Zpx,Zpx,ERA,Imp,Absy,ERA,ERA,ERA ,Absx,Absx,ERA,	//0x30
		Imp ,Idx,ERA ,ERA,ERA,Zp ,Zp ,ERA,Imp,ImmA,Imp,ERA,Abs ,Abs ,Abs ,ERA,	//0x40
		Rel ,Idy,ERA ,ERA,Imp,Zpx,Zpx,ERA,Imp,Absy,ERA,ERA,ERA ,Absx,Absx,ERA,	//0x50
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

BYTE instruc[256]=
{//     0   1   2   3   4   5   6   7   8   9   A    B   C   D   E   F
        BRK,ORA,ERO,ERO,ERO,ORA,ASL,ERO,PHP,ORA,ASLA,ERO,ERO,ORA,ASL,ERO, //00
        BPL,ORA,ERO,ERO,ERO,ORA,ASL,ERO,CLC,ORA,ERO ,ERO,ERO,ORA,ASL,ERO, //10
        JSR,AND,ERO,ERO,BIT,AND,ROL,ERO,PLP,AND,ROLA,ERO,BIT,AND,ROL,ERO, //20
        BMI,AND,ERO,ERO,ERO,AND,ROL,ERO,SEC,AND,ERO ,ERO,ERO,AND,ROL,ERO, //30
        RTI,EOR,ERO,ERO,ERO,EOR,LSR,ERO,PHA,EOR,LSRA,ERO,JMP,EOR,LSR,ERO, //40
        BVC,EOR,ERO,ERO,ERO,EOR,LSR,ERO,CLI,EOR,ERO ,ERO,ERO,EOR,LSR,ERO, //50
        RTS,ADC,ERO,ERO,ERO,ADC,ROR,ERO,PLA,ADC,RORA,ERO,JMP,ADC,ROR,ERO, //60
		BVS,ADC,ERO,ERO,ERO,ADC,ROR,ERO,SEI,ADC,ERO ,ERO,ERO,ADC,ROR,ERO, //70
        ERO,STA,ERO,ERO,STY,STA,STX,ERO,DEY,STA,TXA ,ERO,STY,STA,STX,ERO, //80
        BCC,STA,ERO,ERO,STY,STA,STX,ERO,TYA,STA,TXS ,ERO,ERO,STA,ERO,ERO, //90
        LDY,LDA,LDX,ERO,LDY,LDA,LDX,ERO,TAY,LDA,TAX ,ERO,LDY,LDA,LDX,ERO, //A0
        BCS,LDA,ERO,ERO,LDY,LDA,LDX,ERO,CLV,LDA,TSX ,ERO,LDY,LDA,LDX,ERO, //B0
        CPY,CMP,ERO,ERO,CPY,CMP,DEC,ERO,INY,CMP,DEX ,ERO,CPY,CMP,DEC,ERO, //C0
        BNE,CMP,ERO,ERO,ERO,CMP,DEC,ERO,CLD,CMP,ERO ,ERO,ERO,CMP,DEC,ERO, //D0
        CPX,SBC,ERO,ERO,CPX,SBC,INC,ERO,INX,SBC,NOP ,ERO,CPX,SBC,INC,ERO, //E0
        BEQ,SBC,ERO,ERO,ERO,SBC,INC,ERO,SED,SBC,ERO ,ERO,ERO,SBC,INC,ERO  //F0
};

char TraceArr[256][16] = {
"BRK ","ORA ","Bad Opcode ","Bad Opcode ","Bad Opcode ","ORA ","ASL ","Bad Opcode ","PHP ","ORA ","ASLA","Bad Opcode ","Bad Opcode ","ORA ","ASL ","Bad Opcode ", //00
"BPL ","ORA ","Bad Opcode ","Bad Opcode ","Bad Opcode ","ORA ","ASL ","Bad Opcode ","CLC ","ORA ","Bad Opcode ","Bad Opcode ","Bad Opcode ","ORA ","ASL ","Bad Opcode ", //10
"JSR ","AND ","Bad Opcode ","Bad Opcode ","BIT ","AND ","ROL ","Bad Opcode ","PLP ","AND ","ROLA","Bad Opcode ","BIT ","AND ","ROL ","Bad Opcode ", //20
"BMI ","AND ","Bad Opcode ","Bad Opcode ","Bad Opcode ","AND ","ROL ","Bad Opcode ","SEC ","AND ","Bad Opcode ","Bad Opcode ","Bad Opcode ","AND ","ROL ","Bad Opcode ", //30
"RTI ","EOR ","Bad Opcode ","Bad Opcode ","Bad Opcode ","EOR ","LSR ","Bad Opcode ","PHA ","EOR ","LSRA","Bad Opcode ","JMP ","EOR ","LSR ","Bad Opcode ", //40
"BVC ","EOR ","Bad Opcode ","Bad Opcode ","Bad Opcode ","EOR ","LSR ","Bad Opcode ","CLI ","EOR ","Bad Opcode ","Bad Opcode ","Bad Opcode ","EOR ","LSR ","Bad Opcode ", //50
"RTS ","ADC ","Bad Opcode ","Bad Opcode ","Bad Opcode ","ADC ","ROR ","Bad Opcode ","PLA ","ADC ","RORA","Bad Opcode ","JMP ","ADC ","ROR ","Bad Opcode ", //60
"BVS ","ADC ","Bad Opcode ","Bad Opcode ","Bad Opcode ","ADC ","ROR ","Bad Opcode ","SEI ","ADC ","Bad Opcode ","Bad Opcode ","Bad Opcode ","ADC ","ROR ","Bad Opcode ", //70
"Bad Opcode ","STA ","Bad Opcode ","Bad Opcode ","STY ","STA ","STX ","Bad Opcode ","DEY ","STA ","TXA ","Bad Opcode ","STY ","STA ","STX ","Bad Opcode ", //80
"BCC ","STA ","Bad Opcode ","Bad Opcode ","STY ","STA ","STX ","Bad Opcode ","TYA ","STA ","TXS ","Bad Opcode ","Bad Opcode ","STA ","Bad Opcode ","Bad Opcode ", //90
"LDY ","LDA ","LDX ","Bad Opcode ","LDY ","LDA ","LDX ","Bad Opcode ","TAY ","LDA ","TAX ","Bad Opcode ","LDY ","LDA ","LDX ","Bad Opcode ", //A0
"BCS ","LDA ","Bad Opcode ","Bad Opcode ","LDY ","LDA ","LDX ","Bad Opcode ","CLV ","LDA ","TSX ","Bad Opcode ","LDY ","LDA ","LDX ","Bad Opcode ", //B0
"CPY ","CMP ","Bad Opcode ","Bad Opcode ","CPY ","CMP ","DEC ","Bad Opcode ","INY ","CMP ","DEX ","Bad Opcode ","CPY ","CMP ","DEC ","Bad Opcode ", //C0
"BNE ","CMP ","Bad Opcode ","Bad Opcode ","Bad Opcode ","CMP ","DEC ","Bad Opcode ","CLD ","CMP ","Bad Opcode ","Bad Opcode ","Bad Opcode ","CMP ","DEC ","Bad Opcode ", //D0
"CPX ","SBC ","Bad Opcode ","Bad Opcode ","CPX ","SBC ","INC ","Bad Opcode ","INX ","SBC ","NOP ","Bad Opcode ","CPX ","SBC ","INC ","Bad Opcode ", //E0
"BEQ ","SBC ","Bad Opcode ","Bad Opcode ","Bad Opcode ","SBC ","INC ","Bad Opcode ","SED ","SBC ","Bad Opcode ","Bad Opcode ","Bad Opcode ","SBC ","INC ","Bad Opcode "  //F0
};

BYTE TraceAddyMode[256]=
{//     0    1   2    3   4   5   6   7   8   9    A   B   C    D    E    F
		Imp ,Idx,ERA ,ERA,Imp,Zp ,Zp ,ERA,Imp,ImmA,Imp,ERA,ERA ,Abs ,Abs ,ERA,	//0x00
        Rel ,Idy,ERA ,ERA,ERA,Zpx,Zpx,ERA,Imp,Absy,Imp,ERA,ERA ,Absx,Absx,ERA,  //0x10
		Abs ,Idx,ERA ,ERA,Zp ,Zp ,Zp ,ERA,Imp,ImmA,Imp,ERA,Abs ,Abs ,Abs ,ERA,	//0x20
		Rel ,Idy,ERA ,ERA,ERA,Zpx,Zpx,ERA,Imp,Absy,ERA,ERA,ERA ,Absx,Absx,ERA,	//0x30
		Imp ,Idx,ERA ,ERA,ERA,Zp ,Zp ,ERA,Imp,ImmA,Imp,ERA,Abs ,Abs ,Abs ,ERA,	//0x40
		Rel ,Idy,ERA ,ERA,Imp,Zpx,Zpx,ERA,Imp,Absy,ERA,ERA,ERA ,Absx,Absx,ERA,	//0x50
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


BYTE ticks[256]=
{
	7,6,0,0,2,3,5,0,3,2,2,0,0,4,6,0,
    3,5,0,0,0,4,6,0,2,4,2,0,0,4,7,0,
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

AnsiString Mn[61] = {"ADC ","AND ","ASL ","BCC ","BCS ","BEQ ","BIT ","BMI ","BNE ","BPL ","BRK ","BVC ",
"BVS ","CLC ","CLD ","CLI ","CLV ","CMP ","CPX ","CPY ","DEC ","DEX ","DEY ","EOR ","INC ","INX ","INY ",
"JMP ","JSR ","LDA ","LDX ","LDY ","LSR ","NOP ","ORA ","PHA ","PHP ","PLA ","PLP ","ROL ","ROR ","RTI ","RTS ",
"SBC ","SEC ","SED ","SEI ","STA ","STX ","STY ","TAX ","TAY ","TSX ","TXA ","TXS ","TYA ",
"ASLA","LSRA","ROLA","RORA","????"
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
"", "Tekken 2/MK4 Hacks", "HK-SF3","","","","","","","","VS. System",				//89-99
"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", //100-120
"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", //121-141
"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", //142-162
"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", //163-183
"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", //184-204
"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", //205-225
"76-in-1", "1200-in-1", "Action 52", "", "22-in-1", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", //226-246
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
extern bool Autoframeskip;
extern int FPSnum, Autoframeskipmax, frameskip;
extern TForm *VWFORM;
extern BYTE bitnumsp[2][8];
//Game Genie
int GGCodeNum;
GGCodeSt GGCode[50];
//Internal CPU
BYTE A, X, Y, SP;
unsigned long int PC, TU;
char ClockticksSm;
char TU2;
bool NMIonVBlank,NMIonSprHit,SSize,BkPTA,SpPTA,PPUAdrI,SprVis,BGVis,SprClip,BGClip,DispType;
bool VBlankOcc,Spr0Occ,ScLnSprCnt,VRAMWrFlg, VFirstRead, SFirstRead, CPURunning, TUMode;
LBYTE NTabAdr = 0x2000;
bool SpecialAccessR[0xffff], SpecialAccessW[0xffff];
//unsigned long BGCol = cwhite;

BYTE P = 0x20;
//CCRSt CCR;

MemSt Mem;
//Timing
bool PALMode;
short int LineRate,LineTotal,ScanLine,VBScanLine,MaxScanLine,MHBValue,ScanLineFake;
BYTE LineTicksInt;
float CPUSpeed;
bool VBlanking, FakeSLUsing;
int VBSec;
short int YMax;
//Joystick
extern int JP1A, JP1B, JP1Select, JP1Start, JP1Up, JP1Down, JP1Left, JP1Right;
extern int JP2A, JP2B, JP2Select, JP2Start, JP2Up, JP2Down, JP2Left, JP2Right;
JoypadSt Joy;
extern COLORREF Palette[68];
//Sound
//PulseChanSt PulseChan[2];
//TriChanSt TriChan;
//NoiseChanSt NoiseChan;
//DCMChanSt DCMChan;
//extern BYTE bWAVE[32];
//extern struct _SNDChan SNDChannels[5];
//ROM
FILE * SRAMFileWr, * SRAMFileRd;
bool ROMTrainer;
MMC1St MMC1;
MMC3St MMC3;
//MMC4St MMC4;
M22in1St M22in1;
M16St M16;
M17St M17;
M90St M90;
M24St M24;

extern bool SavingState;

//FPS
extern LARGE_INTEGER ClockFreq;
extern long ClockFreqVblank;
LARGE_INTEGER LastClockVal;

FILE *dout;
#define DPrint(A,B)		fwrite(A,1,B,dout);
//---------------------------------------------------------------------------
//NES Emulator Setup
//---------------------------------------------------------------------------
void NewCPUMode(short int NTSCMode)
{
        PALMode = (bool) (NTSCMode == 0);

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
	LineTicksInt = (BYTE) (CPUSpeed / LineRate);
	ClockFreqVblank = (int) (ClockFreq.QuadPart / VBSec);
}
void Setup(TForm *tf, RECT trct, TMemo *ta, TMemo *tb)
{
	dout = fopen("c:\\debugn4p.txt","w");

	Joy.PaddlePosition = 172;
	Joy.UpdateSig();

	DebuggingTrace = false;
	DebuggingRegs = false;

	Mem.SetupPointers();

        for (int i=0;i<0x10000;i++)
        {
                SpecialAccessR[i] = false;
                SpecialAccessW[i] = false;
        }
        for (int i=0x2000;i<0x2008;i++)
        {
                SpecialAccessR[i] = false;
                SpecialAccessW[i] = true;
        }
        for (int i=0x4000;i<0x4018;i++)
        {
                SpecialAccessR[i] = false;
                SpecialAccessW[i] = true;
        }

        SpecialAccessR[PPUStat] = true;
        SpecialAccessR[SPRIO] = true;
        SpecialAccessR[VRAMIO] = true;
        SpecialAccessR[pAPUStCh] = true;
        SpecialAccessR[Joypad1] = true;
        SpecialAccessR[Joypad2] = true;

        SpecialAccessW[PPUStat] = false;

        for (int i=0x6000;i<0x8000;i++)
        {
                SpecialAccessR[i] = true;
                SpecialAccessW[i] = true;
        }

        for (int i=0x8000;i<0x10000;i++)
        {
                SpecialAccessR[i] = false;
                SpecialAccessW[i] = true;
        }

        //Mapper 17
        for (int i=0x42FC;i<=0x42FF;i++)
                SpecialAccessW[i] = true;
        for (int i=0x4501;i<=0x4507;i++)
                SpecialAccessW[i] = true;
        for (int i=0x4510;i<=0x4517;i++)
                SpecialAccessW[i] = true;

        VideoSetup(tf,trct,ta,tb);
//        AudioSetup(tf);
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
//        AudioShutdown();
}
//---------------------------------------------------------------------------
//6502 General Commands
//---------------------------------------------------------------------------

void __fastcall exec6502()
{
        BYTE opcode;
	while (CPURunning) {
		while (ClockticksSm > 0) {
			if (PC & 0x8000)
                                opcode = Mem.PRGPage[Mem.PRGPageNum[(PC & 0x6000) >> 13]][PC & 0x1FFF];
                        else
                                opcode = *Mem.Main[PC];


                      switch (opcode) {
                                case 0 :
                                        SetB();
                                        PushPCaP();
                                        SetI();
                                        PC = (LBYTE) ((Mem.PRGPage[Mem.PRGPageNum[3]][0x1FFF] << 8) | Mem.PRGPage[Mem.PRGPageNum[3]][0x1FFE]);
                                        break;


                        };

			ClockticksSm -= (char) ticks[opcode];
		}
		HBlank();
	}
}

void __fastcall run6502()
{
//        DXOpen();

        BYTE opcode;
	while (CPURunning) {
		while (ClockticksSm > 0) {
			if (PC & 0x8000)
			opcode = Mem.PRGPage[Mem.PRGPageNum[(PC & 0x6000) >> 13]][PC & 0x1FFF];
		else
			opcode = *Mem.Main[PC];

	  /*		BYTE op2, op3;
			if ((PC+1) & 0x8000)
                                op2 = Mem.PRGPage[Mem.PRGPageNum[((PC+1) & 0x6000) >> 13]][(PC+1) & 0x1FFF];
                        else
                                op2 = *Mem.Main[PC+1];
			if ((PC+2) & 0x8000)
                                op3 = Mem.PRGPage[Mem.PRGPageNum[((PC+2) & 0x6000) >> 13]][(PC+2) & 0x1FFF];
                        else
                                op3 = *Mem.Main[PC+2];

			char tpout[50], tpo2[50];
			ZeroMemory(&tpout, sizeof(tpout));
			if (bytes[opcode] == 1)
			{
				sprintf(&tpout[0],"%04X - %02X\0",PC,opcode);
			} else if (bytes[opcode] == 2) {
				sprintf(&tpout[0],"%04X - %02X %02X\0",PC,opcode,op2);
			} else {
				sprintf(&tpout[0],"%04X - %02X %02X %02X\0",PC,opcode,op2,op3);
			}*/

            char Out1[80], Out2[40];
			unsigned short Addy = PC;
			sprintf(Out1, "%04X    %02X", Addy, TraceMem(Addy));				//PC

			switch (TraceAddyMode[TraceMem(Addy)])
			{
			case ImmA : sprintf(Out2," %02X      %s#$%02X      ", TraceMem(Addy + 1), TraceArr[TraceMem(Addy)], TraceMem(Addy + 1)); break;
			case Abs : sprintf(Out2," %02X %02X   %s$%04X     ", TraceMem(Addy + 1), TraceMem(Addy + 2), TraceArr[TraceMem(Addy)], TraceMem(Addy + 1) | (TraceMem(Addy + 2) << 8)); break;
			case Zp : sprintf(Out2," %02X      %s$%02X       ", TraceMem(Addy + 1), TraceArr[TraceMem(Addy)], TraceMem(Addy + 1)); break;
			case Acc : sprintf(Out2,"         %sA         ", TraceArr[TraceMem(Addy)]); break;
			case Imp : sprintf(Out2,"         %s          ", TraceArr[TraceMem(Addy)]); break;
			case ERA : sprintf(Out2,"         %s          ", TraceArr[TraceMem(Addy)]); break;
			//Add Comments for Addy pointed to/Actual Addy on These
			case Ind : sprintf(Out2," %02X %02X   %s($%04X)   ", TraceMem(Addy + 1), TraceMem(Addy + 2), TraceArr[TraceMem(Addy)], TraceMem(Addy + 1) | (TraceMem(Addy + 2) << 8)); break;
			case Absx : sprintf(Out2," %02X %02X   %s$%04X,X   ", TraceMem(Addy + 1), TraceMem(Addy + 2), TraceArr[TraceMem(Addy)], TraceMem(Addy + 1) | (TraceMem(Addy + 2) << 8)); break;
			case Absy : sprintf(Out2," %02X %02X   %s$%04X,Y   ", TraceMem(Addy + 1), TraceMem(Addy + 2), TraceArr[TraceMem(Addy)], TraceMem(Addy + 1) | (TraceMem(Addy + 2) << 8)); break;
			case Zpx : sprintf(Out2," %02X      %s$%02X,X    ", TraceMem(Addy + 1), TraceArr[TraceMem(Addy)], TraceMem(Addy + 1)); break;
			case Zpy : sprintf(Out2," %02X      %s$%02X,Y    ", TraceMem(Addy + 1), TraceArr[TraceMem(Addy)], TraceMem(Addy + 1)); break;
			case Idx : sprintf(Out2," %02X      %s($%02X,X)   ", TraceMem(Addy + 1), TraceArr[TraceMem(Addy)], TraceMem(Addy + 1)); break;
			case Idy : sprintf(Out2," %02X      %s($%02X),Y   ", TraceMem(Addy + 1), TraceArr[TraceMem(Addy)], TraceMem(Addy + 1)); break;
			case Rel :
				if (TraceMem(Addy + 1) & 0x80)
				{
					BYTE TpRelVal = ~TraceMem(Addy + 1) + 1;
					sprintf(Out2," %02X      %s-$%02X      ", TraceMem(Addy + 1), TraceArr[TraceMem(Addy)], TpRelVal);	//Is this Right?...
				} else {
					sprintf(Out2," %02X      %s$%02X       ", TraceMem(Addy + 1), TraceArr[TraceMem(Addy)], TraceMem(Addy + 1));
				}
				break;
			};
			strcat(Out1, Out2);

			Addrmode((BYTE) addressmode[opcode]);
			PC += bytes[opcode];
			ExecOp((BYTE) instruc[opcode]);
			ClockticksSm -= (char) ticks[opcode];

			sprintf(Out2,"A:%02X X:%02X Y:%02X P:%02X SP:%02X\n\0",A,X,Y,P,SP);
			strcat(Out1,Out2);

  			DPrint(Out1,strlen(Out1));
	  		_flushall();
		}
		HBlank();
	}

//        DXClose();
}

void HBlank()
{
        ScanLine++;
        if (FakeSLUsing) ScanLineFake++; else ScanLineFake = ScanLine;

        ClockticksSm = LineTicksInt;

	if (Mem.MapperNum == 4)
	{
		if ((!VBlanking) && (BGVis))
			MMC3.IRQCounter--;
		if (MMC3.IRQCounter == 0)
		{
			if (MMC3.IRQEnable) irq6502();
			MMC3.IRQCounter = 0xFF;
		}
        } else if (Mem.MapperNum == 16) {
                if (M16.IRQEnabled)
                {
                        M16.IRQCounter--;
						if (M16.IRQCounter == 0) irq6502();
                }
		} else if (Mem.MapperNum == 17) {
                if (M17.IRQEnabled)
                {
                        M17.IRQCounter++;
                        if (M17.IRQCounter == 0xFFFF) { irq6502(); }
                }
        } else if (Mem.MapperNum == 24) {
                if (M24.IRQEnable)
                {
                        M24.IRQCounter++;
                        if (M24.IRQCounter == 0xFF)
                        {
//                                dprinto(AnsiString("IRQ Hit: ") + AnsiString(ScanLine));
                                irq6502();
//                                M24.IRQCounter = 0;
//                                M24.IRQEnable = false;
                        }
                }
	} else if (Mem.MapperNum == 90) {
		if (M90.SLEnabled)
		{
			M90.CounterVal--;
			if (M90.CounterVal == 0)
			{
				irq6502();
//                                tprinto("IRQ from timer");
				M90.SLEnabled = false;
			}
		}
	}

	if (ScanLine == MaxScanLine)
	{
                Spr0Occ = false; VBlanking = false; ScanLine = 0;
		if (SavingState)
			{ SavingState = false; SaveState(); }

                PrepTileline();
	}

        if ((!VBlanking) && (ScanLine < 240))
        {
                DrawScanline();

                unsigned char SSizeNew = (BYTE) ((SSize << 3) + 1);

                if ((!Spr0Occ) && (Mem.Sprite[0] + 1 <= ScanLine) && (Mem.Sprite[0] + 9 + SSizeNew > ScanLine))
                {
                        bool hflip = bit6(Mem.Sprite[2]);
                        unsigned char ydiff = (BYTE) (ScanLine - (Mem.Sprite[0] + 1));
                        short int addr = (short int) ((Mem.Sprite[1] - SSize + bit3(ydiff)) << 4);
                        if (bit7(Mem.Sprite[2])) addr |= (LBYTE) (7 - (ydiff & 7));
                                else addr |= (BYTE) (ydiff & 7);
        
                        for (unsigned char xx=0;xx<8;xx++)
                        {
                                unsigned char col = (BYTE) (((bool) (Mem.PatternTable[SpPTA][addr | 8] & bitnumsp[hflip][xx]) << 1) | (bool) (Mem.PatternTable[SpPTA][addr] & bitnumsp[hflip][xx]));
                                if (col)
								{  //sprite pixel is drawn, check bg pixel
/*
                unsigned char TileX = Mem.Sprite[2] >> 3;
		short int SLTmp = (short int) (ScanLineFake + Mem.BgScrollY);
                unsigned char TileY = (BYTE) (SLTmp >> 3);
                unsigned char NTY = (BYTE) (((bool) (TileY >= 30) ^ (bool) (NTabAdr & 0x800)) << 1);
                unsigned char TileYM30 = (BYTE) (TileY % 30);
		unsigned char TileYDiff = (BYTE) (SLTmp & 7);

		bool NTabAdrBl = (bool) (NTabAdr & 0x400);
		unsigned char SLHead = (BYTE) (Mem.BgScrollX & 0xF8);

				short int NameTable = (LBYTE) (((NTY | (bit5(TileX) ^ NTabAdrBl)) << 10) | 0x2000);
				addr = (short int) ((*Mem.PPU[NameTable | (TileYM30 << 5) | (TileX & 0x1F)] << 4) | TileYDiff);

                                unsigned char bitnum = bitnumsp[0][(Mem.Sprite[2]+xx) & 7];

#ifdef newchr
                                col = (BYTE) (((bool) (*Mem.PPU[(BkPTA << 12) | addr | 8] & bitnum) << 1) | (bool) (*Mem.PPU[(BkPTA << 12) | addr] & bitnum));
#else
								col = (BYTE) (((bool) (Mem.PatternTable[BkPTA][addr | 8] & bitnum) << 1) | (bool) (Mem.PatternTable[BkPTA][addr] & bitnum));
#endif

                                        if (col)
*/
                                                Spr0Occ = true;
                                }
                        }
                }
        }

	if (ScanLine == VBScanLine)
	{
                Application->ProcessMessages();

		if (FakeSLUsing) FakeSLUsing = false;

		for (int i=0;i<2;i++)
		{
/*			if (PulseChan[i].Enabled)
			{
				if (PulseChan[i].LengthLeft > 0)
				{
					if ((PulseChan[i].VolFade == 0) && (PulseChan[i].Volume > 0))  PulseChan[i].Volume-=PulseChan[i].FadeSpeed;
					if ((PulseChan[i].VolFade == 1) && (PulseChan[i].Volume < 15)) PulseChan[i].Volume+=PulseChan[i].FadeSpeed;
					SNDChannels[i].bVol = PulseChan[i].Volume;
					PulseChan[i].LengthLeft--;
				} else if (PulseChan[i].Loop) {
					if ((PulseChan[i].VolFade == 0) && (PulseChan[i].Volume > 0))  PulseChan[i].Volume-=PulseChan[i].FadeSpeed;
					if ((PulseChan[i].VolFade == 1) && (PulseChan[i].Volume < 15)) PulseChan[i].Volume+=PulseChan[i].FadeSpeed;
					SNDChannels[i].bVol = PulseChan[i].Volume;
				} else { SNDChannels[i].bVol = 0; }
			} else { SNDChannels[i].bVol = 0; }*/
		}
//		if (DCMChan.Enabled)
//		{
//			if (DCMChan.BitPointer > (DCMChan.BitLength >> 3))
//			{
//				if (DCMChan.Loop)
//				{
//					SNDChannels[4].bVol = DCMChan.Volume;
//					DCMChan.BitPointer = 0;
//				} else {
//					SNDChannels[4].bVol = 0;
//					if (DCMChan.IRQGen) irq6502();
// 				}
//			} else {
//				SNDChannels[4].bVol = DCMChan.Volume;
//			}
//		} else { SNDChannels[4].bVol = 0; }

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
		FinishTileline();
//		DXRender();
		
		if (NMIonVBlank) nmi6502();
		VBlanking = true;
		VBlankOcc = true;
	}
}

void __fastcall nmi6502()
{
//	tprinto("NMI!");

//	PC++;
        PushPCaP();
	SetI();

//	PC = (LBYTE) (Get16Bit(NMIVector));
	PC = (LBYTE) ((Mem.PRGPage[Mem.PRGPageNum[3]][0x1FFB] << 8) | Mem.PRGPage[Mem.PRGPageNum[3]][0x1FFA]);

	if (HaltOnNMI)
	{
//                tprinto("NMI!  Halting!");
		DebuggingTrace = true;
		DebuggingRegs = true;
		CPURunning = false;
	}
}

void __fastcall irq6502()
{
//	tprinto("IRQ!");

	if (CCRI) return;

//	CPURunning = false; tprinto("IRQ");
//	PC++;
        PushPCaP();
	SetI();

	PC = (LBYTE) ((Mem.PRGPage[Mem.PRGPageNum[3]][0x1FFF] << 8) | Mem.PRGPage[Mem.PRGPageNum[3]][0x1FFE]);
//	PC = (LBYTE) (Get16Bit(IRQVector));
}

void HardBoot()
{
	for (int i=0;i<8;i++) Mem.CHRPageNum[i] = 99;
	for (int i=0;i<8;i++) Mem.CHRPageNumNew[i] = 99;
	for (int i=0;i<4;i++) Mem.PRGPageNum[i] = 99;

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
				Mem.PRGPageNum[0] = 0; Mem.PRGPageNum[1] = 1;
				Mem.PRGPageNum[2] = 14; Mem.PRGPageNum[3] = 15;
//                                tprinto("22in1(C): Contra Mode");
			} else {
				Mem.PRGPageNum[0] = 16; Mem.PRGPageNum[1] = 17;
				Mem.PRGPageNum[2] = 78; Mem.PRGPageNum[3] = 79;
//                                tprinto("22in1(2): 22in1 Mode");
			}
			break;
	};

//	for (int i=0x0000;i<0x6000;i++)
	for (int i=0x0000;i<0x4000;i++)
		*Mem.Main[i] = 0x00;
	for (int i=0x2000;i<0x4000;i++)
		*Mem.PPU[i] = 0x00;
	setmem(&Mem.Sprite[0x00], 0x100, 0x00);
	SP = 0xFF;
	P = 0x20;
	A = 0; X = 0; Y = 0;

	Mem.BgScrollX = 0; Mem.BgScrollY = 0;
	Mem.VRAMAddress = 0; Mem.SPRAddress = 0;
	NTabAdr = 0x2000;
	ScanLine = 0;
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

//	Clockticks = 7;
	ClockticksSm = (char) (LineTicksInt - 7);

	Joy.Count[0] = 0; Joy.Count[1] = 0;
	Joy.Strobe[0] = 0; Joy.Strobe[1] = 0;
	setmem(&Joy.Bits[0][0], 48, 0);

/*	PulseChan[0].Enabled = false;
	PulseChan[1].Enabled = false;
	TriChan.Enabled = false;
	NoiseChan.Enabled = false;
	DCMChan.Enabled = false;
	PulseChan[0].Volume = 0;
	PulseChan[1].Volume = 0;
	PulseChan[0].LengthLeft = 0;
	PulseChan[1].LengthLeft = 0;
	PulseChan[0].Loop = false;
	PulseChan[1].Loop = false;*/

	reset6502();
}

void __fastcall reset6502()
{
	bool DontSwapVRAM = false, DontSwapPRG = false;

	switch (Mem.MapperNum) {
		case 0 :
			Mem.PRGPageNum[0] = 0; Mem.PRGPageNum[1] = 1;
			Mem.PRGPageNum[2] = (BYTE) (Mem.PRGPagesA - 2); Mem.PRGPageNum[3] = (BYTE) (Mem.PRGPagesA - 1);

			Mem.CHRPageNumNew[0] = 0; Mem.CHRPageNumNew[1] = 1; Mem.CHRPageNumNew[2] = 2;
			Mem.CHRPageNumNew[3] = 3; Mem.CHRPageNumNew[4] = 4; Mem.CHRPageNumNew[5] = 5;
			Mem.CHRPageNumNew[6] = 6; Mem.CHRPageNumNew[7] = 7;
			break;
		case 1 :
			Mem.PRGPageNum[0] = 0; Mem.PRGPageNum[1] = 1;
			Mem.PRGPageNum[2] = (BYTE) (Mem.PRGPagesA - 2); Mem.PRGPageNum[3] = (BYTE) (Mem.PRGPagesA - 1);

			Mem.CHRPageNumNew[0] = 0; Mem.CHRPageNumNew[1] = 1; Mem.CHRPageNumNew[2] = 2;
			Mem.CHRPageNumNew[3] = 3; Mem.CHRPageNumNew[4] = 4; Mem.CHRPageNumNew[5] = 5;
			Mem.CHRPageNumNew[6] = 6; Mem.CHRPageNumNew[7] = 7;
			break;
		case 2 :
			Mem.PRGPageNum[0] = 0; Mem.PRGPageNum[1] = 1;
			Mem.PRGPageNum[2] = (BYTE) (Mem.PRGPagesA - 2); Mem.PRGPageNum[3] = (BYTE) (Mem.PRGPagesA - 1);

			Mem.CHRPageNumNew[0] = 0; Mem.CHRPageNumNew[1] = 1; Mem.CHRPageNumNew[2] = 2;
			Mem.CHRPageNumNew[3] = 3; Mem.CHRPageNumNew[4] = 4; Mem.CHRPageNumNew[5] = 5;
			Mem.CHRPageNumNew[6] = 6; Mem.CHRPageNumNew[7] = 7;
			break;
		case 3 :
			Mem.PRGPageNum[0] = 0; Mem.PRGPageNum[1] = 1;
			Mem.PRGPageNum[2] = (BYTE) (Mem.PRGPagesA - 2); Mem.PRGPageNum[3] = (BYTE) (Mem.PRGPagesA - 1);

			Mem.CHRPageNumNew[0] = 0; Mem.CHRPageNumNew[1] = 1; Mem.CHRPageNumNew[2] = 2;
			Mem.CHRPageNumNew[3] = 3; Mem.CHRPageNumNew[4] = 4; Mem.CHRPageNumNew[5] = 5;
			Mem.CHRPageNumNew[6] = 6; Mem.CHRPageNumNew[7] = 7;
			break;
		case 4 :
			Mem.PRGPageNum[0] = 0; Mem.PRGPageNum[1] = 1;
			Mem.PRGPageNum[2] = (BYTE) (Mem.PRGPagesA - 2); Mem.PRGPageNum[3] = (BYTE) (Mem.PRGPagesA - 1);

			Mem.CHRPageNumNew[0] = 0; Mem.CHRPageNumNew[1] = 1; Mem.CHRPageNumNew[2] = 2;
			Mem.CHRPageNumNew[3] = 3; Mem.CHRPageNumNew[4] = 4; Mem.CHRPageNumNew[5] = 5;
			Mem.CHRPageNumNew[6] = 6; Mem.CHRPageNumNew[7] = 7;

// vvv Unknown vvv
//			MMC3.IRQCounter = 0xFF;
// ^^^ Unknown ^^^
			break;
		case 5 :
			Mem.PRGPageNum[0] = (BYTE) (Mem.PRGPagesA - 1); Mem.PRGPageNum[1] = Mem.PRGPageNum[0];
			Mem.PRGPageNum[2] = Mem.PRGPageNum[0]; Mem.PRGPageNum[3] = Mem.PRGPageNum[0];

// vvv Unknown vvv
			Mem.CHRPageNumNew[0] = 0; Mem.CHRPageNumNew[1] = 1; Mem.CHRPageNumNew[2] = 2;
			Mem.CHRPageNumNew[3] = 3; Mem.CHRPageNumNew[4] = 4; Mem.CHRPageNumNew[5] = 5;
			Mem.CHRPageNumNew[6] = 6; Mem.CHRPageNumNew[7] = 7;
// ^^^ Unknown ^^^
			break;
		case 6 :
// vvv Unknown vvv
			Mem.PRGPageNum[0] = 0; Mem.PRGPageNum[1] = 1;
			Mem.PRGPageNum[2] = 2; Mem.PRGPageNum[3] = 3;

			Mem.CHRPageNumNew[0] = 0; Mem.CHRPageNumNew[1] = 1; Mem.CHRPageNumNew[2] = 2;
			Mem.CHRPageNumNew[3] = 3; Mem.CHRPageNumNew[4] = 4; Mem.CHRPageNumNew[5] = 5;
			Mem.CHRPageNumNew[6] = 6; Mem.CHRPageNumNew[7] = 7;
// ^^^ Unknown ^^^
			break;
		case 7 :
			Mem.PRGPageNum[0] = 0; Mem.PRGPageNum[1] = 1;
			Mem.PRGPageNum[2] = 2; Mem.PRGPageNum[3] = 3;

			Mem.CHRPageNumNew[0] = 0; Mem.CHRPageNumNew[1] = 1; Mem.CHRPageNumNew[2] = 2;
			Mem.CHRPageNumNew[3] = 3; Mem.CHRPageNumNew[4] = 4; Mem.CHRPageNumNew[5] = 5;
			Mem.CHRPageNumNew[6] = 6; Mem.CHRPageNumNew[7] = 7;
			break;
		case 8 :
			Mem.PRGPageNum[0] = 0; Mem.PRGPageNum[1] = 1;
			Mem.PRGPageNum[2] = 2; Mem.PRGPageNum[3] = 3;

			Mem.CHRPageNumNew[0] = 0; Mem.CHRPageNumNew[1] = 1; Mem.CHRPageNumNew[2] = 2;
			Mem.CHRPageNumNew[3] = 3; Mem.CHRPageNumNew[4] = 4; Mem.CHRPageNumNew[5] = 5;
			Mem.CHRPageNumNew[6] = 6; Mem.CHRPageNumNew[7] = 7;
			break;
		case 9 :
			Mem.PRGPageNum[0] = 0; Mem.PRGPageNum[1] = (BYTE) (Mem.PRGPagesA - 3);
			Mem.PRGPageNum[2] = (BYTE) (Mem.PRGPagesA - 2); Mem.PRGPageNum[3] = (BYTE) (Mem.PRGPagesA - 1);

// vvv Unknown vvv
			Mem.CHRPageNumNew[0] = 0; Mem.CHRPageNumNew[1] = 1; Mem.CHRPageNumNew[2] = 2;
			Mem.CHRPageNumNew[3] = 3; Mem.CHRPageNumNew[4] = 4; Mem.CHRPageNumNew[5] = 5;
			Mem.CHRPageNumNew[6] = 6; Mem.CHRPageNumNew[7] = 7;
// ^^^ Unknown ^^^
//                        MMC4.Latch[0] = 0xFE;
//                        MMC4.Latch[1] = 0xFE;
			break;
		case 10 :
			Mem.PRGPageNum[0] = 0; Mem.PRGPageNum[1] = 1;
			Mem.PRGPageNum[2] = (BYTE) (Mem.PRGPagesA - 2); Mem.PRGPageNum[3] = (BYTE) (Mem.PRGPagesA - 1);

// vvv Unknown vvv
			Mem.CHRPageNumNew[0] = 0; Mem.CHRPageNumNew[1] = 1; Mem.CHRPageNumNew[2] = 2;
			Mem.CHRPageNumNew[3] = 3; Mem.CHRPageNumNew[4] = 4; Mem.CHRPageNumNew[5] = 5;
			Mem.CHRPageNumNew[6] = 6; Mem.CHRPageNumNew[7] = 7;
// ^^^ Unknown ^^^
//                        MMC4.Latch[0] = 0xFE;
//                        MMC4.Latch[1] = 0xFE;
			break;
		case 11 :
			Mem.PRGPageNum[0] = 0; Mem.PRGPageNum[1] = 1;
			Mem.PRGPageNum[2] = 2; Mem.PRGPageNum[3] = 3;

			Mem.CHRPageNumNew[0] = 0; Mem.CHRPageNumNew[1] = 1; Mem.CHRPageNumNew[2] = 2;
			Mem.CHRPageNumNew[3] = 3; Mem.CHRPageNumNew[4] = 4; Mem.CHRPageNumNew[5] = 5;
			Mem.CHRPageNumNew[6] = 6; Mem.CHRPageNumNew[7] = 7;
			break;
                case 13 :
			Mem.PRGPageNum[0] = 0; Mem.PRGPageNum[1] = 1;
			Mem.PRGPageNum[2] = 2; Mem.PRGPageNum[3] = 3;

			Mem.CHRPageNumNew[0] = 0; Mem.CHRPageNumNew[1] = 1; Mem.CHRPageNumNew[2] = 2;
			Mem.CHRPageNumNew[3] = 3; Mem.CHRPageNumNew[4] = 4; Mem.CHRPageNumNew[5] = 5;
			Mem.CHRPageNumNew[6] = 6; Mem.CHRPageNumNew[7] = 7;
                        break;
		case 15 :
			Mem.PRGPageNum[0] = 0; Mem.PRGPageNum[1] = 1;
			Mem.PRGPageNum[2] = 2; Mem.PRGPageNum[3] = 3;

			Mem.CHRPageNumNew[0] = 0; Mem.CHRPageNumNew[1] = 1; Mem.CHRPageNumNew[2] = 2;
			Mem.CHRPageNumNew[3] = 3; Mem.CHRPageNumNew[4] = 4; Mem.CHRPageNumNew[5] = 5;
			Mem.CHRPageNumNew[6] = 6; Mem.CHRPageNumNew[7] = 7;
			break;
		case 16 :
			Mem.PRGPageNum[0] = 0; Mem.PRGPageNum[1] = 1;
			Mem.PRGPageNum[2] = (BYTE) (Mem.PRGPagesA - 2); Mem.PRGPageNum[3] = (BYTE) (Mem.PRGPagesA - 1);

			Mem.CHRPageNumNew[0] = 0; Mem.CHRPageNumNew[1] = 1; Mem.CHRPageNumNew[2] = 2;
			Mem.CHRPageNumNew[3] = 3; Mem.CHRPageNumNew[4] = 4; Mem.CHRPageNumNew[5] = 5;
			Mem.CHRPageNumNew[6] = 6; Mem.CHRPageNumNew[7] = 7;

			DontSwapVRAM = true;
			break;
		case 17 :
			Mem.PRGPageNum[0] = 0; Mem.PRGPageNum[1] = 1;
			Mem.PRGPageNum[2] = (BYTE) (Mem.PRGPagesA - 2); Mem.PRGPageNum[3] = (BYTE) (Mem.PRGPagesA - 1);

			Mem.CHRPageNumNew[0] = 0; Mem.CHRPageNumNew[1] = 1; Mem.CHRPageNumNew[2] = 2;
			Mem.CHRPageNumNew[3] = 3; Mem.CHRPageNumNew[4] = 4; Mem.CHRPageNumNew[5] = 5;
			Mem.CHRPageNumNew[6] = 6; Mem.CHRPageNumNew[7] = 7;

			DontSwapVRAM = true;
			break;
		case 18 :
			Mem.PRGPageNum[0] = 0; Mem.PRGPageNum[1] = 1;
			Mem.PRGPageNum[2] = (BYTE) (Mem.PRGPagesA - 2); Mem.PRGPageNum[3] = (BYTE) (Mem.PRGPagesA - 1);

			Mem.CHRPageNumNew[0] = 0; Mem.CHRPageNumNew[1] = 1; Mem.CHRPageNumNew[2] = 2;
			Mem.CHRPageNumNew[3] = 3; Mem.CHRPageNumNew[4] = 4; Mem.CHRPageNumNew[5] = 5;
			Mem.CHRPageNumNew[6] = 6; Mem.CHRPageNumNew[7] = 7;

			DontSwapVRAM = true;
			break;
		case 19 :
			Mem.PRGPageNum[0] = 0; Mem.PRGPageNum[1] = 1;
			Mem.PRGPageNum[2] = (BYTE) (Mem.PRGPagesA - 2); Mem.PRGPageNum[3] = (BYTE) (Mem.PRGPagesA - 1);

			Mem.CHRPageNumNew[0] = (BYTE) (Mem.PRGPagesA - 8); Mem.CHRPageNumNew[1] = (BYTE) (Mem.CHRPageNumNew[0] + 1); Mem.CHRPageNumNew[2] = (BYTE) (Mem.CHRPageNumNew[0] + 2);
			Mem.CHRPageNumNew[3] = (BYTE) (Mem.CHRPageNumNew[0] + 3); Mem.CHRPageNumNew[4] = (BYTE) (Mem.CHRPageNumNew[0] + 4); Mem.CHRPageNumNew[5] = (BYTE) (Mem.CHRPageNumNew[0] + 5);
			Mem.CHRPageNumNew[6] = (BYTE) (Mem.CHRPageNumNew[0] + 6); Mem.CHRPageNumNew[7] = (BYTE) (Mem.CHRPageNumNew[0] + 7);
			break;
		case 21 :
			Mem.PRGPageNum[0] = 0; Mem.PRGPageNum[1] = 1;
			Mem.PRGPageNum[2] = (BYTE) (Mem.PRGPagesA - 2); Mem.PRGPageNum[3] = (BYTE) (Mem.PRGPagesA - 1);

			Mem.CHRPageNumNew[0] = 0; Mem.CHRPageNumNew[1] = 1; Mem.CHRPageNumNew[2] = 2;
			Mem.CHRPageNumNew[3] = 3; Mem.CHRPageNumNew[4] = 4; Mem.CHRPageNumNew[5] = 5;
			Mem.CHRPageNumNew[6] = 6; Mem.CHRPageNumNew[7] = 7;

			DontSwapVRAM = true;
			break;
		case 22 :
			Mem.PRGPageNum[0] = 0; Mem.PRGPageNum[1] = 1;
			Mem.PRGPageNum[2] = (BYTE) (Mem.PRGPagesA - 2); Mem.PRGPageNum[3] = (BYTE) (Mem.PRGPagesA - 1);

			Mem.CHRPageNumNew[0] = 0; Mem.CHRPageNumNew[1] = 1; Mem.CHRPageNumNew[2] = 2;
			Mem.CHRPageNumNew[3] = 3; Mem.CHRPageNumNew[4] = 4; Mem.CHRPageNumNew[5] = 5;
			Mem.CHRPageNumNew[6] = 6; Mem.CHRPageNumNew[7] = 7;
			break;
		case 23 :
			Mem.PRGPageNum[0] = 0; Mem.PRGPageNum[1] = 1;
			Mem.PRGPageNum[2] = (BYTE) (Mem.PRGPagesA - 2); Mem.PRGPageNum[3] = (BYTE) (Mem.PRGPagesA - 1);

			Mem.CHRPageNumNew[0] = 0; Mem.CHRPageNumNew[1] = 1; Mem.CHRPageNumNew[2] = 2;
			Mem.CHRPageNumNew[3] = 3; Mem.CHRPageNumNew[4] = 4; Mem.CHRPageNumNew[5] = 5;
			Mem.CHRPageNumNew[6] = 6; Mem.CHRPageNumNew[7] = 7;

			DontSwapVRAM = true;
			break;
		case 24 :
			Mem.PRGPageNum[0] = 0; Mem.PRGPageNum[1] = 1;
			Mem.PRGPageNum[2] = (BYTE) (Mem.PRGPagesA - 2); Mem.PRGPageNum[3] = (BYTE) (Mem.PRGPagesA - 1);

//			Mem.CHRPageNumNew[0] = 0; Mem.CHRPageNumNew[1] = 1; Mem.CHRPageNumNew[2] = 2;
//			Mem.CHRPageNumNew[3] = 3; Mem.CHRPageNumNew[4] = 4; Mem.CHRPageNumNew[5] = 5;
//			Mem.CHRPageNumNew[6] = 6; Mem.CHRPageNumNew[7] = 7;
			DontSwapVRAM = true;
			break;
		case 32 :
			Mem.PRGPageNum[0] = 0; Mem.PRGPageNum[1] = 1;
			Mem.PRGPageNum[2] = (BYTE) (Mem.PRGPagesA - 2); Mem.PRGPageNum[3] = (BYTE) (Mem.PRGPagesA - 1);

			Mem.CHRPageNumNew[0] = 0; Mem.CHRPageNumNew[1] = 1; Mem.CHRPageNumNew[2] = 2;
			Mem.CHRPageNumNew[3] = 3; Mem.CHRPageNumNew[4] = 4; Mem.CHRPageNumNew[5] = 5;
			Mem.CHRPageNumNew[6] = 6; Mem.CHRPageNumNew[7] = 7;

			DontSwapVRAM = true;
			break;
		case 33 :
			Mem.PRGPageNum[0] = 0; Mem.PRGPageNum[1] = 1;
			Mem.PRGPageNum[2] = (BYTE) (Mem.PRGPagesA - 2); Mem.PRGPageNum[3] = (BYTE) (Mem.PRGPagesA - 1);

			Mem.CHRPageNumNew[0] = 0; Mem.CHRPageNumNew[1] = 1; Mem.CHRPageNumNew[2] = 2;
			Mem.CHRPageNumNew[3] = 3; Mem.CHRPageNumNew[4] = 4; Mem.CHRPageNumNew[5] = 5;
			Mem.CHRPageNumNew[6] = 6; Mem.CHRPageNumNew[7] = 7;

			DontSwapVRAM = true;
			break;
		case 34 :
			Mem.PRGPageNum[0] = 0; Mem.PRGPageNum[1] = 1;
			Mem.PRGPageNum[2] = 2; Mem.PRGPageNum[3] = 3;

			Mem.CHRPageNumNew[0] = 0; Mem.CHRPageNumNew[1] = 1; Mem.CHRPageNumNew[2] = 2;
			Mem.CHRPageNumNew[3] = 3; Mem.CHRPageNumNew[4] = 4; Mem.CHRPageNumNew[5] = 5;
			Mem.CHRPageNumNew[6] = 6; Mem.CHRPageNumNew[7] = 7;
			break;
		case 64 :
			Mem.PRGPageNum[0] = (BYTE) (Mem.PRGPagesA - 1); Mem.PRGPageNum[0];
			Mem.PRGPageNum[2] = Mem.PRGPageNum[0]; Mem.PRGPageNum[3] = Mem.PRGPageNum[0];

			Mem.CHRPageNumNew[0] = 0; Mem.CHRPageNumNew[1] = 1; Mem.CHRPageNumNew[2] = 2;
			Mem.CHRPageNumNew[3] = 3; Mem.CHRPageNumNew[4] = 4; Mem.CHRPageNumNew[5] = 5;
			Mem.CHRPageNumNew[6] = 6; Mem.CHRPageNumNew[7] = 7;
			break;
		case 65 :
			Mem.PRGPageNum[0] = 0; Mem.PRGPageNum[1] = 1;
			Mem.PRGPageNum[2] = (BYTE) (Mem.PRGPagesA - 2); Mem.PRGPageNum[3] = (BYTE) (Mem.PRGPagesA - 1);

			Mem.CHRPageNumNew[0] = 0; Mem.CHRPageNumNew[1] = 1; Mem.CHRPageNumNew[2] = 2;
			Mem.CHRPageNumNew[3] = 3; Mem.CHRPageNumNew[4] = 4; Mem.CHRPageNumNew[5] = 5;
			Mem.CHRPageNumNew[6] = 6; Mem.CHRPageNumNew[7] = 7;

			DontSwapVRAM = true;
			break;
		case 66 :
			Mem.PRGPageNum[0] = 0; Mem.PRGPageNum[1] = 1;
			Mem.PRGPageNum[2] = 2; Mem.PRGPageNum[3] = 3;

			Mem.CHRPageNumNew[0] = 0; Mem.CHRPageNumNew[1] = 1; Mem.CHRPageNumNew[2] = 2;
			Mem.CHRPageNumNew[3] = 3; Mem.CHRPageNumNew[4] = 4; Mem.CHRPageNumNew[5] = 5;
			Mem.CHRPageNumNew[6] = 6; Mem.CHRPageNumNew[7] = 7;
			break;
		case 68 :
			Mem.PRGPageNum[0] = 0; Mem.PRGPageNum[1] = 1;
			Mem.PRGPageNum[2] = (BYTE) (Mem.PRGPagesA - 2); Mem.PRGPageNum[3] = (BYTE) (Mem.PRGPagesA - 1);

// vvv Unknown vvv
			Mem.CHRPageNumNew[0] = 0; Mem.CHRPageNumNew[1] = 1; Mem.CHRPageNumNew[2] = 2;
			Mem.CHRPageNumNew[3] = 3; Mem.CHRPageNumNew[4] = 4; Mem.CHRPageNumNew[5] = 5;
			Mem.CHRPageNumNew[6] = 6; Mem.CHRPageNumNew[7] = 7;
// ^^^ Unknown ^^^
			break;
		case 69 :
// vvv Unknown vvv
			Mem.PRGPageNum[0] = 0; Mem.PRGPageNum[1] = 1;
			Mem.PRGPageNum[2] = 2;
// ^^^ Unknown ^^^
			Mem.PRGPageNum[3] = (BYTE) (Mem.PRGPagesA - 1);

// vvv Unknown vvv
			Mem.CHRPageNumNew[0] = 0; Mem.CHRPageNumNew[1] = 1; Mem.CHRPageNumNew[2] = 2;
			Mem.CHRPageNumNew[3] = 3; Mem.CHRPageNumNew[4] = 4; Mem.CHRPageNumNew[5] = 5;
			Mem.CHRPageNumNew[6] = 6; Mem.CHRPageNumNew[7] = 7;
// ^^^ Unknown ^^^
			break;
		case 71 :
			Mem.PRGPageNum[0] = 0; Mem.PRGPageNum[1] = 1;
			Mem.PRGPageNum[2] = (BYTE) (Mem.PRGPagesA - 2); Mem.PRGPageNum[3] = (BYTE) (Mem.PRGPagesA - 1);

			Mem.CHRPageNumNew[0] = 0; Mem.CHRPageNumNew[1] = 1; Mem.CHRPageNumNew[2] = 2;
			Mem.CHRPageNumNew[3] = 3; Mem.CHRPageNumNew[4] = 4; Mem.CHRPageNumNew[5] = 5;
			Mem.CHRPageNumNew[6] = 6; Mem.CHRPageNumNew[7] = 7;
			break;
		case 78 :
			Mem.PRGPageNum[0] = 0; Mem.PRGPageNum[1] = 1;
			Mem.PRGPageNum[2] = (BYTE) (Mem.PRGPagesA - 2); Mem.PRGPageNum[3] = (BYTE) (Mem.PRGPagesA - 1);

// vvv Possible vvv
			Mem.CHRPageNumNew[0] = 0; Mem.CHRPageNumNew[1] = 1; Mem.CHRPageNumNew[2] = 2;
			Mem.CHRPageNumNew[3] = 3; Mem.CHRPageNumNew[4] = 4; Mem.CHRPageNumNew[5] = 5;
			Mem.CHRPageNumNew[6] = 6; Mem.CHRPageNumNew[7] = 7;
// ^^^ Possible ^^^
			break;
		case 90 :
			Mem.PRGPageNum[0] = 0; Mem.PRGPageNum[1] = 1;
			Mem.PRGPageNum[2] = (BYTE) (Mem.PRGPagesA - 2); Mem.PRGPageNum[3] = (BYTE) (Mem.PRGPagesA - 1);

// vvv Unknown vvv
			Mem.CHRPageNumNew[0] = 0; Mem.CHRPageNumNew[1] = 1; Mem.CHRPageNumNew[2] = 2;
			Mem.CHRPageNumNew[3] = 3; Mem.CHRPageNumNew[4] = 4; Mem.CHRPageNumNew[5] = 5;
			Mem.CHRPageNumNew[6] = 6; Mem.CHRPageNumNew[7] = 7;
// ^^^ Unknown ^^^
			break;
		case 91 :
			Mem.PRGPageNum[0] = (BYTE) (Mem.PRGPagesA - 2); Mem.PRGPageNum[1] = (BYTE) (Mem.PRGPagesA - 1);
			Mem.PRGPageNum[2] = (BYTE) (Mem.PRGPagesA - 2); Mem.PRGPageNum[3] = (BYTE) (Mem.PRGPagesA - 1);

// vvv Unknown vvv
			Mem.CHRPageNumNew[0] = 0; Mem.CHRPageNumNew[1] = 1; Mem.CHRPageNumNew[2] = 2;
			Mem.CHRPageNumNew[3] = 3; Mem.CHRPageNumNew[4] = 4; Mem.CHRPageNumNew[5] = 5;
			Mem.CHRPageNumNew[6] = 6; Mem.CHRPageNumNew[7] = 7;
// ^^^ Unknown ^^^
			break;
		case 99 :
			Mem.PRGPageNum[0] = 0; Mem.PRGPageNum[1] = 1;
			Mem.PRGPageNum[2] = (BYTE) (Mem.PRGPagesA - 2); Mem.PRGPageNum[3] = (BYTE) (Mem.PRGPagesA - 1);

			Mem.CHRPageNumNew[0] = 0; Mem.CHRPageNumNew[1] = 1; Mem.CHRPageNumNew[2] = 2;
			Mem.CHRPageNumNew[3] = 3; Mem.CHRPageNumNew[4] = 4; Mem.CHRPageNumNew[5] = 5;
			Mem.CHRPageNumNew[6] = 6; Mem.CHRPageNumNew[7] = 7;
			break;
		case 230 :
			DontSwapVRAM = true;
			DontSwapPRG = true;
			break;
	};

	if (!DontSwapPRG)
	{
		UpdateGGCodes();
	}
	if (!DontSwapVRAM)
	{
		Mem.UpdateCHRPointers();
	}

	PC = (LBYTE) ((Mem.PRGPage[Mem.PRGPageNum[3]][0x1FFD] << 8) | Mem.PRGPage[Mem.PRGPageNum[3]][0x1FFC]);
//	PC = (LBYTE) (Get16Bit(ResetVector));

	SetI();
	SetD();
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
        if (SpecialAccessR[TU])
        {
                BYTE ToRet;
                switch (TU) {
                        case PPUStat :
                                ToRet = (BYTE) ((VBlankOcc << 7) | (Spr0Occ << 6) | (ScLnSprCnt << 5) | (VRAMWrFlg << 4));
                                VBlankOcc = false;
                                Mem.BgScrollUsing = false;
//                                if (DebuggingTrace) dprint(AnsiString("        RegRead: ") + RegInfoLow[TU & 0xFF] + AnsiString(", ToRet = ") + IntToHex(ToRet,2) + AnsiString(" (") + AnsiString(ToBin(ToRet)) + AnsiString(")"));
                                return(ToRet);
                        case SPRIO :
                                ToRet = Mem.Sprite[Mem.SPRAddress];
                                if (!SFirstRead) Mem.SPRAddress++; else SFirstRead = false;
//                                if (DebuggingTrace) dprint(AnsiString("        RegRead: ") + RegInfoLow[TU & 0xFF] + AnsiString(", ToRet = ") + IntToHex(ToRet,2) + AnsiString(" (") + AnsiString(ToBin(ToRet)) + AnsiString(")"));
                                return(ToRet);
                        case VRAMIO :
                                Mem.VRAMAddress &= 0x3FFF;
//                                ToRet = *Mem.PPU[Mem.VRAMAddress];

                                if (Mem.VRAMAddress < 0x3F00)
                                {
                                        if (!VFirstRead)
                                        {
                                                ToRet = *Mem.PPU[Mem.VRAMAddress];
                                                if (PPUAdrI) Mem.VRAMAddress += (short int) 32; else Mem.VRAMAddress++;
                                                Mem.VRAMBuffer = ToRet;
                                        } else {
                                                ToRet = Mem.VRAMBuffer;
                                                Mem.VRAMBuffer = *Mem.PPU[Mem.VRAMAddress];
                                                VFirstRead = false;
                                        }
                                } else {
                                        ToRet = *Mem.PPU[Mem.VRAMAddress];
                                        if (PPUAdrI) Mem.VRAMAddress += (short int) 32; else Mem.VRAMAddress++;
                                }
//                                if (DebuggingTrace) dprint(AnsiString("        RegRead: ") + RegInfoLow[TU & 0xFF] + AnsiString(", ToRet = ") + IntToHex(ToRet,2) + AnsiString(" (") + AnsiString(ToBin(ToRet)) + AnsiString(")"));
                                return(ToRet);
                        case pAPUStCh :
/*                                if (PulseChan[0].LengthLeft) ToRet |= 0x01;
                                if (PulseChan[1].LengthLeft) ToRet |= 0x02;
                                if (TriChan.Enabled) ToRet |= 0x04;
                                if (NoiseChan.Enabled) ToRet |= 0x08;
                                if (DCMChan.Enabled) ToRet |= 0x10;*/
//                                if (DebuggingTrace) dprint(AnsiString("        RegRead: ") + RegInfoHigh[TU & 0xFF] + AnsiString(", ToRet = ") + IntToHex(ToRet,2) + AnsiString(" (") + AnsiString(ToBin(ToRet)) + AnsiString(")"));
                                return(ToRet);
                        case Joypad1 :
                                ToRet = Joy.Get(0);
//                                if (DebuggingTrace) dprint(AnsiString("        RegRead: ") + RegInfoHigh[TU & 0xFF] + AnsiString(", ToRet = ") + IntToHex(ToRet,2) + AnsiString(" (") + AnsiString(ToBin(ToRet)) + AnsiString(")"));
                                return(ToRet);
                        case Joypad2 :
                                ToRet = Joy.Get(1);
//                                if (DebuggingTrace) dprint(AnsiString("        RegRead: ") + RegInfoHigh[TU & 0xFF] + AnsiString(", ToRet = ") + IntToHex(ToRet,2) + AnsiString(" (") + AnsiString(ToBin(ToRet)) + AnsiString(")"));
                                return(ToRet);
                        default :
                                if (Mem.SRAMEnabled)
                                {
//                                        tprint(AnsiString("SRAM Read (E): ") + IntToHex(TU & 0x1FFF,4) + AnsiString(" - ") + IntToHex(*Mem.Main[TU],2));
                                        return(*Mem.Main[TU]);
                                } else {
//                                        tprint(AnsiString("SRAM Read (D): ") + IntToHex(TU & 0x1FFF,4));
                                        return(0);
                                }
                };
        } else {
                if (TU & 0x8000) {
                        return(Mem.PRGPage[Mem.PRGPageNum[(TU & 0x6000) >> 13]][TU & 0x1FFF]);
                } else {
                        return(*Mem.Main[TU]);
                }
        }
}

void __fastcall MemoryTUEquals(BYTE ta)
{
        if (SpecialAccessW[TU])
        {
                switch (TU) {
                        case PPUCtrl1 :
                                NMIonVBlank = ta & 0x80;
                                SSize = ta & 0x20;
                                BkPTA = ta & 0x10;
                                SpPTA = ta & 0x08;
                                PPUAdrI = ta & 0x04;
                                NTabAdr = (short int) (0x2000 | (((ta & 0x02) + bit0(ta)) << 10));
//                                if (DebuggingTrace) dprint(AnsiString("        RegWrite: ") + RegInfoLow[TU & 0xFF] + AnsiString(": ") + IntToHex(ta,2) + AnsiString(" (") + AnsiString(ToBin(ta)) + AnsiString(")"));
                                return;
                        case PPUCtrl2 :
                                SprVis = ta & 0x10;
                                BGVis = ta & 0x08;
                                SprClip = ta & 0x04;
                                BGClip = ta & 0x02;
                                DispType = ta & 0x01;
//                                if (DebuggingTrace) dprint(AnsiString("        RegWrite: ") + RegInfoLow[TU & 0xFF] + AnsiString(": ") + IntToHex(ta,2) + AnsiString(" (") + AnsiString(ToBin(ta)) + AnsiString(")"));
                                return;
                        case SPRAddr :
                                Mem.SPRAddress = ta;
                                SFirstRead = true;
//                                tprint(AnsiString("SPRAddress = ") + IntToHex(Mem.SPRAddress,2));
//                                if (DebuggingTrace) dprint(AnsiString("        RegWrite: ") + RegInfoLow[TU & 0xFF] + AnsiString(": ") + IntToHex(ta,2) + AnsiString(" (") + AnsiString(ToBin(ta)) + AnsiString(")"));
                                return;
                        case SPRIO :
                                Mem.Sprite[Mem.SPRAddress] = ta;
//                                tprint(AnsiString("SPRMemory[") + IntToHex(Mem.SPRAddress,2) + AnsiString("] = ") + IntToHex(ta,2));
                                Mem.SPRAddress++;
//                                                                if (DebuggingTrace) dprint(AnsiString("        RegWrite: ") + RegInfoLow[TU & 0xFF] + AnsiString(": ") + IntToHex(ta,2) + AnsiString(" (") + AnsiString(ToBin(ta)) + AnsiString(")"));
                                return;
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
//                                              Mem.BgScrollY = (short int) (240 - Mem.BgScrollY);
//                                                tprint(AnsiString("Negative Y Scroll: ") + AnsiString(ta));
                                        }
//                                        tprint(AnsiString("Scroll(") + IntToHex(Mem.BgScrollX,2) + AnsiString(", ") + IntToHex(Mem.BgScrollY,2) + AnsiString(")"));
                                }
//                                if (DebuggingTrace) dprint(AnsiString("        RegWrite: ") + RegInfoLow[TU & 0xFF] + AnsiString(": ") + IntToHex(ta,2) + AnsiString(" (") + AnsiString(ToBin(ta)) + AnsiString(")"));
                                return;
                        case VRAMAddr :
                                if (!Mem.VRAMAddrUsing) {
                                        Mem.VRAMAddrUsing = true;
                                        Mem.VRAMAddrHigh = (BYTE) (ta & 0x3F);
                                } else {
                                        Mem.VRAMAddrUsing = false;
                                        Mem.VRAMAddress = (short int) (((Mem.VRAMAddrHigh << 8) | ta));
                                        VFirstRead = true;
//                                      tprint(AnsiString("VRAMAddress = ") + IntToHex(Mem.VRAMAddress,4));

                                        if (ScanLine < 240) {
//                                                tprint(AnsiString("Mid-Frame VRAM Write: Scanline: ") + AnsiString(ScanLine) + AnsiString(", Val = ") + IntToHex(MHBValue,4) + AnsiString(" (") + ToBin((BYTE) ((MHBValue & 0xFF00) >> 8)) + ToBin((BYTE) (MHBValue & 0xFF)) + AnsiString(")"));
                                                NTabAdr = (short int) ((Mem.VRAMAddress & 0x0C00) | 0x2000);
                                                ScanLineFake = (short int) (((Mem.VRAMAddress & 0x03E0) >> 2) | ((Mem.VRAMAddress & 0x3000) >> 12));

                                                Mem.BgScrollX = (unsigned char) ((Mem.VRAMAddress & 0x1F) << 3);
                                                Mem.BgScrollY = 0;
                                                FakeSLUsing = true;
                                        }
                                }
//                                if (DebuggingTrace) dprint(AnsiString("        RegWrite: ") + RegInfoLow[TU & 0xFF] + AnsiString(": ") + IntToHex(ta,2) + AnsiString(" (") + AnsiString(ToBin(ta)) + AnsiString(")"));
                                return;
                        case VRAMIO :
//                                tprint(AnsiString("VRAM[") + IntToHex(Mem.VRAMAddress & 0x3FFF,4) + AnsiString("] = ") + IntToHex(ta,2));
                                *Mem.PPU[Mem.VRAMAddress & 0x3FFF] = ta;
                                if (PPUAdrI) Mem.VRAMAddress += (short int) 32; else Mem.VRAMAddress++;
//                                if (DebuggingTrace) dprint(AnsiString("        RegWrite: ") + RegInfoLow[TU & 0xFF] + AnsiString(": ") + IntToHex(ta,2) + AnsiString(" (") + AnsiString(ToBin(ta)) + AnsiString(")"));
                                return;
                        case pAPUP1C1 :
/*                                SNDChannels[0].bWaveDuty = (BYTE) ((ta & 0xC0) >> 6);
                                PulseChan[0].Loop = bit5(ta);

                                if (bit4(ta))
                                {
                                        PulseChan[0].Volume = (BYTE) (ta & 0x0F);
                                        PulseChan[0].VolFade = 2;
								} else {
//                                        tprint(AnsiString("Envelope[1]: ") + ToBinC(ta,0,3));
                                        PulseChan[0].Volume = 12;
//                                      PulseChan[0].Volume = (BYTE) (ta & 0x0F);
//                                      PulseChan[0].FadeSpeed = 1/8;
                                        PulseChan[0].FadeSpeed = 1/(20-(ta & 0x0F));
//                                      PulseChan[0].FadeSpeed = 1/((ta & 0x0F) + 2);
                                        PulseChan[0].VolFade = 0;
                                }*/
//                                if (DebuggingTrace) dprint(AnsiString("        RegWrite: ") + RegInfoHigh[TU & 0xFF] + AnsiString(": ") + IntToHex(ta,2) + AnsiString(" (") + AnsiString(ToBin(ta)) + AnsiString(")"));
                                return;
                        case pAPUP1C2 :
//                                if (DebuggingTrace) dprint(AnsiString("        RegWrite: ") + RegInfoHigh[TU & 0xFF] + AnsiString(": ") + IntToHex(ta,2) + AnsiString(" (") + AnsiString(ToBin(ta)) + AnsiString(")"));
                                return;
                        case pAPUP1F1 :
//                                SNDChannels[0].dwFreq = (LBYTE) ((SNDChannels[0].dwFreq | 0xFF) & (0x700 | ta));
//                                if (DebuggingTrace) dprint(AnsiString("        RegWrite: ") + RegInfoHigh[TU & 0xFF] + AnsiString(": ") + IntToHex(ta,2) + AnsiString(" (") + AnsiString(ToBin(ta)) + AnsiString(")"));
                                return;
                        case pAPUP1F2 :
//                                PulseChan[0].LengthLeft = LengthInfo[(ta & 0xF8) >> 3];
//                                SNDChannels[0].dwFreq = (LBYTE) ((ta & 0x07) << 8) | (LBYTE) (SNDChannels[0].dwFreq & 0xFF);
//                                if (DebuggingTrace) dprint(AnsiString("        RegWrite: ") + RegInfoHigh[TU & 0xFF] + AnsiString(": ") + IntToHex(ta,2) + AnsiString(" (") + AnsiString(ToBin(ta)) + AnsiString(")"));
                                return;
                        case pAPUP2C1 :
/*                                SNDChannels[1].bWaveDuty = (BYTE) ((ta & 0xC0) >> 6);
                                PulseChan[1].Loop = bit5(ta);

                                if (bit4(ta))
                                {
                                        PulseChan[1].Volume = (BYTE) (ta & 0x0F);
                                        PulseChan[1].VolFade = 2;
								} else {
//                                        tprint(AnsiString("Envelope[2]: ") + ToBinC(ta,0,3));
                                        PulseChan[1].Volume = 12;
//                                      PulseChan[1].Volume = (BYTE) (ta & 0x0F);
//                                      PulseChan[1].FadeSpeed = 1/8;
                                        PulseChan[1].FadeSpeed = 1/(20-(ta & 0x0F));
//                                      PulseChan[1].FadeSpeed = 1/((ta & 0x0F) + 2);
                                        PulseChan[1].VolFade = 0;
                                }
//                              SNDChannels[1].bVol = PulseChan[1].Volume;*/
//                                if (DebuggingTrace) dprint(AnsiString("        RegWrite: ") + RegInfoHigh[TU & 0xFF] + AnsiString(": ") + IntToHex(ta,2) + AnsiString(" (") + AnsiString(ToBin(ta)) + AnsiString(")"));
                                return;
                        case pAPUP2C2 :
//                                if (DebuggingTrace) dprint(AnsiString("        RegWrite: ") + RegInfoHigh[TU & 0xFF] + AnsiString(": ") + IntToHex(ta,2) + AnsiString(" (") + AnsiString(ToBin(ta)) + AnsiString(")"));
                                return;
                        case pAPUP2F1 :
//                                SNDChannels[1].dwFreq = (LBYTE) ((SNDChannels[1].dwFreq | 0xFF) & (0x700 | ta));
//                                if (DebuggingTrace) dprint(AnsiString("        RegWrite: ") + RegInfoHigh[TU & 0xFF] + AnsiString(": ") + IntToHex(ta,2) + AnsiString(" (") + AnsiString(ToBin(ta)) + AnsiString(")"));
                                return;
                        case pAPUP2F2 :
  //                              PulseChan[1].LengthLeft = LengthInfo[(ta & 0xF8) >> 3];
//                                SNDChannels[1].dwFreq = (LBYTE) ((ta & 0x07) << 8) | (LBYTE) (SNDChannels[1].dwFreq & 0xFF);
//                                if (DebuggingTrace) dprint(AnsiString("        RegWrite: ") + RegInfoHigh[TU & 0xFF] + AnsiString(": ") + IntToHex(ta,2) + AnsiString(" (") + AnsiString(ToBin(ta)) + AnsiString(")"));
                                return;

                        case pAPUTC1 :
//                              tprinto(AnsiString("Tri C1:") + ToBin(ta));
//                                if (DebuggingTrace) dprint(AnsiString("        RegWrite: ") + RegInfoHigh[TU & 0xFF] + AnsiString(": ") + IntToHex(ta,2) + AnsiString(" (") + AnsiString(ToBin(ta)) + AnsiString(")"));
                                return;
                        case pAPUTC2 :
//                              tprinto(AnsiString("Tri C2:") + ToBin(ta));
//                                                                if (DebuggingTrace) dprint(AnsiString("        RegWrite: ") + RegInfoHigh[TU & 0xFF] + AnsiString(": ") + IntToHex(ta,2) + AnsiString(" (") + AnsiString(ToBin(ta)) + AnsiString(")"));
                                return;
                        case pAPUTF1 :
//                              tprinto(AnsiString("Tri F1:") + ToBin(ta));
//                                if (DebuggingTrace) dprint(AnsiString("        RegWrite: ") + RegInfoHigh[TU & 0xFF] + AnsiString(": ") + IntToHex(ta,2) + AnsiString(" (") + AnsiString(ToBin(ta)) + AnsiString(")"));
                                return;
                        case pAPUTF2 :
//                              tprinto(AnsiString("Tri F2:") + ToBin(ta));
//                                if (DebuggingTrace) dprint(AnsiString("        RegWrite: ") + RegInfoHigh[TU & 0xFF] + AnsiString(": ") + IntToHex(ta,2) + AnsiString(" (") + AnsiString(ToBin(ta)) + AnsiString(")"));
                                return;

                        case pAPUNC1 :
//                              tprinto(AnsiString("Noise C1:") + ToBin(ta));
//                                if (DebuggingTrace) dprint(AnsiString("        RegWrite: ") + RegInfoHigh[TU & 0xFF] + AnsiString(": ") + IntToHex(ta,2) + AnsiString(" (") + AnsiString(ToBin(ta)) + AnsiString(")"));
                                return;
                        case pAPUNC2 :
//                              tprinto(AnsiString("Noise C2:") + ToBin(ta));
//                                if (DebuggingTrace) dprint(AnsiString("        RegWrite: ") + RegInfoHigh[TU & 0xFF] + AnsiString(": ") + IntToHex(ta,2) + AnsiString(" (") + AnsiString(ToBin(ta)) + AnsiString(")"));
                                return;
                        case pAPUNF1 :
//                              tprinto(AnsiString("Noise F1:") + ToBin(ta));
//                                if (DebuggingTrace) dprint(AnsiString("        RegWrite: ") + RegInfoHigh[TU & 0xFF] + AnsiString(": ") + IntToHex(ta,2) + AnsiString(" (") + AnsiString(ToBin(ta)) + AnsiString(")"));
                                return;
                        case pAPUNF2 :
//                              tprinto(AnsiString("Noise F2:") + ToBin(ta));
//                                if (DebuggingTrace) dprint(AnsiString("        RegWrite: ") + RegInfoHigh[TU & 0xFF] + AnsiString(": ") + IntToHex(ta,2) + AnsiString(" (") + AnsiString(ToBin(ta)) + AnsiString(")"));
                                return;

                        case pAPUDMCC :
//                                DCMChan.Loop = bit6(ta);
 //                               DCMChan.IRQGen = bit7(ta);
//								DCMChan.PlaybackRate = PlayDataRate[ta & 0x0F];
//                                if (DebuggingTrace) dprint(AnsiString("        RegWrite: ") + RegInfoHigh[TU & 0xFF] + AnsiString(": ") + IntToHex(ta,2) + AnsiString(" (") + AnsiString(ToBin(ta)) + AnsiString(")"));
                                return;
                        case pAPUDMCV :
//                                DCMChan.Volume = (BYTE) ((ta & 0x7E) >> 1);
//                                DCMChan.DataBusBit = bit0(ta);
//                                if (DebuggingTrace) dprint(AnsiString("        RegWrite: ") + RegInfoHigh[TU & 0xFF] + AnsiString(": ") + IntToHex(ta,2) + AnsiString(" (") + AnsiString(ToBin(ta)) + AnsiString(")"));
                                return;
                        case pAPUDMCA :
//                                DCMChan.Address = (LBYTE) (0xC000 | (ta << 6));
//                                memcpy(&DCMChan.Data[0], &Mem.PRGROMHigh[DCMChan.Address & 0x3FFF], DCMChan.BitLength >> 3);
//                                DCMChan.BitPointer = 0;
//                                if (DebuggingTrace) dprint(AnsiString("        RegWrite: ") + RegInfoHigh[TU & 0xFF] + AnsiString(": ") + IntToHex(ta,2) + AnsiString(" (") + AnsiString(ToBin(ta)) + AnsiString(")"));
                                return;
                        case pAPUDMCDL :
//                                DCMChan.BitLength = (LBYTE) ((ta << 7) | 1);
//                                memcpy(&DCMChan.Data[0], &Mem.PRGROMHigh[DCMChan.Address & 0x3FFF], DCMChan.BitLength >> 3);
//                                DCMChan.BitPointer = 0;
//                                if (DebuggingTrace) dprint(AnsiString("        RegWrite: ") + RegInfoHigh[TU & 0xFF] + AnsiString(": ") + IntToHex(ta,2) + AnsiString(" (") + AnsiString(ToBin(ta)) + AnsiString(")"));
                                return;
                        case SPRDMA :
//                                tprint(AnsiString("SpriteMem = Memory[") + IntToHex(ta,2) + AnsiString("xx]"));

//                              for (tmpLBYTE=(ta << 8);tmpLBYTE<(ta << 8) + 0xFF;tmpLBYTE++)
//                                      Mem.Sprite[tmpLBYTE & 0xFF] = *Mem.Main[tmpLBYTE];

                                memcpy(&Mem.Sprite[0],Mem.Main[ta << 8],0x100);
//                                if (DebuggingTrace) dprint(AnsiString("        RegWrite: ") + RegInfoHigh[TU & 0xFF] + AnsiString(": ") + IntToHex(ta,2) + AnsiString(" (") + AnsiString(ToBin(ta)) + AnsiString(")"));
                                return;
                        case pAPUStCh :
//                                PulseChan[0].Enabled = bit0(ta);
//								PulseChan[1].Enabled = bit1(ta);
 //                               TriChan.Enabled = bit2(ta);
 //                               NoiseChan.Enabled = bit3(ta);
  //                              DCMChan.Enabled = bit4(ta);
//                                if (DebuggingTrace) dprint(AnsiString("        RegWrite: ") + RegInfoHigh[TU & 0xFF] + AnsiString(": ") + IntToHex(ta,2) + AnsiString(" (") + AnsiString(ToBin(ta)) + AnsiString(")"));
                                return;
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
//                                if (DebuggingTrace) dprint(AnsiString("        RegWrite: ") + RegInfoHigh[TU & 0xFF] + AnsiString(": ") + IntToHex(ta,2) + AnsiString(" (") + AnsiString(ToBin(ta)) + AnsiString(")"));
                                return;
                        case Joypad2 :
                                Joy.SetStrobe(1, bit0(ta));
//                                if (DebuggingTrace) dprint(AnsiString("        RegWrite: ") + RegInfoHigh[TU & 0xFF] + AnsiString(": ") + IntToHex(ta,2) + AnsiString(" (") + AnsiString(ToBin(ta)) + AnsiString(")"));
                                return;

                        default :
                                if ((TU & 0xE000) == 0x6000)
                                        if (Mem.SRAMEnabled)
                                        {
//                                              tprint(AnsiString("SRAM Write (E): ") + IntToHex(TU & 0x1FFF,4) + AnsiString(" - ") + IntToHex(ta,2));
                                                *Mem.Main[TU] = ta;
                                        } else {
//                                              tprint(AnsiString("SRAM Write (D): ") + IntToHex(TU & 0x1FFF,4) + AnsiString(" - ") + IntToHex(ta,2));
                                        }

			switch (Mem.MapperNum) {
				case 0 :
					return;
				case 1 :
					if (TU < 0x8000) return;

//                                        tprint(AnsiString("MMC1: Write: ") + IntToHex(TU,4) + AnsiString(" - ") + IntToHex(ta,2));

					if (bit7(ta)) { MMC1.ArrayPtr = 0; MMC1.Array = 0; return; }
					MMC1.Array |= (BYTE) ((ta & 0x01) << MMC1.ArrayPtr);
					MMC1.ArrayPtr++;
					if (MMC1.ArrayPtr == 5)
					{
						MMC1.UpdateReg((BYTE) ((TU & 0x7000) >> 13));
//                                                tprint(AnsiString("MMC1: Reg[") + AnsiString((TU & 0x7000) >> 13) + AnsiString("] = ") + IntToHex(MMC1.Reg[(TU & 0x7000) >> 13],2) + AnsiString(" (") + ToBin(MMC1.Reg[(TU & 0x7000) >> 13]) + AnsiString(")"));
						return;
					}
					return;
				case 2 :
					if (TU < 0x8000) return;

					Mem.PRGPageNum[0] = (BYTE) ((ta << 1) & Mem.PRGBitMask);
					Mem.PRGPageNum[1] = (BYTE) (Mem.PRGPageNum[0] + 1);

					UpdateGGCodes();
//                                        tprint(AnsiString("UNROM: PRGpg[0,1] = ") + AnsiString(Mem.PRGPageNum[0]) + AnsiString(",") + AnsiString(Mem.PRGPageNum[1]) + AnsiString(", TA = ") + IntToHex(ta,2) + AnsiString("(") + ToBin(ta) + AnsiString(")"));
					return;
				case 3 :
					if (TU < 0x8000) return;
                                        tmpLBYTE = (LBYTE) (((ta & 7) << 3) & Mem.CHRBitMask);
					Mem.CHRPageNumNew[0] = tmpLBYTE; Mem.CHRPageNumNew[1] = (LBYTE) (tmpLBYTE + 1); Mem.CHRPageNumNew[2] = (LBYTE) (tmpLBYTE + 2);
					Mem.CHRPageNumNew[3] = (LBYTE) (tmpLBYTE + 3); Mem.CHRPageNumNew[4] = (LBYTE) (tmpLBYTE + 4); Mem.CHRPageNumNew[5] = (LBYTE) (tmpLBYTE + 5);
					Mem.CHRPageNumNew[6] = (LBYTE) (tmpLBYTE + 6); Mem.CHRPageNumNew[7] = (LBYTE) (tmpLBYTE + 7);
					Mem.UpdateCHRPointers();
//                                        tprint(AnsiString("CNROM: CHRpg[0-7] = ") + AnsiString(tmpLBYTE) + AnsiString("-") + AnsiString(tmpLBYTE + 7));
					return;
				case 4 :
					if (TU < 0x8000) return;

					TU &= 0xE001;

					if (TU == 0x8000)
					{
						MMC3.Command = (BYTE) (ta & 0x07);
						MMC3.PRGSelect = bit6(ta);
						MMC3.CHRSelect = bit7(ta);
//                                                tprint(AnsiString("MMC3: Command# = ") + AnsiString(MMC3.Command) + AnsiString(", PRGSel = ") + AnsiString((BYTE) bit6(ta)) + AnsiString(", CHRSel = ") + AnsiString((BYTE) bit7(ta)));
						if (MMC3.PRGSelect)
						{
							Mem.PRGPageNum[0] = (BYTE) (Mem.PRGPagesA - 2);
						} else {
							Mem.PRGPageNum[2] = (BYTE) (Mem.PRGPagesA - 2);
						}
						return;
					}
					if (TU == 0x8001)
					{
						switch (MMC3.Command) {
							case 0 :
								tmpBYTE = (BYTE) (MMC3.CHRSelect << 2);
//								Mem.CHRPageNumNew[tmpBYTE] = (LBYTE) (((ta & 0xFE) << 1) & Mem.CHRBitMask);
								Mem.CHRPageNumNew[tmpBYTE] = (LBYTE) ((ta & 0xFE) & Mem.CHRBitMask);
								Mem.CHRPageNumNew[tmpBYTE + 1] = (LBYTE) (Mem.CHRPageNumNew[tmpBYTE] + 1);
								Mem.UpdateCHRPointers();
//                                                                tprint(AnsiString("MMC3: CHRpg[") + AnsiString(0 + (MMC3.CHRSelect << 2)) + AnsiString("] = ") + AnsiString(ta));
//                                                                tprint(AnsiString("MMC3: CHRpg[") + AnsiString(1 + (MMC3.CHRSelect << 2)) + AnsiString("] = ") + AnsiString(ta+1));
								return;
							case 1 :
								tmpBYTE = (BYTE) ((MMC3.CHRSelect << 2) + 2);
//								Mem.CHRPageNumNew[tmpBYTE] = (LBYTE) (((ta & 0xFE) << 1) & Mem.CHRBitMask);
								Mem.CHRPageNumNew[tmpBYTE] = (LBYTE) ((ta & 0xFE) & Mem.CHRBitMask);
								Mem.CHRPageNumNew[tmpBYTE + 1] = (LBYTE) (Mem.CHRPageNumNew[tmpBYTE] + 1);
								Mem.UpdateCHRPointers();
//                                                                tprint(AnsiString("MMC3: CHRpg[") + AnsiString(2 + (MMC3.CHRSelect << 2)) + AnsiString("] = ") + AnsiString(ta));
//                                                                tprint(AnsiString("MMC3: CHRpg[") + AnsiString(3 + (MMC3.CHRSelect << 2)) + AnsiString("] = ") + AnsiString(ta+1));
								return;
							case 2 :
								Mem.CHRPageNumNew[4^(MMC3.CHRSelect << 2)] = (LBYTE) (ta & Mem.CHRBitMask);
								Mem.UpdateCHRPointers();
//                                                                tprint(AnsiString("MMC3: CHRpg[") + AnsiString(4 ^ (MMC3.CHRSelect << 2)) + AnsiString("] = ") + AnsiString(ta));
								return;
							case 3 :
								Mem.CHRPageNumNew[5^(MMC3.CHRSelect << 2)] = (LBYTE) (ta & Mem.CHRBitMask);
								Mem.UpdateCHRPointers();
//                                                                tprint(AnsiString("MMC3: CHRpg[") + AnsiString(5 ^ (MMC3.CHRSelect << 2)) + AnsiString("] = ") + AnsiString(ta));
								return;
							case 4 :
								Mem.CHRPageNumNew[6^(MMC3.CHRSelect << 2)] = (LBYTE) (ta & Mem.CHRBitMask);
								Mem.UpdateCHRPointers();
//                                                                tprint(AnsiString("MMC3: CHRpg[") + AnsiString(6 ^ (MMC3.CHRSelect << 2)) + AnsiString("] = ") + AnsiString(ta));
								return;
							case 5 :
								Mem.CHRPageNumNew[7^(MMC3.CHRSelect << 2)] = (LBYTE) (ta & Mem.CHRBitMask);
								Mem.UpdateCHRPointers();
//                                                                tprint(AnsiString("MMC3: CHRpg[") + AnsiString(7 ^ (MMC3.CHRSelect << 2)) + AnsiString("] = ") + AnsiString(ta));
								return;
							case 6 :
								Mem.PRGPageNum[MMC3.PRGSelect << 1] = (BYTE) (ta & Mem.PRGBitMask);
								UpdateGGCodes();
//                                                                tprint(AnsiString("MMC3: PRGpg[") + AnsiString(MMC3.PRGSelect << 1) + AnsiString("] = ") + AnsiString(ta));
								return;
							case 7 :
								Mem.PRGPageNum[1] = (BYTE) (ta & Mem.PRGBitMask);
								UpdateGGCodes();
//                                                                tprint(AnsiString("MMC3: PRGpg[1] = ") + AnsiString(ta));
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
//                                                tprint(AnsiString("MMC3: MirrorChange: ") + AnsiString((bit0(ta)) ? "Horizontal" : "Vertical"));
						return;
					}
					if (TU == 0xA001)	{
						Mem.SRAMEnabled = bit7(ta);
//                                                tprint(AnsiString("MMC3: SRAM = ") + AnsiString((bit7(ta)) ? "On" : "Off"));
						return;
					}
					if (TU == 0xC000)	{
						MMC3.IRQCounter = ta;
//                                                tprint(AnsiString("MMC3: IRQCounter = ") + AnsiString(ta));
						return;
					}
					if (TU == 0xC001)   {
						MMC3.IRQLatch = ta;
//                                                tprint(AnsiString("MMC3: IRQLatch = ") + AnsiString(ta));
						return;
					}
					if (TU == 0xE000)
					{
						MMC3.IRQEnable = false;
						MMC3.IRQCounter = MMC3.IRQLatch;
//                                                tprint(AnsiString("MMC3: IRQEnabled = false"));
//                                                tprint(AnsiString("MMC3: IRQCounter = IRQLatch (") + AnsiString(ta) + AnsiString(")"));
						return;
					}
					if (TU == 0xE001)	{
						MMC3.IRQEnable = true;
//                                                tprint(AnsiString("MMC3: IRQEnabled = true"));
						return;
					}
					return;
				case 7 :
					if (TU < 0x8000) return;

					ta = (BYTE) ((ta & 0x0F) & Mem.PRGBitMask);
					if ((ta << 2) != Mem.PRGPageNum[0])
					{
						Mem.PRGPageNum[0] = (BYTE) (ta << 2); Mem.PRGPageNum[1] = (BYTE) (Mem.PRGPageNum[0] + 1);
						Mem.PRGPageNum[2] = (BYTE) (Mem.PRGPageNum[0] + 2); Mem.PRGPageNum[3] = (BYTE) (Mem.PRGPageNum[0] + 3);
						UpdateGGCodes();
					}
//                                        tprint(AnsiString("AOROM: PRGpg[0-3] = ") + AnsiString(ta) + AnsiString("-") + AnsiString(ta+3));

                                        Mem.UpdateNameTablePointers(bit4(ta),bit4(ta),bit4(ta),bit4(ta));
//                                        tprinto(AnsiString("AOROM: MirrorFrom = ") + IntToHex(0x2000 + (bit4(ta) << 10),4) + AnsiString(" Sc: ") + AnsiString(ScanLine));
					return;
				case 8 :
					if (TU < 0x8000) return;

					Mem.PRGPageNum[0] = (BYTE) ((((ta & 0xF8) >> 3) << 1) & Mem.PRGBitMask);
					Mem.PRGPageNum[1] = (BYTE) (Mem.PRGPageNum[0] + 1);

					Mem.CHRPageNumNew[0] = (BYTE) (((ta & 0x07) << 3) & Mem.CHRBitMask);
					Mem.CHRPageNumNew[1] = (BYTE) (Mem.CHRPageNumNew[0] + 1);
					Mem.CHRPageNumNew[2] = (BYTE) (Mem.CHRPageNumNew[0] + 2); Mem.CHRPageNumNew[3] = (BYTE) (Mem.CHRPageNumNew[0] + 3);
					Mem.CHRPageNumNew[4] = (BYTE) (Mem.CHRPageNumNew[0] + 4); Mem.CHRPageNumNew[5] = (BYTE) (Mem.CHRPageNumNew[0] + 5);
					Mem.CHRPageNumNew[6] = (BYTE) (Mem.CHRPageNumNew[0] + 6); Mem.CHRPageNumNew[7] = (BYTE) (Mem.CHRPageNumNew[0] + 7);

                                        Mem.UpdateCHRPointers();
					UpdateGGCodes();
//                                        tprint(AnsiString("GNROM: PRG = ") + AnsiString(Mem.PRGPageNum[0]) + AnsiString(", CHR = ") + AnsiString(Mem.CHRPageNumNew[0] >> 3) + AnsiString(", ta = ") + IntToHex(ta,2));
					return;
/*                              case 9 :
					if (TU < 0xA000) return;
					if (TU < 0xB000) {
						Mem.PRGPageNum[0] = (BYTE) (ta & Mem.PRGBitMask);
						UpdateGGCodes();
					} else if (TU < 0xC000) {
						if (MMC4.Latch[0] == 0xFD) {
							Mem.CHRPageNumNew[0] = (BYTE) ((ta << 2) & Mem.CHRBitMask);
							Mem.CHRPageNumNew[1] = (BYTE) (Mem.CHRPageNumNew[0] + 1);
							Mem.UpdateCHRPointers();
						}
					} else if (TU < 0xD000) {
						if (MMC4.Latch[0] == 0xFE) {
							Mem.CHRPageNumNew[0] = (BYTE) ((ta << 2) & Mem.CHRBitMask);
							Mem.CHRPageNumNew[1] = (BYTE) (Mem.CHRPageNumNew[0] + 1);
							Mem.UpdateCHRPointers();
						}
					} else if (TU < 0xE000) {
						if (MMC4.Latch[1] == 0xFD) {
							Mem.CHRPageNumNew[2] = (BYTE) ((ta << 2) & Mem.CHRBitMask);
							Mem.CHRPageNumNew[3] = (BYTE) (Mem.CHRPageNumNew[2] + 1);
							Mem.UpdateCHRPointers();
						}
					} else if (TU < 0xF000) {
						if (MMC4.Latch[1] == 0xFE) {
							Mem.CHRPageNumNew[2] = (BYTE) ((ta << 2) & Mem.CHRBitMask);
							Mem.CHRPageNumNew[3] = (BYTE) (Mem.CHRPageNumNew[2] + 1);
							Mem.UpdateCHRPointers();
						}
					} else {
						if (ta) {
							Mem.UpdateNameTablePointers(MrHorz);
						} else {
							Mem.UpdateNameTablePointers(MrVert);
						}
					}
					return;
*/
				case 11 :
					if (TU < 0x8000) return;

					Mem.PRGPageNum[0] = (BYTE) (((ta & (BYTE) 0x03) << 2) & Mem.PRGBitMask);
					Mem.PRGPageNum[1] = (BYTE) (Mem.PRGPageNum[0] + 1);
					Mem.PRGPageNum[2] = (BYTE) (Mem.PRGPageNum[0] + 2); Mem.PRGPageNum[3] = (BYTE) (Mem.PRGPageNum[0] + 3);

					Mem.CHRPageNumNew[0] = (BYTE) ((((ta & 0xF0) >> 4) << 3) & Mem.CHRBitMask);
					Mem.CHRPageNumNew[1] = (BYTE) (Mem.CHRPageNumNew[0] + 1);
					Mem.CHRPageNumNew[2] = (BYTE) (Mem.CHRPageNumNew[0] + 2); Mem.CHRPageNumNew[3] = (BYTE) (Mem.CHRPageNumNew[0] + 3);
					Mem.CHRPageNumNew[4] = (BYTE) (Mem.CHRPageNumNew[0] + 4); Mem.CHRPageNumNew[5] = (BYTE) (Mem.CHRPageNumNew[0] + 5);
					Mem.CHRPageNumNew[6] = (BYTE) (Mem.CHRPageNumNew[0] + 6); Mem.CHRPageNumNew[7] = (BYTE) (Mem.CHRPageNumNew[0] + 7);

                                        Mem.UpdateCHRPointers();
					UpdateGGCodes();
//                                        tprint(AnsiString("ClrDrms: PRG = ") + AnsiString(Mem.PRGPageNum[0]) + AnsiString(", CHR = ") + AnsiString(Mem.CHRPageNumNew[0] >> 3));
					return;
                                case 13 :
					if (TU < 0x8000) return;

                                        ta = Mem.PRGPage[Mem.PRGPageNum[(TU & 0x6000) >> 13]][TU & 0x1FFF];

//                                        tprinto(ToBin(ta));

//                                        Mem.CHRPageNumNew[4] = (BYTE) ((ta & 0x03) << 2);
                                        Mem.CHRPageNumNew[4] = (BYTE) (ta << 2);
                                        Mem.CHRPageNumNew[5] = (BYTE) (Mem.CHRPageNumNew[4] + 1);
                                        Mem.CHRPageNumNew[6] = (BYTE) (Mem.CHRPageNumNew[4] + 2);
                                        Mem.CHRPageNumNew[7] = (BYTE) (Mem.CHRPageNumNew[4] + 3);

                                        Mem.UpdateCHRPointers();

//                                        tprint(AnsiString("ClrDrms: PRG = ") + AnsiString(Mem.PRGPageNum[0]) + AnsiString(", CHR = ") + AnsiString(Mem.CHRPageNumNew[0] >> 3));
					return;
				case 15 :
					if (TU < 0x8000) return;

					switch (TU) {
						case 0x8000 :
                                                        tmpBYTE = (BYTE) ((ta & (BYTE) 0x63) << 1);
                                                        if (bit7(ta)) {
                                                                Mem.PRGPageNum[0] = tmpBYTE;
                                                                Mem.PRGPageNum[1] = (BYTE) (tmpBYTE + 1);
                                                                Mem.PRGPageNum[2] = (BYTE) (tmpBYTE + 3);
                                                                Mem.PRGPageNum[3] = (BYTE) (tmpBYTE + 2);
                                                        } else {
                                                                Mem.PRGPageNum[0] = (BYTE) (tmpBYTE + 1);
                                                                Mem.PRGPageNum[1] = tmpBYTE;
                                                                Mem.PRGPageNum[2] = (BYTE) (tmpBYTE + 2);
                                                                Mem.PRGPageNum[3] = (BYTE) (tmpBYTE + 3);
                                                        }

														
							if (bit6(ta)) {
								Mem.UpdateNameTablePointers(MrHorz);
							} else {
								Mem.UpdateNameTablePointers(MrVert);
							}

							break;
						case 0x8001 :
                                                        tmpBYTE = (BYTE) ((ta & (BYTE) 0x63) << 1);
                                                        if (bit7(ta)) {
                                                                Mem.PRGPageNum[2] = (BYTE) (tmpBYTE + 1);
                                                                Mem.PRGPageNum[3] = tmpBYTE;
							} else {
                                                                Mem.PRGPageNum[2] = tmpBYTE;
                                                                Mem.PRGPageNum[3] = (BYTE) (tmpBYTE + 1);
							}
							break;
						case 0x8002 :
                                                        tmpBYTE = (BYTE) ((ta & (BYTE) 0x63) << 1);
                                                        Mem.PRGPageNum[0] = (BYTE) (tmpBYTE + bit7(ta));
							Mem.PRGPageNum[1] = (BYTE) (Mem.PRGPageNum[0]);
                                                        Mem.PRGPageNum[2] = (BYTE) (Mem.PRGPageNum[0]);
                                                        Mem.PRGPageNum[3] = (BYTE) (Mem.PRGPageNum[0]);
																					break;
						case 0x8003 :
                                                        tmpBYTE = (BYTE) ((ta & (BYTE) 0x63) << 1);
                                                        if (bit7(ta)) {
                                                                Mem.PRGPageNum[2] = (BYTE) (tmpBYTE + 1);
                                                                Mem.PRGPageNum[3] = tmpBYTE;
							} else {
                                                                Mem.PRGPageNum[2] = tmpBYTE;
                                                                Mem.PRGPageNum[3] = (BYTE) (tmpBYTE + 1);
							}
														
							if (bit6(ta)) {
								Mem.UpdateNameTablePointers(MrHorz);
							} else {
								Mem.UpdateNameTablePointers(MrVert);
							}
							break;
					};
					return;
				case 16 :
//                                        Application->MessageBox(IntToHex(TU,4).c_str(), "Mmm", MB_OK);

                                        if (((TU >= 0x6000) && (TU <= 0x600D))
                                         || ((TU >= 0x7FF0) && (TU <= 0x7FFD))
                                         || ((TU >= 0x8000) && (TU <= 0x800D)))
                                        {
//                                                Application->MessageBox(IntToHex(TU,4).c_str(), "Woot!", MB_OK);

                                                tmpBYTE = (BYTE) (TU & 0x000F);
                                                switch (tmpBYTE) {
                                                        case 0x0 :
                                                                Mem.CHRPageNumNew[0] = ta;
                                                                Mem.UpdateCHRPointers();
                                                                break;
                                                        case 0x1 :
                                                                Mem.CHRPageNumNew[1] = ta;
                                                                Mem.UpdateCHRPointers();
                                                                break;
                                                        case 0x2 :
                                                                Mem.CHRPageNumNew[2] = ta;
                                                                Mem.UpdateCHRPointers();
                                                                break;
                                                        case 0x3 :
                                                                Mem.CHRPageNumNew[3] = ta;
                                                                Mem.UpdateCHRPointers();
                                                                break;
                                                        case 0x4 :
                                                                Mem.CHRPageNumNew[4] = ta;
                                                                Mem.UpdateCHRPointers();
                                                                break;
                                                        case 0x5 :
                                                                Mem.CHRPageNumNew[5] = ta;
                                                                Mem.UpdateCHRPointers();
                                                                break;
                                                        case 0x6 :
                                                                Mem.CHRPageNumNew[6] = ta;
                                                                Mem.UpdateCHRPointers();
                                                                break;
                                                        case 0x7 :
                                                                Mem.CHRPageNumNew[7] = ta;
                                                                Mem.UpdateCHRPointers();
                                                                break;
                                                        case 0x8 :
                                                                Mem.PRGPageNum[0] = (BYTE) ((ta << 1) & Mem.PRGBitMask);
                                                                Mem.PRGPageNum[1] = (BYTE) (Mem.PRGPageNum[0] + 1);
																                                                                break;
                                                        case 0x9 :
                                                                switch (ta) {
                                                                        case 0 :
                                                                                Mem.UpdateNameTablePointers(MrHorz);
                                                                                break;
                                                                        case 1 :
                                                                                Mem.UpdateNameTablePointers(MrVert);
                                                                                break;
                                                                        case 2 :
                                                                                Mem.UpdateNameTablePointers(0, 0, 0, 0);
                                                                                break;
                                                                        case 3 :
                                                                                Mem.UpdateNameTablePointers(1, 1, 1, 1);
                                                                                break;
                                                                };
                                                                break;
                                                        case 0xA :
                                                                M16.IRQEnabled = (bool) (ta & 1);
                                                                break;
                                                        case 0xB :
                                                                M16.IRQCounter &= 0xFF00;
                                                                M16.IRQCounter |= ta;
                                                                break;
                                                        case 0xC :
                                                                M16.IRQCounter &= 0x00FF;
                                                                M16.IRQCounter |= (LBYTE) (ta << 8);
                                                                break;
                                                        case 0xD :
                                                                //EPROM
                                                                break;
                                                };
                                        }
					return;
                                case 17 :
                                        switch (TU)
                                        {
                                                case 0x42FE :
                                                        if (ta & 0x10)
                                                        {
//                                                                Mem.UpdateNameTablePointers(0, 0, 0, 0);
                                                                Mem.UpdateNameTablePointers(1, 1, 1, 1);
                                                        } else {
//                                                                Mem.UpdateNameTablePointers(1, 1, 1, 1);
                                                                Mem.UpdateNameTablePointers(0, 0, 0, 0);
                                                        }
                                                        break;
                                                case 0x42FF :
                                                        if (ta & 0x10)
                                                        {
                                                                Mem.UpdateNameTablePointers(MrVert);
//                                                                Mem.UpdateNameTablePointers(MrHorz);
                                                        } else {
                                                                Mem.UpdateNameTablePointers(MrHorz);
//                                                                Mem.UpdateNameTablePointers(MrVert);
                                                        }
                                                        break;
                                                case 0x4501 :
                                                        M17.IRQEnabled = false;
                                                        break;
                                                case 0x4502 :
                                                        M17.IRQCounter &= 0xFF00;
                                                        M17.IRQCounter |= ta;
                                                        break;
                                                case 0x4503 :
                                                        M17.IRQCounter &= 0x00FF;
                                                        M17.IRQCounter |= (LBYTE) (ta << 8);
                                                        M17.IRQEnabled = true;
                                                        break;

                                                case 0x4504 :
														Mem.PRGPageNum[0] = (BYTE) (ta & Mem.PRGBitMask);
														break;
                                                case 0x4505 :
                                                        Mem.PRGPageNum[1] = (BYTE) (ta & Mem.PRGBitMask);
														break;
												case 0x4506 :
														Mem.PRGPageNum[2] = (BYTE) (ta & Mem.PRGBitMask);
														break;
												case 0x4507 :
														Mem.PRGPageNum[3] = (BYTE) (ta & Mem.PRGBitMask);
														break;

												case 0x4510 :
														Mem.CHRPageNumNew[0] = ta;
														Mem.UpdateCHRPointers();
														break;
												case 0x4511 :
                                                        Mem.CHRPageNumNew[1] = ta;
                                                        Mem.UpdateCHRPointers();
                                                        break;
                                                case 0x4512 :
                                                        Mem.CHRPageNumNew[2] = ta;
                                                        Mem.UpdateCHRPointers();
                                                        break;
                                                case 0x4513 :
                                                        Mem.CHRPageNumNew[3] = ta;
                                                        Mem.UpdateCHRPointers();
                                                        break;
                                                case 0x4514 :
                                                        Mem.CHRPageNumNew[4] = ta;
                                                        Mem.UpdateCHRPointers();
                                                        break;
                                                case 0x4515 :
                                                        Mem.CHRPageNumNew[5] = ta;
                                                        Mem.UpdateCHRPointers();
                                                        break;
                                                case 0x4516 :
                                                        Mem.CHRPageNumNew[6] = ta;
                                                        Mem.UpdateCHRPointers();
                                                        break;
                                                case 0x4517 :
                                                        Mem.CHRPageNumNew[7] = ta;
                                                        Mem.UpdateCHRPointers();
                                                        break;
                                        };
                                        return;
                                case 23 :
                                        switch (TU & 0xF000)
                                        {
                                                case 0x8000 :
                                                        Mem.PRGPageNum[0] = (BYTE) (ta);
														break;
                                                case 0x9000 :
                                                        switch (ta) {
                                                                case 0 :
                                                                        Mem.UpdateNameTablePointers(MrVert);
                                                                        break;
                                                                case 1 :
                                                                        Mem.UpdateNameTablePointers(MrHorz);
                                                                        break;
                                                                case 2 :
                                                                        Mem.UpdateNameTablePointers(1, 1, 1, 1);
                                                                        break;
                                                                case 3 :
                                                                        Mem.UpdateNameTablePointers(0, 0, 0, 0);
                                                                        break;
                                                        };
                                                        break;
                                                case 0xA000 :
                                                        Mem.PRGPageNum[1] = (BYTE) (ta);
														break;
                                                default :
                                                        tmp = (BYTE) ((((TU+0x1000) & 0x3000) >> 11) | ((TU & 2) >> 1));

                                                        if (TU & 1)
                                                        {
                                                                Mem.CHRPageNumNew[tmp] &= 0x0F;
                                                                Mem.CHRPageNumNew[tmp] |= (BYTE) (ta << 4);
                                                        } else {
                                                                Mem.CHRPageNumNew[tmp] &= 0xF0;
                                                                Mem.CHRPageNumNew[tmp] |= ta;
                                                        }
                                                        Mem.UpdateCHRPointers();
                                                        break;
                                        };
                                        return;
				case 24 :
					if (TU < 0x8000) return;

					if (TU == 0x8000) {
						Mem.PRGPageNum[0] = (BYTE) ((ta << 1) & Mem.PRGBitMask);
						Mem.PRGPageNum[1] = (BYTE) (Mem.PRGPageNum[0] + 1);
					} else if (TU == 0xB003) {
						switch (ta & 0x0C) {
                                                        case 0x0 :
                                                                Mem.UpdateNameTablePointers(MrVert);
								break;
                                                        case 0x4 :
								Mem.UpdateNameTablePointers(MrHorz);
								break;
                                                        case 0x8 :
								Mem.UpdateNameTablePointers(0, 0, 0, 0);
                                                                break;
                                                        case 0xC :
								Mem.UpdateNameTablePointers(1, 1, 1, 1);
								break;
						};
					} else if (TU == 0xC000) {
						Mem.PRGPageNum[2] = (BYTE) (ta & Mem.PRGBitMask);

					} else if (TU == 0xD000) {
                                                Mem.CHRPageNumNew[0] = (LBYTE) ((ta));
						Mem.UpdateCHRPointers();
					} else if (TU == 0xD001) {
                                                Mem.CHRPageNumNew[1] = (LBYTE) ((ta));
						Mem.UpdateCHRPointers();
					} else if (TU == 0xD002) {
                                                Mem.CHRPageNumNew[2] = (LBYTE) ((ta));
						Mem.UpdateCHRPointers();
					} else if (TU == 0xD003) {
                                                Mem.CHRPageNumNew[3] = (LBYTE) ((ta));
						Mem.UpdateCHRPointers();
					} else if (TU == 0xE000) {
                                                Mem.CHRPageNumNew[4] = (LBYTE) ((ta));
						Mem.UpdateCHRPointers();
					} else if (TU == 0xE001) {
                                                Mem.CHRPageNumNew[5] = (LBYTE) ((ta));
						Mem.UpdateCHRPointers();
					} else if (TU == 0xE002) {
                                                Mem.CHRPageNumNew[6] = (LBYTE) ((ta));
						Mem.UpdateCHRPointers();
					} else if (TU == 0xE003) {
                                                Mem.CHRPageNumNew[7] = (LBYTE) ((ta));
						Mem.UpdateCHRPointers();

					} else if (TU == 0xF000) {
                                                M24.IRQLatch = ta;
                                        } else if (TU == 0xF001) {
                                                M24.IRQEnable = ta & 2;
                                                M24.Tmp = ta & 1;
                                                if (M24.IRQEnable) M24.IRQCounter = M24.IRQLatch;
					} else if (TU == 0xF002) {
                                                M24.IRQEnable = M24.Tmp;

/*                                      } else if (TU == 0xF000) {
                                                if (ta != 255) M24.IRQCounter = ta;
                                        } else if (TU == 0xF001) {
                                                M24.IRQEnable = (bool) ta;
					} else if (TU == 0xF002) {
                                                M24.IRQCounter = 0;
*/

					} else {
//                                                tprint(AnsiString("M24: Illegal Write: Addr: ") + IntToHex(TU,4) + AnsiString(", Val: ") + IntToHex(ta,2) + AnsiString(" (") + ToBin(ta) + AnsiString(")"));
					}
					return;
				case 34 :
					if (TU < 0x7FFD) return;

					if ((TU == 0x7FFD) || (TU >= 0x8000))
					{
						Mem.PRGPageNum[0] = (BYTE) ((ta << 2) & Mem.PRGBitMask);
						Mem.PRGPageNum[1] = (BYTE) (Mem.PRGPageNum[0] + 1);

						UpdateGGCodes();
//                                                tprint(AnsiString("Nina-1: PRG[Low] = ") + AnsiString(Mem.PRGPageNum[0]) + AnsiString(", ta = ") + IntToHex(ta,2));
					}
					if (TU == 0x7FFE)
					{
						Mem.CHRPageNumNew[0] = (BYTE) ((ta << 2) & Mem.CHRBitMask);
						Mem.CHRPageNumNew[1] = (BYTE) (Mem.CHRPageNumNew[0] + 1);
						Mem.CHRPageNumNew[2] = (BYTE) (Mem.CHRPageNumNew[0] + 2); Mem.CHRPageNumNew[3] = (BYTE) (Mem.CHRPageNumNew[0] + 3);

						Mem.UpdateCHRPointers();
//                                                tprint(AnsiString("Nina-1: CHR[Low] = ") + AnsiString(Mem.CHRPageNumNew[0]) + AnsiString(", ta = ") + IntToHex(ta,2));
					}
					if (TU == 0x7FFF)
					{
						Mem.CHRPageNumNew[4] = (BYTE) ((ta << 2) & Mem.CHRBitMask);
						Mem.CHRPageNumNew[5] = (BYTE) (Mem.CHRPageNumNew[4] + 1);
						Mem.CHRPageNumNew[6] = (BYTE) (Mem.CHRPageNumNew[4] + 2); Mem.CHRPageNumNew[7] = (BYTE) (Mem.CHRPageNumNew[4] + 3);

						Mem.UpdateCHRPointers();
//                                                tprint(AnsiString("Nina-1: CHR[High] = ") + AnsiString(Mem.CHRPageNumNew[4]) + AnsiString(", ta = ") + IntToHex(ta,2));
					}
					return;
				case 64 :
					if (TU < 0x8000) return;

					if (TU == 0x8000)
					{
						MMC3.Command = (BYTE) (ta & 0x0F);
						MMC3.PRGSelect = bit6(ta);
						MMC3.CHRSelect = bit7(ta);
//                                                tprint(AnsiString("RAMBO-1: Command# = ") + AnsiString(MMC3.Command) + AnsiString(", PRGSel = ") + AnsiString((BYTE) bit6(ta)) + AnsiString(", CHRSel = ") + AnsiString((BYTE) bit7(ta)));
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
//                                                                tprint(AnsiString("RAMBO-1: CHRpg[") + AnsiString(0 + (MMC3.CHRSelect << 2)) + AnsiString("] = ") + AnsiString(ta));
//                                                                tprint(AnsiString("RAMBO-1: CHRpg[") + AnsiString(1 + (MMC3.CHRSelect << 2)) + AnsiString("] = ") + AnsiString(ta+1));
								return;
							case 1 :
								tmpBYTE = (BYTE) ((MMC3.CHRSelect << 2) + 2);
								Mem.CHRPageNumNew[tmpBYTE] = (LBYTE) ((ta & 0xFE) & Mem.CHRBitMask);
								Mem.CHRPageNumNew[tmpBYTE + 1] = (LBYTE) (Mem.CHRPageNumNew[tmpBYTE] + 1);

								Mem.UpdateCHRPointers();
//                                                                tprint(AnsiString("RAMBO-1: CHRpg[") + AnsiString(2 + (MMC3.CHRSelect << 2)) + AnsiString("] = ") + AnsiString(ta));
//                                                                tprint(AnsiString("RAMBO-1: CHRpg[") + AnsiString(3 + (MMC3.CHRSelect << 2)) + AnsiString("] = ") + AnsiString(ta+1));
								return;
							case 2 :
								Mem.CHRPageNumNew[4^(MMC3.CHRSelect << 2)] = (LBYTE) (ta & Mem.CHRBitMask);
								Mem.UpdateCHRPointers();
//                                                                tprint(AnsiString("RAMBO-1: CHRpg[") + AnsiString(4 ^ (MMC3.CHRSelect << 2)) + AnsiString("] = ") + AnsiString(ta));
								return;
							case 3 :
								Mem.CHRPageNumNew[5^(MMC3.CHRSelect << 2)] = (LBYTE) (ta & Mem.CHRBitMask);
								Mem.UpdateCHRPointers();
//                                                                tprint(AnsiString("RAMBO-1: CHRpg[") + AnsiString(5 ^ (MMC3.CHRSelect << 2)) + AnsiString("] = ") + AnsiString(ta));
								return;
							case 4 :
								Mem.CHRPageNumNew[6^(MMC3.CHRSelect << 2)] = (LBYTE) (ta & Mem.CHRBitMask);
								Mem.UpdateCHRPointers();
//                                                                tprint(AnsiString("RAMBO-1: CHRpg[") + AnsiString(6 ^ (MMC3.CHRSelect << 2)) + AnsiString("] = ") + AnsiString(ta));
								return;
							case 5 :
								Mem.CHRPageNumNew[7^(MMC3.CHRSelect << 2)] = (LBYTE) (ta & Mem.CHRBitMask);
								Mem.UpdateCHRPointers();
//                                                                tprint(AnsiString("RAMBO-1: CHRpg[") + AnsiString(7 ^ (MMC3.CHRSelect << 2)) + AnsiString("] = ") + AnsiString(ta));
								return;
							case 6 :
								Mem.PRGPageNum[MMC3.PRGSelect] = (BYTE) (ta & Mem.PRGBitMask);
								UpdateGGCodes();
//                                                                tprint(AnsiString("RAMBO-1: PRGpg[") + AnsiString(0 + MMC3.PRGSelect) + AnsiString("] = ") + AnsiString(ta));
								return;
							case 7 :
								Mem.PRGPageNum[1+MMC3.PRGSelect] = (BYTE) (ta & Mem.PRGBitMask);
								UpdateGGCodes();
//                                                                tprint(AnsiString("RAMBO-1: PRGpg[") + AnsiString(1 + MMC3.PRGSelect) + AnsiString("] = ") + AnsiString(ta));
								return;
							case 8 :
								Mem.CHRPageNumNew[1] = (LBYTE) (ta & Mem.CHRBitMask);
								Mem.UpdateCHRPointers();
//                                                                tprint(AnsiString("RAMBO-1: CHRpg[") + AnsiString(1) + AnsiString("] = ") + AnsiString(ta));
								return;
							case 9 :
								Mem.CHRPageNumNew[3] = (LBYTE) (ta & Mem.CHRBitMask);
								Mem.UpdateCHRPointers();
//                                                                tprint(AnsiString("RAMBO-1: CHRpg[") + AnsiString(3) + AnsiString("] = ") + AnsiString(ta));
								return;
							case 15 :
								if (MMC3.PRGSelect)
								{
									Mem.PRGPageNum[0] = (BYTE) (ta & Mem.PRGBitMask);
								} else {
									Mem.PRGPageNum[2] = (BYTE) (ta & Mem.PRGBitMask);
								}
								UpdateGGCodes();
//                                                                tprint(AnsiString("RAMBO-1: PRGpg[") + AnsiString((MMC3.PRGSelect) ? "0" : "2") + AnsiString("] = ") + AnsiString(ta));
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
//                                                tprint(AnsiString("RAMBO-1: MirrorChange: ") + AnsiString((bit0(ta)) ? "Horizontal" : "Vertical"));
						return;
					}
					return;
				case 66 :
					if (TU < 0x8000) return;

					Mem.PRGPageNum[0] = (BYTE) (((ta & 0xF0) >> 2) & Mem.PRGBitMask);
					Mem.PRGPageNum[1] = (BYTE) (Mem.PRGPageNum[0] + 1);
					Mem.PRGPageNum[2] = (BYTE) (Mem.PRGPageNum[0] + 2); Mem.PRGPageNum[3] = (BYTE) (Mem.PRGPageNum[0] + 3);

					Mem.CHRPageNumNew[0] = (BYTE) (((ta & 0x0F) << 3) & Mem.CHRBitMask);
					Mem.CHRPageNumNew[1] = (BYTE) (Mem.CHRPageNumNew[0] + 1);
					Mem.CHRPageNumNew[2] = (BYTE) (Mem.CHRPageNumNew[0] + 2); Mem.CHRPageNumNew[3] = (BYTE) (Mem.CHRPageNumNew[0] + 3);
					Mem.CHRPageNumNew[4] = (BYTE) (Mem.CHRPageNumNew[0] + 4); Mem.CHRPageNumNew[5] = (BYTE) (Mem.CHRPageNumNew[0] + 5);
					Mem.CHRPageNumNew[6] = (BYTE) (Mem.CHRPageNumNew[0] + 6); Mem.CHRPageNumNew[7] = (BYTE) (Mem.CHRPageNumNew[0] + 7);

                                        Mem.UpdateCHRPointers();
					UpdateGGCodes();
//                                        tprint(AnsiString("GNROM: PRG = ") + AnsiString(Mem.PRGPageNum[0]) + AnsiString(", CHR = ") + AnsiString(Mem.CHRPageNumNew[0] >> 3) + AnsiString(", ta = ") + IntToHex(ta,2));
					return;
				case 71 :
					if (TU < 0x8000) return;

					if (TU < 0xC000)
					{
						//Unknown
//                                                tprinto(AnsiString("Camerica: Write to Unknown Area!  ta = ") + IntToHex(ta,2) + AnsiString(", addr = ") + IntToHex(TU,4));
					} else {
						Mem.PRGPageNum[0] = (BYTE) ((ta << 1) & Mem.PRGBitMask);
						Mem.PRGPageNum[1] = (BYTE) (Mem.PRGPageNum[0] + 1);
						UpdateGGCodes();
//                                                tprint(AnsiString("Camerica: PRGpg[0,1] = ") + AnsiString(Mem.PRGPageNum[0]) + AnsiString(",") + AnsiString(Mem.PRGPageNum[0] + 1) + AnsiString(", ta = ") + IntToHex(ta,2));
					}
					return;
				case 90 :
					if (TU < 0x8000) return;

//                                        tprinto(AnsiString("M90: Address: ") + IntToHex(TU,4) + AnsiString(", Val: ") + IntToHex(ta,2) + AnsiString(" (") + ToBin(ta) + AnsiString(")"));

					if ((TU & 0xFFFC) == 0x8000) {
						Mem.PRGPageNum[TU & 3] = (BYTE) (ta & Mem.PRGBitMask);
						UpdateGGCodes();

					} else if (TU == 0x9000) {
						if (!M90.CHRSwitch[0])
						{
							Mem.CHRPageNumNew[0] = (LBYTE) ((ta & 0x7F) << 2);
							Mem.CHRPageNumNew[1] = (LBYTE) (Mem.CHRPageNumNew[0] + 1);
							Mem.CHRPageNumNew[2] = (LBYTE) (Mem.CHRPageNumNew[0] + 2);
							Mem.CHRPageNumNew[3] = (LBYTE) (Mem.CHRPageNumNew[0] + 3);
						} else {
							Mem.CHRPageNumNew[0] = (LBYTE) ((Mem.CHRPageNumNew[0] & 0x180) | (ta));
						}
						Mem.UpdateCHRPointers();
					} else if (TU == 0x9001) {
						if (!M90.CHRSwitch[0])
						{
							Mem.CHRPageNumNew[1] = (LBYTE) ((Mem.CHRPageNumNew[1] & 0x180) | (ta));
							Mem.UpdateCHRPointers();
						}
					} else if (TU == 0x9002) {
						if (!M90.CHRSwitch[0])
						{
							Mem.CHRPageNumNew[2] = (LBYTE) ((Mem.CHRPageNumNew[2] & 0x180) | (ta));
							Mem.UpdateCHRPointers();
						}
					} else if (TU == 0x9003) {
						if (!M90.CHRSwitch[0])
						{
							Mem.CHRPageNumNew[3] = (LBYTE) ((Mem.CHRPageNumNew[3] & 0x180) | (ta));
							Mem.UpdateCHRPointers();
						}
					} else if (TU == 0x9004) {
						if (!M90.CHRSwitch)
						{
							Mem.CHRPageNumNew[4] = (LBYTE) ((ta & 0x7F) << 2);
							Mem.CHRPageNumNew[5] = (LBYTE) (Mem.CHRPageNumNew[4] + 1);
							Mem.CHRPageNumNew[6] = (LBYTE) (Mem.CHRPageNumNew[4] + 2);
							Mem.CHRPageNumNew[7] = (LBYTE) (Mem.CHRPageNumNew[4] + 3);
						} else {
							Mem.CHRPageNumNew[4] = (LBYTE) ((Mem.CHRPageNumNew[4] & 0x180) | (ta));
						}
						Mem.UpdateCHRPointers();
					} else if (TU == 0x9005) {
						if (!M90.CHRSwitch[1])
						{
							Mem.CHRPageNumNew[5] = (LBYTE) ((Mem.CHRPageNumNew[5] & 0x180) | (ta));
							Mem.UpdateCHRPointers();
						}
					} else if (TU == 0x9006) {
						if (!M90.CHRSwitch[1])
						{
							Mem.CHRPageNumNew[6] = (LBYTE) ((Mem.CHRPageNumNew[6] & 0x180) | (ta));
							Mem.UpdateCHRPointers();
						}
					} else if (TU == 0x9007) {
						if (!M90.CHRSwitch[1])
						{
							Mem.CHRPageNumNew[7] = (LBYTE) ((Mem.CHRPageNumNew[7] & 0x180) | (ta));
							Mem.UpdateCHRPointers();
						}
					} else if ((TU & 0xFFF8) == 0xB000) {
						if (!M90.CHRSwitch[(bool) (TU & 4)])
						{
							Mem.CHRPageNumNew[TU & 7] = (LBYTE) ((Mem.CHRPageNumNew[TU & 7] & 0x07F) | ((ta & 3) << 7));
                                                        Mem.UpdateCHRPointers();
						}
					} else if (TU == 0xC000) {
						M90.CounterVal = ta;
					} else if (TU == 0xC001) {
						M90.CounterLatch = ta;
					} else if (TU == 0xC002) {
						M90.SLEnabled = false;
						M90.CounterVal = M90.CounterLatch;
					} else if (TU == 0xC003) {
						M90.SLEnabled = true;
					} else {
//						tprinto(AnsiString("M90: Address: ") + IntToHex(TU,4) + AnsiString(", Val: ") + IntToHex(ta,2) + AnsiString(" (") + ToBin(ta) + AnsiString(")"));
					}
					return;
				case 91 :
					if (TU < 0x6000) return;

                                        if ((TU & 0xF003)  == 0x6000) {
						Mem.CHRPageNumNew[0] = (LBYTE) ((ta << 1) & Mem.CHRBitMask);
						Mem.CHRPageNumNew[1] = (LBYTE) (Mem.CHRPageNumNew[0] + 1);
						Mem.UpdateCHRPointers();
//                                                tprint(AnsiString("SF3: CHR[0,1] = ") + AnsiString(Mem.CHRPageNumNew[0]) + AnsiString(",") + AnsiString(Mem.CHRPageNumNew[1]));
                                        } else if ((TU & 0xF003) == 0x6001) {
						Mem.CHRPageNumNew[2] = (LBYTE) ((ta << 1) & Mem.CHRBitMask);
						Mem.CHRPageNumNew[3] = (LBYTE) (Mem.CHRPageNumNew[2] + 1);
						Mem.UpdateCHRPointers();
//                                                tprint(AnsiString("SF3: CHR[2,3] = ") + AnsiString(Mem.CHRPageNumNew[2]) + AnsiString(",") + AnsiString(Mem.CHRPageNumNew[3]));
                                        } else if ((TU & 0xF003) == 0x6002) {
						Mem.CHRPageNumNew[4] = (LBYTE) ((ta << 1) & Mem.CHRBitMask);
						Mem.CHRPageNumNew[5] = (LBYTE) (Mem.CHRPageNumNew[4] + 1);
						Mem.UpdateCHRPointers();
//                                                tprint(AnsiString("SF3: CHR[4,5] = ") + AnsiString(Mem.CHRPageNumNew[4]) + AnsiString(",") + AnsiString(Mem.CHRPageNumNew[5]));
                                        } else if ((TU & 0xF003) == 0x6003) {
						Mem.CHRPageNumNew[6] = (LBYTE) ((ta << 1) & Mem.CHRBitMask);
						Mem.CHRPageNumNew[7] = (LBYTE) (Mem.CHRPageNumNew[6] + 1);
						Mem.UpdateCHRPointers();
//                                                tprint(AnsiString("SF3: CHR[6,7] = ") + AnsiString(Mem.CHRPageNumNew[6]) + AnsiString(",") + AnsiString(Mem.CHRPageNumNew[7]));
                                        } else if ((TU & 0xF001) == 0x7000) {
                                                Mem.PRGPageNum[0] = (BYTE) (ta);
                                        } else if ((TU & 0xF001) == 0x7001) {
                                                Mem.PRGPageNum[1] = (BYTE) (ta);
//                                                tprint(AnsiString("SF3: PRG[0] = ") + AnsiString(Mem.PRGPageNum[0]));
					} else {
//                                                tprinto(AnsiString("SF3: Address: ") + IntToHex(TU,4) + AnsiString(", Val: ") + IntToHex(ta,2));
                                                Application->MessageBox(IntToHex(TU,4).c_str(),"Debug",MB_OK);
					}
					return;
				case 230 :
					if (TU < 0x8000) return;

					if (M22in1.ContraMode) {
						Mem.PRGPageNum[0] = (BYTE) ((ta & 7) << 1);
						Mem.PRGPageNum[1] = (BYTE) (Mem.PRGPageNum[0] + 1);
//                                                tprint(AnsiString("M22in1(C): PRG[0,1,2,3] = ") + AnsiString(Mem.PRGPageNum[0]) + AnsiString(",") + AnsiString(Mem.PRGPageNum[1]) + AnsiString(",") + AnsiString(Mem.PRGPageNum[2]) + AnsiString(",") + AnsiString(Mem.PRGPageNum[3]));
					} else {
						if (bit6(ta))
						{
							Mem.UpdateNameTablePointers(0, 1, 0, 1);
//                                                        tprint(AnsiString("M22in1(2): Mirroring: Vertical"));
						} else {
							Mem.UpdateNameTablePointers(0, 0, 2, 2);
//                                                        tprint(AnsiString("M22in1(2): Mirroring: Horizontal"));
						}
						if (bit5(ta))
						{
							Mem.PRGPageNum[0] = (BYTE) (((ta & 0x1F) << 1) + 16);
							Mem.PRGPageNum[1] = (BYTE) (Mem.PRGPageNum[0] + 1);
							Mem.PRGPageNum[2] = (BYTE) (Mem.PRGPageNum[0]);
							Mem.PRGPageNum[3] = (BYTE) (Mem.PRGPageNum[0] + 1);
						} else {
							Mem.PRGPageNum[0] = (BYTE) (((ta & 0x1E) << 1) + 16);
							Mem.PRGPageNum[1] = (BYTE) (Mem.PRGPageNum[0] + 1);
							Mem.PRGPageNum[2] = (BYTE) (Mem.PRGPageNum[0] + 2);
							Mem.PRGPageNum[3] = (BYTE) (Mem.PRGPageNum[0] + 3);
						}
//                                                tprint(AnsiString("M22in1(2): PRG[0,1,2,3] = ") + AnsiString(Mem.PRGPageNum[0]) + AnsiString(",") + AnsiString(Mem.PRGPageNum[1]) + AnsiString(",") + AnsiString(Mem.PRGPageNum[2]) + AnsiString(",") + AnsiString(Mem.PRGPageNum[3]));
					}
					UpdateGGCodes();
					return;
			};
                };
        } else if (TU < 0x2000) {
                *Mem.Main[TU] = ta;
        }
}
//---------------------------------------------------------------------------
//Addressing Modes
//---------------------------------------------------------------------------
void __fastcall Addrmode(BYTE adrmode)
{
	switch (adrmode) {
		case Imp:
			break;
		case ImmA:	//Immediate - #nn

                        if (PC & 0x8000)
			TU = Mem.PRGPage[Mem.PRGPageNum[((PC + 1) & 0x6000) >> 13]][(PC + 1) & 0x1FFF];
			else
			TU = *Mem.Main[PC+1];

                        TUMode = tmVal;


/*                        asm {
                                mov byte ptr [_TUMode],0
                                mov ecx,dword ptr [_PC]
                                cmp ecx,8000h
                                jnae ImmaSec

                                inc       ecx
                                mov       eax,ecx
                                and       eax,1fffh
                                and       ecx,6000h
                                shr       ecx,12
                                movsx     edx,word ptr [_Mem.PRGPageNum+ecx]
                                shl       edx,13
                                lea       ecx,dword ptr [edx+_Mem.PRGPage]
                                movzx     eax,byte ptr [ecx+eax]
                                mov       dword ptr [_TU],eax

                                jmp ImmaEx
ImmaSec:
                                mov       eax,dword ptr [_Mem+4+4*ecx]
                                movzx     edx,byte ptr [eax]
                                mov       dword ptr [_TU],edx
ImmaEx:
                        }*/
                        break;
		case Abs:	//Absolute - nnnn
			if (PC & 0x8000)
			{
				tmpBYTE = (BYTE) (((PC + 1) & 0x6000) >> 13);
				tmpLBYTE = (LBYTE) ((PC + 1) & 0x1FFF);
				TU = (LBYTE) ((Mem.PRGPage[Mem.PRGPageNum[tmpBYTE]][tmpLBYTE + 1] << 8) | Mem.PRGPage[Mem.PRGPageNum[tmpBYTE]][tmpLBYTE]);
			} else {
				TU = (LBYTE) (Get16Bit(PC + 1));
			}

			TUMode = tmAddr;
			break;
		case Zp:	//Zero-Page - nn

                        if (PC & 0x8000)
			TU = Mem.PRGPage[Mem.PRGPageNum[((PC + 1) & 0x6000) >> 13]][(PC + 1) & 0x1FFF];
			else
			TU = *Mem.Main[PC+1];

                        TUMode = tmAddr;


/*                        asm {
                                mov byte ptr [_TUMode],1

                                mov ecx,dword ptr [_PC]
                                cmp ecx,8000h
                                jnae ZpSec

                                inc       ecx
                                mov       eax,ecx
                                and       eax,1fffh
                                and       ecx,6000h
                                shr       ecx,12
                                movsx     edx,word ptr [_Mem.PRGPageNum+ecx]
                                shl       edx,13
                                lea       ecx,dword ptr [edx+_Mem.PRGPage]
                                movzx     eax,byte ptr [ecx+eax]
                                mov       dword ptr [_TU],eax
                                jmp ZpEx
ZpSec:
                                mov       eax,dword ptr [_Mem+4+4*ecx]
                                movzx     edx,byte ptr [eax]
                                mov       dword ptr [_TU],edx
ZpEx:
                        }*/
			break;
		case Ind:	//Indirect Absolute - (nnnn)
			if (PC & 0x8000)
			{
				tmpBYTE = (BYTE) (((PC + 1) & 0x6000) >> 13);
				tmpLBYTE = (LBYTE) ((PC + 1) & 0x1FFF);
				tmp = Mem.PRGPage[Mem.PRGPageNum[tmpBYTE]][tmpLBYTE];
				TU = (LBYTE) ((Mem.PRGPage[Mem.PRGPageNum[tmpBYTE]][tmpLBYTE + 1] << 8) | tmp);
			} else {
				tmp = *Mem.Main[PC+1];
				TU = (LBYTE) ((*Mem.Main[PC+2] << 8) + tmp);
			}

			if (TU & 0x8000)
			{
				tmpBYTE = (BYTE) ((TU & 0x6000) >> 13);
				tmpLBYTE = (LBYTE) (TU & 0x1FFF);
				TU = (LBYTE) ((Mem.PRGPage[Mem.PRGPageNum[tmpBYTE]][(tmpLBYTE & 0x1F00) | (BYTE) (tmp + 1)] << 8) | Mem.PRGPage[Mem.PRGPageNum[tmpBYTE]][tmpLBYTE]);
			} else {
				TU = (LBYTE) ((*Mem.Main[(LBYTE) (TU & 0xFF00) | (BYTE) (tmp + 1)] << 8) | *Mem.Main[TU]);
			}

			TUMode = tmAddr;
			break;
		case Absx:	//Absolute Indexed, X - nnnn,X
			if (PC & 0x8000)
			{
				tmpBYTE = (BYTE) (((PC + 1) & 0x6000) >> 13);
				tmpLBYTE = (LBYTE) ((PC + 1) & 0x1FFF);
				TU = (LBYTE) ((Mem.PRGPage[Mem.PRGPageNum[tmpBYTE]][tmpLBYTE + 1] << 8) + Mem.PRGPage[Mem.PRGPageNum[tmpBYTE]][tmpLBYTE] + X);
			} else {
				TU = (LBYTE) ((*Mem.Main[PC+2] << 8) + *Mem.Main[PC+1] + X);
			}

			TUMode = tmAddr;
			break;
		case Absy:	//Absolute Indexed, Y - nnnn,Y
			if (PC & 0x8000)
			{
				tmpBYTE = (BYTE) (((PC + 1) & 0x6000) >> 13);
				tmpLBYTE = (LBYTE) ((PC + 1) & 0x1FFF);
				TU = (LBYTE) ((Mem.PRGPage[Mem.PRGPageNum[tmpBYTE]][tmpLBYTE + 1] << 8) + Mem.PRGPage[Mem.PRGPageNum[tmpBYTE]][tmpLBYTE] + Y);
			} else {
				TU = (LBYTE) ((*Mem.Main[PC+2] << 8) + *Mem.Main[PC+1] + Y);
			}

			TUMode = tmAddr;
			break;
		case Zpx:	//Zero-Page Indexed, X - nn,X
			if (PC & 0x8000)
			TU = (BYTE) (Mem.PRGPage[Mem.PRGPageNum[(PC & 0x6000) >> 13]][(PC + 1) & 0x1FFF] + X);
			else
			TU = (BYTE) (*Mem.Main[PC+1] + X);

			TUMode = tmAddr;
			break;
		case Zpy:	//Zero-Page Indexed, Y - nn,Y
			if (PC & 0x8000)
			TU = (BYTE) (Mem.PRGPage[Mem.PRGPageNum[(PC & 0x6000) >> 13]][(PC + 1) & 0x1FFF] + Y);
			else
			TU = (BYTE) (*Mem.Main[PC+1] + Y);

			TUMode = tmAddr;
			break;
		case Idx:	//Indexed Indirect - (nn,X)
			if (PC & 0x8000)
			TU = (BYTE) (Mem.PRGPage[Mem.PRGPageNum[(PC & 0x6000) >> 13]][(PC + 1) & 0x1FFF] + X);
			else
			TU = (BYTE) (*Mem.Main[PC+1] + X);

			if (TU & 0x8000)
			{
				tmpBYTE = (BYTE) ((TU & 0x6000) >> 13);
				tmpLBYTE = (LBYTE) (TU & 0x1FFF);
				TU = (LBYTE) ((Mem.PRGPage[Mem.PRGPageNum[tmpBYTE]][tmpLBYTE + 1] << 8) | Mem.PRGPage[Mem.PRGPageNum[tmpBYTE]][tmpLBYTE]);
			} else {
				TU = (LBYTE) (Get16Bit(TU));
			}

			TUMode = tmAddr;
			break;
		case Idy:	//Indirect Indexed - (nn),Y
			if (PC & 0x8000)
			TU = (BYTE) (Mem.PRGPage[Mem.PRGPageNum[(PC & 0x6000) >> 13]][(PC + 1) & 0x1FFF]);
			else
			TU = *Mem.Main[PC+1];

			if (TU & 0x8000)
			{
				tmpBYTE = (BYTE) ((TU & 0x6000) >> 13);
				tmpLBYTE = (LBYTE) (TU & 0x1FFF);
				TU = (LBYTE) ((Mem.PRGPage[Mem.PRGPageNum[tmpBYTE]][tmpLBYTE + 1] << 8) + Mem.PRGPage[Mem.PRGPageNum[tmpBYTE]][tmpLBYTE] + Y);
			} else {
				TU = (LBYTE) ((*Mem.Main[TU+1] << 8) + *Mem.Main[TU] + Y);
			}

			TUMode = tmAddr;
			break;
		case Rel:	//Relative - nn
			if (PC & 0x8000)
			TU2 = (char) (Mem.PRGPage[Mem.PRGPageNum[(PC & 0x6000) >> 13]][(PC + 1) & 0x1FFF]);
			else
			TU2 = (char) (*Mem.Main[PC+1]);
			break;
		case ERA:
			if (HaltOnBadOp) CPURunning = false;

			Application->ProcessMessages();
			if (!DebuggingTrace)
			{
//                                dprinto(IntToHex(PC,4) + AnsiString("    ") + IntToHex(*Mem.Main[PC],2) + AnsiString("        Bad Opcode!"));
				Application->ProcessMessages();
			}
			break;
	};

	if (!DebuggingTrace) return;

	Application->ProcessMessages();

	BYTE TB,NB,NB2;
	if (PC & 0x8000)
	{
		TB = Mem.PRGPage[Mem.PRGPageNum[(PC & 0x6000) >> 13]][PC & 0x1FFF];
		NB = Mem.PRGPage[Mem.PRGPageNum[((PC + 1) & 0x6000) >> 13]][(PC + 1) & 0x1FFF];
		NB2 = Mem.PRGPage[Mem.PRGPageNum[((PC + 2) & 0x6000) >> 13]][(PC + 2) & 0x1FFF];
	} else {
		TB = *Mem.Main[PC];
		NB = *Mem.Main[PC+1];
		NB2 = *Mem.Main[PC+2];
	}

	AnsiString PCAS = IntToHex(PC,4) + AnsiString("    ");
	AnsiString TBAS = IntToHex(TB,2);
	AnsiString NBAS = IntToHex(NB,2);
	AnsiString NBSAS = (bit7(NB) ? AnsiString(" -$") : AnsiString(" $")) + IntToHex( abs(((char) (NB))),2 );
	AnsiString NB2AS = IntToHex(NB2,2);
	AnsiString TIAS = Mn[instruc[TB]];
	switch (adrmode) {
		case ImmA:
//                        dprint(PCAS + TBAS + NBAS + AnsiString("      ") + TIAS + AnsiString(" #$") + NBAS);
			break;
		case Abs:
//                        dprint(PCAS + TBAS + NBAS + NB2AS + AnsiString("    ") + TIAS + AnsiString(" $") + NB2AS + NBAS);
			break;
		case Zp:
//                        dprint(PCAS + TBAS + NBAS + AnsiString("      ") + TIAS + AnsiString(" $00") + NBAS);
			break;
		case Imp:
//                        dprint(PCAS + TBAS + AnsiString("        ") + TIAS);
			break;
		case Ind:
//                        dprint(PCAS + TBAS + NBAS + NB2AS + AnsiString("    ") + TIAS + AnsiString(" ($") + NB2AS + NBAS + AnsiString(")"));
			break;
		case Absx:
//                        dprint(PCAS + TBAS + NBAS + NB2AS + AnsiString("    ") + TIAS + AnsiString(" $") + NB2AS + NBAS + AnsiString(", X"));
			break;
		case Absy:
//                        dprint(PCAS + TBAS + NBAS + NB2AS + AnsiString("    ") + TIAS + AnsiString(" $") + NB2AS + NBAS + AnsiString(", Y"));
			break;
		case Zpx:
//                        dprint(PCAS + TBAS + NBAS + AnsiString("      ") + TIAS + AnsiString(" $00") + NBAS + AnsiString(", X"));
			break;
		case Zpy:
//                        dprint(PCAS + TBAS + NBAS + AnsiString("      ") + TIAS + AnsiString(" $00") + NBAS + AnsiString(", Y"));
            break;
		case Idx:
//                        dprint(PCAS + TBAS + NBAS + AnsiString("      ") + TIAS + AnsiString(" ($") + NBAS + AnsiString(", X)"));
			break;
		case Idy:
//                        dprint(PCAS + TBAS + NBAS + AnsiString("      ") + TIAS + AnsiString(" ($") + NBAS + AnsiString("), Y"));
			break;
		case Rel:
//                        dprint(PCAS + TBAS + NBAS + AnsiString("      ") + TIAS + NBSAS);
			break;
		default :
//                        dprint(PCAS + TBAS + AnsiString("        Bad Opcode!"));
			break;
	}
}
//---------------------------------------------------------------------------
//Instructions
//---------------------------------------------------------------------------
void __fastcall ExecOp(BYTE opcode)
{
	switch (opcode) {
		case ADC :
			tmpBYTE = TUVal();
			tmpshortint = (short int) (A + tmpBYTE + CCRC);
/*			if (bit7(tmpBYTE) != bit7(A)) { UnsetV(); }	//Signs Diff
			else {
				short int tmpshortint2 = (short int) (((char) A) + ((char) tmpBYTE) + CCRC);
				if (bit7(tmpBYTE)) {		//Signs Neg
					if (tmpshortint2 < -128) SetV(); else UnsetV();
				} else {					//Signs Pos
					if (tmpshortint2 > 127) SetV(); else UnsetV();
				}
			}
*/
                        if (tmpshortint > 0xFF) SetC(); else UnsetC();         

                        if (((~(A^tmpBYTE)) & (A^ (BYTE) tmpshortint)) & 0x80) SetV(); else UnsetV();

			A = (BYTE) (tmpshortint);
			checkacc(A);
			return;
		case AND :
			A &= TUVal();
			checkacc(A);
			return;
		case ASL :
                        tmpBYTE = MemoryTUGet();
			if (bit7(tmpBYTE)) SetC(); else UnsetC();
			tmpBYTE <<= 1;
			checkacc(tmpBYTE)
			MemoryTUEquals(tmpBYTE);
			return;
		case ASLA:
			if (bit7(A)) SetC(); else UnsetC();
			A <<= 1;
			checkacc(A);
			return;
		case BCC :
			if (!CCRC) PC += TU2;
			return;
		case BCS :
			if (CCRC) PC += TU2;
			return;
		case BEQ :
			if (CCRZ) PC += TU2;
			return;
		case BIT :
                        tmpBYTE = MemoryTUGet();
			if (bit6(tmpBYTE)) SetV(); else UnsetV();
			if (bit7(tmpBYTE)) SetN(); else UnsetN();
			tmpBYTE &= A;
			if (tmpBYTE) UnsetZ(); else SetZ();
			return;
		case BMI :
			if (CCRN) PC += TU2;
			return;
		case BNE :
			if (!CCRZ) PC += TU2;
			return;
		case BPL :
			if (!CCRN) PC += TU2;
			return;
		case BRK :
			SetB();
                        PushPCaP();
			SetI();
			PC = (LBYTE) ((Mem.PRGPage[Mem.PRGPageNum[3]][0x1FFF] << 8) | Mem.PRGPage[Mem.PRGPageNum[3]][0x1FFE]);
			return;
		case BVC :
			if (!CCRV) PC += TU2;
			return;
		case BVS :
			if (CCRV) PC += TU2;
			return;
		case CLC :
			UnsetC();
			return;
		case CLD :
			UnsetD();
			return;
		case CLI :
			UnsetI();
			return;
		case CLV :
			UnsetV();
			return;
		case CMP :
			tmpshortint = (short int) (A - TUVal());
			checkacc(tmpshortint);
			if (tmpshortint >= 0) SetC(); else UnsetC();
			return;
		case CPX :
			tmpshortint = (short int) (X - TUVal());
			checkacc(tmpshortint);
			if (tmpshortint >= 0) SetC(); else UnsetC();
			return;
		case CPY :
			tmpshortint = (short int) (Y - TUVal());
			checkacc(tmpshortint);
			if (tmpshortint >= 0) SetC(); else UnsetC();
			return;
		case DEC :
                        tmpBYTE = MemoryTUGet();
			tmpBYTE--;
			checkacc(tmpBYTE);
			MemoryTUEquals(tmpBYTE);
			return;
		case DEX :
			X--;
			checkacc(X);
			return;
		case DEY :
			Y--;
			checkacc(Y);
			return;
		case EOR :
			A ^= TUVal();
			checkacc(A);
			return;
		case INC :
                        tmpBYTE = MemoryTUGet();
			tmpBYTE++;
			checkacc(tmpBYTE);
			MemoryTUEquals(tmpBYTE);
			return;
		case INX :
			X++;
			checkacc(X);
			return;
		case INY :
			Y++;
			checkacc(Y);
			return;
		case JMP :
			PC = (LBYTE) (TU);
			return;
		case JSR :
                        PushPC();
			PC = (LBYTE) (TU);
			return;
		case LDA :
			A = TUVal();
			checkacc(A);
			return;
		case LDX :
			X = TUVal();
			checkacc(X);
			return;
		case LDY :
			Y = TUVal();
			checkacc(Y);
			return;
		case LSR :
                        tmpBYTE = MemoryTUGet();
			if (bit0(tmpBYTE)) SetC(); else UnsetC();
			tmpBYTE >>= 1;
			checkacc(tmpBYTE);
			MemoryTUEquals(tmpBYTE);
			return;
		case LSRA:
			if (bit0(A)) SetC(); else UnsetC();
			A >>= 1;
			checkacc(A);
			return;
                case NOP :
                        return;
		case ORA :
			A |= TUVal();
			checkacc(A);
			return;
		case PHA :
			Mem.Stack[SP] = A;
			SP--;
			return;
		case PHP :
			PushP();
			return;
		case PLA :
			SP++;
			A = Mem.Stack[SP];
			checkacc(A);
			return;
		case PLP :
			PullP();
			return;
		case ROL :
                        tmpBYTE = MemoryTUGet();
			if (CCRC) {
				if (bit7(tmpBYTE)) SetC(); else UnsetC();
				tmpBYTE <<= 1;
				tmpBYTE |= 1;
			} else {
				if (bit7(tmpBYTE)) SetC(); else UnsetC();
				tmpBYTE <<= 1;
			}
			checkacc(tmpBYTE);
			MemoryTUEquals(tmpBYTE);
			return;
		case ROLA :
			if (CCRC) {
				if (bit7(A)) SetC(); else UnsetC();
				A <<= 1;
				A |= 1;
			} else {
				if (bit7(A)) SetC(); else UnsetC();
				A <<= 1;
			}
			checkacc(A);
			return;
		case ROR :
                        tmpBYTE = MemoryTUGet();

			if (CCRC) {
				if (bit0(tmpBYTE)) SetC(); else UnsetC();
				tmpBYTE >>= 1;
				tmpBYTE |= 0x80;
			} else {
				if (bit0(tmpBYTE)) SetC(); else UnsetC();
				tmpBYTE >>= 1;
			}
			checkacc(tmpBYTE);
			MemoryTUEquals(tmpBYTE);
			return;
		case RORA :
			if (CCRC) {
				if (bit0(A)) SetC(); else UnsetC();
				A >>= 1;
				A |= 0x80;
			} else {
				if (bit0(A)) SetC(); else UnsetC();
				A >>= 1;
			}
			checkacc(A);
			return;
		case RTI :
                        PullPCaP();
			return;
		case RTS :
			PullPC();
			return;
		case SBC :
			tmpBYTE = TUVal();
			tmpshortint = (short int) (A - tmpBYTE - (CCRC ^ true));
			if (tmpshortint < 0) UnsetC(); else SetC();

                        if(((A^tmpBYTE) & (A^(BYTE) tmpshortint)) & 0x80 ) SetV(); else UnsetV();

//                        tmpBYTE = (BYTE) (tmpshortint);
//                        tmpshortint = (short int) (((char) A) - ((char) tmpBYTE) - (CCRC ^ true));
//                        if ((tmpshortint < -128) || (tmpshortint > 127)) SetV(); else UnsetV();
//                        A = tmpBYTE;

                        A = (BYTE) tmpshortint;

			checkacc(A);
			return;
		case SEC :
			SetC();
			return;
		case SED :
			SetD();
			return;
		case SEI :
			SetI();
			return;
		case STA :
			MemoryTUEquals(A);
			return;
		case STX :
			MemoryTUEquals(X);
			return;
		case STY :
			MemoryTUEquals(Y);
			return;
		case TAX :
			X = A;
			checkacc(X);
			return;
		case TAY :
			Y = A;
			checkacc(Y);
			return;
		case TSX :
			X = SP;
			checkacc(X);
			return;
		case TXA :
			A = X;
			checkacc(A);
			return;
		case TXS :
			SP = X;
			return;
		case TYA :
			A = Y;
			checkacc(Y);
			return;
		default :
			return;
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

