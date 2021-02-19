/*!
    \file  mcu02_sfr.h
    \brief sfr define
*/

/*
    Copyright (C) 2020 BYD

    2020-08-11, V1.0.0, firmware for mcu02
*/
#ifndef MCU02_SFR_H
#define MCU02_SFR_H

/*  ----------------sfr Register------------------  */
sfr DATAB         			=  0x80;
sfr SP            			=  0x81;
sfr DPL           			=  0x82;
sfr DPH           			=  0x83;
sfr TIMER3_CFG    			=  0x84;
sfr TIMER3_SET_H  			=  0x85;
sfr TIMER3_SET_L  			=  0x86;
sfr PCON          			=  0x87;
sfr TCON          			=  0x88;
sfr TMOD          			=  0x89;
sfr TL0           			=  0x8A;
sfr TL1           			=  0x8B;
sfr TH0           			=  0x8C;
sfr TH1           			=  0x8D;
sfr SOFT_RST      			=  0x8E;
sfr SDR           			=  0x8F;
sfr DATAC         			=  0x90;
sfr WDT_CTRL      			=  0x91;
sfr WDT_EN        			=  0x92;
sfr TIMER2_CFG    			=  0x93;
sfr TIMER2_SET_H  			=  0x94;
sfr TIMER2_SET_L  			=  0x95;
sfr REG_ADDR      			=  0x96;
sfr REG_DATA      			=  0x97;
sfr SCI_S1         			=  0x98;
sfr PWM0_L_L      			=  0x99;
sfr PWM0_L_H      			=  0x9A;
sfr PWM0_H_L      			=  0x9B;
sfr PWM0_H_H      			=  0x9C;
sfr PWM1_L_L      			=  0x9D;
sfr PWM1_L_H      			=  0x9E;
sfr PWM1_H_L      			=  0x9F;
sfr P2            			=  0xA0;
sfr PWM1_H_H      			=  0xA1;
sfr PWM2_L_L      			=  0xA2;
sfr PWM2_L_H      			=  0xA3;
sfr PWM2_H_L      			=  0xA4;
sfr PWM2_H_H      			=  0xA5;
sfr PWM3_L_L      			=  0xA6;
sfr PWM3_L_H      			=  0xA7;
sfr IEN0          			=  0xA8;
sfr PWM3_H_L      			=  0xA9;
sfr PWM3_H_H      			=  0xAA;
sfr CSD_RAWDATAL 			=  0xAB;
sfr CSD_RAWDATAH 			=  0xAC;
sfr SYS_CLK_CFG   			=  0xAD;
sfr INT_PE_STAT   			=  0xAE;
sfr SCAN_START    			=  0xAF;
sfr DATAE         			=  0xB0;
sfr DP_CON        			=  0xB1;
sfr DP_MODE       			=  0xB2;
sfr SCAN_WIDTH    			=  0xB3;
sfr LED2_WIDTH    			=  0xB4;
sfr SPI1_CFG1     			=  0xB5;
sfr SPI1_CFG2     			=  0xB6;
sfr IPH0          			=  0xB7;
sfr IPL0          			=  0xB8;
sfr DP_CON1       			=  0xB9;
sfr SCI_C2     			    =  0xBA;
sfr SCI_C3     			    =  0xBB;
sfr SCI_S2    			    =  0xBC;
sfr SCI_D     			    =  0xBD;
sfr SPI1_STATE    			=  0xBE;
sfr SPI1_SPID     			=  0xBF;
sfr DATAF         			=  0xC0;
sfr ADC_SPT       			=  0xC1;
sfr SCI_INT_CLR        	    =  0xC2;
sfr ADC_SCAN_CFG  			=  0xC3;
sfr ADCCKC        			=  0xC4;
sfr ADC_RDATAH    			=  0xC5;
sfr ADC_RDATAL    			=  0xC6;
sfr EXINT_STAT    			=  0xC7;
sfr DATAG         			=  0xC8;
sfr CSD_START     			=  0xC9;
sfr PULL_I_SEL  			=  0xCA;
sfr SNS_SCAN_CFG1 			=  0xCB;
sfr SNS_SCAN_CFG2 			=  0xCC;
sfr SNS_SCAN_CFG3 			=  0xCD;
sfr SPROG_ADDR_H  			=  0xCE;
sfr SPROG_ADDR_L  			=  0xCF;
sfr PSW           			=  0xD0;
sfr SPROG_DATA    			=  0xD1;
sfr SPROG_CMD     			=  0xD2;
sfr SPROG_TIM     			=  0xD3;
sfr SPROG_RDATA   			=  0xD4;
sfr	INT_POBO_STAT			=  0xD5;	               	
sfr UART1_BDL     			=  0xD6;
sfr UART1_CON1    			=  0xD7;
sfr DATAH         			=  0xD8;
sfr UART1_CON2    			=  0xD9;
sfr UART1_STATE   			=  0xDA;
sfr UART1_BUF     			=  0xDB;
sfr UART0_BDL     			=  0xDC;
sfr UART0_CON1    			=  0xDD;
sfr UART0_CON2    			=  0xDE;
sfr UART0_STATE   			=  0xDF;
sfr ACC           			=  0xE0;
sfr IRCON2        			=  0xE1;
sfr UART0_BUF     			=  0xE2;
sfr IICADD        			=  0xE3;
sfr IICBUF        			=  0xE4;
sfr IICCON        			=  0xE5;
sfr IEN1          			=  0xE6;
sfr IEN2          			=  0xE7;
sfr IICSTAT       			=  0xE8;
sfr IICBUFFER     			=  0xE9;
sfr TRISA         			=  0xEA;
sfr TRISB         			=  0xEB;
sfr TRISC         			=  0xEC;
sfr SCI_C1         			=  0xED;
sfr TRISE         			=  0xEE;
sfr TRISF         			=  0xEF;
sfr B             			=  0xF0;
sfr IRCON1        			=  0xF1;
sfr TRISG         			=  0xF2;
sfr IPH2          			=  0xF3;
sfr IPL2          			=  0xF4;
sfr IPH1          			=  0xF5;
sfr IPL1          			=  0xF6;
sfr TRISH         			=  0xF7;
sfr DATAA         			=  0xF8;
sfr RFID_BUF1      			=  0xF9;
sfr RFID_BUF2      			=  0xFA;
sfr RFID_CFG       			=  0xFB;
sfr RFID_CMD       			=  0xFC;
sfr RFID_CFG2      			=  0xFD;
sfr RFID_BIT_ER    			=  0xFE;
sfr RFID_CFG3				=  0xFF;

