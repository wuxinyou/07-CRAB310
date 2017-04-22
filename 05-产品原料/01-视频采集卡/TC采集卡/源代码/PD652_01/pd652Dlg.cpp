// StreamCatcherDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "pd652.h"
#include "pd652Dlg.h"
#include "VideoQualityDlg.h"
#include "VideoInputDlg.h"
#include "AduioInputDlg.h"

#define COMPILE_MULTIMON_STUBS

#include <MULTIMON.H>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

VOID Dbg( CHAR* pszStr, ... )
{
	char szData[ MAX_PATH ] = "[SC] ";

	va_list args;

	va_start( args, pszStr );

	_vsnprintf( szData + 5, sizeof( szData ) - 1, pszStr, args );

	va_end( args );

    strcat( szData, "\n" );

	OutputDebugString( szData );
}

//  FORMAT CHANGED CALLBACK FUNCTION
//
QRETURN on_process_format_changed( PVOID pDevice, ULONG nVideoInput, ULONG nAudioInput, ULONG nVideoWidth, ULONG nVideoHeight, BOOL bVideoIsInterleaved, double dVideoFrameRate, ULONG nAudioChannels, ULONG nAudioBitsPerSample,  ULONG nAudioSampleFrequency, PVOID pUserData )
{
	Dbg("format changed Detected  \n");

	pd652Dlg* m_pMainDialog = (pd652Dlg*)pUserData;

	if ( m_pMainDialog == NULL ) { return QCAP_RT_OK; }

	if ( m_pMainDialog->GetSafeHwnd() == NULL ) { return QCAP_RT_OK; }

	// OUTPUT FORMAT CHANGED MESSAGE
	//
	CHAR strVideoInput[ MAX_PATH ] = { 0 };

	CHAR strAudioInput[ MAX_PATH ] = { 0 };

	CHAR strFrameType[ MAX_PATH ] = { 0 }; 

    UINT nVH = 0;
            
    if ( nVideoInput == 0 ) { sprintf( strVideoInput, "COMPOSITE" ); }
 	
	if ( nVideoInput == 1 ) { sprintf( strVideoInput, "SVIDEO" ); }
	
	if ( nVideoInput == 2 ) { sprintf( strVideoInput, "HDMI" );}

    if ( nVideoInput == 3 ) { sprintf( strVideoInput, "DVI_D" );}
	
	if ( nVideoInput == 4 ) { sprintf( strVideoInput, "COMPONENTS (YCBCR)" );}
	
	if ( nVideoInput == 5 ) { sprintf( strVideoInput, "DVI_A (RGB / VGA)" );}
	
    if ( nVideoInput == 6 ) { sprintf( strVideoInput, "SDI" );}
	
	if ( nVideoInput == 7 ) { sprintf( strVideoInput, "AUTO" );}

    if ( nAudioInput == 0 ) { sprintf( strAudioInput, "EMBEDDED_AUDIO" );}
	
	if ( nAudioInput == 1 ) { sprintf( strAudioInput, "LINE_IN" );}

    if ( bVideoIsInterleaved == TRUE ) { nVH = nVideoHeight / 2; } else { nVH = nVideoHeight; }

    if ( bVideoIsInterleaved == TRUE ) { sprintf( strFrameType, " I " ); } else { sprintf( strFrameType, " P " ); }
	
	m_pMainDialog->m_strFormatChangedOutput.Format( "INFO : %d x %d%s @%2.3f FPS , %d CH x %d BITS x %d HZ ,  VIDEO INPUT : %s ,  AUDIO INPUT : %s",

													nVideoWidth,

													nVH,

													strFrameType,

													dVideoFrameRate,

													nAudioChannels,

													nAudioBitsPerSample,

													nAudioSampleFrequency,

													strVideoInput,

													strAudioInput ); 

    // NO SOURCE
    //
    if ( nVideoWidth == 0 && 
		
		 nVideoHeight == 0 &&

		 dVideoFrameRate == 0.0 &&

		 nAudioChannels == 0 &&

		 nAudioBitsPerSample == 0 &&

		 nAudioSampleFrequency == 0 ) {

		m_pMainDialog->m_bNoSignal = TRUE;		
	}
    else {

		m_pMainDialog->m_bNoSignal = FALSE;		
    }	

	m_pMainDialog->SetTimer( 0x00000000, 1, NULL );	

    return QCAP_RT_OK;
}    

