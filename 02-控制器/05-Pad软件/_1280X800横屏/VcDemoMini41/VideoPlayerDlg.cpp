// VideoPlayerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "dlgDemo.h"
#include "VideoPlayerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// VideoPlayerDlg dialog


char* EncodeToUTF8(const char* mbcsStr) 
{ 
	 wchar_t*  wideStr; 
	 char*   utf8Str; 
	 int   charLen; 

	 charLen = MultiByteToWideChar(CP_UTF8, 0, mbcsStr, -1, NULL, 0); 
	 wideStr = (wchar_t*) malloc(sizeof(wchar_t)*charLen); 
	 MultiByteToWideChar(CP_ACP, 0, mbcsStr, -1, wideStr, charLen); 

	 charLen = WideCharToMultiByte(CP_UTF8, 0, wideStr, -1, NULL, 0, NULL, NULL); 

	 utf8Str = (char*) malloc(charLen);

	 WideCharToMultiByte(CP_UTF8, 0, wideStr, -1, utf8Str, charLen, NULL, NULL);

	 free(wideStr); 
	 return utf8Str;
} 





VideoPlayerDlg::VideoPlayerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(VideoPlayerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(VideoPlayerDlg)
	//}}AFX_DATA_INIT
}

VideoPlayerDlg::~VideoPlayerDlg()
{

}


void VideoPlayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(VideoPlayerDlg)
	DDX_Control(pDX, IDC_ODLOG_PIC, m_ctrlODLogPic);
	DDX_Control(pDX, IDC_VIDEOPLAYER_PIC, m_ctrlPic);
	DDX_Control(pDX, IDC_VIDEOPLAYER_PLAYTIME, m_ctrlSliderPlayTime);
	DDX_Control(pDX, IDC_VIDEOPLAYER_LIST2, m_ctrlList2);
	DDX_Control(pDX, IDC_VIDEOPLAYER_LIST1, m_ctrlList1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(VideoPlayerDlg, CDialog)
	//{{AFX_MSG_MAP(VideoPlayerDlg)
	ON_LBN_DBLCLK(IDC_VIDEOPLAYER_LIST1, OnDblclkVideoplayerList1)
	ON_LBN_DBLCLK(IDC_VIDEOPLAYER_LIST2, OnDblclkVideoplayerList2)
	ON_WM_TIMER()
	ON_WM_HSCROLL()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// VideoPlayerDlg message handlers

BOOL VideoPlayerDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

//初始化成员变量
	m_bNew = true;
	m_vlcInst = NULL;
	m_vlcMedia = NULL;
	m_vlcMplay = NULL;

	m_bNew = true;
	m_bIsRtsp = false;
//	
	m_bOpen=true;

	m_bFullScreen=false;
	m_bIsPlay=false;
	
	// TODO: Add extra initialization here

	SetWindowText("视频回放");
	char *vlc_argv[100];
	int vlc_argc = 0;
	vlc_argv[vlc_argc++] = "--ignore-config";

	m_vlcInst = libvlc_new (vlc_argc, vlc_argv);

	m_ctrlSliderPlayTime.SetRange(0, 1000);
	m_ctrlSliderPlayTime.SetPos(0);


	TCHAR szPath[MAX_PATH];
	_tcscpy(szPath, RootPath);   //CString to TCHAR
	//该函数用与指定的文件名匹配的所有文件的名字填充列表框。
	int nReslt = DlgDirList(szPath , IDC_VIDEOPLAYER_LIST1 ,NULL,DDL_EXCLUSIVE|DDL_DIRECTORY );    //只显示目录文件

	//初始化部件
	InitWidget();
	
	
           
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void VideoPlayerDlg::InitWidget()
{

	this->MoveWindow(106,85,1074,630);
	m_ctrlPic.MoveWindow(0,0,768,550);
	m_ctrlList1.MoveWindow(768,0,300,299);
	m_ctrlList2.MoveWindow(768,301,300,300);
	m_ctrlSliderPlayTime.MoveWindow(0,560,768,30);

	//设置列表部件的字体
	CFont font;
	font.CreatePointFont(200,"宋体");     //列表框字体的设定
	m_ctrlList1.SetFont(&font);
	m_ctrlList2.SetFont(&font);
	font.Detach();

	//显示OD Log
	m_ctrlODLogPic.MoveWindow(0,0,768,550);
	HBITMAP hBitmap; 
	hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_ODLOG550)); 
	m_ctrlODLogPic.SetBitmap(hBitmap);   


}

