// dlgDemoDlg.h : header file
//

#if !defined(AFX_DLGDEMODLG_H__AAA927C3_2E40_4508_95B9_65DB11951266__INCLUDED_)
#define AFX_DLGDEMODLG_H__AAA927C3_2E40_4508_95B9_65DB11951266__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "datastru.h"
#include "DXMediaCap.h"
#include "BtnST.h"
#include "ChannelWnd.h"

#include "SerialPort.h"  //添加CSerailPort类的头文件
#include "cyQueue.h"
#include "MyProgress.h"
#include "PictureEx.h"

//对话框类
#include "TxtViewerDlg.h"
#include "PicViewerDlg.h"
#include "VideoPlayerDlg.h"


//宏定义预览区的尺寸
#define  VideoArea_X    166
#define  VideoArea_Y    1
#define  VideoArea_W    948
#define  VideoArea_H    718



/////////////////////////////////////////////////////////////////////////////
// CDlgDemoDlg dialog



#define SEND_DATA_LEN       10
#define SEND_DATA_HEAD      0XA7
#define SEND_DATA_ADDRESS   0X01
#define SEND_DATA_CMD       0X80

#define RECEIVE_DATA_LEN       10
#define RECEIVE_DATA_HEAD      0XA6
#define RECEIVE_DATA_ADDRESS   0X01
#define RECEIVE_DATA_CMD       0X80



//定义一个接收数据的数据类型
#pragma pack(1)
typedef union
{
	struct
	{
		unsigned char head;
		unsigned char address;
		unsigned char command;
		unsigned char actionCtrl;
		unsigned char ctrlBoxPower;
		unsigned char leftPower;
		unsigned char rightPower;
		unsigned char reverse_1;
		unsigned char reverse_2;
		unsigned char check;
	}allData;
	unsigned char Data[RECEIVE_DATA_LEN];
} ReceiveDataType;
#pragma pack()

//线程1入口函数
DWORD WINAPI ThreadProc1(LPVOID lpParameter);


class CDlgDemoDlg : public CDialog
{
// Construction
public:

	CSerialPort m_SerialPort; //CSerailPort类对象
	BOOL m_bSerialPortOpened; //标志串口是否打开
	CDlgDemoDlg(CWnd* pParent = NULL);	// standard constructor
	~CDlgDemoDlg();



