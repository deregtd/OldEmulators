/*
NinthStar - A portable Win32 NES Emulator written in C++
Copyright (C) 2000  David de Regt

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

For a copy of the GNU General Public License, go to:
http://www.gnu.org/copyleft/gpl.html#SEC1
*/

#include "stdafx.h"
#include "Atari2600.h"

#include "Global.h"

unsigned char Ticks6507[256]=
{
    7,6,2,2,2,3,5,2,3,2,2,2,2,4,6,2,
    2,5,2,2,2,4,6,2,2,4,2,2,2,4,6,2,
    6,6,2,2,3,3,5,2,4,2,2,2,4,4,6,2,
    2,5,2,2,2,4,6,2,2,4,2,2,2,4,6,2,
    6,6,2,2,2,3,5,2,3,2,2,2,3,4,6,2,
    2,5,2,2,2,4,6,2,2,4,2,2,2,4,6,2,
    6,6,2,2,2,3,5,2,4,2,2,2,5,4,6,2,
    2,5,2,2,2,4,6,2,2,4,2,2,2,4,6,2,
    2,6,2,2,3,3,3,2,2,2,2,2,4,4,4,2,
    2,5,2,2,4,4,4,2,2,4,2,2,2,4,2,2,
    2,6,2,2,3,3,3,2,2,2,2,2,4,4,4,2,
    2,5,2,2,4,4,4,2,2,4,2,2,4,4,4,2,
    2,6,2,2,3,3,5,2,2,2,2,2,4,4,6,2,
    2,5,2,2,2,4,6,2,2,4,2,2,2,4,6,2,
    2,6,2,2,3,3,5,2,2,2,2,2,4,4,6,2,
    2,5,2,2,2,4,6,2,2,4,2,2,2,4,6,2
};

unsigned char Ticks6507Mult[256];

#define NUM_ROMS	510

