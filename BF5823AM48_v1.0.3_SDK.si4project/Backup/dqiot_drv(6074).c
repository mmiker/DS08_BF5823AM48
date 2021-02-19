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
#include "stdlib.h"
#include "byd_ctk.h"
#include "dqiot_drv.h"
#include "dqiot_drv_audio.h"
#include "dqiot_drv_fp.h"
#include "dqiot_drv_motor.h"
#include "dqiot_drv_led.h"
#include "dqiot_drv_reset.h"

#include "mcu02_timer.h"
#include "mcu02_system.h"
#include "mcu02_uart.h"

uint16_t timer0_count_flag = 0;
uint16_t timer1_count_flag = 0;

unsigned char key_check_flag = 0;
unsigned char rfid_check_flag = 0;
unsigned char uart_get_buf[UART0_GET_DATA_LEN];
unsigned char uart_send_buf[UART0_SEND_DATA_LEN];
unsigned char uart_sendbuflen = 0;
unsigned char uart_getbuflen = 0;


unsigned char falg = 0;
/*!
    \brief      timer0 isr
    \param[in]  none
    \param[out] none
    \retval     none
*/
void dqiot_drv_timer0_isr(void) interrupt 1
{
	INT_TIMER0_CLR();

	if(GET_TIMER0_MODE() != TIMER_8BIT_AUTORELOAD)
	{
		TH0 = TH0_reload;
		TL0 = TL0_reload;
	}
	timer0_count_flag++;
}

/*!
    \brief      timer0 isr
    \param[in]  none
    \param[out] none
    \retval     none
*/
void dqiot_drv_timer1_isr(void) interrupt 3
{
	INT_TIMER1_CLR();

	if(GET_TIMER1_MODE() != TIMER_8BIT_AUTORELOAD){
		TH1 = TH1_reload;
		TL1 = TL1_reload;
	}
	timer1_count_flag++;
}

