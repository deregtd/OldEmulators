//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#include <mem.h>
#pragma hdrstop

#include "States.h"
#include "6502.h"
#include "audio.h"
//---------------------------------------------------------------------------
BYTE SelState = 0;
AnsiString filename;
//---------------------------------------------------------------------------
extern BYTE A, X, Y, SP, P;
extern unsigned long int PC, TU;
extern bool NMIonVBlank,NMIonSprHit,SSize,BkPTA,SpPTA,PPUAdrI,SprVis,BGVis,SprClip,BGClip,DispType;
extern bool VBlankOcc,Spr0Occ,ScLnSprCnt,VRAMWrFlg, VFirstRead, SFirstRead, CPURunning, TUMode;
extern LBYTE NTabAdr;
extern MemSt Mem;
extern PulseChanSt PulseChan[2];
extern TriChanSt TriChan;
extern NoiseChanSt NoiseChan;
extern DCMChanSt DCMChan;

extern short int ScanLine;

extern JoypadSt Joy;

extern MMC1St MMC1;
extern MMC3St MMC3;
extern M22in1St M22in1;
extern M16St M16;
extern M17St M17;
extern M90St M90;
extern M24St M24;
//---------------------------------------------------------------------------
struct SaveStateStruct {
   BYTE A, X, Y, P, SP; //Guess
   LBYTE PC;            //Ditto

   BYTE PRGPage[4], CHRPage[8]; //In order of occurence in the file, ROM
                                // page numbers ($8/A/C/E000) and CHR
                                // ($00/04/08/0C/10/14/18/1C00) page numbers.

   BYTE RAM[0x800];     //$0000-$0800 in the CPU
   bool SRAMEnabled;    //Is SaveRAM enabled?  (Mappers like MMC3 can
                        // change this while the cart's running, remember...)
   BYTE SRAM[0x2000];   //Save RAM

   BYTE VRAM[0x2000];   //If VRAM is present, else leave zeroed out and just
                        //use the CHRPage[]
   BYTE SPRRAM[0x100];  // Sprite RAM
   BYTE NameTables[0x1000];     //$2000-$2FFF in the PPU
   BYTE Palette[32];            //$3F00-$3F1F in the PPU
   BYTE CurrMirroring[4];       //Which name table each is getting its data
                                //from... Examples:
                                //4-screen mirroring: 0,1,2,3
                                //Mirror from $2000: 0,0,0,0
                                //Horizontal: 0,0,2,2
                                //Vertical: 0,1,0,1

   LBYTE VRAMAddress;         //Guess
   BYTE SPRRAMAddress;        //Ditto
   BYTE BgScrollX, BgScrollY; //Ditto

   BYTE RegsPPU[2];      //$2000 and $2001
   BYTE RegsSound[0x15]; //$4000-$4013 and $4015

