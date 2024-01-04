//---------------------------------------------------------------------------
#ifndef DebugFrmH
#define DebugFrmH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
//---------------------------------------------------------------------------
class TDebugForm : public TForm
{
__published:	// IDE-managed Components
private:	// User declarations
public:		// User declarations
	__fastcall TDebugForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TDebugForm *DebugForm;
//---------------------------------------------------------------------------
#endif
