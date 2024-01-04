//---------------------------------------------------------------------------
#ifndef TimingWindowFormH
#define TimingWindowFormH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>

#include "6502.h"
#include <vcl\ComCtrls.hpp>
//---------------------------------------------------------------------------
class TTimingForm : public TForm
{
__published:	// IDE-managed Components
	TEdit *Edit1;
	TEdit *Edit2;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TEdit *Edit3;
	TEdit *Edit4;
	TUpDown *HBCyc;
	TUpDown *FLines;
	TUpDown *VBLines;
	TUpDown *VFPS;
	void __fastcall HBCycClick(TObject *Sender, TUDBtnType Button);
	void __fastcall FLinesClick(TObject *Sender, TUDBtnType Button);
	void __fastcall VBLinesClick(TObject *Sender, TUDBtnType Button);
	void __fastcall VFPSClick(TObject *Sender, TUDBtnType Button);
private:	// User declarations
public:		// User declarations
	__fastcall TTimingForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TTimingForm *TimingForm;
//---------------------------------------------------------------------------
#endif
