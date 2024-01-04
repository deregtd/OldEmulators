//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#include <mem.h>
#pragma hdrstop

#include "States.h"
#include "6502.h"
#include "audio.h"
#include "mappers.h"
//---------------------------------------------------------------------------
BYTE SelState = 0;
AnsiString filename;
//---------------------------------------------------------------------------
extern BYTE A, X, Y, SP, P;
extern unsigned long int PC, TU;
extern bool NMIonVBlank,NMIonSprHit,SSize,BkPTA,SpPTA,PPUAdrI,SprVis,BGVis,SprClip,BGClip,DispType;
extern bool VBlankOcc,Spr0Occ,ScLnSprCnt,VRAMWrFlg, VFirstRead, SFirstRead, CPURunning, TUMode;
extern char ClockticksSm;
extern bool VBlanking, FakeSLUsing;
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
#define EndianSwap32b(A)        ((unsigned long) (((A & 0xFF000000) >> 24) | ((A & 0x00FF0000) >> 8) | ((A & 0x0000FF00) << 8) | ((A & 0x000000FF) << 24)))
#define EndianSwap16b(A)        ((LBYTE) (((A & 0xFF00) >> 8) | ((A & 0x00FF) << 8)))
//---------------------------------------------------------------------------
void SaveState()
{
        bool tpb = CPURunning;
        CPURunning = false;

        AnsiString tmpfnamea = filename + AnsiString(SelState);
        char * tmpfname = tmpfnamea.c_str();

        FILE * out = fopen(tmpfname, "wb");

        char TmpStr[4] = "SNSS";
        fwrite(&TmpStr, 4, 1, out);

        unsigned long NumBlocks = 3;
        if (Mem.CHRPages == 0) NumBlocks++;
        if (Mem.SRAMEnabled) NumBlocks++;
        if (Mem.MapperNum > 0) NumBlocks++;

        NumBlocks = EndianSwap32b(NumBlocks);
        fwrite(&NumBlocks, sizeof(NumBlocks), 1, out);

//Start Base Registers Block
        stBaseRegsv1 BR;
        atom BRAtom = { sigBaseRegs, EndianSwap32b(1), EndianSwap32b(sizeof(BR)) };

        BR.A = A; BR.X = X; BR.Y = Y; BR.P = P; BR.SP = SP; BR.PC = EndianSwap16b((LBYTE) (PC));

        for (int i=0;i<0x800;i++)
                BR.RAM[i] = *Mem.Main[i];
        memcpy(&BR.SPRRAM[0], &Mem.Sprite[0], 0x100);
        for (int i=0;i<0x1000;i++)
                BR.NameTables[i] = *Mem.PPU[0x2000 | i];
        for (int i=0;i<32;i++)
                BR.Palette[i] = *Mem.PPU[0x3F00 | i];
        memcpy(&BR.CurrMirroring[0], &Mem.CurrMirroring[0], 4);

        BR.VRAMAddress = EndianSwap16b((LBYTE) (Mem.VRAMAddress));
        BR.SPRRAMAddress = Mem.SPRAddress;
        BR.BgScrollX = Mem.BgScrollX;
        BR.BgScrollY = (BYTE) Mem.BgScrollY;

        fwrite(&BRAtom, sizeof(BRAtom), 1, out);
        fwrite(&BR, EndianSwap32b(BRAtom.Size), 1, out);
//End Base Registers Block

//Start Memory Registers Block
        stMemRegsv1 MR;
        atom MRAtom = { sigMemoryRegs, EndianSwap32b(1), EndianSwap32b(sizeof(MR)) };

        MR.RegsPPU[0] = (BYTE) (
                (NMIonVBlank << 7) |
                (SSize << 5) |
                (BkPTA << 4) |
                (SpPTA << 3) |
                (PPUAdrI << 2) |
                ((NTabAdr & 0x0C00) >> 10)
        );
        MR.RegsPPU[1] = (BYTE) (
                (SprVis << 4) |
                (BGVis << 3) |
                (SprClip << 2) |
                (BGClip << 1)
        );

        fwrite(&MRAtom, sizeof(MRAtom), 1, out);
        fwrite(&MR, EndianSwap32b(MRAtom.Size), 1, out);
//End Memory Registers Block

//Start Sound Block
        stSoundv1 SD;
        atom SDAtom = { sigSound, EndianSwap32b(1), EndianSwap32b(sizeof(SD)) };

        SD.RegsSound[0x14] = (BYTE) (PulseChan[0].Enabled | (PulseChan[1].Enabled << 1) | (TriChan.Enabled << 2) | (NoiseChan.Enabled << 3) | (DCMChan.Enabled << 4));

        fwrite(&SDAtom, sizeof(SDAtom), 1, out);
        fwrite(&SD, EndianSwap32b(SDAtom.Size), 1, out);
//End Sound Block

//Start VRAM Block
        if (Mem.CHRPages == 0)
        {
                atom VRAtom = { sigVRAM, EndianSwap32b(1), EndianSwap32b(0x2000)};

                if (Mem.MapperNum == 13)
                        VRAtom.Size = EndianSwap32b(0x4000);

                fwrite(&VRAtom, EndianSwap32b(sizeof(VRAtom)), 1, out);

                fwrite(&Mem.PatternTable[0][0], EndianSwap32b(VRAtom.Size), 1, out);
        }
//End VRAM Block

//Start Controllers Block
        stControllersv1 Co;
        atom CoAtom = { sigControllers, EndianSwap32b(1), EndianSwap32b(sizeof(Co)) };

        for (int h=0;h<2;h++)
        {
                Co.Type[h] = Joy.type[h];
                for (int i=0;i<24;i++)
                        Co.Bits[h] |= (Joy.Bits[h][i] << i);

                Co.BitPointer[h] = Joy.Count[h];
                Co.Strobe[h] = Joy.Strobe[h];
        }

        Co.Bits[0] = EndianSwap32b(Co.Bits[0]);
        Co.Bits[1] = EndianSwap32b(Co.Bits[1]);

        Co.PaddleButtPressed = Joy.PaddleButtPressed;
        Co.PaddlePosition = Joy.PaddlePosition;
        Co.ZapperButtPressed = Joy.ZapperButtPressed;
        Co.ZapperX = (BYTE) Joy.ZapperX;
        Co.ZapperY = (BYTE) Joy.ZapperY;
        Co.CoinInsert = Joy.CoinInsert;

        fwrite(&CoAtom, sizeof(CoAtom), 1, out);
        fwrite(&Co, EndianSwap32b(CoAtom.Size), 1, out);
//End Controllers Block

//Start SRAM Block
        bool SRW = false;
        for (int i=0;i<0x2000;i++)
                if (Mem.SRAM[i] > 0) SRW = true;

        if (SRW)
        {
                stSRAMv1 SR;
                atom SRAtom = { sigSRAM, EndianSwap32b(1), EndianSwap32b(sizeof(SR)) };

                SR.SRAMEnabled = Mem.SRAMEnabled;
                memcpy(&SR.SRAM[0], &Mem.SRAM[0], 0x2000);

                fwrite(&SRAtom, sizeof(SRAtom), 1, out);
                fwrite(&SR, EndianSwap32b(SRAtom.Size), 1, out);
        }
//End SRAM Block

//Start Mapper Data Block
        if (Mem.MapperNum > 0)
        {
                stMapperDatav1 MD;
                atom MDAtom = { sigMapperData, EndianSwap32b(1), EndianSwap32b(sizeof(MD)) };

                for (int i=0;i<4;i++)
                        MD.PRGPageNm[i] = EndianSwap16b(Mem.PRGPageNum[i]);
                for (int i=0;i<8;i++)
                        MD.CHRPageNm[i] = EndianSwap16b(Mem.CHRPageNum[i]);

                switch (Mem.MapperNum)
                {
                        case 1 :
                                memcpy(&MD.MMCData[0], &MMC1.Reg[0], 4);
                                MD.MMCData[4] = MMC1.Array;
                                MD.MMCData[5] = MMC1.ArrayPtr;
                                break;
                        case 4 :
                                MD.MMCData[0] = MMC3.IRQCounter;
                                MD.MMCData[1] = MMC3.IRQLatch;
                                MD.MMCData[2] = MMC3.IRQEnable;
                                MD.MMCData[3] = MMC3.PRGSelect;
                                MD.MMCData[4] = MMC3.CHRSelect;
                                MD.MMCData[5] = MMC3.Command;
                                break;
                        case 16 :
                                MD.MMCData[0] = (BYTE) (M16.IRQCounter);
                                MD.MMCData[1] = (BYTE) ((M16.IRQCounter) >> 8);
                                MD.MMCData[2] = M16.IRQEnabled;
                                break;
                        case 17 :
                                MD.MMCData[0] = (BYTE) (M17.IRQCounter);
                                MD.MMCData[1] = (BYTE) ((M17.IRQCounter) >> 8);
                                MD.MMCData[2] = M17.IRQEnabled;
                                break;
                        case 24 :
                                MD.MMCData[0] = M24.IRQCounter;
                                MD.MMCData[1] = M24.IRQEnable;
                                break;
                        case 230 :
                                MD.MMCData[0] = M22in1.Resets;
                                break;
                };

                fwrite(&MDAtom, sizeof(MDAtom), 1, out);
                fwrite(&MD, EndianSwap32b(MDAtom.Size), 1, out);
        }
//End Mapper Data Block

        fclose(out);

        CPURunning = tpb;
}

