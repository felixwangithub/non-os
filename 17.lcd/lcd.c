
#include "lcd.h"
#include "font_8x16.h"

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

#define FRAME_BUFFER    0x54000000
#define ROW				      480
#define COL				      800
#define HSPW 				    0
#define HBPD			 	    (46 - 1)
#define HFPD 				    (210 - 1)
#define VSPW				    0
#define VBPD 				    (23 - 1)
#define VFPD 				    (22 - 1)
#define LINEVAL 			  (479)
#define HOZVAL				  (799)

volatile static unsigned int FONTCOLOR;
volatile static unsigned int BACKCOLOR;


// 初始化LCD
void lcd_init(void)
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
	// 配置RGB位数
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

void lcd_set_pixel(unsigned int x, unsigned int y, unsigned int color)
{
	unsigned long * pixel = (unsigned long  *)FRAME_BUFFER;

	*(pixel + y * COL + x) = color;
	
}

unsigned int lcd_get_pixel(unsigned int x, unsigned int y)
{
	unsigned long * pixel = (unsigned long  *)FRAME_BUFFER;
		
	return *(pixel + y * COL + x);
}

void lcd_clear_screen(unsigned int color)
{
	int i, j;

	for (i = 0; i < ROW; i++)
		for (j = 0; j < COL; j++)
			lcd_set_pixel(j, i, color);
}

void lcd_set_backcolor(unsigned int backcolor)
{
	BACKCOLOR = backcolor;
}

void lcd_set_fontcolor(unsigned int fontcolor)
{
	FONTCOLOR = fontcolor;
}

//画实心矩形: 矩形起左上顶点(x0,y0);右下顶点(x1,y1) 
void lcd_rect_fill(int x0, int y0, int x1, int y1,int color) 
{ 
    int i,j; 
    if(x0>x1){i=x0;x0=x1;x1=i;} 
    if(y0>y1){i=y0;y0=y1;y1=i;} 
    for(i=y0;i<y1+1;i++) 
    { 
        for(j=x0;j<x1+1;j++) 
        lcd_set_pixel(j,i,color); 
    } 
}

// 打印字符
//#define FONTDATAMAX 2048
//extern const unsigned char fontdata_8x8[FONTDATAMAX];

//#define FONTDATAMAX 4096  
  
//extern const unsigned char fontdata_8x16[FONTDATAMAX];


void lcd_draw_char(unsigned char c)
{
	// 必须是静态变量
	static int x = 0;	// 第几列
	static int y = 0;	// 第几行

	int i,j;
	unsigned char line_dots;

	// 获得字模
	const unsigned char *char_dots = fontdata_8x16 + c * 16;


	// 是否需要回车换行
	if (c == '\n')
	{
		y += 16;
		if (y > ROW)
			y = 0;
		return ;
	}
	else if (c == '\r')
	{
		x = 0;
		return;
	}

	for (i = 0; i < 16; i++)
	{
		line_dots = char_dots[i];
		for (j = 0; j < 8; j++)
		{
			// 为1,则描白点
			if (line_dots & (0x80 >> j))
			{
				lcd_set_pixel(x+j, y+i, FONTCOLOR);
			}
			// 为0,则描黑点
			else
			{
				lcd_set_pixel(x+j, y+i, BACKCOLOR);
			}
		}
	}

	// 光标移动到下一个16*16的位置，首先坐标+16
	x += 8;
	if (x > COL)
		x = 0;
	// 如果x坐标=0,则y坐标+16
	if (x == 0)
	{
		y += 16;
		if (y > ROW)
			y = 0;
	}
}