struct ROMStuff {
	unsigned long CRC;
	char MapperType;
	char Name[27];
} ROMArray[NUM_ROMS] = {
 { 0x00770CFB, MT_64k,   "32IN1.BIN"    },
 { 0x0003AD92, MT_2k,    "3D_TIC.BIN"   },
 { 0x001D2F8E, MT_16kF6, "ACIDDROP.BIN" },
 { 0x000C0AA3, MT_8kF8,  "ATEAM.BIN"    },
 { 0x0006D1D4, MT_4k,    "ASTROWAR.BIN" },
 { 0x000EE0E9, Unk,      "ASTROIDC.BIN" },
 { 0x0006C060, MT_4k,    "ASTRBLST.BIN" },
 { 0x000C7F62, MT_8kF8,  "ASTERPAL.BIN" },
 { 0x000C8AE0, MT_8kF8,  "ASTEROID.BIN" },
 { 0x00079794, MT_4k,    "ASSAULT.BIN"  },
 { 0x000FD096, MT_8kF8,  "ART_DUEL.BIN" },
 { 0x0006D7AE, MT_4k,    "ARMAMBSH.BIN" },
 { 0x000EBC4F, MT_8kF8,  "AQUAVENT.BIN" },
 { 0x0007F615, MT_4k,    "AMIDAR.BIN"   },
 { 0x000FFFB5, MT_8kF8,  "ALPHBEAM.BIN" },
 { 0x0007B0A9, MT_4k,    "ALIENRET.BIN" },
 { 0x0006E97D, MT_4k,    "ALIEN.BIN"    },
 { 0x00071D54, MT_4k,    "AIRSEA2.BIN"  },
 { 0x0006C1F4, MT_4k,    "AIRLOCK.BIN"  },
 { 0x0007A9DC, MT_4k,    "AIRAIDRS.BIN" },
 { 0x00038DA8, MT_2k,    "AIR_SEA.BIN"  },
 { 0x00078A61, MT_4k,    "AIR_RAID.BIN" },
 { 0x00075EB8, MT_4k,    "ADVNTURE.BIN" },
 { 0x00074E40, MT_4k,    "ADVNTRON.BIN" },
 { 0x00078387, MT_4k,    "ACTIONMN.BIN" },
 { 0x0006D274, MT_4k,    "ATLANTIS.BIN" },
 { 0x00054E06, MT_4k,    "BACHELOR.BIN" },
 { 0x00188504, MT_16kE7, "BURGTIME.BIN" },
 { 0x000B677E, MT_8kF8,  "BUGSBUN.BIN"  },
 { 0x000683F6, MT_4k,    "BUGS.BIN"     },
 { 0x000CF578, MT_8kF8,  "BUCKROG.BIN"  },
 { 0x0007FCEB, MT_4k,    "BRIDGE.BIN"   },
 { 0x00073AE7, MT_4k,    "BRICKICK.BIN" },
 { 0x0003D708, MT_2k,    "BREAKOUT.BIN" },
 { 0x0003CCCD, MT_2k,    "BRAINGMS.BIN" },
 { 0x00036B3D, MT_2k,    "BOXING.BIN"   },
 { 0x0003BACE, MT_2k,    "BOWLING.BIN"  },
 { 0x0007779F, MT_4k,    "BOWLG_TW.BIN" },
 { 0x00076F32, MT_4k,    "BOOMBANG.BIN" },
 { 0x00072EFA, MT_4k,    "BOING.BIN"    },
 { 0x0007A9E2, MT_4k,    "BOGYBLST.BIN" },
 { 0x0006BF6F, MT_4k,    "BOBBY.BIN"    },
 { 0x002F03C8, MT_16kE7, "BNJ.BIN"      },
 { 0x0018AA05, MT_16kF6, "BMX_TNT.BIN"  },
 { 0x000EFFC4, MT_8kF8,  "BLUEPRNT.BIN" },
 { 0x0003B06F, MT_2k,    "BLACK_J.BIN"  },
 { 0x000716BE, MT_4k,    "BIBI.BIN"     },
 { 0x00067D00, MT_4k,    "BERZERK.BIN"  },
 { 0x000737DD, MT_4k,    "BERMUDA.BIN"  },
 { 0x00078E4A, MT_4k,    "BERMDTRI.BIN" },
 { 0x00062E00, MT_4k,    "BEATEM.BIN"   },
 { 0x00071F4D, MT_4k,    "BEANYBOP.BIN" },
 { 0x000EECC2, MT_8kF8,  "BEAMRIDE.BIN" },
 { 0x000D4BD5, MT_8kF8,  "BATLZONE.BIN" },
 { 0x00041129, MT_2k,    "BASMATH.BIN"  },
 { 0x00042CC1, MT_2k,    "BASKETBL.BIN" },
 { 0x00084398, MT_4k,    "BASIC.BIN"    },
 { 0x0007568F, MT_4k,    "BASEATTK.BIN" },
 { 0x00078AC5, MT_4k,    "BARNSTRM.BIN" },
 { 0x0007E66D, MT_4k,    "BANKHEST.BIN" },
 { 0x000852B2, MT_4k,    "BACKGAM.BIN"  },
 { 0x00055706, MT_4k,    "BACHLRTT.BIN" },
 { 0x00076000, MT_4k,    "BURNDESR.BIN" },
 { 0x000761C0, MT_4k,    "CAKEWALK.BIN" },
 { 0x0005AC00, MT_4k,    "CUSTEREV.BIN" },
 { 0x0006F712, MT_4k,    "CUBICOL.BIN"  },
 { 0x000768D0, MT_4k,    "CSMCOMTR.BIN" },
 { 0x0014A44C, MT_16kF6, "CRYSCAST.BIN" },
 { 0x0007657E, MT_4k,    "CRUSMISL.BIN" },
 { 0x0007B4AE, MT_4k,    "CRSHDIVE.BIN" },
 { 0x000765D7, MT_4k,    "CRPTCHOS.BIN" },
 { 0x001B3F40, MT_16kF6, "CROSSBOW.BIN" },
 { 0x00079F21, MT_4k,    "CROSFRCE.BIN" },
 { 0x0006F8B4, MT_4k,    "CRIMLPUR.BIN" },
 { 0x000E8575, MT_8kF8,  "CRAZCLMB.BIN" },
 { 0x00076289, MT_4k,    "CRACKPOT.BIN" },
 { 0x0003DAC6, MT_2k,    "COSMSWRM.BIN" },
 { 0x000622AB, MT_4k,    "COSMCREP.BIN" },
 { 0x0006D169, MT_4k,    "COSMCORR.BIN" },
 { 0x000712EC, MT_4k,    "COSMCARK.BIN" },
 { 0x000DDCA2, MT_8kF8,  "COOKMONS.BIN" },
 { 0x000E3CFA, MT_8kF8,  "CONGBONG.BIN" },
 { 0x0006E90B, MT_4k,    "CONDOR.BIN"   },
 { 0x00039135, MT_2k,    "CONCENTR.BIN" },
 { 0x001B676C, MT_16kF6, "COMMANDO.BIN" },
 { 0x00038698, MT_2k,    "COMBAT.BIN"   },
 { 0x00072415, MT_4k,    "COMANDRD.BIN" },
 { 0x00068D5C, MT_4k,    "COLORBAR.BIN" },
 { 0x0007A01C, MT_4k,    "COLN.BIN"     },
 { 0x00075B0D, MT_4k,    "COKEWINS.BIN" },
 { 0x0003A688, MT_2k,    "CODEBRK.BIN"  },
 { 0x0006DD35, MT_4k,    "COCONUTS.BIN" },
 { 0x00070828, MT_4k,    "CLWNDOWN.BIN" },
 { 0x00057177, MT_4k,    "CIRCUS-J.BIN" },
 { 0x0005485D, MT_4k,    "CIRCATRI.BIN" },
 { 0x000783E3, MT_4k,    "CHUCKWGN.BIN" },
 { 0x000D0D51, MT_8kF8,  "CHUCKICK.BIN" },
 { 0x0007912C, MT_4k,    "CHOPRCMD.BIN" },
 { 0x000745CB, MT_4k,    "CHINASYN.BIN" },
 { 0x0003F1D7, MT_2k,    "CHECKACT.BIN" },
 { 0x000E1A5E, MT_8kF8,  "CHALLANG.BIN" },
 { 0x000737B7, MT_4k,    "CHALENGE.BIN" },
 { 0x000D7C93, MT_8kF8,  "CENTIPED.BIN" },
 { 0x00068E07, MT_4k,    "CATMOUSE.BIN" },
 { 0x000734DC, MT_4k,    "CATHOUSE.BIN" },
 { 0x0007E271, MT_4k,    "CASINO.BIN"   },
 { 0x00077D16, MT_4k,    "CARNIVAL.BIN" },
 { 0x0003D843, MT_2k,    "CANYONB.BIN"  },
 { 0x001A765C, MT_16kF6, "CALIFGMS.BIN" },
 { 0x0007B6B1, MT_4k,    "CX2616PL.BIN" },
 { 0x00072D81, MT_4k,    "DANCPLAT.BIN" },
 { 0x00072902, MT_4k,    "DUCKSHOT.BIN" },
 { 0x001984AC, MT_16kF6, "DSRTFALC.BIN" },
 { 0x000705E0, MT_4k,    "DRGNFIRE.BIN" },
 { 0x00077CD6, MT_4k,    "DRGNDFND.BIN" },
 { 0x0003885C, MT_2k,    "DRAGSTER.BIN" },
 { 0x001CA531, MT_16kF6, "DOUBDUNK.BIN" },
 { 0x7220F, MT_4k, "DOLPHIN.BIN" },
 { 0x6A21C, MT_4k, "DODGE_EM.BIN" },
 { 0xD1113, Unk, "DOCASTLE.BIN" },
 { 0xE3695, Unk, "DKJR.BIN" },
 { 0x63B31, MT_4k, "DK.BIN" },
 { 0x6BD1F, MT_4k, "DISHASTR.BIN" },
 { 0x1D2416, Unk, "DIGDUG.BIN" },
 { 0x7C814, MT_4k, "DICEPUZL.BIN" },
 { 0x6CE26, MT_4k, "DETHTRAP.BIN" },
 { 0xDE446, Unk, "DETHSTAR.BIN" },
 { 0x6EE82, MT_4k, "DEMONDIM.BIN" },
 { 0x6F6B1, MT_4k, "DEMONATK.BIN" },
 { 0x68614, MT_4k, "DEMOHRBY.BIN" },
 { 0xD25EF, Unk, "DEFENDR2.BIN" },
 { 0x7F16C, MT_4k, "DEFENDER.BIN" },
 { 0xDAD52, Unk, "DECATHLN.BIN" },
 { 0x76F96, MT_4k, "DEADDUCK.BIN" },
 { 0x1C5B2A, Unk, "DBLDRAGN.BIN" },
 { 0x781CF, MT_4k, "DARKCVRN.BIN" },
 { 0x1D1088, Unk, "DARKCHAM.BIN" },
 { 0x1A4415, Unk, "DUKES.BIN" },
 { 0xDCBB2, Unk, "E_T.BIN" },
 { 0x9B2D7, Unk, "FROGPOND.BIN" },
 { 0xEE31A, Unk, "FROGGER2.BIN" },
 { 0x800D3, MT_4k, "FROGGER.BIN" },
 { 0x74C49, MT_4k, "FROGFLYS.BIN" },
 { 0xEF1E9, Unk, "FRNTLINE.BIN" },
 { 0x370C3, MT_2k, "FREEWAY.BIN" },
 { 0x74A05, MT_4k, "FRANKMON.BIN" },
 { 0x746B6, MT_4k, "FOREST.BIN" },
 { 0x3D15E, MT_2k, "FOOTBALL.BIN" },
 { 0x6EC02, MT_4k, "FLASHGRD.BIN" },
 { 0x3D33C, MT_2k, "FLAGCAP.BIN" },
 { 0x3A1C0, MT_2k, "FISHDRBY.BIN" },
 { 0x6FE69, MT_4k, "FIRESPIN.BIN" },
 { 0x756AC, MT_4k, "FIREFLY.BIN" },
 { 0x729F3, MT_4k, "FIREFITE.BIN" },
 { 0x78AB0, MT_4k, "FIREBIRD.BIN" },
 { 0x6EC26, MT_4k, "FINLAPCH.BIN" },
 { 0x1BAB1C, Unk, "FIGHTERP.BIN" },
 { 0x78DCF, MT_4k, "FB_PIR8.BIN" },
 { 0xDA986, Unk, "FATHOM.BIN" },
 { 0x299233, MT_32k, "FATALRUN.BIN" },
 { 0x60E96, MT_4k, "FASTFOOD.BIN" },
 { 0x72E5A, MT_4k, "FASTEDIE.BIN" },
 { 0x6EE6D, MT_4k, "FARMYARD.BIN" },
 { 0x70BB6, MT_4k, "FANTCVOY.BIN" },
 { 0x75628, MT_4k, "EXOCET.BIN" },
 { 0xC4D38, Unk, "ESPIAL.BIN" },
 { 0x67284, MT_4k, "ENTOMBED.BIN" },
 { 0x6F69A, MT_4k, "ENDURO_A.BIN" },
 { 0x6DD61, MT_4k, "ENDRO_TW.BIN" },
 { 0x66E29, MT_4k, "ENCONTL5.BIN" },
 { 0x73189, MT_4k, "ELILADDR.BIN" },
 { 0x6CCD7, MT_4k, "EGGOMANA.BIN" },
 { 0xD8234, Unk, "EGGCATCH.BIN" },
 { 0x72018, MT_4k, "EARTHDIE.BIN" },
 { 0x74159, MT_4k, "FROSTBIT.BIN" },
 { 0xC1D1C, Unk, "ELK.BIN" },
 { 0x7325F, MT_4k, "GALAGA.BIN" },
 { 0x3B1D0, MT_2k, "HOMERUN.BIN" },
 { 0x9E4C6, Unk, "HOLEMOLE.BIN" },
 { 0x658A6, MT_4k, "HOLEHUNT.BIN" },
 { 0xDC3CE, Unk, "HERO.BIN" },
 { 0x1694A9, Unk, "HE_MAN.BIN" },
 { 0x7D352, MT_4k, "HAUNTHSE.BIN" },
 { 0x6FDBF, MT_4k, "HARBRESC.BIN" },
 { 0x644A2, MT_4k, "HANGMAN.BIN" },
 { 0x69756, MT_4k, "HALOWEEN.BIN" },
 { 0xBF9F8, Unk, "GYRUSS.BIN" },
 { 0x70434, MT_4k, "GUARDIAN.BIN" },
 { 0xA31DF, Unk, "GROVER.BIN" },
 { 0x749BE, MT_4k, "GRESCAPE.BIN" },
 { 0xDF13C, Unk, "GREMLINS.BIN" },
 { 0xDE0A3, Unk, "GRAVITAR.BIN" },
 { 0x6D872, MT_4k, "GRANDPRX.BIN" },
 { 0x7E8C3, MT_4k, "GORF.BIN" },
 { 0x7217F, MT_4k, "GOPHER.BIN" },
 { 0x3B8FC, MT_2k, "GOLF.BIN" },
 { 0x70C3A, MT_4k, "GLIB.BIN" },
 { 0x78E4D, MT_4k, "GIJOE.BIN" },
 { 0x7104F, MT_4k, "GIGOLO.BIN" },
 { 0xA94B8, Unk, "GHOSTMAN.BIN" },
 { 0xEF23E, Unk, "GHOSTBST.BIN" },
 { 0x632BB, MT_4k, "GAUNTLET.BIN" },
 { 0x7564E, MT_4k, "GASHOG.BIN" },
 { 0x6EA41, MT_4k, "GANGALLY.BIN" },
 { 0xEA387, Unk, "GALAXIAN.BIN" },
 { 0x3F2D0, MT_2k, "HUMAN_CB.BIN" },
 { 0x7DF74, MT_4k, "ICEHOCKY.BIN" },
 { 0xF2694, Unk, "KRULL.BIN" },
 { 0x715A2, MT_4k, "KOOLAIDE.BIN" },
 { 0x60A00, MT_4k, "KNIGHTWN.BIN" },
 { 0x1E4887, Unk, "KLAXNTSC.BIN" },
 { 0x1A4F39, Unk, "KLAX.BIN" },
 { 0x72D4D, MT_4k, "KINGKONG.BIN" },
 { 0x7006B, MT_4k, "KEYSTONE.BIN" },
 { 0x7CB15, MT_4k, "KARATE.BIN" },
 { 0xE16CF, Unk, "KANGAROO.BIN" },
 { 0x36C7C, MT_2k, "KABOOM.BIN" },
 { 0x1EBD1D, Unk, "JRPACMAN.BIN" },
 { 0x77A48, MT_4k, "JRNYESCP.BIN" },
 { 0xE915B, Unk, "JOUST.BIN" },
 { 0xE96A5, Unk, "JNGLHUNT.BIN" },
 { 0x74000, MT_4k, "JNGLFEVR.BIN" },
 { 0x7EF53, MT_4k, "JEDIAREN.BIN" },
 { 0x7A9C2, MT_4k, "JAWBREAK.BIN" },
 { 0x7B00A, MT_4k, "IWANTMOM.BIN" },
 { 0x6B109, MT_4k, "IQ180.BIN" },
 { 0x78E82, MT_4k, "INTRSCCR.BIN" },
 { 0x68828, MT_4k, "INFILTRT.BIN" },
 { 0x39318, MT_2k, "INDY_500.BIN" },
 { 0x7C8BA, MT_4k, "IMMIES.BIN" },
 { 0x67A61, MT_4k, "IMAGSLCT.BIN" },
 { 0xE4094, Unk, "KUNG_FU.BIN" },
 { 0x39538, MT_2k, "LASRBLST.BIN" },
 { 0x72126, MT_4k, "NOESCAPE.BIN" },
 { 0x78403, MT_4k, "NIGHTSTK.BIN" },
 { 0x3C030, MT_2k, "NIGHTDRV.BIN" },
 { 0x72A4B, MT_4k, "NGHTMARE.BIN" },
 { 0x64198, MT_4k, "NEXAR.BIN" },
 { 0x79AA0, MT_4k, "NAMEGAME.BIN" },
 { 0xCED99, Unk, "MYGOLF.BIN" },
 { 0x6D7FC, MT_4k, "MUSCMACH.BIN" },
 { 0x159080, MT_12k, "MTNKING.BIN" },
 { 0xD2BC1, Unk, "MSPACMAN.BIN" },
 { 0x74790, MT_4k, "MRPOSTMN.BIN" },
 { 0xDA890, Unk, "MRDO.BIN" },
 { 0x7877F, MT_4k, "MOUSETRP.BIN" },
 { 0x1606A4, Unk, "MOTOR.BIN" },
 { 0xD1CD4, Unk, "MOONPTRL.BIN" },
 { 0xEFCE0, Unk, "MONTZREV.BIN" },
 { 0x6324E, Unk, "MONS.BIN" },
 { 0x757CA, MT_4k, "MOGULMAN.BIN" },
 { 0xD2510, Unk, "MNR2049R.BIN" },
 { 0x7CCDE, MT_4k, "MISSCOMM.BIN" },
 { 0x7DC54, MT_4k, "MISN3000.BIN" },
 { 0x67900, MT_4k, "MISLCONT.BIN" },
 { 0xDEC87, Unk, "MINRVOL2.BIN" },
 { 0x75B91, MT_4k, "MINEMNOS.BIN" },
 { 0xE7ADB, Unk, "MINDLINK.BIN" },
 { 0x3DB85, MT_2k, "MIN_GOLF.BIN" },
 { 0x17BC36, Unk, "MILLIPED.BIN" },
 { 0x179944, Unk, "MIDNIGHT.BIN" },
 { 0x69E43, MT_4k, "METDEF.BIN" },
 { 0x75974, MT_4k, "MEGAMAN.BIN" },
 { 0x79214, MT_4k, "MEGAFRCE.BIN" },
 { 0x7A590, MT_4k, "MAZECRZ.BIN" },
 { 0x761B8, MT_4k, "MATH_GPX.BIN" },
 { 0x80264, MT_4k, "MASTBULD.BIN" },
 { 0x72300, MT_4k, "MASH.BIN" },
 { 0xE3A01, Unk, "MARIOBRO.BIN" },
 { 0x76097, MT_4k, "MARINWAR.BIN" },
 { 0x7C25E, MT_4k, "MARFLEGR.BIN" },
 { 0x770E7, MT_4k, "MARAUDER.BIN" },
 { 0x3C811, MT_2k, "MAO17600.BIN" },
 { 0x79F28, MT_4k, "MANGIA.BIN" },
 { 0x73769, MT_4k, "MALAGAI.BIN" },
 { 0x7E228, MT_4k, "M_A_D.BIN" },
 { 0x5F691, MT_4k, "LOSTLUGG.BIN" },
 { 0x7020F, MT_4k, "LONDBLTZ.BIN" },
 { 0x806AA, MT_4k, "LOCKCHSE.BIN" },
 { 0x6FF2C, MT_4k, "LASRVOLY.BIN" },
 { 0x70B7A, MT_4k, "LASRGATE.BIN" },
 { 0x7710C, MT_4k, "NUTS.BIN" },
 { 0xC7A8A, Unk, "LANCELOT.BIN" },
 { 0x9E5A5, Unk, "OBELIX.BIN" },
 { 0x73CD9, MT_4k, "QUICKSTP.BIN" },
 { 0xD5653, Unk, "QBRTQUBE.BIN" },
 { 0x6DE9B, MT_4k, "QBERT_PB.BIN" },
 { 0x790D8, MT_4k, "PYRMDWAR.BIN" },
 { 0x7A590, MT_4k, "PUZZL_TW.BIN" },
 { 0xC97B5, Unk, "PROWREST.BIN" },
 { 0xD73C6, Unk, "PRIVEYE.BIN" },
 { 0xBB429, Unk, "PRESSURE.BIN" },
 { 0xDE082, Unk, "PORKYS.BIN" },
 { 0xCC026, Unk, "POPEYE.BIN" },
 { 0x759B0, MT_4k, "POOYAN.BIN" },
 { 0x3B81D, MT_2k, "POLO.BIN" },
 { 0xCD2E4, Unk, "POLEPSN.BIN" },
 { 0xD60BF, Unk, "POLARIS.BIN" },
 { 0x77EF2, MT_4k, "PLAQATTK.BIN" },
 { 0x73C87, MT_4k, "PLANTPAT.BIN" },
 { 0x12157E, Unk, "PITFALL2.BIN" },
 { 0x6D0E6, MT_4k, "PITFALL.BIN" },
 { 0x6C658, MT_4k, "PITF_CCE.BIN" },
 { 0xF4E4A, Unk, "PIGSPACE.BIN" },
 { 0x6AE62, MT_4k, "PIECECKE.BIN" },
 { 0x7844B, MT_4k, "PICNIC.BIN" },
 { 0x1E3898, Unk, "PICKPILE.BIN" },
 { 0xE89F9, Unk, "PHOENIX.BIN" },
 { 0x61D00, MT_4k, "PHILLY.BIN" },
 { 0x84F0E, MT_4k, "PHARHCRS.BIN" },
 { 0x745AE, MT_4k, "PHANTOMT.BIN" },
 { 0x17E1A7, Unk, "PETEROSE.BIN" },
 { 0xDAF43, Unk, "PENGO.BIN" },
 { 0x78E58, MT_4k, "PELE_TW.BIN" },
 { 0x7A98F, MT_4k, "PELE.BIN" },
 { 0x678F5, MT_4k, "PEEKABOO.BIN" },
 { 0x754F5, MT_4k, "PARCHUTE.BIN" },
 { 0x7187D, MT_4k, "PANDCHSE.BIN" },
 { 0x79F1E, MT_4k, "PACMAN.BIN" },
 { 0x70FC5, MT_4k, "PACKONG.BIN" },
 { 0x41828, MT_2k, "OUTLAW.BIN" },
 { 0x3B28C, MT_2k, "OUTERSPC.BIN" },
 { 0x40194, MT_2k, "OTHELLO.BIN" },
 { 0xE2B06, Unk, "OSCAR.BIN" },
 { 0x6A939, MT_4k, "OPENSESM.BIN" },
 { 0x16613C, MT_12k, "OMEGARAC.BIN" },
 { 0x7BFE1, MT_4k, "OINK.BIN" },
 { 0x1D5F30, Unk, "OFTHWALL.BIN" },
 { 0x74CEB, MT_4k, "OFFROCKR.BIN" },
 { 0x6C90A, MT_4k, "OCEANCTY.BIN" },
 { 0xCB384, Unk, "QUINTROO.BIN" },
 { 0x6C480, MT_4k, "RACQUETB.BIN" },
 { 0xA375E, Unk, "RSSOCCER.BIN" },
 { 0x24C452, Unk, "RSBOXING.BIN" },
 { 0x7444B, MT_4k, "RS_VOLLY.BIN" },
 { 0xD53C6, Unk, "RS_FOOTB.BIN" },
 { 0xEF608, Unk, "RS_BASEB.BIN" },
 { 0x7FFD8, MT_4k, "ROOMDOOM.BIN" },
 { 0xDA469, Unk, "ROCNROPE.BIN" },
 { 0xCF815, Unk, "ROBOTANK.BIN" },
 { 0x16BF9A, Unk, "ROADRUNR.BIN" },
 { 0x176FD1, Unk, "RIVRAID2.BIN" },
 { 0xDE35E, Unk, "RIVERP.BIN" },
 { 0x748FB, MT_4k, "RIVERAID.BIN" },
 { 0x72D48, MT_4k, "RIVER_TW.BIN" },
 { 0x76CD2, MT_4k, "RIDDLE.BIN" },
 { 0x78793, MT_4k, "REVNGTOM.BIN" },
 { 0x776A4, MT_4k, "RESCTER1.BIN" },
 { 0x75317, MT_4k, "REACTOR.BIN" },
 { 0x1C59C0, Unk, "RAMPAGE.BIN" },
 { 0x78B88, MT_4k, "RAMIT.BIN" },
 { 0xDE9FF, Unk, "RAIDERS.BIN" },
 { 0x61495, MT_4k, "RAFTRIDR.BIN" },
 { 0x1F9FFA, Unk, "RADARLOK.BIN" },
 { 0xD09F6, Unk, "RSTENNIS.BIN" },
 { 0xBF98B, Unk, "SABOTEUR.BIN" },
 { 0x770C4, MT_4k, "SURVLRUN.BIN" },
 { 0x3F52D, MT_2k, "SURROUND.BIN" },
 { 0x68000, MT_4k, "SURFPRDS.BIN" },
 { 0x7D95E, MT_4k, "SUPRMAN2.BIN" },
 { 0x7DDB2, MT_4k, "SUPRMAN1.BIN" },
 { 0x7AAAA, MT_4k, "SUPRFOOT.BIN" },
 { 0x7852A, MT_4k, "SUPRBASE.BIN" },
 { 0x127A01, Unk, "SUPRBASB.BIN" },
 { 0x6CC64, MT_4k, "SUPFERRI.BIN" },
 { 0x7DEB1, MT_4k, "SUPERCCE.BIN" },
 { 0x81AEF, MT_4k, "SUPERB.BIN" },
 { 0x20013E, Unk, "SUMMERGA.BIN" },
 { 0x76AFF, MT_4k, "SUBSCAN.BIN" },
 { 0x74654, MT_4k, "SUBCOMDR.BIN" },
 { 0x5DEEB, MT_4k, "STRWBERY.BIN" },
 { 0x3BEE2, MT_2k, "STRTRACE.BIN" },
 { 0x772AC, MT_4k, "STRNGHLD.BIN" },
 { 0x7679D, MT_4k, "STRATGYX.BIN" },
 { 0x3978C, MT_2k, "STEPLCHS.BIN" },
 { 0x7AECC, MT_4k, "STELRTRK.BIN" },
 { 0x6BF0E, MT_4k, "STARVYGR.BIN" },
 { 0xF4668, Unk, "STARTREK.BIN" },
 { 0x75DE4, MT_4k, "STARSTRK.BIN" },
 { 0x3B28C, MT_2k, "STARSHIP.BIN" },
 { 0x9FBED, Unk, "STARRAID.BIN" },
 { 0x3ECF8, MT_2k, "STARPATH.BIN" },
 { 0x70BB3, MT_4k, "STARMAST.BIN" },
 { 0x77FCE, MT_4k, "STARGN.BIN" },
 { 0xD32CF, Unk, "STARGATE.BIN" },
 { 0x7554F, MT_4k, "STARFOX.BIN" },
 { 0x7F5B3, MT_4k, "STAREMPR.BIN" },
 { 0x399C8, MT_2k, "STAMPEDE.BIN" },
 { 0x8769C, MT_4k, "SSSNAKE.BIN" },
 { 0x7C4A4, MT_4k, "SQUEEZBX.BIN" },
 { 0xBB6D2, Unk, "SQ_WATER.BIN" },
 { 0xD18CC, Unk, "SQ_FIRE.BIN" },
 { 0xDADB9, Unk, "SQ_EARTH.BIN" },
 { 0xDC396, Unk, "SPYHUNTR.BIN" },
 { 0x148037, Unk, "SPRNMAST.BIN" },
 { 0xCCF71, Unk, "SPRINGER.BIN" },
 { 0x1DC525, Unk, "SPRFOOTB.BIN" },
 { 0x109A6D, Unk, "SPRCOBRA.BIN" },
 { 0x6DF79, MT_4k, "SPITFIRE.BIN" },
 { 0xD0CC0, Unk, "SPIKE_PK.BIN" },
 { 0x7F6BF, MT_4k, "SPIDROID.BIN" },
 { 0x76373, MT_4k, "SPIDRMAN.BIN" },
 { 0x736A0, MT_4k, "SPIDRFTR.BIN" },
 { 0x100FDA, Unk, "SPCSHUTL.BIN" },
 { 0x7C896, MT_4k, "SPCROBOT.BIN" },
 { 0x7A402, MT_4k, "SPCINVAD.BIN" },
 { 0x6F551, MT_4k, "SPACTUNL.BIN" },
 { 0x726EF, MT_4k, "SPACT_TW.BIN" },
 { 0x7274F, MT_4k, "SPACRAID.BIN" },
 { 0x684B8, MT_4k, "SPACMAST.BIN" },
 { 0x3DA9D, MT_2k, "SPACJOCK.BIN" },
 { 0x7D2F5, MT_4k, "SPACHASE.BIN" },
 { 0x3861A, MT_2k, "SPACEWAR.BIN" },
 { 0x69FA4, MT_4k, "SPACECAV.BIN" },
 { 0x7A511, MT_4k, "SPACE2.BIN" },
 { 0x78933, MT_4k, "SPACATTK.BIN" },
 { 0x69409, MT_4k, "SPACANYN.BIN" },
 { 0x7E543, MT_4k, "SORCERER.BIN" },
 { 0xDC5F5, Unk, "SORCAPRN.BIN" },
 { 0x6EAA5, MT_4k, "SOLRSTRM.BIN" },
 { 0x1CA757, Unk, "SOLARIS.BIN" },
 { 0xD7044, Unk, "SOLARFOX.BIN" },
 { 0xDBE3D, Unk, "SNOOPY.BIN" },
 { 0x75DF2, MT_4k, "SNEKPEEK.BIN" },
 { 0x72697, MT_4k, "SNALSQRL.BIN" },
 { 0xF2462, Unk, "SMURFRES.BIN" },
 { 0xF56DE, Unk, "SMURF_PL.BIN" },
 { 0xE5918, Unk, "SMRFSAVE.BIN" },
 { 0x3DD06, MT_2k, "SLOTRACE.BIN" },
 { 0x3507B, MT_2k, "SLOTMACH.BIN" },
 { 0x70BCB, MT_4k, "SKYSKIPR.BIN" },
 { 0x3B491, MT_2k, "SKYJINKS.BIN" },
 { 0x398AF, MT_2k, "SKYDIVER.BIN" },
 { 0x3C00D, MT_2k, "SKIING.BIN" },
 { 0x70A3E, MT_4k, "SKIHUNT.BIN" },
 { 0x3C962, MT_2k, "SKEETSHT.BIN" },
 { 0xDDE3A, Unk, "SKATEBRD.BIN" },
 { 0x9FAC6, Unk, "SINISTAR.BIN" },
 { 0x68EAC, MT_4k, "SHTLORBT.BIN" },
 { 0x67BE3, MT_4k, "SHOOTIN.BIN" },
 { 0x6BADE, MT_4k, "SHARKATK.BIN" },
 { 0x1A3410, Unk, "SENTINEL.BIN" },
 { 0x5787B, MT_4k, "SEESW_TW.BIN" },
 { 0x1C6DB1, Unk, "SECRETQ.BIN" },
 { 0x7359C, MT_4k, "SEAQUEST.BIN" },
 { 0x6FC86, MT_4k, "SEAMNSTR.BIN" },
 { 0x79306, MT_4k, "SEAHWK_P.BIN" },
 { 0x7935D, MT_4k, "SEAHWK_F.BIN" },
 { 0x73659, MT_4k, "SEA_HUNT.BIN" },
 { 0x736DB, MT_4k, "SCUDIV_P.BIN" },
 { 0x7200A, MT_4k, "SAVESHIP.BIN" },
 { 0x78FA2, MT_4k, "SALTDIAG.BIN" },
 { 0xCCE17, Unk, "SWARCADE.BIN" },
 { 0x7CBE1, MT_4k, "TACSCAN.BIN" },
 { 0xE03C5, Unk, "ZAXXON.BIN" },
 { 0x7511B, MT_4k, "Z_TACK.BIN" },
 { 0x75660, MT_4k, "YAR_REV.BIN" },
 { 0x75C5B, MT_4k, "XMAN.BIN" },
 { 0x796A1, Unk, "XEVIOUS.BIN" },
 { 0x1844DC, Unk, "XENOPHOB.BIN" },
 { 0x783B5, MT_4k, "WORMWAR1.BIN" },
 { 0x776E4, MT_4k, "WORLDEND.BIN" },
 { 0x7F832, MT_4k, "WORDZAPR.BIN" },
 { 0x7D047, MT_4k, "WIZRDWOR.BIN" },
 { 0x1B17F4, Unk, "WINTERGA.BIN" },
 { 0xCBF85, Unk, "WINGWAR.BIN" },
 { 0x7E2EA, MT_4k, "WARPLOCK.BIN" },
 { 0x7B217, MT_4k, "WARLORDS.BIN" },
 { 0x7BFC2, MT_4k, "WALLDFND.BIN" },
 { 0x60DE3, MT_4k, "WALLBALL.BIN" },
 { 0x6F80B, MT_4k, "WABBIT.BIN" },
 { 0x7AD6E, MT_4k, "VIDREFLX.BIN" },
 { 0x74E56, MT_4k, "VIDPIN.BIN" },
 { 0x75298, MT_4k, "VIDJOGGR.BIN" },
 { 0x748DF, MT_4k, "VIDCUBE.BIN" },
 { 0x8392D, MT_4k, "VIDCHESS.BIN" },
 { 0x8186E, MT_4k, "VIDCHECK.BIN" },
 { 0x35E7E, MT_2k, "VID_OLYM.BIN" },
 { 0x76C5F, MT_4k, "VENTURE.BIN" },
 { 0xE8BBB, Unk, "VANGUARD.BIN" },
 { 0xBEADA, Unk, "UPNDOWN.BIN" },
 { 0x68272, MT_4k, "UNIVCHOS.BIN" },
 { 0x68822, MT_4k, "UFOPATRL.BIN" },
 { 0x695C3, MT_4k, "TXSCHAIN.BIN" },
 { 0xDC831, Unk, "TUTANK.BIN" },
 { 0x75530, MT_4k, "TURMOIL.BIN" },
 { 0x18095C, MT_12k, "TUNLRUNR.BIN" },
 { 0x7153B, MT_4k, "TUBYBIRD.BIN" },
 { 0x79FCC, MT_4k, "TRONDEAD.BIN" },
 { 0x684C9, MT_4k, "TRICKSHT.BIN" },
 { 0x7B179, MT_4k, "TRAFFIC.BIN" },
 { 0x1D8B25, Unk, "TRACK.BIN" },
 { 0x74D67, MT_4k, "TOWERINF.BIN" },
 { 0xC9379, Unk, "TOOTHPRO.BIN" },
 { 0x6D58D, MT_4k, "TOMBOY.BIN" },
 { 0x779CF, MT_4k, "TIMEWARP.BIN" },
 { 0xC9676, Unk, "TIMEPLT.BIN" },
 { 0x7750E, MT_4k, "THUNDGRD.BIN" },
 { 0x6FA48, MT_4k, "THRSHOLD.BIN" },
 { 0xFB0CE, MT_4k, "TEST.BIN" },
 { 0x3A20A, MT_2k, "TENNIS.BIN" },
 { 0xCC5DC, Unk, "TAZ.BIN" },
 { 0xD0EB4, Unk, "TAXAVOID.BIN" },
 { 0x6EDC1, MT_4k, "TASKFORC.BIN" },
 { 0xE19E4, Unk, "TAPPER.BIN" },
 { 0x71866, MT_4k, "TAPEWORM.BIN" },
 { 0x746D8, MT_4k, "TANKSBUT.BIN" },
 { 0x762D5, MT_4k, "ZOOFUN.BIN" },
 { 0x3E5BE, MT_2k, "TETRIS26.BIN" },
 { 0x7B214, MT_4k, "TFSI.BIN" }
};


