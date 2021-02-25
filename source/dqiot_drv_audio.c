#ifndef __DQIOT_DRV_AUDIO_C__
#define __DQIOT_DRV_AUDIO_C__

#include "dqiot_drv.h"
#include "dqiot_drv_audio.h"
#include "delay.h"

#define AUDIO_IN_BUSY           gpio_bit_get(AUD_BUSY_PORT,AUD_BUSY_PIN)

#define AUDIO_OUT_RST_LO        gpio_bit_reset(AUD_RST_PORT,AUD_RST_PIN)
#define AUDIO_OUT_RST_HI        gpio_bit_set(AUD_RST_PORT,AUD_RST_PIN)

#define AUDIO_OUT_DATA_LO       gpio_bit_reset(AUD_DATA_PORT,AUD_DATA_PIN)
#define AUDIO_OUT_DATA_HI       gpio_bit_set(AUD_DATA_PORT,AUD_DATA_PIN)
#define AUDIO_OUT_DATA_Toggle   gpio_bit_get(AUD_DATA_PORT,AUD_DATA_PIN) ? gpio_bit_reset(AUD_DATA_PORT,AUD_DATA_PIN) : gpio_bit_set(AUD_DATA_PORT,AUD_DATA_PIN)

uint8_t audio_flag=0; // 
uint8_t audio_section=0,audio_time_count=0;
#define AUDIO_MAX_CACHE_NUM  	20
static uint8_t audio_cache[AUDIO_MAX_CACHE_NUM] = {0};

static uint8_t audio_play_end_flag = 0;
/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_audio_gpio_init(void)
{
	gpio_init(AUD_BUSY_PORT,AUD_BUSY_PIN,GPIO_MODE_IPU);

	gpio_init(AUD_DATA_PORT,AUD_DATA_PIN,GPIO_MODE_OUT);
	gpio_bit_reset(AUD_DATA_PORT,AUD_DATA_PIN);

	gpio_init(AUD_RST_PORT,AUD_RST_PIN,GPIO_MODE_OUT);
	gpio_bit_set(AUD_RST_PORT,AUD_RST_PIN);
	
	return;
}

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_audio_gpio_deinit(void)
{
	gpio_init(AUD_BUSY_PORT,AUD_BUSY_PIN,GPIO_MODE_IN_FLOATING);
	gpio_bit_reset(AUD_BUSY_PORT,AUD_BUSY_PIN);
	
	gpio_init(AUD_DATA_PORT,AUD_DATA_PIN,GPIO_MODE_IN_FLOATING);
	gpio_bit_reset(AUD_DATA_PORT,AUD_DATA_PIN);

	gpio_init(AUD_RST_PORT,AUD_RST_PIN,GPIO_MODE_IN_FLOATING);
	gpio_bit_reset(AUD_RST_PORT,AUD_RST_PIN);
	
	return;
}


/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_audio_init(void)
{
	dqiot_drv_timer0_init(200);
	return;
}


/*
parameter: 
	none
return :
	none
*/
uint8_t dqiot_drv_audio_play(uint8_t play_setion)
{
	unsigned char i = 0;
	if(audio_flag == 0 && AUDIO_IN_BUSY == 1)
	{	
		audio_flag = 1;
		audio_section = play_setion;
		audio_time_count = 0;
		dqiot_drv_timer0_start();
	}
	else
	{
		for(i=0;i<AUDIO_MAX_CACHE_NUM;i++)
		{
			if(audio_cache[i]==0)
				break;
		}
		if(i<AUDIO_MAX_CACHE_NUM)
			audio_cache[i]=play_setion;
	}
		
	return 1;
}

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_audio_stop(void)
{
	char i = 0;

	if( audio_flag == 0&&AUDIO_IN_BUSY == 1)
		return;

	dqiot_drv_timer0_stop();

	for(i=0;i<AUDIO_MAX_CACHE_NUM;i++)
	{
		audio_cache[i]=0;
	}

	if(audio_time_count>=4)
	{
		audio_section = 0;
		audio_flag = 3;
		audio_time_count = 0;
	}
	else
	{
		audio_section = 0;
		audio_flag = 3;
	}
		
    dqiot_drv_timer0_start();
	return;
}

/*
parameter: 
	none
return :
	none
*/
uint8_t dqiot_drv_audio_check_busy(void)
{
	return AUDIO_IN_BUSY;
}

/*
parameter: 
	none
return :
	none
*/
uint8_t dqiot_drv_audio_get_state(void)
{
	return audio_flag;
}

/*
parameter: 
	none
return :
	none
*/
uint8_t dqiot_drv_audio_get_section(void)
{
	return audio_section;
}

/*
parameter: 
	none
return :
	none
*/
uint8_t dqiot_drv_audio_get_end_flag(void)
{
	if(audio_play_end_flag == 1)
	{
		audio_play_end_flag = 0;
		return 1;
	}
	return 0;
}	


/*
parameter: 
	none
return :
	none
*/
void Audio_Select_Handle_in_Timer(void)
{
	if(audio_flag == 1)
	{
		if(audio_time_count == 0)
		{
			AUDIO_OUT_RST_HI;
			AUDIO_OUT_DATA_LO;
		}
		else if(audio_time_count == 2)
		{
			AUDIO_OUT_RST_LO;
		}
		else if(audio_time_count >= 4)
		{
			//if(audio_time_count%2 == 0)
			//	AUDIO_OUT_DATA_HI;
			//else
			//	AUDIO_OUT_DATA_LO;
			PA0 = ~PA0;
		}
		audio_time_count ++;

		if(audio_time_count >= (audio_section + 1) * 2 + 4)
		{
			audio_time_count = 0;
			AUDIO_OUT_RST_LO;
			AUDIO_OUT_DATA_LO;
			audio_flag = 2;
		}
	}
	else if(audio_flag == 3)
	{
		if(audio_time_count == 0)
		{
			AUDIO_OUT_DATA_LO;
		}	
		else if(audio_time_count == 1)
		{
			AUDIO_OUT_RST_HI;
		}
		else if(audio_time_count == 3)
		{
			AUDIO_OUT_RST_LO;
		}
		audio_time_count ++;
		if(audio_time_count >= 4)
		{
			audio_time_count = 0;
			AUDIO_OUT_RST_LO;
			AUDIO_OUT_DATA_LO;
 			audio_flag = 2;
		}
		
	}

}

/*
parameter: 
	none
return :
	none
*/
void Audio_timer_event_handler(void)
{
	if((audio_flag == 2)&&(AUDIO_IN_BUSY == 1))
	{
		//extern void mmi_dq_sys_aud_end(void);
		if(audio_cache[0]==0)
		{
			audio_section = 0;
			dqiot_drv_timer0_stop();
			//mmi_dq_sys_aud_end();
			audio_play_end_flag = 1;
			audio_flag = 0;
		}
		else
		{
			char i = 0;
			audio_flag = 1;
			audio_section = audio_cache[0];
			for(i=0;i<AUDIO_MAX_CACHE_NUM-1;i++)
			{
				if(audio_cache[i+1]!=0)
				{
					audio_cache[i]=audio_cache[i+1];
				}
				else
					break;
			}
			audio_cache[i]=0;
			audio_time_count = 0;
		}
	}
	else
		Audio_Select_Handle_in_Timer();
}


#endif//__DQIOT_DRV_AUDIO_C__

