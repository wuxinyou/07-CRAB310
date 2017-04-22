// dlgDemo.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "dlgDemo.h"
#include "dlgDemoDlg.h"

#include "MySplashScreen.h" //用于显示启动画面

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgDemoApp

BEGIN_MESSAGE_MAP(CDlgDemoApp, CWinApp)
	//{{AFX_MSG_MAP(CDlgDemoApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDemoApp construction

CDlgDemoApp::CDlgDemoApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CDlgDemoApp object

CDlgDemoApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CDlgDemoApp initialization

BOOL CDlgDemoApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

// 	CoInitialize(NULL);

//////////////////////显示启动画面///////////////////////////
	
#ifdef USE_SPLASHSCREEN
	CMySplashScreen wndSplash;                  //创建启动窗口类的实例	
	
	wndSplash.Create(IDB_SPLASHSCREEN);
	//	wndSplash.MoveWindow(0,0,1000,700);
	wndSplash.UpdateWindow();           //send WM_PAINT
	Sleep(3000);
	wndSplash.DestroyWindow(); //销毁窗体
#endif

///////////////////////启动画面启动完毕///////////////////////////

	CDlgDemoDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}


	//////////////////////

	//////////////////////

// 	CoUninitialize();

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

int CDlgDemoApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class

	//一下2句代码用于强制关闭软件进程，用于解决关闭后任然留在后台运行的问题。
	HANDLE hself = GetCurrentProcess();
	TerminateProcess(hself, 0);
////////////
	
	return CWinApp::ExitInstance();
}
