// dlgDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Winuser.h"
#include "dlgDemo.h"
#include "dlgDemoDlg.h"
//	#include "ColorPropertyDlg.h"
#include  "CodecSettingFrm.h"
//#include "CVideoDenoiseFrm.h"
//#include "OSDSetting.h"
#include "DeviceControl.h"
#include "ChannelWnd.h"
#include <mmsystem.h>   //just for playsound() 

#include <Dbt.h>    // just for onDeviceChange() 


//全局变量
HANDLE hThread1;




#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


DEVICE_TAG CDlgDemoDlg::VideoTags[100];
DEVICE_TAG CDlgDemoDlg::AudioTags[100];

DEVICE_INFO  CDlgDemoDlg::DeviceInfo[23];
CDlgDemoDlg* g_pDemoDlg = NULL;
//extern SnapOk=false;
int CDlgDemoDlg::m_OpenSata=1;
int CDlgDemoDlg::m_nDevNum=0;
int CDlgDemoDlg::m_PreviewMode=0;
device_handle CDlgDemoDlg::m_device=0;

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}



int CAboutDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	return 0;
}



BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here




	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


/////////////////////////////////////////////////////////////////////////////
// CDlgDemoDlg dialog

CDlgDemoDlg::CDlgDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgDemoDlg)
	m_strReceive = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAM);

	m_fileImg = NULL;
	m_bufImg = NULL;

		//	m_SerialPort=new CSerialPort();
	//初始化成员变量
	m_bSerialPortOpened=FALSE;

	

}

CDlgDemoDlg::~CDlgDemoDlg()
{
	if(m_bSerialPortOpened)
	{
		m_SerialPort.ClosePort();//关闭串口
		m_bSerialPortOpened=FALSE;
	}

	delete pvw;
	delete pvwMask;
	
}
void CDlgDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDemoDlg)
	DDX_Control(pDX, IDC_BLUETOOTH, m_bluetooth);
	DDX_Control(pDX, IDC_CHANNEL, m_channel);
	DDX_Control(pDX, IDC_COMPASS, m_compass);
	DDX_Control(pDX, IDC_WORKMODE, m_workMode);
	DDX_Control(pDX, IDC_SPEED, m_speed);
	DDX_Control(pDX, IDC_INFRARED, m_infrared);
	DDX_Control(pDX, IDC_CHANNELBTN, m_channelBtn);
	DDX_Control(pDX, IDC_BUTTON_EXIT, m_exitBtn);
	DDX_Control(pDX, IDC_BUTTON_OPEN, m_openBtn);
	DDX_Control(pDX, IDC_BTN_VIDEOPLAYER, m_videoPlayerBtn);
	DDX_Control(pDX, IDC_BTN_TXTVIEWER, m_txtViewerBtn);
	DDX_Control(pDX, IDC_BTN_PICVIEWER, m_picViewerBtn);
	DDX_Control(pDX, IDC_LOADDEVICES, m_loadDevicesGIF);
	DDX_Control(pDX, IDC_CTRLBOXVOL, m_ctrlBoxVol);
	DDX_Control(pDX, IDC_LEFTVOL, m_leftVol);
	DDX_Control(pDX, IDC_RIGHTVOL, m_rightVol);
	DDX_Control(pDX, IDC_PADVOL, m_padVol);
	DDX_Control(pDX, IDC_OPENDEVBTN, m_openDevBtn);
	DDX_Control(pDX, IDC_CLOSEDEVBTN, m_closeDevBtn);
	DDX_Control(pDX, IDC_CHARGEGIF, m_chargeGIF);
	DDX_Control(pDX, IDC_RIGHTPOWER, m_rightPower);
	DDX_Control(pDX, IDC_PADPOWER, m_padPower);
	DDX_Control(pDX, IDC_LEFTPOWER, m_leftPower);
	DDX_Control(pDX, IDC_CTRLBOXPOWER, m_ctrlBoxPower);
	DDX_Control(pDX, IDC_BUTTON_PAUSEREC, m_pauseBtn);
	DDX_Control(pDX, IDC_BUTTON_CODEC, m_settingBtn);
	DDX_Control(pDX, IDC_BT_RECORD, m_recordBtn);
	DDX_Control(pDX, IDC_BUTTON_SNAP, m_snapBtn);
	DDX_Control(pDX, IDC_ST_DISPLAY, m_PrvHwnd);
	DDX_Text(pDX, IDC_EDIT, m_strReceive);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CDlgDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BT_STEP_00, OnBtStep00)
	ON_BN_CLICKED(IDC_BT_STEP_01, OnBtStep01)
	ON_BN_CLICKED(IDC_BT_STEP_02, OnBtStep02)
	ON_BN_CLICKED(IDC_BT_STEP_03, OnBtStep03)
	ON_BN_CLICKED(IDC_BT_STEP_04, OnBtStep04)
	ON_BN_CLICKED(IDC_BT_ASSIGN_AUDIO, OnBtAssignAudio)
	ON_BN_CLICKED(IDC_BT_PCOLOR, OnBtPcolor)
	ON_BN_CLICKED(IDC_BT_BMP, OnBtBmp)
	ON_BN_CLICKED(IDC_BT_JPG, OnBtJpg)
	ON_BN_CLICKED(IDC_BT_DRAWFILE, OnBtDrawfile)
	ON_BN_CLICKED(IDC_BT_HIDEFILE, OnBtHidefile)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BT_TEXTOSD, OnBtTextosd)
	ON_BN_CLICKED(IDC_BT_IMAGEOSD, OnBtImageosd)
	ON_BN_CLICKED(IDC_BT_TIMEOSD, OnBtTimeosd)
	ON_BN_CLICKED(IDC_BT_FLIPVIDEO, OnBtFlipvideo)
	ON_BN_CLICKED(IDC_BT_MIRRORVIDEO, OnBtMirrorvideo)
	ON_BN_CLICKED(IDC_BT_BUFDISPLAY, OnBtBufdisplay)
	ON_BN_CLICKED(IDC_BT_SOURCE, OnBtSource)
	ON_COMMAND(ID_SOUR_AV1, OnSourAv1)
	ON_COMMAND(ID_SOUR_AV2, OnSourAv2)
	ON_COMMAND(ID_SOUR_SVIDEO, OnSourSvideo)
	ON_COMMAND(ID_SIZE_D1, OnSizeD1)
	ON_COMMAND(ID_SIZE_CIF, OnSizeCif)
	ON_COMMAND(ID_STAND_NTSC, OnStandNtsc)
	ON_COMMAND(ID_STAND_PAL, OnStandPal)
	ON_UPDATE_COMMAND_UI(ID_SOUR_AV1, OnUpdateSourAv1)
	ON_UPDATE_COMMAND_UI(ID_SOUR_AV2, OnUpdateSourAv2)
	ON_UPDATE_COMMAND_UI(ID_SOUR_SVIDEO, OnUpdateSourSvideo)
	ON_UPDATE_COMMAND_UI(ID_SIZE_D1, OnUpdateSizeD1)
	ON_UPDATE_COMMAND_UI(ID_SIZE_CIF, OnUpdateSizeCif)
	ON_UPDATE_COMMAND_UI(ID_STAND_NTSC, OnUpdateStandNtsc)
	ON_UPDATE_COMMAND_UI(ID_STAND_PAL, OnUpdateStandPal)
	ON_COMMAND(ID_Flip_Video, OnFlipVideo)
	ON_UPDATE_COMMAND_UI(ID_Flip_Video, OnUpdateFlipVideo)
	ON_COMMAND(ID_Mirror_Video, OnMirrorVideo)
	ON_UPDATE_COMMAND_UI(ID_Mirror_Video, OnUpdateMirrorVideo)
	ON_COMMAND(ID_Deinterlace_CANCEL, OnDeinterlaceCANCEL)
	ON_UPDATE_COMMAND_UI(ID_Deinterlace_CANCEL, OnUpdateDeinterlaceCANCEL)
	ON_COMMAND(ID_Deinterlace_GOOD, OnDeinterlaceGOOD)
	ON_UPDATE_COMMAND_UI(ID_Deinterlace_GOOD, OnUpdateDeinterlaceGOOD)
	ON_COMMAND(ID_Deinterlace_STD, OnDeinterlaceSTD)
	ON_UPDATE_COMMAND_UI(ID_Deinterlace_STD, OnUpdateDeinterlaceSTD)
	ON_BN_CLICKED(IDC_BUTTON_GetBuf, OnBUTTONGetBuf)
	ON_BN_CLICKED(IDC_BUTTON_SNAP, OnButtonSnap)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, OnButtonExit)
	ON_BN_CLICKED(IDC_BT_RECORD, OnBtRecord)
	ON_BN_CLICKED(IDC_BUTTON_CODEC, OnButtonCodec)
	ON_BN_CLICKED(IDC_BUTTON_PAUSEREC, OnButtonPauserec)
	ON_WM_DESTROY()
	ON_UPDATE_COMMAND_UI(ID_SIZE_960H, OnUpdateSize960h)
	ON_UPDATE_COMMAND_UI(ID_SIZE_768, OnUpdateSize768)
	ON_COMMAND(ID_SIZE_768, OnSize768)
	ON_COMMAND(ID_SIZE_960H, OnSize960h)
	ON_COMMAND(ID_Deinterlace_LowCpu, OnDeinterlaceLowCpu)
	ON_UPDATE_COMMAND_UI(ID_Deinterlace_LowCpu, OnUpdateDeinterlaceLowCpu)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_OPEN, OnButtonOpen)
	ON_MESSAGE(WM_COMM_RXCHAR, OnComm)   //手动添加串口消息映射
	ON_WM_DEVICECHANGE()                 //手动添加
	ON_BN_CLICKED(IDC_CLOSEDEVBTN, OnClosedevbtn)
	ON_BN_CLICKED(IDC_OPENDEVBTN, OnOpendevbtn)
	ON_BN_CLICKED(IDC_BTN_TXTVIEWER, OnBtnTxtviewer)
	ON_BN_CLICKED(IDC_BTN_PICVIEWER, OnBtnPicviewer)
	ON_BN_CLICKED(IDC_BTN_VIDEOPLAYER, OnBtnVideoplayer)
	ON_MESSAGE(WM_CHANNEL_SET_FOCUS,OnChannelSetFocus)
	ON_MESSAGE(WM_LBTNDBLCLK_SHOWWIN, OnLBTNDBClikShowWin)
	ON_BN_CLICKED(IDC_CHANNELBTN, OnChannelbtn)
	//}}AFX_MSG_MAP

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDemoDlg message handlers



BOOL CDlgDemoDlg::OnInitDialog()
{

	CDialog::OnInitDialog();


//			CAboutDlg dlg;
//		dlg.DoModal();
//
//		dlg.EndDialog(0);



	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here



	//设置数据存储路径
	SetRootPath();


	
	//初始化  发送数据变量
	this->SendData[0]=(char)0xA7;
	this->SendData[1]=(char)0x01;
	this->SendData[2]=(char)0x80;
	this->SendData[3]=(char)0x00;
	this->SendData[4]=(char)0x00;
	this->SendData[5]=(char)0x00;
	this->SendData[6]=(char)0x00;
	this->SendData[7]=(char)0X00;
	this->SendData[8]=(char)0X00;
	this->SendData[9]=(char)0X00;
	this->SendData[10]=(char)0X00;
	this->SendData[11]=(char)0X28;
	

	//成员变量初始化
	RecOK=false;
	IsRecord=false;
	bDevIsConnect=false;
	bIsCharging=false;
	bReadyShutdown=false;
	ReadyClosePort=0;
	
#ifdef USE_3DS_COMPASS
	m_compass.InitCWnd();
#endif


	
	//初始化部件
	InitWidget();
	
	//显示初始化
	showVoltagePicture();
	showSWI();
	ShowBluetooth();
	
	ShowCompass();

#ifdef INITVLC
	//初始化vlc,越晚越好
	InitVLC();
#endif

	/////////////////

	/////////////////





/////////////////////////////////////read inf file start//////////////////////////////////////////

		CString AppPath; 
		//得到当前程序路径
        GetModuleFileName(NULL,AppPath.GetBufferSetLength(1023),1024); 
		AppPath.ReleaseBuffer(); 
        int nPos; 
        nPos = AppPath.ReverseFind('\\'); 
        AppPath = AppPath.Left(nPos); 
		//ini文件存储路径
		strIniFile=AppPath+"\\VCdemoSeting.ini";
		
		CTime time = CTime::GetCurrentTime();

		PicSavePath = RootPath+"\\"+time.Format("%Y%m%d");
		PicPath = PicSavePath+"\\"+"Pic";
		
		RecSavePath = RootPath+"\\"+time.Format("%Y%m%d");
		VideoPath = RecSavePath+"\\"+"Video";
		//将路径写进ini文件里
		WritePrivateProfileString("SystemSetting","PicPath",PicPath,strIniFile); 
		WritePrivateProfileString("SystemSetting","VideoPath",VideoPath,strIniFile);
		
		CString	 strPath;		


		//get the video codec  form ini file 
		CString StrCodec; 
		GetPrivateProfileString("SystemSetting","VideoCodec",X264CODEC_FILTER,StrCodec.GetBuffer(128),128,strIniFile);
		StrCodec.ReleaseBuffer();
		DeviceInfo[dwCard].dwVideoCodecStr=StrCodec;


		//创建图片存储路径
		if(!SetCurrentDirectory(RootPath))
		{
			CreateDirectory(RootPath, NULL);
			
		}
		if(!SetCurrentDirectory(PicSavePath))
		{
			CreateDirectory(PicSavePath, NULL);
			
		}
		if(!SetCurrentDirectory(PicPath))
		{
			CreateDirectory(PicPath, NULL);
			
		}
		//创建视频存储路径
		if(!SetCurrentDirectory(RootPath))
		{
			CreateDirectory(RootPath, NULL);
			
		}
		if(!SetCurrentDirectory(RecSavePath))
		{
			CreateDirectory(RecSavePath, NULL);
			
		}
		if(!SetCurrentDirectory(VideoPath))
		{
			CreateDirectory(VideoPath, NULL);
			
		}

	//get the preview mode form the ini file

	CString PreviewType; 
	GetPrivateProfileString("SystemSetting","PreviewMode","VMR7",PreviewType.GetBuffer(128),128,strIniFile);
	PreviewType.ReleaseBuffer();


/////////////////////////////////////read inf file end//////////////////////////////////////////

	/////////////////////初始化sdk//////////////////////////////////////////////////////////////////
	
	ShowGIF(2,SW_SHOW);
	ShowGIF(1,SW_HIDE);

	////打开定时器4，用于定时初始化设备
	SetTimer(4,1000,NULL);
//	while(!(bDevIsConnect && m_bSerialPortOpened))
//	{
//		ShowGIF(2,SW_SHOW);
//		OnOpendevbtn();
//	}
//	KillTimer(1);        //关闭定时器4。
//	ShowGIF(2,SW_HIDE);

	//InitSDK();	
//////////////////////////////////////打开相关设备//////////////////////////////////////////////
//	OpenSerialPort(3);  //打开串口
	//打开定时器2，用于定时发送数据
	SetTimer(2,100,NULL);//启动定时器1,定时时间是0.1秒
	//打开定时器3，用于定时更新电量信息
	SetTimer(3,1000,NULL);

	//打开定时器5，用于定时检测 速度，工作模式，红外开关
	SetTimer(5,500,NULL);


	
	return TRUE;  // return TRUE  unless you set the focus to a control
}


