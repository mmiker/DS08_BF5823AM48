/*!
    \file  mcu02_system.h
    \brief system define
*/

/*
    Copyright (C) 2020 BYD

    2020-05-10, V1.0.0, firmware for mcu02
*/
#ifndef	MCU02_SYSTEM_H
#define	MCU02_SYSTEM_H

#include "mcu02_sfr.h"

/* global interrupt definitions */
#define	EnableGlobalInterrupt()		EA = 1
#define	DisableGlobalInterrupt()	EA = 0

/* clear interrupt flag definitions */
#define INT_EXTI_0_CLR()         TCON &= ~(0x02)  
#define INT_TIMER0_CLR()         TCON &= ~(0x20)
#define INT_EXTI_1_CLR()     	 TCON &= ~(0x08)
#define INT_TIMER1_CLR()     	 TCON &= ~(0x80)
#define INT_EXTI_2_CLR()     	 IRCON1 &= ~(0x01 << 2)
#define INT_IIC_CLR()         	 IRCON1 &= ~(0x01 << 3)
#define INT_ADC_CLR()         	 IRCON1 &= ~(0x01 << 4)
#define INT_CSD_CLR()         	 IRCON1 &= ~(0x01 << 5)
#define INT_LED_LCD_RFID_CLR()	 IRCON1 &= ~(0x01 << 6)
#define INT_WDT_TIMER2_CLR()  	 IRCON1 &= ~(0x01 << 7)
#define INT_SCI_CLR()        	 IRCON2 &= ~(0x01 << 0)
#define INT_LVDT_CLR()        	 IRCON2 &= ~(0x01 << 1)
#define INT_UART0_CLR()       	 IRCON2 &= ~(0x01 << 2)
#define INT_UART1_CLR()       	 IRCON2 &= ~(0x01 << 3)
#define INT_TIMER3_SM4_CLR()     IRCON2 &= ~(0x01 << 4)
#define INT_SPI1_CLR()        	 IRCON2 &= ~(0x01 << 5)
#define INT_EXTI_3_CLR()      	 IRCON2 &= ~(0x01 << 6)
#define INT_EXTI_4_CLR()      	 IRCON2 &= ~(0x01 << 7)

/* disable interrupt flag definitions */
#define INT_EXTI_0_DISABLE()         IEN0 &= ~(0x01 << 0)  
#define INT_TIMER0_DISABLE()         IEN0 &= ~(0x01 << 1)
#define INT_EXTI_1_DISABLE()     	 IEN0 &= ~(0x01 << 2)
#define INT_TIMER1_DISABLE()     	 IEN0 &= ~(0x01 << 3)
#define INT_EXTI_2_DISABLE()     	 IEN1 &= ~(0x01 << 2)
#define INT_IIC_DISABLE()         	 IEN1 &= ~(0x01 << 3)
#define INT_ADC_DISABLE()         	 IEN1 &= ~(0x01 << 4)
#define INT_CSD_DISABLE()         	 IEN1 &= ~(0x01 << 5)
#define INT_LED_LCD_RFID_DISABLE()	 IEN1 &= ~(0x01 << 6)
#define INT_WDT_TIMER2_DISABLE()  	 IEN1 &= ~(0x01 << 7)
#define INT_SCI_DISABLE()        	 IEN2 &= ~(0x01 << 0)
#define INT_LVDT_DISABLE()        	 IEN2 &= ~(0x01 << 1)
#define INT_UART0_DISABLE()       	 IEN2 &= ~(0x01 << 2)
#define INT_UART1_DISABLE()       	 IEN2 &= ~(0x01 << 3)
#define INT_TIMER3_DISABLE()      	 IEN2 &= ~(0x01 << 4)
#define INT_SPI1_DISABLE()        	 IEN2 &= ~(0x01 << 5)
#define INT_EXTI_3_DISABLE()      	 IEN2 &= ~(0x01 << 6)
#define INT_EXTI_4_DISABLE()      	 IEN2 &= ~(0x01 << 7)

/* enable interrupt flag definitions */
#define INT_EXTI_0_ENABLE()          IEN0 |= (0x01 << 0)  
#define INT_TIMER0_ENABLE()          IEN0 |= (0x01 << 1)
#define INT_EXTI_1_ENABLE()     	 IEN0 |= (0x01 << 2)
#define INT_TIMER1_ENABLE()     	 IEN0 |= (0x01 << 3)
#define INT_EXTI_2_ENABLE()     	 IEN1 |= (0x01 << 2)
#define INT_IIC_ENABLE()         	 IEN1 |= (0x01 << 3)
#define INT_ADC_ENABLE()         	 IEN1 |= (0x01 << 4)
#define INT_CSD_ENABLE()         	 IEN1 |= (0x01 << 5)
#define INT_LED_LCD_RFID_ENABLE()	 IEN1 |= (0x01 << 6)
#define INT_WDT_TIMER2_ENABLE()  	 IEN1 |= (0x01 << 7)
#define INT_SCI_ENABLE()        	 IEN2 |= (0x01 << 0)
#define INT_LVDT_ENABLE()        	 IEN2 |= (0x01 << 1)
#define INT_UART0_ENABLE()       	 IEN2 |= (0x01 << 2)
#define INT_UART1_ENABLE()       	 IEN2 |= (0x01 << 3)
#define INT_TIMER3_ENABLE()      	 IEN2 |= (0x01 << 4)
#define INT_SPI1_ENABLE()        	 IEN2 |= (0x01 << 5)
#define INT_EXTI_3_ENABLE()      	 IEN2 |= (0x01 << 6)
#define INT_EXTI_4_ENABLE()      	 IEN2 |= (0x01 << 7)

