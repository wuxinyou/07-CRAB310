
#ifndef __DXMEDIACAP_2011__
#define __DXMEDIACAP_2011__

#include "datastru.h"

/*
描述：
	初始化 SDK ，必须在调用其他函数之前调用
参数：
	无
返回值：
	0 - 成功；失败则返回错误代码
// */
unsigned __stdcall DXInitialize();
void __stdcall DXUninitialize();

/*
描述：
	获取初始化成功的设备总数
参数：
	无
返回值：
	匹配的设备总数
// */
unsigned __stdcall DXGetDeviceCount();

/*
描述：
	枚举音视频编码过滤器
参数：
	devTags - [out] 用于返回获得的过滤器的 TAG 的数组
	num - [in/out] 指定 devTags 数组的元素个数，返回时则是实际上获得的过滤器的 TAG 的个数
返回值：
	0 - 成功；失败则返回错误代码
// */
unsigned __stdcall DXEnumVideoCodecs(PDEVICE_TAG devTags, unsigned& num);
unsigned __stdcall DXEnumAudioCodecs(PDEVICE_TAG devTags, unsigned& num);

/*
描述：
	枚举视频捕捉设备过滤器
参数：
	devTags - [out] 用于返回获得的过滤器的 TAG 的数组
	num - [in/out] 指定 devTags 数组的元素个数，返回时则是实际上获得的过滤器的 TAG 的个数
返回值：
	0 - 成功；失败则返回错误代码
// */
unsigned __stdcall DXEnumVideoDevices(PDEVICE_TAG devTags, unsigned& num);

/*
描述：
	枚举音频捕捉和渲染设备过滤器
参数：
	devTags - [out] 用于返回获得的过滤器的 TAG 的数组
	num - [in/out] 指定 devTags 数组的元素个数，返回时则是实际上获得的过滤器的 TAG 的个数
返回值：
	0 - 成功；失败则返回错误代码
// */
unsigned __stdcall DXEnumAudioDevices(PDEVICE_TAG devTags, unsigned& num);
unsigned __stdcall DXEnumSoundDevices(PDEVICE_TAG devTags, unsigned& num);

/*
描述：
	占用采集设备
参数：
	idx - [in] 设备在枚举过程中的序号
	err - [out] 返回错误代码
返回值：
	成功则返回设备句柄，否则返回 NULL。可通过 err 获得错误代码
// */
device_handle __stdcall DXOpenDevice(unsigned idx, unsigned* err = NULL);
void __stdcall DXCloseDevice(device_handle device);

/*
描述：
	将属性页显示在制定窗体的指定区域
参数：
	device - [in] 设备句柄
	attrID - [in] 属性类别
	hOwner - [in] 父窗体的句柄。NULL - 隐藏属性页
	rect - [in] 在父窗体上显示的区域。NULL - 表示父窗体的整个客户区
返回值：
	0 - 成功；失败则返回错误代码
// */
unsigned __stdcall DXShowDeviceAttr(device_handle device, unsigned attrID, HWND hOwner, RECT* rect);

/*
描述：
	获取视频属性
参数：
	device - [in] 设备句柄
	standard - [out] 视频制式
	colorspace - [out] 色彩空间
	width - [out] 视频宽度（单位：像素）
	height - [out] 视频高度（单位：像素）
	framerate - [out] 视频帧率（单位：帧/秒）
返回值：
	0 - 成功；失败则返回错误代码
// */
unsigned __stdcall DXGetVideoPara(device_handle device, unsigned& standard, unsigned& colorspace,
								  unsigned& width, unsigned& height, float& framerate);

/*
描述：
	枚举视频输出大小
参数：
	device - [in] 设备句柄
	devTags - [out] 用于返回获得的过滤器的 TAG 的数组
	num - [in/out] 指定 vidCaps 数组的元素个数，返回时则是实际上获得的输出格式 Caps 的个数
返回值：
	0 - 成功；失败则返回错误代码
// */
unsigned __stdcall DXEnumVideoCaps(device_handle device, PVIDEOCAPS vidCaps, unsigned& num);

