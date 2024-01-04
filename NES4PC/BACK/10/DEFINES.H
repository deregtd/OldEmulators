//---------------------------------------------------------------------------
#ifndef DefinesH
#define DefinesH

#define NewP

//---------------------------------------------------------------------------
//Speedup/Macro Definitions
//---------------------------------------------------------------------------
#define PCHi (BYTE) (PC >> 8)
#define PCLo (BYTE) PC
#define TUHi (BYTE) (TU >> 8)
#define TULo (BYTE) TU

#define WriteSRAM()	fseek(SRAMFileWr, 0, 0); fwrite(Mem.Main[0x6000], 0x2000, 1, SRAMFileWr);
#define ReadSRAM()	fseek(SRAMFileRd, 0, 0); fread(Mem.Main[0x6000], 1, 0x2000, SRAMFileRd);

#define PushPC() 	tmpLBYTE = (LBYTE) (PC - 1); Mem.Stack[SP] = (BYTE) (tmpLBYTE >> 8); Mem.Stack[SP - 1] = (BYTE) tmpLBYTE; SP -= (BYTE) 2;
#define PullPC()	PC = (LBYTE) (((Mem.Stack[SP+2] << 8) | Mem.Stack[SP + 1]) + 1); SP += (BYTE) 2;

#ifdef NewP

#define PushP()		Mem.Stack[SP] = P; SP--;
#define PullP()		SP++; P = Mem.Stack[SP];

#else

#define PushP()		Mem.Stack[SP] = CCR.GetCCR(); SP--;
#define PullP()		SP++; CCR.MakeCCR(Mem.Stack[SP]);

#endif

#define TUVal() (TUMode ? MemoryTUGet() : (BYTE) TU)
#define Get16Bit(Addrfit) (*Mem.Main[Addrfit+1] << 8) | *Mem.Main[Addrfit]
#define bit(Bytetodo,Bitnum) (bool) (Bytetodo & (1 << (Bitnum)))
#define bit0(Bytetodo) (bool) (Bytetodo & 1)
#define bit1(Bytetodo) (bool) (Bytetodo & 2)
#define bit2(Bytetodo) (bool) (Bytetodo & 4)
#define bit3(Bytetodo) (bool) (Bytetodo & 8)
#define bit4(Bytetodo) (bool) (Bytetodo & 16)
#define bit5(Bytetodo) (bool) (Bytetodo & 32)
#define bit6(Bytetodo) (bool) (Bytetodo & 64)
#define bit7(Bytetodo) (bool) (Bytetodo & 128)
#define bit8(Bytetodo) (bool) (Bytetodo & 256)
#define bit9(Bytetodo) (bool) (Bytetodo & 512)
#define bit10(Bytetodo) (bool) (Bytetodo & 1024)

#ifdef NewP

#define checkacc(Bytetodo)	if (bit7(Bytetodo)) SetN(); else UnsetN(); if (Bytetodo) UnsetZ(); else SetZ();

#else

#define checkacc(Bytetodo) CCR.N = bit7(Bytetodo); CCR.Z = (!Bytetodo);

#endif
//---------------------------------------------------------------------------
//Definitions - P Flags
//---------------------------------------------------------------------------
#define C_Flag  0x01
#define Z_Flag  0x02
#define I_Flag  0x04
#define D_Flag  0x08
#define B_Flag  0x10
//				0x20
#define V_Flag  0x40
#define N_Flag  0x80

#define C_DeFlag	0xFE
#define Z_DeFlag	0xFD
#define I_DeFlag	0xFB
#define D_DeFlag	0xF7
#define B_DeFlag	0xEF
//					0xDF
#define V_DeFlag	0xBF
#define N_DeFlag	0x7F

#ifdef NewP

#define SetC()	P |= C_Flag
#define SetZ()	P |= Z_Flag
#define SetI()	P |= I_Flag
#define SetD()	P |= D_Flag
#define SetB()	P |= B_Flag
#define SetV()	P |= V_Flag
#define SetN()	P |= N_Flag

#define UnsetC()	P &= C_DeFlag
#define UnsetZ()	P &= Z_DeFlag
#define UnsetI()	P &= I_DeFlag
#define UnsetD()	P &= D_DeFlag
#define UnsetB()	P &= B_DeFlag
#define UnsetV()	P &= V_DeFlag
#define UnsetN()	P &= N_DeFlag

