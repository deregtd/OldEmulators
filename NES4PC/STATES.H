//---------------------------------------------------------------------------
#ifndef StatesH
#define StatesH
//---------------------------------------------------------------------------
void SaveState();
void LoadState();
void UpdateStateSel(unsigned char NewState);
//---------------------------------------------------------------------------
//Signature Defines for each type of block
//---------------------------------------------------------------------------
#define sigBaseRegs     "BASR"
#define sigMemoryRegs   "MEMR"
#define sigVRAM         "VRAM"
#define sigSRAM         "SRAM"
#define sigMapperData   "MPRD"
#define sigControllers  "CNTR"
#define sigSound        "SOUN"
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
   char Sig[4];
   unsigned long Version;
   unsigned long Size;
};

struct stBaseRegsv1 {
//   unsigned char A, X, Y, P, SP; //Guess
//   unsigned short int PC;            //Ditto

   unsigned char RAM[0x800];     //$0000-$0800 in the CPU
   unsigned char SPRRAM[0x100];  // Sprite RAM
   unsigned char NameTables[0x1000];     //$2000-$2FFF in the PPU
   unsigned char Palette[32];            //$3F00-$3F1F in the PPU
   unsigned char CurrMirroring[4];       //Which name table each is getting its data
                                //from... Examples:
                                //4-screen mirroring: 0,1,2,3
                                //Mirror from $2000: 0,0,0,0
                                //Horizontal: 0,0,2,2
                                //Vertical: 0,1,0,1

   unsigned short int VRAMAddress;         //Guess
   unsigned char SPRRAMAddress;        //Ditto
   unsigned char BgScrollX, BgScrollY; //Ditto
};

struct stMemRegsv1 {
   unsigned char RegsPPU[2];      //$2000 and $2001
};

struct stSoundv1 {
   unsigned char RegsSound[0x16]; //$4000-$4015, don't use $4014
};

struct stSRAMv1 {
   unsigned char SRAMEnabled;    //If SRAM is enabled (eg. MMC3 which can enable and
                        // disable it at the switch of a bit) 0=false, >0 = true
   unsigned char SRAM[0x2000];   //$6000-$7FFF of Main Memory (SRAM)
};

struct stMapperDatav1 {
   unsigned short int PRGPageNm[4], CHRPageNm[8]; //In order of occurence in the file, ROM
                                     // page numbers ($8/A/C/E000) and CHR
                                     // ($00/04/08/0C/10/14/18/1C00) page numbers.
   unsigned char MMCData[128]; //Mapper data, not standardized yet, 128 unsigned chars should
                      // be enough for all future mappers. =)
};

struct stControllersv1 {
   unsigned char Type[2];                //Type of controller connected to each of the
                                // controller ports... See the defines section
                                // at the top for the number->controller map.
   unsigned long Bits[2];       //The bits that reads to $4016/$4017 would
                                // return in D0
   unsigned char BitPointer[2];          //Which bit is currently selected for next
                                // being read via D0 of $4016/$4017
   unsigned char Strobe[2];              //The strobe bit (written to $4016/$4017)

//0=false, >0 = true
   unsigned char PaddleButtPressed;      //Paddle: If the button is pressed
   unsigned char PaddlePosition;         //Paddle: Numeric Position
   unsigned char ZapperButtPressed;      //Zapper: If the button is pressed
   unsigned char CoinInsert;             //VS System: If a coin is being inserted
   unsigned char DIPSwitches;            //VS System: DIP Switches
};
//---------------------------------------------------------------------------
#endif
