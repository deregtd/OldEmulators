//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#include <mmsystem.h>
#include <dsound.h>
#include <memory.h>
#pragma hdrstop

#include "audio.h"
//---------------------------------------------------------------------------
extern MemSt Mem;
extern PulseChanSt PulseChan[2];
extern TriChanSt TriChan;
extern NoiseChanSt NoiseChan;
extern DCMChanSt DCMChan;
bool SoundEnabled;
//---------------------------------------------------------------------------
BYTE LengthInfo[32] = {
	5, 126, 10, 1, 19, 2, 40, 3, 80, 4, 30, 5, 7, 6, 13, 7, 6,
	8, 12, 9, 24, 10, 48, 11, 96, 12, 36, 13, 8, 14, 16, 15
};
float PulseWidthInfo[4] = {
	.125, .25, .5, .75
};
LBYTE PlayDataRate[16] = {
	4182, 4710, 5264, 5593, 6258, 7046, 7919, 8363,
	9420, 11186, 12604, 13983, 18885, 21096, 24858, 32767
};
//---------------------------------------------------------------------------
BYTE	bWave[4][32] =
{
	{00,00,00,00,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63},
	{00,00,00,00,00,00,00,00,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63},
	{00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63},
	{00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,63,63,63,63,63,63,63,63}
};
BYTE	bTri[4][32] =
{
	{00,00,00,00,1,1,3,3,3,7,7,15,15,15,31,31,63,63,63,63,31,31,31,15,15,7,7,3,3,3,1,1},
	{00,00,00,00,00,00,00,00,1,1,3,3,7,7,15,15,31,31,63,63,63,63,31,31,15,15,7,7,3,3,1,1},
	{00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,1,3,7,7,15,15,31,63,63,31,15,15,7,7,3,1},
	{00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,7,15,31,63,63,31,15,7}
};
BYTE	bWAVE[32];
BYTE	bPoly[32] = {0,64,0,0,64,0,0,64,0,0,64,0,0,64,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,23};
DWORD	dwFreqTable[2048];
BYTE	bFryUp=0xdf;

DWORD	dwSoundFrequency=22050;
LONG	lSoundTicker;
HANDLE	hThread;
DWORD	dwThreadId;

#define SND_LEN	512	//256

#define NUMEVENTS 2

HWND	hwndOutput;
LPDIRECTSOUND               lpds;
DSBUFFERDESC                dsbdesc;
LPDIRECTSOUNDBUFFER         lpdsb;
LPDIRECTSOUNDBUFFER         lpdsbPrimary;
LPDIRECTSOUNDNOTIFY         lpdsNotify;
WAVEFORMATEX                *pwfx;
MMCKINFO                    mmckinfoData, mmckinfoParent;
DSBPOSITIONNOTIFY           rgdsbpn[NUMEVENTS];
HANDLE                      rghEvent[NUMEVENTS];

struct _SNDChan SNDChannels[5];
//---------------------------------------------------------------------------
void PauseAudio()
{
	for(int i=0;i<5;i++)
	{
		SNDChannels[i].bVol=0;
	}
	for (int i=0;i<1000;i++)
	{
		Application->ProcessMessages();
	}
//	SuspendThread(hThread);
}

void ResumeAudio()
{
	int tmptcnt = 2;
	while (tmptcnt > 1)
	{
		tmptcnt = ResumeThread(hThread);
	}
}
//---------------------------------------------------------------------------
void __fastcall AudioSetup(TForm *tf)
{
	hwndOutput = tf->Handle;

	int	i;
	double	freq;
	double freqt;

	for(i=0;i<2048;i++)
	{
		freqt = 3579545/(double)(32*(i + 1));
		freq = (freqt/((double)dwSoundFrequency));
		dwFreqTable[i] = (DWORD)(freq*65536.0);
	}

	// Setup a thread to handle the processing of the sound.
	hThread = CreateThread(0,0,SND_Thread,0,0,&dwThreadId);

	SNDChannels[0].bVolDir=2;
	SNDChannels[1].bVolDir=2;
	SNDChannels[3].bVolDir=2;
	SNDChannels[4].bVolDir=2;

	PauseAudio();
}

