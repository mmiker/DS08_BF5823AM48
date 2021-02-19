/*!
    \file  byd_adc.h
    \brief adc define
*/

/*
    Copyright (C) 2020 BYD

    2020-05-08, V1.0.0, app for byd
*/

#ifndef BYD_ADC_H
#define	BYD_ADC_H

#include "mcu02_adc.h"
#include "mcu02_system.h"

#define ADC_HANDLE          0
#define ADC_MAX_COUNT       14
#define ADC_NOISE_THRESHOLD 3

#define ADC_MODE  			1 /*0:interrupt; 1:inquiry */

/* variable declarations */
extern volatile bit g_bAdcIntFlag;

/* function declarations */
void byd_adc_init(void);
uint16_t get_adc_data(uint8_t adc_channel_addr);
uint8_t byd_adc_handle(uint8_t adc_channel_addr);
void byd_adc_work(void);

unsigned char adc_VolT(void);
#endif