/////////////////////////////////////////////////////////////视频控制///////////////////////////////////////////////////////////////

void VideoPlayerDlg::OnDblclkVideoplayerList1() 
{
	// TODO: Add your control notification handler code here
	CString str;
	int index=m_ctrlList1.GetCurSel();
	m_ctrlList1.GetText(index,str);
	
	//去除方括号
	str.Replace("[", NULL);
	str.Replace("]", NULL);
	
	
//	m_player.SetUrl(str);
//	CString VideoPath;
	VideoPath=RootPath+"\\"+str+"\\Video";
//	AfxMessageBox(VideoPath);
	
	//	TCHAR szPath[MAX_PATH] ={"C:\\CRABUserData"} ; 
	TCHAR szPath[MAX_PATH];
	_tcscpy(szPath, VideoPath);

	//该函数用与指定的文件名匹配的所有文件的名字填充列表框。
	int nReslt = DlgDirList(szPath , IDC_VIDEOPLAYER_LIST2 ,NULL,DDL_EXCLUSIVE|DDL_ARCHIVE );   //显示文件
	
}

void VideoPlayerDlg::OnDblclkVideoplayerList2() 
{
	// TODO: Add your control notification handler code here
	m_bNew=true;
	CString str;
	int index=m_ctrlList2.GetCurSel();
	m_ctrlList2.GetText(index,str);
	
	
	//	m_player.SetUrl(str);
	m_VideoFilePath=VideoPath+"\\"+str;
	
	UpdateData(FALSE);
	StopVideo();
	PlayVideo();
}

void VideoPlayerDlg::PlayVideo()
{
		m_bIsPlay=true;

	UpdateData(true);
	if (m_VideoFilePath == "")
	{
		return;
	}
	if(m_bNew == true)
	{
		if(m_vlcMplay != NULL)
		{
			libvlc_media_player_release(m_vlcMplay);
		}
		//	AfxMessageBox(m_VideoFilePath);
		if (m_bIsRtsp == false)
		{
			//本地文件
			m_vlcMedia = libvlc_media_new_path (m_vlcInst, EncodeToUTF8(m_VideoFilePath.GetBuffer(0)));
		}
		else
		{
			m_vlcMedia = libvlc_media_new_location(m_vlcInst,m_VideoFilePath.GetBuffer(0));
		}
		
		
		m_vlcMplay = libvlc_media_player_new_from_media (m_vlcMedia);

		//让libVLC播放对象设置gPlayHwnd 为播放窗口句柄，这样libVLC播放窗口就成为IDC_PLAYWND控件的子窗口；
		hwndVideoPlayer = GetDlgItem(IDC_VIDEOPLAYER_PIC)->GetSafeHwnd();
		libvlc_media_player_set_hwnd (m_vlcMplay, hwndVideoPlayer);
		libvlc_media_release(m_vlcMedia);
		m_bNew = false;
	}

	libvlc_media_player_play (m_vlcMplay);

	//开始播放后创建一个定时器，用于关闭Picture的鼠标键盘响应事件
	SetTimer(1,500,NULL);   

	//获取视频文件的时长
	if (m_bIsRtsp == false)
	{ 
		m_TotalTime = libvlc_media_player_get_length(m_vlcMplay);
		m_playerTimer = SetTimer(100,1*100,NULL);
	}
}

void VideoPlayerDlg::PauseVideo()
{
	
	m_bIsPlay=false;
	if(m_vlcMplay != NULL)
		libvlc_media_player_pause(m_vlcMplay);
}

