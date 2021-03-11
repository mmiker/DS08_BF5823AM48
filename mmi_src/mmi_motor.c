#include "mmi_feature.h"
#if defined (__LOCK_MOTOR_SUPPORT__)
#include "mmi_motor.h"
#include "dqiot_drv_motor.h"



/*
parameter: 
	none
return :
	none
*/
void mmi_dq_motor_turn_right(void)
{
	dqiot_drv_motor_turn_right();
	return;
}

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_motor_turn_back(void)
{
	dqiot_drv_motor_turn_back();
	return;
}


/*
parameter: 
	none
return :
	none
*/
void mmi_dq_motor_stop(void)
{
	dqiot_drv_motor_stop();
	return;
}








#endif



