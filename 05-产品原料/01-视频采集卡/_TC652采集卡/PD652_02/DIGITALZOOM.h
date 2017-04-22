#if !defined(AFX_DIGITALZOOM_H__5DF2A407_FE20_49D4_80E6_3BF0D714365A__INCLUDED_)
#define AFX_DIGITALZOOM_H__5DF2A407_FE20_49D4_80E6_3BF0D714365A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DIGITALZOOM.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DIGITALZOOM dialog

class DIGITALZOOM : public CDialog
{
// Construction
public:
	DIGITALZOOM(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DIGITALZOOM)
	enum { IDD = IDD_DIGITALZOOM_DIALOG };
	CString	m_ZoomBot;
	CString	m_ZoomLeft;
	CString	m_ZoomRight;
	CString	m_ZoomTop;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DIGITALZOOM)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DIGITALZOOM)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIGITALZOOM_H__5DF2A407_FE20_49D4_80E6_3BF0D714365A__INCLUDED_)
