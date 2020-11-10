; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CWbcDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "wbc.h"

ClassCount=7
Class1=CWbcApp
Class2=CWbcDlg
Class3=CAboutDlg

ResourceCount=8
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class4=CMyListCtrl
Resource3=CHECK_TOOLS_DIALOG
Class5=CheckToolsDlg
Resource4=SETTING_DIALOG
Class6=SettingDialog
Resource5=MANUAL_WEIGH_DIALOG
Class7=ManualWeighDialog
Resource6=MAIN_DIALOG
Resource7=IDR_MENU1
Resource8=IDR_MENU2

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
LastObject=CWbcDlg

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
ControlCount=24
Control1=IDC_STATIC,button,1342177287
Control2=IDC_STATIC,static,1342308352
Control3=IDC_EDIT1,edit,1350631584
Control4=IDC_STATIC,static,1342308352
Control5=LAST_CHECK_TEXT,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=ID_TEXT,static,1342308352
Control8=IDC_STATIC,button,1342177287
Control9=IDC_STATIC,static,1342308352
Control10=IDC_EDIT2,edit,1350631584
Control11=IDC_LIST1,SysListView32,1350631425
Control12=IDC_STATIC,button,1342177287
Control13=IDC_STATIC,static,1342308352
Control14=IDC_DATETIMEPICKER1,SysDateTimePick32,1342242848
Control15=IDC_STATIC,static,1342308352
Control16=IDC_COMBO1,combobox,1344339970
Control17=IDC_BUTTON1,button,1342242816
Control18=IDC_BUTTON2,button,1073807360
Control19=IDC_LIST2,SysListView32,1350631425
Control20=IDC_STATIC,static,1342308352
Control21=IDC_EDIT3,edit,1350631584
Control22=IDC_STATIC,button,1342177287
Control23=IDC_LIST3,SysListView32,1350631425
Control24=EP_PROMPT_TEXT,static,1342308352

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

[DLG:SETTING_DIALOG]
Type=1
Class=SettingDialog
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT1,edit,1350631552

[CLS:SettingDialog]
Type=0
HeaderFile=SettingDialog.h
ImplementationFile=SettingDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_EDIT1
VirtualFilter=dWC

[DLG:MANUAL_WEIGH_DIALOG]
Type=1
Class=ManualWeighDialog
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=WAFER_LOT_TEXT,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT1,edit,1350631552

[CLS:ManualWeighDialog]
Type=0
HeaderFile=ManualWeighDialog.h
ImplementationFile=ManualWeighDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=ID_MENUITEM32771
VirtualFilter=dWC

[MNU:IDR_MENU1]
Type=1
Class=?
Command1=ID_MENUITEM32771
CommandCount=1

[MNU:IDR_MENU2]
Type=1
Class=?
Command1=ID_MENUITEM32772
CommandCount=1

