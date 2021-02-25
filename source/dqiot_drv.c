/*!
    \file  dqiot_drv.c
    \brief drv
*/

/*
    Copyright (C) 2018 BYD
*/
#ifndef __DQIOT_DRV_C__

#define __DQIOT_DRV_C__

#include "string.h"
//#include <stdio.h>
#include "stdlib.h"
#include "byd_ctk.h"
#include "dqiot_drv.h"

#include "mcu02_timer.h"
#include "mcu02_system.h"
#include "mcu02_uart.h"
#include "delay.h"

uint16_t timer1_count_flag = 0;

unsigned char uart_get_buf[UART0_GET_DATA_LEN];
//unsigned char uart_send_buf[UART0_SEND_DATA_LEN];
//unsigned char uart_sendbuflen = 0;
unsigned char uart_getbuflen = 0;

<<<<<<< HEAD
extern void timer0_event_handler(void);
extern void timer2_event_handler(void);
=======
extern void Audio_timer_event_handler(void);
extern void System_timer_event_handler(void);
>>>>>>> six commit
/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_gpio_init(void)
{
	dqiot_drv_ext_ldo_init();

	dqiot_drv_reset_gpio_init();
<<<<<<< HEAD
	
=======

>>>>>>> six commit
	dqiot_drv_key_led_gpio_init();
	dqiot_drv_rgb_led_gpio_init();

	dqiot_drv_audio_gpio_init();
	dqiot_drv_fp_gpio_init();
	dqiot_drv_motor_gpio_init();
<<<<<<< HEAD
	
	gpio_init(VBAT_TEST_PORT,VBAT_TEST_PIN,GPIO_MODE_OUT);
	gpio_bit_reset(VBAT_TEST_PORT,VBAT_TEST_PIN);

	gpio_init(VBAT_ADC_PORT,VBAT_ADC_PIN,GPIO_MODE_IN_FLOATING);
	//gpio_bit_reset(VBAT_ADC_PORT,VBAT_ADC_PIN);

	gpio_init(WIFI_SDA_PORT,WIFI_SDA_PIN,GPIO_MODE_OUT);
	gpio_bit_set(WIFI_SDA_PORT,WIFI_SDA_PIN);

	gpio_init(WIFI_SCL_PORT,WIFI_SCL_PIN,GPIO_MODE_OUT);
	gpio_bit_set(WIFI_SCL_PORT,WIFI_SCL_PIN);
	
	gpio_init(SW_PORT,SW_PIN,GPIO_MODE_IN_FLOATING);
	//gpio_bit_reset(SW_PORT,SW_PIN);

	gpio_init(GPIOE,GPIO_PIN_4,GPIO_MODE_IN_FLOATING);
	//gpio_bit_reset(GPIOE,GPIO_PIN_4);
	gpio_init(GPIOE,GPIO_PIN_5,GPIO_MODE_IN_FLOATING);
	//gpio_bit_reset(GPIOE,GPIO_PIN_5);
	gpio_init(GPIOE,GPIO_PIN_6,GPIO_MODE_IN_FLOATING);
	//gpio_bit_reset(GPIOE,GPIO_PIN_6);
	gpio_init(GPIOE,GPIO_PIN_7,GPIO_MODE_IN_FLOATING);
=======

	gpio_init(VBAT_TEST_PORT, VBAT_TEST_PIN, GPIO_MODE_OUT);
	gpio_bit_reset(VBAT_TEST_PORT, VBAT_TEST_PIN);

	gpio_init(VBAT_ADC_PORT, VBAT_ADC_PIN, GPIO_MODE_IN_FLOATING);
	//gpio_bit_reset(VBAT_ADC_PORT,VBAT_ADC_PIN);

	gpio_init(WIFI_SDA_PORT, WIFI_SDA_PIN, GPIO_MODE_OUT);
	gpio_bit_set(WIFI_SDA_PORT, WIFI_SDA_PIN);

	gpio_init(WIFI_SCL_PORT, WIFI_SCL_PIN, GPIO_MODE_OUT);
	gpio_bit_set(WIFI_SCL_PORT, WIFI_SCL_PIN);

	gpio_init(SW_PORT, SW_PIN, GPIO_MODE_IN_FLOATING);
	//gpio_bit_reset(SW_PORT,SW_PIN);

	gpio_init(GPIOE, GPIO_PIN_4, GPIO_MODE_IN_FLOATING);
	//gpio_bit_reset(GPIOE,GPIO_PIN_4);
	gpio_init(GPIOE, GPIO_PIN_5, GPIO_MODE_IN_FLOATING);
	//gpio_bit_reset(GPIOE,GPIO_PIN_5);
	gpio_init(GPIOE, GPIO_PIN_6, GPIO_MODE_IN_FLOATING);
	//gpio_bit_reset(GPIOE,GPIO_PIN_6);
	gpio_init(GPIOE, GPIO_PIN_7, GPIO_MODE_IN_FLOATING);
>>>>>>> six commit
	//gpio_bit_reset(GPIOE,GPIO_PIN_7);
	return;
}

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_wake_up(void)
{
<<<<<<< HEAD
	
	//WDT_ENABLE();
	
=======

	//WDT_ENABLE();

>>>>>>> six commit
	BOR_ENABLE();

	CSD_ENABLE();

	//RFID_ENABLE();

<<<<<<< HEAD

	//dqiot_drv_reset_gpio_init();
	
=======
	//dqiot_drv_reset_gpio_init();

>>>>>>> six commit
	dqiot_drv_key_led_gpio_init();
	dqiot_drv_rgb_led_gpio_init();

	dqiot_drv_audio_gpio_init();
	dqiot_drv_fp_gpio_init();
	dqiot_drv_motor_gpio_init();

<<<<<<< HEAD
	// dqiot_drv_fp_poweron();	

=======
>>>>>>> six commit
	dqiot_drv_ext_ldo_on();

	dqiot_drv_key_led_on();

<<<<<<< HEAD
	dqiot_drv_uart0B_init();

	//byd_setbaseline(0);//按键基线复位
	delay_ms(200);
=======
	//byd_setbaseline(0);//按键基线复位
	//delay_ms(200);
>>>>>>> six commit
	return;
}

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_enter_sleep(void)
{

	//dqiot_drv_reset_gpio_init();
	UART0_DISABLE();

	dqiot_drv_ext_ldo_off();
<<<<<<< HEAD
	
=======

>>>>>>> six commit
	dqiot_drv_audio_gpio_deinit();
	dqiot_drv_fp_gpio_deinit();
	dqiot_drv_motor_gpio_deinit();

	dqiot_drv_key_led_gpio_deinit();
	dqiot_drv_rgb_led_gpio_deinit();

<<<<<<< HEAD
//	rfid_enter_lowpower_config();
	
=======
	//	rfid_enter_lowpower_config();

>>>>>>> six commit
	CSD_DISABLE();

	//RFID_DISABLE();

	BOR_DISABLE();
<<<<<<< HEAD
	
=======

>>>>>>> six commit
	WDT_DISABLE();
	return;
}

