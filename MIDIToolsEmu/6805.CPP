//---------------------------------------------------------------------------
//#pragma inline
//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "MTSForm.h"
#include "6805.h"
#include "OtherChips.h"
//---------------------------------------------------------------------------
//Variables
//---------------------------------------------------------------------------
extern TStartFrm *StartFrm;
BYTE tmp;
LBYTE tmpLBYTE;
bool tmpbool;
bool IRQPin = true, CPUMode = cmOFF, TUMode;
BYTE Memory[0x2000], *TB, *NB, *NB2;
BYTE A, X, SP, P;
int PC, TU, Clockticks, Clocktickstmp;
char TU2;
LBYTE ResetVectorGot, SPIVectorGot, SCIVectorGot, TimerVectorGot;
LBYTE IRQVectorGot, SWIVectorGot;
//---------------------------------------------------------------------------
//Information Arrays
//---------------------------------------------------------------------------
BYTE addressmode[256]= { BTB,BTB,BTB,BTB,BTB,BTB,BTB,BTB,BTB,BTB,BTB,BTB,BTB,BTB,BTB,BTB,Dir,Dir,Dir,Dir,Dir,Dir,Dir,Dir,Dir,Dir,Dir,Dir,Dir,Dir,Dir,Dir,Rel,Rel,Rel,Rel,Rel,Rel,Rel,Rel,Rel,Rel,Rel,Rel,Rel,Rel,Rel,Rel,Dir,NoA,NoA,Dir,Dir,NoA,Dir,Dir,Dir,Dir,Dir,NoA,Dir,Dir,NoA,Dir,Inh,NoA,Inh,Inh,Inh,NoA,Inh,Inh,Inh,Inh,Inh,NoA,Inh,Inh,NoA,Inh,Inh,NoA,NoA,Inh,Inh,NoA,Inh,Inh,Inh,Inh,Inh,NoA,Inh,Inh,NoA,Inh,Id8,NoA,NoA,Id8,Id8,NoA,Id8,Id8,Id8,Id8,Id8,NoA,Id8,Id8,NoA,Id8,Ind,NoA,NoA,Ind,Ind,NoA,Ind,Ind,Ind,Ind,Ind,NoA,Ind,Ind,NoA,Ind,Inh,Inh,NoA,Inh,NoA,NoA,NoA,NoA,NoA,NoA,NoA,NoA,NoA,NoA,Inh,Inh,NoA,NoA,NoA,NoA,NoA,NoA,NoA,Inh,Inh,Inh,Inh,Inh,Inh,Inh,NoA,Inh,Imm,Imm,Imm,Imm,Imm,Imm,Imm,NoA,Imm,Imm,Imm,Imm,NoA,Rel,Imm,NoA,Dir,Dir,Dir,Dir,Dir,Dir,Dir,Dir,Dir,Dir,Dir,Dir,Dir,Dir,Dir,Dir,Ext,Ext,Ext,Ext,Ext,Ext,Ext,Ext,Ext,Ext,Ext,Ext,Ext,Ext,Ext,Ext,Id16,Id16,Id16,Id16,Id16,Id16,Id16,Id16,Id16,Id16,Id16,Id16,Id16,Id16,Id16,Id16,Id8,Id8,Id8,Id8,Id8,Id8,Id8,Id8,Id8,Id8,Id8,Id8,Id8,Id8,Id8,Id8,Ind,Ind,Ind,Ind,Ind,
						Ind,Ind,Ind,Ind,Ind,Ind,Ind,Ind,Ind,Ind,Ind};
BYTE instruc[256]=	{	BRSET0,BRCLR0,BRSET1,BRCLR1,BRSET2,BRCLR2,BRSET3,BRCLR4,BRSET4,BRCLR4,BRSET5,BRCLR5,BRSET6,BRCLR6,BRSET7,BRCLR7,BSET0,BCLR0,BSET1,BCLR1,BSET2,BCLR2,BSET3,BCLR3,BSET4,BCLR4,BSET5,BCLR5,BSET6,BCLR6,BSET7,BCLR7,BRA,BRN,BHI,BLS,BCC,BCS,BNE,BEQ,BHCC,BHCS,BPL,BMI,BMC,BMS,BIL,BIH,NEG,NoO,NoO,COM,LSR,NoO,ROR,ASR,ASL,ROL,DEC,NoO,INC,TST,NoO,CLR,NEGA,NoO,MUL,COMA,LSRA,NoO,RORA,ASRA,ASLA,ROLA,DECA,NoO,INCA,TSTA,NoO,CLRA,NEGX,NoO,NoO,COMX,LSRX,NoO,RORX,ASRX,ASLX,ROLX,DECX,NoO,INCX,TSTX,NoO,CLRX,NEG,NoO,NoO,COM,LSR,NoO,ROR,ASR,ASL,ROL,DEC,NoO,INC,TST,NoO,CLR,NEG,NoO,NoO,COM,LSR,NoO,ROR,ASR,ASL,ROL,DEC,NoO,INC,TST,NoO,CLR,
						RTI,RTS,NoO,SWI,NoO,NoO,NoO,NoO,NoO,NoO,NoO,NoO,NoO,NoO,STOP,WAIT,NoO,NoO,NoO,NoO,NoO,NoO,NoO,TAX,CLC,SEC,CLI,SEI,RSP,NOP,NoO,TXA,SUB,CMP,SBC,CPX,AND,BIT,LDA,NoO,EOR,ADCop,ORA,ADD,NoO,BSR,LDX,NoO,SUB,CMP,SBC,CPX,AND,BIT,LDA,STA,EOR,ADCop,ORA,ADD,JMP,JSR,LDX,STX,SUB,CMP,SBC,CPX,AND,BIT,LDA,STA,EOR,ADCop,ORA,ADD,JMP,JSR,LDX,STX,SUB,CMP,SBC,CPX,AND,BIT,LDA,STA,EOR,ADCop,ORA,ADD,JMP,JSR,LDX,STX,SUB,CMP,SBC,CPX,AND,BIT,LDA,STA,EOR,ADCop,ORA,ADD,JMP,JSR,LDX,STX,SUB,CMP,SBC,CPX,AND,BIT,LDA,STA,EOR,ADCop,ORA,ADD,JMP,JSR,LDX,STX };
