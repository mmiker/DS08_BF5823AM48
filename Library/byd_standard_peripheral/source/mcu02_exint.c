/*!
    \file  mcu02_exint.c
    \brief exint driver
*/

/*
    Copyright (C) 2018 BYD

    2020-05-12, V1.0.0, firmware for mcu02
*/

#include "mcu02_exint.h"
#if 0
/*!
    \brief      exti init
    \param[in]  int_port: exti port select
							EXTI_INT0_(x)(x = 0..8),
							EXTI_INT1,
							EXTI_INT2,
							EXTI_INT3,
							EXTI_INT4_(x)(x = 7..22)
				trigger : exti port trigge mode 
							EXTI_TRIG_BOTH :	rising and falling trigger 
							EXTI_TRIG_FALLING :	falling trigger 
							EXTI_TRIG_RISING :	rising edge trigger 
				status : enable or disable exti 
							ENABLE,
							DISABLE
				prio   : interrupt priority
						 	HIGH :high priority
							LOW  :low priority
    \param[out] none
    \retval     none
*/
void exti_init(EXTI_PORT_enum int_port,EXTI_TRIG_enum trigger,ControlStatus status,IntPrioStatus prio)
{
	uint8_t addr,pin;
	uint8_t trig_addr,trig_pin,irq;

	if(int_port <= EXTI_INT0_8){	/* exti_0_0 ~ exti_0_8*/
		if(int_port == EXTI_INT0_8){
			addr = PERIPH_IO_SEL1;
			trig_addr = EXT_INT_CON1;
			trig_pin = 0x00;
		}else{
			addr = PERIPH_IO_SEL2;
			trig_addr = EXT_INT_CON2;
			trig_pin = 0x00;
		}
		pin = (int_port & 0x07);
		irq = INT_EXTI_0;

	}else if(int_port <= EXTI_INT3){	/* exti_1/exti_2/exti_3 */
		addr = PERIPH_IO_SEL1;
		trig_addr = EXT_INT_CON1;
		trig_pin = ((int_port - EXTI_INT0_8) << 1);
		pin = (int_port & 0x07);

		if(int_port == EXTI_INT1)
			irq = INT_EXTI_1;
		else if(int_port == EXTI_INT2)
			irq = INT_EXTI_2;
		else
		    irq = INT_EXTI_3; 

	}else if(int_port <= EXTI_INT4_22){	/* exti_4 */
		addr = (int_port - NONE_0);
		addr = (PERIPH_IO_SEL3 + (addr>>3));
		pin = ((int_port - NONE_0) & 0x07);
		irq = INT_EXTI_4; 
	}
	if(status == ENABLE){
        REG_ADDR = addr;
	    REG_DATA |= (0x01 << pin);
		if(int_port < NONE_0){
            REG_ADDR = trig_addr;
	        REG_DATA &= ~(0x03 << trig_pin);
			REG_ADDR = trig_addr;
	        REG_DATA |= (trigger << trig_pin);
		}else{
			if(trigger == EXTI_TRIG_FALLING){
				REG_ADDR = EXT_INT_CON2;
	        	REG_DATA &= ~(0x04);
			}else if(trigger == EXTI_TRIG_RISING){
                REG_ADDR = EXT_INT_CON2;
	        	REG_DATA |= (0x04);
			}
		}
        
		interrupt_enable(irq,prio);

	}else{
		REG_ADDR = addr;
	    REG_DATA &= ~(0x01 << pin);
		interrupt_disable(irq);
	}
}
#endif