// MySplashScreen.cpp : implementation file
//

#include "stdafx.h"
#include "dlgDemo.h"
#include "MySplashScreen.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMySplashScreen

IMPLEMENT_DYNCREATE(CMySplashScreen, CStatic)

CMySplashScreen::CMySplashScreen()
{
}

CMySplashScreen::~CMySplashScreen()
{
}


BEGIN_MESSAGE_MAP(CMySplashScreen, CStatic)
	//{{AFX_MSG_MAP(CMySplashScreen)

	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMySplashScreen message handlers



void CMySplashScreen::Create(UINT nBitmapID)
{
	m_bitmap.LoadBitmap(nBitmapID);
	BITMAP bitmap;
	m_bitmap.GetBitmap(&bitmap);
	int x=(::GetSystemMetrics(SM_CXSCREEN)-bitmap.bmWidth)/2;
	int y=(::GetSystemMetrics(SM_CYSCREEN)-bitmap.bmHeight)/2;
	CRect rect(x,y,x+bitmap.bmWidth,y+bitmap.bmHeight);
	CreateEx(0,AfxRegisterWndClass(0),"",WS_POPUP|WS_VISIBLE,rect,NULL,0);
}

void CMySplashScreen::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	BITMAP bitmap;
	m_bitmap.GetBitmap(&bitmap);
	CDC dcComp;
	dcComp.CreateCompatibleDC(&dc);
	dcComp.SelectObject(&m_bitmap);
	// draw bitmap
	dc.BitBlt(0,0,bitmap.bmWidth,bitmap.bmHeight,&dcComp,0,0,SRCCOPY);
	
	// Do not call CFrameWnd::OnPaint() for painting messages
}
