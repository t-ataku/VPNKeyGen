# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** 編集しないでください **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=dotkey95 - Win32 Debug nocache
!MESSAGE 構成が指定されていません。ﾃﾞﾌｫﾙﾄの dotkey95 - Win32 Debug nocache を設定します。
!ENDIF 

!IF "$(CFG)" != "dotkey95 - Win32 Release" && "$(CFG)" !=\
 "dotkey95 - Win32 Debug" && "$(CFG)" != "dotkey95 - Win32 Debug nocache" &&\
 "$(CFG)" != "dotkey95 - Win32 Release nocache"
!MESSAGE 指定された ﾋﾞﾙﾄﾞ ﾓｰﾄﾞ "$(CFG)" は正しくありません。
!MESSAGE ｺﾏﾝﾄﾞ ﾗｲﾝ上でﾏｸﾛ 'CFG' を定義することによって
!MESSAGE NMAKE 実行時にﾋﾞﾙﾄﾞ ﾓｰﾄﾞを指定できます。例えば:
!MESSAGE 
!MESSAGE NMAKE /f "dotkey95.mak" CFG="dotkey95 - Win32 Debug nocache"
!MESSAGE 
!MESSAGE 選択可能なﾋﾞﾙﾄﾞ ﾓｰﾄﾞ:
!MESSAGE 
!MESSAGE "dotkey95 - Win32 Release" ("Win32 (x86) Application" 用)
!MESSAGE "dotkey95 - Win32 Debug" ("Win32 (x86) Application" 用)
!MESSAGE "dotkey95 - Win32 Debug nocache" ("Win32 (x86) Application" 用)
!MESSAGE "dotkey95 - Win32 Release nocache" ("Win32 (x86) Application" 用)
!MESSAGE 
!ERROR 無効な構成が指定されています。
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 
################################################################################
# Begin Project
# PROP Target_Last_Scanned "dotkey95 - Win32 Debug"
RSC=rc.exe
MTL=mktyplib.exe
CPP=cl.exe

!IF  "$(CFG)" == "dotkey95 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\dotkey95.exe" "$(OUTDIR)\dotkey95.bsc"

CLEAN : 
	-@erase "$(INTDIR)\Dotkey95.obj"
	-@erase "$(INTDIR)\Dotkey95.res"
	-@erase "$(INTDIR)\Dotkey95.sbr"
	-@erase "$(INTDIR)\Md4.obj"
	-@erase "$(INTDIR)\Md4.sbr"
	-@erase "$(INTDIR)\Md5c.obj"
	-@erase "$(INTDIR)\Md5c.sbr"
	-@erase "$(INTDIR)\Otp_hash.obj"
	-@erase "$(INTDIR)\Otp_hash.sbr"
	-@erase "$(INTDIR)\Otp_put.obj"
	-@erase "$(INTDIR)\Otp_put.sbr"
	-@erase "$(INTDIR)\Prefs.obj"
	-@erase "$(INTDIR)\Prefs.sbr"
	-@erase "$(INTDIR)\Sha.obj"
	-@erase "$(INTDIR)\Sha.sbr"
	-@erase "$(INTDIR)\Tray.obj"
	-@erase "$(INTDIR)\Tray.sbr"
	-@erase "$(OUTDIR)\dotkey95.bsc"
	-@erase "$(OUTDIR)\dotkey95.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "PROTOTYPES" /D "MSDOS" /D "LITTLE_ENDIAN" /D "USE_STDLIB_H" /D "USE_STRING_H" /D SIGTYPE=int /FR /YX /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "PROTOTYPES" /D "MSDOS" /D "LITTLE_ENDIAN" /D "USE_STDLIB_H" /D "USE_STRING_H"\
 /D SIGTYPE=int /FR"$(INTDIR)/" /Fp"$(INTDIR)/dotkey95.pch" /YX /Fo"$(INTDIR)/"\
 /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\Release/
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x411 /d "NDEBUG"
# ADD RSC /l 0x411 /d "NDEBUG"
RSC_PROJ=/l 0x411 /fo"$(INTDIR)/Dotkey95.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/dotkey95.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Dotkey95.sbr" \
	"$(INTDIR)\Md4.sbr" \
	"$(INTDIR)\Md5c.sbr" \
	"$(INTDIR)\Otp_hash.sbr" \
	"$(INTDIR)\Otp_put.sbr" \
	"$(INTDIR)\Prefs.sbr" \
	"$(INTDIR)\Sha.sbr" \
	"$(INTDIR)\Tray.sbr"

