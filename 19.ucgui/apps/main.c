
#include "lcd_s70.h"
#include "GUI.h"
#include "GUIDEMO.h"
#include "printf.h"
#include "PROGBAR.h"

void timer_init(unsigned long ms);

int main(void)
{
	//printf("Debug: Uart Initialized!!\n\r");
	GUI_Init();
	//printf("Debug: GUI Initialized!!\n\r");
	timer_init(1);

	while(1)
	{
		//GUIDEMO_Graph();
		GUIDEMO_Navigation();
		GUIDEMO_main();
	}
		
	return 0;
}
