#ifndef __MMI_RFID_C__
#define __MMI_RFID_C__

#include "dqiot_drv.h"
#include "mmi_feature.h"
#include "mmi_rfid.h"

#ifdef __LOCK_RFID_CARD_SUPPORT__
unsigned char rfid_uid_buff[12];
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
	unsigned short adc_value = 0;
	unsigned short temp = 0;
	unsigned char ret = 0;
	
	memset(rfid_uid_buff,0x00,sizeof(rfid_uid_buff));
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
			ret = get_card_number(rfid_uid_buff);
			RFID_DISABLE();
		}
	}
}
/*
parameter: 
	none
return :
	none
*/
void mmi_dq_rfid_config(void)
{
	return;
}
/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_rfid_wait_rfid_tx_complete(void)
{
	return RET_SUCESS;
}
/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_rfid_transmit(unsigned char *buf,unsigned char len)
{
	return RET_SUCESS;
}
/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_rfid_transmit_bit(unsigned char *buf, unsigned char len)
{
	return RET_SUCESS;
}
/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_rfid_transmit_9bit(unsigned char *buf, unsigned char *paritybuf,unsigned char len)
{
	return RET_SUCESS;
}
/*
parameter: 
	current status machine
return :
	none
*/
RET_VAL mmi_dq_set_rfid_receive_bit(unsigned char *buf,unsigned char len)
{
	return RET_SUCESS;
}
/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_rfid_receive(unsigned char *buf,unsigned char *anti_byte,unsigned char len)
{
	return RET_SUCESS;
}
/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_rfid_byte_err_bit(void)
{
	unsigned char err_bit = 0;
	return err_bit;
}

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_rfid_rx(unsigned char *buf)
{
	return;
}

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_rfid_rx_bit(void)
{
	unsigned char rx_bit = 0;
	return rx_bit;
}

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_rfid_enter_lowpower_config(void)
{
	return;
}

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_rfid_exit_lowpower_config(void)
{
	return;
}
#endif

#endif//__MMI_RFID_C__
