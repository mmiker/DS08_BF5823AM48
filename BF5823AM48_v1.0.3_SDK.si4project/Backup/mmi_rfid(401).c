#ifndef __MMI_RFID_C__
#define __MMI_RFID_C__

#include "dqiot_drv.h"
#include "mmi_feature.h"
#include "mmi_rfid.h"
#include "string.h"
#include "stdlib.h"
#include "delay.h"

#ifdef __LOCK_RFID_CARD_SUPPORT__
#define RFID_SEC_DATA_LEN 12
unsigned char rfid_uid_buff_temp[RFID_SEC_DATA_LEN];
unsigned char rfid_uid_buff[2][RFID_SEC_DATA_LEN];
unsigned short adc_last_value = 0;

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_rfid_init(void)
{
	
}

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_rfid_check(void)
{
	#if 0
	unsigned short adc_value = 0;
	unsigned short temp = 0;
	unsigned char ret = 0;
	
	memset(rfid_uid_buff_temp,0x00,sizeof(rfid_uid_buff_temp));
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
			RFID_ENABLE();
			delay_ms(1);
			ret = get_card_number(rfid_uid_buff_temp);
			RFID_DISABLE();
		}
	}
	#endif
}

/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_rfid_gen_char(uint8_t index)
{
	uint8_t i=0;
	if(index >= 2)
		return RET_FAIL;
	for(i=0;i<RFID_SEC_DATA_LEN;i++)
	{
		rfid_uid_buff[index][i]=rfid_uid_buff_temp[i];
		rfid_uid_buff_temp[i] = 0x00;
	}
	return RET_SUCESS;
}


/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_rfid_match(void)
{
	if(memcmp((const char *)rfid_uid_buff[0],(const char *)rfid_uid_buff[1],RFID_SEC_DATA_LEN)== 0)
		return RET_SUCESS;
	return RET_FAIL;
}

/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_rfid_search_by_temp(uint8_t *index)
{
	return RET_FAIL;
}

/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_rfid_search_by_id(uint8_t id, uint8_t *index)
{
	return RET_FAIL;
}

/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_rfid_delete(uint8_t index)
{
	return RET_FAIL;
}

/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_rfid_store(uint8_t *index)
{
	return RET_FAIL;
}


#endif

#endif//__MMI_RFID_C__
