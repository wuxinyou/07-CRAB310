// ColorPropertyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "dlgDemo.h"
#include "ColorPropertyDlg.h"
#include "DXMediaCap.h"
#include "dlgDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CColorPropertyDlg::Device_ColorProp ColorProperty [5];

/////////////////////////////////////////////////////////////////////////////
// CColorPropertyDlg dialog


CColorPropertyDlg::CColorPropertyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CColorPropertyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CColorPropertyDlg)
	m_strBrightness = _T("");
	m_strContrast = _T("");
	m_strSaturation = _T("");
	m_strHue = _T("");
	m_strSharpness = _T("");
	//}}AFX_DATA_INIT
}


void CColorPropertyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CColorPropertyDlg)
	DDX_Control(pDX, IDC_HUE_SLIDER, m_conHue);
	DDX_Control(pDX, IDC_SHARPNESS_SLIDER, m_conSharpness);
	DDX_Control(pDX, IDC_SATURATION_SLIDER, m_conSaturation);
	DDX_Control(pDX, IDC_CONTRAST_SLIDER, m_conContrast);
	DDX_Control(pDX, IDC_BRIGHTNESS_SLIDER, m_conBrightness);
	DDX_Text(pDX, IDC_BRIGHTNESS_STATIC, m_strBrightness);
	DDX_Text(pDX, IDC_CONTRAST_STATIC, m_strContrast);
	DDX_Text(pDX, IDC_SATURATION_STATIC, m_strSaturation);
	DDX_Text(pDX, IDC_HUE_STATIC, m_strHue);
	DDX_Text(pDX, IDC_SHARPNESS_STATIC, m_strSharpness);
	//}}AFX_DATA_MAP


}


BEGIN_MESSAGE_MAP(CColorPropertyDlg, CDialog)
	//{{AFX_MSG_MAP(CColorPropertyDlg)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_BRIGHTNESS_SLIDER, OnCustomdrawBrightnessSlider)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_CONTRAST_SLIDER, OnCustomdrawContrastSlider)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SATURATION_SLIDER, OnCustomdrawSaturationSlider)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SHARPNESS_SLIDER, OnCustomdrawSharpnessSlider)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_HUE_SLIDER, OnCustomdrawHueSlider)
	ON_BN_CLICKED(IDOKEXIT, OnOkexit)
	ON_BN_CLICKED(IDC_DEF_COLOR_BUTTON, OnDefColorButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorPropertyDlg message handlers

BOOL CColorPropertyDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();


	int i;
	long iFlags=0;
	for (i=0; i<5; i++)
	{
		ColorProperty[i].CurVal =0;
		ColorProperty[i].DefaultVal =0;
		ColorProperty[i].MaxVal =0;
		ColorProperty[i].MinVal =0;
		ColorProperty[i].StepVal =0;
	}

	if (CDlgDemoDlg::m_nDevNum >0)
	{
		for (i=0; i<5; i++)
		{
			//得到设备色彩属性的取值范围，步进，默认值
			DXGetDisplayParaRange(CDlgDemoDlg::DeviceInfo[dwCard].dwChannelHandle ,i,&ColorProperty[i].MinVal ,
				                             &ColorProperty[i].MaxVal ,
											 &ColorProperty[i].StepVal ,
											 &ColorProperty[i].DefaultVal ,
											 &iFlags);
			
		}
	}


	//设置托动条范围,步进
	m_conBrightness.SetRange(ColorProperty[0].MinVal ,
		                           ColorProperty[0].MaxVal  ,true);
	m_conBrightness.SetPos(ColorProperty[0].DefaultVal);
	m_conBrightness.SetTicFreq(ColorProperty[0].StepVal);



	m_conContrast.SetRange(ColorProperty[1].MinVal ,
		                           ColorProperty[1].MaxVal  ,true);
	m_conContrast.SetPos(ColorProperty[1].DefaultVal);
	m_conContrast.SetTicFreq(ColorProperty[1].StepVal);


	m_conSaturation.SetRange(ColorProperty[2].MinVal ,
		                           ColorProperty[2].MaxVal  ,true);
	m_conSaturation.SetPos(ColorProperty[2].DefaultVal);
	m_conSaturation.SetTicFreq(ColorProperty[2].StepVal);


	m_conHue.SetRange(ColorProperty[3].MinVal ,
		                           ColorProperty[3].MaxVal  ,true);
	m_conHue.SetPos(ColorProperty[3].DefaultVal);
	m_conHue.SetTicFreq(ColorProperty[3].StepVal);

	m_conSharpness.SetRange(ColorProperty[4].MinVal ,
		                           ColorProperty[4].MaxVal  ,true);
	m_conSharpness.SetPos(ColorProperty[4].DefaultVal);
	m_conSharpness.SetTicFreq(ColorProperty[4].StepVal);


	m_strBrightness.Format( "%3d", ColorProperty[0].DefaultVal );
	m_strContrast.Format( "%3d", ColorProperty[1].DefaultVal);
	m_strSaturation.Format( "%3d", ColorProperty[2].DefaultVal );
	m_strHue.Format( "%3d",ColorProperty[3].DefaultVal );
	m_strSharpness.Format( "%3d", ColorProperty[4].DefaultVal);


	return TRUE;
}

