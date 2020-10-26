; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMyListCtrl
LastTemplate=CListCtrl
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "wbc.h"

ClassCount=5
Class1=CWbcApp
Class2=CWbcDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class5=CMyListCtrl
Resource3=IDD_WBC_DIALOG

[CLS:CWbcApp]
Type=0
HeaderFile=wbc.h
ImplementationFile=wbc.cpp
Filter=N

[CLS:CWbcDlg]
Type=0
HeaderFile=wbcDlg.h
ImplementationFile=wbcDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=wbcDlg.h
ImplementationFile=wbcDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_WBC_DIALOG]
Type=1
Class=CWbcDlg
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816

[CLS:CMyListCtrl]
Type=0
HeaderFile=CMyListCtrl.h
ImplementationFile=CMyListCtrl.cpp
BaseClass=CListCtrl
Filter=W

