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

void  BSP_Init (void)
{
    BSP_OSTickInit();                                           /* Initialize OS periodic time source                   */
    BSP_LED_Init();                                             /* Init LEDs.                                           */

    BSP_UART_Init();

    SDRAM_init();
    LCD_Init();
    LTDC_Clear(WHITE);
    BACK_COLOR=WHITE;
    POINT_COLOR=RED;
    APPOLO_RGB(0,0,gImage_xiong);
    tp_dev.init();
    TIM2_init();     //定时器2周期采样ADC的值
    TIM3_init();     //定时器3输出PWM供测试使用
    TIM5_init();     //定时器5输入捕获计算频率
    CEKONG_init();
}
