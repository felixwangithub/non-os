
.global _start

_start: 
		
	//外设基地址及大小告诉CPU
	ldr r0, =0x70000000							//ldr: load
	orr r0, r0, #0x13 							//0x13=b10011=256M, 参见arm1176jzfs内核参考手册Page3-130
	mcr p15,0,r0,c15,c2,4       				//把r0的值(包括了外设基地址+外设大小)告诉cpu
	
	//关看门狗
	ldr r0, =0x7E004000							//watch dog timer base address
	mov r1, #0
	str r1, [r0]								//disable watch dog.  str: Store
	
	//设置栈
	ldr sp, =0x0C002000							//S3C6410 的内部8K 的SRAM 被映射到0X0C000000，而ARM 默认的栈是递减的，所以可以让SP 指向0X0C002000
	
	//打开icache
	orr	r0, r0, #0x00001000						@ set bit 12 (I) I-cache
	mcr	p15, 0, r0, c1, c0, 0	
	
	// 设置时钟
	bl clock_init
	
	//调用C函数点灯
	bl  main
	
halt:
	b   halt
	
