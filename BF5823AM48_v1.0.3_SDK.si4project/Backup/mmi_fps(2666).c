#ifndef __MMI_FPC_C__
#define __MMI_FPC_C__

#include "string.h"
#include "mmi_fps.h"
#include "mmi_feature.h"
#include "dqiot_drv.h"

#ifdef __LOCK_FP_SUPPORT__
/*
parameter: 
	current status machine
return :
	none
*/
//void mmi_dq_fp_set_fp_uart_handle_cb(fp_uart_handle_callback cb)
//{
	
//}

/*
parameter: 
	current status machine
return :
	none
*/
void mmi_dq_fps_set_irq_handle_cb(fp_irq_handle_callback cb)
{
	cb = NULL;
}

/*
parameter: 
	current status machine
return :
	none
*/
void mmi_dq_fp_init(void)
{
	dqiot_drv_fp_poweron();	
	
	// dqiot_drv_uart0B_init();
	return;
}


/*
parameter: 
	current status machine
return :
	none
*/
unsigned char mmi_dq_fp_get_fp_mode(void)
{
	return 1;
}

/*
parameter: 
	current status machine
return :
	none
*/
unsigned short mmi_dq_fp_get_image(void)
{
	unsigned short retval = 0;

	return retval;
}

/*
parameter: 
	current status machine
return :
	none
*/
unsigned short mmi_dq_fp_gen_char(unsigned char id)
{
	unsigned short retval = 0;
	id = 0;
	return retval;
}

/*
parameter: 
	current status machine
return :
	none
*/
unsigned short mmi_dq_fp_match(void)
{
	unsigned short retval = 0;

	return retval;
}

/*
parameter: 
	current status machine
return :
	none
*/
unsigned short mmi_dq_fp_reg_module(void)
{
	unsigned short retval = 0;

	return retval;
}

/*
parameter: 
	current status machine
return :
	none
*/
unsigned short mmi_dq_fp_store_char(unsigned char id,unsigned short index)
{
	unsigned short retval = 0;
	
	id = 0;
	index = 0;

	return retval;
}

/*
parameter: 
	current status machine
return :
	none
*/
unsigned short mmi_dq_fp_delete(unsigned short index)
{
	unsigned short retval = 0;
	
	index = 0;

	return retval;
}

/*
parameter: 
	current status machine
return :
	none
*/
unsigned short mmi_dq_fp_empty(void)
{
	unsigned short retval = 0;
	
	return retval;
}

/*
parameter: 
	current status machine
return :
	none
*/
unsigned char mmi_dq_fp_get_valid_templete(unsigned short *count)
{
	unsigned char retval =0;
	
	*count = 0;

	return retval;
}

/*
parameter: 
	current status machine
return :
	none
*/
unsigned char mmi_dq_fp_high_speed_search(unsigned char Buf_id,unsigned short *index)
{
	unsigned short retval = 0;
	
	Buf_id = 0;
	*index = 0;
	return retval;
}

/*
parameter: 
	current status machine
return :
	none
*/
unsigned char mmi_dq_fp_search(unsigned char Buf_id,unsigned short *index)
{
	unsigned short retval = 0;
	
	Buf_id = 0;
	*index = 0;
	
	return retval;
}

/*
parameter: 
	current status machine
return :
	none
*/
void mmi_dq_fp_light(FP_COLOR light_id)
{
	light_id = 0;
}

/*
parameter: 
	current status machine
return :
	none
*/
FP_COLOR mmi_dq_fp_get_light(void)
{
	return 0;
}

#endif  //__LOCK_FP_SUPPORT__

#endif//__MMI_FPC_C__

