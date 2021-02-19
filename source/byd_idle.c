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

//关闭相应使用模块节约功耗

    TIMER2_INT_ENABLE();//使能中断
	TIMER2_ENABLE();

	lowpower_idle();//enter idlemode
		
//	delay_us(1);	
	
	TIMER2_DISABLE();
	TIMER2_INT_DISABLE();//关闭中断
		
	WDT_ENABLE();//open wdt

//恢复使用模块配置

}

