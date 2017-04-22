#if !defined(AFX_STATICBTN_H__BFD5DACA_8091_45DF_AE4B_F40EC3D1486B__INCLUDED_)
#define AFX_STATICBTN_H__BFD5DACA_8091_45DF_AE4B_F40EC3D1486B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StaticBtn.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStaticBtn window

class CStaticBtn : public CStatic
{
// Construction
public:
	CStaticBtn();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStaticBtn)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CStaticBtn();

	// Generated message map functions
protected:
	//{{AFX_MSG(CStaticBtn)
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnClicked();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:
	HBITMAP hBitmap; //ÓÃÓÚpicture¿Ø¼þÌùÍ¼
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATICBTN_H__BFD5DACA_8091_45DF_AE4B_F40EC3D1486B__INCLUDED_)
