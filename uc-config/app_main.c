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
 *                                            EXAMPLE CODE
 *
 *                                          STM32746G-EVAL2
 *                                         Evaluation Board
 *
 * Filename      : app.c
 * Version       : V1.00
 * Programmer(s) : FF
 *********************************************************************************************************
 */

/*
 *********************************************************************************************************
 *                                             INCLUDE FILES
 *********************************************************************************************************
 */

#include  <stdarg.h>
#include  <stdio.h>
#include  <string.h>
#include  <math.h>
#include  <stm32f7xx_hal.h>

#include  <cpu.h>
#include  <lib_math.h>
#include  <lib_mem.h>
#include  <os_app_hooks.h>

#include  <app_cfg.h>
#include  <bsp.h>

uint16_t raw_icekong[4];

extern ADC_HandleTypeDef ICEKONG;
extern _touch_dev tp_dev;
extern struct rgb_parameter m19;
extern SD_HandleTypeDef SDCARD_Handler;             //SD卡句柄
extern USBH_ClassTypeDef  USBH_msc;
extern __lwip_dev lwipdev;
USBH_HandleTypeDef  USB_Host;

/*
 *********************************************************************************************************
 *                                            LOCAL DEFINES
 *********************************************************************************************************
 */

/*
 *********************************************************************************************************
 *                                       LOCAL GLOBAL VARIABLES
 *********************************************************************************************************
 */
OS_Q KEY_Q, RPM_Q;
uint16_t *key_value;
int32_t *rpm_value;
/* --------------- APPLICATION GLOBALS ---------------- */
static OS_TCB AppTaskStartTCB;
static CPU_STK AppTaskStartStk[APP_CFG_TASK_START_STK_SIZE];

/* --------------- SEMAPHORE TASK TEST --------------- */
OS_TCB AppTaskObj0TCB;
CPU_STK AppTaskObj0Stk[APP_CFG_TASK_OBJ_STK_SIZE];

OS_TCB AppTaskObj1TCB;
CPU_STK AppTaskObj1Stk[APP_CFG_TASK_OBJ_STK_SIZE];

OS_TCB AppTaskObj2TCB;
CPU_STK AppTaskObj2Stk[APP_CFG_TASK_OBJ_STK_SIZE];

OS_TCB AppTaskObj3TCB;
CPU_STK AppTaskObj3Stk[APP_CFG_TASK_OBJ_STK_SIZE];

OS_TCB AppTaskObj4TCB;
CPU_STK AppTaskObj4Stk[APP_CFG_TASK_OBJ_STK_SIZE];

OS_TCB AppTaskObj5TCB;
CPU_STK AppTaskObj5Stk[APP_CFG_TASK_OBJ_STK_SIZE];

/*
 *********************************************************************************************************
 *                                         FUNCTION PROTOTYPES
 *********************************************************************************************************
 */

static void
AppTaskStart (void *p_arg);
static void
AppTaskCreate (void);

static void
AppTaskObj0 (void *p_arg);
static void
AppTaskObj1 (void *p_arg);
static void
AppTaskObj2 (void *p_arg);
static void
AppTaskObj3 (void *p_arg);
static void
AppTaskObj4 (void *p_arg);
static void
AppTaskObj5 (void *p_arg);
static void
MessQueue_Init (void);
/*
 *********************************************************************************************************
 *                                                main()
 *
 * Description : This is the standard entry point for C code.  It is assumed that your code will call
 *               main() once you have performed all necessary initialization.
 *
 * Arguments   : none
 *
 * Returns     : none
 *
 * Notes       : 1) HAL library initialization:
 *                      a) Configures the Flash prefetch, intruction and data caches.
 *                      b) Configures the Systick to generate an interrupt. However, the function ,
 *                         HAL_InitTick(), that initializes the Systick has been overwritten since Micrium's
 *                         RTOS has its own Systick initialization and it is recommended to initialize the
 *                         Systick after multitasking has started.
 *
 *********************************************************************************************************
 */

