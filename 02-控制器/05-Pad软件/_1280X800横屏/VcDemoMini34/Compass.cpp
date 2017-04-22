// Compass.cpp : implementation file
//

#include "stdafx.h"
//	#include "DrawShanDlg.h"
#include "dlgDemo.h"
#include "Compass.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCompass

CCompass::CCompass()
{
}

CCompass::~CCompass()
{
}


BEGIN_MESSAGE_MAP(CCompass, CStatic)
	//{{AFX_MSG_MAP(CCompass)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
	ON_WM_ERASEBKGND()  //手动添加
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCompass message handlers


BOOL CCompass::OnEraseBkgnd(CDC* pDC) 
{
	CWnd::OnEraseBkgnd(pDC);
	//
		////////////////////////////贴图////////////////////////
	CBitmap bitmap;
	bitmap.LoadBitmap(IDB_BITMAP_COMPASS);
	
	BITMAP bmp;
	bitmap.GetBitmap(&bmp);

	
	
	CDC dcCompatible;
	dcCompatible.CreateCompatibleDC(pDC);
	
	dcCompatible.SelectObject(&bitmap);
	
	CRect rect;
	this->GetClientRect(&rect);
	//pDC->BitBlt(0,0,rect.Width(),rect.Height(),&dcCompatible,0,0,SRCCOPY);    //1:1 贴图
	pDC->StretchBlt(0,0,rect.Width(),rect.Height(),&dcCompatible,0,0,bmp.bmWidth,bmp.bmHeight,SRCCOPY);  //缩放贴图

////////////////////////////////贴图完成///////////////////////////////////////////
	return true;

}

void CCompass::DrawFan(int iAngle)
{
		CClientDC dc(this);
		CPen pen(PS_SOLID,1,RGB(10,150,0));
		CPen *pOldPen=dc.SelectObject(&pen);

		int r=70;

		
		m_pointOrigin.x=74;
		m_pointOrigin.y=74;
		
		m_point2=m_pointOrigin;		
		
		int i=0;

		double angle=0;
		for(i=-30+iAngle;i<30+iAngle;i++)
		{
			angle=i*3.14159/180;
			int cx=(int)r*sin(angle);
			int cy=(int)r*cos(angle);
			
			m_point1.x=m_pointOrigin.x+cx;
			m_point1.y=m_pointOrigin.y-cy;
			
			dc.MoveTo(m_pointOrigin);
			dc.LineTo(m_point1);
			dc.MoveTo(m_point1);
			dc.LineTo(m_point2);
			m_point2=m_point1;	
			
		}
		
		dc.SelectObject(pOldPen);
	
}

void CCompass::ClearScreen()
{
	Invalidate(true);
	UpdateWindow();
}

void CCompass::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
//	dc.MoveTo(CPoint(0,0));
//	dc.LineTo(CPoint(50,50));
	
	// Do not call CStatic::OnPaint() for painting messages
}
