#ifndef __MMI_FM_H__
#define __MMI_FM_H__

#include "mmi_feature.h"


/*
parameter: 
	none
return :
	none
*/
void mmi_dq_factory_mode_test_item_result(unsigned char item_name, unsigned char result);

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_factory_mode_get_test_project(void);

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_factory_mode_test_start(void);

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_factory_mode_test_stop(void);

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_factory_mode_key_test(unsigned char key_value);

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_factory_mode_fp_test(void);

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_factory_mode_rfid_test(void);

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_factory_mode_motor_test(void);

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_factory_mode_motor_test_back(void);

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_factory_mode_reset_test(void);

#endif
