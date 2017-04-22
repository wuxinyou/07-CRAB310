// AduioInputDlg.cpp : implementation file
//

#include "stdafx.h"
#include "pd652.h"
#include "pd652Dlg.h"
#include "AduioInputDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAduioInputDlg dialog


CAduioInputDlg::CAduioInputDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAduioInputDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAduioInputDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CAduioInputDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAduioInputDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAduioInputDlg, CDialog)
	//{{AFX_MSG_MAP(CAduioInputDlg)
	ON_BN_CLICKED(IDC_RADIO_INPUT_EMBEDDED_AUDIO, OnRadioInputEmbeddedAudio)
	ON_BN_CLICKED(IDC_RADIO_INPUT_LINEIN, OnRadioInputLinein)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAduioInputDlg message handlers

void CAduioInputDlg::OnOK() 
{
	// TODO: Add extra validation here
	
//	CDialog::OnOK();
}

void CAduioInputDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
//	CDialog::OnCancel();
}

BOOL CAduioInputDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	pd652Dlg* pParent = (pd652Dlg*)AfxGetMainWnd();

	ULONG inputs = 0;

	QCAP_GET_AUDIO_INPUT( pParent->m_hVideoDevice, &inputs );

	if ( inputs == 0 ) { CheckDlgButton( IDC_RADIO_INPUT_EMBEDDED_AUDIO, BST_CHECKED ); }

	if ( inputs == 1 ) { CheckDlgButton( IDC_RADIO_INPUT_LINEIN, BST_CHECKED ); }

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAduioInputDlg::OnRadioInputEmbeddedAudio() 
{
	// TODO: Add your control notification handler code here

	pd652Dlg* pParent = (pd652Dlg*)AfxGetMainWnd();

	QCAP_SET_AUDIO_INPUT( pParent->m_hVideoDevice, 0x00000000 );

	CDialog::OnOK();
}

void CAduioInputDlg::OnRadioInputLinein() 
{
	// TODO: Add your control notification handler code here

	pd652Dlg* pParent = (pd652Dlg*)AfxGetMainWnd();

	QCAP_SET_AUDIO_INPUT( pParent->m_hVideoDevice, 0x00000001 );

	CDialog::OnOK();
}