LRESULT CDlgDemoDlg::OnLBTNDBClikShowWin(WPARAM wp,LPARAM lp)
{
	::AfxMessageBox(_T("btdub windows class false"));	
	return 0;
}
LRESULT CDlgDemoDlg::OnChannelSetFocus(WPARAM wp,LPARAM lp)
{
	UINT idx=(UINT)wp-100;
	
	CString text;
	text.Format("Cur No:%d",idx+1);
	SetDlgItemText(IDC_STATIC_CHANNEL,text);
	dwCard=idx;
	return 0;
}
// CChannelWnd message handlers
//MainWndProc
LRESULT CALLBACK MainWndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	DWORD dwCard = 0;
	//::AfxMessageBox(_T("eeee windows class false"));
	switch(msg)
	{
	case WM_COMMAND:
		break;
	case WM_PAINT:
		break;
	case WM_MOVE:
		break;
	case WM_SIZE:
		
		break;
		
	case WM_DESTROY:
		break;
	case WM_SHOWWINDOW:
		
		break;
		
	case WM_LBUTTONDOWN:
	
		break;
	case WM_MOUSEMOVE:
		break;
	case WM_LBUTTONUP:
		
		
		break;
	case WM_LBUTTONDBLCLK:
		{
		//	::AfxMessageBox(_T("eeee windows class false"));
	
			
			break;
			
		}
		
	}
	
	return DefWindowProc(hWnd, msg, wParam, lParam);
}
BOOL CDlgDemoDlg::CreateWindowClass(  ) 
{
	wsprintf(m_strClassname, "DEMO_Window");
		m_wc.cbSize        = sizeof(m_wc);
	m_wc.style         = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW ;//CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW
	m_wc.lpfnWndProc   = MainWndProc;
	m_wc.hInstance     = AfxGetInstanceHandle();
	m_wc.lpszClassName = m_strClassname;
	m_wc.hbrBackground = CreateSolidBrush(RGB( 255, 0, 255 )  );
	m_wc.hCursor       = LoadCursor( NULL, IDC_ARROW );//LoadCursor(g_Hinstance, MAKEINTRESOURCE (IDC_ARROW));
	m_wc.cbClsExtra    = 0;
	m_wc.cbWndExtra    = 0;
	m_wc.hIcon         = NULL;
	m_wc.hIconSm       = NULL;
	m_wc.lpszMenuName  = NULL;

	if ( 0 == RegisterClassEx( &m_wc ) &&
		ERROR_CLASS_ALREADY_EXISTS != GetLastError() )
		return FALSE;
	return TRUE;

}
void CDlgDemoDlg::OnCreateWindow( DWORD dwCard )
{
//	UpdateData();
	CRect rcShowWin;
	rcShowWin = g_rcShowWin;
	DWORD dwStyle	   = WS_VISIBLE | WS_CHILD;
	HWND hDeskopWnd    = m_PrvHwnd.m_hWnd;
	
	if ( DeviceInfo[dwCard].m_pWnd )
	{

		return;
	}

	if ( m_nDevNum == 1 )
	{
	

//		DeviceInfo[dwCard].dwDispWidth = 720;
//		DeviceInfo[dwCard].dwDispHeight = 576;
//
//		DeviceInfo[dwCard].dwDispPosX = ( DWORD( dwCard % 2 ) ) * ( rcShowWin.Width() / 2 ) + 1; //+ (DWORD)rcShowWin.left;
//		DeviceInfo[dwCard].dwDispPosY = ( DWORD( dwCard / 2 ) ) * ( rcShowWin.Height() / 2 );// + //(DWORD)rcShowWin.top;


		// before 20160711
//		DeviceInfo[dwCard].dwDispWidth = 718;
//		DeviceInfo[dwCard].dwDispHeight = 568;
//
//		DeviceInfo[dwCard].dwDispPosX = 25; 
//		DeviceInfo[dwCard].dwDispPosY = 125;

		//modified on 20160711

		DeviceInfo[dwCard].dwDispWidth = VideoArea_W;
		DeviceInfo[dwCard].dwDispHeight = VideoArea_H;
		
		DeviceInfo[dwCard].dwDispPosX = VideoArea_X; 
		DeviceInfo[dwCard].dwDispPosY = VideoArea_Y;


	}

	if ( m_nDevNum > 1 && m_nDevNum <= 4 )
	{
		DeviceInfo[dwCard].dwDispWidth = (DWORD)rcShowWin.Width() / 2 ;
		DeviceInfo[dwCard].dwDispHeight = (DWORD)rcShowWin.Height() / 2;
		DeviceInfo[dwCard].dwDispPosX = ( DWORD( dwCard % 2 ) ) * ( rcShowWin.Width() / 2 ) + 1; //+ (DWORD)rcShowWin.left;
		DeviceInfo[dwCard].dwDispPosY = ( DWORD( dwCard / 2 ) ) * ( rcShowWin.Height() / 2 );// + //(DWORD)rcShowWin.top;

	}

	if ( m_nDevNum > 4 && m_nDevNum <= 9)
	{
		DeviceInfo[dwCard].dwDispWidth = (DWORD)rcShowWin.Width() / 3 ;
		DeviceInfo[dwCard].dwDispHeight = (DWORD)rcShowWin.Height() / 3;
		DeviceInfo[dwCard].dwDispPosX = ( DWORD( dwCard % 3 ) ) * ( rcShowWin.Width() / 3 ) + 1; //+ (DWORD)rcShowWin.left;
		DeviceInfo[dwCard].dwDispPosY = ( DWORD( dwCard / 3 ) ) * ( rcShowWin.Height() / 3 );// + //(DWORD)rcShowWin.top;
		
	}
	

	
//	CRect rc(DeviceInfo[dwCard].dwDispPosX,
//		DeviceInfo[dwCard].dwDispPosY,
//		DeviceInfo[dwCard].dwDispPosX+DeviceInfo[dwCard].dwDispWidth,
//		DeviceInfo[dwCard].dwDispPosY+	DeviceInfo[dwCard].dwDispHeight
//		);
//	
//
//	
//	pvw->Create(100+dwCard,rc,this);

	
	
	DeviceInfo[dwCard].m_pWnd=pvw;
	DeviceInfo[dwCard].dwPrvHandle =pvw->m_hWnd;
	DeviceInfo[dwCard].m_pWnd->GetClientRect (& DeviceInfo[dwCard].dwPrvRect);
	
	
	 



}

void CDlgDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDlgDemoDlg::OnPaint() 
{
	
	/*
	CPaintDC dc(this); // device context for painting


		//draw the line
	//	::AfxMessageBox("onPaint");
	COLORREF clr=RGB(0,0,254);
//
	if(IsRecord)
		clr=RGB(0,250,0);

	CPen pan(0,3,clr);

	
	dc.SelectObject(&pan);
	CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
	dc.SelectObject(pBrush);
	CPoint m_ptOrigin(25,125);
	CPoint point(743,693);
	dc.Rectangle(CRect(m_ptOrigin,point));
	*/
	


	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting
//
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);

	}
	else
	{
		CDialog::OnPaint();

		if (m_fileImg != NULL)
		{
			//DXUpdateImg(m_fileImg, GetDlgItem(IDC_ST_DRAWFILE)->GetSafeHwnd(), NULL);
		}
		if (m_bufImg != NULL)
		{
			//DXUpdateImg(m_bufImg, GetDlgItem(IDC_ST_DRAWFILE)->GetSafeHwnd(), NULL);
		}
	}

}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDlgDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDlgDemoDlg::OnBtStep00() 
{
	// TODO: Add your control notification handler code here

}

void CDlgDemoDlg::OnBtStep01() 
{
	// TODO: Add your control notification handler code here
	
#ifdef _DEBUG
	m_device = DXOpenDevice(0, NULL);
#else
	m_device = DXOpenDevice(1, NULL);
#endif // _DEBUG

	// 获取输入端子
	unsigned curSource = 0; // 这个是输入端子的序号
	unsigned char num = 0;

	DXGetVideoSources(m_device, & curSource, NULL, & num);
	if (num > 0)
	{
		unsigned* sources = new unsigned[num]; // 这个是输入端子的类型编号
		DXGetVideoSources(m_device, NULL, sources, & num);

		unsigned char idx = 0;
		TCHAR sz[12];
		for (idx = 0; idx < num; idx++)
		{
			wsprintf(sz, _T("%d"), sources[idx]);
			ComboBox_AddString(GetDlgItem(IDC_CB_SOURCES)->GetSafeHwnd(), sz);
		}

		ComboBox_SetCurSel(GetDlgItem(IDC_CB_SOURCES)->GetSafeHwnd(), curSource);

		delete [] sources; sources = NULL;
	}


	DXDeviceRun(m_device);

	DXShowDeviceAttr(m_device, 0, GetSafeHwnd(), NULL);
}

void CDlgDemoDlg::OnBtStep02() 
{
	// TODO: Add your control notification handler code here


	
}

void CDlgDemoDlg::OnBtStep03() 
{

}

void CDlgDemoDlg::OnBtStep04() 
{
	
}





void CDlgDemoDlg::OnBtAssignAudio() 
{
	// TODO: Add your control notification handler code here
	static BOOL bAssignAudio = FALSE;
	bAssignAudio = ! bAssignAudio;

// 	DEVICE_TAG devTag = {};

	DXSetAudioDevice(m_device, NULL);
}

void CDlgDemoDlg::OnBtPcolor() 
{
	// TODO: Add your control notification handler code here
	static BOOL bPColor = FALSE;

	bPColor = ! bPColor;

	DXEnablePColor(m_device, bPColor ? _T("c:\\pcolor.debug") : NULL, 256);
}

void CDlgDemoDlg::OnBtBmp() 
{
	// TODO: Add your control notification handler code here
	
}

void CDlgDemoDlg::OnBtJpg() 
{

}

unsigned __stdcall rawVideoCallback(unsigned char* buffer, unsigned colorSpace,
									   unsigned width, unsigned height, unsigned bytesWidth, void* context)
{
	CString	 strPath;
	CTime time = CTime::GetCurrentTime();
	strPath = PicSavePath+"\\" + time.Format("%Y%m%d-%H%M%S.bmp");
	if(SnapOk)
	{
		int gotBufferLen=colorSpace*width*height;
		DXSaveBMPFile(_T(strPath.GetBuffer(strPath.GetLength())), buffer, gotBufferLen, colorSpace, width, height, bytesWidth);
		SnapOk=false;
	}
	
	return 0;
}

//void CDlgDemoDlg::OnBtCallback() 
//{
//	// TODO: Add your control notification handler code here
//
//	
//  	if (DeviceInfo[dwCard].dwConnectState)
//   {
//			if (bCallback==false)
//		{
//			DXSetRawVideoCallback(DeviceInfo[dwCard].dwChannelHandle, rawVideoCallback, this);
//			 SetDlgItemText(IDC_BT_CALLBACK,"StopCallback");
//			 bCallback=true;
//			 SnapOk=true;
//		}
//		else
//		{
//			DXStopRawVideoCallback(DeviceInfo[dwCard].dwChannelHandle);
//			SetDlgItemText(IDC_BT_CALLBACK,"StartCallback");
//			bCallback=false;
//		}
//
//   }
//	
//
//	
//}

void CDlgDemoDlg::OnBtDrawfile() 
{
	// TODO: Add your control notification handler code here
	TCHAR szFile[MAX_PATH +1];
	::Edit_GetText(GetDlgItem(IDC_ET_DRAWFILE)->GetSafeHwnd(), szFile, MAX_PATH);

//	m_fileImg = DXCreateFileImg(szFile, NULL);
	if (m_fileImg != NULL)
	{
	//	DXUpdateImg(m_fileImg, GetDlgItem(IDC_ST_DRAWFILE)->GetSafeHwnd(), NULL);
	}
}

void CDlgDemoDlg::OnBtHidefile() 
{

}

BOOL CDlgDemoDlg::OnEraseBkgnd(CDC* pDC) 
{
	CDialog::OnEraseBkgnd(pDC);
	// TODO: Add your message handler code here and/or call default

	CBitmap bitmap;
	bitmap.LoadBitmap(IDB_BITMAP_CRAB);

	BITMAP bmp;
	bitmap.GetBitmap(&bmp);

	
	
	CDC dcCompatible;
	dcCompatible.CreateCompatibleDC(pDC);
	
	dcCompatible.SelectObject(&bitmap);
	
	CRect rect;
	this->GetClientRect(&rect);
	//pDC->BitBlt(0,0,rect.Width(),rect.Height(),&dcCompatible,0,0,SRCCOPY);    //1:1 贴图
	pDC->StretchBlt(0,0,rect.Width(),rect.Height(),&dcCompatible,0,0,bmp.bmWidth,bmp.bmHeight,SRCCOPY);  //缩放贴图

	bitmap.DeleteObject();   //release resource

//	return CDialog::OnEraseBkgnd(pDC);
	return true;
	

}

void CDlgDemoDlg::OnBtTextosd() 
{
	// TODO: Add your control notification handler code here

}

void CDlgDemoDlg::OnBtImageosd() 
{
	// TODO: Add your control notification handler code here

}

void CDlgDemoDlg::OnBtTimeosd() 
{

}

void CDlgDemoDlg::OnBtFlipvideo() 
{
	// TODO: Add your control notification handler code here
	DXFlipVideo(m_device, TRUE);
}

void CDlgDemoDlg::OnBtMirrorvideo() 
{
	// TODO: Add your control notification handler code here
		
}

void CDlgDemoDlg::OnBtBufdisplay() 
{

}

void CDlgDemoDlg::OnBtSource() 
{
	// TODO: Add your control notification handler code here

}

void CDlgDemoDlg::OnSourAv1() 
{
	// TODO: Add your command handler code here
	if (m_nDevNum>0)
	{
			//设置视频源输入为AV1
			m_DeviceControl.SetVideoSource(DeviceInfo[dwCard].dwChannelHandle,1);
	}

	
}

