#if !defined(AFX_ADUIOINPUTDLG_H__2397D882_EE84_4737_8063_0FD4F458427F__INCLUDED_)
#define AFX_ADUIOINPUTDLG_H__2397D882_EE84_4737_8063_0FD4F458427F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AduioInputDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAduioInputDlg dialog

class CAduioInputDlg : public CDialog
{
// Construction
public:
	CAduioInputDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAduioInputDlg)
	enum { IDD = IDD_AUDIO_INPUT_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAduioInputDlg)
	protected:
	virtual void OnOK();
	virtual void OnCancel();

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAduioInputDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnRadioInputEmbeddedAudio();
	afx_msg void OnRadioInputLinein();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADUIOINPUTDLG_H__2397D882_EE84_4737_8063_0FD4F458427F__INCLUDED_)
