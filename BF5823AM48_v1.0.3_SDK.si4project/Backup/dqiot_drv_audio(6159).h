#ifndef __DQIOT_DRV_AUDIO_H__
#define __DQIOT_DRV_AUDIO_H__

#include "dqiot_gpio.h"

/*
parameter: 
	none
return :
	none
*/
void drv_audio_gpio_init(void);

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