void CDlgDemoDlg::OnSourAv2() 
{
	// TODO: Add your command handler code here
	if (m_nDevNum>0)
	{
				//设置视频源输入为AV2
	m_DeviceControl.SetVideoSource(DeviceInfo[dwCard].dwChannelHandle,2);
	
	}


	
}

void CDlgDemoDlg::OnSourSvideo() 
{
	// TODO: Add your command handler code here

	if (m_nDevNum>0)
	{
				//设置视频源输入为SVIDEO
		m_DeviceControl.SetVideoSource(DeviceInfo[dwCard].dwChannelHandle,3);

	}
}

void CDlgDemoDlg::OnSizeD1() 
{
	// TODO: Add your command handler code here
	if (m_nDevNum>0)
	{		
		    //pal=32 ntsc=1
			if (DeviceInfo[dwCard].dwVidStandard==32)
			{
				if (DeviceInfo[dwCard].dwWidth!=720)
				{
						if (DeviceInfo[dwCard].dwConnectState)
						{
								m_DeviceControl.StopPrview(DeviceInfo[dwCard].dwChannelHandle);

						}
						
						if (DeviceInfo[dwCard].dwConnectState)
						{
							m_DeviceControl.DisConnectDevice(DeviceInfo[dwCard].dwChannelHandle);
						}

							DeviceInfo[dwCard].dwWidth=720;
							DeviceInfo[dwCard].dwHeight=576;

								if(m_nDevNum==1) 
								{
										::MoveWindow(GetDlgItem(IDC_ST_DISPLAY)->GetSafeHwnd(),0,0,DeviceInfo[dwCard].dwWidth,	DeviceInfo[dwCard].dwHeight,false);
								}
								m_PrvHwnd.GetClientRect (&g_rcShowWin);

																		
							DeviceInfo[dwCard].dwConnectState=m_DeviceControl.ConnectDevice(DeviceInfo[dwCard].dwChannelHandle,
																			DeviceInfo[dwCard].dwVidStandard,
																			DeviceInfo[dwCard].dwColorspace,
																			DeviceInfo[dwCard].dwWidth,
																			DeviceInfo[dwCard].dwHeight,
																			DeviceInfo[dwCard].dwFrameRate);
						if (DeviceInfo[dwCard].dwConnectState)
						{

							DeviceInfo[dwCard].dwPrviewState=m_DeviceControl.StartPrview(DeviceInfo[dwCard].dwChannelHandle,
																				DeviceInfo[dwCard].dwPrvHandle,
																				&DeviceInfo[dwCard].dwPrvRect,
																				m_PreviewMode,
																				true);	
													
						}


				}
			}
			else
			{
				if (DeviceInfo[dwCard].dwWidth!=640)
				{
						if (DeviceInfo[dwCard].dwConnectState)
						{
								m_DeviceControl.StopPrview(DeviceInfo[dwCard].dwChannelHandle);

						}
						
						if (DeviceInfo[dwCard].dwConnectState)
						{
							m_DeviceControl.DisConnectDevice(DeviceInfo[dwCard].dwChannelHandle);
						}

							DeviceInfo[dwCard].dwWidth=640;
							DeviceInfo[dwCard].dwHeight=480;
								if(m_nDevNum==1) 
								{
										::MoveWindow(GetDlgItem(IDC_ST_DISPLAY)->GetSafeHwnd(),0,0,DeviceInfo[dwCard].dwWidth,	DeviceInfo[dwCard].dwHeight,false);
								}
								m_PrvHwnd.GetClientRect (&g_rcShowWin);
																		
							DeviceInfo[dwCard].dwConnectState=m_DeviceControl.ConnectDevice(DeviceInfo[dwCard].dwChannelHandle,
																			DeviceInfo[dwCard].dwVidStandard,
																			DeviceInfo[dwCard].dwColorspace,
																			DeviceInfo[dwCard].dwWidth,
																			DeviceInfo[dwCard].dwHeight,
																			DeviceInfo[dwCard].dwFrameRate);
						if (DeviceInfo[dwCard].dwConnectState)
						{

							DeviceInfo[dwCard].dwPrviewState=m_DeviceControl.StartPrview(DeviceInfo[dwCard].dwChannelHandle,
																				DeviceInfo[dwCard].dwPrvHandle,
																				&DeviceInfo[dwCard].dwPrvRect,
																				m_PreviewMode,
																				true);	
													
						}


				}


			}
		
		




	}

}

void CDlgDemoDlg::OnSizeCif() 
{
	// TODO: Add your command handler code here
	if (m_nDevNum>0)
	{		
		//pal=32 ntsc=1
	
	
			if (DeviceInfo[dwCard].dwWidth!=352)
			{
				if (DeviceInfo[dwCard].dwConnectState)
				{
					m_DeviceControl.StopPrview(DeviceInfo[dwCard].dwChannelHandle);
					
				}
				
				if (DeviceInfo[dwCard].dwConnectState)
				{
					m_DeviceControl.DisConnectDevice(DeviceInfo[dwCard].dwChannelHandle);
				}
				
				DeviceInfo[dwCard].dwWidth=352;
				DeviceInfo[dwCard].dwHeight=288;			
				DeviceInfo[dwCard].dwConnectState=m_DeviceControl.ConnectDevice(DeviceInfo[dwCard].dwChannelHandle,
					DeviceInfo[dwCard].dwVidStandard,
					DeviceInfo[dwCard].dwColorspace,
					DeviceInfo[dwCard].dwWidth,
					DeviceInfo[dwCard].dwHeight,
					DeviceInfo[dwCard].dwFrameRate);
				if (DeviceInfo[dwCard].dwConnectState)
				{
					
					DeviceInfo[dwCard].dwPrviewState=m_DeviceControl.StartPrview(DeviceInfo[dwCard].dwChannelHandle,
						DeviceInfo[dwCard].dwPrvHandle,
						&DeviceInfo[dwCard].dwPrvRect,
						m_PreviewMode,
						true);	
					
				}
				
				
			}		
	}
}

void CDlgDemoDlg::OnStandNtsc() 
{
	// TODO: Add your command handler code here

	if (m_nDevNum>0)
	{		
		    //pal=32 ntsc=1
			if (DeviceInfo[dwCard].dwVidStandard!=1)
			{
				
				
						if (DeviceInfo[dwCard].dwConnectState)
						{
								m_DeviceControl.StopPrview(DeviceInfo[dwCard].dwChannelHandle);

						}
						
						if (DeviceInfo[dwCard].dwConnectState)
						{
							m_DeviceControl.DisConnectDevice(DeviceInfo[dwCard].dwChannelHandle);
						}

						
								if (DeviceInfo[dwCard].dwHeight>480)
								DeviceInfo[dwCard].dwHeight=480;

								DeviceInfo[dwCard].dwVidStandard=1;
								DeviceInfo[dwCard].dwFrameRate=30;

								//connect device										
							DeviceInfo[dwCard].dwConnectState=m_DeviceControl.ConnectDevice(DeviceInfo[dwCard].dwChannelHandle,
																			DeviceInfo[dwCard].dwVidStandard,
																			DeviceInfo[dwCard].dwColorspace,
																			DeviceInfo[dwCard].dwWidth,
																			DeviceInfo[dwCard].dwHeight,
																			DeviceInfo[dwCard].dwFrameRate);
						if (DeviceInfo[dwCard].dwConnectState)
						{

							DeviceInfo[dwCard].dwPrviewState=m_DeviceControl.StartPrview(DeviceInfo[dwCard].dwChannelHandle,
																				DeviceInfo[dwCard].dwPrvHandle,
																				&DeviceInfo[dwCard].dwPrvRect,
																				m_PreviewMode,
																				true);	
													
						}


				
			}
		
		}
}

void CDlgDemoDlg::OnStandPal() 
{
	// TODO: Add your command handler code here

		if (m_nDevNum>0)
	{		
		    //pal=32 ntsc=1
			if (DeviceInfo[dwCard].dwVidStandard!=32)
			{
				
				
						if (DeviceInfo[dwCard].dwPrviewState )
						{
								m_DeviceControl.StopPrview(DeviceInfo[dwCard].dwChannelHandle);

						}
						
						if (DeviceInfo[dwCard].dwConnectState)
						{
							m_DeviceControl.DisConnectDevice(DeviceInfo[dwCard].dwChannelHandle);
						}

						

								DeviceInfo[dwCard].dwVidStandard=32;
								DeviceInfo[dwCard].dwFrameRate=25;

								//connect device										
							DeviceInfo[dwCard].dwConnectState=m_DeviceControl.ConnectDevice(DeviceInfo[dwCard].dwChannelHandle,
																			DeviceInfo[dwCard].dwVidStandard,
																			DeviceInfo[dwCard].dwColorspace,
																			DeviceInfo[dwCard].dwWidth,
																			DeviceInfo[dwCard].dwHeight,
																			DeviceInfo[dwCard].dwFrameRate);
						if (DeviceInfo[dwCard].dwConnectState)
						{

							DeviceInfo[dwCard].dwPrviewState=m_DeviceControl.StartPrview(DeviceInfo[dwCard].dwChannelHandle,
																				DeviceInfo[dwCard].dwPrvHandle,
																				&DeviceInfo[dwCard].dwPrvRect,
																				m_PreviewMode,
																				true);	
													
						}


				
			}
		
		}
}

void CDlgDemoDlg::OnUpdateSourAv1(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here

  	AfxGetMainWnd()->GetMenu()->CheckMenuItem(ID_SOUR_AV1,MF_CHECKED);
	AfxGetMainWnd()->GetMenu()->CheckMenuItem(ID_SOUR_AV2,MF_UNCHECKED);
	AfxGetMainWnd()->GetMenu()->CheckMenuItem(ID_SOUR_SVIDEO,MF_UNCHECKED);
	
}

void CDlgDemoDlg::OnUpdateSourAv2(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here

	AfxGetMainWnd()->GetMenu()->CheckMenuItem(ID_SOUR_AV1,MF_UNCHECKED);
	AfxGetMainWnd()->GetMenu()->CheckMenuItem(ID_SOUR_AV2,MF_CHECKED);
	AfxGetMainWnd()->GetMenu()->CheckMenuItem(ID_SOUR_SVIDEO,MF_UNCHECKED);
	
}

void CDlgDemoDlg::OnUpdateSourSvideo(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here

	AfxGetMainWnd()->GetMenu()->CheckMenuItem(ID_SOUR_AV1,MF_UNCHECKED);
	AfxGetMainWnd()->GetMenu()->CheckMenuItem(ID_SOUR_AV2,MF_UNCHECKED);
	AfxGetMainWnd()->GetMenu()->CheckMenuItem(ID_SOUR_SVIDEO,MF_CHECKED);
	
}

void CDlgDemoDlg::OnUpdateSizeD1(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	AfxGetMainWnd()->GetMenu()->CheckMenuItem(ID_SIZE_D1,MF_CHECKED);
	AfxGetMainWnd()->GetMenu()->CheckMenuItem(ID_SIZE_CIF,MF_UNCHECKED);
	AfxGetMainWnd()->GetMenu()->CheckMenuItem(ID_SIZE_960H,MF_UNCHECKED);
	AfxGetMainWnd()->GetMenu()->CheckMenuItem(ID_SIZE_768,MF_UNCHECKED);
	
}

void CDlgDemoDlg::OnUpdateSizeCif(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	AfxGetMainWnd()->GetMenu()->CheckMenuItem(ID_SIZE_D1,MF_UNCHECKED);
	AfxGetMainWnd()->GetMenu()->CheckMenuItem(ID_SIZE_CIF,MF_CHECKED);
	AfxGetMainWnd()->GetMenu()->CheckMenuItem(ID_SIZE_960H,MF_UNCHECKED);
	AfxGetMainWnd()->GetMenu()->CheckMenuItem(ID_SIZE_768,MF_UNCHECKED);
}

void CDlgDemoDlg::OnUpdateStandNtsc(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	AfxGetMainWnd()->GetMenu()->CheckMenuItem(ID_STAND_PAL,MF_UNCHECKED);
	AfxGetMainWnd()->GetMenu()->CheckMenuItem(ID_STAND_NTSC,MF_CHECKED);
}

void CDlgDemoDlg::OnUpdateStandPal(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	AfxGetMainWnd()->GetMenu()->CheckMenuItem(ID_STAND_PAL,MF_CHECKED);
	AfxGetMainWnd()->GetMenu()->CheckMenuItem(ID_STAND_NTSC,MF_UNCHECKED);
}

void CDlgDemoDlg::OnFlipVideo() 
{
	// TODO: Add your command handler code here
	if (m_nDevNum>0)
	{
			if (AfxGetMainWnd()->GetMenu()->GetMenuState(ID_Flip_Video,MF_CHECKED))
			{
					//	m_DeviceControl.SetVideoFlip(DeviceInfo[dwCard].dwChannelHandle,true);
				DXFlipVideo(DeviceInfo[dwCard].dwChannelHandle,true);

			}
			else

			{
					DXFlipVideo(DeviceInfo[dwCard].dwChannelHandle,false);

			}

	}

	
}

void CDlgDemoDlg::OnUpdateFlipVideo(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
		if (AfxGetMainWnd()->GetMenu()->GetMenuState(ID_Flip_Video,MF_CHECKED))
		{
				AfxGetMainWnd()->GetMenu()->CheckMenuItem(ID_Flip_Video,MF_UNCHECKED);
		}
		else
		{
				AfxGetMainWnd()->GetMenu()->CheckMenuItem(ID_Flip_Video,MF_CHECKED);
		}
}

void CDlgDemoDlg::OnMirrorVideo() 
{
	// TODO: Add your command handler code here

	if (m_nDevNum>0)
	{
			if (AfxGetMainWnd()->GetMenu()->GetMenuState(ID_Mirror_Video,MF_CHECKED))
			{
					m_DeviceControl.SetVideoMirro(DeviceInfo[dwCard].dwChannelHandle,true);

			}
			else

			{
					m_DeviceControl.SetVideoMirro(DeviceInfo[dwCard].dwChannelHandle,false);

			}

	}
	
}

void CDlgDemoDlg::OnUpdateMirrorVideo(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
		if (AfxGetMainWnd()->GetMenu()->GetMenuState(ID_Mirror_Video,MF_CHECKED))
		{
				AfxGetMainWnd()->GetMenu()->CheckMenuItem(ID_Mirror_Video,MF_UNCHECKED);
		}
		else
		{
				AfxGetMainWnd()->GetMenu()->CheckMenuItem(ID_Mirror_Video,MF_CHECKED);
		}
}

void CDlgDemoDlg::OnDeinterlaceCANCEL() 
{
	// TODO: Add your command handler code here
		if (m_nDevNum>0)
	{
		//取消隔行算法
		m_DeviceControl.EnableDeinterlace(DeviceInfo[dwCard].dwChannelHandle,0,false);
	}
}

