#ifndef __MMI_FPC_C__
#define __MMI_FPC_C__

#include "mmi_feature.h"
#ifdef __LOCK_FP_SUPPORT__
#include "string.h"
#include "mmi_fps.h"
#include "dqiot_drv.h"
// #include <stdio.h>

unsigned char FP_oldStatus = 0;

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
//void mmi_dq_fps_set_irq_handle_cb(fp_irq_handle_callback cb)
//{
//	cb = NULL;
//}

/*
parameter: 
	current status machine
return :
	none
*/
void mmi_dq_fp_init(void)
{
	u16 waittime = 2000;
	dqiot_drv_fp_poweron();
	while (--waittime)
	{
		delay_ms(1);
		if (FP_Get_Start_Flag() == 1)
		{
			FP_Light(FP_BLUE);
			return;
		}
	}

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
unsigned char mmi_dq_fp_get_image(void)
{
	unsigned char retval = 0;

	retval = PS_GetImage();
	return retval;
}

/*
parameter: 
	current status machine
return :
	none
*/
unsigned char mmi_dq_fp_gen_char(unsigned char id)
{
	unsigned char retval = 0;
	unsigned char real_buf_id;

	if (id == 0)
		real_buf_id = CHAR_BUFFER1;
	else if (id == 1)
		real_buf_id = CHAR_BUFFER2;
	else if (id == 2)
		real_buf_id = CHAR_BUFFER3;
	else if (id == 3)
		real_buf_id = CHAR_BUFFER4;

	retval = PS_GenChar(real_buf_id); //��������
	return retval;
}

/*
parameter: 
	current status machine
return :
	none
*/
unsigned char mmi_dq_fp_match(void)
{
	unsigned char retval = 0;

	retval = PS_Match();
	return retval;
}

/*
parameter: 
	current status machine
return :
	none
*/
unsigned char mmi_dq_fp_reg_module(void)
{
	unsigned char retval = 0;

	retval = PS_RegModel();
	return retval;
}

/*
parameter: 
	current status machine
return :
	none
*/
unsigned char mmi_dq_fp_store_char(unsigned char id, unsigned short index)
{
	unsigned char retval = 0;
	unsigned char real_buf_id;

	if (id == 0)
		real_buf_id = CHAR_BUFFER1;
	else if (id == 1)
		real_buf_id = CHAR_BUFFER2;
	else if (id == 2)
		real_buf_id = CHAR_BUFFER3;
	else if (id == 3)
		real_buf_id = CHAR_BUFFER4;

	retval = PS_StoreChar(real_buf_id, index); //����ģ��
	return retval;
}

/*
parameter: 
	current status machine
return :
	none
*/
unsigned char mmi_dq_fp_delete(unsigned short index)
{
	unsigned char retval = 0;

	retval = PS_DeletChar(index, 1);
	return retval;
}

/*
parameter: 
	current status machine
return :
	none
*/
unsigned char mmi_dq_fp_empty(void)
{
	unsigned char retval = 0;

	retval = PS_Empty();
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
	unsigned char retval = 0;

	retval = PS_ValidTempleteNum(count);
	return retval;
}

/*
parameter: 
	current status machine
return :
	none
*/
unsigned char mmi_dq_fp_high_speed_search(unsigned char Buf_id, unsigned short *index)
{
	unsigned char retval = 0;
	unsigned char real_buf_id;

	if (Buf_id == 0)
		real_buf_id = CHAR_BUFFER1;
	else if (Buf_id == 1)
		real_buf_id = CHAR_BUFFER2;
	else if (Buf_id == 2)
		real_buf_id = CHAR_BUFFER3;
	else if (Buf_id == 3)
		real_buf_id = CHAR_BUFFER4;
	
	retval = PS_HighSpeedSearch(real_buf_id, 0, 300, index);
	return retval;
}

/*
parameter: 
	current status machine
return :
	none
*/
unsigned char mmi_dq_fp_search(unsigned char Buf_id, unsigned short *index)
{
	unsigned char retval = 0;
	unsigned char real_buf_id;

	if (Buf_id == 0)
		real_buf_id = CHAR_BUFFER1;
	else if (Buf_id == 1)
		real_buf_id = CHAR_BUFFER2;
	else if (Buf_id == 2)
		real_buf_id = CHAR_BUFFER3;
	else if (Buf_id == 3)
		real_buf_id = CHAR_BUFFER4;

	retval = PS_Search(real_buf_id, 0, 300, index);
	return retval;
}

/*
parameter: 
	current status machine
return :
	none
*/
void mmi_dq_fp_light(FP_COLOR_E light_id)
{
	FP_Light(light_id); //���
}

/*
parameter: 
	current status machine
return :
	none
*/
FP_COLOR_E mmi_dq_fp_get_light(void)
{
	FP_COLOR_E retval = 0;
	retval = FP_Get_Light();
	return retval;
}

/* �����ж� */
unsigned char mmi_dq_fp_work(void)
{
	if (gpio_bit_get(GPIOF, GPIO_PIN_6) == 0)
	{
		if (FP_oldStatus == 0)
		{
			FP_oldStatus = 1;
			return 1;
		}
	}
	else
		FP_oldStatus = 0;
	return 0;
}

unsigned char mmi_dq_fp_get_pin(void)
{
	return gpio_bit_get(GPIOF, GPIO_PIN_6);
}

#endif //__LOCK_FP_SUPPORT__

#endif //__MMI_FPC_C__
