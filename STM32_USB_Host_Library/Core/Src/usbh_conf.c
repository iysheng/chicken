/**
 ******************************************************************************
 * @file    usb_bsp.c
 * @author  MCD Application Team
 * @version V3.2.2
 * @date    07-July-2015
 * @brief   This file implements the board support package for the USB host library
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT 2015 STMicroelectronics</center></h2>
 *
 * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at:
 *
 *        http://www.st.com/software_license_agreement_liberty_v2
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "usbh_core.h"
#include "main.h"

HCD_HandleTypeDef hhcd;

#if 0
/**
 * @brief  USBH_LL_Init
 *         Initialize the Low Level portion of the Host driver.
 * @param  phost: Host handle
 * @retval USBH Status
 */
USBH_StatusTypeDef
USBH_LL_Init (USBH_HandleTypeDef *phost)
  {
    __HAL_RCC_USB_OTG_FS_CLK_ENABLE()
    ; //使能OTG FS时钟
    if (USB_OTG_FS_CORE_ID == phost->id)
      {
	/* Set the LL Driver parameters */
	hhcd.Instance = USB_OTG_FS;
	hhcd.Init.Host_channels = 11;
	hhcd.Init.dma_enable = 0;
	hhcd.Init.low_power_enable = 0;
	hhcd.Init.phy_itface = HCD_PHY_EMBEDDED;
	hhcd.Init.Sof_enable = 0;
	hhcd.Init.speed = HCD_SPEED_FULL;
	hhcd.Init.vbus_sensing_enable = 0;
	hhcd.Init.lpm_enable = 0;
	/* Link the driver to the stack */
	hhcd.pData = phost;
	phost->pData = &hhcd;
	HAL_HCD_Init (&hhcd);
      }
    return USBH_OK;
  }
#endif

void
HAL_HCD_MspInit (HCD_HandleTypeDef *hhcd)
{
  if (USB_OTG_FS == hhcd->Instance)
    {
      GPIO_InitTypeDef GPIO_InitStruct;
      __HAL_RCC_GPIOA_CLK_ENABLE()
      ;                   //使能GPIOA时钟
      //配置PA11 12
      GPIO_InitStruct.Pin = GPIO_PIN_11 | GPIO_PIN_12;    //PA11 12
      GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;           //复用
      GPIO_InitStruct.Pull = GPIO_NOPULL;               //无上下拉
      GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;          //高速
      GPIO_InitStruct.Alternate = GPIO_AF10_OTG_FS;     //复用为OTG FS
      HAL_GPIO_Init (GPIOA, &GPIO_InitStruct);         //初始化
      /* Enable USB FS Clocks */
      __HAL_RCC_USB_OTG_FS_CLK_ENABLE()
      ;
      //使能中断
      HAL_NVIC_SetPriority (OTG_FS_IRQn, 0, 3);          //抢占优先级0，子优先级3
      HAL_NVIC_EnableIRQ (OTG_FS_IRQn);                //使能OTG USB FS中断
    }
}
/**
 * @brief  DeInitializes the HCD MSP.
 * @param  hhcd: HCD handle
 * @retval None
 */
void
HAL_HCD_MspDeInit (HCD_HandleTypeDef *hhcd)
{
  if (hhcd->Instance == USB_OTG_FS)
    {
      /* Disable USB FS Clocks */
      __HAL_RCC_USB_OTG_FS_CLK_DISABLE();
    }
  else if (hhcd->Instance == USB_OTG_HS)
    {
      /* Disable USB HS Clocks */
      __HAL_RCC_USB_OTG_HS_CLK_DISABLE();
      __HAL_RCC_USB_OTG_HS_ULPI_CLK_DISABLE();
    }
}
/**
 * @brief  SOF callback.
 * @param  hhcd: HCD handle
 * @retval None
 */
void
HAL_HCD_SOF_Callback (HCD_HandleTypeDef *hhcd)
{
  USBH_LL_IncTimer (hhcd->pData);
}
/**
 * @brief  Connect callback.
 * @param  hhcd: HCD handle
 * @retval None
 */
void
HAL_HCD_Connect_Callback (HCD_HandleTypeDef *hhcd)
{
  USBH_LL_Connect (hhcd->pData);
}
/**
 * @brief  Disconnect callback.
 * @param  hhcd: HCD handle
 * @retval None
 */
void
HAL_HCD_Disconnect_Callback (HCD_HandleTypeDef *hhcd)
{
  USBH_LL_Disconnect (hhcd->pData);
}
/**
 * @brief  USBH_LL_DeInit
 *         De-Initialize the Low Level portion of the Host driver.
 * @param  phost: Host handle
 * @retval USBH Status
 */
