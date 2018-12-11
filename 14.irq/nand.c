
#define ELFIN_NAND_BASE		0x70200000

#define NFCONF_OFFSET           0x00
#define NFCONT_OFFSET           0x04
#define NFCMMD_OFFSET           0x08
#define NFADDR_OFFSET           0x0c
#define NFDATA_OFFSET						0x10
#define NFMECCDATA0_OFFSET      0x14
#define NFMECCDATA1_OFFSET      0x18
#define NFSECCDATA0_OFFSET      0x1c
#define NFSBLK_OFFSET           0x20
#define NFEBLK_OFFSET           0x24
#define NFSTAT_OFFSET           0x28
#define NFESTAT0_OFFSET         0x2c
#define NFESTAT1_OFFSET         0x30
#define NFMECC0_OFFSET          0x34
#define NFMECC1_OFFSET          0x38
#define NFSECC_OFFSET           0x3c
#define NFMLCBITPT_OFFSET       0x40
#define NF8ECCERR0_OFFSET				0x44
#define NF8ECCERR1_OFFSET				0x48
#define NF8ECCERR2_OFFSET				0x4c
#define NFM8ECC0_OFFSET					0x50
#define NFM8ECC1_OFFSET					0x54
#define NFM8ECC2_OFFSET					0x58
#define NFM8ECC3_OFFSET					0x5c
#define NFMLC8BITPT0_OFFSET			0x60
#define NFMLC8BITPT1_OFFSET			0x64

#define NFCONF						(ELFIN_NAND_BASE+NFCONF_OFFSET)
#define NFCONT						(ELFIN_NAND_BASE+NFCONT_OFFSET)
#define NFCMMD						(ELFIN_NAND_BASE+NFCMMD_OFFSET)
#define NFADDR           	(ELFIN_NAND_BASE+NFADDR_OFFSET)
#define NFDATA          	(ELFIN_NAND_BASE+NFDATA_OFFSET)
#define NFMECCDATA0     	(ELFIN_NAND_BASE+NFMECCDATA0_OFFSET)
#define NFMECCDATA1     	(ELFIN_NAND_BASE+NFMECCDATA1_OFFSET)
#define NFSECCDATA0      	(ELFIN_NAND_BASE+NFSECCDATA0_OFFSET)
#define NFSBLK          	(ELFIN_NAND_BASE+NFSBLK_OFFSET)
#define NFEBLK           	(ELFIN_NAND_BASE+NFEBLK_OFFSET)
#define NFSTAT           	(ELFIN_NAND_BASE+NFSTAT_OFFSET)
#define NFESTAT0         	(ELFIN_NAND_BASE+NFESTAT0_OFFSET)
#define NFESTAT1         	(ELFIN_NAND_BASE+NFESTAT1_OFFSET)
#define NFMECC0          	(ELFIN_NAND_BASE+NFMECC0_OFFSET)
#define NFMECC1          	(ELFIN_NAND_BASE+NFMECC1_OFFSET)
#define NFSECC           	(ELFIN_NAND_BASE+NFSECC_OFFSET)
#define NFMLCBITPT        (ELFIN_NAND_BASE+NFMLCBITPT_OFFSET)
#define NF8ECCERR0				(ELFIN_NAND_BASE+NF8ECCERR0_OFFSET)
#define NF8ECCERR1				(ELFIN_NAND_BASE+NF8ECCERR1_OFFSET)
#define NF8ECCERR2				(ELFIN_NAND_BASE+NF8ECCERR2_OFFSET)
#define NFM8ECC0					(ELFIN_NAND_BASE+NFM8ECC0_OFFSET)
#define NFM8ECC1					(ELFIN_NAND_BASE+NFM8ECC1_OFFSET)
#define NFM8ECC2					(ELFIN_NAND_BASE+NFM8ECC2_OFFSET)
#define NFM8ECC3					(ELFIN_NAND_BASE+NFM8ECC3_OFFSET)
#define NFMLC8BITPT0			(ELFIN_NAND_BASE+NFMLC8BITPT0_OFFSET)
#define NFMLC8BITPT1			(ELFIN_NAND_BASE+NFMLC8BITPT1_OFFSET)

