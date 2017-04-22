/* 头文件包含 ------------------------------------------------------------------*/
#include "Mpu6050Control.h"

/* 类型定义 --------------------------------------------------------------------*/

/* 宏定义-----------------------------------------------------------------------*/ 
//数据帧长度宏
#define SEND_BUF_LEN 						10
#define RECIVE_BUF_LEN 					32 
 

//构造函数
Mpu6050Control::Mpu6050Control(SerialPort * p1)
{
	port=p1;  
	reciveChin=new RingChain(RECIVE_BUF_LEN); 
	reciveBuf=new uint8_t[RECIVE_BUF_LEN]; 
	for(int i=0;i<RECIVE_BUF_LEN;i++)
	{
		reciveBuf[i]=0;
	}	
	imudata = new imu_data;
}


//析构函数
Mpu6050Control::~Mpu6050Control()
{
	delete reciveChin;
	delete [] sendBuf;
	delete [] reciveBuf;
	delete imudata;
}
 

/**
  * 功  能：接收控制终端的数据
  * 参  数：接收数据的串口
  * 返回值：
			true:成功接收一帧
			false:没有接收到一帧数据
  */
//88 AF 1C 00 1D FF 63 10 11 00 00 00 00 00 00 00 00 00 00 00 00 FF E4 FF 05 06 F1 FF 00 FF FF CF 
bool Mpu6050Control::imureciveData(SerialPort *port)
{
	uint8_t checkSum=0;
	bool readFlag=false;
  //接收串行数据
	while (port->readAllow()&&(readFlag==false))
	{
		reciveChin->setData(port->getChar());
		reciveChin->next();
		if(reciveChin->getData()==0x88)//检测帧头	
		{	
			checkSum+=0x88;
			reciveChin->next();
			if(reciveChin->getData()==0xAF)//检测帧头	
			{
				for(int i=0;i<(RECIVE_BUF_LEN-3);i++)
				{
					 checkSum+=reciveChin->getData();
					 reciveChin->next();
				}
				reciveChin->next();
				if(checkSum==reciveChin->getData())//校验和正确
				{
					//将数据存入数组
					for(int i=0;i<RECIVE_BUF_LEN;i++)
					{
						 reciveChin->next();
						 reciveBuf[i]=reciveChin->getData();
					}
					readFlag=true;
				}
				reciveChin->next(); 
			}
		  else
			{
				 reciveChin->previous();//跳至上个节点	
			}			
		 	checkSum=0;
		}	
	}
	return 	readFlag;
}
 

/**
  * 功  能：处理接收到的数据
  * 参  数：接收数据的串口
  * 返回值：
			true:成功接收一帧
			false:没有接收到一帧数据
  */
bool Mpu6050Control::dealrecData()
{
	uint8_t i=0;
	float acc[3],angular[3],angle[3],tempature;
	bool tempFlag = false;  
	
	tempFlag = imureciveData(port);
	if(tempFlag==true)
	{  
// 		switch(reciveBuf[1])
// 		{
// 			 case 0x51: //标识这个包是加速度包
// 					acc[0] 			= ((short)(reciveBuf[3]<<8 | reciveBuf[2]))/32768.0*16;      //X轴加速度
// 					acc[1] 			= ((short)(reciveBuf[5]<<8 | reciveBuf[4]))/32768.0*16;      //Y轴加速度
// 					acc[2] 			= ((short)(reciveBuf[7]<<8 | reciveBuf[6]))/32768.0*16;      //Z轴加速度
// 					tempature   = ((short)(reciveBuf[9]<<8 | reciveBuf[8]))/340.0+36.25;      //温度
// 					break;
// 			 case 0x52: //标识这个包是角速度包
// 					angular[0] 	= ((short)(reciveBuf[3]<<8| reciveBuf[2]))/32768.0*2000;      //X轴角速度
// 					angular[1] 	= ((short)(reciveBuf[5]<<8| reciveBuf[4]))/32768.0*2000;      //Y轴角速度
// 					angular[2] 	= ((short)(reciveBuf[7]<<8| reciveBuf[6]))/32768.0*2000;      //Z轴角速度
// 					tempature   = ((short)(reciveBuf[9]<<8| reciveBuf[8]))/340.0+36.25;      	//温度
// 					break;
// 			 case 0x53: //标识这个包是角度包
// 					angle[0] 		= ((short)(reciveBuf[3]<<8| reciveBuf[2]))/32768.0*180;   		//X轴滚转角（x 轴）
// 					angle[1] 		= ((short)(reciveBuf[5]<<8| reciveBuf[4]))/32768.0*180;   		//Y轴俯仰角（y 轴）
// 					angle[2] 		= ((short)(reciveBuf[7]<<8| reciveBuf[6]))/32768.0*180;   		//Z轴偏航角（z 轴）
// 					tempature   = ((short)(reciveBuf[9]<<8| reciveBuf[8]))/340.0+36.25;   		//温度 
// 					break;
// 			 default:  break;
// 		} 
//帧头：0x88,0xAF;长度：LEN；
		i = 3;
    imudata->accl[0] = (reciveBuf[i++]<<8) + reciveBuf[i++];
    imudata->accl[1] = (reciveBuf[i++]<<8) + reciveBuf[i++];
    imudata->accl[2] = (reciveBuf[i++]<<8) + reciveBuf[i++];

    imudata->gyro[0] = (reciveBuf[i++]<<8) + reciveBuf[i++];
    imudata->gyro[1] = (reciveBuf[i++]<<8) + reciveBuf[i++];
    imudata->gyro[2] = (reciveBuf[i++]<<8) + reciveBuf[i++];
    
    imudata->mag[0] = (reciveBuf[i++]<<8) + reciveBuf[i++];
    imudata->mag[1] = (reciveBuf[i++]<<8) + reciveBuf[i++];
    imudata->mag[2] = (reciveBuf[i++]<<8) + reciveBuf[i++];
    
    imudata->roll 	= (reciveBuf[i++]<<8) + reciveBuf[i++];
    imudata->pitch 	= (reciveBuf[i++]<<8) + reciveBuf[i++];
    imudata->yaw 		= (reciveBuf[i++]<<8) + reciveBuf[i++];
    
    imudata->presure =  (reciveBuf[i++]<<0)+ (reciveBuf[i++]<<8)+ (reciveBuf[i++]<<16)+(reciveBuf[i++]<<24);
// 		GPIO_WriteBit(GPIOE, GPIO_Pin_13, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOE, GPIO_Pin_13)));
	}
	angleX = (int16_t)imudata->yaw; 
	return tempFlag;
}

 