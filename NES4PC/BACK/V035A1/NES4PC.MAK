# ---------------------------------------------------------------------------
VERSION = BCB.01
# ---------------------------------------------------------------------------
!ifndef BCB
BCB = $(MAKEDIR)\..
!endif
# ---------------------------------------------------------------------------
PROJECT = nes4pc.exe
OBJFILES = nes4pc.obj main.obj video.obj 6502.obj audio.obj \
   AboutWindowForm.obj OptionsWindowForm.obj Defines.obj TimingWindowForm.obj \
   DebugFrm.obj
RESFILES = nes4pc.res
RESDEPEN = $(RESFILES) main.dfm AboutWindowForm.dfm OptionsWindowForm.dfm \
   TimingWindowForm.dfm DebugFrm.dfm
LIBFILES = 
DEFFILE = 
# ---------------------------------------------------------------------------
CFLAG1 = -O2 -Hc -w -k- -r -vi -c -a4 -b- -w-par -w-inl -Vx -Ve -x -5
CFLAG2 = -I$(BCB)\projects;$(BCB)\include;$(BCB)\include\vcl \
   -H=$(BCB)\lib\vcl.csm 
PFLAGS = -AWinTypes=Windows;WinProcs=Windows;DbiTypes=BDE;DbiProcs=BDE;DbiErrs=BDE \
   -U$(BCB)\projects;$(BCB)\lib\obj;$(BCB)\lib \
   -I$(BCB)\projects;$(BCB)\include;$(BCB)\include\vcl -$L- -$D- -JPHNV -M  
RFLAGS = -i$(BCB)\projects;$(BCB)\include;$(BCB)\include\vcl 
LFLAGS = -L$(BCB)\projects;$(BCB)\lib\obj;$(BCB)\lib -aa -Tpe -x -V4.0 
IFLAGS = 
LINKER = ilink32
# ---------------------------------------------------------------------------
ALLOBJ = c0w32.obj $(OBJFILES)
ALLRES = $(RESFILES)
ALLLIB = $(LIBFILES) vcl.lib import32.lib cp32mt.lib 
# ---------------------------------------------------------------------------
.autodepend

$(PROJECT): $(OBJFILES) $(RESDEPEN) $(DEFFILE)
    $(BCB)\BIN\$(LINKER) @&&!
    $(LFLAGS) +
    $(ALLOBJ), +
    $(PROJECT),, +
    $(ALLLIB), +
    $(DEFFILE), +
    $(ALLRES) 
!

.pas.hpp:
    $(BCB)\BIN\dcc32 $(PFLAGS) { $** }

.pas.obj:
    $(BCB)\BIN\dcc32 $(PFLAGS) { $** }

.cpp.obj:
    $(BCB)\BIN\bcc32 $(CFLAG1) $(CFLAG2) -o$* $* 

.c.obj:
    $(BCB)\BIN\bcc32 $(CFLAG1) $(CFLAG2) -o$* $**

.rc.res:
    $(BCB)\BIN\brcc32 $(RFLAGS) $<
#-----------------------------------------------------------------------------