#define CCRC	(P & C_Flag)
#define CCRZ	(bool) (P & Z_Flag)
#define CCRI	(bool) (P & I_Flag)
#define CCRD	(bool) (P & D_Flag)
#define CCRB	(bool) (P & B_Flag)
#define CCRV	(bool) (P & V_Flag)
#define CCRN	(bool) (P & N_Flag)

#else

#define SetC()	CCR.C = true
#define SetZ()	CCR.Z = true
#define SetI()	CCR.I = true
#define SetD()	CCR.D = true
#define SetB()	CCR.B = true
#define SetV()	CCR.V = true
#define SetN()	CCR.N = true

#define UnsetC()	CCR.C = false
#define UnsetZ()	CCR.Z = false
#define UnsetI()	CCR.I = false
#define UnsetD()	CCR.D = false
#define UnsetB()	CCR.B = false
#define UnsetV()	CCR.V = false
#define UnsetN()	CCR.N = false

#define CCRC	CCR.C
#define CCRZ    CCR.Z
#define CCRI    CCR.I
#define CCRD    CCR.D
#define CCRB    CCR.B
#define CCRV    CCR.V
#define CCRN	CCR.N

#endif
//---------------------------------------------------------------------------
//Definitions - TU Modes
//---------------------------------------------------------------------------
#define tmVal	false
#define tmAddr	true
//---------------------------------------------------------------------------
//Definitions - Register Addresses
//---------------------------------------------------------------------------
#define PPUCtrl1 0x2000
#define PPUCtrl2 0x2001
#define PPUStat 0x2002
#define SPRAddr 0x2003
#define SPRIO 0x2004
#define BgScroll 0x2005
#define VRAMAddr 0x2006
#define VRAMIO 0x2007

#define pAPUP1C1 0x4000
#define pAPUP1C2 0x4001
#define pAPUP1F1 0x4002
#define pAPUP1F2 0x4003
#define pAPUP2C1 0x4004
#define pAPUP2C2 0x4005
#define pAPUP2F1 0x4006
#define pAPUP2F2 0x4007
#define pAPUTC1 0x4008
#define pAPUTC2 0x4009
#define pAPUTF1 0x400A
#define pAPUTF2 0x400B
#define pAPUNC1 0x400C
#define pAPUNC2 0x400D
#define pAPUNF1 0x400E
#define pAPUNF2 0x400F
#define pAPUDMCC 0x4010
#define pAPUDMCV 0x4011
#define pAPUDMCA 0x4012
#define pAPUDMCDL 0x4013
#define SPRDMA 0x4014
#define pAPUStCh 0x4015
#define Joypad1 0x4016
#define Joypad2 0x4017
//---------------------------------------------------------------------------
//Definitions - PROM Vectors
//---------------------------------------------------------------------------
#define NMIVector 0xFFFA
#define ResetVector 0xFFFC
#define IRQVector 0xFFFE
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
//---------------------------------------------------------------------------
//Definitions - Opcodes
//---------------------------------------------------------------------------
#define ADC	0
#define AND	1
#define ASL	2
#define BCC	3
#define BCS	4
#define BEQ 5
#define BIT 6
#define BMI	7
#define BNE	8
#define BPL	9
#define BRK	10
#define BVC	11
#define BVS	12
#define CLC	13
#define CLD	14
#define CLI	15
#define CLV	16
#define CMP	17
#define CPX	18
#define CPY	19
#define DEC	20
#define DEX	21
#define DEY	22
#define EOR	23
#define INC	24
#define INX	25
#define INY	26
#define JMP	27
#define JSR	28
#define LDA	29
#define LDX	30
#define LDY	31
#define LSR	32
#define NOP	33
#define ORA	34
#define PHA	35
#define PHP	36
#define PLA	37
#define PLP	38
#define ROL	39
#define ROR	40
#define RTI	41
#define RTS	42
#define SBC	43
#define SEC	44
#define SED	45
#define SEI	46
#define STA	47
#define STX	48
#define STY	49
#define TAX	50
#define TAY	51
#define TSX	52
#define TXA	53
#define TXS	54
#define TYA	55

#define ASLA 56
#define LSRA 57
#define ROLA 58
#define RORA 59