void VideoPlayerDlg::StopVideo()
{
	if (m_vlcMplay == NULL)
	{
		return;
	}
	libvlc_media_player_stop(m_vlcMplay);
	m_bNew = true;
	m_vlcMplay = NULL;
	//libvlc_exception_clear(&m_vlcEx);
	if (m_vlcMedia != NULL)
	{
		libvlc_media_release(m_vlcMedia);
	}
	if (m_vlcMplay != NULL)
	{
		libvlc_media_player_release(m_vlcMplay);
	}

	KillTimer(100);
	m_ctrlSliderPlayTime.SetPos(0);
	OnPaint();
	
}

void VideoPlayerDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default

	if (nIDEvent == 100)
	{
		libvlc_time_t m_CurTime = libvlc_media_player_get_time(m_vlcMplay);
		//float fPos = libvlc_media_player_get_position(m_vlcMplay, &m_vlcEx);
		m_TotalTime = libvlc_media_player_get_length(m_vlcMplay);
		int m_npos = m_CurTime*1000/m_TotalTime;
		m_ctrlSliderPlayTime.SetPos(m_npos);
		
		if(libvlc_Ended == libvlc_media_player_get_state(m_vlcMplay))//获取播放状态的函数,如果是结束就发送stop命令，更改状态。
			StopVideo();
	}
	
	//用于关闭VLC的消息响应, 目的是为了让对话框接收消息响应
	if(nIDEvent == 1)
	{
//		TCHAR szWndTitle[1024];
//		int nLen = GetWindowText(hwnd , szWndTitle, 1024);
//		if (0 != nLen)
//		{
			//禁用鼠标消息
			CWnd* pWnd =GetDlgItem(IDC_VIDEOPLAYER_PIC);
			pWnd->EnableWindow(FALSE);
			KillTimer(1);
		//	}
	}


	
	CDialog::OnTimer(nIDEvent);
}

void VideoPlayerDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	if (pScrollBar->GetSafeHwnd() == m_ctrlSliderPlayTime.GetSafeHwnd())
	{
		if (m_vlcMplay != NULL)
		{
			libvlc_time_t m_CurTime;
			m_TotalTime = libvlc_media_player_get_length(m_vlcMplay);
			double pos = m_ctrlSliderPlayTime.GetPos()/1000.0;
			m_CurTime = m_TotalTime * pos;
			libvlc_media_player_set_time(m_vlcMplay,m_CurTime);
		}
	}
	
	else
	{
		CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
	}
}

////////////////////////////////////////////////////////FullScreen////////////////////////////////////////////////////////////////

//全屏切换时用于显示和隐藏其他部件
void VideoPlayerDlg::ShowOtherWidget(bool SWMode)
{


	//显示
	if(SWMode)
	{
		m_ctrlList1.ShowWindow(SW_SHOW);
		m_ctrlList2.ShowWindow(SW_SHOW);
		m_ctrlSliderPlayTime.ShowWindow(SW_SHOW);


	
		
	}
	//隐藏
	else
	{
		m_ctrlList1.ShowWindow(SW_HIDE);
		m_ctrlList2.ShowWindow(SW_HIDE);
		m_ctrlSliderPlayTime.ShowWindow(SW_HIDE);
	
	}
}




