// StreamCatcherDemo.h : main header file for the STREAMCATCHERDEMO application
//

#if !defined(AFX_STREAMCATCHERDEMO_H__FE6504F6_6434_4654_812A_A4370D05F22E__INCLUDED_)
#define AFX_STREAMCATCHERDEMO_H__FE6504F6_6434_4654_812A_A4370D05F22E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// pd652App:
// See StreamCatcherDemo.cpp for the implementation of this class
//

class pd652App : public CWinApp
{
public:
	pd652App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(pd652App)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(pd652App)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:

	HANDLE m_hShareMemory;
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STREAMCATCHERDEMO_H__FE6504F6_6434_4654_812A_A4370D05F22E__INCLUDED_)
