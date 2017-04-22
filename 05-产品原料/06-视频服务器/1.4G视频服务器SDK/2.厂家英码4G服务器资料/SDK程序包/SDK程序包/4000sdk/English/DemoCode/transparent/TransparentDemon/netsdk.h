#ifndef NETMODULE_H
#define NETMODULE_H

#ifdef WIN32

#ifdef NETMODULE_EXPORTS
#define H264_DVR_API  extern "C" __declspec(dllexport)
#else
#define H264_DVR_API  extern "C" __declspec(dllimport)   //VC 用
#endif

#ifndef CALL_METHOD
#define CALL_METHOD	__stdcall  //__cdecl
#endif

#else	//linux
#define H264_DVR_API	extern "C"
#define CALL_METHOD
#define CALLBACK
#define WORD	unsigned short
#define DWORD	unsigned long
#define LPDWORD	DWORD*
#define BOOL	int
#define TRUE	1
#define FALSE	0
#define BYTE	unsigned char
#define LONG	long
#define UINT	unsigned int
#define HDC		void*
#define HWND	void*
#define LPVOID	void*
//#define NULL	0
#define LPCSTR  char*
#define LPCTSTR  const char*
#endif


enum SDK_RET_CODE
{	
	H264_DVR_NOERROR					= 0,					//没有错误
	H264_DVR_SUCCESS					= 1,					//返回成功
	H264_DVR_SDK_NOTVALID			= -10000,				//非法请求
	H264_DVR_NO_INIT					= -10001,				//SDK未经初始化
	H264_DVR_ILLEGAL_PARAM			= -10002,			//用户参数不合法
	H264_DVR_INVALID_HANDLE			= -10003,			//句柄无效
	H264_DVR_SDK_UNINIT_ERROR		= -10004,			//SDK清理出错
	H264_DVR_SDK_TIMEOUT				= -10005,			//等待超时
	H264_DVR_SDK_MEMORY_ERROR		= -10006,			//内存错误，创建内存失败
	H264_DVR_SDK_NET_ERROR			= -10007,			//网络错误
	H264_DVR_SDK_OPEN_FILE_ERROR		= -10008,			//打开文件失败
	H264_DVR_SDK_UNKNOWNERROR		= -10009,			//未知错误
	H264_DVR_DEV_VER_NOMATCH			= -11000,			//收到数据不正确，可能版本不匹配
	H264_DVR_SDK_NOTSUPPORT			= -11001,			//版本不支持

	H264_DVR_OPEN_CHANNEL_ERROR		= -11200,			//打开通道失败
	H264_DVR_CLOSE_CHANNEL_ERROR		= -11201,			//关闭通道失败
	H264_DVR_SUB_CONNECT_ERROR		= -11202,			//建立媒体子连接失败
	H264_DVR_SUB_CONNECT_SEND_ERROR	= -11203,			//媒体子连接通讯失败

	

	/// 用户管理部分错误码
	H264_DVR_NOPOWER					= -11300,			//无权限
	H264_DVR_PASSWORD_NOT_VALID		= -11301,			// 账号密码不对
	H264_DVR_LOGIN_USER_NOEXIST		= -11302,			//用户不存在
	H264_DVR_USER_LOCKED				= -11303,			// 该用户被锁定
	H264_DVR_USER_IN_BLACKLIST		= -11304,			// 该用户不允许访问(在黑名单中)
	H264_DVR_USER_HAS_USED			= -11305,			// 该用户以登陆
	H264_DVR_USER_NOT_LOGIN			= -11306,			// 该用户没有登陆
	H264_DVR_CONNECT_DEVICE_ERROR    = -11307,			//可能设备不存在
	H264_DVR_ACCOUNT_INPUT_NOT_VALID = -11308,			//用户管理输入不合法
	H264_DVR_ACCOUNT_OVERLAP			= -11309,			//索引重复
	H264_DVR_ACCOUNT_OBJECT_NONE		= -11310,			//不存在对象, 用于查询时
	H264_DVR_ACCOUNT_OBJECT_NOT_VALID= -11311,			//不存在对象
	H264_DVR_ACCOUNT_OBJECT_IN_USE	= -11312,			//对象正在使用
	H264_DVR_ACCOUNT_SUBSET_OVERLAP	= -11313,			//子集超范围 (如组的权限超过权限表，用户权限超出组的权限范围等等)
	H264_DVR_ACCOUNT_PWD_NOT_VALID	= -11314,			//密码不正确
	H264_DVR_ACCOUNT_PWD_NOT_MATCH	= -11315,			//密码不匹配
	H264_DVR_ACCOUNT_RESERVED		= -11316,			//保留帐号


	/// 配置管理相关错误码
	
	H264_DVR_OPT_RESTART				= -11400,			// 保存配置后需要重启应用程序
	H264_DVR_OPT_REBOOT				= -11401,			// 需要重启系统
	H264_DVR_OPT_FILE_ERROR			= -11402,			// 写文件出错
	H264_DVR_OPT_CAPS_ERROR			= -11403,			// 配置特性不支持
	H264_DVR_OPT_VALIDATE_ERROR		= -11404,			// 配置校验失败
	H264_DVR_OPT_CONFIG_NOT_EXIST	= -11405,			// 请求或者设置的配置不存在
	
	/// 

	H264_DVR_CTRL_PAUSE_ERROR		= -11500,			//暂停失败
	H264_DVR_SDK_NOTFOUND			= -11501,			//查找失败，没有找到对应文件
	H264_DVR_CFG_NOT_ENABLE         = -11502,           //配置未启用

	H264_DVR_DECORD_FAIL            = -11503,           //配置未启用

	//DNS协议解析返回错误码
	H264_DVR_SOCKET_ERROR             = -11600,         //创建套节字失败
	H264_DVR_SOCKET_CONNECT           = -11601,         //连接套节字失败
	H264_DVR_SOCKET_DOMAIN            = -11602,         //域名解析失败
	H264_DVR_SOCKET_SEND              = -11603,         //发送数据失败

};


//云台操作类型
enum PTZ_ControlType
{
	TILT_UP = 0,			//云台左
	TILT_DOWN,				//右
	PAN_LEFT,				//上
	PAN_RIGHT,				//下
	PAN_LEFTTOP,			//左上
	PAN_LEFTDOWN,			//左下
	PAN_RIGTHTOP,			//右上
	PAN_RIGTHDOWN,			//右下
	ZOOM_OUT,				//变倍小
	ZOOM_IN,				//变倍大
	FOCUS_FAR,				//焦点后调
	FOCUS_NEAR,				//焦点前调
	IRIS_OPEN,				//光圈扩大
	IRIS_CLOSE,				//光圈缩小

	EXTPTZ_OPERATION_ALARM,			///< 报警功能 
	EXTPTZ_LAMP_ON,					///< 灯光开
	EXTPTZ_LAMP_OFF,				//灯光关
	EXTPTZ_POINT_SET_CONTROL,			//设置预置点 
	EXTPTZ_POINT_DEL_CONTROL,			//清除预置点 
	EXTPTZ_POINT_MOVE_CONTROL,			//转预置点
	EXTPTZ_STARTPANCRUISE,			//开始水平旋转			
	EXTPTZ_STOPPANCRUISE,			//停止水平旋转	
	EXTPTZ_SETLEFTBORDER,			//设置左边界		
	EXTPTZ_SETRIGHTBORDER,			//设置右边界	
	EXTPTZ_STARTLINESCAN,			//自动扫描开始 
	EXTPTZ_CLOSELINESCAN,			//自动扫描开停止 
	EXTPTZ_ADDTOLOOP,				//加入预置点到巡航	p1巡航线路	p2预置点值	
	EXTPTZ_DELFROMLOOP,				//删除巡航中预置点	p1巡航线路	p2预置点值	
	EXTPTZ_POINT_LOOP_CONTROL,			//开始巡航
	EXTPTZ_POINT_STOP_LOOP_CONTROL,	//停止巡航
	EXTPTZ_CLOSELOOP,				//清除巡航	p1巡航线路		
	EXTPTZ_FASTGOTO,				//快速定位	
	EXTPTZ_AUXIOPEN,				//辅助开关，关闭在子命令中
	EXTPTZ_OPERATION_MENU,				//球机菜单操作，其中包括开，关，确定等等
	EXTPTZ_REVERSECOMM,				//镜头翻转
	EXTPTZ_OPERATION_RESET,			///< 云台复位

	EXTPTZ_TOTAL,
};


#define PAN_AUTO		29	/* 云台以SS的速度左右自动扫描 */
#define EXTPTZ_FASTGOTO	30	//三维定位


#define NET_MAX_CHANNUM 			32			//最大通道个数
#define NET_DECORDR_CH              16          //最大解码通道个数
#define NET_MAX_USER_NUM			60			//最多用户数
#define NET_MAX_RIGTH_NUM			128			//最多权限数
#define NET_MAX_GROUP_NUM			50			//最多组数
#define NET_MAX_USER_LENGTH			32			//用户名密码最大长度
#define NET_MAX_COMBINE_NUM			2			//最大组合编码通道数
#define NET_MAX_DECORDR_CH          16          //最大解码通道个数

#define NET_MAX_DDNS_TYPE			5			//支持的DDNS种类
#define NET_MAX_ARSP_TYPE			5
#define NET_MAX_ALARMSERVER_TYPE    5           //支持报警中心种类
#define NET_MAX_SYSFUNC				20			//最多系统功能个数
#define NET_MAX_PTZ_PROTOCOL_LENGTH 32			//云台协议名称最大长度
#define NET_N_WEEKS					7			//星期数
#define	NET_N_TSECT					6			//时间段数
#define NET_MD_REGION_ROW			32			//动态检测区域行数
#define NET_COVERNUM				8			 //覆盖区域数
#define NET_MAX_FILTERIP_NUM		64			//IP地址最大过滤数
#define NET_NAME_PASSWORD_LEN		64			//用户名密码最大长度
#define NET_MAX_PATH_LENGTH	        260			//路径长度
#define NET_N_MIN_TSECT				2
#define NET_MAX_RETURNED_LOGLIST	128			//最多日志条数
#define NET_MAX_MAC_LEN             32          //MAC地址字符最大长度
#define NET_IW_ENCODING_TOKEN_MAX   128
#define NET_MAX_AP_NUMBER           10          //SID最大数量，暂定10
#define NET_MAX_INFO_LEN		    128
#define NET_MAX_USERNAME_LENGTH		128
#define NET_MAX_SERIALNO_LENGTH		128          //最大解码通道个数

//DDNS参数
#define DDNS_MAX_DDNS_NAMELEN 64  //主机名长度
#define DDNS_MAX_DDNS_PWDLEN 32   //密码长度
#define DDNS_MAX_DDNS_IPSIZE 64   //IP地址长度
#define DDNS_MAX_DDNS_IDSIZE 32   //设备标识长度
#define DDNS_MAX_SERIALINFO_SIZE 16 //序列号以及用户名长度



//摄象机参数
#define CAMERAPARA_MAXNUM  16    //曝光能力中目前最大长度
//短信最大数量
#define MAX_RECIVE_MSG_PHONE_COUNT 3	///<最大发生短信数量


#define  MAX_HVR_CHNCAP       16
//DDNS服务器设备的信息
typedef struct _DDNS_INFO
{
	char ID[64];    //设备标识
	char IP[DDNS_MAX_DDNS_IPSIZE];   //内网IP
	int WebPort; //Web端口,默认为80
	int MediaPort; //媒体端口,默认为34567
	int MobilePort;  //手机监控端口，默认为34599
	int UPNPWebPort;  //UPNP启动下Web端口,UPNP不开启为0
	int UPNPMediaPort; //UPNP启动下媒体端口,UPNP不开启为0
	int UPNPMobilePort; //UPNP启动下手机监控端口,UPNP不开启为0
	char Username[DDNS_MAX_DDNS_NAMELEN]; //用户名
	char Password[DDNS_MAX_DDNS_PWDLEN]; //密码
}DDNS_INFO,*pDDNS_INFO;

//DDNS信息查询模式
typedef struct _SearchMode
{
	int  nType;        //查询类型，见SearchModeType
	char szSerIP[DDNS_MAX_DDNS_IPSIZE];//服务器地址
	int nSerPort;           //服务器端口号
	char szSerialInfo[DDNS_MAX_SERIALINFO_SIZE];  //如果是按序列号，则为序列号，如果是用户名，则为用户名
}SearchMode;

//DDNS信息查询类型
enum SearchModeType
{
	DDNS_SERIAL = 0,//按序列号
	DDNS_USERNAME,  //按用户名
};
//实时预览扩展接口增加的参数：预览类型
typedef enum _H264_DVR_RealPlayType
{
	NET_RType_Realplay = 0,	//实时预览
	NET_RType_Main_Realplay2,	//实时监视-主码流，等同于NET_RType_Realplay
	NET_RType_Main_Realplay3,
	NET_RType_Sub_Realplay_1,	//实时监视-从码流1
	NET_RType_Sub_Realplay_2,	//实时监视-从码流2
	NET_RType_Sub_Realplay_3,	//实时监视-从码流3

	NET_RType_Multiplay_1,	//多画面预览－1画面
	NET_RType_Multiplay_4,	//多画面预览－4画面
	NET_RType_Multiplay_6,	//多画面预览－6画面
	NET_RType_Multiplay_8,	//多画面预览－8画面
	NET_RType_Multiplay_9,	//多画面预览－9画面
	NET_RType_Multiplay_12,	//多画面预览－12画面
	NET_RType_Multiplay_16,	//多画面预览－16画面
} NET_RealPlayType;

/// 组合编码模式
enum NetCombinType
{
	NET_COMBIN_NONE,
	NET_COMBIN_1,
	NET_COMBIN_2,
	NET_COMBIN_3,
	NET_COMBIN_4,
	NET_COMBIN_5,
	NET_COMBIN_6,
	NET_COMBIN_7,
	NET_COMBIN_8,
	NET_COMBIN_9,
	NET_COMBIN_10,
	NET_COMBIN_11,
	NET_COMBIN_12,
	NET_COMBIN_13,
	NET_COMBIN_14,
	NET_COMBIN_15,
	NET_COMBIN_16,
	NET_COMBIN_1_4,
	NET_COMBIN_5_8,
	NET_COMBIN_9_12,
	NET_COMBIN_13_16,
	NET_COMBIN_1_8,
	NET_COMBIN_9_16,
	NET_COMBIN_1_9,
	NET_COMBIN_8_16,
	NET_COMBIN_1_16
};

