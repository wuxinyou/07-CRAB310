// ConfigPtz.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "ConfigPtz.h"
#include "ClientDemo5Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfigPtz dialog


CConfigPtz::CConfigPtz(CWnd* pParent /*=NULL*/)
: CDialog(CConfigPtz::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConfigPtz)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CConfigPtz::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigPtz)
	DDX_Control(pDX, IDC_COMBO_CONFIRM, m_cmbConfirm);
	DDX_Control(pDX, IDC_COMBO_STOPPOS, m_cmbStoppos);
	DDX_Control(pDX, IDC_COMBO_DATA, m_cmbData);
	DDX_Control(pDX, IDC_COMBO_BAUDRATE, m_cmbBaundrate);
	DDX_Control(pDX, IDC_EDIT_ADDRESS, m_editAddress);
	DDX_Control(pDX, IDC_COMBO_PROTOCOL, m_cmbProtocol);
	DDX_Control(pDX, IDC_COMBO_CHANNEL, m_cmbChannel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigPtz, CDialog)
//{{AFX_MSG_MAP(CConfigPtz)
ON_BN_CLICKED(IDC_BTN_UPGRADE, OnBtnUpgrade)
ON_CBN_SELCHANGE(IDC_COMBO_CHANNEL, OnSelchangeComboChannel)
	ON_EN_CHANGE(IDC_EDIT_ADDRESS, OnChangeEditAddress)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigPtz message handlers

void CConfigPtz::OnBtnUpgrade() 
{
	// TODO: Add your control notification handler code here
	CleanAll();
	((CClientDemo5Dlg *)AfxGetMainWnd())->GetPTZConfigInfo();
}

void CConfigPtz::OnOK() 
{
	// TODO: Add extra validation here
	if ( m_cmbChannel.GetCurSel() != -1)
	{
		SavePtzInfo();
		((CClientDemo5Dlg *)AfxGetMainWnd())->SetPtzConfigInfo(&m_PtzCfgAll);
	}
}

void CConfigPtz::OnSelchangeComboChannel() 
{
	// TODO: Add your control notification handler code here
	int nIndex = m_cmbChannel.GetCurSel();
	if (nIndex == m_nChannelNum)
	{
		ShowPtzInfo(0);
		m_nLastChannel = nIndex;
	}else
	{
		if(m_nLastChannel == m_nChannelNum)
		{
			ShowPtzInfo(nIndex);
			m_nLastChannel = nIndex;
		}else if (nIndex != m_nLastChannel)
		{
			SavePtzInfo();
			m_nLastChannel = nIndex;
			ShowPtzInfo(nIndex);
		}
	}
}