// NO SIGNAL DETEACTED CALLBACK FUNCTION
//
QRETURN on_process_no_signal_detected( PVOID pDevice, ULONG nVideoInput, ULONG nAudioInput, PVOID pUserData )
{
	pd652Dlg* m_pMainDialog = (pd652Dlg*)pUserData;

	Dbg("No Signal Detected  \n");

	if ( m_pMainDialog == NULL ) { return QCAP_RT_OK; }

	if ( m_pMainDialog->GetSafeHwnd() == NULL ) { return QCAP_RT_OK; }

	m_pMainDialog->m_bNoSignal = TRUE;

	m_pMainDialog->SetTimer( 0x00000000, 1, NULL );	

	return QCAP_RT_OK;
}

// SIGNAL REMOVED CALLBACK FUNCTION
//
QRETURN on_process_signal_removed( PVOID pDevice, ULONG nVideoInput, ULONG nAudioInput, PVOID pUserData )
{
	pd652Dlg* m_pMainDialog = (pd652Dlg*)pUserData;

	Dbg(" Signal Removed \n");

	if ( m_pMainDialog == NULL ) { return QCAP_RT_OK; }

	if ( m_pMainDialog->GetSafeHwnd() == NULL ) { return QCAP_RT_OK; }

	m_pMainDialog->m_bNoSignal = TRUE;

	m_pMainDialog->SetTimer( 0x00000000, 1, NULL );	

    return QCAP_RT_OK;
}    

// PREVIEW VIDEO CALLBACK FUNCTION
//
QRETURN on_process_preview_video_buffer( PVOID pDevice, double dSampleTime, BYTE* pFrameBuffer, ULONG nFrameBufferLen, PVOID pUserData)
{
	pd652Dlg* m_pMainDialog = (pd652Dlg*)pUserData;
	
    return QCAP_RT_OK;
}

// PREVIEW AUDIO CALLBACK FUNCTION
//
QRETURN on_process_preview_audio_buffer( PVOID pDevice, double dSampleTime, BYTE* pFrameBuffer, ULONG nFrameBufferLen, PVOID pUserData)
{
	pd652Dlg* m_pMainDialog = (pd652Dlg*)pUserData;
	
    return QCAP_RT_OK;
}

/////////////////////////////////////////////////////////////////////////////
// pd652Dlg dialog

