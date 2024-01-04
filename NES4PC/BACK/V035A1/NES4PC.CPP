//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("main.cpp", StartFrm);
USERES("nes4pc.res");
USEUNIT("video.cpp");
USEUNIT("6502.cpp");
USEUNIT("audio.cpp");
USEFORM("AboutWindowForm.cpp", AboutWindow);
USEFORM("OptionsWindowForm.cpp", OptionsForm);
USEUNIT("Defines.cpp");
USEFORM("TimingWindowForm.cpp", TimingForm);
USEFORM("DebugFrm.cpp", DebugForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	try
	{
		Application->Initialize();
		Application->Title = "NES4PC";
		Application->CreateForm(__classid(TStartFrm), &StartFrm);
		Application->CreateForm(__classid(TAboutWindow), &AboutWindow);
		Application->CreateForm(__classid(TOptionsForm), &OptionsForm);
		Application->CreateForm(__classid(TTimingForm), &TimingForm);
		Application->CreateForm(__classid(TDebugForm), &DebugForm);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	return 0;
}
//---------------------------------------------------------------------------
