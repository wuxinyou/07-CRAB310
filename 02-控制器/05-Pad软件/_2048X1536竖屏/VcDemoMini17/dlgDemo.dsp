# Microsoft Developer Studio Project File - Name="dlgDemo" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=dlgDemo - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "dlgDemo.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "dlgDemo.mak" CFG="dlgDemo - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "dlgDemo - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "dlgDemo - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "dlgDemo - Win32 Release"

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
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /fo"dlgDemo.res" /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"..\output\dlgDemo.bsc"
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /pdb:"..\output\dlgDemo.pdb" /machine:I386 /out:"../AppExe/VCDemo.exe"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "dlgDemo - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /fo"dlgDemo.res" /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 winmm.lib /nologo /subsystem:windows /pdb:"..\output\dlgDemo.pdb" /debug /machine:I386 /out:"../AppExe/CRAB.exe" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "dlgDemo - Win32 Release"
# Name "dlgDemo - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\BCMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\BtnST.cpp
# End Source File
# Begin Source File

SOURCE=.\ChannelWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\CodecSettingFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\cyQueue.cpp
# End Source File
# Begin Source File

SOURCE=.\DeviceControl.cpp
# End Source File
# Begin Source File

SOURCE=.\dlgDemo.cpp
# End Source File
# Begin Source File

SOURCE=.\dlgDemo.rc
# End Source File
# Begin Source File

SOURCE=.\dlgDemoDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MyProgress.cpp
# End Source File
# Begin Source File

SOURCE=.\PictureEx.cpp
# End Source File
# Begin Source File

SOURCE=.\SerialPort.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\BCMenu.h
# End Source File
# Begin Source File

SOURCE=.\BtnST.h
# End Source File
# Begin Source File

SOURCE=.\ChannelWnd.h
# End Source File
# Begin Source File

SOURCE=.\CodecSettingFrm.h
# End Source File
# Begin Source File

SOURCE=.\cyQueue.h
# End Source File
# Begin Source File

SOURCE=.\datastru.h
# End Source File
# Begin Source File

SOURCE=.\DeviceControl.h
# End Source File
# Begin Source File

SOURCE=.\dlgDemo.h
# End Source File
# Begin Source File

SOURCE=.\dlgDemoDlg.h
# End Source File
# Begin Source File

SOURCE=.\DXMediaCap.h
# End Source File
# Begin Source File

SOURCE=.\MyProgress.h
# End Source File
# Begin Source File

SOURCE=.\PictureEx.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SerialPort.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\backGround.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\charge2_718.gif
# End Source File
# Begin Source File

SOURCE=.\res\CRAB.bmp
# End Source File
# Begin Source File

SOURCE=.\res\dlgDemo.ico
# End Source File
# Begin Source File

SOURCE=.\res\dlgDemo.rc2
# End Source File
# Begin Source File

SOURCE=.\res\haiguan.ico
# End Source File
# Begin Source File

SOURCE=.\res\openBtn1.ico
# End Source File
# Begin Source File

SOURCE=.\res\recordBtn1.ico
# End Source File
# Begin Source File

SOURCE=.\res\recordBtn2.ico
# End Source File
# Begin Source File

SOURCE=.\res\settingBtn1.ico
# End Source File
# Begin Source File

SOURCE=.\res\snap.ico
# End Source File
# Begin Source File

SOURCE=.\res\snapBtn1.ico
# End Source File
# Begin Source File

SOURCE=.\res\snapBtn2.ico
# End Source File
# Begin Source File

SOURCE=".\res\电量指示立体02_100.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\电量指示立体02_20.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\电量指示立体02_40.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\电量指示立体02_60.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\电量指示立体02_80.bmp"
# End Source File
# End Group
# Begin Source File

SOURCE=.\res\CRAB.png
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
