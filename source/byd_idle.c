/*!
    \file  byd_idle.c
    \brief idle app
*/

/*
    Copyright (C) 2020 BYD

    2020-07-20, V1.0.0, app for byd
*/

#include "byd_idle.h"
#include "byd_init.h"
#include "delay.h"
#include "bydmcu_libopt.h"

/*!
    \brief      enter idlemode example
				wake-up interrupt sources:
				exti0-4/wdt/timer2/iic/lcd
    \param[in]  none
    \param[out] none
    \retval     none
*/
void byd_idlemode(void)
{
		
/*-----------------------------------------------------------------------------------
		close other wake-up interrupt sources that you already use
-------------------------------------------------------------------------------------*/	
	
	WDT_DISABLE();//close wdt	 	   

//�ر���Ӧʹ��ģ���Լ����

    TIMER2_INT_ENABLE();//ʹ���ж�
	TIMER2_ENABLE();

	lowpower_idle();//enter idlemode
		
//	delay_us(1);	
	
	TIMER2_DISABLE();
	TIMER2_INT_DISABLE();//�ر��ж�
		
	WDT_ENABLE();//open wdt

//�ָ�ʹ��ģ������

}