#define ERO 60	//Error
//---------------------------------------------------------------------------
//Definitions - VRAM Mirroring
//---------------------------------------------------------------------------
#define MrNone 0, 0, 0, 0
#define MrHorz 0, 0, 2, 2
#define MrVert 0, 1, 0, 1
#define MrFour 0, 1, 2, 3
//---------------------------------------------------------------------------
//Definitions - Joypad Types
//---------------------------------------------------------------------------
#define jpJoypad 0
#define jpPaddle 1
#define jpZapper 2
#define jpQuadJoypad 3
#define jpRobot 4
#define jpPowerPad 5
//---------------------------------------------------------------------------
struct MemSt {
	unsigned char *Main[0x10001];

	unsigned char MainRAM[0x800];		//0x0000-0x1FFF
	unsigned char Stack[0x100];
	unsigned char RegLow[0x8];			//0x2000-0x3FFF
	unsigned char RegHigh[0x18];		//0x4000-0x4017
	unsigned char Expansion[0x2000];	//0x4018-0x5FFF
	unsigned char SRAM[0x2000];			//0x6000-0x7FFF
	unsigned char PRGROMLow[0x4000];	//0x8000-0xBFFF
	unsigned char PRGROMHigh[0x4000];	//0xC000-0xFFFF
	unsigned char Accum;

	unsigned char *PPU[0x4000];

	unsigned char PatternTable[0x2][0x1000];	//0x0000-0x1FFF
	unsigned char NameTable[0x4][0x3C0];		//0x2000- ...
	unsigned char AttributeTable[0x4][0x40];	//... 0x2FFF
	unsigned char ImagePalette[0x10];			//0x3F00- ...
	unsigned char SpritePalette[0x10];			//... 0x3FFF
	unsigned char VRAMAddrHigh;
	unsigned VRAMAddress : 14;
	bool VRAMAddrUsing;

	unsigned char Sprite[0x100];	//0x00-0xFF
	unsigned char SPRAddress;

	unsigned char BgScrollX;
	short int BgScrollY;
	bool BgScrollUsing;

	unsigned char PRGPages, CHRPages, MapperNum;
	short int PRGPagesA, CHRPagesA;
	short int PRGBitMask, CHRBitMask;
	short int PRGPageNum[4], CHRPageNum[8];
	short int PRGPageNumNew[4], CHRPageNumNew[8];
	unsigned char PRGPage[0x80][0x2000];
	unsigned char CHRPage[0x200][0x400];

	bool SRAMEnabled;

