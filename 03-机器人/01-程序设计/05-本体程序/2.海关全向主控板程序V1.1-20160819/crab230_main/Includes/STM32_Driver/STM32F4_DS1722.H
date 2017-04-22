/******************** (C) COPYRIGHT 2010 www.armjishu.com ********************
* File Name          : spi_flash.h
* Author             : www.armjishu.com
* Version            : V1.0
* Library            : Using STM32F10X_STDPERIPH_VERSION V3.3.0
* Date               : 10/16/2010
* Description        : Header for spi_flash.c file.
*******************************************************************************/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DS1722_H
#define __DS1722_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "misc.h" 

#ifndef		DS1722_GLOBALS    
	#define		DS1722_EXT    
#else 
	#define		DS1722_EXT	extern
#endif 
//PA3~~7:  SS1,SS2 SCK MISO mosi

#define DS1722_SPI                           SPI1
#define DS1722_SPI_CLK                       RCC_APB2Periph_SPI1
#define DS1722_SPI_SCK_PIN                   GPIO_Pin_5                  /* PA.05 */
#define DS1722_SPI_SCK_GPIO_PORT             GPIOA                       /* GPIOA */
#define DS1722_SPI_SCK_GPIO_CLK              RCC_APB2Periph_GPIOA
#define DS1722_SPI_MISO_PIN                  GPIO_Pin_6                  /* PA.06 */
#define DS1722_SPI_MISO_GPIO_PORT            GPIOA                       /* GPIOA */
#define DS1722_SPI_MISO_GPIO_CLK             RCC_APB2Periph_GPIOA
#define DS1722_SPI_MOSI_PIN                  GPIO_Pin_7                  /* PA.07 */
#define DS1722_SPI_MOSI_GPIO_PORT            GPIOA                       /* GPIOA */
#define DS1722_SPI_MOSI_GPIO_CLK             RCC_APB2Periph_GPIOA
#define DS1722_SPI_CS_PIN                    GPIO_Pin_4                  /* PB.09 */
#define DS1722_SPI_CS_GPIO_PORT              GPIOA                       /* GPIOD */
#define DS1722_SPI_CS_GPIO_CLK               RCC_APB2Periph_GPIOA

/* Exported macro ------------------------------------------------------------*/
/* Select SPI FLASH: Chip Select pin low   DS1722为高有效  */
#define DS1722_SPI_CS_HIGH()       GPIO_ResetBits(DS1722_SPI_CS_GPIO_PORT, DS1722_SPI_CS_PIN)
/* Deselect SPI FLASH: Chip Select pin high */
#define DS1722_SPI_CS_LOW()        GPIO_SetBits(DS1722_SPI_CS_GPIO_PORT, DS1722_SPI_CS_PIN)


#define ENDS1722   GPIO_SetBits(GPIOA, GPIO_Pin_4)
#define DISDS1722  GPIO_ResetBits(GPIOA, GPIO_Pin_4)

#define DS1722INITWORD 0x80E8//初始化Ds1722为12位


#define GetTemperature()   		(str_ds1722_spi_data.temperature >> 8)


typedef struct Sds1722//定义数据缓冲区结构体
{  
  uint8_t over_send_flag;
  uint16_t state;                   //初始化状态寄存器
  int16_t temperature;              //温度值初始化
}DS1722_SPI_STRUCT;		

extern	DS1722_SPI_STRUCT	str_ds1722_spi_data;
 
  
extern void SpiInit(void);
extern void Ds1722GpioInit(void);
extern void Ds1722Init(void);
extern void SpiSendByte(uint8_t dat);
extern int16_t SPI_SendHalfWord(int16_t HalfWord);
extern void StartTranDs1722(void);
extern uint8_t FinishTranDs1722(void);
extern void InterruptDealDs1722(int16_t chr);
extern void SPI1_IRQHandler(void);

extern void Ds1722Work(void);
#endif /* __SPI_FLASH_H */

/******************* (C) COPYRIGHT 2010 www.armjishu.com *****END OF FILE****/
