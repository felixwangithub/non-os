
volatile unsigned long *gpkcon0 = (volatile unsigned long *)0x7F008800;
volatile unsigned long *gpkdat = (volatile unsigned long *)0x7F008808;

//延时

void delay(void)
{
	volatile int i=0x10000;
	while(i--);
}

int main(void)
{
	*gpkcon0 = 0x11110000;	//设置gpk4、5、6、7为输出
	while(1)
	{
		*gpkdat = 0x00;
		delay();
		*gpkdat = 0xf0;
		delay();
	}	
}