/*
描述：
	设置视频属性
参数：
	device - [in] 设备句柄
	standard - [in] 视频制式
	colorspace - [in] 色彩空间
	width - [in] 视频宽度（单位：像素）
	height - [in] 视频高度（单位：像素）
	framerate - [in] 视频帧率（单位：帧/秒）
返回值：
	0 - 成功；失败则返回错误代码
// */
unsigned __stdcall DXSetVideoPara(device_handle device, unsigned standard, unsigned colorspace,
								  unsigned width, unsigned height, float framerate);

/*
描述：
	获取显示属性的取值范围、默认值、步长、标志
参数：
	device - [in] 设备句柄
	paraType - [in] 参数类型
					0 - 亮度，1 - 对比度，2 - 饱和度，3 - 色度，4 - 锐度
	pMin - [in] 最小值
	pMax - [in] 最大值
	pSteppingDelta - [in] 步长
	pDefault - [in] 默认值
	pCapsFlags - [in] 自动/手动标志
返回值：
	0 - 成功；失败则返回错误代码
// */
unsigned __stdcall DXGetDisplayParaRange(device_handle device, unsigned paraType,
										 long* pMin, long* pMax, long* pSteppingDelta, long* pDefault, long* pCapsFlags);

/*
描述：
	获取显示属性
参数：
	device - [in] 设备句柄
	paraType - [in] 参数类型
					0 - 亮度，1 - 对比度，2 - 饱和度，3 - 色度，4 - 锐度
	value - [out] 参数值
	flag - [out] 自动/手动标志
返回值：
	0 - 成功；失败则返回错误代码
// */
unsigned __stdcall DXGetDisplayPara(device_handle device, unsigned paraType, long& value, long& flags);

/*
描述：
	设置显示属性
参数：
	device - [in] 设备句柄
	paraType - [in] 参数类型
					0 - 亮度，1 - 对比度，2 - 饱和度，3 - 色度，4 - 锐度
	value - [in] 参数值
	flag - [in] 自动/手动标志
返回值：
	0 - 成功；失败则返回错误代码
// */
unsigned __stdcall DXSetDisplayPara(device_handle device, unsigned paraType, long value, long flags);

/*
描述：
	获取设备当前选择的端子和包含的输入端子
参数：
	device - [in] 设备句柄
	curSource - [out] 当前选择的输入端子的序号。NULL - 忽略
	sources - [out] 包含的输入端子的类型数组（比如：S-VIDEO、DV...）。NULL - 忽略
	num - [in/out] 端子数量。NULL - 忽略，此时尽可获取当前选择的输入端子
返回值：
	0 - 成功；失败则返回错误代码
// */
unsigned __stdcall DXGetVideoSources(device_handle device, unsigned* curSource, unsigned* sources = NULL, unsigned char* num = NULL);

/*
描述：
	设置设备的输入端子
参数：
	device - [in] 设备句柄
	source - [in] 当前选择的输入端子的序号
返回值：
	0 - 成功；失败则返回错误代码
// */
unsigned __stdcall DXSetVideoSource(device_handle device, unsigned source);

/*
描述：
	获取设备的信号状态
参数：
	device - [in] 设备句柄
	signal - [out] 信号状态。0 - 信号丢失；1 - 信号正常
返回值：
	0 - 成功；失败则返回错误代码
// */
unsigned __stdcall DXGetSignalPresent(device_handle device, unsigned& signal);

/*
描述：
	控制设备运行状态
参数：
	device - [in] 设备句柄
返回值：
	0 - 成功；失败则返回错误代码
// */
unsigned __stdcall DXDeviceRun(device_handle device);
unsigned __stdcall DXDevicePause(device_handle device);
unsigned __stdcall DXDeviceStop(device_handle device);

/*
描述：
	获取设备运行状态
参数：
	device - [in] 设备句柄
	state - [out] 设备运行状态
返回值：
	0 - 成功；失败则返回错误代码
// */
unsigned __stdcall DXGetDeviceState(device_handle device, unsigned& state);

