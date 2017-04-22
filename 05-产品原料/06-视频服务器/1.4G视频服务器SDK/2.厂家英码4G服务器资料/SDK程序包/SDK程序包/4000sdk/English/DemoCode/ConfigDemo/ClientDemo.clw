; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDeviceEdit
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "clientdemo.h"
LastPage=0

ClassCount=16
Class1=CClientDemoApp
Class2=CAboutDlg
Class3=CClientDemoDlg
Class4=CColorButton
Class5=CColorDlg
Class6=CDeviceEdit
Class7=CDeviceEditDlg
Class8=CDialogKeyBoard
Class9=CDlgCoverFile
Class10=Cdlgcoverfile
Class11=CLocalPlayback
Class12=CNetAlarmDlg
Class13=CPromptDlg
Class14=CPTZDlg
Class15=CRemotePlaybackDlg
Class16=CVideoWnd

ResourceCount=17
Resource1=IDD_VIDEO_WND
Resource2=IDD_DEVICE_DLG
Resource3=IDD_DLG_TAB_PLAYBACK
Resource4=IDD_REMOTE_PLAYBACK
Resource5=IDD_KEYBOARD_DLG
Resource6=IDD_DIALOG_IPEdit
Resource7=IDD_DEV_CONFIG
Resource8=IDD_ABOUTBOX
Resource9=IDD_PTZ_DLG
Resource10=IDD_DLG_LOCALPLAYBACK
Resource11=IDD_DLG_TESTCOVER
Resource12=IDD_DLG_NETALARM
Resource13=IDD_CLIENTDEMO_DIALOG
Resource14=IDD_CRUISEEDIT
Resource15=IDD_CONFIG_DLG
Resource16=IDD_COLOR_DLG
Resource17=IDD_DLG_PROMPT (English (U.S.))

[CLS:CClientDemoApp]
Type=0
BaseClass=CWinApp
HeaderFile=ClientDemo.h
ImplementationFile=ClientDemo.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=ClientDemoDlg.cpp
ImplementationFile=ClientDemoDlg.cpp

[CLS:CClientDemoDlg]
Type=0
BaseClass=CDialog
HeaderFile=ClientDemoDlg.h
ImplementationFile=ClientDemoDlg.cpp
LastObject=IDC_CHECK_OSD
Filter=D
VirtualFilter=dWC

[CLS:CColorButton]
Type=0
BaseClass=CButton
HeaderFile=ColorButton.h
ImplementationFile=ColorButton.cpp

[CLS:CColorDlg]
Type=0
BaseClass=CDialog
HeaderFile=ColorDlg.h
ImplementationFile=ColorDlg.cpp

[CLS:CDeviceEdit]
Type=0
BaseClass=CDialog
HeaderFile=DeviceEdit.h
ImplementationFile=DeviceEdit.cpp
LastObject=CDeviceEdit

[CLS:CDeviceEditDlg]
Type=0
BaseClass=CDialog
HeaderFile=DeviceEditDlg.h
ImplementationFile=DeviceEditDlg.cpp

[CLS:CDialogKeyBoard]
Type=0
BaseClass=CDialog
HeaderFile=DialogKeyBoard.h
ImplementationFile=DialogKeyBoard.cpp

[CLS:CDlgCoverFile]
Type=0
BaseClass=CDialog
HeaderFile=DlgCoverFile.h
ImplementationFile=dlgcoverfile.cpp

[CLS:Cdlgcoverfile]
Type=0
BaseClass=CDialog
HeaderFile=DlgCoverFile.h
ImplementationFile=dlgcoverfile.cpp

[CLS:CLocalPlayback]
Type=0
BaseClass=CDialog
HeaderFile=LocalPlayback.h
ImplementationFile=LocalPlayback.cpp

[CLS:CNetAlarmDlg]
Type=0
BaseClass=CDialog
HeaderFile=NetAlarmDlg.h
ImplementationFile=NetAlarmDlg.cpp

[CLS:CPromptDlg]
Type=0
BaseClass=CDialog
HeaderFile=PromptDlg.h
ImplementationFile=PromptDlg.cpp

[CLS:CPTZDlg]
Type=0
BaseClass=CDialog
HeaderFile=PTZDlg.h
ImplementationFile=PTZDlg.cpp

[CLS:CRemotePlaybackDlg]
Type=0
BaseClass=CDialog
HeaderFile=RemotePlaybackDlg.h
ImplementationFile=RemotePlaybackDlg.cpp

