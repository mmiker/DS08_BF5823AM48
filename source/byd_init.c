/*!
    \file  byd_init.c
    \brief init app
*/

/*
    Copyright (C) 2020 BYD

    2020-07-28, V1.0.0, app for byd
*/

#include "byd_init.h"
#include "byd_ctk.h"
#include "byd_iic.h"
#include "byd_adc.h"
#include "bydmcu_libopt.h"
#include "byd_tracemode.h"

#include "dqiot_drv.h"

/*!
    \brief      wdt config
    \param[in]  none
    \param[out] none
    \retval     none
*/
void byd_wdt_init(void)
{
   wdt_init(WDT_TIME_2304MS);

//   INT_WDT_TIMER2_CLR();
//   WDT_IPL_SET(LOW);
//   WDT_INT_DISABLE();
   
}
/*!
    \brief      gpio config
    \param[in]  none
    \param[out] none
    \retval     none
*/
void byd_gpio_init(void)
{
//请根据实际应用初始化gpio,默认输入

//未封装的IO口配置输出为低
//GPIOF
//	gpio_init(GPIOF,GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,GPIO_MODE_OUT);
//	GPIOF_BIT_RESET(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
	
//GPIOA
//    gpio_init(GPIOA,0x0f,GPIO_MODE_OUT);//GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
//	GPIOA_BIT_RESET(0x0f);

//GPIOB
//    gpio_init(GPIOB,GPIO_PIN_ALL,GPIO_MODE_OUT);
//	GPIOB_BIT_RESET(GPIO_PIN_ALL);

//GPIOC
//    gpio_init(GPIOC,GPIO_PIN_ALL,GPIO_MODE_OUT);
//	GPIOC_BIT_RESET(GPIO_PIN_ALL);

//GPIOE
//    gpio_init(GPIOE,GPIO_PIN_ALL,GPIO_MODE_OUT);
//	GPIOE_BIT_RESET(GPIO_PIN_ALL);

//GPIOF
//  gpio_init(GPIOF,GPIO_PIN_ALL,GPIO_MODE_OUT);
//	GPIOF_BIT_RESET(GPIO_PIN_ALL);

//GPIOG
//    gpio_init(GPIOG,0x0f,GPIO_MODE_OUT);//GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
//	GPIOG_BIT_RESET(0x0f);

//GPIOH
//    gpio_init(GPIOH,GPIO_PIN_4,GPIO_MODE_OUT);
//	GPIOH_BIT_RESET(GPIO_PIN_4);
	
}