/*  ----------------apb sfr register------------------  */
#define	CFG0_REG            	0x00
#define	CFG1_REG            	0x01
#define	CFG2_REG            	0x02
#define	CFG3_REG            	0x03
#define	CFG4_REG            	0x04
#define	CFG5_REG            	0x05
#define	CFG6_REG            	0x06
#define	CFG7_REG            	0x07
#define	CFG8_REG            	0x08
#define	CFG9_REG            	0x09
#define	CFG10_REG           	0x0A
#define	CFG11_REG           	0x0B
#define	CFG12_REG           	0x0C
#define	CFG13_REG           	0x0D
								
#define	RST_STAT            	0x0F
#define	PU_PA               	0x17
#define	PU_PB               	0x18
#define	PU_PC               	0x19
#define	PU_PE               	0x1B
#define	PU_PF               	0x1C
#define	PU_PG               	0x1D
#define	PU_PH               	0x1E
#define	LCD_IO_SEL_1        	0x1F
#define	LCD_IO_SEL_2        	0x20
#define	LCD_IO_SEL_3        	0x21
#define	LCD_IO_SEL_4        	0x22
#define	COM_IO_SEL          	0x23
#define	SEG_IO_SEL          	0x24
#define	ODRAIN_EN           	0x25
#define	SNS_IO_SEL1         	0x26
#define	SNS_IO_SEL2         	0x27
#define	SNS_IO_SEL3         	0x28
#define	SNS_IO_SEL4         	0x29
#define	ADC_IO_SEL0          	0x2A
#define	SAN_ANA_CFG         	0x2B
#define	SEL_LVDT_VTH        	0x2C
#define	PD_ANA              	0x2D


