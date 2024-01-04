//---------------------------------------------------------------------------
#ifndef StatesH
#define StatesH
//---------------------------------------------------------------------------
void SaveState();
void LoadState();
void UpdateStateSel(BYTE NewState);
//---------------------------------------------------------------------------
//Typedefs
//---------------------------------------------------------------------------
typedef unsigned char BYTE;             //8-bit (BYTE)
typedef unsigned short int LBYTE;       //16-bit (Pentium WORD)
//---------------------------------------------------------------------------
//Version Defines (Emulator-specific, I just use these)
//---------------------------------------------------------------------------
#define verBaseRegs 1
#define verMemoryRegs 1
#define verStdSRAM 1
#define verMapperData 1
#define verControllers 1
//---------------------------------------------------------------------------
//Signature Number Defines for each type of block
//---------------------------------------------------------------------------
#define sigBaseRegs 0x01
#define sigMemoryRegs 0x02
#define sigStdSRAM 0x03
#define sigMapperData 0x04
#define sigControllers 0x05
//---------------------------------------------------------------------------
//Controller Type Defines
//---------------------------------------------------------------------------
#define jpJoypad 0
#define jpPaddle 1
#define jpZapper 2
#define jpQuadJoypad 3
#define jpRobot 4
#define jpPowerPad 5
//---------------------------------------------------------------------------
struct atom {
   unsigned  Sig : 24;
   unsigned  Ver : 8;
   unsigned  Size : 32;
};

struct stBaseRegsv1 {
   BYTE A, X, Y, P, SP; //Guess
   LBYTE PC;            //Ditto

   BYTE RAM[0x800];     //$0000-$0800 in the CPU
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
};

struct stMemRegsv1 {
   BYTE RegsPPU[2];      //$2000 and $2001
   BYTE RegsSound[0x16]; //$4000-$4015, don't use $4014, it's only there for
                         // padding to 32-bit alignment
};

struct stStdSRAMv1 {
   bool SRAMEnabled;    //If SRAM is enabled (eg. MMC3 which can enable and
                        // disable it at the switch of a bit)
   BYTE SRAM[0x2000];   //$6000-$7FFF of Main Memory (SRAM/WRAM)

   BYTE Padding[3];     //Pad to 32-bit alignment
};

struct stMapperDatav1 {
   LBYTE PRGPageNm[4], CHRPageNm[8]; //In order of occurence in the file, ROM
                                     // page numbers ($8/A/C/E000) and CHR
                                     // ($00/04/08/0C/10/14/18/1C00) page numbers.
   BYTE MMCData[128]; //Mapper data, not standardized yet, 128 bytes should
                      // be enough for all future mappers. =)
};

struct stControllersv1 {
   BYTE Type[2];                //Type of controller connected to each of the
                                // controller ports... See the defines section
                                // at the top for the number->controller map.
   unsigned long Bits[2];       //The bits that reads to $4016/$4017 would
                                // return in D0
   BYTE BitPointer[2];          //Which bit is currently selected for next
                                // being read via D0 of $4016/$4017
   bool Strobe[2];              //The strobe bit (written to $4016/$4017)

   bool PaddleButtPressed;      //Paddle: If the button is pressed
   BYTE PaddlePosition;         //Paddle: Numeric Position
   bool ZapperButtPressed;      //Zapper: If the button is pressed
   BYTE ZapperX, ZapperY;       //Zapper: (x,y) Coordinate being pointed at
   bool CoinInsert;             //VS System: If a coin is being inserted
};
//---------------------------------------------------------------------------
#endif
                