DWORD WINAPI SND_Thread( LPVOID vPtr )
{
	int	i;
	WAVEFORMATEX wfx;
	BOOL Done = FALSE;
	GUID IID_IDirectSoundNotify = { 0xb0210783 , 0x89cd , 0x11d0, 0xaf, 0x8, 0x0, 0xa0, 0xc9, 0x25, 0xcd, 0x16 };

	// Create Direct Sound Object.

	if (DirectSoundCreate( NULL, &lpds, NULL ) != DS_OK)
	{
		tprinto("DirectSound Error!  Sound disabled!");
		return(0);
	}
	// Set co-op level.

	lpds->SetCooperativeLevel( hwndOutput, DSSCL_PRIORITY);	//DSSCL_NORMAL );

	// Obtain primary buffer
	ZeroMemory(&dsbdesc, sizeof(DSBUFFERDESC));
	dsbdesc.dwSize = sizeof(DSBUFFERDESC);
	dsbdesc.dwFlags = DSBCAPS_PRIMARYBUFFER;
	lpds->CreateSoundBuffer(&dsbdesc,&lpdsbPrimary,NULL);

	// Set primary buffer format
	memset(&wfx, 0, sizeof(WAVEFORMATEX));
	wfx.wFormatTag = WAVE_FORMAT_PCM;
	wfx.nChannels = 1;
	wfx.nSamplesPerSec = dwSoundFrequency;
	wfx.wBitsPerSample = (BYTE) 8;
	wfx.nBlockAlign = (WORD) (wfx.wBitsPerSample / 8 * wfx.nChannels);
	wfx.nAvgBytesPerSec = (DWORD) (wfx.nSamplesPerSec * wfx.nBlockAlign);
	lpdsbPrimary->SetFormat(&wfx);

	memset(&dsbdesc, 0, sizeof(DSBUFFERDESC));
	dsbdesc.dwSize = sizeof(DSBUFFERDESC);
	dsbdesc.dwFlags =  DSBCAPS_GETCURRENTPOSITION2   // Always a good idea
			| DSBCAPS_GLOBALFOCUS         // Allows background playing
			| DSBCAPS_CTRLPOSITIONNOTIFY; // Needed for notification
	// The size of the buffer is arbitrary, but should be at least
	// two seconds, to keep data writes well ahead of the play
	// position.
	dsbdesc.dwBufferBytes = SND_LEN*2; //wfx.nAvgBytesPerSec * 2;
	dsbdesc.lpwfxFormat = &wfx;
	lpds->CreateSoundBuffer(&dsbdesc,&lpdsb,NULL);

	for ( i = 0; i < NUMEVENTS; i++)
	{
		rghEvent[i] = CreateEvent(NULL, FALSE, FALSE, NULL);
		if (NULL == rghEvent[i]) return -5;
	}

	rgdsbpn[0].dwOffset = 0;
	rgdsbpn[0].hEventNotify = rghEvent[0];
	rgdsbpn[1].dwOffset = (dsbdesc.dwBufferBytes/2);
	rgdsbpn[1].hEventNotify = rghEvent[1];

	lpdsb->QueryInterface(IID_IDirectSoundNotify,&(LPVOID)lpdsNotify);

	lpdsNotify->SetNotificationPositions(NUMEVENTS,rgdsbpn);

	lpdsb->Play(0,0,DSBPLAY_LOOPING);

	while (!Done)
	{
		DWORD dwEvt = MsgWaitForMultipleObjects(
			NUMEVENTS,      // How many possible events
			rghEvent,       // Location of handles
			FALSE,          // Wait for all?
			INFINITE,       // How long to wait
			QS_ALLINPUT);   // Any message is an event
		// WAIT_OBJECT_0 == 0 but is properly treated as an arbitrary
		// index value assigned to the first event, therefore we subtract
		// it from dwEvt to get the zero-based index of the event.
		dwEvt -= WAIT_OBJECT_0;
		// If the event was set by the buffer, there's input
		// to process.
		if (dwEvt < NUMEVENTS)
		{
			LONG            lNumToWrite;
			DWORD           dwStartOfs;
			VOID            *lpvPtr1, *lpvPtr2;
			DWORD           dwBytes1, dwBytes2;

			if (dwEvt == 0)
				dwStartOfs = rgdsbpn[NUMEVENTS - 1].dwOffset;
			else
				dwStartOfs = rgdsbpn[dwEvt-1].dwOffset;
			lNumToWrite = (LONG) rgdsbpn[dwEvt].dwOffset - dwStartOfs;
			if (lNumToWrite < 0) lNumToWrite += dsbdesc.dwBufferBytes;

			lpdsb->Lock(
					 dwStartOfs,       // Offset of lock start
					 lNumToWrite,      // Number of bytes to lock
					 &lpvPtr1,         // Address of lock start
					 &dwBytes1,        // Count of bytes locked
					 &lpvPtr2,         // Address of wrap around
					 &dwBytes2,        // Count of wrap around bytes
					 0);               // Flags

			SND_Calc((BYTE*)lpvPtr1);

			lpdsb->Unlock(lpvPtr1, dwBytes1, lpvPtr2, dwBytes2);
		// If it's the last event, it's a message
		}  // end message processing
		else if (dwEvt == NUMEVENTS)
		{
			MSG	msg;
			while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				if (msg.message == WM_QUIT)
				{
					Done = TRUE;
				}
				else
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}
		}  // end message processing
	} // while (!Done)

	tprint("DirectSound Initialized!");
	return(0);
}

