/*
 * bsp_tim.c
 *
 *  Created on: 2017年5月14日
 *      Author: iysheng
 */

#include "main.h"

TIM_HandleTypeDef ITIM2,ITIM3,ITIM4,ITIM5;
TIM_MasterConfigTypeDef iMasterConfig;
TIM_OC_InitTypeDef iConfig;
int32_t ic_value[2];//捕获的计数值
extern OS_Q RPM_Q;
extern OS_TCB      AppTaskObj1TCB;
extern uint32_t lwip_localtime;		//lwip本地时间计数器,单位:ms
void TIM2_init(void)
{
  __HAL_RCC_TIM2_CLK_ENABLE();
  ITIM2.Instance=TIM2;
  ITIM2.Init.Period=1999;//周期为1999<-->1000ms,频率1Hz
  ITIM2.Init.Prescaler=53999;//APB1=108MHz,采样时钟间隔为500us，频率为2khz
  ITIM2.Init.CounterMode=TIM_COUNTERMODE_UP;
  HAL_TIM_Base_Init(&ITIM2);
  iMasterConfig.MasterOutputTrigger=TIM_TRGO_UPDATE;
  iMasterConfig.MasterSlaveMode=TIM_MASTERSLAVEMODE_ENABLE;
  HAL_TIMEx_MasterConfigSynchronization(&ITIM2,&iMasterConfig);
  HAL_TIM_Base_Start_IT(&ITIM2);
}

void TIM3_init(void)
{
  __HAL_RCC_TIM3_CLK_ENABLE();
  ITIM3.Instance=TIM3;
  ITIM3.Init.Period=499;//周期为1999<-->1000ms，频率为1hz
  ITIM3.Init.Prescaler=53999;//采样时钟间隔为500us，频率为2khz
  ITIM3.Init.CounterMode=TIM_COUNTERMODE_UP;
  HAL_TIM_PWM_Init(&ITIM3);
  iConfig.OCMode=TIM_OCMODE_PWM1;
  iConfig.Pulse=299;
  iConfig.OCPolarity=TIM_OCPOLARITY_HIGH;
  HAL_TIM_PWM_ConfigChannel(&ITIM3,&iConfig,TIM_CHANNEL_4);//PB1
  HAL_TIM_PWM_Start(&ITIM3,TIM_CHANNEL_4);
  //HAL_TIM_PWM_ConfigChannel(&ITIM3,&iConfig,TIM_CHANNEL_3); //PB0
  //HAL_TIM_PWM_Start(&ITIM3,TIM_CHANNEL_3);
}

void TIM4_Init()
{
  __HAL_RCC_TIM4_CLK_ENABLE();
  ITIM4.Instance=TIM4;                          //通用定时器3
  ITIM4.Init.Prescaler=1079;                     //分频
  ITIM4.Init.CounterMode=TIM_COUNTERMODE_UP;    //向上计数器
  ITIM4.Init.Period=999;                        //自动装载值
  ITIM4.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;//时钟分频因子
  HAL_TIM_Base_Init(&ITIM4);
  HAL_TIM_Base_Start_IT(&ITIM4); //使能定时器3和定时器3更新中断：TIM_IT_UPDATE
}

void TIM5_init(void)
{
  static TIM_IC_InitTypeDef IC_Config;
  __HAL_RCC_TIM5_CLK_ENABLE();
  ITIM5.Instance=TIM5;
  ITIM5.Init.Prescaler=107;//107--精度达到1us
  ITIM5.Init.CounterMode=TIM_COUNTERMODE_UP;
  ITIM5.Init.Period=0xffffffff;
  ITIM5.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;
  HAL_TIM_IC_Init(&ITIM5);
  IC_Config.ICPolarity=TIM_ICPOLARITY_RISING;
  IC_Config.ICPrescaler=TIM_ICPSC_DIV1;
  IC_Config.ICFilter=0;
  IC_Config.ICSelection=TIM_ICSELECTION_DIRECTTI;
 // HAL_TIM_IC_ConfigChannel(&ITIM5,&IC_Config,TIM_CHANNEL_1);//TIM_CHANNEL_1 PA0
  //HAL_TIM_IC_Start_IT(&ITIM5,TIM_CHANNEL_1);//开启中断
  HAL_TIM_IC_ConfigChannel(&ITIM5,&IC_Config,TIM_CHANNEL_4);//TIM_CHANNEL_1 PA3
    HAL_TIM_IC_Start_IT(&ITIM5,TIM_CHANNEL_4);//开启中断
  //HAL_TIM_IC_ConfigChannel(&ITIM5,&IC_Config,TIM_CHANNEL_2);//TIM_CHANNEL_2 PA1
  //HAL_TIM_IC_Start_IT(&ITIM5,TIM_CHANNEL_2);//开启中断
}

