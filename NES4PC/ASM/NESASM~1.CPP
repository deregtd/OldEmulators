//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "nesasmfrm.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TStartFrm *StartFrm;
//---------------------------------------------------------------------------
AnsiString Mn[56] = {"ADC","AND","ASL","BCC","BCS","BEQ","BIT","BMI","BNE","BPL",
"BRK","BVC","BVS","CLC","CLD","CLI","CLV","CMP","CPX","CPY","DEC","DEX","DEY",
"EOR","INC","INX","INY","JMP","JSR","LDA","LDX","LDY","LSR","NOP","ORA","PHA",
"PHP","PLA","PLP","ROL","ROR","RTI","RTS",
"SBC","SEC","SED","SEI","STA","STX","STY","TAX","TAY","TSX","TXA","TXS","TYA"};
unsigned char InstrucMode[56] = {
0,0,0,1,1,1,0,1,1,1,2,1,1,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,2,2,2,2,0,0,2,2,0,2,2,2,0,0,0,2,2,2,2,2,2
};
unsigned char ByteForInst[56][13] = {

};
//---------------------------------------------------------------------------
struct SRCLineSt {
	unsigned char Inst, Addr;
	unsigned short int Address;
    
	unsigned char Bytes;
	unsigned char Data[2];

	bool TargetNeeded;
	AnsiString TargetLabel;

