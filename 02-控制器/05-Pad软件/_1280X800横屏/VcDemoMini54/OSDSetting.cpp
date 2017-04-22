// OSDSetting.cpp : implementation file
//

#include "stdafx.h"
#include "dlgDemo.h"
#include "OSDSetting.h"
#include "DXMediaCap.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// OSDSetting dialog


OSDSetting::OSDSetting(CWnd* pParent /*=NULL*/)
	: CDialog(OSDSetting::IDD, pParent)
{
	//{{AFX_DATA_INIT(OSDSetting)
	m_TimeOsdCheck = true;
	m_TimeTranCheck =true;
	m_TxtOsdCheck1 =true;
	m_TxtPlaceY1 = _T("50");
	m_TxtPlaceY2 = _T("100");
	m_TxtPlaceX1 = _T("10");
	m_TxtPlaceX2 = _T("10");
	m_PicPlaceX = _T("50");
	m_PicPlaceY = _T("150");
	m_TimePlaceY = _T("10");
	m_TxtFontSize1 = _T("25");
	m_TxtFontSize2 = _T("25");
	m_TimeFontSize = _T("25");
	m_TxtOSD1 = _T("Camera1");
	m_TxtOSD2 = _T("Camera2");
	m_PicFile = _T("");
	m_TxtTranCheck1 = true;
	m_TxtTranCheck2 = true;
	m_TxtOsdCheck1=true;
	m_TxtOsdCheck2 = true;
	m_TimeTranCheck = true;
	m_TxtOsdCheck1 = true;
	m_TimePlaceX = _T("10");
	//}}AFX_DATA_INIT
}


void OSDSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(OSDSetting)
	DDX_Control(pDX, IDC_PICTUREOSD_CHECK, m_PicOsdCheck);
	DDX_Check(pDX, IDC_TIMEOSD_CHECK, m_TimeOsdCheck);
	DDX_Text(pDX, IDC_TextPlaceY_EDIT1, m_TxtPlaceY1);
	DDX_Text(pDX, IDC_TextPlaceY_EDIT2, m_TxtPlaceY2);
	DDX_Text(pDX, IDC_TEXTPlaceX_EDIT1, m_TxtPlaceX1);
	DDX_Text(pDX, IDC_TEXTPlaceX_EDIT2, m_TxtPlaceX2);
	DDX_Text(pDX, IDC_PicturePlaceX_EDIT, m_PicPlaceX);
	DDX_Text(pDX, IDC_PicturePlaceY_EDIT, m_PicPlaceY);
	DDX_Text(pDX, IDC_TimePlaceY_EDIT, m_TimePlaceY);
	DDX_Text(pDX, IDC_TextFontSize_EDIT1, m_TxtFontSize1);
	DDX_Text(pDX, IDC_TextFontSize_EDIT3, m_TxtFontSize2);
	DDX_Text(pDX, IDC_TimeFontSize_EDIT1, m_TimeFontSize);
	DDX_Text(pDX, IDC_Texosd_EDIT4, m_TxtOSD1);
	DDX_Text(pDX, IDC_Texosd_EDIT5, m_TxtOSD2);
	DDX_Text(pDX, IDC_PictureFile_EDIT, m_PicFile);
	DDX_Check(pDX, IDC_TEXTTRAN_CHECK1, m_TxtTranCheck1);
	DDX_Check(pDX, IDC_TEXTTRAN_CHECK2, m_TxtTranCheck2);
	DDX_Check(pDX, IDC_TEXTOSD_CHECK1, m_TxtOsdCheck1);
	DDX_Check(pDX, IDC_TEXTOSD_CHECK2, m_TxtOsdCheck2);
	DDX_Check(pDX, IDC_TIMETRAN_CHECK, m_TimeTranCheck);
	DDX_Text(pDX, IDC_TimePlaceX_EDIT, m_TimePlaceX);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(OSDSetting, CDialog)
	//{{AFX_MSG_MAP(OSDSetting)
	ON_BN_CLICKED(IDC_TIMEOSD_CHECK, OnTimeosdCheck)
	ON_BN_CLICKED(IDC_BUTTON_COLOR2, OnButtonColor2)
	ON_BN_CLICKED(IDC_BUTTON_COLOR3, OnButtonColor3)
	ON_BN_CLICKED(IDC_BUTTON_COLOR1, OnButtonColor1)
	ON_BN_CLICKED(IDC_OPENFILE_BUTTON, OnOpenfileButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// OSDSetting message handlers

void OSDSetting::OnOK() 
{
	// TODO: Add extra validation here
		//time osd place para


	 
	GetDlgItem(IDC_TimePlaceX_EDIT)->GetWindowText( m_TimePlaceX);
	GetDlgItem(IDC_TimePlaceY_EDIT)->GetWindowText( m_TimePlaceY);
    TosdInfo[dwCard].TimeX=atoi(m_TimePlaceX);
	TosdInfo[dwCard].TimeY=atoi(m_TimePlaceY);
	// txt osd place para

	GetDlgItem(IDC_TEXTPlaceX_EDIT1)->GetWindowText( m_TxtPlaceX1);
	GetDlgItem(IDC_TEXTPlaceX_EDIT2)->GetWindowText( m_TxtPlaceX2);
	GetDlgItem(IDC_TextPlaceY_EDIT1)->GetWindowText( m_TxtPlaceY1);
	GetDlgItem(IDC_TextPlaceY_EDIT2)->GetWindowText( m_TxtPlaceY2);
	TosdInfo[dwCard].TxtPlaceX[0]=atoi(m_TxtPlaceX1);
	TosdInfo[dwCard].TxtPlaceX[1]=atoi(m_TxtPlaceX2);
	TosdInfo[dwCard].TxtPlaceY[0]=atoi(m_TxtPlaceY1);
	TosdInfo[dwCard].TxtPlaceY[1]=atoi(m_TxtPlaceY2);
	//picture osd place para

	GetDlgItem(IDC_PicturePlaceX_EDIT)->GetWindowText( m_PicPlaceX);
	GetDlgItem(IDC_PicturePlaceY_EDIT)->GetWindowText( m_PicPlaceY);
	TosdInfo[dwCard].PicPlaceX[0]=atoi(m_PicPlaceX);
	TosdInfo[dwCard].PicPlaceY[0]=atoi(m_PicPlaceY);

	GetDlgItem(IDC_TimeFontSize_EDIT1)->GetWindowText( m_TimeFontSize);
	GetDlgItem(IDC_TextFontSize_EDIT1)->GetWindowText( m_TxtFontSize1);
	GetDlgItem(IDC_TextFontSize_EDIT2)->GetWindowText( m_TxtFontSize2);
	TosdInfo[dwCard].TimeFontSizeVal=atoi(m_TimeFontSize);
	TosdInfo[dwCard].TxtFontSizeVal[0]=atoi(m_TxtFontSize1);
	TosdInfo[dwCard].TxtFontSizeVal[1]=atoi(m_TxtFontSize2);



	TosdInfo[dwCard].TxtColor[0]=RGB(0,255,0);
	TosdInfo[dwCard].TxtColor[1]=RGB(0,255,0);
	TosdInfo[dwCard].TimeColor=RGB(0,255,0);
	TosdInfo[dwCard].BackColor =RGB(0,0,0);
	

 	 CString OsdTxt1,OsdTxt2;
	 GetDlgItem(IDC_Texosd_EDIT4)->GetWindowText( m_TxtOSD1);
	 GetDlgItem(IDC_Texosd_EDIT4)->GetWindowText( m_TxtOSD2);
	 TosdInfo[dwCard].Osd_Txtstring[0]=m_TxtOSD1;
	 TosdInfo[dwCard].Osd_Txtstring[1]=m_TxtOSD2;

	 GetDlgItem(IDC_Texosd_EDIT4)->GetWindowText( m_TxtOSD1);
	 GetDlgItem(IDC_Texosd_EDIT4)->GetWindowText( m_TxtOSD2);

	TosdInfo[dwCard].TxtFont[0]=	TEXT("Arial");
	TosdInfo[dwCard].TxtFont[1]=	TEXT("Arial");
	TosdInfo[dwCard].TimeFont=TEXT("Arial");



	// time osd setting
	
	if(BST_CHECKED==((CButton*)GetDlgItem(IDC_TIMEOSD_CHECK))->GetCheck())
	{
			if(BST_CHECKED==((CButton*)GetDlgItem(IDC_TIMETRAN_CHECK))->GetCheck())
			{
				//time osd setting
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
										   
				
				
				
			}
			else
			{
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
											false,
											255);
			}
			//enable time osd 
	
			m_DeviceControl.StartOsd(CDlgDemoDlg::DeviceInfo[dwCard].dwChannelHandle,0,0,true);
			
	}
	else

	{
			//cancel time osd
		m_DeviceControl.StartOsd (CDlgDemoDlg::DeviceInfo[dwCard].dwChannelHandle,0,0,false);
		
	}

	    //text1 osd setting
	if(BST_CHECKED==((CButton*)GetDlgItem(IDC_TEXTOSD_CHECK1))->GetCheck())
	{
		
			if(BST_CHECKED==((CButton*)GetDlgItem(IDC_TEXTTRAN_CHECK1))->GetCheck())
			{
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
			}
			else
			{
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
											false,
											255);
			}
			//enable txt1 osd 
			m_DeviceControl.StartOsd (CDlgDemoDlg::DeviceInfo[dwCard].dwChannelHandle,1,0,true);

	}
	else

	{
			
			//enable txt1 osd 
	//	m_DeviceControl.StartOsd (CDlgDemoDlg::DeviceInfo[dwCard].dwChannelHandle,1,0,false);
	}
		
			//text2 osd setting
	if(BST_CHECKED==((CButton*)GetDlgItem(IDC_TEXTOSD_CHECK2))->GetCheck())
	{
			
			if(BST_CHECKED==((CButton*)GetDlgItem(IDC_TEXTTRAN_CHECK2))->GetCheck())
			{
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
			}
			else
			{
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
											false,
											255);
			}
				//enable txt2 osd 
			m_DeviceControl.StartOsd (CDlgDemoDlg::DeviceInfo[dwCard].dwChannelHandle,1,1,true);
	}
	else

	{


			//enable txt2 osd 
	//	m_DeviceControl.StartOsd (CDlgDemoDlg::DeviceInfo[dwCard].dwChannelHandle,1,1,false);
	}
	//picture osd setting
	if(BST_CHECKED==((CButton*)GetDlgItem(IDC_PICTUREOSD_CHECK))->GetCheck())
	{
			if(BST_CHECKED==((CButton*)GetDlgItem(IDC_PICTUREOSD_CHECK))->GetCheck())
			{
				m_DeviceControl.SetOSDPara(CDlgDemoDlg::DeviceInfo[dwCard].dwChannelHandle,
											2,
											0,
											TosdPara[dwCard].PicOsdFile,
											TosdInfo[dwCard].PicPlaceX[0],
											TosdInfo[dwCard].PicPlaceY[0],
											TosdInfo[dwCard].TxtFontSizeVal[1],
											TosdInfo[dwCard].TxtFont[1],
											TosdInfo[dwCard].TxtColor [1],
											TosdInfo[dwCard].BackColor ,
											true,
											80);
			}
			else
			{
				m_DeviceControl.SetOSDPara(CDlgDemoDlg::DeviceInfo[dwCard].dwChannelHandle,
											2,
											0,
											TosdPara[dwCard].PicOsdFile,
											TosdInfo[dwCard].PicPlaceX[0],
											TosdInfo[dwCard].PicPlaceY[0],
											TosdInfo[dwCard].TxtFontSizeVal[1],
											TosdInfo[dwCard].TxtFont[1],
											TosdInfo[dwCard].TxtColor [1],
											TosdInfo[dwCard].BackColor ,
											false,
											0);
			}

			//	m_DeviceControl.StartOsd (CDlgDemoDlg::DeviceInfo[dwCard].dwChannelHandle,2,0,true);
	}
	CDialog::OnOK();
}

