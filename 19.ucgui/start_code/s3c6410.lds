OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_start)
SECTIONS 
{
    . = 0x50000000;
    . = ALIGN(4);
	.text : 
	{

/*************Bootloader**********************/	
		./start_code/s3c6410.o(.text)
		./start_code/clock.o(.text)
		./start_code/sdram.o(.text)
		./start_code/nand.o(.text)
/*********************************************/
			
		*(.text)
			
	}
	. = ALIGN(4);
	.rodata : {* (.rodata)}
	. = ALIGN(4);
	.data : {* (.data)}
	
	. = ALIGN(4);
 
	bss_start = .;
    .bss ALIGN(4)  : { *(.bss)  *(COMMON) }
    bss_end = .;
}
