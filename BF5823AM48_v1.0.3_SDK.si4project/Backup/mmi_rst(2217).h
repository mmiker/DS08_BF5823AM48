#ifndef __MMI_RST_H__
#define __MMI_RST_H__

#include "mmi_feature.h"

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_rst_timer_event(void);

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_rst_get_pin(void);

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_rst_get_state(void);


#endif
