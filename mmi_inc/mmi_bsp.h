#ifndef __MMI_BSP_H__
#define __MMI_BSP_H__

#include "mmi_key.h"
#include "mmi_fps.h"
#include "mmi_audio.h"
#include "mmi_rfid.h"

/*
parameter: 
	current status machine
return :
	none
*/
void mmi_dq_bsp_init(void);
/*
parameter: 
	none
return :
	none
*/
void mmi_dq_bsp_wake_up(void);

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_bsp_enter_sleep(void);

#endif
