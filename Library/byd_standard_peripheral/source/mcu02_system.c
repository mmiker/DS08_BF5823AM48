/*!
    \file  mcu02_system.c
    \brief system driver
*/

/*
    Copyright (C) 2020 BYD

    2020-05-10, V1.0.0, firmware for mcu02
*/

#include "mcu02_system.h"

/*!
    \brief      apb sfr write 
    \param[in]  apb_sfr_addr: write apb sfr addr
                apb_sfr_data: write apb sfr data
    \param[out] none
    \retval     none
*/
void apb_sfr_write(uint8_t apb_sfr_addr,uint8_t apb_sfr_data)
{
	REG_ADDR = apb_sfr_addr;
	REG_DATA = apb_sfr_data;
}

/*!
    \brief      apb sfr read 
    \param[in]  apb_sfr_addr: apb sfr addr to read
    \param[out] none
    \retval     data read from apb sfr
*/
uint8_t apb_sfr_read(uint8_t apb_sfr_addr)
{
	REG_ADDR = apb_sfr_addr;
	return REG_DATA;
}

/*!
    \brief      interrupt cofig 
    \param[in]  IRQn_Type: 
						INT_EXTI_0 		:	 intterrupt vector of exti_0       
						INT_TIMER0      :	 intterrupt vector of timer0       
						INT_EXTI_1      :	 intterrupt vector of exti_1       
						INT_TIMER1      :	 intterrupt vector of timer1       
						INT_EXTI_2      :	 intterrupt vector of exti_2       
						INT_IIC         :	 intterrupt vector of iic          
						INT_ADC         :	 intterrupt vector of adc          
						INT_CSD         :	 intterrupt vector of csd          
						INT_LED_LCD_RFID:	 intterrupt vector of led/lcd/rfid 
						INT_WDT_TIMER2  :	 intterrupt vector of wdt/timer2   
						INT_SCI         :	 intterrupt vector of sci         
						INT_LVDT        :	 intterrupt vector of lvdt         
						INT_UART0       :	 intterrupt vector of uart0        
						INT_UART1       :	 intterrupt vector of uart1        
						INT_TIMER3_SM4  :	 intterrupt vector of timer3/sm4       
						INT_SPI1        :	 intterrupt vector of spi1         
						INT_EXTI_3      :	 intterrupt vector of exti_3   
					PrioStatus: interrupt priority
						HIGH :high priority
						LOW :low priority
    \param[out] none
    \retval     none
*/
//void interrupt_enable(IRQn_Type irq,IntPrioStatus PrioStatus)
//{	
//	if(irq <= INT_TIMER1){
//		IEN0 |= (0x01 << irq);
//		if(PrioStatus == HIGH){
//			IPL0 |= (0x01 << irq);
//		}
//	}else if(irq <= INT_WDT_TIMER2){
//		irq -= 7;
//		IEN1 |= (0x01 << irq);
//		if(PrioStatus == HIGH){
//			IPL1 |= (0x01 << irq);
//		}
//	}else{
//		irq -= INT_SCI;
//		IEN2 |= (0x01 << irq);
//		if(PrioStatus == HIGH){
//			IPL2 |= (0x01 << irq);
//		}
//	}	
//}
/*!
    \brief      interrup_disable 
    \param[in]  IRQn_Type:
						INT_EXTI_0 		:	 intterrupt of exti_0       
						INT_TIMER0      :	 intterrupt of timer0       
						INT_EXTI_1      :	 intterrupt of exti_1       
						INT_TIMER1      :	 intterrupt of timer1       
						INT_EXTI_2      :	 intterrupt of exti_2       
						INT_IIC         :	 intterrupt of iic          
						INT_ADC         :	 intterrupt of adc          
						INT_CSD         :	 intterrupt of csd          
						INT_LED_LCD_RFID:	 intterrupt of led/lcd/rfid 
						INT_WDT_TIMER2  :	 intterrupt of wdt/timer2   
						INT_SCI         :	 intterrupt of sci        
						INT_LVDT        :	 intterrupt of lvdt         
						INT_UART0       :	 intterrupt of uart0        
						INT_UART1       :	 intterrupt of uart1        
						INT_TIMER3_SM4  :	 intterrupt of timer3/sm4       
						INT_SPI1        :	 intterrupt of spi1         
						INT_EXTI_3      :	 intterrupt of exti_3
    \param[out] none
    \retval     none
*/
//void interrupt_disable(IRQn_Type irq)
//{
//	if(irq <= INT_TIMER1)
//	{
//		IEN0 &= ~(0x01 << irq);	
//	}
//	else if(irq <= INT_WDT_TIMER2)
//	{
//		irq -= 7;
//		IEN1 &= ~(0x01 << irq);		
//	}
//	else
//	{
//		irq -= INT_SCI;
//		IEN2 &= ~(0x01 << irq);		
//	}	
//}

/*!
    \brief      get system rst state
    \param[in]  none 
    \param[out] none
    \retval     reset state
                bit0:WDTRST_STAT     
                bit1:POR_STAT      
                bit2:BOR_STAT 
                bit3:ADDROF_STAT
                bit4:PROG_STAT  
                bit5:SOFT_STAT
                bit6:DEBUG_STAT
				bit7:BOOT_STAT
*/
uint8_t get_system_rst_state(void)
{
     REG_ADDR = RST_STAT;
	 return REG_DATA;
}

/*!
    \brief      clear system rst state
    \param[in]  rst_flag:
     			WDTRST_STAT     
                POR_STAT      
                BOR_STAT 
                ADDROF_STAT
                PROG_STAT  
                SOFT_STAT
                DEBUG_STAT
				BOOT_STAT
				CLR_ALL_STAT    
    \param[out] none
    \retval     none
*/
void system_rst_state_clear(uint8_t rst_flag)
{
	 REG_ADDR = RST_STAT;
	 REG_DATA &= ~rst_flag;
}