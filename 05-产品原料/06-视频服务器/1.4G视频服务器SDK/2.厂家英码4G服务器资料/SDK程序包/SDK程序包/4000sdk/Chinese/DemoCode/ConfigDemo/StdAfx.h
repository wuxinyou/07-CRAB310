// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__1AB56EE8_B58E_4EDA_B4FE_C579222C9EE9__INCLUDED_)
#define AFX_STDAFX_H__1AB56EE8_B58E_4EDA_B4FE_C579222C9EE9__INCLUDED_

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
#pragma warning(disable: 4786)
#include "define.h"

#include "multilanguage.h"

#pragma warning(disable:  4083 4514 4786 4800 )

#include "..\\bin\\NetSdk.h"
#pragma comment (lib,"..\\bin\\NetSdk") 

typedef struct _DEV_ATTRIBUTE  
{
	H264_DVR_DEVICEINFO deviveInfo;
	SDK_CONFIG_NORMAL   NormalConfig;
}DEV_ATTRIBUTE;

typedef struct
{
	SDK_MOTIONCONFIG_ALL MotionCfgAll;
	SDK_BLINDDETECTCONFIG_ALL DectectCfgAll;
	SDK_VIDEOLOSSCONFIG_ALL VideoLossCfgAll;
	SDK_ALARM_INPUTCONFIG_ALL AlarmInCfgAll;
	SDK_AlarmOutConfigAll  AlarmOutCfgAll;
	SDK_NETALARMCONFIG_ALL AlarmRmCfgAll;
	

}ALARMCONFIGALL;

typedef struct  
{
	SDK_ChannelNameConfigAll ChanNameCfgAll;
	SDK_GUISetConfig GUISetCfg;
	SDK_VideoWidgetConfigAll   VideoWdtCfgAll;
    SDK_BlindDetectFunction BlindDetFunc[NET_MAX_CHANNUM];
}OUTPUTCONFIGALL;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__1AB56EE8_B58E_4EDA_B4FE_C579222C9EE9__INCLUDED_)
