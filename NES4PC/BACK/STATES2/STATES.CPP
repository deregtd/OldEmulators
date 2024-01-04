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
void SaveState()
{
        bool tpb = CPURunning;
        CPURunning = false;

        AnsiString tmpfnamea = filename + AnsiString(SelState);
        char * tmpfname = tmpfnamea.c_str();

        FILE * out = fopen(tmpfname, "wb");

        unsigned long NumBlocks = 3;
        if (Mem.SRAMEnabled) NumBlocks++;
        if (Mem.MapperNum > 0) NumBlocks++;

        fwrite(&NumBlocks, 4, 1, out);

//Start Base Registers Block
        stBaseRegsv1 BR;
        atom BRAtom = { sigBaseRegs, verBaseRegs, sizeof(BR) };

        BR.A = A; BR.X = X; BR.Y = Y; BR.P = P; BR.SP = SP; BR.PC = (LBYTE) PC;

        for (int i=0;i<0x800;i++)
                BR.RAM[i] = *Mem.Main[i];
        if (Mem.CHRPages == 0)
                memcpy(&BR.VRAM[0], &Mem.PatternTable[0][0], 0x2000);
        memcpy(&BR.SPRRAM[0], &Mem.Sprite[0], 0x100);
        for (int i=0;i<0x1000;i++)
                BR.NameTables[i] = *Mem.PPU[0x2000 | i];
        for (int i=0;i<32;i++)
                BR.Palette[i] = *Mem.PPU[0x3F00 | i];
        memcpy(&BR.CurrMirroring[0], &Mem.CurrMirroring[0], 4);

        BR.VRAMAddress = (LBYTE) Mem.VRAMAddress;
        BR.SPRRAMAddress = Mem.SPRAddress;
        BR.BgScrollX = Mem.BgScrollX;
        BR.BgScrollY = (BYTE) Mem.BgScrollY;

        fwrite(&BRAtom, sizeof(BRAtom), 1, out);
        fwrite(&BR, BRAtom.Size, 1, out);
//End Base Registers Block

//Start Memory Registers Block
        stMemRegsv1 MR;
        atom MRAtom = { sigMemoryRegs, verMemoryRegs, sizeof(MR) };

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

        MR.RegsSound[0x14] = (BYTE) (PulseChan[0].Enabled | (PulseChan[1].Enabled << 1) | (TriChan.Enabled << 2) | (NoiseChan.Enabled << 3) | (DCMChan.Enabled << 4));

        fwrite(&MRAtom, sizeof(MRAtom), 1, out);
        fwrite(&MR, MRAtom.Size, 1, out);
//End Memory Registers Block

//Start Controllers Block
        stControllersv1 Co;
        atom CoAtom = { sigControllers, verControllers, sizeof(Co) };

        for (int h=0;h<2;h++)
        {
                Co.Type[h] = Joy.type[h];
                for (int i=0;i<24;i++)
                        Co.Bits[h] |= (Joy.Bits[h][i] << i);

                Co.BitPointer[h] = Joy.Count[h];
                Co.Strobe[h] = Joy.Strobe[h];
        }

        Co.PaddleButtPressed = Joy.PaddleButtPressed;
        Co.PaddlePosition = Joy.PaddlePosition;
        Co.ZapperButtPressed = Joy.ZapperButtPressed;
        Co.ZapperX = (BYTE) Joy.ZapperX;
        Co.ZapperY = (BYTE) Joy.ZapperY;
        Co.CoinInsert = Joy.CoinInsert;

        fwrite(&CoAtom, sizeof(CoAtom), 1, out);
        fwrite(&Co, CoAtom.Size, 1, out);
//End Controllers Block

//Start Standard SRAM Block
        bool SRW = false;
        for (int i=0;i<0x2000;i++)
                if (Mem.SRAM[i] > 0) SRW = true;

        if (SRW)
        {
                stStdSRAMv1 SR;
                atom SRAtom = { sigStdSRAM, verStdSRAM, sizeof(SR) };

                SR.SRAMEnabled = Mem.SRAMEnabled;
                memcpy(&SR.SRAM[0], &Mem.SRAM[0], 0x2000);

                fwrite(&SRAtom, sizeof(SRAtom), 1, out);
                fwrite(&SR, SRAtom.Size, 1, out);
        }
//End Standard SRAM Block

//Start Mapper Data Block
        if (Mem.MapperNum > 0)
        {
                stMapperDatav1 MD;
                atom MDAtom = { sigMapperData, verMapperData, sizeof(MD) };

                memcpy(&MD.PRGPageNm[0], &Mem.PRGPageNum[0], 4 *2);
                memcpy(&MD.CHRPageNm[0], &Mem.CHRPageNum[0], 8 *2);

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
                fwrite(&MD, MDAtom.Size, 1, out);
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
        ScanLine = 0; VBlanking = false; ClockticksSm = 113;

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

        BYTE tmpbyte;

//Get # of Blocks
        unsigned long NumBlocks;
        fread(&NumBlocks, 4, 1, in);
        atom tmpAtom;

//Parse Blocks
        for (unsigned long bnt=0;bnt<NumBlocks;bnt++)
        {
                fread(&tmpAtom, sizeof(tmpAtom), 1, in);
                switch (tmpAtom.Sig)
                {
                        case 0x01 :     //Base Regs
                                switch (tmpAtom.Ver)
                                {
                                        case 1 :
                                                stBaseRegsv1 BRv1;
                                                fread(&BRv1, tmpAtom.Size, 1, in);

                                                A = BRv1.A; X = BRv1.X; Y = BRv1.Y; P = BRv1.P; SP = BRv1.SP; PC = BRv1.PC;

                                                for (int i=0;i<0x800;i++)
                                                         *Mem.Main[i] = BRv1.RAM[i];

                                                if (Mem.CHRPages == 0)
                                                        memcpy(&Mem.PatternTable[0][0], &BRv1.VRAM[0], 0x2000);

                                                memcpy(&Mem.Sprite[0], &BRv1.SPRRAM[0], 0x100);

                                                for (int i=0;i<0x1000;i++)
                                                        *Mem.PPU[0x2000 | i] = BRv1.NameTables[i];
                                                for (int i=0;i<32;i++)
                                                        *Mem.PPU[0x3F00 | i] = BRv1.Palette[i];

                                                Mem.UpdateNameTablePointers(BRv1.CurrMirroring[0],BRv1.CurrMirroring[1],BRv1.CurrMirroring[2],BRv1.CurrMirroring[3]);

                                                Mem.VRAMAddress = BRv1.VRAMAddress;
                                                Mem.SPRAddress = BRv1.SPRRAMAddress;
                                                Mem.BgScrollX = BRv1.BgScrollX;
                                                Mem.BgScrollY = BRv1.BgScrollY;

                                                break;
                                };
                                break;
                        case 0x02 :     //Memory Regs
                                switch (tmpAtom.Ver)
                                {
                                        case 1 :
                                                stMemRegsv1 MRv1;
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

                                                PulseChan[0].Enabled = MRv1.RegsSound[0x15] & 1;
                                                PulseChan[1].Enabled = MRv1.RegsSound[0x15] & 2;
                                                TriChan.Enabled = MRv1.RegsSound[0x15] & 4;
                                                NoiseChan.Enabled = MRv1.RegsSound[0x15] & 8;
                                                DCMChan.Enabled = MRv1.RegsSound[0x15] & 16;

                                                break;
                                };
                                break;
                        case 0x03 :     //Standard SRAM
                                switch (tmpAtom.Ver)
                                {
                                        case 1 :
                                                stStdSRAMv1 SRv1;
                                                fread(&SRv1, tmpAtom.Size, 1, in);

                                                Mem.SRAMEnabled = SRv1.SRAMEnabled;
                                                memcpy(&Mem.SRAM[0], &SRv1.SRAM[0], 0x2000);

                                                break;
                                };
                                break;
                        case 0x04 :     //Mapper Data
                                switch (tmpAtom.Ver)
                                {
                                        case 1 :
                                                stMapperDatav1 MDv1;
                                                fread(&MDv1, tmpAtom.Size, 1, in);
                                                memcpy(&Mem.PRGPageNum[0], &MDv1.PRGPageNm[0], 4 *2);

                                                memcpy(&Mem.CHRPageNumNew[0], &MDv1.CHRPageNm[0], 8 *2);

                                                Mem.UpdateCHRPointers();

                                                switch (Mem.MapperNum)
                                                {
                                                        case 1 :
                                                                memcpy(&MMC1.Reg[0], &MDv1.MMCData[0], 4);
                                                                MMC1.Array = MDv1.MMCData[4];
                                                                MMC1.ArrayPtr = MDv1.MMCData[5];

                                                                MMC1.PRGSwitch = bit2(MMC1.Reg[0]);
                                                                MMC1.PRGSwitchSize = bit3(MMC1.Reg[0]);
                                                                MMC1.VROMSwitchSize = bit4(MMC1.Reg[0]);
                                                                MMC1.PRGPageSwitch = bit4(MMC1.Reg[1]);
                                                                break;
                                                        case 4 :
                                                                MMC3.IRQCounter = MDv1.MMCData[0];
                                                                MMC3.IRQLatch = MDv1.MMCData[1];
                                                                MMC3.IRQEnable = MDv1.MMCData[2];
                                                                MMC3.PRGSelect = MDv1.MMCData[3];
                                                                MMC3.CHRSelect = MDv1.MMCData[4];
                                                                MMC3.Command = MDv1.MMCData[5];
                                                                break;
                                                        case 16 :
                                                                M16.IRQCounter = (LBYTE) ((MDv1.MMCData[1] << 8) | MDv1.MMCData[0]);
                                                                M16.IRQEnabled = MDv1.MMCData[2];
                                                                break;
                                                        case 17 :
                                                                M17.IRQCounter = (LBYTE) ((MDv1.MMCData[1] << 8) | MDv1.MMCData[0]);
                                                                M17.IRQEnabled = MDv1.MMCData[2];
                                                                break;
                                                        case 24 :
                                                                M24.IRQCounter = MDv1.MMCData[0];
                                                                M24.IRQEnable = MDv1.MMCData[1];
                                                                break;
                                                        case 230 :
                                                                M22in1.Resets = MDv1.MMCData[0];
                                                                break;
                                                };
                                                break;
                                };
                                break;
                        case 0x05 :
                                switch (tmpAtom.Ver)
                                {
                                        case 1 :
                                                stControllersv1 Cov1;
                                                fread(&Cov1, tmpAtom.Size, 1, in);

                                                for (int h=0;h<2;h++)
                                                {
                                                        Joy.type[h] = Cov1.Type[h];
                                                        for (int i=0;i<24;i++)
                                                                Joy.Bits[h][i] = Cov1.Bits[h] & (1 << i);

                                                        Joy.Count[h] = Cov1.BitPointer[h];
                                                        Joy.Strobe[h] = Cov1.Strobe[h];
                                                }

                                                Joy.PaddleButtPressed = Cov1.PaddleButtPressed;
                                                Joy.PaddlePosition = Cov1.PaddlePosition;
                                                Joy.ZapperButtPressed = Cov1.ZapperButtPressed;
                                                Joy.ZapperX = Cov1.ZapperX;
                                                Joy.ZapperY = Cov1.ZapperY;
                                                Joy.CoinInsert = Cov1.CoinInsert;

                                                break;
                                };
                                break;
                        default :
                                for (unsigned long i=0;i<tmpAtom.Size;i++)
                                        fread(&tmpbyte, 1, 1, in);
                                break;
                };
        }

	fclose(in);

        CPURunning = tpb;
}
void UpdateStateSel(BYTE NewState)
{
	SelState = NewState;
}
//---------------------------------------------------------------------------

