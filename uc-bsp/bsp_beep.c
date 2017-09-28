/*
 * bsp_beep.c
 *
 *  Created on: 2017Äê9ÔÂ28ÈÕ
 *      Author: iysheng
 */
#include  "stm32f7xx_hal.h"

#define  BSP_BEEP_PIN GPIO_PIN_13

void  BSP_BEEP_Init (void)
{
  GPIO_InitTypeDef  gpio_init;

      __HAL_RCC_GPIOC_CLK_ENABLE();                      /* Enable GPIO clock for BEEP(PC13)                     */
      gpio_init.Pin = BSP_BEEP_PIN;
      gpio_init.Mode  = GPIO_MODE_OUTPUT_PP;
      gpio_init.Pull  = GPIO_PULLUP;
      gpio_init.Speed = GPIO_SPEED_HIGH;
      HAL_GPIO_Init(GPIOC, &gpio_init);
      HAL_GPIO_WritePin(GPIOC, BSP_BEEP_PIN, GPIO_PIN_SET);
  }

void  BSP_BEEP_1 (void)
{
  HAL_GPIO_WritePin(GPIOC, BSP_BEEP_PIN, GPIO_PIN_RESET);
  HAL_Delay(2);
  HAL_GPIO_WritePin(GPIOC, BSP_BEEP_PIN, GPIO_PIN_SET);
  HAL_Delay(2);
  }
