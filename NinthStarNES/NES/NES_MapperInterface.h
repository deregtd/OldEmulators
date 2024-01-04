/*
 * NESten Mapper Interface v2.1
 */

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

/* So this file only gets included once */

#ifndef __INTERFACE_H__
#define __INTERFACE_H__

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
	};
	struct
	{
		unsigned b0 : 8;
	};
}	u8_n;

typedef	union
{
	struct
	{
		unsigned n0 : 4;
		unsigned n1 : 4;
		unsigned n2 : 4;
		unsigned n3 : 4;
	};
	struct
	{
		unsigned b0 : 8;
		unsigned b1 : 8;
	};
	struct
	{
		unsigned s0 :16;
	};
}	u16_n;

typedef	union
{
	struct
	{
		unsigned n0 : 4;
		unsigned n1 : 4;
		unsigned n2 : 4;
		unsigned n3 : 4;
		unsigned n4 : 4;
		unsigned n5 : 4;
		unsigned n6 : 4;
		unsigned n7 : 4;
	};
	struct
	{
		unsigned b0 : 8;
		unsigned b1 : 8;
		unsigned b2 : 8;
		unsigned b3 : 8;
	};
	struct
	{
		unsigned s0 :16;
		unsigned s1 :16;
	};
	struct
	{
		unsigned l0 :32;
	};
}	u32_n;

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
typedef	u8 *	(*F_s32_p)	(int);
typedef	int	(*F__s32)	(void);
typedef	int	(*F_addmenu)	(int,char *,int,int,int,int,int);

typedef	void	(*PWriteFunc)	(int,int,int);
typedef	int	(*PReadFunc)	(int,int);

typedef	void	(*F_s32WF)	(int,PWriteFunc);
typedef	void	(*F_s32RF)	(int,PReadFunc);

typedef	PWriteFunc
		(*F_s32_WF)	(int);
typedef	PReadFunc
		(*F_s32_RF)	(int);

/* The Mapper Interface Structure - Pointers to data and functions within NESten */

typedef	struct	MapperParam
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

	/* IRQ */
		F		IRQ;

	/* Save RAM Handling */

		F_s32		Set_SRAMSize;	/* Sets the size of the SRAM (in bytes) */
		F		Save_SRAM;	/* Saves SRAM to disk */
		F		Load_SRAM;	/* Loads SRAM from disk */

	/* Misc Callbacks */
		F_PChar		DbgOut;		/* Echo text to debug window */
		F_PChar		StatusOut;	/* Echo text on status bar */
		F__s32		GetMenuRoot;	/* Gets root menu */
		F_addmenu	AddMenuItem;	/* Adds an item to a menu, returns a menu handle (for making submenus) */

	/* Special Chip functions */
	/* MMC5: */
		F		MMC5_UpdateAttributeCache;
				/* Call when it is in EXRAM mode, and $5C00 has been written to */
}	TMapperParam, *PMapperParam;

extern PMapperParam MP;

typedef	void	(*TInitMapper)	(const PMapperParam,int);
typedef	void	(*TUnloadMapper)(void);
typedef	int	(*THBlank)	(int,int);
typedef	int	(*TTileHandler)	(int,int,int);
typedef	void	(*TMapperSnd)	(s16 *,int);
typedef	void	(*TMenuClick)	(int,int,int,int);

typedef	u8	Ar128[128];
typedef	void	(*TSaveMI)	(Ar128);
typedef	void	(*TLoadMI)	(const Ar128); 

#define		MS_None		0
#define		MS_Partial	1
#define		MS_Nearly	2
#define		MS_Full		3

#define		MENU_NOCHECK	0
#define		MENU_UNCHECKED	1
#define		MENU_CHECKED	2

/* Mapper Information structure - Contains pointers to mapper functions, sent to NESten on load mapper  */

typedef struct	MapperInfo
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
		TMenuClick	MenuClick;
}	TMapperInfo, *PMapperInfo;

typedef	PMapperInfo
		(*TLoadMapper)	(int);
typedef	PMapperInfo
		(*TLoadBoard)	(char *);

/* DLL Information Structure:- Contains general information about the mapper DLL */

typedef	struct	DLLInfo
{
		char *		Author;
		int		Date;
		int		Version;
		TLoadMapper	LoadMapper;
		TLoadBoard	LoadBoard;
}	TDLLInfo, *PDLLInfo;

typedef	PDLLInfo(*TLoad_DLL)	(int);
typedef	void	(*TUnload_DLL)	(void);

#endif		/* __INTERFACE_H__ */