BOOL CConfigPtz::OnInitDialog() 
{
	CDialog::OnInitDialog();
	_CWndCS(this);
	// TODO: Add extra initialization here
	m_editAddress.SetLimitText(4);
	
	m_cmbStoppos.AddString("1");
	m_cmbStoppos.AddString("2");
	
	m_cmbData.AddString("5");
	m_cmbData.AddString("6");
	m_cmbData.AddString("7");
	m_cmbData.AddString("8");
	
	m_cmbConfirm.AddString(_CS("ConfigPtz.None"));
	m_cmbConfirm.AddString(_CS("ConfigPtz.Odd"));
	m_cmbConfirm.AddString(_CS("ConfigPtz.Even"));
	m_cmbConfirm.AddString(_CS("ConfigPtz.Mark"));
	m_cmbConfirm.AddString(_CS("ConfigPtz.Space"));
	
	m_cmbBaundrate.AddString("1200");
	m_cmbBaundrate.AddString("2400");
	m_cmbBaundrate.AddString("4800");
	m_cmbBaundrate.AddString("9600");
	m_cmbBaundrate.AddString("19200");
	m_cmbBaundrate.AddString("38400");
	m_cmbBaundrate.AddString("57600");
	m_cmbBaundrate.AddString("115200");
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CConfigPtz::InitDlgInfo(SDK_STR_PTZCONFIG_ALL *pPtzCfgAll, int nChannel, SDK_PTZPROTOCOLFUNC *pPtzProtocol)
{
	CString str = "";
	int nIndex = 0;
	m_cmbChannel.ResetContent();
	int i = 0;
	for (;i < nChannel;i++)
	{
		str.Format(_T("%d"),i+1);
		nIndex = m_cmbChannel.AddString(str);
		m_cmbChannel.SetItemData(nIndex,i);
	}
	nIndex = m_cmbChannel.AddString(_CS("OneClick.All"));
	m_cmbChannel.SetItemData(nIndex,nChannel);
	
	m_cmbChannel.SetCurSel(0);
	m_nChannelNum = nChannel;
	m_nLastChannel = 0;
	
	if ( pPtzCfgAll!= NULL && pPtzProtocol != NULL)
	{
		memcpy(&m_PtzCfgAll,pPtzCfgAll,sizeof(SDK_STR_PTZCONFIG_ALL));
		memcpy(&m_PtzProtocol,pPtzProtocol,sizeof(SDK_PTZPROTOCOLFUNC));
	}
	
	for ( i = 0 ;i<pPtzProtocol->nProNum;i++)
	{
		m_cmbProtocol.AddString(pPtzProtocol->vPTZProtocol[i]);
	}
	ShowPtzInfo(0);
}

void CConfigPtz::ShowPtzInfo(int nIndex)
{
	for (int i = 0 ;i < m_cmbProtocol.GetCount();i++)
	{
		m_cmbProtocol.SetCurSel(i);
		CString strTemp;
		m_cmbProtocol.GetWindowText(strTemp);
		if (strTemp == m_PtzCfgAll.ptzAll[nIndex].sProtocolName)
		{
			break;
		}
	}

	CString strTemp;
	strTemp.Format("%d", m_PtzCfgAll.ptzAll[nIndex].ideviceNo);
	m_editAddress.SetWindowText(strTemp);
	
	strTemp.Format("%d", m_PtzCfgAll.ptzAll[nIndex].dstComm.iBaudRate);
	m_cmbBaundrate.SelectString(-1,strTemp);
	
	strTemp.Format("%d", m_PtzCfgAll.ptzAll[nIndex].dstComm.iDataBits );
	m_cmbData.SelectString(-1, strTemp);
	
	strTemp.Format("%d", m_PtzCfgAll.ptzAll[nIndex].dstComm.iStopBits );
	m_cmbStoppos.SelectString(-1, strTemp);
	
	m_cmbConfirm.SetCurSel(m_PtzCfgAll.ptzAll[nIndex].dstComm.iParity );
}

void CConfigPtz::SavePtzInfo()
{
	int nIndex = m_cmbChannel.GetCurSel();
	if (nIndex == m_nChannelNum)
	{
		for (int i = 0;i<m_nChannelNum;i++)
		{
			CString strTemp;
			m_editAddress.GetWindowText(strTemp);
			m_PtzCfgAll.ptzAll[i].ideviceNo = atoi( strTemp.GetBuffer(0) );
			
			m_cmbData.GetWindowText(strTemp);
			m_PtzCfgAll.ptzAll[i].dstComm.iDataBits = atoi( strTemp.GetBuffer(0) );
			
			m_cmbBaundrate.GetWindowText(strTemp);
			m_PtzCfgAll.ptzAll[i].dstComm.iBaudRate = atoi( strTemp.GetBuffer(0) );
			
			m_cmbStoppos.GetWindowText(strTemp);
			m_PtzCfgAll.ptzAll[i].dstComm.iStopBits = atoi( strTemp.GetBuffer(0) );
			
			m_PtzCfgAll.ptzAll[i].dstComm.iParity = m_cmbConfirm.GetCurSel();
			
			m_cmbProtocol.GetWindowText(strTemp);
	        strcpy ( m_PtzCfgAll.ptzAll[i].sProtocolName, strTemp.GetBuffer(0) ); 
		}
	}else
	{
		CString strTemp;
		m_editAddress.GetWindowText(strTemp);
		m_PtzCfgAll.ptzAll[m_nLastChannel].ideviceNo = atoi( strTemp.GetBuffer(0) );
		
		m_cmbData.GetWindowText(strTemp);
		m_PtzCfgAll.ptzAll[m_nLastChannel].dstComm.iDataBits = atoi( strTemp.GetBuffer(0) );
		
		m_cmbBaundrate.GetWindowText(strTemp);
		m_PtzCfgAll.ptzAll[m_nLastChannel].dstComm.iBaudRate = atoi( strTemp.GetBuffer(0) );
		
		m_cmbStoppos.GetWindowText(strTemp);
		m_PtzCfgAll.ptzAll[m_nLastChannel].dstComm.iStopBits = atoi( strTemp.GetBuffer(0) );
		
		m_PtzCfgAll.ptzAll[m_nLastChannel].dstComm.iParity = m_cmbConfirm.GetCurSel();
		
		m_cmbProtocol.GetWindowText(strTemp);
	    strcpy ( m_PtzCfgAll.ptzAll[m_nLastChannel].sProtocolName, strTemp.GetBuffer(0) ); 
	}
}

void CConfigPtz::CleanAll()
{
	m_cmbChannel.ResetContent();
	SetDlgItemText(IDC_EDIT_ADDRESS,_T(""));
	m_cmbProtocol.ResetContent();
	m_cmbBaundrate.SetCurSel(-1);
	m_cmbData.SetCurSel(-1);
	m_cmbStoppos.SetCurSel(-1);
	m_cmbConfirm.SetCurSel(-1);
}

void CConfigPtz::OnChangeEditAddress() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	CString strTemp;
	int iDeviceAddress;
	
	UpdateData();
	m_editAddress.GetWindowText(strTemp);
	
	iDeviceAddress = atoi(strTemp.GetBuffer(0));
	if (iDeviceAddress > 255)
	{
		CString strAddress;
		strAddress.Format("%d", 255);
		m_editAddress.SetWindowText(strAddress);
	}
	if (iDeviceAddress < 0)
	{
		CString strAddress;
		strAddress.Format("%d", 0);
		m_editAddress.SetWindowText(strAddress);
	}
}
