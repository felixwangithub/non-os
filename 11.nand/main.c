#include "uart.h"

int main()
{
	char c;
	
	uart_init();

	putstr("Uart Initialized!\n\r");
	while (1)
	{
		c = getchar();
		putchar(c);
	}
	
	return 0;
}
