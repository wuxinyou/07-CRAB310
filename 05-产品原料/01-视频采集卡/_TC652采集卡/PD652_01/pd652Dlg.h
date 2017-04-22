// StreamCatcherDemoDlg.h : header file
//

#if !defined(AFX_STREAMCATCHERDEMODLG_H__DF394323_15B8_4E17_AA4E_BFC507BE5EE2__INCLUDED_)
#define AFX_STREAMCATCHERDEMODLG_H__DF394323_15B8_4E17_AA4E_BFC507BE5EE2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ChannelWindow.h"

#include "SetupDlg.h"

/////////////////////////////////////////////////////////////////////////////
// pd652Dlg dialog

class pd652Dlg : public CDialog
{
// Construction
public:
	pd652Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(pd652Dlg)
	enum { IDD = IDD_STREAMCATCHERDEMO_DIALOG };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(pd652Dlg)
	protected:
	virtual void OnOK();
	virtual void OnCancel();
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(pd652Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:

	BOOL				OnLButtonDblClk_ChannelWindow();

	BOOL				OnButtonVideoInput_SetupDialog();

	BOOL				OnButtonAudioInput_SetupDialog();

	BOOL				OnButtonVideoQuality_SetupDialog();

	BOOL				OnButtonSnapshotJPG_SetupDialog();

	BOOL				OnButtonSnapshotBMP_SetupDialog();

	BOOL				OnButtonRecordStart1_1_SetupDialog();

	BOOL				OnButtonRecordStop1_1_SetupDialog();

	BOOL				OnButtonRecordStart1_2_SetupDialog();

	BOOL				OnButtonRecordStop1_2_SetupDialog();

	BOOL				OnButtonRecordStart1_3_SetupDialog();

	BOOL				OnButtonRecordStop1_3_SetupDialog();

	BOOL				OnCheckGpuSupport_SetupDialog();

	BOOL				OnCheckAutoDeinterlace_SetupDialog();

	BOOL				OnCheckShowCloneVideo_SetupDialog();

	BOOL				HwUninitialize();

	BOOL				HwInitialize();
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	CChannelWindow		m_oChannelWindows[ 2 ];

	CChannelWindow		m_oCloneWindows;
	
	CSetupDlg			m_oSetupDialog;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// VIDEO PROPERTIES

	PVOID 				m_hVideoDevice;

	PVOID				m_hCloneCapDev;

	ULONG				m_nVideoWidth;

	ULONG				m_nVideoHeight;

	BOOL				m_bVideoIsInterleaved;

	double				m_dVideoFrameRate;

	BOOL				m_bVideoDeinterlaceEnable;

	BOOL				m_bNoSignal;

	BOOL				m_bSupportGPU1;
	
	BOOL				m_bIsRecord1;

	BOOL				m_bSupportGPU2;
	
	BOOL				m_bIsRecord2;

	
	BOOL				m_bSupportGPU3;
	
	BOOL				m_bIsRecord3;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// AUDIO PROPERTIES

	ULONG				m_nAudioChannels;

	ULONG				m_nAudioBitsPerSample;

	ULONG				m_nAudioSampleFrequency;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// QUALITY PROPERTIES
	
	ULONG				m_nSharpness;

	ULONG				m_nSaturation;

	ULONG				m_nHue;

	ULONG				m_nConstrast;

	ULONG				m_nBrightness;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// RECORD & FILE PROPERTIES
	
	CString				m_strDefaultPath;

	CString				m_strSnapshotPath;

	CString				m_strRecordPath;

	CString				m_strRecordFileName;

	CString				m_strFormatChangedOutput;

	////////////////////////////////////////////

	PVOID 				m_hNetworkServer;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STREAMCATCHERDEMODLG_H__DF394323_15B8_4E17_AA4E_BFC507BE5EE2__INCLUDED_)