#define __REG(x)					(*(volatile unsigned long *)(x))
#define __REGb(x)					(*(volatile unsigned char *)(x))
#define NFCONF_REG				__REG(ELFIN_NAND_BASE+NFCONF_OFFSET)
#define NFCONT_REG				__REG(ELFIN_NAND_BASE+NFCONT_OFFSET)
#define NFCMD_REG					__REG(ELFIN_NAND_BASE+NFCMMD_OFFSET)
#define NFADDR_REG        __REG(ELFIN_NAND_BASE+NFADDR_OFFSET)
#define NFDATA_REG        __REG(ELFIN_NAND_BASE+NFDATA_OFFSET)
#define NFDATA8_REG       __REGb(ELFIN_NAND_BASE+NFDATA_OFFSET)
#define NFMECCDATA0_REG   __REG(ELFIN_NAND_BASE+NFMECCDATA0_OFFSET)
#define NFMECCDATA1_REG   __REG(ELFIN_NAND_BASE+NFMECCDATA1_OFFSET)
#define NFSECCDATA0_REG   __REG(ELFIN_NAND_BASE+NFSECCDATA0_OFFSET)
#define NFSBLK_REG        __REG(ELFIN_NAND_BASE+NFSBLK_OFFSET)
#define NFEBLK_REG        __REG(ELFIN_NAND_BASE+NFEBLK_OFFSET)
#define NFSTAT_REG        __REG(ELFIN_NAND_BASE+NFSTAT_OFFSET)
#define NFESTAT0_REG      __REG(ELFIN_NAND_BASE+NFESTAT0_OFFSET)
#define NFESTAT1_REG      __REG(ELFIN_NAND_BASE+NFESTAT1_OFFSET)
#define NFMECC0_REG       __REG(ELFIN_NAND_BASE+NFMECC0_OFFSET)
#define NFMECC1_REG       __REG(ELFIN_NAND_BASE+NFMECC1_OFFSET)
#define NFSECC_REG        __REG(ELFIN_NAND_BASE+NFSECC_OFFSET)
#define NFMLCBITPT_REG    __REG(ELFIN_NAND_BASE+NFMLCBITPT_OFFSET)

#define NAND_DISABLE_CE()	(NFCONT_REG |= (1 << 1))
#define NAND_ENABLE_CE()	(NFCONT_REG &= ~(1 << 1))
#define NF_TRANSRnB()			do { while(!(NFSTAT_REG & (1 << 0))); } while(0)  //do {} while(0)的妙用

//NFSTAT
//RnB(Read-only)			[0] 
//The status of RnB input pin.
//0: NAND Flash memory busy
//1: NAND Flash memory ready to operate

// Standard NAND flash commands
#define NAND_CMD_READ0				0
#define NAND_CMD_READ1				1
#define NAND_CMD_RNDOUT				5
#define NAND_CMD_PAGEPROG			0x10
#define NAND_CMD_READOOB			0x50
#define NAND_CMD_ERASE1				0x60
#define NAND_CMD_STATUS				0x70
#define NAND_CMD_STATUS_MULTI	0x71
#define NAND_CMD_SEQIN				0x80
#define NAND_CMD_RNDIN				0x85
#define NAND_CMD_READID				0x90
#define NAND_CMD_ERASE2				0xd0
#define NAND_CMD_RESET				0xff
// Extended commands for large page devices
#define NAND_CMD_READSTART		0x30
#define NAND_CMD_RNDOUTSTART	0xE0
#define NAND_CMD_CACHEDPROG		0x15

/* K9GAG08U0E-S Command Sets */

