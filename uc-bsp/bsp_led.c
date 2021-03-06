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
*                                         STM32746G-EVAL2
*                                         Evaluation Board
*
* Filename      : bsp_led.c
* Version       : V1.00
* Programmer(s) : FF
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#include  "bsp_led.h"

#include  "stm32f7xx_hal.h"


/*
*********************************************************************************************************
*                                               DEFINES
*********************************************************************************************************
*/

#define  BSP_LED0_GPIOB_PIN                       DEF_BIT_00
#define  BSP_LED1_GPIOB_PIN                       DEF_BIT_01


/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                          LOCAL DATA TYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                     LOCAL CONFIGURATION ERRORS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*********************************************************************************************************
**                                         GLOBAL FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                          LED INITIALIZATION
*
* Description : Board Support package LED initialization.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : BSP_Init().
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_LED_Init (void)
{
    GPIO_InitTypeDef  gpio_init;

    __HAL_RCC_GPIOB_CLK_ENABLE();                               /* Enable GPIO clock for LED1(PF10)                     */
    __HAL_RCC_GPIOI_CLK_ENABLE();
                                                                /* Configure the GPIOB for LED1(PF10)                   */
    gpio_init.Pin   = BSP_LED0_GPIOB_PIN|BSP_LED1_GPIOB_PIN;
    gpio_init.Mode  = GPIO_MODE_OUTPUT_PP;
    gpio_init.Pull  = GPIO_PULLUP;
    gpio_init.Speed = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(GPIOB, &gpio_init);
    gpio_init.Pin   = GPIO_PIN_11;
    HAL_GPIO_Init(GPIOI, &gpio_init);
    BSP_LED_Off(0u);
    BSP_LED_Off(1u);
    BSP_LED_On(2u);
}


/*
*********************************************************************************************************
*                                            BSP_LED_Off()
*
* Description : Turn OFF any or all the LEDs on the board.
*
* Argument(s) : led    The ID of the LED to control:
*
*                           0    turn OFF all LEDs on the board.
*                           1    turn OFF LED1 on the board.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_LED_Off (CPU_INT08U  led)
{
    switch (led) {
        case 0u:HAL_GPIO_WritePin(GPIOB, BSP_LED0_GPIOB_PIN, GPIO_PIN_SET);break;
        case 1u:HAL_GPIO_WritePin(GPIOB, BSP_LED1_GPIOB_PIN, GPIO_PIN_SET);break;
        case 2u:HAL_GPIO_WritePin(GPIOI, GPIO_PIN_11, GPIO_PIN_RESET);break;
        default:
          HAL_GPIO_WritePin(GPIOI, GPIO_PIN_11, GPIO_PIN_RESET);
             HAL_GPIO_WritePin(GPIOB, BSP_LED0_GPIOB_PIN, GPIO_PIN_SET);
             HAL_GPIO_WritePin(GPIOB, BSP_LED1_GPIOB_PIN, GPIO_PIN_SET);
             break;
    }
}


/*
*********************************************************************************************************
*                                            BSP_LED_On()
*
* Description : Turn ON any or all the LEDs on the board.
*
* Argument(s) : led     The ID of the LED to control:
*                           0    turn ON all LEDs on the board.
*                           1    turn ON LED1 on the board.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_LED_On (CPU_INT08U  led)
{
    switch (led) {
        case 0u:HAL_GPIO_WritePin(GPIOB, BSP_LED0_GPIOB_PIN, GPIO_PIN_RESET);break;
        case 1u:HAL_GPIO_WritePin(GPIOB, BSP_LED1_GPIOB_PIN, GPIO_PIN_RESET);break;
        case 2u:HAL_GPIO_WritePin(GPIOI, GPIO_PIN_11, GPIO_PIN_SET);break;
        default:
          HAL_GPIO_WritePin(GPIOI, GPIO_PIN_11, GPIO_PIN_SET);
             HAL_GPIO_WritePin(GPIOB, BSP_LED0_GPIOB_PIN, GPIO_PIN_RESET);
             HAL_GPIO_WritePin(GPIOB, BSP_LED1_GPIOB_PIN, GPIO_PIN_RESET);
             break;
    }
}


/*
*********************************************************************************************************
*                                          BSP_LED_Toggle()
*
* Description : Toggles any or all the LEDs on the board.
*
* Argument(s) : led   The ID of the LED to control:
*
*                       0    toggle all LEDs on the board
*                       1    toggle LED1
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_LED_Toggle (CPU_INT08U  led)
{
    switch (led) {
        case 0u:HAL_GPIO_TogglePin(GPIOB, BSP_LED0_GPIOB_PIN);break;
        case 1u:HAL_GPIO_TogglePin(GPIOB, BSP_LED1_GPIOB_PIN);break;
        case 2u:HAL_GPIO_TogglePin(GPIOI, GPIO_PIN_11);break;
        default:
          HAL_GPIO_TogglePin(GPIOI, GPIO_PIN_11);
             HAL_GPIO_TogglePin(GPIOB, BSP_LED0_GPIOB_PIN);
             HAL_GPIO_TogglePin(GPIOB, BSP_LED1_GPIOB_PIN);
             break;
    }
}
