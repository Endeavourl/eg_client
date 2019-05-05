# Microsoft Developer Studio Project File - Name="EG_client" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=EG_client - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "EG_client.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "EG_client.mak" CFG="EG_client - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "EG_client - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe
# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "EG_CLIENT_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /Zi /O2 /Oy- /Ob2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "UNICODE" /D "_USRDLL" /D "EG_CLIENT_EXPORTS" /Fr /FD /c
# SUBTRACT CPP /WX /YX
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x419 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib detours.lib FLCoreCommon.lib FLCoreDALib.lib FLCoreFreelancerEXE.lib /nologo /dll /debug /debugtype:coff /machine:I386
# SUBTRACT LINK32 /pdb:none
# Begin Target

# Name "EG_client - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Tools"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Error.cpp
# End Source File
# Begin Source File

SOURCE=.\Memory.cpp
# End Source File
# Begin Source File

SOURCE=.\Tools.cpp
# End Source File
# End Group
# Begin Group "Settings"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\IniFile.cpp
# End Source File
# Begin Source File

SOURCE=.\Preferences.cpp
# End Source File
# End Group
# Begin Group "Hacks"

# PROP Default_Filter ""
# Begin Group "Hooks"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CDetoured_DPClient.cpp
# End Source File
# Begin Source File

SOURCE=.\CDetoured_INI_Reader.cpp
# End Source File
# Begin Source File

SOURCE=.\ReceiveChat_Detoured.cpp
# End Source File
# Begin Source File

SOURCE=.\SinglePlayer_Detoured.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\Hacks.cpp
# End Source File
# Begin Source File

SOURCE=.\Hooks.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\EG_client.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "FL Headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\FLCommon.h
# End Source File
# Begin Source File

SOURCE=.\FLDALib.h
# End Source File
# Begin Source File

SOURCE=.\FreelancerEXE.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\CDetoured_DPClient.h
# End Source File
# Begin Source File

SOURCE=.\CDetoured_INI_Reader.h
# End Source File
# Begin Source File

SOURCE=.\EG_client.h
# End Source File
# Begin Source File

SOURCE=.\IniFile.h
# End Source File
# Begin Source File

SOURCE=.\Preferences.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\rsrc.rc
# End Source File
# End Group
# End Target
# End Project