cAtari2600::cAtari2600()
{
	for (int i=0;i<256;i++)
		Ticks6507Mult[i] = Ticks6507[i] * 3;
	
	CPU = new c6507();
	CPU->Clockticks = &Clockticks;
	CPU->TicksToCount = &TicksToCount;

	TIA = new cA26_TIA();
	TIA->Clockticks = &Clockticks;
	TIA->TicksToCount = &TicksToCount;

	PIA = new cA26_PIA();
	PIA->Clockticks = &Clockticks;
	PIA->VBLANK = &TIA->VBLANK;

	TIA->INPT4 = &PIA->INPT4;
	TIA->INPT5 = &PIA->INPT5;

	GFX = new cA26_GFX();
	
	TIA->pGFX = GFX;
	TIA->pPIA = PIA;

	CPU->pTIA = TIA;
	CPU->pPIA = PIA;

	Debugger = new cA26_Debugger();
	Debugger->CPU = CPU;
	Debugger->TIA = TIA;
	Debugger->SetMode(0);

	char tpo[40];
    sprintf(tpo,"NinthStar - Atari2600 - Stopped");
	SetWindowText(gData->MainWnd,tpo);
	
	CPU->MapperType = MT_4k;

	Stopped = true;
	Stop = false;
	NeedQuit = false;
	NeedDie = false;
}

