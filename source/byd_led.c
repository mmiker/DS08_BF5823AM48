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
	LED_ARR_COM_EN(0xff);//LED行列矩阵COM及SEG口选择,COM口PB0~PB3,SEG口PB4~PB7,对应位1为使能,0为关闭
	LED_ARR_MODE_SET(0);

#if LED_SCAN_INT_EN		
	LED_ARR_SCAN_SET(0);//LED行列矩阵扫描模式选择，0为中断模式，1为循环模式
	LED_IP_SET; 	    //设置LED中断优先级为高，根据实际应用设置优先级
	LED_INT_FLAG_CLR;	//清除LED中断标志位
	LED_IE_SET;			//开LED中断	
#else
	LED_ARR_SCAN_SET(1);
#endif

	LED_ARR_DUTY_SET(4);//LED行列矩阵COM通道占空比选择(0~7) (x+1)/8
	
	LED_MATRIX_MODE_SET(1);
	LED_TRI_COM_INV_SET(1);//LED行列矩阵COM口反向选择,1 亮灯时输出高电平; 0 亮灯时输出低电平	

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
	LED_START();//LED扫描开始

}