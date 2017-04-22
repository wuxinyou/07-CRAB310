#if !defined(AFX_CVIDEODENOISEFRM_H__6BABA8F8_E12C_4BA1_AC93_44E35F3716AF__INCLUDED_)
#define AFX_CVIDEODENOISEFRM_H__6BABA8F8_E12C_4BA1_AC93_44E35F3716AF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CVideoDenoiseFrm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCVideoDenoiseFrm dialog

class CCVideoDenoiseFrm : public CDialog
{
// Construction
public:
	CCVideoDenoiseFrm(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCVideoDenoiseFrm)
	enum { IDD = IDD_CVIDEODENOISEFRM_DIALOG };
	CSliderCtrl	m_Contrast_Silider;
	CSliderCtrl	m_Bright_Silider;
	CSliderCtrl	m_Sharp_Silider;
	CSliderCtrl	m_Denoise_Silider;
	CString	m_denoise_value;
	CString	m_Sharp_Value;
	CString	m_Bright_Value;
	int		m_SliBrightValue;
	int		m_SliContractValue;
	CString	m_Contrast_Value;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCVideoDenoiseFrm)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCVideoDenoiseFrm)
	virtual BOOL OnInitDialog();
	afx_msg void OnCustomdrawSliderDenoise(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnOK();
	afx_msg void OnCustomdrawSliderSharp(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSliderBright(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSliderContract(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CVIDEODENOISEFRM_H__6BABA8F8_E12C_4BA1_AC93_44E35F3716AF__INCLUDED_)