void cAtari2600::PowerOn()
{
	CPU->A = 0; CPU->X = 0; CPU->Y = 0; CPU->SP = 0xFF; CPU->P = 0x20;		//Reset Registers

	Reset();
}

void cAtari2600::Reset()
{
	Debugger->TraceOffset = -1;

	for (int i=0;i<4;i++)
		CPU->PageNum[i] = i;

	for (int i=0x294;i<=0x297;i++)
		CPU->WType[i] = WT_PIAREGISTER;
	
	CPU->RType[0x284] = RT_PIAREGISTER;

	CPU->RType[0x282] = RT_PIAREGISTER;

	CPU->RType[0x280] = RT_PIAREGISTER;
	CPU->RType[0x281] = RT_PIAREGISTER;
	CPU->WType[0x280] = WT_PIAREGISTER;
	CPU->WType[0x281] = WT_PIAREGISTER;

	for (int i=0x0;i<=0x14;i++)
		CPU->WType[0x000 | i] = WT_TIAREGISTER;
	
//	for (int i=0x15;i<=0x1A;i++)
//		CPU->WType[0x000 | i] = WT____REGISTER;	//Audio Shit

	for (int i=0x1B;i<=0x2C;i++)
		CPU->WType[0x000 | i] = WT_TIAREGISTER;
	
	for (int i=0x0;i<=0xD;i++)
		CPU->RType[0x000 | i] = RT_TIAREGISTER;

	for (int i=0x80;i<0x100;i++)
	{
		CPU->RType[i] = RT_RAM;
		CPU->WType[i] = WT_RAM;
		CPU->RType[i + 0x100] = RT_RAM;
		CPU->WType[i + 0x100] = WT_RAM;
	}

	for (int i=0x1000;i<0x2000;i++)
	{
		CPU->RType[i] = RT_PRG;
		CPU->WType[i] = WT_ERROR;
	}


	switch (CPU->MapperType)
	{
	case MT_2k:
		for (int i=0;i<4;i++)
			CPU->PageNum[i] = i & 1;
		break;
	case MT_4k:
		for (int i=0;i<4;i++)
			CPU->PageNum[i] = i;
		break;
	case MT_8kF8:
		for (int i=0;i<4;i++)
			CPU->PageNum[i] = i;
		CPU->RType[0x1FF8] = RT_MAPPER;
		CPU->RType[0x1FF9] = RT_MAPPER;
		CPU->WType[0x1FF8] = WT_MAPPER;
		CPU->WType[0x1FF9] = WT_MAPPER;
		break;
	case MT_16kF6:
		for (int i=0;i<4;i++)
			CPU->PageNum[i] = i;
		CPU->RType[0x1FF6] = RT_MAPPER;
		CPU->RType[0x1FF7] = RT_MAPPER;
		CPU->RType[0x1FF8] = RT_MAPPER;
		CPU->RType[0x1FF9] = RT_MAPPER;
		CPU->WType[0x1FF6] = WT_MAPPER;
		CPU->WType[0x1FF7] = WT_MAPPER;
		CPU->WType[0x1FF8] = WT_MAPPER;
		CPU->WType[0x1FF9] = WT_MAPPER;
		break;
	default:
		MessageBox(gData->MainWnd, "Sorry, Mapper Not Supported Yet", "Error", MB_OK);
		break;
	}

	CPU->Reset();

	TIA->SLnum = 0;
	Clockticks = 0;

	bool tpb = Debugger->Logging;
	Debugger->Logging = false;
	if (Debugger->Enabled)
		Debugger->Update();
	Debugger->Logging = tpb;
}

