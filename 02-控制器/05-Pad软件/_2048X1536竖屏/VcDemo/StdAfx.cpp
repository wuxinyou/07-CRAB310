// stdafx.cpp : source file that includes just the standard includes
//	dlgDemo.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

#pragma comment(lib, "DXMediaCap.lib")

bool SnapOk = 0;
CString PicSavePath=" ";
 CString RecSavePath=" ";
 CString strIniFile=" ";

int nCard=0;

 int             m_OpenSata[16];
 int             m_StartPreview[16];
int 			m_nDevNum;
RECT			 g_rcShowWin = { 0, 0, 0, 0 };
DWORD dwCard=0;
