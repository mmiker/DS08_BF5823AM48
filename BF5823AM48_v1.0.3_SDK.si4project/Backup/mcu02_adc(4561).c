/*!
    \file  mcu02_adc.c
    \brief adc driver
*/

/*
    Copyright (C) 2020 BYD

    2020-05-08, V1.0.0, firmware for mcu02
*/
#include "mcu02_adc.h"


/*!
    \brief      close all adc io function
    \param[in]  none
    \param[out] none
    \retval     none
*/        
void adc_io_reset(void)
{
	ADC_IO_CGF0();
	ADC_IO_CGF1();
	ADC_IO_CGF2();
	ADC_IO_CGF3();
	ADC_IO_CGF4();
	ADC_IO_CGF5();	
}