void OSDSetting::OnTimeosdCheck() 
{
	// TODO: Add your control notification handler code here
	
}

BOOL OSDSetting::OnInitDialog() 
{
	CDialog::OnInitDialog();





	
	








	



	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void OSDSetting::OnButtonColor2() 
{
	// TODO: Add your control notification handler code here
	CColorDialog dlgOSDColor(TosdInfo[dwCard].TxtColor[0], CC_RGBINIT, NULL);

	//TXT OSD 1 COLOR PARA
	if (dlgOSDColor.DoModal() == IDOK)
	{
		TosdInfo[dwCard].TxtColor[0] = dlgOSDColor.GetColor();
	}
}

void OSDSetting::OnButtonColor3() 
{
	// TODO: Add your control notification handler code here
		CColorDialog dlgOSDColor(TosdInfo[dwCard].TxtColor[1], CC_RGBINIT, NULL);

	if (dlgOSDColor.DoModal() == IDOK)
	{
		TosdInfo[dwCard].TxtColor[1] = dlgOSDColor.GetColor();
	}
}

void OSDSetting::OnButtonColor1() 
{
	// TODO: Add your control notification handler code here
	CColorDialog dlgOSDColor(TosdInfo[dwCard].TimeColor, CC_RGBINIT, NULL);

	//time osd color para
	if (dlgOSDColor.DoModal() == IDOK)
	{
		TosdInfo[dwCard].TimeColor = dlgOSDColor.GetColor();
	}
}

void OSDSetting::OnOpenfileButton() 
{
	// TODO: Add your control notification handler code here
		CString m_FilePath;
	  CFileDialog OpenFiledlg(true ,NULL,NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,NULL,NULL);
	   if(OpenFiledlg.DoModal()==IDOK)   
     { 
			   m_FilePath = OpenFiledlg.GetPathName();////////取出文件路径 
		
			  UpdateData(FALSE); 
     } 
	 	TosdPara[0].PicOsdFile=m_FilePath;
	   GetDlgItem(IDC_PictureFile_EDIT)->SetWindowText(m_FilePath);
	   
}
