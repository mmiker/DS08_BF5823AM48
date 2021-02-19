/*!
    \file  mcu02_gpio.c
    \brief gpio driver
*/

/*
    Copyright (C) 2020 BYD

    2020-07-10, V1.0.0, firmware for mcu02
*/

#include "mcu02_gpio.h"
#include "mcu02_system.h"

/*!
    \brief      gpio init
    \param[in]  gpio_port: GPIOA/GPIOB/GPIOC/GPIOE/GPIOF/GPIOG/GPIOH
				gpio_pin : GPIO_PIN_(x),x = (0..7)
				gpio_mode : gpio mode
					GPIO_MODE_IN_FLOATING : floating input mode
					GPIO_MODE_IPU : pull-up input mode 
					GPIO_MODE_OUT : GPIO output 
					GPIO_MODE_OUT_OD : GPIO output with open-drain,only PC4/PC5/PE4/PE5
    \param[out] none
    \retval     none
*/
void gpio_init(GPIO_PORT_enum gpio_port,uint8_t gpio_pin,GPIO_MODE_enum gpio_mode)
{
	switch(gpio_port){
		case GPIOA:
			if(gpio_mode == GPIO_MODE_IN_FLOATING){
				TRISA |= gpio_pin;
				REG_ADDR = PU_PA;
	            REG_DATA &= (~gpio_pin);				
			}else if(gpio_mode == GPIO_MODE_IPU){
				TRISA |= gpio_pin;
                REG_ADDR = PU_PA;
	            REG_DATA |= (gpio_pin);
			}else if(gpio_mode == GPIO_MODE_OUT){
				TRISA &= ~gpio_pin;
			}

			break;

		case GPIOB:
			if(gpio_mode == GPIO_MODE_IN_FLOATING){
				TRISB |= gpio_pin;
                REG_ADDR = PU_PB;
	            REG_DATA &= (~gpio_pin);
			}else if(gpio_mode == GPIO_MODE_IPU){
				TRISB |= gpio_pin;
                REG_ADDR = PU_PB;
	            REG_DATA |= (gpio_pin);
			}else if(gpio_mode == GPIO_MODE_OUT){
				TRISB &= ~gpio_pin;
			}

			break;

		case GPIOC:
			if(gpio_mode == GPIO_MODE_IN_FLOATING){
				TRISC |= gpio_pin;
                REG_ADDR = PU_PC;
	            REG_DATA &= (~gpio_pin);
			}else if(gpio_mode == GPIO_MODE_IPU){
				TRISC |= gpio_pin;
                REG_ADDR = PU_PC;
	            REG_DATA |= (gpio_pin);
			}else if(gpio_mode == GPIO_MODE_OUT){
				TRISC &= ~gpio_pin;
				if(gpio_pin & 0x30){//PC4,PC5
                    REG_ADDR = ODRAIN_EN;
	                REG_DATA &= ~((gpio_pin&0x30)>>4);
				}
			}else if(gpio_mode == GPIO_MODE_OUT_OD){
				TRISC &= ~gpio_pin;
				REG_ADDR = ODRAIN_EN;
	            REG_DATA |= ((gpio_pin&0x30)>>4);
			}

			break;
		
		case GPIOE:
			if(gpio_mode == GPIO_MODE_IN_FLOATING){
				TRISE |= gpio_pin;
                REG_ADDR = PU_PE;
	            REG_DATA &= (~gpio_pin);
			}else if(gpio_mode == GPIO_MODE_IPU){
				TRISE |= gpio_pin;
                REG_ADDR = PU_PE;
	            REG_DATA |= (gpio_pin);
			}else if(gpio_mode == GPIO_MODE_OUT){
				TRISE &= ~gpio_pin;
				if(gpio_pin & 0x30){//PE4,PE5
					REG_ADDR = ODRAIN_EN;
	                REG_DATA &= ~((gpio_pin&0x30)>>2);
				}
			}else if(gpio_mode == GPIO_MODE_OUT_OD){
				TRISE &= ~gpio_pin;
                REG_ADDR = ODRAIN_EN;
	            REG_DATA |= ((gpio_pin&0x30)>>2);
			}

			break;

		case GPIOF:
			if(gpio_mode == GPIO_MODE_IN_FLOATING){
				TRISF |= gpio_pin;
                REG_ADDR = PU_PF;
	            REG_DATA &= (~gpio_pin);
			}else if(gpio_mode == GPIO_MODE_IPU){
				TRISF |= gpio_pin;
                REG_ADDR = PU_PF;
	            REG_DATA |= (gpio_pin);
			}else if(gpio_mode == GPIO_MODE_OUT){
				TRISF &= ~gpio_pin;
			}

			break;

		case GPIOG:
			if(gpio_mode == GPIO_MODE_IN_FLOATING){
				TRISG |= gpio_pin;
                REG_ADDR = PU_PG;
	            REG_DATA &= (~gpio_pin);
			}else if(gpio_mode == GPIO_MODE_IPU){
				TRISG |= gpio_pin;
                REG_ADDR = PU_PG;
	            REG_DATA |= (gpio_pin);
			}else if(gpio_mode == GPIO_MODE_OUT){
				TRISG &= ~gpio_pin;
			}

			break;

		case GPIOH:
			if(gpio_mode == GPIO_MODE_IN_FLOATING){
				TRISH |= gpio_pin;
                REG_ADDR = PU_PH;
	            REG_DATA &= (~gpio_pin);
			}else if(gpio_mode == GPIO_MODE_IPU){
				TRISH |= gpio_pin;
                REG_ADDR = PU_PH;
	            REG_DATA |= (gpio_pin);
			}else if(gpio_mode == GPIO_MODE_OUT){
				TRISH &= ~gpio_pin;
			}

			break;
		default:
			break;
	}
}

/*!
    \brief      gpio bit set
    \param[in]  gpio_port: GPIOA/GPIOB/GPIOC/GPIOE/GPIOF/GPIOG/GPIOH
				gpio_pin : GPIO_PIN_(x),x = (0..7)
    \param[out] none
    \retval     none
*/
void gpio_bit_set(GPIO_PORT_enum gpio_port,uint8_t gpio_pin)
{
	switch(gpio_port)
	{
		case GPIOA:
			DATAA |= gpio_pin;break;
		case GPIOB:
			DATAB |= gpio_pin;break;
		case GPIOC:
			DATAC |= gpio_pin;break;		
		case GPIOE:
			DATAE |= gpio_pin;break;
		case GPIOF:
			DATAF |= gpio_pin;break;
		case GPIOG:
			DATAG |= gpio_pin;break;
		case GPIOH:
			DATAH |= gpio_pin;break;
		default:
			break;
	}
}

/*!
    \brief      gpio bit reset
    \param[in]  gpio_port: GPIOA/GPIOB/GPIOC/GPIOE/GPIOF/GPIOG/GPIOH
				gpio_pin : GPIO_PIN_(x),x = (0..7)
    \param[out] none
    \retval     none
*/
void gpio_bit_reset(GPIO_PORT_enum gpio_port,uint8_t gpio_pin)
{	
	switch(gpio_port)
	{
		case GPIOA:
			DATAA &= ~gpio_pin;break;
		case GPIOB:
			DATAB &= ~gpio_pin;break;
		case GPIOC:
			DATAC &= ~gpio_pin;break;		
		case GPIOE:
			DATAE &= ~gpio_pin;break;
		case GPIOF:
			DATAF &= ~gpio_pin;break;
		case GPIOG:
			DATAG &= ~gpio_pin;break;
		case GPIOH:
			DATAH &= ~gpio_pin;break;
		default:
			break;
	}
}
