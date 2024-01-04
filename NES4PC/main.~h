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
	TMenuItem *EmulationReset;
	TOpenDialog *OpenDialog1;
	TMenuItem *Help1;
	TMenuItem *About1;
	TMenuItem *Options1;

	TMenuItem *Options2;
	TMenuItem *N3;
	TMenuItem *N5;
	TMenuItem *CPUMode1;
	TMenuItem *NTSC1;
	TMenuItem *PAL1;
	TMenuItem *UpdateVideoMode1;
	TMenuItem *N8;
	TMenuItem *TakeScreenshot1;
	TMenuItem *PoweroffColdBoot1;
	TLabel *Label15;
	TEdit *FrameskipInfo;
	TUpDown *FrameskipSlider;
	TEdit *ControlBox;
	TMenuItem *AlwaysonTop1;
	TMenuItem *N2;
	TMenuItem *LoadState1;
	TMenuItem *SaveState1;
	TLabel *Label1;
	TLabel *SelStateInfo;
	TMenuItem *DrawPatternTables1;
	TMemo *DPrintBox;
	void __fastcall FileExitClick(TObject *Sender);
	void __fastcall EmulationStartClick(TObject *Sender);
	void __fastcall FileOpenClick(TObject *Sender);
	
	void __fastcall EmulationResetClick(TObject *Sender);
	
	void __fastcall KeyDownEv(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall KeyUpEv(TObject *Sender, WORD &Key, TShiftState Shift);

	void __fastcall StartFrmDestroy(TObject *Sender);
	void __fastcall StartFrmClose(TObject *Sender, TCloseAction &Action);

	void __fastcall FrameskipSliderClick(TObject *Sender, TUDBtnType Button);

	void __fastcall About1Click(TObject *Sender);
	void __fastcall Options1Click(TObject *Sender);

	void __fastcall MouseDn(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall MouseBtUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall MouseMv(TObject *Sender, TShiftState Shift, int X, int Y);

	void __fastcall StartFrmShow(TObject *Sender);
	void __fastcall PAL1Click(TObject *Sender);
	void __fastcall NTSC1Click(TObject *Sender);

	void __fastcall UpdateVideoMode1Click(TObject *Sender);

	void __fastcall TakeScreenshot1Click(TObject *Sender);

	void __fastcall PoweroffColdBoot1Click(TObject *Sender);

/*
        void __fastcall EmulationStepClick(TObject *Sender);

	void __fastcall DebugClearDebugWindowClick(TObject *Sender);
	void __fastcall DebugViewPatternTablesClick(TObject *Sender);
	void __fastcall DumpSpriteMemoryClick(TObject *Sender);
	void __fastcall DumpVRAMClick(TObject *Sender);
	void __fastcall DisplayTrace1Click(TObject *Sender);
	void __fastcall DebugRegisters1Click(TObject *Sender);
	void __fastcall DumpMainMemory1Click(TObject *Sender);
	void __fastcall ClearTrapWindow1Click(TObject *Sender);
	void __fastcall N6Click(TObject *Sender);
	void __fastcall ViewNameTables1Click(TObject *Sender);
	void __fastcall HaltonBadOpcode1Click(TObject *Sender);
	void __fastcall ForceNMI1Click(TObject *Sender);
	void __fastcall HaltonNMI1Click(TObject *Sender);
	void __fastcall ForceVblank1Click(TObject *Sender);
	void __fastcall ToggleDebugger1Click(TObject *Sender);
*/

	void __fastcall ActivateForm(TObject *Sender);
	void __fastcall AlwaysonTop1Click(TObject *Sender);
	void __fastcall SaveState1Click(TObject *Sender);
	void __fastcall LoadState1Click(TObject *Sender);
	void __fastcall DrawPatternTables1Click(TObject *Sender);
	
private:	// User declarations
public:		// User declarations
	__fastcall TStartFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TStartFrm *StartFrm;
//---------------------------------------------------------------------------
#endif