/*
描述：
	将视频显示在指定窗体的矩形区域内
参数：
	device - [in] 设备句柄
	hWnd - [in] 显示视频的窗体句柄。NULL - 停止显示视频
	rect - [in] 视频显示的矩形区域。NULL - 占用整个窗体
	vvmrtype - [in] 视频显示模式，0为OVERLAY显示，1为离屏显示,2为VMR9显示模式
返回值：
	0 - 成功；失败则返回错误代码
// */
unsigned __stdcall DXStartPreview(device_handle device, HWND hWnd, PRECT rect, unsigned vmrtype);

/*
描述：
	停止预览
参数：
	device - [in] 设备句柄
返回值：
	0 - 成功；失败则返回错误代码
// */
unsigned __stdcall DXStopPreview(device_handle device);

/*
描述：
	冻结视频显示部分
参数：
	device - [in] 设备句柄
	bFreeze - [in] TRUE - 冻结显示，FALSE - 解冻显示
返回值：
	0 - 成功；失败则返回错误代码
// */
unsigned __stdcall DXFreezePreview(device_handle device, BOOL bFreeze);

/*
描述：
	检查设备是否包含音频
参数：
	device - [in] 设备句柄
	bHasAudio - [out] TRUE - 包含音频，FALSE - 没有音频
返回值：
	0 - 成功；失败则返回错误代码
// */
unsigned __stdcall DXHasAudio(device_handle device, BOOL& bHasAudio);

/*
描述：
	为设备分配音频采集设备。
		注意：!!! 只能在 state_stopped 状态下调用
参数：
	device - [in] 设备句柄
	bSound - [in] TRUE - 开始声音输出，FALSE - 终止声音输出
	audioDevice - [in] 音频采集设备。NULL - 使用设备自带的音频
返回值：
	0 - 成功；失败则返回错误代码
// */
unsigned __stdcall DXSetAudioDevice(device_handle device, PDEVICE_TAG audioDevice = NULL);

/*
描述：
	开始或者终止声音输出。
		注意：!!! 只有开始了声音输出，静音操作、音量调节、录像时包含音频等操作才能成功
参数：
	device - [in] 设备句柄
	bSound - [in] TRUE - 开始声音输出，FALSE - 终止声音输出
	soundDevice - [in] 声音输出设备。NULL - 使用默认设备
返回值：
	0 - 成功；失败则返回错误代码
// */
unsigned __stdcall DXSetSoundOut(device_handle device, BOOL bSound/*, PDEVICE_TAG soundDevice = NULL*/);

/*
描述：
	静音操作
参数：
	device - [in] 设备句柄
	bMute - [in] TRUE - 静音，FALSE - 非静音
返回值：
	0 - 成功；失败则返回错误代码，一般失败原因是因为没有开始声音输出
// */
unsigned __stdcall DXEnableMute(device_handle device, BOOL bMute);

/*
描述：
	设置音量和平衡
参数：
	device - [in] 设备句柄
	volume - [in] 音量大小，取值范围(0, 100]
	balance - [in] 左右平衡，取值范围[-10, 10]，负数表示左声道强，正数表述右声道强，0 - 左右平衡
				注意：!!! NULL - 表示不设置平衡
返回值：
	0 - 成功；失败则返回错误代码，一般失败原因是因为没有开始声音输出
// */
unsigned __stdcall DXSetAudioVolume(device_handle device, unsigned char volume, unsigned char* const balance = NULL);

/*
描述：
	获取音量和平衡
参数：
	device - [in] 设备句柄
	volume - [out] 音量大小，取值范围(0, 100]
				注意：!!! NULL - 表示不获取音量
	balance - [out] 左右平衡，取值范围[-10, 10]，负数表示左声道强，正数表述右声道强，0 - 左右平衡
				注意：!!! NULL - 表示不获取平衡
返回值：
	0 - 成功；失败则返回错误代码，一般失败原因是因为没有开始声音输出
// */
unsigned __stdcall DXGetAudioVolume(device_handle device, unsigned char* volume, unsigned char* balance = NULL);

/*
描述：
	更换视频编码器
		注意：!!! 当正在进行录像时，则操作失败
参数：
	device - [in] 设备句柄
	videoEncoder - [in] 视频编码器的 TAG，NULL - 表示不用编码，即录像时采用原始数据
返回值：
	0 - 成功；失败则返回错误代码
// */
unsigned __stdcall DXSetVideoCodec(device_handle device, PDEVICE_TAG videoEncoder);