void VideoPlayerDlg::FullScreenShow()
{
    // TODO: Add your command handler code here

    if ((TRUE == m_bOpen) && (FALSE == m_bFullScreen))
    {
        m_bFullScreen = TRUE;

        //获取对话框原始位置
        GetWindowPlacement(&m_OldWndPlacement);
		GetDlgItem(IDC_VIDEOPLAYER_PIC)->GetWindowPlacement(&m_OldPicPlacement);

        CRect WindowRect;
        GetWindowRect(&WindowRect);

        CRect ClientRect;
        RepositionBars(0, 0xffff, AFX_IDW_PANE_FIRST, reposQuery, &ClientRect);
        ClientToScreen(&ClientRect);

        //获取屏幕的分辨率
        int nFullWidth  = GetSystemMetrics(SM_CXSCREEN);
        int nFullHeight = GetSystemMetrics(SM_CYSCREEN);

        //对话框全屏显示
        m_FullScreenRect.left = WindowRect.left - ClientRect.left;
        int m_top = WindowRect.top - ClientRect.top;
        m_FullScreenRect.top    = m_top;
        m_FullScreenRect.right  = WindowRect.right - ClientRect.right + nFullWidth;
        m_FullScreenRect.bottom = WindowRect.bottom - ClientRect.bottom + nFullHeight;

        m_NewWndPlacement.length           = sizeof(WINDOWPLACEMENT);
        m_NewWndPlacement.flags            = 0;
        m_NewWndPlacement.showCmd          = SW_SHOWNORMAL;
        m_NewWndPlacement.rcNormalPosition = m_FullScreenRect;
        SetWindowPlacement(&m_NewWndPlacement);

        //Picture控件全屏显示
        GetDlgItem(IDC_VIDEOPLAYER_PIC)->MoveWindow(CRect(0, 0, nFullWidth, nFullHeight));


        //隐藏控件
		ShowOtherWidget(FALSE);
		//重绘
		Invalidate(FALSE);
		UpdateWindow();
        
    }
}
//
void VideoPlayerDlg::NormalShow(void)
{
    if ((TRUE == m_bOpen) && (TRUE == m_bFullScreen))
    {
        //恢复默认窗口
        SetWindowPlacement(&m_OldWndPlacement);
		GetDlgItem(IDC_VIDEOPLAYER_PIC)->SetWindowPlacement(&m_OldPicPlacement);


        m_bFullScreen = FALSE;

        //显示控件
		ShowOtherWidget(TRUE);

		//重绘
		Invalidate(FALSE);
       
    }
}



BOOL VideoPlayerDlg::PreTranslateMessage(MSG* pMsg) 
{
	if (TRUE == m_bOpen)
    {
        if (WM_LBUTTONDBLCLK == pMsg->message) // 1 鼠标双击响应
        {
			//获取鼠标位置
            CPoint ptCursor;
            GetCursorPos(&ptCursor);
			
            CRect rc;
            GetDlgItem(IDC_VIDEOPLAYER_PIC)->GetWindowRect(&rc);
			
            //1.1 双击时鼠标位于Picture控件范围内才响应
            if (rc.PtInRect(ptCursor))
            {
                if (FALSE == m_bFullScreen)
                {
                    FullScreenShow(); //全屏显示
                }
                else
                {
                    NormalShow();  //恢复默认显示
                }
				
            }
        } //end of if (WM_LBUTTONDBLCLK == pMsg->message)
		else if(WM_LBUTTONUP==pMsg->message)  //单击输入
		{
			//获取鼠标位置
            CPoint ptCursor;
            GetCursorPos(&ptCursor);
			
            CRect rc;
            GetDlgItem(IDC_VIDEOPLAYER_PIC)->GetWindowRect(&rc);
			
            //1.1 双击时鼠标位于Picture控件范围内才响应
            if (rc.PtInRect(ptCursor))
            {
				if(false==m_bIsPlay)
				{
					PlayVideo();
					m_bIsPlay=true;
				}
				else
				{
					PauseVideo();
					
				}
				//暂停播放
            }
		}
        else if (WM_KEYDOWN == pMsg->message) // 2 键盘输入响应
        {
            // 2.1键盘输入Esc
            if (VK_ESCAPE == pMsg->wParam)
            {
				if (TRUE == m_bFullScreen)
				{
					NormalShow();  //恢复默认显示
				}                
            }
			
            // 2.2键盘输入Enter
            if (VK_RETURN == pMsg->wParam)
            {
                if (FALSE == m_bFullScreen)
                {
                    FullScreenShow(); //全屏显示
                }
                else
                {
                    NormalShow();  //恢复默认显示
                }
            }
        } //end of if (WM_KEYDOWN == pMsg->message)
    } // end of if (TRUE == m_bOpen)
	
	
    return 0;
}


/////////////////////////////////////////////////end of fullScreen////////////////////////////////////////////////////////////////////////

void VideoPlayerDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	StopVideo();
	
	CDialog::OnClose();
}
