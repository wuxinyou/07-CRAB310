#if !defined(AFX_COMPASS_H__4686B36C_64B6_4B30_893A_FCBDE46EF64F__INCLUDED_)
#define AFX_COMPASS_H__4686B36C_64B6_4B30_893A_FCBDE46EF64F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Compass.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCompass window

class CCompass : public CStatic
{
// Construction
public:
	CCompass();

// Attributes
public:

// Operations
public:
	void DrawFan(int iAngle=0);
	void ClearScreen();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCompass)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCompass();

	// Generated message map functions
protected:
	//{{AFX_MSG(CCompass)
	afx_msg void OnPaint();
	//}}AFX_MSG
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);   //ÊÖ¶¯Ìí¼Ó

	DECLARE_MESSAGE_MAP()

private:
	CPoint m_point1,m_point2,m_pointOrigin;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMPASS_H__4686B36C_64B6_4B30_893A_FCBDE46EF64F__INCLUDED_)
