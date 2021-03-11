#ifndef __MMI_FPS_H__
#define __MMI_FPS_H__

#include "mmi_feature.h"
#ifdef __LOCK_FP_SUPPORT__
#include "dqiot_fp_sy.h"


// typedef void (*fp_irq_handle_callback)(void);

// typedef enum FP_COLOR
// {
// 	FP_BLUE = 0x00,
// 	FP_GREEN = 0x01,
// 	FP_RED = 0x02,
// 	FP_C_INVALID = 0xFF
// } FP_COLOR;

typedef enum FP_BUFF
{
	FP_CHAR_BUFF_1 = 0x01,
	FP_CHAR_BUFF_2 = 0x02,
	FP_CHAR_BUFF_3 = 0x03,
	FP_CHAR_BUFF_4 = 0x04,
	FP_CHAR_BUFF_5 = 0x05,
	FP_CHAR_BUFF_6 = 0x06,
	FP_CHAR_BUFF_INVALID = 0xFF
}FP_BUFF;

/*
parameter: 
	current status machine
return :
	none
*/
void mmi_dq_fp_init(void);

/*
parameter: 
	current status machine
return :
	none
*/
unsigned char mmi_dq_fp_get_image(void);

/*
parameter: 
	current status machine
return :
	none
*/
unsigned char mmi_dq_fp_gen_char(unsigned char id);

/*
parameter: 
	current status machine
return :
	none
*/
unsigned char mmi_dq_fp_high_speed_search(unsigned char Buf_id,unsigned short *index);

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_fp_light(FP_COLOR_E light_id);

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_fp_match(void);

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_fp_reg_module(void);

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_fp_store_char(unsigned char id, unsigned short index);

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_fp_delete(unsigned short index);

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_fp_empty(void);

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_fp_get_valid_templete(unsigned short *count);

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_fp_search(unsigned char Buf_id, unsigned short *index);

/*
parameter: 
	none
return :
	none
*/
FP_COLOR_E mmi_dq_fp_get_light(void);

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_fp_work(void);

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_fp_get_pin(void);
#endif

#endif //__MMI_FPS_H__

