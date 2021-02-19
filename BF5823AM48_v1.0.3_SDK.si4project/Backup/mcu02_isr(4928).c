/*!
    \file  mcu02_isr.c
    \brief isr driver
*/

/*
    Copyright (C) 2020 BYD

    2020-05-18, V1.0.0, firmware for mcu02
*/
#include "byd_init.h"
#include "byd_idle.h"
#include "byd_ctk_api.h"
#include "byd_sm4.h"
#include "byd_led.h"
#include "delay.h"
#include "bydmcu_libopt.h"
#include "byd_tracemode.h"

/*!
    \brief      timer0 isr
    \param[in]  none
    \param[out] none
    \retval     none
*
unsigned int t0_cnt=0;


void timer0_isr(void) interrupt 1
{
	INT_TIMER0_CLR();

	if(GET_TIMER0_MODE() != TIMER_8BIT_AUTORELOAD)
	{
		TH0 = TH0_reload;
		TL0 = TL0_reload;
	}
	t0_cnt++;
	if(t0_cnt>=4000)
	{
		t0_cnt=0;
		PH4=~PH4;
		PB5=~PB5;//TEST
		PB6=~PB6;//TEST
		PB7=~PB7;//TEST
	}
}
*/
/*!
    \brief      timer1 isr
    \param[in]  none
    \param[out] none
    \retval     none
*

void timer1_isr(void) interrupt 3
{
	INT_TIMER1_CLR();

	if(GET_TIMER1_MODE() != TIMER_8BIT_AUTORELOAD){
		TH1 = TH1_reload;
		TL1 = TL1_reload;
	}
}

/*!
    \brief      timer2 isr
    \param[in]  none
    \param[out] none
    \retval     none
*/
#if 0
void timer2_wdt_isr(void) interrupt 14
{

	INT_WDT_TIMER2_CLR();	
/*	
	if(GET_INT_TIMER2_FLAG_STATE())
	{
	    //timer2
	}
	else if(GET_INT_WDT_FLAG_STATE())
	{
	   //wdt
	}	
*/

}
#endif
/*!
    \brief      timer3 and sm4 isr
    \param[in]  none
    \param[out] none
    \retval     none
*/

void timer3_sm4_isr(void) interrupt 19
{
	INT_TIMER3_SM4_CLR();

#if SM4_INT_EN
	if(GET_INT_SM4_FLAG_STATE())
	{
	   g_bSm4IntFlag = 1;
	}
#endif

/*
	if(GET_INT_TIMER3_FLAG_STATE())
	{
		TIMER3_ENABLE();
	}
*/	
}

/*!
    \brief      sci isr
    \param[in]  none
    \param[out] none
    \retval     none
*/
//void sci_isr(void)	interrupt 15
//{
//	INT_SCI_CLR();
//}

/*!
    \brief      spi1 isr
    \param[in]  none
    \param[out] none
    \retval     none
*/
void spi1_isr(void)	interrupt 20
{
	INT_SPI1_CLR();
}

/*!
    \brief      uart0 isr
    \param[in]  none
    \param[out] none
    \retval     none
*
void uart0_isr(void) interrupt 17
{
//	uint8_t temp;
	
	INT_UART0_CLR();
	
//	if(GET_UART0_RX_STATE())
//	{
//		temp = UART0_BUF;
//		CLR_UART0_RX_STATE();//清除接收中断标志位
//	}
//	if(GET_UART0_TX_STATE())
//	{
//		CLR_UART0_TX_STATE();//清除发送中断标志位
//      UART0_TX_INT_DISABLE();		
//	}
	
}

/*!
    \brief      uart1 isr
    \param[in]  none
    \param[out] none
    \retval     none
*/
void uart1_isr(void) interrupt 18
{
//	uint8_t temp;

	INT_UART1_CLR();

//	if(GET_UART1_RX_STATE())
//	{
//		temp = UART1_BUF;
//		CLR_UART1_RX_STATE();//清除接收中断标志位
//	}
//	if(GET_UART1_TX_STATE())
//	{
//		CLR_UART1_TX_STATE();//清除发送中断标志位
//      UART1_TX_INT_DISABLE();		
//	}	
}

/*!
    \brief      iic isr
    \param[in]  none
    \param[out] none
    \retval     none
*/

void iic_isr(void)	interrupt 10
{
	INT_IIC_CLR();

#if TRACEMODE_EN==0
//	iic_isr_func();
#else
	byd_tracemode_isr();
#endif

}