int
main (void)
{
  OS_ERR err;
  HAL_Init (); /* See Note 1.                                          */
  BSP_SystemClkCfg (); /* Initialize CPU clock frequency to 216Mhz             */

  CPU_Init (); /* Initialize the uC/CPU services                       */

  Mem_Init (); /* Initialize Memory Managment Module                   */
  Math_Init (); /* Initialize Mathematical Module                       */

  CPU_IntDis (); /* Disable all Interrupts.                              */

  OSInit (&err); /* Init uC/OS-III.                                      */

  App_OS_SetAllHooks ();
  MessQueue_Init ();

  OSTaskCreate (&AppTaskStartTCB, /* Create the start task                                */
		"App Task Start", AppTaskStart, 0u,
		APP_CFG_TASK_START_PRIO,
		&AppTaskStartStk[0u],
		AppTaskStartStk[APP_CFG_TASK_START_STK_SIZE / 10u],
		APP_CFG_TASK_START_STK_SIZE,
		0u, 0u, 0u, (OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR ), &err);
  OSStart (&err); /* Start multitasking (i.e. give control to uC/OS-III). */

  while (DEF_ON)
    { /* Should Never Get Here.                               */

    }
}

/*
 *********************************************************************************************************
 *                                          STARTUP TASK
 *
 * Description : This is an example of a startup task.  As mentioned in the book's text, you MUST
 *               initialize the ticker only once multitasking has started.
 *
 * Arguments   : p_arg   is the argument passed to 'AppTaskStart()' by 'OSTaskCreate()'.
 *
 * Returns     : none
 *
 * Notes       : 1) The first line of code is used to prevent a compiler warning because 'p_arg' is not
 *                  used.  The compiler should not generate any code for this statement.
 *********************************************************************************************************
 */
static uint8_t
SD_ShowCardInfo ()
{
  HAL_StatusTypeDef ret;
  HAL_SD_CardInfoTypeDef cardInfo;
  ret = HAL_SD_GetCardInfo (&SDCARD_Handler, &cardInfo);
  switch (cardInfo.CardType)
    {
    case CARD_SDSC:
      printf ("Card Type:CARD_SDSC\r\n");
      break;
    case CARD_SDHC_SDXC:
      printf ("Card Type:CARD_SDHC_SDXC\r\n");
      break;
    case CARD_SECURED:
      printf ("Card Type:CARD_SECURED\r\n");
      break;
    default:
      printf ("Unknown Card Type\r\n");
      break;
    }
  //printf ("Card RCA:%x\r\n", (unsigned int) cardInfo.RelCardAdd);        //卡相对地址
  printf ("Card Capacity:%u MB\r\n",
	  (unsigned int) (cardInfo.BlockNbr * cardInfo.BlockSize) >> 20);//显示容量
  //printf ("Card BlockNbr:%u\r\n", (unsigned int) cardInfo.BlockNbr);
  //printf ("Card BlockSize:%u\r\n", (unsigned int) cardInfo.BlockSize);//显示块大小
  return ret;
}

void usbh_pUsrFunc(USBH_HandleTypeDef *phost, uint8_t id)
   {
  printf("hello usbh_pUsrFunc-----id:%u----->\r\n",(unsigned int)id);
    }

static void
AppTaskStart (void *p_arg)
{
  OS_ERR err;

  (void) p_arg;
  BSP_Init (); /* Initialize BSP functions                             */
  RGB_Init (&m19);
#if OS_CFG_STAT_TASK_EN > 0u
  OSStatTaskCPUUsageInit (&err); /* Compute CPU capacity with no task running            */
#endif

#ifdef CPU_CFG_INT_DIS_MEAS_EN
  CPU_IntDisMeasMaxCurReset ();
#endif

  APP_TRACE_DBG(("Creating Application Tasks\n\r"));
  AppTaskCreate (); /* Create Application tasks */

  while (DEF_TRUE)
    { /* Task body, always written as an infinite loop.       */
      OSTaskDel ((OS_TCB*) 0, &err);
      //OSTimeDlyHMSM (0, 0, 10, 0, OS_OPT_TIME_DLY, &err);
    }
}

