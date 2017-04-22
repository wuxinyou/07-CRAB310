#if !defined(AFX_TXTVIEWERDLG_H__C785DCB6_C14E_44DC_9F3C_FD5E437D8D44__INCLUDED_)
#define AFX_TXTVIEWERDLG_H__C785DCB6_C14E_44DC_9F3C_FD5E437D8D44__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TxtViewerDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// TxtViewerDlg dialog

class TxtViewerDlg : public CDialog
{
// Construction
public:
	TxtViewerDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(TxtViewerDlg)
	enum { IDD = IDD_TEXTVIEWER_DLG };
	CEdit	m_ctrlEdit;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(TxtViewerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(TxtViewerDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void OpenMyFile();


};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TXTVIEWERDLG_H__C785DCB6_C14E_44DC_9F3C_FD5E437D8D44__INCLUDED_)