	void __fastcall SetupPointers()
	{
		for (int i=0;i<0x800;i++)
		{
			Main[i] = &MainRAM[i];
			Main[i+0x800] = &MainRAM[i];
			Main[i+0x1000] = &MainRAM[i];
			Main[i+0x1800] = &MainRAM[i];
		}
		for (int i=0x100;i<0x200;i++)
		{
			Main[i] = &Stack[i & 0xFF];
			Main[i+0x800] = &Stack[i & 0xFF];
			Main[i+0x1000] = &Stack[i & 0xFF];
			Main[i+0x1800] = &Stack[i & 0xFF];
		}
		for (int i=0x2000;i<0x4000;i++)
			Main[i] = &RegLow[i % 0x8];
		for (int i=0x4000;i<0x6000;i++)
			Main[i] = &RegHigh[(i-0x4000) % 0x18];
		for (int i=0x6000;i<0x8000;i++)
			Main[i] = &SRAM[i - 0x6000];
		for (int i=0x8000;i<0xC000;i++)
			Main[i] = &PRGROMLow[i - 0x8000];
		for (int i=0xC000;i<0x10000;i++)
			Main[i] = &PRGROMHigh[i - 0xC000];

		Main[0x10000] = &Accum;

		for (int i=0;i<0x1000;i++)
		{
			PPU[i] = &PatternTable[0][i];
			PPU[0x1000 | i] = &PatternTable[1][i];
        }
		for (int i=0x000;i<0x3C0;i++)
		{
			PPU[0x2000 + i] = &NameTable[0][i];
			PPU[0x2400 + i] = &NameTable[0][i];
			PPU[0x2800 + i] = &NameTable[0][i];
			PPU[0x2C00 + i] = &NameTable[0][i];
        }
		for (int i=0x3C0;i<0x400;i++)
		{
			PPU[0x2000 + i] = &AttributeTable[0][i - 0x3C0];
			PPU[0x2400 + i] = &AttributeTable[0][i - 0x3C0];
			PPU[0x2800 + i] = &AttributeTable[0][i - 0x3C0];
			PPU[0x2C00 + i] = &AttributeTable[0][i - 0x3C0];
		}
		for (int i=0x3000;i<0x3F00;i++)
			PPU[i] = PPU[i - 0x1000];
		for (int i=0x3F00;i<0x4000;i++)
		{
			if (!(i & 0x10)) { PPU[i] = &ImagePalette[i & 0x0F]; }
			if (i & 0x10) { PPU[i] = &SpritePalette[i & 0x0F]; }
			if (!(i & 0x0F)) { PPU[i] = &ImagePalette[0]; }
//			if (!(i & 0x03)) { PPU[i] = &ImagePalette[0]; }
		}
	}
	void __fastcall UpdateCHRPRGPointers()
	{
		UpdateCHRPointers();
		UpdatePRGPointers();
	}
	void __fastcall UpdateCHRPointers()
	{
		if (!CHRPageNum) return;

		if (CHRPageNum[0] != CHRPageNumNew[0])
			memcpy(&PatternTable[0][0], &CHRPage[CHRPageNumNew[0]][0], 0x400);
		if (CHRPageNum[1] != CHRPageNumNew[1])
			memcpy(&PatternTable[0][0x400], &CHRPage[CHRPageNumNew[1]][0], 0x400);
		if (CHRPageNum[2] != CHRPageNumNew[2])
			memcpy(&PatternTable[0][0x800], &CHRPage[CHRPageNumNew[2]][0], 0x400);
		if (CHRPageNum[3] != CHRPageNumNew[3])
			memcpy(&PatternTable[0][0xC00], &CHRPage[CHRPageNumNew[3]][0], 0x400);
		if (CHRPageNum[4] != CHRPageNumNew[4])
			memcpy(&PatternTable[1][0], &CHRPage[CHRPageNumNew[4]][0], 0x400);
		if (CHRPageNum[5] != CHRPageNumNew[5])
			memcpy(&PatternTable[1][0x400], &CHRPage[CHRPageNumNew[5]][0], 0x400);
		if (CHRPageNum[6] != CHRPageNumNew[6])
			memcpy(&PatternTable[1][0x800], &CHRPage[CHRPageNumNew[6]][0], 0x400);
		if (CHRPageNum[7] != CHRPageNumNew[7])
			memcpy(&PatternTable[1][0xC00], &CHRPage[CHRPageNumNew[7]][0], 0x400);
		for (unsigned char i=0;i<8;i++)
			CHRPageNum[i] = CHRPageNumNew[i];
	}
	void __fastcall UpdatePRGPointers()
	{
		if (PRGPageNum[0] != PRGPageNumNew[0])
			memcpy(&PRGROMLow[0],&PRGPage[PRGPageNumNew[0]][0],0x2000);
		if (PRGPageNum[1] != PRGPageNumNew[1])
			memcpy(&PRGROMLow[0x2000],&PRGPage[PRGPageNumNew[1]][0],0x2000);
		if (PRGPageNum[2] != PRGPageNumNew[2])
			memcpy(&PRGROMHigh[0],&PRGPage[PRGPageNumNew[2]][0],0x2000);
		if (PRGPageNum[3] != PRGPageNumNew[3])
			memcpy(&PRGROMHigh[0x2000],&PRGPage[PRGPageNumNew[3]][0],0x2000);
		for (unsigned char i=0;i<4;i++)
			PRGPageNum[i] = PRGPageNumNew[i];
	}
	void UpdateNameTablePointers(unsigned char a, unsigned char b, unsigned char c, unsigned char d)
	{
		for (int i=0x000;i<0x3C0;i++)
		{
			PPU[0x2000 + i] = &NameTable[a][i];
			PPU[0x2400 + i] = &NameTable[b][i];
			PPU[0x2800 + i] = &NameTable[c][i];
			PPU[0x2C00 + i] = &NameTable[d][i];
		}
		for (int i=0x3C0;i<0x400;i++)
		{
			PPU[0x2000 + i] = &AttributeTable[a][i & 0x3F];
			PPU[0x2400 + i] = &AttributeTable[b][i & 0x3F];
			PPU[0x2800 + i] = &AttributeTable[c][i & 0x3F];
			PPU[0x2C00 + i] = &AttributeTable[d][i & 0x3F];
		}
	}
};
//---------------------------------------------------------------------------
#endif