pd652Dlg::pd652Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(pd652Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(pd652Dlg)
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void pd652Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(pd652Dlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(pd652Dlg, CDialog)
	//{{AFX_MSG_MAP(pd652Dlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// pd652Dlg message handlers

void pd652Dlg::OnOK() 
{
	// TODO: Add extra validation here
	
	// CDialog::OnOK();
}

void pd652Dlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	// CDialog::OnCancel();
}

BOOL pd652Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	// INITIALIZE MEMBER VARIABLES
	//
	{	m_hVideoDevice = 0;

		m_hCloneCapDev = 0;

		m_nVideoWidth = 0;

		m_nVideoHeight = 0;

		m_bVideoIsInterleaved = FALSE;

		m_dVideoFrameRate = 0.0;

		m_bVideoDeinterlaceEnable = FALSE;

		m_nAudioChannels = 0;

		m_nAudioBitsPerSample = 0;

		m_nAudioSampleFrequency = 0;
		
		m_bNoSignal = TRUE;

		m_bSupportGPU1 = FALSE;
	
		m_bIsRecord1 = FALSE;

		m_bSupportGPU2 = FALSE;
	
		m_bIsRecord2 = FALSE;

		m_bSupportGPU3 = FALSE;
	
		m_bIsRecord3 = FALSE;

		m_nSharpness = 128;

		m_nSaturation = 128;

		m_nHue = 128;

		m_nConstrast = 128;

		m_nBrightness = 128;

		// GET DEFAULT RECORD PATH
		// 
		{	BYTE pData[ MAX_PATH ]; DWORD dwType = REG_SZ; DWORD dwData = MAX_PATH;

			HKEY hKey = NULL; RegOpenKey( HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders", &hKey );

			RegQueryValueEx( hKey, "Personal", NULL, &dwType, pData, &dwData );

			RegCloseKey( hKey );

			CHAR psz[ MAX_PATH ] = "";

			if ( strlen( (CHAR*)(pData) ) ) {

				m_strDefaultPath.Format( "%s", (CHAR*)(pData) );
			}
			else {

				m_strDefaultPath.Format( "%s", "" );
			}

			m_strSnapshotPath.Format( "%s\\My Snapshots", m_strDefaultPath );

			m_strRecordPath.Format( "%s\\My Records", m_strDefaultPath );

			CreateDirectory( m_strSnapshotPath, NULL );

			CreateDirectory( m_strRecordPath, NULL );
		}

		m_strRecordFileName = "";
	}
	// INITIALIZE COM RESOURCE
	//
	{	HRESULT hr = CoInitialize( NULL );
	}
	// INITIALIZE USER INTERFACE RESOURCE
	//
	{	m_oChannelWindows[ 0 ].Create( NULL, "MyChannelWindow#01", WS_CHILD | WS_VISIBLE, CRect( 0, 0, 720, 480 ), this, 0x00000001, NULL ); // VIDEO WINDOW

		m_oChannelWindows[ 1 ].Create( NULL, "MyChannelWindow#01", WS_CHILD | WS_VISIBLE, CRect( 0, 0, 720, 480 ), this, 0x00000002, NULL ); // BACKGROUND WINDOW

		m_oCloneWindows.Create( NULL, "MyCloneWindow#01", WS_CHILD | WS_VISIBLE, CRect( 0, 0, 0, 0 ), this, 0x10000001, NULL ); // BACKGROUND WINDOW

		// INITIALIZE MAIN WINDOW
		//
		{	CRect oWindowRect; GetWindowRect( &oWindowRect );

			CRect oClientRect; GetClientRect( &oClientRect );

			ULONG cx = oWindowRect.Width() - oClientRect.Width();		// GET DEFAULT BOUNDARY WIDTH OF DIALOG

			ULONG cy = oWindowRect.Height() - oClientRect.Height();		// GET DEFAULT BOUNDARY HEIGHT OF DIALOG

			MoveWindow( 0, 0, cx + 720, cy + 480 );

			m_oChannelWindows[ 0 ].MoveWindow( 0, 0, cx + 720, cy + 480 );

			m_oChannelWindows[ 1 ].MoveWindow( 0, 0, cx + 720, cy + 480 );

			m_oChannelWindows[ 1 ].ShowWindow( FALSE );

			m_oCloneWindows.MoveWindow( cx + 720 - 320, cy + 480 - 240, 320, 240 );

			m_oCloneWindows.ShowWindow( FALSE );
		}

		// INITIALIZE SETUP DIALOG
		//
		{	HMONITOR hMonitor = MonitorFromWindow( m_hWnd, MONITOR_DEFAULTTONEAREST );			

			MONITORINFO sMonitorInfo = { sizeof(MONITORINFO), }; 
			
			GetMonitorInfo( hMonitor, &sMonitorInfo );

			CRect oMonitorRect = sMonitorInfo.rcWork;			
			
			m_oSetupDialog.Create( IDD_SETUP_DIALOG, this );

			CRect oWindowRect; m_oSetupDialog.GetWindowRect( &oWindowRect );

			CRect oClientRect; m_oSetupDialog.GetClientRect( &oClientRect );

			ULONG cx = oWindowRect.Width() - oClientRect.Width();		// GET DEFAULT BOUNDARY WIDTH OF DIALOG

			ULONG cy = oWindowRect.Height() - oClientRect.Height();		// GET DEFAULT BOUNDARY HEIGHT OF DIALOG

			m_oSetupDialog.SetWindowPos( &(CWnd::wndTop), (oMonitorRect.Width() - (960 + cx)) / 2,

														  (oMonitorRect.Height() - (105 + 40 + cy)),
														  
														  (cx + 960), 

														  (cy + 350),
														  
														  (NULL));
			m_oSetupDialog.ShowWindow( TRUE );
		}

		SetWindowText( "" DEFAULT_PRODUCT ", " DEFAULT_PRODUCT_VERSION );	
	}

	HwInitialize();	

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void pd652Dlg::OnPaint() 
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
	}
}

HCURSOR pd652Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL pd652Dlg::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default

	CRect rect_client;	GetClientRect( &rect_client );

	CBrush brush_fill_rect( RGB(0, 0, 0) );

	pDC->FillRect( &rect_client, &brush_fill_rect );

	return CWnd::OnEraseBkgnd(pDC);
}

BOOL pd652Dlg::OnLButtonDblClk_ChannelWindow() 
{
	// TODO: Add your message handler code here and/or call default
	
	HMONITOR hMonitor = MonitorFromWindow( m_hWnd, MONITOR_DEFAULTTONEAREST );	

	MONITORINFO sMonitorInfo = { sizeof(MONITORINFO), }; 

	GetMonitorInfo( hMonitor, &sMonitorInfo );

	CRect oMonitorRect = sMonitorInfo.rcMonitor;

	CRect oWindowRect; GetWindowRect( &oWindowRect );

	if ( oWindowRect.Width() < oMonitorRect.Width() ) {

		m_oChannelWindows[ 0 ].MoveWindow( 0, 0, oMonitorRect.Width(), oMonitorRect.Height() );

		m_oChannelWindows[ 1 ].MoveWindow( 0, 0, oMonitorRect.Width(), oMonitorRect.Height() );

		m_oCloneWindows.MoveWindow( oMonitorRect.Width() - 320, oMonitorRect.Height() - 240, 320, 240 );

		MoveWindow( oMonitorRect );
	}
	else {

		m_oChannelWindows[ 0 ].MoveWindow( 0, 0, 720, 480 );

		m_oChannelWindows[ 1 ].MoveWindow( 0, 0, 720, 480 );

		m_oCloneWindows.MoveWindow( 720 - 320, 480 - 240, 320, 240 );

		MoveWindow( (oMonitorRect.Width() - 720) / 2, (oMonitorRect.Height() - 480) / 2, 720, 480 );	
	}	

	return TRUE;
}

