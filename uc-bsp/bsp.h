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
 * Filename      : bsp.h
 * Version       : V1.00
 * Programmer(s) : FF
 *********************************************************************************************************
 */

/*
 *********************************************************************************************************
 *                                                 MODULE
 *
 * Note(s) : (1) This header file is protected from multiple pre-processor inclusion through use of the
 *               BSP present pre-processor macro definition.*
 *********************************************************************************************************
 */

#ifndef  BSP_H_
#define  BSP_H_

/*
 *********************************************************************************************************
 *                                     EXTERNAL C LANGUAGE LINKAGE
 *
 * Note(s) : (1) C++ compilers MUST 'extern'ally declare ALL C function prototypes & variable/object
 *               declarations for correct C language linkage.
 *********************************************************************************************************
 */

#ifdef __cplusplus
extern "C"
  { /* See Note #1.                                         */
#endif

/*
 *********************************************************************************************************
 *                                                 EXTERNS
 *********************************************************************************************************
 */

/*
 *********************************************************************************************************
 *                                              INCLUDE FILES
 *********************************************************************************************************
 */
#include  "bsp_uart.h"
#include  "bsp_tim.h"
#include  "bsp_clock.h"
#include  "bsp_led.h"
#include  "bsp_sdram.h"
#include  "bsp_rgb.h"
#include  "bsp_adc.h"
#include  "bsp_touch.h"
#include  "bsp_nand.h"
#include  "bsp_sdcard.h"
#include  "usbh_core.h"
#include  "bsp_rtc.h"
#include  "bsp_net.h"
#include  "pcf8574.h"
#include  "bsp_beep.h"
/*
 *********************************************************************************************************
 *                                               CONSTANTS
 *********************************************************************************************************
 */

/*
 *********************************************************************************************************
 *                                             PERIPH DEFINES
 *********************************************************************************************************
 */

/*
 *********************************************************************************************************
 *                                               DATA TYPES
 *********************************************************************************************************
 */

/*
 *********************************************************************************************************
 *                                            GLOBAL VARIABLES
 *********************************************************************************************************
 */

/*
 *********************************************************************************************************
 *                                                 MACRO'S
 *********************************************************************************************************
 */
#define ETH_RST(n)              (n?HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_RESET))   //LCD±≥π‚PD13
/*
 *********************************************************************************************************
 *                                           FUNCTION PROTOTYPES
 *********************************************************************************************************
 */
void
BSP_Init (void);

/*
 *********************************************************************************************************
 *                                   EXTERNAL C LANGUAGE LINKAGE END
 *********************************************************************************************************
 */

#ifdef __cplusplus
} /* End of 'extern'al C lang linkage.                    */
#endif

/*
 *********************************************************************************************************
 *                                             MODULE END
 *********************************************************************************************************
 */

#endif                                                          /* End of module include.                               */

