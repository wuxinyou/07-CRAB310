// SetupDlg.cpp : implementation file
//

#include "stdafx.h"
#include "pd652.h"
#include "pd652Dlg.h"
#include "SetupDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetupDlg dialog


CSetupDlg::CSetupDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetupDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetupDlg)
	//}}AFX_DATA_INIT
}


void CSetupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetupDlg)
	DDX_Control(pDX, IDC_BUTTON_RECORD_STOP_1_3, m_btnRecordStop_1_3);
	DDX_Control(pDX, IDC_BUTTON_RECORD_START_1_3, m_btnRecordStart_1_3);
	DDX_Control(pDX, IDC_CHECK_GPU_SUPPORT_1_3, m_checkGPU_1_3);
	DDX_Control(pDX, IDC_EDIT_RECORD_PATH_1_3, m_edit_record_3);
	DDX_Control(pDX, IDC_CHECK_SHOW_CLONE_VIDEO, m_btnShowCloneVideo);
	DDX_Control(pDX, IDC_EDIT_RECORD_PATH_1_2, m_edit_record_2);
	DDX_Control(pDX, IDC_EDIT_RECORD_PATH_1_1, m_edit_record_1);
	DDX_Control(pDX, IDC_EDIT_JPG_PATH, m_edit_jpg);
	DDX_Control(pDX, IDC_EDIT_BMP_PATH, m_edit_bmp);
	DDX_Control(pDX, IDC_CHECK_AUTO_DEINTERLACE, m_checkAutoDeinterlace);
	DDX_Control(pDX, IDC_BUTTON_VIDEO_QUALITY, m_btnVideoQuality);
	DDX_Control(pDX, IDC_BUTTON_VIDEO_INPUT, m_btnVideoInput);
	DDX_Control(pDX, IDC_BUTTON_SNAPSHOT_BMP, m_btnSnapshot_bmp);
	DDX_Control(pDX, IDC_BUTTON_SNAPSHOT_JPG, m_btnSnapshot_jpg);
	DDX_Control(pDX, IDC_BUTTON_AUDIO_INPUT, m_btnAudioInput);
	DDX_Control(pDX, IDC_BUTTON_RECORD_STOP_1_2, m_btnRecordStop_1_2);
	DDX_Control(pDX, IDC_BUTTON_RECORD_START_1_2, m_btnRecordStart_1_2);
	DDX_Control(pDX, IDC_BUTTON_RECORD_STOP_1_1, m_btnRecordStop_1_1);
	DDX_Control(pDX, IDC_BUTTON_RECORD_START_1_1, m_btnRecordStart_1_1);
	DDX_Control(pDX, IDC_CHECK_GPU_SUPPORT_1_2, m_checkGPU_1_2);
	DDX_Control(pDX, IDC_CHECK_GPU_SUPPORT_1_1, m_checkGPU_1_1);
	DDX_Control(pDX, IDC_STATIC_DEVICE_FORMAT_INFOMATION, m_staticDeviceFormatInformation);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetupDlg, CDialog)
	//{{AFX_MSG_MAP(CSetupDlg)
	ON_BN_CLICKED(IDC_BUTTON_VIDEO_INPUT, OnButtonVideoInput)
	ON_BN_CLICKED(IDC_BUTTON_AUDIO_INPUT, OnButtonAudioInput)
	ON_BN_CLICKED(IDC_BUTTON_VIDEO_QUALITY, OnButtonVideoQuality)
	ON_BN_CLICKED(IDC_CHECK_AUTO_DEINTERLACE, OnCheckAutoDeinterlace)
	ON_WM_SYSCOMMAND()
	ON_BN_CLICKED(IDC_BUTTON_SNAPSHOT_BMP, OnButtonSnapshotBmp)
	ON_BN_CLICKED(IDC_BUTTON_SNAPSHOT_JPG, OnButtonSnapshotJpg)
	ON_BN_CLICKED(IDC_BUTTON_RECORD_START_1_1, OnButtonRecordStart11)
	ON_BN_CLICKED(IDC_BUTTON_RECORD_STOP_1_1, OnButtonRecordStop11)
	ON_BN_CLICKED(IDC_BUTTON_RECORD_START_1_2, OnButtonRecordStart12)
	ON_BN_CLICKED(IDC_BUTTON_RECORD_STOP_1_2, OnButtonRecordStop12)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_AVI_1_RADIO, OnAvi1Radio)
	ON_BN_CLICKED(IDC_MP4_1_RADIO, OnMp41Radio)
	ON_BN_CLICKED(IDC_AVI_2_RADIO, OnAvi2Radio)
	ON_BN_CLICKED(IDC_MP4_2_RADIO, OnMp42Radio)
	ON_BN_CLICKED(IDC_CHECK_SHOW_CLONE_VIDEO, OnCheckShowCloneVideo)
	ON_BN_CLICKED(IDC_AVI_3_RADIO, OnAvi3Radio)
	ON_BN_CLICKED(IDC_MP4_3_RADIO, OnMp43Radio)
	ON_BN_CLICKED(IDC_BUTTON_RECORD_START_1_3, OnButtonRecordStart13)
	ON_BN_CLICKED(IDC_BUTTON_RECORD_STOP_1_3, OnButtonRecordStop13)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetupDlg message handlers

void CSetupDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void CSetupDlg::OnCancel()
{
	// TODO: Add extra cleanup here
	
	pd652Dlg* pParent = (pd652Dlg*)(GetParent());	

	CDialog::OnCancel();

	pParent->DestroyWindow();
}

BOOL CSetupDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	pd652Dlg* pParent = (pd652Dlg*)AfxGetMainWnd();
	
	// TODO: Add extra initialization here

	SetWindowText( "" DEFAULT_PRODUCT " " DEFAULT_PRODUCT_VERSION );

	m_staticDeviceFormatInformation.SetWindowText( "INFO : ..." );

	// SET PAHT
	::GetModuleFileName( 0, pParent->m_strSnapshotPath.GetBufferSetLength( MAX_PATH + 1 ), MAX_PATH );
	
	pParent->m_strSnapshotPath.ReleaseBuffer();

	INT nPos;

	nPos = pParent->m_strSnapshotPath.ReverseFind('\\');
	
	// GET PATH
	pParent->m_strSnapshotPath = pParent->m_strSnapshotPath.Left( nPos );
	
	pParent->m_strRecordPath = pParent->m_strSnapshotPath;

	CString strFullPath;

	// SHOW PATH
	strFullPath = pParent->m_strSnapshotPath + CString(_T("\\unname.jpg"));

	m_edit_jpg.SetWindowText( (LPCTSTR)strFullPath );

	strFullPath = pParent->m_strSnapshotPath + CString(_T("\\unname.bmp"));

	m_edit_bmp.SetWindowText( (LPCTSTR)strFullPath );

	strFullPath = pParent->m_strSnapshotPath + CString(_T("\\unname1_1080_12M.mp4"));

	m_edit_record_1.SetWindowText( (LPCTSTR)strFullPath );

	strFullPath = pParent->m_strSnapshotPath + CString(_T("\\unname2_480_6M.mp4"));

	m_edit_record_2.SetWindowText( (LPCTSTR)strFullPath );

	strFullPath = pParent->m_strSnapshotPath + CString(_T("\\unname3_240_2M.mp4"));

	m_edit_record_3.SetWindowText( (LPCTSTR)strFullPath );

	CheckDlgButton( IDC_AVI_1_RADIO, BST_UNCHECKED );

	CheckDlgButton( IDC_AVI_2_RADIO, BST_UNCHECKED );

	CheckDlgButton( IDC_AVI_3_RADIO, BST_UNCHECKED );

	CheckDlgButton( IDC_MP4_1_RADIO, BST_CHECKED );

	CheckDlgButton( IDC_MP4_2_RADIO, BST_CHECKED );

	CheckDlgButton( IDC_MP4_3_RADIO, BST_CHECKED );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSetupDlg::OnButtonVideoInput() 
{
	// TODO: Add your control notification handler code here
	
	pd652Dlg* pParent = (pd652Dlg*)AfxGetMainWnd();

	pParent->OnButtonVideoInput_SetupDialog();
}

void CSetupDlg::OnButtonAudioInput() 
{
	// TODO: Add your control notification handler code here

	pd652Dlg* pParent = (pd652Dlg*)AfxGetMainWnd();

	pParent->OnButtonAudioInput_SetupDialog();
}

void CSetupDlg::OnButtonVideoQuality() 
{
	// TODO: Add your control notification handler code here
	
	pd652Dlg* pParent = (pd652Dlg*)AfxGetMainWnd();

	pParent->OnButtonVideoQuality_SetupDialog();
}

