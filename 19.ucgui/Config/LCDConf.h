#ifndef LCDCONF_H
#define LCDCONF_H

#include "lcd_s70.h"

/*********************************************************************
*                   General configuration of LCD
**********************************************************************
*/
#define LCD_XSIZE          (800)    /* ��Xˮƽ���ص� */
#define LCD_YSIZE          (480)    /* ��Yˮƽ���ص� */
#define LCD_BITSPERPIXEL   (24)	    /* 24λɫ�� */
#define LCD_CONTROLLER     (-1)	    /* �꿪��,ʹ��LCDDriver������ģ�� */
#define LCD_FIXEDPALETTE   (888)    /* R:8-G:8-B:8 */
#define LCD_SWAP_RB        (1)	    /* RB��ɫ���� */
#define LCD_SWAP_XY        (0)	    /* ��x,y���򲻵��� */
#define LCD_INIT_CONTROLLER()   LCD_S70_Init() /* ��������ʼ���ӿ� */

#endif /* LCDCONF_H */

