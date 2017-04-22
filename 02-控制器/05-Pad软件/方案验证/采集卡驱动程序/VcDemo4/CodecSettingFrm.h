#if !defined(AFX_CODECSETTINGFRM_H__53CE676D_EF85_4CD8_BC46_09DD62DEB7CB__INCLUDED_)
#define AFX_CODECSETTINGFRM_H__53CE676D_EF85_4CD8_BC46_09DD62DEB7CB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CodecSettingFrm.h : header file
//
#include "dlgDemoDlg.h"
/////////////////////////////////////////////////////////////////////////////
// CCodecSettingFrm dialog

class CCodecSettingFrm : public CDialog
{
// Construction
public:
	CCodecSettingFrm(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCodecSettingFrm)
	enum { IDD = IDD_CODECSETTINGFRM_DIALOG };
	CEdit	m_RecEditPath;
	CEdit	m_SnapEditPath;
	CComboBox	m_AudioCode_Comb;
	CComboBox	m_VideoCode_Comb;
	CString	m_SnapPath;
	CString	m_CapPath;
	CString	m_VidStr;
	CString	m_PicStr;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCodecSettingFrm)
	public:
	virtual void Serialize(CArchive& ar);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCodecSettingFrm)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboAudiocodec();
	afx_msg void OnSelchangeComboVideocodec();
	virtual void OnOK();
	afx_msg void OnButtonBrowseSnapdir();
	afx_msg void OnButtonBrowseRecdir();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CODECSETTINGFRM_H__53CE676D_EF85_4CD8_BC46_09DD62DEB7CB__INCLUDED_)
