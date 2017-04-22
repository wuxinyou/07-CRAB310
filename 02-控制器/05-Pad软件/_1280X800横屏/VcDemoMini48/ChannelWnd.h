#if !defined(AFX_CHANNELWND_H__A73E4EA3_5A0D_4DC9_953D_CD8DDC52B632__INCLUDED_)
#define AFX_CHANNELWND_H__A73E4EA3_5A0D_4DC9_953D_CD8DDC52B632__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChannelWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChannelWnd window

#define WM_CHANNEL_SET_FOCUS	(WM_USER+10)
#define WM_LBTNDBLCLK_SHOWWIN   WM_USER + 100


class CChannelWnd : public CWnd
{
// Construction
public:
	CChannelWnd();

	BOOL Create(UINT uID, RECT &rect, CWnd *pParentWnd,
		DWORD dwStyle = WS_CLIPCHILDREN | WS_TABSTOP | WS_VISIBLE | WS_CHILDWINDOW);
// Attributes
public:

// Operations
public:
	void SetBKBmp(unsigned short BmpID);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChannelWnd)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CChannelWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CChannelWnd)
	afx_msg void OnPaint();
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	UINT	m_id;
private:
	unsigned short m_BKbmpID;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHANNELWND_H__A73E4EA3_5A0D_4DC9_953D_CD8DDC52B632__INCLUDED_)