#define	IDLE_WAKE_CFG       	0x30
#define	LED_DRIVE           	0x31
#define	ADC_CFG_SEL             0x32
#define	PWM_IO_SEL          	0x33
#define	PERIPH_IO_SEL1      	0x34
#define	PERIPH_IO_SEL2      	0x35
#define	PERIPH_IO_SEL3      	0x36
#define	PERIPH_IO_SEL4      	0x37
#define	PERIPH_IO_SEL5      	0x38
#define	EXT_INT_CON1        	0x39
#define	EXT_INT_CON2        	0x3A
#define	SPI1_TX_START_ADDR  	0x3E
#define	SPI1_RX_START_ADDR  	0x3F
#define	SPI1_NUM_L          	0x40
#define	SPI_NUM_H           	0x41
#define	ADC_CFG_SEL1			0x42
#define	DUMMY_REG				0x43

#define IIC_FIL_MODE            0x50
#define SNS_IO_SEL5             0x51
#define SNS_IO_SEL6             0x52
#define ADC_IO_SEL1             0x53
#define ADC_IO_SEL2             0x54
#define ADC_IO_SEL3             0x55
#define ADC_IO_SEL4             0x56
#define ADC_IO_SEL5             0x57
#define RFID_MODE_SEL           0x58
#define RFID_ANTIC_NVB          0x59
#define FLASH_BOOT_EN           0x5A
#define EEP_SELECT              0x5B
#define SCI_BDH                 0x60
#define SCI_BDL                 0x61
#define SFR_LDO_CTRL            0x62
#define BOOT_CMD                0x6A
#define ROM_OFFSET_L            0x6B
#define ROM_OFFSET_H            0x6C

#define	LCD_TEST				0x70
#define	SFR_TEST_SEL			0x71
#define	SFR_TEST_SEL1			0x72

#define SM4_MODE                0x80
#define SM4_START               0x81
#define SM4_DATA0               0x82
#define SM4_DATA1               0x83
#define SM4_DATA2               0x84
#define SM4_DATA3               0x85
#define SM4_DATA4               0x86
#define SM4_DATA5               0x87
#define SM4_DATA6               0x88
#define SM4_DATA7               0x89
#define SM4_DATA8               0x8a
#define SM4_DATA9               0x8b
#define SM4_DATA10              0x8c
#define SM4_DATA11              0x8d
#define SM4_DATA12              0x8e
#define SM4_DATA13              0x8f
#define SM4_DATA14              0x90
#define SM4_DATA15              0x91
#define SM4_KEY0                0x92
#define SM4_KEY1                0x93
#define SM4_KEY2                0x94
#define SM4_KEY3                0x95
#define SM4_KEY4                0x96
#define SM4_KEY5                0x97
#define SM4_KEY6                0x98
#define SM4_KEY7                0x99
#define SM4_KEY8                0x9a
#define SM4_KEY9                0x9b
#define SM4_KEY10               0x9c
#define SM4_KEY11               0x9d
#define SM4_KEY12               0x9e
#define SM4_KEY13               0x9f
#define SM4_KEY14               0xA0
#define SM4_KEY15               0xA1


/*  ----------------Bit Register------------------  */

/*  DATAA  */
sbit PA0  = DATAA^0;
sbit PA1  = DATAA^1;
sbit PA2  = DATAA^2;
sbit PA3  = DATAA^3;


/*  DATAB  */
sbit PB0  = DATAB^0;
sbit PB1  = DATAB^1;
sbit PB2  = DATAB^2;
sbit PB3  = DATAB^3;
sbit PB4  = DATAB^4;
sbit PB5  = DATAB^5;
sbit PB6  = DATAB^6;
sbit PB7  = DATAB^7;

/*  TCON  */
sbit IE0  = TCON^1;
sbit IE1  = TCON^3;
sbit TR0  = TCON^4;
sbit TF0  = TCON^5;
sbit TR1  = TCON^6;
sbit TF1  = TCON^7;


/*  DATAC  */
sbit PC0  = DATAC^0;
sbit PC1  = DATAC^1;
sbit PC2  = DATAC^2;
sbit PC3  = DATAC^3;
sbit PC4  = DATAC^4;
sbit PC5  = DATAC^5;
sbit PC6  = DATAC^6;
sbit PC7  = DATAC^7;


/*  IEN0  */
sbit EX0  = IEN0^0;
sbit ET0  = IEN0^1;
sbit EX1  = IEN0^2;
sbit ET1  = IEN0^3;
sbit EA   = IEN0^7;


/*  DATAE  */
sbit PE0  = DATAE^0;
sbit PE1  = DATAE^1;
sbit PE2  = DATAE^2;
sbit PE3  = DATAE^3;
sbit PE4  = DATAE^4;
sbit PE5  = DATAE^5;
sbit PE6  = DATAE^6;
sbit PE7  = DATAE^7;