/*
 *********************************************************************************************************
 *                                          AppTaskCreate()
 *
 * Description : Create Application Tasks.
 *
 * Argument(s) : none
 *
 * Return(s)   : none
 *
 * Caller(s)   : AppTaskStart()
 *
 * Note(s)     : none.
 *********************************************************************************************************
 */

static void
AppTaskCreate (void)
{
  OS_ERR os_err;
  /* ---------- CREATE KERNEL OBJECTS TEST TASK --------- */
  OSTaskCreate (&AppTaskObj0TCB, "Kernel Objects Task 0", AppTaskObj0, 0,
  APP_CFG_TASK_OBJ0_PRIO,
		&AppTaskObj0Stk[0],
		AppTaskObj0Stk[APP_CFG_TASK_OBJ_STK_SIZE / 10u],
		APP_CFG_TASK_OBJ_STK_SIZE,
		0u, 0u, 0, (OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR ),
		&os_err);

  OSTaskCreate (&AppTaskObj1TCB, "Kernel Objects Task 1", AppTaskObj1, 0,
  APP_CFG_TASK_OBJ1_PRIO,
		&AppTaskObj1Stk[0],
		AppTaskObj1Stk[APP_CFG_TASK_OBJ_STK_SIZE / 10u],
		APP_CFG_TASK_OBJ_STK_SIZE,
		0u, 0u, 0, (OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR ),
		&os_err);
  OSTaskCreate (&AppTaskObj2TCB, "Kernel Objects Task 2", AppTaskObj2, 0,
  APP_CFG_TASK_OBJ2_PRIO,
		&AppTaskObj2Stk[0],
		AppTaskObj2Stk[APP_CFG_TASK_OBJ_STK_SIZE / 10u],
		APP_CFG_TASK_OBJ_STK_SIZE,
		0u, 0u, 0, (OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR ),
		&os_err);
  OSTaskCreate (&AppTaskObj3TCB, "Kernel Objects Task 3", AppTaskObj3, 0,
  APP_CFG_TASK_OBJ3_PRIO,
		&AppTaskObj3Stk[0],
		AppTaskObj3Stk[APP_CFG_TASK_OBJ_STK_SIZE / 10u],
		APP_CFG_TASK_OBJ_STK_SIZE,
		0u, 0u, 0, (OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR ),
		&os_err);
#if 0
  OSTaskCreate (&AppTaskObj4TCB, "Kernel Objects Task 4", AppTaskObj4, 0,
    APP_CFG_TASK_OBJ4_PRIO,
  		&AppTaskObj4Stk[0],
  		AppTaskObj4Stk[APP_CFG_TASK_OBJ_STK_SIZE / 10u],
  		APP_CFG_TASK_OBJ_STK_SIZE,
  		0u, 0u, 0, (OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR ),
  		&os_err);
#endif
  OSTaskCreate (&AppTaskObj5TCB, "Kernel Objects Task 5", AppTaskObj5, 0,
      APP_CFG_TASK_OBJ5_PRIO,
    		&AppTaskObj5Stk[0],
    		AppTaskObj5Stk[APP_CFG_TASK_OBJ_STK_SIZE / 10u],
    		APP_CFG_TASK_OBJ_STK_SIZE,
    		0u, 0u, 0, (OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR ),
    		&os_err);
}

/*
 *********************************************************************************************************
 *                                          AppTaskObj0()
 *
 * Description : Test uC/OS-III objects.
 *
 * Argument(s) : p_arg is the argument passed to 'AppTaskObj0' by 'OSTaskCreate()'.
 *
 * Return(s)   : none
 *
 * Caller(s)   : This is a task
 *
 * Note(s)     : none.
 *********************************************************************************************************
 */

