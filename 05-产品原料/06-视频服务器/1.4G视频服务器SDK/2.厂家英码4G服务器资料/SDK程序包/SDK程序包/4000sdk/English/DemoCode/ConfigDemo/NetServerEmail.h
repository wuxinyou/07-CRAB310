#if !defined(AFX_NETSERVEREMAIL_H__9FD2AD5D_80A9_4ACE_9423_104425DB25EF__INCLUDED_)
#define AFX_NETSERVEREMAIL_H__9FD2AD5D_80A9_4ACE_9423_104425DB25EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NetServerEmail.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNetServerEmail dialog

class CNetServerEmail : public CDialog
{
// Construction
public:
	void GetRecAddr();
	void SaveConfig();
	BOOL m_ensure;
	SDK_NetEmailConfig m_netEmailCfg;
	void InitDlgInfo(SDK_NetEmailConfig* pNetEmailCfg);
	CNetServerEmail(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNetServerEmail)
	enum { IDD = IDD_CONFIG_NETSERVER_EMAIL };
	CButton	m_ctlEnableSSL;
	CButton	m_ctlEnableEmail;
	CString	m_smtp;
	CString	m_sendAddr;
	CString	m_recAddr;
	CString	m_password;
	int		m_port;
	CString	m_title;
	CString	m_userName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNetServerEmail)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNetServerEmail)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnCheckEnable();
	afx_msg void OnCheckSslEnable();
	afx_msg void OnKillfocusEditPort();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NETSERVEREMAIL_H__9FD2AD5D_80A9_4ACE_9423_104425DB25EF__INCLUDED_)
