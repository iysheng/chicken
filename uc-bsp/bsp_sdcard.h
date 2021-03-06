/*
 * bsp_sdcard.h
 *
 *  Created on: 2017年9月14日
 *      Author: iysheng
 */

#ifndef UC_BSP_BSP_SDCARD_H_
#define UC_BSP_BSP_SDCARD_H_

#define SD_TIMEOUT      ((uint32_t)100000000)       //超时时间
#define SD_DMA_MODE     0	                        //1：DMA模式，0：查询模式

extern SD_HandleTypeDef        SDCARD_Handler;      //SD卡句柄
extern HAL_SD_CardInfoTypeDef  SDCardInfo;          //SD卡信息结构体

uint8_t SD_Init(void);
uint8_t SD_GetCardInfo(HAL_SD_CardInfoTypeDef *cardinfo);
uint8_t SD_ReadDisk(uint8_t* buf,uint32_t sector,uint8_t cnt);
uint8_t SD_WriteDisk(uint8_t *buf,uint32_t sector,uint8_t cnt);
uint8_t SD_ReadBlocks_DMA(uint32_t *buf,uint64_t sector,uint32_t blocksize,uint32_t cnt);
uint8_t SD_WriteBlocks_DMA(uint32_t *buf,uint64_t sector,uint32_t blocksize,uint32_t cnt);

#endif /* UC_BSP_BSP_SDCARD_H_ */