//这些结构体和枚举是提供给外部使用，所有可能会和设备那边定义了2次,所以都在前面加了SDK_
enum SDK_CAPTURE_SIZE_t {
	SDK_CAPTURE_SIZE_D1,		///< 720*576(PAL)	720*480(NTSC)
	SDK_CAPTURE_SIZE_HD1,		///< 352*576(PAL)	352*480(NTSC)
	SDK_CAPTURE_SIZE_BCIF,		///< 720*288(PAL)	720*240(NTSC)
	SDK_CAPTURE_SIZE_CIF,		///< 352*288(PAL)	352*240(NTSC)
	SDK_CAPTURE_SIZE_QCIF,		///< 176*144(PAL)	176*120(NTSC)
	SDK_CAPTURE_SIZE_VGA,		///< 640*480(PAL)	640*480(NTSC)
	SDK_CAPTURE_SIZE_QVGA,		///< 320*240(PAL)	320*240(NTSC)
	SDK_CAPTURE_SIZE_SVCD,		///< 480*480(PAL)	480*480(NTSC)
	SDK_CAPTURE_SIZE_QQVGA,		///< 160*128(PAL)	160*128(NTSC)
	SDK_CAPTURE_SIZE_ND1 = 9,     ///< 240*192
	SDK_CAPTURE_SIZE_650TVL,      ///< 926*576
	SDK_CAPTURE_SIZE_720P,        ///< 1280*720
	SDK_CAPTURE_SIZE_1_3M,        ///< 1280*960
	SDK_CAPTURE_SIZE_UXGA ,       ///< 1600*1200
	SDK_CAPTURE_SIZE_1080P,       ///< 1920*1080
	SDK_CAPTURE_SIZE_WUXGA,       ///< 1920*1200
	SDK_CAPTURE_SIZE_2_5M,        ///< 1872*1408
	SDK_CAPTURE_SIZE_3M,          ///< 2048*1536
	SDK_CAPTURE_SIZE_5M,          ///< 3744*1408
	SDK_CAPTURE_SIZE_NR,
};

/// 捕获码流控制模式类型
enum SDK_capture_brc_t {
	SDK_CAPTURE_BRC_CBR,			///< 固定码流。
	SDK_CAPTURE_BRC_VBR,			///< 可变码流。
	SDK_CAPTURE_BRC_MBR,			///< 混合码流。
	SDK_CAPTURE_BRC_NR				///< 枚举的码流控制模式数目。
};

/// 捕获压缩格式类型
enum SDK_CAPTURE_COMP_t {
	SDK_CAPTURE_COMP_DIVX_MPEG4,	///< DIVX MPEG4。
	SDK_CAPTURE_COMP_MS_MPEG4,		///< MS MPEG4。
	SDK_CAPTURE_COMP_MPEG2,			///< MPEG2。
	SDK_CAPTURE_COMP_MPEG1,			///< MPEG1。
	SDK_CAPTURE_COMP_H263,			///< H.263
	SDK_CAPTURE_COMP_MJPG,			///< MJPG
	SDK_CAPTURE_COMP_FCC_MPEG4,		///< FCC MPEG4
	SDK_CAPTURE_COMP_H264,			///< H.264
	SDK_CAPTURE_COMP_NR				///< 枚举的压缩标准数目。
};

/// 捕获通道类型
enum SDK_CAPTURE_CHANNEL_t {
	SDK_CHL_MAIN_T = 0,		///< 主通道	－	主码流1 
	SDK_CHL_2END_T = 1,		///< 辅通道	－	出辅码流2 
	SDK_CHL_3IRD_T = 2,		///< 辅通道	－	出辅码流3 
	SDK_CHL_4RTH_T = 3,		///< 辅通道	－	出辅码流4 
	SDK_CHL_JPEG_T = 4,		///< 辅通道	－	出JPEG抓图 
	SDK_CHL_FUNCTION_NUM
};
/// 音频编码类型
enum SDK_AudioEncodeTypes
{
	SDK_AUDIO_ENCODE_NONE = 0,
	SDK_AUDIO_ENCODE_G729_8KBIT,
	SDK_AUDIO_ENCODE_G726_16KBIT,
	SDK_AUDIO_ENCODE_G726_24KBIT,
	SDK_AUDIO_ENCODE_G726_32KBIT,
	SDK_AUDIO_ENCODE_G726_40KBIT,
	SDK_AUDIO_ENCODE_PCM_8TO16BIT,
	SDK_AUDIO_ENCODE_PCM_ALAW,
	SDK_AUDIO_ENCODE_PCM_ULAW,
	SDK_AUDIO_ENCODE_ADPCM8K16BIT,
	SDK_AUDIO_ENCODE_ADPCM16K16BIT,
	SDK_AUDIO_ENCODE_G711_ALAW,
	SDK_AUDIO_ENCODE_MPEG2_LAYER1,
	SDK_AUDIO_ENCODE_AMR8K16BIT,
	SDK_AUDIO_ENCODE_G711_ULAW,
	SDK_AUDIO_ENCODE_IMA_ADPCM_8K16BIT,
	SDK_AUDIO_ENCODE_TYPES_NR,
};



//配置类型
typedef enum _SDK_CONFIG_TYPE
{
	E_SDK_CONFIG_NOTHING = 0,		//
	E_SDK_CONFIG_USER,			//用户信息，包含了权限列表，用户列表和组列表
	E_SDK_CONFIG_ADD_USER,		//增加用户
	E_SDK_CONFIG_MODIFY_USER,		//修改用户
	E_SDK_CONFIG_DELETE_USER,
	E_SDK_CONFIG_ADD_GROUP,		//增加组
	E_SDK_CONFIG_MODIFY_GROUP,	//修改组
	E_SDK_COFIG_DELETE_GROUP,
	E_SDK_CONFIG_MODIFY_PSW,		//修改密码


	E_SDK_CONFIG_ABILITY_SYSFUNC = 9,//支持的网络功能
	E_SDK_CONFIG_ABILTY_ENCODE,	//首先获得编码能力
	E_SDK_CONFIG_ABILITY_PTZPRO,	//云台协议
	E_SDK_COMFIG_ABILITY_COMMPRO,	//串口协议
	
	E_SDK_CONFIG_ABILITY_MOTION_FUNC,	//动态检测块
	E_SDK_CONFIG_ABILITY_BLIND_FUNC,	//视频遮挡块
	E_SDK_CONFIG_ABILITY_DDNS_SERVER,	//DDNS服务支持类型
	E_SDK_CONFIG_ABILITY_TALK,		//对讲编码类型



	E_SDK_CONFIG_SYSINFO = 17,		//系统信息
	E_SDK_CONFIG_SYSNORMAL,	//普通配置
	E_SDK_CONFIG_SYSENCODE,	//编码配置
	E_SDK_CONFIG_SYSNET,		//网络设置
	E_SDK_CONFIG_PTZ,			//云台页面
	E_SDK_CONFIG_COMM,		//串口页面
	E_SDK_CONFIG_RECORD,		//录像设置界面
	E_SDK_CONFIG_MOTION,		//动态检测页面
	E_SDK_CONFIG_SHELTER,		//视频遮挡
	E_SDK_CONFIG_VIDEO_LOSS,  //视频丢失,
	E_SDK_CONFIG_ALARM_IN,	//报警输入
	E_SDK_CONFIG_ALARM_OUT,	//报警输出
	E_SDK_CONFIG_DISK_MANAGER,//硬盘管理界面
	E_SDK_CONFIG_OUT_MODE,	//输出模式界面
	E_SDK_CONFIG_CHANNEL_NAME,//通道名称
	E_SDK_CONFIG_AUTO,		//自动维护界面配置
	E_SDK_CONFIG_DEFAULT,     //恢复默认界面配置
	E_SDK_CONFIG_DISK_INFO,	//硬盘信息
	E_SDK_CONFIG_LOG_INFO,	//查询日志
	E_SDK_CONFIG_NET_IPFILTER,
	E_SDK_CONFIG_NET_DHCP,
	E_SDK_CONFIG_NET_DDNS,
	E_SDK_CONFIG_NET_EMAIL,
	E_SDK_CONFIG_NET_MULTICAST,
	E_SDK_CONFIG_NET_NTP,
	E_SDK_CONFIG_NET_PPPOE,
	E_SDK_CONFIG_NET_DNS,
	E_SDK_CONFIG_NET_FTPSERVER,
	
	E_SDK_CONFIG_SYS_TIME,	//系统时间	
	E_SDK_CONFIG_CLEAR_LOG,	//清除日志
	E_SDK_REBOOT_DEV,		//重启启动设备
	E_SDK_CONFIG_ABILITY_LANG,	//支持语言
	E_SDK_CONFIG_VIDEO_FORMAT,
	E_SDK_CONFIG_COMBINEENCODE,	//组合编码
	E_SDK_CONFIG_EXPORT,	//配置导出
	E_SDK_CONFIG_IMPORT,	//配置导入
	E_SDK_LOG_EXPORT,		//日志导出
	E_SDK_CONFIG_COMBINEENCODEMODE, //组合编码模式
	E_SDK_WORK_STATE,	//运行状态
	E_SDK_ABILITY_LANGLIST, //实际支持的语言集
	E_SDK_CONFIG_NET_ARSP,
	E_SDK_CONFIG_SNAP_STORAGE,
	E_SDK_CONFIG_NET_3G, //3G拨号
	E_SDK_CONFIG_NET_MOBILE, //手机监控
	E_SDK_CONFIG_UPGRADEINFO, //获取升级信息
	E_SDK_CONFIG_NET_DECODER,
	E_SDK_ABILITY_VSTD, //实际支持的视频制式
	E_SDK_CONFIG_ABILITY_VSTD,	//支持视频制式
	E_SDK_CONFIG_NET_UPNP, //UPUN设置
	E_SDK_CONFIG_NET_WIFI,
	E_SDK_CONFIG_NET_WIFI_AP_LIST,
	E_SDK_CONFIG_SYSENCODE_SIMPLIIFY, //简化的编码配置
	E_SDK_CONFIG_ALARM_CENTER,  //告警中心
	E_SDK_CONFIG_NET_ALARM,
	E_SDK_CONFIG_NET_MEGA,     //互信互通
	E_SDK_CONFIG_NET_XINGWANG, //星望
	E_SDK_CONFIG_NET_SHISOU,   //视搜
	E_SDK_CONFIG_NET_VVEYE,    //VVEYE
	E_SDK_CONFIG_NET_PHONEMSG,  //短信
	E_SDK_CONFIG_NET_PHONEMEDIAMSG,  //彩信
	E_SDK_VIDEO_PREVIEW,
	E_SDK_CONFIG_NET_DECODER_V2,
	E_SDK_CONFIG_NET_DECODER_V3,//数字通道
	E_SDK_CONFIG_ABILITY_SERIALNO,	// 序列号
    E_SDK_CONFIG_NET_RTSP,    //RTSP
	E_SDK_GUISET,              //GUISET
	E_SDK_CATCHPIC,               //抓图
	E_SDK_VIDEOCOLOR,             //视频颜色设置
	E_SDK_CONFIG_COMM485,
	E_SDK_COMFIG_ABILITY_COMMPRO485, //串口485
	E_SDK_CONFIG_SYS_TIME_NORTC,	//系统时间noRtc
	E_SDK_CONFIG_REMOTECHANNEL,   //远程通道
	E_SDK_CONFIG_OPENTRANSCOMCHANNEL , //打开透明串口
	E_SDK_CONFIG_CLOSETRANSCOMCHANNEL,  //关闭透明串口
	E_SDK_CONFIG_SERIALWIRTE,  //写入透明串口信息
	E_SDK_CONFIG_SERIALREAD,   //读取透明串口信息
	E_SDK_CONFIG_CHANNELTILE_DOT,	//点阵信息
	E_SDK_CONFIG_CAMERA,           //摄象机参数
	E_SDK_CONFIG_ABILITY_CAMERA,    //曝光能力级
	E_SDK_CONFIG_BUGINFO,    //命令调试
	E_SDK_CONFIG_STORAGENOTEXIST,//硬盘不存在
	E_SDK_CONFIG_STORAGELOWSPACE, //硬盘容量不足
	E_SDK_CONFIG_STORAGEFAILURE, //硬盘出错
	E_SDK_CFG_NETIPCONFLICT,    //IP冲突
	E_SDK_CFG_NETABORT,  //网络异常

	E_SDK_CONFIG_CHNSTATUS, //通道状态
	E_SDK_CONFIG_CHNMODE,  //通道模式

	E_SDK_CONFIG_NET_DAS,    //主动注册
}SDK_CONFIG_TYPE;



/// 报警事件码
enum SDK_EventCodeTypes
{
	SDK_EVENT_CODE_INIT = 0,
	SDK_EVENT_CODE_LOCAL_ALARM = 1,	//本地报警
	SDK_EVENT_CODE_NET_ALARM,		//网络报警
	SDK_EVENT_CODE_MANUAL_ALARM,	//手动报警
	SDK_EVENT_CODE_VIDEO_MOTION,	//动态检测
	SDK_EVENT_CODE_VIDEO_LOSS,		//视频丢失
	SDK_EVENT_CODE_VIDEO_BLIND,		//视频遮挡
	SDK_EVENT_CODE_VIDEO_TITLE,		
	SDK_EVENT_CODE_VIDEO_SPLIT,
	SDK_EVENT_CODE_VIDEO_TOUR,
	SDK_EVENT_CODE_STORAGE_NOT_EXIST,
	SDK_EVENT_CODE_STORAGE_FAILURE,
	SDK_EVENT_CODE_LOW_SPACE,
	SDK_EVENT_CODE_NET_ABORT,
	SDK_EVENT_CODE_COMM,
	SDK_EVENT_CODE_STORAGE_READ_ERROR,
	SDK_EVENT_CODE_STORAGE_WRITE_ERROR,
	SDK_EVENT_CODE_NET_IPCONFLICT,
	SDK_EVENT_CODE_ALARM_EMERGENCY,
	SDK_EVENT_CODE_DEC_CONNECT,
	SDK_EVENT_CODE_NR,
};
//! 编码配置的类型
enum SDK_ENCODE_TYPE_BY_RECORD
{
	SDK_ENCODE_TYPE_TIM = 0,
	SDK_ENCODE_TYPE_MTD = 1,
	SDK_ENCODE_TYPE_ALM = 2,
	SDK_ENCODE_TYPE_NUM = 3,
	SDK_ENCODE_TYPE_SNAP_TIMER = 0,
	SDK_ENCODE_TYPE_SNAP_TRIGGER = 1,
};
#define SDK_EXTRATYPES 3 //辅码流类型

