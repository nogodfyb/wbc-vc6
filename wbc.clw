; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CWbcDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "wbc.h"

ClassCount=5
Class1=CWbcApp
Class2=CWbcDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=MAIN_DIALOG
Resource2=IDR_MAINFRAME
Class4=CMyListCtrl
Resource3=IDD_ABOUTBOX
Class5=CheckToolsDlg
Resource4=CHECK_TOOLS_DIALOG

[CLS:CWbcApp]
Type=0
HeaderFile=wbc.h
ImplementationFile=wbc.cpp
Filter=N
LastObject=IDC_EDIT1

[CLS:CWbcDlg]
Type=0
HeaderFile=wbcDlg.h
ImplementationFile=wbcDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_EDIT1

[CLS:CAboutDlg]
Type=0
HeaderFile=wbcDlg.h
ImplementationFile=wbcDlg.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[CLS:CMyListCtrl]
Type=0
HeaderFile=CMyListCtrl.h
ImplementationFile=CMyListCtrl.cpp
BaseClass=CListCtrl
Filter=W
LastObject=IDC_EDIT1

[DLG:MAIN_DIALOG]
Type=1
Class=CWbcDlg
ControlCount=3
Control1=IDC_STATIC,button,1342177287
Control2=IDC_STATIC,static,1342308352
Control3=IDC_EDIT1,edit,1350631584

[DLG:CHECK_TOOLS_DIALOG]
Type=1
Class=CheckToolsDlg
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816

[CLS:CheckToolsDlg]
Type=0
HeaderFile=CheckToolsDlg.h
ImplementationFile=CheckToolsDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDOK

