
.global _start

_start: 
		
	//�������ַ����С����CPU
	ldr r0, =0x70000000							//ldr: load
	orr r0, r0, #0x13 							//0x13=b10011=256M, �μ�arm1176jzfs�ں˲ο��ֲ�Page3-130
	mcr p15,0,r0,c15,c2,4       				//��r0��ֵ(�������������ַ+�����С)����cpu
	
	//�ؿ��Ź�
	ldr r0, =0x7E004000							//watch dog timer base address
	mov r1, #0
	str r1, [r0]								//disable watch dog.  str: Store
	
	//����ջ
	ldr sp, =0x0C002000							//S3C6410 ���ڲ�8K ��SRAM ��ӳ�䵽0X0C000000����ARM Ĭ�ϵ�ջ�ǵݼ��ģ����Կ�����SP ָ��0X0C002000
	
	//��icache
	orr	r0, r0, #0x00001000						@ set bit 12 (I) I-cache
	mcr	p15, 0, r0, c1, c0, 0	
	
	// ����ʱ��
	bl clock_init
	
	// ��ʼ��sdram
	bl sdram_init
    
    // �ض�λ
	adr r0, _start			@_start�ĵ�ǰ��ַ  						
	ldr r1, =_start 		@_start�����ӵ�ַ						
	ldr r2, =bss_start
	cmp r0, r1				@�Ƚϵ�ǰ��ַ�����ӵ�ַ
	beq clean_bss			@�����ȣ�˵���Ѿ����ˣ����bss��
copy_loop:
	ldr r3, [r0], #4		@���洢����ַΪr0(_start�ĵ�ǰ��ַ)�������ݶ���Ĵ���r3�������µ�ַr0+4д��r0
	str r3, [r1], #4		@��r3�е�������д����r1(_start�����ӵ�ַ)Ϊ��ַ�Ĵ洢���У������µ�ַr1+4д��r1
	cmp r1, r2				@�Ƚ�_start�����ӵ�ַ��bss_start�ĵ�ַ
	bne copy_loop			@�������ȣ�˵����û�п����꣬����������������С����bss_start - _start�����ӵ�ַ
		
	// ��BSS��
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
	
	//����main����
	ldr pc, =main
	
halt:
	b   halt
	