#ifndef __MMI_RFID_C__
#define __MMI_RFID_C__
#include "mmi_feature.h"
#ifdef __LOCK_RFID_CARD_SUPPORT__
#include "dqiot_drv.h"
#include "mmi_rfid.h"
#include "string.h"
#include "stdlib.h"
#include "delay.h"
#include "mmi_fs.h"

unsigned char rfid_uid_buff_temp[RFID_SEC_DATA_LEN] = {0};
unsigned char rfid_uid_buff[2][RFID_SEC_DATA_LEN];
unsigned char RF_oldStatus = 0;

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_rfid_init(void)
{
	dqiot_drv_rfid_init();
}

/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_rfid_check(void)
{
	return dqiot_drv_rfid_check() ? RET_SUCESS : RET_FAIL;
}

/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_rfid_work(void)
{
	return dqiot_drv_rfid_get_card_number(rfid_uid_buff_temp) ? RET_SUCESS : RET_FAIL;
}

/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_rfid_gen_char(unsigned char index)
{
	unsigned char i = 0;
	if (index >= 2)
		return RET_FAIL;
	for (i = 0; i < RFID_SEC_DATA_LEN; i++)
	{
		rfid_uid_buff[index][i] = rfid_uid_buff_temp[i];
		rfid_uid_buff_temp[i] = 0x00;
	}
	return RET_SUCESS;
}

/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_rfid_match(void)
{
	if (memcmp((const char *)rfid_uid_buff[0], (const char *)rfid_uid_buff[1], RFID_SEC_DATA_LEN) == 0)
		return RET_SUCESS;
	return RET_FAIL;
}

/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_rfid_search_by_temp(unsigned char *index)
{
	*index = mmi_dq_fs_check_rfid(rfid_uid_buff_temp, FDS_USE_TYPE_ALL);
	if (*index != 0xFF)
		return RET_SUCESS;

	return RET_FAIL;
}

/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_rfid_search_by_id(unsigned char id, unsigned char *index)
{
	if (id > 1)
		return RET_FAIL;

	*index = mmi_dq_fs_check_rfid(rfid_uid_buff[id], FDS_USE_TYPE_ALL);
	if (*index != 0xFF)
		return RET_SUCESS;

	return RET_FAIL;
}

/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_rfid_delete(unsigned char index)
{
	return mmi_dq_fs_del_rfid(index);
}

/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_rfid_store(unsigned char id)
{
	return mmi_dq_fs_set_rfid(rfid_uid_buff[id], FDS_USE_TYPE_USER);
}

#endif

#endif //__MMI_RFID_C__
