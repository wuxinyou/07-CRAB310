/***********************************************************************************************
*文件名		：	DataTypeConvertion.h
*描述		：	数据类型转换
*作者		：	孟浩
*创建日期	：	2016.1.17
*修改日期	：	2016.1.17
*修改人 		：	孟浩
*修改原因	：	整理代码，添加注释
*版本 		：	1.0
*历史版本	：	无
***********************************************************************************************/

#ifndef	_DATATYPECONVERTION_H
#define	_DATATYPECONVERTION_H
#ifdef __cplusplus
	 extern "C" {
	#endif
		 
	#include	"stdint.h"

	typedef union
			{	uint16_t u16_data;
				uint8_t  u8_data[2];
			}	Char2Uint;	// uint8_t转uint16_t
		
	#ifdef __cplusplus
	 }
	#endif
#endif
/*--------------------------------- End of DataTypeConvertion.h -----------------------------*/