void CDlgDemoDlg::OnUpdateDeinterlaceCANCEL(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here

	AfxGetMainWnd()->GetMenu()->CheckMenuItem(ID_Deinterlace_STD,MF_UNCHECKED);
	AfxGetMainWnd()->GetMenu()->CheckMenuItem(ID_Deinterlace_GOOD,MF_UNCHECKED);
	AfxGetMainWnd()->GetMenu()->CheckMenuItem(ID_Deinterlace_CANCEL,MF_CHECKED);
	AfxGetMainWnd()->GetMenu()->CheckMenuItem(ID_Deinterlace_LowCpu,MF_UNCHECKED);
	
}

void CDlgDemoDlg::OnDeinterlaceGOOD() 
{
	// TODO: Add your command handler code here
		if (m_nDevNum>0)
	{
			//s设置隔行算法为良好
			m_DeviceControl.EnableDeinterlace(DeviceInfo[dwCard].dwChannelHandle,2,true);
	}
}

void CDlgDemoDlg::OnUpdateDeinterlaceGOOD(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	AfxGetMainWnd()->GetMenu()->CheckMenuItem(ID_Deinterlace_STD,MF_UNCHECKED);
	AfxGetMainWnd()->GetMenu()->CheckMenuItem(ID_Deinterlace_GOOD,MF_CHECKED);
	AfxGetMainWnd()->GetMenu()->CheckMenuItem(ID_Deinterlace_CANCEL,MF_UNCHECKED);
	AfxGetMainWnd()->GetMenu()->CheckMenuItem(ID_Deinterlace_LowCpu,MF_UNCHECKED);
}

void CDlgDemoDlg::OnDeinterlaceSTD() 
{
	// TODO: Add your command handler code here
	if (m_nDevNum>0)
	{
		//设置隔行算法为标准
	
		m_DeviceControl.EnableDeinterlace(DeviceInfo[dwCard].dwChannelHandle,0,true);
	}
}

void CDlgDemoDlg::OnUpdateDeinterlaceSTD(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
		
	AfxGetMainWnd()->GetMenu()->CheckMenuItem(ID_Deinterlace_STD,MF_CHECKED);
	AfxGetMainWnd()->GetMenu()->CheckMenuItem(ID_Deinterlace_GOOD,MF_UNCHECKED);
	AfxGetMainWnd()->GetMenu()->CheckMenuItem(ID_Deinterlace_CANCEL,MF_UNCHECKED);
	AfxGetMainWnd()->GetMenu()->CheckMenuItem(ID_Deinterlace_LowCpu,MF_UNCHECKED);
}

//void CDlgDemoDlg::OnColorPropertyButton() 
//{
//	// TODO: Add your control notification handler code here
//	CColorPropertyDlg coDlg;
//
//	coDlg.DoModal();	
//	
//}



void CDlgDemoDlg::OnBUTTONGetBuf() 
{
	// TODO: Add your control notification handler code here

	unsigned YuvbufferLen;
	unsigned RgbbufferLen ;
	unsigned char* buffer;
	unsigned char* RgbBuf;
	if (DeviceInfo[dwCard].dwWidth>0)
	{

		YuvbufferLen = DeviceInfo[dwCard].dwWidth *DeviceInfo[dwCard].dwHeight *2;
		RgbbufferLen = DeviceInfo[dwCard].dwWidth *DeviceInfo[dwCard].dwHeight *3;
		buffer = new unsigned char[YuvbufferLen];
		RgbBuf = new unsigned char[RgbbufferLen];

	}



	unsigned gotBufferLen = 0;
	unsigned colorSpace = 0;
	unsigned width = 0;
	unsigned height = 0;
	unsigned bytesWidth = 0;
	CString	 strPath;


	CTime time = CTime::GetCurrentTime();

   if (DeviceInfo[dwCard].dwConnectState)
	{
		     //get the cur buf ,video stream format is the yuv2

			DXGetFrameBuffer(DeviceInfo[dwCard].dwChannelHandle,
							buffer,
							YuvbufferLen,
							& gotBufferLen, 
							& colorSpace,
							& width,
							& height,
							& bytesWidth,
							NULL);
			//snap file name
			strPath = PicSavePath+"\\" + time.Format("%Y%m%d-%H%M%S.bmp");
			//YUV2 TO RGB24
			DXConvertYUVtoRGB(DeviceInfo[dwCard].dwChannelHandle,
								buffer,
								RgbBuf,
								width,
								height,
								false,
								false);

			//save to bmp file
			m_DeviceControl.SaveRGBToBmp(strPath,width,height,RgbBuf);
		//	DXSaveBMPFile(_T(strPath.GetBuffer(strPath.GetLength())), buffer, gotBufferLen, colorSpace, width, height, bytesWidth);
			strPath = PicSavePath+"\\" + time.Format("%Y%m%d-%H%M%S.jpg");
				//save to jpg file
			DXSaveJPGFile(_T(strPath.GetBuffer(strPath.GetLength())), buffer, gotBufferLen, colorSpace, width, height, bytesWidth, 50);
			delete [] buffer;
			delete [] RgbBuf;
		
			::AfxMessageBox("Snap jpg ok: "+strPath);

	}


}

void CDlgDemoDlg::OnButtonSnap() 
{
	// TODO: Add your control notification handler code here
	Sleep(100);
	SetCursorPos( 0,0); //强制将鼠标移动到(0,0)的坐标从而避免了总是显示按下的状态
//	Sleep(1000);
//	mouse_event( MOUSEEVENTF_LEFTDOWN, 0,0,0,NULL);//鼠标down事件

	//如果没有连接设备，则退出
	if(!bDevIsConnect)
		return;

	this->OpenThread1();

	CString	 strPath;
	CTime time = CTime::GetCurrentTime();
	if (DeviceInfo[dwCard].dwConnectState)
	{
//		strPath = PicSavePath+"\\" + time.Format("%Y%m%d-%H%M%S.bmp");
//		m_DeviceControl.SnapPicture(DeviceInfo[dwCard].dwChannelHandle,_T(strPath.GetBuffer(strPath.GetLength())),0,NULL);
	//	Sleep(50);
		strPath = PicPath+"\\" + time.Format("%Y%m%d-%H%M%S.JPG");
		m_DeviceControl.SnapPicture(DeviceInfo[dwCard].dwChannelHandle,_T(strPath.GetBuffer(strPath.GetLength())),1,NULL);
		
		//	::AfxMessageBox("Snap jpg ok: "+strPath);
	}

	//	GetFocus();
}

//void CDlgDemoDlg::OnButtonCallsnap() 
//{
//	 //TODO: Add your control notification handler code here
//		if (bCallback==false)
//		{
//			::AfxMessageBox("Please start the callback");
//		}
//		if (SnapOk==false)
//		{
//			SnapOk=true;
//		}
//}

void CDlgDemoDlg::OnButtonExit() 
{
	// TODO: Add your control notification handler code here
	for(int j=0;j<sizeof(DeviceInfo)/sizeof(DeviceInfo[0]);j++)
	{
		if(DeviceInfo[j].m_pWnd)
		{
			DeviceInfo[j].m_pWnd->DestroyWindow();
			delete DeviceInfo[j].m_pWnd;
			DeviceInfo[j].m_pWnd=NULL;
			
		};
	}
	for(int i=0;i<m_nDevNum;i++)
	{
		
		if (DeviceInfo[i].dwPrviewState )
		{
			m_DeviceControl.StopPrview(DeviceInfo[i].dwChannelHandle);
			
		}
		
		if (DeviceInfo[i].dwConnectState)
		{
			m_DeviceControl.DisConnectDevice(DeviceInfo[i].dwChannelHandle);
		}
	}
	DXUninitialize();
	
	//一下2句代码用于强制关闭软件进程，用于解决关闭后任然留在后台运行的问题。
	HANDLE hself = GetCurrentProcess();
	TerminateProcess(hself, 0);
	////////////
	CDialog::OnCancel();

}


void CDlgDemoDlg::OnBtRecord() 
{
	// TODO: Add your control notification handler code here
	Sleep(100);
	SetCursorPos( 0,0); //强制将鼠标移动到(0,0)的坐标从而避免了总是显示按下的状态
	
	if(!bDevIsConnect)
		return;
	

	CString	 strPath;
	
	
	if (bDevIsConnect)
	{	
		DXGetVideoPara(DeviceInfo[dwCard].dwChannelHandle,
			DeviceInfo[dwCard].dwVidStandard,
			DeviceInfo[dwCard].dwColorspace,
			DeviceInfo[dwCard].dwWidth,
			DeviceInfo[dwCard].dwHeight,
			DeviceInfo[dwCard].dwFrameRate);
		
		if(!RecOK)
		{
			//开启定时器显示录制边框
			SetTimer(1,1000,NULL);//启动定时器1,定时时间是1秒
			IsRecord=true;
			
			if(	DeviceInfo[dwCard].dwVideoCodecStr==X264CODEC_FILTER)
			{
				//set the h264 video codec paramete
				DeviceInfo[dwCard].dwVideoCodecpara.Bitrate= 0;  ////为0时候,编码器内部自己计算
				DeviceInfo[dwCard].dwVideoCodecpara.fps = int(DeviceInfo[dwCard].dwFrameRate);
				DeviceInfo[dwCard].dwVideoCodecpara.keyframeinterval = 110;
				DeviceInfo[dwCard].dwVideoCodecpara.rcMode = codec_CBR;
				DeviceInfo[dwCard].dwVideoCodecpara.Quality = 9;
				DeviceInfo[dwCard].dwVideoCodecpara.Maxrbps=4000;
				DeviceInfo[dwCard].dwVideoCodecpara.Peekbps=2000;
				
				CTime time = CTime::GetCurrentTime();
				strPath = VideoPath+"\\" + time.Format("%Y%m%d-%H%M%S.mp4");
				//start recording
				m_DeviceControl.StartRecord(DeviceInfo[dwCard].dwChannelHandle,
					strPath,
					DeviceInfo[dwCard].dwVideoCodecStr,
					DeviceInfo[dwCard].dwVideoCodecpara);
				SetDlgItemText(IDC_BT_RECORD,"Stop Rec");
				RecOK=true;
				
			}
			if(	DeviceInfo[dwCard].dwVideoCodecStr==XVIDCODEC_FILTER)
			{
				//set the xvid video codec paramete
				DeviceInfo[dwCard].dwVideoCodecpara.Bitrate= 1280;  
				DeviceInfo[dwCard].dwVideoCodecpara.fps = int(DeviceInfo[dwCard].dwFrameRate);
				DeviceInfo[dwCard].dwVideoCodecpara.keyframeinterval = 110;
				DeviceInfo[dwCard].dwVideoCodecpara.rcMode = codec_CBR;
				DeviceInfo[dwCard].dwVideoCodecpara.Quality = 4;
				
			}
			
			CTime time = CTime::GetCurrentTime();
			strPath = VideoPath+"\\" + time.Format("%Y%m%d-%H%M%S.avi");
			//start recording
			m_DeviceControl.StartRecord(DeviceInfo[dwCard].dwChannelHandle,
				strPath,
				DeviceInfo[dwCard].dwVideoCodecStr,
				DeviceInfo[dwCard].dwVideoCodecpara);
			SetDlgItemText(IDC_BT_RECORD,"Stop Rec");
			RecOK=true;
			
			
			
			
		}
		else
		{
			m_DeviceControl.StopRecord(DeviceInfo[dwCard].dwChannelHandle);
			
			SetDlgItemText(IDC_BT_RECORD,"Record");
			RecOK=false;
			IsRecord=false;
			//	::AfxMessageBox("REC OK: "+strPath);
			
			this->DrawRecordFrame(RGB(0,0,0));
			KillTimer(1);        //关闭定时器1。
		}
	}
}

void CDlgDemoDlg::OnButtonCodec() 
{
	// TODO: Add your control notification handler code here
		CCodecSettingFrm CodecDlg;

	   CodecDlg.DoModal();
}

//void CDlgDemoDlg::OnDenoiseStd() 
//{
//	// TODO: Add your command handler code here
//
//	  CCVideoDenoiseFrm CodecDlg;
//
//	   CodecDlg.DoModal();
//}

void CDlgDemoDlg::OnButtonPauserec() 
{
	// TODO: Add your control notification handler code here
	if (RecOK)
	{

		if(PauseRec==false)
		{
			   ///pause the video recording
				m_DeviceControl.FreezeRecord(DeviceInfo[dwCard].dwChannelHandle,true);
				PauseRec=true;
				SetDlgItemText(IDC_BUTTON_PAUSEREC,"Stop Pause");
		}
		else

		{
				m_DeviceControl.FreezeRecord(DeviceInfo[dwCard].dwChannelHandle,false);
				PauseRec=false;
				SetDlgItemText(IDC_BUTTON_PAUSEREC,"Pause Rec");
		}

		
	}
}

//void CDlgDemoDlg::OnOsdsetButton() 
//{
//	// TODO: Add your control notification handler code here
//	OSDSetting OsdDialog;
//	OsdDialog.DoModal();
//	
//}

void CDlgDemoDlg::OnDestroy() 
{
	CDialog::OnDestroy();


	//释放采集卡资源
	for(int i=0;i<sizeof(DeviceInfo)/sizeof(DeviceInfo[0]);i++)
	{
		if(DeviceInfo[i].m_pWnd)
		{
			DeviceInfo[i].m_pWnd->DestroyWindow();
			delete DeviceInfo[i].m_pWnd;
			DeviceInfo[i].m_pWnd=NULL;
			
		};
	}
	
	for(int j=0;j<m_nDevNum;j++)
	{
		
		if (DeviceInfo[j].dwPrviewState )
		{
			m_DeviceControl.StopPrview(DeviceInfo[j].dwChannelHandle);
			
		}
		
		if (DeviceInfo[j].dwConnectState)
		{
			m_DeviceControl.DisConnectDevice(DeviceInfo[j].dwChannelHandle);
		}
	}
	DXUninitialize();

	//释放vlc资源



	// TODO: Add your message handler code here
	
}

void CDlgDemoDlg::OnUpdateSize960h(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	AfxGetMainWnd()->GetMenu()->CheckMenuItem(ID_SIZE_D1,MF_UNCHECKED);
	AfxGetMainWnd()->GetMenu()->CheckMenuItem(ID_SIZE_CIF,MF_UNCHECKED);
	AfxGetMainWnd()->GetMenu()->CheckMenuItem(ID_SIZE_960H,MF_CHECKED);
	AfxGetMainWnd()->GetMenu()->CheckMenuItem(ID_SIZE_768,MF_UNCHECKED);
	
}

