#ifndef __MMI_SYS_H__
#define __MMI_SYS_H__

#include "mmi_ms.h"
#include "mmi_com.h"

/*
function: system enter sleep
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_init(void);


/*
function: system enter sleep
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_enter_sleep(void);

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_show_message_with_id(unsigned char text_id,unsigned long time_msec);


#endif //__MMI_SYS_H__

