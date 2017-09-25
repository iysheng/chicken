#ifndef __LAN8720_H
#define __LAN8720_H
#include "stm32f7xx_hal_conf.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F746������
//LAN8720��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2016/1/1
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	
extern ETH_HandleTypeDef ETH_Handler;               //��̫�����
extern uint8_t Rx_Buff[ETH_RXBUFNB][ETH_RX_BUF_SIZE]; 					//��̫���ײ���������buffersָ��
extern uint8_t Tx_Buff[ETH_TXBUFNB][ETH_TX_BUF_SIZE]; 					//��̫���ײ���������buffersָ��
extern ETH_DMADescTypeDef DMARxDscrTab[ETH_RXBUFNB];	//��̫��DMA�������������ݽṹ��ָ��
extern ETH_DMADescTypeDef DMATxDscrTab[ETH_TXBUFNB];	//��̫��DMA�������������ݽṹ��ָ��
extern ETH_DMADescTypeDef  *DMATxDescToSet;			//DMA����������׷��ָ��
extern ETH_DMADescTypeDef  *DMARxDescToGet; 		//DMA����������׷��ָ�� 
 

uint8_t LAN8720_Init(void);
uint32_t LAN8720_ReadPHY(uint16_t reg);
void LAN8720_WritePHY(uint16_t reg,uint16_t value);
uint8_t LAN8720_Get_Speed(void);
uint8_t ETH_MACDMA_Config(void);
uint8_t ETH_Mem_Malloc(void);
void ETH_Mem_Free(void);
uint32_t  ETH_GetRxPktSize(ETH_DMADescTypeDef *DMARxDesc);
#define NET_RST(n)   (n?HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_RESET))   //LCD����PD13
#endif