void CSetupDlg::OnCheckAutoDeinterlace() 
{
	// TODO: Add your control notification handler code here
	
	pd652Dlg* pParent = (pd652Dlg*)AfxGetMainWnd();

	pParent->OnCheckAutoDeinterlace_SetupDialog();
}

void CSetupDlg::OnCheckShowCloneVideo() 
{
	// TODO: Add your control notification handler code here
	
	pd652Dlg* pParent = (pd652Dlg*)AfxGetMainWnd();

	pParent->OnCheckShowCloneVideo_SetupDialog();
}

void CSetupDlg::OnSysCommand(UINT nID, LPARAM lParam) 
{
	// TODO: Add your message handler code here and/or call default

	pd652Dlg* pParent = (pd652Dlg*)AfxGetMainWnd();

	if ( nID == SC_CLOSE ) { 

		::SendMessage( AfxGetMainWnd()->m_hWnd, WM_SYSCOMMAND, SC_CLOSE, 0  );
    }

	CDialog::OnSysCommand(nID, lParam);
}

void CSetupDlg::OnButtonSnapshotBmp() 
{
	// TODO: Add your control notification handler code here
	
	pd652Dlg* pParent = (pd652Dlg*)AfxGetMainWnd();

	pParent->OnButtonSnapshotBMP_SetupDialog();
}

void CSetupDlg::OnButtonSnapshotJpg() 
{
	// TODO: Add your control notification handler code here

	pd652Dlg* pParent = (pd652Dlg*)AfxGetMainWnd();

	pParent->OnButtonSnapshotJPG_SetupDialog();
}

void CSetupDlg::OnButtonRecordStart11() 
{
	// TODO: Add your control notification handler code here

 	pd652Dlg* pParent = (pd652Dlg*)AfxGetMainWnd();

	pParent->OnButtonRecordStart1_1_SetupDialog();

}

void CSetupDlg::OnButtonRecordStop11() 
{
	// TODO: Add your control notification handler code here

 	pd652Dlg* pParent = (pd652Dlg*)AfxGetMainWnd();

	pParent->OnButtonRecordStop1_1_SetupDialog();
}

void CSetupDlg::OnButtonRecordStart12() 
{
	// TODO: Add your control notification handler code here

 	pd652Dlg* pParent = (pd652Dlg*)AfxGetMainWnd();

	pParent->OnButtonRecordStart1_2_SetupDialog();	
}

void CSetupDlg::OnButtonRecordStop12() 
{
	// TODO: Add your control notification handler code here

 	pd652Dlg* pParent = (pd652Dlg*)AfxGetMainWnd();

	pParent->OnButtonRecordStop1_2_SetupDialog();
}

void CSetupDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here	
}

void CSetupDlg::OnAvi1Radio() 
{
	// TODO: Add your control notification handler code here
	
	pd652Dlg* pParent = (pd652Dlg*)AfxGetMainWnd();

	CString strFullPath;

	strFullPath = pParent->m_strSnapshotPath + CString(_T("\\unname1_1080_12M.avi"));

	m_edit_record_1.SetWindowText( (LPCTSTR)strFullPath );

	UINT iCheckedAVI_1, iCheckedMP4_1, iCheckedAVI_2, iCheckedMP4_2, iCheckedAVI_3, iCheckedMP4_3;

	iCheckedAVI_1 = ((CButton*)GetDlgItem(IDC_AVI_1_RADIO))->GetCheck();		// 1 PRESENT BE CHOSEN, 0 BE ELSE

	iCheckedMP4_1 = ((CButton*)GetDlgItem(IDC_MP4_1_RADIO))->GetCheck();

	iCheckedAVI_2 = ((CButton*)GetDlgItem(IDC_AVI_2_RADIO))->GetCheck();

	iCheckedMP4_2 = ((CButton*)GetDlgItem(IDC_MP4_2_RADIO))->GetCheck();

	iCheckedAVI_3 = ((CButton*)GetDlgItem(IDC_AVI_3_RADIO))->GetCheck();

	iCheckedMP4_3 = ((CButton*)GetDlgItem(IDC_MP4_3_RADIO))->GetCheck();	

	if ( iCheckedAVI_1 ){ ((CButton*)GetDlgItem(IDC_AVI_1_RADIO))->SetCheck( TRUE ); }

	if ( iCheckedMP4_1 ){ ((CButton*)GetDlgItem(IDC_MP4_1_RADIO))->SetCheck( TRUE ); }

	if ( iCheckedAVI_2 ){ ((CButton*)GetDlgItem(IDC_AVI_2_RADIO))->SetCheck( TRUE ); }

	if ( iCheckedMP4_2 ){ ((CButton*)GetDlgItem(IDC_MP4_2_RADIO))->SetCheck( TRUE ); }

	if ( iCheckedAVI_3 ){ ((CButton*)GetDlgItem(IDC_AVI_3_RADIO))->SetCheck( TRUE ); }

	if ( iCheckedMP4_3 ){ ((CButton*)GetDlgItem(IDC_MP4_3_RADIO))->SetCheck( TRUE ); }	
}

