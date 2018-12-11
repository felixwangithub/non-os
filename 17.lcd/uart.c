// 功能:初始化串口
#include "uart.h" 
#include "lcd.h"


#define GPACON  	(*((volatile unsigned long *)0x7F008000))
#define GPADAT  	(*((volatile unsigned long *)0x7F008004))

#define ULCON0  	(*((volatile unsigned long *)0x7F005000))
#define UCON0   	(*((volatile unsigned long *)0x7F005004))
#define UFCON0  	(*((volatile unsigned long *)0x7F005008))
#define UMCON0  	(*((volatile unsigned long *)0x7F00500C))

#define UFSTAT0 	(*((volatile unsigned long *)0x7F005018))
#define UTXH0 		(*((volatile unsigned long *)0x7F005020))
#define URXH0	 	(*((volatile unsigned long *)0x7F005024))
#define UBRDIV0	 	(*((volatile unsigned long *)0x7F005028))
#define UDIVSLOT0	(*((volatile unsigned long *)0x7F00502C))


void uart_init(void)
{
	/* 1. 配置引脚 */

	GPACON &= ~0xff;
	GPACON |= 0x22;					//GPA0=b0010=UART RXD[0]; GPA1=b0010=UART TXD[0]

	/* 2. 设置数据格式 */

	ULCON0 = 0x03;					//Normal mode,No Parity, 1 stop bit, 8-bit

	//ULCON0:
	/*===============================================================*/
	/* [7]			[6]			[5:3]		[2]			[1:0]		 */
	/* Reserved		Infra-Red	Parity		Stop Bit	Word Length	 */
	/*===============================================================*/
	// Infra-Red: 0=Normal, 1=Infra-Red Tx/Rx Mode
	// Parity: 0xx=No Parity, 100=Odd, 101=Even
	// Number of Stop Bit: 0=One Stop Bit, 1=Two Stop Bit
	// Word Length: 00=5-bit, 01=6-bit, 10=7-bit 11=8-bit

	/* 3. 设置时钟 */

	UCON0 = 0x05;					// b0000000000101, Clock = PCLK, Disalbe all interrupts, Interrupt or Polling mode

	//UCON0:
	/*===========================================================================================================*/
	/* [11:10]		[9]		[8]		[7]			[6]					[5]			[4]			[3:2]		[1:0]	 */
	/* Clock		Tx Int 	Rx Int  Rx Time 	Rx Error Status 	Loop-back	Send Break	Transmit	Receive	 */
	/* Selection	Type	Type	Out Enalbe	Interrupt Enable	Mode		Signal		Mode		Mode	 */
	/*===========================================================================================================*/

	// Clock Selection:
	// Select PCLK or EXT_UCLK04) or EXT_UCLK14) clock for the UART baud rate.
	// x0 = PCLK : DIV_VAL = (PCLK / (bps x 16) ) -1
	// 01 = EXT_UCLK0: DIV_VAL1) = (EXT_UCLK0 / (bps x 16) ) –1
	// 11 = EXT_UCLK1: DIV_VAL1) = (EXT_UCLK1 / (bps x 16) ) –1

	// Tx Interrupt Type:
	// Interrupt request type.
	// 0 = Pulse (Interrupt is requested as soon as the Tx buffer becomes empty in Non-FIFO mode or reaches Tx FIFO Trigger Level in FIFO mode.)
	// 1 = Level (Interrupt is requested while Tx buffer is empty in Non-FIFO mode or reaches Tx FIFO Trigger Level in FIFO mode.)

	// Rx Interrupt Type:
	// Interrupt request type.
	// 0 = Pulse (Interrupt is requested the instant Rx buffer receives the data in Non-FIFO mode or reaches Rx FIFO Trigger Level in FIFO mode.)
	// 1 = Level (Interrupt is requested while Rx buffer is receiving data in Non-FIFO mode or reaches Rx FIFO Trigger Level in FIFO mode.)

	// Rx Time Out Enable:
	// Enable/Disable Rx time-out interrupts when UART FIFO is enabled.
	// The interrupt is a receive interrupt. 
	// 0 = Disable 1 = Enable

	// Rx Error Status Interrupt Enable:
	// Enable the UART to generate an interrupt upon an exception, such as a break, frame error, parity error, or overrun error during a receive operation.
	// 0 = Do not generate receive error status interrupt.
	// 1 = Generate receive error status interrupt.

	// Loop-back Mode:
	// Setting loop-back bit to 1 cause the UART to enter the loop-back mode. This mode is provided for test purposes only.
	// 0 = Normal operation 1 = Loop-back mode

	// Send Break Signal:
	// Setting this bit causes the UART to send a break during 1 frame time. This bit is automatically cleared after sending the break signal.
	// 0 = Normal transmit 1 = Send break signal

	// Transmit Mode:
	// Determine which function is currently able to write Tx data to the UART transmit buffer register.
	// 00 = Disable
	// 01 = Interrupt request or polling mode
	// 10 = DMA request (DMA_UART0)
	// 11 = DMA request (DMA_UART1)

	// Receive Mode:
	// Determine which function is currently able to read data from UART receive buffer register.
	// 00 = Disable
	// 01 = Interrupt request or polling mode
	// 10 = DMA request (DMA_UART0)
	// 11 = DMA request (DMA_UART1)

	/* 4. 设置FIFO */

	UFCON0 = 0x01;					// b00000001, FIFO Enable

	//UFCON0:
	/*===============================================================================*/
	/* [7:6]			[5:4]			[3]			[2]			[1]			[0]	     */
	/* Tx FIFO			Rx FIFO			Reserved	Tx FIFO		Rx FIFO		FIFO	 */
	/* Trigger Level	Trigger Level				Reset		Reset		Enalbe   */
	/*===============================================================================*/

	// Tx FIFO Trigger Level:
	// Determine the trigger level of transmit FIFO.
	// 00 = Empty 01 = 16-byte
	// 10 = 32-byte 11 = 48-byte

	// Rx FIFO Trigger Level:
	// Determine the trigger level of receive FIFO.1)
	// 00 = 1-byte 01 = 8-byte
	// 10 = 16-byte 11 = 32-byte

	// Tx FIFO Reset:
	// Auto-cleared after resetting FIFO
	// 0 = Normal 1= Tx FIFO reset

	// Rx FIFO Reset:
	// Auto-cleared after resetting FIFO
	// 0 = Normal 1= Rx FIFO reset

	// FIFO Enable:
	// 0 = Disable 1 = Enable

	/* 5. 设置控制流 */

	UMCON0 = 0;					//无控制流

	/* 6. 设置波特率 */

	UBRDIV0 = 35;
	UDIVSLOT0 = 0x1;
	
	// PCLK : DIV_VAL	= (PCLK / (bps x 16) ) -1
	//					= (66.5M/(115200*16))-1
	//					= 36.08 -1
	//					= 35.08
	// UBRDIV0 = 35
	// (num of 1’s in UDIVSLOT0)/16 = 0.08
	// then, (num of 1’s in UDIVSLOT0) = 1.28 = 1
	// so, UDVISLOT0 = 0x1
	
	
}


