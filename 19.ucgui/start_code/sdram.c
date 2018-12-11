
// DRAM CONTROLLER STATUS REGISTER:
#define P1MEMSTAT 					(*((volatile unsigned long *)0x7E001000))

// DRAM CONTROLLER COMMAND REGISTER:
#define P1MEMCCMD 					(*((volatile unsigned long *)0x7E001004))

// DIRECT COMMAND REGISTER:
#define P1DIRECTCMD 				(*((volatile unsigned long *)0x7E001008))

// MEMORY CONFIGURATION REGISTER:
#define P1MEMCFG 						(*((volatile unsigned long *)0x7E00100C))

// REFRESH PERIOD REGISTER:
#define P1REFRESH 					(*((volatile unsigned long *)0x7E001010))

// CAS LATENCY REGISTER:
#define P1CASLAT 						(*((volatile unsigned long *)0x7E001014))

// T_DQSS REGISTER:
#define P1T_DQSS 						(*((volatile unsigned long *)0x7E001018))

// T_MRD REGISTER:
#define P1T_MRD 						(*((volatile unsigned long *)0x7E00101C))

// T_RAS REGISTER:
#define P1T_RAS 						(*((volatile unsigned long *)0x7E001020))

// T_RC REGISTER:
#define P1T_RC 							(*((volatile unsigned long *)0x7E001024))

// T_RCD REGISTER:
#define P1T_RCD 						(*((volatile unsigned long *)0x7E001028))

// T_RFC REGISTER:
#define P1T_RFC 						(*((volatile unsigned long *)0x7E00102C))

// T_RP REGISTER:
#define P1T_RP 							(*((volatile unsigned long *)0x7E001030))

// T_RRD REGISTER:
#define P1T_RRD 						(*((volatile unsigned long *)0x7E001034))

// T_WR REGISTER:
#define P1T_WR 							(*((volatile unsigned long *)0x7E001038))

// T_WTR REGISTER:
#define P1T_WTR 						(*((volatile unsigned long *)0x7E00103C))

// T_XP REGISTER:
#define P1T_XP 							(*((volatile unsigned long *)0x7E001040))

// T_XSR REGISTER:
#define P1T_XSR 						(*((volatile unsigned long *)0x7E001044))

// T_ESR REGISTER:
#define P1T_ESR 						(*((volatile unsigned long *)0x7E001048))

// MEMORY CONFIGURATION 2 REGISTER:
#define P1MEMCFG2 					(*((volatile unsigned long *)0x7E00104C))

// MEMORY CONFIGURATION 3 REGISTER:
#define P1MEMCFG3 					(*((volatile unsigned long *)0x7E001050))

// CHIP_N_CFG REGISTER:
#define P1_chip_0_cfg 			(*((volatile unsigned long *)0x7E001200))
#define P1_chip_1_cfg 			(*((volatile unsigned long *)0x7E001204))

// Memory controller status register
#define MEM_SYS_CFG 				(*((volatile unsigned long *)0x7E00F120))

// HCLK=133 MHz£¨ 1 clock cycle =£®1/133£©us
#define HCLK	133000000				