void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
  GPIO_InitTypeDef  GPIO_Initure;
  if(htim->Instance==TIM3)
  {
  __HAL_RCC_GPIOB_CLK_ENABLE();		//开启GPIOB时钟
  GPIO_Initure.Pin=GPIO_PIN_1; //PB1--CH4 PB0--CH3
  GPIO_Initure.Mode=GPIO_MODE_AF_PP;  //复用推挽输出
  GPIO_Initure.Pull=GPIO_PULLUP;          //上拉
  GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //高速
  GPIO_Initure.Alternate=GPIO_AF2_TIM3;
  HAL_GPIO_Init(GPIOB,&GPIO_Initure);     //GPIOB1、TIM3的4通道，LED0
  }
}

void
HAL_TIM_Base_MspInit (TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM2)
    {
      __HAL_RCC_TIM2_CLK_ENABLE()
      ;
      HAL_NVIC_EnableIRQ (TIM2_IRQn);
      HAL_NVIC_SetPriority (TIM2_IRQn, 0x0, 2);
    }
  else if (htim->Instance == TIM3)
    {
      __HAL_RCC_TIM3_CLK_ENABLE()
      ;
      HAL_NVIC_EnableIRQ (TIM3_IRQn);
      HAL_NVIC_SetPriority (TIM3_IRQn, 0x0, 3);
    }
  else if (htim->Instance == TIM4)
    {
      __HAL_RCC_TIM4_CLK_ENABLE()
      ;            //使能TIM4时钟
      HAL_NVIC_SetPriority (TIM4_IRQn, 1, 0);    //设置中断优先级，抢占优先级1，子优先级3
      HAL_NVIC_EnableIRQ (TIM4_IRQn);          //开启ITM3中断
    }
}

void HAL_TIM_IC_MspInit(TIM_HandleTypeDef *htim)
{
  GPIO_InitTypeDef  GPIO_Initure;
  if(htim->Instance==TIM5)
  {
    __HAL_RCC_TIM5_CLK_ENABLE();
    HAL_NVIC_EnableIRQ(TIM5_IRQn);
    HAL_NVIC_SetPriority(TIM5_IRQn, 0x0, 2);  //开启TIM5中断
    __HAL_RCC_GPIOA_CLK_ENABLE();		//开启GPIOA时钟
    GPIO_Initure.Pin=GPIO_PIN_3; //PA3
    GPIO_Initure.Mode=GPIO_MODE_AF_PP;  //复用推挽输出
    GPIO_Initure.Pull=GPIO_PULLDOWN;          //上拉
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //高速
    GPIO_Initure.Alternate=GPIO_AF2_TIM5;
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);     //GPIOA3、TIM5的4通道
  }
}

/*定时器溢出中断处理函数*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if(htim->Instance==TIM5)
  {
    if((ic_value[0]&0x40)==0x40)
    {
      ic_value[0]++;//溢出次数加 1
    }
  }
  else if(htim->Instance==TIM3)
  {
      //lwip_localtime +=10; //加10
  }
  else if(htim->Instance==TIM4)
   {
       lwip_localtime +=10; //加10
   }
}

void TIM2_IRQHandler(void){
  OSIntEnter();
  HAL_TIM_IRQHandler(&ITIM2);
  BSP_LED_Toggle(2);
  OSIntExit();
}

void TIM3_IRQHandler(void){
  HAL_TIM_IRQHandler(&ITIM3);
}

void TIM4_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&ITIM4);
}

void TIM5_IRQHandler(void){
  OSIntEnter();
   HAL_TIM_IRQHandler(&ITIM5);
  OSIntExit();
}

/*输入捕获中断的回调函数*/
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
  static OS_ERR err;
  if(htim->Instance==TIM5)
  {
	    switch(ic_value[0]>>30)
	    {
	    case 0x00:ic_value[0]=1<<30;ic_value[1]=0x00;__HAL_TIM_DISABLE(htim);__HAL_TIM_SET_COUNTER(htim,0);__HAL_TIM_ENABLE(htim);break;//捕获第一个中断
	    case 0x01:ic_value[0]|=1<<31;ic_value[1]=HAL_TIM_ReadCapturedValue(htim,TIM_CHANNEL_4);
	    OSQPost (&RPM_Q,
	                   (void *)&ic_value[0],
	                   1,
					   OS_OPT_POST_FIFO + OS_OPT_POST_ALL,
	                   &err);
		break;//捕获第二个中断，完成一次周期捕获
	    default:break;
	    }
#if 0
    switch(ic_value[0])
    {
    case 0x00:ic_value[0]=0x40;ic_value[1]=0x00;__HAL_TIM_DISABLE(htim);__HAL_TIM_SET_COUNTER(htim,0);__HAL_TIM_ENABLE(htim);break;//捕获第一个中断
    case 0x40:ic_value[0]|=0x80;ic_value[1]=HAL_TIM_ReadCapturedValue(htim,4);
    OSTaskSemPost(&AppTaskObj1TCB,OS_OPT_POST_NONE,&err);break;//捕获第二个中断，完成一次周期捕获
    default:break;
    }
#endif
  }
}


