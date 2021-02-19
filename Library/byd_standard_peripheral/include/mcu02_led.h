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

#define LED_LCD_FUN_SET(x)         {DP_CON &= ~(0x40);DP_CON |= (0x40&(x<<6));}//1ΪLED_LCD���ܿ���0ΪLED_LCD���ܹ�
#define LED_SER_FUN_SET(x)         {DP_CON &= ~(0x04);DP_CON |= (0x04&(x<<2));}//1ΪLED���ܣ�0ΪLCD����
#define LED_SER_COM_SET(x)   	   {DP_CON &= ~(0x01);DP_CON |= (0x01&(x<<0));}//COM�����ѡ��0Ϊ��������1Ϊ����(������LED/LCDӲ��ɨ��ʱ����Ч)
#define LED_SER_MODE_SET(x)        {DP_MODE &= ~(0x80);DP_MODE |= (0x80&(x<<7));}//1Ϊ���е���ģʽ��0Ϊ���о���ģʽ��
#define LED_SER_MATRIX_SET(x)      {DP_CON &= ~(0x38);DP_CON |= (0x38&(x<<3));}//LED���е������ѡ��(X*Y) 0-4*5��1-5*6��2-6*7��3-7*8,4-4*5(��PB3Ϊ��ʼ�˿�)
#define LED_SER_CURRENT_SET(x)	   {REG_ADDR = LED_DRIVE;REG_DATA &= ~(0x0F);REG_DATA |= (0x0F&(x<<0));}	//LED������������(0~15)�����չ������(0-3.7mA),(9-43.7mA),(15-68.7mA)@LEDѹ��2.5V
#define LED_SER_LED1_WIDTH_SET(x)  (SCAN_WIDTH = x)   							//�����Ƶ�ͨʱ��1���ã�(x+1)*16us
#define LED_SER_LED2_WIDTH_SET(x)  (LED2_WIDTH = x)								//�����Ƶ�ͨʱ��2���ã�(x+1)*16us
#define LED_SER_SCAN_SET(x)        {DP_CON &= ~(0x02);DP_CON |= (0x02&(x<<1));}//LEDɨ��ģʽѡ��0Ϊ�ж�ģʽ��1Ϊѭ��ģʽ 
#define LED_START()  		       SCAN_START = 1 //LED��ʼɨ��
#define LED_STOP()  		       SCAN_START = 0 //LEDֹͣɨ��

#define LED_MATRIX_MODE_SET(x)     {DP_CON1 &= ~(0x20);DP_CON1 |= (0x20 & (x<<5));}//LED���о�������ģʽѡ��,0 N������; 1 ����������
#define LED_TRI_COM_INV_SET(x)     {DP_CON1 &= ~(0x40);DP_CON1 |= (0x40 & (x<<6));}//LED���о�������������ģʽCOM�ڷ���ѡ��,0 ����ʱ����ߵ�ƽ; 1 ����ʱ����͵�ƽ


#define LED_ARR_FUN_SET(x)    	   {DP_CON &= ~(0x04);DP_CON |= (0x04&(x<<2));}//1ΪLED���ܣ�0ΪLCD����
#define LED_ARR_SEG_SET(x)    	   {REG_ADDR = SEG_IO_SEL;REG_DATA &= ~(0xFF);REG_DATA |= (0xFF&x);}//LED���о���SEG��ѡ��,��Ӧ��λΪ1ѡ��ΪSEG�ڹ���(PH0~7)
#define LED_ARR_COM_EN(x)     	   {REG_ADDR = COM_IO_SEL;REG_DATA &= ~(0xFF);REG_DATA |= (0xFF&x);}//LED���о���COM��ѡ��,��Ӧ��λΪ1ѡ��ΪCOM�ڹ���(PB0~7)
#define LED_ARR_COM_SET(x)    	   {DP_CON &= ~(0x01);DP_CON |= (0x01&(x));}//COM�����ѡ��0Ϊ��������1Ϊ����(������LED/LCDӲ��ɨ��ʱ����Ч)
#define LED_ARR_MODE_SET(x)   	   {DP_MODE &= ~(0x80);DP_MODE |= (0x80&(x<<7));}//1Ϊ���е���ģʽ��0Ϊ���о���ģʽ��
#define LED_ARR_DUTY_SET(x)   	   {DP_CON &= ~(0x38);DP_CON |= (0x38&(x<<3));}//LED���о���COMͨ��ռ�ձ�ѡ��(0~7) (x+1)/8
#define LED_ARR_SCAN_SET(x)   	   {DP_CON &= ~(0x02);DP_CON |= (0x02&(x<<1));}//LED���о���ɨ��ģʽѡ��0Ϊ�ж�ģʽ��1Ϊѭ��ģʽ 


#define LED_IE_SET 			  	   IEN1 |= 0x40			//��LED�ж�ʹ��
#define LED_IE_CLR 			  	   IEN1 &= ~0x40	    //��LED�ж�ʹ��
#define LED_IP_SET 			  	   IPL1 |= 0x40			//����LED�ж����ȼ�Ϊ��
#define LED_IP_CLR 			  	   IPL1 &= ~0x40	    //����LED�ж����ȼ�Ϊ��
#define LED_INT_FLAG_CLR 	  	   IRCON1 &= ~0x40;INT_PE_STAT = ~0x01 // ���LED�жϱ�־λ





void led_arr_data(uint8_t com,uint8_t seg);


#endif