USBH_StatusTypeDef
USBH_LL_DeInit (USBH_HandleTypeDef *phost)
{
  HAL_HCD_DeInit (phost->pData);
  return USBH_OK;
}

/*******************************************************************************
 LL Driver Interface (USB Host Library --> HCD)
 *******************************************************************************/
/**
 * @brief  USBH_LL_Init
 *         Initialize the Low Level portion of the Host driver.
 * @param  phost: Host handle
 * @retval USBH Status
 */
#if 1
USBH_StatusTypeDef
USBH_LL_Init (USBH_HandleTypeDef *phost)
{
  /* Set the LL Driver parameters */
  hhcd.Instance = USB_OTG_FS;
  hhcd.Init.Host_channels = 11;
  hhcd.Init.dma_enable = 0;
  hhcd.Init.low_power_enable = 0;
  hhcd.Init.phy_itface = HCD_PHY_EMBEDDED;
  hhcd.Init.Sof_enable = 0;
  hhcd.Init.speed = HCD_SPEED_FULL;
  hhcd.Init.vbus_sensing_enable = 0;
  hhcd.Init.lpm_enable = 0;

  /* Link the driver to the stack */
  hhcd.pData = phost;
  phost->pData = &hhcd;

  /* Initialize the LL Driver */
  HAL_HCD_Init (&hhcd);
  USBH_LL_SetTimer (phost, HAL_HCD_GetCurrentFrame (&hhcd));

  return USBH_OK;
}
#endif

/**
 * @brief  USBH_LL_Start
 *         Start the Low Level portion of the Host driver.
 * @param  phost: Host handle
 * @retval USBH Status
 */
USBH_StatusTypeDef
USBH_LL_Start (USBH_HandleTypeDef *phost)
{
  HAL_HCD_Start (phost->pData);
  return USBH_OK;
}

/**
 * @brief  USBH_LL_Stop
 *         Stop the Low Level portion of the Host driver.
 * @param  phost: Host handle
 * @retval USBH Status
 */
USBH_StatusTypeDef
USBH_LL_Stop (USBH_HandleTypeDef *phost)
{
  HAL_HCD_Stop (phost->pData);
  return USBH_OK;
}

/**
 * @brief  USBH_LL_GetSpeed
 *         Return the USB Host Speed from the Low Level Driver.
 * @param  phost: Host handle
 * @retval USBH Speeds
 */
USBH_SpeedTypeDef
USBH_LL_GetSpeed (USBH_HandleTypeDef *phost)
{
  USBH_SpeedTypeDef speed = USBH_SPEED_FULL;
  switch (HAL_HCD_GetCurrentSpeed (phost->pData))
    {
    case 0:
      speed = USBH_SPEED_HIGH;
      break;

    case 1:
      speed = USBH_SPEED_FULL;
      break;

    case 2:
      speed = USBH_SPEED_LOW;
      break;

    default:
      speed = USBH_SPEED_FULL;
      break;
    }
  return speed;
}

/**
 * @brief  USBH_LL_ResetPort
 *         Reset the Host Port of the Low Level Driver.
 * @param  phost: Host handle
 * @retval USBH Status
 */
USBH_StatusTypeDef
USBH_LL_ResetPort (USBH_HandleTypeDef *phost)
{
  HAL_HCD_ResetPort (phost->pData);
  return USBH_OK;
}

/**
 * @brief  USBH_LL_GetLastXferSize
 *         Return the last transferred packet size.
 * @param  phost: Host handle
 * @param  pipe: Pipe index
 * @retval Packet Size
 */
uint32_t
USBH_LL_GetLastXferSize (USBH_HandleTypeDef *phost, uint8_t pipe)
{
  return HAL_HCD_HC_GetXferCount (phost->pData, pipe);;
}

/**
 * @brief  USBH_LL_OpenPipe
 *         Open a pipe of the Low Level Driver.
 * @param  phost: Host handle
 * @param  pipe_num: Pipe index
 * @param  epnum: Endpoint Number
 * @param  dev_address: Device USB address
 * @param  speed: Device Speed
 * @param  ep_type: Endpoint Type
 * @param  mps: Endpoint Max Packet Size
 * @retval USBH Status
 */
USBH_StatusTypeDef
USBH_LL_OpenPipe (USBH_HandleTypeDef *phost, uint8_t pipe_num, uint8_t epnum,
		  uint8_t dev_address, uint8_t speed, uint8_t ep_type,
		  uint16_t mps)
{
  HAL_HCD_HC_Init (phost->pData, pipe_num, epnum, dev_address, speed, ep_type,
		   mps);
  return USBH_OK;
}

/**
 * @brief  USBH_LL_ClosePipe
 *         Close a pipe of the Low Level Driver.
 * @param  phost: Host handle
 * @param  pipe_num: Pipe index
 * @retval USBH Status
 */
