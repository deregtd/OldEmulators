//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "DebugFrm.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TDebugForm *DebugForm;
//---------------------------------------------------------------------------
__fastcall TDebugForm::TDebugForm(TComponent* Owner) : TForm(Owner)
{
	DebugForm->ClientWidth = 512;
	DebugForm->ClientHeight = 480;
}
//---------------------------------------------------------------------------