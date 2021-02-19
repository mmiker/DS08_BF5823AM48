/*!
    \file  dqiot_drv.h
*/

/*

*/

#ifndef __DQIOT_DRV_H__

#define __DQIOT_DRV_H__

#include "dqiot_gpio.h"
#include "dqiot_drv_audio.h"
#include "dqiot_drv_fp.h"
#include "dqiot_drv_motor.h"
#include "dqiot_drv_led.h"
#include "dqiot_drv_reset.h"
#include "dqiot_drv_ldo.h"
#include "dqiot_drv_rfid.h"
#include "dqiot_drv_touch.h"

#include "bydmcu_libopt.h"


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
void dqiot_drv_wake_up(void);

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_enter_sleep(void);

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
void dqiot_drv_timer0_init(uint16_t us);
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
void dqiot_drv_log_output(unsigned char *string);
/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_log_output_data(unsigned char sym,unsigned int out_data);

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_timer2_init(void);

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_timer2_start(void);

#endif //__DQIOT_DRV_H__
