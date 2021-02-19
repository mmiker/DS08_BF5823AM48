#ifndef __DQIOT_DRV_RFID_H__
#define __DQIOT_DRV_RFID_H__

#include "mmi_feature.h"

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_rfid_init(void);

/*
parameter: 
	none
return :
	none
*/
uint8_t dqiot_drv_rfid_check(void);

/*
parameter: 
	none
return :
	none
*/
uint8_t dqiot_drv_rfid_get_card_number(uint8_t *uid);

#endif