[CLS:CVideoWnd]
Type=0
BaseClass=CDialog
HeaderFile=VideoWnd.h
ImplementationFile=VideoWnd.cpp

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_CLIENTDEMO_DIALOG]
Type=1
Class=CClientDemoDlg
ControlCount=11
Control1=IDC_STATIC_CMBWND,static,1342308352
Control2=IDC_COMBOWNDNUM,combobox,1344339971
Control3=IDC_BTN_DEVICE,button,1342278656
Control4=IDC_BTN_PTZ,button,1342278656
Control5=IDC_BTN_COLOR,button,1342278656
Control6=IDC_BTN_PLAYBACK,button,1342278656
Control7=IDC_BTN_CAPTURE,button,1342242816
Control8=IDC_BTN_SAVE,button,1342242816
Control9=IDC_BTN_DEV_KEYBOARD,button,1342278656
Control10=IDC_BTN_NET_ALARM,button,1342278656
Control11=IDC_CHECK_OSD,button,1342242819

[DLG:IDD_COLOR_DLG]
Type=1
Class=CColorDlg
ControlCount=13
Control1=IDC_STATIC9,button,1342177287
Control2=IDC_STATIC10,static,1342308352
Control3=IDC_STATIC11,static,1342308352
Control4=IDC_STATIC12,static,1342308352
Control5=IDC_STATIC13,static,1342308352
Control6=IDC_STATIC14,static,1073872896
Control7=IDC_BUTTONPOLL,button,1342242816
Control8=IDC_SLIDERDBD,msctls_trackbar32,1342242840
Control9=IDC_SLIDERBHD,msctls_trackbar32,1342242840
Control10=IDC_SLIDERSD,msctls_trackbar32,1342242840
Control11=IDC_SLIDERYL,msctls_trackbar32,1073807384
Control12=IDC_SLIDERLD,msctls_trackbar32,1342242840
Control13=IDC_BUTTON1,button,1073807360

[DLG:IDD_CONFIG_DLG]
Type=1
Class=CDeviceEdit
ControlCount=29
Control1=IDC_EDIT_DEVICE_NAME,edit,1350631552
Control2=IDOK,button,1342242817
Control3=IDCANCEL,button,1342242816
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT_PORT,edit,1350639744
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT_USERNAME,edit,1350631552
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_EDIT_PSW,edit,1350631584
Control12=IDC_STATIC,static,1073872896
Control13=IDC_EDIT_TOTALCHANNEL,edit,1082204288
Control14=IDC_EDIT_SVR,edit,1350631552
Control15=IDC_BTN_Setting,button,1342242816
Control16=IDC_LIST_Upgrade,SysListView32,1350633473
Control17=IDC_BTN_Search,button,1342242816
Control18=IDC_STATIC,static,1342177287
Control19=IDC_STATIC,static,1342177287
Control20=IDC_STATIC,static,1342308352
Control21=IDC_STATIC,static,1342308352
Control22=IDC_STATIC,static,1342308352
Control23=IDC_EDIT_HOSTIP,edit,1350631552
Control24=IDC_EDIT_HOSTPORT,edit,1350631552
Control25=IDC_EDIT_SERIALID,edit,1350631552
Control26=IDC_LIST_DDNS_DEV,SysListView32,1082198017
Control27=IDC_BTN_GETINFO,button,1073807360
Control28=IDC_CHECK_IP,button,1342242819
Control29=IDC_CHECK_SerialID,button,1342242819

[DLG:IDD_DEVICE_DLG]
Type=1
Class=CDeviceEditDlg
ControlCount=1
Control1=IDC_TREE1,SysTreeView32,1350631430