/*!
    \brief      timer config example
    \param[in]  none
    \param[out] none
    \retval     none
*/
void byd_timer_init(void)
{
#if 0  // timer0示例配置1ms
/*
   t = (count*12000000/fosc) us 
   n = 8,13,16计数位数,cout必须小于2的n次方,取决配置TIMER0_MODE_SET
   fosc = 1,4,8,12M	
*/       	
	count = 1000;
	TIMER0_MODE_SET(TIMER_16BIT);//TIMER_13BIT,TIMER_8BIT_AUTORELOAD,TIMER_8BIT	
	TIMER0_CT_MODE_SET(TIME_SELECT);//COUNT_SELECT
	TIMER0_COUNT_16BIT(count);//TIMER_16BIT
//	TIMER0_COUNT_13BIT(count);//TIMER_13BIT
//	TIMER0_COUNT_8BIT(count);//TIMER_8BIT_AUTORELOAD,TIMER_8BIT
	timer0_1_init(TIMER0);

	INT_TIMER0_CLR();
	TIMER0_IPL_SET(LOW);
	TIMER0_INT_ENABLE();
	TIMER0_ENABLE();
#endif

#if 0  // timer1示例配置5ms
/*
   t = (count*12000000/fosc) us 
   n = 8,13,16计数位数,cout必须小于2的n次方,取决配置TIMER0_MODE_SET
   fosc = 1,4,8,12M		 
*/ 

    count = 5000;
	TIMER1_MODE_SET(TIMER_16BIT);//TIMER_13BIT,TIMER_8BIT_AUTORELOAD
	TIMER1_CT_MODE_SET(TIME_SELECT);//COUNT_SELECT
	TIMER1_COUNT_16BIT(count);//TIMER_16BIT
//	TIMER1_COUNT_13BIT(count);//TIMER_13BIT
//	TIMER1_COUNT_8BIT(count);//TIMER_8BIT_AUTORELOAD
	timer0_1_init(TIMER1);

	INT_TIMER1_CLR();//清除中断标志	
	TIMER1_IPL_SET(LOW);//中断优先级为低
	TIMER1_INT_ENABLE();//使能中断	
	TIMER1_ENABLE();
#endif

#if 0 //timer2示例配置,用于休眠唤醒
/*
   t = prescale*(1000000/32768)*(count+1) us 
   prescale = 1,65536   
*/    

	count = 391;
	TIMER2_CLOCK_SELECT(TIMER2_CLOCK_RC);//TIMER2_CLOCK_XTAL选择外部晶振要使能XTAL_32K_ENABLE()
	TIMER2_AUTO_RELOAD(DISABLE);//ENABLE
	TIMER2_PRESCALE(TIMER2_PRESCALE_1);//TIMER2_PRESCALE_65536
	TIMER2_COUNT_SET(count);

	INT_WDT_TIMER2_CLR();//清除中断标志	
	TIMER2_IPL_SET(LOW); //中断优先级为低
	TIMER2_INT_DISABLE();//关闭中断

#endif

#if 0  // //timer3示例配置1ms
/*
   t = (clock_divide/24)*(count+1) us 
   clock_divide = 12,4   
*/
	
	count = 1999;
	TIMER3_CLOCK_DIVIDE(TIMER3_CLOCK_DIVIDE_12);
	TIMER3_AUTO_RELOAD(DISABLE);//ENABLE
	TIMER3_COUNT_SET(count);

	INT_TIMER3_SM4_CLR();//清除中断标志	
	TIMER3_IPL_SET(LOW);//中断优先级为低
	TIMER3_INT_ENABLE();//使能中断
	TIMER3_ENABLE();
#endif
}

/*!
    \brief      exti config example
    \param[in]  none
    \param[out] none
    \retval     none
*/
void byd_exint_init(void)
{
	EA = 0;
/*外部中断0示例*/
#if 0
    INT0_0_7_TRIGGER_SET(EXTI_TRIG_FALLING);//上升沿或者下降沿或者双沿触发	
	INT0_0_PH0_CONFIG(ENABLE);//使能IO口的中断功能
	INT0_0_7_FLAG_CLR(INT0_0_PH0_FLAG);//清除中断标志

	INT0_1_PH1_CONFIG(ENABLE);//使能IO口的中断功能
	INT0_0_7_FLAG_CLR(INT0_0_PH1_FLAG);//清除中断标志

	INT0_8_TRIGGER_SET(EXTI_TRIG_FALLING);//上升沿或者下降沿或者双沿触发	
	INT0_8_PB0_CONFIG(ENABLE);//使能IO口的中断功能
    INT0_8_FLAG_CLR();//清除中断标志

	INT_EXTI_0_CLR();//清除中断源标志
	INT0_IPL_SET(LOW);//中断优先级为低
	INT0_ENABLE();//使能中断源
#endif


/*外部中断1示例*/
#if 0
    INT1_TRIGGER_SET(EXTI_TRIG_FALLING);//上升沿或者下降沿或者双沿触发	
	INT1_PB1_CONFIG(ENABLE);//使能IO口的中断功能
	INT_EXTI_1_CLR();//清除中断源标志
	INT1_IPL_SET(LOW);//中断优先级为低
	INT1_ENABLE();//使能中断源
#endif

/*外部中断2示例*/
#if 0
    INT2_TRIGGER_SET(EXTI_TRIG_FALLING);//上升沿或者下降沿或者双沿触发	
	INT2_PB2_CONFIG(ENABLE);//使能IO口的中断功能
	INT_EXTI_2_CLR();//清除中断源标志
	INT2_IPL_SET(LOW);//中断优先级为低
	INT2_ENABLE();//使能中断源
#endif

/*外部中断3示例*/
#if 0
    INT3_TRIGGER_SET(EXTI_TRIG_FALLING);//上升沿或者下降沿或者双沿触发	
	INT3_PB3_CONFIG(ENABLE);//使能IO口的中断功能
	INT_EXTI_3_CLR();//清除中断源标志
	INT3_IPL_SET(LOW);//中断优先级为低
	INT3_ENABLE();//使能中断源
#endif

/*外部中断4示例*/
#if 0
	INT4_TRIGGER_SET(EXTI4_TRIG_FALLING);//上升沿或者下降沿触发,请注意调用宏定义必须为EXTI4_TRIG_FALLING/EXTI4_TRIG_RISING		
	INT4_07_PE4_CONFIG(ENABLE);//使能IO口的中断功能
	INT4_15_PF4_CONFIG(ENABLE);//使能IO口的中断功能
	INT4_19_PG0_CONFIG(ENABLE);//使能IO口的中断功能
	INT_EXTI_4_CLR();//清除中断源标志
	INT4_IPL_SET(LOW);//中断优先级为低
	INT4_ENABLE();//使能中断源
#endif
	EA = 1;
}

