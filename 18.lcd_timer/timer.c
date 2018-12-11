#include "stdio.h"

#define EINT0CON0  			(*((volatile unsigned long *)0x7F008900))
#define EINT0MASK  			(*((volatile unsigned long *)0x7F008920))
#define EINT0PEND  			(*((volatile unsigned long *)0x7F008924))
#define PRIORITY 	    	(*((volatile unsigned long *)0x7F008280))
#define SERVICE     		(*((volatile unsigned long *)0x7F008284))
#define SERVICEPEND 		(*((volatile unsigned long *)0x7F008288))
#define VIC0IRQSTATUS  		(*((volatile unsigned long *)0x71200000))
#define VIC0FIQSTATUS  		(*((volatile unsigned long *)0x71200004))
#define VIC0RAWINTR    		(*((volatile unsigned long *)0x71200008))
#define VIC0INTSELECT  		(*((volatile unsigned long *)0x7120000c))
#define VIC0INTENABLE  		(*((volatile unsigned long *)0x71200010))
#define VIC0INTENCLEAR 		(*((volatile unsigned long *)0x71200014))
#define VIC0PROTECTION 		(*((volatile unsigned long *)0x71200020))
#define VIC0SWPRIORITYMASK 	(*((volatile unsigned long *)0x71200024))
#define VIC0PRIORITYDAISY  	(*((volatile unsigned long *)0x71200028))
#define VIC0ADDRESS        	(*((volatile unsigned long *)0x71200f00))

#define		PWMTIMER_BASE			(0x7F006000)
#define		TCFG0    	( *((volatile unsigned long *)(PWMTIMER_BASE+0x00)) )
#define		TCFG1    	( *((volatile unsigned long *)(PWMTIMER_BASE+0x04)) )
#define		TCON      	( *((volatile unsigned long *)(PWMTIMER_BASE+0x08)) )
#define		TCNTB0    	( *((volatile unsigned long *)(PWMTIMER_BASE+0x0C)) )
#define		TCMPB0    	( *((volatile unsigned long *)(PWMTIMER_BASE+0x10)) )
#define		TCNTO0    	( *((volatile unsigned long *)(PWMTIMER_BASE+0x14)) )
#define		TCNTB1    	( *((volatile unsigned long *)(PWMTIMER_BASE+0x18)) )
#define		TCMPB1    	( *((volatile unsigned long *)(PWMTIMER_BASE+0x1C)) )
#define		TCNTO1    	( *((volatile unsigned long *)(PWMTIMER_BASE+0x20)) )
#define		TCNTB2    	( *((volatile unsigned long *)(PWMTIMER_BASE+0x24)) )
#define		TCMPB2    	( *((volatile unsigned long *)(PWMTIMER_BASE+0x28)) )
#define		TCNTO2    	( *((volatile unsigned long *)(PWMTIMER_BASE+0x2C)) )
#define		TCNTB3    	( *((volatile unsigned long *)(PWMTIMER_BASE+0x30)) )
#define		TCMPB3    	( *((volatile unsigned long *)(PWMTIMER_BASE+0x34)) )
#define		TCNTO3    	( *((volatile unsigned long *)(PWMTIMER_BASE+0x38)) )
#define		TCNTB4    	( *((volatile unsigned long *)(PWMTIMER_BASE+0x3C)) )
#define		TCNTO4    	( *((volatile unsigned long *)(PWMTIMER_BASE+0x40)) )
#define		TINT_CSTAT 	( *((volatile unsigned long *)(PWMTIMER_BASE+0x44)) )

volatile int hh,mm,ss;

void irq_init(void)
{
	/* 在中断控制器里使能timer0中断 */
	VIC0INTENABLE |= (1<<23);
	
	//printf("\r\ndebug:irq_init success!\r\n");

}

// timer0中断的中断处理函数
void do_irq()
{
	ss++;
	
	if(ss > 59)
	{
		ss = 0;
		mm++;
	}
	
	if(mm>59)
	{
		mm = 0;
		hh++;
	}
	
	if(hh>23)
	{
		ss = 0;
		hh = 0;
	}

	//清timer0的中断状态寄存器
	TINT_CSTAT |= 1<<5;      
	

}

// 初始化timer
void timer_init(unsigned long ms)
{
	
	// PCLK = 66MHz
	
	// 定时器的输入时钟 = PCLK / ( {prescaler value + 1} ) / {divider value} = PCLK/(65+1)/1=1Mhz(0.001ms)

	//设置预分频系数为65
	
	TCFG0 |= 65;

	// 1分频, 定时器时钟为1Mhz(0.001ms)
	TCFG1 = 0;

	// 1s = 1Mhz, 1ms = 1000Hz， 1ns = 1Hz
	TCNTB0 = (ms*1000);
	TCMPB0 = 0;

	// 手动更新
	TCON |= 1<<1;

	// 清手动更新位
	TCON &= ~(1<<1);

	// 自动加载和启动timer0
	TCON |= (1<<0)|(1<<3);

	// 使能timer0中断
	TINT_CSTAT |= 0x1;
}


