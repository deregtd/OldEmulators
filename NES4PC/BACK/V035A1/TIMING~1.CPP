//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "TimingWindowForm.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TTimingForm *TimingForm;
//---------------------------------------------------------------------------
extern short int LineRate, MaxScanLine, VBScanLine;
extern int VBSec;
extern BYTE LineTicksInt;
extern long ClockFreq, ClockFreqVblank;
//---------------------------------------------------------------------------
void __fastcall TTimingForm::HBCycClick(TObject *Sender, TUDBtnType Button)
{
	LineTicksInt = HBCyc->Position;
}
void __fastcall TTimingForm::FLinesClick(TObject *Sender, TUDBtnType Button)
{
	VBScanLine = FLines->Position;
	MaxScanLine = (short int) (FLines->Position + VBLines->Position);
	LineRate = (short int) (MaxScanLine * VBSec);
}
void __fastcall TTimingForm::VBLinesClick(TObject *Sender, TUDBtnType Button)
{
	MaxScanLine = (short int) (FLines->Position + VBLines->Position);
	LineRate = (short int) (MaxScanLine * VBSec);
}
void __fastcall TTimingForm::VFPSClick(TObject *Sender, TUDBtnType Button)
{
	VBSec = VFPS->Position;
	LineRate = (short int) (MaxScanLine * VBSec);

	ClockFreqVblank = ClockFreq / VBSec;
}
//---------------------------------------------------------------------------
__fastcall TTimingForm::TTimingForm(TComponent* Owner) : TForm(Owner)
{
}
//---------------------------------------------------------------------------