unsigned long ticks[256]=        {       5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,5,1,1,5,5,1,5,5,5,5,5,1,5,4,1,5,3,1,11,3,3,1,3,3,3,3,3,1,3,3,1,3,3,1,1,3,3,1,3,3,3,3,3,1,3,3,1,3,6,1,1,6,6,1,6,6,6,6,6,1,6,5,1,6,5,1,1,5,5,1,5,5,5,5,5,1,5,4,1,5,9,6,1,11,1,1,1,1,1,1,1,1,1,1,2,2,1,1,1,1,1,1,1,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,2,1,2,2,2,2,1,6,2,1,3,3,3,3,3,3,3,4,3,3,3,3,2,5,3,4,4,4,4,4,4,4,4,5,4,4,4,4,3,6,4,5,5,5,5,5,5,5,5,6,5,5,5,5,4,7,5,6,4,4,4,4,4,4,4,5,4,4,4,4,3,6,4,5,3,3,3,3,3,3,3,4,3,3,3,3,2,5,3,4 };
BYTE bytes[256]=	{	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2,1,2,2,2,2,2,1,2,2,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,2,2,1,2,2,2,2,2,1,2,2,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,1,2,2,2,2,1,2,2,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 };
char * Mn[118] = { "None","ADC","ADD","AND","ASL","ASLA","ASLX","ASR","ASRA","ASRX","BCC","BCLR 0,","BCLR 1,","BCLR 2,","BCLR 3,","BCLR 4,","BCLR 5,","BCLR 6,","BCLR 7,","BCS","BEQ","BHCC","BHCS","BHI","BHS","BIH","BIL","BIT","BLO","BLS","BMC","BMI","BMS","BNE","BPL","BRA","BRCLR 0,","BRCLR 1,","BRCLR 2,","BRCLR 3,","BRCLR 4,","BRCLR 5,","BRCLR 6,","BRCLR 7,","BRN","BRSET 0,","BRSET 1,","BRSET 2,","BRSET 3,","BRSET 4,","BRSET 5,","BRSET 6,","BRSET 7,","BSET 0,","BSET 1,","BSET 2,","BSET 3,","BSET 4,","BSET 5,","BSET 6,","BSET 7,","BSR","CLC","CLI","CLR","CLRA","CLRX","CMP","COM","COMA","COMX","CPX","DEC","DECA","DECX","EOR","INC","INCA","INCX","JMP","JSR","LDA","LDX","LSL","LSLA","LSLX","LSR","LSRA","LSRX","MUL","NEG","NEGA","NEGX","NOP","ORA","ROL","ROLA","ROLX","ROR","RORA","RORX","RSP","RTI","RTS","SBC","SEC","SEI","STA","STOP","STX","SUB","SWI","TAX","TST","TSTA","TSTX","TXA","WAIT" };
char * RegInfo[0x20] = { "Port A Data", "Port B Data", "Port C Data", "Port D Fixed Input", "Port A Data Direction", "Port B Data Direction", "Port C Data Direction", "Unused", "Unused", "Unused", "SPI Control", "SPI Status", "SPI Data I/O", "SCI Baud Rate", "SCI Control 1", "SCI Control 2", "SCI Status", "SCI Data", "Timer Control", "Timer Status", "Input Capture (High)", "Input Capture (Low)", "Output Compare (High)", "Output Compare (Low)", "Timer Count (High)", "Timer Count (Low)", "Alternate Count (High)", "Alternate Count (Low)", "EPROM Program", "COP Reset", "COP Control", "Unused" };
//---------------------------------------------------------------------------
CCRSt CCR; SCISt SCI; LEDSt LED; LCDSt LCD; EEPROMSt EEPROM; ADCSt ADC; SwitchesSt Switches;
//---------------------------------------------------------------------------
//Memory Accessing Commands
//---------------------------------------------------------------------------
BYTE MemoryTUGet()
{
		BYTE ToRet;
#ifndef Streamlined
		switch (TU) {
			case PortBDataRegister :
				ToRet = (BYTE) (!bit0(Memory[PortADataRegister]) << 7);
				break;
			case PortCDataRegister :
				ToRet = Switches.TVal;
				break;
			case SPIDataIORegister :
	            if (bit7(Memory[PortADataRegister]) == false) {
					ToRet = ADC.Get();
				}
				else if (bit5(Memory[PortADataRegister]) == false) {
					ToRet = EEPROM.Read();
				} else {
					ToRet = 0;
                }
				break;
			case SPIStatusRegister :
				ToRet = Memory[SPIStatusRegister];
				Memory[SPIStatusRegister] = 0;
				break;
			case SCIStatusRegister :
				ToRet = Memory[SCIStatusRegister];
				break;
			case SCIDataRegister :
                ToRet = SCI.Get();
				break;
			default :
				ToRet = Memory[TU];
				break;
		};
		if (DebuggingTrace)
		{
			if (TU < 0x0020) dprint(AnsiString("        RegRead: ") + AnsiString(RegInfo[TU]) + AnsiString(": ") + IntToHex(ToRet,2));
			if (TU == 0x1FDF) dprint(AnsiString("        RegRead: Option Register: ") + IntToHex(ToRet,2));
		}
        return(ToRet);
#else
		switch (TU) {
			case PortBDataRegister :
				return((BYTE) (!bit0(Memory[PortADataRegister]) << 7));
			case PortCDataRegister :
				return(Switches.TVal);
			case SPIDataIORegister :
	            if (bit7(Memory[PortADataRegister]) == false) {
					return(ADC.Get());
				} else if (bit5(Memory[PortADataRegister]) == false) {
					return(EEPROM.Read());
				} else {
					return(0);
                }
			case SPIStatusRegister :
				ToRet = Memory[SPIStatusRegister];
				Memory[SPIStatusRegister] = 0;
                return(ToRet);
			case SCIStatusRegister :
				return(Memory[SCIStatusRegister]);
			case SCIDataRegister :
                return(SCI.Get());
			default :
				return(Memory[TU]);
		};
#endif
}

void MemoryTUEquals(BYTE ta)
{
#ifndef Streamlined
		if (DebuggingTrace)
		{
			if (TU < 0x0020) dprint(AnsiString("        RegWrite: ") + AnsiString(RegInfo[TU]) + AnsiString(": ") + AnsiString(ToBin(ta)));
		    if (TU == 0x1FDF) dprint(AnsiString("        RegWrite: Option Register: ") + AnsiString(ToBin(ta)));
		}
#endif
	    switch (TU) {
			case PortBDataRegister :
				if (bit2(Memory[PortADataRegister])) { LCD.Data(ta); return; } //DR (Data)
				else { LCD.Instruction(ta); return; } //IR (Instruction)
			case SPIDataIORegister :
				if (!bit6(Memory[PortADataRegister])) {
					EEPROM.Instruction(ta);
				} else if (bit7(Memory[PortADataRegister]) == false) {
 					if (ta == 0xC0) ADC.Channel = 0;		//Chan 0
					if (ta == 0xE0) ADC.Channel = 1;		//Chan 1
 					if (ta == 0xD0) ADC.Channel = 2;		//Chan 2
 					if (ta == 0xF0) ADC.Channel = 3;		//Chan 3
				} else {
					LED.Byte1 ^= true;
					if (LED.Byte1) { LED.SetLow(ta); } else { LED.SetHi(ta); }
				}
				Memory[SPIStatusRegister] |= 0x80;
				return;
			case SCIDataRegister :
				SCI.Send(ta);
				return;
			default :
				Memory[TU] = ta;
				return;
		};
}
//---------------------------------------------------------------------------
//6805 General Commands
//---------------------------------------------------------------------------
void reset6805()
{	A = 0; X = 0; SP = 0xFF; Clockticks = 0;
	CCR.C = false; CCR.Z = false; CCR.N = false; CCR.I = true; CCR.H = false;
	PC = ResetVectorGot;
	LCD.Clear();
	SCI.InputBuffer[0] = 0x00; SCI.InputBuffer[1] = 0x00; SCI.InputBufferBytes = 0;
}

