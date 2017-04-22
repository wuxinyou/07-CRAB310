// DeviceControl.cpp: implementation of the DeviceControl class.
//  video device sdk class
//  write by tony yu  2810482962@qq.com
///  copyright shenzhen zhongan vision
//  2013/12
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "dlgDemo.h"
#include "DeviceControl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DeviceControl::DeviceControl()
{
	

}

DeviceControl::~DeviceControl()
{

}
int DeviceControl::InitDevice ()
{
	int NumDevice;
	DXInitialize();
	NumDevice=DXGetDeviceCount();
	return NumDevice;

}
void DeviceControl::UnInitDevice ()
{

	DXUninitialize();
	
}
HANDLE DeviceControl::OpenDevice(int nCard,unsigned*OpenDevState)
{

	HANDLE DeviceChancel;
	DeviceChancel=DXOpenDevice(nCard,OpenDevState);
	return DeviceChancel;
	
}
void DeviceControl::CloseDevice(HANDLE ChannelHandle)
{

	DXCloseDevice(ChannelHandle);
	
}

BOOL DeviceControl::ConnectDevice(HANDLE ChannelHandle, int VideoStandard, int ColorSpace,int nWidth, int nHeight, float FrameRate)
{
	DXSetVideoPara(ChannelHandle,VideoStandard,ColorSpace,nWidth,nHeight,FrameRate);
	if (DXDeviceRun(ChannelHandle)==0)
	{

		return true;
	}
	else
	{

		return false;
	}
	
}
// set video source
BOOL DeviceControl::SetVideoSource(HANDLE ChannelHandle,unsigned VidSource)
{
	int ok=1;
	unsigned char SourceNum=10;
	//得到设备的视频输入源数量，如只有一个就不设置
	DXGetVideoSources(ChannelHandle,NULL,NULL,&SourceNum);
	if (SourceNum>1)
	{

			ok=DXSetVideoSource(ChannelHandle,VidSource);
		
	}

	if(ok==0)
	{

		return true ;
	}
	else
	{

		return false;
	}
	
}
void DeviceControl::DisConnectDevice(HANDLE ChannelHandle )
{

	DXStopPreview(ChannelHandle);
	DXDeviceStop(ChannelHandle);
}
BOOL DeviceControl::GetVideoPara(HANDLE ChannelHandle, unsigned& nWidth, unsigned& nHeight, unsigned& ColorSpace, unsigned& VideoStandard, float& FrameRate)
{


	DXGetVideoPara(ChannelHandle,VideoStandard,ColorSpace,nWidth,nHeight,FrameRate);
	return true ;
}
BOOL DeviceControl::StartPrview(HANDLE ChannelHandle,HWND PrvHwnd,PRECT rect, unsigned PrvModle,bool PrvEnable)
{
	if(PrvEnable)
	{
			DXStartPreview(ChannelHandle,PrvHwnd,rect,PrvModle);
	}
	return true;
	
}
BOOL DeviceControl::StopPrview(HANDLE ChannelHandle)
{
	DXStopPreview(ChannelHandle);
	return true;
}
BOOL DeviceControl::FreezePreview(HANDLE ChannelHandle,BOOL bFreeze)
{
	DXFreezePreview(ChannelHandle,bFreeze);
	return true;
}

//get video signal
BOOL DeviceControl::GetSignalPresent(HANDLE ChannelHandle, unsigned& signal)
{
	//0 NoSignal 1: signal is ok
	DXGetSignalPresent(ChannelHandle,signal);
	return true;
}

//snap pciture
BOOL DeviceControl::SnapPicture(HANDLE ChannelHandle, TCHAR* szFileName,int PictureType, PRECT rect)
{
	int ok=1;
	if (PictureType==0)
	{
		ok=DXSnapToBMPFile(ChannelHandle,szFileName,rect);
	}
	else
	{
		ok=DXSnapToJPGFile(ChannelHandle,szFileName,100,rect);
	}
	if(ok==0)
	{

		return true ;
	}
	else
	{

		return false;
	}

}
// video flip
BOOL DeviceControl::SetVideoFlip(HANDLE ChannelHandle,BOOL FlipEnable)
{
	int ok=1;
	ok=DXFlipVideo(ChannelHandle,FlipEnable);
	if (ok==0)
	{

		return true;
	}
	else

	{
			return false;
		
	}
}

