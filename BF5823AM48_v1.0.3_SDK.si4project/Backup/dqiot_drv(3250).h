/*!
    \file  dqiot_drv.h
*/

/*

*/

#ifndef __DQIOT_DRV_H__

#define __DQIOT_DRV_H__

#include "dqiot_gpio.h"

#define __DRV_UART0A_INT_SUPPORT__
#define __DRV_UART0B_INT_SUPPORT__

#define UART0_GET_DATA_LEN	20
#define UART0_SEND_DATA_LEN	20

#define KEY_TIMER_COUNT		1  //base 10ms
#define RFID_TIMER_COUNT	5  //base 10ms



/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_gpio_init(void);

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_init(void);

/*
parameter: 
	none
return :
	none
*/
uint16_t dqiot_drv_get_timer0_count(void);
/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_set_timer0_count(uint16_t count);

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_set_timer0_count(uint16_t count);
/*
parameter: 
	none
return :
	none
*/
uint16_t dqiot_drv_get_timer1_count(void);

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_set_timer1_count(uint16_t count);

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_ext_ldo_init(void);

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_ext_ldo_on(void);

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_ext_ldo_off(void);

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_key_led_init(void);

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_key_led_on(void);

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_key_led_off(void);

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_rgb_led_init(void);

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_timer0_init(void);
/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_timer0_start(void);
/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_timer0_stop(void);
/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_timer1_init(void);

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_timer1_start(void);

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_timer1_stop(void);
/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_uart0A_init(void);
/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_uart0B_init(void);

/*
parameter: 
	none
return :
	none
*/
unsigned char dqiot_drv_get_uart0_data(unsigned char len);

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_uart0_sendData(unsigned char *p_data, unsigned char length);

/*
parameter: 
	none
return :
	none
*/
unsigned char dqiot_drv_get_touch_flag(void);

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_log_output(unsigned char *string);
/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_log_output_data(unsigned char sym,unsigned int out_data);

#endif //__DQIOT_DRV_H__
