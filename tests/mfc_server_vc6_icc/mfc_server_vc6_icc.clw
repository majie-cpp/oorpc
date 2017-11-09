; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMfc_server_vc6_iccDlg
LastTemplate=CSocket
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "mfc_server_vc6_icc.h"

ClassCount=5
Class1=CMfc_server_vc6_iccApp
Class2=CMfc_server_vc6_iccDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class5=ServeSocket
Class4=ListenSocket
Resource3=IDD_MFC_SERVER_VC6_ICC_DIALOG

[CLS:CMfc_server_vc6_iccApp]
Type=0
HeaderFile=mfc_server_vc6_icc.h
ImplementationFile=mfc_server_vc6_icc.cpp
Filter=N

[CLS:CMfc_server_vc6_iccDlg]
Type=0
HeaderFile=mfc_server_vc6_iccDlg.h
ImplementationFile=mfc_server_vc6_iccDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CMfc_server_vc6_iccDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=mfc_server_vc6_iccDlg.h
ImplementationFile=mfc_server_vc6_iccDlg.cpp
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

[DLG:IDD_MFC_SERVER_VC6_ICC_DIALOG]
Type=1
Class=CMfc_server_vc6_iccDlg
ControlCount=2
Control1=IDCANCEL,button,1342242816
Control2=IDC_LIST1,listbox,1353777409

[CLS:ListenSocket]
Type=0
HeaderFile=ListenSocket.h
ImplementationFile=ListenSocket.cpp
BaseClass=CSocket
Filter=N

[CLS:ServeSocket]
Type=0
HeaderFile=ServeSocket.h
ImplementationFile=ServeSocket.cpp
BaseClass=CSocket
Filter=N

