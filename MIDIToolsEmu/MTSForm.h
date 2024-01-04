//---------------------------------------------------------------------------
#ifndef MTEmH
#define MTEmH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Menus.hpp>
#include <vcl\Dialogs.hpp>
#include <vcl\ExtCtrls.hpp>
#include <vcl\ComCtrls.hpp>
//---------------------------------------------------------------------------
class TStartFrm : public TForm
{
__published:	// IDE-managed Components
	TMainMenu *MainMenu1;
	TMenuItem *FileMenu;				//&File
    TMenuItem *Open1;					// &Open
    TMenuItem *N1;						// -----
    TMenuItem *Exit1;					// E&xit

	TMenuItem *Options1;				//&Options
    TMenuItem *DebugDisplay1;			// Debug &Trace
    TMenuItem *Debug1;					// Debug &Registers
    TMenuItem *vMHZMeter1;				// &vMHZ Meter

	TMenuItem *Emulation1;				//&CPU
    TMenuItem *Start1;					// &Start
    TMenuItem *Reset1;					// &Reset

	TMenuItem *Memory1;					//&Debugging
	TMenuItem *DebuggingOn1;			// &Debugging On
	TMenuItem *N2;						// -------------------
    TMenuItem *Step1;					// Ste&p
    TMenuItem *N3;						// -------------------
    TMenuItem *ClearTraceWindow1;		// &Clear Trace Window
    TMenuItem *N4;						// -------------------
    TMenuItem *DumpMemory1;				// Dump &Memory To File

    TOpenDialog *OpenDialog1;
	TSaveDialog *SaveDialog1;
    TTimer *Timer1;
	TMemo *TracerInfo;
	TScrollBar *Dial;
	TGroupBox *GroupBox1;
    TGroupBox *GroupBox3;
    TGroupBox *GroupBox5;
    TGroupBox *GroupBox6;
    TGroupBox *GroupBox7;
    TBevel *Bevel2;
	TLabel *Row1;
    TLabel *Row2;
	TCheckBox *Light11; TCheckBox *Light21; TCheckBox *Light31; TCheckBox *Light41;
	TCheckBox *Light12; TCheckBox *Light22; TCheckBox *Light32; TCheckBox *Light42;
	TCheckBox *Light13; TCheckBox *Light23; TCheckBox *Light33; TCheckBox *Light43;
	TCheckBox *Light14; TCheckBox *Light24; TCheckBox *Light34; TCheckBox *Light44;
	TCheckBox *Button4; TCheckBox *Button3; TCheckBox *Button2; TCheckBox *Button1;
	TCheckBox *Button8; TCheckBox *Button7; TCheckBox *Button6; TCheckBox *Button5;