void CSetupDlg::OnMp41Radio() 
{
	// TODO: Add your control notification handler code here

	pd652Dlg* pParent = (pd652Dlg*)AfxGetMainWnd();

	CString strFullPath;

	strFullPath = pParent->m_strSnapshotPath + CString(_T("\\unname1_1080_12M.mp4"));

	m_edit_record_1.SetWindowText( (LPCTSTR)strFullPath );

	UINT iCheckedAVI_1, iCheckedMP4_1, iCheckedAVI_2, iCheckedMP4_2, iCheckedAVI_3, iCheckedMP4_3;
	
	iCheckedAVI_1 = ((CButton*)GetDlgItem(IDC_AVI_1_RADIO))->GetCheck();		// 1 PRESENT BE CHOSEN, 0 BE ELSE

	iCheckedMP4_1 = ((CButton*)GetDlgItem(IDC_MP4_1_RADIO))->GetCheck();

	iCheckedAVI_2 = ((CButton*)GetDlgItem(IDC_AVI_2_RADIO))->GetCheck();

	iCheckedMP4_2 = ((CButton*)GetDlgItem(IDC_MP4_2_RADIO))->GetCheck();

	iCheckedAVI_3 = ((CButton*)GetDlgItem(IDC_AVI_3_RADIO))->GetCheck();

	iCheckedMP4_3 = ((CButton*)GetDlgItem(IDC_MP4_3_RADIO))->GetCheck();	

	if ( iCheckedAVI_1 ){ ((CButton*)GetDlgItem(IDC_AVI_1_RADIO))->SetCheck( TRUE ); }

	if ( iCheckedMP4_1 ){ ((CButton*)GetDlgItem(IDC_MP4_1_RADIO))->SetCheck( TRUE ); }

	if ( iCheckedAVI_2 ){ ((CButton*)GetDlgItem(IDC_AVI_2_RADIO))->SetCheck( TRUE ); }

	if ( iCheckedMP4_2 ){ ((CButton*)GetDlgItem(IDC_MP4_2_RADIO))->SetCheck( TRUE ); }

	if ( iCheckedAVI_3 ){ ((CButton*)GetDlgItem(IDC_AVI_3_RADIO))->SetCheck( TRUE ); }

	if ( iCheckedMP4_3 ){ ((CButton*)GetDlgItem(IDC_MP4_3_RADIO))->SetCheck( TRUE ); }
}

void CSetupDlg::OnAvi2Radio() 
{
	// TODO: Add your control notification handler code here

	pd652Dlg* pParent = (pd652Dlg*)AfxGetMainWnd();

	CString strFullPath;

	strFullPath = pParent->m_strSnapshotPath + CString(_T("\\unname2_480_6M.avi"));

	m_edit_record_2.SetWindowText( (LPCTSTR)strFullPath );

	UINT iCheckedAVI_1, iCheckedMP4_1, iCheckedAVI_2, iCheckedMP4_2, iCheckedAVI_3, iCheckedMP4_3;

	iCheckedAVI_1 = ((CButton*)GetDlgItem(IDC_AVI_1_RADIO))->GetCheck();		// 1 PRESENT BE CHOSEN, 0 BE ELSE

	iCheckedMP4_1 = ((CButton*)GetDlgItem(IDC_MP4_1_RADIO))->GetCheck();

	iCheckedAVI_2 = ((CButton*)GetDlgItem(IDC_AVI_2_RADIO))->GetCheck();

	iCheckedMP4_2 = ((CButton*)GetDlgItem(IDC_MP4_2_RADIO))->GetCheck();

	iCheckedAVI_3 = ((CButton*)GetDlgItem(IDC_AVI_3_RADIO))->GetCheck();

	iCheckedMP4_3 = ((CButton*)GetDlgItem(IDC_MP4_3_RADIO))->GetCheck();	

	if ( iCheckedAVI_1 ){ ((CButton*)GetDlgItem(IDC_AVI_1_RADIO))->SetCheck( TRUE ); }

	if ( iCheckedMP4_1 ){ ((CButton*)GetDlgItem(IDC_MP4_1_RADIO))->SetCheck( TRUE ); }

	if ( iCheckedAVI_2 ){ ((CButton*)GetDlgItem(IDC_AVI_2_RADIO))->SetCheck( TRUE ); }

	if ( iCheckedMP4_2 ){ ((CButton*)GetDlgItem(IDC_MP4_2_RADIO))->SetCheck( TRUE ); }

	if ( iCheckedAVI_3 ){ ((CButton*)GetDlgItem(IDC_AVI_3_RADIO))->SetCheck( TRUE ); }

	if ( iCheckedMP4_3 ){ ((CButton*)GetDlgItem(IDC_MP4_3_RADIO))->SetCheck( TRUE ); }
}

