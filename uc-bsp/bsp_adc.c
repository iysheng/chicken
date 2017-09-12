/*
 * bsp_adc.c
 *
 *  Created on: 2017年5月15日
 *      Author: iysheng
 */

#include "main.h"

ADC_HandleTypeDef ICEKONG;
DMA_HandleTypeDef IDMA_ADC;
extern OS_TCB       AppTaskObj0TCB;

void CEKONG_init(void)
{
  ADC_ChannelConfTypeDef Iconfig;
  __HAL_RCC_ADC1_CLK_ENABLE();
  ICEKONG.Instance = ADC1;
  ICEKONG.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV8;//APB2=108MHz
  ICEKONG.Init.Resolution = ADC_RESOLUTION_12B;//12bit转换结果
  ICEKONG.Init.ScanConvMode = ENABLE;
  ICEKONG.Init.ContinuousConvMode = DISABLE;
  ICEKONG.Init.DiscontinuousConvMode = DISABLE;
  ICEKONG.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  ICEKONG.Init.NbrOfConversion = IDAC_COUNT;
  ICEKONG.Init.DMAContinuousRequests = ENABLE;
  ICEKONG.Init.EOCSelection = ADC_EOC_SEQ_CONV;
  ICEKONG.Init.ExternalTrigConv=ADC_EXTERNALTRIGCONV_T2_TRGO;//定时器2驱动ADC周期转换
  ICEKONG.Init.ExternalTrigConvEdge=ADC_EXTERNALTRIGCONVEDGE_RISING;
  HAL_ADC_Init(&ICEKONG);

  Iconfig.Channel = ADC_CHANNEL_TEMPSENSOR;
  Iconfig.Rank = 1;
  Iconfig.SamplingTime = ADC_SAMPLETIME_480CYCLES;
  HAL_ADC_ConfigChannel(&ICEKONG,&Iconfig);

  Iconfig.Channel = ADC_CHANNEL_4;//PA4
  Iconfig.Rank = 2;
  Iconfig.SamplingTime = ADC_SAMPLETIME_480CYCLES;
  HAL_ADC_ConfigChannel(&ICEKONG,&Iconfig);

  Iconfig.Channel = ADC_CHANNEL_5;//PA5
  Iconfig.Rank = 3;
  Iconfig.SamplingTime = ADC_SAMPLETIME_480CYCLES;
  HAL_ADC_ConfigChannel(&ICEKONG,&Iconfig);

  Iconfig.Channel = ADC_CHANNEL_6;//PA6
  Iconfig.Rank = 4;
  Iconfig.SamplingTime = ADC_SAMPLETIME_480CYCLES;
  HAL_ADC_ConfigChannel(&ICEKONG,&Iconfig);
}

void HAL_ADC_MspInit(ADC_HandleTypeDef* hadc)
{
  GPIO_InitTypeDef  GPIO_Initure;
  if(hadc->Instance==ADC1)
  {
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_DMA2_CLK_ENABLE();//使能DMA2时钟
  GPIO_Initure.Mode=GPIO_MODE_ANALOG;
  GPIO_Initure.Pull=GPIO_NOPULL;
  GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;
  GPIO_Initure.Pin=GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6;
  HAL_GPIO_Init(GPIOA,&GPIO_Initure);//PA4\PA5\PA6

  IDMA_ADC.Instance=DMA2_Stream0;
  IDMA_ADC.Init.Channel=DMA_CHANNEL_0;
  IDMA_ADC.Init.Direction=DMA_PERIPH_TO_MEMORY;
  IDMA_ADC.Init.PeriphInc=DMA_PINC_DISABLE;
  IDMA_ADC.Init.MemInc=DMA_MINC_ENABLE;
  IDMA_ADC.Init.PeriphDataAlignment=DMA_PDATAALIGN_HALFWORD;
  IDMA_ADC.Init.MemDataAlignment=DMA_MDATAALIGN_HALFWORD;
  IDMA_ADC.Init.Mode=DMA_CIRCULAR;
  IDMA_ADC.Init.Priority=DMA_PRIORITY_LOW;
  IDMA_ADC.Init.FIFOMode=DMA_FIFOMODE_DISABLE;
  HAL_DMA_Init(&IDMA_ADC);
  HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);//开启DMA2中断
  HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 0x0, 2);

  __HAL_LINKDMA(&ICEKONG,DMA_Handle,IDMA_ADC);
  }
}

  void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
  {
	static OS_ERR err;
    if(hadc->Instance==ADC1)
    {
        OSTaskSemPost(&AppTaskObj0TCB,OS_OPT_POST_NONE,&err);
    }
  }

  void DMA2_Stream0_IRQHandler(void)
  {
     HAL_DMA_IRQHandler(&IDMA_ADC);
  }
