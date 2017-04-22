// dlgDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Winuser.h"
#include "dlgDemo.h"
#include "dlgDemoDlg.h"
//#include "ColorPropertyDlg.h"
//#include  "CodecSettingFrm.h"
//#include "CVideoDenoiseFrm.h"
//#include "OSDSetting.h"
#include "DeviceControl.h"
//#include "ChannelWnd.h"



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
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_fileImg = NULL;
	m_bufImg = NULL;
}

void CDlgDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDemoDlg)
	DDX_Control(pDX, IDC_ST_DISPLAY, m_PrvHwnd);
	DDX_Control(pDX, IDC_BT_CALLBACK, m_bt_CallBack);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CDlgDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

//	ON_UPDATE_COMMAND_UI(ID_Deinterlace_GOOD, OnUpdateDeinterlaceGOOD)
//	ON_COMMAND(ID_Deinterlace_STD, OnDeinterlaceSTD)
//	ON_UPDATE_COMMAND_UI(ID_Deinterlace_STD, OnUpdateDeinterlaceSTD)
//	ON_BN_CLICKED(IDC_COLOR_PROPERTY_BUTTON, OnColorPropertyButton)
//	ON_BN_CLICKED(IDC_BUTTON_GetBuf, OnBUTTONGetBuf)
//	ON_BN_CLICKED(IDC_BUTTON_SNAP, OnButtonSnap)
//	ON_BN_CLICKED(IDC_BUTTON_CALLSNAP, OnButtonCallsnap)
//	ON_BN_CLICKED(IDC_BUTTON_EXIT, OnButtonExit)
//	ON_BN_CLICKED(IDC_BT_RECORD, OnBtRecord)
//	ON_BN_CLICKED(IDC_BUTTON_CODEC, OnButtonCodec)
//	ON_COMMAND(ID_DENOISE_STD, OnDenoiseStd)
//	ON_BN_CLICKED(IDC_BUTTON_PAUSEREC, OnButtonPauserec)
//	ON_BN_CLICKED(IDC_OSDSET_BUTTON, OnOsdsetButton)
//	ON_WM_DESTROY()
//	ON_UPDATE_COMMAND_UI(ID_SIZE_960H, OnUpdateSize960h)
//	ON_UPDATE_COMMAND_UI(ID_SIZE_768, OnUpdateSize768)
//	ON_COMMAND(ID_SIZE_768, OnSize768)
//	ON_COMMAND(ID_SIZE_960H, OnSize960h)
//	ON_COMMAND(ID_Deinterlace_LowCpu, OnDeinterlaceLowCpu)


//	ON_UPDATE_COMMAND_UI(ID_Deinterlace_LowCpu, OnUpdateDeinterlaceLowCpu)
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

	////关联菜单项
	/*

	CMenu menu;
	menu.LoadMenu(IDR_MENU1);
	SetMenu(&menu);
	menu.Detach();

	///////////////////////////////////
		PauseRec=false;
		CodecSet=false;
	    RecOK=false;
	    bCallback=false;
	    m_StartPreview=1;
	    m_VidStandard=1;
        m_Width=0;
    	m_Height=0;
	    m_Colorspace=0;
       m_FrameRate=0;

	   //menu 状态
		AfxGetMainWnd()->GetMenu()->CheckMenuItem(ID_SIZE_D1,MF_CHECKED);
		AfxGetMainWnd()->GetMenu()->CheckMenuItem(ID_STAND_PAL,MF_CHECKED);
		AfxGetMainWnd()->GetMenu()->CheckMenuItem(ID_SOUR_AV1,MF_CHECKED);

		AfxGetMainWnd()->GetMenu()->CheckMenuItem(ID_Deinterlace_LowCpu,MF_CHECKED);
		AfxGetMainWnd()->GetMenu()->CheckMenuItem(ID_SIZE_D1,MF_CHECKED);

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


		CString StrPic; 
		GetPrivateProfileString("SystemSetting","PicSaveParh","d:\\Pic",StrPic.GetBuffer(128),128,strIniFile);
		StrPic.ReleaseBuffer();
		PicSavePath=StrPic;

		CString StrVid; 
		GetPrivateProfileString("SystemSetting","VideoSaveParh","d:\\Video",StrVid.GetBuffer(128),128,strIniFile);
		StrVid.ReleaseBuffer();
		RecSavePath=StrVid;
		if(!SetCurrentDirectory(PicSavePath))
		{
			 CreateDirectory(PicSavePath, NULL);

		}

		if(!SetCurrentDirectory(RecSavePath))
		{
			CreateDirectory(RecSavePath, NULL);
			
		}

	*/
	
		//初始化sdk
		
		m_nDevNum=m_DeviceControl.InitDevice (); //设备数量


		if(m_nDevNum==1) 
		{
		//		::MoveWindow(GetDlgItem(IDC_ST_DISPLAY)->GetSafeHwnd(),0,0,DeviceInfo[dwCard].dwWidth,	DeviceInfo[dwCard].dwHeight,false);
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
		/*
		if ( !CreateWindowClass() )
		{
			::AfxMessageBox(_T("Create windows class false"));
			return FALSE;
		}
	*/
		for (int j=0; j<m_nDevNum; j++)
		{
			OnCreateWindow( 0 );   //指定。。。
			
		
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
				//open device  打开设备
				DeviceInfo[i].dwChannelHandle =m_DeviceControl.OpenDevice (i, &DeviceInfo[i].dwOpenDevState );
			
			
			
			if (DeviceInfo[i].dwOpenDevState!=0)
			{
				::AfxMessageBox("open device false");
				return FALSE;
			}
			else
			{
				
				//connect the device  连接设备
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
																				0,
																				true);	
								//设置隔行算法为标准
	
							m_DeviceControl.EnableDeinterlace(DeviceInfo[i].dwChannelHandle,0,true);

							//设置降噪算法
							DXEnableDenoise(DeviceInfo[i].dwChannelHandle,65);
					
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
	

		DeviceInfo[dwCard].dwDispWidth = 720;
		DeviceInfo[dwCard].dwDispHeight = 576;

		DeviceInfo[dwCard].dwDispPosX = ( DWORD( dwCard % 2 ) ) * ( rcShowWin.Width() / 2 ) + 1; //+ (DWORD)rcShowWin.left;
		DeviceInfo[dwCard].dwDispPosY = ( DWORD( dwCard / 2 ) ) * ( rcShowWin.Height() / 2 );// + //(DWORD)rcShowWin.top;

	}
	/*
	if ( m_nDevNum > 1 && m_nDevNum <= 4 )
	{
		DeviceInfo[dwCard].dwDispWidth = (DWORD)rcShowWin.Width() / 2 ;
		DeviceInfo[dwCard].dwDispHeight = (DWORD)rcShowWin.Height() / 2;
		DeviceInfo[dwCard].dwDispPosX = ( DWORD( dwCard % 2 ) ) * ( rcShowWin.Width() / 2 ) + 1; //+ (DWORD)rcShowWin.left;
		DeviceInfo[dwCard].dwDispPosY = ( DWORD( dwCard / 2 ) ) * ( rcShowWin.Height() / 2 );// + //(DWORD)rcShowWin.top;

	}
	*/

	
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
		 
/*		 
	 
*/


}


//以下都屏蔽
/*

*/

