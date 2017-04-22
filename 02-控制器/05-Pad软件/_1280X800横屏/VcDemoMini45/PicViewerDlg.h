#if !defined(AFX_PICVIEWERDLG_H__344B57B3_9351_455C_8501_BDE62D0A9CFE__INCLUDED_)
#define AFX_PICVIEWERDLG_H__344B57B3_9351_455C_8501_BDE62D0A9CFE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PicViewerDlg.h : header file
//

#include "pictureEx.h"
#include "BtnST.h"

/////////////////////////////////////////////////////////////////////////////
// PicViewerDlg dialog

class PicViewerDlg : public CDialog
{
// Construction
public:
	PicViewerDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(PicViewerDlg)
	enum { IDD = IDD_PICVIEWER_DLG };
	CPictureEx	m_ctrlPic;
	CListBox	m_ctrlList2;
	CListBox	m_ctrlList1;
	CButtonST	m_ctrlBtnPrev;
	CButtonST	m_ctrlBtnNext;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(PicViewerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(PicViewerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkList1();
	afx_msg void OnDblclkList2();
	afx_msg void OnBtnprev();
	afx_msg void OnBtnnext();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void ShowPicture();

private:
	CString m_PicFilePath;
//	CString VideoPath;

	int list2Index;
	int list2ItemCount;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PICVIEWERDLG_H__344B57B3_9351_455C_8501_BDE62D0A9CFE__INCLUDED_)
