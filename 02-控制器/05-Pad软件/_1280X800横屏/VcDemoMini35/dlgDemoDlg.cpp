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

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

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
	DDX_Control(pDX, IDC_COMPASS, m_compass);
	DDX_Control(pDX, IDC_WORKMODE, m_workMode);
	DDX_Control(pDX, IDC_SPEED, m_speed);
	DDX_Control(pDX, IDC_INFRARED, m_infrared);
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
	ON_BN_CLICKED(IDC_CLOSEDEVBTN, OnClosedevbtn)
	ON_BN_CLICKED(IDC_OPENDEVBTN, OnOpendevbtn)
	ON_BN_CLICKED(IDC_BTN_TXTVIEWER, OnBtnTxtviewer)
	ON_BN_CLICKED(IDC_BTN_PICVIEWER, OnBtnPicviewer)
	ON_MESSAGE(WM_CHANNEL_SET_FOCUS,OnChannelSetFocus)
	ON_MESSAGE(WM_LBTNDBLCLK_SHOWWIN, OnLBTNDBClikShowWin)
	ON_BN_CLICKED(IDC_BTN_VIDEOPLAYER, OnBtnVideoplayer)
	//}}AFX_MSG_MAP

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDemoDlg message handlers



BOOL CDlgDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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
	this->SendData[9]=(char)0X28;
	

	//成员变量初始化
	RecOK=false;
	IsRecord=false;
	bDevIsConnect=false;
	bIsCharging=false;
	ReadyClosePort=0;
	


	

	
	//初始化部件
	InitWidget();
	
	//显示初始化
	showVoltagePicture();
	showSWI();

	m_compass.InitCWnd();



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
	SetTimer(4,200,NULL);
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
	SetTimer(2,30,NULL);//启动定时器1,定时时间是0.1秒
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
	CDialog::OnCancel();

}


void CDlgDemoDlg::OnBtRecord() 
{
	// TODO: Add your control notification handler code here
	
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
	CPoint m_ptOrigin(164,1);
	CPoint point(1116,719);
	dc.Rectangle(CRect(m_ptOrigin,point));

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
		this->SendSerialData();
	
		break;
	case 3:

		showVoltagePicture();
	//	this->UpdatePowerStatus();
		break;
	case 4:
#ifdef USEPORT
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
			if(!bIsCharging)
			{
				ShowGIF(2,SW_SHOW);
				ShowGIF(1,SW_HIDE);

				OnOpendevbtn();
			}
		}
		break;
	case 5:
		//显示机器人的工作状态，包括 速度，工作模式，红外。
		showSWI();
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

	unsigned char tempData[10]={0};
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
	//	m_strReceive.Format("%d %d %d %d %d %d %d %d %d %d %d %d ",QUEUESIZE,tempData[0],tempData[1],tempData[2],tempData[3],tempData[4],tempData[5],tempData[6],tempData[7],tempData[8],tempData[9],check);



			

			if(check==tempData[9])
		{
			for(int icopy=0;icopy<QUEUESIZE-1;icopy++)
			{
				ReceiveData.Data[icopy]=tempData[icopy];
				
			}

			this->ReceiveDataProcess();
		}
		//校验处理完

		//处理接收数据，主要是控制信号的处理
	
		
		
	}
	



	//

//
	//将数据显示在编辑框
		UpdateData(FALSE);  //将接收到的字符显示在接收编辑框中

		
//	for(int j=0;j<QUEUESIZE-1;j++)
//	{
//		unsigned int high4;  //高4位
//		unsigned int low4;  //低4位
//		
//		ch=(unsigned char)ch;
//		//先将高4位和低4位分离
//		high4=ch/16;      //2^4=16
//		low4=ch%16;
//		
//		
//		
//		
//		//Hex转换
//		if(high4>=0 && high4<=9)
//		{
//			high4=48+high4;
//		}
//		else if(high4>=10 && high4<=15)
//		{
//			high4=65+high4-10;
//		}
//		
//		if(low4>=0 && low4<=9)
//		{
//			low4=48+low4;
//		}
//		else if(low4>=10 && low4<=15)
//		{
//			low4=65+low4-10;
//		}
//		
//		
//		
//		m_strReceive +=high4;
//		m_strReceive +=low4;
//		m_strReceive +=32;   //添加空格
//		
//	}
//
//  
//



 
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
		if(lastSendCount>10)  //发送10次以后立即关闭串口和采集卡
		{
			lastSendCount=0;
			OnClosedevbtn();   
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
	
	
	if(bDevIsConnect)
	{
		DXDeviceStop(DeviceInfo[0].dwChannelHandle);
		bDevIsConnect=false;
	}

	if(m_bSerialPortOpened)
	{
		m_SerialPort.ClosePort();//关闭串口
		m_bSerialPortOpened=false;
	}




//	ShowMask();
}


void CDlgDemoDlg::OnOpendevbtn() 
{
	// TODO: Add your control notification handler code here
	if(!bDevIsConnect)
	{
		DXUninitialize();
		InitSDK();
	}
	if(!m_bSerialPortOpened)
	{
#ifdef USEPORT
		AfxMessageBox("UsePort");
		OpenSerialPort(3);  //打开串口
#endif
	}
	
}


