//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "OptionsWindowForm.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TOptionsForm *OptionsForm;
//---------------------------------------------------------------------------
//extern DWORD dwSoundFrequency;
extern bool Autoframeskip;//, SoundEnabled;
extern int Autoframeskipmax;
extern int JP1A, JP1B, JP1Select, JP1Start, JP1Up, JP1Down, JP1Left, JP1Right, CoinIns;
extern int JP2A, JP2B, JP2Select, JP2Start, JP2Up, JP2Down, JP2Left, JP2Right;
extern int GGCodeNum;
extern GGCodeSt GGCode[50];
extern JoypadSt Joy;
//---------------------------------------------------------------------------
void __fastcall TOptionsForm::KeyChange(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if (Sender == CoinInsertBut) CoinIns = Key;

	if (Sender == P1A) JP1A = Key;
	if (Sender == P1B) JP1B = Key;
	if (Sender == P1Select) JP1Select = Key;
	if (Sender == P1Start) JP1Start = Key;
	if (Sender == P1Up) JP1Up = Key;
	if (Sender == P1Down) JP1Down = Key;
	if (Sender == P1Left) JP1Left = Key;
	if (Sender == P1Right) JP1Right = Key;

	if (Sender == P2A) JP2A = Key;
	if (Sender == P2B) JP2B = Key;
	if (Sender == P2Select) JP2Select = Key;
	if (Sender == P2Start) JP2Start = Key;
	if (Sender == P2Up) JP2Up = Key;
	if (Sender == P2Down) JP2Down = Key;
	if (Sender == P2Left) JP2Left = Key;
	if (Sender == P2Right) JP2Right = Key;
}
//---------------------------------------------------------------------------
void __fastcall TOptionsForm::Timer1Timer(TObject *Sender)
{
	CoinInsertBut->Text = CoinIns;

	P1A->Text = JP1A;
	P1B->Text = JP1B;
	P1Select->Text = JP1Select;
	P1Start->Text = JP1Start;
	P1Up->Text = JP1Up;
	P1Down->Text = JP1Down;
	P1Left->Text = JP1Left;
	P1Right->Text = JP1Right;

	P2A->Text = JP2A;
	P2B->Text = JP2B;
	P2Select->Text = JP2Select;
	P2Start->Text = JP2Start;
	P2Up->Text = JP2Up;
	P2Down->Text = JP2Down;
	P2Left->Text = JP2Left;
	P2Right->Text = JP2Right;
}
//---------------------------------------------------------------------------
__fastcall TOptionsForm::TOptionsForm(TComponent* Owner) : TForm(Owner)
{ }
void __fastcall TOptionsForm::FormShow(TObject *Sender)
{
	OptionsForm->CoinInsertBut->Text = CoinIns;
	OptionsForm->P1A->Text = JP1A;
	OptionsForm->P1B->Text = JP1B;
	OptionsForm->P1Select->Text = JP1Select;
	OptionsForm->P1Start->Text = JP1Start;
	OptionsForm->P1Up->Text = JP1Up;
	OptionsForm->P1Down->Text = JP1Down;
	OptionsForm->P1Left->Text = JP1Left;
	OptionsForm->P1Right->Text = JP1Right;

	OptionsForm->P2A->Text = JP2A;
	OptionsForm->P2B->Text = JP2B;
	OptionsForm->P2Select->Text = JP2Select;
	OptionsForm->P2Start->Text = JP2Start;
	OptionsForm->P2Up->Text = JP2Up;
	OptionsForm->P2Down->Text = JP2Down;
	OptionsForm->P2Left->Text = JP2Left;
	OptionsForm->P2Right->Text = JP2Right;

	Timer1->Enabled = true;
}
void __fastcall TOptionsForm::Button1Click(TObject *Sender)
{ OptionsForm->Hide(); }
void __fastcall TOptionsForm::FormHide(TObject *Sender)
{
	Timer1->Enabled = false;

	if (P1TpJoy->Checked) Joy.type[0] = jpJoypad;
	if (P2TpJoy->Checked) Joy.type[1] = jpJoypad;
	if (P2TpZapper->Checked) Joy.type[1] = jpZapper;
	if (P2TpPaddle->Checked) Joy.type[1] = jpPaddle;

	Autoframeskip = AutoFS->Checked;
	Autoframeskipmax = AutoFSMax->Position;

	AnsiString tmpline;
	GGCodeNum = 0;
	for (int i=0;i<GameGenieMemo->Lines->Count;i++)
	{
		tmpline = GameGenieMemo->Lines->Strings[i];
		tmpline = tmpline.UpperCase();
		GameGenieMemo->Lines->Strings[i] = tmpline;
		if ((tmpline.Length() != 6) && (tmpline.Length() != 8)) { GameGenieMemo->Lines->Delete(i); i--; }
		else {
			unsigned char MiniDigits[8];
			for (int i=0;i<tmpline.Length();i++)
			{
				if (AnsiString(tmpline[i+1]) == "A") MiniDigits[i] = 0;
				if (AnsiString(tmpline[i+1]) == "P") MiniDigits[i] = 1;
				if (AnsiString(tmpline[i+1]) == "Z") MiniDigits[i] = 2;
				if (AnsiString(tmpline[i+1]) == "L") MiniDigits[i] = 3;
				if (AnsiString(tmpline[i+1]) == "G") MiniDigits[i] = 4;
				if (AnsiString(tmpline[i+1]) == "I") MiniDigits[i] = 5;
				if (AnsiString(tmpline[i+1]) == "T") MiniDigits[i] = 6;
				if (AnsiString(tmpline[i+1]) == "Y") MiniDigits[i] = 7;
				if (AnsiString(tmpline[i+1]) == "E") MiniDigits[i] = 8;
				if (AnsiString(tmpline[i+1]) == "O") MiniDigits[i] = 9;
				if (AnsiString(tmpline[i+1]) == "X") MiniDigits[i] = 10;
				if (AnsiString(tmpline[i+1]) == "U") MiniDigits[i] = 11;
				if (AnsiString(tmpline[i+1]) == "K") MiniDigits[i] = 12;
				if (AnsiString(tmpline[i+1]) == "S") MiniDigits[i] = 13;
				if (AnsiString(tmpline[i+1]) == "V") MiniDigits[i] = 14;
				if (AnsiString(tmpline[i+1]) == "N") MiniDigits[i] = 15;
            }

			GGCode[i].Address = (LBYTE) (0x8000 | (bit2(MiniDigits[3]) << 14) | (bit1(MiniDigits[3]) << 13) | (bit0(MiniDigits[3]) << 12) | (bit3(MiniDigits[4]) << 11) | (bit2(MiniDigits[5]) << 10) | (bit1(MiniDigits[5]) << 9) | (bit0(MiniDigits[5]) << 8) | (bit3(MiniDigits[1]) << 7) | (bit2(MiniDigits[2]) << 6) | (bit1(MiniDigits[2]) << 5) | (bit0(MiniDigits[2]) << 4) | (bit3(MiniDigits[3]) << 3) | (bit2(MiniDigits[4]) << 2) | (bit1(MiniDigits[4]) << 1) | bit0(MiniDigits[4]));

			switch (tmpline.Length()) {
				case 6 :
					GGCode[i].CompareValueEnabled = false;
					GGCode[i].Value = (BYTE) ((bit3(MiniDigits[0]) << 7) | (bit2(MiniDigits[1]) << 6) | (bit1(MiniDigits[1]) << 5) | (bit0(MiniDigits[1]) << 4) | (bit3(MiniDigits[5]) << 3) | (bit2(MiniDigits[0]) << 2) | (bit1(MiniDigits[0]) << 1) | bit0(MiniDigits[0]));
					break;
				case 8 :
					GGCode[i].CompareValueEnabled = true;
					GGCode[i].CompareValue = (BYTE) ((bit3(MiniDigits[3]) << 7) | (bit2(MiniDigits[7]) << 6) | (bit1(MiniDigits[7]) << 5) | (bit0(MiniDigits[7]) << 4) | (bit3(MiniDigits[5]) << 3) | (bit2(MiniDigits[6]) << 2) | (bit1(MiniDigits[6]) << 1) | bit0(MiniDigits[6]));
					GGCode[i].Value = (BYTE) ((bit3(MiniDigits[0]) << 7) | (bit2(MiniDigits[1]) << 6) | (bit1(MiniDigits[1]) << 5) | (bit0(MiniDigits[1]) << 4) | (bit3(MiniDigits[7]) << 3) | (bit2(MiniDigits[0]) << 2) | (bit1(MiniDigits[0]) << 1) | bit0(MiniDigits[0]));
					break;
			};
			GGCodeNum++;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TOptionsForm::P2TpJoyClick(TObject *Sender)
{
	P2A->Visible = true;
	P2B->Visible = true;
	P2Select->Visible = true;
	P2Start->Visible = true;
	P2Up->Visible = true;
	P2Down->Visible = true;
	P2Left->Visible = true;
	P2Right->Visible = true;
	P2LeftText->Visible = true;
	P2RightText->Visible = true;
	P2UpText->Visible = true;
	P2DownText->Visible = true;
	P2Descrip->Caption = "Select   Start                    A           B";
}
//---------------------------------------------------------------------------
void __fastcall TOptionsForm::P2TpZapperClick(TObject *Sender)
{
	P2A->Visible = false;
	P2B->Visible = false;
	P2Select->Visible = false;
	P2Start->Visible = false;
	P2Up->Visible = false;
	P2Down->Visible = false;
	P2Left->Visible = false;
	P2Right->Visible = false;
	P2LeftText->Visible = false;
	P2RightText->Visible = false;
	P2UpText->Visible = false;
	P2DownText->Visible = false;
	P2Descrip->Caption = "";
}
//---------------------------------------------------------------------------
void __fastcall TOptionsForm::P2TpPaddleClick(TObject *Sender)
{
	P2A->Visible = true;
	P2B->Visible = false;
	P2Select->Visible = false;
	P2Start->Visible = false;
	P2Up->Visible = false;
	P2Down->Visible = false;
	P2Left->Visible = true;
	P2Right->Visible = true;
	P2LeftText->Visible = true;
	P2RightText->Visible = true;
	P2UpText->Visible = false;
	P2DownText->Visible = false;
	P2Descrip->Caption = "                                    Button";
}
//---------------------------------------------------------------------------
void __fastcall TOptionsForm::P1TpJoyClick(TObject *Sender)
{
	P1A->Visible = true;
	P1B->Visible = true;
	P1Select->Visible = true;
	P1Start->Visible = true;
	P1Up->Visible = true;
	P1Down->Visible = true;
	P1Left->Visible = true;
	P1Right->Visible = true;
	P1LeftText->Visible = true;
	P1RightText->Visible = true;
	P1UpText->Visible = true;
	P1DownText->Visible = true;
	P1Descrip->Caption = "Select   Start                    A           B";
}
//---------------------------------------------------------------------------
void __fastcall TOptionsForm::PBRateChange(TObject *Sender)
{ /*dwSoundFrequency = PlaybackRateCombo->Items->Strings[PlaybackRateCombo->ItemIndex].ToInt();*/ }
void __fastcall TOptionsForm::SndEnabledChnge(TObject *Sender)
{ /*SoundEnabled = SndEnabledCheck->Checked;*/ }
//---------------------------------------------------------------------------
