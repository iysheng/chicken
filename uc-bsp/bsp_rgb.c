/*
 * bsp_rgb.c
 *
 *  Created on: 2017��9��8��
 *      Author: iysheng
 */
#include "stm32f7xx.h"
#include "stm32f7xx_hal.h"
#include "bsp_rgb.h"

void
LTDC_Fill (uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint16_t color)
{
  uint32_t timeout = 0;
  __HAL_RCC_DMA2D_CLK_ENABLE()
    ;               //ʹ��DMA2Dʱ��
  DMA2D->CR = 3 << 16;				//�Ĵ������洢��ģʽ
  DMA2D->OPFCCR = LCD_PIXFORMAT;	//������ɫ��ʽ
  DMA2D->OOR = 0;				//������ƫ��
  DMA2D->CR &= ~(1 << 0);				//��ֹͣDMA2D
  DMA2D->OMAR = LCD_BUFFER_ADDR;				//����洢����ַ
  DMA2D->NLR = (ey - sy + 1) | ((ex - sx + 1) << 16);	//�趨�����Ĵ���
  DMA2D->OCOLR = color;				//�趨�����ɫ�Ĵ���
  DMA2D->CR |= 1 << 0;				//����DMA2D
  while ((DMA2D->ISR & (1 << 1)) == 0)	//�ȴ��������
    {
      timeout++;
      if (timeout > 0X1FFFFF)
	break;	//��ʱ�˳�
    }
  DMA2D->IFCR |= 1 << 1;				//���������ɱ�־
}

int
RGB_Init (struct rgb_parameter *mode)
{
  int ret;
  RCC_PeriphCLKInitTypeDef PeriphClkIniture;
  __HAL_RCC_LTDC_CLK_ENABLE()
  ;
  PeriphClkIniture.PeriphClockSelection = (uint32_t) RCC_PERIPHCLK_LTDC;
  PeriphClkIniture.PLLSAI.PLLSAIN = 396;
  PeriphClkIniture.PLLSAI.PLLSAIR = 3;
  PeriphClkIniture.PLLSAIDivR = RCC_PLLSAIDIVR_4;
  ret = HAL_RCCEx_PeriphCLKConfig (&PeriphClkIniture);
  if (HAL_OK != ret)
    goto fail;
  //LTDC_HandleTypeDef LTDC_Handler;	    //LTDC���
  //memset(&LTDC_Handler,0,sizeof(LTDC_Handler));
  LTDC_Handler.Instance = LTDC;
  LTDC_Handler.Init.HSPolarity = LTDC_HSPOLARITY_AL;         //ˮƽͬ������
  LTDC_Handler.Init.VSPolarity = LTDC_VSPOLARITY_AL;         //��ֱͬ������
  LTDC_Handler.Init.DEPolarity = LTDC_DEPOLARITY_AL;         //����ʹ�ܼ���
  LTDC_Handler.Init.PCPolarity = LTDC_PCPOLARITY_IPC;        //����ʱ�Ӽ���
  LTDC_Handler.Init.HorizontalSync = mode->hsw - 1;          //ˮƽͬ�����
  LTDC_Handler.Init.VerticalSync = mode->vsw - 1;            //��ֱͬ�����
  LTDC_Handler.Init.AccumulatedHBP = mode->hsw + mode->hbp - 1; //ˮƽͬ�����ؿ��
  LTDC_Handler.Init.AccumulatedVBP = mode->vsw + mode->vbp - 1; //��ֱͬ�����ظ߶�
  LTDC_Handler.Init.AccumulatedActiveW = mode->hsw + mode->hbp + mode->width
      - 1; //��Ч���
  LTDC_Handler.Init.AccumulatedActiveH = mode->vsw + mode->vbp + mode->height
      - 1; //��Ч�߶�
  LTDC_Handler.Init.TotalWidth = mode->hsw + mode->hbp + mode->width + mode->hfp
      - 1;   //�ܿ��
  LTDC_Handler.Init.TotalHeigh = mode->vsw + mode->vbp + mode->height
      + mode->vfp - 1;  //�ܸ߶�
  LTDC_Handler.Init.Backcolor.Red = 0;           //��Ļ�������ɫ����
  LTDC_Handler.Init.Backcolor.Green = 0;         //��Ļ��������ɫ����
  LTDC_Handler.Init.Backcolor.Blue = 0;          //��Ļ����ɫ��ɫ����
  ret = HAL_LTDC_Init (&LTDC_Handler);
  if (HAL_OK != ret)
    goto fail;

  LTDC_LayerCfgTypeDef pLayerCfg;
  pLayerCfg.WindowX0 = 0;                       //������ʼX����
  pLayerCfg.WindowY0 = 0;                       //������ʼY����
  pLayerCfg.WindowX1 = mode->width;          //������ֹX����
  pLayerCfg.WindowY1 = mode->height;         //������ֹY����
  pLayerCfg.PixelFormat = LCD_PIXFORMAT;		    //���ظ�ʽ
  pLayerCfg.Alpha = 255;			//Alphaֵ���ã�0~255,255Ϊ��ȫ��͸��
  pLayerCfg.Alpha0 = 0;			        //Ĭ��Alphaֵ
  pLayerCfg.BlendingFactor1 = (uint32_t) 6 << 8;    //���ò���ϵ��
  pLayerCfg.BlendingFactor2 = (uint32_t) 7 << 8;	//���ò���ϵ��
  pLayerCfg.FBStartAdress = LCD_BUFFER_ADDR;	        //���ò���ɫ֡������ʼ��ַ
  pLayerCfg.ImageWidth = mode->width;        //������ɫ֡�������Ŀ��
  pLayerCfg.ImageHeight = mode->height;      //������ɫ֡�������ĸ߶�
  pLayerCfg.Backcolor.Red = (uint8_t) (LCD_BACK_COLOR & 0X00FF0000) >> 16; //������ɫ��ɫ����
  pLayerCfg.Backcolor.Green = (uint8_t) (LCD_BACK_COLOR & 0X0000FF00) >> 8; //������ɫ��ɫ����
  pLayerCfg.Backcolor.Blue = (uint8_t) LCD_BACK_COLOR & 0X000000FF;   //������ɫ��ɫ����
  ret = HAL_LTDC_ConfigLayer (&LTDC_Handler, &pLayerCfg, 0);   //������ѡ�еĲ�
  if (HAL_OK != ret)
    goto fail;
  ret = HAL_LTDC_SetWindowPosition (&LTDC_Handler, 0, 0, 0);  //���ô��ڵ�λ��
  if (HAL_OK != ret)
    goto fail;
  ret = HAL_LTDC_SetWindowSize (&LTDC_Handler, mode->width, mode->height, 0); //���ô��ڴ�С
  LCD_LED(1);
  //LTDC_Fill (0, 0, mode->width - 1, mode->height - 1, LCD_BACK_COLOR);  //����
  fail: return ret;
}