// video mirro
BOOL DeviceControl:: SetVideoMirro(HANDLE ChannelHandle,BOOL MirroEnable)
{
	int ok=1;
	ok=DXMirrorVideo(ChannelHandle,MirroEnable);
	if (ok==0)
	{

		return true;
	}
	else

	{
			return false;
		
	}
}


// osd para
BOOL DeviceControl::SetOSDPara(HANDLE ChannelHandle, unsigned OsdType, int OsdNo, LPCTSTR OsdFile, int x, int y, int pointSize, LPCTSTR faceName, COLORREF OSDcolor, COLORREF Backcolor, BOOL transparent, unsigned char PicAlpha)
{
	int ok=1;
	switch(OsdType)
	{
			case 0:
				
					ok=DXSetTimeOSD(ChannelHandle,x,y,pointSize,faceName,OSDcolor,Backcolor,transparent);
			
			break;
			case 1:
				
								
					ok=DXSetTextOSD(ChannelHandle,x,y,OsdNo,OsdFile,pointSize,faceName,OSDcolor,Backcolor,transparent);
				
		
			break;
			case 2:
			
					ok=DXSetPictureOSD(ChannelHandle,x,y,OsdNo,OsdFile,transparent);
		
			break;
			
		
	}
	if (ok==0)
	{

		return true;
	}
	else

	{
			return false;
		
	}

}
///



/// start osd
BOOL DeviceControl::StartOsd(HANDLE ChannelHandle,unsigned OsdType,int OsdNo,BOOL OSDEnable)
{
	int ok=1;
	ok=DXEnOSDDisp(ChannelHandle,OsdType,OsdNo,OSDEnable);
	if (ok==0)
	{

		return true;
	}
	else

	{
			return false;
		
	}
}



// enable deinterlace
BOOL DeviceControl:: EnableDeinterlace(HANDLE ChannelHandle,int DeintType,BOOL enable)
{
	int ok=1;
	ok=DXEnableDeinterlace(ChannelHandle,DeintType);
	if(enable==false)
	{
			ok=DXEnableDeinterlace(ChannelHandle,-1);
	}

	if (ok==0)
	{

		return true;
	}
	else

	{
			return false;
		
	}
}
BOOL DeviceControl::GetCurBuffer(HANDLE ChannelHandle,
								 unsigned BufType,
								unsigned char* pbuffer,
								unsigned bufferLen,
								unsigned width,
								unsigned height,
								BOOL EnableFilp)
{


	int ok=1;

	switch(BufType)
	{
		case 0:
			ok=DXGetFrameBuffer(ChannelHandle,pbuffer,bufferLen,NULL,NULL,&width,&height,NULL,NULL);	
			break;
		case 1:
			unsigned char* buffer = new unsigned char[bufferLen];
			ok=DXGetFrameBuffer(ChannelHandle,buffer,bufferLen,NULL,NULL,&width,&height,NULL,NULL);
			DXConvertYUVtoRGB(ChannelHandle,buffer,pbuffer,width,height,EnableFilp,false);
			break;
			
	}

		if (ok==0)
	{

		return true;
	}
	else

	{
			return false;
		
	}
}
// yuv2 to rgb24
BOOL DeviceControl:: ConvertYUVtoRGB(HANDLE ChannelHandle,
						void* pYUVBuf,
						void* pRGBBuf,
						long lImgWidth, 
						long lImgHeight,
						BOOL bInverted,
						BOOL bInvertColor)
{
	int ok=1;
	ok=DXConvertYUVtoRGB(ChannelHandle,
						pYUVBuf,
						pRGBBuf,
						lImgWidth,
						lImgHeight,
						bInverted,
						bInvertColor);
	if (ok==0)
	{
		return true;
	}
	else

	{
			return false;
	}

}

//保存buffer到bmp文件  