//接收数据处理函数
void CDlgDemoDlg::ReceiveDataProcess()
{

	unsigned char snapByte=0;
	unsigned char recordByte=0;
	unsigned char chargeByte=0;

	snapByte   = (ReceiveData.allData.actionCtrl & (0x03<<2)) >> 2;
	recordByte = (ReceiveData.allData.actionCtrl & (0x03<<0)) >> 0;
	chargeByte = (ReceiveData.allData.actionCtrl & (0x03<<4)) >> 4;

	
	static int isSnap=0;
	//判断是否拍照
	if(snapByte==0x01)
	{
		if(isSnap==0)
		{
			OnButtonSnap();	
			isSnap=1;
		}
		
	}
	else
		isSnap=0;
	//判断是否在录像
	static int isRecord=0;
	if(recordByte==0x01)
	{
		if(isRecord==0)
		{
			OnBtRecord();	
			isRecord=1;
		}
	}
	else
		isRecord=0;

	//判断是否准备充电
	if(chargeByte || ReceiveData.allData.actionCtrl==0x08)   //包含测试代码
	{
		ReadyClosePort=0x03;
	}
	
}


BOOL CDlgDemoDlg::OnDeviceChange(UINT nEventType,DWORD dwData)
{
    //DEV_BROADCAST_DEVICEINTERFACE* dbd = (DEV_BROADCAST_DEVICEINTERFACE*) dwData;
//	switch (nEventType)
//	{
//	case DBT_DEVICEREMOVECOMPLETE://移除设备
//
//	//	AfxMessageBox("移除设备");
//
//		break;
//	case DBT_DEVICEARRIVAL://添加设备
//		//	AfxMessageBox("添加设备");
//		//只要有一个设备没有连接就继续连接
//		SetTimer(4,200,NULL);
//		
//		ReadyClosePort=0;
//		
//		break;
//
//	default:
//		break;
//	}
//
//	return TRUE;



	DEV_BROADCAST_HDR* dhr = (DEV_BROADCAST_HDR *)dwData;
	TRACE("--nEventType--:%d\n", nEventType);
	switch (nEventType)
	{
	case DBT_DEVICEREMOVECOMPLETE://移除设备
		TRACE("--DEVICE REMOVE--\n");
#if 1
		if(dhr->dbch_devicetype == DBT_DEVTYP_PORT) 
		{ 
			PDEV_BROADCAST_PORT lpdbv = (PDEV_BROADCAST_PORT)dhr; 
			int len = strlen(lpdbv->dbcp_name);
			CString name(lpdbv->dbcp_name);//COM8
			int port = 3;
			sscanf(name.GetBuffer(0), "COM%d", &port);
		} 
#endif
		TRACE("--DEVICE REMOVE--end\n");
		break;
	case DBT_DEVICEARRIVAL://添加设备
		TRACE("--DEVICE ARRIVAL--\n");
#if 1		
		if(dhr->dbch_devicetype == DBT_DEVTYP_PORT) 
		{ 
			PDEV_BROADCAST_PORT lpdbv = (PDEV_BROADCAST_PORT)dhr; 
			int len = strlen(lpdbv->dbcp_name);
			CString name(lpdbv->dbcp_name);//COM8
			int port = 3;
			sscanf(name.GetBuffer(0), "COM%d", &port);
		} 
#endif
		break;
	default:
		break;
	}

	return TRUE;


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
			m_leftVol.SetBitmap(hBitmap);                 /***IDB_BITMAP1是你载入资源中位图的ID号***/
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
	
}

/////////////////////////////////////////////////////////////////////电量显示完成////////////////////////////////////////////////////////////
//////////////////////显示速度，工作模式，红外开关状态///////////////////////////////
void CDlgDemoDlg::showSWI()
{
	int speed=0;
	int workMode=0;
	int infrared=0;

	//	HBITMAP hBitmap; 
	
	switch(speed)
	{
	case 0:
		hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP_v1)); 
		m_speed.SetBitmap(hBitmap);  

		DeleteObject(hBitmap);
		

		break;
	}
	switch(workMode)
	{
	case 0:
		hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP_AUTOMODE)); 
		m_workMode.SetBitmap(hBitmap);  

		DeleteObject(hBitmap);
		
		break;
	}
	switch(infrared)
	{
	case 0:
		hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP_OFF)); 
		m_infrared.SetBitmap(hBitmap);    
		
		DeleteObject(hBitmap);
					
		break;
	}



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
	m_compass.Render();
	
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