/* get multiinterrupt flag status definitions */
#define GET_INT_LED_FLAG_STATE()      	 (INT_PE_STAT & (0x01 << 0))
#define GET_INT_LCD_FLAG_STATE()      	 (INT_PE_STAT & (0x01 << 1))
#define GET_INT_RFID_FLAG_STATE()      	 (INT_PE_STAT & (0x01 << 2))
#define GET_INT_TIMER2_FLAG_STATE()      (INT_PE_STAT & (0x01 << 3))
#define GET_INT_WDT_FLAG_STATE()      	 (INT_PE_STAT & (0x01 << 4))
#define GET_INT08_FLAG_STATE()      	 (INT_PE_STAT & (0x01 << 5))
#define GET_INT_TIMER3_FLAG_STATE()      (INT_PE_STAT & (0x01 << 6))
#define GET_INT_SM4_FLAG_STATE()         (INT_PE_STAT & (0x01 << 7))

#define WDTRST_STAT   0x01                
#define POR_STAT      0x02
#define BOR_STAT 	  0x04
#define ADDROF_STAT	  0x08
#define PROG_STAT  	  0x10
#define SOFT_STAT	  0x20
#define DEBUG_STAT	  0x40
#define BOOT_STAT	  0x80
#define CLR_ALL_STAT  0xff

/* system oscillator and voltage definitions */

#define BOR_ENABLE()          {REG_ADDR = PD_ANA;REG_DATA &= 0xdf;}//开掉电复位
#define BOR_DISABLE()         {REG_ADDR = PD_ANA;REG_DATA |= 0x20;}//关掉电复位

#define PLL_WAKE_TIME_SET(x)        {REG_ADDR = IDLE_WAKE_CFG;REG_DATA &= ~(0x07);REG_DATA |= (0x07&x);}//唤醒PLL时间设置0~7:(0.2ms,0.3ms,0.4ms,0.5ms,0.6ms,0.7ms,0.9ms,1ms)
#define PLL_13P56M_WAKE_TIME_SET(x) {REG_ADDR = IDLE_WAKE_CFG;REG_DATA &= ~(0x18);REG_DATA |= (0x18&(x<<3));}//唤醒PLL_13.56M时间设置0~3:(1ms,1.5ms,2ms,2.5ms)

#define PLL_13P56M_ENABLE()   {REG_ADDR = PD_ANA;REG_DATA &= 0xf7;}//打开晶振13.56M
#define PLL_13P56M_DISABLE()  {REG_ADDR = PD_ANA;REG_DATA |= 0x08;}//关闭晶振13.56M
#define XTAL_32K_ENABLE()     {REG_ADDR = PD_ANA;REG_DATA &= 0xef;}//打开晶振32K
#define XTAL_32K_DISABLE()    {REG_ADDR = PD_ANA;REG_DATA |= 0x10;}//关闭晶振32K

#define SFR_LDO_SELECT(x)     {REG_ADDR = SFR_LDO_CTRL;REG_DATA &= ~0x08;REG_DATA |= (x<<3);}//0:配置字控制LDO功耗; 1:SFR控制LDO功耗
#define SFR_LDO_SET(x)        {REG_ADDR = SFR_LDO_CTRL;REG_DATA &= ~0x07;REG_DATA |= (x);}//设置LDO值

#define SOFT_RESET()          SOFT_RST = 0x55 //软复位

#define W8(addr,value)       (*(volatile unsigned char *)(addr))=((unsigned char)(value))
#define R8(addr)             (*(volatile unsigned char *)(addr))

#define W16(addr,value)      (*(volatile unsigned short *)(addr))=((unsigned short)(value))
#define R16(addr)		     (*(volatile unsigned short *)(addr))

#define W32(addr,value)      (*(volatile unsigned long *)(addr))=((unsigned long)(value))
#define R32(addr)		     (*(volatile unsigned long *)(addr))

/* multi interrupt flag definitions */
typedef enum
{
    INT_LED_FLAG    = 0,	/* interrupt flag of led   */
	INT_LCD_FLAG    = 1,	/* interrupt flag of lcd   */
	INT_RFID_FLAG   = 2,	/* interrupt flag of rfid  */
	INT_TIMER2_FLAG = 3,	/* interrupt flag of timer2*/
	INT_WDT_FLAG    = 4,	/* interrupt flag of wdt   */
	INT_08_FLAG     = 5,	/* interrupt flag of int0_8*/
	INT_07_FLAG     = 6,	/* interrupt flag of int0_7*/
	INT_06_FLAG     = 7,	/* interrupt flag of int0_6*/
	INT_05_FLAG     = 8,	/* interrupt flag of int0_5*/
	INT_04_FLAG     = 9,	/* interrupt flag of int0_4*/
	INT_03_FLAG     = 10,	/* interrupt flag of int0_3*/
	INT_02_FLAG     = 11,	/* interrupt flag of int0_2*/
	INT_01_FLAG     = 12,	/* interrupt flag of int0_1*/
	INT_00_FLAG     = 13,	/* interrupt flag of int0_0*/   	
	
}MultiIntFlag_enum;


/* function declarations */
/* apb sfr write */
void apb_sfr_write(uint8_t apb_sfr_addr,uint8_t apb_sfr_data);

/* apb sfr read */
uint8_t apb_sfr_read(uint8_t apb_sfr_addr);

/* interrupt enable */
void interrupt_enable(IRQn_Type irq,IntPrioStatus PrioStatus);

/* interrupt enable */
void interrupt_disable(IRQn_Type irq);

/*get reset state */
uint8_t get_system_rst_state(void);
/*clear reset state */
void system_rst_state_clear(uint8_t rst_flag);

#endif