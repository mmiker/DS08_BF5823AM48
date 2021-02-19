#ifndef __MMI_KEY_H__
#define __MMI_KEY_H__


typedef enum KEY_VAL
{
	KEY_0 = 0x00,
	KEY_1 = 0x01,
	KEY_2 = 0x02,
	KEY_3 = 0x03,
	KEY_4 = 0x04,
	KEY_5 = 0x05,
	KEY_6 = 0x06,
	KEY_7 = 0x07,
	KEY_8 = 0x08,
	KEY_9 = 0x09,
	KEY_S = 0x0A,
	KEY_H = 0x0B,
	KEY_INVALID = 0xFF
}KEY_VAL;

#define KEY_LED_PWM_ON_H	80
#define KEY_LED_PWM_ON_L	20

#define KEY_LED_PWM_OFF_H	0
#define KEY_LED_PWM_OFF_L	100

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_key_get_value(void);
/*
parameter: 
	none
return :
	none
*/
void mmi_dq_key_work(void);

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_get_key_map(unsigned char index);

#endif //__MMI_KEY_H__