/*
描述：
	设置视频编码器的具体属性（改变编码器类型的时候需调用此函数，因为默认值会导致录像不正常）
参数：
	device - [in] 设备句柄
	codecType--[in]编码器的类型,如:codec_x264
	pPara - [in]编码器的具体属性（codec_x264,codec_xvid的属性数组目前都用VidCodecX264Para），NULL - 表示使用默认属性
返回值：
	0 - 成功；失败则返回错误代码
// */
unsigned __stdcall DXSetVideoCodecPara(device_handle device, unsigned codecType, void* pPara);
/*
描述：
	获取视频编码器的具体属性
参数：
	device - [in] 设备句柄
	codecType--[out]编码器的类型,如:codec_x264
	pPara - [out]编码器的具体属性
返回值：
	0 - 成功；失败则返回错误代码
// */
unsigned __stdcall DXGetVideoCodecPara(device_handle device, unsigned& codecType, void* pPara);

/*
描述：
	更换音频编码器
		注意：!!! 当正在进行录像时，则操作失败
参数：
	device - [in] 设备句柄
	audioEncoder - [in] 音频编码器的 TAG，NULL - 表示不用编码，即录像时采用原始数据
返回值：
	0 - 成功；失败则返回错误代码
// */
unsigned __stdcall DXSetAudioCodec(device_handle device, PDEVICE_TAG audioEncoder);

/*
描述：
	开始录像
参数：
	device - [in] 设备句柄
	szFileName - [in] 指定录像文件全路径(x264保存为mp4格式的)。NULL - 停止录像
	saveAudio - [in] 是否将音频也录制到文件中
	timeSize - [in] 限定录像文件的时间长度（单位：秒），NULL - 不限制
	dataSize - [in] 限定录像文件的数据长度（单位：字节），NULL - 不限制
	saveNotify - [in] 录像事件通知接口指针
返回值：
	0 - 成功；失败则返回错误代码
// */
unsigned __stdcall DXStartCapture(device_handle device, TCHAR* szFileName, BOOL saveAudio,
										  unsigned* timeSize = NULL, unsigned* dataSize = NULL,
										  ISaveNotify* saveNotify = NULL);

/*
描述：
	停止录像
参数：
	device - [in] 设备句柄
返回值：
	0 - 成功；失败则返回错误代码
// */
unsigned __stdcall DXStopCapture(device_handle device);

/*
描述：
	冻结录像部分（包括视频和音频）
	注意：!!! 适用于需要多段时间录像的情况
参数：
	device - [in] 设备句柄
	bFreeze - [in] TRUE - 冻结录像，FALSE - 解冻录像
返回值：
	0 - 成功；失败则返回错误代码
// */
unsigned __stdcall DXFreezeCaputre(device_handle device, BOOL bFreeze);

/*
描述：
	插入视频效果（针对原始视频数据）
	参数：
	device - [in] 设备句柄
	ispTask - [in] 新插入的视频效果的接口指针
返回值：
	0 - 成功；失败则返回错误代码
// */
unsigned __stdcall DXAttachIspTask(device_handle device, IispTask* ispTask);
unsigned __stdcall DXDetachIspTask(device_handle device, IispTask* ispTask);

/*
描述：
	编码视频数据回调的函数原型
参数：
	fourcc - [in] 获取的编码数据的编码器的FOURCC
	buffer - [in] 缓冲区指针
	bufferSize - [out] 获取的编码数据的缓冲区大小（单位：字节）
	context - [in] 回调函数的上下文
返回值：
	0 - 成功；失败则返回错误代码
// */
typedef unsigned (__stdcall *fnEncVideoCallback)(unsigned fourcc, unsigned char* buffer, 
	unsigned bufferSize, void* context);

/*
描述：
	设置编码视频数据回调的函数
参数：
	device - [in] 设备句柄
	fn - [in] 回调函数指针，NULL - 停止回调
	context - [in] 回调函数的上下文
返回值：
	0 - 成功；失败则返回错误代码
// */
unsigned __stdcall DXSetEncVideoCallback(device_handle device, fnEncVideoCallback fn, void* context);

