#if !defined(AFX_3DSSHOW_H__E5CBF092_FBB0_48E1_BBC8_F0316C410EBC__INCLUDED_)
#define AFX_3DSSHOW_H__E5CBF092_FBB0_48E1_BBC8_F0316C410EBC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// 3DSShow.h : header file
//
#include "3ds.h"

/////////////////////////////////////////////////////////////////////////////
// C3DSShow window

class C3DSShow : public CStatic
{
// Construction
public:
	C3DSShow();
	
	HDC		hDC;
	int	 Width,Height;
	HGLRC m_hGLContext;
	int m_GLPixelIndex;
	HPALETTE	m_hPalette;		//OpenGL调色板
	
	void	InitCWnd();
	BOOL	CreateViewGLContext(HDC hDC);
	BOOL	SetWindowPixelFormat(HDC hDC);
	void	SetLogicalPalette(void);//设置逻辑调色板
	void	Render();
	////////////////////////////////////////////////////////////
	void	load3dobj(char* dir,char* cn,int a);
	BOOL	Scene(int obj,float x,float h,float z,float r,int re,float size);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(C3DSShow)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~C3DSShow();

	void setRotateParm(GLfloat angleX, GLfloat angleY);

	// Generated message map functions
protected:
	//{{AFX_MSG(C3DSShow)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:
	CLoad3DS *m_3ds;
	CLoad3DS *m_3ds_compass;
	int r;
	/////相应鼠标的变量
	GLfloat m_rotateAngleX;
	GLfloat m_rotateAngleY;
	
	CPoint m_pointOrigin,m_pointTerminal;
	BOOL  m_lButtonDown;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_3DSSHOW_H__E5CBF092_FBB0_48E1_BBC8_F0316C410EBC__INCLUDED_)