//网络传输策略
enum SDK_TransferPolicy
{
	SDK_TRANSFER_POLICY_AUTO,		///< 自适应
	SDK_TRANSFER_POLICY_QUALITY,	///< 质量优先
	SDK_TRANSFER_POLICY_FLUENCY,	///< 流量优先
	SDK_TRANSFER_POLICY_NR,
};



typedef struct {
	int left;
	int top;
	int right;
	int bottom;
}sdkRect;

/// 音频输入格式，语音对讲用
struct SDK_AudioInFormatConfig
{
	int iBitRate;	   ///< 码流大小，kbps为单位，比如192kbps，128kbps
	int iSampleRate;   ///< 采样率，Hz为单位，比如44100Hz
	int iSampleBit;    ///< 采样的位深
	int iEncodeType;   ///< 编码方式，参照AudioEncodeTypes定义
};

//语音对讲格式
typedef enum __TALK_CODING_TYPE
{
	TALK_DEFAULT = 0,
	TALK_PCM = 1,					//PCM
	TALK_G711a,						//G711a
	TALK_AMR,						//AMR
	TALK_G711u,						//G711u
	TALK_G726,						//G726
}TALK_CODING_TYPE;
//语音对讲
typedef struct  
{
	TALK_CODING_TYPE		encodeType;		//编码类型
	int						nAudioBit;		//用实际的值表示，如8位 则填值为8
	unsigned int			dwSampleRate;	//采样率，如16k 则填值为16000
	char					reserved[64];
}H264_DVR_TALKDECODE_INFO;


/// 系统时间结构
typedef struct SDK_SYSTEM_TIME{
	int  year;///< 年。   
	int  month;///< 月，January = 1, February = 2, and so on.   
	int  day;///< 日。   
	int  wday;///< 星期，Sunday = 0, Monday = 1, and so on   
	int  hour;///< 时。   
	int  minute;///< 分。   
	int  second;///< 秒。   
	int  isdst;///< 夏令时标识。   
}SDK_SYSTEM_TIME;

//录像设置相关结构体
typedef struct tagSDK_TIMESECTION
{
	//!使能
	int enable;
	//!开始时间:小时
	int startHour;
	//!开始时间:分钟
	int	startMinute;
	//!开始时间:秒钟
	int	startSecond;
	//!结束时间:小时
	int	endHour;
	//!结束时间:分钟
	int	endMinute;
	//!结束时间:秒钟
	int	endSecond;
}SDK_TIMESECTION;	

typedef struct{
	int dwYear;		//年
	int dwMonth;	//月
	int dwDay;		//日
	int dwHour;		//时
	int dwMinute;	//分
	int dwSecond;	//秒
}H264_DVR_TIME,*LPH264_DVR_TIME;

//时间结构
typedef struct _NEW_NET_TIME								
{
	unsigned int second			:6;					//	秒	1-60		
	unsigned int minute			:6;					//	分	1-60		
	unsigned int hour			:5;					//	时	1-24		
	unsigned int day			:5;					//	日	1-31		
	unsigned int month			:4;					//	月	1-12		
	unsigned int year			:6;					//	年	2000-2063	
}NEW_NET_TIME, *LPNET_TIME;
///< 夏令时结构
struct DSTPoint
{
	int	iYear;
	int	iMonth;
	int	iWeek;		///<周1:first  to2 3 4 -1:last one   0:表示使用按日计算的方法[-1,4]
	int	iWeekDay;	///<weekday from sunday=0	[0, 6]
	int Hour;
	int Minute;
};

struct SDK_VIDEO_FORMAT
{
	int		iCompression;			//  压缩模式 	
	int		iResolution;			//  分辨率 参照枚举capture_size_t(DVRAPI.H) 	
	int		iBitRateControl;		//  码流控制 参照枚举capture_brc_t(DVRAPI.H) 	
	int		iQuality;				//  码流的画质 档次1-6		
	int		nFPS;					//  帧率值，NTSC/PAL不区分,负数表示多秒一帧		
	int		nBitRate;				//  0-4096k,该列表主要由客户端保存，设备只接收实际的码流值而不是下标。
	int		iGOP;					//  描述两个I帧之间的间隔时间，2-12 
} ;
struct  SDK_AUDIO_FORMAT
{
	int		nBitRate;				//  码流kbps	
	int		nFrequency;				//  采样频率	
	int		nMaxVolume;				//  最大音量阈值
} ;
// 媒体格式
struct SDK_MEDIA_FORMAT
{
	SDK_VIDEO_FORMAT vfFormat;			//  视频格式定义 			
	SDK_AUDIO_FORMAT afFormat;			//  音频格式定义 
	bool	bVideoEnable;				//  开启视频编码 
	bool	bAudioEnable;				//  开启音频编码 	
} ;

typedef union {	//IP addr
	unsigned char	c[4];
	unsigned short	s[2];
	unsigned int 	l;
}CONFIG_IPAddress;








///////////////////用户帐号管理相关结构体/////////////////////////////////
typedef struct _OPR_RIGHT
{
	char name[NET_MAX_USER_LENGTH];
}OPR_RIGHT;

typedef struct _USER_INFO
{
	int			rigthNum;
	char		rights[NET_MAX_RIGTH_NUM][NET_MAX_USER_LENGTH];
	char		Groupname[NET_MAX_USER_LENGTH];
	char		memo[NET_MAX_USER_LENGTH];
	char		name[NET_MAX_USER_LENGTH];
	char		passWord[NET_MAX_USER_LENGTH];
	bool		reserved;		//是否保留
	bool		shareable;		//本用户是否允许复用 1-复用，0-不复用
}USER_INFO;

typedef struct _USER_GROUP_INFO
{
	int			rigthNum;
	char		memo[NET_MAX_USER_LENGTH]; 
	char		name[NET_MAX_USER_LENGTH];
	char		rights[NET_MAX_RIGTH_NUM][NET_MAX_USER_LENGTH];	//权限列表
}USER_GROUP_INFO;

//用户信息配置结构
typedef struct _USER_MANAGE_INFO
{
	int					rigthNum;
	OPR_RIGHT			rightList[NET_MAX_RIGTH_NUM];
	int					groupNum;
	USER_GROUP_INFO		groupList[NET_MAX_GROUP_NUM];
	int					userNum;
	USER_INFO			userList[NET_MAX_USER_NUM];
}USER_MANAGE_INFO;

//修改用户
typedef struct _CONF_MODIFYUSER
{
	char UserName[NET_MAX_USER_LENGTH];
	USER_INFO User;
}CONF_MODIFYUSER;

//修改组
typedef struct _CONF_MODIFYGROUP
{
	char GroupName[NET_MAX_USER_LENGTH];
	USER_GROUP_INFO Group;
}CONF_MODIFYGROUP;


/// 修改用户密码请求
struct _CONF_MODIFY_PSW
{
	char sUserName[NET_MAX_USER_LENGTH];
	char Password[NET_MAX_USER_LENGTH];
	char NewPassword[NET_MAX_USER_LENGTH];
};

//普通配置页结构体
typedef struct _SDK_CONFIG_NORMAL
{	
	SDK_SYSTEM_TIME sysTime;		//系统时间

	int iLocalNo;			/*!< 本机编号:[0, 998] */
	int iOverWrite;			/*!< 硬盘满时处理 "OverWrite", "StopRecord" */		
	int iSnapInterval;			///< 定时抓图的时间间隔，以秒为单位 
	char sMachineName[64];	///< 机器名
	int iVideoStartOutPut;	/*!< 输出模式 */
	int iAutoLogout;			///< 本地菜单自动注销(分钟)	[0, 120]

	int iVideoFormat;		/*!< 视频制式:“PAL”, “NTSC”, “SECAM” */
	int iLanguage;			/*!< 语言选择:“English”, “SimpChinese”, “TradChinese”, “Italian”, “Spanish”, “Japanese”, “Russian”, “French”, “German” */	
	int iDateFormat;		/*!< 日期格式:“YYMMDD”, “MMDDYY”, “DDMMYY” */
	int iDateSeparator;		/*!< 日期分割符:“.”, “-”, “/” */
	int iTimeFormat;		/*!< 时间格式:“12”, “24” */
	int iDSTRule;			///< 夏令时规则 
	int iWorkDay;			///< 工作日
	DSTPoint dDSTStart;
	DSTPoint dDSTEnd;
}SDK_CONFIG_NORMAL;


//以下编码配置相关
// 编码设置
struct SDK_CONFIG_ENCODE
{
	SDK_MEDIA_FORMAT dstMainFmt[SDK_ENCODE_TYPE_NUM];		//  主码流格式 	
	SDK_MEDIA_FORMAT dstExtraFmt[SDK_EXTRATYPES];	//  辅码流格式 
	SDK_MEDIA_FORMAT dstSnapFmt[SDK_ENCODE_TYPE_NUM];		//  抓图格式 
};
struct  SDK_EncodeConfigAll
{
	SDK_CONFIG_ENCODE vEncodeConfigAll[NET_MAX_CHANNUM];
};


// 简化版本编码配置
/// 媒体格式
struct SDK_MEDIA_FORMAT_SIMPLIIFY
{
	SDK_VIDEO_FORMAT vfFormat;			//  视频格式定义 			
	bool	bVideoEnable;			//  开启视频编码 
	bool	bAudioEnable;			//  开启音频编码 	
};

/// 编码设置
struct SDK_CONFIG_ENCODE_SIMPLIIFY
{
	SDK_MEDIA_FORMAT dstMainFmt;		//  主码流格式 	
	SDK_MEDIA_FORMAT dstExtraFmt;	//  辅码流格式 
};

/// 全通道编码配置
struct SDK_EncodeConfigAll_SIMPLIIFY
{
	SDK_CONFIG_ENCODE_SIMPLIIFY vEncodeConfigAll[NET_MAX_CHANNUM];
};


struct  SDK_CombineEncodeConfigAll
{
	SDK_CONFIG_ENCODE vEncodeConfigAll[NET_MAX_COMBINE_NUM];
};

/// 组合编码模式
struct SDK_CombEncodeParam
{
	int iEncodeMode;	 //见CombineEncodeMode
};

struct SDK_CombEncodeModeAll
{
	SDK_CombEncodeParam vEncodeParam[NET_MAX_COMBINE_NUM];
};

//!视频物件结构
struct  SDK_VIDEO_WIDGET
{
	unsigned int rgbaFrontground;		///< 物件的前景MakeRGB，和透明度	
	unsigned int rgbaBackground;		///< 物件的后景MakeRGB，和透明度	
	sdkRect	rcRelativePos;			///< 物件边距与整长的比例*8191
	bool	bPreviewBlend;			///< 预览叠加	
	bool	bEncodeBlend;			///< 编码叠加
};

//!视频物件设置
struct SDK_CONFIG_VIDEOWIDGET
{
	SDK_VIDEO_WIDGET	dstCovers[NET_COVERNUM];
	SDK_VIDEO_WIDGET	ChannelTitle;
	SDK_VIDEO_WIDGET	TimeTitle;
	struct 
	{
		char strName[NET_NAME_PASSWORD_LEN];
#ifdef WIN32
 		__int64 iSerialNo;	
#else
		long long iSerialNo;	
#endif
	}ChannelName;					/// 通道名称
	int				iCoverNum;		/*!< 当前该通道有几个叠加的区域 */
};

/// 视频物件(输出模式对话框)
struct SDK_VideoWidgetConfigAll
{
	SDK_CONFIG_VIDEOWIDGET vVideoWidegetConfigAll[NET_MAX_CHANNUM];
};

//视频颜色
struct SDK_VIDEOCOLOR_PARAM
{
	int	nBrightness;		///< 亮度	0-100
	int	nContrast;			///< 对比度	0-100
	int	nSaturation;		///< 饱和度	0-100
	int	nHue;				///< 色度	0-100
	int	mGain;				///< 增益	0-100 第７位置1表示自动增益		
	int	mWhitebalance;		///< 自动白电平控制，bit7置位表示开启自动控制.0x0,0x1,0x2分别代表低,中,高等级
	int nAcutance;          ///< 锐度   0-15
};
///< 视频颜色设置
struct SDK_VIDEOCOLOR
{
	SDK_TIMESECTION			tsTimeSection;		/// 时间段
	SDK_VIDEOCOLOR_PARAM	dstColor;			/// 颜色定义
	int					iEnable;
};

struct SDK_CONFIG_VIDEOCOLOR
{
	SDK_VIDEOCOLOR dstVideoColor[NET_N_MIN_TSECT];
};

struct SDK_VideoColorConfigAll
{
	SDK_CONFIG_VIDEOCOLOR vVideoColorAll[NET_MAX_CHANNUM];
};


/// 所有通道名称标题
struct SDK_ChannelNameConfigAll
{
	char channelTitle[NET_MAX_CHANNUM][NET_NAME_PASSWORD_LEN];
};

//输出模式
struct SDK_GUISetConfig
{
	int iWindowAlpha;			///< 窗口透明度	[128, 255]
	bool bTimeTitleEn;			///< 时间标题显示使能
	bool bChannelTitleEn;		///< 通道标题显示使能	
	bool bAlarmStatus;			///<  报警状态
	bool bRecordStatus;			///<  录像状态显示使能
	bool bChanStateRecEn;		///< 录像标志显示使能
	bool bChanStateVlsEn;		///< 视频丢失标志显示使能
	bool bChanStateLckEn;		///< 通道锁定标志显示使能	
	bool bChanStateMtdEn;		///< 动态检测标志显示使能
	bool bBitRateEn;			///< 码流显示使能
	bool bRemoteEnable;			///< 遥控器使能
	bool bDeflick;				///< 抗抖动
};


////!普通网络设置
struct SDK_CONFIG_NET_COMMON
{
	//!主机名
	char HostName[NET_NAME_PASSWORD_LEN];
	//!主机IP
	CONFIG_IPAddress HostIP;
	//!子网掩码
	CONFIG_IPAddress Submask;
	//!网关IP
	CONFIG_IPAddress Gateway;
	//!HTTP服务端口
	int HttpPort;
	//!TCP侦听端口
	int TCPPort;	
	//!SSL侦听端口
	int SSLPort;
	//!UDP侦听端口
	int UDPPort;
	//!最大连接数
	int MaxConn;
	//!监视协议 {"TCP","UDP","MCAST",…}
	int MonMode;
	//!限定码流值
	int MaxBps;
	//!传输策略
	//char TransferPlan[NET_NAME_PASSWORD_LEN];
	int TransferPlan;

