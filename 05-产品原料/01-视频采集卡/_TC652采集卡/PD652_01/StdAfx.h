// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

//#define WINVER 0x0500

#if !defined(AFX_STDAFX_H__6BA1620D_D549_4FD1_98FD_D0DF68F08C2F__INCLUDED_)
#define AFX_STDAFX_H__6BA1620D_D549_4FD1_98FD_D0DF68F08C2F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <VFW.H>

//#include "AMESDK.H"

#include "QCAP.H"

#define FREE( p ) { if( p ) { free( p ); p = NULL; } }	

// SET INITIAL PARAMETER VALUES
//

#define	SC_DEFAULT_STANDARD                 0		// 0 = NTSC / 1 = PALB

#define SC_DEFAULT_INPUT_SUPPORT			0x00000000	// HDMI

#define DEFAULT_PRODUCT						"StreamCatcher QCAP - PD652"

#define DEFAULT_PRODUCT_VERSION				""


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__6BA1620D_D549_4FD1_98FD_D0DF68F08C2F__INCLUDED_)