void CSetupDlg::OnMp42Radio() 
{
	// TODO: Add your control notification handler code here

	pd652Dlg* pParent = (pd652Dlg*)AfxGetMainWnd();

	CString strFullPath;

	strFullPath = pParent->m_strSnapshotPath + CString(_T("\\unname2_480_6M.mp4"));

	m_edit_record_2.SetWindowText( (LPCTSTR)strFullPath );

	UINT iCheckedAVI_1, iCheckedMP4_1, iCheckedAVI_2, iCheckedMP4_2, iCheckedAVI_3, iCheckedMP4_3;

	iCheckedAVI_1 = ((CButton*)GetDlgItem(IDC_AVI_1_RADIO))->GetCheck();		// 1 PRESENT BE CHOSEN, 0 BE ELSE

	iCheckedMP4_1 = ((CButton*)GetDlgItem(IDC_MP4_1_RADIO))->GetCheck();

	iCheckedAVI_2 = ((CButton*)GetDlgItem(IDC_AVI_2_RADIO))->GetCheck();

	iCheckedMP4_2 = ((CButton*)GetDlgItem(IDC_MP4_2_RADIO))->GetCheck();

	iCheckedAVI_3 = ((CButton*)GetDlgItem(IDC_AVI_3_RADIO))->GetCheck();

	iCheckedMP4_3 = ((CButton*)GetDlgItem(IDC_MP4_3_RADIO))->GetCheck();	

	if ( iCheckedAVI_1 ){ ((CButton*)GetDlgItem(IDC_AVI_1_RADIO))->SetCheck( TRUE ); }

	if ( iCheckedMP4_1 ){ ((CButton*)GetDlgItem(IDC_MP4_1_RADIO))->SetCheck( TRUE ); }

	if ( iCheckedAVI_2 ){ ((CButton*)GetDlgItem(IDC_AVI_2_RADIO))->SetCheck( TRUE ); }

	if ( iCheckedMP4_2 ){ ((CButton*)GetDlgItem(IDC_MP4_2_RADIO))->SetCheck( TRUE ); }

	if ( iCheckedAVI_3 ){ ((CButton*)GetDlgItem(IDC_AVI_3_RADIO))->SetCheck( TRUE ); }

	if ( iCheckedMP4_3 ){ ((CButton*)GetDlgItem(IDC_MP4_3_RADIO))->SetCheck( TRUE ); }
}

