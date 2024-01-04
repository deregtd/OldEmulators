//---------------------------------------------------------------------------
#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Dialogs.hpp>
#include <vcl\Menus.hpp>
#include <vcl\ExtCtrls.hpp>
#include <vcl\ComCtrls.hpp>

#include "Defines.h"
#include "AboutWindowForm.h"
#include "OptionsWindowForm.h"
#include "TimingWindowForm.h"
#include "DebugFrm.h"
#include "6502.h"
//---------------------------------------------------------------------------
class TStartFrm : public TForm
{
__published:	// IDE-managed Components
	TMainMenu *MainMenu1;
	TMenuItem *FileMenu;
	TMenuItem *FileOpen;
	TMenuItem *FileExit;
	TMenuItem *EmulationMenu;
	TMenuItem *EmulationStart;
	TMenuItem *N2;
	TMenuItem *EmulationStep;
	TGroupBox *GroupBox2;
	TLabel *Label1;
	TLabel *PCInfo;
	TLabel *ClockticksInfo;
	TLabel *Label4;
	TLabel *Label5;
	TCheckBox *CarryCheck;
	TCheckBox *ZeroCheck;
	TCheckBox *InterruptCheck;
	TCheckBox *DecimalCheck;
	TCheckBox *BreakCheck;
	TCheckBox *OverflowCheck;
	TCheckBox *NegativeCheck;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label8;
	TLabel *AccumulatorInfo;
	TLabel *XRegisterInfo;
	TLabel *YRegisterInfo;
	TLabel *Label9;
	TLabel *StackPointerInfo;
	TBevel *Bevel1;
	TMenuItem *EmulationReset;
	TGroupBox *GroupBox3;
	TMemo *StatusInfo;
	TGroupBox *GroupBox4;
	TMemo *TracerInfo;
	TMenuItem *DebugMenu;
	TMenuItem *DebugClearDebugWindow;
	TMenuItem *DebugViewPatternTables;
	TMenuItem *DumpSpriteMemory;
	TMenuItem *DumpVRAM;
	TOpenDialog *OpenDialog1;
	TMenuItem *N4;
	TMenuItem *DisplayTrace1;
	TMenuItem *DebugRegisters1;
	TMenuItem *DumpView1;
	TMenuItem *DumpMainMemory1;
	TMenuItem *ClearTrapWindow1;
	TMenuItem *N6;
	TGroupBox *GroupBox1;
	TLabel *Label11;
	TLabel *BGScrollXInfo;
	TLabel *BGScrollYInfo;
	TLabel *Label12;
	TLabel *VRAMAddressInfo;
	TLabel *Label13;
	TLabel *SPRAddressInfo;
	TLabel *NameTableInfo;
	TMenuItem *ViewNameTables1;
	TMenuItem *N7;
	TMenuItem *Help1;
	TMenuItem *About1;
	TMenuItem *Options1;

	TMenuItem *Options2;
	TMenuItem *N3;
	TMenuItem *N5;
	TMenuItem *CPUMode1;
	TMenuItem *NTSC1;
	TMenuItem *PAL1;
	TMenuItem *HaltonBadOpcode1;
	TMenuItem *HaltonNMI1;
	TMenuItem *ForceNMI1;
	TMenuItem *N9;
	TMenuItem *UpdateVideoMode1;
	TMenuItem *TimingWindow1;
	TMenuItem *GraphicsEngine1;
	TMenuItem *Screen1;
	TMenuItem *Tile1;
	TMenuItem *Scanline1;
	TLabel *SoundLengthLeftInfo;
	TLabel *Label2;
	TMenuItem *N8;
	TMenuItem *TakeScreenshot1;
	TMenuItem *ForceVblank1;
	TMenuItem *PoweroffColdBoot1;
	TLabel *OInfo;
	TLabel *Label3;
	TLabel *Label15;
	TEdit *FrameskipInfo;
	TUpDown *FrameskipSlider;
	TLabel *Label16;
	TMenuItem *N10;
	TMenuItem *ToggleDebugger1;
	TLabel *Label10;
	TLabel *ScanlineInfo;
	void __fastcall FileExitClick(TObject *Sender);
	void __fastcall EmulationStartClick(TObject *Sender);
	void __fastcall FileOpenClick(TObject *Sender);
	void __fastcall EmulationStepClick(TObject *Sender);
	
	void __fastcall EmulationResetClick(TObject *Sender);
	
	void __fastcall DebugClearDebugWindowClick(TObject *Sender);
	void __fastcall DebugViewPatternTablesClick(TObject *Sender);
	void __fastcall DumpSpriteMemoryClick(TObject *Sender);
	void __fastcall DumpVRAMClick(TObject *Sender);
	void __fastcall DisplayTrace1Click(TObject *Sender);
	void __fastcall DebugRegisters1Click(TObject *Sender);
	void __fastcall DumpMainMemory1Click(TObject *Sender);
	void __fastcall ClearTrapWindow1Click(TObject *Sender);
	void __fastcall N6Click(TObject *Sender);
	void __fastcall KeyDownEv(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall KeyUpEv(TObject *Sender, WORD &Key, TShiftState Shift);
	
	void __fastcall StartFrmDestroy(TObject *Sender);
	void __fastcall StartFrmClose(TObject *Sender, TCloseAction &Action);
	void __fastcall ViewNameTables1Click(TObject *Sender);
	
	
	void __fastcall FrameskipSliderClick(TObject *Sender, TUDBtnType Button);
	
	
	void __fastcall About1Click(TObject *Sender);
	void __fastcall Options1Click(TObject *Sender);
	void __fastcall MouseDn(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	
	void __fastcall MouseBtUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);


	void __fastcall StartFrmShow(TObject *Sender);
	void __fastcall PAL1Click(TObject *Sender);
	void __fastcall NTSC1Click(TObject *Sender);
	void __fastcall HaltonBadOpcode1Click(TObject *Sender);
	void __fastcall ForceNMI1Click(TObject *Sender);
	void __fastcall HaltonNMI1Click(TObject *Sender);
	void __fastcall UpdateVideoMode1Click(TObject *Sender);
	
	
	
	
	void __fastcall Screen1Click(TObject *Sender);
	void __fastcall Tile1Click(TObject *Sender);
	void __fastcall Scanline1Click(TObject *Sender);
	void __fastcall MouseMv(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall TakeScreenshot1Click(TObject *Sender);
	
	void __fastcall ForceVblank1Click(TObject *Sender);
	void __fastcall PoweroffColdBoot1Click(TObject *Sender);
	
	void __fastcall ToggleDebugger1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TStartFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TStartFrm *StartFrm;
//---------------------------------------------------------------------------
void __fastcall UpdateUI();
//---------------------------------------------------------------------------
#endif