BOOL pd652Dlg::OnButtonVideoInput_SetupDialog() 
{
	// TODO: Add your control notification handler code here

	if ( m_hVideoDevice == 0 ) { return FALSE; }

	CVideoInputDlg dlg;

	INT_PTR nResponse = -1;
	
	nResponse = dlg.DoModal();

	return TRUE;
}

BOOL pd652Dlg::OnButtonAudioInput_SetupDialog() 
{
	// TODO: Add your control notification handler code here

	if ( m_hVideoDevice == 0 ) { return FALSE; }

	CAduioInputDlg dlg(this);

	INT_PTR nResponse = -1;
	
	nResponse = dlg.DoModal();

	return TRUE;
}

BOOL pd652Dlg::OnButtonVideoQuality_SetupDialog() 
{
	// TODO: Add your control notification handler code here
	
	if ( m_hVideoDevice == 0 ) { return FALSE; }

	CVideoQualityDlg dlg(this);

	INT_PTR nResponse = -1;

	nResponse = dlg.DoModal();

	return TRUE;
}

BOOL pd652Dlg::OnCheckAutoDeinterlace_SetupDialog() 
{
	// TODO: Add your control notification handler code here

	if ( m_oSetupDialog.m_checkAutoDeinterlace.GetCheck() == TRUE ) {

		m_bVideoDeinterlaceEnable = TRUE;
	}
	else {

		m_bVideoDeinterlaceEnable = FALSE;
	}

    if ( m_hVideoDevice != 0 ) {

		if ( m_bVideoDeinterlaceEnable ) {

			QCAP_SET_VIDEO_DEINTERLACE( m_hVideoDevice, 1 );
		}		
        else {

		    QCAP_SET_VIDEO_DEINTERLACE( m_hVideoDevice, 0 );
		}        
    }

	return TRUE;
}

BOOL pd652Dlg::OnCheckShowCloneVideo_SetupDialog()
{
	if ( m_oSetupDialog.m_btnShowCloneVideo.GetCheck() == TRUE ) {
		
		m_oChannelWindows[ 0 ].SetParent( CWnd::GetDesktopWindow() );

		m_oChannelWindows[ 1 ].SetParent( CWnd::GetDesktopWindow() );

		m_oCloneWindows.SetParent( CWnd::GetDesktopWindow() );

		m_oChannelWindows[ 0 ].SetParent( this );

		m_oChannelWindows[ 1 ].SetParent( this );

		m_oCloneWindows.SetParent( this );
		
		m_oCloneWindows.ShowWindow( TRUE );		

		if ( m_hVideoDevice != 0 ) {
			
			QCAP_CREATE_CLONE( m_hVideoDevice, m_oCloneWindows.GetSafeHwnd(), &m_hCloneCapDev, 1 );

			if ( m_hCloneCapDev != 0 ) {

				QCAP_RUN( m_hCloneCapDev );

				QCAP_SET_AUDIO_VOLUME( m_hCloneCapDev, 0 );
			}
		}
	}
	else {
		
		m_oCloneWindows.ShowWindow( FALSE );

		if ( m_hCloneCapDev != 0 ) {

			QCAP_STOP( m_hCloneCapDev );

			QCAP_DESTROY( m_hCloneCapDev );

			m_hCloneCapDev = 0;
		}
	}    

	return TRUE;
}


BOOL pd652Dlg::OnButtonSnapshotJPG_SetupDialog() 
{
	if ( m_hVideoDevice != 0 ) {

		CString strFullPathName;

		strFullPathName = m_strSnapshotPath + _T("\\unname.jpg");

		ULONG nStrlen = strFullPathName.GetLength();

		CHAR* psz = strFullPathName.GetBuffer( nStrlen+1 );

        QCAP_SNAPSHOT_JPG( m_hVideoDevice, psz, 100 );

		strFullPathName.ReleaseBuffer();
	}

	return TRUE;
}

BOOL pd652Dlg::OnButtonSnapshotBMP_SetupDialog() 
{
	if ( m_hVideoDevice != 0 ) {
		
		CString strFullPathName;

		strFullPathName = m_strSnapshotPath + _T("\\unname.bmp");
		
		ULONG nStrlen = strFullPathName.GetLength();

		CHAR* psz = strFullPathName.GetBuffer( nStrlen+1 );

        QCAP_SNAPSHOT_BMP( m_hVideoDevice, psz );

		strFullPathName.ReleaseBuffer();
	}

	return TRUE;
}


