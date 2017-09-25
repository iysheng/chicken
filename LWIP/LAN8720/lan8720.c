#include "lan8720.h"
#include "lwip_comm.h"
#include "malloc.h"
#include "string.h"
#include "main.h"
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

ETH_HandleTypeDef ETH_Handler;      //��̫�����

//ETH_DMADescTypeDef *DMARxDscrTab;	//��̫��DMA�������������ݽṹ��ָ��
//ETH_DMADescTypeDef *DMATxDscrTab;	//��̫��DMA�������������ݽṹ��ָ��

//uint8_t *Rx_Buff; 					//��̫���ײ���������buffersָ��
//uint8_t *Tx_Buff; 					//��̫���ײ���������buffersָ��
uint8_t Rx_Buff[ETH_RXBUFNB][ETH_RX_BUF_SIZE]; 		//��̫���ײ���������buffersָ��
uint8_t Tx_Buff[ETH_TXBUFNB][ETH_TX_BUF_SIZE]; 		//��̫���ײ���������buffersָ��
ETH_DMADescTypeDef DMARxDscrTab[ETH_RXBUFNB];	//��̫��DMA�������������ݽṹ��ָ��
ETH_DMADescTypeDef DMATxDscrTab[ETH_TXBUFNB];	//��̫��DMA�������������ݽṹ��ָ��

uint32_t
interrupt_state (void)
{
  int state;
  state = (ETH_Handler.Instance->DMAIER);
  return (uint32_t) state;
}

//LAN8720��ʼ��
//����ֵ:0,�ɹ�;
//    ����,ʧ��
uint8_t
LAN8720_Init (void)
{
  uint8_t macaddress[6];
  uint32_t ret;
  //OSIntEnter();                         //�ر������жϣ���λ���̲��ܱ���ϣ�
  __HAL_RCC_GPIOA_CLK_ENABLE()
  ;
  ETH_RST(0);       //Ӳ����λ
  PCF8574_WriteBit(ETH_RESET_IO,1);       //Ӳ����λ
  delay_ms(100);
  PCF8574_WriteBit(ETH_RESET_IO,0);       //Ӳ����λ
  ETH_RST(1);       //��λ����
  delay_ms(100);
  //OSIntExit();                          //���������ж�

  macaddress[0] = lwipdev.mac[0];
  macaddress[1] = lwipdev.mac[1];
  macaddress[2] = lwipdev.mac[2];
  macaddress[3] = lwipdev.mac[3];
  macaddress[4] = lwipdev.mac[4];
  macaddress[5] = lwipdev.mac[5];

  ETH_Handler.Instance = ETH;
  ETH_Handler.Init.AutoNegotiation = ETH_AUTONEGOTIATION_ENABLE;    //ʹ����Э��ģʽ
  ETH_Handler.Init.Speed = ETH_SPEED_100M;    //�ٶ�100M,�����������Э��ģʽ�������þ���Ч
  ETH_Handler.Init.DuplexMode = ETH_MODE_FULLDUPLEX;   //ȫ˫��ģʽ�������������Э��ģʽ�������þ���Ч
  ETH_Handler.Init.PhyAddress = LAN8720_PHY_ADDRESS;    //LAN8720��ַ
  ETH_Handler.Init.MACAddr = macaddress;            //MAC��ַ
  ETH_Handler.Init.RxMode = ETH_RXINTERRUPT_MODE;   //�жϽ���ģʽ
  ETH_Handler.Init.ChecksumMode = ETH_CHECKSUM_BY_HARDWARE;   //Ӳ��֡У��
  ETH_Handler.Init.MediaInterface = ETH_MEDIA_INTERFACE_RMII;   //RMII�ӿ�
  ret = HAL_ETH_Init (&ETH_Handler); //debug�������޸��ˣ�HAL�����stm32f7xx_hal_eth.c Line215
  if (ret == HAL_OK)
    return 0;   //�ɹ�
  else
    return 1;  //ʧ��
}

//ETH�ײ�������ʱ��ʹ�ܣ���������
//�˺����ᱻHAL_ETH_Init()����
//heth:��̫�����
void
HAL_ETH_MspInit (ETH_HandleTypeDef *heth)
{
  GPIO_InitTypeDef GPIO_Initure;

  __HAL_RCC_ETH_CLK_ENABLE()
  ;             //����ETHʱ��
  __HAL_RCC_GPIOA_CLK_ENABLE()
  ;			//����GPIOAʱ��
  __HAL_RCC_GPIOB_CLK_ENABLE()
  ;			//����GPIOBʱ��
  __HAL_RCC_GPIOC_CLK_ENABLE()
  ;			//����GPIOCʱ��
  __HAL_RCC_GPIOG_CLK_ENABLE()
  ;			//����GPIOGʱ��

  /*������������ RMII�ӿ�
   ETH_MDIO -------------------------> PA2
   ETH_MDC --------------------------> PC1
   ETH_RMII_REF_CLK------------------> PA1
   ETH_RMII_CRS_DV ------------------> PA7
   ETH_RMII_RXD0 --------------------> PC4
   ETH_RMII_RXD1 --------------------> PC5
   ETH_RMII_TX_EN -------------------> PB11
   ETH_RMII_TXD0 --------------------> PG13
   ETH_RMII_TXD1 --------------------> PG14
   ETH_RESET-------------------------> PA8*/

  //PA1,2,7
  GPIO_Initure.Pin = GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_7;
  GPIO_Initure.Mode = GPIO_MODE_AF_PP;          //���츴��
  GPIO_Initure.Pull = GPIO_NOPULL;              //����������
  GPIO_Initure.Speed = GPIO_SPEED_HIGH;         //����
  GPIO_Initure.Alternate = GPIO_AF11_ETH;       //����ΪETH����
  HAL_GPIO_Init (GPIOA, &GPIO_Initure);         //��ʼ��

  //PB11
  GPIO_Initure.Pin = GPIO_PIN_11;               //PB11
  HAL_GPIO_Init (GPIOB, &GPIO_Initure);         //ʼ��

  //PC1,4,5
  GPIO_Initure.Pin = GPIO_PIN_1 | GPIO_PIN_4 | GPIO_PIN_5; //PC1,4,5
  HAL_GPIO_Init (GPIOC, &GPIO_Initure);         //��ʼ��

  //PG13,14
  GPIO_Initure.Pin = GPIO_PIN_13 | GPIO_PIN_14;   //PG13,14
  HAL_GPIO_Init (GPIOG, &GPIO_Initure);         //��ʼ��

  GPIO_Initure.Pin = GPIO_PIN_8;
  GPIO_Initure.Mode = GPIO_MODE_OUTPUT_PP;          //���츴��
  GPIO_Initure.Speed = GPIO_SPEED_HIGH;         //����
  HAL_GPIO_Init (GPIOA, &GPIO_Initure);         //��ʼ��

  HAL_NVIC_SetPriority (ETH_IRQn, 0, 0);         //�����ж����ȼ�Ӧ�ø�һ��
  HAL_NVIC_EnableIRQ (ETH_IRQn);
}