/*!
    \brief      exti_0_0~8 isr
    \param[in]  none
    \param[out] none
    \retval     none
*/
void exti_0_isr(void) interrupt 0
{
	INT_EXTI_0_CLR();
/*
	if(GET_INT0_8_FLAG_STATE())//int0_8 on PB0
	{
		INT0_8_FLAG_CLR();
	}

	if(GET_INT0_0_7_FLAG_STATE(0))//int0_0 on PH0
	{
		INT0_0_7_FLAG_CLR(0);
	}
	if(GET_INT0_0_7_FLAG_STATE(1))//int0_1 on PH1
	{
		INT0_0_7_FLAG_CLR(1);
	}
	if(GET_INT0_0_7_FLAG_STATE(2))//int0_2 on PH2
	{
		INT0_0_7_FLAG_CLR(2);
	}
	if(GET_INT0_0_7_FLAG_STATE(3))//int0_3 on PH3
	{
		INT0_0_7_FLAG_CLR(3);
	}
	if(GET_INT0_0_7_FLAG_STATE(4))//int0_4 on PH4
	{
		INT0_0_7_FLAG_CLR(4);
	}
	if(GET_INT0_0_7_FLAG_STATE(5))//int0_5 on PH5
	{
		INT0_0_7_FLAG_CLR(5);
	}
	if(GET_INT0_0_7_FLAG_STATE(6))//int0_6 on PH6
	{
		INT0_0_7_FLAG_CLR(6);
	}
	if(GET_INT0_0_7_FLAG_STATE(7))//int0_7 on PH7
	{
		INT0_0_7_FLAG_CLR(7);
	}
*/
}

/*!
    \brief      exti_1 isr
    \param[in]  none
    \param[out] none
    \retval     none
*/
void exti_1_isr(void) interrupt 2
{
	INT_EXTI_1_CLR();
}

/*!
    \brief      exti_2 isr
    \param[in]  none
    \param[out] none
    \retval     none
*/
void exti_2_isr(void) interrupt 9
{
	INT_EXTI_2_CLR(); 	
}

/*!
    \brief      exti_3 isr
    \param[in]  none
    \param[out] none
    \retval     none
*/
void exti_3_isr(void) interrupt 21
{
	INT_EXTI_3_CLR();
}

/*!
    \brief      exti_4 isr
    \param[in]  none
    \param[out] none
    \retval     none
*/
void exti_4_isr(void) interrupt 22
{
	INT_EXTI_4_CLR();
//获取对应IO口DATAX数据来判断INT4XX的中断引脚来源 	
//	if(GET_GPIOE_BIT(GPIO_PIN_4))
//	{		
//	}
//	if(GET_GPIOE_BIT(GPIO_PIN_5))
//	{
//	}
//	if(GET_GPIOE_BIT(GPIO_PIN_6))
//	{
//	}
//	if(GET_GPIOE_BIT(GPIO_PIN_7))
//	{
//	}

//	if(GET_GPIOF_BIT(GPIO_PIN_4))
//	{		
//	}
//	if(GET_GPIOF_BIT(GPIO_PIN_5))
//	{
//	}
//	if(GET_GPIOF_BIT(GPIO_PIN_6))
//	{
//	}
//	if(GET_GPIOF_BIT(GPIO_PIN_7))
//	{
//	}

//	if(GET_GPIOG_BIT(GPIO_PIN_0))
//	{		
//	}
//	if(GET_GPIOG_BIT(GPIO_PIN_1))
//	{
//	}
//	if(GET_GPIOG_BIT(GPIO_PIN_2))
//	{
//	}
//	if(GET_GPIOG_BIT(GPIO_PIN_3))
//	{
//	}
}

/*!
    \brief      lvdt isr
    \param[in]  none
    \param[out] none
    \retval     none
*/
void lvdt_isr(void) interrupt 16
{
	INT_LVDT_CLR();
/*	
	if(GET_INT_LVDT_FLAG_STATE(INT_VOL_UP_FLAG))
	{
	    
	}
	if(GET_INT_LVDT_FLAG_STATE(INT_VOL_DOWN_FLAG))
	{
	    
	}
*/
}

/*!
    \brief      led_lcd_rfid isr
    \param[in]  none
    \param[out] none
    \retval     none
*/
void led_lcd_rfid_isr(void) interrupt 13
{
#if LED_SCAN_INT_EN
	if(GET_INT_LED_FLAG_STATE())
	{	
		INT_LED_LCD_RFID_CLR();	
		LED_START();
    }
#endif
	

#if 0//RFID_EN

	uint8_t tmpData;

    if(GET_INT_RFID_FLAG_STATE())	
	{
		INT_LED_LCD_RFID_CLR(); //清除中断标志

		if(RFID_CFG & RFID_TX_COMPLET_FLAG)//字节发送完毕
		{
			RFID_TX_COMPLTE_CLR();
		}		
		if((RFID_CFG & RFID_RX_FULL_FLAG))//字节接收已完成
		{
			RFID_RX_FULL_CLR();
	        tmpData = RFID_BUF2;
		}	
	}
#endif
}