void CDlgDemoDlg::OnUpdateSize768(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	AfxGetMainWnd()->GetMenu()->CheckMenuItem(ID_SIZE_D1,MF_UNCHECKED);
	AfxGetMainWnd()->GetMenu()->CheckMenuItem(ID_SIZE_CIF,MF_UNCHECKED);
	AfxGetMainWnd()->GetMenu()->CheckMenuItem(ID_SIZE_960H,MF_UNCHECKED);
	AfxGetMainWnd()->GetMenu()->CheckMenuItem(ID_SIZE_768,MF_CHECKED);
	
}

void CDlgDemoDlg::OnSize768() 
{
	// TODO: Add your command handler code here
		if (m_nDevNum>0)
	{		
		    //pal=32 ntsc=1
			if (DeviceInfo[dwCard].dwVidStandard==32)
			{
				if (DeviceInfo[dwCard].dwWidth!=768)
				{
						if (DeviceInfo[dwCard].dwConnectState)
						{
								m_DeviceControl.StopPrview(DeviceInfo[dwCard].dwChannelHandle);

						}
						
						if (DeviceInfo[dwCard].dwConnectState)
						{
							m_DeviceControl.DisConnectDevice(DeviceInfo[dwCard].dwChannelHandle);
						}

							DeviceInfo[dwCard].dwWidth=768;
							DeviceInfo[dwCard].dwHeight=576;
								if(m_nDevNum==1) 
								{
										::MoveWindow(GetDlgItem(IDC_ST_DISPLAY)->GetSafeHwnd(),0,0,DeviceInfo[dwCard].dwWidth,	DeviceInfo[dwCard].dwHeight,false);
								}
								m_PrvHwnd.GetClientRect (&g_rcShowWin);
																		
							DeviceInfo[dwCard].dwConnectState=m_DeviceControl.ConnectDevice(DeviceInfo[dwCard].dwChannelHandle,
																			DeviceInfo[dwCard].dwVidStandard,
																			DeviceInfo[dwCard].dwColorspace,
																			DeviceInfo[dwCard].dwWidth,
																			DeviceInfo[dwCard].dwHeight,
																			DeviceInfo[dwCard].dwFrameRate);
						if (DeviceInfo[dwCard].dwConnectState)
						{

							DeviceInfo[dwCard].dwPrviewState=m_DeviceControl.StartPrview(DeviceInfo[dwCard].dwChannelHandle,
																				DeviceInfo[dwCard].dwPrvHandle,
																				&DeviceInfo[dwCard].dwPrvRect,
																				m_PreviewMode,
																				true);	
													
						}


				}
			}
			else
			{
				if ((DeviceInfo[dwCard].dwWidth!=720)&&(DeviceInfo[dwCard].dwHeight!=480))
				{
						if (DeviceInfo[dwCard].dwConnectState)
						{
								m_DeviceControl.StopPrview(DeviceInfo[dwCard].dwChannelHandle);

						}
						
						if (DeviceInfo[dwCard].dwConnectState)
						{
							m_DeviceControl.DisConnectDevice(DeviceInfo[dwCard].dwChannelHandle);
						}

							DeviceInfo[dwCard].dwWidth=720;
							DeviceInfo[dwCard].dwHeight=480;
								if(m_nDevNum==1) 
								{
										::MoveWindow(GetDlgItem(IDC_ST_DISPLAY)->GetSafeHwnd(),0,0,DeviceInfo[dwCard].dwWidth,	DeviceInfo[dwCard].dwHeight,false);
								}
								m_PrvHwnd.GetClientRect (&g_rcShowWin);
																		
							DeviceInfo[dwCard].dwConnectState=m_DeviceControl.ConnectDevice(DeviceInfo[dwCard].dwChannelHandle,
																			DeviceInfo[dwCard].dwVidStandard,
																			DeviceInfo[dwCard].dwColorspace,
																			DeviceInfo[dwCard].dwWidth,
																			DeviceInfo[dwCard].dwHeight,
																			DeviceInfo[dwCard].dwFrameRate);
						if (DeviceInfo[dwCard].dwConnectState)
						{

							DeviceInfo[dwCard].dwPrviewState=m_DeviceControl.StartPrview(DeviceInfo[dwCard].dwChannelHandle,
																				DeviceInfo[dwCard].dwPrvHandle,
																				&DeviceInfo[dwCard].dwPrvRect,
																				m_PreviewMode,
																				true);	
													
						}


				}


			}
		
		




	}
}

void CDlgDemoDlg::OnSize960h() 
{
	// TODO: Add your command handler code here
		if (m_nDevNum>0)
	{		
		    //pal=32 ntsc=1
			if (DeviceInfo[dwCard].dwVidStandard==32)
			{
				if (DeviceInfo[dwCard].dwWidth!=960)
				{
						if (DeviceInfo[dwCard].dwConnectState)
						{
								m_DeviceControl.StopPrview(DeviceInfo[dwCard].dwChannelHandle);

						}
						
						if (DeviceInfo[dwCard].dwConnectState)
						{
							m_DeviceControl.DisConnectDevice(DeviceInfo[dwCard].dwChannelHandle);
						}

							DeviceInfo[dwCard].dwWidth=960;
							DeviceInfo[dwCard].dwHeight=576;
								if(m_nDevNum==1) 
								{
										::MoveWindow(GetDlgItem(IDC_ST_DISPLAY)->GetSafeHwnd(),0,0,DeviceInfo[dwCard].dwWidth,	DeviceInfo[dwCard].dwHeight,false);
								}
								m_PrvHwnd.GetClientRect (&g_rcShowWin);
																		
							DeviceInfo[dwCard].dwConnectState=m_DeviceControl.ConnectDevice(DeviceInfo[dwCard].dwChannelHandle,
																			DeviceInfo[dwCard].dwVidStandard,
																			DeviceInfo[dwCard].dwColorspace,
																			DeviceInfo[dwCard].dwWidth,
																			DeviceInfo[dwCard].dwHeight,
																			DeviceInfo[dwCard].dwFrameRate);
						if (DeviceInfo[dwCard].dwConnectState)
						{

							DeviceInfo[dwCard].dwPrviewState=m_DeviceControl.StartPrview(DeviceInfo[dwCard].dwChannelHandle,
																				DeviceInfo[dwCard].dwPrvHandle,
																				&DeviceInfo[dwCard].dwPrvRect,
																				m_PreviewMode,
																				true);	
													
						}


				}
			}
			else
			{
				if ((DeviceInfo[dwCard].dwWidth!=960)&&(DeviceInfo[dwCard].dwHeight!=480))
				{
						if (DeviceInfo[dwCard].dwConnectState)
						{
								m_DeviceControl.StopPrview(DeviceInfo[dwCard].dwChannelHandle);

						}
						
						if (DeviceInfo[dwCard].dwConnectState)
						{
							m_DeviceControl.DisConnectDevice(DeviceInfo[dwCard].dwChannelHandle);
						}

							DeviceInfo[dwCard].dwWidth=960;
							DeviceInfo[dwCard].dwHeight=480;
								if(m_nDevNum==1) 
								{
										::MoveWindow(GetDlgItem(IDC_ST_DISPLAY)->GetSafeHwnd(),0,0,DeviceInfo[dwCard].dwWidth,	DeviceInfo[dwCard].dwHeight,false);
								}
								m_PrvHwnd.GetClientRect (&g_rcShowWin);
																		
							DeviceInfo[dwCard].dwConnectState=m_DeviceControl.ConnectDevice(DeviceInfo[dwCard].dwChannelHandle,
																			DeviceInfo[dwCard].dwVidStandard,
																			DeviceInfo[dwCard].dwColorspace,
																			DeviceInfo[dwCard].dwWidth,
																			DeviceInfo[dwCard].dwHeight,
																			DeviceInfo[dwCard].dwFrameRate);
						if (DeviceInfo[dwCard].dwConnectState)
						{

							DeviceInfo[dwCard].dwPrviewState=m_DeviceControl.StartPrview(DeviceInfo[dwCard].dwChannelHandle,
																				DeviceInfo[dwCard].dwPrvHandle,
																				&DeviceInfo[dwCard].dwPrvRect,
																				m_PreviewMode,
																				true);	
													
						}


				}


			}
		
		




	}
}

void CDlgDemoDlg::OnDeinterlaceLowCpu() 
{
	// TODO: Add your command handler code here
		m_DeviceControl.EnableDeinterlace(DeviceInfo[dwCard].dwChannelHandle,0,true);
	
}

void CDlgDemoDlg::OnUpdateDeinterlaceLowCpu(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	AfxGetMainWnd()->GetMenu()->CheckMenuItem(ID_Deinterlace_STD,MF_CHECKED);
	AfxGetMainWnd()->GetMenu()->CheckMenuItem(ID_Deinterlace_GOOD,MF_UNCHECKED);
	AfxGetMainWnd()->GetMenu()->CheckMenuItem(ID_Deinterlace_CANCEL,MF_UNCHECKED);
	AfxGetMainWnd()->GetMenu()->CheckMenuItem(ID_Deinterlace_LowCpu,MF_CHECKED);
}

//void CDlgDemoDlg::OnRadioVmr7() 
//{
//	// TODO: Add your control notification handler code here
//
//		WritePrivateProfileString("SystemSetting","PreviewMode","VMR7",strIniFile); 
//	
//}
//
//void CDlgDemoDlg::OnRadioOffscrean() 
//{
//	// TODO: Add your control notification handler code here
//
//		WritePrivateProfileString("SystemSetting","PreviewMode","OFFScrean",strIniFile); 
//	
//}
//
//void CDlgDemoDlg::OnRadioVmr9() 
//{
//	// TODO: Add your control notification handler code here
//
//		WritePrivateProfileString("SystemSetting","PreviewMode","VMR9",strIniFile);
//	
//}

//void CDlgDemoDlg::OnZoomButton() 
//{
//	// TODO: Add your control notification handler code here
//	DIGITALZOOM ZoomDlg;
//	 ZoomDlg.DoModal();
//}

void CDlgDemoDlg::DrawRecordFrame(COLORREF clr)
{
//	CPaintDC dc(this); 
	CClientDC dc(this);
	//draw the line
//	::AfxMessageBox("onPaint");
	CPen pan(0,3,clr);
	
	
	dc.SelectObject(&pan);
	CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
	dc.SelectObject(pBrush);
	CPoint m_ptOrigin(165,51);
	CPoint point(1116,799);
	dc.Rectangle(CRect(m_ptOrigin,point));

	//绘制REC录像标志
//	CRect RECRect(400,300,450,350);
//	dc.DrawText("REC",RECRect,0);
//
//	dc.DrawText("",RECRect,0);

}

void CDlgDemoDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	static bool flag=true;
	switch(nIDEvent)
	{
	case 1:		
		if(flag)
		{
			DrawRecordFrame(RGB(250,0,0));

		}
		else
		{
			DrawRecordFrame(RGB(0,250,0));

		}
		flag=!flag;
		break;
	case 2:

#ifdef ACTIVE_SEND     //上位机主动发送数据
		this->SendSerialData();
#endif
		
		break;
	case 3:

		showVoltagePicture();
	//	this->UpdatePowerStatus();
		break;
	case 4:

		
#ifdef USE_PORT
		if(bDevIsConnect && m_bSerialPortOpened)
#else
		if(bDevIsConnect)
#endif
		{
			//KillTimer(4);        //关闭定时器4。
			ShowGIF(2,SW_HIDE);

		}
		else
		{
			//如果不在充电，就加载设备资源以及显示加载界面，
			//	if(!bIsCharging)
			{
				ShowGIF(2,SW_SHOW);
			//	ShowGIF(1,SW_HIDE);

			//	OnOpendevbtn();
			}
		}
#ifndef OPEN_DEV_DEBUG

		//如果不是准备关机，则一直打开设备
		if(!bReadyShutdown)
		{
//			if(bDevIsConnect)
//				OnOpendevbtn(2);			
			OnOpendevbtn();
		}
		
#endif


		
		break;
	case 5:
		//显示机器人的工作状态，包括 速度，工作模式，红外,蓝牙状态。
		showSWI();

		ShowCompass();
		ShowOSD();
		ShowBluetooth();
		break;
		
	case 6:  //Timer6用于定时关闭：外部进程：VLC
		
		TerminateProcess(ShExecInfo.hProcess,0);
		
		
		SetTimer(7,500,NULL);
		KillTimer(6);
		break;
	case 7:
		//关闭后可以不将主界面总在最前面
		//设置窗口总在最前面
		//因为关闭VLC后立即恢复还是会有窗口一闪而过，所以加一个延时。
#ifdef WNDTOPMOST
		/*		ShowWindow(SW_SHOW);
		UpdateWindow();*/
		SetWindowPos(&CWnd::wndNoTopMost,0,0,0,0,
			SWP_NOMOVE|SWP_NOSIZE|SWP_NOACTIVATE);
#endif
				KillTimer(7);
		break;

	}

	
	CDialog::OnTimer(nIDEvent);
}

//打开录像文件目录
void CDlgDemoDlg::OnButtonOpen() 
{
	// TODO: Add your control notification handler code here
		ShellExecute(NULL,NULL,RecSavePath, NULL,NULL,SW_SHOW);  //第三个参数，输入你要打开的文件路径
	
		
}



//背景音乐线程
DWORD WINAPI ThreadProc1(LPVOID lpParameter)
{
	//add operations
//	Beep(301,2000);
	PlaySound("1374.wav",NULL, SND_FILENAME | SND_LOOP);
	return 0;


}


void CDlgDemoDlg::OpenThread1() 
{
	// TODO: Add your control notification handler code here

	// 照相是闪烁一下
	pvwMask->ShowWindow(SW_SHOW);

	pvwMask->SetBKBmp(IDB_BITMAP);
	hThread1=CreateThread(NULL,0,ThreadProc1,NULL,CREATE_SUSPENDED,NULL);

	ResumeThread(hThread1);

	CloseHandle(hThread1);

	pvwMask->ShowWindow(SW_HIDE);

}

