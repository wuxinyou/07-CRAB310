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
//	#include "DIGITALZOOM.h"





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
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAM);

	m_fileImg = NULL;
	m_bufImg = NULL;
}

void CDlgDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDemoDlg)
	DDX_Control(pDX, IDC_BUTTON_CODEC, m_settingBtn);
	DDX_Control(pDX, IDC_BUTTON_EXIT, m_exitBtn);
	DDX_Control(pDX, IDC_BT_RECORD, m_recordBtn);
	DDX_Control(pDX, IDC_BUTTON_SNAP, m_snapBtn);
	DDX_Control(pDX, IDC_ST_DISPLAY, m_PrvHwnd);
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
	//	ON_BN_CLICKED(IDC_BT_CALLBACK, OnBtCallback)
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
	//	ON_BN_CLICKED(IDC_COLOR_PROPERTY_BUTTON, OnColorPropertyButton)
	ON_BN_CLICKED(IDC_BUTTON_GetBuf, OnBUTTONGetBuf)
	ON_BN_CLICKED(IDC_BUTTON_SNAP, OnButtonSnap)
	//	ON_BN_CLICKED(IDC_BUTTON_CALLSNAP, OnButtonCallsnap)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, OnButtonExit)
	ON_BN_CLICKED(IDC_BT_RECORD, OnBtRecord)
	ON_BN_CLICKED(IDC_BUTTON_CODEC, OnButtonCodec)
	//	ON_COMMAND(ID_DENOISE_STD, OnDenoiseStd)
	ON_BN_CLICKED(IDC_BUTTON_PAUSEREC, OnButtonPauserec)
	//	ON_BN_CLICKED(IDC_OSDSET_BUTTON, OnOsdsetButton)
	ON_WM_DESTROY()
	ON_UPDATE_COMMAND_UI(ID_SIZE_960H, OnUpdateSize960h)
	ON_UPDATE_COMMAND_UI(ID_SIZE_768, OnUpdateSize768)
	ON_COMMAND(ID_SIZE_768, OnSize768)
	ON_COMMAND(ID_SIZE_960H, OnSize960h)
	ON_COMMAND(ID_Deinterlace_LowCpu, OnDeinterlaceLowCpu)
	ON_UPDATE_COMMAND_UI(ID_Deinterlace_LowCpu, OnUpdateDeinterlaceLowCpu)
//	ON_BN_CLICKED(IDC_RADIO_VMR7, OnRadioVmr7)
//	ON_BN_CLICKED(IDC_RADIO_OFFSCREAN, OnRadioOffscrean)
//	ON_BN_CLICKED(IDC_RADIO_VMR9, OnRadioVmr9)
	ON_MESSAGE(WM_CHANNEL_SET_FOCUS,OnChannelSetFocus)
	ON_MESSAGE(WM_LBTNDBLCLK_SHOWWIN, OnLBTNDBClikShowWin)
	//	ON_BN_CLICKED(IDC_ZOOM_BUTTON2, OnZoomButton)
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
	//主界面设置 设置最大化
	this->ShowWindow(SW_SHOWMAXIMIZED);
	CString title="CRAB中国海关";
	SetWindowText(title);
//按钮设置
	//拍照按钮设置
	//m_snapBtn.m_bIsCheckBox=true;
	m_snapBtn.SetAlign(2);
	//	m_btn.SubclassDlgItem(IDC_BTN,this);
	m_snapBtn.SetIcon(IDI_SNAPBTN);

	m_snapBtn.SetFlat(true);
	m_snapBtn.DrawTransparent(TRUE);
//	m_btn.SetColor(CButtonST::BTNST_COLOR_BK_OUT, RGB(208,208,208));
//	m_btn.SetColor(CButtonST::BTNST_COLOR_BK_FOCUS, RGB(20,208,208));
//	m_btn.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, 30);

//	m_snapBtn.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, 30);
	m_snapBtn.MoveWindow(291,796,67,69);

	//录像按钮设置
	m_recordBtn.m_bIsCheckBox=true;
	m_recordBtn.SetAlign(2);
	//	m_btn.SubclassDlgItem(IDC_BTN,this);
	m_recordBtn.SetIcon(IDI_RECORDBTN2,IDI_RECORDBTN1);

	m_recordBtn.SetFlat(true);
