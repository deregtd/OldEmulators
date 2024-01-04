//---------------------------------------------------------------------------
#ifndef Unit6805H
#define Unit6805H

#include "MTSForm.h"
//---------------------------------------------------------------------------
//Processor Type Definitions
//---------------------------------------------------------------------------
#define DebuggingTrace StartFrm->DebugDisplay1->Checked
#define DebuggingRegs StartFrm->Debug1->Checked
#define PCH (BYTE) (PC >> 8)
#define PCL (BYTE) PC

extern TStartFrm *StartFrm;
typedef unsigned char BYTE;
typedef unsigned short int LBYTE;
extern bool CPUMode;
extern BYTE Memory[0x2000];
extern int PC;
extern BYTE A, X, SP, P;
extern char TU2;
extern LBYTE SCIVectorGot;
//---------------------------------------------------------------------------
//System-Used Functions
//---------------------------------------------------------------------------
void exec6805(unsigned long opcode);
void reset6805();

BYTE MemoryTUGet();
void MemoryTUEquals(BYTE ta);

char * ToBin(BYTE tc);

#define TUVal()		(TUMode) ? MemoryTUGet() : TU
#define Branchif(F) if (F) PC += TU2;
#define Get16Bit(A) (short int) ((Memory[A] << 8) + Memory[A + 1])
#define bit0(F) (bool) (F & 1)
#define bit1(F) (bool) (F & 2)
#define bit2(F) (bool) (F & 4)
#define bit3(F) (bool) (F & 8)
#define bit4(F) (bool) (F & 16)
#define bit5(F) (bool) (F & 32)
#define bit6(F) (bool) (F & 64)
#define bit7(F) (bool) (F & 128)
#define checkacc(F) CCR.N = bit7(F); CCR.Z = !((bool) F);
#define GetCCR() (BYTE) ((CCR.H << 4) & (CCR.I << 3) & (CCR.N << 2) & (CCR.Z << 1) & CCR.C)
//---------------------------------------------------------------------------
//Definitions - TU Modes
//---------------------------------------------------------------------------
#define tmVal	false
#define tmAddr	true
//---------------------------------------------------------------------------
//Definitions - CPU Modes
//---------------------------------------------------------------------------
#define cmOFF		false
#define cmRUNNING	true
//---------------------------------------------------------------------------
//Definitions - EEPROM Modes
//---------------------------------------------------------------------------
#define eepRead		false
#define	eepWrite	true

#define eepInst		0
#define eepAddr		1
#define	eepCmd		2
//---------------------------------------------------------------------------
//Definitions - Register Addresses
//---------------------------------------------------------------------------
#define PortADataRegister 0x0000
#define PortBDataRegister 0x0001
#define PortCDataRegister 0x0002
#define PortDFixedInputRegister 0x0003
#define PortADataDirectionRegister 0x0004
#define PortBDataDirectionRegister 0x0005
#define PortCDataDirectionRegister 0x0006
#define SPIControlRegister 0x000A
#define SPIStatusRegister 0x000B
#define SPIDataIORegister 0x000C
#define SCIBaudRateRegister 0x000D
#define SCIControlRegister1 0x000E
#define SCIControlRegister2 0x000F
#define SCIStatusRegister 0x0010
#define SCIDataRegister 0x0011
#define TimerControlRegister 0x0012
#define TimerStatusRegister 0x0013
#define InputCaptureRegisterHigh 0x0014
#define InputCaptureRegisterLow 0x0015
#define OutputCompareRegisterHigh 0x0016
#define OutputCompareRegisterLow 0x0017
#define TimerCountRegisterHigh 0x0018
#define TimerCountRegisterLow 0x0019
#define AltCountRegisterHigh 0x001A
#define AltCountRegisterLow 0x001B
#define EPROMProgramRegister 0x001C
#define COPResetRegister 0x001D
#define COPControlRegister 0x001E

