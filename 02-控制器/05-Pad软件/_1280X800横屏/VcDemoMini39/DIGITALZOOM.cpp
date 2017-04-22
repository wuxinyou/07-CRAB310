// DIGITALZOOM.cpp : implementation file
//

#include "stdafx.h"
#include "dlgDemo.h"
#include "DIGITALZOOM.h"
#include "DeviceControl.h"

#include "dlgDemoDlg.h"

#include "DXMediaCap.h"

#include<windows.h>
#include<stdio.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DIGITALZOOM dialog


DIGITALZOOM::DIGITALZOOM(CWnd* pParent /*=NULL*/)
	: CDialog(DIGITALZOOM::IDD, pParent)
{
	//{{AFX_DATA_INIT(DIGITALZOOM)
	m_ZoomBot = _T("100");
	m_ZoomLeft = _T("10");
	m_ZoomRight = _T("300");
	m_ZoomTop = _T("20");
	//}}AFX_DATA_INIT
}


void DIGITALZOOM::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DIGITALZOOM)
	DDX_Text(pDX, IDC_ZOOMBOT_EDIT2, m_ZoomBot);
	DDX_Text(pDX, IDC_ZOOMLEFT_EDIT3, m_ZoomLeft);
	DDX_Text(pDX, IDC_ZOOMRIGHT_EDIT4, m_ZoomRight);
	DDX_Text(pDX, IDC_ZOOMTOP_EDIT1, m_ZoomTop);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DIGITALZOOM, CDialog)
	//{{AFX_MSG_MAP(DIGITALZOOM)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DIGITALZOOM message handlers

void DIGITALZOOM::OnOK() 
{
	// TODO: Add extra validation here

	RECT ZoomRect;
	
	GetDlgItem(IDC_ZOOMBOT_EDIT2)->GetWindowText( m_ZoomBot);
	GetDlgItem(IDC_ZOOMLEFT_EDIT3)->GetWindowText( m_ZoomLeft);
	GetDlgItem(IDC_ZOOMRIGHT_EDIT4)->GetWindowText( m_ZoomRight);
	GetDlgItem(IDC_ZOOMTOP_EDIT1)->GetWindowText( m_ZoomTop);
    ZoomRect.bottom=atoi(m_ZoomBot);
	ZoomRect.left =atoi(m_ZoomLeft);
	ZoomRect.right=atoi(m_ZoomRight);
	ZoomRect.top=atoi(m_ZoomTop);


		if(BST_CHECKED==((CButton*)GetDlgItem(IDC_ZOOM_CHECK1))->GetCheck())
		{

			if (CDlgDemoDlg::DeviceInfo[dwCard].dwConnectState)
			{
				
					DXEnFScale(CDlgDemoDlg::DeviceInfo[dwCard].dwChannelHandle,
								true,
								&ZoomRect,
								SWS_SA_FAST_BILINEAR);
									

			}

		}
		else

		{

			if (CDlgDemoDlg::DeviceInfo[dwCard].dwConnectState)
			{
				
				DXEnFScale(CDlgDemoDlg::DeviceInfo[dwCard].dwChannelHandle,
							false,
							&ZoomRect,
							SWS_SA_FAST_BILINEAR);
				
				
			}

		}
	
	CDialog::OnOK();
}