static void
AppTaskObj0 (void *p_arg)
{
  OS_ERR os_err;
  (void) p_arg;
  static uint8_t uline;
  static float ftemp;
  static uint32_t uitemp;
  static char rstr[64];
  GUI_Init ();
  HAL_ADC_Start_DMA (&ICEKONG, (uint32_t *) raw_icekong, IDAC_COUNT);
  while (DEF_TRUE)
    {
      //BSP_LED_Off(0);
      OSTaskSemPend (100,
      OS_OPT_PEND_BLOCKING,
		     NULL, &os_err);
      if (os_err == OS_ERR_NONE)
	{
	  while (uline < 4)
	    {
	      switch (uline)
		{
		case 0:
		  {
		    sprintf ((char *) rstr, "PA4:%4dKg", raw_icekong[1]);
		    break;
		  }
		case 1:
		  {
		    sprintf ((char *) rstr, "PA5:%4dN.m", raw_icekong[2]);
		    break;
		  }
		case 2:
		  {
		    sprintf ((char *) rstr, "PA6:%4dcm", raw_icekong[3]);
		    break;
		  }
		case 3:
		  {
		    uitemp = raw_icekong[0];
		    ftemp = ((float) uitemp) / 4095 * 3300;
		    ftemp = ((ftemp - 760.0) / 2.5) + 25;
		    sprintf ((char *) rstr, "%0.3f", ftemp);
		    break;
		  }
		default:
		  break;
		}
	      GUI_DispStringAt ((const char *) rstr, 400, uline * 100);
	      printf ("%s\r\n", rstr);
	      uline++;
	    }
	  uline = 0;
	}
      APP_TRACE_INFO(("Object test task 0 running ....\r\n"));
    }
}

static void
AppTaskObj1 (void *p_arg)
{
  OS_ERR os_err;
  (void) p_arg;
  static OS_MSG_SIZE msg_size;
  static uint64_t hole_ic_value;              //捕获的计数值
  static char rstr[64];
  GUI_Init ();
  while (DEF_TRUE)
    {
      rpm_value = (int32_t *) OSQPend (&RPM_Q, 1000,
      OS_OPT_PEND_BLOCKING,
				       &msg_size,
				       NULL,
				       &os_err);
      if (os_err == OS_ERR_NONE)
	{
	  (*rpm_value) &= ~(3 << 30);
	  hole_ic_value = (*rpm_value);
	  hole_ic_value += *(rpm_value + 1);
	  *rpm_value = hole_ic_value / 1000;
	  //sprintf ((char *) rstr, "PWM:%6dms...%6lldus", (int) (*rpm_value),
	  //   (long long int) hole_ic_value);
	  snprintf ((char *) rstr, 15, "PWM:%dms", (int) (*rpm_value));
	  GUI_DispStringAt ((const char *) rstr, 400, 400);
	  printf ("task1 %s &msg_size is %d\r\n", rstr, (int) msg_size);
	  //*rpm_value = 0x00;
	}
      APP_TRACE_INFO(("Object test task 1 running ....\r\n"));
    }
}

static void
AppTaskObj2 (void *p_arg)
{
  OS_ERR os_err;
  (void) p_arg;
  static uint8_t upoint;
  while (DEF_TRUE)
    {
      OSTaskSemPend (100,
      OS_OPT_PEND_BLOCKING,
		     NULL, &os_err);

      if (os_err == OS_ERR_NONE)
	{
	  GUI_TOUCH_Exec ();
	  FT5206_Scan ();
	  if (tp_dev.sta != 0)
	    {
	      tp_dev.sta &= 0x1f;
	      do
		{
		  upoint++;
		  tp_dev.sta >>= 1;
		}
	      while (tp_dev.sta & 0x01);
	      tp_dev.sta = upoint;
	      OSQPost (&KEY_Q, (void *) (&(tp_dev.x[0])), 1,
	      OS_OPT_POST_FIFO + OS_OPT_POST_ALL,
		       &os_err);					//发送消息队列
	      upoint = 0;
	    }
	}
      APP_TRACE_INFO(("Object test task 2 running ....\r\n"));
    }
}
static void
AppTaskObj3 (void *p_arg)
{
  OS_ERR os_err;
  OS_MSG_SIZE msg_size;
  (void) p_arg;
  static char rstr[64];
  while (DEF_TRUE)
    {
      key_value = (uint16_t *) OSQPend (&KEY_Q, 1000,
      OS_OPT_PEND_BLOCKING,
					&msg_size,
					NULL,
					&os_err);
      if (os_err == OS_ERR_NONE)
	{
	  sprintf ((char *) rstr, "->num:%3dm_size is:%d.",
		   (int) (*(uint8_t *) (key_value + 10)), (int) msg_size);
	  printf ("%s\r\n", rstr);
	  GUI_DispStringAt ((const char *) rstr, 0, 100);
	  for (int i = 0; i < *(uint8_t *) (key_value + 10); i++)
	    {
	      sprintf ((char *) rstr, "point%dx is %3d,y is %3d.",
		       (int) (*(uint8_t *) (key_value + 10)),
		       (int) (*(uint16_t *) (key_value + i)),
		       (int) (*(uint16_t *) (key_value + 5 + i)));
	      GUI_DispStringAt ((const char *) rstr, 0, 400);
	      printf ("%s\r\n", rstr);
	    }
	}
    }
}

