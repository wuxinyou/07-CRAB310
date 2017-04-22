; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDlgDemoDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "dlgDemo.h"

ClassCount=13
Class1=CDlgDemoApp
Class2=CDlgDemoDlg
Class3=CAboutDlg

ResourceCount=5
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_DLGDEMO_DIALOG
Resource4=IDD_CODECSETTINGFRM_DIALOG
Class4=IDD_PROPERTY_DIALOG
Class5=OSDSetDlg
Class6=ColorPropertyDlg
Class7=CColorPropertyDlg
Class8=CCodecSetting
Class9=CCodecSetFrm
Class10=CCodecSettingFrm
Class11=CCVideoDenoiseFrm
Class12=OSDSetting
Class13=DIGITALZOOM
Resource5=IDR_MENU1

[CLS:CDlgDemoApp]
Type=0
HeaderFile=dlgDemo.h
ImplementationFile=dlgDemo.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC

[CLS:CDlgDemoDlg]
Type=0
HeaderFile=dlgDemoDlg.h
ImplementationFile=dlgDemoDlg.cpp
Filter=W
LastObject=IDC_BUTTON_CODEC
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=dlgDemoDlg.h
ImplementationFile=dlgDemoDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MENU1]
Type=1
Class=CDlgDemoDlg
Command1=ID_SIZE_768
Command2=ID_SIZE_D1
Command3=ID_SIZE_CIF
Command4=ID_SOUR_AV1
Command5=ID_SOUR_AV2
Command6=ID_SOUR_SVIDEO
Command7=ID_STAND_PAL
Command8=ID_STAND_NTSC
Command9=ID_Deinterlace_LowCpu
Command10=ID_Deinterlace_STD
Command11=ID_Deinterlace_GOOD
Command12=ID_Deinterlace_CANCEL
Command13=ID_DENOISE_STD
Command14=ID_Flip_Video
Command15=ID_Mirror_Video
CommandCount=15

[DLG:IDD_DLGDEMO_DIALOG]
Type=1
Class=CDlgDemoDlg
ControlCount=6
Control1=IDC_ST_DISPLAY,static,1342177287
Control2=IDC_BT_RECORD,button,1342242816
Control3=IDC_BUTTON_SNAP,button,1342242816
Control4=IDC_BUTTON_EXIT,button,1342242816
Control5=IDC_BUTTON_CODEC,button,1342242816
Control6=IDC_BUTTON_PAUSEREC,button,1342242816

[CLS:IDD_PROPERTY_DIALOG]
Type=0
HeaderFile=IDD_PROPERTY_DIALOG.h
ImplementationFile=IDD_PROPERTY_DIALOG.cpp
BaseClass=CDialog
Filter=D
LastObject=IDD_PROPERTY_DIALOG

[CLS:ColorPropertyDlg]
Type=0
HeaderFile=olorPropertyDlg.h
ImplementationFile=olorPropertyDlg.cpp
BaseClass=CDialog
Filter=D

[CLS:CColorPropertyDlg]
Type=0
HeaderFile=ColorPropertyDlg.h
ImplementationFile=ColorPropertyDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDOK
VirtualFilter=dWC

[CLS:CCodecSetting]
Type=0
HeaderFile=CodecSetting.h
ImplementationFile=CodecSetting.cpp
BaseClass=CDialog
Filter=D

[CLS:CCodecSetFrm]
Type=0
HeaderFile=CodecSetFrm.h
ImplementationFile=CodecSetFrm.cpp
BaseClass=CDialog
Filter=D

[DLG:IDD_CODECSETTINGFRM_DIALOG]
Type=1
Class=CCodecSettingFrm
ControlCount=17
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_COMBO_VIDEOCODEC,combobox,1344340226
Control5=IDC_STATIC,button,1342177287
Control6=IDC_STATIC,button,1342177287
Control7=IDC_RADIO_H264,button,1342177289
Control8=IDC_RADIO_XVID,button,1342177289
Control9=IDC_RADIO_DIVX,button,1342177289
Control10=IDC_COMBO_AUDIOCODEC,combobox,1344340226
Control11=IDC_STATIC,button,1342177287
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_EDIT_SNAPDIR,edit,1350631552
Control15=IDC_CAP_DIR_EDIT,edit,1350631552
Control16=IDC_BUTTON_BROWSE_SNAPDIR,button,1342242816
Control17=IDC_BUTTON_BROWSE_RECDIR,button,1342242816

[CLS:CCodecSettingFrm]
Type=0
HeaderFile=CodecSettingFrm.h
ImplementationFile=CodecSettingFrm.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_EDIT_SNAPDIR

[CLS:CCVideoDenoiseFrm]
Type=0
HeaderFile=CVideoDenoiseFrm.h
ImplementationFile=CVideoDenoiseFrm.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_STATIC_CONTRAST

[CLS:OSDSetting]
Type=0
HeaderFile=OSDSetting.h
ImplementationFile=OSDSetting.cpp
BaseClass=CDialog
Filter=D
LastObject=ID_Deinterlace_CANCEL
VirtualFilter=dWC

[CLS:DIGITALZOOM]
Type=0
HeaderFile=DIGITALZOOM.h
ImplementationFile=DIGITALZOOM.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC

