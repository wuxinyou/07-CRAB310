// VideoQualityDlg.cpp : implementation file
//

#include "stdafx.h"
#include "pd652.h"
#include "pd652Dlg.h"

#include "VideoQualityDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVideoQualityDlg dialog


CVideoQualityDlg::CVideoQualityDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVideoQualityDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVideoQualityDlg)

	m_staticBrightness = _T("255");

	m_staticContrast = _T("255");

	m_staticHue = _T("255");

	m_staticSaturation = _T("255");

	m_staticSharpness = _T("255");

	//}}AFX_DATA_INIT	
}


void CVideoQualityDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVideoQualityDlg)
	DDX_Control(pDX, IDC_SLIDER_SHARPNESS, m_sldSharpness);
	DDX_Control(pDX, IDC_SLIDER_SATURATION, m_sldSaturation);
	DDX_Control(pDX, IDC_SLIDER_HUE, m_sldHue);
	DDX_Control(pDX, IDC_SLIDER_CONSTRAST, m_sldConstrast);
	DDX_Control(pDX, IDC_SLIDER_BRIGHTNESS, m_sldBrightness);
	DDX_Text(pDX, IDC_STATIC_BRIGHTNESS, m_staticBrightness);
	DDX_Text(pDX, IDC_STATIC_CONSTRAST, m_staticContrast);
	DDX_Text(pDX, IDC_STATIC_HUE, m_staticHue);
	DDX_Text(pDX, IDC_STATIC_SATURATION, m_staticSaturation);
	DDX_Text(pDX, IDC_STATIC_SHARPNESS, m_staticSharpness);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CVideoQualityDlg, CDialog)
	//{{AFX_MSG_MAP(CVideoQualityDlg)
	ON_BN_CLICKED(IDC_BUTTON_DEFAULT, OnButtonDefault)
	ON_BN_CLICKED(IDC_BUTTON_OK, OnButtonOk )
	ON_NOTIFY(NM_OUTOFMEMORY, IDC_SLIDER_BRIGHTNESS, OnOutofmemorySliderBrightness)
	ON_NOTIFY(NM_OUTOFMEMORY, IDC_SLIDER_CONSTRAST, OnOutofmemorySliderConstrast)
	ON_NOTIFY(NM_OUTOFMEMORY, IDC_SLIDER_HUE, OnOutofmemorySliderHue)
	ON_NOTIFY(NM_OUTOFMEMORY, IDC_SLIDER_SATURATION, OnOutofmemorySliderSaturation)
	ON_NOTIFY(NM_OUTOFMEMORY, IDC_SLIDER_SHARPNESS, OnOutofmemorySliderSharpness)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_BRIGHTNESS, OnReleasedcaptureSliderBrightness)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_CONSTRAST, OnReleasedcaptureSliderConstrast)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_HUE, OnReleasedcaptureSliderHue)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_SATURATION, OnReleasedcaptureSliderSaturation)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_SHARPNESS, OnReleasedcaptureSliderSharpness)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVideoQualityDlg message handlers

void CVideoQualityDlg::OnButtonDefault() 
{	
	// TODO: Add your control notification handler code here
	
	pd652Dlg* m_pMainDialog = (pd652Dlg*)AfxGetMainWnd();

    if ( m_pMainDialog->m_hVideoDevice != NULL ) {

		QCAP_SET_VIDEO_BRIGHTNESS( m_pMainDialog->m_hVideoDevice, 128 );

        m_sldBrightness.SetPos( 128 );

        m_staticBrightness = _T("128");

		m_pMainDialog->m_nBrightness = 128;
	
        QCAP_SET_VIDEO_CONTRAST( m_pMainDialog->m_hVideoDevice, 128 );

        m_sldConstrast.SetPos( 128 );

        m_staticContrast = _T("128");

		m_pMainDialog->m_nConstrast = 128;

        QCAP_SET_VIDEO_HUE( m_pMainDialog->m_hVideoDevice, 128 );

        m_sldHue.SetPos( 128 );

        m_staticHue = _T("128");

		m_pMainDialog->m_nHue = 128;

        QCAP_SET_VIDEO_SATURATION( m_pMainDialog->m_hVideoDevice, 128 );

        m_sldSaturation.SetPos( 128 );

        m_staticSaturation = _T("128");

		m_pMainDialog->m_nSaturation = 128;

        QCAP_SET_VIDEO_SHARPNESS( m_pMainDialog->m_hVideoDevice, 128 );

        m_sldSharpness.SetPos( 128 );

        m_staticSharpness = _T("128");
		
		m_pMainDialog->m_nSharpness = 128;	
     }	

	UpdateData( FALSE );  
}

void CVideoQualityDlg::OnButtonOk() 
{
	// TODO: Add your control notification handler code here

	pd652Dlg* pParent = (pd652Dlg*)AfxGetMainWnd();

	CDialog::OnOK();
}

void CVideoQualityDlg::OnOutofmemorySliderBrightness(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here

	*pResult = 0;
}

void CVideoQualityDlg::OnOutofmemorySliderConstrast(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here

	*pResult = 0;
}

void CVideoQualityDlg::OnOutofmemorySliderHue(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here

	*pResult = 0;
}

void CVideoQualityDlg::OnOutofmemorySliderSaturation(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here

	*pResult = 0;
}

void CVideoQualityDlg::OnOutofmemorySliderSharpness(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here

	*pResult = 0;
}

