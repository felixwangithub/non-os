#ifndef __LCD_S70_H__
#define __LCD_S70_H__

#ifdef __cplusplus
extern "C" {
#endif

#define GPECON  (*((volatile unsigned long *)0x7F008080))
#define GPEDAT  (*((volatile unsigned long *)0x7F008084))
#define GPEPUD  (*((volatile unsigned long *)0x7F008088))
#define GPFCON  (*((volatile unsigned long *)0x7F0080A0))
#define GPFDAT  (*((volatile unsigned long *)0x7F0080A4))
#define GPFPUD  (*((volatile unsigned long *)0x7F0080A8))
#define GPICON  (*((volatile unsigned long *)0x7F008100))
#define GPIPUD  (*((volatile unsigned long *)0x7F008108))
#define GPJCON  (*((volatile unsigned long *)0x7F008120))
#define GPJPUD  (*((volatile unsigned long *)0x7F008128))

/* display controller */
#define MIFPCON  	    (*((volatile unsigned long *)0x7410800C))
#define SPCON        	(*((volatile unsigned long *)0x7F0081A0))
#define VIDCON0      	(*((volatile unsigned long *)0x77100000))
#define VIDCON1      	(*((volatile unsigned long *)0x77100004))
#define VIDTCON0     	(*((volatile unsigned long *)0x77100010))
#define VIDTCON1     	(*((volatile unsigned long *)0x77100014))
#define VIDTCON2     	(*((volatile unsigned long *)0x77100018))
#define WINCON0      	(*((volatile unsigned long *)0x77100020))
#define VIDOSD0A      	(*((volatile unsigned long *)0x77100040))
#define VIDOSD0B      	(*((volatile unsigned long *)0x77100044))
#define VIDOSD0C      	(*((volatile unsigned long *)0x77100048))
#define VIDW00ADD0B0    (*((volatile unsigned long *)0x771000A0))
#define VIDW00ADD1B0    (*((volatile unsigned long *)0x771000D0))
#define VIDW00ADD2      (*((volatile unsigned long *)0x77100100))
#define DITHMODE        (*((volatile unsigned long *)0x77100170))

#define FRAME_BUFFER   		0x54000000
#define ROW					480
#define COL					800
#define HSPW 				0
#define HBPD			 	(46 - 1)
#define HFPD 				(210 - 1)
#define VSPW				0
#define VBPD 				(23 - 1)
#define VFPD 				(22 - 1)
#define LINEVAL 			(479)
#define HOZVAL				(799)

void LCD_S70_Init(void);
void LCD_ClearScreen(unsigned int Color);
void LCD_SetPixel(unsigned int x, unsigned int y, unsigned int Color);
unsigned int LCD_GetPixel(unsigned int x, unsigned int y);
void LCD_RectFill(int x0, int y0, int x1, int y1,int color);

#ifdef __cplusplus
}
#endif

#endif
