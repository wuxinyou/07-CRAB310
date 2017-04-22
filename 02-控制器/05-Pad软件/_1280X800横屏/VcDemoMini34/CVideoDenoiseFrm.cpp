// CVideoDenoiseFrm.cpp : implementation file
//

#include "stdafx.h"
#include "dlgDemo.h"
#include "CVideoDenoiseFrm.h"
#include "dlgDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

 DRateColorPara dratepara;
/////////////////////////////////////////////////////////////////////////////
// CCVideoDenoiseFrm dialog
BOOL CCVideoDenoiseFrm::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_SliBrightValue = 0;
	m_SliContractValue = 30;
	m_Denoise_Silider.SetRange(0 , 100  ,true);
	m_Denoise_Silider.SetPos(65);
	m_Denoise_Silider.SetTicFreq(1);
	
	m_denoise_value.Format( "%3d", 65 );


	m_Sharp_Silider.SetRange(0 , 255  ,true);
	m_Sharp_Silider.SetPos(20);
	m_Sharp_Silider.SetTicFreq(1);
	
	m_Sharp_Value.Format( "%3d", 20 );


	m_Bright_Silider.SetRange(-255 , 255  ,true);
	m_Bright_Silider.SetPos(0);
	m_Bright_Silider.SetTicFreq(1);
	
	m_Bright_Value.Format( "%3d", 0 );


	m_Contrast_Silider.SetRange(0 , 100  ,true);
	m_Contrast_Silider.SetPos(30);
	m_Contrast_Silider.SetTicFreq(1);
	
	m_Contrast_Value.Format( "%3d", 30 );

   return 0;
}

CCVideoDenoiseFrm::CCVideoDenoiseFrm(CWnd* pParent /*=NULL*/)
	: CDialog(CCVideoDenoiseFrm::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCVideoDenoiseFrm)
	m_denoise_value = _T("");
	m_Sharp_Value = _T("");
	m_Bright_Value = _T("");
	m_Contrast_Value = _T("");
	//}}AFX_DATA_INIT
}


void CCVideoDenoiseFrm::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCVideoDenoiseFrm)
	DDX_Control(pDX, IDC_SLIDER_CONTRACT, m_Contrast_Silider);
	DDX_Control(pDX, IDC_SLIDER_BRIGHT, m_Bright_Silider);
	DDX_Control(pDX, IDC_SLIDER_SHARP, m_Sharp_Silider);
	DDX_Control(pDX, IDC_SLIDER_DENOISE, m_Denoise_Silider);
	DDX_Text(pDX, IDC_STATIC_DENOISE, m_denoise_value);
	DDX_Text(pDX, IDC_STATIC_SHARP, m_Sharp_Value);
	DDX_Text(pDX, IDC_STATIC_BRIGHT, m_Bright_Value);
	DDX_Text(pDX, IDC_STATIC_CONTRAST, m_Contrast_Value);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCVideoDenoiseFrm, CDialog)
	//{{AFX_MSG_MAP(CCVideoDenoiseFrm)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_DENOISE, OnCustomdrawSliderDenoise)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_SHARP, OnCustomdrawSliderSharp)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_BRIGHT, OnCustomdrawSliderBright)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_CONTRACT, OnCustomdrawSliderContract)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCVideoDenoiseFrm message handlers

void CCVideoDenoiseFrm::OnCustomdrawSliderDenoise(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int nValue = m_Denoise_Silider.GetPos();

	if(	CDlgDemoDlg::DeviceInfo[dwCard].dwOpenDevState ==0)
	{
		DXEnableDenoise(CDlgDemoDlg::DeviceInfo[dwCard].dwChannelHandle,nValue);
	}
	m_denoise_value.Format( "%3d", nValue );
	
	UpdateData(FALSE);
	*pResult = 0;
}

BOOL CCVideoDenoiseFrm::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::OnCommand(wParam, lParam);
}

BOOL CCVideoDenoiseFrm::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::Create(IDD, pParentWnd);
}

void CCVideoDenoiseFrm::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void CCVideoDenoiseFrm::OnCustomdrawSliderSharp(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int nValue = m_Sharp_Silider.GetPos();
	
	if(	CDlgDemoDlg::DeviceInfo[dwCard].dwOpenDevState ==0)
	{
		DXEnableSharpen(CDlgDemoDlg::DeviceInfo[dwCard].dwChannelHandle,nValue);
	}
	m_Sharp_Value.Format( "%3d", nValue );
	
	UpdateData(FALSE);
	*pResult = 0;
}

void CCVideoDenoiseFrm::OnCustomdrawSliderBright(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	m_SliBrightValue = m_Bright_Silider.GetPos();
	
	dratepara.nBrightness = m_SliBrightValue;
	dratepara.nContrast   = m_SliContractValue;
	
	if(	CDlgDemoDlg::DeviceInfo[dwCard].dwOpenDevState ==0)
	{
		
		DXEnDataRaterPara(CDlgDemoDlg::DeviceInfo[dwCard].dwChannelHandle,drate_color,&dratepara);
	}
	
	m_Bright_Value.Format( "%3d", m_SliBrightValue );
	UpdateData(FALSE);
	
	*pResult = 0;
}

void CCVideoDenoiseFrm::OnCustomdrawSliderContract(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	m_SliContractValue = m_Contrast_Silider.GetPos();
			 
	dratepara.nBrightness = m_SliBrightValue;
	dratepara.nContrast   = m_SliContractValue;
	if(	CDlgDemoDlg::DeviceInfo[dwCard].dwOpenDevState ==0)
	{
		
		DXEnDataRaterPara(CDlgDemoDlg::DeviceInfo[dwCard].dwChannelHandle,drate_color,&dratepara);
	}
	
	m_Contrast_Value.Format( "%3d", m_SliContractValue );
	UpdateData(FALSE);
	*pResult = 0;
}