[DLG:IDD_KEYBOARD_DLG]
Type=1
Class=CDialogKeyBoard
ControlCount=66
Control1=ID_KEY_0,button,1342275585
Control2=ID_KEY_1,button,1342275585
Control3=ID_KEY_2,button,1342275585
Control4=ID_KEY_3,button,1342275585
Control5=ID_KEY_4,button,1342275585
Control6=ID_KEY_5,button,1342275585
Control7=ID_KEY_6,button,1342275585
Control8=ID_KEY_7,button,1342275585
Control9=ID_KEY_8,button,1342275585
Control10=ID_KEY_9,button,1342275585
Control11=ID_KEY_10,button,1342275585
Control12=ID_KEY_11,button,1342275585
Control13=ID_KEY_12,button,1342275585
Control14=ID_KEY_13,button,1342275585
Control15=ID_KEY_14,button,1342275585
Control16=ID_KEY_15,button,1342275585
Control17=ID_KEY_16,button,1342275585
Control18=ID_KEY_10PlUS,button,1342275585
Control19=IDC_KEY_ESC,button,1342275584
Control20=IDC_KEY_ENTER,button,1342275584
Control21=IDC_KEY_MENU,button,1342275584
Control22=IDC_KEY_UP,button,1342275584
Control23=IDC_KEY_LEFT,button,1342275584
Control24=IDC_KEY_RIGHT,button,1342275584
Control25=IDC_KEY_DOWN,button,1342275584
Control26=IDC_KEY_SPLIT,button,1342275840
Control27=IDC_KEY_SPLIT_1,button,1342275840
Control28=IDC_KEY_SPLIT_4,button,1342275840
Control29=IDC_KEY_SPLIT_8,button,1342275840
Control30=IDC_KEY_SPLIT_9,button,1342275840
Control31=IDC_KEY_SPLIT_16,button,1342275840
Control32=IDC_KEY_PLAY,button,1342275584
Control33=IDC_KEY_STOP,button,1342275584
Control34=IDC_KEY_BACK,button,1342275584
Control35=IDC_KEY_FAST,button,1342275584
Control36=IDC_KEY_SLOW,button,1342275584
Control37=IDC_KEY_NEXT,button,1342275584
Control38=IDC_KEY_PREV,button,1342275584
Control39=IDC_KEY_SEARCH,button,1342275584
Control40=IDC_KEY_RECORD,button,1342275584
Control41=IDC_KEY_INFO,button,1342275840
Control42=IDC_KEY_ALARM,button,1342275840
Control43=IDC_KEY_BACKUP,button,1342275840
Control44=IDC_KEY_SHUTDOWN,button,1342275840
Control45=IDC_KEY_PTZ_UP,button,1342275584
Control46=IDC_KEY_PTZ_LEFT,button,1342275584
Control47=IDC_KEY_PTZ_RIGHT,button,1342275584
Control48=IDC_KEY_PTZ_DOWN,button,1342276352
Control49=IDC_KEY_ZOOM_TELE,button,1342275584
Control50=IDC_KEY_ZOOM_WIDE,button,1342275584
Control51=IDC_STATIC_ZOOM,static,1342308352
Control52=IDC_KEY_IRIS_LARGE,button,1342275584
Control53=IDC_KEY_IRIS_SMALL,button,1342275584
Control54=IDC_STATIC_IRIS,static,1342308352
Control55=IDC_KEY_FOCUS_FAR,button,1342275584
Control56=IDC_KEY_FOCUS_NEAR,button,1342275584
Control57=IDC_STATIC_FOCUS,static,1342308352
Control58=IDC_KEY_PTZ,button,1342275584
Control59=IDC_KEY_SHIFT,button,1342275584
Control60=IDC_KEY_FUNC,button,1342275584
Control61=IDC_KEY_SET_PRESET,button,1342275584
Control62=IDC_KEY_GO_PRESET,button,1342275584
Control63=IDC_KEY_DEL_PRESET,button,1342275584
Control64=IDC_KEY_AUTO_TOUR,button,1342275584
Control65=IDC_KEY_AUTO_PAN,button,1342275840
Control66=IDC_KEY_AUTO_SCAN,button,1342275584

[DLG:IDD_DLG_TESTCOVER]
Type=1
Class=CDlgCoverFile
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EDIT_SrcPath,edit,1350633600
Control6=IDC_EDIT_DesPath,edit,1350633600
Control7=IDC_BUTTON1,button,1342243072
Control8=IDC_BUTTON2,button,1342243072

[DLG:IDD_DLG_LOCALPLAYBACK]
Type=1
Class=CLocalPlayback
ControlCount=8
Control1=IDC_BUTTON_OPEN,button,1342242816
Control2=IDC_BUTTON_PLAY,button,1342242816
Control3=IDC_BUTTON_STOP,button,1342242816
Control4=IDC_BUTTON_PAUSE,button,1342242816
Control5=IDC_BUTTON_FAST,button,1342242816
Control6=IDC_BUTTON_SLOW,button,1342242816
Control7=IDC_STATIC_PLAYWINDOW,button,1342210055
Control8=IDC_SLIDERFILE,msctls_trackbar32,1342242836

[DLG:IDD_DLG_NETALARM]
Type=1
Class=CNetAlarmDlg
ControlCount=4
Control1=IDC_BTN_START,button,1342243072
Control2=IDC_BTN_STOP,button,1342243072
Control3=IDC_STATIC,static,1342308352
Control4=IDC_CMB_CHANNEL,combobox,1344340226

[DLG:IDD_DLG_PROMPT]
Type=1
Class=CPromptDlg

