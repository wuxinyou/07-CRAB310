 
/* 定义防止递归包含的控制宏----------------------------------------------------*/
#ifndef _VIDEO_CONTROL_H
#define _VIDEO_CONTROL_H

/* 头文件包含 ------------------------------------------------------------------*/
#include "BaseControl.h"     //协议的基类
 
 
#define VIDEO_1  0x81
#define VIDEO_2  0x82
#define VIDEO_12 0x9b

class VideoControl  
{
public:
	VideoControl(SerialPort * p);
	virtual ~VideoControl(); 
	void sendVideoCommand(uint8_t );
	void sendVideoChannel(uint8_t );	
 
private:
	SerialPort *port; 
};
#endif   