BOOL pd652Dlg::OnButtonRecordStart1_1_SetupDialog()
{
	m_oSetupDialog.m_btnRecordStart_1_1.EnableWindow( FALSE ); 

	m_oSetupDialog.m_btnRecordStop_1_1.EnableWindow( TRUE ); 

	m_bSupportGPU1 = m_oSetupDialog.m_checkGPU_1_1.GetCheck();

	if ( m_hVideoDevice != 0 ) {

		CString strFullPathName;

		UINT iCheckedAVI, iCheckedMP4;

		iCheckedAVI = m_oSetupDialog.IsDlgButtonChecked( IDC_AVI_1_RADIO );

		iCheckedMP4 = m_oSetupDialog.IsDlgButtonChecked( IDC_MP4_1_RADIO );

		if ( iCheckedAVI == BST_CHECKED ) {
			
			QCAP_SET_AUDIO_RECORD_PROPERTY( m_hVideoDevice, 0, QCAP_ENCODER_TYPE_SOFTWARE, QCAP_ENCODER_FORMAT_PCM );

			strFullPathName = m_strRecordPath + _T("\\unname1_1080_12M.avi");
		}

        if ( iCheckedMP4 == BST_CHECKED ) {

			QCAP_SET_AUDIO_RECORD_PROPERTY( m_hVideoDevice, 0, QCAP_ENCODER_TYPE_SOFTWARE, QCAP_ENCODER_FORMAT_AAC );

			strFullPathName = m_strRecordPath + _T("\\unname1_1080_12M.mp4");
		}

		ULONG nStrlen = strFullPathName.GetLength();

		CHAR* psz = strFullPathName.GetBuffer( nStrlen+1 );

		if ( m_bSupportGPU1 ) {

			QCAP_SET_VIDEO_RECORD_PROPERTY( m_hVideoDevice, 0, QCAP_ENCODER_TYPE_INTEL_MEDIA_SDK, QCAP_ENCODER_FORMAT_H264, QCAP_RECORD_MODE_CBR, 8000, 12 * 1024 * 1024, 30, 0, 0, QCAP_DOWNSCALE_MODE_OFF);

			QCAP_START_RECORD( m_hVideoDevice, 0, psz );			
		}
		else {

			QCAP_SET_VIDEO_RECORD_PROPERTY( m_hVideoDevice, 0, QCAP_ENCODER_TYPE_SOFTWARE, QCAP_ENCODER_FORMAT_H264, QCAP_RECORD_MODE_CBR, 8000, 12 * 1024 * 1024, 30, 0, 0, QCAP_DOWNSCALE_MODE_OFF);

			QCAP_START_RECORD( m_hVideoDevice, 0, psz );
		}

		m_bIsRecord1 = true;

		strFullPathName.ReleaseBuffer();
	}

	return TRUE;
}

BOOL pd652Dlg::OnButtonRecordStop1_1_SetupDialog()
{
	m_oSetupDialog.m_btnRecordStart_1_1.EnableWindow( TRUE ); 

	m_oSetupDialog.m_btnRecordStop_1_1.EnableWindow( FALSE ); 

	if ( m_hVideoDevice != 0 )
	{
		QCAP_STOP_RECORD( m_hVideoDevice, 0 );

		m_bIsRecord1 = false;
	}

	return TRUE;
}