/*------------------------------------------------------------------*/
/* Function 						| 1st Set 	| 2nd Set 	| Acceptable Command*/
/* 											|						|						|	during Busy				*/
/*------------------------------------------------------------------*/										
/* Read 								|	00h 			|	30h				|										*/
/*------------------------------------------------------------------*/
/* Read for Copy Back 	| 00h 			|	35h				|										*/
/*------------------------------------------------------------------*/
/* Cache Read 					| 31h 			|  -				|										*/
/*------------------------------------------------------------------*/
/* Read Start for Last 	|	3Fh 			|  -				|										*/
/* Page Cache Read 			|						|						|										*/
/*------------------------------------------------------------------*/
/* Page Program 				|	80h 			|	10h				|										*/
/*------------------------------------------------------------------*/
/* Cache Program 				| 80h 			| 15h				|										*/
/*------------------------------------------------------------------*/
/* Copy-Back Program 		| 85h 			| 10h				|										*/
/*------------------------------------------------------------------*/
/* Block Erase 					|	60h 			| D0h				|										*/
/*------------------------------------------------------------------*/
/* Random Data Input		| 85h				|  -				|										*/
/*------------------------------------------------------------------*/
/* Random Data Output		| 05h 			| E0h				|										*/
/*------------------------------------------------------------------*/
/* Read ID 							| 90h 			| -					|										*/
/*------------------------------------------------------------------*/
/* Read Status 					| 70h 			| - 				| O									*/
/*------------------------------------------------------------------*/
/* Chip Status1 				| F1h 			| - 				| O									*/
/*------------------------------------------------------------------*/
/* Chip Status2 				| F2h 			| 					| O									*/
/*------------------------------------------------------------------*/
/* Reset 								| FFh 			| - 				| O									*/
/*------------------------------------------------------------------*/

#define MEM_SYS_CFG     (*((volatile unsigned long *)0x7E00F120))

void nand_init(void)
{
	// 设置NAND Flash控制器
	NFCONF_REG = ( (0x2<<12)|(0xf<<8)|(0x7<<4) );
	
	/*== TACLS [14:12] ==*/
	// CLE & ALE duration setting value (0~7) 
	// Duration = HCLK x TACLS	
	// HCLK=133 MHz， 1 clock cycle =（1/133）us.
	// Duration = HCLK x TACLS = 15 ns
	// TACLS = 15 ns / (1/133) us = 1.995 = 2
	
	/*== TWRPH0 [10:8] --> WE Pulse Width(tWP) = 15 ns ==*/
	// TWRPH0 duration setting value (0~7)
	// Duration = HCLK x ( TWRPH0 + 1 )
	// HCLK=133 MHz， 1 clock cycle =（1/133）us.
	// Duration = HCLK x ( TWRPH0 + 1 ) = 15 ns
	// TWRPH0 = (15 ns / (1/133) us) - 1= 1.995 - 1 = 1
	
	/*== TWRPH1 [6:4] --> WE Pulse Width(tWH) = 10 ns ==*/
	// TWRPH1 duration setting value (0~7)
	// Duration = HCLK x ( TWRPH0 + 1 )
	// HCLK=133 MHz， 1 clock cycle =（1/133）us.
	// Duration = HCLK x ( TWRPH0 + 1 ) = 10 ns
	// TWRPH0 = (10 ns / (1/133) us) - 1= 1.33 - 1 = 0.33 = 1
	
	NFCONT_REG |= (0x3<<0);				// Nand Flash Controller enable; Disable chip select
	
	//	MODE 			[0] 		NAND Flash controller operating mode
	//	0: NAND Flash Controller Disable (Don’t work)
	//	1: NAND Flash Controller Enable
	
	//  Reg_nCE0 [1]	
	//  NAND Flash Memory Xm0CSn2 signal control
	//  0: Force Xm0CSn2 to low(Enable chip select)
	//	1: Force Xm0CSn2 to High(Disable chip select)	
	
	//	Reg_nCE1 [2] NAND Flash Memory Xm0CSn3 signal control
	//	0: Force Xm0CSn3 to low(Enable chip select)
	//	1: Force Xm0CSn3 to High(Disable chip select)
	
	//	Note: Even Reg_nCE1 and Reg_nCE0 are set to zero
	//	simultaneously, only one of them is asserted.
		
}

