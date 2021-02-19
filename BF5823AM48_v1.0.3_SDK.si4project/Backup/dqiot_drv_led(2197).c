#ifndef __DQIOT_DRV_LED_C__
#define __DQIOT_DRV_LED_C__

#include "dqiot_drv.h"
#include "dqiot_drv_led.h"

/*
parameter: 
	none
return :
	none
*/
void drv_key_led_gpio_init(void)
{
	gpio_init(KEY_LED_1_PORT,KEY_LED_1_PIN,GPIO_MODE_OUT);
	gpio_init(KEY_LED_2_PORT,KEY_LED_2_PIN,GPIO_MODE_OUT);
	gpio_init(KEY_LED_3_PORT,KEY_LED_3_PIN,GPIO_MODE_OUT);
	gpio_bit_set(KEY_LED_1_PORT,KEY_LED_1_PIN);
	gpio_bit_set(KEY_LED_2_PORT,KEY_LED_2_PIN);
	gpio_bit_set(KEY_LED_3_PORT,KEY_LED_3_PIN);

	return;
}

/*
parameter: 
	none
return :
	none
*/
void drv_key_led_on(void)
{
	gpio_bit_reset(KEY_LED_1_PORT,KEY_LED_1_PIN);
	gpio_bit_reset(KEY_LED_2_PORT,KEY_LED_2_PIN);
	gpio_bit_reset(KEY_LED_3_PORT,KEY_LED_3_PIN);

	return;
}

/*
parameter: 
	none
return :
	none
*/
void drv_key_led_off(void)
{
	gpio_bit_set(KEY_LED_1_PORT,KEY_LED_1_PIN);
	gpio_bit_set(KEY_LED_2_PORT,KEY_LED_2_PIN);
	gpio_bit_set(KEY_LED_3_PORT,KEY_LED_3_PIN);

	return;
}

/*
parameter: 
	none
return :
	none
*/
void drv_rgb_led_gpio_init(void)
{
	gpio_init(RGB_LED_R_PORT,RGB_LED_R_PIN,GPIO_MODE_OUT);
	gpio_init(RGB_LED_G_PORT,RGB_LED_G_PIN,GPIO_MODE_OUT);
	gpio_init(RGB_LED_B_PORT,RGB_LED_B_PIN,GPIO_MODE_OUT);
	gpio_bit_reset(RGB_LED_R_PORT,RGB_LED_R_PIN);
	gpio_bit_reset(RGB_LED_G_PORT,RGB_LED_G_PIN);
	gpio_bit_reset(RGB_LED_B_PORT,RGB_LED_B_PIN);

	return;
}

#endif