//iWidth：图像宽； iHeight：图像高；pBuffer：图像RGB数据；
bool DeviceControl::SaveRGBToBmp( const char * fileName,  int iWidth, int iHeight, BYTE *pBuffer)  
{  
	
	BITMAPINFOHEADER bih;  
	DeviceControl::ConstructBih(iWidth,iHeight,bih);  
	BITMAPFILEHEADER bhh;  
	DeviceControl::ContructBhh(iWidth,iHeight,bhh);  
	
	TCHAR BMPFileName[1024];  
	int widthStep = (((iWidth * 24) + 31) & (~31)) / 8 ; //每行实际占用的大小（每行都被填充到一个4字节边界）  
	int DIBSize = widthStep * iHeight ;  //buffer的大小 （字节为单位）  
	

	
	strcpy(BMPFileName,fileName);  
	CFile file;  
	try  
	{  
		if(file.Open(BMPFileName,CFile::modeWrite | CFile::modeCreate))  
		{//写入文件  
			
			file.Write((LPSTR)&bhh,sizeof(BITMAPFILEHEADER));  
			file.Write((LPSTR)&bih,sizeof(BITMAPINFOHEADER));  
			file.Write(pBuffer,DIBSize);  
			file.Close();  
			return true;  
		}  
		
	}  
	catch (...)   
	{  
		AfxMessageBox("MyDC::SaveDIB2Bmp");  
	}  
	return false;  
}  



//构建BMP位图文件头  
void DeviceControl::ContructBhh(int nWidth,int nHeight,BITMAPFILEHEADER& bhh) 
{  
	int widthStep = (((nWidth * 24) + 31) & (~31)) / 8 ; //每行实际占用的大小（每行都被填充到一个4字节边界）  
	bhh.bfType = ((WORD) ('M' << 8) | 'B');  //'BM'  
	bhh.bfSize = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER) + widthStep * nHeight;  
	bhh.bfReserved1 = 0;  
	bhh.bfReserved2 = 0;  
	bhh.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER);  
	
}  


//构建BMP文件信息头  
void DeviceControl::ConstructBih(int nWidth,int nHeight,BITMAPINFOHEADER& bih)   
{  
	int widthStep = (((nWidth * 24) + 31) & (~31)) / 8 ;   
	
	bih.biSize=40;       // header size  
	bih.biWidth=nWidth;  
	bih.biHeight=nHeight;  
	bih.biPlanes=1;  
	bih.biBitCount=24;     // RGB encoded, 24 bit  
	bih.biCompression=BI_RGB;   // no compression 非压缩  
	bih.biSizeImage=widthStep*nHeight*3;  
	bih.biXPelsPerMeter=0;  
	bih.biYPelsPerMeter=0;  
	bih.biClrUsed=0;  
	bih.biClrImportant=0;   
	
}  

BOOL DeviceControl:: StartRecord(HANDLE ChannelHandle, CString szFileName,CString CodecType, VidCodecX264Para H264CodecPara)
{
		unsigned CodecNum=100;
		CString VidCodec[100];
		int CurVidCodec=0;
		int ok=1;
		CString strVideo;
		DEVICE_TAG VideoCodec[100];
		DXEnumVideoCodecs(VideoCodec, CodecNum);
		
		//指定编码器为xvid
		for (unsigned i=0; i< CodecNum;i++)
		{
			strVideo.Format (_T("%s"),VideoCodec[i].deviceName);
			VidCodec[i].Format (_T("%s"),VideoCodec[i].deviceName);
	
			if (strcmp(strVideo,CodecType)==0)
			{
				CurVidCodec=i;
			}

		}

		//设置编码器
      
		ok=DXSetVideoCodec(ChannelHandle,&VideoCodec[CurVidCodec]);

		//设置264编码器参数

		if (strcmp(X264CODEC_FILTER,CodecType)==0)
		{
			DXSetVideoCodecPara(ChannelHandle, codec_x264, &H264CodecPara);	
		}
		 


		ok=DXStartCapture(ChannelHandle, TEXT(szFileName.GetBuffer(szFileName.GetLength())), FALSE, NULL, NULL, NULL);

		
		if (ok==0)
		{

		return true;
		}
		else

		{
			return false;
		
		}

}

BOOL DeviceControl::StopRecord(HANDLE ChannelHandle)
{
		int ok=1;
		ok=DXStopCapture(ChannelHandle);
		if (ok==0)
		{

			return true;
		}
		else

		{
			return false;
		
		}
	
	
}
BOOL DeviceControl::FreezeRecord(HANDLE ChannelHandle,BOOL Enable)
{
		int ok=1;
		ok=DXFreezeCaputre(ChannelHandle,Enable);
		if (ok==0)
		{

			return true;
		}
		else

		{
			return false;
		
		}
}