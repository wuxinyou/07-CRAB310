; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDlgDemoDlg
LastTemplate=CStatic
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "dlgDemo.h"

ClassCount=17
Class1=CDlgDemoApp
Class2=CDlgDemoDlg
Class3=CAboutDlg

ResourceCount=8
Resource1=IDD_TEXTVIEWER_DLG
Resource2=IDR_MAINFRAME
Resource3=IDD_VIDEOPLAYER_DLG
Resource4=IDD_ABOUTBOX
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
Resource5=IDD_CODECSETTINGFRM_DIALOG
Class14=TxtViewerDlg
Resource6=IDD_DLGDEMO_DIALOG
Class15=PicViewerDlg
Resource7=IDD_PICVIEWER_DLG
Class16=VideoPlayerDlg
Class17=CStaticBtn
Resource8=IDR_MENU1

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
LastObject=CDlgDemoDlg
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=dlgDemoDlg.h
ImplementationFile=dlgDemoDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308481
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352

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
ControlCount=30
Control1=IDC_ST_DISPLAY,static,1342177287
Control2=IDC_BT_RECORD,button,1342242816
Control3=IDC_BUTTON_SNAP,button,1342242816
Control4=IDC_BUTTON_EXIT,button,1342242816
Control5=IDC_BUTTON_CODEC,button,1342242816
Control6=IDC_BUTTON_PAUSEREC,button,1342242816
Control7=IDC_BUTTON_OPEN,button,1342242816
Control8=IDC_EDIT,edit,1352728644
Control9=IDC_PADPOWER,msctls_progress32,1342177281
Control10=IDC_CTRLBOXPOWER,msctls_progress32,1342177281
Control11=IDC_LEFTPOWER,msctls_progress32,1342177281
Control12=IDC_RIGHTPOWER,msctls_progress32,1342177281
Control13=IDC_CLOSEDEVBTN,button,1342242816
Control14=IDC_OPENDEVBTN,button,1342242816
Control15=IDC_CHARGEGIF,static,1342177284
Control16=IDC_PADVOL,static,1342177294
Control17=IDC_CTRLBOXVOL,static,1342177294
Control18=IDC_LEFTVOL,static,1342177294
Control19=IDC_RIGHTVOL,static,1342177294
Control20=IDC_LOADDEVICES,static,1342177284
Control21=IDC_BTN_VIDEOPLAYER,button,1342242816
Control22=IDC_BTN_PICVIEWER,button,1342242816
Control23=IDC_BTN_TXTVIEWER,button,1342242816
Control24=IDC_SPEED,static,1342177294
Control25=IDC_WORKMODE,static,1342177294
Control26=IDC_INFRARED,static,1342177294
Control27=IDC_COMPASS,static,1342177550
Control28=IDC_CHANNEL,static,1342177550
Control29=IDC_CHANNELBTN,button,1342242816
Control30=IDC_BLUETOOTH,static,1342177550

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
ControlCount=15
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,button,1342177287
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EDIT_SNAPDIR,edit,1350631552
Control6=IDC_CAP_DIR_EDIT,edit,1350631552
Control7=IDC_BUTTON_BROWSE_SNAPDIR,button,1342242816
Control8=IDC_BUTTON_BROWSE_RECDIR,button,1342242816
Control9=IDC_STATIC,button,1342177287
Control10=IDC_STATIC,static,1342308352
Control11=IDC_COMBOUINT,combobox,1344340226
Control12=IDC_STATIC,static,1342308352
Control13=IDC_EDITADDRESS,edit,1350631552
Control14=IDC_STATIC,static,1342308352
Control15=IDC_EDITNAME,edit,1350631552

[CLS:CCodecSettingFrm]
Type=0
HeaderFile=CodecSettingFrm.h
ImplementationFile=CodecSettingFrm.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_COMBOUINT

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

[DLG:IDD_TEXTVIEWER_DLG]
Type=1
Class=TxtViewerDlg
ControlCount=1
Control1=IDC_EDIT1,edit,1344340036

[CLS:TxtViewerDlg]
Type=0
HeaderFile=TxtViewerDlg.h
ImplementationFile=TxtViewerDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=ID_Deinterlace_CANCEL
VirtualFilter=dWC

[DLG:IDD_PICVIEWER_DLG]
Type=1
Class=PicViewerDlg
ControlCount=5
Control1=IDC_PIC,static,1342177284
Control2=IDC_BTNPREV,button,1342242816
Control3=IDC_BTNNEXT,button,1342242816
Control4=IDC_LIST1,listbox,1344340227
Control5=IDC_LIST2,listbox,1344340227

[CLS:PicViewerDlg]
Type=0
HeaderFile=PicViewerDlg.h
ImplementationFile=PicViewerDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_LIST1
VirtualFilter=dWC

[DLG:IDD_VIDEOPLAYER_DLG]
Type=1
Class=VideoPlayerDlg
ControlCount=5
Control1=IDC_VIDEOPLAYER_PIC,static,1342177287
Control2=IDC_VIDEOPLAYER_LIST1,listbox,1344340227
Control3=IDC_VIDEOPLAYER_LIST2,listbox,1344340227
Control4=IDC_VIDEOPLAYER_PLAYTIME,msctls_trackbar32,1342242840
Control5=IDC_ODLOG_PIC,static,1342177294

[CLS:VideoPlayerDlg]
Type=0
HeaderFile=VideoPlayerDlg.h
ImplementationFile=VideoPlayerDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_VIDEOPLAYER_LIST2
VirtualFilter=dWC

[CLS:CStaticBtn]
Type=0
HeaderFile=StaticBtn.h
ImplementationFile=StaticBtn.cpp
BaseClass=CStatic
Filter=W
VirtualFilter=WC

