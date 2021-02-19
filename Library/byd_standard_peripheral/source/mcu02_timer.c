/*!
    \file  mcu02_timer.c
    \brief timer driver
*/

/*
    Copyright (C) 2018 BYD

    2020-07-16, V1.0.0, firmware for mcu02
*/

#include "mcu02_timer.h"
#include "mcu02_system.h"
#include "mcu02_clock.h"

uint8_t data TH0_reload = 0,TL0_reload = 0;
uint8_t data TH1_reload = 0,TL1_reload = 0;


/*!
    \brief      timer0 or timer1 init
    \param[in]  timer_port: TIMER0 or TIMER1
    \param[out] none
    \retval     none
*/
void timer0_1_init(TIMER_enum timer_port)
{	
	if(timer_port == TIMER0){
		
		TH0_reload = TH0;
		TL0_reload = TL0;		
		
	}else if(timer_port == TIMER1){
		
		TH1_reload = TH1;
		TL1_reload = TL1;		
	}
}

