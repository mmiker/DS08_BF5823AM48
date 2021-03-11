/*!
    \file  dqiot_drv.c
    \brief drv
*/

/*
    Copyright (C) 2018 BYD
*/
#ifndef __DQIOT_DRV_C__

#define __DQIOT_DRV_C__
#include "mmi_feature.h"

#include "string.h"
// #include <stdio.h>
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

extern void Audio_timer_event_handler(void);
extern void System_timer_event_handler(void);
/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_init(void)
{
	dqiot_drv_ext_ldo_init();

	dqiot_drv_reset_gpio_init();
	
	dqiot_drv_key_led_gpio_init();
	dqiot_drv_rgb_led_gpio_init();

	dqiot_drv_audio_gpio_init();
	dqiot_drv_fp_gpio_init();
	dqiot_drv_uart0B_init();
	dqiot_drv_motor_gpio_init();
	
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
	//gpio_bit_reset(GPIOE,GPIO_PIN_7);


	dqiot_drv_ext_ldo_on();

	dqiot_drv_key_led_on();

	
	dqiot_drv_timer2_init();
	
	dqiot_drv_timer2_start();
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
	
	//WDT_ENABLE();
	
	BOR_ENABLE();

	CSD_ENABLE();

	//RFID_ENABLE();


	//dqiot_drv_reset_gpio_init();
	
	dqiot_drv_key_led_gpio_init();
	dqiot_drv_rgb_led_gpio_init();
#ifdef __LOCK_AUDIO_SUPPORT__
	dqiot_drv_audio_gpio_init();
#endif
#ifdef __LOCK_FP_SUPPORT__
	dqiot_drv_fp_gpio_init();

	dqiot_drv_uart0B_init();
#endif
#ifdef __LOCK_MOTOR_SUPPORT__
	dqiot_drv_motor_gpio_init();
#endif

	dqiot_drv_ext_ldo_on();

	dqiot_drv_key_led_on();

	//byd_setbaseline(0);//�������߸�λ
	//delay_ms(200);
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

#ifdef __LOCK_AUDIO_SUPPORT__
	dqiot_drv_audio_gpio_deinit();
#endif
#ifdef __LOCK_FP_SUPPORT__
	dqiot_drv_fp_gpio_deinit();
#endif
#ifdef __LOCK_MOTOR_SUPPORT__
	dqiot_drv_motor_gpio_deinit();
#endif
	dqiot_drv_key_led_gpio_deinit();
	dqiot_drv_rgb_led_gpio_deinit();

//	rfid_enter_lowpower_config();
	
	CSD_DISABLE();

	//RFID_DISABLE();

	BOR_DISABLE();
	
	WDT_DISABLE();
	return;
}



/*!
    \brief      timer0 isr
    \param[in]  none
    \param[out] none
    \retval     none
*/
void dqiot_drv_timer0_isr(void) interrupt 1
{
	INT_TIMER0_CLR();

	Audio_timer_event_handler();

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

	if (GET_TIMER1_MODE() != TIMER_8BIT_AUTORELOAD)
	{
		TH1 = TH1_reload;
		TL1 = TL1_reload;
	}
	timer1_count_flag++;
}


