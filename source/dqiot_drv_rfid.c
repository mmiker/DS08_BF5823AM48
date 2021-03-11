#ifndef __DQIOT_DRV_RFID_C__
#define __DQIOT_DRV_RFID_C__
#include "mmi_feature.h"
#ifdef __LOCK_RFID_CARD_SUPPORT__

#include "byd_init.h"
#include "dqiot_drv.h"
#include "byd_mifare.h"
#include "iso14443.h"
#include "delay.h"
#include "byd_adc.h"
// #include "stdio.h"

static unsigned short adc_last_value = 0;
/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_rfid_init(void)
{
#if 1 //MIFARE_EN
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
#if 1 //MIFARE_EN
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

	// printf("adc value %d\n", (int)adc_value);

	if (adc_last_value == 0)
	{
		adc_last_value = adc_value;
	}
	if (adc_value > 500)
	{
		if (adc_value < adc_last_value - 30 || adc_value > adc_last_value + 30) //(adc_value > adc_last_value + 50)||(adc_value < adc_last_value - 50))
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
	uint8_t ret = 0;
	RFID_ENABLE();
	if (get_card_number(uid) == RETURN_OK)
		ret = 1;
	else
		ret = 0;

	if (adc_last_value == 0 && ret == 0)
		dqiot_drv_rfid_check();

	RFID_DISABLE();
	return ret;
}
#endif
#endif