<<<<<<< HEAD


=======
>>>>>>> six commit
/*!
    \brief      timer0 isr
    \param[in]  none
    \param[out] none
    \retval     none
*/
void dqiot_drv_timer0_isr(void) interrupt 1
{
	INT_TIMER0_CLR();

<<<<<<< HEAD
	timer0_event_handler();
=======
	Audio_timer_event_handler();
>>>>>>> six commit

	//if(GET_TIMER0_MODE() != TIMER_8BIT_AUTORELOAD)
	//{
	//	TH0 = TH0_reload;
	//	TL0 = TL0_reload;
	//}
}

/*!
    \brief      timer1 isr
    \param[in]  none
    \param[out] none
    \retval     none
*/
void dqiot_drv_timer1_isr(void) interrupt 3
{
	INT_TIMER1_CLR();

<<<<<<< HEAD
	if(GET_TIMER1_MODE() != TIMER_8BIT_AUTORELOAD){
=======
	if (GET_TIMER1_MODE() != TIMER_8BIT_AUTORELOAD)
	{
>>>>>>> six commit
		TH1 = TH1_reload;
		TL1 = TL1_reload;
	}
	timer1_count_flag++;
}

<<<<<<< HEAD

=======
>>>>>>> six commit
/*!
    \brief      timer2 isr
    \param[in]  none
    \param[out] none
    \retval     none
*/
void timer2_wdt_isr(void) interrupt 14
{

<<<<<<< HEAD
	INT_WDT_TIMER2_CLR();	
	if(GET_INT_TIMER2_FLAG_STATE())
	{
	    //timer2
	    timer2_event_handler();
	}
	else if(GET_INT_WDT_FLAG_STATE())
	{
	   //wdt
	}	

=======
	INT_WDT_TIMER2_CLR();
	if (GET_INT_TIMER2_FLAG_STATE())
	{
		//timer2
		System_timer_event_handler();
	}
	else if (GET_INT_WDT_FLAG_STATE())
	{
		//wdt
	}
>>>>>>> six commit
}

/*
parameter: 
	none
return :
	none
*/
uint16_t dqiot_drv_get_timer1_count(void)
{
	return timer1_count_flag;
}

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_set_timer1_count(uint16_t count)
{
	timer1_count_flag = count;
	return;
}

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_timer0_init(uint16_t us)
{
	uint16_t count;
	count = us;
<<<<<<< HEAD
	TIMER0_MODE_SET(TIMER_8BIT_AUTORELOAD);//TIMER_13BIT,TIMER_8BIT_AUTORELOAD,TIMER_8BIT	
	TIMER0_CT_MODE_SET(TIME_SELECT);//COUNT_SELECT
	TIMER0_COUNT_8BIT(count);//TIMER_16BIT
=======
	TIMER0_MODE_SET(TIMER_8BIT_AUTORELOAD); //TIMER_13BIT,TIMER_8BIT_AUTORELOAD,TIMER_8BIT
	TIMER0_CT_MODE_SET(TIME_SELECT);		//COUNT_SELECT
	TIMER0_COUNT_8BIT(count);				//TIMER_16BIT
>>>>>>> six commit
	timer0_1_init(TIMER0);
	return;
}

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_timer0_start(void)
{
	INT_TIMER0_CLR();
	TIMER0_IPL_SET(HIGH);
	TIMER0_INT_ENABLE();
	TIMER0_ENABLE();
}

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_timer0_stop(void)
{
	INT_TIMER0_CLR();
	TIMER0_DISABLE();
}

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_timer1_init(void)
{
	uint16_t count;
	count = 1000;
<<<<<<< HEAD
	TIMER1_MODE_SET(TIMER_16BIT);//TIMER_13BIT,TIMER_8BIT_AUTORELOAD,TIMER_8BIT	
	TIMER1_CT_MODE_SET(TIME_SELECT);//COUNT_SELECT
	TIMER1_COUNT_16BIT(count);//TIMER_16BIT
=======
	TIMER1_MODE_SET(TIMER_16BIT);	 //TIMER_13BIT,TIMER_8BIT_AUTORELOAD,TIMER_8BIT
	TIMER1_CT_MODE_SET(TIME_SELECT); //COUNT_SELECT
	TIMER1_COUNT_16BIT(count);		 //TIMER_16BIT
>>>>>>> six commit
	timer0_1_init(TIMER1);
	return;
}

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_timer1_start(void)
{
	INT_TIMER1_CLR();
	TIMER1_IPL_SET(LOW);
	TIMER1_INT_ENABLE();
	TIMER1_ENABLE();
}

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_timer1_stop(void)
{
	INT_TIMER0_CLR();
	TIMER0_DISABLE();
	dqiot_drv_set_timer1_count(0);
	return;
}

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_timer2_init(void)
{
	/*
	   t = prescale*(1000000/32768)*(count+1) us 
	   prescale = 1,65536	
<<<<<<< HEAD
	*/	  
	uint16_t count;
	count = 3276;
	TIMER2_CLOCK_SELECT(TIMER2_CLOCK_XTAL);//TIMER2_CLOCK_XTAL选择外部晶振要使能XTAL_32K_ENABLE()
	TIMER2_AUTO_RELOAD(ENABLE);//ENABLE
	TIMER2_PRESCALE(TIMER2_PRESCALE_1);//TIMER2_PRESCALE_65536
	TIMER2_COUNT_SET(count);
	
	INT_WDT_TIMER2_CLR();//清除中断标志	
	TIMER2_IPL_SET(LOW); //中断优先级为低
	TIMER2_INT_DISABLE();//关闭中断
=======
	*/
	uint16_t count;
	count = 3276;
	TIMER2_CLOCK_SELECT(TIMER2_CLOCK_XTAL); //TIMER2_CLOCK_XTAL选择外部晶振要使能XTAL_32K_ENABLE()
	TIMER2_AUTO_RELOAD(ENABLE);				//ENABLE
	TIMER2_PRESCALE(TIMER2_PRESCALE_1);		//TIMER2_PRESCALE_65536
	TIMER2_COUNT_SET(count);

	INT_WDT_TIMER2_CLR(); //清除中断标志
	TIMER2_IPL_SET(LOW);  //中断优先级为低
	TIMER2_INT_DISABLE(); //关闭中断
>>>>>>> six commit
	return;
}

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_timer2_start(void)
{
	//INT_WDT_TIMER2_CLR();
	TIMER2_IPL_SET(LOW);
	TIMER2_INT_ENABLE();
	TIMER2_ENABLE();
	return;
}

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_timer2_stop(void)
{
	//INT_WDT_TIMER2_CLR();
	TIMER2_DISABLE();
	return;
}

<<<<<<< HEAD

=======
>>>>>>> six commit
/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_uart0A_init(void)
{
<<<<<<< HEAD
	GPIOE_BIT_SET(GPIO_PIN_4|GPIO_PIN_5);//避免有毛刺
	 	
	UART0_PORT_SET(UART0_PE4_PE5);
	UART0_CON2 = 0;
	UART0_STATE = 0;
    uart_baudrate_config(UART0,UART_BAUDRATE_57600);//波特率
	UART0_STOP_MODE(STOP_WIDTH_1BIT);//停止位
	UART0_DATA_MODE(DATA_MODE_8BIT);//数据位
	UART0_PARITY_SET(DISABLE); //奇偶校验使能
	UART0_PARITY_SEL(ODD_PARITY);//奇偶校验选择
    UART0_MULTI_MODE(DISABLE);//多处理器通信模式
	
	UART0_RX_ENABLE();//接收使能 
#ifdef __DRV_UART0A_INT_SUPPORT__   
	UART0_TX_INT_ENABLE();//发送中断使能
	UART0_RX_INT_ENABLE();//接收中断使能
	INT_UART0_CLR();//清除中断源标志
	UART0_IPL_SET(LOW);//中断优先级设置
	UART0_INT_ENABLE();//中断源	
#else
	UART0_TX_INT_DISABLE();//发送中断关闭
	UART0_RX_INT_DISABLE();//接收中断关闭
=======
	GPIOE_BIT_SET(GPIO_PIN_4 | GPIO_PIN_5); //避免有毛刺

	UART0_PORT_SET(UART0_PE4_PE5);
	UART0_CON2 = 0;
	UART0_STATE = 0;
	uart_baudrate_config(UART0, UART_BAUDRATE_57600); //波特率
	UART0_STOP_MODE(STOP_WIDTH_1BIT);				  //停止位
	UART0_DATA_MODE(DATA_MODE_8BIT);				  //数据位
	UART0_PARITY_SET(DISABLE);						  //奇偶校验使能
	UART0_PARITY_SEL(ODD_PARITY);					  //奇偶校验选择
	UART0_MULTI_MODE(DISABLE);						  //多处理器通信模式

	UART0_RX_ENABLE(); //接收使能
#ifdef __DRV_UART0A_INT_SUPPORT__
	UART0_TX_INT_ENABLE(); //发送中断使能
	UART0_RX_INT_ENABLE(); //接收中断使能
	INT_UART0_CLR();	   //清除中断源标志
	UART0_IPL_SET(LOW);	   //中断优先级设置
	UART0_INT_ENABLE();	   //中断源
#else
	UART0_TX_INT_DISABLE(); //发送中断关闭
	UART0_RX_INT_DISABLE(); //接收中断关闭
>>>>>>> six commit
#endif

	// memset(uart_get_buf, 0x00, sizeof(uart_get_buf));
	// uart_getbuflen = 0;

<<<<<<< HEAD
	UART0_ENABLE();//使能uart0
=======
	UART0_ENABLE(); //使能uart0
>>>>>>> six commit
	return;
}

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_uart0B_init(void)
{
<<<<<<< HEAD
	GPIOF_BIT_SET(GPIO_PIN_4|GPIO_PIN_5);//避免有毛刺
	 	
	UART0_PORT_SET(UART0_PF4_PF5);
	UART0_CON2 = 0;
	UART0_STATE = 0;
    uart_baudrate_config(UART0,UART_BAUDRATE_57600);//波特率
	UART0_STOP_MODE(STOP_WIDTH_1BIT);//停止位
	UART0_DATA_MODE(DATA_MODE_8BIT);//数据位
	UART0_PARITY_SET(DISABLE); //奇偶校验使能
	UART0_PARITY_SEL(ODD_PARITY);//奇偶校验选择
    UART0_MULTI_MODE(DISABLE);//多处理器通信模式
	
	UART0_RX_ENABLE();//接收使能 
#ifdef __DRV_UART0B_INT_SUPPORT__   
   	//UART0_TX_INT_ENABLE();//发送中断使能
   	UART0_TX_INT_ENABLE();//发送中断关闭
	UART0_RX_INT_ENABLE();//接收中断使能
	INT_UART0_CLR();//清除中断源标志
	UART0_IPL_SET(HIGH);//中断优先级设置
	UART0_INT_ENABLE();//中断源	
#else
	UART0_TX_INT_DISABLE();//发送中断关闭
	UART0_RX_INT_DISABLE();//接收中断关闭
=======
	GPIOF_BIT_SET(GPIO_PIN_4 | GPIO_PIN_5); //避免有毛刺

	UART0_PORT_SET(UART0_PF4_PF5);
	UART0_CON2 = 0;
	UART0_STATE = 0;
	uart_baudrate_config(UART0, UART_BAUDRATE_57600); //波特率
	UART0_STOP_MODE(STOP_WIDTH_1BIT);				  //停止位
	UART0_DATA_MODE(DATA_MODE_8BIT);				  //数据位
	UART0_PARITY_SET(DISABLE);						  //奇偶校验使能
	UART0_PARITY_SEL(ODD_PARITY);					  //奇偶校验选择
	UART0_MULTI_MODE(DISABLE);						  //多处理器通信模式

	UART0_RX_ENABLE(); //接收使能
#ifdef __DRV_UART0B_INT_SUPPORT__
	//UART0_TX_INT_ENABLE();//发送中断使能
	UART0_TX_INT_ENABLE(); //发送中断关闭
	UART0_RX_INT_ENABLE(); //接收中断使能
	INT_UART0_CLR();	   //清除中断源标志
	UART0_IPL_SET(HIGH);   //中断优先级设置
	UART0_INT_ENABLE();	   //中断源
#else
	UART0_TX_INT_DISABLE(); //发送中断关闭
	UART0_RX_INT_DISABLE(); //接收中断关闭
>>>>>>> six commit
#endif

	// memset(uart_get_buf, 0x00, sizeof(uart_get_buf));
	// uart_getbuflen = 0;

<<<<<<< HEAD
	UART0_ENABLE();//使能uart0
=======
	UART0_ENABLE(); //使能uart0
>>>>>>> six commit
	return;
}

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_uart0_isr(void) interrupt 17
{

<<<<<<< HEAD
		if(GET_UART0_RX_STATE())
		{
			if(uart_getbuflen >= UART0_GET_DATA_LEN )
				return;
			else
				uart_get_buf[uart_getbuflen++] = UART0_BUF;
			CLR_UART0_RX_STATE();//清除接收中断标志位
		}
		//if(GET_UART0_TX_STATE())
		//{
		//	CLR_UART0_TX_STATE();//清除发送中断标志位
		//	UART0_TX_INT_DISABLE(); 	
		//}

=======
	if (GET_UART0_RX_STATE())
	{
		if (uart_getbuflen >= UART0_GET_DATA_LEN)
			return;
		else
			uart_get_buf[uart_getbuflen++] = UART0_BUF;
		CLR_UART0_RX_STATE(); //清除接收中断标志位
	}
	//if(GET_UART0_TX_STATE())
	//{
	//	CLR_UART0_TX_STATE();//清除发送中断标志位
	//	UART0_TX_INT_DISABLE();
	//}
>>>>>>> six commit
}

/*
parameter: 
	none
return :
	none
*/
unsigned char dqiot_drv_get_uart0_data(unsigned char len)
{
	return uart_get_buf[len];
}

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_clr_uart0_data(void)
{
	memset(uart_get_buf, 0, sizeof(uart_get_buf));
	uart_getbuflen = 0;
}

<<<<<<< HEAD

=======
>>>>>>> six commit
/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_uart0_sendData(unsigned char *p_data, unsigned char length)
{
<<<<<<< HEAD
	#if 1
=======
#if 1
>>>>>>> six commit
	unsigned char i = 0;
	//dqiot_drv_uart0B_init();
	//memset(uart_send_buf,0x00,sizeof(uart_send_buf));
	//memcpy(uart_send_buf,p_data,length);
	//uart_sendbuflen = length;

<<<<<<< HEAD
	for(i=0;i<length;i++)
	{
		uart_tx_byte(UART0,p_data[i]);
	}
	#endif
=======
	for (i = 0; i < length; i++)
	{
		uart_tx_byte(UART0, p_data[i]);
	}
#endif
>>>>>>> six commit
}

char putchar(char c)
{
<<<<<<< HEAD
     uart_tx_byte(UART0,c);
     return c;
}


=======
	uart_tx_byte(UART0, c);
	return c;
}

>>>>>>> six commit
#endif //__DQIOT_DRV_C__
