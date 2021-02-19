#ifndef __DQIOT_DRV_FP_C__
#define __DQIOT_DRV_FP_C__

#include "dqiot_drv.h"
#include "dqiot_drv_fp.h"
#include "delay.h"

//unsigned char test_data[] ={0xAA,0xAA,0x87,0x00,0x02,0x0A,0x01,0x01,0xE8};
unsigned char test_data[] ={0xEF,0x01,0xFF,0xFF,0xFF,0xFF,0x01,0x00,0x07,0x41,0x01,0x01,0x00,0x50,0x00,0x9B};

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_fp_gpio_init(void)
{
	gpio_init(FP_PWR_PORT,FP_PWR_PIN,GPIO_MODE_OUT);
	gpio_bit_set(FP_PWR_PORT,FP_PWR_PIN);

	gpio_init(FP_INT_PORT,FP_INT_PIN,GPIO_MODE_IPU);

	gpio_init(FP_TX_PORT,FP_TX_PIN,GPIO_MODE_OUT);
	gpio_bit_set(FP_TX_PORT,FP_TX_PIN);
	gpio_init(FP_RX_PORT,FP_RX_PIN,GPIO_MODE_IPU);
	gpio_bit_set(FP_RX_PORT,FP_RX_PIN);
	return;
}

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_fp_gpio_deinit(void)
{
	gpio_init(FP_TX_PORT,FP_TX_PIN,GPIO_MODE_OUT);
	gpio_bit_reset(FP_TX_PORT,FP_TX_PIN);
	
	gpio_init(FP_RX_PORT,FP_RX_PIN,GPIO_MODE_OUT);
	gpio_bit_reset(FP_RX_PORT,FP_RX_PIN);
	
	gpio_init(FP_PWR_PORT,FP_PWR_PIN,GPIO_MODE_OUT);
	gpio_bit_reset(FP_PWR_PORT,FP_PWR_PIN);

	//gpio_init(FP_INT_PORT,FP_INT_PIN,GPIO_MODE_IPU);

	return;
}


/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_fp_poweron(void)
{
    gpio_bit_reset(FP_PWR_PORT,FP_PWR_PIN);
	return;
}

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_fp_poweroff(void)
{
    gpio_bit_set(FP_PWR_PORT,FP_PWR_PIN);
	return;
}


/*
parameter: 
	none
return :
	none
*/
void drv_fp_test(void)
{
	
	delay_ms(100);

	dqiot_drv_uart0_sendData(test_data,16);

}


#endif//__DQIOT_DRV_FP_C__

