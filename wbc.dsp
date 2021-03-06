# Microsoft Developer Studio Project File - Name="wbc" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=wbc - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "wbc.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "wbc.mak" CFG="wbc - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "wbc - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "wbc - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "wbc - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "wbc - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "wbc - Win32 Release"
# Name "wbc - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AddRelationDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\AddToolDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\AdminMainDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\CheckRecordListDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\CheckToolsDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CMyListCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\Epo.cpp
# End Source File
# Begin Source File

SOURCE=.\ExceptionRegisterDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\ManualWeighDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\MyRepository.cpp
# End Source File
# Begin Source File

SOURCE=.\MySqlUtil.cpp
# End Source File
# Begin Source File

SOURCE=.\MyUtils.cpp
# End Source File
# Begin Source File

SOURCE=.\SettingDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\ShiftUtils.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\ToolsListDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\ToolsRelation.cpp
# End Source File
# Begin Source File

SOURCE=.\ValiadteUtils.cpp
# End Source File
# Begin Source File

SOURCE=.\wbc.cpp
# End Source File
# Begin Source File

SOURCE=.\wbc.rc
# End Source File
# Begin Source File

SOURCE=.\wbcDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\WeighRecordListDialog.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AddRelationDialog.h
# End Source File
# Begin Source File

SOURCE=.\AddToolDialog.h
# End Source File
# Begin Source File

SOURCE=.\AdminMainDialog.h
# End Source File
# Begin Source File

SOURCE=.\CheckRecordListDialog.h
# End Source File
# Begin Source File

SOURCE=.\CheckToolsDlg.h
# End Source File
# Begin Source File

SOURCE=.\CMyListCtrl.h
# End Source File
# Begin Source File

SOURCE=.\Epo.h
# End Source File
# Begin Source File

SOURCE=.\ExceptionRegisterDialog.h
# End Source File
# Begin Source File

SOURCE=.\ManualWeighDialog.h
# End Source File
# Begin Source File

SOURCE=.\MyRepository.h
# End Source File
# Begin Source File

SOURCE=.\MySqlUtil.h
# End Source File
# Begin Source File

SOURCE=.\MyUtils.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SettingDialog.h
# End Source File
# Begin Source File

SOURCE=.\ShiftUtils.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\ToolsListDialog.h
# End Source File
# Begin Source File

SOURCE=.\ToolsRelation.h
# End Source File
# Begin Source File

SOURCE=.\ValiadteUtils.h
# End Source File
# Begin Source File

SOURCE=.\wbc.h
# End Source File
# Begin Source File

SOURCE=.\wbcDlg.h
# End Source File
# Begin Source File

SOURCE=.\WeighRecordListDialog.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\wbc.ico
# End Source File
# Begin Source File

SOURCE=.\res\wbc.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