   BYTE MMCData[128]; //Mapper data, not standardized yet, 128 bytes should
                      // be enough for all future mappers. =)
};
//---------------------------------------------------------------------------
void SaveState()
{
        AnsiString tmpfnamea = filename + AnsiString(SelState);
        char * tmpfname = tmpfnamea.c_str();

        FILE * out = fopen(tmpfname, "wb");

        SaveStateStruct ts;

        ts.A = A; ts.X = X; ts.Y = Y; ts.P = P; ts.SP = SP; ts.PC = (LBYTE) PC;

        memcpy(&ts.PRGPage[0], &Mem.PRGPageNum[0], 4);
        memcpy(&ts.CHRPage[0], &Mem.CHRPageNum[0], 8);

        memcpy(&ts.RAM[0], &Mem.MainRAM[0], 0x800);
        ts.SRAMEnabled = Mem.SRAMEnabled;
        memcpy(&ts.SRAM[0], &Mem.SRAM[0], 0x2000);
        if (Mem.CHRPages == 0)
                for (int i=0;i<8;i++)
                        memcpy(&ts.VRAM[i << 10], &Mem.CHRPage[i][0], 0x400);
        memcpy(&ts.SPRRAM[0], &Mem.Sprite[0], 0x100);
        for (int i=0;i<0x1000;i++)
                ts.NameTables[i] = *Mem.PPU[0x2000 | i];
        for (int i=0;i<32;i++)
                ts.Palette[i] = *Mem.PPU[0x3F00 | i];
        memcpy(&ts.CurrMirroring[0], &Mem.CurrMirroring[0], 4);

        ts.VRAMAddress = (LBYTE) Mem.VRAMAddress;
        ts.SPRRAMAddress = Mem.SPRAddress;
        ts.BgScrollX = Mem.BgScrollX;
        ts.BgScrollY = (BYTE) Mem.BgScrollY;

        ts.RegsPPU[0] = (BYTE) (
                (NMIonVBlank << 7) |
                (SSize << 5) |
                (BkPTA << 4) |
                (SpPTA << 3) |
                (PPUAdrI << 2) |
                ((NTabAdr & 0x0C00) >> 10)
        );
        ts.RegsPPU[1] = (BYTE) (
                (SprVis << 4) |
                (BGVis << 3) |
                (SprClip << 2) |
                (BGClip << 1)
        );

        ts.RegsSound[0x14] = (BYTE) (PulseChan[0].Enabled | (PulseChan[1].Enabled << 1) | (TriChan.Enabled << 2) | (NoiseChan.Enabled << 3) | (DCMChan.Enabled << 4));

        setmem(&ts.MMCData[0],128,0)
        switch (Mem.MapperNum) {
                case 1 :
                        
                        break;
        };

        fwrite(&ts, sizeof(ts), 1, out);
        fclose(out);
}
void LoadState()
{
	AnsiString tmpfnamea = filename + AnsiString(SelState);
	char * tmpfname = tmpfnamea.c_str();

	FILE * in = fopen(tmpfname, "r+b");

	SaveStateStruct ts;
	fread(&ts, sizeof(ts), 1, in);

	ScanLine = 0;
	NMIonVBlank = false; NMIonSprHit = false; SSize = false; BkPTA = false; SpPTA = false;
        Spr0Occ = false; VBlankOcc = false; PPUAdrI = false; SprVis = false; BGVis = false;
	SprClip = false; BGClip = false; DispType = false; ScLnSprCnt = false; VRAMWrFlg = false;
	VFirstRead = false; SFirstRead = false; TUMode = false;

	Joy.Count[0] = 0; Joy.Count[1] = 0;
	Joy.Strobe[0] = 0; Joy.Strobe[1] = 0;
	setmem(&Joy.Bits[0][0], 48, 0);

        A = ts.A; X = ts.X; Y = ts.Y; P = ts.P; SP = ts.SP; PC = ts.PC;

        memcpy(&Mem.PRGPageNum[0], &ts.PRGPage[0], 4);
        memcpy(&Mem.CHRPageNumNew[0], &ts.CHRPage[0], 8);
        Mem.UpdateCHRPointers();

        memcpy(&Mem.MainRAM[0], &ts.RAM[0], 0x800);
        Mem.SRAMEnabled = ts.SRAMEnabled;
        memcpy(&Mem.SRAM[0], &ts.SRAM[0], 0x2000);

        if (Mem.CHRPages == 0)
                for (int i=0;i<8;i++)
                        memcpy(&Mem.CHRPage[i][0], &ts.VRAM[i << 10], 0x400);

        memcpy(&Mem.Sprite[0], &ts.SPRRAM[0], 0x100);

        for (int i=0;i<0x1000;i++)
                *Mem.PPU[0x2000 | i] = ts.NameTables[i];
        for (int i=0;i<32;i++)
                *Mem.PPU[0x3F00 | i] = ts.Palette[i];

        Mem.UpdateNameTablePointers(ts.CurrMirroring[0],ts.CurrMirroring[1],ts.CurrMirroring[2],ts.CurrMirroring[3]);

        Mem.VRAMAddress = ts.VRAMAddress;
        Mem.SPRAddress = ts.SPRRAMAddress;
        Mem.BgScrollX = ts.BgScrollX;
        Mem.BgScrollY = ts.BgScrollY;

        NTabAdr = (LBYTE) (((ts.RegsPPU[0] & 3) << 10) | 0x2000);
        PPUAdrI = ts.RegsPPU[0] & 4;
        SpPTA = ts.RegsPPU[0] & 8;
        BkPTA = ts.RegsPPU[0] & 16;
        SSize = ts.RegsPPU[0] & 32;
        NMIonVBlank = ts.RegsPPU[0] & 128;

        BGClip = ts.RegsPPU[1] & 2;
        SprClip = ts.RegsPPU[1] & 4;
        BGVis = ts.RegsPPU[1] & 8;
        SprVis = ts.RegsPPU[1] & 16;

        PulseChan[0].Enabled = ts.RegsSound[0x14] & 1;
        PulseChan[1].Enabled = ts.RegsSound[0x14] & 2;
        TriChan.Enabled = ts.RegsSound[0x14] & 4;
        NoiseChan.Enabled = ts.RegsSound[0x14] & 8;
        DCMChan.Enabled = ts.RegsSound[0x14] & 16;

        switch (Mem.MapperNum) {
        };

	fclose(in);
}
void UpdateStateSel(BYTE NewState)
{
	SelState = NewState;
}
//---------------------------------------------------------------------------