//	m_btn.SetColor(CButtonST::BTNST_COLOR_BK_OUT, RGB(208,208,208));
//	m_btn.SetColor(CButtonST::BTNST_COLOR_BK_FOCUS, RGB(20,208,208));
//	m_btn.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, 30);

//	m_snapBtn.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, 30);
	m_recordBtn.MoveWindow(291,700,67,69);
	//设置窗口设置
	m_settingBtn.ShowWindow(SW_HIDE);

	//成员变量初始化
	    RecOK=false;

	////关联菜单项

//	CMenu menu;
//	menu.LoadMenu(IDR_MENU1);
//	SetMenu(&menu);
//	menu.Detach();
//
//	///////////////////////////////////
//		PauseRec=false;
//		CodecSet=false;
//	    RecOK=false;
//	    bCallback=false;
//	    m_StartPreview=1;
//	    m_VidStandard=1;
//        m_Width=0;
//    	m_Height=0;
//	    m_Colorspace=0;
//       m_FrameRate=0;
//	   
//
//	   //menu 状态
//		AfxGetMainWnd()->GetMenu()->CheckMenuItem(ID_SIZE_D1,MF_CHECKED);
//		AfxGetMainWnd()->GetMenu()->CheckMenuItem(ID_STAND_PAL,MF_CHECKED);
//		AfxGetMainWnd()->GetMenu()->CheckMenuItem(ID_SOUR_AV1,MF_CHECKED);
//
//		AfxGetMainWnd()->GetMenu()->CheckMenuItem(ID_Deinterlace_LowCpu,MF_CHECKED);
//		AfxGetMainWnd()->GetMenu()->CheckMenuItem(ID_SIZE_D1,MF_CHECKED);

		//end of menu set
		CString AppPath; 
		//得到当前程序路径
        GetModuleFileName(NULL,AppPath.GetBufferSetLength(1023),1024); 
		AppPath.ReleaseBuffer(); 
        int nPos; 
        nPos = AppPath.ReverseFind('\\'); 
        AppPath = AppPath.Left(nPos); 
		//ini文件存储路径
		strIniFile=AppPath+"\\VCdemoSeting.ini";
	//	PicSavePath="d:\\Pic";
	//	RecSavePath="d:\\Video";

		//WritePrivateProfileString("SystemSetting","PicSaveParh",PicSavePath,strIniFile); 
	//	WritePrivateProfileString("SystemSetting","VideoSaveParh",RecSavePath,strIniFile);

			//get the save picture file path form ini file
		CString StrPic; 
		GetPrivateProfileString("SystemSetting","PicSaveParh","d:\\Pic",StrPic.GetBuffer(128),128,strIniFile);
		StrPic.ReleaseBuffer();
		PicSavePath=StrPic;
			//get the save picture file path form ini file 
		CString StrVid; 
		GetPrivateProfileString("SystemSetting","VideoSaveParh","d:\\Video",StrVid.GetBuffer(128),128,strIniFile);
		StrVid.ReleaseBuffer();
		RecSavePath=StrVid;

				//get the video codec  form ini file 
		CString StrCodec; 
		GetPrivateProfileString("SystemSetting","VideoCodec",X264CODEC_FILTER,StrCodec.GetBuffer(128),128,strIniFile);
		StrCodec.ReleaseBuffer();
		DeviceInfo[dwCard].dwVideoCodecStr=StrCodec;

			
		if(!SetCurrentDirectory(PicSavePath))
		{
			 CreateDirectory(PicSavePath, NULL);

		}

		if(!SetCurrentDirectory(RecSavePath))
		{
			CreateDirectory(RecSavePath, NULL);
			
		}

	///get the preview mode form the ini file
