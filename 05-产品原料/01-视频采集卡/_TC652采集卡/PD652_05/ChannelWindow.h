#if !defined(AFX_CHANNELWINDOW_H__5ADA000A_DBC5_4D6B_A072_61B1460BE13D__INCLUDED_)
#define AFX_CHANNELWINDOW_H__5ADA000A_DBC5_4D6B_A072_61B1460BE13D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChannelWindow.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChannelWindow window

class CChannelWindow : public CWnd
{
// Construction
public:
	CChannelWindow();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChannelWindow)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CChannelWindow();

	// Generated message map functions
protected:
	//{{AFX_MSG(CChannelWindow)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHANNELWINDOW_H__5ADA000A_DBC5_4D6B_A072_61B1460BE13D__INCLUDED_)
