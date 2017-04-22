///////////////////////////////////////////////////////////////////////////////////////////////
// DeviceControl.h: interface for the DeviceControl class.
//
// WriteDeviceControl.h by tony yu qq:67505494

//	copyright ShenZhen ZhongAn Vision

 // 20131210

/////////////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "DXMediaCap.h"
#include "ChannelWnd.h"



#if !defined(AFX_DEVICECONTROL_H__B4861B41_DB02_4E63_AEAA_1FBA5283B0C3__INCLUDED_)
#define AFX_DEVICECONTROL_H__B4861B41_DB02_4E63_AEAA_1FBA5283B0C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
typedef struct DEVICE_INFO
{
	DEVICE_INFO()
	{
		m_pWnd=NULL;
	 }
	CChannelWnd	*m_pWnd;
	unsigned int dwHeight;
	unsigned int dwWidth;
	float dwFrameRate;
	unsigned int dwColorspace;
	unsigned int dwVidStandard;
	unsigned  dwOpenDevState;
	BOOL dwConnectState;
	BOOL  dwPrviewState;
	HANDLE dwChannelHandle;
	HWND dwPrvHandle;
	RECT dwPrvRect;

	PRECT dwSnapPicRect;
	RECT dwZoomRect;
	VidCodecPara  dwVideoCodecpara;
	CString       dwVideoCodecStr;
	DWORD			dwDispWidth;                     //预览显示宽度
	DWORD			dwDispHeight;                    //预览显示高度
	DWORD			dwDispPosX;                      //预览显示水平起始位置
	DWORD			dwDispPosY; 

	DWORD			dwZoomWidth;                     //预览显示宽度
	DWORD			dwZoomHeight;                    //预览显示高度
	DWORD			dwZoomPosX;                      //预览显示水平起始位置
	DWORD			dwZoomPosY; 



}Device_Info;


typedef struct Device_ColorPara
 {
	int ColorType;
	int MinVal;
	int MaxVal;
	int StepVal;
	int DefaultVal;
	int CurVal;
 }DeviceColorProp;

 static Device_ColorPara DeviceColorPara[23];      

typedef struct TOSD_INFO
{
	int TimeX;
	int TimeY;
	int TxtPlaceX [23];
	int TxtPlaceY [23];
	int PicPlaceX[23];
	int PicPlaceY[23];
	int TimeFontSizeVal;
	int TxtFontSizeVal[23];
	LPCTSTR Osd_Txtstring[23];
	CString PicOsdFile;
	LPCTSTR TimeFont;
	LPCTSTR TxtFont[23];
	COLORREF TxtColor[23];
	 COLORREF TimeColor;
	COLORREF BackColor;
	char Alpha [23];
   
}TosdInfo;
             
 static TOSD_INFO TosdPara[23];     
class DeviceControl  
{
public:
	DeviceControl();
	virtual ~DeviceControl();
	int InitDevice();
	void UnInitDevice();

	HANDLE OpenDevice(int nCard,unsigned*OpenDevState);
	void CloseDevice(HANDLE ChannelHandle);
	BOOL  ConnectDevice(HANDLE ChannelHandle,
						int VideoStandard, 
						int ColorSpace,
						int nWidth,
						int nHeight,
						float FrameRate);
	void DisConnectDevice(HANDLE ChannelHandle);
	BOOL SetVideoSource(HANDLE ChannelHandle,unsigned VideoSource);
	BOOL GetVideoPara(HANDLE ChannelHandle,
					unsigned& nWidth,
					unsigned& nHeight,
					unsigned& ColorSpace,
					unsigned& VideoStandard,
					float& FrameRate);
	BOOL  StartPrview(HANDLE ChannelHandle,HWND PrvHwnd,PRECT rect, unsigned PrvModle,bool PrvEnable) ;
	BOOL StopPrview(HANDLE ChannelHandle);
	BOOL FreezePreview(HANDLE ChannelHandle,BOOL bFreeze);
	BOOL GetSignalPresent(HANDLE ChannelHandle, unsigned& signal);
	BOOL SnapPicture(HANDLE ChannelHandle, TCHAR* szFileName,int PictureType, PRECT rect);
	BOOL SetVideoFlip(HANDLE ChannelHandle,BOOL FlipEnable);
	BOOL GetVideoColorPara(HANDLE ChannelHandle, unsigned paraType, long& value, long& flags);
	BOOL GetVideoColorParaRange(HANDLE ChannelHandle,
								unsigned paraType,
								long* pMin,
								long* pMax, 
								long* pSteppingDelta,
								long* pDefault,
								long* pCapsFlags);
	BOOL SetVideoColorPara(HANDLE ChannelHandle, unsigned paraType, long value, long flags);
	BOOL SetOSDPara(HANDLE ChannelHandle,
					unsigned OsdType,
					int OsdNo,
					LPCTSTR OsdFile,
					int x, 
					int y,  
					int pointSize,
					LPCTSTR faceName,
					COLORREF OSDcolor, 
					COLORREF Backcolor,
					BOOL transparent,
					unsigned char PicAlpha);
	BOOL StartOsd(HANDLE ChannelHandle,unsigned OsdType,int OsdNo,BOOL osdEnable);

	BOOL SetVideoMirro(HANDLE ChannelHandle,BOOL MirroEnable);



	BOOL EnableDeinterlace(HANDLE ChannelHandle,int DeintType,BOOL enable);

	BOOL GetCurBuffer(HANDLE ChannelHandle,
					unsigned BufType,
					unsigned char* pbuffer,
					unsigned bufferLen,
					unsigned width,
					unsigned height,
					BOOL EnableFilp);

	BOOL ConvertYUVtoRGB(HANDLE ChannelHandle,
						void* pYUVBuf,
						void* pRGBBuf,
						long lImgWidth, 
						long lImgHeight,
						BOOL bInverted,
						BOOL bInvertColor);
	bool DeviceControl::SaveRGBToBmp( const char * fileName,  int iWidth, int iHeight, BYTE *pBuffer)  ;

	void DeviceControl::ContructBhh(int nWidth,int nHeight,BITMAPFILEHEADER& bhh); 

		
		//构建BMP文件信息头  
	void DeviceControl::ConstructBih(int nWidth,int nHeight,BITMAPINFOHEADER& bih) ;
	
	BOOL StartRecord(HANDLE ChannelHandle,CString szFileName,CString CodecType, VidCodecPara nCodecPara);

	BOOL StopRecord(HANDLE ChannelHandle);

	BOOL FreezeRecord(HANDLE ChannelHandle,BOOL Enable);




};



#endif // !defined(AFX_DEVICECONTROL_H__B4861B41_DB02_4E63_AEAA_1FBA5283B0C3__INCLUDED_)

//extern DEVICE_INFO DeviceInfo[23];