/*!
    \brief      uart0 and uart1 config example
    \param[in]  none
    \param[out] none
    \retval     none
*/
void uart_config(void)
{
/*uart0 config PC4/PC5*/
#if 0
	
	GPIOC_BIT_SET(GPIO_PIN_4|GPIO_PIN_5);//避免有毛刺
	 	
	UART0_PORT_SET(UART0_PC4_PC5);
	UART0_CON2 = 0;
	UART0_STATE = 0;
    uart_baudrate_config(UART0,UART_BAUDRATE_9600);//波特率
	UART0_STOP_MODE(STOP_WIDTH_1BIT);//停止位
	UART0_DATA_MODE(DATA_MODE_8BIT);//数据位
	UART0_PARITY_SET(DISABLE); //奇偶校验使能
	UART0_PARITY_SEL(ODD_PARITY);//奇偶校验选择
    UART0_MULTI_MODE(DISABLE);//多处理器通信模式
	
	UART0_RX_ENABLE();//接收使能 
	   
#if 0    
	UART0_TX_INT_DISABLE();//发送中断关闭
	UART0_RX_INT_DISABLE();//接收中断关闭
#else
   	UART0_TX_INT_ENABLE();//发送中断使能
	UART0_RX_INT_ENABLE();//接收中断使能
	INT_UART0_CLR();//清除中断源标志
	UART0_IPL_SET(LOW);//中断优先级设置
	UART0_INT_ENABLE();//中断源	
#endif
	
	UART0_ENABLE();//使能uart0
	

#endif

/*uart0 config PE4/PE5*/
#if 0
	
	GPIOC_BIT_SET(GPIO_PIN_4|GPIO_PIN_5);//避免有毛刺
	 	
	UART0_PORT_SET(UART0_PE4_PE5);
	UART0_CON2 = 0;
	UART0_STATE = 0;
    uart_baudrate_config(UART0,UART_BAUDRATE_9600);//波特率
	UART0_STOP_MODE(STOP_WIDTH_1BIT);//停止位
	UART0_DATA_MODE(DATA_MODE_8BIT);//数据位
	UART0_PARITY_SET(DISABLE); //奇偶校验使能
	UART0_PARITY_SEL(ODD_PARITY);//奇偶校验选择
    UART0_MULTI_MODE(DISABLE);//多处理器通信模式
	
	UART0_RX_ENABLE();//接收使能 
	   
#if 0    
	UART0_TX_INT_DISABLE();//发送中断关闭
	UART0_RX_INT_DISABLE();//接收中断关闭
#else
   	UART0_TX_INT_ENABLE();//发送中断使能
	UART0_RX_INT_ENABLE();//接收中断使能
	INT_UART0_CLR();//清除中断源标志
	UART0_IPL_SET(LOW);//中断优先级设置
	UART0_INT_ENABLE();//中断源	
#endif
	
	UART0_ENABLE();//使能uart0
	

#endif

/*uart1 config*/
#if 0
	
	GPIOC_BIT_SET(GPIO_PIN_6|GPIO_PIN_7);//避免有毛刺
	    
	UART1_PORT_SET(UART1_PC6_PC7);
	UART1_CON2 = 0;
	UART1_STATE = 0;
	uart_baudrate_config(UART1,UART_BAUDRATE_9600);//波特率
	UART1_STOP_MODE(STOP_WIDTH_1BIT);//停止位
	UART1_DATA_MODE(DATA_MODE_8BIT);//数据位
	UART1_PARITY_SET(DISABLE); //奇偶校验使能
	UART1_PARITY_SEL(ODD_PARITY);//奇偶校验选择
    UART1_MULTI_MODE(DISABLE);//多处理器通信模式
	
	UART1_RX_ENABLE();//接收使能
    
#if 0
	UART1_TX_INT_DISABLE();//发送中断关闭
	UART1_RX_INT_DISABLE();//接收中断关闭
#else
    UART1_TX_INT_ENABLE();//发送中断使能
	UART1_RX_INT_ENABLE();//接收中断使能   	
	INT_UART1_CLR();//清除中断源标志
	UART1_IPL_SET(LOW);//中断优先级设置
	UART1_INT_ENABLE();//中断源
#endif
	
	UART1_ENABLE();//使能uart1
	
#endif
}