//串口消息处理函数
LONG CDlgDemoDlg::OnComm(WPARAM ch, LPARAM port)
{
	//将接收到的数据入队并且出队保存

	unsigned char tempData[RECEIVE_DATA_LEN]={0};
	unsigned char check=0;
	static bool isHeadEntry=false;

	//这里我尝试使用(char)ch==0xa5,发现失败，我想可以推导出奇偶检验失败的原因。
	if(ch==RECEIVE_DATA_HEAD || isHeadEntry)      //如果是帧头或者帧头已经入队，数据才可以入队，否则一概不能入队。
	{
		isHeadEntry=true;     //标记帧头已经入队
		ReceiveQueue.EnQueue(ch);
	}
	

	if(ReceiveQueue.IsFull())  //如果队满，就全部出队
	{
		//	AfxMessageBox("没有发现此串口或被占用");
		for(int i=0;i<QUEUESIZE-1;i++)
			ReceiveQueue.DeQueue(tempData[i]);  //出队临时保存
		
		isHeadEntry=false;  //帧头已经出队		

		//接收数据 校验处理
		for(int icheck=0;icheck<QUEUESIZE-2;icheck++)
		{
			check+=tempData[icheck];
			
		}
#ifdef PORT_DEBUG
		static int recNumber=0;
		recNumber++;
		m_strReceive.Format("%X %X %x %x %x %x %x %x %x %x %x %x %x %x %d",
			QUEUESIZE,tempData[0],tempData[1],tempData[2],tempData[3],tempData[4],
			tempData[5],tempData[6],tempData[7],tempData[8],tempData[9],tempData[10],tempData[11],check,recNumber);

		UpdateData(FALSE);  //将接收到的字符显示在接收编辑框中
#endif

			if(check==tempData[RECEIVE_DATA_LEN-1])
		{
			for(int icopy=0;icopy<QUEUESIZE-1;icopy++)
			{
				ReceiveData.Data[icopy]=tempData[icopy];
				
			}
			//处理接收数据，主要是控制信号的处理
			this->ReceiveDataProcess();
			//收到即发送
#ifdef PASSIVE_REPLY    //被动回复
			this->SendSerialData();
#endif
		}
		//校验处理完


	}

	return 0;
}

void CDlgDemoDlg::OpenSerialPort(UINT port)
{
	if(m_SerialPort.InitPort(this, port, 9600,'N',8,1,EV_RXFLAG | EV_RXCHAR,512))
	{
		m_SerialPort.StartMonitoring();     //串口开始监控
		m_bSerialPortOpened=TRUE;
	}
	else
	{
	//	AfxMessageBox("没有发现此串口或被占用");
		

		m_bSerialPortOpened=FALSE;
	}
}

void CDlgDemoDlg::SendSerialData()
{
	// TODO: Add your control notification handler code here
	if(!m_bSerialPortOpened) return; //检查串口是否打开


 //发送充电准备好
	SendData[3]=ReadyClosePort;
 //控制发送充电准备好信号的帧数
	static int lastSendCount=0;
	if(ReadyClosePort)
	{
		lastSendCount++;
		if(lastSendCount>5)  //发送10次以后立即关闭串口和采集卡
		{
			lastSendCount=0;

			//关闭前先保存一下视频
			if(RecOK) //如果正在录制
			{
				OnBtRecord();
			}
			OnClosedevbtn();   //关闭采集卡和串口
		}
		
	}






 //计算校验和
	unsigned char checkSum=0;
	
	for(int i=0;i<SEND_DATA_LEN-1;i++)
	{
		checkSum+=SendData[i];
	}
	SendData[SEND_DATA_LEN-1]=checkSum;


	m_SerialPort.WriteToPort((char *)SendData,SEND_DATA_LEN);//发送数据

}

/////////////////////////////////////////
//使用进度条显示电量信息
//该函数已经被弃用，被showVoltagePicture取代
/////////////////////////////////////////
void CDlgDemoDlg::UpdatePowerStatus()
{
	GetSystemPowerStatus(&SystemPowerStatus);
	
	m_padPower.SetPos(SystemPowerStatus.BatteryLifePercent-1);
	
	bIsCharging=SystemPowerStatus.ACLineStatus;

	//根据充电情况显示充电动态图
	if(bIsCharging)
	{
		ShowGIF(1,SW_SHOW);
		ShowGIF(2,SW_HIDE);
	}
	else
	{
		ShowGIF(1,SW_HIDE);
	}
	

	if(m_bSerialPortOpened)   //如果串口打开才更新，否则更新无效
	{
		m_ctrlBoxPower.SetPos( Voltage2Volume(ReceiveData.allData.ctrlBoxPower,3) );
		m_leftPower.SetPos( Voltage2Volume(ReceiveData.allData.leftPower,7) );
		m_rightPower.SetPos( Voltage2Volume(ReceiveData.allData.rightPower,7) );
	}

}

void CDlgDemoDlg::InitSDK()
{
	m_nDevNum=m_DeviceControl.InitDevice ();
	
	if(m_nDevNum==1) 
	{
		::MoveWindow(GetDlgItem(IDC_ST_DISPLAY)->GetSafeHwnd(),VideoArea_X,VideoArea_Y,VideoArea_W,VideoArea_H,false);
	}
	m_PrvHwnd.GetClientRect (&g_rcShowWin);
	
	
	
	if(m_nDevNum<1)
	{
	//	::AfxMessageBox("视频采集失败!!!");
		return ;
	}
	else
	{
		
		////////////////
		if ( !CreateWindowClass() )
		{
			::AfxMessageBox(_T("Create windows class false"));
			return ;
		}
		
		for (int j=0; j<m_nDevNum; j++)
		{
			OnCreateWindow( j );
			
			
		}
		
		for (int i=0; i<m_nDevNum; i++)
		{
			DeviceInfo[i].dwWidth =VideoArea_W;
			DeviceInfo[i].dwHeight =VideoArea_H;
			//yuv2 type
			DeviceInfo[i].dwColorspace=2;
			DeviceInfo[i].dwFrameRate=25;
			//pal =0x20  ntsc=0x01;
			DeviceInfo[i].dwVidStandard=32;
			//open device
			DeviceInfo[i].dwChannelHandle =m_DeviceControl.OpenDevice (i, &DeviceInfo[i].dwOpenDevState );
			
			
			
			if (DeviceInfo[i].dwOpenDevState!=0)
			{
				::AfxMessageBox("open device false");
				return ;
			}
			else
			{
				
				//connect the device
				DeviceInfo[i].dwConnectState=m_DeviceControl.ConnectDevice(DeviceInfo[i].dwChannelHandle,
					DeviceInfo[i].dwVidStandard,
					DeviceInfo[i].dwColorspace,
					DeviceInfo[i].dwWidth,
					DeviceInfo[i].dwHeight,
					DeviceInfo[i].dwFrameRate);
				if (DeviceInfo[i].dwConnectState)
				{
					//start preview
					DeviceInfo[i].dwPrviewState=m_DeviceControl.StartPrview(DeviceInfo[i].dwChannelHandle,
						DeviceInfo[i].dwPrvHandle,
						&DeviceInfo[i].dwPrvRect ,
						m_PreviewMode,
						true);	
					//设置隔行算法为标准
					
					//	m_DeviceControl.EnableDeinterlace(DeviceInfo[i].dwChannelHandle,0,true);
					
					//设置降噪算法
					//	DXEnableDenoise(DeviceInfo[i].dwChannelHandle,50);
					
				}
				
				
				if (!DeviceInfo[i].dwPrviewState)
				{
					::AfxMessageBox("Start Preview Flase");
					return ;
				} 
				
				bDevIsConnect=true;     //标记已经连接设备
			}
			
		}
		
		
		
		
	}

	//初始化OSD
	ShowOSD();
	
	
}

void CDlgDemoDlg::OnClosedevbtn() 
{
	// TODO: Add your control notification handler code here
//#ifdef OPEN_DEV_DEBUG
//	bReadyShutdown=true;
//#endif
////
//		for(int i=0;i<sizeof(DeviceInfo)/sizeof(DeviceInfo[0]);i++)
//	{
//		if(DeviceInfo[i].m_pWnd)
//		{
//			DeviceInfo[i].m_pWnd->DestroyWindow();
//			delete DeviceInfo[i].m_pWnd;
//			DeviceInfo[i].m_pWnd=NULL;
//			
//		};
//	}
//	
//	for(int j=0;j<m_nDevNum;j++)
//	{
//		
//		if (DeviceInfo[j].dwPrviewState )
//		{
//			m_DeviceControl.StopPrview(DeviceInfo[j].dwChannelHandle);
//			
//		}
//		
//		if (DeviceInfo[j].dwConnectState)
//		{
//			m_DeviceControl.DisConnectDevice(DeviceInfo[j].dwChannelHandle);
//		}
//	}

	///

	
	if(bDevIsConnect)
	{	

		DXDeviceStop(DeviceInfo[0].dwChannelHandle);
		bDevIsConnect=false;
	}

	if(m_bSerialPortOpened)
	{
		m_SerialPort.ClosePort();//关闭串口
		m_bSerialPortOpened=FALSE;


		//	delete m_SerialPort;
	}




//	ShowMask();
}


void CDlgDemoDlg::OnOpendevbtn() 
{
	// TODO: Add your control notification handler code here
//#ifdef OPEN_DEV_DEBUG
//	bReadyShutdown=false;
//#endif

#ifdef USE_SDK
	if(!bDevIsConnect)
	{
		DXUninitialize();
		InitSDK();
		
	}
#endif


#ifdef USE_SDK
	if(!m_bSerialPortOpened && bDevIsConnect)
#else
		if(!m_bSerialPortOpened)
#endif
		{
			//	AfxMessageBox("UsePort");
			//	m_SerialPort=new CSerialPort();
#ifdef USE_PORT
			
			OpenSerialPort(4);  //打开串口
#endif
		}

}


//接收数据处理函数
void CDlgDemoDlg::ReceiveDataProcess()
{

//	unsigned char snapByte=0;
//	unsigned char recordByte=0;
	unsigned char readyShutdown=0;

//	snapByte   = (ReceiveData.allData.ctrlByte_1 & (0x03<<2)) >> 2;
//	recordByte = (ReceiveData.allData.ctrlByte_1 & (0x03<<0)) >> 0;
	readyShutdown = (ReceiveData.allData.ctrlByte_1 & (0x03<<6)) >> 6;

	
//	static int isSnap=0;
//	//判断是否拍照
//	if(snapByte==0x01)
//	{
//		if(isSnap==0)
//		{
//			OnButtonSnap();	
//			isSnap=1;
//		}
//		
//	}
//	else
//		isSnap=0;
//	//判断是否在录像
//	static int isRecord=0;
//	if(recordByte==0x01)
//	{
//		if(isRecord==0)
//		{
//			OnBtRecord();	
//			isRecord=1;
//		}
//	}
//	else
//		isRecord=0;

	//判断是否准备关机
	if(readyShutdown) 
	{
		ReadyClosePort=0x02;
		bReadyShutdown=true;
	}
	else
	{
		ReadyClosePort=0;
		//	bReadyShutdown=false;  //这句绝对不能加！！！
	}
	
	
}


BOOL CDlgDemoDlg::OnDeviceChange(UINT nEventType,DWORD dwData)
{
    //DEV_BROADCAST_DEVICEINTERFACE* dbd = (DEV_BROADCAST_DEVICEINTERFACE*) dwData;



	switch (nEventType)
	{
	case DBT_DEVICEREMOVECOMPLETE://移除设备

	//	AfxMessageBox("移除设备");

		break;
	case DBT_DEVICEARRIVAL://添加设备
		//	AfxMessageBox("添加设备");
		//只要有一个设备没有连接就继续连接
//		SetTimer(4,200,NULL);
//		
//		ReadyClosePort=0;
		
		break;

	default:
		//	AfxMessageBox("设备变化");
//		for(int i=0;i<5;i++)
//		{
//			OnOpendevbtn();
//			
//		}
		//这里有2种情况：1.上电时：bReadyShutdown=false,是没有问题的，
						 //	2.下电时：bReadyShutdown=false;有点问题，但是这是发生在物理电路已经断开了，所以不会有影响。
		bReadyShutdown=false;
		break;
	}

	return TRUE;

//
//
//	DEV_BROADCAST_HDR* dhr = (DEV_BROADCAST_HDR *)dwData;
//	TRACE("--nEventType--:%d\n", nEventType);
//	switch (nEventType)
//	{
//	case DBT_DEVICEREMOVECOMPLETE://移除设备
//		TRACE("--DEVICE REMOVE--\n");
//#if 1
//		if(dhr->dbch_devicetype == DBT_DEVTYP_PORT) 
//		{ 
//			PDEV_BROADCAST_PORT lpdbv = (PDEV_BROADCAST_PORT)dhr; 
//			int len = strlen(lpdbv->dbcp_name);
//			CString name(lpdbv->dbcp_name);//COM8
//			int port = 3;
//			sscanf(name.GetBuffer(0), "COM%d", &port);
//		} 
//#endif
//		TRACE("--DEVICE REMOVE--end\n");
//		break;
//	case DBT_DEVICEARRIVAL://添加设备
//		TRACE("--DEVICE ARRIVAL--\n");
//#if 1		
//		if(dhr->dbch_devicetype == DBT_DEVTYP_PORT) 
//		{ 
//			PDEV_BROADCAST_PORT lpdbv = (PDEV_BROADCAST_PORT)dhr; 
//			int len = strlen(lpdbv->dbcp_name);
//			CString name(lpdbv->dbcp_name);//COM8
//			int port = 3;
//			sscanf(name.GetBuffer(0), "COM%d", &port);
//		} 
//#endif
//		break;
//	default:
//		AfxMessageBox("设备变化");
//
//		break;
//	}

	//	return TRUE;


}

void CDlgDemoDlg::ShowMask()
{
	pvwMask->ShowWindow(SW_SHOW);
	//pvwMask->SetFocus();
//pvwMask->SetFocus();
//	pvwMask->ShowWindow(SW_SHOW);
//
	pvwMask->SetBKBmp(IDB_BITMAP);
	
}

//电压与电量的转换函数
//出入：电压值，电池串数
//输出：电压百分比
int CDlgDemoDlg::Voltage2Volume(unsigned char voltage,int cellNum)
{
	double percent=0;
	double singleCellVoltage=0;
	int percentNum=0;

	singleCellVoltage=voltage*0.2/cellNum;

	//最大最小值处理
	if(singleCellVoltage>=4.16)
		return 100;
	if(singleCellVoltage<=3.61)
		return 0;

//	y = -2.3377x^3 + 24.98x^2 - 86.314x + 96.045
	percent = -2.3377*singleCellVoltage*singleCellVoltage*singleCellVoltage
			+ 24.98*singleCellVoltage*singleCellVoltage
			- 86.314*singleCellVoltage + 96.045;

	percentNum = int(percent*100);

	return percentNum;		
}

