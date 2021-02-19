#ifndef __MMI_FPC_C__
#define __MMI_FPC_C__

#include "string.h"
#include "mmi_fps.h"
#include "mmi_feature.h"
#include "dqiot_drv.h"
#include "delay.h"
#include "mmi_fs.h"

#ifdef __LOCK_FP_SUPPORT__

/* ValidN，OldValidN 模块内有效模板个数 */
u16 ValidN = 0, OldValidN = 0;
/* FP_oldStatus，FP_newStatus 记录按压状态 (1按下/0未按下)*/
u16 FP_oldStatus = 0, FP_newStatus = 0;
/* waittime 等待确认码时间 x*1000ms ; FP_Status 指纹模块状态(0未连接/1连接)*/
u16 waittime, FP_Status = 0;

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
	dqiot_drv_uart0B_init();
	dqiot_drv_fp_poweron();

#if 1
	waittime = 3;
	while (--waittime)
	{
		if (PS_HandShake(&AS608_Addr) == 0x55) /* 与AS608模块握手 */
		{
			FP_Status = 1;
#if 1 /* 读库指纹个数 */
			PS_ValidTempleteNum(&ValidN);
#endif
			FP_Light(FP_BLUE); //点灯
			return;
		}
	}
#else
	waittime = 3000;
	while (--waittime)
	{
		if (uart_rx_byte(UART0) == 0x55)
		{
			FP_Status = 1;
#if 1 /* 读库指纹个数 */
			PS_ValidTempleteNum(&ValidN);
#endif
			FP_Light(FP_BLUE); //点灯
			return;
		}
	}
#endif

	FP_Status = 0;
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

#if 0
	waittime = 1; //等待确认码时间
	while (--waittime)
	{
		retval = PS_GetImage();
		if (retval != 1 && retval != 2)
			return retval;
	}
#else
	retval = PS_GetImage();
#endif
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
	unsigned char real_buf_id;

	if (id == 0)
		real_buf_id = CHAR_BUFFER1;
	else if (id == 1)
		real_buf_id = CHAR_BUFFER2;
	else if (id == 2)
		real_buf_id = CHAR_BUFFER3;
	else if (id == 3)
		real_buf_id = CHAR_BUFFER4;

#if 0
	waittime = 3; //等待确认码时间
	while (--waittime)
	{
		delay_ms(1);
		retval = PS_GenChar(real_buf_id);
		if (retval != 1)
			return retval;
	}
#else
	retval = PS_GenChar(real_buf_id); //生成特征

#endif
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

#if 0
	waittime = 3; //等待确认码时间
	while (--waittime)
	{
		delay_ms(1);
		retval = PS_Match();
		if (retval != 1)
			return retval;
	}
#else
	retval = PS_Match();
#endif
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

#if 0
	waittime = 3; //等待确认码时间
	while (--waittime)
	{
		delay_ms(1);
		retval = PS_RegModel();
		if (retval != 1)
			return retval;
	}
#else
	retval = PS_RegModel();
#endif
	return retval;
}

/*
parameter: 
	current status machine
return :
	none
*/
unsigned short mmi_dq_fp_store_char(unsigned char id, unsigned short index)
{
	unsigned short retval = 0;
	unsigned char real_buf_id;

	if (id == 0)
		real_buf_id = CHAR_BUFFER1;
	else if (id == 1)
		real_buf_id = CHAR_BUFFER2;
	else if (id == 2)
		real_buf_id = CHAR_BUFFER3;
	else if (id == 3)
		real_buf_id = CHAR_BUFFER4;

#if 0
	waittime = 3; //等待确认码时间
	while (--waittime)
	{
		delay_ms(1);
		retval = PS_StoreChar(real_buf_id, index); //储存模板
		if (retval != 1)
			return retval;
	}
#else
	retval = PS_StoreChar(real_buf_id, index); //储存模板
#endif
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

#if 0
	waittime = 2; //等待确认码时间
	while (--waittime)
	{
		delay_ms(1);
		retval = PS_DeletChar(index, 1);
		if (retval != 1)
			return retval;
	}
#else
	retval = PS_DeletChar(index, 1);
#endif
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

#if 0
	waittime = 3; //等待确认码时间
	while (--waittime)
	{
		delay_ms(1);
		retval = PS_Empty();
		if (retval != 1)
			return retval;
	}
#else
	retval = PS_Empty();
#endif
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

#if 0
	waittime = 3; //等待确认码时间
	while (--waittime)
	{
		delay_ms(1);
		retval = PS_ValidTempleteNum(count);
		if (retval != 1)
			return retval;
	}
#else
	retval = PS_ValidTempleteNum(count);
#endif
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
	unsigned short retval = 0;
	unsigned char real_buf_id;

	if (Buf_id == 0)
		real_buf_id = CHAR_BUFFER1;
	else if (Buf_id == 1)
		real_buf_id = CHAR_BUFFER2;
	else if (Buf_id == 2)
		real_buf_id = CHAR_BUFFER3;
	else if (Buf_id == 3)
		real_buf_id = CHAR_BUFFER4;

#if 0
	waittime = 2; //等待确认码时间
	while (--waittime)
	{
		delay_ms(1);
		retval = PS_HighSpeedSearch(real_buf_id, 0, 300, index);
		if (retval != 1)
			return retval;
	}
#else
	retval = PS_HighSpeedSearch(real_buf_id, 0, 300, index);
#endif
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
	unsigned short retval = 0;
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
	FP_Light(light_id); //点灯
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

/* 触摸判断 */
int mmi_dq_fp_work(void)
{
	if (gpio_bit_get(GPIOF, GPIO_PIN_6) == 0)
		FP_newStatus = 1;
	else
		FP_newStatus = 0;

	if (FP_newStatus == 1 && FP_newStatus != FP_oldStatus)
	{
		FP_oldStatus = 1;
		return 1;
	}
	else if (FP_newStatus == 0 && FP_newStatus != FP_oldStatus)
	{
		FP_oldStatus = 0;
		return 0;
	}
	else if (FP_newStatus == 1 && FP_newStatus == FP_oldStatus)
		return 0;
}

#endif //__LOCK_FP_SUPPORT__

#endif //__MMI_FPC_C__