	//!是否启用高速录像下载测率
	bool bUseHSDownLoad;

	//!MAC地址
	char sMac[NET_MAX_MAC_LEN];
};

//DHCP
struct SDK_NetDHCPConfig
{
	bool bEnable;
	char ifName[32];
};
/// 所有网卡的DHCP配置
struct SDK_NetDHCPConfigAll
{
	SDK_NetDHCPConfig vNetDHCPConfig[2];
};

///< DNS设置
struct SDK_NetDNSConfig
{
	CONFIG_IPAddress		PrimaryDNS;
	CONFIG_IPAddress		SecondaryDNS;
};
///< 服务器结构定义
struct SDK_RemoteServerConfig
{
	char ServerName[NET_NAME_PASSWORD_LEN];	///< 服务名
	CONFIG_IPAddress ip;						///< IP地址
	int Port;							///< 端口号
	char UserName[NET_NAME_PASSWORD_LEN];		///< 用户名
	char Password[NET_NAME_PASSWORD_LEN];		///< 密码	
	bool Anonymity;							///< 是否匿名登录
};
///< IP权限设置
struct SDK_NetIPFilterConfig
{
	bool Enable;		///< 是否开启
	CONFIG_IPAddress BannedList[NET_MAX_FILTERIP_NUM];		///< 黑名单列表
	CONFIG_IPAddress TrustList[NET_MAX_FILTERIP_NUM];		///< 白名单列表
};

///< 组播设置
struct SDK_NetMultiCastConfig
{
	bool Enable;		///< 是否开启
	SDK_RemoteServerConfig Server;		///< 组播服务器
};

///< pppoe设置
struct SDK_NetPPPoEConfig
{
	bool Enable;	///< 是否开启
	SDK_RemoteServerConfig Server;		///< PPPOE服务器
	CONFIG_IPAddress addr;		///< 拨号后获得的IP地址
};

///< DDNS设置
struct SDK_NetDDNSConfig
{
	bool Enable;	///< 是否开启
	bool Online;		///< 是否在线
	char DDNSKey[NET_NAME_PASSWORD_LEN];	///< DDNS类型名称, 目前有: JUFENG
	char HostName[NET_NAME_PASSWORD_LEN];	///< 主机名
	SDK_RemoteServerConfig Server;			///< DDNS服务器
	
};

///< DDNS设置
struct SDK_NetDDNSConfigALL
{
	SDK_NetDDNSConfig ddnsConfig[NET_MAX_DDNS_TYPE];
};

///< FTP设置
struct SDK_FtpServerConfig{
	bool bEnable;        ///< 服务器使能     
	SDK_RemoteServerConfig Server;	///< FTP服务器
	char cRemoteDir[NET_MAX_PATH_LENGTH];	///< 远程目录
	int iMaxFileLen;	///< 文件最大长度
};

///< NTP设置
struct SDK_NetNTPConfig
{
	///< 是否开启
	bool Enable;
	///< PPPOE服务器
	SDK_RemoteServerConfig Server;
	///< 更新周期
	int UpdatePeriod;
	///< 时区
	int TimeZone;
};
#define  NET_MAX_EMAIL_TITLE_LEN 64
#define  NET_MAX_EMAIL_RECIEVERS  5
#define  NET_EMAIL_ADDR_LEN  32

///< EMAIL设置
struct SDK_NetEmailConfig
{
	///< 是否开启
	bool Enable;
	///< smtp 服务器地址使用字符串形式填充
	///< 可以填ip,也可以填域名
	SDK_RemoteServerConfig Server;
	bool bUseSSL;
	///< 发送地址
	char SendAddr[NET_EMAIL_ADDR_LEN];
	///< 接收人地址
	char Recievers[NET_MAX_EMAIL_RECIEVERS][NET_EMAIL_ADDR_LEN];
	///< 邮件主题
	char Title[NET_MAX_EMAIL_TITLE_LEN];
	///< email有效时间
	SDK_TIMESECTION Schedule[NET_N_MIN_TSECT];
};

///< ARSP(主动注册服务器)设置
struct SDK_NetARSPConfig
{
	bool bEnable;	///< 是否开启
	char sARSPKey[NET_NAME_PASSWORD_LEN];	///< DNS类型名称
	int iInterval;	///< 保活间隔时间
	char sURL[NET_NAME_PASSWORD_LEN];    ///< 本机域名
	SDK_RemoteServerConfig Server;		///< DDNS服务器
	int nHttpPort;                  ///< 服务器HTTP端口
};

struct SDK_NetARSPConfigAll
{
	SDK_NetARSPConfig vNetARSPConfigAll[NET_MAX_ARSP_TYPE];
};

///< 解码器地址设置
struct SDK_NetDecoderConfig
{
	bool Enable;						///< 是否开启
	char UserName[NET_NAME_PASSWORD_LEN];	///< DDNS类型名称, 目前有: JUFENG
	char PassWord[NET_NAME_PASSWORD_LEN];	///< 主机名
	char Address[NET_NAME_PASSWORD_LEN];
	int Protocol;
	int Port;							///< 解码器连接端口
	int Channel;						///< 解码器连接通道号
	int Interval;                       ///< 轮巡的间隔时间(s)
};

/// 所有通道的解码器地址设置
struct SDK_NetDecoderConfigAll
{
	SDK_NetDecoderConfig vNetDecoderConfig[NET_MAX_DECORDR_CH];
};


/// 解码器地址设置V2版本
struct SDK_NetDecoderConfig_V2
{
	int nTotalNum;            //有效的数组个数，最大为NET_MAX_CHANNUM
	SDK_NetDecoderConfig vNetDecoderConfig[NET_MAX_CHANNUM];
};

/// 所有通道的解码器地址设置V2版本
struct SDK_NetDecoderConfigAll_V2
{
	SDK_NetDecoderConfig_V2 vNetDecoderArray[NET_MAX_DECORDR_CH];
};

///< 解码器地址设置
struct SDK_NetDecorderConfigV3
{
	bool Enable;						///< 是否开启
	char UserName[NET_NAME_PASSWORD_LEN];	///< DDNS类型名称, 目前有: JUFENG
	char PassWord[NET_NAME_PASSWORD_LEN];	///< 主机名
	char Address[NET_NAME_PASSWORD_LEN];
	int Protocol;
	int Port;							///< 解码器连接端口
	int Channel;						///< 解码器连接通道号
	int Interval;                       ///< 轮巡的间隔时间(s),0:表示永久
	char ConfName[NET_NAME_PASSWORD_LEN];	///<配置名称
	int DevType;						///<设备类型
	int StreamType;						///<连接的码流类型CaptureChannelTypes
};

/*解码器连接类型*/
enum SDK_DecorderConnType
{
	SDK_CONN_SINGLE = 0, 	/*单连接*/
	SDK_CONN_MULTI = 1,		/*多连接轮巡*/
	SDK_CONN_TYPE_NR,
};

/*数字通道的配置*/
struct SDK_NetDigitChnConfig
{
	bool Enable;		/*数字通道是否开启*/		
	int ConnType;		/*连接类型，取DecoderConnectType的值*/
	int TourIntv;		/*多连接时轮巡间隔*/
	unsigned int SingleConnId;	/*单连接时的连接配置ID, 从1开始，0表示无效*/
	bool EnCheckTime;	/*开启对时*/
	SDK_NetDecorderConfigV3 NetDecorderConf[32]; /*网络设备通道配置表*/
};

/*所有数字通道的配置*/
struct SDK_NetDecorderConfigAll_V3
{
	SDK_NetDigitChnConfig DigitChnConf[NET_MAX_DECORDR_CH];
};

//通道模式
#define MAX_HVR_CHNCAP_CHN		16
typedef struct SDK_HVR_CHNCAP 
{
	int nD1Chn;		// 支持的D1路数
	int n960HChn;		// 支持的960H路数
	int n720PChn;		// 支持的720P路数
	int n1080PChn;		// 支持的1080P路数
	int nRes[4];
}SDK_HVR_CHNCAP, *SDK_PHVR_CHNCAP;

typedef struct SDK_CAPTURE_HVRCAP 
{
	SDK_HVR_CHNCAP DigitalCap;		// 支持的数字通道信息
	SDK_HVR_CHNCAP AnalogCap;		// 支持的模拟通道信息
}SDK_CAPTURE_HVRCAP, *SDK_PCAPTURE_HVRCAP;

typedef struct SDK_CAPTURE_TOTAL_HVRCAP 
{
	int		nHVRCap;			// 实际支持的模式
	SDK_CAPTURE_HVRCAP	HVRCap[MAX_HVR_CHNCAP_CHN];		// 所有模式的汇总
}SDK_CAPTURE_TOTAL_HVRCAP, *SDK_PCAPTURE_TOTAL_HVRCAP;

//通道模式配置
struct SDK_NetDecorderChnModeConfig
{
	SDK_CAPTURE_TOTAL_HVRCAP 	HVRTotalCap;
	int HVRCurCapMode;
};


/*数字通道状态*/
struct SDK_NetDecorderChnStatus
{
	char ChnName[NET_NAME_PASSWORD_LEN];
	char pMaxResName[50];
	char	pCurResName[50];
	char pStatus[50];
};

/*所有数字通道状态*/
struct SDK_NetDecorderChnStatusAll
{
	SDK_NetDecorderChnStatus ChnStatusAll[NET_MAX_DECORDR_CH];
};

///< 3G拨号设置
struct SDK_Net3GConfig
{
	bool bEnable;			  ///< 无线模块使能标志
	int iNetType;			  ///< 无线网络类型
	char sAPN[NET_NAME_PASSWORD_LEN];		///< 接入点名称
	char sDialNum[NET_NAME_PASSWORD_LEN];   ///< 拨号号码
	char sUserName[NET_NAME_PASSWORD_LEN];  ///< 拨号用户名
	char sPassword[NET_NAME_PASSWORD_LEN];  ///< 拨号密码
	CONFIG_IPAddress addr;			  ///< 拨号后获得的IP地址
};

///< 手机监控设置包括
struct SDK_NetMoblieConfig
{
	bool bEnable;	///< 是否开启
	SDK_RemoteServerConfig Server;		///< 服务器
};

//RTSP
struct SDK_NetRTSPConfig
{
	bool bServer;
	bool bClient;
	SDK_RemoteServerConfig Server;		///< 服务器模式
	SDK_RemoteServerConfig Client;		///< 客户端模式
};

///< UPNP设置
struct SDK_NetUPNPConfig
{
	bool bEnable;			  ///< 使能标志
	bool bState;              ///< 状态, 1: OK 0: NOK
	int iHTTPPort;			  ///< HTTP连接映射后的端口
	int iMediaPort;			  ///< 媒体连接映射后的端口
	int iMobliePort;		  ///< 手机监控映射后的端口
};

///< WIFI设置
struct SDK_NetWifiConfig
{
	bool bEnable;
	char sSSID[36];            //SSID Number
	int nChannel;                   //channel
	char sNetType[32];         //Infra, Adhoc
	char sEncrypType[32];      //NONE, WEP, TKIP, AES
	char sAuth[32];            //OPEN, SHARED, WEPAUTO, WPAPSK, WPA2PSK, WPANONE, WPA, WPA2
	int  nKeyType;                  //0:Hex 1:ASCII
	char sKeys[NET_IW_ENCODING_TOKEN_MAX];
	CONFIG_IPAddress HostIP;		///< host ip
	CONFIG_IPAddress Submask;		///< netmask
	CONFIG_IPAddress Gateway;		///< gateway
};

enum SDK_RSSI_SINGNAL
{
	SDK_RSSI_NO_SIGNAL,   //<= -90db
	SDK_RSSI_VERY_LOW,     //<= -81db
	SDK_RSSI_LOW,          //<= -71db
	SDK_RSSI_GOOD,         //<= -67db
	SDK_RSSI_VERY_GOOD,    //<= -57db
	SDK_RSSI_EXCELLENT     //>-57db
};

struct SDK_NetWifiDevice
{
	char sSSID[36];            //SSID Number
	int nRSSI;                 //SEE SDK_RSSI_SINGNAL
	int nChannel;
	char sNetType[32];         //Infra, Adhoc
	char sEncrypType[32];      //NONE, WEP, TKIP, AES
	char sAuth[32];            //OPEN, SHARED, WEPAUTO, WPAPSK, WPA2PSK, WPANONE, WPA, WPA2
};

struct SDK_NetWifiDeviceAll
{
	int nDevNumber;
	SDK_NetWifiDevice vNetWifiDeviceAll[NET_MAX_AP_NUMBER];
};

///< 报警中心设置
struct SDK_NetAlarmCenterConfig
{
	bool bEnable;		///< 是否开启
	char sAlarmServerKey[NET_NAME_PASSWORD_LEN];	///< 报警中心协议类型名称, 
	///< 报警中心服务器
	SDK_RemoteServerConfig Server;	
	bool bAlarm;
	bool bLog;
};

struct SDK_NetAlarmServerConfigAll
{
	SDK_NetAlarmCenterConfig vAlarmServerConfigAll[NET_MAX_ALARMSERVER_TYPE];
};


//互信互通
struct SDK_CONFIG_NET_MEGA
{
	bool bEnable;
	bool bNetManEnable;
	CONFIG_IPAddress ServerIP;
	int iServerPort;
	char sDeviceId[32];
	char sUserName[24];
	char sPasswd[32];
	int iMaxCon;
	int iVideoPort;
	int iAudioPort;
	int iMsgPort;
	int iUpdatePort;
};

// 新望平台
struct SDK_CONFIG_NET_XINGWANG
{
	bool bEnable;
	bool bSyncTime;
	bool bSubStream;
	CONFIG_IPAddress ServerIP;
	int iServerPort;
	int iDownLoadPort;
	char sPasswd[32];
	char szSID[32];
};

// 视搜平台
struct SDK_CONFIG_NET_SHISOU
{
	bool bEnable;
	SDK_RemoteServerConfig Server;
	char szSID[NET_MAX_USERNAME_LENGTH];
};

// VVEYE平台
struct SDK_CONFIG_NET_VVEYE
{
	bool bEnable;                
	bool bCorpEnable;            //只有在使用企业服务器时才需要设置Server
	SDK_RemoteServerConfig Server;
	char szDeviceName[NET_MAX_USERNAME_LENGTH];
};

// 报警中心消息类型
enum SDK_AlarmCenterMsgType
{
	SDK_ALARMCENTER_ALARM,
	SDK_ALARMCENTER_LOG,
};

// 报警中心消息类型
enum SDK_AlarmCenterStatus
{
	SDK_AC_START,
	SDK_AC_STOP,
};