void LoadState()
{
        bool tpb = CPURunning;
        CPURunning = false;

//Reset all variables to beginning of frame status
        ScanLine = 0; VBlanking = false; ClockticksSm = 114;

        FakeSLUsing = false;

        NMIonVBlank = false; NMIonSprHit = false; SSize = false; BkPTA = false; SpPTA = false;
        Spr0Occ = false; VBlankOcc = false; PPUAdrI = false; SprVis = false; BGVis = false;
	SprClip = false; BGClip = false; DispType = false; ScLnSprCnt = false; VRAMWrFlg = false;
        VFirstRead = false; SFirstRead = false; TUMode = false;

        setmem(&Mem.SRAM[0], 0x2000, 0);

        Joy.Count[0] = 0; Joy.Count[1] = 0;
	Joy.Strobe[0] = 0; Joy.Strobe[1] = 0;
        setmem(&Joy.Bits[0][0], 48, 0);

        Mem.PRGPageNum[0] = 0; Mem.PRGPageNum[1] = 1;
        Mem.PRGPageNum[2] = (BYTE) (Mem.PRGPagesA - 2); Mem.PRGPageNum[3] = (BYTE) (Mem.PRGPagesA - 1);

        Mem.CHRPageNumNew[0] = 0; Mem.CHRPageNumNew[1] = 1; Mem.CHRPageNumNew[2] = 2;
        Mem.CHRPageNumNew[3] = 3; Mem.CHRPageNumNew[4] = 4; Mem.CHRPageNumNew[5] = 5;
        Mem.CHRPageNumNew[6] = 6; Mem.CHRPageNumNew[7] = 7;

        Mem.UpdateCHRPointers();

        AnsiString tmpfnamea = filename + AnsiString(SelState);
	char * tmpfname = tmpfnamea.c_str();

	FILE * in = fopen(tmpfname, "r+b");

        BYTE tmpbyte; char TmpStr[4];

        fread(&TmpStr[4], 4, 1, in);

//Get # of Blocks
        unsigned long NumBlocks;
        fread(&NumBlocks, 4, 1, in);
        NumBlocks = EndianSwap32b(NumBlocks);
        atom tmpAtom;

//Parse Blocks
        stBaseRegsv1 BRv1;
        stMemRegsv1 MRv1;
        stSoundv1 SDv1;
        stSRAMv1 SRv1;
        stMapperDatav1 MDv1;
        stControllersv1 Cov1;
        int h, i;

        for (unsigned long bnt=0;bnt<NumBlocks;bnt++)
        {
                fread(&tmpAtom, sizeof(tmpAtom), 1, in);
                tmpAtom.Size = EndianSwap32b(tmpAtom.Size);
                tmpAtom.Version = EndianSwap32b(tmpAtom.Version);
                if (strncmp(tmpAtom.Sig, sigBaseRegs, 4) == 0) {
                        if (tmpAtom.Version == 1) {
                                fread(&BRv1, tmpAtom.Size, 1, in);

                                A = BRv1.A; X = BRv1.X; Y = BRv1.Y; P = BRv1.P; SP = BRv1.SP; PC = EndianSwap16b(BRv1.PC);

                                for (i=0;i<0x800;i++)
                                        *Mem.Main[i] = BRv1.RAM[i];

                                memcpy(&Mem.Sprite[0], &BRv1.SPRRAM[0], 0x100);

                                for (i=0;i<0x1000;i++)
                                        *Mem.PPU[0x2000 | i] = BRv1.NameTables[i];
                                for (i=0;i<32;i++)
                                        *Mem.PPU[0x3F00 | i] = BRv1.Palette[i];

                                Mem.UpdateNameTablePointers(BRv1.CurrMirroring[0],BRv1.CurrMirroring[1],BRv1.CurrMirroring[2],BRv1.CurrMirroring[3]);

                                Mem.VRAMAddress = EndianSwap16b(BRv1.VRAMAddress);
                                Mem.SPRAddress = BRv1.SPRRAMAddress;
                                Mem.BgScrollX = BRv1.BgScrollX;
                                Mem.BgScrollY = BRv1.BgScrollY;
                        }
                } else if (strncmp(tmpAtom.Sig, sigMemoryRegs, 4) == 0) {
                        if (tmpAtom.Version == 1) {
                                fread(&MRv1, tmpAtom.Size, 1, in);

                                NTabAdr = (LBYTE) (((MRv1.RegsPPU[0] & 3) << 10) | 0x2000);
                                PPUAdrI = MRv1.RegsPPU[0] & 4;
                                SpPTA = MRv1.RegsPPU[0] & 8;
                                BkPTA = MRv1.RegsPPU[0] & 16;
                                SSize = MRv1.RegsPPU[0] & 32;
                                NMIonVBlank = MRv1.RegsPPU[0] & 128;

                                BGClip = MRv1.RegsPPU[1] & 2;
                                SprClip = MRv1.RegsPPU[1] & 4;
                                BGVis = MRv1.RegsPPU[1] & 8;
                                SprVis = MRv1.RegsPPU[1] & 16;
                        }
                } else if (strncmp(tmpAtom.Sig, sigSound, 4) == 0) {
                        if (tmpAtom.Version == 1) {
                                fread(&SDv1, tmpAtom.Size, 1, in);

                                PulseChan[0].Enabled = SDv1.RegsSound[0x15] & 1;
                                PulseChan[1].Enabled = SDv1.RegsSound[0x15] & 2;
                                TriChan.Enabled = SDv1.RegsSound[0x15] & 4;
                                NoiseChan.Enabled = SDv1.RegsSound[0x15] & 8;
                                DCMChan.Enabled = SDv1.RegsSound[0x15] & 16;
                        }
                } else if (strncmp(tmpAtom.Sig, sigVRAM, 4) == 0) {
                        if (tmpAtom.Version == 1) {
                                fread(&Mem.PatternTable[0][0], 1, tmpAtom.Size, in);
                        }
                } else if (strncmp(tmpAtom.Sig, sigControllers, 4) == 0) {
                        if (tmpAtom.Version == 1) {
                                fread(&Cov1, tmpAtom.Size, 1, in);

                                for (h=0;h<2;h++)
                                {
                                        Joy.type[h] = Cov1.Type[h];
                                        for (i=0;i<24;i++)
                                                Joy.Bits[h][i] = EndianSwap32b(Cov1.Bits[h]) & (1 << i);

                                        Joy.Count[h] = Cov1.BitPointer[h];
                                        Joy.Strobe[h] = Cov1.Strobe[h];
                                }

                                Joy.PaddleButtPressed = Cov1.PaddleButtPressed;
                                Joy.PaddlePosition = Cov1.PaddlePosition;
                                Joy.ZapperButtPressed = Cov1.ZapperButtPressed;
                                Joy.ZapperX = Cov1.ZapperX;
                                Joy.ZapperY = Cov1.ZapperY;
                                Joy.CoinInsert = Cov1.CoinInsert;
                        }
                } else if (strncmp(tmpAtom.Sig, sigSRAM, 4) == 0) {
                        if (tmpAtom.Version == 1) {
                                fread(&SRv1, tmpAtom.Size, 1, in);

                                Mem.SRAMEnabled = SRv1.SRAMEnabled;
                                memcpy(&Mem.SRAM[0], &SRv1.SRAM[0], 0x2000);
                        }
                } else if (strncmp(tmpAtom.Sig, sigMapperData, 4) == 0) {
                        if (tmpAtom.Version == 1) {
                                fread(&MDv1, tmpAtom.Size, 1, in);

                                for (int i=0;i<4;i++)
                                        Mem.PRGPageNum[i] = EndianSwap16b(MDv1.PRGPageNm[i]);
                                for (int i=0;i<8;i++)
                                        Mem.CHRPageNum[i] = EndianSwap16b(MDv1.CHRPageNm[i]);

                                Mem.UpdateCHRPointers();

                                if (Mem.MapperNum == 1)
                                {
                                        memcpy(&MMC1.Reg[0], &MDv1.MMCData[0], 4);
                                        MMC1.Array = MDv1.MMCData[4];
                                        MMC1.ArrayPtr = MDv1.MMCData[5];

                                        MMC1.PRGSwitch = bit2(MMC1.Reg[0]);
                                        MMC1.PRGSwitchSize = bit3(MMC1.Reg[0]);
                                        MMC1.VROMSwitchSize = bit4(MMC1.Reg[0]);
                                        MMC1.PRGPageSwitch = bit4(MMC1.Reg[1]);
                                } else if (Mem.MapperNum == 4) {
                                        MMC3.IRQCounter = MDv1.MMCData[0];
                                        MMC3.IRQLatch = MDv1.MMCData[1];
                                        MMC3.IRQEnable = MDv1.MMCData[2];
                                        MMC3.PRGSelect = MDv1.MMCData[3];
                                        MMC3.CHRSelect = MDv1.MMCData[4];
                                        MMC3.Command = MDv1.MMCData[5];
                                } else if (Mem.MapperNum == 16) {
                                        M16.IRQCounter = (LBYTE) ((MDv1.MMCData[1] << 8) | MDv1.MMCData[0]);
                                        M16.IRQEnabled = MDv1.MMCData[2];
                                } else if (Mem.MapperNum == 17) {
                                        M17.IRQCounter = (LBYTE) ((MDv1.MMCData[1] << 8) | MDv1.MMCData[0]);
                                        M17.IRQEnabled = MDv1.MMCData[2];
                                } else if (Mem.MapperNum == 24) {
                                        M24.IRQCounter = MDv1.MMCData[0];
                                        M24.IRQEnable = MDv1.MMCData[1];
                                } else if (Mem.MapperNum == 230) {
                                        M22in1.Resets = MDv1.MMCData[0];
                                }
                        }
                } else {
                        for (unsigned long i=0;i<tmpAtom.Size;i++)
                                fread(&tmpbyte, 1, 1, in);
                }
        }

	fclose(in);

        CPURunning = tpb;
}
void UpdateStateSel(BYTE NewState)
{
	SelState = NewState;
}
//---------------------------------------------------------------------------