void
HAL_LTDC_MspInit (LTDC_HandleTypeDef* hltdc)
{
  GPIO_InitTypeDef GPIO_Initure;

  __HAL_RCC_LTDC_CLK_ENABLE()
  ;                //ʹ��LTDCʱ��
  __HAL_RCC_DMA2D_CLK_ENABLE()
  ;               //ʹ��DMA2Dʱ��
  __HAL_RCC_GPIOB_CLK_ENABLE()
  ;               //ʹ��GPIOBʱ��
  __HAL_RCC_GPIOF_CLK_ENABLE()
  ;               //ʹ��GPIOFʱ��
  __HAL_RCC_GPIOG_CLK_ENABLE()
  ;               //ʹ��GPIOGʱ��
  __HAL_RCC_GPIOH_CLK_ENABLE()
  ;               //ʹ��GPIOHʱ��
  __HAL_RCC_GPIOI_CLK_ENABLE()
  ;               //ʹ��GPIOIʱ��

  //��ʼ��PB5����������
  GPIO_Initure.Pin = GPIO_PIN_5;                //PB5������������Ʊ���
  GPIO_Initure.Mode = GPIO_MODE_OUTPUT_PP;      //�������
  GPIO_Initure.Pull = GPIO_PULLUP;              //����
  GPIO_Initure.Speed = GPIO_SPEED_HIGH;         //����
  HAL_GPIO_Init (GPIOB, &GPIO_Initure);

  //��ʼ��PF10
  GPIO_Initure.Pin = GPIO_PIN_10;
  GPIO_Initure.Mode = GPIO_MODE_AF_PP;          //����
  GPIO_Initure.Pull = GPIO_NOPULL;
  GPIO_Initure.Speed = GPIO_SPEED_HIGH;         //����
  GPIO_Initure.Alternate = GPIO_AF14_LTDC;      //����ΪLTDC
  HAL_GPIO_Init (GPIOF, &GPIO_Initure);

  //��ʼ��PG6,7,11
  GPIO_Initure.Pin = GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_11;
  HAL_GPIO_Init (GPIOG, &GPIO_Initure);

  //��ʼ��PH9,10,11,12,13,14,15
  GPIO_Initure.Pin = GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 |\
 GPIO_PIN_12
      | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
  HAL_GPIO_Init (GPIOH, &GPIO_Initure);

  //��ʼ��PI0,1,2,4,5,6,7,9,10
  GPIO_Initure.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_4
      | GPIO_PIN_5 |\
 GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_9 | GPIO_PIN_10;
  HAL_GPIO_Init (GPIOI, &GPIO_Initure);
}