/*
parameter: 
	none
return :
	none
*/
uint16_t dqiot_drv_get_timer0_count(void)
{
	return timer0_count_flag;
}

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_set_timer0_count(uint16_t count)
{
	timer0_count_flag = count;
	return;
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
void dqiot_drv_gpio_init(void)
{
	dqiot_drv_ext_ldo_init();

	drv_reset_gpio_init();
	
	drv_key_led_gpio_init();
	drv_rgb_led_gpio_init();

	drv_audio_gpio_init();
	drv_fp_gpio_init();
	drv_motor_gpio_init();

	return;
}


/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_init(void)
{
	dqiot_drv_timer0_init();
	dqiot_drv_timer0_start();
	memset(uart_get_buf,0x00,sizeof(uart_get_buf));
	uart_getbuflen = 0;
	uart_sendbuflen = 0;
	drv_fp_init();
	
	return;
}

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_key_proc(void)
{
	
}

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_rfid_proc(void)
{
	
}

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_ext_ldo_init(void)
{
	gpio_init(EXT_LDO_PORT,EXT_LDO_PIN,GPIO_MODE_OUT);
	gpio_bit_reset(EXT_LDO_PORT,EXT_LDO_PIN);
	return;
}

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_ext_ldo_on(void)
{
	gpio_bit_set(EXT_LDO_PORT,EXT_LDO_PIN);
	return;
}

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_ext_ldo_off(void)
{
	gpio_bit_reset(EXT_LDO_PORT,EXT_LDO_PIN);
	return;
}

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_timer0_init(void)
{
	uint16_t count;
	count = 1000;
	TIMER0_MODE_SET(TIMER_16BIT);//TIMER_13BIT,TIMER_8BIT_AUTORELOAD,TIMER_8BIT	
	TIMER0_CT_MODE_SET(TIME_SELECT);//COUNT_SELECT
	TIMER0_COUNT_16BIT(count);//TIMER_16BIT
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
	TIMER0_IPL_SET(LOW);
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
	//INT_TIMER0_CLR();
	//TIMER0_DISABLE();
	dqiot_drv_set_timer0_count(0);
	return;
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
	TIMER1_MODE_SET(TIMER_16BIT);//TIMER_13BIT,TIMER_8BIT_AUTORELOAD,TIMER_8BIT	
	TIMER1_CT_MODE_SET(TIME_SELECT);//COUNT_SELECT
	TIMER1_COUNT_16BIT(count);//TIMER_16BIT
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
	return;
}


/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_uart0A_init(void)
{
	GPIOC_BIT_SET(GPIO_PIN_4|GPIO_PIN_5);//避免有毛刺
	 	
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
#endif
	UART0_ENABLE();//使能uart0
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
	GPIOC_BIT_SET(GPIO_PIN_4|GPIO_PIN_5);//避免有毛刺
	 	
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
   	UART0_TX_INT_ENABLE();//发送中断使能
	UART0_RX_INT_ENABLE();//接收中断使能
	INT_UART0_CLR();//清除中断源标志
	UART0_IPL_SET(LOW);//中断优先级设置
	UART0_INT_ENABLE();//中断源	
#else
	UART0_TX_INT_DISABLE();//发送中断关闭
	UART0_RX_INT_DISABLE();//接收中断关闭
#endif
	UART0_ENABLE();//使能uart0
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
	INT_UART0_CLR();
	
	if(GET_UART0_RX_STATE())
	{
		uart_sendbuflen = 5;
		CLR_UART0_RX_STATE();//清除接收中断标志位
	}
	else
	{
		if(uart_getbuflen == UART0_GET_DATA_LEN )
			return;
		else
			uart_get_buf[uart_getbuflen++] = UART0_BUF;
	}
//	if(GET_UART0_TX_STATE())
//	{
//		CLR_UART0_TX_STATE();//清除发送中断标志位
//      UART0_TX_INT_DISABLE();		
//	}
}

/*
parameter: 
	none
return :
	none
*/
unsigned char dqiot_drv_get_uart0_data(unsigned char len)
{
	//if(len > UART0_GET_DATA_LEN)
	//	return 0xFF;
	//else
	{
		if(len == 0)
			return uart_sendbuflen;
		else if(len == 1)
			return uart_getbuflen;
		else
			return uart_get_buf[len-2];
	}
}

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_uart0_sendData(unsigned char *p_data, unsigned char length)
{
	unsigned char i = 0;
	dqiot_drv_uart0B_init();
	memset(uart_send_buf,0x00,sizeof(uart_send_buf));
	memcpy(uart_send_buf,p_data,length);
	uart_sendbuflen = length;

	for(i=0;i<length;i++)
	{
		uart_tx_byte(UART0,uart_send_buf[i]);
		//dqiot_drv_log_output_data('&',uart_send_buf[i]);
	}
}


/*
parameter: 
	none
return :
	none
*/
unsigned char dqiot_drv_get_touch_flag(void)
{
	unsigned char touch_flag = 0;
	
	touch_flag = byd_get_touch_flag();

	return touch_flag;
}

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_log_output(unsigned char *string)
{
	dqiot_drv_uart0A_init();
	while((*string != '\r')&&(*(string+1) != '\n'))
	{
		uart_tx_byte(UART0,*string++);
	}
	uart_tx_byte(UART0,'\r');
	uart_tx_byte(UART0,'\n');
	return;
}

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_log_output_data(unsigned char sym,unsigned int out_data)
{
	unsigned char i = 0,j = 0;
	unsigned char data_temp[10];
	unsigned int temp_data = out_data;
	dqiot_drv_uart0A_init();
	
	memset(data_temp,0x00,sizeof(data_temp));
	for(i=0;i<10;i++)
		uart_tx_byte(UART0,sym);

	i = 0;
	
	while(temp_data/10)
	{
		data_temp[i++] = temp_data%10;
		temp_data = temp_data/10;
		if(temp_data < 10)
		{
			data_temp[i] = temp_data;
			data_temp[i+1] = '\0';
		}
	}

	if(i == 0)
	{
		uart_tx_byte(UART0,out_data+0x30);
	}
	else
	{
		while(i > 0)
		{
			uart_tx_byte(UART0,data_temp[i--]+0x30);
			if(i == 0)
			{
				uart_tx_byte(UART0,data_temp[0]+0x30);
				break;
			}
		}
	}
	
	for(i=0;i<10;i++)
		uart_tx_byte(UART0,sym);
	
	uart_tx_byte(UART0,'\r');
	uart_tx_byte(UART0,'\n');
	return;
}


#endif //__DQIOT_DRV_C__
