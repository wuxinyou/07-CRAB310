#if !defined(AFX_SETUPDLG_H__14424584_B4D9_4085_A0F4_7E7607876F4A__INCLUDED_)
#define AFX_SETUPDLG_H__14424584_B4D9_4085_A0F4_7E7607876F4A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetupDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetupDlg dialog

class CSetupDlg : public CDialog
{
// Construction
public:
	CSetupDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSetupDlg)
	enum { IDD = IDD_SETUP_DIALOG };
	CButton	m_btnRecordStop_1_3;
	CButton	m_btnRecordStart_1_3;
	CButton	m_checkGPU_1_3;
	CEdit	m_edit_record_3;
	CButton	m_btnShowCloneVideo;
	CEdit	m_edit_record_2;
	CEdit	m_edit_record_1;
	CEdit	m_edit_jpg;
	CEdit	m_edit_bmp;
	CButton	m_checkAutoDeinterlace;
	CButton	m_btnVideoQuality;
	CButton	m_btnVideoInput;
	CButton	m_btnSnapshot_bmp;
	CButton	m_btnSnapshot_jpg;
	CButton	m_btnAudioInput;
	CButton	m_btnRecordStop_1_2;
	CButton	m_btnRecordStart_1_2;
	CButton	m_btnRecordStop_1_1;
	CButton	m_btnRecordStart_1_1;
	CButton	m_checkGPU_1_2;
	CButton	m_checkGPU_1_1;
	CStatic	m_staticDeviceFormatInformation;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetupDlg)
	protected:
	virtual void OnOK();
	virtual void OnCancel();

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSetupDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonVideoInput();
	afx_msg void OnButtonAudioInput();
	afx_msg void OnButtonVideoQuality();
	afx_msg void OnCheckAutoDeinterlace();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnButtonSnapshotBmp();
	afx_msg void OnButtonSnapshotJpg();
	afx_msg void OnButtonRecordStart11();
	afx_msg void OnButtonRecordStop11();
	afx_msg void OnButtonRecordStart12();
	afx_msg void OnButtonRecordStop12();
	afx_msg void OnDestroy();
	afx_msg void OnAvi1Radio();
	afx_msg void OnMp41Radio();
	afx_msg void OnAvi2Radio();
	afx_msg void OnMp42Radio();
	afx_msg void OnCheckShowCloneVideo();
	afx_msg void OnAvi3Radio();
	afx_msg void OnMp43Radio();
	afx_msg void OnButtonRecordStart13();
	afx_msg void OnButtonRecordStop13();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETUPDLG_H__14424584_B4D9_4085_A0F4_7E7607876F4A__INCLUDED_)