// 告警中心消息内容
struct SDK_NetAlarmCenterMsg
{
	CONFIG_IPAddress HostIP;		///< 设备IP
	int nChannel;                   ///< 通道
	int nType;                      ///< 类型 见AlarmCenterMsgType
	int nStatus;                    ///< 状态 见AlarmCenterStatus
	SDK_SYSTEM_TIME Time;           ///< 发生时间
	char sEvent[NET_MAX_INFO_LEN];  ///< 事件
	char sSerialID[NET_MAX_MAC_LEN]; ///< 设备序列号
	char sDescrip[NET_MAX_INFO_LEN];  ///< 描述
};

/// 编码信息
struct SDK_EncodeInfo
{
	bool bEnable;			///< 使能项
	int iStreamType;		///< 码流类型，capture_channel_t
	bool bHaveAudio;		///< 是否支持音频
	unsigned int uiCompression;		///< capture_comp_t的掩码
	unsigned int uiResolution;		///< capture_size_t的掩码
};

/// 编码能力
struct CONFIG_EncodeAbility
{
	unsigned int iMaxEncodePower;		///< 支持的最大编码能力
	int iChannelMaxSetSync;		///< 每个通道分辨率是否需要同步 0-不同步, 1 -同步
	unsigned int nMaxPowerPerChannel[NET_MAX_CHANNUM];		///< 每个通道支持的最高编码能力
	unsigned int ImageSizePerChannel[NET_MAX_CHANNUM];		///< 每个通道支持的图像分辨率
	unsigned int ExImageSizePerChannel[NET_MAX_CHANNUM];		///< 每个通道支持的辅码流图像分辨率
	SDK_EncodeInfo vEncodeInfo[SDK_CHL_FUNCTION_NUM];	///< 编码信息,暂时最大就4中码流
	SDK_EncodeInfo vCombEncInfo[SDK_CHL_FUNCTION_NUM];	///< 组合编码信息,暂时最大就4中码流
	int	iMaxBps;				///< 最高码流Kbps
	unsigned int ExImageSizePerChannelEx[NET_MAX_CHANNUM][SDK_CAPTURE_SIZE_NR];	///< 每个通道支持的辅码流图像分辨率
};

// 串口协议
enum SDK_CommProtocol
{
	SDK_CONSOLE = 0,
	SDK_KEYBOARD,
	SDK_COM_TYPES,
};
/// 串口协议
struct SDK_COMMFUNC
{
	//每个协议最多由64个字符组成
	int nProNum;
	char vCommProtocol[100][32];
};

/// 云台协议
struct SDK_PTZPROTOCOLFUNC
{
	//每个协议最多由64个字符组成
	int nProNum;
	char vPTZProtocol[100][NET_MAX_PTZ_PROTOCOL_LENGTH];
};

/// 区域遮挡能力集
struct SDK_BlindDetectFunction
{
	int iBlindConverNum;	///< 区域遮挡块数
};

/// 动检区域能力集
struct SDK_MotionDetectFunction
{
	int iGridRow;
	int iGridColumn;
};

/// 支持的DDNS类型
struct SDK_DDNSServiceFunction
{
	int  nTypeNum;
	char vDDNSType[NET_MAX_DDNS_TYPE][64];
};

/// 支持语言
struct SDK_MultiLangFunction
{
	//每个协议最多由64个字符组成
	int nLangNum;
	char vLanguageName[128][64];
};

/// 支持的视频制式
struct SDK_MultiVstd
{
	//每个协议最多由3个字符组成
	int nVstdNum;
	char vVstdName[3][64];
};

/// 编码功能
enum SDK_EncodeFunctionTypes
{
	SDK_ENCODE_FUNCTION_TYPE_DOUBLE_STREAM,		///< 双码流功能
	SDK_ENCODE_FUNCTION_TYPE_COMBINE_STREAM,	///< 组合编码功能
	SDK_ENCODE_FUNCTION_TYPE_SNAP_STREAM,		///< 抓图功能
	SDK_ENCODE_FUNCTION_TYPE_NR,
};

/// 报警功能
enum SDK_AlarmFucntionTypes
{
	SDK_ALARM_FUNCTION_TYPE_MOTION_DETECT,	///< 动态检测
	SDK_ALARM_FUNCTION_TYPE_BLIND_DETECT,	///< 视屏遮挡
	SDK_ALARM_FUNCTION_TYPE_LOSS_DETECT,	///< 视屏丢失
	SDK_ALARM_FUNCTION_TYPE_LOCAL_ALARM,	///< 本地报警
	SDK_ALARM_FUNCTION_TYPE_NET_ALARM,		///< 网络报警
	SDK_ALARM_FUNCTION_TYPE_IP_CONFLICT,	///< IP地址冲突
	SDK_ALARM_FUNCTION_TYPE_NET_ABORT,		///< 网络异常
	SDK_ALARM_FUNCTION_TYPE_STORAGE_NOTEXIST,	///< 存储设备不存在
	SDK_ALARM_FUNCTION_TYPE_STORAGE_LOWSPACE,	///< 存储设备容量不足
	SDK_ALARM_FUNCTION_TYPE_STORAGE_FAILURE,	///< 存储设备访问失败
	SDK_ALARM_FUNCTION_TYPE_NR
};

/// 网络服务功能
enum SDK_NetServerTypes
{
	SDK_NET_SERVER_TYPES_IPFILTER,		///< 白黑名单
	SDK_NET_SERVER_TYPES_DHCP,			///< DHCP功能
	SDK_NET_SERVER_TYPES_DDNS,			///< DDNS功能
	SDK_NET_SERVER_TYPES_EMAIL,			///< Email功能
	SDK_NET_SERVER_TYPES_MULTICAST,		///< 多播功能
	SDK_NET_SERVER_TYPES_NTP,			///< NTP功能
	SDK_NET_SERVER_TYPES_PPPOE,
	SDK_NET_SERVER_TYPES_DNS,
	SDK_NET_SERVER_TYPES_ARSP,			///< 主动注册服务
	SDK_NET_SERVER_TYPES_3G,            ///< 3G拨号
	SDK_NET_SERVER_TYPES_MOBILE=10,        ///< 手机监控
	SDK_NET_SERVER_TYPES_UPNP,			    ///< UPNP
	SDK_NET_SERVER_TYPES_FTP,			    ///< FTP
	SDK_NET_SERVER_TYPES_WIFI,          ///<WIFI
	SDK_NET_SERVER_TYPES_ALARM_CENTER,  ///< 告警中心
	SDK_NET_SERVER_TYPES_NETPLAT_MEGA,  ///< 互信互通
	SDK_NET_SERVER_TYPES_NETPLAT_XINWANG,  ///< 星望
	SDK_NET_SERVER_TYPES_NETPLAT_SHISOU,  ///< 视搜
	SDK_NET_SERVER_TYPES_NETPLAT_VVEYE,  ///< 威威眼
	SDK_NET_SERVER_TYPES_RTSP,     //RTSP
	SDK_NET_SERVER_TYPES_PHONEMSG=20,     //手机信息发送配置
	SDK_NET_SERVER_TYPES_PHONEMULTIMEDIAMSG,     //手机信息发送配置
	SDK_NET_SERVER_TYPES_DAS,          //主动注册
	SDK_NET_SERVER_TYPES_NR,
    
};

/// 预览功能
enum SDK_PreviewTypes
{
	SDK_PREVIEW_TYPES_TOUR,		///< 轮巡
	SDK_PREVIEW_TYPES_TALK,		///< GUI界面配置
	SDK_PREVIEW_TYPES_NR
};

///串口类型
enum SDK_CommTypes
{
	SDK_COMM_TYPES_RS485,			///<485串口
	SDK_COMM_TYPES_RS232,			///<232串口
	SDK_COMM_TYPES_NR
};

///支持的系统功能
struct SDK_SystemFunction
{
	bool vEncodeFunction[SDK_ENCODE_FUNCTION_TYPE_NR];	///< 编码功能EncodeFunctionTypes
	bool vAlarmFunction[SDK_ALARM_FUNCTION_TYPE_NR];		///< 报警功能AlarmFucntionTypes
	bool vNetServerFunction[SDK_NET_SERVER_TYPES_NR];	///< 网络服务功能NetServerTypes
	bool vPreviewFunction[SDK_PREVIEW_TYPES_NR];		///< 预览功能PreviewTypes
	bool vCommFunction[SDK_COMM_TYPES_NR];			///<串口类型SDK_CommTypes
};

struct SDK_COMMATTRI
{
	int	iDataBits;	// 数据位取值为5,6,7,8 
	int	iStopBits;	// 停止位
	int	iParity;	// 校验位
	int	iBaudRate;	// 实际波特率
};

// 串口配置
struct SDK_CONFIG_COMM_X
{
	char iProtocolName[32];	// 串口协议:“Console” 
	int iPortNo;		// 端口号 
	SDK_COMMATTRI aCommAttri;		// 串口属性 
};

struct SDK_CommConfigAll
{
	SDK_CONFIG_COMM_X vCommConfig[SDK_COM_TYPES];
};


// 云台设置
struct SDK_STR_CONFIG_PTZ
{
	char sProtocolName[NET_MAX_PTZ_PROTOCOL_LENGTH];	// 协议名称 	
	int	ideviceNo;				// 云台设备地址编号 	
	int	iNumberInMatrixs;		// 在矩阵中的统一编号	
	int iPortNo;				// 串口端口号	[1, 4] 	
	SDK_COMMATTRI dstComm;			// 串口属性 	
};

//所有通道云台协议
struct SDK_STR_PTZCONFIG_ALL
{
	SDK_STR_CONFIG_PTZ ptzAll[NET_MAX_CHANNUM];
};

//RS485
struct SDK_STR_RS485CONFIG_ALL
{
	SDK_STR_CONFIG_PTZ ptzAll[NET_MAX_CHANNUM];
};


struct SDK_CONFIG_WORKSHEET
{	
	SDK_TIMESECTION	tsSchedule[NET_N_WEEKS][NET_N_TSECT];	/*!< 时间段 */
};

/// 录像模式种类
enum SDK_RecordModeTypes
{
	SDK_RECORD_MODE_CLOSED,		///< 关闭录像
	SDK_RECORD_MODE_MANUAL,		///< 手动录像
	SDK_RECORD_MODE_CONFIG,		///< 按配置录像
	SDK_RECORD_MODE_NR,		
};

///< 录像设置
struct SDK_RECORDCONFIG
{
	int iPreRecord;			///< 预录时间，为零时表示关闭	
	bool bRedundancy;		///< 冗余开关
	bool bSnapShot;			///< 快照开关	
	int iPacketLength;		///< 录像打包长度（分钟）[1, 255]
	int iRecordMode;		///< 录像模式，0 关闭，1 禁止 2 配置
	SDK_CONFIG_WORKSHEET wcWorkSheet;			///< 录像时间段	
	unsigned int typeMask[NET_N_WEEKS][NET_N_TSECT];		///< 录像类型掩码
};

//录像设置结构体
struct SDK_RECORDCONFIG_ALL
{
	SDK_RECORDCONFIG vRecordConfigAll[NET_MAX_CHANNUM];
};

///< 图片设置
struct SDK_SnapshotConfig
{
	int iPreSnap;			///< 预抓图片数
	bool bRedundancy;		///< 冗余开关
	int iSnapMode;		///< 录像模式，见RecordModeTypes
	SDK_CONFIG_WORKSHEET wcWorkSheet;				///< 录像时间段	
	unsigned int typeMask[NET_N_WEEKS][NET_N_TSECT];	///< 录像类型掩码，见enum RecordTypes
};

struct SDK_SnapshotConfigAll
{
	SDK_SnapshotConfig vSnapshotConfigAll[NET_MAX_CHANNUM];
};


//报警相关结构体
//  云台联动结构
struct SDK_PtzLinkConfig
{
	int iType;		// 联动的类型 
	int iValue;		// 联动的类型对应的值 
};

#define CHANNELNAME_MAX_LEN 64  //通道名称最大长度

struct SDK_EventHandler
{
	unsigned int	dwRecord;				// 录象掩码 
	int		iRecordLatch;			// 录像延时：10～300 sec  	
	unsigned int	dwTour;					// 轮巡掩码 	
	unsigned int	dwSnapShot;				// 抓图掩码 
	unsigned int	dwAlarmOut;				// 报警输出通道掩码 
	unsigned int	dwMatrix;				// 矩阵掩码 
	int		iEventLatch;			// 联动开始延时时间，s为单位 
	int		iAOLatch;				// 报警输出延时：10～300 sec  
	SDK_PtzLinkConfig PtzLink[NET_MAX_CHANNUM];		// 云台联动项 
	SDK_CONFIG_WORKSHEET schedule;		// 录像时间段

	bool	bRecordEn;				// 录像使能 
	bool	bTourEn;				// 轮巡使能 
	bool	bSnapEn;				// 抓图使能 	
	bool	bAlarmOutEn;			// 报警使能 
	bool	bPtzEn;

	// 云台联动使能 
	bool	bTip;					// 屏幕提示使能 	
	bool	bMail;					// 发送邮件 	
	bool	bMessage;				// 发送消息到报警中心 	
	bool	bBeep;					// 蜂鸣 	
	bool	bVoice;					// 语音提示 		
	bool	bFTP;					// 启动FTP传输 
	bool	bMatrixEn;				// 矩阵使能 
	bool	bLog;					// 日志使能
	bool	bMessagetoNet;			// 消息上传给网络使能 

	bool    bShowInfo;              // 是否在GUI上和编码里显示报警信息
	unsigned int    dwShowInfoMask;         // 要联动显示报警信息的通道掩码
	char    pAlarmInfo[CHANNELNAME_MAX_LEN];//要显示的报警信息

	bool    bShortMsg;              //发送短信
	bool    bMultimediaMsg;         //发送彩信
};


///< 动态检测设置
struct SDK_MOTIONCONFIG
{
	bool bEnable;							// 动态检测开启 
	int iLevel;								// 灵敏度 
	unsigned int mRegion[NET_MD_REGION_ROW];			// 区域，每一行使用一个二进制串 	
	SDK_EventHandler hEvent;					// 动态检测联动 
};

/// 全通道动态检测配置
struct SDK_MOTIONCONFIG_ALL
{
	SDK_MOTIONCONFIG vMotionDetectAll[NET_MAX_CHANNUM];
};

///< 遮挡检测配置
struct SDK_BLINDDETECTCONFIG
{
	bool	bEnable;		///< 遮挡检测开启
	int		iLevel;			///< 灵敏度：1～6
	SDK_EventHandler hEvent;	///< 遮挡检测联动
};