void exec6805(unsigned long opcode)
{
	Clocktickstmp -= ticks[opcode];
/*	asm {
		mov eax, [opcode]
		mov eax, dword ptr [ticks + eax]
		sub dword ptr [Clocktickstmp], eax
	}*/

#ifndef Streamlined
	if (DebuggingTrace)
    {
		Application->ProcessMessages();
		TB = &Memory[PC];
		switch (addressmode[opcode]) {
    		case Inh:
				dprint(IntToHex(PC,4) + AnsiString("    ") + IntToHex(*TB,2) + AnsiString("        ") + AnsiString(Mn[instruc[*TB]])); break;
			case Imm:
				NB = &Memory[PC+1];
				dprint(IntToHex(PC,4) + AnsiString("    ") + IntToHex(*TB,2) + IntToHex(*NB,2) + AnsiString("      ") + AnsiString(Mn[instruc[*TB]]) + AnsiString(" #$") + IntToHex(*NB,2)); break;
			case Ext:
				NB = &Memory[PC+1];
				NB2 = &Memory[PC+2];
				dprint(IntToHex(PC,4) + AnsiString("    ") + IntToHex(*TB,2) + IntToHex(*NB,2) + IntToHex(*NB2,2) + AnsiString("    ") + AnsiString(Mn[instruc[*TB]]) + AnsiString(" $") + IntToHex(*NB,2) + IntToHex(*NB2,2)); break;
			case Dir:
				NB = &Memory[PC+1];
				dprint(IntToHex(PC,4) + AnsiString("    ") + IntToHex(*TB,2) + IntToHex(*NB,2) + AnsiString("      ") + AnsiString(Mn[instruc[*TB]]) + AnsiString(" $") + IntToHex(*NB,2)); break;
			case Ind:
				dprint(IntToHex(PC,4) + AnsiString("    ") + IntToHex(*TB,2) + AnsiString("        ") + AnsiString(Mn[instruc[*TB]]) + AnsiString(", X")); break;
			case Id8:
				NB = &Memory[PC+1];
				dprint(IntToHex(PC,4) + AnsiString("    ") + IntToHex(*TB,2) + IntToHex(*NB,2) + AnsiString("      ") + AnsiString(Mn[instruc[*TB]]) + AnsiString(" $") + IntToHex(*NB,2) + AnsiString(",X")); break;
			case Id16:
				NB = &Memory[PC+1];
				NB2 = &Memory[PC+2];
				dprint(IntToHex(PC,4) + AnsiString("    ") + IntToHex(*TB,2) + IntToHex(*NB,2) + IntToHex(*NB2,2) + AnsiString("    ") + AnsiString(Mn[instruc[*TB]]) + AnsiString(" $") + IntToHex(*NB,2) + IntToHex(*NB2,2) + AnsiString(",X")); break;
			case Rel:
				NB = &Memory[PC+1];
				dprint(IntToHex(PC,4) + AnsiString("    ") + IntToHex(*TB,2) + IntToHex(*NB,2) + AnsiString("      ") + AnsiString(Mn[instruc[*TB]]) + AnsiString(" $") + IntToHex(*NB,2)); break;
			case BTB:
				NB = &Memory[PC+1];
				NB2 = &Memory[PC+2];
				dprint(IntToHex(PC,4) + AnsiString("    ") + IntToHex(*TB,2) + IntToHex(*NB,2) + IntToHex(*NB2,2) + AnsiString("    ") + AnsiString(Mn[instruc[*TB]]) + AnsiString(" $") + IntToHex(*NB,2) + AnsiString(", $") + IntToHex(*NB2,2)); break;
			case NoA:
				dprint(IntToHex(PC,4) + AnsiString("    ") + IntToHex(*TB,2) + AnsiString("        Illegal!")); break;
		}
    }
#endif

	switch (opcode) {
//Bit Test Branch
		case 0x00 :
			TU = Memory[PC+1];
			CCR.C = bit0(MemoryTUGet());
			if (CCR.C) PC += ((char) (Memory[PC+2]));
			PC += 3;
			break;
		case 0x01 :
			TU = Memory[PC+1];
			CCR.C = bit0(MemoryTUGet());
			if (!CCR.C) PC += ((char) (Memory[PC+2]));
			PC += 3;
			break;
		case 0x02 :
			TU = Memory[PC+1];
			CCR.C = bit1(MemoryTUGet());
			if (CCR.C) PC += ((char) (Memory[PC+2]));
			PC += 3;
			break;
		case 0x03 :
			TU = Memory[PC+1];
			CCR.C = bit1(MemoryTUGet());
			if (!CCR.C) PC += ((char) (Memory[PC+2]));
			PC += 3;
			break;
		case 0x04 :
			TU = Memory[PC+1];
			CCR.C = bit2(MemoryTUGet());
			if (CCR.C) PC += ((char) (Memory[PC+2]));
			PC += 3;
			break;
		case 0x05 :
			TU = Memory[PC+1];
			CCR.C = bit2(MemoryTUGet());
			if (!CCR.C) PC += ((char) (Memory[PC+2]));
			PC += 3;
			break;
		case 0x06 :
			TU = Memory[PC+1];
			CCR.C = bit3(MemoryTUGet());
			if (CCR.C) PC += ((char) (Memory[PC+2]));
			PC += 3;
			break;
		case 0x07 :
			TU = Memory[PC+1];
			CCR.C = bit3(MemoryTUGet());
			if (!CCR.C) PC += ((char) (Memory[PC+2]));
			PC += 3;
			break;
		case 0x08 :
			TU = Memory[PC+1];
			CCR.C = bit4(MemoryTUGet());
			if (CCR.C) PC += ((char) (Memory[PC+2]));
			PC += 3;
			break;
		case 0x09 :
			TU = Memory[PC+1];
			CCR.C = bit4(MemoryTUGet());
			if (!CCR.C) PC += ((char) (Memory[PC+2]));
			PC += 3;
			break;
		case 0x0A :
			TU = Memory[PC+1];
			CCR.C = bit5(MemoryTUGet());
			if (CCR.C) PC += ((char) (Memory[PC+2]));
			PC += 3;
			break;
		case 0x0B :
			TU = Memory[PC+1];
			CCR.C = bit5(MemoryTUGet());
			if (!CCR.C) PC += ((char) (Memory[PC+2]));
			PC += 3;
			break;
		case 0x0C :
			TU = Memory[PC+1];
			CCR.C = bit6(MemoryTUGet());
			if (CCR.C) PC += ((char) (Memory[PC+2]));
			PC += 3;
			break;
		case 0x0D :
			TU = Memory[PC+1];
			CCR.C = bit6(MemoryTUGet());
			if (!CCR.C) PC += ((char) (Memory[PC+2]));
			PC += 3;
			break;
		case 0x0E :
			TU = Memory[PC+1];
			CCR.C = bit7(MemoryTUGet());
			if (CCR.C) PC += ((char) (Memory[PC+2]));
			PC += 3;
			break;
		case 0x0F :
			TU = Memory[PC+1];
			CCR.C = bit7(MemoryTUGet());
			if (!CCR.C) PC += ((char) (Memory[PC+2]));
			PC += 3;
			break;
//Bit Set/Clear
		case 0x10 :
			TU = Memory[PC+1];
			MemoryTUEquals(Memory[TU] | (BYTE) 0x01);
			PC += 2;
			break;
		case 0x11 :
			TU = Memory[PC+1];
			MemoryTUEquals(Memory[TU] & (BYTE) 0xFE);
			PC += 2;
			break;
		case 0x12 :
			TU = Memory[PC+1];
			MemoryTUEquals(Memory[TU] | (BYTE) 0x02);
			PC += 2;
			break;
		case 0x13 :
			TU = Memory[PC+1];
			MemoryTUEquals(Memory[TU] & (BYTE) 0xFD);
			PC += 2;
			break;
		case 0x14 :
			TU = Memory[PC+1];
			MemoryTUEquals(Memory[TU] | (BYTE) 0x04);
			PC += 2;
			break;
		case 0x15 :
			TU = Memory[PC+1];
			MemoryTUEquals(Memory[TU] & (BYTE) 0xFB);
			PC += 2;
			break;
		case 0x16 :
			TU = Memory[PC+1];
			MemoryTUEquals(Memory[TU] | (BYTE) 0x08);
			PC += 2;
			break;
		case 0x17 :
			TU = Memory[PC+1];
			MemoryTUEquals(Memory[TU] & (BYTE) 0xF7);
			PC += 2;
			break;
		case 0x18 :
			TU = Memory[PC+1];
			MemoryTUEquals(Memory[TU] | (BYTE) 0x10);
			PC += 2;
			break;
		case 0x19 :
			TU = Memory[PC+1];
			MemoryTUEquals(Memory[TU] & (BYTE) 0xEF);
			PC += 2;
			break;
		case 0x1A :
			TU = Memory[PC+1];
			MemoryTUEquals(Memory[TU] | (BYTE) 0x20);
			PC += 2;
			break;
		case 0x1B :
			TU = Memory[PC+1];
			MemoryTUEquals(Memory[TU] & (BYTE) 0xDF);
			PC += 2;
			break;
		case 0x1C :
			TU = Memory[PC+1];
			MemoryTUEquals(Memory[TU] | (BYTE) 0x40);
			PC += 2;
			break;
		case 0x1D :
			TU = Memory[PC+1];
			MemoryTUEquals(Memory[TU] & (BYTE) 0xBF);
			PC += 2;
			break;
		case 0x1E :
			TU = Memory[PC+1];
			MemoryTUEquals(Memory[TU] | (BYTE) 0x80);
			PC += 2;
			break;
		case 0x1F :
			TU = Memory[PC+1];
			MemoryTUEquals(Memory[TU] & (BYTE) 0x7F);
			PC += 2;
			break;
//Branch
		case 0x20 :	//BRA
			PC += 2 + (char) (Memory[PC+1]);
			break;
		case 0x21 :	//BRN
			PC += 2;
			break;
		case 0x22 :	//BHI
			TU2 = (char) (Memory[PC+1]);
			Branchif(!CCR.C && !CCR.Z);
			PC += 2;
			break;
		case 0x23 :	//BLS
			TU2 = (char) (Memory[PC+1]);
			Branchif(CCR.C || CCR.Z);
			PC += 2;
			break;
		case 0x24 :	//BCC
			TU2 = (char) (Memory[PC+1]);
			Branchif(!CCR.C);
			PC += 2;
			break;
		case 0x25 :	//BCS
			TU2 = (char) (Memory[PC+1]);
			Branchif(CCR.C);
			PC += 2;
			break;
		case 0x26 :	//BNE
			TU2 = (char) (Memory[PC+1]);
			Branchif(!CCR.Z);
			PC += 2;
			break;
		case 0x27 :	//BEQ
			TU2 = (char) (Memory[PC+1]);
			Branchif(CCR.Z);
			PC += 2;
			break;
		case 0x28 :	//BHCC
			TU2 = (char) (Memory[PC+1]);
			Branchif(!CCR.H);
			PC += 2;
			break;
		case 0x29 :	//BHCS
			TU2 = (char) (Memory[PC+1]);
			Branchif(CCR.H);
			PC += 2;
			break;
		case 0x2A :	//BPL
			TU2 = (char) (Memory[PC+1]);
			Branchif(!CCR.N);
			PC += 2;
			break;
		case 0x2B :	//BMI
			TU2 = (char) (Memory[PC+1]);
			Branchif(CCR.N);
			PC += 2;
			break;
		case 0x2C :	//BMC
			TU2 = (char) (Memory[PC+1]);
			Branchif(!CCR.I);
			PC += 2;
			break;
		case 0x2D :	//BMS
			TU2 = (char) (Memory[PC+1]);
			Branchif(CCR.I);
			PC += 2;
			break;
		case 0x2E :	//BIL
			PC += 2;
			break;
		case 0x2F :	//BIH
			PC += 2 + (char) (Memory[PC+1]);
			break;
//Read/Modify/Write
		case 0x30 : //NEG
			TU = Memory[PC+1];
//			CCR.C = (bool) (Memory[TU]);
			if ((Memory[TU] != 0x80) && (Memory[TU] != 0x00))
//			if (Memory[TU] & 0x7F)
			{ 	CCR.C = true; Memory[TU] = (BYTE) (Memory[TU] ^ 0x80); } else { CCR.C = false; }
			checkacc(Memory[TU]);
			PC += 2;
			break;
		case 0x40 : //NEGA
//			CCR.C = (bool) A;
			if ((A != 0x80) && (A != 0x00))
//			if (A & 0x7F)
			{ 	CCR.C = true; A = (BYTE) (A ^ 0x80); } else { CCR.C = false; }
			checkacc(A);
			PC += 1;
			break;
		case 0x50 : //NEGX
//			CCR.C = (bool) X;
			if ((X != 0x80) && (X != 0x00))
//			if (X & 0x7F)
			{ 	CCR.C = true; X = (BYTE) (X ^ 0x80); } else { CCR.C = false; }
			checkacc(X);
			PC += 1;
			break;
		case 0x60 : //NEG
			TU = Memory[PC+1] + X;
//			CCR.C = (bool) (Memory[TU]);
			if ((Memory[TU] != 0x80) && (Memory[TU] != 0x00))
//			if (Memory[TU] & 0x7F)
			{ 	CCR.C = true; Memory[TU] = (BYTE) (Memory[TU] ^ 0x80); } else { CCR.C = false; }
			checkacc(Memory[TU]);
			PC += 2;
			break;
		case 0x70 : //NEG
//			CCR.C = (bool) (Memory[X]);
			if ((Memory[X] != 0x80) && (Memory[X] != 0x00))
//			if (Memory[X] & 0x7F)
			{ 	CCR.C = true; Memory[X] = (BYTE) (Memory[X] ^ 0x80); } else { CCR.C = false; }
			checkacc(Memory[X]);
			PC += 1;
			break;

		case 0x33 : //COM
			TU = Memory[PC+1];
			Memory[TU] = (BYTE) ~Memory[TU];
			CCR.C = true;
			checkacc(Memory[TU]);
			PC += 2;
			break;
		case 0x43 : //COMA
			A = (BYTE) ~A;
			CCR.C = true;
			checkacc(A);
			PC += 1;
        	break;
        case 0x53 : //COMX
			X = (BYTE) ~X;
			CCR.C = true;
			checkacc(X);
			PC += 1;
        	break;
		case 0x63 : //COM
			TU = Memory[PC+1] + X;
			Memory[TU] = (BYTE) ~Memory[TU];
			CCR.C = true;
			checkacc(Memory[TU]);
			PC += 2;
        	break;
        case 0x73 : //COM
			TU = X;
			Memory[TU] = (BYTE) ~Memory[TU];
			CCR.C = true;
			checkacc(Memory[TU]);
			PC += 1;
        	break;

        case 0x34 : //LSR
			TU = Memory[PC+1];
			CCR.C = bit0(Memory[TU]);
			Memory[TU] >>= 1;
			CCR.N = false; CCR.Z = (bool) (Memory[TU]);
			PC += 2;
        	break;
        case 0x44 : //LSRA
			CCR.C = bit0(A);
			A >>= 1;
			CCR.N = false; CCR.Z = (bool) (A);
			PC += 1;
        	break;
        case 0x54 : //LSRX
			CCR.C = bit0(X);
			X >>= 1;
			CCR.N = false; CCR.Z = (bool) (X);
			PC += 1;
        	break;
		case 0x64 : //LSR
			TU = Memory[PC+1] + X;
			CCR.C = bit0(Memory[TU]);
			Memory[TU] >>= 1;
			CCR.N = false; CCR.Z = (bool) (Memory[TU]);
			PC += 2;
			break;
		case 0x74 : //LSR
			TU = X;
			CCR.C = bit0(Memory[X]);
			Memory[X] >>= 1;
			CCR.N = false; CCR.Z = (bool) (Memory[X]);
			PC += 1;
			break;

		case 0x36 : //ROR
			TU = Memory[PC+1];
			tmpbool = bit0(Memory[TU]);
			Memory[TU] = (BYTE) ((Memory[TU] >> 1) | (((BYTE) (CCR.C)) << 7));
			checkacc(Memory[TU]);
			CCR.C = tmpbool;
			PC += 2;
        	break;
        case 0x46 : //RORA
/*			asm {
				ror	[A],1
                jc	RORA1

				mov al,[CCR.C]
				or	[A],al
                mov	[CCR.C],1
				jmp RORA2
RORA1:
				mov al,[CCR.C]
				or	[A],al
                mov	[CCR.C],0
RORA2:
            }*/
			tmpbool = bit0(A);
			A = (BYTE) ((A >> 1) | (((BYTE) (CCR.C)) << 7));
			checkacc(A);
			CCR.C = tmpbool;
			PC++;
        	break;
        case 0x56 : //RORX
            tmpbool = bit0(X);
			X = (BYTE) ((X >> 1) | (((BYTE) (CCR.C)) << 7));
			checkacc(X);
			CCR.C = tmpbool;
			PC++;
        	break;
        case 0x66 : //ROR
			TU = Memory[PC+1] + X;
            tmpbool = bit0(Memory[TU]);
			Memory[TU] = (BYTE) ((Memory[TU] >> 1) | (((BYTE) (CCR.C)) << 7));
			checkacc(Memory[TU]);
			CCR.C = tmpbool;
			PC += 2;
        	break;
        case 0x76 : //ROR
			TU = X;
            tmpbool = bit0(Memory[TU]);
			Memory[TU] = (BYTE) ((Memory[TU] >> 1) | (((BYTE) (CCR.C)) << 7));
			checkacc(Memory[TU]);
			CCR.C = tmpbool;
			PC += 1;
        	break;

        case 0x37 : //ASR
			TU = Memory[PC+1];
			CCR.C = bit0(Memory[TU]);
			Memory[TU] = (BYTE) ((Memory[TU] >> 1) & (bit7((BYTE) (Memory[TU] << 7))));
			checkacc(Memory[TU]);
			PC += 2;
        	break;
        case 0x47 : //ASRA
			CCR.C = bit0(A);
			A = (BYTE) ((A >> 1) & (bit7((BYTE) (A << 7))));
			checkacc(A);
			PC += 1;
        	break;
        case 0x57 : //ASRX
			CCR.C = bit0(X);
			X = (BYTE) ((X >> 1) & (bit7((BYTE) (X << 7))));
			checkacc(X);
			PC += 1;
        	break;
        case 0x67 : //ASR
			TU = Memory[PC+1] + X;
			CCR.C = bit0(Memory[TU]);
			Memory[TU] = (BYTE) ((Memory[TU] >> 1) & (bit7((BYTE) (Memory[TU] << 7))));
			checkacc(Memory[TU]);
			PC += 2;
        	break;
        case 0x77 : //ASR
			TU = X;
			CCR.C = bit0(Memory[TU]);
			Memory[TU] = (BYTE) ((Memory[TU] >> 1) & (bit7((BYTE) (Memory[TU] << 7))));
			checkacc(Memory[TU]);
			PC += 1;
        	break;

		case 0x38 : //LSL
			TU = Memory[PC+1];
			CCR.C = bit7(Memory[TU]);
			Memory[TU] <<= 1;
			checkacc(Memory[TU]);
			PC += 2;
			break;
		case 0x48 : //LSLA
			CCR.C = bit7(A);
			A <<= 1;
			checkacc(A);
			PC += 1;
			break;
		case 0x58 : //LSLX
			CCR.C = bit7(X);
			X <<= 1;
			checkacc(X);
			PC += 1;
			break;
		case 0x68 : //LSL
			TU = Memory[PC+1] + X;
			CCR.C = bit7(Memory[TU]);
			Memory[TU] <<= 1;
			checkacc(Memory[TU]);
			PC += 2;
			break;
		case 0x78 : //LSL
			TU = X;
			CCR.C = bit7(Memory[TU]);
			Memory[TU] <<= 1;
			checkacc(Memory[TU]);
			PC += 1;
			break;

		case 0x39 : //ROL
			TU = Memory[PC+1];
			tmpbool = bit7(Memory[TU]);
			Memory[TU] = (BYTE) ((Memory[TU] << 1) | (BYTE) (CCR.C));
			checkacc(Memory[TU]);
			CCR.C = tmpbool;
			PC += 2;
        	break;
        case 0x49 : //ROLA
            tmpbool = bit7(A);
			A = (BYTE) ((A << 1) | (BYTE) (CCR.C));
			checkacc(A);
			CCR.C = tmpbool;
			PC += 1;
        	break;
        case 0x59 : //ROLX
            tmpbool = bit7(X);
			X = (BYTE) ((X << 1) | (BYTE) (CCR.C));
			checkacc(X);
			CCR.C = tmpbool;
			PC += 1;
        	break;
        case 0x69 : //ROL
			TU = Memory[PC+1] + X;
            tmpbool = bit7(Memory[TU]);
			Memory[TU] = (BYTE) ((Memory[TU] << 1) | (BYTE) (CCR.C));
			checkacc(Memory[TU]);
			CCR.C = tmpbool;
			PC += 2;
        	break;
        case 0x79 : //ROL
			TU = X;
            tmpbool = bit7(Memory[TU]);
			Memory[TU] = (BYTE) ((Memory[TU] << 1) | (BYTE) (CCR.C));
			checkacc(Memory[TU]);
			CCR.C = tmpbool;
			PC += 1;
        	break;

        case 0x3A : //DEC
			TU = Memory[PC+1];
			Memory[TU]--;
			checkacc(Memory[TU]);
			PC += 2;
			break;
		case 0x4A : //DECA
			A--;
			checkacc(A);
			PC += 1;
			break;
		case 0x5A : //DECX
			X--;
			checkacc(X);
			PC += 1;
			break;
		case 0x6A : //DEC
			TU = Memory[PC+1] + X;
			Memory[TU]--;
			checkacc(Memory[TU]);
			PC += 2;
			break;
		case 0x7A : //DEC
			TU = X;
			Memory[TU]--;
			checkacc(Memory[TU]);
			PC += 1;
			break;

		case 0x3C : //INC
			TU = Memory[PC+1];
			Memory[TU]++;
			checkacc(Memory[TU]);
			PC += 2;
			break;
		case 0x4C : //INCA
			A++;
			checkacc(A);
			PC += 1;
			break;
		case 0x5C : //INCX
			X++;
			checkacc(X);
			PC += 1;
			break;
		case 0x6C : //INC
			TU = Memory[PC+1] + X;
			Memory[TU]++;
			checkacc(Memory[TU]);
			PC += 2;
			break;
		case 0x7C : //INC
			TU = X;
			Memory[TU]++;
			checkacc(Memory[TU]);
			PC += 1;
			break;

		case 0x3D : //TST
			checkacc(Memory[Memory[PC+1]]);
			PC += 2;
			break;
		case 0x4D : //TSTA
			checkacc(A);
			PC += 1;
			break;
		case 0x5D : //TSTX
			checkacc(X);
			PC += 1;
			break;
		case 0x6D : //TST
			checkacc(Memory[Memory[PC+1] + X]);
			PC += 2;
        	break;
        case 0x7D : //TST
			checkacc(Memory[X]);
			PC += 1;
			break;

		case 0x3F : //CLR
			TU = Memory[PC+1];
			MemoryTUEquals(0x00);
			CCR.N = false; CCR.Z = true;
			PC += 2;
			break;
		case 0x4F : //CLRA
			A = 0;
			CCR.N = false; CCR.Z = true;
			PC += 1;
			break;
		case 0x5F : //CLRX
			X = 0;
			CCR.N = false; CCR.Z = true;
			PC += 1;
			break;
		case 0x6F : //CLR
			TU = Memory[PC+1] + X;
			MemoryTUEquals(0x00);
			CCR.N = false; CCR.Z = true;
			PC += 2;
        	break;
        case 0x7F : //CLR
			TU = X;
			MemoryTUEquals(0x00);
			CCR.N = false; CCR.Z = true;
			PC += 1;
        	break;

		case 0x42 : //MUL
			tmpLBYTE = (LBYTE) (X * A);
			X = (BYTE) (tmpLBYTE >> 8);
			A = (BYTE) (tmpLBYTE);
			CCR.H = false; CCR.C = false;
			PC += 1;
			break;

//Control
		case 0x80 : //RTI
        	CCR.MakeCCR(Memory[SP+1]);
            A = Memory[SP+2];
            X = Memory[SP+3];
			PC = Get16Bit(SP+4);
            SP += (BYTE) 5;
			break;
		case 0x81 : //RTS
			PC = Get16Bit(SP+1);
            SP += (BYTE) 2;
			break;
		case 0x83 : //SWI
			PC += 1;
			break;
		case 0x8E : //STOP
			PC += 1;
			break;
		case 0x8F : //WAIT
			PC += 1;
			break;

		case 0x97 : //TAX
			X = A;
			PC += 1;
			break;
		case 0x98 : //CLC
			CCR.C = false;
			PC += 1;
			break;
		case 0x99 : //SEC
			CCR.C = true;
			PC += 1;
			break;
		case 0x9A : //CLI
			CCR.I = false;
			PC += 1;
			break;
		case 0x9B : //SEI
			CCR.I = true;
			PC += 1;
			break;
		case 0x9C : //RSP
			SP = 0xFF;
			PC += 1;
			break;
		case 0x9D : //NOP
			PC += 1;
			break;
		case 0x9F : //TXA
			A = X;
			PC += 1;
			break;
//Register/Memory
		case 0xA0 : //SUB
			tmp = Memory[PC+1];
			A -= tmp;
			CCR.C = (tmp > A);
			checkacc(A);
			PC += 2;
			break;
		case 0xB0 : //SUB
			TU = Memory[PC+1];
			tmp = MemoryTUGet();
			A -= tmp;
			CCR.C = (tmp > A);
			checkacc(A);
			PC += 2;
        	break;
		case 0xC0 : //SUB
			TU = Get16Bit(PC + 1);
			tmp = MemoryTUGet();
			A -= tmp;
			CCR.C = (tmp > A);
			checkacc(A);
			PC += 3;
        	break;
		case 0xD0 : //SUB
			TU = Get16Bit(PC+1) + X;
			tmp = MemoryTUGet();
			A -= tmp;
			CCR.C = (tmp > A);
			checkacc(A);
			PC += 3;
        	break;
		case 0xE0 : //SUB
			TU = Memory[PC+1] + X;
			tmp = MemoryTUGet();
			A -= tmp;
			CCR.C = (tmp > A);
			checkacc(A);
			PC += 2;
        	break;
		case 0xF0 : //SUB
			TU = X;
			tmp = MemoryTUGet();
			A -= tmp;
			CCR.C = (tmp > A);
			checkacc(A);
			PC += 1;
        	break;

		case 0xA1 : //CMP
			tmp = Memory[PC+1]; CCR.C = (tmp > A); checkacc((BYTE) (A - tmp));
			PC += 2;
        	break;
		case 0xB1 : //CMP
			TU = Memory[PC+1];
			tmp = MemoryTUGet(); CCR.C = (tmp > A); checkacc((BYTE) (A - tmp));
			PC += 2;
        	break;
		case 0xC1 : //CMP
			TU = Get16Bit(PC + 1);
			tmp = MemoryTUGet(); CCR.C = (tmp > A); checkacc((BYTE) (A - tmp));
			PC += 3;
        	break;
		case 0xD1 : //CMP
			TU = Get16Bit(PC+1) + X;
			tmp = MemoryTUGet(); CCR.C = (tmp > A); checkacc((BYTE) (A - tmp));
			PC += 3;
        	break;
		case 0xE1 : //CMP
			TU = Memory[PC+1] + X;
			tmp = MemoryTUGet(); CCR.C = (tmp > A); checkacc((BYTE) (A - tmp));
			PC += 2;
        	break;
		case 0xF1 : //CMP
			TU = X;
			tmp = MemoryTUGet(); CCR.C = (tmp > A); checkacc((BYTE) (A - tmp));
			PC += 1;
        	break;

		case 0xA2 : //SBC
			tmp = Memory[PC+1]; CCR.C = (tmp > A); checkacc((BYTE) (A - tmp));
			PC += 2;
        	break;
		case 0xB2 : //SBC
			TU = Memory[PC+1];
			tmp = MemoryTUGet(); CCR.C = (tmp > A); checkacc((BYTE) (A - tmp));
			PC += 2;
        	break;
		case 0xC2 : //SBC
			TU = Get16Bit(PC + 1);
			tmp = MemoryTUGet(); CCR.C = (tmp > A); checkacc((BYTE) (A - tmp));
			PC += 3;
        	break;
		case 0xD2 : //SBC
			TU = Get16Bit(PC+1) + X;
			tmp = MemoryTUGet(); CCR.C = (tmp > A); checkacc((BYTE) (A - tmp));
			PC += 3;
        	break;
		case 0xE2 : //SBC
			TU = Memory[PC+1] + X;
			tmp = MemoryTUGet(); CCR.C = (tmp > A); checkacc((BYTE) (A - tmp));
			PC += 2;
			break;
		case 0xF2 : //SBC
			TU = X;
			tmp = MemoryTUGet(); CCR.C = (tmp > A); checkacc((BYTE) (A - tmp));
			PC += 1;
        	break;

		case 0xA3 : //CPX
			tmp = Memory[PC+1];
			CCR.C = (tmp > X);
			checkacc((BYTE) (X - tmp));
			PC += 2;
        	break;
		case 0xB3 : //CPX
			TU = Memory[PC+1];
			tmp = MemoryTUGet();
			CCR.C = (tmp > X);
			checkacc((BYTE) (X - tmp));
			PC += 2;
        	break;
		case 0xC3 : //CPX
			TU = Get16Bit(PC + 1);
			tmp = MemoryTUGet();
			CCR.C = (tmp > X);
			checkacc((BYTE) (X - tmp));
			PC += 3;
        	break;
		case 0xD3 : //CPX
			TU = Get16Bit(PC+1) + X;
			tmp = MemoryTUGet();
			CCR.C = (tmp > X);
			checkacc((BYTE) (X - tmp));
			PC += 3;
        	break;
		case 0xE3 : //CPX
			TU = Memory[PC+1] + X;
			tmp = MemoryTUGet();
			CCR.C = (tmp > X);
			checkacc((BYTE) (X - tmp));
			PC += 2;
        	break;
		case 0xF3 : //CPX
			TU = X;
			tmp = MemoryTUGet();
			CCR.C = (tmp > X);
			checkacc((BYTE) (X - tmp));
			PC += 1;
        	break;

		case 0xA4 : //AND
            A &= Memory[PC+1];
            checkacc(A);
			PC += 2;
        	break;
		case 0xB4 : //AND
			TU = Memory[PC+1];
            A &= MemoryTUGet();
            checkacc(A);
			PC += 2;
        	break;
		case 0xC4 : //AND
			TU = Get16Bit(PC + 1);
            A &= MemoryTUGet();
            checkacc(A);
			PC += 3;
        	break;
		case 0xD4 : //AND
			TU = Get16Bit(PC+1) + X;
            A &= MemoryTUGet();
            checkacc(A);
			PC += 3;
        	break;
		case 0xE4 : //AND
			TU = Memory[PC+1] + X;
            A &= MemoryTUGet();
            checkacc(A);
			PC += 2;
        	break;
		case 0xF4 : //AND
			TU = X;
            A &= MemoryTUGet();
            checkacc(A);
			PC += 1;
        	break;

		case 0xA5 : //BIT
			checkacc(A & Memory[PC+1]);
			PC += 2;
        	break;
		case 0xB5 : //BIT
			TU = Memory[PC+1];
			checkacc(A & MemoryTUGet());
			PC += 2;
        	break;
		case 0xC5 : //BIT
			TU = Get16Bit(PC + 1);
			checkacc(A & MemoryTUGet());
			PC += 3;
        	break;
		case 0xD5 : //BIT
			TU = Get16Bit(PC+1) + X;
			checkacc(A & MemoryTUGet());
			PC += 3;
        	break;
		case 0xE5 : //BIT
			TU = Memory[PC+1] + X;
			checkacc(A & MemoryTUGet());
			PC += 2;
			break;
		case 0xF5 : //BIT
			TU = X;
			checkacc(A & MemoryTUGet());
			PC += 1;
        	break;

		case 0xA6 : //LDA
			A = Memory[PC+1];
			checkacc(A);
			PC += 2;
        	break;
		case 0xB6 : //LDA
			TU = Memory[PC+1];
			A = MemoryTUGet();
			checkacc(A);
			PC += 2;
        	break;
		case 0xC6 : //LDA
			TU = Get16Bit(PC + 1);
			A = MemoryTUGet();
			checkacc(A);
			PC += 3;
        	break;
		case 0xD6 : //LDA
			TU = Get16Bit(PC+1) + X;
			A = MemoryTUGet();
			checkacc(A);
			PC += 3;
        	break;
		case 0xE6 : //LDA
			TU = Memory[PC+1] + X;
			A = MemoryTUGet();
			checkacc(A);
			PC += 2;
        	break;
		case 0xF6 : //LDA
			TU = X;
			A = MemoryTUGet();
			checkacc(A);
			PC += 1;
        	break;

		case 0xB7 : //STA
			TU = Memory[PC+1];
			MemoryTUEquals(A);
			PC += 2;
        	break;
		case 0xC7 : //STA
			TU = Get16Bit(PC + 1);
			MemoryTUEquals(A);
			PC += 3;
        	break;
		case 0xD7 : //STA
			TU = Get16Bit(PC+1) + X;
			MemoryTUEquals(A);
			PC += 3;
        	break;
		case 0xE7 : //STA
			TU = Memory[PC+1] + X;
			MemoryTUEquals(A);
			PC += 2;
        	break;
		case 0xF7 : //STA
			TU = X;
			MemoryTUEquals(A);
			PC += 1;
        	break;

		case 0xA8 : //EOR
			A ^= Memory[PC+1];
            checkacc(A);
			PC += 2;
        	break;
		case 0xB8 : //EOR
			TU = Memory[PC+1];
			A ^= MemoryTUGet();
            checkacc(A);
			PC += 2;
        	break;
		case 0xC8 : //EOR
			TU = Get16Bit(PC + 1);
			A ^= MemoryTUGet();
            checkacc(A);
			PC += 3;
        	break;
		case 0xD8 : //EOR
			TU = Get16Bit(PC+1) + X;
			A ^= MemoryTUGet();
            checkacc(A);
			PC += 3;
        	break;
		case 0xE8 : //EOR
			TU = Memory[PC+1] + X;
			A ^= MemoryTUGet();
            checkacc(A);
			PC += 2;
        	break;
		case 0xF8 : //EOR
			TU = X;
			A ^= MemoryTUGet();
            checkacc(A);
			PC += 1;
        	break;

		case 0xA9 : //ADC
			tmp = Memory[PC+1]; CCR.H = bit3(A) && bit3(tmp); CCR.C = bit7(A) && bit7(tmp);
			A += (BYTE) (tmp + CCR.C); checkacc(A);
			PC += 2;
        	break;
		case 0xB9 : //ADC
			TU = Memory[PC+1];
			tmp = MemoryTUGet(); CCR.H = bit3(A) && bit3(tmp); CCR.C = bit7(A) && bit7(tmp);
			A += (BYTE) (tmp + CCR.C); checkacc(A);
			PC += 2;
        	break;
		case 0xC9 : //ADC
			TU = Get16Bit(PC + 1);
			tmp = MemoryTUGet(); CCR.H = bit3(A) && bit3(tmp); CCR.C = bit7(A) && bit7(tmp);
			A += (BYTE) (tmp + CCR.C); checkacc(A);
			PC += 3;
        	break;
		case 0xD9 : //ADC
			TU = Get16Bit(PC+1) + X;
			tmp = MemoryTUGet(); CCR.H = bit3(A) && bit3(tmp); CCR.C = bit7(A) && bit7(tmp);
			A += (BYTE) (tmp + CCR.C); checkacc(A);
			PC += 3;
        	break;
		case 0xE9 : //ADC
			TU = Memory[PC+1] + X;
			tmp = MemoryTUGet(); CCR.H = bit3(A) && bit3(tmp); CCR.C = bit7(A) && bit7(tmp);
			A += (BYTE) (tmp + CCR.C); checkacc(A);
			PC += 2;
        	break;
		case 0xF9 : //ADC
			TU = X;
			tmp = MemoryTUGet(); CCR.H = bit3(A) && bit3(tmp); CCR.C = bit7(A) && bit7(tmp);
			A += (BYTE) (tmp + CCR.C); checkacc(A);
			PC += 1;
        	break;

		case 0xAA : //ORA
			A |= Memory[PC+1];
			checkacc(A);
			PC += 2;
        	break;
		case 0xBA : //ORA
			TU = Memory[PC+1];
			A |= MemoryTUGet();
			checkacc(A);
			PC += 2;
        	break;
		case 0xCA : //ORA
			TU = Get16Bit(PC + 1);
			A |= MemoryTUGet();
			checkacc(A);
			PC += 3;
        	break;
		case 0xDA : //ORA
			TU = Get16Bit(PC+1) + X;
			A |= MemoryTUGet();
			checkacc(A);
			PC += 3;
        	break;
		case 0xEA : //ORA
			TU = Memory[PC+1] + X;
			A |= MemoryTUGet();
			checkacc(A);
			PC += 2;
        	break;
		case 0xFA : //ORA
			TU = X;
			A |= MemoryTUGet();
			checkacc(A);
			PC += 1;
        	break;

		case 0xAB : //ADD
			tmp = Memory[PC+1]; CCR.H = bit3(A) && bit3(tmp); CCR.C = bit7(A) && bit7(tmp);
			A += tmp; checkacc(A);
			PC += 2;
        	break;
		case 0xBB : //ADD
			TU = Memory[PC+1];
			tmp = MemoryTUGet(); CCR.H = bit3(A) && bit3(tmp); CCR.C = bit7(A) && bit7(tmp);
			A += tmp; checkacc(A);
			PC += 2;
        	break;
		case 0xCB : //ADD
			TU = Get16Bit(PC + 1);
			tmp = MemoryTUGet(); CCR.H = bit3(A) && bit3(tmp); CCR.C = bit7(A) && bit7(tmp);
			A += tmp; checkacc(A);
			PC += 3;
        	break;
		case 0xDB : //ADD
			TU = Get16Bit(PC+1) + X;
			tmp = MemoryTUGet(); CCR.H = bit3(A) && bit3(tmp); CCR.C = bit7(A) && bit7(tmp);
			A += tmp; checkacc(A);
			PC += 3;
        	break;
		case 0xEB : //ADD
			TU = Memory[PC+1] + X;
			tmp = MemoryTUGet(); CCR.H = bit3(A) && bit3(tmp); CCR.C = bit7(A) && bit7(tmp);
			A += tmp; checkacc(A);
			PC += 2;
        	break;
		case 0xFB : //ADD
			TU = X;
			tmp = MemoryTUGet(); CCR.H = bit3(A) && bit3(tmp); CCR.C = bit7(A) && bit7(tmp);
			A += tmp; checkacc(A);
			PC += 1;
        	break;

		case 0xBC : //JMP
			PC = Memory[PC+1];
        	break;
		case 0xCC : //JMP
			PC = (((Memory[PC + 1] & 0x1F) << 8) + Memory[PC + 2]);
//			PC = ((Memory[PC + 1] << 8) + Memory[PC + 2]);
////			PC = Get16Bit(PC + 1);
        	break;
		case 0xDC : //JMP
			PC = Get16Bit(PC + 1) + X;
        	break;
		case 0xEC : //JMP
			PC = Memory[PC+1] + X;
        	break;
		case 0xFC : //JMP
			PC = X;
        	break;

		case 0xAD :	//BSR
        	PC += 2;
			Memory[SP] = PCL;
			Memory[SP-1] = PCH;
            SP -= (BYTE) 2;
			PC += (char) (Memory[PC-1]);
			break;
		case 0xBD : //JSR
			PC += 2;
			Memory[SP] = PCL; Memory[SP-1] = PCH;
            SP -= (BYTE) 2; PC = Memory[PC-1];
        	break;
		case 0xCD : //JSR
			PC += 3;
			Memory[SP] = PCL; Memory[SP-1] = PCH;
            SP -= (BYTE) 2;
            PC = Get16Bit(PC - 2);
        	break;
		case 0xDD : //JSR
			PC += 3;
			Memory[SP] = PCL; Memory[SP-1] = PCH;
            SP -= (BYTE) 2; PC = Get16Bit(PC - 2) + X;
        	break;
		case 0xED : //JSR
			PC += 2;
			Memory[SP] = PCL; Memory[SP-1] = PCH;
            SP -= (BYTE) 2; PC = Memory[PC-1] + X;
        	break;
		case 0xFD : //JSR
			PC += 1;
			Memory[SP] = PCL; Memory[SP-1] = PCH;
            SP -= (BYTE) 2; PC = X;
        	break;

		case 0xAE : //LDX
			X = Memory[PC+1];
			checkacc(X);
			PC += 2;
        	break;
		case 0xBE : //LDX
			TU = Memory[PC+1];
			X = MemoryTUGet();
			checkacc(X);
			PC += 2;
        	break;
		case 0xCE : //LDX
			TU = Get16Bit(PC + 1);
			X = MemoryTUGet();
			checkacc(X);
			PC += 3;
        	break;
		case 0xDE : //LDX
			TU = Get16Bit(PC+1) + X;
			X = MemoryTUGet();
			checkacc(X);
			PC += 3;
        	break;
		case 0xEE : //LDX
			TU = Memory[PC+1] + X;
			X = MemoryTUGet();
			checkacc(X);
			PC += 2;
        	break;
		case 0xFE : //LDX
			TU = X;
			X = MemoryTUGet();
			checkacc(X);
			PC += 1;
        	break;

		case 0xBF : //STX
			TU = Memory[PC+1];
			MemoryTUEquals(X);
			PC += 2;
        	break;
		case 0xCF : //STX
			TU = Get16Bit(PC + 1);
			MemoryTUEquals(X);
			PC += 3;
        	break;
		case 0xDF : //STX
			TU = Get16Bit(PC+1) + X;
			MemoryTUEquals(X);
			PC += 3;
        	break;
		case 0xEF : //STX
			TU = Memory[PC+1] + X;
			MemoryTUEquals(X);
			PC += 2;
        	break;
		case 0xFF : //STX
			TU = X;
			MemoryTUEquals(X);
			PC += 1;
        	break;

		default :
			CPUMode = cmOFF;
			Application->MessageBox("MTS has encountered an illegal opcode.", "Error: Bad Opcode", MB_OK);
        	break;
    };
}
//---------------------------------------------------------------------------
//Shortcut Commands
//---------------------------------------------------------------------------
char * ToBin(BYTE tc)
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
//BYTE __fastcall TUVal()
//{
//	if (TUMode == tmVal) { return((BYTE) (TU)); }
//	else { return(MemoryTUGet()); }
//}
//---------------------------------------------------------------------------