    static int 			m_nDevNum;
	 static int 			m_PreviewMode;
    static  int             m_OpenSata;
	 int             m_StartPreview;
	unsigned int             m_VidStandard;
	unsigned int             m_Width;
	unsigned int             m_Height;
	unsigned int             m_Colorspace;
	float             m_FrameRate;
	static  device_handle	m_device;
	static	DEVICE_TAG VideoTags[100];
	static	DEVICE_TAG AudioTags[100];
	static DEVICE_INFO  DeviceInfo[23];

// Dialog Data
	//{{AFX_DATA(CDlgDemoDlg)
	enum { IDD = IDD_DLGDEMO_DIALOG };
	CButtonST	m_exitBtn;
	CButtonST	m_openBtn;
	CButtonST	m_videoPlayerBtn;
	CButtonST	m_txtViewerBtn;
	CButtonST	m_picViewerBtn;
	CPictureEx	m_loadDevicesGIF;
	CStatic	m_ctrlBoxVol;
	CStatic	m_leftVol;
	CStatic	m_rightVol;
	CStatic	m_padVol;
	CButton	m_openDevBtn;
	CButton	m_closeDevBtn;
	CPictureEx	m_chargeGIF;
	MyProgress	m_rightPower;
	MyProgress	m_padPower;
	MyProgress	m_leftPower;
	MyProgress	m_ctrlBoxPower;
	CButtonST	m_pauseBtn;
	CButtonST	m_settingBtn;
	CButtonST	m_recordBtn;
	CButtonST	m_snapBtn;
	CStatic	m_PrvHwnd;
	CButton	m_bt_CallBack;
	CString	m_strReceive;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
		WNDCLASSEX             m_wc;
	char          m_strClassname[50];
	// Generated message map functions
	//{{AFX_MSG(CDlgDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtStep00();
	afx_msg void OnBtStep01();
	afx_msg void OnBtStep02();
	afx_msg void OnBtStep03();
	afx_msg void OnBtStep04();
	afx_msg void OnBtAssignAudio();
	afx_msg void OnBtPcolor();
	afx_msg void OnBtBmp();
	afx_msg void OnBtJpg();
	afx_msg void OnBtDrawfile();
	afx_msg void OnBtHidefile();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnBtTextosd();
	afx_msg void OnBtImageosd();
	afx_msg void OnBtTimeosd();
	afx_msg void OnBtFlipvideo();
	afx_msg void OnBtMirrorvideo();
	afx_msg void OnBtBufdisplay();
	afx_msg void OnBtSource();
	afx_msg void OnSourAv1();
	afx_msg void OnSourAv2();
	afx_msg void OnSourSvideo();
	afx_msg void OnSizeD1();
	afx_msg void OnSizeCif();
	afx_msg void OnStandNtsc();
	afx_msg void OnStandPal();
	afx_msg void OnUpdateSourAv1(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSourAv2(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSourSvideo(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSizeD1(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSizeCif(CCmdUI* pCmdUI);
	afx_msg void OnUpdateStandNtsc(CCmdUI* pCmdUI);
	afx_msg void OnUpdateStandPal(CCmdUI* pCmdUI);
	afx_msg void OnFlipVideo();
	afx_msg void OnUpdateFlipVideo(CCmdUI* pCmdUI);
	afx_msg void OnMirrorVideo();
	afx_msg void OnUpdateMirrorVideo(CCmdUI* pCmdUI);
	afx_msg void OnDeinterlaceCANCEL();
	afx_msg void OnUpdateDeinterlaceCANCEL(CCmdUI* pCmdUI);
	afx_msg void OnDeinterlaceGOOD();
	afx_msg void OnUpdateDeinterlaceGOOD(CCmdUI* pCmdUI);
	afx_msg void OnDeinterlaceSTD();
	afx_msg void OnUpdateDeinterlaceSTD(CCmdUI* pCmdUI);
	afx_msg void OnBUTTONGetBuf();
	afx_msg void OnButtonSnap();
	afx_msg void OnButtonExit();
	afx_msg void OnBtRecord();
	afx_msg void OnButtonCodec();
	afx_msg void OnButtonPauserec();
	afx_msg void OnDestroy();
	afx_msg void OnUpdateSize960h(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSize768(CCmdUI* pCmdUI);
	afx_msg void OnSize768();
	afx_msg void OnSize960h();
	afx_msg void OnDeinterlaceLowCpu();
	afx_msg void OnUpdateDeinterlaceLowCpu(CCmdUI* pCmdUI);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButtonOpen();
	afx_msg LONG OnComm(WPARAM ch, LPARAM port);    //串口消息处理函数
	afx_msg BOOL OnDeviceChange(UINT nEventType, DWORD dwData);  //手动添加 设备检测消息函数
	afx_msg void OnClosedevbtn();
	afx_msg void OnOpendevbtn();
	afx_msg void OnBtnTxtviewer();
	afx_msg void OnBtnPicviewer();
	afx_msg void OnBtnVideoplayer();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	LRESULT OnChannelSetFocus(WPARAM wp,LPARAM lp);
	LRESULT OnLBTNDBClikShowWin(WPARAM wPara, LPARAM lParam);
 

private:

	void InitSDK();   // 初始化SDK
	BOOL CreateWindowClass( );            //创建窗口类
	void OnCreateWindow( DWORD dwCard ); //创建预览子窗体
	void DrawRecordFrame(COLORREF);     //绘制录制视屏时的边框
	void OpenThread1();        //打开线程1
	void OpenSerialPort(UINT port);		//打开串口
	void SendSerialData();         //发送数据
	void UpdatePowerStatus();       //更新4个电量的显示信息 
	void ReceiveDataProcess();      //接收数据处理函数
	//测试图片显示函数
	void showVoltagePicture();
	void InitWidget();    //集中设置部件的尺寸和位置

	void ShowGIF(int GIFnum,int SWMode);


	void ShowMask();

	//电池的电压与电量数值转化函数
	int Voltage2Volume(unsigned char voltage,int cellNum);
	

	BOOL PauseRec;
	BOOL CodecSet;
	BOOL RecOK;
	BOOL IsRecord;
    BOOL bCallback ;
	BOOL bDevIsConnect;     //标记采集卡设备已经连接
	BOOL bIsCharging;       //标记正在充电


	unsigned char ReadyClosePort;    //准备关闭串口和采集卡
							//0默认，1准备关闭，2立马关闭。
	image_handle	m_fileImg;
	image_handle	m_bufImg;
	DeviceControl m_DeviceControl;
	

	

	CChannelWnd *pvw;   //预览窗口

	CChannelWnd *pvwMask;//预览窗口的掩饰层
	

	ReceiveDataType ReceiveData; //串口接收数据帧
	unsigned char SendData[SEND_DATA_LEN];   //串口发送数据帧

	CyQueue ReceiveQueue;  //串口接收队列

	SYSTEM_POWER_STATUS SystemPowerStatus;  //pad电量信息

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGDEMODLG_H__AAA927C3_2E40_4508_95B9_65DB11951266__INCLUDED_)