/* 接收一个字符 */
char getchar(void)
{
	while ((UFSTAT0 & 0x7f) == 0);    // 如果RX FIFO空，等待； 否则，只要有数据，取出
	return URXH0;                     // 取数据 
}

//UFSTATn:
/*========================================================================================*/
/* [15]			[14] 			[13:8] 			[7] 		[6] 			[5:0]		  */
/* Reserved		Tx FIFO Full 	Tx FIFO Count	Reserved	Rx FIFO Full	Rx FIFO Count */
/*========================================================================================*/

// Tx FIFO Full
// Set to 1 automatically whenever transmit FIFO is full
// during transmit operation
// 0 = 0-byte ≤ Tx FIFO data ≤ 63-byte
// 1 = Full

// Rx FIFO Full
// Set to 1 automatically whenever receive FIFO is full during
// receive operation
// 0 = 0-byte ≤ Rx FIFO data ≤ 63-byte
// 1 = Full

// 当RX FIFO空时， 	Bit[6] == 0, Bit[5:0] == 000000, Bit[7:0]== b00000000 == 0x00
// 当Rx FIFO满时， 	Bit[6] == 1, Bit[5:0] == 111111，Bit[7:0]== b01111111 == 0x7f
// Rx FIFO非空非满：Bit[6] == 0, Bit[5:0] == 0xxxxx，Bit[7:0]== b00xxxxxx

/* 发送一个字符 */
void putchar(char c)
{
	while (UFSTAT0 & (1<<14)); 		// 如果TX FIFO满，等待； 否则，只要未满，继续发送数据
	UTXH0 = c;                      // 写数据 
	lcd_draw_char(c);
}


/* 发送一个字符串 */

void putstr(char * str)
{
	while (*str) {
		putchar(*str++);
	}
}

