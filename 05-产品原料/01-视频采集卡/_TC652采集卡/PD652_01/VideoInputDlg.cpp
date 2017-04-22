// VideoInputDlg.cpp : implementation file
//

#include "stdafx.h"
#include "pd652.h"
#include "pd652Dlg.h"
#include "VideoInputDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern VOID Dbg( CHAR* pszStr, ... );

/////////////////////////////////////////////////////////////////////////////
// CVideoInputDlg dialog


CVideoInputDlg::CVideoInputDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVideoInputDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVideoInputDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CVideoInputDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVideoInputDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CVideoInputDlg, CDialog)
	//{{AFX_MSG_MAP(CVideoInputDlg)
	ON_BN_CLICKED(IDC_RADIO_INPUT_HDMI, OnRadioInputHdmi)
	ON_BN_CLICKED(IDC_RADIO_INPUT_DVID, OnRadioInputDvid)
	ON_BN_CLICKED(IDC_RADIO_INPUT_COMPONENTS, OnRadioInputComponents)
	ON_BN_CLICKED(IDC_RADIO_INPUT_DVIA, OnRadioInputDvia)
	ON_BN_CLICKED(IDC_RADIO_INPUT_SDI, OnRadioInputSdi)
	ON_BN_CLICKED(IDC_RADIO_INPUT_COMPOSITE, OnRadioInputComposite)
	ON_BN_CLICKED(IDC_RADIO_INPUT_SVIDEO, OnRadioInputSvideo)
	ON_BN_CLICKED(IDC_RADIO_INPUT_AUTO, OnRadioInputAuto)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVideoInputDlg message handlers


void CVideoInputDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void CVideoInputDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
//	CDialog::OnCancel();
}

BOOL CVideoInputDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here
	
	pd652Dlg* pParent = (pd652Dlg*)AfxGetMainWnd();

	ULONG inputs = 0;

	if ( pParent->m_hVideoDevice != 0 ) {

		QCAP_GET_VIDEO_INPUT( pParent->m_hVideoDevice, &inputs );

		if ( inputs == 0 ) { CheckDlgButton( IDC_RADIO_INPUT_COMPOSITE, BST_CHECKED ); }

		if ( inputs == 1 ) { CheckDlgButton( IDC_RADIO_INPUT_SVIDEO, BST_CHECKED ); }

		if ( inputs == 2 ) { CheckDlgButton( IDC_RADIO_INPUT_HDMI, BST_CHECKED ); }

		if ( inputs == 3 ) { CheckDlgButton( IDC_RADIO_INPUT_DVID, BST_CHECKED ); }

		if ( inputs == 4 ) { CheckDlgButton( IDC_RADIO_INPUT_COMPONENTS, BST_CHECKED ); }

		if ( inputs == 5 ) { CheckDlgButton( IDC_RADIO_INPUT_DVIA, BST_CHECKED ); }

		if ( inputs == 6 ) { CheckDlgButton( IDC_RADIO_INPUT_SDI, BST_CHECKED ); }

		if ( inputs == 7 ) { CheckDlgButton( IDC_RADIO_INPUT_AUTO, BST_CHECKED ); }
	}

	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CVideoInputDlg::OnRadioInputHdmi() 
{
	// TODO: Add your control notification handler code here
	pd652Dlg* pParent = (pd652Dlg*)AfxGetMainWnd();
	
	QCAP_SET_VIDEO_INPUT( pParent->m_hVideoDevice, 0x00000002 );

	CDialog::OnOK();	
}

void CVideoInputDlg::OnRadioInputDvid() 
{
	// TODO: Add your control notification handler code here
	
	pd652Dlg* pParent = (pd652Dlg*)AfxGetMainWnd();

	QCAP_SET_VIDEO_INPUT( pParent->m_hVideoDevice, 0x00000003 );

	CDialog::OnOK();	
}

void CVideoInputDlg::OnRadioInputComponents() 
{
	// TODO: Add your control notification handler code here
	
	pd652Dlg* pParent = (pd652Dlg*)AfxGetMainWnd();

	QCAP_SET_VIDEO_INPUT( pParent->m_hVideoDevice, 0x00000004 );

	CDialog::OnOK();		
}

void CVideoInputDlg::OnRadioInputDvia() 
{
	// TODO: Add your control notification handler code here
	
	pd652Dlg* pParent = (pd652Dlg*)AfxGetMainWnd();

	QCAP_SET_VIDEO_INPUT( pParent->m_hVideoDevice, 0x00000005 );

	CDialog::OnOK();	
}

void CVideoInputDlg::OnRadioInputSdi() 
{
	// TODO: Add your control notification handler code here
	
	pd652Dlg* pParent = (pd652Dlg*)AfxGetMainWnd();

	QCAP_SET_VIDEO_INPUT( pParent->m_hVideoDevice, 0x00000006 );

	CDialog::OnOK();		
}

void CVideoInputDlg::OnRadioInputComposite() 
{
	// TODO: Add your control notification handler code here
	
	pd652Dlg* pParent = (pd652Dlg*)AfxGetMainWnd();

	QCAP_SET_VIDEO_INPUT( pParent->m_hVideoDevice, 0x00000000 );

	CDialog::OnOK();		
}

void CVideoInputDlg::OnRadioInputSvideo() 
{
	// TODO: Add your control notification handler code here
	
	pd652Dlg* pParent = (pd652Dlg*)AfxGetMainWnd();

	QCAP_SET_VIDEO_INPUT( pParent->m_hVideoDevice, 0x00000001 );

	CDialog::OnOK();	
}

void CVideoInputDlg::OnRadioInputAuto() 
{
	// TODO: Add your control notification handler code here
	
	pd652Dlg* pParent = (pd652Dlg*)AfxGetMainWnd();

	QCAP_SET_VIDEO_INPUT( pParent->m_hVideoDevice, 0x00000007 );

	CDialog::OnOK();	
}