/*
描述：
	开始编码视频数据回调的函数
参数：
	device - [in] 设备句柄
	fn - [in] 回调函数指针，NULL - 停止回调
	context - [in] 回调函数的上下文
返回值：
	0 - 成功；失败则返回错误代码
// */
unsigned __stdcall DXStartEncVideoCallback(device_handle device, fnEncVideoCallback fn, void* context);

/*
描述：
	停止编码视频数据回调的函数
参数：
	device - [in] 设备句柄
返回值：
	0 - 成功；失败则返回错误代码
// */
unsigned __stdcall DXStopEncVideoCallback(device_handle device);

/*
描述：
	使能去隔行功能
参数：
	device - [in] 设备句柄
	deinterlace - [in] 去隔行化方法：     0 -- 自适应隔行处理
	                                      1 -- SimpleBob
//                                        2 -- TomsMoComp
//                                        3 -- YADIF
//                                        其他值表示自动取消隔行功能
返回值：
	0 - 成功；失败则返回错误代码
// */
unsigned __stdcall DXEnableDeinterlace(device_handle device, unsigned deinterlace);

/*
描述：
	使能去噪功能
参数：
	device - [in] 设备句柄
	denoise - [in] 降噪标准 (5 - 100)，其他值表示自动取消去噪功能
返回值：
	0 - 成功；失败则返回错误代码
// */
unsigned __stdcall DXEnableDenoise(device_handle device, unsigned denoise = 35);

/*
描述：
	锐化处理功能
参数：
	device - [in] 设备句柄
	deSharpness - [in] 锐化标准(0 - 255)，其它值表示自动取消锐化功能
返回值：
	0 - 成功；失败则返回错误代码
// */
unsigned __stdcall DXEnableSharpen(device_handle device, unsigned deSharpness = 128);

/*
描述：
	使能伪彩功能
参数：
	device - [in] 设备句柄
	szPColorTemplateFile - [in] 伪彩的模板文件。NULL - 停止使用伪彩
	pcolorDepth - [in] 伪彩的色深。此参数保留。
返回值：
	0 - 成功；失败则返回错误代码
// */
unsigned __stdcall DXEnablePColor(device_handle device, TCHAR* szPColorTemplateFile, unsigned pcolorDepth);

unsigned __stdcall DXConvertYUVtoRGB(device_handle device, void* pYUVBuf,
							  void* pRGBBuf,
							  long lImgWidth, 
							  long lImgHeight,
							  BOOL bInverted,
                              BOOL bInvertColor);

/*
描述：
	音频原始数据回调的函数原型
参数：
	buffer - [in] 缓冲区指针
	bufferSize - [out] 获取的编码数据的缓冲区大小（单位：字节）
	context - [in] 回调函数的上下文
返回值：
	0 - 成功；失败则返回错误代码
// */
typedef unsigned (__stdcall *fnAudDataCallback)(unsigned char* buffer, unsigned bufferSize, void* context);

/*
描述：
	设置音频原始数据回调的函数
参数：
	device - [in] 设备句柄
	fn - [in] 回调函数指针，NULL - 停止回调
	context - [in] 回调函数的上下文
返回值：
	0 - 成功；失败则返回错误代码
// */
unsigned __stdcall DXSetAudDataCallback(device_handle device, fnAudDataCallback fn, void* context);

/*
描述：
	开始音频原始数据回调的函数
参数：
	device - [in] 设备句柄
	fn - [in] 回调函数指针，NULL - 停止回调
	context - [in] 回调函数的上下文
返回值：
	0 - 成功；失败则返回错误代码
// */
unsigned __stdcall DXStartAudDataCallback(device_handle device, fnAudDataCallback fn, void* context);

/*
描述：
	停止音频原始数据回调的函数
参数：
	device - [in] 设备句柄
返回值：
	0 - 成功；失败则返回错误代码
// */
unsigned __stdcall DXStopAudDataCallback(device_handle device);