void cAtari2600::OpenFile(char * FileName)
{
	Stop = true;

	FILE *in = fopen(FileName,"rb");

	fseek(in, 0, SEEK_END);
	int flen = ftell(in);
	fseek(in, 0, SEEK_SET);

	unsigned long CRC32 = 0;
	for (int i=0;i<flen;i++)
		CRC32 += fgetc(in);

	fseek(in, 0, SEEK_SET);

	fread(&CPU->PRG,flen,1,in);		//Read in PRG Data

	fclose(in);

	for (int i=0;i<NUM_ROMS;i++)
		if (ROMArray[i].CRC == CRC32)
			CPU->MapperType = ROMArray[i].MapperType;

	PowerOn();

	if (Debugger->Enabled)
		Debugger->Update();

	delete []FileName;
}

void cAtari2600::Run()
{
	Debugger->TraceOffset = -1;

	Stopped = false;

	do
	{
		if (Debugger->Enabled)
			Debugger->AddInst();

		TicksToCount = Ticks6507Mult[CPU->Op];
		CPU->ExecOp();
		
		if (Debugger->Enabled)
			Debugger->Update();
		
		if (PIA->Looped)
		{
			PIA->Counter -= TicksToCount;
		} else {
			PIA->CurrInterval -= TicksToCount;
			while (PIA->CurrInterval <= 0)
			{
				PIA->CurrInterval += PIA->FullInterval;
				PIA->Counter--;
				if (PIA->Counter == 0xFF)
					PIA->Looped = true;
			}
		}
		
		Clockticks += TicksToCount;
		while (Clockticks >= 228)
		{
			Clockticks -= 228;
			TIA->Scanline();
			
			MSG msg;
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				if (!TranslateAccelerator(gData->MainWnd, gData->hAccelTable, &msg)) 
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}
		}
	} while (!Stop);

	char tpo[40];
    sprintf(tpo,"NinthStar - Atari2600 - Stopped");
	SetWindowText(gData->MainWnd,tpo);

	Stopped = true;

	if (NeedQuit)
		SendMessage(gData->MainWnd, WM_TEMPDESTROY, 0, 0);
	else if (NeedDie)
		this->Release();
}

