/*!
    \file  mcu02_led.h
    \brief
*/

/*
    Copyright (C) 2020 BYD

    2020-07-13, V1.0.0, firmware for mcu02
*/

#ifndef MCU02_LED_H
#define	MCU02_LED_H

#include "mcu02_sfr.h"
#include "mcu02_system.h"

#define XBYTE ((unsigned char volatile xdata *) 0)

#define LED_LCD_FUN_SET(x)         {DP_CON &= ~(0x40);DP_CON |= (0x40&(x<<6));}//1为LED_LCD功能开，0为LED_LCD功能关
#define LED_SER_FUN_SET(x)         {DP_CON &= ~(0x04);DP_CON |= (0x04&(x<<2));}//1为LED功能，0为LCD功能
#define LED_SER_COM_SET(x)   	   {DP_CON &= ~(0x01);DP_CON |= (0x01&(x<<0));}//COM大电流选择，0为不开启，1为开启(开启后LED/LCD硬件扫描时序无效)
#define LED_SER_MODE_SET(x)        {DP_MODE &= ~(0x80);DP_MODE |= (0x80&(x<<7));}//1为串行点阵模式，0为行列矩阵模式；
#define LED_SER_MATRIX_SET(x)      {DP_CON &= ~(0x38);DP_CON |= (0x38&(x<<3));}//LED串行点阵矩阵选择(X*Y) 0-4*5，1-5*6，2-6*7，3-7*8,4-4*5(以PB3为起始端口)
#define LED_SER_CURRENT_SET(x)	   {REG_ADDR = LED_DRIVE;REG_DATA &= ~(0x0F);REG_DATA |= (0x0F&(x<<0));}	//LED驱动能力配置(0~15)，参照规格书表格(0-3.7mA),(9-43.7mA),(15-68.7mA)@LED压降2.5V
#define LED_SER_LED1_WIDTH_SET(x)  (SCAN_WIDTH = x)   							//单个灯导通时间1配置，(x+1)*16us
#define LED_SER_LED2_WIDTH_SET(x)  (LED2_WIDTH = x)								//单个灯导通时间2配置，(x+1)*16us
#define LED_SER_SCAN_SET(x)        {DP_CON &= ~(0x02);DP_CON |= (0x02&(x<<1));}//LED扫描模式选择，0为中断模式，1为循环模式 
#define LED_START()  		       SCAN_START = 1 //LED开始扫描
#define LED_STOP()  		       SCAN_START = 0 //LED停止扫描

#define LED_MATRIX_MODE_SET(x)     {DP_CON1 &= ~(0x20);DP_CON1 |= (0x20 & (x<<5));}//LED行列矩阵驱动模式选择,0 N管驱动; 1 三极管驱动
#define LED_TRI_COM_INV_SET(x)     {DP_CON1 &= ~(0x40);DP_CON1 |= (0x40 & (x<<6));}//LED行列矩阵三级管驱动模式COM口反向选择,0 亮灯时输出高电平; 1 亮灯时输出低电平


#define LED_ARR_FUN_SET(x)    	   {DP_CON &= ~(0x04);DP_CON |= (0x04&(x<<2));}//1为LED功能，0为LCD功能
#define LED_ARR_SEG_SET(x)    	   {REG_ADDR = SEG_IO_SEL;REG_DATA &= ~(0xFF);REG_DATA |= (0xFF&x);}//LED行列矩阵SEG口选择,对应的位为1选择为SEG口功能(PH0~7)
#define LED_ARR_COM_EN(x)     	   {REG_ADDR = COM_IO_SEL;REG_DATA &= ~(0xFF);REG_DATA |= (0xFF&x);}//LED行列矩阵COM口选择,对应的位为1选择为COM口功能(PB0~7)
#define LED_ARR_COM_SET(x)    	   {DP_CON &= ~(0x01);DP_CON |= (0x01&(x));}//COM大电流选择，0为不开启，1为开启(开启后LED/LCD硬件扫描时序无效)
#define LED_ARR_MODE_SET(x)   	   {DP_MODE &= ~(0x80);DP_MODE |= (0x80&(x<<7));}//1为串行点阵模式，0为行列矩阵模式；
#define LED_ARR_DUTY_SET(x)   	   {DP_CON &= ~(0x38);DP_CON |= (0x38&(x<<3));}//LED行列矩阵COM通道占空比选择(0~7) (x+1)/8
#define LED_ARR_SCAN_SET(x)   	   {DP_CON &= ~(0x02);DP_CON |= (0x02&(x<<1));}//LED行列矩阵扫描模式选择，0为中断模式，1为循环模式 


#define LED_IE_SET 			  	   IEN1 |= 0x40			//开LED中断使能
#define LED_IE_CLR 			  	   IEN1 &= ~0x40	    //关LED中断使能
#define LED_IP_SET 			  	   IPL1 |= 0x40			//设置LED中断优先级为高
#define LED_IP_CLR 			  	   IPL1 &= ~0x40	    //设置LED中断优先级为低
#define LED_INT_FLAG_CLR 	  	   IRCON1 &= ~0x40;INT_PE_STAT = ~0x01 // 清除LED中断标志位





void led_arr_data(uint8_t com,uint8_t seg);


#endif