//
//	CString PreviewType; 
//	GetPrivateProfileString("SystemSetting","PreviewMode","VMR7",PreviewType.GetBuffer(128),128,strIniFile);
//	PreviewType.ReleaseBuffer();
//	
//		//////////////设置控件状态值
//	if(	PreviewType=="VMR7")
//	{
//			((CButton*)GetDlgItem(IDC_RADIO_VMR7))->SetCheck(1); 
//			m_PreviewMode=0;
//
//	}
//
//		if(	PreviewType=="OFFScrean")
//	{
//			((CButton*)GetDlgItem(IDC_RADIO_OFFSCREAN))->SetCheck(1); 
//			m_PreviewMode=1;
//	}
//		if(	PreviewType=="VMR9")
//	{
//			((CButton*)GetDlgItem(IDC_RADIO_VMR9))->SetCheck(1); 
//			m_PreviewMode=2;
//	}

	////////////////////////////////////////read inf file end//////////////////

		/////////////////////初始化sdk
		
		m_nDevNum=m_DeviceControl.InitDevice ();
	
		if(m_nDevNum==1) 
		{
				::MoveWindow(GetDlgItem(IDC_ST_DISPLAY)->GetSafeHwnd(),25,125,718,568,false);
		}
		m_PrvHwnd.GetClientRect (&g_rcShowWin);

		

	if(m_nDevNum<1)
	{
		::AfxMessageBox("please check the device valid ");
		return FALSE;
	}
	else
	{
		
		////////////////
		if ( !CreateWindowClass() )
		{
			::AfxMessageBox(_T("Create windows class false"));
			return FALSE;
		}

		for (int j=0; j<m_nDevNum; j++)
		{
			OnCreateWindow( j );
			
		
		}
	
		for (int i=0; i<m_nDevNum; i++)
		{
			DeviceInfo[i].dwWidth =720;
			DeviceInfo[i].dwHeight =576;
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
				return FALSE;
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
					return FALSE;
				} 
				
				
			}

		}
		


	}


	
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

		DeviceInfo[dwCard].dwDispWidth = 718;
		DeviceInfo[dwCard].dwDispHeight = 568;

		DeviceInfo[dwCard].dwDispPosX = 25; //+ (DWORD)rcShowWin.left;
		DeviceInfo[dwCard].dwDispPosY = 125;// + //(DWORD)rcShowWin.top;
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
	

	
		CRect rc(DeviceInfo[dwCard].dwDispPosX,
		DeviceInfo[dwCard].dwDispPosY,
		DeviceInfo[dwCard].dwDispPosX+DeviceInfo[dwCard].dwDispWidth,
			DeviceInfo[dwCard].dwDispPosY+	DeviceInfo[dwCard].dwDispHeight
		);


	CChannelWnd *pvw=new CChannelWnd;
	pvw->Create(100+dwCard,rc,this);

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
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

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
	bitmap.LoadBitmap(IDB_BITMAP1);

	BITMAP bmp;
	bitmap.GetBitmap(&bmp);

	
	
	CDC dcCompatible;
	dcCompatible.CreateCompatibleDC(pDC);
	
	dcCompatible.SelectObject(&bitmap);
	
	CRect rect;
	this->GetClientRect(&rect);
	//pDC->BitBlt(0,0,rect.Width(),rect.Height(),&dcCompatible,0,0,SRCCOPY);    //1:1 贴图
	pDC->StretchBlt(0,0,rect.Width(),rect.Height(),&dcCompatible,0,0,bmp.bmWidth,bmp.bmHeight,SRCCOPY);  //缩放贴图

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
	CString	 strPath;
	CTime time = CTime::GetCurrentTime();
	if (DeviceInfo[dwCard].dwConnectState)
	{
		strPath = PicSavePath+"\\" + time.Format("%Y%m%d-%H%M%S.bmp");
		m_DeviceControl.SnapPicture(DeviceInfo[dwCard].dwChannelHandle,_T(strPath.GetBuffer(strPath.GetLength())),0,NULL);
	//	Sleep(50);
		strPath = PicSavePath+"\\" + time.Format("%Y%m%d-%H%M%S.JPG");
		m_DeviceControl.SnapPicture(DeviceInfo[dwCard].dwChannelHandle,_T(strPath.GetBuffer(strPath.GetLength())),1,NULL);
		
			::AfxMessageBox("Snap jpg ok: "+strPath);
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
		CString	 strPath;

	
	if (DeviceInfo[dwCard].dwConnectState)
	{	
		DXGetVideoPara(DeviceInfo[dwCard].dwChannelHandle,
						DeviceInfo[dwCard].dwVidStandard,
						DeviceInfo[dwCard].dwColorspace,
						DeviceInfo[dwCard].dwWidth,
						DeviceInfo[dwCard].dwHeight,
						DeviceInfo[dwCard].dwFrameRate);
			
				if(!RecOK)
				{
					
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
							strPath = RecSavePath+"\\" + time.Format("%Y%m%d-%H%M%S.mp4");
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
							strPath = RecSavePath+"\\" + time.Format("%Y%m%d-%H%M%S.avi");
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
					::AfxMessageBox("REC OK: "+strPath);
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