/*  IPL0  */
sbit PX0  = IPL0^0;
sbit PT0  = IPL0^1;
sbit PX2  = IPL0^2;
sbit PT1  = IPL0^3;

/*  DATAF  */
sbit PF0  = DATAF^0;
sbit PF1  = DATAF^1;
sbit PF2  = DATAF^2;
sbit PF3  = DATAF^3;
sbit PF4  = DATAF^4;
sbit PF5  = DATAF^5;
sbit PF6  = DATAF^6;
sbit PF7  = DATAF^7;

/*  DATAG  */
sbit PG0  = DATAG^0;
sbit PG1  = DATAG^1;
sbit PG2  = DATAG^2;
sbit PG3  = DATAG^3;


/*  PSW  */
sbit P   = PSW^0;
sbit F1  = PSW^1;
sbit OV  = PSW^2;
sbit RS0 = PSW^3;
sbit RS1 = PSW^4;
sbit F0  = PSW^5;
sbit AC  = PSW^6;
sbit CY  = PSW^7;


/*  DATAH  */
sbit PH0  = DATAH^0;
sbit PH1  = DATAH^1;
sbit PH2  = DATAH^2;
sbit PH3  = DATAH^3;
sbit PH4  = DATAH^4;
sbit PH5  = DATAH^5;
sbit PH6  = DATAH^6;
sbit PH7  = DATAH^7;

/*  IICSTAT  */
sbit IIC_RECOV  = IICSTAT^0;
sbit IIC_WCOL  	= IICSTAT^1;
sbit IIC_ACK 	= IICSTAT^2;
sbit IIC_BF  	= IICSTAT^3;
sbit IIC_AD  	= IICSTAT^4;
sbit IIC_RW  	= IICSTAT^5;
sbit IIC_STOP  	= IICSTAT^6;
sbit IIC_START  = IICSTAT^7;

/*  ----------------Bit Register------------------  */

/* interrupt vector definitions */
typedef enum
{
	INT_EXTI_0  		= 0 	,		/* intterrupt vector of exti_0       */
	INT_TIMER0    		= 1 	,		/* intterrupt vector of timer0       */
	INT_EXTI_1     		= 2 	,		/* intterrupt vector of exti_1       */
	INT_TIMER1     		= 3 	,		/* intterrupt vector of timer1       */
	INT_EXTI_2     		= 9 	,		/* intterrupt vector of exti_2       */
	INT_IIC         	= 10	,		/* intterrupt vector of iic          */
	INT_ADC         	= 11	,		/* intterrupt vector of adc          */
	INT_CSD         	= 12	,		/* intterrupt vector of csd          */
	INT_LED_LCD_RFID	= 13	,		/* intterrupt vector of led/lcd/rfid */
	INT_WDT_TIMER2  	= 14	,		/* intterrupt vector of wdt/timer2   */
	INT_SCI        	    = 15	,		/* intterrupt vector of spi0         */
	INT_LVDT        	= 16	,		/* intterrupt vector of lvdt         */
	INT_UART0       	= 17	,		/* intterrupt vector of uart0        */
	INT_UART1       	= 18	,		/* intterrupt vector of uart1        */
	INT_TIMER3_SM4      = 19	,		/* intterrupt vector of timer3/sm4   */
	INT_SPI1        	= 20	,		/* intterrupt vector of spi1         */
	INT_EXTI_3      	= 21	,		/* intterrupt vector of exti_3       */
	INT_EXTI_4      	= 22	,		/* intterrupt vector of exti_4       */
}IRQn_Type;

/* exact-width types */
typedef	unsigned char		uint8_t;
typedef	signed char			int8_t;
typedef unsigned int		uint16_t;
typedef signed int			int16_t;
typedef unsigned long		uint32_t;
typedef signed long			int32_t;

typedef unsigned long  u32;
typedef unsigned short u16;
typedef unsigned char  u8;

typedef signed long  s32;
typedef signed short s16;
typedef signed char  s8;


/* enum definitions */
typedef enum {DISABLE = 0, ENABLE = !DISABLE} EventStatus, ControlStatus;
typedef enum {RESET = 0, SET = !RESET} FlagStatus;
typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrStatus;
typedef enum {LOW = 0, HIGH = !LOW} IntPrioStatus;

#endif