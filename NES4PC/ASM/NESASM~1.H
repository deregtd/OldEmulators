//---------------------------------------------------------------------------
#ifndef nesasmfrmH
#define nesasmfrmH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Dialogs.hpp>
//---------------------------------------------------------------------------
class TStartFrm : public TForm
{
__published:	// IDE-managed Components
	TSaveDialog *SaveDialog1;
	TOpenDialog *OpenDialog1;
	TOpenDialog *OpenDialog2;
	TButton *Button1;
	void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TStartFrm(TComponent* Owner);
};
extern TStartFrm *StartFrm;
//---------------------------------------------------------------------------
AnsiString LeftS(AnsiString tg, int len);
AnsiString RightS(AnsiString tg, int len);
BYTE __fastcall HexToDec(AnsiString tc);
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//Definitions - Addressing Modes
//---------------------------------------------------------------------------
#define Imp						0 //[nothing] - D
#define Acc						1 //A - D
#define Imm						2 //#aa - D
#define Abs						3 //aaaa - D
#define Zp						4 //aa - D
#define Ind						5 //(aaaa) - D
#define Absx					6 //aaaa,X - D
#define Absy					7 //aaaa,Y - D
#define Zpx						8 //aa,X - D
#define Zpy						9 //aa,Y - D
#define Idx						10 //(aa,X) - D
#define Idy						11 //(aa),Y - D
#define Rel						12 //aa - D

#define Unk						50
#define Unx						51
#define Uny						52
//---------------------------------------------------------------------------
//Definitions - Opcodes
//---------------------------------------------------------------------------
#define ADC	0
#define AND	1
#define ASL	2
#define BCC	3
#define BCS	4
#define BEQ 5
#define BIT 6
#define BMI	7
#define BNE	8
#define BPL	9
#define BRK	10
#define BVC	11
#define BVS	12
#define CLC	13
#define CLD	14
#define CLI	15
#define CLV	16
#define CMP	17
#define CPX	18
#define CPY	19
#define DEC	20
#define DEX	21
#define DEY	22
#define EOR	23
#define INC	24
#define INX	25
#define INY	26
#define JMP	27
#define JSR	28
#define LDA	29
#define LDX	30
#define LDY	31
#define LSR	32
#define NOP	33
#define ORA	34
#define PHA	35
#define PHP	36
#define PLA	37
#define PLP	38
#define ROL	39
#define ROR	40
#define RTI	41
#define RTS	42
#define SBC	43
#define SEC	44
#define SED	45
#define SEI	46
#define STA	47
#define STX	48
#define STY	49
#define TAX	50
#define TAY	51
#define TSX	52
#define TXA	53
#define TXS	54
#define TYA	55
//---------------------------------------------------------------------------
#endif