"$(OUTDIR)\dotkey95.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/dotkey95.pdb" /machine:I386 /out:"$(OUTDIR)/dotkey95.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Dotkey95.obj" \
	"$(INTDIR)\Dotkey95.res" \
	"$(INTDIR)\Md4.obj" \
	"$(INTDIR)\Md5c.obj" \
	"$(INTDIR)\Otp_hash.obj" \
	"$(INTDIR)\Otp_put.obj" \
	"$(INTDIR)\Prefs.obj" \
	"$(INTDIR)\Sha.obj" \
	"$(INTDIR)\Tray.obj"

"$(OUTDIR)\dotkey95.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "dotkey95 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\dotkey95.exe" "$(OUTDIR)\dotkey95.bsc"

CLEAN : 
	-@erase "$(INTDIR)\Dotkey95.obj"
	-@erase "$(INTDIR)\Dotkey95.res"
	-@erase "$(INTDIR)\Dotkey95.sbr"
	-@erase "$(INTDIR)\Md4.obj"
	-@erase "$(INTDIR)\Md4.sbr"
	-@erase "$(INTDIR)\Md5c.obj"
	-@erase "$(INTDIR)\Md5c.sbr"
	-@erase "$(INTDIR)\Otp_hash.obj"
	-@erase "$(INTDIR)\Otp_hash.sbr"
	-@erase "$(INTDIR)\Otp_put.obj"
	-@erase "$(INTDIR)\Otp_put.sbr"
	-@erase "$(INTDIR)\Prefs.obj"
	-@erase "$(INTDIR)\Prefs.sbr"
	-@erase "$(INTDIR)\Sha.obj"
	-@erase "$(INTDIR)\Sha.sbr"
	-@erase "$(INTDIR)\Tray.obj"
	-@erase "$(INTDIR)\Tray.sbr"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\dotkey95.bsc"
	-@erase "$(OUTDIR)\dotkey95.exe"
	-@erase "$(OUTDIR)\dotkey95.ilk"
	-@erase "$(OUTDIR)\dotkey95.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "PROTOTYPES" /D "MSDOS" /D "LITTLE_ENDIAN" /D "USE_STDLIB_H" /D "USE_STRING_H" /D SIGTYPE=int /FR /YX /c
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "PROTOTYPES" /D "MSDOS" /D "LITTLE_ENDIAN" /D "USE_STDLIB_H" /D\
 "USE_STRING_H" /D SIGTYPE=int /FR"$(INTDIR)/" /Fp"$(INTDIR)/dotkey95.pch" /YX\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x411 /d "_DEBUG"
# ADD RSC /l 0x411 /d "_DEBUG"
RSC_PROJ=/l 0x411 /fo"$(INTDIR)/Dotkey95.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/dotkey95.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Dotkey95.sbr" \
	"$(INTDIR)\Md4.sbr" \
	"$(INTDIR)\Md5c.sbr" \
	"$(INTDIR)\Otp_hash.sbr" \
	"$(INTDIR)\Otp_put.sbr" \
	"$(INTDIR)\Prefs.sbr" \
	"$(INTDIR)\Sha.sbr" \
	"$(INTDIR)\Tray.sbr"

