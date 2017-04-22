// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__A6EF1E93_33EB_476A_B556_185C5C5C1935__INCLUDED_)
#define AFX_STDAFX_H__A6EF1E93_33EB_476A_B556_185C5C5C1935__INCLUDED_

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

#include <windowsx.h>
#include "DeviceControl.h"
//	#include "BtnST.h"
class CChannelWnd;
extern bool SnapOk;
extern RECT			 g_rcShowWin ;

extern	DWORD dwCard ;


//保存路径
extern CString RootPath;     //文件根目录

extern CString PicSavePath;    //文件1级目录，即每次登录的日期目录
extern CString RecSavePath;

extern CString PicPath;        //文件2级目录，即日期目下的两个Pic和Video目录
extern CString VideoPath;

extern CString strIniFile;

//保存登录信息
extern CString customsUint;
extern CString address;
extern CString name;
extern int nComboUintIndex;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__A6EF1E93_33EB_476A_B556_185C5C5C1935__INCLUDED_)
