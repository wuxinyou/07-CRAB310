/********************************************************************
	created:	2011/08/05
	created:	5:8:2011   9:31
	purpose:	
*********************************************************************/

#ifndef __LIBDXCAP_DATASTRU__20110805__
#define __LIBDXCAP_DATASTRU__20110805__

typedef void* device_handle;
typedef void* image_handle;

// 运行状态
enum {state_stopped, state_paused, state_running};

// 去隔行模式
enum {di_none, di_weave, di_blend, di_bob};

// 降噪模式
enum {dn_none, dn_b};

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

#define X264CODEC_FILTER TEXT("x264 Codec\0")
enum {codec_sys,codec_x264};
typedef struct{
	int bitrate; // 码率（单位：kbps）
	int keyinterval;  //关键帧间隔
}VidCodecSysPara;

enum {x264_cqp, x264_crf, x264_abr};
typedef struct{
	int fps;
	int keyframeinterval;
	int rcMode;   //码率控制,x264_cqp(恒定质量), x264_crf(恒定码率), x264_abr(平均码率)
	int Quality;
	int Datarate;
//	char * Mp4file;	
}VidCodecX264Para;

enum {drate_color};
typedef struct{
	int nBrightness; // 亮度，取值(-255到255)
	int nContrast;  //对比度，取值(-100到100)
}DRateColorPara;

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