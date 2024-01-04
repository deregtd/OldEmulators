//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "MTSForm.h"
#include "6805.h"
#include "OtherChips.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TStartFrm *StartFrm;
//---------------------------------------------------------------------------
int lastclockticks, startct;
bool Debugging = false, FileOpened = false;

extern CCRSt CCR;
extern SCISt SCI;
extern LEDSt LED;
extern LCDSt LCD;
extern EEPROMSt EEPROM;
extern ADCSt ADC;
extern SwitchesSt Switches;

extern bool CPUMode, TUMode;
extern BYTE Memory[0x2000], *TB, *NB, *NB2;
extern int PC, TU, Clockticks, Clocktickstmp;
extern BYTE A, X, SP, P;
extern char TU2;
extern LBYTE ResetVectorGot, SPIVectorGot, SCIVectorGot, TimerVectorGot;
extern LBYTE IRQVectorGot, SWIVectorGot;

struct VarListItemSt {
	AnsiString Caption;
	AnsiString AddrCaption;
    unsigned short int AddrVal;
    BYTE * Value;
    void Set(AnsiString Cap, unsigned short int Addr)
    {
		this->Caption = Cap;
        this->AddrVal = Addr;
        this->AddrCaption = IntToHex(Addr, 4);
        this->Value = &Memory[Addr];
    }
};
struct VarListSt {
	BYTE NumItems;
	VarListItemSt Items[100];
	void AddItem(AnsiString Cap, LBYTE Addr)
    {
    	this->Items[this->NumItems].Set(Cap, Addr);
        this->NumItems++;
		StartFrm->VarList->Items->Add(" ");
		this->Update();
    }
	void RemoveItem(int ItemNum)
    {
		for (int i=ItemNum; i<(this->NumItems - 1); i++)
			this->Items[i] = this->Items[i+1];
		this->NumItems--;
		StartFrm->VarList->Items->Clear();
		for (int i=0;i<this->NumItems;i++)
			StartFrm->VarList->Items->Add(" ");
		this->Update();
    }
	void Update()
    {
		for (int i=0;i<this->NumItems;i++)
			StartFrm->VarList->Items->Strings[i] = this->Items[i].AddrCaption + AnsiString("    ") + this->Items[i].Caption + AnsiString("    ") + IntToHex(*this->Items[i].Value, 2) + AnsiString("    ") + AnsiString(ToBin(*this->Items[i].Value));
    }
} VarListItems;