BOOL pd652Dlg::OnButtonRecordStart1_2_SetupDialog()
{
	m_oSetupDialog.m_btnRecordStart_1_2.EnableWindow( FALSE ); 

	m_oSetupDialog.m_btnRecordStop_1_2.EnableWindow( TRUE ); 

	m_bSupportGPU2 = m_oSetupDialog.m_checkGPU_1_2.GetCheck();

	if ( m_hVideoDevice != 0 )
	{
		CString strFullPathName;

		UINT iCheckedAVI, iCheckedMP4;

		iCheckedAVI = m_oSetupDialog.IsDlgButtonChecked( IDC_AVI_2_RADIO );

		iCheckedMP4 = m_oSetupDialog.IsDlgButtonChecked( IDC_MP4_2_RADIO );

		if ( iCheckedAVI == BST_CHECKED ) {

			QCAP_SET_AUDIO_RECORD_PROPERTY( m_hVideoDevice, 1, QCAP_ENCODER_TYPE_SOFTWARE, QCAP_ENCODER_FORMAT_PCM );

			strFullPathName = m_strRecordPath + _T("\\unname2_480_6M.avi");
		}

        if ( iCheckedMP4 == BST_CHECKED ) {

			QCAP_SET_AUDIO_RECORD_PROPERTY( m_hVideoDevice, 1, QCAP_ENCODER_TYPE_SOFTWARE, QCAP_ENCODER_FORMAT_AAC );

			strFullPathName = m_strRecordPath + _T("\\unname2_480_6M.mp4");
		}

		ULONG nStrlen = strFullPathName.GetLength();

		CHAR* psz = strFullPathName.GetBuffer( nStrlen+1 );

		if ( m_bSupportGPU2 ) {

			QCAP_SET_VIDEO_RECORD_PROPERTY( m_hVideoDevice, 1, QCAP_ENCODER_TYPE_INTEL_MEDIA_SDK, QCAP_ENCODER_FORMAT_H264, QCAP_RECORD_MODE_CBR, 8000, 6 * 1024 * 1024, 30, 0, 0, QCAP_DOWNSCALE_MODE_1_2 );

			QCAP_START_RECORD( m_hVideoDevice, 1, psz );			
		}
		else {

			QCAP_SET_VIDEO_RECORD_PROPERTY( m_hVideoDevice, 1, QCAP_ENCODER_TYPE_SOFTWARE, QCAP_ENCODER_FORMAT_H264, QCAP_RECORD_MODE_CBR, 8000, 6 * 1024 * 1024, 30, 0, 0, QCAP_DOWNSCALE_MODE_1_2 );

			QCAP_START_RECORD( m_hVideoDevice, 1, psz );
		}

		m_bIsRecord2 = true;

		strFullPathName.ReleaseBuffer();
	}

	return TRUE;
}

BOOL pd652Dlg::OnButtonRecordStop1_2_SetupDialog()
{
	m_oSetupDialog.m_btnRecordStart_1_2.EnableWindow( TRUE ); 

	m_oSetupDialog.m_btnRecordStop_1_2.EnableWindow( FALSE ); 

	if ( m_hVideoDevice != 0 ) {

		QCAP_STOP_RECORD( m_hVideoDevice, 1 );

		m_bIsRecord2 = false;
	}

	return TRUE;
}

BOOL pd652Dlg::OnButtonRecordStart1_3_SetupDialog()
{
	m_oSetupDialog.m_btnRecordStart_1_3.EnableWindow( FALSE ); 

	m_oSetupDialog.m_btnRecordStop_1_3.EnableWindow( TRUE ); 

	m_bSupportGPU3 = m_oSetupDialog.m_checkGPU_1_3.GetCheck();

	if ( m_hVideoDevice != 0 ) {

		CString strFullPathName;

		UINT iCheckedAVI, iCheckedMP4;

		iCheckedAVI = m_oSetupDialog.IsDlgButtonChecked( IDC_AVI_3_RADIO );

		iCheckedMP4 = m_oSetupDialog.IsDlgButtonChecked( IDC_MP4_3_RADIO );

		if ( iCheckedAVI == BST_CHECKED ) {

			QCAP_SET_AUDIO_RECORD_PROPERTY( m_hVideoDevice, 2, QCAP_ENCODER_TYPE_SOFTWARE, QCAP_ENCODER_FORMAT_PCM );

			strFullPathName = m_strRecordPath + _T("\\unname3_240_2M.avi");
		}

        if ( iCheckedMP4 == BST_CHECKED ) {

			QCAP_SET_AUDIO_RECORD_PROPERTY( m_hVideoDevice, 2, QCAP_ENCODER_TYPE_SOFTWARE, QCAP_ENCODER_FORMAT_AAC );

			strFullPathName = m_strRecordPath + _T("\\unname3_240_2M.mp4");
		}

		ULONG nStrlen = strFullPathName.GetLength();

		CHAR* psz = strFullPathName.GetBuffer( nStrlen+1 );

		if ( m_bSupportGPU3 ) {

			QCAP_SET_VIDEO_RECORD_PROPERTY( m_hVideoDevice, 2, QCAP_ENCODER_TYPE_INTEL_MEDIA_SDK, QCAP_ENCODER_FORMAT_H264, QCAP_RECORD_MODE_CBR, 8000, 2 * 1024 * 1024, 30, 0, 0, QCAP_DOWNSCALE_MODE_1_4 );

			QCAP_START_RECORD( m_hVideoDevice, 2, psz );			
		}
		else {

			QCAP_SET_VIDEO_RECORD_PROPERTY( m_hVideoDevice, 2, QCAP_ENCODER_TYPE_SOFTWARE, QCAP_ENCODER_FORMAT_H264, QCAP_RECORD_MODE_CBR, 8000, 2 * 1024 * 1024, 30, 0, 0, QCAP_DOWNSCALE_MODE_1_4 );

			QCAP_START_RECORD( m_hVideoDevice, 2, psz );
		}

		m_bIsRecord3 = true;

		strFullPathName.ReleaseBuffer();
	}

	return TRUE;
}