/*
描述：
	设置时间OSD参数的函数
参数：
	device - [in] 设备句柄
	x,y - [in]时间OSD的位置坐标
返回值：
	0 - 成功；失败则返回错误代码
// */
unsigned __stdcall DXSetTimeOSD
(
	/*in*/ device_handle device, 
	/*in*/ int x, 
	/*in*/ int y,  
	/*in*/ int pointSize,
	/*in*/ LPCTSTR faceName = TEXT("Arial"),
	/*in*/ COLORREF color = RGB(0,0,255),
	/*in*/ COLORREF bgcolor = RGB(0, 0, 0),
	/*in*/ BOOL transparent = TRUE
);

/*
描述：
	设置文本OSD参数的函数
参数：
	device - [in] 设备句柄
	x,y - [in]时间OSD的位置坐标
返回值：
	0 - 成功；失败则返回错误代码
// */							
unsigned __stdcall DXSetTextOSD
(
	/*in*/ device_handle device, 
	/*in*/ int x, 
	/*in*/ int y,
	/*in*/ int TextNO,
	/*in*/ LPCTSTR osdText,
	/*in*/ int pointSize,
	/*in*/ LPCTSTR faceName = TEXT("Arial"),
	/*in*/ COLORREF color  = RGB(0,0,255),
	/*in*/ COLORREF bgcolor = RGB(0, 0, 0),
	/*in*/ BOOL transparent = TRUE 
);

/*
描述：
	设置图片OSD参数的函数
参数：
	device - [in] 设备句柄
	x,y - [in]时间OSD的位置坐标
返回值：
	0 - 成功；失败则返回错误代码
// */
unsigned __stdcall DXSetPictureOSD
(
	/*in*/ device_handle device, 
	/*in*/ int x, 
	/*in*/ int y,
	/*in*/ int PicNO,
	/*in*/ LPCTSTR picFileName,
	/*in*/ BOOL transparent = TRUE,
	/*in*/ unsigned char alpha = 255
);

/*
描述：
	设置图片OSD参数的函数
参数：
	device - [in] 设备句柄
	osdType - [in]叠加类型
返回值：
	0 - 成功；失败则返回错误代码
// */
unsigned __stdcall DXEnOSDDisp
(
	/*in*/ device_handle device, 
	/*in*/ unsigned osdType,       //0表示时间叠加，1表示文本叠加，2表示图片叠加
	/*in*/ int number,				/* 叠加编号，当number = -1时为全部 */
	/*in*/ BOOL enable
);

/*
描述：
	从加密芯片用户区读取数据的函数
参数：
	device - [in] 设备句柄
	chPassWord - [in]密码
	chData------[out]读取数据空间
	chLen-------[out]读取数据长度,不超过0x20
返回值：
	0 - 成功；失败则返回错误代码
// */
unsigned __stdcall DXReadDeviceSerial(device_handle device,unsigned char * chPassWord,
						 unsigned char * chData,  unsigned char& chLen);

//从加密芯片用户区读出数据
/*
描述：
	向加密芯片用户区写入数据的函数
参数：
	device - [in] 设备句柄
	chPassWord - [in]密码
	chData------[in]写入数据空间
	chLen-------[in]写入数据长度,不超过0x20
返回值：
	0 - 成功；失败则返回错误代码
// */
unsigned __stdcall DXWriteDeviceSerial(device_handle device,unsigned char * chPassWord,
						 unsigned char * chData,  unsigned char chLen);

/*
描述：
	原始视频数据回调的函数原型
参数：
	buffer - [in] 缓冲区指针
	colorSpace - [in] 获取的原始数据的色彩空间类型
	width - [in] 获取的原始数据的像素宽度
	height - [in] 获取的原始数据的像素高度
	bytesWidth - [in] 获取的原始数据的字节宽度
	context - [in] 回调函数的上下文
返回值：
	0 - 成功；失败则返回错误代码
// */
typedef unsigned (__stdcall *fnRawVideoCallback)(unsigned char* buffer, unsigned colorSpace,
									   unsigned width, unsigned height, unsigned bytesWidth, void* context);

