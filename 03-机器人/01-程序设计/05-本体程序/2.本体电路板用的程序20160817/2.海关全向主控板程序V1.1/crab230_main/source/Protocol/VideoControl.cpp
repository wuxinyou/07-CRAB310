/* 头文件包含 ------------------------------------------------------------------*/
#include "VideoControl.h"


/* 类型定义 --------------------------------------------------------------------*/
/* 宏定义-----------------------------------------------------------------------*/
  
//构造函数
VideoControl::VideoControl(SerialPort * p)
{
	port=p; 
}

//析构函数
VideoControl::~VideoControl()
{
	delete port;
} 
 /**
  * 功  能：发送变焦指令
  * 参  数：STOP 0x00;TELE 0x01;WIDE 0x02
  * 返回值：无
  * 
  */
void VideoControl::sendVideoCommand(uint8_t data1)				 
{
	uint8_t buf[2] = {0};
	uint8_t i=0;

	buf[i++] = 0x00; 
	buf[i++] = data1;   
	
	port->write(buf,i); 
}

 /**
  * 功  能：发送画面切换指令
  * 参  数：0x81,第一画面；0x82,第二画面；0x9b，上下画面分割。
  * 返回值：无
  * 
  */
void VideoControl::sendVideoChannel(uint8_t cmd)				 
{
	sendVideoCommand(cmd); 
} 