void CDlgDemoDlg::InitWidget()
{
///////////////////////////////////////////////////////////////////////////////////////////////////
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
	this->m_padVol.MoveWindow(150,14,76,22);
	this->m_ctrlBoxVol.MoveWindow(346,14,76,22);
	this->m_leftVol.MoveWindow(548,14,76,22);
	this->m_rightVol.MoveWindow(744,14,76,22);
	// 设置速度，工作模式，红外显示位置和尺寸
	this->m_speed.MoveWindow(894,12,25,25);
	this->m_workMode.MoveWindow(1034,12,60,25);
	this->m_infrared.MoveWindow(1176,12,25,25);
	//设置罗盘显示位置和尺寸
	this->m_compass.MoveWindow(9,621,149,149);

	
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




	//初始化打开资源和关闭资源 按钮
	m_closeDevBtn.ShowWindow(SW_HIDE);
	m_openDevBtn.ShowWindow(SW_HIDE);

	m_closeDevBtn.MoveWindow(500,17,100,20);
	m_openDevBtn.MoveWindow(500,45,100,20);


	//初始化预览区边框
	m_PrvHwnd.ShowWindow(SW_HIDE);
	
	//隐藏接收数据编辑框，该编辑框仅用于调试串口	
	this->GetDlgItem(IDC_EDIT)->ShowWindow(false);



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
	m_snapBtn.SetIcon(IDI_SNAPBTN1,IDI_SNAPBTN1);
	m_snapBtn.SetFlat(true);
	m_snapBtn.DrawTransparent(TRUE);
	m_snapBtn.MoveWindow(11,90,143,137);

	//录像按钮设置
	m_recordBtn.SetWindowText("");   //清空按钮上的文字
	m_recordBtn.SetAlign(2);
	m_recordBtn.SetIcon(IDI_RECORDBTN1,IDI_RECORDBTN1);
	m_recordBtn.SetFlat(true);
	m_recordBtn.DrawTransparent(TRUE);
	m_recordBtn.MoveWindow(11,267,143,137);

	//设置按钮设置
	m_settingBtn.SetWindowText("");   //清空按钮上的文字
	m_settingBtn.SetAlign(2);
	m_settingBtn.SetIcon(IDI_SETTINGBTN1);
	m_settingBtn.SetFlat(true);
	m_settingBtn.DrawTransparent(TRUE);
	m_settingBtn.MoveWindow(11,444,143,137);

	//查看日志按钮设置
	m_txtViewerBtn.SetWindowText("");   //清空按钮上的文字
	m_txtViewerBtn.SetAlign(2);
	m_txtViewerBtn.SetIcon(IDI_TXTVIEWERBTN1);
	m_txtViewerBtn.SetFlat(true);
	m_txtViewerBtn.DrawTransparent(TRUE);
	m_txtViewerBtn.MoveWindow(1126,90,143,137);

	//查看图片按钮设置
	m_picViewerBtn.SetWindowText("");   //清空按钮上的文字
	m_picViewerBtn.SetAlign(2);
	m_picViewerBtn.SetIcon(IDI_PICVIEWERBTN1);
	m_picViewerBtn.SetFlat(true);
	m_picViewerBtn.DrawTransparent(TRUE);
	m_picViewerBtn.MoveWindow(1126,267,143,137);

	//视频回放按钮设置
	m_videoPlayerBtn.SetWindowText("");   //清空按钮上的文字
	m_videoPlayerBtn.SetAlign(2);
	m_videoPlayerBtn.SetIcon(IDI_VIDEOPLAYERBTN1);
	m_videoPlayerBtn.SetFlat(true);
	m_videoPlayerBtn.DrawTransparent(TRUE);
	m_videoPlayerBtn.MoveWindow(1126,444,143,137);

	//退出按钮设置
	m_exitBtn.SetWindowText("");   //清空按钮上的文字
	m_exitBtn.SetAlign(2);
	m_exitBtn.SetIcon(IDI_EXITBTN1);
	m_exitBtn.SetFlat(true);
	m_exitBtn.DrawTransparent(TRUE);
	m_exitBtn.MoveWindow(1126,621,143,137);


	//隐藏暂停和打开按钮
	m_pauseBtn.ShowWindow(SW_HIDE);
	m_openBtn.ShowWindow(SW_HIDE);



//	Invalidate(true);
//	UpdateWindow();


	
}







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

//////////////////////////////////////////////////////////////set OSD///////////////////////////////////////////////////////////////////////////

void CDlgDemoDlg::ShowOSD()
{
	dwCard=0;
	//设置时间显示的坐标
	TosdInfo[dwCard].TimeX=10;
	TosdInfo[dwCard].TimeY=10;
	//设置文本1和文本2的显示坐标
	TosdInfo[dwCard].TxtPlaceX[0]=20;
	TosdInfo[dwCard].TxtPlaceX[1]=30;
	TosdInfo[dwCard].TxtPlaceY[0]=20;
	TosdInfo[dwCard].TxtPlaceY[1]=30;
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
	TosdInfo[dwCard].Osd_Txtstring[0]="wuxinyou";
	TosdInfo[dwCard].Osd_Txtstring[1]="wuxinyou";
	//设置字体的格式
	TosdInfo[dwCard].TxtFont[0]=	TEXT("Arial");
	TosdInfo[dwCard].TxtFont[1]=	TEXT("Arial");
	TosdInfo[dwCard].TimeFont=TEXT("Arial");

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



}

 
/////////////////////////////////////////////////////////end of OSD setting ///////////////////////////////////////////////////////////////////////////////////
