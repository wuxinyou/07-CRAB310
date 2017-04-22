// dlgDemo.h : main header file for the DLGDEMO application
//

#if !defined(AFX_DLGDEMO_H__E3593870_3ECD_41BE_A675_05565CC6E162__INCLUDED_)
#define AFX_DLGDEMO_H__E3593870_3ECD_41BE_A675_05565CC6E162__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDlgDemoApp:
// See dlgDemo.cpp for the implementation of this class
//

class CDlgDemoApp : public CWinApp
{
public:
	CDlgDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgDemoApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDlgDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGDEMO_H__E3593870_3ECD_41BE_A675_05565CC6E162__INCLUDED_)
