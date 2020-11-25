; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=AdminMainDialog
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "wbc.h"

ClassCount=15
Class1=CWbcApp
Class2=CWbcDlg
Class3=CAboutDlg

ResourceCount=18
Resource1=CHECK_TOOLS_DIALOG
Resource2=IDR_MAINFRAME
Class4=CMyListCtrl
Resource3=IDR_MENU2
Class5=CheckToolsDlg
Resource4=MANUAL_WEIGH_DIALOG
Class6=SettingDialog
Resource5=IDR_MENU3
Class7=ManualWeighDialog
Resource6=IDD_ABOUTBOX
Resource7=MAIN_DIALOG
Resource8=TOOLS_LIST_DIALOG
Resource9=ADD_TOOL_DIALOG
Class8=ExceptionRegisterDialog
Resource10=TOOLS_RELATION
Class9=AdminMainDialog
Resource11=SETTING_DIALOG
Class10=ToolsListDialog
Resource12=CHECK_RECORD_LIST
Class11=ToolsRelation
Resource13=IDR_MENU1
Class12=AddToolDialog
Resource14=EXCEPTION_REGISTER
Resource15=ADD_RELATION_DIALOG
Class13=AddRelationDialog
Resource16=WEIGH_RECORD_LIST
Class14=CheckRecordListDialog
Resource17=ADMIN_MAIN_DIALOG
Class15=WeighRecordListDialog
Resource18=IDR_MENU4

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
LastObject=ID_MENUITEM32773

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
ControlCount=26
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
Control19=IDC_LIST2,SysListView32,1350631429
Control20=IDC_STATIC,static,1342308352
Control21=IDC_EDIT3,edit,1350631584
Control22=IDC_STATIC,button,1342177287
Control23=IDC_LIST3,SysListView32,1350631425
Control24=EP_PROMPT_TEXT,static,1342308352
Control25=IDC_BUTTON3,button,1342242816
Control26=IDC_BUTTON4,button,1342242816

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

[MNU:IDR_MENU3]
Type=1
Class=?
Command1=ID_MENUITEM32773
CommandCount=1

[DLG:EXCEPTION_REGISTER]
Type=1
Class=ExceptionRegisterDialog
ControlCount=16
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=WAFER_LOT_TEXT,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_COMBO1,combobox,1344339970
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT1,edit,1350631552
Control9=IDC_STATIC,static,1342308352
Control10=IDC_COMBO2,combobox,1344340226
Control11=IDC_STATIC,static,1342308352
Control12=IDC_EDIT2,edit,1350631552
Control13=IDC_STATIC,static,1342308352
Control14=IDC_EDIT3,edit,1350631584
Control15=IDC_STATIC,static,1342308352
Control16=IDC_EDIT4,edit,1350631552

[CLS:ExceptionRegisterDialog]
Type=0
HeaderFile=ExceptionRegisterDialog.h
ImplementationFile=ExceptionRegisterDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=ExceptionRegisterDialog
VirtualFilter=dWC

[DLG:ADMIN_MAIN_DIALOG]
Type=1
Class=AdminMainDialog
ControlCount=6
Control1=IDC_TAB1,SysTabControl32,1342177280
Control2=IDC_STATIC,static,1342308352
Control3=IDC_EDIT1,edit,1350631552
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EDIT2,edit,1350631584
Control6=IDC_BUTTON1,button,1342242816

[CLS:AdminMainDialog]
Type=0
HeaderFile=AdminMainDialog.h
ImplementationFile=AdminMainDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=AdminMainDialog
VirtualFilter=dWC

[DLG:TOOLS_LIST_DIALOG]
Type=1
Class=ToolsListDialog
ControlCount=2
Control1=IDC_LIST1,SysListView32,1350631425
Control2=IDC_BUTTON1,button,1342242816

[CLS:ToolsListDialog]
Type=0
HeaderFile=ToolsListDialog.h
ImplementationFile=ToolsListDialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=ID_MENUITEM32775

[DLG:TOOLS_RELATION]
Type=1
Class=ToolsRelation
ControlCount=2
Control1=IDC_LIST1,SysListView32,1350631425
Control2=IDC_BUTTON1,button,1342242816

[CLS:ToolsRelation]
Type=0
HeaderFile=ToolsRelation.h
ImplementationFile=ToolsRelation.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=ID_MENUITEM32771

[DLG:ADD_TOOL_DIALOG]
Type=1
Class=AddToolDialog
ControlCount=10
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT1,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_COMBO1,combobox,1344340227
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT2,edit,1350631552
Control9=IDC_STATIC,static,1342308352
Control10=IDC_EDIT3,edit,1350631552

[CLS:AddToolDialog]
Type=0
HeaderFile=AddToolDialog.h
ImplementationFile=AddToolDialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=AddToolDialog

[MNU:IDR_MENU4]
Type=1
Class=?
Command1=ID_MENUITEM32774
Command2=ID_MENUITEM32775
CommandCount=2

[DLG:ADD_RELATION_DIALOG]
Type=1
Class=AddRelationDialog
ControlCount=14
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_EDIT1,edit,1350631552
Control10=IDC_EDIT2,edit,1350631552
Control11=IDC_COMBO1,combobox,1344340227
Control12=IDC_COMBO2,combobox,1344340227
Control13=IDC_COMBO3,combobox,1344340227
Control14=IDC_COMBO4,combobox,1344340227

[CLS:AddRelationDialog]
Type=0
HeaderFile=AddRelationDialog.h
ImplementationFile=AddRelationDialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=AddRelationDialog

[DLG:CHECK_RECORD_LIST]
Type=1
Class=CheckRecordListDialog
ControlCount=6
Control1=IDC_LIST1,SysListView32,1350631425
Control2=IDC_STATIC,static,1342308352
Control3=IDC_DATETIMEPICKER1,SysDateTimePick32,1342242848
Control4=IDC_STATIC,static,1342308352
Control5=IDC_DATETIMEPICKER2,SysDateTimePick32,1342242848
Control6=IDC_BUTTON1,button,1342242816

[CLS:CheckRecordListDialog]
Type=0
HeaderFile=CheckRecordListDialog.h
ImplementationFile=CheckRecordListDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=CheckRecordListDialog
VirtualFilter=dWC

[DLG:WEIGH_RECORD_LIST]
Type=1
Class=WeighRecordListDialog
ControlCount=6
Control1=IDC_LIST1,SysListView32,1350631425
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_DATETIMEPICKER1,SysDateTimePick32,1342242848
Control5=IDC_DATETIMEPICKER2,SysDateTimePick32,1342242848
Control6=IDC_BUTTON1,button,1342242816

[CLS:WeighRecordListDialog]
Type=0
HeaderFile=WeighRecordListDialog.h
ImplementationFile=WeighRecordListDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=ID_MENUITEM32771
VirtualFilter=dWC