[DLG:IDD_PTZ_DLG]
Type=1
Class=CPTZDlg
ControlCount=29
Control1=IDC_STATIC4,button,1342177287
Control2=IDC_STATIC5,static,1342308352
Control3=IDC_BUTTONLEFT,button,1342275584
Control4=IDC_BUTTONDOWN,button,1342275584
Control5=IDC_BUTTONUP,button,1342275584
Control6=IDC_BUTTONRIGHT,button,1342275584
Control7=IDC_STATIC6,static,1342308352
Control8=IDC_STATIC7,static,1342308352
Control9=IDC_STATIC8,static,1342308352
Control10=IDC_BUTTONTJLEFT,button,1342275584
Control11=IDC_BUTTONJJLEFT,button,1342275584
Control12=IDC_BUTTONGQLEFT,button,1342275584
Control13=IDC_BUTTONTJRIGHT,button,1342275584
Control14=IDC_BUTTONJJRIGHT,button,1342275584
Control15=IDC_BUTTONGQRIGHT,button,1342275584
Control16=IDC_BUTTONLEFTUP,button,1342275584
Control17=IDC_BUTTONRIGHTUP,button,1342275584
Control18=IDC_BUTTONLEFTDOWN,button,1342275584
Control19=IDC_BUTTONRIGHTDOWN,button,1342275584
Control20=IDC_STATIC,static,1342308352
Control21=IDC_COMBO1,combobox,1344339971
Control22=IDC_UsePresent,button,1342275584
Control23=IDC_ADDPRESENT,button,1342275584
Control24=IDC_PRESENTDELETE,button,1342275584
Control25=IDC_STATIC,static,1342308352
Control26=IDC_COMBO2,combobox,1344274435
Control27=IDC_CRUISEEDIT,button,1342275584
Control28=IDC_CRUISEPLAY,button,1342275584
Control29=IDC_CRUISESTOP,button,1342275584

[DLG:IDD_REMOTE_PLAYBACK]
Type=1
Class=CRemotePlaybackDlg
ControlCount=28
Control1=IDC_STATIC,static,1342308354
Control2=IDC_COMBO_DEVICE,combobox,1344339971
Control3=IDC_STATIC,static,1342308352
Control4=IDC_COMBO_CHANNEL,combobox,1344339971
Control5=IDC_STATIC,static,1342308352
Control6=IDC_COMBO_TYPE,combobox,1344339971
Control7=IDC_STATIC,static,1342308354
Control8=IDC_DATE_BEGIN,SysDateTimePick32,1342242848
Control9=IDC_TIME_BEGIN,SysDateTimePick32,1342242857
Control10=IDC_STATIC,static,1342308352
Control11=IDC_DATE_END,SysDateTimePick32,1342242848
Control12=IDC_TIME_END,SysDateTimePick32,1342242857
Control13=IDC_LIST1,SysListView32,1350631437
Control14=IDC_SEARCH,button,1342242816
Control15=IDC_DOWNLOAD,button,1342242816
Control16=IDC_STATIC_VIDEO,button,1342210055
Control17=IDC_PLAY,button,1342242816
Control18=IDC_STOP,button,1342242816
Control19=IDC_FAST,button,1342242816
Control20=IDC_SLOW,button,1342242816
Control21=IDC_PROGRESS1,msctls_progress32,1350565889
Control22=IDC_PAUSE,button,1342242816
Control23=IDC_CHECK_TIME,button,1342242819
Control24=IDC_CHECK_NAME,button,1342242819
Control25=IDC_STATIC,static,1342308354
Control26=IDC_PAGE_UP,button,1342242816
Control27=IDC_PAGE_DOWN,button,1342242816
Control28=IDC_BUTTON_Audio,button,1342242816

[DLG:IDD_VIDEO_WND]
Type=1
Class=CVideoWnd
ControlCount=0

[DLG:IDD_DEV_CONFIG]
Type=1
Class=?
ControlCount=1
Control1=IDC_COMBO1,combobox,1344339971

[DLG:IDD_CRUISEEDIT]
Type=1
Class=?
ControlCount=7
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,static,1342308352
Control3=IDC_COMBO2,combobox,1344339971
Control4=IDC_BUTTONADDPRESENT,button,1342242816
Control5=IDC_BUTTONDELETEPRESENT,button,1342242816
Control6=IDC_BUTTONDELETECRUISE,button,1342242816
Control7=IDC_EDIT1,edit,1350633600

[DLG:IDD_DLG_TAB_PLAYBACK]
Type=1
Class=?
ControlCount=1
Control1=IDC_TAB1,SysTabControl32,1342177280

[DLG:IDD_DIALOG_IPEdit]
Type=1
Class=?
ControlCount=14
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_IPADDRESS_IP,SysIPAddress32,1342242816
Control10=IDC_IPADDRESS_Mask,SysIPAddress32,1342242816
Control11=IDC_IPADDRESS_Gateway,SysIPAddress32,1342242816
Control12=IDC_EDIT_Http,edit,1350631552
Control13=IDC_EDIT_Tcp,edit,1350631552
Control14=IDC_EDIT_Mac,edit,1350633600

[DLG:IDD_DLG_PROMPT (English (U.S.))]
Type=1
Class=?
ControlCount=1
Control1=IDC_STATIC_MSG,static,1342308352