BOOL CVideoQualityDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	pd652Dlg* m_pMainDialog = (pd652Dlg*)AfxGetMainWnd();

	// TODO: Add extra initialization here
	
	m_sldBrightness.SetRange( 0, 255, TRUE );

	m_sldConstrast.SetRange( 0, 255, TRUE );

	m_sldHue.SetRange( 0, 255, TRUE );

	m_sldSaturation.SetRange( 0, 255, TRUE );

	m_sldSharpness.SetRange( 0, 255, TRUE );

	// SET VALUES 
	CHAR sz[ MAX_PATH ] = { 0 };

	QCAP_SET_VIDEO_BRIGHTNESS( m_pMainDialog->m_hVideoDevice, m_pMainDialog->m_nBrightness );

	m_sldBrightness.SetPos( m_pMainDialog->m_nBrightness );

	itoa( m_pMainDialog->m_nBrightness, sz, 10 );

	m_staticBrightness = (LPTSTR)sz;
	
	QCAP_SET_VIDEO_CONTRAST( m_pMainDialog->m_hVideoDevice, m_pMainDialog->m_nConstrast );

	m_sldConstrast.SetPos( m_pMainDialog->m_nConstrast );

	itoa( m_pMainDialog->m_nConstrast, sz, 10 );

	m_staticContrast = (LPTSTR)sz;
	
	QCAP_SET_VIDEO_HUE( m_pMainDialog->m_hVideoDevice, m_pMainDialog->m_nHue );

	m_sldHue.SetPos( m_pMainDialog->m_nHue );

	itoa( m_pMainDialog->m_nHue, sz, 10 );

	m_staticHue = (LPTSTR)sz;

	QCAP_SET_VIDEO_SATURATION( m_pMainDialog->m_hVideoDevice, m_pMainDialog->m_nSaturation );

	m_sldSaturation.SetPos( m_pMainDialog->m_nSaturation );

	itoa(  m_pMainDialog->m_nSaturation, sz, 10 );

	m_staticSaturation = (LPTSTR)sz;

	QCAP_SET_VIDEO_SHARPNESS( m_pMainDialog->m_hVideoDevice, m_pMainDialog->m_nSharpness );

	m_sldSharpness.SetPos( m_pMainDialog->m_nSharpness );

	itoa( m_pMainDialog->m_nSharpness, sz, 10 );

	m_staticSharpness = (LPTSTR)sz;

	UpdateData( FALSE );
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CVideoQualityDlg::OnReleasedcaptureSliderBrightness(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here

	pd652Dlg* m_pMainDialog = (pd652Dlg*)AfxGetMainWnd();

	QCAP_SET_VIDEO_BRIGHTNESS( m_pMainDialog->m_hVideoDevice, m_sldBrightness.GetPos() );

	CHAR sz[ MAX_PATH ] = { 0 };

	itoa(m_sldBrightness.GetPos(), sz, 10 );

	m_staticBrightness = (LPTSTR)sz;

	m_pMainDialog->m_nBrightness = m_sldBrightness.GetPos();

	UpdateData( FALSE );	

	*pResult = 0;
}

void CVideoQualityDlg::OnReleasedcaptureSliderConstrast(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here

	pd652Dlg* m_pMainDialog = (pd652Dlg*)AfxGetMainWnd();

	QCAP_SET_VIDEO_CONTRAST( m_pMainDialog->m_hVideoDevice, m_sldConstrast.GetPos() );	

	CHAR sz[ MAX_PATH ] = { 0 };

	itoa( m_sldConstrast.GetPos(), sz, 10 );

	m_staticContrast = (LPTSTR)sz;

	m_pMainDialog->m_nConstrast = m_sldConstrast.GetPos();

	UpdateData( FALSE );	

	*pResult = 0;
}

void CVideoQualityDlg::OnReleasedcaptureSliderHue(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	pd652Dlg* m_pMainDialog = (pd652Dlg*)AfxGetMainWnd();

	QCAP_SET_VIDEO_HUE( m_pMainDialog->m_hVideoDevice, m_sldHue.GetPos() );	

	CHAR sz[ MAX_PATH ] = { 0 };

	itoa( m_sldHue.GetPos(), sz, 10 );

	m_staticHue = (LPTSTR)sz;

	m_pMainDialog->m_nHue = m_sldHue.GetPos();

	UpdateData( FALSE );

	*pResult = 0;
}

void CVideoQualityDlg::OnReleasedcaptureSliderSaturation(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here

	pd652Dlg* m_pMainDialog = (pd652Dlg*)AfxGetMainWnd();

	QCAP_SET_VIDEO_SATURATION( m_pMainDialog->m_hVideoDevice, m_sldSaturation.GetPos() );

	CHAR sz[ MAX_PATH ] = { 0 };

	itoa( m_sldSaturation.GetPos(), sz, 10 );

	m_staticSaturation = (LPTSTR)sz;

	m_pMainDialog->m_nSaturation = m_sldSaturation.GetPos();

	UpdateData( FALSE );	

	*pResult = 0;
}

void CVideoQualityDlg::OnReleasedcaptureSliderSharpness(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here

	pd652Dlg* m_pMainDialog = (pd652Dlg*)AfxGetMainWnd();

	QCAP_SET_VIDEO_SHARPNESS( m_pMainDialog->m_hVideoDevice, m_sldSharpness.GetPos() );	

	CHAR sz[ MAX_PATH ] = { 0 };

	itoa( m_sldSharpness.GetPos(), sz, 10 );

	m_staticSharpness = (LPTSTR)sz;

	m_pMainDialog->m_nSharpness = m_sldSharpness.GetPos();

	UpdateData( FALSE );	

	*pResult = 0;
}
