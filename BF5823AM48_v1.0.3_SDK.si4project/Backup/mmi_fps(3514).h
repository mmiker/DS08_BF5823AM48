#ifndef __MMI_FPS_H__
#define __MMI_FPS_H__

#include "mmi_feature.h"

typedef void (*fp_irq_handle_callback)(void);

typedef enum FP_COLOR
{
	FP_BLUE = 0x00,
	FP_GREEN = 0x01,
	FP_RED = 0x02,
	FP_C_INVALID = 0xFF
}FP_COLOR;


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
unsigned short mmi_dq_fp_get_image(void);


/*
parameter: 
	current status machine
return :
	none
*/
void mmi_dq_fps_set_irq_handle_cb(fp_irq_handle_callback cb);

/*
parameter: 
	current status machine
return :
	none
*/
unsigned short mmi_dq_fp_gen_char(unsigned char id);

/*
parameter: 
	current status machine
return :
	none
*/
unsigned char mmi_dq_fp_high_speed_search(unsigned char Buf_id,unsigned short *index);

/*
parameter: 
	current status machine
return :
	none
*/
void mmi_dq_fp_light(FP_COLOR light_id);

#endif //__MMI_FPS_H__

