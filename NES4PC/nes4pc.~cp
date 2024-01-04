//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("main.cpp", StartFrm);
USERES("nes4pc.res");
USEUNIT("6502.cpp");
USEFORM("AboutWindowForm.cpp", AboutWindow);
USEFORM("OptionsWindowForm.cpp", OptionsForm);
USEUNIT("Defines.cpp");
USEUNIT("States.cpp");
USEUNIT("video.cpp");
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
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	return 0;
}
//---------------------------------------------------------------------------
