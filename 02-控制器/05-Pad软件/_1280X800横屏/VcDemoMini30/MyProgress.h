#if !defined(AFX_MYPROGRESS_H__2AD3D52A_2C36_4E60_AB9F_A8B883FD1890__INCLUDED_)
#define AFX_MYPROGRESS_H__2AD3D52A_2C36_4E60_AB9F_A8B883FD1890__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyProgress.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// MyProgress window

class MyProgress : public CProgressCtrl
{
// Construction
public:
	MyProgress();

// Attributes
public:

// Operations
public:
	int SetPos(int nPos);
	void SetRange(int nLower, int nUpper);
	void SetColor(COLORREF prgsColor,COLORREF freeColor,COLORREF prgsTextColor, COLORREF freeTextColor);
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MyProgress)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~MyProgress();

	// Generated message map functions
protected:
	//{{AFX_MSG(MyProgress)
		// NOTE - the ClassWizard will add and remove member functions here.

	afx_msg void OnPaint();
	//}}AFX_MSG
	
private:
	COLORREF m_prgsColor; //进度条进度部分颜色
    COLORREF m_freeColor; //进度条后面空余部分颜色
    COLORREF m_prgsTextColor; //进度部分字体颜色
    COLORREF m_freeTextColor; //空白部分字体颜色
    int  m_iMin;    //进度条的最小值，通常是0
    int  m_iMax;    //进度条的最大值，通常是100
    int  m_iPos;    //当前的进度
    int  m_nBarWidth;  //进度条宽度

	
	
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYPROGRESS_H__2AD3D52A_2C36_4E60_AB9F_A8B883FD1890__INCLUDED_)
