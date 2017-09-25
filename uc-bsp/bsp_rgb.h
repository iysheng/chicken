/*
 * bsp_rgb.h
 *
 *  Created on: 2017��9��8��
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
//������ɫ
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
#define BROWN 			 0XBC40 //��ɫ
#define BRRED 			 0XFC07 //�غ�ɫ
#define GRAY  			 0X8430 //��ɫ
//GUI��ɫ

#define DARKBLUE      	 0X01CF	//����ɫ
#define LIGHTBLUE      	 0X7D7C	//ǳ��ɫ
#define GRAYBLUE       	 0X5458 //����ɫ
//������ɫΪPANEL����ɫ
/*
 * ����ɫ����ɳ�� BGR
 */
#define BK_HY_COLOR 0xcfe8cc

#define LIGHTGREEN     	 0X841F //ǳ��ɫ
//#define LIGHTGRAY        0XEF5B //ǳ��ɫ(PANNEL)
#define LGRAY 			 0XC618 //ǳ��ɫ(PANNEL),���屳��ɫ

#define LGRAYBLUE        0XA651 //ǳ����ɫ(�м����ɫ)
#define LBBLUE           0X2B12 //ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)

LTDC_HandleTypeDef LTDC_Handler;	    //LTDC���
#define LCD_LED(n)              (n?HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_RESET))   //LCD����PD13
#define LCD_PIXEL_FORMAT_RGB565         0X02
//������ɫ���ظ�ʽ,һ����RGB565
#define LCD_PIXFORMAT				LCD_PIXEL_FORMAT_RGB565
#define LCD_BUFFER_ADDR				0XC0000000
#define LCD_BACK_COLOR				0x000000

int
RGB_Init (struct rgb_parameter *mode);
#endif /* USR_BSP_RGB_H_ */
