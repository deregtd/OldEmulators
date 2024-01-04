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

// Very -=VERY=- Messy...  Going to need to be rewritten but I just wanted to make
// Akilla happy.  Hi2u Akilla :PPP

// Azimer
//
// History:
// ------------------------------------------------------------------------------------
// Dec. 17th	-	BASIC Pulse Waves #1 and #2 completed (sounds pretty nice actually)

#include "stdafx.h"

#include <stdio.h> // Needed for debugging information...

#include "NES_APU.h"
#include "..\NinthStar.h"

cNES_APU *APU;