"$(OUTDIR)\dotkey95.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/dotkey95.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/dotkey95.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Dotkey95.obj" \
	"$(INTDIR)\Dotkey95.res" \
	"$(INTDIR)\Md4.obj" \
	"$(INTDIR)\Md5c.obj" \
	"$(INTDIR)\Otp_hash.obj" \
	"$(INTDIR)\Otp_put.obj" \
	"$(INTDIR)\Prefs.obj" \
	"$(INTDIR)\Sha.obj" \
	"$(INTDIR)\Tray.obj"

"$(OUTDIR)\dotkey95.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "dotkey95 - Win32 Debug nocache"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "dotkey95"
# PROP BASE Intermediate_Dir "dotkey95"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DbgNocache"
# PROP Intermediate_Dir "DbgNocache"
# PROP Target_Dir ""
OUTDIR=.\DbgNocache
INTDIR=.\DbgNocache

ALL : "$(OUTDIR)\dotkey95.exe" "$(OUTDIR)\dotkey95.bsc"

CLEAN : 
	-@erase "$(INTDIR)\Dotkey95.obj"
	-@erase "$(INTDIR)\Dotkey95.res"
	-@erase "$(INTDIR)\Dotkey95.sbr"
	-@erase "$(INTDIR)\Md4.obj"
	-@erase "$(INTDIR)\Md4.sbr"
	-@erase "$(INTDIR)\Md5c.obj"
	-@erase "$(INTDIR)\Md5c.sbr"
	-@erase "$(INTDIR)\Otp_hash.obj"
	-@erase "$(INTDIR)\Otp_hash.sbr"
	-@erase "$(INTDIR)\Otp_put.obj"
	-@erase "$(INTDIR)\Otp_put.sbr"
	-@erase "$(INTDIR)\Prefs.obj"
	-@erase "$(INTDIR)\Prefs.sbr"
	-@erase "$(INTDIR)\Sha.obj"
	-@erase "$(INTDIR)\Sha.sbr"
	-@erase "$(INTDIR)\Tray.obj"
	-@erase "$(INTDIR)\Tray.sbr"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\dotkey95.bsc"
	-@erase "$(OUTDIR)\dotkey95.exe"
	-@erase "$(OUTDIR)\dotkey95.ilk"
	-@erase "$(OUTDIR)\dotkey95.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "PROTOTYPES" /D "MSDOS" /D "LITTLE_ENDIAN" /D "USE_STDLIB_H" /D "USE_STRING_H" /D SIGTYPE=int /FR /YX /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "PROTOTYPES" /D "MSDOS" /D "LITTLE_ENDIAN" /D "USE_STDLIB_H" /D "USE_STRING_H" /D SIGTYPE=int /D "NOCACHE" /FR /YX /c
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "PROTOTYPES" /D "MSDOS" /D "LITTLE_ENDIAN" /D "USE_STDLIB_H" /D\
 "USE_STRING_H" /D SIGTYPE=int /D "NOCACHE" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/dotkey95.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\DbgNocache/
CPP_SBRS=.\DbgNocache/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x411 /d "_DEBUG"
# ADD RSC /l 0x411 /d "_DEBUG"
RSC_PROJ=/l 0x411 /fo"$(INTDIR)/Dotkey95.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/dotkey95.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Dotkey95.sbr" \
	"$(INTDIR)\Md4.sbr" \
	"$(INTDIR)\Md5c.sbr" \
	"$(INTDIR)\Otp_hash.sbr" \
	"$(INTDIR)\Otp_put.sbr" \
	"$(INTDIR)\Prefs.sbr" \
	"$(INTDIR)\Sha.sbr" \
	"$(INTDIR)\Tray.sbr"

"$(OUTDIR)\dotkey95.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/dotkey95.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/dotkey95.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Dotkey95.obj" \
	"$(INTDIR)\Dotkey95.res" \
	"$(INTDIR)\Md4.obj" \
	"$(INTDIR)\Md5c.obj" \
	"$(INTDIR)\Otp_hash.obj" \
	"$(INTDIR)\Otp_put.obj" \
	"$(INTDIR)\Prefs.obj" \
	"$(INTDIR)\Sha.obj" \
	"$(INTDIR)\Tray.obj"

