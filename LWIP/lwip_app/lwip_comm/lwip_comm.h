#ifndef _LWIP_COMM_H
#define _LWIP_COMM_H 
#include "lan8720.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ���������ɣ��������������κ���;
//ALIENTEK STM32F746������
//lwipͨ������ ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2016/1/1
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) �������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//*******************************************************************************
//�޸���Ϣ
//��
////////////////////////////////////////////////////////////////////////////////// 	   
 
#define LWIP_MAX_DHCP_TRIES		4   //DHCP������������Դ���
   
//lwip���ƽṹ��
typedef struct  
{
	uint8_t mac[6];      //MAC��ַ
	uint8_t remoteip[4];	//Զ������IP��ַ
	uint8_t ip[4];       //����IP��ַ
	uint8_t netmask[4]; 	//��������
	uint8_t gateway[4]; 	//Ĭ�����ص�IP��ַ
	
	__IO uint8_t dhcpstatus;	//dhcp״̬
					//0,δ��ȡDHCP��ַ;
					//1,����DHCP��ȡ״̬
					//2,�ɹ���ȡDHCP��ַ
					//0XFF,��ȡʧ��.
}__lwip_dev;
extern __lwip_dev lwipdev;	//lwip���ƽṹ��

void lwip_pkt_handle(void);
void lwip_periodic_handle(void);
	
void lwip_comm_default_ip_set(__lwip_dev *lwipx);
uint8_t lwip_comm_mem_malloc(void);
void lwip_comm_mem_free(void);
uint8_t lwip_comm_init(void);
void lwip_dhcp_process_handle(void);

#endif












