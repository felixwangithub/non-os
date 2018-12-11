#include "stdio.h"

void init_uart();
void timer_init(unsigned long ms);


int main()
{
	timer_init(1000);   	//1000ms 定时中断

	printf("\r\n#############timer test############\r\n");
	
	while (1);
	
	return 0;
}
