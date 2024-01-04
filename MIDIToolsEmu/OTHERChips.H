//---------------------------------------------------------------------------
#ifndef OtherChipsH
#define OtherChipsH

#include "6805.h"
//---------------------------------------------------------------------------
extern bool CPUMode, TUMode;
extern BYTE Memory[0x2000], *TB, *NB, *NB2;
extern int PC, TU, Clockticks;
extern char TU2;
//---------------------------------------------------------------------------
//External Chip Structures
//---------------------------------------------------------------------------
struct LEDSt {
	bool Byte1;
	bool Enabled;
	bool Light[16];
    void RedrawLo()
	{
		StartFrm->Light11->Checked = this->Light[0];
		StartFrm->Light21->Checked = this->Light[1];
		StartFrm->Light31->Checked = this->Light[2];
		StartFrm->Light41->Checked = this->Light[3];
		StartFrm->Light12->Checked = this->Light[4];
		StartFrm->Light22->Checked = this->Light[5];
		StartFrm->Light32->Checked = this->Light[6];
		StartFrm->Light42->Checked = this->Light[7];
    }
    void RedrawHi()
    {
		StartFrm->Light13->Checked = this->Light[8];
		StartFrm->Light23->Checked = this->Light[9];
		StartFrm->Light33->Checked = this->Light[10];
		StartFrm->Light43->Checked = this->Light[11];
		StartFrm->Light14->Checked = this->Light[12];
		StartFrm->Light24->Checked = this->Light[13];
		StartFrm->Light34->Checked = this->Light[14];
		StartFrm->Light44->Checked = this->Light[15];
	}
	void UpdateDebug()
	{
		if (bit5(Memory[PortADataRegister])) { StartFrm->LEDEnabled->Caption = "No"; } else { StartFrm->LEDEnabled->Caption = "Yes"; }
    }
    void SetLow(BYTE ts)
    {
		for (int i=0;i<8;i++)
        	this->Light[i] = (bool) (ts & (BYTE) (1 << i));
		this->RedrawLo();
    }
    void SetHi(BYTE ts)
    {
		for (int i=8;i<16;i++)
        	this->Light[i] = (bool) (ts & (BYTE) (1 << (i-8)));
		this->RedrawHi();
	}
};
struct LCDSt {
	unsigned CursorX : 4;
	unsigned CursorY : 1;
	unsigned Power : 1;
	unsigned Shifts : 1;
	unsigned CursorVis : 1;
	bool BusyFlag;
	char Text[16][2];
	void Data(BYTE ts)
	{
		if (ts == 0x7E) ts = 0xBB;
		if (ts == 0xDB) ts = 0x9E;
		if (ts == 0xFF) ts = 149;
		this->Text[this->CursorX][this->CursorY] = (char) ts;
		this->CursorX += this->Shifts;
		this->Redraw();
	}
	void Instruction(BYTE tg)
	{
		if (tg == 0x01) this->Clear();
		if (tg == 0x06) this->Shifts = true;
		if (tg == 0x0C) { this->CursorVis = false; this->Power = true; }
		if (tg == 0x0E) { this->CursorVis = true; this->Power = true; }
		if (tg == 0x10) this->CursorX--;
		if (tg == 0xC0) { this->CursorX = 0; this->CursorY = 0; }
		if (tg & 0x40) { this->CursorY = 1; this->CursorX = tg - 0x40; }
		else if (tg & 0x80) { this->CursorY = 0; this->CursorX = tg - 0x80; }
		this->Redraw();
	}
	void Clear()
	{
		for (int x=0;x<16;x++)
			for (int y=0;y<2;y++)
				this->Text[x][y] = 0x20;
		this->CursorX = 0;
		this->CursorY = 0;
		this->Redraw();
	}
	void Redraw()
	{
		AnsiString rows[2];
		if (this->Power)
        {
			for (int i=0;i<16;i++)
				for (int j=0;j<2;j++)
					rows[j] += this->Text[i][j];
			if (this->CursorVis)
				rows[this->CursorY][this->CursorX] = 95;
		} else {
        	for (int j=0;j<2;j++)
				rows[j] = "----------------";
        }
		StartFrm->Row1->Caption = rows[0];
		StartFrm->Row2->Caption = rows[1];
	}
	void UpdateDebug()
	{
		if (bit0(Memory[PortADataRegister])) { StartFrm->LCDEnabled->Caption = "No"; } else { StartFrm->LCDEnabled->Caption = "Yes"; }
		if (bit1(Memory[PortADataRegister])) { StartFrm->LCDDataDirection->Caption = "Write"; } else { StartFrm->LCDDataDirection->Caption = "Read"; }
		if (bit2(Memory[PortADataRegister])) { StartFrm->LCDDataMode->Caption = "Character"; } else { StartFrm->LCDDataMode->Caption = "Command"; }
		if (this->Power) { StartFrm->LCDPower->Caption = "Yes"; } else { StartFrm->LCDPower->Caption = "No"; }
		if (this->Shifts) { StartFrm->LCDShift->Caption = "Yes"; } else { StartFrm->LCDShift->Caption = "No"; }
		if (this->CursorVis) { StartFrm->LCDVisibleCursor->Caption = "Yes"; } else { StartFrm->LCDVisibleCursor->Caption = "No"; }
       	StartFrm->CursorInfo->Caption = AnsiString((BYTE) this->CursorX) + AnsiString(",") + AnsiString((BYTE) this->CursorY);
	}
};
struct EEPROMSt {
	BYTE CommandMode;
	bool WriteEnabled;
	bool Mode;
	BYTE Address;
	BYTE Bytes[0x100];
	BYTE Read()
	{
		if ((this->CommandMode == eepCmd) && (this->Mode == eepRead))
		{
			this->CommandMode = eepInst;
			return(this->Bytes[this->Address]);
		}
		return(0x00);
	}
	void Write(BYTE ta)
	{
		if ((this->WriteEnabled) && (this->Mode == eepWrite))
		{
			this->Bytes[this->Address] = ta;
			this->CommandMode = eepInst;
		}
	}
	void Instruction(BYTE ta)
	{
		if (this->CommandMode == eepInst)
		{
			if (ta == 0x02)
			{
				this->Mode = eepWrite;
				this->CommandMode = eepAddr;
#ifndef Streamlined
	            if (DebuggingTrace) dprint("EEPROM: Mode = Write");
#endif
	        }
			if (ta == 0x03)
	        {
	        	this->Mode = eepRead;
				this->CommandMode = eepAddr;
#ifndef Streamlined
	            if (DebuggingTrace) dprint("EEPROM: Mode = Read");
#endif
	        }
			if (ta == 0x04)
	        {
	        	this->WriteEnabled = false;
#ifndef Streamlined
	            if (DebuggingTrace) dprint("EEPROM: Writable = Off");
#endif
	        }
			if (ta == 0x06)
	        {
	        	this->WriteEnabled = true;
#ifndef Streamlined
	            if (DebuggingTrace) dprint("EEPROM: Writable = On");
#endif
	        }
	    } else if (this->CommandMode == eepAddr) {
           	this->Address = ta;
            this->CommandMode = eepCmd;
#ifndef Streamlined
            if (DebuggingTrace) dprint(AnsiString("EEPROM: Address = ") + IntToHex(ta,2));
#endif
	    } else if (this->CommandMode == eepCmd) {
           	this->Write(ta);
#ifndef Streamlined
            if (DebuggingTrace) dprint(AnsiString("EEPROM: Store: Address = ") + IntToHex(this->Address,2) + AnsiString(", Value = ") + IntToHex(ta,2));
#endif
        }
    }
	void UpdateDebug()
    {
		if (bit6(Memory[PortADataRegister])) { StartFrm->EEPROMEnabled->Caption = "No"; } else { StartFrm->EEPROMEnabled->Caption = "Yes"; }
		if (this->Mode) { StartFrm->EEPROMMode->Caption = "Write"; } else { StartFrm->EEPROMMode->Caption = "Read"; }
		if (this->WriteEnabled) { StartFrm->EEPROMWritable->Caption = "Yes"; } else { StartFrm->EEPROMWritable->Caption = "No"; }
		StartFrm->EEPROMAddress->Caption = this->Address;
    }
};
struct ADCSt {
	BYTE Channel;
	bool Byte1;
    BYTE Value[4];

	BYTE Get()
	{
		this->Byte1 ^= true;
		if (this->Channel == 0)	//Chan 0
		{
			if (this->Byte1) { return((BYTE) (this->Value[0] >> 5)); }	//Byte 1
			else { return((BYTE) (this->Value[0] << 3)); }	//Byte 2
		}
        return(0);
    }
	void UpdateDebug()
	{
		if (bit7(Memory[PortADataRegister])) { StartFrm->ADCEnabled->Caption = "No"; } else { StartFrm->ADCEnabled->Caption = "Yes"; }
		StartFrm->ADCChannel->Caption = AnsiString(Channel);
		StartFrm->ADCValue0->Caption = IntToHex(this->Value[0],2);
	}
};
struct SwitchesSt {
	BYTE TVal;
	BYTE Val[8];
	void Recalc()
	{ TVal = (BYTE) (Val[0] + Val[1] + Val[2] + Val[3] + Val[4] + Val[5] + Val[6] + Val[7]); }
};
//---------------------------------------------------------------------------
#endif
