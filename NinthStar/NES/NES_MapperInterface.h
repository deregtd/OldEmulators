/*
 * NESten Mapper Interface v2.1
 */

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

/* So this file only gets included once */

#ifndef __NES_INTERFACE_H__
#define __NES_INTERFACE_H__

/* Standard header files, used by all mappers */

#include <windows.h>

#define	MSGBOX_FLAGS	(MB_OK | MB_ICONERROR | MB_DEFBUTTON1 | MB_APPLMODAL)

/* Mapper Interface version (2.1) */

#define CurrentMapperInterface 0x00020001

/* Integer types */

typedef	signed char	s8;
typedef	signed short	s16;
typedef	signed long	s32;

typedef	unsigned char	u8;
typedef	unsigned short	u16;
typedef	unsigned long	u32;

typedef	union
{
	struct
	{
		unsigned n0 : 4;
		unsigned n1 : 4;
	} n;
	struct
	{
		unsigned b0 : 8;
	} b;
}	u8_n;

typedef	union
{
	struct
	{
		unsigned n0 : 4;
		unsigned n1 : 4;
		unsigned n2 : 4;
		unsigned n3 : 4;
	} n;
	struct
	{
		unsigned b0 : 8;
		unsigned b1 : 8;
	} b;
	struct
	{
		unsigned s0 :16;
	} s;
}	u16_n;

/* Function types */
typedef	void	(*F)		(void);
typedef	void	(*F_s32)	(int);
typedef	void	(*F_s32s32)	(int,int);
typedef	void	(*F_s32s32s32)	(int,int,int);
typedef	void	(*F_s32s32s32s32)
				(int,int,int,int);
typedef	void	(*F_PChar)	(char *);
typedef	int	(*F_s32_s32)	(int);
typedef	int	(*F_s32s32_s32)	(int,int);
typedef	void *	(*F_s32_p)	(int);

typedef	void	(*TWriteFunc)	(int,int,int);
typedef	int	(*TReadFunc)	(int,int);

typedef	void	(*F_s32WF)	(int,TWriteFunc);
typedef	void	(*F_s32RF)	(int,TReadFunc);

typedef	TWriteFunc
		(*F_s32_WF)	(int);
typedef	TReadFunc
		(*F_s32_RF)	(int);

/* The Mapper Interface Structure - Pointers to data and functions within NESten */

typedef	struct	TMapperParam
{
	/* .NES Header information */
		int		Flags;
		int		PRG_ROM_Size;
		int		CHR_ROM_Size;
		int		Unused;

	/* Functions for managing read/write handlers */
		F_s32WF		SetWriteHandler;
		F_s32RF		SetReadHandler;
		F_s32_WF	GetWriteHandler;
		F_s32_RF	GetReadHandler;

	/* Functions for mapping PRG */
		F_s32s32	SetPRG_ROM4;
		F_s32s32	SetPRG_ROM8;
		F_s32s32	SetPRG_ROM16;
		F_s32s32	SetPRG_ROM32;
		F_s32_s32	GetPRG_ROM4;	/* -1 if no ROM mapped */
#define		GetPRG_ROM8(x)	GetPRG_ROM4(x) >> 1
#define		GetPRG_ROM16(x)	GetPRG_ROM4(x) >> 2
		F_s32s32	SetPRG_RAM4;
		F_s32s32	SetPRG_RAM8;
		F_s32s32	SetPRG_RAM16;
		F_s32s32	SetPRG_RAM32;
		F_s32_s32	GetPRG_RAM4;	/* -1 if no RAM mapped */
#define		GetPRG_RAM8(x)	GetPRG_RAM4(x) >> 1
		F_s32_p		GetPRG_Ptr4;
		
		F_s32		SetPRG_OB4;	/* Open bus */

	/* Functions for mapping CHR */
		F_s32s32	SetCHR_ROM1;
		F_s32s32	SetCHR_ROM2;
		F_s32s32	SetCHR_ROM4;
		F_s32s32	SetCHR_ROM8;
		F_s32_s32	GetCHR_ROM1;	/* -1 if no ROM mapped */
		F_s32s32	SetCHR_RAM1;
		F_s32s32	SetCHR_RAM2;
		F_s32s32	SetCHR_RAM4;
		F_s32s32	SetCHR_RAM8;
		F_s32_s32	GetCHR_RAM1;	/* -1 if no RAM mapped */
		F_s32_p		GetCHR_Ptr1;
/*		F_s32		SetCHR_OB1;	/* Open bus */

	/* Functions for controlling mirroring */
		F		Mirror_H;
		F		Mirror_V;
		F		Mirror_4;
		F		Mirror_S0;
		F		Mirror_S1;
		F_s32s32s32s32	Mirror_Custom;

	/* Save RAM Handling */

		F_s32		Set_SRAMSize;	/* Sets the size of the SRAM (in bytes) and clears PRG_RAM */
		F		Save_SRAM;	/* Saves SRAM to disk */
		F		Load_SRAM;	/* Loads SRAM from disk */


	/* Callback for debugging purposes */
		F_PChar		DbgOut;

	/* Special Chip functions */
	/* MMC5: */
		F		MMC5_UpdateAttributeCache;
				/* Call when it is in EXRAM mode, and $5C00 has been written to */
}	*PMapperParam;

//PMapperParam MP;	/* Used by all mappers, might as well drop it in here */

typedef	void	(*TInitMapper)	(const PMapperParam,int);
typedef	void	(*TUnloadMapper)(void);
typedef	int	(*THBlank)	(int,int);
typedef	int	(*TTileHandler)	(int,int,int);
typedef	void	(*TMapperSnd)	(s16 *,int);

typedef	u8	Ar128[128];
typedef	void	(*TSaveMI)	(Ar128);
typedef	void	(*TLoadMI)	(const Ar128); 

#define		MS_None		0
#define		MS_Partial	1
#define		MS_Nearly	2
#define		MS_Full		3

/* Mapper Information structure - Contains pointers to mapper functions, sent to NESten on load mapper  */

typedef struct	TMapper_Info
{
	/* Mapper Information */
		char *		BoardName;
		int		MapperNum;
		int		MapperSupport;
		int		BankSize;

	/* Mapper Functions */
		TInitMapper	InitMapper;
		TUnloadMapper	UnloadMapper;
		THBlank		HBlank;
		TTileHandler	TileHandler;
		TSaveMI		SaveMI;
		TLoadMI		LoadMI;
		TMapperSnd	MapperSnd;
}	*PMapper_Info;

typedef	PMapper_Info
		(*TLoadMapper_ByNum)
				(int);
typedef	PMapper_Info
		(*TLoadMapper_ByBoard)
				(char *);

/* DLL Information Structure:- Contains general information about the mapper DLL */

typedef	struct	TDLL_Info
{
		char *		Author;
		int		Date;
		int		Version;
		TLoadMapper_ByNum
				LoadMapper;
		TLoadMapper_ByBoard
				LoadMapper_ByBoard;
}	*PDLL_Info;

typedef	PDLL_Info
		(*TLoad_DLL)	(int);
typedef	void	(*TUnload_DLL)	(void);

#endif		/* __INTERFACE_H__ */