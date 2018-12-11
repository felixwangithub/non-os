// 启动代码
.global _start

_start:

	// 把外设的基地址告诉CPU
	ldr r0, =0x70000000 					
	orr r0, r0, #0x13					
	mcr p15,0,r0,c15,c2,4				
	
	// 关看门狗
	ldr r0, =0x7E004000
	mov r1, #0
	str r1, [r0] 
	
	// 设置栈
	ldr sp, =0x0C002000
	
	// 开启icaches
	orr	r0, r0, #0x00001000						@ set bit 12 (I) I-cache
	mcr	p15, 0, r0, c1, c0, 0	

	// 设置时钟
	bl clock_init
	
	// 初始化sdram
	bl sdram_init

	// 初始化NAND Flash
	bl nand_init

	// 重定位，把程序的代码段、数据段复制到它的链接地址去
	adr r0, _start   		@ _start的当前地址 = 0x0		
	ldr r1, =_start  		@ _start的链接地址 = 0x50000000	
	ldr r2, =bss_start	@ bss_start的链接地址  = (0x50000000 + .text + .rodata + .data)      	
	sub r2, r2, r1			@ r2 = bss段的起始地址- 代码段的起始地址 =sizeof(.text + .rodata + .data)
	cmp r0,r1						@ 比较当前地址和链接地址
	beq clean_bss				@ 如果相等，说明已经搬运，清除bss段；否则跳转执行copy2ddr，进行代码搬运
	bl copy2ddr					@ int copy2ddr(nand_start, ddr_start, len)  
											@ nand_start = r0 =_start  
											@ ddr_start	 = r1 = 0x50000000
											@ len				 = r2 =	sizeof(.text + .rodata + .data)
	cmp r0, #0					@ 调用copy2ddr函数后，如果拷贝成功，返回0， 即r0 = 0; 如果拷贝不成功，r0 ！= 0
	bne halt						@ 如果r0 ！= 0， 说明拷贝失败，跳转死循环
		
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

	// 跳转
on_ddr:
	ldr pc, =main
	
halt:
	b halt	