////////////////////////////////////////////////////////////显示电量///////////////////////////////////////////////////////////////////////////
void CDlgDemoDlg::showVoltagePicture()
{
	//	HBITMAP hBitmap; 
	
	GetSystemPowerStatus(&SystemPowerStatus);
	
	int padPercent = SystemPowerStatus.BatteryLifePercent;
	int ctrlBoxPercent = Voltage2Volume(ReceiveData.allData.ctrlBoxPower,3);
	int leftPercent = Voltage2Volume(ReceiveData.allData.leftPower,7);
	int rightPercent = Voltage2Volume(ReceiveData.allData.rightPower,7);

	//显示Pad电量
	switch( padPercent/20 )
	{
		//0~20   show 20%
	case 0:
		hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP20)); 
		m_padVol.SetBitmap(hBitmap);                 /***IDB_BITMAP1是你载入资源中位图的ID号***/
		break;
		//20~40     show 40%
	case 1:
		hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP40)); 
		m_padVol.SetBitmap(hBitmap);                 /***IDB_BITMAP1是你载入资源中位图的ID号***/
		break;
		//40~60     show 60%
	case 2:
		hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP60)); 
		m_padVol.SetBitmap(hBitmap);                 /***IDB_BITMAP1是你载入资源中位图的ID号***/
		break;
		//60~80     show 80%
	case 3:
		hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP80)); 
		m_padVol.SetBitmap(hBitmap);                 /***IDB_BITMAP1是你载入资源中位图的ID号***/
		break;
		//80~100     show 100%
	case 4:
	case 5:
		hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP100)); 
		m_padVol.SetBitmap(hBitmap);                 /***IDB_BITMAP1是你载入资源中位图的ID号***/

		break;
		
	}
	DeleteObject(hBitmap);

	if(m_bSerialPortOpened)
	{
		//显示控制器电量
		switch( ctrlBoxPercent/20 )
		{
			//0~20   show 20%
		case 0:
			hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP20)); 
			m_ctrlBoxVol.SetBitmap(hBitmap);                 /***IDB_BITMAP1是你载入资源中位图的ID号***/
			break;
			//20~40     show 40%
		case 1:
			hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP40)); 
			m_ctrlBoxVol.SetBitmap(hBitmap);                 /***IDB_BITMAP1是你载入资源中位图的ID号***/
			break;
			//40~60     show 60%
		case 2:
			hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP60)); 
			m_ctrlBoxVol.SetBitmap(hBitmap);                 /***IDB_BITMAP1是你载入资源中位图的ID号***/
			break;
			//60~80     show 80%
		case 3:
			hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP80)); 
			m_ctrlBoxVol.SetBitmap(hBitmap);                 /***IDB_BITMAP1是你载入资源中位图的ID号***/
			break;
			//80~100     show 100%
		case 4:
			hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP100)); 
			m_ctrlBoxVol.SetBitmap(hBitmap);                 /***IDB_BITMAP1是你载入资源中位图的ID号***/
			break;
			
		}
		DeleteObject(hBitmap);

#ifdef  SHOW_LEFT_RIGHT_POWER
		//显示左电池电量
		switch( leftPercent/20 )
		{
			//0~20   show 20%
		case 0:
			hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP20)); 
			m_leftVol.SetBitmap(hBitmap);                 /***IDB_BITMAP1是你载入资源中位图的ID号***/
			break;
			//20~40     show 40%
		case 1:
			hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP40)); 
			m_leftVol.SetBitmap(hBitmap);                 /***IDB_BITMAP1是你载入资源中位图的ID号***/
			break;
			//40~60     show 60%
		case 2:
			hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP60)); 
			m_leftVol.SetBitmap(hBitmap);                 /***IDB_BITMAP1是你载入资源中位图的ID号***/
			break;
			//60~80     show 80%
		case 3:
			hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP80)); 
			m_leftVol.SetBitmap(hBitmap);                 
			break;
			//80~100     show 100%
		case 4:
			hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP100)); 
			m_leftVol.SetBitmap(hBitmap);                 /***IDB_BITMAP1是你载入资源中位图的ID号***/
			break;
			
		}
		DeleteObject(hBitmap);
		//显示右电池电量
		switch( rightPercent/20 )
		{
			//0~20   show 20%
		case 0:
			hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP20)); 
			m_rightVol.SetBitmap(hBitmap);                 /***IDB_BITMAP1是你载入资源中位图的ID号***/
			break;
			//20~40     show 40%
		case 1:
			hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP40)); 
			m_rightVol.SetBitmap(hBitmap);                 /***IDB_BITMAP1是你载入资源中位图的ID号***/
			break;
			//40~60     show 60%
		case 2:
			hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP60)); 
			m_rightVol.SetBitmap(hBitmap);                 /***IDB_BITMAP1是你载入资源中位图的ID号***/
			break;
			//60~80     show 80%
		case 3:
			hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP80)); 
			m_rightVol.SetBitmap(hBitmap);                 /***IDB_BITMAP1是你载入资源中位图的ID号***/
			break;
			//80~100     show 100%
		case 4:
			hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP100)); 
			m_rightVol.SetBitmap(hBitmap);                 /***IDB_BITMAP1是你载入资源中位图的ID号***/
			break;
			
		}
		DeleteObject(hBitmap);
#endif

	}
	else
	{			
		hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP20)); 
		m_ctrlBoxVol.SetBitmap(hBitmap);                 /***IDB_BITMAP1是你载入资源中位图的ID号***/
		
		//	hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP20)); 
		m_rightVol.SetBitmap(hBitmap);                 /***IDB_BITMAP1是你载入资源中位图的ID号***/
		
		//	hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP20)); 
		m_leftVol.SetBitmap(hBitmap);                 /***IDB_BITMAP1是你载入资源中位图的ID号***/

		DeleteObject(hBitmap); //release resource
		
	}
	
	
	
//显示充电保护屏

	//保存充电状态
	//	bIsCharging=SystemPowerStatus.ACLineStatus;
	
	//根据充电情况显示充电动态图
	if(bIsCharging)
	{
		ShowGIF(1,SW_SHOW);
		ShowGIF(2,SW_HIDE);

	}
	else 
	{

		ShowGIF(1,SW_HIDE);
	}
	
}

/////////////////////////////////////////////////////////////////////电量显示完成////////////////////////////////////////////////////////////

//////////////////////显示速度，工作模式，红外开关，通道 状态///////////////////////////////
void CDlgDemoDlg::showSWI()
{

	//	ReceiveData.allData.statusByte_1=0x53;
	//	ReceiveData.allData.statusByte_2=0x80;
	int speed    =   (ReceiveData.allData.statusByte_2 & (0x03<<6)) >> 6;
	int workMode =   (ReceiveData.allData.statusByte_1 & (0x03<<6)) >> 6;
	int infrared =   (ReceiveData.allData.statusByte_1 & (0x03<<4)) >> 4;
	int channel  =   (ReceiveData.allData.statusByte_1 & (0x0f<<0)) >> 0;
	//	int channel  =(int)SendData[4];


	//	HBITMAP hBitmap; 
	
	switch(speed)
	{
	case 0:
		hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP_v1)); 
		break;
	case 1:
		hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP_v2)); 
		break;
	case 2:
		hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP_v3)); 
		break;
	case 3:
		hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP_v4)); 
		break;
	default:
		hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP_v1)); 
		break;

	}
	m_speed.SetBitmap(hBitmap);  
	DeleteObject(hBitmap);

#ifdef SHOW_AUTOMODE
	switch(workMode)
	{
	case 0:
		hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP_MANUMODE));		
		break;
	case 1:
		hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP_AUTOMODE));		
		break;
	default:
		hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP_MANUMODE));		
		break;
	}
	m_workMode.SetBitmap(hBitmap); 
	DeleteObject(hBitmap);

#endif

	//使用红外指示功能
#ifdef USE_INFRARED   
	
	switch(infrared)
	{
	case 0:
		hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP_OFF)); 					
		break;
	case 1:
		hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP_ON)); 					
		break;
	default:
		hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP_OFF)); 					
		break;
	}
	m_infrared.SetBitmap(hBitmap);  		
	DeleteObject(hBitmap);
#endif

	//使用通道改变功能
#ifdef USE_CHANGE_CHANNEL

	switch(channel)
	{
	case 0:
		hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_CHANNEL1));  
		break;
	case 1:
		hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_CHANNEL2));
		break;
	case 2:
		hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_CHANNEL3));
		break;
	case 3:
		hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_CHANNEL4));		
		break;
	default:
		hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_CHANNEL1));		
		break;
	}
	m_channel.SetBitmap(hBitmap); 
	DeleteObject(hBitmap);
#endif



	
}

////////////////////////显示蓝牙状态//////////////////////
void CDlgDemoDlg::ShowBluetooth()
{
	BOOL bluetoothStatus=m_bSerialPortOpened;
//	bluetoothStatus=true;
	switch(bluetoothStatus)
	{
	case false:

		hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BLUETOOTH_OFF));  
		break;
	case true:
		hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BLUETOOTH_ON));
		break;
	default:
		hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BLUETOOTH_OFF));		
		break;

	}
	m_bluetooth.SetBitmap(hBitmap); 
	DeleteObject(hBitmap);
}

void CDlgDemoDlg::ShowCompass()
{
		//更新罗盘
	static iangle=0;
	if(iangle>360)
		iangle=0;
	else
		iangle+=2;
	//	if(iangle%20==0)

	//如果使用GDI
	//	m_compass.ClearScreen();

	//	m_compass.DrawFan(iangle);
	//如果使用3DS文件
	int rotateAngle=ReceiveData.allData.azimuthAngle;

#ifdef USE_3DS_COMPASS
	m_compass.SetRotateAngle(rotateAngle);
	m_compass.Render();
#endif
}


/////////////////////////////显示GIF/////////////////////////////////////////////
void CDlgDemoDlg::ShowGIF(int GIFnum,int SWMode)
{
	//保证如果SWMode有变化时则ShowWindow
	static int prevMode1=-1;
	static int prevMode2=-1;
	
	switch(GIFnum)
	{
	case 1:
		if(prevMode1!=SWMode)
		{
			prevMode1=SWMode;
			m_chargeGIF.ShowWindow(SWMode);
			//	AfxMessageBox("m_chargeGIF test");
		}
		break;

	case 2:
		if(prevMode2!=SWMode)
		{
			prevMode2=SWMode;
			m_loadDevicesGIF.ShowWindow(SWMode);
			//	AfxMessageBox("m_loadDevicesGIF test");
		}
		break;
	default:
		break;
	}

	
}

