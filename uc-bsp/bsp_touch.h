/*
 * bsp_touch.h
 *
 *  Created on: 2017��5��15��
 *      Author: iysheng
 */

#ifndef BSP_TOUCH_H_
#define BSP_TOUCH_H_

#define TP_PRES_DOWN 0x80  //����������
#define TP_CATH_PRES 0x40  //�а���������
#define CT_MAX_TOUCH  5    //������֧�ֵĵ���,�̶�Ϊ5��

#define READ_TIMES 5 	//��ȡ����
#define LOST_VAL 1	  	//����ֵ

#define ERR_RANGE 50 //��Χ

#define FT_TP1_REG 				0X03	  	//��һ�����������ݵ�ַ
#define FT_TP2_REG 				0X09		//�ڶ������������ݵ�ַ
#define FT_TP3_REG 				0X0F		//���������������ݵ�ַ
#define FT_TP4_REG 				0X15		//���ĸ����������ݵ�ַ
#define FT_TP5_REG 				0X1B		//��������������ݵ�ַ

//I2C��д����
#define FT_CMD_WR 				0X70    	//д����
#define FT_CMD_RD 				0X71		//������

//FT5206 ���ּĴ�������
#define FT_DEVIDE_MODE 			0x00   		//FT5206ģʽ���ƼĴ���
#define FT_REG_NUM_FINGER       0x02		//����״̬�Ĵ���

#define	FT_ID_G_LIB_VERSION		0xA1		//�汾
#define FT_ID_G_MODE 			0xA4   		//FT5206�ж�ģʽ���ƼĴ���
#define FT_ID_G_THGROUP			0x80   		//������Чֵ���üĴ���
#define FT_ID_G_PERIODACTIVE	0x88   		//����״̬�������üĴ���

//������оƬ��������
#define PEN         HAL_GPIO_ReadPin(GPIOH,GPIO_PIN_7) //T_PEN
#define DOUT        HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_3) //T_MISO

//IO��������
#define FT_RST(n)  (n?HAL_GPIO_WritePin(GPIOI,GPIO_PIN_8,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOI,GPIO_PIN_8,GPIO_PIN_RESET))//FT5206��λ����
#define FT_INT      HAL_GPIO_ReadPin(GPIOH,GPIO_PIN_7)  //FT5206�ж�����
//IO��������
#define CT_SDA_IN()  {GPIOI->MODER&=~(3<<(3*2));GPIOI->MODER|=0<<3*2;}	//PI3����ģʽ
#define CT_SDA_OUT() {GPIOI->MODER&=~(3<<(3*2));GPIOI->MODER|=1<<3*2;} 	//PI3���ģʽ
//IO��������
#define CT_IIC_SCL(n) (n?HAL_GPIO_WritePin(GPIOH,GPIO_PIN_6,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOH,GPIO_PIN_6,GPIO_PIN_RESET))//SCL
#define CT_IIC_SDA(n) (n?HAL_GPIO_WritePin(GPIOI,GPIO_PIN_3,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOI,GPIO_PIN_3,GPIO_PIN_RESET))//SDA
#define CT_READ_SDA   HAL_GPIO_ReadPin(GPIOI,GPIO_PIN_3)//����SDA



typedef struct
{
	uint8_t (*init)(void);			//��ʼ��������������
	uint8_t (*scan)(void);				//ɨ�败����.0,��Ļɨ��;1,��������;
	uint16_t x[CT_MAX_TOUCH]; 		//��ǰ����
	uint16_t y[CT_MAX_TOUCH];		//�����������5������
    uint8_t sta;
}_touch_dev;


uint8_t FT5206_Init(void);
void CT_Delay(void);
void CT_IIC_Init(void);
void CT_IIC_Start(void);
uint8_t CT_IIC_Wait_Ack(void);
void CT_IIC_Stop(void);
uint8_t CT_IIC_Read_Byte(unsigned char ack);
void CT_IIC_Send_Byte(uint8_t txd);
uint8_t FT5206_WR_Reg(uint16_t reg,uint8_t *buf,uint8_t len);
void FT5206_RD_Reg(uint16_t reg,uint8_t *buf,uint8_t len);
uint8_t FT5206_Scan(void);
void CT_IIC_Ack(void);
void CT_IIC_NAck(void);
void delay_ms(uint32_t times);
void delay_us(uint32_t times);

#endif /* BSP_TOUCH_H_ */