/*
描述：
	设置原始视频数据回调的函数
参数：
	device - [in] 设备句柄
	fn - [in] 回调函数指针，NULL - 停止回调
	context - [in] 回调函数的上下文
返回值：
	0 - 成功；失败则返回错误代码
// */
unsigned __stdcall DXSetRawVideoCallback(device_handle device, fnRawVideoCallback fn, void* context);

/*
描述：
	开始原始视频数据回调的函数
参数：
	device - [in] 设备句柄
	fn - [in] 回调函数指针，NULL - 停止回调
	context - [in] 回调函数的上下文
返回值：
	0 - 成功；失败则返回错误代码
// */
unsigned __stdcall DXStartRawVideoCallback(device_handle device, fnRawVideoCallback fn, void* context);

/*
描述：
	停止原始视频数据回调的函数
参数：
	device - [in] 设备句柄
返回值：
	0 - 成功；失败则返回错误代码
// */
unsigned __stdcall DXStopRawVideoCallback(device_handle device);

/*
描述：
	暂停原始视频数据回调的函数
参数：
	device - [in] 设备句柄
	bPause---[in] true:暂停原始流回调;false:重新开始原始流回调
返回值：
	0 - 成功；失败则返回错误代码
// */
unsigned __stdcall DXPauseRawVideoCallback(device_handle device, bool bPause);

/*
描述：
	获取指定区域的原始视频帧数据到缓冲区
参数：
	device - [in] 设备句柄
	buffer - [in] 指向缓冲区。NULL - 后续参数返回相应的数据，比如，所需缓冲区的大小、颜色空间、视频尺寸
	bufferLen - [in] 指向的缓冲区的大小（单位：字节）
	gotBufferLen - [out] 实际获取的数据的大小（单位：字节）
	colorSpace - [out] 获取的原始数据的色彩空间类型
	width - [out] 获取的原始数据的像素宽度
	height - [out] 获取的原始数据的像素高度
	bytesWidth - [out] 获取的原始数据的字节宽度
	rect - [in] 指定获取数据的区域
返回值：
	0 - 成功；失败则返回错误代码
// */
unsigned __stdcall DXGetFrameBuffer(device_handle device, unsigned char* buffer, unsigned bufferLen, unsigned* gotBufferLen = NULL,
									unsigned* colorSpace = NULL, unsigned* width = NULL, unsigned* height = NULL, unsigned* bytesWidth = NULL,
									PRECT rect = NULL);

/*
描述：
	保存原始视频帧数据到 BMP文件
参数：
	szFileName - [in] BMP文件路径
	buffer - [in] 指向缓冲区
	bufferLen - [in] 指向的缓冲区的大小（单位：字节）
	colorSpace - [in] 获取的原始数据的色彩空间类型
	width - [in] 获取的原始数据的像素宽度
	height - [in] 获取的原始数据的像素高度
	bytesWidth - [in] 获取的原始数据的字节宽度
返回值：
	0 - 成功；失败则返回错误代码
// */
unsigned __stdcall DXSaveBMPFile(TCHAR* szFileName, unsigned char* buffer, unsigned bufferLen,
								 unsigned colorSpace, unsigned width, unsigned height, unsigned bytesWidth);

/*
描述：
	保存原始视频帧数据到 JPG文件
参数：
	szFileName - [in] JPG文件路径
	buffer - [in] 指向缓冲区
	bufferLen - [in] 指向的缓冲区的大小（单位：字节）
	colorSpace - [in] 获取的原始数据的色彩空间类型
	width - [in] 获取的原始数据的像素宽度
	height - [in] 获取的原始数据的像素高度
	bytesWidth - [in] 获取的原始数据的字节宽度
	quality - [in] JPG文件的画面质量
返回值：
	0 - 成功；失败则返回错误代码
// */
unsigned __stdcall DXSaveJPGFile(TCHAR* szFileName, unsigned char* buffer, unsigned bufferLen,
								 unsigned colorSpace, unsigned width, unsigned height, unsigned bytesWidth, unsigned quality);