BOOL pd652Dlg::OnButtonRecordStop1_3_SetupDialog()
{
	m_oSetupDialog.m_btnRecordStart_1_3.EnableWindow( TRUE ); 

	m_oSetupDialog.m_btnRecordStop_1_3.EnableWindow( FALSE ); 

	if ( m_hVideoDevice != 0 ) {

		QCAP_STOP_RECORD( m_hVideoDevice, 2 );

		m_bIsRecord3 = false;
	}

	return TRUE;
}

void pd652Dlg::OnDestroy() 
{
	// UNINITIALIZE DEVICE RESOURCE
	//
	{	HwUninitialize();
	}
	// UNINITIALIZE USER INTERFACE RESOURCE
	//
	{	m_oChannelWindows[ 0 ].DestroyWindow();

		m_oChannelWindows[ 1 ].DestroyWindow();

		m_oSetupDialog.DestroyWindow();
	}
	// UNINITIALIZE COM RESOURCE
	//
	{	CoUninitialize();
	}
}

BOOL pd652Dlg::HwInitialize()
{
	// CALLBACK FUNCTION
	//        
	PF_FORMAT_CHANGED_CALLBACK m_pFormatChangedCB = { 0 };

	PF_VIDEO_PREVIEW_CALLBACK  m_pPreviewVideoCB = { 0 };

	PF_AUDIO_PREVIEW_CALLBACK m_pPreviewAudioCB = { 0 };
   
	PF_NO_SIGNAL_DETECTED_CALLBACK m_pNoSignalDetectedCB = { 0 };

	PF_SIGNAL_REMOVED_CALLBACK m_pSignalRemovedCB = { 0 };

	// CREATE CAPTURE DEVICE
	//
	QCAP_CREATE( "DC1150 USB", 0, m_oChannelWindows[ 0 ].m_hWnd, &m_hVideoDevice, 1 );

    if ( m_hVideoDevice == 0 ) { return false;  }       	

    // REGISTER FORMAT CHANGED CALLBACK FUNCTION
    // 
    m_pFormatChangedCB = on_process_format_changed;

    QCAP_REGISTER_FORMAT_CHANGED_CALLBACK( m_hVideoDevice, m_pFormatChangedCB, this );

    // REGISTER PREVIEW VIDEO CALLBACK FUNCTION
    // 
    m_pPreviewVideoCB = on_process_preview_video_buffer;

    QCAP_REGISTER_VIDEO_PREVIEW_CALLBACK( m_hVideoDevice, m_pPreviewVideoCB, this );

    // REGISTER PREVIEW AUDIO CALLBACK FUNCTION
    //
    m_pPreviewAudioCB = on_process_preview_audio_buffer;

    QCAP_REGISTER_AUDIO_PREVIEW_CALLBACK( m_hVideoDevice, m_pPreviewAudioCB, this );
	
	// REGISTER NO SIGNAL DETECTED CALLBACK FUNCTION
	//
	m_pNoSignalDetectedCB = on_process_no_signal_detected;

	QCAP_REGISTER_NO_SIGNAL_DETECTED_CALLBACK( m_hVideoDevice, m_pNoSignalDetectedCB, this );

	// REGISTER SIGNAL REMOVED CALLBACK FUNCTION
	//
	m_pSignalRemovedCB =  on_process_signal_removed;

	QCAP_REGISTER_SIGNAL_REMOVED_CALLBACK( m_hVideoDevice, m_pSignalRemovedCB, this );

    QCAP_SET_VIDEO_DEINTERLACE( m_hVideoDevice, 0 );

	QCAP_SET_AUDIO_VOLUME( m_hVideoDevice, 100 );

    QCAP_RUN( m_hVideoDevice );	
 
	// UPDATE USER INTERFACE RESOURCE
	//
	if ( m_hVideoDevice == 0 ) { 

		m_oSetupDialog.m_btnVideoInput.EnableWindow( FALSE );

		m_oSetupDialog.m_btnVideoQuality.EnableWindow( FALSE );

		m_oSetupDialog.m_btnAudioInput.EnableWindow( FALSE );
		
		m_oSetupDialog.m_btnSnapshot_bmp.EnableWindow( FALSE ); 

		m_oSetupDialog.m_btnSnapshot_jpg.EnableWindow( FALSE ); 

		m_oSetupDialog.m_btnRecordStart_1_1.EnableWindow( FALSE ); 

		m_oSetupDialog.m_btnRecordStop_1_1.EnableWindow( FALSE ); 

		m_oSetupDialog.m_btnRecordStart_1_2.EnableWindow( FALSE ); 

		m_oSetupDialog.m_btnRecordStop_1_2.EnableWindow( FALSE ); 

		m_oSetupDialog.m_btnRecordStart_1_3.EnableWindow( FALSE ); 

		m_oSetupDialog.m_btnRecordStop_1_3.EnableWindow( FALSE ); 

		m_oSetupDialog.m_checkGPU_1_1.EnableWindow( FALSE ); 

		m_oSetupDialog.m_checkGPU_1_1.SetCheck( 0 );

		m_oSetupDialog.m_checkGPU_1_2.EnableWindow( FALSE ); 

		m_oSetupDialog.m_checkGPU_1_2.SetCheck( 0 );

		m_oSetupDialog.m_checkGPU_1_3.EnableWindow( FALSE ); 

		m_oSetupDialog.m_checkGPU_1_3.SetCheck( 0 );

		m_oSetupDialog.m_checkAutoDeinterlace.EnableWindow( FALSE ); 

		m_oSetupDialog.m_checkAutoDeinterlace.SetCheck( 0 );
	}
	else {
			
		m_oSetupDialog.m_btnSnapshot_bmp.EnableWindow( TRUE ); 

		m_oSetupDialog.m_btnSnapshot_jpg.EnableWindow( TRUE);

		m_oSetupDialog.m_btnRecordStart_1_1.EnableWindow( TRUE ); 

		m_oSetupDialog.m_btnRecordStop_1_1.EnableWindow( FALSE ); 

		m_oSetupDialog.m_btnRecordStart_1_2.EnableWindow( TRUE ); 

		m_oSetupDialog.m_btnRecordStop_1_2.EnableWindow( FALSE ); 

		m_oSetupDialog.m_btnRecordStart_1_3.EnableWindow( TRUE ); 

		m_oSetupDialog.m_btnRecordStop_1_3.EnableWindow( FALSE ); 

		m_oSetupDialog.m_checkGPU_1_1.EnableWindow( TRUE ); 

		m_oSetupDialog.m_checkGPU_1_1.SetCheck( 0 );

		m_oSetupDialog.m_checkGPU_1_2.EnableWindow( TRUE ); 

		m_oSetupDialog.m_checkGPU_1_2.SetCheck( 0 );

		m_oSetupDialog.m_checkGPU_1_3.EnableWindow( TRUE ); 

		m_oSetupDialog.m_checkGPU_1_3.SetCheck( 0 );

		m_oSetupDialog.m_checkAutoDeinterlace.EnableWindow( TRUE ); 

		m_oSetupDialog.m_checkAutoDeinterlace.SetCheck( 0 );
	}	

	return TRUE;
}