#define OptionRegister 0x1FDF
//---------------------------------------------------------------------------
//Definitions - PROM Vectors
//---------------------------------------------------------------------------
#define SPIVector 0x1FF4
#define SCIVector 0x1FF6
#define TimerVector 0x1FF8
#define IRQVector 0x1FFA
#define SWIVector 0x1FFC
#define ResetVector 0x1FFE
//---------------------------------------------------------------------------
//Definitions - Addressing Modes
//---------------------------------------------------------------------------
#define Imm		0 //#nn
#define Inh		1 //[nothing]
#define Ext		2 //nnnn
#define Dir		3 //nn
#define Ind		4 //,X
#define Id8		5 //nn,X
#define Id16	6 //nnnn,X
#define Rel		7 //nn
#define BTB		8 //nn, nn
#define NoA		9 //No Addressing Mode
//---------------------------------------------------------------------------
//Definitions - Opcodes
//---------------------------------------------------------------------------
#define NoO 0
#define ADCop	1
#define ADD	2
#define AND	3
#define ASL	4
#define ASLA 5
#define ASLX 6
#define ASR 7
#define ASRA 8
#define ASRX 9
#define BCC	10
#define BCLR0 11
#define BCLR1 12
#define BCLR2 13
#define BCLR3 14
#define BCLR4 15
#define BCLR5 16
#define BCLR6 17
#define BCLR7 18
#define BCS	19
#define BEQ 20
#define BHCC 21
#define BHCS 22
#define BHI 23
#define BHS 24
#define BIH 25
#define BIL 26
#define BIT 27
#define BLO 28
#define BLS 29
#define BMC 30
#define BMI	31
#define BMS 32
#define BNE	33
#define BPL	34
#define BRA 35
#define BRCLR0 36
#define BRCLR1 37
#define BRCLR2 38
#define BRCLR3 39
#define BRCLR4 40
#define BRCLR5 41
#define BRCLR6 42
#define BRCLR7 43
#define BRN 44
#define BRSET0 45
#define BRSET1 46
#define BRSET2 47
#define BRSET3 48
#define BRSET4 49
#define BRSET5 50
#define BRSET6 51
#define BRSET7 52
#define BSET0 53
#define BSET1 54
#define BSET2 55
#define BSET3 56
#define BSET4 57
#define BSET5 58
#define BSET6 59
#define BSET7 60
#define BSR 61
#define CLC	62
#define CLI	63
#define CLR 64
#define CLRA 65
#define CLRX 66
#define CMP	67
#define COM 68
#define COMA 69
#define COMX 70
#define CPX	71
#define DEC	72
#define DECA 73
#define DECX 74
#define EOR	75
#define INC	76
#define INCA 77
#define INCX 78
#define JMP	79
#define JSR	80
#define LDA	81
#define LDX	82
#define LSL 83
#define LSLA 84
#define LSLX 85
#define LSR	86
#define LSRA 87
#define LSRX 88
#define MUL 89
#define NEG 90
#define NEGA 91
#define NEGX 92
#define NOP	93
#define ORA	94
#define ROL	95
#define ROLA 96
#define ROLX 97
#define ROR	98
#define RORA 99
#define RORX 100
#define RSP 101
#define RTI	102
#define RTS	103
#define SBC	104
#define SEC	105
#define SEI	106
#define STA	107
#define STOP 108
#define STX	109
#define SUB 110
#define SWI 111
#define TAX	112
#define TST 113
#define TSTA 114
#define TSTX 115
#define TXA	116
#define WAIT 117
//---------------------------------------------------------------------------
//Internal 6805 Structures
//---------------------------------------------------------------------------
struct CCRSt {
	unsigned	C : 1;
	unsigned	Z : 1;
	unsigned	N : 1;
	unsigned	I : 1;
	unsigned	H : 1;
    int			  : 3;
    void MakeCCR(BYTE mf)
    { this->H = mf & 0x10; this->I = mf & 0x08; this->N = mf & 0x04; this->Z = mf & 0x02; this->C = mf & 0x01; }
	void UpdateDebug()
    {
		StartFrm->StatRegInfo->Caption = IntToHex(((this->H << 4) & (this->I << 3) & (this->N << 2) & (this->Z << 1) & this->C), 2);

		StartFrm->CarryCheck->Checked = this->C;
		StartFrm->ZeroCheck->Checked = this->Z;
		StartFrm->InterruptCheck->Checked = this->I;
		StartFrm->NegativeCheck->Checked = this->N;
		StartFrm->HalfCarryCheck->Checked = this->H;
    }
};
extern CCRSt CCR;
struct SCISt {
	BYTE InputBuffer[0x02];
	BYTE OutputBuffer[0x02];
    unsigned InputBufferBytes : 2;
    unsigned OutputBufferBytes : 2;
	void IRQ()
    {
		Memory[SP] = PCL;
		Memory[SP-1] = PCH;
		Memory[SP-2] = X;
		Memory[SP-3] = A;
		Memory[SP-4] = GetCCR();
		SP -= (BYTE) 5;
		CCR.I = true;
        PC = SCIVectorGot;
#ifndef Streamlined
		if (DebuggingTrace) dprint("SCI Interrupt!");
#endif
    }
	BYTE Get()
	{
		BYTE ToRet = this->InputBuffer[0];
		this->InputBuffer[0] = this->InputBuffer[1];
		this->InputBuffer[1] = 0x00;
		this->InputBufferBytes--;
#ifndef Streamlined
		if ((MIDIChat) && ((DebuggingRegs) || (DebuggingTrace))) StartFrm->MIDIChatInfo->Lines->Add(AnsiString("SCI Reciever: Buffer = ") + IntToHex(this->InputBuffer[0],2) + AnsiString(" ") + IntToHex(this->InputBuffer[1],2) + ", BufferBytes = " + AnsiString((int) this->InputBufferBytes));
#endif
        return(ToRet);
	}
	void Send(BYTE ts)
	{
		if (this->OutputBufferBytes == 0) { this->OutputBuffer[0] = ts; this->OutputBufferBytes++; }
		else if (this->OutputBufferBytes == 1) { this->OutputBuffer[1] = ts; this->OutputBufferBytes++; }
#ifndef Streamlined
		if ((MIDIChat) && ((DebuggingRegs) || (DebuggingTrace))) StartFrm->MIDIChatInfo->Lines->Add(AnsiString("SCI Transmitter: Buffer = ") + IntToHex(this->OutputBuffer[0],2) + AnsiString(" ") + IntToHex(this->OutputBuffer[1],2) + ", BufferBytes = " + AnsiString((int) this->OutputBufferBytes));
#endif
    }
	void Update()
    {
		if (this->OutputBufferBytes > 0) {
#ifndef Streamlined
			if (MIDIChat) StartFrm->MIDIChatInfo->Lines->Add(AnsiString("Out> ") + IntToHex(this->OutputBuffer[0],2));
#endif
			this->OutputBuffer[0] = this->OutputBuffer[1];
			this->OutputBuffer[1] = 0x00;
			this->OutputBufferBytes--;
        } else if ((bit7(Memory[SCIControlRegister2])) && (!CCR.I))
           	{ Memory[SCIStatusRegister] = 0x80; this->IRQ(); }

		if ((bit5(Memory[SCIControlRegister2])) && (!CCR.I) && (this->InputBufferBytes == 2))
           	{ Memory[SCIStatusRegister] = 0x20; this->IRQ(); }
    }
};
//---------------------------------------------------------------------------
#endif
