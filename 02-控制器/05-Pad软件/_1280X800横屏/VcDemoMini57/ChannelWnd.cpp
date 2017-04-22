// ChannelWnd.cpp : implementation file
//

#include "stdafx.h"
#include "dlgDemo.h"
#include "ChannelWnd.h"
#include "dlgDemoDlg.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define CLASS_CVideoWndEx		"CChannelWnd"

CChannelWnd::CChannelWnd()
{
	m_BKbmpID=0;
}

CChannelWnd::~CChannelWnd()
{
}


BEGIN_MESSAGE_MAP(CChannelWnd, CWnd)
	//{{AFX_MSG_MAP(CChannelWnd)
	ON_WM_PAINT()
	ON_WM_MOUSEACTIVATE()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CChannelWnd message handlers
//预览窗体消息处理函数
LRESULT CALLBACK ClientWndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	DWORD dwCard = 0;
	//::AfxMessageBox(_T("eeee windows class false"));
	switch(msg)
	{
	case WM_COMMAND:
		break;
	case WM_PAINT:
		break;
	case WM_MOVE:
		break;
	case WM_SIZE:
		
		break;
		
	case WM_DESTROY:
		break;
	case WM_SHOWWINDOW:
		
		break;
		
	case WM_LBUTTONDOWN:
			break;
	case WM_MOUSEMOVE:
		break;
	case WM_LBUTTONUP:
		
		
		break;
	case WM_LBUTTONDBLCLK:
		{
					
		}
		
	}
	
	return DefWindowProc(hWnd, msg, wParam, lParam);
}
BOOL CChannelWnd::PreCreateWindow(CREATESTRUCT& cs) 
{
	WNDCLASS wc		 = {0};
	wc.style         = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc   = ClientWndProc;//::DefWindowProc;
	wc.hInstance     = AfxGetInstanceHandle();
	wc.lpszClassName = CLASS_CVideoWndEx;
	wc.hbrBackground = CreateSolidBrush(RGB(0,0,0));
	wc.hCursor       = LoadCursor( NULL, IDC_ARROW );
	if(!AfxRegisterClass(&wc))
		return FALSE;
	
	return CWnd::PreCreateWindow(cs);
}

BOOL CChannelWnd::Create(UINT uID, RECT &rect, CWnd *pParentWnd,DWORD dwStyle)
{
	m_id=uID;
	if(CreateEx(0,CLASS_CVideoWndEx,CLASS_CVideoWndEx,dwStyle,rect,pParentWnd,uID))
	{
		//DT("CChannelWnd Create,m_hWnd=0x%x",m_hWnd);
		ModifyStyle(NULL,WS_CLIPCHILDREN);
		return TRUE;
	}
	return FALSE;
}

void CChannelWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	
	CFont font;
	
	ULONG nFontSize = 300;
		
	font.CreatePointFont( nFontSize, TEXT("Arial"), NULL );
	HFONT hOldFont = (HFONT)dc.SelectObject( &font );

	CRect rc;
	GetClientRect(rc);
	if(1)
	{
//		//可以在这里绘制矩形框，但是这里不需要
		
//		if(GetFocus()==this)
//		{
//			dc.FillSolidRect(rc,RGB(255,0,0));
//		}
//		else
//		{
//			dc.FillSolidRect(rc,RGB(0,0,0));
//		}
		
		rc.DeflateRect(2,2,2,2);
		dc.FillSolidRect(rc,RGB(0,0,255));
		
		CString string = TEXT("No Signal");

		dc.DrawText( string, &rc, DT_SINGLELINE| DT_CENTER | DT_VCENTER );	
	}
	else
	{
		
		//贴图
		
		CBitmap bitmap;
		bitmap.LoadBitmap(m_BKbmpID);
		
		BITMAP bmp;
		bitmap.GetBitmap(&bmp);
		
		
		
		CDC dcCompatible;
		dcCompatible.CreateCompatibleDC(&dc);
		
		dcCompatible.SelectObject(&bitmap);
		
		
		//pDC->BitBlt(0,0,rect.Width(),rect.Height(),&dcCompatible,0,0,SRCCOPY);    //1:1 贴图
		dc.StretchBlt(0,0,rc.Width(),rc.Height(),&dcCompatible,0,0,bmp.bmWidth,bmp.bmHeight,SRCCOPY);  //缩放贴图
	}

	
	// Do not call CWnd::OnPaint() for painting messages
}

int CChannelWnd::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message) 
{
	SetFocus();
	return MA_ACTIVATE;
	//return CWnd::OnMouseActivate(pDesktopWnd, nHitTest, message);
}

void CChannelWnd::OnSetFocus(CWnd* pOldWnd) 
{
	CWnd::OnSetFocus(pOldWnd);
	GetParent()->PostMessage(WM_CHANNEL_SET_FOCUS,m_id,0);

	Invalidate();
}

void CChannelWnd::OnKillFocus(CWnd* pNewWnd) 
{
	CWnd::OnKillFocus(pNewWnd);
	Invalidate();	
}

void CChannelWnd::SetBKBmp(unsigned short BmpID)
{
	m_BKbmpID=BmpID;

	Invalidate();//设置无效区，出发重绘消息
}