static void
AppTaskObj4 (void *p_arg)
{
  OS_ERR os_err;
  (void) p_arg;
  static char rstr[64];
  char nand_mode[32];
    uint32_t nand_id;
  __HAL_RCC_CRC_CLK_ENABLE()
    ;
    GUI_Init ();
    USBH_Init(&USB_Host,&usbh_pUsrFunc,USB_OTG_FS_CORE_ID);
    USBH_RegisterClass(&USB_Host,&USBH_msc);
    USBH_Start(&USB_Host);
    GUI_SetBkColor (BK_HY_COLOR);
    GUI_Clear ();
    GUI_CURSOR_Show ();
    GUI_CURSOR_Select (&GUI_CursorCrossL);
    GUI_PID_STATE touchState;
    GUI_TOUCH_Calibrate (GUI_COORD_X, 0, m19.width, 0, m19.width - 1);
    GUI_TOUCH_Calibrate (GUI_COORD_Y, 0, m19.height, 0, m19.height - 1);
    GUI_DispStringAt ("iysheng@163.com", 100, 100);
    while (DEF_TRUE)
      {
	GUI_TOUCH_GetState (&touchState);
	      GUI_GotoXY (0, 250);
	      GUI_DispString ("x:");
	      GUI_DispDec ((touchState.x)++, 4);
	      GUI_DispString (" y:");
	      GUI_DispDec (touchState.y, 4);
	      nand_id = NAND_ReadID ();
	      sprintf (nand_mode, "%x", (unsigned int) nand_id);
	      printf ("nand_mode is %s.\r\n", nand_mode);
	      SD_ShowCardInfo ();
	      USBH_Process(&USB_Host);
	      for(nand_id=0;nand_id++;nand_id<0xfffff);
	      //OSTimeDlyHMSM (0, 0, 10, 0, OS_OPT_TIME_DLY, &os_err);
      }
}
static void
AppTaskObj5 (void *p_arg)
{
  OS_ERR os_err;
  (void) p_arg;
  uint32_t ret;
  PCF8574_Init();
  printf("start---net---lwip\r\n");
  do{
    ret = lwip_comm_init();
    printf("waiting---net---init\r\n");
  } while(ret==1);
#if LWIP_DHCP
  while((lwipdev.dhcpstatus!=2)&&(lwipdev.dhcpstatus!=0XFF))//等待DHCP获取成功/超时溢出
  	{
  		lwip_periodic_handle();	//LWIP内核需要定时处理的函数
  		printf("waiting---net---dhcp\r\n");
  	}
#endif
  while (DEF_TRUE)
        {
      printf("hello net lwip\r\n");
      //tcp_server_test();
      tcp_client_test();
        }
}
void
MessQueue_Init (void)
{
  OS_ERR p_err;
  OSQCreate (&KEY_Q, "Touch key messgae queue", 5, &p_err);
  if (p_err != OS_ERR_NONE)
    APP_TRACE_INFO(("Create KEY_Q failed.\r\n"));
  OSQCreate (&RPM_Q, "Round per minnet messgae queue", 5, &p_err);
  if (p_err != OS_ERR_NONE)
    APP_TRACE_INFO(("Create RPM_Q failed.\r\n"));
}