/// 全通道遮挡检测配置
struct SDK_BLINDDETECTCONFIG_ALL
{
	SDK_BLINDDETECTCONFIG vBlindDetectAll[NET_MAX_CHANNUM];
};

///< 基本事件结构
struct SDK_VIDEOLOSSCONFIG
{
	bool bEnable;			///< 使能
	SDK_EventHandler hEvent;	///< 处理参数
};

/// 所有通道的基本时间结构
struct SDK_VIDEOLOSSCONFIG_ALL
{
	SDK_VIDEOLOSSCONFIG vGenericEventConfig[NET_MAX_CHANNUM];
};

///< 报警输入配置
struct SDK_ALARM_INPUTCONFIG
{
	bool	bEnable;		///< 报警输入开关
	int		iSensorType;	///< 传感器类型常开 or 常闭
	SDK_EventHandler hEvent;	///< 报警联动
};

///< 所有通道的报警输入配置
struct SDK_ALARM_INPUTCONFIG_ALL
{
	SDK_ALARM_INPUTCONFIG vAlarmConfigAll[NET_MAX_CHANNUM];
};

///< 网路报警
struct SDK_NETALARMCONFIG
{
	bool bEnable;			///< 使能
	SDK_EventHandler hEvent;	///< 处理参数
};

/// 所有通道的网路报警结构
struct SDK_NETALARMCONFIG_ALL
{
	SDK_NETALARMCONFIG vNetAlarmConfig[NET_MAX_CHANNUM];
};

///< 本地报警输出配置
struct SDK_AlarmOutConfig
{
	int nAlarmOutType;		///< 报警输出类型: 配置,手动,关闭
	int nAlarmOutStatus;    ///< 报警状态: 0:打开 1;闭合
};

///< 硬盘容量不足事件结构
struct SDK_StorageLowSpaceConfig
{
	bool bEnable;
	int iLowerLimit;		///< 硬盘剩余容量下限, 百分数
	SDK_EventHandler hEvent;	///< 处理参数
};

///< 所有通道的报警输出配置
struct SDK_AlarmOutConfigAll
{
	SDK_AlarmOutConfig vAlarmOutConfigAll[NET_MAX_CHANNUM];
};

/// 所有通道的解码器地址设置V2版本
struct SDK_AbilitySerialNo
{
	char serialNo[NET_MAX_SERIALNO_LENGTH];
	char productType[NET_MAX_SERIALNO_LENGTH];
};

///< 驱动器信息结构
struct SDK_DriverInformation 
{
	int		iDriverType;		///< 驱动器类型
	bool	bIsCurrent;			///< 是否为当前工作盘
	unsigned int	uiTotalSpace;		///< 总容量，MB为单位
	unsigned int	uiRemainSpace;		///< 剩余容量，MB为单位
	int		iStatus;			///< 错误标志，文件系统初始化时被设置
	int		iLogicSerialNo;				///< 逻辑序号
	SDK_SYSTEM_TIME  tmStartTimeNew;		///< 新录像时间段的开始时间
	SDK_SYSTEM_TIME	 tmEndTimeNew;			///< 新录像时间段的结束时间
	SDK_SYSTEM_TIME	 tmStartTimeOld;		///< 老录像时间段的开始时间
	SDK_SYSTEM_TIME	 tmEndTimeOld;			///< 老录像时间段的结束时间
};
enum 
{
	SDK_MAX_DRIVER_PER_DISK = 2,	///< 每个磁盘最多的分区数
	SDK_MAX_DISK_PER_MACHINE = 8,	///< 最多支持8块硬盘
};
//硬盘管理
struct SDK_STORAGEDISK
{
	int		iPhysicalNo;
	int		iPartNumber;		// 分区数
	SDK_DriverInformation diPartitions[SDK_MAX_DRIVER_PER_DISK];
};

struct SDK_StorageDeviceInformationAll
{
	int iDiskNumber;
	SDK_STORAGEDISK vStorageDeviceInfoAll[SDK_MAX_DISK_PER_MACHINE];
};

/// 存储设备控制类型
enum SDK_StorageDeviceControlTypes
{
	SDK_STORAGE_DEVICE_CONTROL_SETTYPE,		///< 设置类型
	SDK_STORAGE_DEVICE_CONTROL_RECOVER,		///< 恢复错误
	SDK_STORAGE_DEVICE_CONTROL_PARTITIONS,	///< 分区操作
	SDK_STORAGE_DEVICE_CONTROL_CLEAR,		///< 清除操作
	SDK_STORAGE_DEVICE_CONTROL_NR,
};

/// 清除磁盘数据类型
enum SDK_StorageDeviceClearTypes
{
	SDK_STORAGE_DEVICE_CLEAR_DATA,			///< 清除录像数据
	SDK_STORAGE_DEVICE_CLEAR_PARTITIONS,	///< 清除分区
	SDK_STORAGE_DEVICE_CLEAR_NR,
};

/// 驱动器类型
enum SDK_FileSystemDriverTypes
{
	SDK_DRIVER_READ_WRITE	= 0,	///< 读写驱动器
	SDK_DRIVER_READ_ONLY	= 1,	///< 只读驱动器
	SDK_DRIVER_EVENTS		= 2,	///< 事件驱动器
	SDK_DRIVER_REDUNDANT	= 3,	///< 冗余驱动器
	SDK_DRIVER_SNAPSHOT		= 4,	///< 快照驱动器
	SDK_DRIVER_TYPE_NR		= 5,	///< 驱动器类型个数
	SDK_DRIVER_UNUSED		= 0xff,	///< 没有使用的驱动器结构
};

/// 存储设备控制
struct SDK_StorageDeviceControl
{
	int iAction;	///< 见enum SDK_StorageDeviceControlTypes
	int iSerialNo;	///< 磁盘序列号
	int iPartNo;    ///< 分区号
	int iType;		///< enum SDK_StorageDeviceClearTypes或者SDK_FileSystemDriverTypes
	int iPartSize[2/*MAX_DRIVER_PER_DISK*/];	///< 各个分区的大小
};

/// 设备信息
typedef struct _H264_DVR_DEVICEINFO
{
	char sSoftWareVersion[64];	///< 软件版本信息
	char sHardWareVersion[64];	///< 硬件版本信息
	char sEncryptVersion[64];	///< 加密版本信息
	SDK_SYSTEM_TIME tmBuildTime;///< 软件创建时间
	char sSerialNumber[64];			///< 设备序列号
	int byChanNum;				///< 视频输入通道数
	int iVideoOutChannel;		///< 视频输出通道数
	int byAlarmInPortNum;		///< 报警输入通道数
	int byAlarmOutPortNum;		///< 报警输出通道数
	int iTalkInChannel;			///< 对讲输入通道数
	int iTalkOutChannel;		///< 对讲输出通道数
	int iExtraChannel;			///< 扩展通道数	
	int iAudioInChannel;		///< 音频输入通道数
	int iCombineSwitch;			///< 组合编码通道分割模式是否支持切换
	int iDigChannel;		///<数字通道数
	unsigned int uiDeviceRunTime;	///<系统运行时间
}H264_DVR_DEVICEINFO,*LPH264_DVR_DEVICEINFO;

///< 自动维护设置
struct SDK_AutoMaintainConfig
{
	int iAutoRebootDay;				///< 自动重启设置日期
	int iAutoRebootHour;			///< 重启整点时间	[0, 23]	
	int iAutoDeleteFilesDays;		///< 自动删除文件时间[0, 30]
};

/// 默认配置种类
enum SDK_DefaultConfigKinds
{
	SDK_DEFAULT_CFG_GENERAL,			// 普通配置
	SDK_DEFAULT_CFG_ENCODE,				// 编码配置
	SDK_DEFAULT_CFG_RECORD,				// 录像配置
	SDK_DEFAULT_CFG_NET_SERVICE,		// 网络服务
	SDK_DEFAULT_CFG_NET_COMMON,			// 通用网络
	SDK_DEFAULT_CFG_ALARM,				// 报警
	SDK_DEFAULT_CFG_PTZCOMM,			// 云台，串口
	SDK_DEFAULT_CFG_USERMANAGER,		// 用户管理
	SDK_DEFAULT_CFG_PREVIEW,			// 预览配置
	SDK_DEFAULT_CFG_END,
};

/// 恢复的默认配置种类
struct SDK_SetDefaultConfigTypes
{
	bool vSetDefaultKinds[SDK_DEFAULT_CFG_END];
}; 


typedef struct H264_DVR_CLIENTINFO{
	int nChannel;	//通道号
	int nStream;	//0表示主码流，为1表示子码流
	int nMode;		//0：TCP方式,1：UDP方式,2：多播方式,3 - RTP方式，4-音视频分开(TCP)
	int nComType;	//只对组合编码通道有效, 组合编码通道的拼图模式
	void* hWnd;
	H264_DVR_CLIENTINFO()
	{
		hWnd=0;
	}
	
	
}*LPH264_DVR_CLIENTINFO;


enum SDK_File_Type
{
	SDK_RECORD_ALL = 0,
	SDK_RECORD_ALARM = 1, //外部报警录像
	SDK_RECORD_DETECT,	  //视频侦测录像
	SDK_RECORD_REGULAR,	  //普通录像
	SDK_RECORD_MANUAL,	  //手动录像
	SDK_PIC_ALL = 10,
	SDK_PIC_ALARM,		  //外部报警录像
	SDK_PIC_DETECT,		  //视频侦测录像
	SDK_PIC_REGULAR,      //普通录像
	SDK_PIC_MANUAL,       //手动录像
	SDK_TYPE_NUM
};

//查询录像条件
struct H264_DVR_FINDINFO
{
	int nChannelN0;			//通道号
	int nFileType;			//文件类型, 见SDK_File_Type
	H264_DVR_TIME startTime;	//开始时间
	H264_DVR_TIME endTime;	//结束时间
	char szCard[32];		//卡号
	void *hWnd;
	H264_DVR_FINDINFO()
	{
		hWnd=NULL;
	}
};

//录像文件返回结构体
struct H264_DVR_FILE_DATA 
{
	int ch;						//通道号
	int size;					//文件大小
	char sFileName[108];		///< 文件名
	SDK_SYSTEM_TIME stBeginTime;	///< 文件开始时间
	SDK_SYSTEM_TIME stEndTime;		///< 文件结束时间
	void *hWnd;
	H264_DVR_FILE_DATA()
	{
		hWnd=NULL;
	}
};

//回放动作
enum SEDK_PlayBackAction
{
	SDK_PLAY_BACK_PAUSE,		/*<! 暂停回放 */
	SDK_PLAY_BACK_CONTINUE,		/*<! 继续回放 */
	SDK_PLAY_BACK_SEEK,			/*<! 回放定位，时间s为单位 */
	SDK_PLAY_BACK_FAST,	        /*<! 加速回放 */
	SDK_PLAY_BACK_SLOW,	        /*<! 减速回放 */
	SDK_PLAY_BACK_SEEK_PERCENT, /*<! 回放定位百分比 */
};

//按时间段查询
struct SDK_SearchByTime
{
	int nHighChannel;			///< 33~64录像通道号掩码
	int nLowChannel;			///< 1~32录像通道号掩码
	int nFileType;              ///< 文件类型, 见SDK_File_Type
	SDK_SYSTEM_TIME stBeginTime;	    ///< 查询开始时间
	SDK_SYSTEM_TIME stEndTime;		///< 查询结束时间
	int    iSync;               ///< 是否需要同步
};

//每个通道的录像信息
struct SDK_SearchByTimeInfo
{
	int iChannel;			    ///< 录像通道号
	///< 录像记录用720个字节的5760位来表示一天中的1440分钟
	///< 0000:无录像 0001:F_COMMON 0002:F_ALERT 0003:F_DYNAMIC 0004:F_CARD 0005:F_HAND
	unsigned char cRecordBitMap[720];
};

struct SDK_SearchByTimeResult
{
	int nInfoNum;										 ///< 通道的录像记录信息个数
	SDK_SearchByTimeInfo ByTimeInfo[NET_MAX_CHANNUM];    ///< 通道的录像记录信息
};

//报警信息
typedef struct SDK_ALARM_INFO
{
	int nChannel;
	int iEvent;
	int iStatus;
	SDK_SYSTEM_TIME SysTime;
}SDK_AlarmInfo;

/// 日志查询条件
struct SDK_LogSearchCondition
{
	int nType;	///< 日志类型
	int iLogPosition;			///< 从上次查询的结束时的日志指针
	SDK_SYSTEM_TIME stBeginTime;	///< 查询日志开始时间
	SDK_SYSTEM_TIME stEndTime;		///< 查询日志结束时间
};


struct SDK_LogItem
{
	char sType[24];	///< 日志类型
	char sUser[32];	///< 日志用户
	char sData[68];	///< 日志数据
	SDK_SYSTEM_TIME stLogTime;	///< 日志时间
	int iLogPosition;			///< 从上次查询的结束时的日志指针
};

//日志返回信息
struct SDK_LogList
{
	int iNumLog;
	SDK_LogItem Logs[NET_MAX_RETURNED_LOGLIST];
};

/// 语音对讲格式
struct SDK_AudioInFormatConfigAll
{
	SDK_AudioInFormatConfig vAudioInFormatConfig[SDK_AUDIO_ENCODE_TYPES_NR];
};

/// 告警状态
struct SDK_DVR_ALARMSTATE
{
	int iVideoMotion; ///< 移动侦测状态,用掩码表示通道号,bit0代表通道一,以此类推 1: 有告警 0: 无告警
	int iVideoBlind; ///< 视频遮挡状态,用掩码表示通道号,bit0代表通道一,以此类推 1: 有告警 0: 无告警
	int iVideoLoss;	///< 视频丢失状态,用掩码表示通道号,bit0代表通道一,以此类推 1: 有告警 0: 无告警
	int iAlarmIn;	///< 告警输入状态,用掩码表示通道号,bit0代表通道一,以此类推 1: 有告警 0: 无告警
	int iAlarmOut;	///< 告警输出状态,用掩码表示通道号,bit0代表通道一,以此类推 1: 有告警 0: 无告警
};

// 通道状态
struct SDK_DVR_CHANNELSTATE
{
	bool bRecord; ///< 是否正在录像
	int iBitrate;	///< 当前码率
};

// DVR工作状态
struct SDK_DVR_WORKSTATE
{
	SDK_DVR_CHANNELSTATE vChnState[NET_MAX_CHANNUM];
	SDK_DVR_ALARMSTATE vAlarmState;
};


