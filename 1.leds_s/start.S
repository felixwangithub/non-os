
.global _start
_start: 
		
	//外设基地址及大小告诉CPU
	ldr r0, =0x70000000							//ldr: load
	orr r0, r0, #0x13 							//0x13=b10011=256M, 参见arm1176jzfs内核参考手册Page3-130
	mcr p15,0,r0,c15,c2,4       		//把r0的值(包括了外设基地址+外设大小)告诉cpu
	
	//关看门狗
	ldr r0, =0x7E004000							//watch dog timer base address
	mov r1, #0
	str r1, [r0]										//disable watch dog.  str: Store
	
	//设置GPKCON0
	ldr r0, =0x7F008800							//GPKCON0 address
	ldr r1, =0x11110000							//GPK_4,5,6,7设置为输出， GPKn设置为0001时，GPKn引脚设置为输出
	str r1, [r0]
	
	mov r2, #0x1000									//LED循环计数
led_blink:
	ldr r0, =0x7F008808							//GPKDAT address
	mov r1, #0xF0										//设置GPK_4,5,6,7为高电平，Led熄灭
	str r1, [r0]
	
	bl  delay
	
	ldr r0, =0x7F008808
	mov r1, #0x00										//设置GPK_4,5,6,7为低电平，Led点亮
	str r1, [r0]
	
	bl  delay
	
	sub r2, r2, #1									//r2=r2-1
	cmp r2, #0
	bne led_blink										//如果r2!=0，则跳转至led_blink处执行。bne：Branch Not Equal
		
halt:
	b   halt												//b: Branch
		
delay:
	mov r0, #0x1000000	
delay_loop:		
	sub r0, r0, #1
	cmp r0, #0
	bne delay_loop
	mov pc, lr											//从delay子程序返回
		
		
