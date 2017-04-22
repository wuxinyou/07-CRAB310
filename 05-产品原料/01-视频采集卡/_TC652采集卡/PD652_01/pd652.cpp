// StreamCatcherDemo.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "pd652.h"
#include "pd652Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// pd652App

BEGIN_MESSAGE_MAP(pd652App, CWinApp)
	//{{AFX_MSG_MAP(pd652App)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// pd652App construction

pd652App::pd652App()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only pd652App object

ULONG g_n_init_device_number = -1;

pd652App theApp;

/////////////////////////////////////////////////////////////////////////////
// pd652App initialization

BOOL pd652App::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// [2009.06.15] [HUENGPEI@YUAN.COM.TW] TO ALLOW ONLY ONE INSTANCE TO BE CREATED.
	// 
	{	m_hShareMemory = OpenFileMapping( FILE_MAP_ALL_ACCESS, TRUE, "pd652.MP" );

		if ( m_hShareMemory == NULL ) {

			m_hShareMemory = CreateFileMapping( (HANDLE)(0xFFFFFFFF), NULL, PAGE_READWRITE, 0, 100, "pd652.MP" );
		}
		else {

			CloseHandle( m_hShareMemory );

			m_hShareMemory = NULL;

			return FALSE;
		}
	}

	pd652Dlg dlg;

	m_pMainWnd = &dlg;

	int nResponse = dlg.DoModal();


	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

int pd652App::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class

	// [2009.06.15] [HUENGPEI@YUAN.COM.TW] TO ALLOW ONLY ONE INSTANCE TO BE CREATED.
	// 
	{	if ( m_hShareMemory ) {

			CloseHandle( m_hShareMemory );

			m_hShareMemory = NULL;
		}
	}

	return CWinApp::ExitInstance();
}
