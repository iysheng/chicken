/*
 * bsp_sdram.c
 *
 *  Created on: 2017��5��15��
 *      Author: iysheng
 */

#include "main.h"

SDRAM_HandleTypeDef ISDRAM;
FMC_SDRAM_TimingTypeDef ISDRAM_Timing;

void SDRAM_init(void)
{
  ISDRAM.Instance=FMC_SDRAM_DEVICE;
  ISDRAM.Init.SDBank=FMC_SDRAM_BANK1;
  ISDRAM.Init.ColumnBitsNumber=FMC_SDRAM_COLUMN_BITS_NUM_9;
  ISDRAM.Init.RowBitsNumber=FMC_SDRAM_ROW_BITS_NUM_13;
  ISDRAM.Init.MemoryDataWidth=FMC_SDRAM_MEM_BUS_WIDTH_16;
  ISDRAM.Init.InternalBankNumber=FMC_SDRAM_INTERN_BANKS_NUM_4;
  ISDRAM.Init.CASLatency=FMC_SDRAM_CAS_LATENCY_3;
  ISDRAM.Init.WriteProtection=FMC_SDRAM_WRITE_PROTECTION_DISABLE;
  ISDRAM.Init.SDClockPeriod=FMC_SDRAM_CLOCK_PERIOD_2;
  ISDRAM.Init.ReadBurst=FMC_SDRAM_RBURST_ENABLE;
  ISDRAM.Init.ReadPipeDelay=FMC_SDRAM_RPIPE_DELAY_1;
  ISDRAM_Timing.LoadToActiveDelay=2;
  ISDRAM_Timing.ExitSelfRefreshDelay=8;
  ISDRAM_Timing.SelfRefreshTime=6;
  ISDRAM_Timing.RowCycleDelay=6;
  ISDRAM_Timing.WriteRecoveryTime=2;
  ISDRAM_Timing.RPDelay=2;
  ISDRAM_Timing.RCDDelay=2;
  HAL_SDRAM_Init(&ISDRAM,&ISDRAM_Timing);
  SDRAM_Initialization_Sequence(&ISDRAM);
}

//����SDRAM��ʼ������
void SDRAM_Initialization_Sequence(SDRAM_HandleTypeDef *hsdram)
{
    uint32_t temp=0;
    //SDRAM��������ʼ������Ժ���Ҫ��������˳���ʼ��SDRAM
    SDRAM_Send_Cmd(0,FMC_SDRAM_CMD_CLK_ENABLE,1,0); //ʱ������ʹ��
    //HAL_Delay(1);                                  //������ʱ1MS
    delay_us(1000);
    SDRAM_Send_Cmd(0,FMC_SDRAM_CMD_PALL,1,0);       //�����д洢��Ԥ���
    SDRAM_Send_Cmd(0,FMC_SDRAM_CMD_AUTOREFRESH_MODE,8,0);//������ˢ�´���
    //����ģʽ�Ĵ���,SDRAM��bit0~bit2Ϊָ��ͻ�����ʵĳ��ȣ�
	//bit3Ϊָ��ͻ�����ʵ����ͣ�bit4~bit6ΪCASֵ��bit7��bit8Ϊ����ģʽ
	//bit9Ϊָ����дͻ��ģʽ��bit10��bit11λ����λ
	temp=(uint32_t)SDRAM_MODEREG_BURST_LENGTH_1          |	//����ͻ������:1(������1/2/4/8)
              SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL   |	//����ͻ������:����(����������/����)
              SDRAM_MODEREG_CAS_LATENCY_3           |	//����CASֵ:3(������2/3)
              SDRAM_MODEREG_OPERATING_MODE_STANDARD |   //���ò���ģʽ:0,��׼ģʽ
              SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;     //����ͻ��дģʽ:1,�������
    SDRAM_Send_Cmd(0,FMC_SDRAM_CMD_LOAD_MODE,1,temp);   //����SDRAM��ģʽ�Ĵ���
    //ˢ��Ƶ�ʼ�����(��SDCLKƵ�ʼ���),���㷽��:
	//COUNT=SDRAMˢ������/����-20=SDRAMˢ������(us)*SDCLKƵ��(Mhz)/����
    //����ʹ�õ�SDRAMˢ������Ϊ64ms,SDCLK=216/2=108Mhz,����Ϊ8192(2^13).
	//����,COUNT=64*1000*108/8192-20=823
	HAL_SDRAM_ProgramRefreshRate(&ISDRAM,823);
}

