
.globl _start
_start:

	// 外设地址告诉cpu
    ldr r0, =0x70000000
    orr r0, r0, #0x13
    mcr p15,0,r0,c15,c2,4
    
	// 关看门狗
	ldr r0, =0x7E004000
	mov r1, #0
	str r1, [r0]
	
	// 设置栈
	ldr sp, =8*1024

	// 初始化时钟
	bl clock_init

	// 初始化ddr
	bl sdram_init

	// 初始化nandflash
	bl nand_init
	
	//初始化串口
	bl uart_init

	// 重定位，把程序的代码段、数据段复制到它的链接地址去
	adr r0, _start   			
	ldr r1, =_start  			
	ldr r2, =bss_start      	
	sub r2, r2, r1
	cmp r0,r1
	beq clean_bss
	bl copy2ddr					
	cmp r0, #0
	bne halt
	

	// 清BSS，把BSS段对应的内存清零
clean_bss:
	ldr r0, =bss_start
	ldr r1, =bss_end
	mov r3, #0
	cmp r0, r1
	beq on_ddr
clean_loop:
	str r3, [r0], #4
	cmp r0, r1
	bne clean_loop

on_ddr:
	// 跳转
	ldr pc, =main

halt:
	b halt
