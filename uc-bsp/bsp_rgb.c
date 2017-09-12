/*
 * bsp_rgb.c
 *
 *  Created on: 2017年9月8日
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
    ;               //使能DMA2D时钟
  DMA2D->CR = 3 << 16;				//寄存器到存储器模式
  DMA2D->OPFCCR = LCD_PIXFORMAT;	//设置颜色格式
  DMA2D->OOR = 0;				//设置行偏移
  DMA2D->CR &= ~(1 << 0);				//先停止DMA2D
  DMA2D->OMAR = LCD_BUFFER_ADDR;				//输出存储器地址
  DMA2D->NLR = (ey - sy + 1) | ((ex - sx + 1) << 16);	//设定行数寄存器
  DMA2D->OCOLR = color;				//设定输出颜色寄存器
  DMA2D->CR |= 1 << 0;				//启动DMA2D
  while ((DMA2D->ISR & (1 << 1)) == 0)	//等待传输完成
    {
      timeout++;
      if (timeout > 0X1FFFFF)
	break;	//超时退出
    }
  DMA2D->IFCR |= 1 << 1;				//清除传输完成标志
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
  //LTDC_HandleTypeDef LTDC_Handler;	    //LTDC句柄
  //memset(&LTDC_Handler,0,sizeof(LTDC_Handler));
  LTDC_Handler.Instance = LTDC;
  LTDC_Handler.Init.HSPolarity = LTDC_HSPOLARITY_AL;         //水平同步极性
  LTDC_Handler.Init.VSPolarity = LTDC_VSPOLARITY_AL;         //垂直同步极性
  LTDC_Handler.Init.DEPolarity = LTDC_DEPOLARITY_AL;         //数据使能极性
  LTDC_Handler.Init.PCPolarity = LTDC_PCPOLARITY_IPC;        //像素时钟极性
  LTDC_Handler.Init.HorizontalSync = mode->hsw - 1;          //水平同步宽度
  LTDC_Handler.Init.VerticalSync = mode->vsw - 1;            //垂直同步宽度
  LTDC_Handler.Init.AccumulatedHBP = mode->hsw + mode->hbp - 1; //水平同步后沿宽度
  LTDC_Handler.Init.AccumulatedVBP = mode->vsw + mode->vbp - 1; //垂直同步后沿高度
  LTDC_Handler.Init.AccumulatedActiveW = mode->hsw + mode->hbp + mode->width
      - 1; //有效宽度
  LTDC_Handler.Init.AccumulatedActiveH = mode->vsw + mode->vbp + mode->height
      - 1; //有效高度
  LTDC_Handler.Init.TotalWidth = mode->hsw + mode->hbp + mode->width + mode->hfp
      - 1;   //总宽度
  LTDC_Handler.Init.TotalHeigh = mode->vsw + mode->vbp + mode->height
      + mode->vfp - 1;  //总高度
  LTDC_Handler.Init.Backcolor.Red = 0;           //屏幕背景层红色部分
  LTDC_Handler.Init.Backcolor.Green = 0;         //屏幕背景层绿色部分
  LTDC_Handler.Init.Backcolor.Blue = 0;          //屏幕背景色蓝色部分
  ret = HAL_LTDC_Init (&LTDC_Handler);
  if (HAL_OK != ret)
    goto fail;

  LTDC_LayerCfgTypeDef pLayerCfg;
  pLayerCfg.WindowX0 = 0;                       //窗口起始X坐标
  pLayerCfg.WindowY0 = 0;                       //窗口起始Y坐标
  pLayerCfg.WindowX1 = mode->width;          //窗口终止X坐标
  pLayerCfg.WindowY1 = mode->height;         //窗口终止Y坐标
  pLayerCfg.PixelFormat = LCD_PIXFORMAT;		    //像素格式
  pLayerCfg.Alpha = 255;			//Alpha值设置，0~255,255为完全不透明
  pLayerCfg.Alpha0 = 0;			        //默认Alpha值
  pLayerCfg.BlendingFactor1 = (uint32_t) 6 << 8;    //设置层混合系数
  pLayerCfg.BlendingFactor2 = (uint32_t) 7 << 8;	//设置层混合系数
  pLayerCfg.FBStartAdress = LCD_BUFFER_ADDR;	        //设置层颜色帧缓存起始地址
  pLayerCfg.ImageWidth = mode->width;        //设置颜色帧缓冲区的宽度
  pLayerCfg.ImageHeight = mode->height;      //设置颜色帧缓冲区的高度
  pLayerCfg.Backcolor.Red = (uint8_t) (LCD_BACK_COLOR & 0X00FF0000) >> 16; //背景颜色红色部分
  pLayerCfg.Backcolor.Green = (uint8_t) (LCD_BACK_COLOR & 0X0000FF00) >> 8; //背景颜色绿色部分
  pLayerCfg.Backcolor.Blue = (uint8_t) LCD_BACK_COLOR & 0X000000FF;   //背景颜色蓝色部分
  ret = HAL_LTDC_ConfigLayer (&LTDC_Handler, &pLayerCfg, 0);   //设置所选中的层
  if (HAL_OK != ret)
    goto fail;
  ret = HAL_LTDC_SetWindowPosition (&LTDC_Handler, 0, 0, 0);  //设置窗口的位置
  if (HAL_OK != ret)
    goto fail;
  ret = HAL_LTDC_SetWindowSize (&LTDC_Handler, mode->width, mode->height, 0); //设置窗口大小
  LCD_LED(1);
  //LTDC_Fill (0, 0, mode->width - 1, mode->height - 1, LCD_BACK_COLOR);  //清屏
  fail: return ret;
}

void
HAL_LTDC_MspInit (LTDC_HandleTypeDef* hltdc)
{
  GPIO_InitTypeDef GPIO_Initure;

  __HAL_RCC_LTDC_CLK_ENABLE()
  ;                //使能LTDC时钟
  __HAL_RCC_DMA2D_CLK_ENABLE()
  ;               //使能DMA2D时钟
  __HAL_RCC_GPIOB_CLK_ENABLE()
  ;               //使能GPIOB时钟
  __HAL_RCC_GPIOF_CLK_ENABLE()
  ;               //使能GPIOF时钟
  __HAL_RCC_GPIOG_CLK_ENABLE()
  ;               //使能GPIOG时钟
  __HAL_RCC_GPIOH_CLK_ENABLE()
  ;               //使能GPIOH时钟
  __HAL_RCC_GPIOI_CLK_ENABLE()
  ;               //使能GPIOI时钟

  //初始化PB5，背光引脚
  GPIO_Initure.Pin = GPIO_PIN_5;                //PB5推挽输出，控制背光
  GPIO_Initure.Mode = GPIO_MODE_OUTPUT_PP;      //推挽输出
  GPIO_Initure.Pull = GPIO_PULLUP;              //上拉
  GPIO_Initure.Speed = GPIO_SPEED_HIGH;         //高速
  HAL_GPIO_Init (GPIOB, &GPIO_Initure);

  //初始化PF10
  GPIO_Initure.Pin = GPIO_PIN_10;
  GPIO_Initure.Mode = GPIO_MODE_AF_PP;          //复用
  GPIO_Initure.Pull = GPIO_NOPULL;
  GPIO_Initure.Speed = GPIO_SPEED_HIGH;         //高速
  GPIO_Initure.Alternate = GPIO_AF14_LTDC;      //复用为LTDC
  HAL_GPIO_Init (GPIOF, &GPIO_Initure);

  //初始化PG6,7,11
  GPIO_Initure.Pin = GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_11;
  HAL_GPIO_Init (GPIOG, &GPIO_Initure);

  //初始化PH9,10,11,12,13,14,15
  GPIO_Initure.Pin = GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 |\
 GPIO_PIN_12
      | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
  HAL_GPIO_Init (GPIOH, &GPIO_Initure);

  //初始化PI0,1,2,4,5,6,7,9,10
  GPIO_Initure.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_4
      | GPIO_PIN_5 |\
 GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_9 | GPIO_PIN_10;
  HAL_GPIO_Init (GPIOI, &GPIO_Initure);
}