/// 按键值, 不能随便更改
enum SDK_NetKeyBoardValue
{
	SDK_NET_KEY_0, SDK_NET_KEY_1, SDK_NET_KEY_2, SDK_NET_KEY_3, SDK_NET_KEY_4, SDK_NET_KEY_5, SDK_NET_KEY_6, SDK_NET_KEY_7, SDK_NET_KEY_8, SDK_NET_KEY_9,
	SDK_NET_KEY_10, SDK_NET_KEY_11, SDK_NET_KEY_12, SDK_NET_KEY_13, SDK_NET_KEY_14, SDK_NET_KEY_15, SDK_NET_KEY_16, SDK_NET_KEY_10PLUS,
	SDK_NET_KEY_UP = 20,     // 上或者云台向上
	SDK_NET_KEY_DOWN,        // 下或者云台向下
	SDK_NET_KEY_LEFT,        // 左或者云台向左
	SDK_NET_KEY_RIGHT,       // 右或者云台向右
	SDK_NET_KEY_SHIFT, 
	SDK_NET_KEY_PGUP,        // 上一页
	SDK_NET_KEY_PGDN,        // 下一页
	SDK_NET_KEY_RET,         // 确认
	SDK_NET_KEY_ESC,         // 取消或退出
	SDK_NET_KEY_FUNC,        // 切换输入法
	SDK_NET_KEY_PLAY,        // 播放/暂停
	SDK_NET_KEY_BACK,        // 倒放
	SDK_NET_KEY_STOP,        // 停止
	SDK_NET_KEY_FAST,        // 快放
	SDK_NET_KEY_SLOW,        // 慢放
	SDK_NET_KEY_NEXT,        // 下一个文件
	SDK_NET_KEY_PREV,        // 上一个文件
	SDK_NET_KEY_REC = 40,    // 录像设置
	SDK_NET_KEY_SEARCH,      // 录像查询
	SDK_NET_KEY_INFO,        // 系统信息
	SDK_NET_KEY_ALARM,       // 告警输出
	SDK_NET_KEY_ADDR,        // 遥控器地址设置
	SDK_NET_KEY_BACKUP,      // 备份
	SDK_NET_KEY_SPLIT,       // 画面分割模式切换，每按一次切换到下一个风格模式
	SDK_NET_KEY_SPLIT1,      // 单画面
	SDK_NET_KEY_SPLIT4,      // 四画面
	SDK_NET_KEY_SPLIT8,      // 八画面
	SDK_NET_KEY_SPLIT9,      // 九画面
	SDK_NET_KEY_SPLIT16,     // 16画面
	SDK_NET_KEY_SHUT,        // 关机
	SDK_NET_KEY_MENU,        // 菜单
	SDK_NET_KEY_PTZ = 60,    // 进入云台控制模式
	SDK_NET_KEY_TELE,        // 变倍减
	SDK_NET_KEY_WIDE,        // 变倍加
	SDK_NET_KEY_IRIS_SMALL,  // 光圈增
	SDK_NET_KEY_IRIS_LARGE,  // 光圈减
	SDK_NET_KEY_FOCUS_NEAR,  // 聚焦远
	SDK_NET_KEY_FOCUS_FAR,   // 聚焦近
	SDK_NET_KEY_BRUSH,       // 雨刷
	SDK_NET_KEY_LIGHT,       // 灯光
	SDK_NET_KEY_SPRESET,     // 设置预置点
	SDK_NET_KEY_GPRESET,     // 转至预置点
	SDK_NET_KEY_DPRESET,     // 清除预置点 
	SDK_NET_KEY_PATTERN,     // 模式
	SDK_NET_KEY_AUTOSCAN,    // 自动扫描开始结束
	SDK_NET_KEY_AUTOTOUR,    // 自动巡航
	SDK_NET_KEY_AUTOPAN,     // 线扫开始/结束
};

/// 按键状态
enum SDK_NetKeyBoardState
{
	SDK_NET_KEYBOARD_KEYDOWN,	// 按键按下
	SDK_NET_KEYBOARD_KEYUP,		// 按键松开
};

struct SDK_NetKeyBoardData
{
	int iValue;
	int iState;
};

// 升级信息获取
struct SDK_UpgradeInfo
{
	char szSerial[64];
	char szHardware[64];
	char szVendor[64];
	unsigned int uiLogoArea[2];
};

/// 网络报警
struct SDK_NetAlarmInfo
{
	int iEvent;  //目前未使用
	int iState;   //每bit表示一个通道,bit0:第一通道,0-无报警 1-有报警, 依次类推
};

enum SERIAL_TYPE
{
	RS232 = 0,
	RS485 = 1,
};


enum MEDIA_PACK_TYPE
{
	FILE_HEAD =	0,	    		// 文件头
	VIDEO_I_FRAME = 1,			// 视频I帧
	VIDEO_B_FRAME =	2,			// 视频B帧
	VIDEO_P_FRAME = 3,			// 视频P帧
	VIDEO_BP_FRAME = 4,			// 视频BP帧
	VIDEO_BBP_FRAME	= 5,		// 视频B帧B帧P帧
	VIDEO_J_FRAME = 6,			// 图片帧
	AUDIO_PACKET = 10,			// 音频包
};

typedef struct
{
	int		nPacketType;				// 包类型,见MEDIA_PACK_TYPE
	char*	pPacketBuffer;				// 缓存区地址
	unsigned int	dwPacketSize;				// 包的大小

	// 绝对时标
	int		nYear;						// 时标:年		
	int		nMonth;						// 时标:月
	int		nDay;						// 时标:日
	int		nHour;						// 时标:时
	int		nMinute;					// 时标:分
	int		nSecond;					// 时标:秒
	unsigned int 	dwTimeStamp;					// 相对时标低位，单位为毫秒
	unsigned int	dwTimeStampHigh;        //相对时标高位，单位为毫秒
	unsigned int   dwFrameNum;             //帧序号
	unsigned int   dwFrameRate;            //帧率
	unsigned short uWidth;              //图像宽度
	unsigned short uHeight;             //图像高度
	unsigned int       Reserved[6];            //保留
} PACKET_INFO_EX;


struct SDK_OEMInfo
{
	int nOEMID;                     //OEM ID
	char sCompanyName[NET_MAX_USERNAME_LENGTH]; //公司名
	char sTel[NET_MAX_USERNAME_LENGTH];         //电话
	char sAddr[NET_MAX_USERNAME_LENGTH];        //地址
};
typedef struct __TransComChannel//透明窗口
{
	SERIAL_TYPE TransComType;//SERIAL_TYPE
	unsigned int baudrate;
	unsigned int databits;
	unsigned int stopbits;
	unsigned int parity;
} TransComChannel;
enum SDK_State_Type
{
	DEV_STATE_DDNS=0,	
};

//摄象机参数.....

//曝光配置
struct SDK_ExposureCfg
{
	int  level;    //曝光等级
	unsigned int leastTime;//自动曝光时间下限或手动曝光时间，单位微秒
	unsigned int mostTime; //自动曝光时间上限，单位微秒
};

//增益配置
struct SDK_GainCfg
{
	int gain;    //自动增益上限(自动增益启用)或固定增益值
	int autoGain;//自动增益是否启用，0:不开启  1:开启
};

//网络摄像机配置
struct SDK_CameraParam
{
	unsigned int whiteBalance;         //白平衡
	unsigned int dayNightColor;        //日夜模式，取值有彩色、自动切换和黑白
	int elecLevel;             //参考电平值
	unsigned int apertureMode;          //自动光圈模式
	unsigned int BLCMode;               //背光补偿模式
	SDK_ExposureCfg exposureConfig;//曝光配置
	SDK_GainCfg     gainConfig;    //增益配置

	unsigned int PictureFlip;		//图片上下翻转
	unsigned int PictureMirror;	//图片左右翻转(镜像)
	unsigned int RejectFlicker;	//日光灯防闪功能
	unsigned int EsShutter;		//电子慢快门功能

	int ircut_mode;		//IR-CUT切换 0 = 红外灯同步切换 1 = 自动切换
};

//所有摄象机配置
struct SDK_AllCameraParam
{
	SDK_CameraParam vCameraParamAll[NET_MAX_CHANNUM];   //所有的通道
};

//曝光能力级
struct SDK_CameraAbility
{
	int  count;      //支持曝光速度数量
	unsigned int speeds[CAMERAPARA_MAXNUM]; //曝光速度
	int  status;     //工作状态  >= 0 正常    < 0 异常
	int  elecLevel;  //参考电平值
	int  luminance;  //平均亮度
	char pVersion[64];//xm 2a版本
	char reserve[32];//保留
};

//本地播放控制
enum SDK_LoalPlayAction
{
	SDK_Local_PLAY_PAUSE,		/*<! 暂停播放 */
	SDK_Local_PLAY_CONTINUE,		/*<! 继续正常播放 */
	SDK_Local_PLAY_FAST,	        /*<! 加速播放 */
	SDK_Local_PLAY_SLOW,	        /*<! 减速播放 */	
	
};

//短信配置
struct SDK_NetShortMsgCfg
{
	bool bEnable;       //发送手机短信的功能是否启用
	char pDesPhoneNum[MAX_RECIVE_MSG_PHONE_COUNT][16];
	int  sendTimes;     //需要向每个手机发送多少次短信
};
//手机彩信配置
struct SDK_NetMultimediaMsgCfg
{
	bool bEnable;				// 发送手机彩信的功能是否启用
	char pDesPhoneNum[MAX_RECIVE_MSG_PHONE_COUNT][16]; //接收彩信的手机号，现支持3个手机号
	char pGateWayDomain[40];	// 网关地址，域名或IP
	int  gateWayPort;			// 网关端口
	char pMmscDomain[40];		// 彩信服务器地址，IP或域名
	int  mmscPort;				// 彩信服务器端口号
};

struct SDK_DASSerInfo
{
	bool enable;
	char serAddr[NET_NAME_PASSWORD_LEN];
	int  port;
	char userName[NET_NAME_PASSWORD_LEN];
	char passwd[NET_NAME_PASSWORD_LEN];
	char devID[NET_NAME_PASSWORD_LEN];
};

// 透明串口回调函数原形
typedef void (CALL_METHOD *fTransComCallBack) (long lLoginID, long lTransComType, char *pBuffer, unsigned long dwBufSize, unsigned long dwUser);
//服务器断开回调原形
typedef void (CALL_METHOD *fDisConnect)(long lLoginID, char *pchDVRIP, long nDVRPort, unsigned long dwUser);

//原始数据回调原形
typedef int(CALL_METHOD *fRealDataCallBack) (long lRealHandle, long dwDataType, unsigned char *pBuffer,long lbufsize,long dwUser);
typedef int(CALL_METHOD *fRealDataCallBack_V2) (long lRealHandle, const PACKET_INFO_EX *pFrame, unsigned int dwUser);

// 回放录像进度回调原形
typedef void(CALL_METHOD *fDownLoadPosCallBack) (long lPlayHandle, long lTotalSize, long lDownLoadSize, long dwUser);

//消息（报警）回调原形
typedef bool (CALL_METHOD *fMessCallBack)(long lLoginID, char *pBuf,
									   unsigned long dwBufLen, long dwUser);

//升级设备程序回调原形
typedef void(CALL_METHOD *fUpgradeCallBack) (long lLoginID, long lUpgradechannel,
										   int nTotalSize, int nSendSize, long dwUser);

// 语音对讲的音频数据回调函数原形
typedef void (CALL_METHOD *pfAudioDataCallBack)(long lVoiceHandle, char *pDataBuf, 
											 long dwBufSize, char byAudioFlag, long dwUser);


//本地播放结束回调原形
typedef void (CALL_METHOD * fLocalPlayFileCallBack)(long lPlayHand, long nUser);

//信息帧回调设置
typedef void (CALL_METHOD  *InfoFramCallBack)(long lPlayHand, long nType, LPCSTR pBuf,long nSize, long nUser);
#ifdef WIN32
//RigisterDraw回调原形
typedef void (CALL_METHOD * fPlayDrawCallBack)(long lPlayHand,HDC hDc,long nUser);
#else//linux没用到这个回调
typedef void (CALL_METHOD * fPlayDrawCallBack)(long lPlayHand,void* hDc,long nUser);
#endif // WIN32  

//*** */SDK初始化
H264_DVR_API long CALL_METHOD H264_DVR_Init(fDisConnect cbDisConnect, unsigned long dwUser);

//*** */SDK退出清理
H264_DVR_API bool CALL_METHOD H264_DVR_Cleanup();

//获取错误信息
H264_DVR_API long CALL_METHOD H264_DVR_GetLastError();

// 设置连接设备超时时间和尝试次数
//nWaitTime:单位ms不设置时默认5000ms,
//nTryTimes:次数,不设置时默认3次
H264_DVR_API bool CALL_METHOD H264_DVR_SetConnectTime(long nWaitTime, long nTryTimes);

//*** */向设备注册
enum SocketStyle
{
	TCPSOCKET=0,
	UDPSOCKET
};
H264_DVR_API long CALL_METHOD H264_DVR_Login(char *sDVRIP, unsigned short wDVRPort, char *sUserName, char *sPassword,
							   LPH264_DVR_DEVICEINFO lpDeviceInfo, int *error,SocketStyle socketTyle=TCPSOCKET);

//向设备注册扩展接口
//增加登陆类型 0==web 1 ==升级工具 2 == 搜索工具
H264_DVR_API long CALL_METHOD H264_DVR_LoginEx(char *sDVRIP, unsigned short wDVRPort, char *sUserName, char *sPassword,
							   LPH264_DVR_DEVICEINFO lpDeviceInfo, int nType, int *error);

//*** */向设备注销
H264_DVR_API long CALL_METHOD H264_DVR_Logout(long lLoginID);

//设置接收DVR信息回调, 例如报警信息,以ID号区分
H264_DVR_API bool CALL_METHOD H264_DVR_SetDVRMessCallBack(fMessCallBack cbAlarmcallback, unsigned long lUser);

//建立报警上传通道
H264_DVR_API long CALL_METHOD H264_DVR_SetupAlarmChan(long lLoginID);
H264_DVR_API bool CALL_METHOD H264_DVR_CloseAlarmChan(long lLoginID);


