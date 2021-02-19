#ifndef __DQIOT_DRV_RFID_C__
#define __DQIOT_DRV_RFID_C__

#include "byd_init.h"
#include "dqiot_drv.h"
#include "byd_mifare.h" 
#include "iso14443.h"
#include "delay.h"
#include "byd_adc.h"

static unsigned short adc_last_value = 0;
/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_rfid_init(void)
{
#if MIFARE_EN
	rfid_config();
#endif
}


/*
parameter: 
	none
return :
	none
*/
uint8_t dqiot_drv_rfid_check(void)
{
#if MIFARE_EN
	unsigned short adc_value = 0;
	unsigned short temp = 0;
	unsigned char ret = 0;
	
	RFID_ENABLE();
	ADC_ENABLE();
	delay_us(20);
	temp = get_adc_data(ADC_CHANNEL_7);
	RFID_DISABLE();
	ADC_DISABLE();

	adc_value = temp;

	if(adc_last_value == 0)
	{
		adc_last_value = adc_value;
	}
	if(adc_value > 500)
	{
		if((adc_value > adc_last_value + 200)||(adc_value < adc_last_value - 200))
		{
			return 1;
		}
	}
#endif
	return 0;
}


/*
parameter: 
	none
return :
	none
*/
uint8_t dqiot_drv_rfid_get_card_number(uint8_t *uid)
{
	if(get_card_number(uid) == RETURN_OK)
		return 1;
	else
		return 0;
}
#endif
