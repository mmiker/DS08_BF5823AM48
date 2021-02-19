/*!
    \file  main.c
    \brief main file
*/

#include "main.h"
#include "dqiot_drv.h"
#include "mmi_ms.h"
#include "mmi_fs.h"
#include "mmi_sys.h"
#include "mmi_audio.h"
#include "mmi_bsp.h"
//#include "stdio.h"



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
    unsigned char i = 0;
	WDT_DISABLE();

	system_init();
	
	mmi_dq_bsp_init();

	mmi_dq_key_init();

	mmi_dq_fp_init();

	mmi_dq_rfid_init();

	mmi_dq_aud_init();

	byd_adc_init();

	wdt_init(WDT_TIME_2304MS);

	//WDT_ENABLE();
	
	mmi_dq_sys_init();

	if(mmi_dq_fs_get_init_flag() == FDS_INIT_INVALID)
	{
		//mmi_dq_ms_set_sys_state(SYS_STATUS_ADD_ADMIN_PWD);
		mmi_dq_sys_chg_admin_pwd();
	}
	else 
		mmi_dq_ms_set_sys_state(SYS_STATUS_IDLE);

	//printf("main while satrt");

	
	while(1)
	{
		if(SYS_STATUS_ENTER_SLEEP == mmi_dq_ms_get_sys_state())
		{
			//TIMER2_ENABLE();
			
			lowpower_idle();
			
			mmi_sleep_task_proc();
		}
		else if(SYS_STATUS_WAIT_FOR_ENTER_SLEEP == mmi_dq_ms_get_sys_state())
		{
			WDT_CTRL = WDT_TIME_2304MS;
		
			mmi_wait_sleep_task_proc();
		}
		else
		{
		
			mmi_task_proc();
		}
		
		mmi_dq_ms_sys_msg_handle();
	}
}