struct BPListItemSt {
	AnsiString Caption;
	AnsiString AddrCaption;
    unsigned short int AddrVal;
    void Set(AnsiString Cap, unsigned short int Addr)
    {
		this->Caption = Cap;
        this->AddrVal = Addr;
        this->AddrCaption = IntToHex(Addr, 4);
    }
};
struct BPListSt {
	BYTE NumItems;
	BPListItemSt Items[100];
	void AddItem(AnsiString Cap, LBYTE Addr)
    {
    	this->Items[this->NumItems].Set(Cap, Addr);
        this->NumItems++;
		this->Redraw();
    }
	void RemoveItem(int ItemNum)
    {
		for (int i=ItemNum; i<(this->NumItems - 1); i++)
			this->Items[i] = this->Items[i+1];
		this->NumItems--;
		this->Redraw();
    }
	void Update()
    {
		for (int i=0;i<this->NumItems;i++)
        {
			if (PC == this->Items[i].AddrVal)
			{
				CPUMode = cmOFF;
				Application->MessageBox(AnsiString(AnsiString("Hit Breakpoint: ") + this->Items[i].Caption).c_str(), "Breakpoint", MB_OK);
            }
		}
    }
	void Redraw()
    {
		StartFrm->BPList->Items->Clear();
        for (int i=0;i<this->NumItems;i++)
			StartFrm->BPList->Items->Add(this->Items[i].AddrCaption + AnsiString("    ") + this->Items[i].Caption);
    }
} BPItems;
//---------------------------------------------------------------------------
//Debugging Functions
//---------------------------------------------------------------------------
void UpdateUI()
{
    SCI.Update();

    if (VariableTrace)
    	VarListItems.Update();

    if (BPTrace)
    	BPItems.Update();

	if (DebuggingRegs)
    {
		StartFrm->PCInfo->Caption = IntToHex(PC, 4);
		StartFrm->ClockticksInfo->Caption = (int) Clockticks;

		StartFrm->AccumulatorInfo->Caption = IntToHex(A, 2);
		StartFrm->XRegisterInfo->Caption = IntToHex(X, 2);
		StartFrm->StackPointerInfo->Caption = IntToHex(SP, 2);
	}

	if (DeviceInfo)
    {
        CCR.UpdateDebug();
	    ADC.UpdateDebug();
	    EEPROM.UpdateDebug();
		LCD.UpdateDebug();
	    LED.UpdateDebug();
    }
}
//---------------------------------------------------------------------------
//Shortcut Functions
//---------------------------------------------------------------------------
BYTE HexToDec(AnsiString tc)
{
	BYTE toret;
	if (((tc[1] >= 48) && (tc[1] <= 57)) && ((tc[2] >= 48) && (tc[2] <= 57))) toret = (BYTE) (16*(tc[1] - 48) + (tc[2] - 48));
	if (((tc[1] >= 48) && (tc[1] <= 57)) && ((tc[2] >= 65) && (tc[2] <= 70))) toret = (BYTE) (16*(tc[1] - 48) + (tc[2] - 55));
	if (((tc[1] >= 65) && (tc[1] <= 70)) && ((tc[2] >= 48) && (tc[2] <= 57))) toret = (BYTE) (16*(tc[1] - 55) + (tc[2] - 48));
	if (((tc[1] >= 65) && (tc[1] <= 70)) && ((tc[2] >= 65) && (tc[2] <= 70))) toret = (BYTE) (16*(tc[1] - 55) + (tc[2] - 55));
	return(toret);
}
BYTE HexToDec(char tc[2])
{
	BYTE toret;
	if (((tc[0] >= 48) && (tc[0] <= 57)) && ((tc[1] >= 48) && (tc[1] <= 57))) toret = (BYTE) (16*(tc[0] - 48) + (tc[1] - 48));
	if (((tc[0] >= 48) && (tc[0] <= 57)) && ((tc[1] >= 65) && (tc[1] <= 70))) toret = (BYTE) (16*(tc[0] - 48) + (tc[1] - 55));
	if (((tc[0] >= 65) && (tc[0] <= 70)) && ((tc[1] >= 48) && (tc[1] <= 57))) toret = (BYTE) (16*(tc[0] - 55) + (tc[1] - 48));
	if (((tc[0] >= 65) && (tc[0] <= 70)) && ((tc[1] >= 65) && (tc[1] <= 70))) toret = (BYTE) (16*(tc[0] - 55) + (tc[1] - 55));
	return(toret);
}
//---------------------------------------------------------------------------
//Normal Menu Functions
//---------------------------------------------------------------------------
void __fastcall TStartFrm::Open1Click(TObject *Sender)
{
		if (OpenDialog1->Execute())
		{
				int position;
				BYTE length;
				char type[2], length2[2], position2a[2], position2b[2], tmpstore2a[34], tmpstore2b[2], dummy[2];
				bool endfile = false;
				FILE * in;

				if (OpenDialog1->FileName[OpenDialog1->FileName.Length() - 2] == 109)// || 77)
				{
						in = fopen(OpenDialog1->FileName.c_str(), "rb");
						fseek(in, 0L, 0); fread(&Memory[0x0000], 1, 0x2000, in); fclose(in);
//				} else if (OpenDialog1->FileName[OpenDialog1->FileName.Length() - 2] == 115) {
				} else if (OpenDialog1->FileName[OpenDialog1->FileName.Length() - 2] == 83) { //"s" - S19
						in = fopen(OpenDialog1->FileName.c_str(), "rt");
						memset(&Memory[0],0x2000,0);
						do {
							fread(&type, 1, 2, in); fread(&length2, 1, 2, in); length = HexToDec(length2);
							if (AnsiString(type[0]) + AnsiString(type[1]) == "S1")
							{
								fread(&position2a, 1, 2, in); fread(&position2b, 1, 2, in); position = (int) (256 * HexToDec(position2a) + HexToDec(position2b));
								length -= (BYTE) 2; fread(&tmpstore2a, 1, 2*length, in);
								for (int i=0;i<length;i++)
								{
										tmpstore2b[0] = tmpstore2a[2*i]; tmpstore2b[1] = tmpstore2a[2*i + 1]; Memory[position+i] = HexToDec(tmpstore2b);
								}
							} else if (AnsiString(type[0]) + AnsiString(type[1]) == "S9") {
								endfile = true;
							}
							fread(&dummy, 1, 1, in);
						} while (endfile == false);
						fclose(in);
                } else {
						return;
                }
				ResetVectorGot = Get16Bit(ResetVector);
				SPIVectorGot = Get16Bit(SPIVector);
				SCIVectorGot = Get16Bit(SCIVector);
				TimerVectorGot = Get16Bit(TimerVector);
				IRQVectorGot = Get16Bit(IRQVector);
				SWIVectorGot = Get16Bit(SWIVector);
				reset6805(); UpdateUI();
                FileOpened = true;
				StartFrm->Caption = AnsiString("MTS - Stopped");
		}
}
void __fastcall TStartFrm::Exit1Click(TObject *Sender)
{
	CPUMode = cmOFF;
	FILE * tmp = fopen("eeprom.dat", "wb");
    fwrite(&EEPROM.Bytes[0x00], 1, 0x100, tmp);
    fclose(tmp);
    Application->Terminate();
}
void __fastcall TStartFrm::FormKill(TObject *Sender, TCloseAction &Action)
{ StartFrm->Exit1Click(NULL); }

