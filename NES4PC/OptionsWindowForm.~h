//---------------------------------------------------------------------------
#ifndef OptionsWindowFormH
#define OptionsWindowFormH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\ExtCtrls.hpp>
#include <vcl\Menus.hpp>

#include "Defines.h"
#include "6502.h"
#include <vcl\ComCtrls.hpp>
//---------------------------------------------------------------------------
class TOptionsForm : public TForm
{
__published:	// IDE-managed Components
	TButton *Button1;
	TTimer *Timer1;
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TGroupBox *GroupBox1;
	TLabel *P1Descrip;
	TLabel *P1LeftText;
	TLabel *P1RightText;
	TLabel *P1UpText;
	TLabel *P1DownText;
	TEdit *P1Down;
	TEdit *P1Left;
	TEdit *P1Up;
	TEdit *P1Right;
	TEdit *P1Select;
	TEdit *P1Start;
	TEdit *P1A;
	TEdit *P1B;
	TGroupBox *GroupBox3;
	TRadioButton *P1TpJoy;
	TTabSheet *TabSheet2;
	TGroupBox *GroupBox4;
	TRadioButton *P2TpJoy;
	TRadioButton *P2TpZapper;
	TRadioButton *P2TpPaddle;
	TGroupBox *GroupBox2;
	TLabel *P2Descrip;
	TLabel *P2DownText;
	TLabel *P2RightText;
	TLabel *P2UpText;
	TLabel *P2LeftText;
	TEdit *P2Down;
	TEdit *P2Left;
	TEdit *P2Up;
	TEdit *P2Right;
	TEdit *P2Select;
	TEdit *P2Start;
	TEdit *P2A;
	TEdit *P2B;
	TTabSheet *TabSheet3;
	TMemo *GameGenieMemo;
	TTabSheet *TabSheet4;
	TTabSheet *TabSheet5;
	TTabSheet *TabSheet6;
	TGroupBox *GroupBox5;
	TRadioButton *ManualFS;
	TRadioButton *AutoFS;
	TGroupBox *GroupBox6;
	TUpDown *AutoFSMax;
	TEdit *AutoFSMaxText;
	TLabel *Label1;
	TLabel *Label2;
	TMemo *Memo1;
	TEdit *CoinInsertBut;
	TLabel *Label3;
	TTabSheet *TabSheet7;
	TCheckBox *SndEnabledCheck;
	TComboBox *PlaybackRateCombo;
	TLabel *Label4;
	void __fastcall KeyChange(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormHide(TObject *Sender);
	void __fastcall P2TpJoyClick(TObject *Sender);
	void __fastcall P2TpZapperClick(TObject *Sender);
	void __fastcall P2TpPaddleClick(TObject *Sender);
	void __fastcall P1TpJoyClick(TObject *Sender);
	
	
	void __fastcall PBRateChange(TObject *Sender);
	void __fastcall SndEnabledChnge(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TOptionsForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TOptionsForm *OptionsForm;
//---------------------------------------------------------------------------
#endif
