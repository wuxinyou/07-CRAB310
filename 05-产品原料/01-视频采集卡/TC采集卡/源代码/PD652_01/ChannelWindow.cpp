// ChannelWindow.cpp : implementation file
//

#include "stdafx.h"
#include "pd652.h"
#include "pd652Dlg.h"
#include "ChannelWindow.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChannelWindow

CChannelWindow::CChannelWindow()
{
}

CChannelWindow::~CChannelWindow()
{
}


BEGIN_MESSAGE_MAP(CChannelWindow, CWnd)
	//{{AFX_MSG_MAP(CChannelWindow)
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CChannelWindow message handlers

BOOL CChannelWindow::OnEraseBkgnd(CDC* pDC) 
{
	pd652Dlg* pParent = (pd652Dlg*)AfxGetMainWnd();

	// TO FILL IN THE TEXT 
	//
	CFont font;

	ULONG nFontSize = 300;
		
	font.CreatePointFont( nFontSize, TEXT("Arial"), NULL );

	HFONT hOldFont = (HFONT)pDC->SelectObject( &font );

	pDC->SetBkMode( TRANSPARENT );		
		
	pDC->SetTextColor( RGB( 255, 255, 255 ) );

	if ( pParent->m_hVideoDevice == 0 ) {

		CRect rect_client;
		
		GetClientRect( &rect_client );
		
		CBrush brush_fill_rect( RGB(0, 0, 0) );

		pDC->FillRect( &rect_client, &brush_fill_rect );

		CString string = TEXT("No Device");

		pDC->DrawText( string, &rect_client, DT_SINGLELINE| DT_CENTER | DT_VCENTER );		
	}

	if ( pParent->m_bNoSignal == 1 ) {
		
		CRect rect_client;	GetClientRect( &rect_client );

		CBrush brush_fill_rect( RGB(0, 0, 255) );

		pDC->FillRect( &rect_client, &brush_fill_rect );

		CString string = TEXT("No Source");

		pDC->DrawText( string, &rect_client, DT_SINGLELINE| DT_CENTER | DT_VCENTER );		
	}
	
	pDC->SelectObject( &hOldFont );

	font.DeleteObject();

	return TRUE;
}

BOOL CChannelWindow::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

int CChannelWindow::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	return 0;
}

void CChannelWindow::OnDestroy() 
{
	CWnd::OnDestroy();
	
	// TODO: Add your message handler code here	
}

void CChannelWindow::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	pd652Dlg* pParent = (pd652Dlg*)(GetParent());

	pParent->OnLButtonDblClk_ChannelWindow();

	CWnd::OnLButtonDblClk(nFlags, point);
}

void CChannelWindow::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	pd652Dlg* pParent = (pd652Dlg*)(GetParent());

	pParent->PostMessage( 0x201, MAKELPARAM( point.x, point.y ) );
}
