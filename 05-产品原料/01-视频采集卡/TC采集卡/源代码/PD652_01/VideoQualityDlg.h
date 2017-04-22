#if !defined(AFX_VIDEOQUALITYDLG_H__462DF648_8E2E_4223_A42D_B7EEAAD68071__INCLUDED_)
#define AFX_VIDEOQUALITYDLG_H__462DF648_8E2E_4223_A42D_B7EEAAD68071__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VideoQualityDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVideoQualityDlg dialog

class CVideoQualityDlg : public CDialog
{
// Construction
public:
	CVideoQualityDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CVideoQualityDlg)
	enum { IDD = IDD_VIDEO_QUALITY_DIALOG };
	CSliderCtrl	m_sldSharpness;
	CSliderCtrl	m_sldSaturation;
	CSliderCtrl	m_sldHue;
	CSliderCtrl	m_sldConstrast;
	CSliderCtrl	m_sldBrightness;
	CString	m_staticBrightness;
	CString	m_staticContrast;
	CString	m_staticHue;
	CString	m_staticSaturation;
	CString	m_staticSharpness;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVideoQualityDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CVideoQualityDlg)
	afx_msg void OnButtonDefault();
	afx_msg void OnButtonOk();
	afx_msg void OnOutofmemorySliderBrightness(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnOutofmemorySliderConstrast(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnOutofmemorySliderHue(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnOutofmemorySliderSaturation(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnOutofmemorySliderSharpness(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	afx_msg void OnReleasedcaptureSliderBrightness(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureSliderConstrast(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureSliderHue(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureSliderSaturation(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureSliderSharpness(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIDEOQUALITYDLG_H__462DF648_8E2E_4223_A42D_B7EEAAD68071__INCLUDED_)