void HAL_SDRAM_MspInit(SDRAM_HandleTypeDef *hsdram)
{
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_FMC_CLK_ENABLE();                 //ʹ��FMCʱ��
    __HAL_RCC_GPIOC_CLK_ENABLE();               //ʹ��GPIOCʱ��
    __HAL_RCC_GPIOD_CLK_ENABLE();               //ʹ��GPIODʱ��
    __HAL_RCC_GPIOE_CLK_ENABLE();               //ʹ��GPIOEʱ��
    __HAL_RCC_GPIOF_CLK_ENABLE();               //ʹ��GPIOFʱ��
    __HAL_RCC_GPIOG_CLK_ENABLE();               //ʹ��GPIOGʱ��

    //��ʼ��PC0,2,3
    GPIO_Initure.Pin=GPIO_PIN_0|GPIO_PIN_2|GPIO_PIN_3;
    GPIO_Initure.Mode=GPIO_MODE_AF_PP;          //���츴��
    GPIO_Initure.Pull=GPIO_PULLUP;              //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;         //����
    GPIO_Initure.Alternate=GPIO_AF12_FMC;       //����ΪFMC
    HAL_GPIO_Init(GPIOC,&GPIO_Initure);         //��ʼ��

    GPIO_Initure.Pin=GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_14|GPIO_PIN_15;
    HAL_GPIO_Init(GPIOD,&GPIO_Initure); //��ʼ��PD0,1,8,9,10,14,15

    GPIO_Initure.Pin=GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
    HAL_GPIO_Init(GPIOE,&GPIO_Initure); //��ʼ��PE0,1,7,8,9,10,11,12,13,14,15

    GPIO_Initure.Pin=GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
    HAL_GPIO_Init(GPIOF,&GPIO_Initure); //��ʼ��PF0,1,2,3,4,5,11,12,13,14,15

    GPIO_Initure.Pin=GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_8|GPIO_PIN_15;
    HAL_GPIO_Init(GPIOG,&GPIO_Initure);	//��ʼ��PG0,1,2,4,5,8,15

}

uint8_t SDRAM_Send_Cmd(uint8_t bankx,uint8_t cmd,uint8_t refresh,uint16_t regval)
{
    uint32_t target_bank=0;
    FMC_SDRAM_CommandTypeDef Command;

    if(bankx==0) target_bank=FMC_SDRAM_CMD_TARGET_BANK1;
    else if(bankx==1) target_bank=FMC_SDRAM_CMD_TARGET_BANK2;
    Command.CommandMode=cmd;                //����
    Command.CommandTarget=target_bank;      //Ŀ��SDRAM�洢����
    Command.AutoRefreshNumber=refresh;      //��ˢ�´���
    Command.ModeRegisterDefinition=regval;  //Ҫд��ģʽ�Ĵ�����ֵ
    if(HAL_SDRAM_SendCommand(&ISDRAM,&Command,0X1000)==HAL_OK) //��SDRAM��������
    {
        return 0;
    }
    else return 1;
}

void FMC_SDRAM_WriteBuffer(uint8_t *pBuffer,uint32_t WriteAddr,uint32_t n)
{
	for(;n!=0;n--)
	{
		*(uint8_t*)(Bank5_SDRAM_ADDR+WriteAddr)=*pBuffer;
		WriteAddr++;
		pBuffer++;
	}
}

void FMC_SDRAM_ReadBuffer(uint8_t *pBuffer,uint32_t ReadAddr,uint32_t n)
{
	for(;n!=0;n--)
	{
		*pBuffer++=*(uint8_t*)(Bank5_SDRAM_ADDR+ReadAddr);
		ReadAddr++;
	}
}
