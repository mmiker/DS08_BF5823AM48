#ifndef __MMI_KEY_C__
#define __MMI_KEY_C__

#include "dqiot_drv.h"
#include "mmi_feature.h"
#include "mmi_key.h"

unsigned char g_touch_flag = 0;
/*
parameter: 
	none
return :
	none
*/
void mmi_dq_key_init(void)
{
	dqiot_drv_touch_init();
	return;
}

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_key_check(void)
{
	return dqiot_drv_touch_check();
}

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_key_work(void)
{
	return dqiot_drv_touch_work();
}

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_key_get_value(void)
{
	return dqiot_drv_get_touch_value();
}

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_get_key_map(unsigned char index)
{
	unsigned char key_val = KEY_INVALID;
	#ifdef __DQ_PROJECT_DS08__
	switch(index)
	{
		case 0:
			key_val = KEY_3;
			break;
		case 1:
			key_val = KEY_2;
			break;
		case 2:
			key_val = KEY_1;
			break;
		case 3:
			key_val = KEY_6;
			break;
		case 4:
			key_val = KEY_9;
			break;
		case 5:
			key_val = KEY_H;
			break;
		case 6:
			key_val = KEY_5;
			break;
		case 7:
			key_val = KEY_4;
			break;
		case 8:
			key_val = KEY_7;
			break;
		case 9:
			key_val = KEY_S;
			break;
		case 10:
			key_val = KEY_0;
			break;
		case 11:
			key_val = KEY_8;
			break;
		default:
			break;
	}
	#endif
	return key_val;
}

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_key_entersleep(void)
{
#ifdef BYD_CTK_ENABLE
	//TIMER2_ENABLE();
	//CSD_DISABLE();
	//lowpower_idle();
	//TIMER2_DISABLE();
	//CSD_ENABLE();
#endif
}
#endif//__MMI_KEY_C__