void cAtari2600::UpdateInterface()
{
	GFX->ReLoad(gData->Width, gData->Height, GFX->Mode3D);
	Debugger->DoubleSize = DoubleSize;
	Debugger->SetMode(Debugger->Mode);
}

void cAtari2600::EmuMsg(DWORD Message, DWORD Data1, DWORD Data2)
{
	HMENU MyMenu;

	switch (Message)
	{
		case ID_EMULATION_START:
			if (Stopped)
			{
				Stop = false;
				Run();
			} else {
				Stop = true;
			}
			break;
		case ID_EMULATION_STEP:
			if (Stopped)
			{
				Stop = true;
				Run();
			} else {
				Stop = true;
			}
			break;
		case ID_EMULATION_RESET:
			Reset();
			break;
		case ID_EMULATION_STOP:
			Stop = true;
			break;
		case ID_OPTIONS_DOUBLESIZEMODE:
			DoubleSize ^= true;
			MyMenu = GetMenu(gData->MainWnd);
			if (DoubleSize)
			{		//Check
				SetWindowPos(gData->MainWnd, HWND_TOP, 0, 0, (160*2)+8, (192*2)+48, SWP_SHOWWINDOW);
				gData->Width = 160*2; gData->Height = 192*2;
				CheckMenuItem(MyMenu, ID_OPTIONS_DOUBLESIZEMODE, MF_CHECKED);
			} else {	//Uncheck
				SetWindowPos(gData->MainWnd, HWND_TOP, 0, 0, 160+8, 192+48, SWP_SHOWWINDOW);
				gData->Width = 160; gData->Height = 192;
				CheckMenuItem(MyMenu, ID_OPTIONS_DOUBLESIZEMODE, MF_UNCHECKED);
			}
			break;
		case ID_OPTIONS_AUTOFRAMESKIP:
			GFX->aFSkip ^= true;
			MyMenu = GetMenu(gData->MainWnd);
			if (GFX->aFSkip)
			{		//Check
				CheckMenuItem(MyMenu, ID_OPTIONS_AUTOFRAMESKIP, MF_CHECKED);
			} else {	//Uncheck
				CheckMenuItem(MyMenu, ID_OPTIONS_AUTOFRAMESKIP, MF_UNCHECKED);
			}
			break;
		case ID_OPTIONS_DECREASEFRAMESKIP:
			if (--GFX->FSkip < 0) GFX->FSkip = 0;
			break;
		case ID_OPTIONS_INCREASEFRAMESKIP:
			GFX->FSkip++;
			break;
		case ID_OPTIONS_3DHARDWAREACCELERATION:
			GFX->Mode3D ^= true;
			UpdateInterface();
			MyMenu = GetMenu(gData->MainWnd);
			if (GFX->Mode3D)
			{		//Check
				CheckMenuItem(MyMenu, ID_OPTIONS_3DHARDWAREACCELERATION, MF_CHECKED);
			} else {	//Uncheck
				CheckMenuItem(MyMenu, ID_OPTIONS_3DHARDWAREACCELERATION, MF_UNCHECKED);
			}
			break;
		case ID_OPTIONS_FILTERINGMODE_POINTNONE:
			GFX->FilterMode = D3DTEXF_NONE;
			UpdateInterface();
			break;
		case ID_OPTIONS_FILTERINGMODE_LINEAR:
			GFX->FilterMode = D3DTEXF_LINEAR;
			UpdateInterface();
			break;
		case ID_OPTIONS_FILTERINGMODE_CUBIC:
			GFX->FilterMode = D3DTEXF_FLATCUBIC;
			UpdateInterface();
			break;
		case ID_DEBUG_OFF:
			Debugger->SetMode(0);
			MyMenu = GetMenu(gData->MainWnd);
			CheckMenuItem(MyMenu, ID_DEBUG_OFF, MF_CHECKED);
			CheckMenuItem(MyMenu, ID_DEBUG_LOW, MF_UNCHECKED);
			CheckMenuItem(MyMenu, ID_DEBUG_MEDIUM, MF_UNCHECKED);
			CheckMenuItem(MyMenu, ID_DEBUG_HIGH, MF_UNCHECKED);
			break;
		case ID_DEBUG_LOW:
			Debugger->SetMode(1);
			MyMenu = GetMenu(gData->MainWnd);
			CheckMenuItem(MyMenu, ID_DEBUG_OFF, MF_UNCHECKED);
			CheckMenuItem(MyMenu, ID_DEBUG_LOW, MF_CHECKED);
			CheckMenuItem(MyMenu, ID_DEBUG_MEDIUM, MF_UNCHECKED);
			CheckMenuItem(MyMenu, ID_DEBUG_HIGH, MF_UNCHECKED);
			break;
		case ID_DEBUG_MEDIUM:
			Debugger->SetMode(2);
			MyMenu = GetMenu(gData->MainWnd);
			CheckMenuItem(MyMenu, ID_DEBUG_OFF, MF_UNCHECKED);
			CheckMenuItem(MyMenu, ID_DEBUG_LOW, MF_UNCHECKED);
			CheckMenuItem(MyMenu, ID_DEBUG_MEDIUM, MF_CHECKED);
			CheckMenuItem(MyMenu, ID_DEBUG_HIGH, MF_UNCHECKED);
			break;
		case ID_DEBUG_HIGH:
			Debugger->SetMode(3);
			MyMenu = GetMenu(gData->MainWnd);
			CheckMenuItem(MyMenu, ID_DEBUG_OFF, MF_UNCHECKED);
			CheckMenuItem(MyMenu, ID_DEBUG_LOW, MF_UNCHECKED);
			CheckMenuItem(MyMenu, ID_DEBUG_MEDIUM, MF_UNCHECKED);
			CheckMenuItem(MyMenu, ID_DEBUG_HIGH, MF_CHECKED);
			break;
		case ID_OPTIONS_CLEARALLBREAKPOINTS:
			ZeroMemory(&Debugger->BreakP,sizeof(Debugger->BreakP));
			break;
		case ID_OPTIONS_CONTROLLERMODE_PADDLES:
			MyMenu = GetMenu(gData->MainWnd);
			PIA->Paddles = 1;
			CheckMenuItem(MyMenu, ID_OPTIONS_CONTROLLERMODE_PADDLES, MF_CHECKED);
			CheckMenuItem(MyMenu, ID_OPTIONS_CONTROLLERMODE_JOYSTICKS, MF_UNCHECKED);
			break;
		case ID_OPTIONS_CONTROLLERMODE_JOYSTICKS:
			MyMenu = GetMenu(gData->MainWnd);
			PIA->Paddles = 0;
			CheckMenuItem(MyMenu, ID_OPTIONS_CONTROLLERMODE_PADDLES, MF_UNCHECKED);
			CheckMenuItem(MyMenu, ID_OPTIONS_CONTROLLERMODE_JOYSTICKS, MF_CHECKED);
			break;
		case ID_OPTIONS_CONTROLLERCONFIG:
			PIA->OpenConfig();
			break;
/*		case ID_OPTIONS_SOUNDOPTIONS:
			//OpenSoundConfig(gData->hInst, gData->MainWnd);
			break;
		case ID_OPTIONS_SOUNDON:
			SoundEnabled ^= true;
			//ToggleSound(SoundEnabled);
			MyMenu = GetMenu(gData->MainWnd);
			if (SoundEnabled)
				CheckMenuItem(MyMenu, ID_OPTIONS_SOUNDON, MF_CHECKED);
			else 
				CheckMenuItem(MyMenu, ID_OPTIONS_SOUNDON, MF_UNCHECKED);
			break;*/
	}
}

