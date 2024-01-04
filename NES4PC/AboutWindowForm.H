//---------------------------------------------------------------------------
#ifndef AboutWindowFormH
#define AboutWindowFormH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TAboutWindow : public TForm
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox1;
	TLabel *Label2;
	TLabel *Label3;
	TButton *Button1;
	TImage *Image1;
	void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TAboutWindow(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TAboutWindow *AboutWindow;
//---------------------------------------------------------------------------
#endif
