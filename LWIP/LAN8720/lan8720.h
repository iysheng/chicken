#ifndef __LAN8720_H
#define __LAN8720_H
#include "stm32f7xx_hal_conf.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F746开发板
//LAN8720驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2016/1/1
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	
extern ETH_HandleTypeDef ETH_Handler;               //以太网句柄
extern uint8_t Rx_Buff[ETH_RXBUFNB][ETH_RX_BUF_SIZE]; 					//以太网底层驱动接收buffers指针
extern uint8_t Tx_Buff[ETH_TXBUFNB][ETH_TX_BUF_SIZE]; 					//以太网底层驱动发送buffers指针
extern ETH_DMADescTypeDef DMARxDscrTab[ETH_RXBUFNB];	//以太网DMA接收描述符数据结构体指针
extern ETH_DMADescTypeDef DMATxDscrTab[ETH_TXBUFNB];	//以太网DMA发送描述符数据结构体指针
extern ETH_DMADescTypeDef  *DMATxDescToSet;			//DMA发送描述符追踪指针
extern ETH_DMADescTypeDef  *DMARxDescToGet; 		//DMA接收描述符追踪指针 
 

uint8_t LAN8720_Init(void);
uint32_t LAN8720_ReadPHY(uint16_t reg);
void LAN8720_WritePHY(uint16_t reg,uint16_t value);
uint8_t LAN8720_Get_Speed(void);
uint8_t ETH_MACDMA_Config(void);
uint8_t ETH_Mem_Malloc(void);
void ETH_Mem_Free(void);
uint32_t  ETH_GetRxPktSize(ETH_DMADescTypeDef *DMARxDesc);
#define NET_RST(n)   (n?HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_RESET))   //LCD背光PD13
#endif
