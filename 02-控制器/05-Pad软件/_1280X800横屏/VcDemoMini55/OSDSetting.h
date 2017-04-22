#if !defined(AFX_OSDSETTING_H__1969C9A4_25C4_4ABE_B0AD_BA558602703E__INCLUDED_)
#define AFX_OSDSETTING_H__1969C9A4_25C4_4ABE_B0AD_BA558602703E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OSDSetting.h : header file
//
#include "DeviceControl.h"
#include "dlgDemoDlg.h"
/////////////////////////////////////////////////////////////////////////////
// OSDSetting dialog

class OSDSetting : public CDialog
{
// Construction
public:
	OSDSetting(CWnd* pParent = NULL);   // standard constructor


// Dialog Data
	//{{AFX_DATA(OSDSetting)
	enum { IDD = IDD_OSDSETTING_DIALOG };
	CButton	m_PicOsdCheck;
	BOOL	m_TimeOsdCheck;
	CString	m_TxtPlaceY1;
	CString	m_TxtPlaceY2;
	CString	m_TxtPlaceX1;
	CString	m_TxtPlaceX2;
	CString	m_PicPlaceX;
	CString	m_PicPlaceY;
	CString	m_TimePlaceY;
	CString	m_TxtFontSize1;
	CString	m_TxtFontSize2;
	CString	m_TimeFontSize;
	CString	m_TxtOSD1;
	CString	m_TxtOSD2;
	CString	m_PicFile;
	BOOL	m_TxtTranCheck1;
	BOOL	m_TxtTranCheck2;
	BOOL	m_TxtOsdCheck1;
	BOOL	m_TxtOsdCheck2;
	BOOL	m_TimeTranCheck;
	CString	m_TimePlaceX;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(OSDSetting)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(OSDSetting)
	virtual void OnOK();
	afx_msg void OnTimeosdCheck();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonColor2();
	afx_msg void OnButtonColor3();
	afx_msg void OnButtonColor1();
	afx_msg void OnOpenfileButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	DeviceControl  m_DeviceControl;
	TOSD_INFO TosdInfo[23];
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OSDSETTING_H__1969C9A4_25C4_4ABE_B0AD_BA558602703E__INCLUDED_)