"$(OUTDIR)\dotkey95.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "dotkey95 - Win32 Release nocache"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "dotkey90"
# PROP BASE Intermediate_Dir "dotkey90"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "RelNocache"
# PROP Intermediate_Dir "RelNocache"
# PROP Target_Dir ""
OUTDIR=.\RelNocache
INTDIR=.\RelNocache

ALL : "$(OUTDIR)\dotkey95.exe" "$(OUTDIR)\dotkey95.bsc"

CLEAN : 
	-@erase "$(INTDIR)\Dotkey95.obj"
	-@erase "$(INTDIR)\Dotkey95.res"
	-@erase "$(INTDIR)\Dotkey95.sbr"
	-@erase "$(INTDIR)\Md4.obj"
	-@erase "$(INTDIR)\Md4.sbr"
	-@erase "$(INTDIR)\Md5c.obj"
	-@erase "$(INTDIR)\Md5c.sbr"
	-@erase "$(INTDIR)\Otp_hash.obj"
	-@erase "$(INTDIR)\Otp_hash.sbr"
	-@erase "$(INTDIR)\Otp_put.obj"
	-@erase "$(INTDIR)\Otp_put.sbr"
	-@erase "$(INTDIR)\Prefs.obj"
	-@erase "$(INTDIR)\Prefs.sbr"
	-@erase "$(INTDIR)\Sha.obj"
	-@erase "$(INTDIR)\Sha.sbr"
	-@erase "$(INTDIR)\Tray.obj"
	-@erase "$(INTDIR)\Tray.sbr"
	-@erase "$(OUTDIR)\dotkey95.bsc"
	-@erase "$(OUTDIR)\dotkey95.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "PROTOTYPES" /D "MSDOS" /D "LITTLE_ENDIAN" /D "USE_STDLIB_H" /D "USE_STRING_H" /D SIGTYPE=int /YX /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "PROTOTYPES" /D "MSDOS" /D "LITTLE_ENDIAN" /D "USE_STDLIB_H" /D "USE_STRING_H" /D SIGTYPE=int /D "NOCACHE" /FR /YX /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "PROTOTYPES" /D "MSDOS" /D "LITTLE_ENDIAN" /D "USE_STDLIB_H" /D "USE_STRING_H"\
 /D SIGTYPE=int /D "NOCACHE" /FR"$(INTDIR)/" /Fp"$(INTDIR)/dotkey95.pch" /YX\
 /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\RelNocache/
CPP_SBRS=.\RelNocache/
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x411 /d "NDEBUG"
# ADD RSC /l 0x411 /d "NDEBUG"
RSC_PROJ=/l 0x411 /fo"$(INTDIR)/Dotkey95.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/dotkey95.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Dotkey95.sbr" \
	"$(INTDIR)\Md4.sbr" \
	"$(INTDIR)\Md5c.sbr" \
	"$(INTDIR)\Otp_hash.sbr" \
	"$(INTDIR)\Otp_put.sbr" \
	"$(INTDIR)\Prefs.sbr" \
	"$(INTDIR)\Sha.sbr" \
	"$(INTDIR)\Tray.sbr"

"$(OUTDIR)\dotkey95.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/dotkey95.pdb" /machine:I386 /out:"$(OUTDIR)/dotkey95.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Dotkey95.obj" \
	"$(INTDIR)\Dotkey95.res" \
	"$(INTDIR)\Md4.obj" \
	"$(INTDIR)\Md5c.obj" \
	"$(INTDIR)\Otp_hash.obj" \
	"$(INTDIR)\Otp_put.obj" \
	"$(INTDIR)\Prefs.obj" \
	"$(INTDIR)\Sha.obj" \
	"$(INTDIR)\Tray.obj"

"$(OUTDIR)\dotkey95.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

################################################################################
# Begin Target