/*!
    \brief      pwm config example
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pwm_config(void)
{
/*	
	pwm_duty = (pwm_cnt_h+pwm_cnt_l)/sys_clk
	pwm_width = pwm_cnt_h/(pwm_cnt_h+pwm_cnt_l)
*/
//必须先使能才能配置PWM DUTYWIDTH	
	PWM_CH_ENABLE(PWM0_CH_PB6);
	PWM_CH_ENABLE(PWM1_CH_PB7);
	PWM_CH_ENABLE(PWM2_CH_PH7);
	pwm0_duty_width_config(10000,10000);
	pwm1_duty_width_config(20000,20000);
	pwm2_duty_width_config(30000,30000);

/*!!!!!!!!!恢复IO口功能要关闭pwm!!!!!!!!!!!*/
//	PWM_CH_DISABLE(PWM0_CH_PB6);
//	PWM_CH_DISABLE(PWM1_CH_PB7);
//  SET_PB6_IO_OUT;SET_PB6_L;
//  SET_PB7_IO_OUT;SET_PB7_L;
}

/*!
    \brief      spi config example
    \param[in]  none
    \param[out] none
    \retval     none
*/
void spi_config(void)
{
    SPI_DEVICE_MODE(SPI_MASTER);//SPI_SLAVE
	SPI_PRESCALE_SET(SYS_CLK_DIVIDE_6);//12M/6=2M
	SPI_DUPLEX_SET(FULL_DUPLEX);//HALF_DUPLEX
	SPI_ENDIAN_SET(MSB_FIRST);//LSB_FIRST
	SPI_CPOL_SET(CPOL_LOW);//CPOL_HIGH
	SPI_CPHA_SET(SPI_CPHA_1Edge);//SPI_CPHA_2Edge
	
	SPI_TX_INT_DISABLE();
	SPI_RX_INT_DISABLE();

	INT_SPI1_CLR();
	SPI_IPL_SET(LOW);
	SPI_INT_DISABLE();

	SPI_ENABLE();
}
	
/*
	\brief      byd init
    \param[in]  none
    \param[out] none
    \retval     none
*/
void byd_init(void)
{
	DisableGlobalInterrupt();

	clock_config(SYS_CLOCK_SEL);
	
	BOR_ENABLE();//power off reset
	PLL_WAKE_TIME_SET(0);//idle mode wake time
	
//	byd_gpio_init();
	dqiot_drv_gpio_init();

#if TRACEMODE_EN	
	byd_tracemode_init(0x54,GPIO_PE4_PE5);//debug init
#endif

	EnableGlobalInterrupt();
			
#if BYD_CTK_EN
	byd_ctk_init();		
#endif

	XTAL_32K_ENABLE();
	delay_ms(1500);

#if MIFARE_EN
	rfid_config();
#endif

//	byd_timer_init();//示例使用timer2唤醒idle模式

//	uart_config();
//	spi_config();
//	pwm_config();
//	byd_exint_init();
//	lvdt_init(0);
	dqiot_drv_init();

    byd_wdt_init();	
}
