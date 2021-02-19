#ifndef __MMI_RST_C__
#define __MMI_RST_C__

#include "dqiot_drv.h"
#include "mmi_feature.h"
#include "mmi_rst.h"
#include "mmi_ms.h"
#include "mmi_queue.h"

static unsigned char rst_flag = 0;
static unsigned int  rst_count = 0;
/*
parameter: 
	none
return :
	none
*/
void mmi_dq_rst_init(void)
{


}

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_rst_timer_event(void)
{
	if(dqiot_drv_get_reset_pin() == 0)
	{
		if(rst_flag == 0)
		{
			rst_count ++;
			if(rst_count >= 40)
			{
				rst_flag = 1;
				//mmi_dq_ms_set_msg_que(QUE_EVENT_RST,QUE_PRO_LOW,0);
			}
		}	
	}
	else 
	{
		rst_count = 0;
		rst_flag = 0;
	}

}

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_rst_get_pin(void)
{
	return dqiot_drv_get_reset_pin();

}

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_rst_get_state(void)
{
	if(rst_flag == 1)
	{
		rst_flag = 2;
		return 1;
	}
	return 0;

}



#endif
