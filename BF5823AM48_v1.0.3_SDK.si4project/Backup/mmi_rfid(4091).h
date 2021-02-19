#ifndef __MMI_RFID_H__
#define __MMI_RFID_H__

#include "mmi_com.h"

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_rfid_init(void);

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_rfid_check(void);

/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_rfid_gen_char(uint8_t index);

/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_rfid_match(void);

/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_rfid_search_by_temp(uint8_t* index);

/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_rfid_search_by_id(uint8_t id, uint8_t* index);

/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_rfid_delete(uint8_t index);

/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_rfid_store(uint8_t* index);

#endif //__MMI_RFID_H__

