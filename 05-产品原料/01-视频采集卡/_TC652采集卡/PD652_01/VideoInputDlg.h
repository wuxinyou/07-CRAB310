#if !defined(AFX_VIDEOINPUTDLG_H__103011B0_C4F5_4234_A872_255DAAFEBAB8__INCLUDED_)
#define AFX_VIDEOINPUTDLG_H__103011B0_C4F5_4234_A872_255DAAFEBAB8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VideoInputDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVideoInputDlg dialog

class CVideoInputDlg : public CDialog
{
// Construction
public:
	CVideoInputDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CVideoInputDlg)
	enum { IDD = IDD_VIDEO_INPUT_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVideoInputDlg)
	protected:
	virtual void OnOK();
	virtual void OnCancel();

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CVideoInputDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnRadioInputHdmi();
	afx_msg void OnRadioInputDvid();
	afx_msg void OnRadioInputComponents();
	afx_msg void OnRadioInputDvia();
	afx_msg void OnRadioInputSdi();
	afx_msg void OnRadioInputComposite();
	afx_msg void OnRadioInputSvideo();
	afx_msg void OnRadioInputAuto();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIDEOINPUTDLG_H__103011B0_C4F5_4234_A872_255DAAFEBAB8__INCLUDED_)