int sdram_init(void)
{
		/* 1. Program memc_cmd to °Æ3°Øb100°Ø, which makes DRAM Controller enter °ÆConfig°Ø state. */
		P1MEMCCMD = 0x4;
		
		/* 2. Write memory timing parameter */
		/* 2.1 Set Refresh duty cycle */
		P1REFRESH = 1038;			// K4X1G163PC Manual Page 1£∫ Auto refresh duty cycle £∫7.8us for -25 to 85 °„C
													// HCLK=133 MHz£¨ 1 clock cycle =£®1/133£©us. 
													// Refresh period (clock cycles) = 7.8us / (1/133)us = 1038 clock cycles.
		
		//										[31:15] Read undefined. Write as Zero
		//		Refresh period 	[14:0] 	Memory refresh period in memory clock cycles.
		
		/* 2.2 Set CAS Latency */
		 P1CASLAT = 3<<1;			// K4X1G163PC Manual Page 1£∫MRS cycle with address key programs: CAS Latency ( 3 )
		// CAS Latency 		[3:1] 	CAS latency in memory clock cycles.
		// CAS Half cycle 	[0]
		// Encodes whether the CAS latency is half a memory clock cycle
		// more than the value given in bits[3:1]
		// 0 = Zero cycle offset to value in [3:1]. [0] is forced to 0 in MDDR and SDR mode.
		// 1 = Half cycle offset to the value in [3:1].
		
		/* 2.3 Set t_DQSS */
		P1T_DQSS = 1;				  //tDQSS: min 0.75 tCK, max 1.25 tCK
		// t_DQSS  	[1:0] 	Write to DQS in memory clock cycles.
		
		/* 2.4 Set tMRD */
		P1T_MRD = 2;				  //tMRD: 2 tCK
		// t_MRD 		[6:0] 	Set mode register command time in memory clock cycles.
		
		/* 2.5 Set Row active time */
		P1T_RAS = 6;					// tRAS: min 42ns
													// tRAS (tCK) = 42ns / (1/133)us = 5.6 tCK = 6 tCK
		// t_RAS 		[3:0] 	Set RAS to precharge delay in memory clock cycles.
		
		/* 2.6 Set Row cycle time */
		P1T_RC = 	8;					// tRC: min 60ns
													// tRC (tCK) = 60ns / (1/133)us = 7.9 tCK = 8 tCK
		// t_RC 		[3:0] 	Set Active bank x to Active bank x delay in memory clock cycles.
		
		/* 2.7 Set RAS to CAS delay */
		P1T_RCD = (3) | ((3-3)<<3);					// tRCD: min 18ns
																				// tRCD (tCK) = 18ns / (1/133)us = 2.4 tCK = 3 tCK
		// scheduled_RCD 	[5:3] 	Set t_RCD-3
		// t_RCD 					[2:0] 	Set the RAS to CAS minimum delay in memory clock cycles
		
		/* 2.7 Set Auto refresh cycle time */
		P1T_RFC = (10) | ((10-3)<<5);				// tRFC: min 72ns
																				// tRFC (tCK) = 72ns / (1/133) us = 9.6 tCK = 10 tCK
		// scheduled_RFC 	[9:5] 	Set t_RFC -3.
		// t_RFC 					[4:0] 	Set the autorefresh command time in memory clock cycles
		
		/* 2.8 Set Row precharge time */
		P1T_RP = 	(3) | ((3-3)<<3);					// tRP: min 18ns
																				// tRP (tCK) = 18ns / (1/133) us = 2.4 tCK = 3 tCK
		// scheduled_RP 	[5:3] 	Set t_RP -3
		// t_RP 					[2:0] 	Set the precharge to RAS delay in memory clock cycles
		
		/* 2.9 Set Row active to Row active delay */
		P1T_RRD = 2;												// tRRD: min 12ns
																				// tRRD (tCK) = 12ns / (1/133) us = 1.6 tCK = 2 tCK
		// t_RRD 					[3:0] 	Set Active bank x to Active bank y delay in memory clock cycles.

		/* 2.10 Set Write recovery time */
		P1T_WR = 	2;												// tWR: min 12ns
																				// tWR (tCK) = 12ns / (1/133) us = 1.6 tCK = 2 tCK
		// t_WR 					[2:0] 	Set the write to precharge delay in memory clock cycles.
		
		/* 2.11 Set Write to Read delay time */
		P1T_WTR = 1;
		// t_WTR 					[2:0] 	Set the write to read delay in memory clock cycles.
		
		/* 2.11 Set the exit power down command time */
		P1T_XP = 1;													// Power down exit time: tPDEX = 1 tCK
		// t_XP 					[7:0] 	Set the exit power down command time in memory clock cycles.
		
		/* 2.11 Set Exit self refresh to active command time */ 
		P1T_XSR = 16;												// tXSR: min 120ns
																				// tXSR (tCK) = 120 ns / (1/133) us = 16 tCK
		// t_XSR 					[7:0] 	Set the exit self refresh command time in memory clock cycles.
		
		/* 2.12 Set Exit self refresh to active command time */ 
		P1T_ESR = 16;												// tESR: min 120ns
																				// tESR (tCK) = 120 ns / (1/133) us = 16 tCK
		// t_ESR 					[7:0] 	Set the self refresh command time in memory clock cycles.
		
		/* 3. Chip Configuration */
		P1MEMCFG = (1<<21) | (2<<15) | (0<<6) | (3<<3) | (2);			// 2 chips, Burst 4, Address bit 10, Row bits 14, Column bits 10
		
		/*===================================================================*/
		/* Organization 			Bank Address 		Row Address 		Column Address */
		/* 64Mx16 						BA0,BA1 				A0 - A13 				A0 - A9        */
		/*===================================================================*/
		
		// Active chips	[22:21]	00 = 1 chip 	01 = 2 chips 	10 = Reserved		11 = Reserved
		// Memory burst	[17:15]	000 = Burst 1;	001 = Burst 2;	010 = Burst 4;	011 = Burst 8;	100 = Burst 16;	101~111 = Reserved
		// AP bit				[6]			0 = address bit 10.		1 = address bit 8.
		// Row bits			[5:3]		000 = 11 bits; 	001 = 12 bits; 	010 = 13 bits;	011 = 14 bits;	100 = 15 bits;	101 = 16 bits
		// Column bits	[2:0]		000 = 8 bits;	001 = 9 bits;	010 = 10 bits;	011 = 11 bits;	100 = 12 bits
		
		P1MEMCFG2 = (1<<11) | (3<<8) | (1<<6) | (5);							// Read delay: 1 cycle;Memory type:Mobile DDR SDRAM
																															// Memory width: 32-bit; 
		
		P1_chip_0_cfg = (1<<16);																	// Bank-Row-Column organization
		
		/* 4. SDRAM Initialization */
		P1DIRECTCMD = 3<<18;
		P1DIRECTCMD = 0<<18;
		P1DIRECTCMD = 1<<18;
		P1DIRECTCMD = 1<<18;
		P1DIRECTCMD = (2<<18) | (2<<16) | (0);										//EMRS: BA1=1, BA0=0
		P1DIRECTCMD = (2<<18) | (0<<16) | (3<<4) | (0<<3) | (2);	//MRS: BA1=1, BA0=0; CAS Latency=3; Busrt Type=Sequential(0); Burst Length=4(010)
		
		MEM_SYS_CFG = 0x0;
		
		/* 5. Make DRAM Controller enter 'Ready' state */
		P1MEMCCMD = 0x000;
		// Memc_cmd [2:0]  Changes the state of the DRAM controller
		// 000 = Go 001 = Sleep 010 = Wakeup 011 = Pause
		// 100 = Configure 101~111 = Reserved
		
		/* 6. Check memory status field until it becomes °Æ2°Øb01°Ø, which means °ÆReady°Ø. */
		
		while(!((P1MEMSTAT & 0x3) == 0x1));								//Wait until memory status becomes 'Ready'
		
		return 0;
		
}




