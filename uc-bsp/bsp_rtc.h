/*
 * bsp_rtc.h
 *
 *  Created on: 2017��9��23��
 *      Author: iysheng
 */

#ifndef UC_BSP_BSP_RTC_H_
#define UC_BSP_BSP_RTC_H_

//////////////////////////////////////////////////////////////////////////////////
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F7������
//RTC��������
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2016/1/13
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved
//////////////////////////////////////////////////////////////////////////////////

extern RTC_HandleTypeDef RTC_Handler;  //RTC���

uint8_t RTC_Init(void);              //RTC��ʼ��
HAL_StatusTypeDef RTC_Set_Time(uint8_t hour,uint8_t min,uint8_t sec,uint8_t ampm);      //RTCʱ������
HAL_StatusTypeDef RTC_Set_Date(uint8_t year,uint8_t month,uint8_t date,uint8_t week);	//RTC��������
void RTC_Set_AlarmA(uint8_t week,uint8_t hour,uint8_t min,uint8_t sec); //��������ʱ��(����������,24Сʱ��)
void RTC_Set_WakeUp(uint32_t wksel,uint16_t cnt);             //�����Ի��Ѷ�ʱ������

#endif /* UC_BSP_BSP_RTC_H_ */