//远程配置设备接口 配置类型见SDK_CONFIG_TYPE
H264_DVR_API long  CALL_METHOD H264_DVR_GetDevConfig(long lLoginID, unsigned long dwCommand, int nChannelNO, char * lpOutBuffer, unsigned long dwOutBufferSize, unsigned long* lpBytesReturned,int waittime = 1000);
H264_DVR_API long  CALL_METHOD H264_DVR_SetDevConfig(long lLoginID, unsigned long dwCommand, int nChannelNO, char * lpInBuffer, unsigned long dwInBufferSize, int waittime = 1000);
//跨网段设置设备配置，目前只支持对网络配置进行设置
H264_DVR_API long CALL_METHOD H264_DVR_SetConfigOverNet(unsigned long dwCommand, int nChannelNO, char * lpInBuffer, unsigned long dwInBufferSize, int waittime = 1000);

//日志查询
H264_DVR_API bool CALL_METHOD H264_DVR_FindDVRLog(long lLoginID, SDK_LogSearchCondition *pFindParam, SDK_LogList *pRetBuffer, long lBufSize, int waittime = 2000);

//打开实时预览
H264_DVR_API long CALL_METHOD H264_DVR_RealPlay(long lLoginID, LPH264_DVR_CLIENTINFO lpClientInfo);
H264_DVR_API bool CALL_METHOD H264_DVR_StopRealPlay(long lRealHandle,void*hWnd=NULL);
H264_DVR_API long CALL_METHOD H264_DVR_PauseRealPlay(long lRealHandle, bool bPause);

//设置回调函数，用户自己处理客户端收到的数据
H264_DVR_API bool CALL_METHOD H264_DVR_SetRealDataCallBack(long lRealHandle,fRealDataCallBack cbRealData, long dwUser);
H264_DVR_API bool CALL_METHOD H264_DVR_SetRealDataCallBack_V2(long lRealHandle,fRealDataCallBack_V2 cbRealData, long dwUser);

//清除回调函数,该函数需要在H264_DVR_StopRealPlay前调用
H264_DVR_API bool CALL_METHOD H264_DVR_DelRealDataCallBack(long lRealHandle,fRealDataCallBack cbRealData, long dwUser);
H264_DVR_API bool CALL_METHOD H264_DVR_DelRealDataCallBack_V2(long lRealHandle,fRealDataCallBack_V2 cbRealData, long dwUser);

//录像查询
//lLoginID		登陆句柄
//lpFindInfo	查询条件
//lpFileData	查找到的录像数据，外部开内存
//lMaxCount		最大录像数目
//findcount		查找到的录像数目
//waittime		查询超时时间
H264_DVR_API long CALL_METHOD H264_DVR_FindFile(long lLoginID, H264_DVR_FINDINFO* lpFindInfo, H264_DVR_FILE_DATA *lpFileData, int lMaxCount, int *findcount, int waittime = 5000);

//录像查询
//lLoginID		登陆句柄
//lpFindInfo	查询条件
//lpFileData	查找到的录像数据，外部开内存
//waittime		查询超时时间
H264_DVR_API long CALL_METHOD H264_DVR_FindFileByTime(long lLoginID, SDK_SearchByTime* lpFindInfo, SDK_SearchByTimeResult *lpFileData, int waittime = 10000);

//录像回放
//lLoginID		登陆句柄
//sPlayBackFileName	回放的录像名称
//cbDownLoadPos 进度回调		用户通知用户设备是否已经将数据发送完毕
								//客户如果想实时显示进度，应该从码流里面获取时间来计算
								//网络部分不分析码流，如果以当前接收数据大小/总大小来计算进度的话不是很准，应该以当前时间，根据开始时间和结束时间来计算进度
//fDownLoadDataCallBack 数据回调
//dwDataUser	回调参数
H264_DVR_API long CALL_METHOD H264_DVR_PlayBackByName(long lLoginID, H264_DVR_FILE_DATA *sPlayBackFile, fDownLoadPosCallBack cbDownLoadPos, fRealDataCallBack fDownLoadDataCallBack, long dwDataUser);
H264_DVR_API long CALL_METHOD H264_DVR_PlayBackByName_V2(long lLoginID, H264_DVR_FILE_DATA *sPlayBackFile, fDownLoadPosCallBack cbDownLoadPos, fRealDataCallBack_V2 fDownLoadDataCallBack, long dwDataUser);

//按时间进行录像回放
H264_DVR_API long CALL_METHOD H264_DVR_PlayBackByTime(long lLoginID, H264_DVR_FINDINFO* lpFindInfo, fDownLoadPosCallBack cbDownLoadPos, fRealDataCallBack fDownLoadDataCallBack, long dwDataUser);
//H264_DVR_API long CALL_METHOD H264_DVR_PlayBackByTimeEx(long lLoginID, int nChannelID, LPH264_DVR_TIME lpStartTime,
//											LPH264_DVR_TIME lpStopTime, fRealDataCallBack fDownLoadDataCallBack, long dwDataUser,
//											fDownLoadPosCallBack cbDownLoadPos, long dwPosUser);

H264_DVR_API long CALL_METHOD H264_DVR_PlayBackByTimeEx(long lLoginID, H264_DVR_FINDINFO* lpFindInfo,fRealDataCallBack fDownLoadDataCallBack, long dwDataUser,
											fDownLoadPosCallBack cbDownLoadPos, long dwPosUser);

H264_DVR_API bool CALL_METHOD H264_DVR_StopPlayBack(long lPlayHandle);

//回放控制分,暂停,定位等等
H264_DVR_API bool CALL_METHOD H264_DVR_PlayBackControl(long lPlayHandle, long lControlCode,long lCtrlValue);

//录像下载,用户可以不使用回调，自己通过H264_DVR_GetDownloadPos获取进度
H264_DVR_API long CALL_METHOD H264_DVR_GetFileByName(long lLoginID,H264_DVR_FILE_DATA *sPlayBackFile,char *sSavedFileName, 
											fDownLoadPosCallBack cbDownLoadPos = NULL, long dwDataUser = NULL );

H264_DVR_API long CALL_METHOD H264_DVR_GetFileByTime(long lLoginID, H264_DVR_FINDINFO* lpFindInfo, char *sSavedFileDIR, bool bMerge = false,
											fDownLoadPosCallBack cbDownLoadPos = NULL, long dwDataUser = NULL );

H264_DVR_API bool CALL_METHOD H264_DVR_StopGetFile(long lFileHandle);
//获取下载进度
H264_DVR_API int CALL_METHOD H264_DVR_GetDownloadPos(long lFileHandle);

//升级
H264_DVR_API long CALL_METHOD H264_DVR_Upgrade(long lLoginID, char *sFileName, int nType = 0, fUpgradeCallBack cbUpgrade = NULL, long dwUser = 0);
//升级状态 1 成功， 2 正在升级 3 失败
H264_DVR_API int CALL_METHOD H264_DVR_GetUpgradeState(long lUpgradeHandle);
H264_DVR_API long CALL_METHOD H264_DVR_CloseUpgradeHandle(long lUpgradeHandle);


//云台控制，默认是开启云台，速度4，用户也可以自行设置速度
H264_DVR_API bool CALL_METHOD H264_DVR_PTZControl(long lLoginID,int nChannelNo, long lPTZCommand, bool bStop = false, long lSpeed = 4);

//扩展云台控制，包括预置点设置，巡航路线，快速定位等等
H264_DVR_API bool CALL_METHOD H264_DVR_PTZControlEx(long lLoginID,int nChannelNo, long lPTZCommand, 
									long lParam1, long lParam2, long lParam3, bool bStop = false);

//设备控制：返回值 true 成功， false 失败
H264_DVR_API bool CALL_METHOD H264_DVR_ControlDVR(long lLoginID, int type, int waittime = 2000);


//搜索局域网内的设备
H264_DVR_API bool CALL_METHOD H264_DVR_SearchDevice(char* szBuf, int nBufLen, int* pRetLen, int nSearchTime);


//语音对讲，负责数据传发接口
H264_DVR_API long CALL_METHOD H264_DVR_StartVoiceCom_MR(long lLoginID, pfAudioDataCallBack pVcb, long dwDataUser);
H264_DVR_API bool CALL_METHOD H264_DVR_VoiceComSendData(long lVoiceHandle, char *pSendBuf, long lBufSize);
H264_DVR_API bool CALL_METHOD H264_DVR_StopVoiceCom(long lVoiceHandle);

//设置对讲音频编码方式，用户可以不设置，默认为G711A编码
H264_DVR_API bool CALL_METHOD H264_DVR_SetTalkMode(long lLoginID, SDK_AudioInFormatConfig* pTalkMode);

// lRecordType录像模式, 见SDK_RecordModeTypes
H264_DVR_API bool CALL_METHOD H264_DVR_StartDVRRecord(long lLoginID, int nChannelNo ,long lRecordType);
H264_DVR_API bool CALL_METHOD H264_DVR_StopDVRRecord(long lLoginID, int nChannelNo);

H264_DVR_API bool CALL_METHOD H264_DVR_SetSystemDateTime(long lLoginID, SDK_SYSTEM_TIME *pSysTime);
H264_DVR_API bool CALL_METHOD H264_DVR_GetDVRWorkState(long lLoginID, SDK_DVR_WORKSTATE *pWorkState);

H264_DVR_API bool CALL_METHOD H264_DVR_ClickKey(long lLoginID, SDK_NetKeyBoardData *pKeyBoardData);

// 磁盘管理
H264_DVR_API int CALL_METHOD H264_DVR_StorageManage(long lLoginID, SDK_StorageDeviceControl *pStorageCtl);

H264_DVR_API bool CALL_METHOD H264_DVR_SendNetAlarmMsg(long lLoginID, SDK_NetAlarmInfo *pAlarmInfo);

// 抓图
H264_DVR_API bool CALL_METHOD H264_DVR_CatchPic(long lLoginID, int nChannel, char *sFileName);
H264_DVR_API bool CALL_METHOD H264_DVR_CatchPicInBuffer(long lLoginID, int nChannel, char *pBuffer, int nBufLen, int *pPicLen);

H264_DVR_API bool CALL_METHOD H264_DVR_StartAlarmCenterListen(int nPort, fMessCallBack cbAlarmCenter, unsigned long dwDataUser);
H264_DVR_API bool CALL_METHOD H264_DVR_StopAlarmCenterListen();

//透明232,485
H264_DVR_API bool CALL_METHOD H264_DVR_SerialWrite(long lLoginID, SERIAL_TYPE nType, char *pBuffer, int nBufLen);
H264_DVR_API bool CALL_METHOD H264_DVR_SerialRead(long lLoginID, SERIAL_TYPE nType, char *pBuffer, int nBufLen, int *pReadLen);

H264_DVR_API int CALL_METHOD H264_DVR_GetDDNSInfo(SearchMode &searchmode, DDNS_INFO *pDevicInfo, int maxDeviceNum, int &nretNum);

//nStream: 0表示主码流，为1表示子码流
H264_DVR_API bool CALL_METHOD H264_DVR_MakeKeyFrame(long lLoginID, int nChannel, int nStream);

//nStream: 0表示主码流，为1表示子码流
H264_DVR_API bool CALL_METHOD H264_DVR_GetOEMInfo(long lLoginID, SDK_OEMInfo *pOEMInfo);
// 创建透明串口通道
H264_DVR_API bool CALL_METHOD H264_DVR_OpenTransComChannel(long lLoginID, TransComChannel *TransInfo, fTransComCallBack cbTransCom, unsigned long lUser);
//关闭透明串口通道
H264_DVR_API bool CALL_METHOD H264_DVR_CloseTransComChannel(long lLoginID, SERIAL_TYPE nType);
//获取状态信息
H264_DVR_API bool CALL_METHOD H264_DVR_GetDeviceState(long lLoginID, SDK_State_Type type, char *pState);
//获取ui图片:type 1:为全图片 2:活动区域图片
H264_DVR_API bool CALL_METHOD H264_DVR_CatchPicUI(long lLoginID,char *saveFileName,int type=1);

#ifdef WIN32

//打开通道音频 //预览，回放，本地播放 一个函数
H264_DVR_API bool CALL_METHOD H264_DVR_OpenSound(long lHandle);
//关闭通道音频 //预览，回放，本地播放 一个函数
H264_DVR_API bool CALL_METHOD H264_DVR_CloseSound(long lHandle);
//抓本地图片 //预览，回放，本地播放 一个函数
H264_DVR_API bool CALL_METHOD H264_DVR_LocalCatchPic(long lHandle,char*szSaveFileName);
//打开对讲
H264_DVR_API long CALL_METHOD H264_DVR_StartLocalVoiceCom(long lLoginID);
//开始本地录像
H264_DVR_API bool CALL_METHOD H264_DVR_StartLocalRecord(long lRealHandle,char*szSaveFileName,long type=0);
//关闭本地录像
H264_DVR_API bool CALL_METHOD H264_DVR_StopLocalRecord(long lRealHandle);

//播放本地文件
H264_DVR_API long CALL_METHOD H264_DVR_StartLocalPlay(char*pFileName,void* hWnd,fPlayDrawCallBack drawCallBack=NULL,long user=NULL);
//关闭本地播放
H264_DVR_API bool CALL_METHOD H264_DVR_StopLocalPlay(long lPlayHandle);
//获取播放位置用于回放，和本地播放
H264_DVR_API float CALL_METHOD H264_DVR_GetPlayPos(long lPlayHandle);
//设置播放位置（百分比）用于回放，和本地播放
H264_DVR_API bool CALL_METHOD H264_DVR_SetPlayPos(long lPlayHandle,float fRelativPos);
//播放控制（播放，停止，恢复，快发，慢放）
H264_DVR_API bool CALL_METHOD H264_DVR_LocalPlayCtrl(long lPlayHandle,SDK_LoalPlayAction action,long lCtrlValue);
//设置播放结束回调
H264_DVR_API bool CALL_METHOD H264_DVR_SetFileEndCallBack(long lPlayHandle,fLocalPlayFileCallBack callBack,long user);
//设置信息帧回调
H264_DVR_API bool CALL_METHOD H264_DVR_SetInfoFrameCallBack(long lPlayHandle,InfoFramCallBack callback,long user);

//本地颜色控制 //预览，回放，本地播放 一个函数
H264_DVR_API bool CALL_METHOD H264_DVR_LocalGetColor(long lHandle, DWORD nRegionNum, LONG *pBrightness, LONG *pContrast, LONG *pSaturation, LONG *pHue);
H264_DVR_API bool CALL_METHOD H264_DVR_LocalSetColor(long lHandle, DWORD nRegionNum, LONG nBrightness, LONG nContrast, LONG nSaturation, LONG nHue);
#endif
//设置本地ip
H264_DVR_API bool CALL_METHOD H264_DVR_SetLocalBindAddress(char*szIP);






#endif