void __fastcall TStartFrm::Start1Click(TObject *Sender)
{
	if (FileOpened == false)
    {
		Application->MessageBox("You must load a binary before starting emulation!","Error: No File Loaded",MB_OK);
		return;
    }

	if (CPUMode == cmRUNNING)
    {
		StartFrm->Caption = AnsiString("MTS - Stopped");
		CPUMode = cmOFF;
		Start1->Caption = "Start";
        return;
    } else {
		StartFrm->Caption = AnsiString("MTS - Running");
		CPUMode = cmRUNNING;
		Start1->Caption = "Stop";
    }

   	while (CPUMode == cmRUNNING) {
#ifndef Streamlined
		Clocktickstmp = 1000;
		while ((Clocktickstmp > 0) && (CPUMode == cmRUNNING)) {
			exec6805(Memory[PC]);
	        UpdateUI();
		}
		Clockticks += 1000;
#else
		Clocktickstmp = 5000;
		while (Clocktickstmp > 0) {
			exec6805(Memory[PC]);
           	SCI.Update();
		}
		Clockticks += 5000;
#endif
		Application->ProcessMessages();
    }
	CPUMode = cmOFF;
	StartFrm->Caption = AnsiString("MTS - Stopped");
	Start1->Caption = "Start";
}
void __fastcall TStartFrm::Reset1Click(TObject *Sender)		{ reset6805(); TracerInfo->Lines->Clear(); UpdateUI(); for (int i=0x50;i<0xFF;i++) Memory[i] = 0x00; }

void __fastcall TStartFrm::DebuggingOn1Click(TObject *Sender)
{
	if (Debugging == false)
    {
		Debugging = true;
		DebuggingOn1->Caption = "&Debugging Off";
		StartFrm->ClientWidth = 713;
		StartFrm->ClientHeight = 393;
		Options1->Enabled = true;
		DebugDisplay1->Enabled = true;
		Debug1->Enabled = true;
		Step1->Enabled = true;
		ClearTraceWindow1->Enabled = true;
        DumpMemory1->Enabled = true;
    } else {
		Debugging = false;
		DebuggingOn1->Caption = "&Debugging On";
		StartFrm->ClientWidth = 345;
		StartFrm->ClientHeight = 210;
		DebuggingTrace = false; DebugDisplay1->Checked = DebuggingTrace;
		DebuggingRegs = false; Debug1->Checked = DebuggingRegs;
		Options1->Enabled = false;
		DebugDisplay1->Enabled = false;
		Debug1->Enabled = false;
		Step1->Enabled = false;
		ClearTraceWindow1->Enabled = false;
        DumpMemory1->Enabled = false;
    }
}
//---------------------------------------------------------------------------
//Debugging Menu Functions
//---------------------------------------------------------------------------
void __fastcall TStartFrm::Step1Click(TObject *Sender)
{ CPUMode = cmRUNNING; exec6805(Memory[PC]); CPUMode = cmOFF; UpdateUI(); }