// 读一页，即2048byte  NAND Flash memory I/F: Support 512Bytes and 2KB Page
static int nandll_read_page (unsigned char *buf, unsigned long addr)
{

	int i;
	int page_size = 2048;

	// 发片选
	NAND_ENABLE_CE();

	// 发读命令：0x00
	NFCMD_REG = NAND_CMD_READ0;
	// 发地址
	NFADDR_REG = 0;											//1st cycle：列地址1（列地址：A0 ~ A7）
	NFADDR_REG = 0;											//2nd cycle：列地址2（列地址：A8 ~ A13）
	NFADDR_REG = (addr) & 0xff;					//3rd cycle：行地址1（页地址：A14 ~ A20; 块地址：A21）
	NFADDR_REG = (addr >> 8) & 0xff;		//4th cycle：行地址2（块地址：A22 ~ A29）
	NFADDR_REG = (addr >> 16) & 0xff;		//5th cycle：行地址3（块地址：A30 ~ A32）
	
	// Row Address: A0 ~ A13(可寻址2^13=8K) 			-->列地址：表示寻址的页里面具体的Byte
	// Column Address:  													-->行地址：表示寻址的页
	// 	- Block Address : A21 ~ A32(可寻址2^11=2048 blocks)
	//  - Page Address :  A14 ~ A20(可寻址2^6=64 pages)
	//  - *A33 : Chip address for K9LBG08U0E, K9HCG08U1E
	
	/*============ illustration of 1 page =================*/
	
	// 	-------------------------------------------------
	// |			|			|			列地址		|			|			|				 | bit 7
	// 	-------------------------------------------------
	// |			|			|			列地址		|			|			|				 | bit 6
	// 	-------------------------------------------------
	// |			|			|			列地址		|			|			|				 | bit 5
	// 	-------------------------------------------------
	// |			|			|			列地址		|			|			|				 | bit 4
	// 	-------------------------------------------------
	// |			|			|			列地址		|			|			|				 | bit 3
	// 	-------------------------------------------------
	// |			|			|			列地址		|			|			|				 | bit 2
	// 	-------------------------------------------------
	// |			|			|			列地址		|			|			|				 | bit 1
	// 	-------------------------------------------------
	// |	0B	|	1B	|			列地址		|	...	|	8KB	| 436B	 | bit 0
	// ===================================================
	// |						数据区											|	ECC区  |
	// ===================================================
	
	// 发读命令：0x30
	NFCMD_REG = NAND_CMD_READSTART;

	// 等待数据
	NF_TRANSRnB();

	// 连续读2048个字节
	for(i=0; i < page_size; i++)
	{
		*buf++ = NFDATA8_REG;
	}

	// 取消片选
	NAND_DISABLE_CE();

	return 0;
}

/* Read Flow Chart */

// Start -> Write 00h -> Write Address -> Write 30h -> Read Data -> ECC Generation -> Verify ECC -> Page Read Completed

/* Read Operation */
// 00h -> Col. Add1 -> Col. Add2 -> Row Add1 -> Row Add2 -> Row Add3 -> 30h -> Busy -> Dout N -> Dout N+1 -> ... -> Dout M


// 从NAND中拷贝代码到DRAM
int copy2ddr(unsigned int nand_start, unsigned int ddr_start, unsigned int len)
{
	unsigned char *buf = (unsigned char *)ddr_start;
	int i;
	unsigned int page_shift = 11;

	// 发片选
	NAND_ENABLE_CE();

	// 使len为2048的整数倍
	len = (len/2048+1)*2048;

	// 循环拷贝，每次拷贝一页数据
	for (i = 0; i < (len>>page_shift); i++, buf+=(1<<page_shift))
	{
		// 读一页，即2048byte
		nandll_read_page(buf, i);
	}

	return 0;
}
