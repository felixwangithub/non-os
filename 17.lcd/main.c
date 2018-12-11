#include "stdio.h"
#include "lcd.h"

void uart_init(void);
void timer_init(unsigned long ms);


int main()
{
	
	lcd_init();
	
	lcd_clear_screen(Black);

  lcd_set_backcolor(Black);

  lcd_set_fontcolor(Yellow);

	printf("\r\nLCD INITIALIZED!\r\n");
	
	while (1);
	
	return 0;
}
