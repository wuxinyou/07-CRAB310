#if !defined(AFX_VIDEOPLAYERDLG_H__D627C9B8_E9A1_4548_9325_90D507676199__INCLUDED_)
#define AFX_VIDEOPLAYERDLG_H__D627C9B8_E9A1_4548_9325_90D507676199__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VideoPlayerDlg.h : header file
//
#include "vlc.h"
#include <Afxtempl.h>

/////////////////////////////////////////////////////////////////////////////
// VideoPlayerDlg dialog

class VideoPlayerDlg : public CDialog
{
// Construction
public:

	VideoPlayerDlg(CWnd* pParent = NULL);   // standard constructor
	
	bool		m_bNew;
	
	// 	libvlc_exception_t		m_vlcEx;
	libvlc_instance_t*		m_vlcInst;
	libvlc_media_player_t*	m_vlcMplay;
	libvlc_media_t*			m_vlcMedia;
	// 
	libvlc_time_t m_TotalTime;
	// 	UINT m_TimerReturn;
	UINT_PTR m_playerTimer;
	bool m_bIsRtsp;

// Dialog Data
	//{{AFX_DATA(VideoPlayerDlg)
	enum { IDD = IDD_VIDEOPLAYER_DLG };
	CSliderCtrl	m_ctrlSliderPlayTime;
	CListBox	m_ctrlList2;
	CListBox	m_ctrlList1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(VideoPlayerDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(VideoPlayerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkVideoplayerList1();
	afx_msg void OnDblclkVideoplayerList2();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void StopVideo();
	void PlayVideo();
	void PauseVideo();
	void ShowOtherWidget(bool SWMode);
	void FullScreenShow();
	void NormalShow(void);
	
private:
	
	HWND hwndVideoPlayer ;
	CString m_VideoFilePath;
	
	//成员变量
	BOOL            m_bOpen;
	BOOL            m_bFullScreen;     // 全屏标志
	BOOL            m_bIsPlay;
	CRect           m_FullScreenRect;  // 整个屏幕尺寸
	WINDOWPLACEMENT m_OldWndPlacement; // 全屏时对话框的位置属性
	WINDOWPLACEMENT m_NewWndPlacement; // 全屏后对话框的位置属性
	WINDOWPLACEMENT m_OldPicPlacement; // 全屏时对话框的位置属性
	WINDOWPLACEMENT m_NewPicPlacement; // 全屏后对话框的位置属性


};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIDEOPLAYERDLG_H__D627C9B8_E9A1_4548_9325_90D507676199__INCLUDED_)
