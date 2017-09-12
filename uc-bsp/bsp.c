/*
 *********************************************************************************************************
 *                                            EXAMPLE CODE
 *
 *               This file is provided as an example on how to use Micrium products.
 *
 *               Please feel free to use any application code labeled as 'EXAMPLE CODE' in
 *               your application products.  Example code may be used as is, in whole or in
 *               part, or may be used as a reference only. This file can be modified as
 *               required to meet the end-product requirements.
 *
 *               Please help us continue to provide the Embedded community with the finest
 *               software available.  Your honesty is greatly appreciated.
 *
 *               You can find our product's user manual, API reference, release notes and
 *               more information at https://doc.micrium.com.
 *               You can contact us at www.micrium.com.
 *********************************************************************************************************
 */

/*
 *********************************************************************************************************
 *
 *                                    MICRIUM BOARD SUPPORT PACKAGE
 *
 *                                          STM32746G-EVAL2
 *                                         Evaluation Board
 *
 * Filename      : bsp.c
 * Version       : V1.00
 * Programmer(s) : FF
 *********************************************************************************************************
 */

/*
 *********************************************************************************************************
 *                                             INCLUDE FILES
 *********************************************************************************************************
 */

#include  <cpu_core.h>
#include  <app_cfg.h>

#include  "bsp.h"
#include  "bsp_os.h"

#include  "stm32f7xx_hal.h"

extern _touch_dev tp_dev;

/*
 *********************************************************************************************************
 *                                            LOCAL DEFINES
 *********************************************************************************************************
 */

/*
 *********************************************************************************************************
 *                                           LOCAL CONSTANTS
 *********************************************************************************************************
 */

/*
 *********************************************************************************************************
 *                                          LOCAL DATA TYPES
 *********************************************************************************************************
 */

/*
 *********************************************************************************************************
 *                                            LOCAL TABLES
 *********************************************************************************************************
 */

/*
 *********************************************************************************************************
 *                                       LOCAL GLOBAL VARIABLES
 *********************************************************************************************************
 */
extern uint32_t POINT_COLOR;		//画笔颜色
extern uint32_t BACK_COLOR;  	//背景色

/*
 *********************************************************************************************************
 *                                      LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************
 */
void
EXTI_Init (void)
{
  GPIO_InitTypeDef GPIO_Initure;

  __HAL_RCC_GPIOH_CLK_ENABLE()
  ;			//开启GPIOH时钟
  GPIO_Initure.Pin = GPIO_PIN_2 | GPIO_PIN_3;            //PH2 PH3
  GPIO_Initure.Mode = GPIO_MODE_IT_FALLING;
  GPIO_Initure.Pull = GPIO_PULLUP;          //上拉
  GPIO_Initure.Speed = GPIO_SPEED_HIGH;     //高速
  HAL_GPIO_Init (GPIOH, &GPIO_Initure);     //初始化
  HAL_NVIC_EnableIRQ (EXTI2_IRQn);     //初始化按键中断,模拟边沿探测
  HAL_NVIC_SetPriority (EXTI2_IRQn, 5, 1);    //设置优先级抢占优先级(3bit)为5,次优先级(0bit)为1
  HAL_NVIC_EnableIRQ (EXTI3_IRQn);     //初始化按键中断,模拟边沿探测
  HAL_NVIC_SetPriority (EXTI3_IRQn, 5, 1);    //设置优先级抢占优先级(3bit)为5,次优先级(0bit)为1
}

/*
 *********************************************************************************************************
 *                                               BSP_Init()
 *
 * Description : Initialize the Board Support Package (BSP).
 *
 * Argument(s) : none.
 *
 * Return(s)   : none.
 *
 * Caller(s)   : Application.
 *
 * Note(s)     : (1) This function SHOULD be called before any other BSP function is called.
 *********************************************************************************************************
 */

void
BSP_Init (void)
{
  BSP_OSTickInit (); /* Initialize OS periodic time source                   */
  BSP_LED_Init (); /* Init LEDs.                                           */
  BSP_UART_Init ();
  SDRAM_init ();
  struct rgb_parameter m19;
  m19.hbp = 46;
  m19.vbp = 23;
  m19.hfp = 210;
  m19.vfp = 22;
  m19.hsw = 1;
  m19.vsw = 1;
  m19.width = 800;
  m19.height = 480;
  RGB_Init (&m19);
  EXTI_Init ();
  //BACK_COLOR=WHITE;
  //POINT_COLOR=RED;
  //APPOLO_RGB(0,0,gImage_xiong);
  //tp_dev.init ();
  TIM2_init ();     //定时器2周期采样ADC的值
  TIM3_init ();     //定时器3输出PWM供测试使用
  TIM5_init ();     //定时器5输入捕获计算频率
  CEKONG_init();
}

void
EXTI2_IRQHandler (void)
{
  OSIntEnter ();
  HAL_GPIO_EXTI_IRQHandler (GPIO_PIN_2);
  OSIntExit ();
}

void
EXTI3_IRQHandler (void)
{
  OSIntEnter ();
  HAL_GPIO_EXTI_IRQHandler (GPIO_PIN_3);
  OSIntExit ();
}

void
HAL_GPIO_EXTI_Callback (uint16_t GPIO_Pin)
{
  switch (GPIO_Pin)
    {
    case GPIO_PIN_2:
      BSP_LED_On (0);
      break;    //PH2-KEY1-点亮led1-PB0
    case GPIO_PIN_3:
      BSP_LED_Off (0);
      break;    //PH3-KEY0-熄灭led1-PB0
    default:
      break;
    }
}