	TGroupBox *GroupBox2;
	TBevel *Bevel1;
	TLabel *Label10;
	TLabel *Label4;
	TLabel *PCInfo;
	TLabel *ClockticksInfo;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *AccumulatorInfo;
	TLabel *XRegisterInfo;
	TLabel *Label9;
	TLabel *StackPointerInfo;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label8;
	TCheckBox *CarryCheck;
	TCheckBox *ZeroCheck;
	TCheckBox *InterruptCheck;
	TCheckBox *NegativeCheck;
	TCheckBox *HalfCarryCheck;
	TPageControl *PageControl1;
	TTabSheet *VariableSheet;
	TEdit *NewMemItemAddr;
	TPopupMenu *VarListPop;
	TMenuItem *VarRemove;
	TButton *VarAdd;
	TEdit *NewMemItemName;
	TMenuItem *VariableTrace1;
	TTabSheet *MIDIChat;
	TMemo *MIDIChatInfo;
	TEdit *MIDIChatSending;
	TLabel *Label13;
	TButton *MIDIChatSend;
	TTabSheet *DeviceInfo;
	TLabel *Label28;
	TGroupBox *GroupBox4;
	TLabel *Label22;
	TLabel *Label23;
	TLabel *Label29;
	TLabel *Label15;
	TLabel *Label16;
	TLabel *Label11;
	TLabel *Label17;
	TLabel *LCDVisibleCursor;
	TLabel *CursorInfo;
	TLabel *LCDShift;
	TLabel *LCDPower;
	TLabel *LCDDataDirection;
	TLabel *LCDDataMode;
	TLabel *LCDEnabled;
	TGroupBox *GroupBox8;
	TLabel *Label24;
	TLabel *Label14;
	TLabel *Label26;
	TLabel *Label27;
	TLabel *ADCValue0;
	TLabel *ADCChannel;
	TLabel *ADCEnabled;
	TGroupBox *GroupBox9;
	TLabel *Label25;
	TLabel *EEPROMEnabled;
	TLabel *EEPROMMode;
	TLabel *EEPROMWritable;
	TLabel *EEPROMAddress;
	TLabel *Label19;
	TLabel *Label20;
	TLabel *Label18;
	TGroupBox *GroupBox10;
	TLabel *Label21;
	TLabel *LEDEnabled;
	TMenuItem *MIDIChat1;
	TMenuItem *DeviceInfo1;
	TLabel *Label30;
	TTabSheet *Breakpointsheet;
	TLabel *Label31;
	TEdit *BPAddr;
	TButton *BPAdd;
	TEdit *BPName;
	TPopupMenu *BPPop;
	TMenuItem *BPRemove;
	TMenuItem *BPTrace1;
	TMenuItem *N5;
	TLabel *Label32;
	TLabel *StatRegInfo;
	TListBox *BPList;
	TListBox *VarList;
	TLabel *Label12;
	TLabel *Label33;
	void __fastcall Exit1Click(TObject *Sender);
	void __fastcall Open1Click(TObject *Sender);
	void __fastcall DumpMemory1Click(TObject *Sender);
	void __fastcall Start1Click(TObject *Sender);
	void __fastcall Step1Click(TObject *Sender);
	void __fastcall Reset1Click(TObject *Sender);
	void __fastcall DebugDisplay1Click(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall vMHZMeter1Click(TObject *Sender);
	void __fastcall Debug1Click(TObject *Sender);
	void __fastcall ClearTraceWindow1Click(TObject *Sender);
	void __fastcall DebuggingOn1Click(TObject *Sender);
	void __fastcall VarAddClick(TObject *Sender);
	void __fastcall VariableTrace1Click(TObject *Sender);
	void __fastcall MIDIChatSendClick(TObject *Sender);
	void __fastcall DialChange(TObject *Sender);

	void __fastcall Button4Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button8Click(TObject *Sender);
	void __fastcall Button7Click(TObject *Sender);
	void __fastcall Button6Click(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
	void __fastcall MIDIChat1Click(TObject *Sender);
	void __fastcall DeviceInfo1Click(TObject *Sender);
	
	void __fastcall VarRemoveClick(TObject *Sender);
	void __fastcall BPRemoveClick(TObject *Sender);
	void __fastcall BPAddClick(TObject *Sender);
	void __fastcall BPTrace1Click(TObject *Sender);
	void __fastcall FormKill(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
	__fastcall TStartFrm(TComponent* Owner);
};
extern TStartFrm *StartFrm;
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------
BYTE HexToDec(char tc[2]);
BYTE HexToDec(AnsiString tc);
void UpdateUI();
#define dprint(tp) StartFrm->TracerInfo->Lines->Add(tp);
//---------------------------------------------------------------------------
//Defines
//---------------------------------------------------------------------------
#define VariableTrace StartFrm->VariableTrace1->Checked
#define BPTrace StartFrm->BPTrace1->Checked
#define DebuggingTrace StartFrm->DebugDisplay1->Checked
#define DebuggingRegs StartFrm->Debug1->Checked
#define DeviceInfo StartFrm->DeviceInfo1->Checked
#define MIDIChat StartFrm->MIDIChat1->Checked
//---------------------------------------------------------------------------
#endif