USBH_StatusTypeDef
USBH_LL_ClosePipe (USBH_HandleTypeDef *phost, uint8_t pipe)
{
  HAL_HCD_HC_Halt (phost->pData, pipe);
  return USBH_OK;
}

/**
 * @brief  USBH_LL_SubmitURB
 *         Submit a new URB to the low level driver.
 * @param  phost: Host handle
 * @param  pipe: Pipe index
 *         This parameter can be a value from 1 to 15
 * @param  direction : Channel number
 *          This parameter can be one of the these values:
 *           0 : Output
 *           1 : Input
 * @param  ep_type : Endpoint Type
 *          This parameter can be one of the these values:
 *            @arg EP_TYPE_CTRL: Control type
 *            @arg EP_TYPE_ISOC: Isochronous type
 *            @arg EP_TYPE_BULK: Bulk type
 *            @arg EP_TYPE_INTR: Interrupt type
 * @param  token : Endpoint Type
 *          This parameter can be one of the these values:
 *            @arg 0: PID_SETUP
 *            @arg 1: PID_DATA
 * @param  pbuff : pointer to URB data
 * @param  length : Length of URB data
 * @param  do_ping : activate do ping protocol (for high speed only)
 *          This parameter can be one of the these values:
 *           0 : do ping inactive
 *           1 : do ping active
 * @retval Status
 */

USBH_StatusTypeDef
USBH_LL_SubmitURB (USBH_HandleTypeDef *phost, uint8_t pipe, uint8_t direction,
		   uint8_t ep_type, uint8_t token, uint8_t* pbuff,
		   uint16_t length, uint8_t do_ping)
{
  HAL_HCD_HC_SubmitRequest (phost->pData, pipe, direction, ep_type, token,
			    pbuff, length, do_ping);
  return USBH_OK;
}

/**
 * @brief  USBH_LL_GetURBState
 *         Get a URB state from the low level driver.
 * @param  phost: Host handle
 * @param  pipe: Pipe index
 *         This parameter can be a value from 1 to 15
 * @retval URB state
 *          This parameter can be one of the these values:
 *            @arg URB_IDLE
 *            @arg URB_DONE
 *            @arg URB_NOTREADY
 *            @arg URB_NYET
 *            @arg URB_ERROR
 *            @arg URB_STALL
 */
USBH_URBStateTypeDef
USBH_LL_GetURBState (USBH_HandleTypeDef *phost, uint8_t pipe)
{
  return (USBH_URBStateTypeDef) HAL_HCD_HC_GetURBState (phost->pData, pipe);
}

/**
 * @brief  USBH_LL_DriverVBUS
 *         Drive VBUS.
 * @param  phost: Host handle
 * @param  state : VBUS state
 *          This parameter can be one of the these values:
 *           0 : VBUS Active
 *           1 : VBUS Inactive
 * @retval Status
 */

USBH_StatusTypeDef
USBH_LL_DriverVBUS (USBH_HandleTypeDef *phost, uint8_t state)
{

  return USBH_OK;
}

/**
 * @brief  USBH_LL_SetToggle
 *         Set toggle for a pipe.
 * @param  phost: Host handle
 * @param  pipe: Pipe index
 * @param  pipe_num: Pipe index
 * @param  toggle: toggle (0/1)
 * @retval Status
 */
USBH_StatusTypeDef
USBH_LL_SetToggle (USBH_HandleTypeDef *phost, uint8_t pipe, uint8_t toggle)
{
  if (hhcd.hc[pipe].ep_is_in)
    {
      hhcd.hc[pipe].toggle_in = toggle;
    }
  else
    {
      hhcd.hc[pipe].toggle_out = toggle;
    }
  return USBH_OK;
}

/**
 * @brief  USBH_LL_GetToggle
 *         Return the current toggle of a pipe.
 * @param  phost: Host handle
 * @param  pipe: Pipe index
 * @retval toggle (0/1)
 */
uint8_t
USBH_LL_GetToggle (USBH_HandleTypeDef *phost, uint8_t pipe)
{
  uint8_t toggle = 0;

  if (hhcd.hc[pipe].ep_is_in)
    {
      toggle = hhcd.hc[pipe].toggle_in;
    }
  else
    {
      toggle = hhcd.hc[pipe].toggle_out;
    }
  return toggle;
}
/**
 * @brief  USBH_Delay
 *         Delay routine for the USB Host Library
 * @param  Delay: Delay in ms
 * @retval None
 */
void
USBH_Delay (uint32_t Delay)
{
  HAL_Delay (Delay);
}

/*
 * 中断处理函数
 */
#if 1
void
OTG_FS_IRQHandler (void)
{
  HAL_HCD_IRQHandler (&hhcd);
  //USBH_OTG_ISR_Handler(&USB_OTG_Core);
}
#endif
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
