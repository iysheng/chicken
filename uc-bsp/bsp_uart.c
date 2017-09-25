#include "bsp_uart.h"
#include "stm32f7xx_hal.h"
#include "main.h"
UART_HandleTypeDef UART_DEBUG;

void BSP_UART_Init(void)
{
  static HAL_StatusTypeDef test;
  UART_DEBUG.Instance=UART_DEBUG_PORT;
  UART_DEBUG.Init.BaudRate=115200;
  UART_DEBUG.Init.WordLength=UART_WORDLENGTH_8B;
  UART_DEBUG.Init.StopBits=UART_STOPBITS_1;
  UART_DEBUG.Init.Parity=UART_PARITY_NONE;
  UART_DEBUG.Init.Mode=UART_MODE_TX_RX;
  UART_DEBUG.Init.HwFlowCtl=UART_HWCONTROL_NONE;
  test = HAL_UART_Init(&UART_DEBUG);
  test++;
}

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
  GPIO_InitTypeDef GPIO_Initure;
  if(huart->Instance == USART2)
  {
    __HAL_RCC_USART2_CLK_ENABLE();//USART2时钟使能
    __HAL_RCC_GPIOA_CLK_ENABLE();
    GPIO_Initure.Pin=GPIO_PIN_2;
    GPIO_Initure.Mode=GPIO_MODE_AF_PP;
    GPIO_Initure.Pull=GPIO_NOPULL;
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_LOW;
    GPIO_Initure.Alternate=GPIO_AF7_USART2;
    HAL_GPIO_Init(GPIOA,&GPIO_Initure); 
    GPIO_Initure.Pin=GPIO_PIN_3;
    GPIO_Initure.Alternate=GPIO_AF7_USART2;
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);
    HAL_NVIC_SetPriority(USART2_IRQn, 1, 1);
    HAL_NVIC_EnableIRQ(USART2_IRQn);
  }
  else if(huart->Instance == USART1)
  {
    __HAL_RCC_USART1_CLK_ENABLE();//USART1时钟使能
    __HAL_RCC_GPIOA_CLK_ENABLE();
    GPIO_Initure.Pin=GPIO_PIN_10;
    GPIO_Initure.Mode=GPIO_MODE_AF_PP;
    GPIO_Initure.Pull=GPIO_NOPULL;
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_LOW;
    GPIO_Initure.Alternate=GPIO_AF7_USART1;
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);
    GPIO_Initure.Pin=GPIO_PIN_9; 
    GPIO_Initure.Alternate=GPIO_AF7_USART1;
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);
    HAL_NVIC_SetPriority(USART1_IRQn, 1, 1);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
  }
}

int _write (int fd, const void *buf, size_t count)
{
  (void)fd;
  //HAL_UART_Transmit(&UART_DEBUG, (uint8_t *)buf, count, 0xFFFF);
  HAL_UART_Transmit_IT(&UART_DEBUG, (uint8_t *)buf, count);
  return count;
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
  //if((huart->Instance==USART1)||((huart->Instance==USART2))//如果是串口1
    {
      huart->gState = HAL_UART_STATE_READY;
    }
  }

void USART1_IRQHandler(void){
  OSIntEnter();
  HAL_UART_IRQHandler(&UART_DEBUG);
  OSIntExit();
}
void USART2_IRQHandler(void){
  OSIntEnter();
  HAL_UART_IRQHandler(&UART_DEBUG);
  OSIntExit();
}



