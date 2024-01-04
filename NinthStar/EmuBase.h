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

#ifndef EMUBASE_H
#define EMUBASE_H

class cEmuBase {
	public :
		cEmuBase() { }
		virtual void Release() { }

		virtual void OpenFile(char *toopen) { }

		virtual void UpdateInterface() { }
		virtual void RePaint() { }

		virtual void SaveSettings() { }
		virtual void LoadSettings() { }

		virtual void Run() { }
		virtual void IRQ() { }

		virtual void EmuMsg(DWORD Message, DWORD Data1, DWORD Data2) { }

		int Clockticks, LastTicks;

		bool Stop, Stopped, NeedQuit, NeedDie;

	private :
};

#endif