void cAtari2600::LoadSettings()
{
	gData->hAccelTable = LoadAccelerators(gData->hInst, (LPCTSTR)IDR_A26_ACCEL);

	HMENU hMenu = LoadMenu(gData->hInst, (LPCTSTR)IDM_A26_MENU);

	unsigned long Size;
	HKEY SettingsBase;

	//Default Settings
	GFX->Mode3D = 0;
	DoubleSize = 0;
	SoundEnabled = 1;
	GFX->aFSkip = 1;
	GFX->FSkip = 0;
	//End Defaults

	RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\NinthStar\\Atari2600\\", 0, KEY_ALL_ACCESS, &SettingsBase);
	Size=4; RegQueryValueEx(SettingsBase, "SoundEnabled", 0, NULL, (unsigned char *) &SoundEnabled, &Size);
	Size=4; RegQueryValueEx(SettingsBase, "DoubleSize", 0, NULL, (unsigned char *) &DoubleSize, &Size);
	Size=4; RegQueryValueEx(SettingsBase, "aFSkip", 0, NULL, (unsigned char *) &GFX->aFSkip, &Size);
	Size=4; RegQueryValueEx(SettingsBase, "FSkip", 0, NULL, (unsigned char *) &GFX->FSkip, &Size);
	Size=4; RegQueryValueEx(SettingsBase, "Mode3D", 0, NULL, (unsigned char *) &GFX->Mode3D, &Size);
	Size=4; RegQueryValueEx(SettingsBase, "Paddles", 0, NULL, (unsigned char *) &PIA->Paddles, &Size);
	RegCloseKey(SettingsBase);
	
	if (PIA->Paddles)
	{
		CheckMenuItem(hMenu, ID_OPTIONS_CONTROLLERMODE_PADDLES, MF_CHECKED);
		CheckMenuItem(hMenu, ID_OPTIONS_CONTROLLERMODE_JOYSTICKS, MF_UNCHECKED);
	} else {
		CheckMenuItem(hMenu, ID_OPTIONS_CONTROLLERMODE_PADDLES, MF_UNCHECKED);
		CheckMenuItem(hMenu, ID_OPTIONS_CONTROLLERMODE_JOYSTICKS, MF_CHECKED);
	}

	if (SoundEnabled)
		CheckMenuItem(hMenu, ID_OPTIONS_SOUNDON, MF_CHECKED);
	else
		CheckMenuItem(hMenu, ID_OPTIONS_SOUNDON, MF_UNCHECKED);
	if (GFX->Mode3D)
		CheckMenuItem(hMenu, ID_OPTIONS_3DHARDWAREACCELERATION, MF_CHECKED);
	else
		CheckMenuItem(hMenu, ID_OPTIONS_3DHARDWAREACCELERATION, MF_UNCHECKED);
	if (GFX->aFSkip)
		CheckMenuItem(hMenu, ID_OPTIONS_AUTOFRAMESKIP, MF_CHECKED);
	else
		CheckMenuItem(hMenu, ID_OPTIONS_AUTOFRAMESKIP, MF_UNCHECKED);
	if (DoubleSize)
	{		//Check
		gData->Width = 160*2; gData->Height = 192*2;
		CheckMenuItem(hMenu, ID_OPTIONS_DOUBLESIZEMODE, MF_CHECKED);
	} else {	//Uncheck
		gData->Width = 160; gData->Height = 192;
		CheckMenuItem(hMenu, ID_OPTIONS_DOUBLESIZEMODE, MF_UNCHECKED);
	}

	SetMenu(gData->MainWnd, hMenu);

	SetWindowPos(gData->MainWnd, HWND_TOP, 0, 0, gData->Width+8, gData->Height+48, SWP_SHOWWINDOW);

//	SetControlConfig(Keys);

	PowerOn();
}