BOOL pd652Dlg::HwUninitialize()
{	
	if ( m_hCloneCapDev != 0 ) {

		QCAP_STOP( m_hCloneCapDev );

		QCAP_DESTROY( m_hCloneCapDev );

		m_hCloneCapDev = NULL;
	}
	
	if ( m_hVideoDevice != 0 ) {

		QCAP_STOP( m_hVideoDevice );

		QCAP_DESTROY( m_hVideoDevice );

		m_hVideoDevice = NULL;
	}
	return TRUE;
}


void pd652Dlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	
	if( nIDEvent == 0x00000000 )
	{
		KillTimer ( 0x00000000 );

		if( m_bNoSignal )
		{
			if( m_bIsRecord1 )
			{
				QCAP_STOP_RECORD( m_hVideoDevice, 0 );

				m_bIsRecord1 = false;
			}

			if( m_bIsRecord2 )
			{
				QCAP_STOP_RECORD( m_hVideoDevice, 1 );

				m_bIsRecord2 = false;
			}

			if( m_bIsRecord3 )
			{
				QCAP_STOP_RECORD( m_hVideoDevice, 2 );

				m_bIsRecord3 = false;
			}

			m_oSetupDialog.m_staticDeviceFormatInformation.SetWindowText( _T("INFO :...") );

			m_oChannelWindows[ 0 ].ShowWindow( FALSE );

			m_oChannelWindows[ 1 ].ShowWindow( TRUE );	
		}
		else
		{
			m_oSetupDialog.m_staticDeviceFormatInformation.SetWindowText( (LPCTSTR)m_strFormatChangedOutput );

			m_oChannelWindows[ 0 ].ShowWindow( TRUE );

			m_oChannelWindows[ 1 ].ShowWindow( FALSE );	
		}

	}

	CDialog::OnTimer(nIDEvent);
}

void pd652Dlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CWnd::OnLButtonDown(nFlags, point);	
	
	PostMessage( WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM( point.x, point.y ) );
}
