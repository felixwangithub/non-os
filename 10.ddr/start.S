
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
	
	// 初始化sdram
	bl sdram_init
    
    // 重定位
	adr r0, _start			@_start的当前地址  						
	ldr r1, =_start 		@_start的链接地址						
	ldr r2, =bss_start
	cmp r0, r1				@比较当前地址和链接地址
	beq clean_bss			@如果相等，说明已经搬运，清除bss段
copy_loop:
	ldr r3, [r0], #4		@将存储器地址为r0(_start的当前地址)的字数据读入寄存器r3，并将新地址r0+4写入r0
	str r3, [r1], #4		@将r3中的字数据写入以r1(_start的链接地址)为地址的存储器中，并将新地址r1+4写入r1
	cmp r1, r2				@比较_start的链接地址和bss_start的地址
	bne copy_loop			@如果不相等，说明还没有拷贝完，继续拷贝。拷贝大小等于bss_start - _start的链接地址
		
	// 清BSS段
clean_bss:
	ldr r0, =bss_start
	ldr r1, =bss_end
	mov r2, #0
	cmp r0, r1
	beq on_ddr
clean_loop:
	str r2, [r0], #4
	cmp r0, r1
	bne clean_loop	

on_ddr:
	
	//调用main函数
	ldr pc, =main
	
halt:
	b   halt
	