/////////////////////////////////////////////开始初始化界面显示/////////////////////////////////////////////////////
void CDlgDemoDlg::InitWidget()
{

///////////////////////////////////////////////////////////////////////////////////////////////////
	//电量指示不使用精度条，而是使用图片的形式
	//初始化电量显示进度条
	m_rightPower.SetRange(0,99);
	m_padPower.SetRange(0,99);
	m_leftPower.SetRange(0,99);
	m_ctrlBoxPower.SetRange(0,99);
	
	m_rightPower.SetColor(RGB(0,200,0),RGB(200,200,200),RGB(200,0,0),RGB(0,0,0));
	
	m_rightPower.SetPos(0);
	
	this->m_padPower.MoveWindow(112,17,96,16);
	this->m_ctrlBoxPower.MoveWindow(112,45,96,16);
	this->m_leftPower.MoveWindow(352,17,96,16);
	this->m_rightPower.MoveWindow(352,45,96,16);

	
	//暂时隐藏  使用PIC
	m_padPower.ShowWindow(SW_HIDE);
	m_ctrlBoxPower.ShowWindow(SW_HIDE);
	m_leftPower.ShowWindow(SW_HIDE);
	m_rightPower.ShowWindow(SW_HIDE);
////////////////////////////////////////////////////////////////////////////////////////////////////
	

	// 设置电量图标部件位置和尺寸
	this->m_padVol.MoveWindow(140,14,76,22);
	this->m_ctrlBoxVol.MoveWindow(544,14,76,22);

	this->m_leftVol.MoveWindow(538,14,76,22);
	this->m_rightVol.MoveWindow(734,14,76,22);


	// 设置速度，工作模式，红外，通道 显示位置和尺寸
	this->m_speed.MoveWindow(856,12,25,25);
	this->m_workMode.MoveWindow(1016,12,60,25);

	this->m_infrared.MoveWindow(1100,12,25,25);
	this->m_channel.MoveWindow(1202,12,60,25);
	//设置蓝牙标志的显示位置和尺寸
	this->m_bluetooth.MoveWindow(1187,8,33,37);
//没有使用通道改变按钮供功能，则隐藏部件
#ifndef USE_CHANGE_CHANNEL
	m_channel.ShowWindow(SW_HIDE);
#endif

#ifndef USE_INFRARED
	m_infrared.ShowWindow(SW_HIDE);
#endif
	
#ifndef SHOW_LEFT_RIGHT_POWER
	m_leftVol.ShowWindow(SW_HIDE);
	m_rightVol.ShowWindow(SW_HIDE);
#endif
	
#ifndef SHOW_AUTOMODE
	m_workMode.ShowWindow(SW_HIDE);
#endif

	//设置罗盘显示位置和尺寸
	this->m_compass.MoveWindow(17,621,130,130);
//没有使用罗盘显示功能，则隐藏部件
#ifndef USE_3DS_COMPASS
	m_compass.ShowWindow(SW_HIDE);
#endif

	
//初始化预览区窗口	
	pvw=new CChannelWnd;
	CRect rc(VideoArea_X, VideoArea_Y, VideoArea_W+VideoArea_X, VideoArea_H+VideoArea_Y	);	
	pvw->Create(100,rc,this);
	pvwMask =new  CChannelWnd;
	CRect rcMask(VideoArea_X, VideoArea_Y, VideoArea_W+VideoArea_X, VideoArea_H+VideoArea_Y);
	pvwMask->Create(110,rcMask,this);
	pvwMask->SetBKBmp(IDB_BITMAP);
	
	
	//初始化充电动态图 和 加载资源动态图
	m_chargeGIF.MoveWindow(VideoArea_X-1, VideoArea_Y-1, VideoArea_W+VideoArea_X+2, VideoArea_H+VideoArea_Y+2);
	m_loadDevicesGIF.MoveWindow(VideoArea_X-1, VideoArea_Y-1, VideoArea_W+VideoArea_X+2, VideoArea_H+VideoArea_Y+2);
	
	if (m_chargeGIF.Load(MAKEINTRESOURCE(IDR_CHARGEGIF),_T("Gif")))
		m_chargeGIF.Draw();		
	if (m_loadDevicesGIF.Load(MAKEINTRESOURCE(IDR_LOADDEVICES),_T("Gif")))
		m_loadDevicesGIF.Draw();






	//调试打开关闭资源设备
#ifdef OPEN_DEV_DEBUG
	m_closeDevBtn.MoveWindow(350,0,80,30);
	m_openDevBtn.MoveWindow(450,0,80,30);

#else 
	//初始化打开资源和关闭资源 按钮
	m_closeDevBtn.ShowWindow(SW_HIDE);
	m_openDevBtn.ShowWindow(SW_HIDE);

#endif




	//初始化预览区边框
	m_PrvHwnd.ShowWindow(SW_HIDE);
	
	//隐藏接收数据编辑框，该编辑框仅用于调试串口
#ifdef PORT_DEBUG
	//	this->GetDlgItem(IDC_EDIT)->ShowWindow(SW_SHOW);
	this->GetDlgItem(IDC_EDIT)->MoveWindow(0,0,300,50);
#else
	this->GetDlgItem(IDC_EDIT)->ShowWindow(SW_HIDE);
#endif
	//	this->GetDlgItem(IDC_EDIT)->ShowWindow(false);



	//主界面设置 设置最大化
	//	this->ShowWindow(SW_SHOWMAXIMIZED);
	//得到屏幕的大小
	int   cx   =   GetSystemMetrics(   SM_CXSCREEN   );   
	int   cy   =   GetSystemMetrics(   SM_CYSCREEN   );

//	this->MoveWindow(0,0,cx,cy);
	this->MoveWindow(0,0,1280,800);   //在Xp笔记本上运行

	CString title="CRAB中国海关";
	SetWindowText(title);



	//拍照按钮设置
	m_snapBtn.SetWindowText("");   //清空按钮上的文字
	m_snapBtn.SetAlign(2);
	m_snapBtn.SetIcon(IDI_SNAPBTN2,IDI_SNAPBTN1);
	m_snapBtn.SetFlat(true);
	m_snapBtn.DrawTransparent(TRUE);
	m_snapBtn.MoveWindow(11,159,143,137);

	//录像按钮设置
	m_recordBtn.SetWindowText("");   //清空按钮上的文字
	m_recordBtn.SetAlign(2);
	m_recordBtn.SetIcon(IDI_RECORDBTN2,IDI_RECORDBTN1);
	m_recordBtn.SetFlat(true);
	m_recordBtn.DrawTransparent(TRUE);
	m_recordBtn.MoveWindow(11,336,143,137);

	//设置按钮设置
	m_settingBtn.SetWindowText("");   //清空按钮上的文字
	m_settingBtn.SetAlign(2);
	m_settingBtn.SetIcon(IDI_SETTINGBTN2,IDI_SETTINGBTN1);
	m_settingBtn.SetFlat(true);
	m_settingBtn.DrawTransparent(TRUE);
	m_settingBtn.MoveWindow(11,513,143,137);

	//查看日志按钮设置
	m_txtViewerBtn.SetWindowText("");   //清空按钮上的文字
	m_txtViewerBtn.SetAlign(2);
	m_txtViewerBtn.SetIcon(IDI_TXTVIEWERBTN1,IDI_TXTVIEWERBTN1);
	m_txtViewerBtn.SetFlat(true);
	m_txtViewerBtn.DrawTransparent(TRUE);
	m_txtViewerBtn.MoveWindow(1126,90,143,137);

//没有使用改变通道按钮功能，则隐藏部件
#ifdef USE_CHANGE_CHANNEL	
	//查看通道切换按钮设置
	m_channelBtn.SetWindowText("");   //清空按钮上的文字
	m_channelBtn.SetAlign(2);
	m_channelBtn.SetIcon(IDI_CHANNELSWITCH2,IDI_CHANNELSWITCH1);
	m_channelBtn.SetFlat(true);
	m_channelBtn.DrawTransparent(TRUE);
	m_channelBtn.MoveWindow(1126,90,143,137);
#else
	m_channelBtn.ShowWindow(SW_HIDE);
#endif

	//查看图片按钮设置
	m_picViewerBtn.SetWindowText("");   //清空按钮上的文字
	m_picViewerBtn.SetAlign(2);
	m_picViewerBtn.SetIcon(IDI_PICVIEWERBTN2,IDI_PICVIEWERBTN1);
	m_picViewerBtn.SetFlat(true);
	m_picViewerBtn.DrawTransparent(TRUE);
	m_picViewerBtn.MoveWindow(1126,159,143,137);

	//视频回放按钮设置
	m_videoPlayerBtn.SetWindowText("");   //清空按钮上的文字
	m_videoPlayerBtn.SetAlign(2);
	m_videoPlayerBtn.SetIcon(IDI_VIDEOPLAYERBTN2,IDI_VIDEOPLAYERBTN1);
	m_videoPlayerBtn.SetFlat(true);
	m_videoPlayerBtn.DrawTransparent(TRUE);
	m_videoPlayerBtn.MoveWindow(1126,336,143,137);

	//退出按钮设置
	m_exitBtn.SetWindowText("");   //清空按钮上的文字
	m_exitBtn.SetAlign(2);
	m_exitBtn.SetIcon(IDI_EXITBTN2,IDI_EXITBTN1);
	m_exitBtn.SetFlat(true);
	m_exitBtn.DrawTransparent(TRUE);
	m_exitBtn.MoveWindow(1126,513,143,137);


	//隐藏   暂停,打开,文本查看按钮
	m_pauseBtn.ShowWindow(SW_HIDE);
	m_openBtn.ShowWindow(SW_HIDE);



	m_txtViewerBtn.ShowWindow(SW_HIDE);




	//设置窗口总在最前面
#ifdef WNDTOPMOST
	ShowWindow(SW_SHOW);
	UpdateWindow();
	SetWindowPos(&CWnd::wndTopMost,0,0,0,0,
				SWP_NOMOVE|SWP_NOSIZE|SWP_NOACTIVATE);
#endif
	///////////////////////////////////////////////////////


	Invalidate(true);
	UpdateWindow();


	
}




/////////////////////////////////////////打开回放数据窗口///////////////////////////////////////////////////////////


void CDlgDemoDlg::OnBtnTxtviewer() 
{
	// TODO: Add your control notification handler code here

	TxtViewerDlg dlg;
	dlg.DoModal();

	
}

void CDlgDemoDlg::OnBtnPicviewer() 
{
	// TODO: Add your control notification handler code here
	PicViewerDlg dlg;
	dlg.DoModal();
	
}

void CDlgDemoDlg::OnBtnVideoplayer() 
{
	// TODO: Add your control notification handler code here
	VideoPlayerDlg dlg;
	dlg.DoModal();
	
}

///////////////////////////////////////////////////切换通道按钮////////////////////////////////////////////////////////////
void CDlgDemoDlg::OnChannelbtn() 
{
	// TODO: Add your control notification handler code here
	Sleep(100);
	SetCursorPos( 0,0); //强制将鼠标移动到(0,0)的坐标从而避免了总是显示按下的状态
	static int clickTimes=0;

	clickTimes++;

	if(clickTimes>=4)
		clickTimes=0;

	SendData[4]=(unsigned char)clickTimes;    //通道数

	
	
}

//////////////////////////////////////////////////////////////set OSD///////////////////////////////////////////////////////////////////////////

void CDlgDemoDlg::ShowOSD()
{
	int screenMode  =  (ReceiveData.allData.statusByte_2 & (0x03<<4)) >> 4;
	screenMode=1;  //just for test
	static int screenModeLast=-1;

	//如果分屏模式没有变化就直接退出，当然第一次不退出
//	if( (screenModeLast==screenMode) && (screenModeLast!=-1) )
//	{
//		return ;
//	}
	screenModeLast=screenMode;

	dwCard=0;
	//设置时间显示的坐标
	TosdInfo[dwCard].TimeX=5;
	TosdInfo[dwCard].TimeY=5;

	//设置字体的大小
	TosdInfo[dwCard].TimeFontSizeVal=20;
	TosdInfo[dwCard].TxtFontSizeVal[0]=20;
	TosdInfo[dwCard].TxtFontSizeVal[1]=20;
	//设置字体颜色
	TosdInfo[dwCard].TxtColor[0]=RGB(0,255,0);
	TosdInfo[dwCard].TxtColor[1]=RGB(0,255,0);
	TosdInfo[dwCard].TimeColor=RGB(0,255,0);
	TosdInfo[dwCard].BackColor =RGB(0,0,0);
	//设置显示的文本内容	
	TosdInfo[dwCard].Osd_Txtstring[0]="行车画面";
	TosdInfo[dwCard].Osd_Txtstring[1]="观测画面";
	//设置字体的格式
	TosdInfo[dwCard].TxtFont[0]=	TEXT("Arial");
	TosdInfo[dwCard].TxtFont[1]=	TEXT("Arial");
	TosdInfo[dwCard].TimeFont=TEXT("Arial");

		//根据分屏模式设置OSD显示模式
	switch(screenMode)
	{
	//行车画面
	case 1:
		//设置文本1和文本2的显示坐标
		TosdInfo[dwCard].TxtPlaceX[0]=670;
		TosdInfo[dwCard].TxtPlaceY[0]=5;
		
		//设置文本1显示参数
		
		m_DeviceControl.SetOSDPara(CDlgDemoDlg::DeviceInfo[dwCard].dwChannelHandle,
			1,
			0,
			TosdInfo[dwCard].Osd_Txtstring[0],
			TosdInfo[dwCard].TxtPlaceX[0],
			TosdInfo[dwCard].TxtPlaceY[0],
			TosdInfo[dwCard].TxtFontSizeVal[0],
			TosdInfo[dwCard].TxtFont[0],
			TosdInfo[dwCard].TxtColor [0],
			TosdInfo[dwCard].BackColor ,
			true,
			255);
		m_DeviceControl.StartOsd (CDlgDemoDlg::DeviceInfo[dwCard].dwChannelHandle,1,0,true);		
		break;
		//观测画面
	case 2:
		TosdInfo[dwCard].TxtPlaceX[1]=670;
		TosdInfo[dwCard].TxtPlaceY[1]=5;
		//设置文本2显示参数
		m_DeviceControl.SetOSDPara(CDlgDemoDlg::DeviceInfo[dwCard].dwChannelHandle,
			1,
			1,
			TosdInfo[dwCard].Osd_Txtstring[1],
			TosdInfo[dwCard].TxtPlaceX[1],
			TosdInfo[dwCard].TxtPlaceY[1],
			TosdInfo[dwCard].TxtFontSizeVal[1],
			TosdInfo[dwCard].TxtFont[1],
			TosdInfo[dwCard].TxtColor [1],
			TosdInfo[dwCard].BackColor ,
			true,
			255);
		m_DeviceControl.StartOsd (CDlgDemoDlg::DeviceInfo[dwCard].dwChannelHandle,1,0,true);
		break;
		//上下分屏画面
	case 3:
		//设置文本1和文本2的显示坐标
		TosdInfo[dwCard].TxtPlaceX[0]=670;
		TosdInfo[dwCard].TxtPlaceY[0]=215;
		TosdInfo[dwCard].TxtPlaceX[1]=670;
		TosdInfo[dwCard].TxtPlaceY[1]=455;
		
		//设置文本1显示参数
		
		m_DeviceControl.SetOSDPara(CDlgDemoDlg::DeviceInfo[dwCard].dwChannelHandle,
			1,
			0,
			TosdInfo[dwCard].Osd_Txtstring[0],
			TosdInfo[dwCard].TxtPlaceX[0],
			TosdInfo[dwCard].TxtPlaceY[0],
			TosdInfo[dwCard].TxtFontSizeVal[0],
			TosdInfo[dwCard].TxtFont[0],
			TosdInfo[dwCard].TxtColor [0],
			TosdInfo[dwCard].BackColor ,
			true,
			255);
		m_DeviceControl.StartOsd (CDlgDemoDlg::DeviceInfo[dwCard].dwChannelHandle,1,0,true);
		
		//设置文本2显示参数
		m_DeviceControl.SetOSDPara(CDlgDemoDlg::DeviceInfo[dwCard].dwChannelHandle,
			1,
			1,
			TosdInfo[dwCard].Osd_Txtstring[1],
			TosdInfo[dwCard].TxtPlaceX[1],
			TosdInfo[dwCard].TxtPlaceY[1],
			TosdInfo[dwCard].TxtFontSizeVal[1],
			TosdInfo[dwCard].TxtFont[1],
			TosdInfo[dwCard].TxtColor [1],
			TosdInfo[dwCard].BackColor ,
			true,
			255);
		m_DeviceControl.StartOsd (CDlgDemoDlg::DeviceInfo[dwCard].dwChannelHandle,1,1,true);

		break;
	default:
		break;
	}
		

	//以下显示均是透明显示
	//设置时间显示参数
	m_DeviceControl.SetOSDPara(CDlgDemoDlg::DeviceInfo[dwCard].dwChannelHandle,
		0,
		0,
		TosdInfo[dwCard].Osd_Txtstring[1],
		TosdInfo[dwCard].TimeX,
		TosdInfo[dwCard].TimeY,
		TosdInfo[dwCard].TimeFontSizeVal,
		TosdInfo[dwCard].TimeFont,
		TosdInfo[dwCard].TimeColor,
		TosdInfo[dwCard].BackColor ,
		true,
		255);
	m_DeviceControl.StartOsd(CDlgDemoDlg::DeviceInfo[dwCard].dwChannelHandle,0,0,true);





}

 
/////////////////////////////////////////////////////////end of OSD setting ///////////////////////////////////////////////////////////////////////////////////

//设置存储数据路径
void CDlgDemoDlg::SetRootPath()
{
	int diskNum=0;
	char  szDrives[128];//临时变量
	diskNum=GetLogicalDriveStrings(sizeof(szDrives), szDrives);   //获取根目录
	diskNum/=4;
	//	CString fileName;
	switch(diskNum)
	{
	case 1:
		RootPath="C:\\CRABUserData";
		break;
	case 2:
		RootPath="D:\\CRABUserData";
		break;
	default:
		break;		
	}
	//	AfxMessageBox("您的用户数据存储于： "+RootPath);
}

////////////////////////////////////////打开和关闭外部程序//////////////////////////////////////////////
void CDlgDemoDlg::InitVLC()
{
	//	SHELLEXECUTEINFO   ShExecInfo   =   {0};
    ShExecInfo.cbSize   =   sizeof(SHELLEXECUTEINFO);
    ShExecInfo.fMask   =   SEE_MASK_NOCLOSEPROCESS;
    ShExecInfo.hwnd   =   NULL;
    ShExecInfo.lpVerb   =   NULL;
    ShExecInfo.lpFile   =   "vlc.exe ";
    ShExecInfo.lpParameters   =   " ";
    ShExecInfo.lpDirectory   =   NULL;
    ShExecInfo.nShow   =   SW_SHOW;
    ShExecInfo.hInstApp   =   NULL;
    ShellExecuteEx(&ShExecInfo);

	//以下代码可获取窗口句柄
//	HWND hWnd; 
//	hWnd=::FindWindow("vlc",NULL);
	//	hWnd=m_hWnd;
//	::ShowWindow(hWnd, SW_HIDE);
//	::MoveWindow(hWnd,0,0,50,50,true);
	
//    Sleep(2000); //延时3秒后关闭刚才打开的程序
//    TerminateProcess(ShExecInfo.hProcess,INFINITE);

	SetTimer(6,500,NULL);



}


/////////////////////////////////////////////////////////////////////////////////////////////////////////

