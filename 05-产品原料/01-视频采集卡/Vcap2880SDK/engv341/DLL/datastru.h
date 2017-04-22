/********************************************************************
	created:	2011/08/05

*********************************************************************/

#ifndef __LIBDXCAP_DATASTRU__20110805__
#define __LIBDXCAP_DATASTRU__20110805__

typedef void* device_handle;
typedef void* image_handle;

// 运行状态
enum {state_stopped, state_paused, state_running};

// 视频颜色空间
enum {cs_rgb24, cs_rgb32, cs_yuy2};

// 设备信息
#define MAX_DEVICE_NAME		128
typedef struct _device_tag
{
	unsigned	idx;							// 过滤器在枚举过程中的序号
	TCHAR		deviceName[MAX_DEVICE_NAME];	// 过滤器的名称
} DEVICE_TAG, *PDEVICE_TAG;

typedef struct _videocaps
{
	int width;
	int height;
}VIDEOCAPS, *PVIDEOCAPS;

//----视频编码参数申明----------------------
#define X264CODEC_FILTER TEXT("x264 Codec\0")
#define XVIDCODEC_FILTER TEXT("xvid Codec\0")
#define AAC_FILTER       TEXT("aac Codec\0")
enum {codec_sys,codec_x264,codec_xvid};
enum {acodec_sys,acodec_aac};
enum {codec_CBR=0, codec_VBR=1};
typedef struct{
	int fps;    //帧率
	int keyframeinterval;  //关键帧间隔，必须大于等于帧率
	int rcMode;   //码率控制:codec_CBR(恒定码率)/codec_VBR(平均码率)；
	int Quality; //codec_xvid: 1 ~ 31 (1为最小量度，压缩质量最好)
	int Bitrate; //码率（单位：kbps）默认值256，x264中为0时，编码器内部自己计算

	int Maxrbps;  //VBR有效，默认值4000000,位率范围:56bps ~ 10Mbps; 单位Kbps
	int Peekbps;  //VBR有效，默认值10000000bps,位率范围:56bps ~ 10Mbps; 单位Kbps
}VidCodecPara;
//-------------------------------------------

enum {drate_color};
typedef struct{
	int nBrightness; // 亮度，取值(-255到255)
	int nContrast;  //对比度，取值(-100到100)
}DRateColorPara;

enum SwsAlogrithm
{
	SWS_SA_FAST_BILINEAR	= 0,
	SWS_SA_BILINEAR			,
	SWS_SA_BICUBIC			,
	SWS_SA_X				,
	SWS_SA_POINT			,
	SWS_SA_AREA				,
	SWS_SA_BICUBLIN			,
	SWS_SA_GAUSS			,
	SWS_SA_SINC				,
	SWS_SA_LANCZOS			,
	SWS_SA_SPLINE			,
};

// 录像通知
EXTERN_C const IID IID_ISaveNotify;
/*
// {BAE74021-AFEC-4336-8497-658ED4432F65}
DEFINE_GUID(IID_ISaveNotify, 
			0xbae74021, 0xafec, 0x4336, 0x84, 0x97, 0x65, 0x8e, 0xd4, 0x43, 0x2f, 0x65);
			// */
class ISaveNotify : public IUnknown// 录像的事件通知
{
public:
	virtual HRESULT foo() = 0;
};

// isp接口
//EXTERN_C const IID IID_IispTask;
/*
/// {BC7DE54C-F483-4768-9CBA-3228D81600CD}
DEFINE_GUID(IID_IispTask, 
			0xbc7de54c, 0xf483, 0x4768, 0x9c, 0xba, 0x32, 0x28, 0xd8, 0x16, 0x0, 0xcd);
			// */

//class IispTask : public IUnknown // 视频处理接口
//{
//public:
//	virtual HRESULT QueryAccept(/*AM_MEDIA_TYPE**/void* mt) = 0;

//	virtual HRESULT BeginIsp() = 0;
//	virtual HRESULT IspTask(/*IMediaSample**/void* pMS) = 0;
//	virtual HRESULT EndIsp() = 0;
//};
EXTERN_C const IID IID_IispTask;
class IispTask : public IUnknown
{
public:
    virtual /* [local][id] */ HRESULT STDMETHODCALLTYPE QueryAccept( 
        void *mt) = 0;
    
    virtual /* [id] */ HRESULT STDMETHODCALLTYPE BeginIsp( void) = 0;
    
    virtual /* [local][id] */ HRESULT STDMETHODCALLTYPE IspTask( 
        void *pMS) = 0;
    
    virtual /* [id] */ HRESULT STDMETHODCALLTYPE EndIsp( void) = 0;
    
};



#endif // __LIBDXCAP_DATASTRU__20110805__