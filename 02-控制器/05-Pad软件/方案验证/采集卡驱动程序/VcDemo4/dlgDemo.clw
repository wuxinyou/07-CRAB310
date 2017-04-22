; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDlgDemoDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "dlgDemo.h"

ClassCount=12
Class1=CDlgDemoApp
Class2=CDlgDemoDlg
Class3=CAboutDlg

ResourceCount=7
Resource1=IDD_CVIDEODENOISEFRM_DIALOG
Resource2=IDR_MAINFRAME
Resource3=IDD_COLORPROPERTYDLG_DIALOG
Resource4=IDD_ABOUTBOX
Class4=IDD_PROPERTY_DIALOG
Class5=OSDSetDlg
Class6=ColorPropertyDlg
Class7=CColorPropertyDlg
Class8=CCodecSetting
Class9=CCodecSetFrm
Resource5=IDD_DLGDEMO_DIALOG
Class10=CCodecSettingFrm
Resource6=IDD_CODECSETTINGFRM_DIALOG
Class11=CCVideoDenoiseFrm
Class12=OSDSetting
Resource7=IDD_OSDSETTING_DIALOG

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
LastObject=IDC_BT_CALLBACK
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

[DLG:IDD_DLGDEMO_DIALOG]
Type=1
Class=CDlgDemoDlg
ControlCount=6
Control1=IDC_ST_DISPLAY,static,1342177287
Control2=IDC_BT_CALLBACK,button,1342242816
Control3=IDC_BT_RECORD,button,1342242816
Control4=IDC_BUTTON_CALLSNAP,button,1342242816
Control5=IDC_BUTTON_EXIT,button,1342242816
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

[DLG:IDD_COLORPROPERTYDLG_DIALOG]
Type=1
Class=CColorPropertyDlg
ControlCount=17
Control1=IDC_DEF_COLOR_BUTTON,button,1342242817
Control2=IDOKEXIT,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_BRIGHTNESS_STATIC,static,1342308352
Control9=IDC_CONTRAST_STATIC,static,1342308352
Control10=IDC_SATURATION_STATIC,static,1342308352
Control11=IDC_HUE_STATIC,static,1342308352
Control12=IDC_SHARPNESS_STATIC,static,1342308352
Control13=IDC_BRIGHTNESS_SLIDER,msctls_trackbar32,1342242840
Control14=IDC_CONTRAST_SLIDER,msctls_trackbar32,1342242840
Control15=IDC_SATURATION_SLIDER,msctls_trackbar32,1342242840
Control16=IDC_HUE_SLIDER,msctls_trackbar32,1342242840
Control17=IDC_SHARPNESS_SLIDER,msctls_trackbar32,1342242840

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

[DLG:IDD_CVIDEODENOISEFRM_DIALOG]
Type=1
Class=CCVideoDenoiseFrm
ControlCount=14
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_SLIDER_DENOISE,msctls_trackbar32,1342242840
Control5=IDC_STATIC_DENOISE,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_SLIDER_SHARP,msctls_trackbar32,1342242840
Control8=IDC_STATIC_SHARP,static,1342308352
Control9=IDC_SLIDER_BRIGHT,msctls_trackbar32,1342242840
Control10=IDC_SLIDER_CONTRACT,msctls_trackbar32,1342242840
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC_BRIGHT,static,1342308352
Control14=IDC_STATIC_CONTRAST,static,1342308352

[CLS:CCVideoDenoiseFrm]
Type=0
HeaderFile=CVideoDenoiseFrm.h
ImplementationFile=CVideoDenoiseFrm.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_STATIC_CONTRAST

[DLG:IDD_OSDSETTING_DIALOG]
Type=1
Class=OSDSetting
ControlCount=48
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_TIMEOSD_CHECK,button,1342242819
Control4=IDC_TIMETRAN_CHECK,button,1342242819
Control5=IDC_STATIC,button,1342177287
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_TimeFontSize_EDIT1,edit,1350631552
Control11=IDC_TimePlaceX_EDIT,edit,1350631552
Control12=IDC_TimePlaceY_EDIT,edit,1350631552
Control13=IDC_STATIC,button,1342177287
Control14=IDC_TEXTOSD_CHECK1,button,1342242819
Control15=IDC_TEXTTRAN_CHECK1,button,1342242819
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_TextFontSize_EDIT1,edit,1350631552
Control21=IDC_TEXTPlaceX_EDIT1,edit,1350631552
Control22=IDC_TextPlaceY_EDIT1,edit,1350631552
Control23=IDC_STATIC,button,1342177287
Control24=IDC_PICTUREOSD_CHECK,button,1342242819
Control25=IDC_STATIC,static,1342308352
Control26=IDC_STATIC,static,1342308352
Control27=IDC_PicturePlaceX_EDIT,edit,1350631552
Control28=IDC_PicturePlaceY_EDIT,edit,1350631552
Control29=IDC_STATIC,button,1342177287
Control30=IDC_TEXTOSD_CHECK2,button,1342242819
Control31=IDC_TEXTTRAN_CHECK2,button,1342242819
Control32=IDC_STATIC,static,1342308352
Control33=IDC_STATIC,static,1342308352
Control34=IDC_STATIC,static,1342308352
Control35=IDC_STATIC,static,1342308352
Control36=IDC_TextFontSize_EDIT3,edit,1350631552
Control37=IDC_TEXTPlaceX_EDIT2,edit,1350631552
Control38=IDC_TextPlaceY_EDIT2,edit,1350631552
Control39=IDC_BUTTON_COLOR2,button,1342242816
Control40=IDC_BUTTON_COLOR3,button,1342242816
Control41=IDC_BUTTON_COLOR1,button,1342242816
Control42=IDC_STATIC,static,1342308352
Control43=IDC_STATIC,static,1342308352
Control44=IDC_Texosd_EDIT4,edit,1350631552
Control45=IDC_Texosd_EDIT5,edit,1350631552
Control46=IDC_STATIC,static,1342308352
Control47=IDC_PictureFile_EDIT,edit,1350631552
Control48=IDC_OPENFILE_BUTTON,button,1342242816

[CLS:OSDSetting]
Type=0
HeaderFile=OSDSetting.h
ImplementationFile=OSDSetting.cpp
BaseClass=CDialog
Filter=D
LastObject=ID_Deinterlace_CANCEL
VirtualFilter=dWC