/*
描述：
	直接抓取原始视频帧数据到 BMP文件
参数：
	device - [in] 设备句柄
	szFileName - [in] BMP文件路径
	rect - [in] 指定获取数据的区域
返回值：
	0 - 成功；失败则返回错误代码
// */
unsigned __stdcall DXSnapToBMPFile(device_handle device, TCHAR* szFileName, PRECT rect = NULL);

/*
描述：
	直接抓取原始视频帧数据到 BMP文件
参数：
	device - [in] 设备句柄
	szFileName - [in] BMP文件路径
	buffer - [in] 指向缓冲区
	bufferLen - [in] 指向的缓冲区的大小（单位：字节）
	colorSpace - [in] 获取的原始数据的色彩空间类型
	width - [in] 获取的原始数据的像素宽度
	height - [in] 获取的原始数据的像素高度
	bytesWidth - [in] 获取的原始数据的字节宽度
	rect - [in] 指定获取数据的区域
返回值：
	0 - 成功；失败则返回错误代码
// */
unsigned __stdcall DXSnapToJPGFile(device_handle device, TCHAR* szFileName, unsigned quality, PRECT rect = NULL);

/*
描述：
	翻转视频
参数：
	device - [in] 设备句柄
	flip - [in] TRUE - 启用翻转，FALSE - 禁用翻转
返回值：
	0 - 成功；失败则返回错误代码
// */
unsigned __stdcall DXFlipVideo(device_handle device, BOOL flip);

/*
描述：
	镜像视频
参数：
	device - [in] 设备句柄
	mirror - [in] TRUE - 启用镜像，FALSE - 禁用镜像
返回值：
	0 - 成功；失败则返回错误代码
// */
unsigned __stdcall DXMirrorVideo(device_handle device, BOOL mirror);

/*
描述：
	由图片缓冲创建预览对象
参数：
	imgbuffer - [in] 图片缓冲区
	buffersize - [in] 图片缓冲区的大小（单位：字节）
	colorspace - [in] 图片缓冲的数据的色彩空间
	width - [in] 图片的宽度（单位：像素）
	height - [in] 图片的高度（单位：像素）
	err - [out] 返回错误代码
返回值：
	成功则返回图像句柄，否则返回 NULL。可通过 err 获得错误代码
// */
image_handle __stdcall DXCreateBufferImg(unsigned char* imgbuffer, unsigned buffersize,
										  unsigned colorspace, unsigned width, unsigned height,
										  unsigned* err);

/*
描述：
	由图片文件创建预览对象
参数：
	szImgFile - [in] 图片文件全路径
	err - [out] 返回错误代码
返回值：
	成功则返回图像句柄，否则返回 NULL。可通过 err 获得错误代码
// */
image_handle __stdcall DXCreateFileImg(TCHAR* szImgFile, unsigned* err);

/*
描述：
	由更新预览对象到指定的窗体的相应区域
参数：
	img - [in] 预览对象
	hPrevWnd - [in] 预览的窗体
	rect - [in] 预览的区域
返回值：
	0 - 成功；失败则返回错误代码
// */
unsigned __stdcall DXUpdateImg(image_handle img, HWND hPrevWnd, RECT* rect);

/*
描述：
	删除预览对象
参数：
	img - [in] 预览对象
返回值：
	无
// */
void __stdcall DXDestroyImg(image_handle img);

/*
描述：
	调节码流的相关属性值
参数：
	device - [in] 设备句柄
	RateType--[in]码流属性的类型,如:drate_color
	pPara - [in]编码器的具体属性值，NULL - 表示停止调节码流的对应属性
返回值：
	0 - 成功；失败则返回错误代码
// */
unsigned __stdcall DXEnDataRaterPara(device_handle device, unsigned RateType, void* pPara);

/*
描述：
	调节码流的相关属性值
参数：
	src - [in] 原始流
	dst--[out]输出流
	pixelsPerLines - [in]每一行的像素总数
	width - [in]宽
	height - [in]高
返回值：
	0 - 成功；失败则返回错误代码
// */
unsigned __stdcall DXYuy2Gray(unsigned char *src, unsigned char *dst, unsigned pixelsPerLines, unsigned width, unsigned height);

#endif // __DXMEDIACAP_2011__
