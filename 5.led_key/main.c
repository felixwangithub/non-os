
/*
* 	GPK4  -->  LED1		|	GPN0  -->  KEY1
*   GPK5  -->  LED2		|	GPN1  -->  KEY2
*	GPK6  -->  LED4		|	GPN2  -->  KEY3
*	GPK7  -->  LED3		|	GPN3  -->  KEY4
*/


#define GPKCON0 (*(volatile unsigned long *)0x7F008800)
#define GPKDAT (*(volatile unsigned long *)0x7F008808)

#define GPNCON (*(volatile unsigned long *)0x7F008830)
#define GPNDAT (*(volatile unsigned long *)0x7F008834)

int main(void)
{
	int key=0;
	GPKCON0 = 0x11110000;			//设置GPK 4、5、6、7为输出
	GPNCON  = 0x00;					//设置GPN 0，1，2，3为输入
	GPKDAT  = 0x000000f0; 			//LED 熄灭

	while(1)
	{
		key = GPNDAT;				//读取按键状态
		if(key & (1<<0))			//如果GPN0 ==1, KEY1没有按下
			GPKDAT |= 1<<4;			//LED1(GPK4)熄灭
		else GPKDAT &= ~(1<<4);    	//LED1(GPK4)点亮

		if(key & (1<<1))			//如果GPN1 ==1, KEY2没有按下
			GPKDAT |= 1<<5;			//LED2(GPK5)熄灭
		else GPKDAT &= ~(1<<5);    	//LED2(GPK5)点亮

		if(key & (1<<2))			//如果GPN2 ==1, KEY3没有按下
			GPKDAT |= 1<<7;			//LED4(GPK7)熄灭
		else GPKDAT &= ~(1<<7);    	//LED4(GPK7)点亮

		if(key & (1<<3))			//如果GPN3 ==1, KEY4没有按下
			GPKDAT |= 1<<6;			//LED3(GPK6)熄灭
		else GPKDAT &= ~(1<<6);    	//LED3(GPK6)点亮
	}
	
	
}