BOOL CColorPropertyDlg::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::Create(IDD, pParentWnd);

	

}

void CColorPropertyDlg::OnOk2() 
{
	// TODO: Add your control notification handler code here
	
}

void CColorPropertyDlg::OnCustomdrawBrightnessSlider(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int nValue = m_conBrightness.GetPos();
	ColorProperty[0].CurVal= nValue;

	if(	CDlgDemoDlg::DeviceInfo[dwCard].dwConnectState)
	{
		DXSetDisplayPara(CDlgDemoDlg::DeviceInfo[dwCard].dwChannelHandle,0,nValue,0);
	}
	m_strBrightness.Format( "%3d", nValue );
	
	UpdateData(FALSE);
	*pResult = 0;
}

void CColorPropertyDlg::OnCustomdrawContrastSlider(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
		int nValue = m_conContrast.GetPos();
	ColorProperty[1].CurVal= nValue;

	if(	CDlgDemoDlg::DeviceInfo[dwCard].dwConnectState)
	{
		DXSetDisplayPara(CDlgDemoDlg::DeviceInfo[dwCard].dwChannelHandle,1,nValue,0);
	}
	m_strContrast.Format( "%3d", nValue );
	
	UpdateData(FALSE);
	*pResult = 0;

}

void CColorPropertyDlg::OnCustomdrawSaturationSlider(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int nValue = m_conSaturation.GetPos();
	ColorProperty[2].CurVal= nValue;

		if(	CDlgDemoDlg::DeviceInfo[dwCard].dwConnectState)
	{
		DXSetDisplayPara(CDlgDemoDlg::DeviceInfo[dwCard].dwChannelHandle,2,nValue,0);
	}
	m_strSaturation.Format( "%3d", nValue );
	
	UpdateData(FALSE);
	*pResult = 0;

}

void CColorPropertyDlg::OnCustomdrawSharpnessSlider(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
		int nValue = m_conSharpness.GetPos();
	ColorProperty[0].CurVal= nValue;

	if(	CDlgDemoDlg::DeviceInfo[dwCard].dwConnectState)
	{
		DXSetDisplayPara(CDlgDemoDlg::DeviceInfo[dwCard].dwChannelHandle,4,nValue,0);
	}
	m_strSharpness.Format( "%3d", nValue );
	
	UpdateData(FALSE);
	*pResult = 0;
	*pResult = 0;
}

void CColorPropertyDlg::OnCustomdrawHueSlider(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
		int nValue = m_conHue.GetPos();
	ColorProperty[3].CurVal= nValue;

	if(	CDlgDemoDlg::DeviceInfo[dwCard].dwConnectState)
	{
		DXSetDisplayPara(CDlgDemoDlg::DeviceInfo[dwCard].dwChannelHandle,3,nValue,0);
	}
	m_strHue.Format( "%3d", nValue );
	
	UpdateData(FALSE);
	*pResult = 0;

}

void CColorPropertyDlg::OnOkexit() 
{
	// TODO: Add your control notification handler code here
		CDialog::OnCancel();
}

void CColorPropertyDlg::OnDefColorButton() 
{
	// TODO: Add your control notification handler code here
		//设置托动条范围,步进

	m_conBrightness.SetPos(ColorProperty[0].DefaultVal);
	m_conContrast.SetPos(ColorProperty[1].DefaultVal);
	m_conSaturation.SetPos(ColorProperty[2].DefaultVal);
	m_conHue.SetPos(ColorProperty[3].DefaultVal);
	m_conSharpness.SetPos(ColorProperty[4].DefaultVal);


	m_strBrightness.Format( "%3d", ColorProperty[0].DefaultVal );
	m_strContrast.Format( "%3d", ColorProperty[1].DefaultVal);
	m_strSaturation.Format( "%3d", ColorProperty[2].DefaultVal );
	m_strHue.Format( "%3d",ColorProperty[3].DefaultVal );
	m_strSharpness.Format( "%3d", ColorProperty[4].DefaultVal);

		if(	CDlgDemoDlg::DeviceInfo[dwCard].dwConnectState)
	{
		for(int i=0;i<5;i++)
		{
				DXSetDisplayPara(CDlgDemoDlg::DeviceInfo[dwCard].dwChannelHandle,i,ColorProperty[i].DefaultVal,0);
		}
	
	}


}
