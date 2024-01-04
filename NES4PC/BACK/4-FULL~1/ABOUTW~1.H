//---------------------------------------------------------------------------
#ifndef AboutWindowFormH
#define AboutWindowFormH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
//---------------------------------------------------------------------------
class TAboutWindow : public TForm
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TMemo *Memo1;
	TButton *Button1;
	void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TAboutWindow(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TAboutWindow *AboutWindow;
//---------------------------------------------------------------------------
#endif
