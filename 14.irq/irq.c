#include "stdio.h"
#define GPNCON     			(*((volatile unsigned long *)0x7F008830))
#define GPNDAT     			(*((volatile unsigned long *)0x7F008834))
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


void irq_init(void)
{
	/* 配置GPN0~5引脚为中断功能 */
	GPNCON &= ~(0xfff);
	GPNCON |= 0xaaa;

	/* 设置中断触发方式为: 双边沿触发 */
	EINT0CON0 &= ~(0xfff);
	EINT0CON0 |= 0x777;

	/* 禁止屏蔽中断 */
	EINT0MASK &= ~(0x3f);

	/* 在中断控制器里使能这些中断 */
	VIC0INTENABLE |= (0x3); /* bit0: eint0~3, bit1: eint4~11 */
}


void do_irq(void)
{
	int i = 0;

	/* 分辨是哪个中断 */
	for (i = 0; i < 6; i ++)
	{
		if (EINT0PEND & (1<<i))
		{
			if (GPNDAT & (1<<i))
			{
				printf("Interrupt Pended --> K%d released\n\r", i+1);
			}
			else
			{
				printf("Interrupt Pended --> K%d pressed\n\r", i+1);
			}
		}
	}

	/* 清中断 */
	EINT0PEND   = 0x3f;
	VIC0ADDRESS = 0;
}


