//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "AboutWindowForm.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TAboutWindow *AboutWindow;
//---------------------------------------------------------------------------
__fastcall TAboutWindow::TAboutWindow(TComponent* Owner) : TForm(Owner) { }
//---------------------------------------------------------------------------
void __fastcall TAboutWindow::Button1Click(TObject *Sender)
{ AboutWindow->Hide(); }
//---------------------------------------------------------------------------