void __fastcall TStartFrm::DumpMemory1Click(TObject *Sender)
{	if (SaveDialog1->Execute())
    { FILE * out = fopen(SaveDialog1->FileName.c_str(), "wb"); fwrite(&Memory[0], 1, 0x2000, out); fclose(out); } }
void __fastcall TStartFrm::MIDIChat1Click(TObject *Sender)
{ MIDIChat ^= true; }
void __fastcall TStartFrm::DeviceInfo1Click(TObject *Sender)
{ DeviceInfo ^= true; }
void __fastcall TStartFrm::VariableTrace1Click(TObject *Sender)
{ VariableTrace ^= true; }
void __fastcall TStartFrm::BPTrace1Click(TObject *Sender)
{ BPTrace ^= true; }
void __fastcall TStartFrm::DebugDisplay1Click(TObject *Sender)
{ DebuggingTrace ^= true; }
void __fastcall TStartFrm::Debug1Click(TObject *Sender)
{ DebuggingRegs ^= true; }
void __fastcall TStartFrm::vMHZMeter1Click(TObject *Sender)
{ vMHZMeter1->Checked ^= true; Timer1->Enabled = vMHZMeter1->Checked; }

void __fastcall TStartFrm::ClearTraceWindow1Click(TObject *Sender)
{ TracerInfo->Lines->Clear(); }
//---------------------------------------------------------------------------
//Timer Functions
//---------------------------------------------------------------------------
void __fastcall TStartFrm::Timer1Timer(TObject *Sender)
{
	if (FileOpened == false)
    {
		StartFrm->Caption = AnsiString("MTS - No File Loaded");
		return;
    }
	if (CPUMode == cmRUNNING)
    {
		StartFrm->Caption = AnsiString("MTS - Running - vMHZ: ") + AnsiString(((float) ((int) ((Clockticks - lastclockticks)/10000)))/100);
		lastclockticks = Clockticks;
    } else {
		StartFrm->Caption = AnsiString("MTS - Stopped");
    }
}
//---------------------------------------------------------------------------
//Other Functions
//---------------------------------------------------------------------------
__fastcall TStartFrm::TStartFrm(TComponent* Owner) : TForm(Owner)
{
	StartFrm->ClientWidth = 345;
    StartFrm->ClientHeight = 210;
	StartFrm->Left = 0;
    StartFrm->Top = 0;
    Timer1->Enabled = vMHZMeter1->Checked;

	FILE * tmp = fopen("eeprom.dat", "rb");
	fseek(tmp, 0, SEEK_END);
    if (ftell(tmp) >= 255)
    {
		fseek(tmp, 0, SEEK_SET);
	    fread(&EEPROM.Bytes[0x00], 1, 0x100, tmp);
	}
    fclose(tmp);

    FileOpened = false;

#ifndef Streamlined
	Memory1->Visible = true;
	Memory1->Enabled = true;
    DebuggingOn1->Enabled = true;
#else
	Memory1->Visible = false;
	Memory1->Enabled = false;
    DebuggingOn1->Enabled = false;
#endif
}
//---------------------------------------------------------------------------
void __fastcall TStartFrm::MIDIChatSendClick(TObject *Sender)
{
	if (SCI.InputBufferBytes == 0) { SCI.InputBuffer[0] = HexToDec(MIDIChatSending->Text); SCI.InputBufferBytes++; }
	else if (SCI.InputBufferBytes == 1) { SCI.InputBuffer[1] = HexToDec(MIDIChatSending->Text); SCI.InputBufferBytes++; }
	else if (SCI.InputBufferBytes == 2) Memory[SCIStatusRegister] |= 0x08;
	if (MIDIChat) StartFrm->MIDIChatInfo->Lines->Add(AnsiString("In> ") + MIDIChatSending->Text);

	MIDIChatSending->Text = "";
}
//---------------------------------------------------------------------------
void __fastcall TStartFrm::DialChange(TObject *Sender)
{ ADC.Value[0] = (BYTE) StartFrm->Dial->Position; }

