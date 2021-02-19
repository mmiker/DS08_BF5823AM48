#ifndef __DQIOT_DRV_RFID_C__
#define __DQIOT_DRV_RFID_C__

#include "byd_init.h"
#include "dqiot_drv.h"
#include "byd_mifare.h" 
#include "iso14443.h"
#include "delay.h"


/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_rfid_init(void)
{
#if MIFARE_EN
	rfid_config();
#endif
}

#endif
