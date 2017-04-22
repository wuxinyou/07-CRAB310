// dlgDemoDlg.h : header file
//

#if !defined(AFX_DLGDEMODLG_H__AAA927C3_2E40_4508_95B9_65DB11951266__INCLUDED_)
#define AFX_DLGDEMODLG_H__AAA927C3_2E40_4508_95B9_65DB11951266__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "datastru.h"
#include "DXMediaCap.h"
#include "BtnST.h"




/////////////////////////////////////////////////////////////////////////////
// CDlgDemoDlg dialog

class CDlgDemoDlg : public CDialog
{
// Construction
public:
	CDlgDemoDlg(CWnd* pParent = NULL);	// standard constructor

    static int 			m_nDevNum;
	 static int 			m_PreviewMode;
    static  int             m_OpenSata;
	 int             m_StartPreview;
	unsigned int             m_VidStandard;
	unsigned int             m_Width;
	unsigned int             m_Height;
	unsigned int             m_Colorspace;
	float             m_FrameRate;
	static  device_handle	m_device;
	static	DEVICE_TAG VideoTags[100];
	static	DEVICE_TAG AudioTags[100];
	static DEVICE_INFO  DeviceInfo[23];

// Dialog Data
	//{{AFX_DATA(CDlgDemoDlg)
	enum { IDD = IDD_DLGDEMO_DIALOG };
	CButtonST	m_settingBtn;
	CButtonST	m_exitBtn;
	CButtonST	m_recordBtn;
	CButtonST	m_snapBtn;
	CStatic	m_PrvHwnd;
	CButton	m_bt_CallBack;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
		WNDCLASSEX             m_wc;
	char          m_strClassname[50];
	// Generated message map functions
	//{{AFX_MSG(CDlgDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtStep00();
	afx_msg void OnBtStep01();
	afx_msg void OnBtStep02();
	afx_msg void OnBtStep03();
	afx_msg void OnBtStep04();
	afx_msg void OnBtAssignAudio();
	afx_msg void OnBtPcolor();
	afx_msg void OnBtBmp();
	afx_msg void OnBtJpg();
	//	afx_msg void OnBtCallback();
	afx_msg void OnBtDrawfile();
	afx_msg void OnBtHidefile();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnBtTextosd();
	afx_msg void OnBtImageosd();
	afx_msg void OnBtTimeosd();
	afx_msg void OnBtFlipvideo();
	afx_msg void OnBtMirrorvideo();
	afx_msg void OnBtBufdisplay();
	afx_msg void OnBtSource();
	afx_msg void OnSourAv1();
	afx_msg void OnSourAv2();
	afx_msg void OnSourSvideo();
	afx_msg void OnSizeD1();
	afx_msg void OnSizeCif();
	afx_msg void OnStandNtsc();
	afx_msg void OnStandPal();
	afx_msg void OnUpdateSourAv1(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSourAv2(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSourSvideo(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSizeD1(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSizeCif(CCmdUI* pCmdUI);
	afx_msg void OnUpdateStandNtsc(CCmdUI* pCmdUI);
	afx_msg void OnUpdateStandPal(CCmdUI* pCmdUI);
	afx_msg void OnFlipVideo();
	afx_msg void OnUpdateFlipVideo(CCmdUI* pCmdUI);
	afx_msg void OnMirrorVideo();
	afx_msg void OnUpdateMirrorVideo(CCmdUI* pCmdUI);
	afx_msg void OnDeinterlaceCANCEL();
	afx_msg void OnUpdateDeinterlaceCANCEL(CCmdUI* pCmdUI);
	afx_msg void OnDeinterlaceGOOD();
	afx_msg void OnUpdateDeinterlaceGOOD(CCmdUI* pCmdUI);
	afx_msg void OnDeinterlaceSTD();
	afx_msg void OnUpdateDeinterlaceSTD(CCmdUI* pCmdUI);
	//	afx_msg void OnColorPropertyButton();
	afx_msg void OnBUTTONGetBuf();
	afx_msg void OnButtonSnap();
	//	afx_msg void OnButtonCallsnap();
	afx_msg void OnButtonExit();
	afx_msg void OnBtRecord();
	afx_msg void OnButtonCodec();
	//	afx_msg void OnDenoiseStd();
	afx_msg void OnButtonPauserec();
	//	afx_msg void OnOsdsetButton();
	afx_msg void OnDestroy();
	afx_msg void OnUpdateSize960h(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSize768(CCmdUI* pCmdUI);
	afx_msg void OnSize768();
	afx_msg void OnSize960h();
	afx_msg void OnDeinterlaceLowCpu();
	afx_msg void OnUpdateDeinterlaceLowCpu(CCmdUI* pCmdUI);
//	afx_msg void OnRadioVmr7();
//	afx_msg void OnRadioOffscrean();
//	afx_msg void OnRadioVmr9();
	//	afx_msg void OnZoomButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	LRESULT OnChannelSetFocus(WPARAM wp,LPARAM lp);
	LRESULT OnLBTNDBClikShowWin(WPARAM wPara, LPARAM lParam);
 

private:

	BOOL CreateWindowClass( );            //创建窗口类
	void OnCreateWindow( DWORD dwCard ); //创建预览子窗体
	BOOL PauseRec;
	BOOL CodecSet;
	BOOL RecOK;
    BOOL bCallback ;
	image_handle	m_fileImg;
	image_handle	m_bufImg;
	DeviceControl m_DeviceControl;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGDEMODLG_H__AAA927C3_2E40_4508_95B9_65DB11951266__INCLUDED_)
