
volatile unsigned long *gpkcon0 = (volatile unsigned long *)0x7F008800;
volatile unsigned long *gpkdat = (volatile unsigned long *)0x7F008808;
void delay(int count);


int main(void)
{
	*gpkcon0 = 0x11110000;	//设置gpk4、5、6、7为输出
	while(1)
	{
		*gpkdat = 0x00;
		delay(0x1000000);
		*gpkdat = 0xf0;
		delay(0x1000000);
	}	
}

