/*!
    \file  byd_led.c
    \brief led app
*/

/*
    Copyright (C) 2020 BYD

    2020-07-13, V1.0.0, app for byd
*/

#include "byd_led.h"

/*!
    \brief      led config
    \param[in]  none
    \param[out] none
    \retval     none
*/
void led_init(void)
{
    	
	LED_LCD_FUN_SET(1);
	LED_ARR_FUN_SET(1);
	LED_ARR_COM_SET(0);
	LED_ARR_SEG_SET(0x00);
	LED_ARR_COM_EN(0xff);//LED���о���COM��SEG��ѡ��,COM��PB0~PB3,SEG��PB4~PB7,��Ӧλ1Ϊʹ��,0Ϊ�ر�
	LED_ARR_MODE_SET(0);

#if LED_SCAN_INT_EN		
	LED_ARR_SCAN_SET(0);//LED���о���ɨ��ģʽѡ��0Ϊ�ж�ģʽ��1Ϊѭ��ģʽ
	LED_IP_SET; 	    //����LED�ж����ȼ�Ϊ�ߣ�����ʵ��Ӧ���������ȼ�
	LED_INT_FLAG_CLR;	//���LED�жϱ�־λ
	LED_IE_SET;			//��LED�ж�	
#else
	LED_ARR_SCAN_SET(1);
#endif

	LED_ARR_DUTY_SET(4);//LED���о���COMͨ��ռ�ձ�ѡ��(0~7) (x+1)/8
	
	LED_MATRIX_MODE_SET(1);
	LED_TRI_COM_INV_SET(1);//LED���о���COM�ڷ���ѡ��,1 ����ʱ����ߵ�ƽ; 0 ����ʱ����͵�ƽ	

}

/*!
    \brief      led work example
    \param[in]  none
    \param[out] none
    \retval     none
*/
void led_work(void)
{

	led_arr_data(0,0x0f);	
	led_arr_data(1,0x0f);	
	led_arr_data(2,0x0f);
	led_arr_data(3,0x0f);    	
	LED_START();//LEDɨ�迪ʼ

}