	unsigned char OutputByte;
} SRCLine[0x8000];
struct JmpLineSt {
	unsigned short int Addr;
	AnsiString Label;
} JmpLine[0x200];
//---------------------------------------------------------------------------
int totallines;
//---------------------------------------------------------------------------
void __fastcall TStartFrm::Button1Click(TObject *Sender)
{

/*
Status:

Need to do ByteForInst table
Need to implement comment skipping

First Pass Complete except for looking for jump labels and ByteForInst thingy

Need to implement second pass which will match the branch/jump instructions that need targets to their jump labels
	and set the data bytes accordingly as well as setting Address values for the SRCLine array entries
Need to implement third pass which will write the compiled data to an output file
*/
	char * tmpbuff = ""; AnsiString Buff, InstTxt; int linetotal = 0; unsigned short int tmpval; bool val8bit;
	FILE *in = fopen("c:\\nes4pc\\asm\\test.asm", "rt");
	fseek(in, 0, 2); int lenfile = ftell(in); fseek(in, 0, 0);

	while (ftell(in) < lenfile - 2)
	{
		fgets(tmpbuff, 20, in);
		Buff = (AnsiString(tmpbuff).TrimLeft()).UpperCase();

		InstTxt = LeftS(Buff, 3);
		SRCLine[linetotal].Inst = i;
		for (unsigned char i=0;i<56;i++)
			if (InstTxt == Mn[i]) SRCLine[linetotal].Inst = i;
		Buff.Delete(1,3);
		Buff = Buff.TrimLeft();

		if ((SRCLine[linetotal].Inst == JMP) || (SRCLine[linetotal].Inst == JSR) || (InstrucMode[SRCLine[linetotal].Inst] == 1)) SRCLine[linetotal].TargetNeeded = true;

		if (InstrucMode[SRCLine[linetotal].Inst] == 1) { SRCLine[linetotal].Addr = Rel; SRCLine[linetotal].Bytes = 1; }
		else if (InstrucMode[SRCLine[linetotal].Inst] == 2) { SRCLine[linetotal].Addr = Imp; SRCLine[linetotal].Bytes = 1; }
		else {
			if (Buff == "A") { SRCLine[linetotal].Addr = Acc; }
			else if (LeftS(Buff,1) == "#") { SRCLine[linetotal].Addr = Imm; InstTxt = RightS(Buff, Buff.Length() - 1); }
			else if (LeftS(Buff,1) == "(") {
				if (RightS(Buff,3) == "),Y") { SRCLine[linetotal].Addr = Idy; InstTxt = LeftS(Buff, Buff.Length() - 3); InstTxt = RightS(InstTxt, InstTxt.Length() - 1); }
				else if (RightS(Buff,3) == ",X)") { SRCLine[linetotal].Addr = Idx; InstTxt = LeftS(Buff, Buff.Length() - 3); InstTxt = RightS(InstTxt, InstTxt.Length() - 1); }
	            else { SRCLine[linetotal].Addr = Ind; InstTxt = LeftS(Buff, Buff.Length() - 1); InstTxt = RightS(InstTxt, InstTxt.Length() - 1); }
	        }
			else if (RightS(Buff,2) == ",X") {
				SRCLine[linetotal].Addr = Unx;
				InstTxt = LeftS(Buff, Buff.Length() - 2);
	        }
			else if (RightS(Buff,2) == ",Y") {
				SRCLine[linetotal].Addr = Uny;
				InstTxt = LeftS(Buff, Buff.Length() - 2);
			}
	 		else {
				SRCLine[linetotal].Addr = Unk;
				InstTxt = Buff;
	        }
		}

		if (SRCLine[linetotal].Addr > Acc) {
			tmpval = 0; val8bit = true;
			if (LeftS(InstTxt, 1) == "$") {	//Hex
				InstTxt.Delete(1,1);
				if (InstTxt.Length() == 2) val8bit = true;

				if (val8bit) { tmpval = HexToDec(InstTxt); }
				else { tmpval = (unsigned short int) ((HexToDec(LeftS(InstTxt,2)) << 8) | HexToDec(RightS(InstTxt,2))); }
			} else if (LeftS(InstTxt, 1) == "%") {	//Binary
				if (InstTxt[1] == 49) tmpval |= 128;
				if (InstTxt[2] == 49) tmpval |= 64;
				if (InstTxt[3] == 49) tmpval |= 32;
				if (InstTxt[4] == 49) tmpval |= 16;
				if (InstTxt[5] == 49) tmpval |= 8;
				if (InstTxt[6] == 49) tmpval |= 4;
				if (InstTxt[7] == 49) tmpval |= 2;
				if (InstTxt[8] == 49) tmpval |= 1;
				val8bit = true;
			} else {	//Decimal
				if ((SRCLine[linetotal].Inst != JMP) || (SRCLine[linetotal].Inst != JSR) || (InstrucMode[SRCLine[linetotal].Inst] != 1)) {
					tmpval = (unsigned short int) InstTxt.ToInt();
					if (tmpval > 255) val8bit = false;
				} else {
					SRCLine[linetotal].TargetLabel = InstTxt;
                }
			}

			SRCLine[linetotal].Data[0] = (BYTE) tmpval;
			if (val8bit) {
				if (SRCLine[linetotal].Addr == Unk) SRCLine[linetotal].Addr == Zp;
				if (SRCLine[linetotal].Addr == Unx) SRCLine[linetotal].Addr == Zpx;
				if (SRCLine[linetotal].Addr == Uny) SRCLine[linetotal].Addr == Zpy;
				SRCLine[linetotal].Bytes = 2;
			} else {
				SRCLine[linetotal].Data[1] = (BYTE) (tmpval >> 8);
				if (SRCLine[linetotal].Addr == Unk) SRCLine[linetotal].Addr == Abs;
				if (SRCLine[linetotal].Addr == Unx) SRCLine[linetotal].Addr == Absx;
				if (SRCLine[linetotal].Addr == Uny) SRCLine[linetotal].Addr == Absy;
				SRCLine[linetotal].Bytes = 3;
			}
		}

		SRCLine[linetotal].OutputByte = ByteForInst[SRCLine[linetotal].Inst][SRCLine[linetotal].Addr];

		linetotal++;
	}

	fclose(in);
}
//---------------------------------------------------------------------------
AnsiString LeftS(AnsiString tg, int len)
{ tg.SetLength(len); return(tg); }
AnsiString RightS(AnsiString tg, int len)
{ tg.Delete(1,tg.Length() - len); return(tg); }

BYTE __fastcall HexToDec(AnsiString tc)
{
	BYTE toret;
	if (((tc[1] >= 48) && (tc[1] <= 57)) && ((tc[2] >= 48) && (tc[2] <= 57))) toret = (BYTE) (16*(tc[1] - 48) + (tc[2] - 48));
	if (((tc[1] >= 48) && (tc[1] <= 57)) && ((tc[2] >= 65) && (tc[2] <= 70))) toret = (BYTE) (16*(tc[1] - 48) + (tc[2] - 55));
	if (((tc[1] >= 65) && (tc[1] <= 70)) && ((tc[2] >= 48) && (tc[2] <= 57))) toret = (BYTE) (16*(tc[1] - 55) + (tc[2] - 48));
	if (((tc[1] >= 65) && (tc[1] <= 70)) && ((tc[2] >= 65) && (tc[2] <= 70))) toret = (BYTE) (16*(tc[1] - 55) + (tc[2] - 55));
	return(toret);
}
//---------------------------------------------------------------------------
__fastcall TStartFrm::TStartFrm(TComponent* Owner) : TForm(Owner) { }
//---------------------------------------------------------------------------

