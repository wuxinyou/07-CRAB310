#if !defined(AFX_MYSPLASHSCREEN_H__62204593_26D3_47EE_AE04_25E3C6E7BBB7__INCLUDED_)
#define AFX_MYSPLASHSCREEN_H__62204593_26D3_47EE_AE04_25E3C6E7BBB7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MySplashScreen.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMySplashScreen frame

class CMySplashScreen : public CStatic
{
	DECLARE_DYNCREATE(CMySplashScreen)
public:
	CMySplashScreen();           // protected constructor used by dynamic creation

// Attributes
public:
	void Create(UINT nBitmapID);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMySplashScreen)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMySplashScreen();

	// Generated message map functions
	//{{AFX_MSG(CMySplashScreen)

	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CBitmap m_bitmap;

private:
	
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSPLASHSCREEN_H__62204593_26D3_47EE_AE04_25E3C6E7BBB7__INCLUDED_)
