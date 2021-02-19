#ifndef __DQIOT_DRV_AUDIO_C__
#define __DQIOT_DRV_AUDIO_C__

#include "dqiot_drv.h"
#include "dqiot_drv_audio.h"
#include "delay.h"

unsigned char g_audio_section = 0;

/*
parameter: 
	none
return :
	none
*/
void drv_audio_gpio_init(void)
{
	gpio_init(AUD_BUSY_PORT,AUD_BUSY_PIN,GPIO_MODE_IN_FLOATING);

	gpio_init(AUD_DATA_PORT,AUD_DATA_PIN,GPIO_MODE_OUT);
	gpio_bit_reset(AUD_DATA_PORT,AUD_DATA_PIN);

	gpio_init(AUD_RST_PORT,AUD_RST_PIN,GPIO_MODE_OUT);
	gpio_bit_reset(AUD_RST_PORT,AUD_RST_PIN);
	
	return;
}

/*
parameter: 
	none
return :
	none
*/
void drv_audio_init(void)
{
	
	return;
}


/*
parameter: 
	none
return :
	none
*/
unsigned char drv_audio_play(unsigned char play_setion)
{
	unsigned char i = 0;
	
	gpio_bit_set(AUD_RST_PORT,AUD_RST_PIN);
	delay_ms(200);
	gpio_bit_reset(AUD_RST_PORT,AUD_RST_PIN);
	delay_ms(200);
	for(i=0;i<play_setion;i++)
	{
		gpio_bit_set(AUD_DATA_PORT,AUD_DATA_PIN);
		delay_ms(100);
		gpio_bit_reset(AUD_DATA_PORT,AUD_DATA_PIN);
		delay_ms(100);
	}
	g_audio_section = play_setion;
	return 1;
}

/*
parameter: 
	none
return :
	none
*/
void drv_audio_stop(void)
{
	return;
}

/*
parameter: 
	none
return :
	none
*/
unsigned char drv_audio_check_busy(void)

{
	return 1;
}

/*
parameter: 
	none
return :
	none
*/
unsigned char drv_audio_get_section(void)
{
	return g_audio_section;
}

#endif//__DQIOT_DRV_AUDIO_C__

