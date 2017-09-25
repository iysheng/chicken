#include "pcf8574.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F7������
//PCF8574��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2016/1/13
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	
//IIC��ʼ��
void IIC_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;

    __HAL_RCC_GPIOH_CLK_ENABLE();   //ʹ��GPIOHʱ��

    //PH4,5��ʼ������
    GPIO_Initure.Pin=GPIO_PIN_4|GPIO_PIN_5;
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //�������
    GPIO_Initure.Pull=GPIO_PULLUP;          //����
    GPIO_Initure.Speed=GPIO_SPEED_FAST;     //����
    HAL_GPIO_Init(GPIOH,&GPIO_Initure);

    IIC_SDA(1);
    IIC_SCL(1);
}

//����IIC��ʼ�ź�
void IIC_Start(void)
{
	SDA_OUT();     //sda�����
	IIC_SDA(1);
	IIC_SCL(1);
	delay_us(4);
 	IIC_SDA(0);//START:when CLK is high,DATA change form high to low
	delay_us(4);
	IIC_SCL(0);//ǯסI2C���ߣ�׼�����ͻ��������
}
//����IICֹͣ�ź�
void IIC_Stop(void)
{
	SDA_OUT();//sda�����
	IIC_SCL(0);
	IIC_SDA(0);//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	IIC_SCL(1);
	IIC_SDA(1);//����I2C���߽����ź�
	delay_us(4);
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
uint8_t IIC_Wait_Ack(void)
{
	uint8_t ucErrTime=0;
	SDA_IN();      //SDA����Ϊ����
	IIC_SDA(1);delay_us(1);
	IIC_SCL(1);delay_us(1);
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL(0);//ʱ�����0
	return 0;
}
//����ACKӦ��
void IIC_Ack(void)
{
	IIC_SCL(0);
	SDA_OUT();
	IIC_SDA(0);
	delay_us(2);
	IIC_SCL(1);
	delay_us(2);
	IIC_SCL(0);
}
//������ACKӦ��
void IIC_NAck(void)
{
	IIC_SCL(0);
	SDA_OUT();
	IIC_SDA(1);
	delay_us(2);
	IIC_SCL(1);
	delay_us(2);
	IIC_SCL(0);
}
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��
void IIC_Send_Byte(uint8_t txd)
{
    uint8_t t;
	SDA_OUT();
    IIC_SCL(0);//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {
        IIC_SDA((txd&0x80)>>7);
        txd<<=1;
		delay_us(2);   //��TEA5767��������ʱ���Ǳ����
		IIC_SCL(1);
		delay_us(2);
		IIC_SCL(0);
		delay_us(2);
    }
}
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK
uint8_t IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA����Ϊ����
    for(i=0;i<8;i++ )
	{
        IIC_SCL(0);
        delay_us(2);
		IIC_SCL(1);
        receive<<=1;
        if(READ_SDA)receive++;
		delay_us(1);
    }
    if (!ack)
        IIC_NAck();//����nACK
    else
        IIC_Ack(); //����ACK
    return receive;
}
//��ʼ��PCF8574
uint8_t PCF8574_Init(void)
{
    uint8_t temp=0;
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_GPIOB_CLK_ENABLE();           //ʹ��GPIOBʱ��
	
    GPIO_Initure.Pin=GPIO_PIN_12;           //PB12
    GPIO_Initure.Mode=GPIO_MODE_INPUT;      //����
    GPIO_Initure.Pull=GPIO_PULLUP;          //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //����
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);     //��ʼ��
    IIC_Init();					            //IIC��ʼ�� 	
	//���PCF8574�Ƿ���λ
    IIC_Start();    	 	   
	IIC_Send_Byte(PCF8574_ADDR);            //д��ַ			   
	temp=IIC_Wait_Ack();		            //�ȴ�Ӧ��,ͨ���ж��Ƿ���ACKӦ��,���ж�PCF8574��״̬
    IIC_Stop();					            //����һ��ֹͣ����
    PCF8574_WriteOneByte(0XFF);	            //Ĭ�����������IO����ߵ�ƽ
	return temp;
}

//��ȡPCF8574��8λIOֵ
//����ֵ:����������
uint8_t PCF8574_ReadOneByte(void)
{				  
	uint8_t temp=0;
    IIC_Start();    	 	   
	IIC_Send_Byte(PCF8574_ADDR|0X01);   //�������ģʽ			   
	IIC_Wait_Ack();	 
    temp=IIC_Read_Byte(0);		   
    IIC_Stop();							//����һ��ֹͣ����	    
	return temp;
}
//��PCF8574д��8λIOֵ  
//DataToWrite:Ҫд�������
void PCF8574_WriteOneByte(uint8_t DataToWrite)
{				   	  	    																 
    IIC_Start();  
    IIC_Send_Byte(PCF8574_ADDR|0X00);   //����������ַ0X40,д���� 	 
	IIC_Wait_Ack();	    										  		   
	IIC_Send_Byte(DataToWrite);    	 	//�����ֽ�							   
	IIC_Wait_Ack();      
    IIC_Stop();							//����һ��ֹͣ���� 
	delay_ms(10);	 
}

//����PCF8574ĳ��IO�ĸߵ͵�ƽ
//bit:Ҫ���õ�IO���,0~7
//sta:IO��״̬;0��1
void PCF8574_WriteBit(uint8_t bit,uint8_t sta)
{
    uint8_t data;
    data=PCF8574_ReadOneByte(); //�ȶ���ԭ��������
    if(sta==0)data&=~(1<<bit);     
    else data|=1<<bit;
    PCF8574_WriteOneByte(data); //д���µ�����
}

//��ȡPCF8574��ĳ��IO��ֵ
//bit��Ҫ��ȡ��IO���,0~7
//����ֵ:��IO��ֵ,0��1
uint8_t PCF8574_ReadBit(uint8_t bit)
{
    uint8_t data;
    data=PCF8574_ReadOneByte(); //�ȶ�ȡ���8λIO��ֵ 
    if(data&(1<<bit))return 1;
    else return 0;   
}  
    