# Name "dotkey95 - Win32 Release"
# Name "dotkey95 - Win32 Debug"
# Name "dotkey95 - Win32 Debug nocache"
# Name "dotkey95 - Win32 Release nocache"

!IF  "$(CFG)" == "dotkey95 - Win32 Release"

!ELSEIF  "$(CFG)" == "dotkey95 - Win32 Debug"

!ELSEIF  "$(CFG)" == "dotkey95 - Win32 Debug nocache"

!ELSEIF  "$(CFG)" == "dotkey95 - Win32 Release nocache"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\Dotkey95.c
DEP_CPP_DOTKE=\
	".\Dotkey95.h"\
	

!IF  "$(CFG)" == "dotkey95 - Win32 Release"


"$(INTDIR)\Dotkey95.obj" : $(SOURCE) $(DEP_CPP_DOTKE) "$(INTDIR)"

"$(INTDIR)\Dotkey95.sbr" : $(SOURCE) $(DEP_CPP_DOTKE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dotkey95 - Win32 Debug"


"$(INTDIR)\Dotkey95.obj" : $(SOURCE) $(DEP_CPP_DOTKE) "$(INTDIR)"

"$(INTDIR)\Dotkey95.sbr" : $(SOURCE) $(DEP_CPP_DOTKE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dotkey95 - Win32 Debug nocache"


"$(INTDIR)\Dotkey95.obj" : $(SOURCE) $(DEP_CPP_DOTKE) "$(INTDIR)"

"$(INTDIR)\Dotkey95.sbr" : $(SOURCE) $(DEP_CPP_DOTKE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dotkey95 - Win32 Release nocache"


"$(INTDIR)\Dotkey95.obj" : $(SOURCE) $(DEP_CPP_DOTKE) "$(INTDIR)"

"$(INTDIR)\Dotkey95.sbr" : $(SOURCE) $(DEP_CPP_DOTKE) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dotkey95.rc
DEP_RSC_DOTKEY=\
	".\disable.ico"\
	".\dotkey95.ico"\
	

!IF  "$(CFG)" == "dotkey95 - Win32 Release"


"$(INTDIR)\Dotkey95.res" : $(SOURCE) $(DEP_RSC_DOTKEY) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "dotkey95 - Win32 Debug"


"$(INTDIR)\Dotkey95.res" : $(SOURCE) $(DEP_RSC_DOTKEY) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "dotkey95 - Win32 Debug nocache"


"$(INTDIR)\Dotkey95.res" : $(SOURCE) $(DEP_RSC_DOTKEY) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "dotkey95 - Win32 Release nocache"


"$(INTDIR)\Dotkey95.res" : $(SOURCE) $(DEP_RSC_DOTKEY) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Md4.c
DEP_CPP_MD4_C=\
	".\md4.h"\
	".\sizes.h"\
	

!IF  "$(CFG)" == "dotkey95 - Win32 Release"


"$(INTDIR)\Md4.obj" : $(SOURCE) $(DEP_CPP_MD4_C) "$(INTDIR)"

"$(INTDIR)\Md4.sbr" : $(SOURCE) $(DEP_CPP_MD4_C) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dotkey95 - Win32 Debug"


"$(INTDIR)\Md4.obj" : $(SOURCE) $(DEP_CPP_MD4_C) "$(INTDIR)"

"$(INTDIR)\Md4.sbr" : $(SOURCE) $(DEP_CPP_MD4_C) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dotkey95 - Win32 Debug nocache"


"$(INTDIR)\Md4.obj" : $(SOURCE) $(DEP_CPP_MD4_C) "$(INTDIR)"

"$(INTDIR)\Md4.sbr" : $(SOURCE) $(DEP_CPP_MD4_C) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dotkey95 - Win32 Release nocache"


"$(INTDIR)\Md4.obj" : $(SOURCE) $(DEP_CPP_MD4_C) "$(INTDIR)"

"$(INTDIR)\Md4.sbr" : $(SOURCE) $(DEP_CPP_MD4_C) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Md5c.c
DEP_CPP_MD5C_=\
	".\md5.h"\
	".\sizes.h"\
	

!IF  "$(CFG)" == "dotkey95 - Win32 Release"


"$(INTDIR)\Md5c.obj" : $(SOURCE) $(DEP_CPP_MD5C_) "$(INTDIR)"

"$(INTDIR)\Md5c.sbr" : $(SOURCE) $(DEP_CPP_MD5C_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dotkey95 - Win32 Debug"


"$(INTDIR)\Md5c.obj" : $(SOURCE) $(DEP_CPP_MD5C_) "$(INTDIR)"

"$(INTDIR)\Md5c.sbr" : $(SOURCE) $(DEP_CPP_MD5C_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dotkey95 - Win32 Debug nocache"


"$(INTDIR)\Md5c.obj" : $(SOURCE) $(DEP_CPP_MD5C_) "$(INTDIR)"

"$(INTDIR)\Md5c.sbr" : $(SOURCE) $(DEP_CPP_MD5C_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dotkey95 - Win32 Release nocache"


"$(INTDIR)\Md5c.obj" : $(SOURCE) $(DEP_CPP_MD5C_) "$(INTDIR)"

"$(INTDIR)\Md5c.sbr" : $(SOURCE) $(DEP_CPP_MD5C_) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Otp_hash.c
DEP_CPP_OTP_H=\
	".\md4.h"\
	".\md5.h"\
	".\otp.h"\
	".\sha.h"\
	".\sizes.h"\
	

!IF  "$(CFG)" == "dotkey95 - Win32 Release"


"$(INTDIR)\Otp_hash.obj" : $(SOURCE) $(DEP_CPP_OTP_H) "$(INTDIR)"

"$(INTDIR)\Otp_hash.sbr" : $(SOURCE) $(DEP_CPP_OTP_H) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dotkey95 - Win32 Debug"


"$(INTDIR)\Otp_hash.obj" : $(SOURCE) $(DEP_CPP_OTP_H) "$(INTDIR)"

"$(INTDIR)\Otp_hash.sbr" : $(SOURCE) $(DEP_CPP_OTP_H) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dotkey95 - Win32 Debug nocache"


"$(INTDIR)\Otp_hash.obj" : $(SOURCE) $(DEP_CPP_OTP_H) "$(INTDIR)"

"$(INTDIR)\Otp_hash.sbr" : $(SOURCE) $(DEP_CPP_OTP_H) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dotkey95 - Win32 Release nocache"


"$(INTDIR)\Otp_hash.obj" : $(SOURCE) $(DEP_CPP_OTP_H) "$(INTDIR)"

"$(INTDIR)\Otp_hash.sbr" : $(SOURCE) $(DEP_CPP_OTP_H) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Otp_put.c
DEP_CPP_OTP_P=\
	".\otp.h"\
	".\sizes.h"\
	

!IF  "$(CFG)" == "dotkey95 - Win32 Release"


"$(INTDIR)\Otp_put.obj" : $(SOURCE) $(DEP_CPP_OTP_P) "$(INTDIR)"

"$(INTDIR)\Otp_put.sbr" : $(SOURCE) $(DEP_CPP_OTP_P) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dotkey95 - Win32 Debug"


"$(INTDIR)\Otp_put.obj" : $(SOURCE) $(DEP_CPP_OTP_P) "$(INTDIR)"

"$(INTDIR)\Otp_put.sbr" : $(SOURCE) $(DEP_CPP_OTP_P) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dotkey95 - Win32 Debug nocache"


"$(INTDIR)\Otp_put.obj" : $(SOURCE) $(DEP_CPP_OTP_P) "$(INTDIR)"

"$(INTDIR)\Otp_put.sbr" : $(SOURCE) $(DEP_CPP_OTP_P) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dotkey95 - Win32 Release nocache"


"$(INTDIR)\Otp_put.obj" : $(SOURCE) $(DEP_CPP_OTP_P) "$(INTDIR)"

"$(INTDIR)\Otp_put.sbr" : $(SOURCE) $(DEP_CPP_OTP_P) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Prefs.c
DEP_CPP_PREFS=\
	".\Dotkey95.h"\
	

!IF  "$(CFG)" == "dotkey95 - Win32 Release"


"$(INTDIR)\Prefs.obj" : $(SOURCE) $(DEP_CPP_PREFS) "$(INTDIR)"

"$(INTDIR)\Prefs.sbr" : $(SOURCE) $(DEP_CPP_PREFS) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dotkey95 - Win32 Debug"


"$(INTDIR)\Prefs.obj" : $(SOURCE) $(DEP_CPP_PREFS) "$(INTDIR)"

"$(INTDIR)\Prefs.sbr" : $(SOURCE) $(DEP_CPP_PREFS) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dotkey95 - Win32 Debug nocache"


"$(INTDIR)\Prefs.obj" : $(SOURCE) $(DEP_CPP_PREFS) "$(INTDIR)"

"$(INTDIR)\Prefs.sbr" : $(SOURCE) $(DEP_CPP_PREFS) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dotkey95 - Win32 Release nocache"


"$(INTDIR)\Prefs.obj" : $(SOURCE) $(DEP_CPP_PREFS) "$(INTDIR)"

"$(INTDIR)\Prefs.sbr" : $(SOURCE) $(DEP_CPP_PREFS) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Sha.c
DEP_CPP_SHA_C=\
	".\sizes.h"\
	

!IF  "$(CFG)" == "dotkey95 - Win32 Release"


"$(INTDIR)\Sha.obj" : $(SOURCE) $(DEP_CPP_SHA_C) "$(INTDIR)"

"$(INTDIR)\Sha.sbr" : $(SOURCE) $(DEP_CPP_SHA_C) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dotkey95 - Win32 Debug"


"$(INTDIR)\Sha.obj" : $(SOURCE) $(DEP_CPP_SHA_C) "$(INTDIR)"

"$(INTDIR)\Sha.sbr" : $(SOURCE) $(DEP_CPP_SHA_C) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dotkey95 - Win32 Debug nocache"


"$(INTDIR)\Sha.obj" : $(SOURCE) $(DEP_CPP_SHA_C) "$(INTDIR)"

"$(INTDIR)\Sha.sbr" : $(SOURCE) $(DEP_CPP_SHA_C) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dotkey95 - Win32 Release nocache"


"$(INTDIR)\Sha.obj" : $(SOURCE) $(DEP_CPP_SHA_C) "$(INTDIR)"

"$(INTDIR)\Sha.sbr" : $(SOURCE) $(DEP_CPP_SHA_C) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Tray.c
DEP_CPP_TRAY_=\
	".\Dotkey95.h"\
	

!IF  "$(CFG)" == "dotkey95 - Win32 Release"


"$(INTDIR)\Tray.obj" : $(SOURCE) $(DEP_CPP_TRAY_) "$(INTDIR)"

"$(INTDIR)\Tray.sbr" : $(SOURCE) $(DEP_CPP_TRAY_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dotkey95 - Win32 Debug"


"$(INTDIR)\Tray.obj" : $(SOURCE) $(DEP_CPP_TRAY_) "$(INTDIR)"

"$(INTDIR)\Tray.sbr" : $(SOURCE) $(DEP_CPP_TRAY_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dotkey95 - Win32 Debug nocache"


"$(INTDIR)\Tray.obj" : $(SOURCE) $(DEP_CPP_TRAY_) "$(INTDIR)"

"$(INTDIR)\Tray.sbr" : $(SOURCE) $(DEP_CPP_TRAY_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dotkey95 - Win32 Release nocache"


"$(INTDIR)\Tray.obj" : $(SOURCE) $(DEP_CPP_TRAY_) "$(INTDIR)"

"$(INTDIR)\Tray.sbr" : $(SOURCE) $(DEP_CPP_TRAY_) "$(INTDIR)"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
