//---------------------------------------------------------------------------
#ifndef audioH
#define audioH
//---------------------------------------------------------------------------
#include "video.h"
//---------------------------------------------------------------------------
struct PulseChanSt {
	unsigned short int Frequency;
	unsigned char LengthLeft;
	unsigned char Width;
	float Volume;
	float FadeSpeed;
	unsigned char VolFade;
	unsigned char Fade;
	bool Loop;
	bool Enabled;
};
struct TriChanSt {
	unsigned short int Frequency;
	unsigned char LengthLeft;
	bool Enabled;
};
struct NoiseChanSt {
	bool Enabled;
};
struct DCMChanSt {
	unsigned char Data[4200];
	unsigned short int BitLength;
	float BitPointer;
	unsigned short int Address;
	unsigned char Volume;
	bool DataBusBit;		//????
	short int PlaybackRate;
	bool IRQGen;
	bool Loop;
	bool Enabled;
};
//---------------------------------------------------------------------------
void ResumeAudio();
void PauseAudio();
void SND_Calc(BYTE	*bBuf);
DWORD WINAPI SND_Thread( LPVOID vPtr );
void __fastcall AudioSetup(TForm *tf);
void __fastcall AudioShutdown();
//---------------------------------------------------------------------------
struct _SNDChan
{
	unsigned dwFreq : 11;	//Frequency: 11-bit (0-2047)
//	DWORD	dwFreq;			//Frequency (0-2047)
//	double	Cycle;
	DWORD	dwCycle;
	BYTE	bWaveDuty;		//Pulsewidth, 0-3 ($4000, D0/D1)
//	BYTE	bLen;
	BYTE	bVolDir;		// Direction of volume fade.
//	BYTE	bIVol;			// Initial Volume.
	BYTE	bVol;			// Current Volume Level.
	LONG	lVTickerInit;	// Ticker initialization value.
//	LONG	lTickerTime;	// One time element of the ticker..
	LONG	lVTicker;		// Timer Used for updating Variables.
};
//---------------------------------------------------------------------------
#endif
