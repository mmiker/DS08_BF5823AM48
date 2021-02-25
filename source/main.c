/*!
    \file  main.c
    \brief main file
*/

#include "main.h"
<<<<<<< HEAD
=======
#include "mmi_feature.h"
>>>>>>> six commit
#include "dqiot_drv.h"
#include "mmi_ms.h"
#include "mmi_fs.h"
#include "mmi_fps.h"
#include "mmi_sys.h"
#include "mmi_audio.h"
#include "mmi_bsp.h"
#include "mmi_fm.h"
<<<<<<< HEAD
//#include "stdio.h"

#define ADCVDT_EN 1 /* adcµçÑ¹¼ì²â */

extern uint16_t timer0_count;
=======
#include "dqiot_drv_audio.h"
//#include "stdio.h"

extern uint16_t timer0_count;
extern uint8_t audio_flag;
>>>>>>> six commit

void system_init(void)
{
	DisableGlobalInterrupt();

	clock_config(SYS_CLOCK_SEL);

	BOR_ENABLE();		  //power off reset
	PLL_WAKE_TIME_SET(0); //idle mode wake time

#if TRACEMODE_EN
	byd_tracemode_init(0x54, GPIO_PE4_PE5); //debug init
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
<<<<<<< HEAD

	mmi_dq_fp_init();

	mmi_dq_rfid_init();

	mmi_dq_aud_init();

=======
#ifdef __LOCK_FP_SUPPORT__
	mmi_dq_fp_init();
#endif
#ifdef __LOCK_RFID_CARD_SUPPORT__
	mmi_dq_rfid_init();
#endif
#ifdef __LOCK_AUDIO_SUPPORT__
	mmi_dq_aud_init();
#endif
>>>>>>> six commit
	byd_adc_init();

	wdt_init(WDT_TIME_2304MS);

<<<<<<< HEAD
#if ADCVDT_EN //¿ª»ú¼ì²â
	if (adc_VolT() == 1)
		mmi_dq_aud_play_with_id(AUD_BASE_ID_LOW_BATTERY);
#endif

=======
>>>>>>> six commit
	//WDT_ENABLE();

	mmi_dq_sys_init();

<<<<<<< HEAD
#if 0
	if(mmi_dq_fs_get_factory_flag() == 0)
	{
		mmi_dq_factory_mode_test_start();
	}
	else
#endif
	if (mmi_dq_fs_get_admin_status() == 0)
	{
		mmi_dq_sys_chg_admin_pwd();
	}
	else
		mmi_dq_ms_set_sys_state(SYS_STATUS_IDLE);

	//printf("main while satrt");
=======
	if (0 == mmi_dq_sys_check_vbat())
	{
#ifdef __FACTORY_TEST_SUPPORT__
		if (mmi_dq_fs_get_factory_flag() == 0)
		{
			mmi_dq_factory_mode_test_start();
		}
		else
		{
#endif
			if (mmi_dq_fs_get_admin_status() == 0)
			{
				mmi_dq_sys_add_admin_pwd();
			}
			else
				mmi_dq_ms_set_sys_state(SYS_STATUS_IDLE);
#ifdef __FACTORY_TEST_SUPPORT__
		}
#endif
	}
>>>>>>> six commit

	while (1)
	{
		if (SYS_STATUS_ENTER_SLEEP == mmi_dq_ms_get_sys_state())
		{
			lowpower_idle();

			mmi_sleep_task_proc();
		}
		else
		{
			WDT_CTRL = WDT_TIME_2304MS;

			mmi_task_proc();
		}

		mmi_dq_ms_sys_msg_handle();

		if (SYS_STATUS_WAIT_FOR_ENTER_SLEEP == mmi_dq_ms_get_sys_state())
			mmi_wait_sleep_task_proc();
	}
}
