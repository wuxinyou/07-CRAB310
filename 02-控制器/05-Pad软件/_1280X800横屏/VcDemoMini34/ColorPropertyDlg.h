#include "afxwin.h"
#if !defined(AFX_COLORPROPERTYDLG_H__3032A601_63C1_4BDE_8D7B_BF440283D5F8__INCLUDED_)
#define AFX_COLORPROPERTYDLG_H__3032A601_63C1_4BDE_8D7B_BF440283D5F8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ColorPropertyDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CColorPropertyDlg dialog

class CColorPropertyDlg : public CDialog
{
// Construction
public:
	CColorPropertyDlg(CWnd* pParent = NULL);   // standard constructor

	 static struct Device_ColorProp
        {
            long MinVal;
            long MaxVal;
            long StepVal;
            long DefaultVal;
            long CurVal;


        };

// Dialog Data
	//{{AFX_DATA(CColorPropertyDlg)
	enum { IDD = IDD_COLORPROPERTYDLG_DIALOG };
	CSliderCtrl	m_conHue;
	CSliderCtrl	m_conSharpness;
	CSliderCtrl	m_conSaturation;
	CSliderCtrl	m_conContrast;
	CSliderCtrl	m_conBrightness;
	CString	m_strBrightness;
	CString	m_strContrast;
	CString	m_strSaturation;
	CString	m_strHue;
	CString	m_strSharpness;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorPropertyDlg)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:


  

	// Generated message map functions
	//{{AFX_MSG(CColorPropertyDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnOk2();
	afx_msg void OnCustomdrawBrightnessSlider(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawContrastSlider(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSaturationSlider(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSharpnessSlider(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawHueSlider(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnOkexit();
	afx_msg void OnDefColorButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORPROPERTYDLG_H__3032A601_63C1_4BDE_8D7B_BF440283D5F8__INCLUDED_)
