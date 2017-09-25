/*
 * bsp_rgb.h
 *
 *  Created on: 2017年9月8日
 *      Author: iysheng
 */

#ifndef USR_BSP_RGB_H_
#define USR_BSP_RGB_H_
struct rgb_parameter{
  uint32_t width;
  uint32_t height;
  uint32_t hsw;
  uint32_t vsw;
  uint32_t hbp;
  uint32_t vbp;
  uint32_t hfp;
  uint32_t vfp;
};
//画笔颜色
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000
#define BLUE         	 0x001F
#define BRED             0XF81F
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40 //棕色
#define BRRED 			 0XFC07 //棕红色
#define GRAY  			 0X8430 //灰色
//GUI颜色

#define DARKBLUE      	 0X01CF	//深蓝色
#define LIGHTBLUE      	 0X7D7C	//浅蓝色
#define GRAYBLUE       	 0X5458 //灰蓝色
//以上三色为PANEL的颜色
/*
 * 护眼色、豆沙绿 BGR
 */
#define BK_HY_COLOR 0xcfe8cc

#define LIGHTGREEN     	 0X841F //浅绿色
//#define LIGHTGRAY        0XEF5B //浅灰色(PANNEL)
#define LGRAY 			 0XC618 //浅灰色(PANNEL),窗体背景色

#define LGRAYBLUE        0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE           0X2B12 //浅棕蓝色(选择条目的反色)

LTDC_HandleTypeDef LTDC_Handler;	    //LTDC句柄
#define LCD_LED(n)              (n?HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_RESET))   //LCD背光PD13
#define LCD_PIXEL_FORMAT_RGB565         0X02
//定义颜色像素格式,一般用RGB565
#define LCD_PIXFORMAT				LCD_PIXEL_FORMAT_RGB565
#define LCD_BUFFER_ADDR				0XC0000000
#define LCD_BACK_COLOR				0x000000

int
RGB_Init (struct rgb_parameter *mode);
#endif /* USR_BSP_RGB_H_ */
