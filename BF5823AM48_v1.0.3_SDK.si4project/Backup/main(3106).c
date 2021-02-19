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

int main(void)
{
	u8 i = 0;
#if MIFARE_EN
    u8 ret;
    u8 gbuff[6];
#endif
    
	WDT_DISABLE();

	byd_init();

	WDT_ENABLE();

	drv_ext_ldo_on();

	drv_key_led_on();

	drv_fp_init();

	mmi_dq_sys_init();

	//mmi_dq_aud_play_with_id(6,NULL);
	delay_ms(2000);

	drv_fp_test();
	delay_ms(500);
	
	dqiot_drv_uart0A_init();
	dqiot_drv_uart0_sendData();
	
	while(1)
	{
		WDT_CTRL = WDT_TIME_2304MS;
		//mmi_task_proc();
	
#if BYD_CTK_EN	
		byd_ctk_work();
#endif

#if MIFARE_EN
		ret = get_card_number(gbuff);
		if(RETURN_OK == ret)
		{
	        if(RETURN_OK == M1_Example(gbuff))
			{
			   ;
			}
		}
#endif	

	}
}

