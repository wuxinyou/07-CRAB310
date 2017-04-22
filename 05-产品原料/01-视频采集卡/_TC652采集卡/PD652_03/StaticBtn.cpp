// StaticBtn.cpp : implementation file
//

#include "stdafx.h"
#include "dlgDemo.h"
#include "StaticBtn.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStaticBtn

CStaticBtn::CStaticBtn()
{

}

CStaticBtn::~CStaticBtn()
{
}


BEGIN_MESSAGE_MAP(CStaticBtn, CStatic)
	//{{AFX_MSG_MAP(CStaticBtn)
	ON_WM_LBUTTONDBLCLK()
	ON_CONTROL_REFLECT(BN_CLICKED, OnClicked)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStaticBtn message handlers








void CStaticBtn::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	
	CStatic::OnLButtonDblClk(nFlags, point);
}

void CStaticBtn::OnClicked() 
{
	// TODO: Add your control notification handler code here
	static int clickTimes=0;
	clickTimes++;
	if(clickTimes>=5)
		clickTimes=1;

	switch(clickTimes)
	{
	case 1:
		hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_CHANNEL1)); 
		break;
	case 2:
		hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_CHANNEL2)); 
		break;
	case 3:
		hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_CHANNEL3)); 
		break;
	case 4:
		hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_CHANNEL4)); 
		break;
	default:
		break;
	}
	
	this->SetBitmap(hBitmap);                
	if(hBitmap)
		DeleteObject(hBitmap);
	
}
