/*!
    \file  main.c
    \brief main file
*/

#include "main.h"
#include "dqiot_drv.h"
#include "mmi_ms.h"
#include "mmi_sys.h"
#include "mmi_audio.h"

extern uint16_t timer0_count;

void system_init(void)
{
	DisableGlobalInterrupt();

	clock_config(SYS_CLOCK_SEL);
	
	BOR_ENABLE();//power off reset
	PLL_WAKE_TIME_SET(0);//idle mode wake time
	
#if TRACEMODE_EN	
	byd_tracemode_init(0x54,GPIO_PE4_PE5);//debug init
#endif

	EnableGlobalInterrupt();
			
	XTAL_32K_ENABLE();
	delay_ms(1500);
}

int main(void)
{
	u8 i = 0;
#if MIFARE_EN
    u8 ret;
    u8 gbuff[6];
#endif
    
	WDT_DISABLE();

	system_init();
	
	mmi_dq_bsp_init();

	mmi_dq_key_init();

	mmi_dq_fp_init();

	mmi_dq_rfid_init();

	wdt_init(WDT_TIME_2304MS);

	WDT_ENABLE();

	mmi_dq_sys_init();
	
	while(1)
	{
		WDT_CTRL = WDT_TIME_2304MS;
		//mmi_task_proc();
	
#if MIFARE_EN
		ret = get_card_number(gbuff);
		if(RETURN_OK == ret)
		{
			uint8_t get_ok = 0x9E;
	        if(RETURN_OK == M1_Example(gbuff))
			{
			   ;
			}
		}
#endif	

	}
}

