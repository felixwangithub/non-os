
#include "lcd_s70.h"

// 初始化LCD
void  LCD_S70_Init(void)
{
	// 配置GPIO用于LCD相关的功能
	GPICON = 0xAAAAAAAA;
	GPJCON = 0x00AAAAAA;

	// normal mode
	MIFPCON &= ~(1<<3);

	// RGB I/F
	SPCON =  (SPCON & ~(0x3)) | 1;

	// 配置VIDCONx，设置接口类型、时钟、极性和使能LCD控制器等
	// 16位
	VIDCON0 = (0<<26)|(0<<17)|(0<<16)|(0<<6)|(0<<5)|(1<<4)|(0<<2)|(3<<0);
	// HSYNC  VSYNC 反转
	VIDCON1 |= 1<<5 | 1<<6;

	// 配置VIDTCONx，设置时序和长宽等
	// 设置时序
	VIDTCON0 = VBPD<<16 | VFPD<<8 | VSPW<<0;
	VIDTCON1 = HBPD<<16 | HFPD<<8 | HSPW<<0;
	// 设置长宽
	VIDTCON2 = (LINEVAL << 11) | (HOZVAL << 0);


	// 配置WINCON0，设置window0的数据格式
	// 配置RGB位数: 24BPP
	WINCON0 |= 1<<0;
	WINCON0 &= ~(0xf << 2);
	//WINCON0 |= 0x5<<2;
	//WINCON0 |= 0x1<<16;//当字体颠倒
	WINCON0 |= 0xB<<2;

	// 配置VIDOSD0A/B/C,设置window0的坐标系
#define LeftTopX     0
#define LeftTopY     0
#define RightBotX   799
#define RightBotY   479
	VIDOSD0A = (LeftTopX<<11) | (LeftTopY << 0);
	VIDOSD0B = (RightBotX<<11) | (RightBotY << 0);
	VIDOSD0C = (LINEVAL + 1) * (HOZVAL + 1);

	// 置VIDW00ADD0B0和VIDW00ADD1B0，设置framebuffer的地址
	VIDW00ADD0B0 = FRAME_BUFFER;
	VIDW00ADD1B0 = (((HOZVAL + 1)*4 + 0) * (LINEVAL + 1)) & (0xffffff);
}



void LCD_SetPixel(unsigned int x, unsigned int y, unsigned int Color)
{
	unsigned long * pixel = (unsigned long  *)FRAME_BUFFER;

	*(pixel + y * COL + x) = Color;
	
}

unsigned int LCD_GetPixel(unsigned int x, unsigned int y)
{
	unsigned long * pixel = (unsigned long  *)FRAME_BUFFER;
		
	return *(pixel + y * COL + x);
}

void LCD_ClearScreen(unsigned int Color)
{
	int i, j;

	for (i = 0; i < ROW; i++)
		for (j = 0; j < COL; j++)
			LCD_SetPixel(j, i, Color);
}

//画实心矩形: 矩形起左上顶点(x0,y0);右下顶点(x1,y1) 
void LCD_RectFill(int x0, int y0, int x1, int y1,int color) 
{ 
    int i,j; 
    if(x0>x1){i=x0;x0=x1;x1=i;} 
    if(y0>y1){i=y0;y0=y1;y1=i;} 
    for(i=y0;i<y1+1;i++) 
    { 
        for(j=x0;j<x1+1;j++) 
        LCD_SetPixel(j,i,color); 
    } 
}







