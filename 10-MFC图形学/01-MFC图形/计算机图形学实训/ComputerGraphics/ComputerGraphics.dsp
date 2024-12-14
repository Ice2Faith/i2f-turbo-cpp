# Microsoft Developer Studio Project File - Name="ComputerGraphics" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=ComputerGraphics - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ComputerGraphics.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ComputerGraphics.mak" CFG="ComputerGraphics - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ComputerGraphics - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "ComputerGraphics - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ComputerGraphics - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "ComputerGraphics - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "ComputerGraphics - Win32 Release"
# Name "ComputerGraphics - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=".\ComputerGraphics.cpp"
# End Source File
# Begin Source File

SOURCE=".\ComputerGraphics.rc"
# End Source File
# Begin Source File

SOURCE=".\ComputerGraphicsDoc.cpp"
# End Source File
# Begin Source File

SOURCE=".\ComputerGraphicsView.cpp"
# End Source File
# Begin Source File

SOURCE=.\DlgBaseOperationHelp.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCartonSetting.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgColorSetting.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgGeoModCreateSetting.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgGraphVarySetting.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgInputBox.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgLightSetting.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgMaterialSetting.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgOperationTips.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSizeSetting.cpp
# End Source File
# Begin Source File

SOURCE=.\GData.cpp
# End Source File
# Begin Source File

SOURCE=.\GGrating.cpp
# End Source File
# Begin Source File

SOURCE=.\GHideZBuffer.cpp
# End Source File
# Begin Source File

SOURCE=.\GLighting.cpp
# End Source File
# Begin Source File

SOURCE=.\GProjection.cpp
# End Source File
# Begin Source File

SOURCE=.\GStereo.cpp
# End Source File
# Begin Source File

SOURCE=.\GTMFile.cpp
# End Source File
# Begin Source File

SOURCE=.\GTranglelized.cpp
# End Source File
# Begin Source File

SOURCE=.\GVary.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=".\ComputerGraphics.h"
# End Source File
# Begin Source File

SOURCE=".\ComputerGraphicsDoc.h"
# End Source File
# Begin Source File

SOURCE=".\ComputerGraphicsView.h"
# End Source File
# Begin Source File

SOURCE=.\DlgBaseOperationHelp.h
# End Source File
# Begin Source File

SOURCE=.\DlgCartonSetting.h
# End Source File
# Begin Source File

SOURCE=.\DlgColorSetting.h
# End Source File
# Begin Source File

SOURCE=.\DlgGeoModCreateSetting.h
# End Source File
# Begin Source File

SOURCE=.\DlgGraphVarySetting.h
# End Source File
# Begin Source File

SOURCE=.\DlgInputBox.h
# End Source File
# Begin Source File

SOURCE=.\DlgLightSetting.h
# End Source File
# Begin Source File

SOURCE=.\DlgMaterialSetting.h
# End Source File
# Begin Source File

SOURCE=.\DlgOperationTips.h
# End Source File
# Begin Source File

SOURCE=.\DlgSizeSetting.h
# End Source File
# Begin Source File

SOURCE=.\GData.h
# End Source File
# Begin Source File

SOURCE=.\GGrating.h
# End Source File
# Begin Source File

SOURCE=.\GHideZBuffer.h
# End Source File
# Begin Source File

SOURCE=.\GLighting.h
# End Source File
# Begin Source File

SOURCE=.\GProjection.h
# End Source File
# Begin Source File

SOURCE=.\GStereo.h
# End Source File
# Begin Source File

SOURCE=.\GTMFile.h
# End Source File
# Begin Source File

SOURCE=.\GTranglelized.h
# End Source File
# Begin Source File

SOURCE=.\GVary.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=".\res\ComputerGraphics.ico"
# End Source File
# Begin Source File

SOURCE=".\res\ComputerGraphics.rc2"
# End Source File
# Begin Source File

SOURCE=".\res\ComputerGraphicsDoc.ico"
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
