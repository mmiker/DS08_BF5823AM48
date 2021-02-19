#ifndef __DQIOT_DRV_MOTOR_C__
#define __DQIOT_DRV_MOTOR_C__

#include "dqiot_drv.h"

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_motor_gpio_init(void)
{
	gpio_init(MOTOR_PWREN_PORT,MOTOR_PWREN_PIN,GPIO_MODE_OUT);
	gpio_bit_reset(MOTOR_PWREN_PORT,MOTOR_PWREN_PIN);

	gpio_init(MOTOR_A_PORT,MOTOR_A_PIN,GPIO_MODE_OUT);
	gpio_bit_reset(MOTOR_A_PORT,MOTOR_A_PIN);

	gpio_init(MOTOR_B_PORT,MOTOR_B_PIN,GPIO_MODE_OUT);
	gpio_bit_reset(MOTOR_B_PORT,MOTOR_B_PIN);
	return;
}

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_motor_gpio_deinit(void)
{
	gpio_init(MOTOR_PWREN_PORT,MOTOR_PWREN_PIN,GPIO_MODE_OUT);
	gpio_bit_reset(MOTOR_PWREN_PORT,MOTOR_PWREN_PIN);

	gpio_init(MOTOR_A_PORT,MOTOR_A_PIN,GPIO_MODE_OUT);
	gpio_bit_reset(MOTOR_A_PORT,MOTOR_A_PIN);

	gpio_init(MOTOR_B_PORT,MOTOR_B_PIN,GPIO_MODE_OUT);
	gpio_bit_reset(MOTOR_B_PORT,MOTOR_B_PIN);
	return;
}


/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_motor_init(void)
{
	
	return;
}

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_motor_turn_right(void)
{
	gpio_bit_set(MOTOR_PWREN_PORT,MOTOR_PWREN_PIN);
	gpio_bit_set(MOTOR_A_PORT,MOTOR_A_PIN);
	gpio_bit_reset(MOTOR_B_PORT,MOTOR_B_PIN);
	return;
}

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_motor_turn_back(void)
{
	gpio_bit_set(MOTOR_PWREN_PORT,MOTOR_PWREN_PIN);
	gpio_bit_reset(MOTOR_A_PORT,MOTOR_A_PIN);
	gpio_bit_set(MOTOR_B_PORT,MOTOR_B_PIN);
	return;
}

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_motor_stop(void)
{
	gpio_bit_reset(MOTOR_A_PORT,MOTOR_A_PIN);
	gpio_bit_reset(MOTOR_B_PORT,MOTOR_B_PIN);
	gpio_bit_reset(MOTOR_PWREN_PORT,MOTOR_PWREN_PIN);
}

#endif