void __fastcall TStartFrm::Button1Click(TObject *Sender)
{ Switches.Val[0] = Button1->Checked; Switches.Recalc(); }
void __fastcall TStartFrm::Button2Click(TObject *Sender)
{ Switches.Val[1] = (BYTE) (Button2->Checked << 1); Switches.Recalc(); }
void __fastcall TStartFrm::Button3Click(TObject *Sender)
{ Switches.Val[2] = (BYTE) (Button3->Checked << 2); Switches.Recalc(); }
void __fastcall TStartFrm::Button4Click(TObject *Sender)
{ Switches.Val[3] = (BYTE) (Button4->Checked << 3); Switches.Recalc(); }
void __fastcall TStartFrm::Button5Click(TObject *Sender)
{ Switches.Val[4] = (BYTE) (Button5->Checked << 4); Switches.Recalc(); }
void __fastcall TStartFrm::Button6Click(TObject *Sender)
{ Switches.Val[5] = (BYTE) (Button6->Checked << 5); Switches.Recalc(); }
void __fastcall TStartFrm::Button7Click(TObject *Sender)
{ Switches.Val[6] = (BYTE) (Button7->Checked << 6); Switches.Recalc(); }
void __fastcall TStartFrm::Button8Click(TObject *Sender)
{ Switches.Val[7] = (BYTE) (Button8->Checked << 7); Switches.Recalc(); }
//---------------------------------------------------------------------------
void __fastcall TStartFrm::VarAddClick(TObject *Sender)
{
	if (NewMemItemAddr->Text.Length() < 4) return;

	LBYTE toret = 0;
	char * tmp = NewMemItemAddr->Text.c_str();
    char c1 = tmp[0], c2 = tmp[1], c3 = tmp[2], c4 = tmp[3];
	if ((c1 >= 48) && (c1 <= 57)) toret += (LBYTE) (4096*(c1 - 48));
	else if ((c1 >= 65) && (c1 <= 70)) toret += (LBYTE) (4096*(c1 - 55));
    else return;
	if ((c2 >= 48) && (c2 <= 57)) toret += (LBYTE) (256*(c2 - 48));
	else if ((c2 >= 65) && (c2 <= 70)) toret += (LBYTE) (256*(c2 - 55));
    else return;
	if ((c3 >= 48) && (c3 <= 57)) toret += (LBYTE) (16*(c3 - 48));
	else if ((c3 >= 65) && (c3 <= 70)) toret += (LBYTE) (16*(c3 - 55));
    else return;
	if ((c4 >= 48) && (c4 <= 57)) toret += (LBYTE) (c4 - 48);
	else if ((c4 >= 65) && (c4 <= 70)) toret += (LBYTE) (c4 - 55);
    else return;

	if (toret > 0x1FFF) return;

	VarListItems.AddItem(NewMemItemName->Text, toret);
	NewMemItemName->Text = "";
    NewMemItemAddr->Text = "";
}
void __fastcall TStartFrm::VarRemoveClick(TObject *Sender)
{
	VarListItems.RemoveItem(StartFrm->VarList->ItemIndex);
}
//---------------------------------------------------------------------------
void __fastcall TStartFrm::BPAddClick(TObject *Sender)
{
	if (BPAddr->Text.Length() < 4) return;

	LBYTE toret = 0;
	char * tmp = BPAddr->Text.c_str();
    char c1 = tmp[0], c2 = tmp[1], c3 = tmp[2], c4 = tmp[3];
	if ((c1 >= 48) && (c1 <= 57)) toret += (LBYTE) (4096*(c1 - 48));
	else if ((c1 >= 65) && (c1 <= 70)) toret += (LBYTE) (4096*(c1 - 55));
    else return;
	if ((c2 >= 48) && (c2 <= 57)) toret += (LBYTE) (256*(c2 - 48));
	else if ((c2 >= 65) && (c2 <= 70)) toret += (LBYTE) (256*(c2 - 55));
    else return;
	if ((c3 >= 48) && (c3 <= 57)) toret += (LBYTE) (16*(c3 - 48));
	else if ((c3 >= 65) && (c3 <= 70)) toret += (LBYTE) (16*(c3 - 55));
    else return;
	if ((c4 >= 48) && (c4 <= 57)) toret += (LBYTE) (c4 - 48);
	else if ((c4 >= 65) && (c4 <= 70)) toret += (LBYTE) (c4 - 55);
    else return;

    if (toret > 0x1FFF) return;

	BPItems.AddItem(BPName->Text, toret);
	BPName->Text = "";
    BPAddr->Text = "";
}
void __fastcall TStartFrm::BPRemoveClick(TObject *Sender)
{
	BPItems.RemoveItem(StartFrm->BPList->ItemIndex);
}
//---------------------------------------------------------------------------