void __fastcall AudioShutdown()
{
	PauseAudio();
}
//---------------------------------------------------------------------------
void SND_Calc(BYTE	*bBuf)
{
	if (!SoundEnabled) return;
	int	i,j;
	BYTE	b;

	lSoundTicker = (DWORD) (((dwSoundFrequency)*7.8)/1000.0);

//	for(i=0;i<32;i++)
//	{
//		bPoly[i] += (BYTE) (((bFryUp^0xbe)<<1)&0x1f);
//		bFryUp += (BYTE) 0x37;
//	}

//	setmem(&bBuf[0], SND_LEN, 0);
	for(i=0;i<SND_LEN;i++)
		bBuf[i]=0;

	for(i=0;i<2;i++)
	{
		if(SNDChannels[i].bVol!=0)
		{
			switch(i)
			{
			case	0:	case	1:		//Pulse
				if (!PulseChan[i].Enabled) break;
				for(j=0;j<SND_LEN;j++)
				{
					b = bWave[SNDChannels[i].bWaveDuty]
						[(SNDChannels[i].dwCycle>>11)&0x1f];
					b = (BYTE) ((SNDChannels[i].bVol*b)>>4);
					bBuf[j] = (BYTE) ((bBuf[j]+b)>>1);
					SNDChannels[i].dwCycle+=dwFreqTable[SNDChannels[i].dwFreq];
					SNDChannels[i].lVTicker--;	//=lSoundTicker;
					if(SNDChannels[i].lVTicker<0)
					{
						SNDChannels[i].lVTicker = SNDChannels[i].lVTickerInit;
						if(SNDChannels[i].bVolDir == 0)
							if(SNDChannels[i].bVol!=0)
								SNDChannels[i].bVol--;
						if(SNDChannels[i].bVolDir == 1)
							if(SNDChannels[i].bVol!=15)
								SNDChannels[i].bVol++;
					}
				}
				break;
			case    2:   //Tri
				if (!TriChan.Enabled) break;
				for(j=0;j<SND_LEN;j++)
				{
					b = bTri[SNDChannels[i].bWaveDuty]
						[(SNDChannels[i].dwCycle>>11)&0x1f];
					b = (BYTE) ((SNDChannels[i].bVol*b)>>4);
					bBuf[j] = (BYTE) ((bBuf[j]+b)>>1);
					SNDChannels[i].dwCycle+=dwFreqTable[SNDChannels[i].dwFreq];
					SNDChannels[i].lVTicker--;	//=lSoundTicker;
					if(SNDChannels[i].lVTicker<0)
					{
						SNDChannels[i].lVTicker = SNDChannels[i].lVTickerInit;
						if(SNDChannels[i].bVolDir == 0)
							if(SNDChannels[i].bVol!=0)
								SNDChannels[i].bVol--;
						if(SNDChannels[i].bVolDir == 1)
							if(SNDChannels[i].bVol!=15)
								SNDChannels[i].bVol++;
					}
				}
				break;
			case	3:		//Noise
				if (!NoiseChan.Enabled) break;

				for(j=0;j<SND_LEN;j++)
				{
					b = bPoly[(SNDChannels[i].dwCycle>>11)&0x1f];
					b = (BYTE) ((SNDChannels[i].bVol*b)>>4);
					bBuf[j] = (BYTE) ((bBuf[j]+b) >> 1);
					SNDChannels[i].dwCycle+=dwFreqTable[SNDChannels[i].dwFreq];
					SNDChannels[i].lVTicker--;//=lSoundTicker;
					if(SNDChannels[i].lVTicker<0)
					{
						if(SNDChannels[i].bVolDir == 0)
							if(SNDChannels[i].bVol!=0)
								SNDChannels[i].bVol--;
						if(SNDChannels[i].bVolDir == 1)
							if(SNDChannels[i].bVol!=15)
								SNDChannels[i].bVol++;
					}
				}
				break;
			case	4:		//PCM
				if ((!DCMChan.Enabled) || (DCMChan.BitPointer > (DCMChan.BitLength >> 3))) break;
				for(j=0;j<32;j++)
				{
					bWAVE[j] = DCMChan.Data[(short int) DCMChan.BitPointer];
					DCMChan.BitPointer+=DCMChan.PlaybackRate/0x1000;
				}
				for(j=0;j<SND_LEN;j++)
				{
					b = (BYTE) (bWAVE[(SNDChannels[i].dwCycle>>11)&0x1f]);
					b = (BYTE)((SNDChannels[i].bVol*b)>>4);
					bBuf[j] = (BYTE) ((bBuf[j]+b) >> 1);
					SNDChannels[i].dwCycle+=dwFreqTable[SNDChannels[i].dwFreq];
					SNDChannels[i].lVTicker-=lSoundTicker;
				}
				break;
			default:
				break;
			}
		}
	}
}
//---------------------------------------------------------------------------

