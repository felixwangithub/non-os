#include "stdio.h"
#include "lcd.h"

void uart_init(void);
void timer_init(unsigned long ms);
void irq_init(void);

extern volatile int hh,mm,ss;


int main()
{
	
	lcd_init();
	
	lcd_clear_screen(Black);

  lcd_set_backcolor(Black);

  lcd_set_fontcolor(Yellow);

	//printf("\r\ndebug:lcd initialized!\r\n");
	
	timer_init(1000);
	irq_init();
	
	while (1)
	{
		printf("\r%02d : %02d : %02d\r",hh,mm,ss);
		
	}
	
	return 0;
}