/*!
    \brief      timer2 isr
    \param[in]  none
    \param[out] none
    \retval     none
*/
void timer2_wdt_isr(void) interrupt 14
{

	INT_WDT_TIMER2_CLR();	
	if(GET_INT_TIMER2_FLAG_STATE())
	{
	    //timer2
	    System_timer_event_handler();
	}
	else if(GET_INT_WDT_FLAG_STATE())
	{
	   //wdt
	}	

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
	TIMER0_MODE_SET(TIMER_8BIT_AUTORELOAD);//TIMER_13BIT,TIMER_8BIT_AUTORELOAD,TIMER_8BIT	
	TIMER0_CT_MODE_SET(TIME_SELECT);//COUNT_SELECT
	TIMER0_COUNT_8BIT(count);//TIMER_16BIT
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
	/*
	   t = prescale*(1000000/32768)*(count+1) us 
	   prescale = 1,65536	
	*/	  
	uint16_t count;
	count = 3276;
	TIMER2_CLOCK_SELECT(TIMER2_CLOCK_XTAL);//TIMER2_CLOCK_XTALѡ���ⲿ����Ҫʹ��XTAL_32K_ENABLE()
	TIMER2_AUTO_RELOAD(ENABLE);//ENABLE
	TIMER2_PRESCALE(TIMER2_PRESCALE_1);//TIMER2_PRESCALE_65536
	TIMER2_COUNT_SET(count);
	
	INT_WDT_TIMER2_CLR();//����жϱ�־	
	TIMER2_IPL_SET(LOW); //�ж����ȼ�Ϊ��
	TIMER2_INT_DISABLE();//�ر��ж�
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


/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_uart0A_init(void)
{
	GPIOE_BIT_SET(GPIO_PIN_4|GPIO_PIN_5);//������ë��
	 	
	UART0_PORT_SET(UART0_PE4_PE5);
	UART0_CON2 = 0;
	UART0_STATE = 0;
    uart_baudrate_config(UART0,UART_BAUDRATE_57600);//������
	UART0_STOP_MODE(STOP_WIDTH_1BIT);//ֹͣλ
	UART0_DATA_MODE(DATA_MODE_8BIT);//����λ
	UART0_PARITY_SET(DISABLE); //��żУ��ʹ��
	UART0_PARITY_SEL(ODD_PARITY);//��żУ��ѡ��
    UART0_MULTI_MODE(DISABLE);//�ദ����ͨ��ģʽ
	
	UART0_RX_ENABLE();//����ʹ�� 
#ifdef __DRV_UART0A_INT_SUPPORT__   
	UART0_TX_INT_ENABLE();//�����ж�ʹ��
	UART0_RX_INT_ENABLE();//�����ж�ʹ��
	INT_UART0_CLR();//����ж�Դ��־
	UART0_IPL_SET(LOW);//�ж����ȼ�����
	UART0_INT_ENABLE();//�ж�Դ	
#else
	UART0_TX_INT_DISABLE();//�����жϹر�
	UART0_RX_INT_DISABLE();//�����жϹر�
#endif

	// memset(uart_get_buf, 0x00, sizeof(uart_get_buf));
	// uart_getbuflen = 0;

	UART0_ENABLE();//ʹ��uart0
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
	GPIOF_BIT_SET(GPIO_PIN_4|GPIO_PIN_5);//������ë��
	 	
	UART0_PORT_SET(UART0_PF4_PF5);
	UART0_CON2 = 0;
	UART0_STATE = 0;
    uart_baudrate_config(UART0,UART_BAUDRATE_57600);//������
	UART0_STOP_MODE(STOP_WIDTH_1BIT);//ֹͣλ
	UART0_DATA_MODE(DATA_MODE_8BIT);//����λ
	UART0_PARITY_SET(DISABLE); //��żУ��ʹ��
	UART0_PARITY_SEL(ODD_PARITY);//��żУ��ѡ��
    UART0_MULTI_MODE(DISABLE);//�ദ����ͨ��ģʽ
	
	UART0_RX_ENABLE();//����ʹ�� 
#ifdef __DRV_UART0B_INT_SUPPORT__   
   	//UART0_TX_INT_ENABLE();//�����ж�ʹ��
   	UART0_TX_INT_ENABLE();//�����жϹر�
	UART0_RX_INT_ENABLE();//�����ж�ʹ��
	INT_UART0_CLR();//����ж�Դ��־
	UART0_IPL_SET(HIGH);//�ж����ȼ�����
	UART0_INT_ENABLE();//�ж�Դ	
#else
	UART0_TX_INT_DISABLE();//�����жϹر�
	UART0_RX_INT_DISABLE();//�����жϹر�
#endif

	// memset(uart_get_buf, 0x00, sizeof(uart_get_buf));
	// uart_getbuflen = 0;

	UART0_ENABLE();//ʹ��uart0
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

		if(GET_UART0_RX_STATE())
		{
			if(uart_getbuflen >= UART0_GET_DATA_LEN )
				return;
			else
				uart_get_buf[uart_getbuflen++] = UART0_BUF;
			CLR_UART0_RX_STATE();//��������жϱ�־λ
		}
		//if(GET_UART0_TX_STATE())
		//{
		//	CLR_UART0_TX_STATE();//��������жϱ�־λ
		//	UART0_TX_INT_DISABLE(); 	
		//}

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


/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_uart0_sendData(unsigned char *p_data, unsigned char length)
{
	#if 1
	unsigned char i = 0;
	//dqiot_drv_uart0B_init();
	//memset(uart_send_buf,0x00,sizeof(uart_send_buf));
	//memcpy(uart_send_buf,p_data,length);
	//uart_sendbuflen = length;

	for(i=0;i<length;i++)
	{
		uart_tx_byte(UART0,p_data[i]);
	}
	#endif
}

char putchar(char c)
{
     uart_tx_byte(UART0,c);
     return c;
}


#endif //__DQIOT_DRV_C__
