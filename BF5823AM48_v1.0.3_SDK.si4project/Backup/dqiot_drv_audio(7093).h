#ifndef __DQIOT_DRV_AUDIO_H__
#define __DQIOT_DRV_AUDIO_H__

#include "mcu02_gpio.h"

#define AUD_BUSY_PORT	GPIOA
#define AUD_BUSY_PIN	GPIO_PIN_1

#define AUD_DATA_PORT	GPIOA
#define AUD_DATA_PIN	GPIO_PIN_0

#define AUD_RST_PORT	GPIOG
#define AUD_RST_PIN		GPIO_PIN_2

/*
parameter: 
	none
return :
	none
*/
void drv_audio_init(void);

/*
parameter: 
	none
return :
	none
*/
unsigned char drv_audio_check_busy(void);

/*
parameter: 
	none
return :
	none
*/
unsigned char drv_audio_get_section(void);

/*
parameter: 
	none
return :
	none
*/
unsigned char drv_audio_play(unsigned char play_setion);

#endif//__DQIOT_DRV_AUDIO_H__