void CSetupDlg::OnAvi3Radio() 
{
	// TODO: Add your control notification handler code here

	pd652Dlg* pParent = (pd652Dlg*)AfxGetMainWnd();

	CString strFullPath;

	strFullPath = pParent->m_strSnapshotPath + CString(_T("\\unname3_240_2M.avi"));

	m_edit_record_3.SetWindowText( (LPCTSTR)strFullPath );

	UINT iCheckedAVI_1, iCheckedMP4_1, iCheckedAVI_2, iCheckedMP4_2, iCheckedAVI_3, iCheckedMP4_3;

	iCheckedAVI_1 = ((CButton*)GetDlgItem(IDC_AVI_1_RADIO))->GetCheck();		// 1 PRESENT BE CHOSEN, 0 BE ELSE

	iCheckedMP4_1 = ((CButton*)GetDlgItem(IDC_MP4_1_RADIO))->GetCheck();

	iCheckedAVI_2 = ((CButton*)GetDlgItem(IDC_AVI_2_RADIO))->GetCheck();

	iCheckedMP4_2 = ((CButton*)GetDlgItem(IDC_MP4_2_RADIO))->GetCheck();

	iCheckedAVI_3 = ((CButton*)GetDlgItem(IDC_AVI_3_RADIO))->GetCheck();

	iCheckedMP4_3 = ((CButton*)GetDlgItem(IDC_MP4_3_RADIO))->GetCheck();	

	if ( iCheckedAVI_1 ){ ((CButton*)GetDlgItem(IDC_AVI_1_RADIO))->SetCheck( TRUE ); }

	if ( iCheckedMP4_1 ){ ((CButton*)GetDlgItem(IDC_MP4_1_RADIO))->SetCheck( TRUE ); }

	if ( iCheckedAVI_2 ){ ((CButton*)GetDlgItem(IDC_AVI_2_RADIO))->SetCheck( TRUE ); }

	if ( iCheckedMP4_2 ){ ((CButton*)GetDlgItem(IDC_MP4_2_RADIO))->SetCheck( TRUE ); }

	if ( iCheckedAVI_3 ){ ((CButton*)GetDlgItem(IDC_AVI_3_RADIO))->SetCheck( TRUE ); }

	if ( iCheckedMP4_3 ){ ((CButton*)GetDlgItem(IDC_MP4_3_RADIO))->SetCheck( TRUE ); }
}

void CSetupDlg::OnMp43Radio() 
{
	// TODO: Add your control notification handler code here

	pd652Dlg* pParent = (pd652Dlg*)AfxGetMainWnd();

	CString strFullPath;

	strFullPath = pParent->m_strSnapshotPath + CString(_T("\\unname3_240_2M.mp4"));

	m_edit_record_3.SetWindowText( (LPCTSTR)strFullPath );

	UINT iCheckedAVI_1, iCheckedMP4_1, iCheckedAVI_2, iCheckedMP4_2, iCheckedAVI_3, iCheckedMP4_3;

	iCheckedAVI_1 = ((CButton*)GetDlgItem(IDC_AVI_1_RADIO))->GetCheck();		// 1 PRESENT BE CHOSEN, 0 BE ELSE

	iCheckedMP4_1 = ((CButton*)GetDlgItem(IDC_MP4_1_RADIO))->GetCheck();

	iCheckedAVI_2 = ((CButton*)GetDlgItem(IDC_AVI_2_RADIO))->GetCheck();

	iCheckedMP4_2 = ((CButton*)GetDlgItem(IDC_MP4_2_RADIO))->GetCheck();

	iCheckedAVI_3 = ((CButton*)GetDlgItem(IDC_AVI_3_RADIO))->GetCheck();

	iCheckedMP4_3 = ((CButton*)GetDlgItem(IDC_MP4_3_RADIO))->GetCheck();	

	if ( iCheckedAVI_1 ){ ((CButton*)GetDlgItem(IDC_AVI_1_RADIO))->SetCheck( TRUE ); }

	if ( iCheckedMP4_1 ){ ((CButton*)GetDlgItem(IDC_MP4_1_RADIO))->SetCheck( TRUE ); }

	if ( iCheckedAVI_2 ){ ((CButton*)GetDlgItem(IDC_AVI_2_RADIO))->SetCheck( TRUE ); }

	if ( iCheckedMP4_2 ){ ((CButton*)GetDlgItem(IDC_MP4_2_RADIO))->SetCheck( TRUE ); }

	if ( iCheckedAVI_3 ){ ((CButton*)GetDlgItem(IDC_AVI_3_RADIO))->SetCheck( TRUE ); }

	if ( iCheckedMP4_3 ){ ((CButton*)GetDlgItem(IDC_MP4_3_RADIO))->SetCheck( TRUE ); }
}

void CSetupDlg::OnButtonRecordStart13() 
{
	// TODO: Add your control notification handler code here

 	pd652Dlg* pParent = (pd652Dlg*)AfxGetMainWnd();

	pParent->OnButtonRecordStart1_3_SetupDialog();
}

void CSetupDlg::OnButtonRecordStop13() 
{
	// TODO: Add your control notification handler code here

 	pd652Dlg* pParent = (pd652Dlg*)AfxGetMainWnd();

	pParent->OnButtonRecordStop1_3_SetupDialog();
}
