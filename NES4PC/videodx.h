//---------------------------------------------------------------------------
#ifndef tstgdiH
#define tstgdiH
//---------------------------------------------------------------------------
void ClearFrame();
bool Render();

bool DXOpen();
void DXClose();
bool DXLock();
bool DXUnlock();

void pset(short int x,short int y,unsigned long color);
bool VideoSetup(TForm *nf);
void VideoShutdown();
//---------------------------------------------------------------------------
#endif
