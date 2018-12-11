#ifndef LCDCONF_H
#define LCDCONF_H

#include "lcd_s70.h"

/*********************************************************************
*                   General configuration of LCD
**********************************************************************
*/
#define LCD_XSIZE          (800)    /* 屏X水平像素点 */
#define LCD_YSIZE          (480)    /* 屏Y水平像素点 */
#define LCD_BITSPERPIXEL   (24)	    /* 24位色深 */
#define LCD_CONTROLLER     (-1)	    /* 宏开关,使用LCDDriver下驱动模板 */
#define LCD_FIXEDPALETTE   (888)    /* R:8-G:8-B:8 */
#define LCD_SWAP_RB        (1)	    /* RB颜色调换 */
#define LCD_SWAP_XY        (0)	    /* 屏x,y方向不调换 */
#define LCD_INIT_CONTROLLER()   LCD_S70_Init() /* 屏驱动初始化接口 */

#endif /* LCDCONF_H */