//��ȡPHY�Ĵ���ֵ
uint32_t
LAN8720_ReadPHY (uint16_t reg)
{
  uint32_t regval;
  HAL_ETH_ReadPHYRegister (&ETH_Handler, reg, &regval);
  return regval;
}

//��LAN8720ָ���Ĵ���д��ֵ
//reg:Ҫд��ļĴ���
//value:Ҫд���ֵ
void
LAN8720_WritePHY (uint16_t reg, uint16_t value)
{
  uint32_t temp = value;
  HAL_ETH_ReadPHYRegister (&ETH_Handler, reg, &temp);
}

//�õ�8720���ٶ�ģʽ
//����ֵ:
//001:10M��˫��
//101:10Mȫ˫��
//010:100M��˫��
//110:100Mȫ˫��
//����:����.
uint8_t
LAN8720_Get_Speed (void)
{
  uint8_t speed;
  speed = ((LAN8720_ReadPHY (31) & 0x1C) >> 2); //��LAN8720��31�żĴ����ж�ȡ�����ٶȺ�˫��ģʽ
  return speed;
}

extern void
lwip_pkt_handle (void);		//��lwip_comm.c���涨��

//�жϷ�����
void
ETH_IRQHandler (void)
{
  printf ("get in eth_irqhandler\r\n");
  while (ETH_GetRxPktSize (ETH_Handler.RxDesc))
    {
      printf ("receive data\r\n");
      lwip_pkt_handle ();		//������̫�����ݣ����������ύ��LWIP
    }
  //����жϱ�־λ
  __HAL_ETH_DMA_CLEAR_IT(&ETH_Handler, ETH_DMA_IT_NIS);
  __HAL_ETH_DMA_CLEAR_IT(&ETH_Handler, ETH_DMA_IT_R);

}

//��ȡ���յ���֡����
//DMARxDesc:����DMA������
//����ֵ:���յ���֡����
uint32_t
ETH_GetRxPktSize (ETH_DMADescTypeDef *DMARxDesc)
{
  uint32_t frameLength = 0;
  if (((DMARxDesc->Status & ETH_DMARXDESC_OWN) == (uint32_t) RESET)
      && ((DMARxDesc->Status & ETH_DMARXDESC_ES) == (uint32_t) RESET)
      && ((DMARxDesc->Status & ETH_DMARXDESC_LS) != (uint32_t) RESET))
    {
      frameLength = ((DMARxDesc->Status & ETH_DMARXDESC_FL)
	  >> ETH_DMARXDESC_FRAME_LENGTHSHIFT);
    }
  return frameLength;
}

//ΪETH�ײ����������ڴ�
//����ֵ:0,����
//    ����,ʧ��
uint8_t
ETH_Mem_Malloc (void)
{
  //DMARxDscrTab=mymalloc(SRAMDTCM,ETH_RXBUFNB*sizeof(ETH_DMADescTypeDef));//�����ڴ�
  //DMATxDscrTab=mymalloc(SRAMDTCM,ETH_TXBUFNB*sizeof(ETH_DMADescTypeDef));//�����ڴ�
  //Rx_Buff=mymalloc(SRAMDTCM,ETH_RX_BUF_SIZE*ETH_RXBUFNB);	//�����ڴ�
  //Tx_Buff=mymalloc(SRAMDTCM,ETH_TX_BUF_SIZE*ETH_TXBUFNB);	//�����ڴ�
  if (!(uint32_t) &DMARxDscrTab || !(uint32_t) &DMATxDscrTab
      || !(uint32_t) &Rx_Buff || !(uint32_t) &Tx_Buff)
    {
      ETH_Mem_Free ();
      return 1;	//����ʧ��
    }
  return 0;		//����ɹ�
}

//�ͷ�ETH �ײ�����������ڴ�
void
ETH_Mem_Free (void)
{
  //myfree(SRAMDTCM,DMARxDscrTab);//�ͷ��ڴ�
  //myfree(SRAMDTCM,DMATxDscrTab);//�ͷ��ڴ�
  //myfree(SRAMDTCM,Rx_Buff);		//�ͷ��ڴ�
  //myfree(SRAMDTCM,Tx_Buff);		//�ͷ��ڴ�
}

