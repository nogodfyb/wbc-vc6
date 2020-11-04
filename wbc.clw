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
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class4=CMyListCtrl
Resource3=MAIN_DIALOG
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
LastObject=ID_TEXT

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
ControlCount=7
Control1=IDC_STATIC,button,1342177287
Control2=IDC_STATIC,static,1342308352
Control3=IDC_EDIT1,edit,1350631584
Control4=IDC_STATIC,static,1342308352
Control5=LAST_CHECK_TEXT,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=ID_TEXT,static,1342308352

[DLG:CHECK_TOOLS_DIALOG]
Type=1
Class=CheckToolsDlg
ControlCount=30
Control1=IDC_STATIC,static,1342308352
Control2=CHECK_TOOLS_DLG_WS,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT1,edit,1350631584
Control5=IDC_STATIC,button,1342177287
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=SCRAPER_TEXT,static,1342308352
Control11=STEELMESH_TEXT,static,1342308352
Control12=SHIM_TEXT,static,1342308352
Control13=IDC_EDIT2,edit,1350631584
Control14=IDC_EDIT3,edit,1350631584
Control15=IDC_STATIC,static,1342308352
Control16=IDC_COMBO1,combobox,1344340226
Control17=IDC_COMBO2,combobox,1344340226
Control18=IDC_COMBO3,combobox,1344340226
Control19=IDC_STATIC,button,1342177287
Control20=IDC_STATIC,static,1342308352
Control21=IDC_STATIC,static,1342308352
Control22=IDC_STATIC,static,1342308352
Control23=IDC_STATIC,static,1342308352
Control24=IDC_STATIC,static,1342308352
Control25=IDC_EDIT4,edit,1350631560
Control26=IDC_COMBO4,combobox,1344340226
Control27=IDC_BUTTON1,button,1342242816
Control28=IDC_EDIT5,edit,1350631552
Control29=IDC_EDIT6,edit,1350631552
Control30=IDC_EDIT7,edit,1350631552

[CLS:CheckToolsDlg]
Type=0
HeaderFile=CheckToolsDlg.h
ImplementationFile=CheckToolsDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CHECK_TOOLS_DLG_WS
VirtualFilter=dWC

