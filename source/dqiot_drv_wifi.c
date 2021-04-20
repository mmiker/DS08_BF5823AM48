#ifndef __DQIOT_DRV_WIFI_C__
#define __DQIOT_DRV_WIFI_C__
#include "mmi_feature.h"
#ifdef __LOCK_WIFI_SUPPORT__
#include "dqiot_drv_wifi.h"
#include "iic_master.h"
#include "delay.h"
#include "mmi_fs.h"
#include "mmi_audio.h"
#include "mmi_wifi.h"
#include "mmi_fps.h"
#include "mmi_ms.h"
// #include <stdio.h>

unsigned char wifi_add_flag = 0;
extern unsigned char uart_get_buf[];
extern unsigned char uart_getbuflen;
// extern void printfS(char *show, char *status);
// extern void printfV(char *show, int value);

/**
  * @brief  GPIO初始化
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
void dqiot_drv_wifi_gpio_init(void)
{
	/*wifi
	UART0_TX	PF4	输出
	UART0_RX	PF5	输入
	NRST_CTR	PF7	供电
	*/
	gpio_init(FP_TX_PORT, FP_TX_PIN, GPIO_MODE_OUT);
	gpio_bit_set(FP_TX_PORT, FP_TX_PIN);

	gpio_init(FP_RX_PORT, FP_RX_PIN, GPIO_MODE_IPU);
	gpio_bit_set(FP_RX_PORT, FP_RX_PIN);

	gpio_init(FP_PWR_PORT, FP_PWR_PIN, GPIO_MODE_OUT);
	gpio_bit_set(FP_PWR_PORT, FP_PWR_PIN);

	return;
}

/**
  * @brief  GPIO取消初始化
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
void dqiot_drv_wifi_gpio_deinit(void)
{
	/*wifi
	UART0_TX	PF4	输出
	UART0_RX	PF5	输入
	NRST_CTR	PF7	供电
	*/
	gpio_init(FP_TX_PORT, FP_TX_PIN, GPIO_MODE_IN_FLOATING);
	gpio_bit_reset(FP_TX_PORT, FP_TX_PIN);

	gpio_init(FP_RX_PORT, FP_RX_PIN, GPIO_MODE_IN_FLOATING);
	gpio_bit_reset(FP_RX_PORT, FP_RX_PIN);

	gpio_init(FP_PWR_PORT, FP_PWR_PIN, GPIO_MODE_IN_FLOATING);
	gpio_bit_reset(FP_PWR_PORT, FP_PWR_PIN);

	return;
}

/**
  * @brief  串口数据接收
  * @param  send		发送数据
  * @param  send_len	发送数据长度
  * @param  Buf			接收数据
  * @param  len			接收数据长度
  * @return 串口数据
  * @note   none
  * @see    none
  */
uint8_t UH010_ReadDatas(uint8_t *send, uint8_t send_len, uint8_t *Buf, uint8_t len)
{
#if 0
	uint8_t i;

	if (send_len > 0)
	{
		EA = 0;
		iic_master_start();

		if (iic_sendbyte_and_getnack(WIFI_ADDR))
		{
			//iic_master_stop();
			//EA = 1;
			//return 1;
		}

		for (i = 0; i < send_len; i++)
		{
			if (iic_sendbyte_and_getnack(send[i]))
			{
				//iic_master_stop();
				//EA = 1;
				//return 1;
			}
		}

		if (iic_sendbyte_and_getnack(WIFI_ADDR | 0x01))
		{
			//iic_master_stop();
			//EA = 1;
			//return 1;
		}

		for (i = 0; i < len; i++)
		{
			Buf[i] = iic_receive_byte();
			if (i == (len - 1))
				break;
			iic_respond(ACK);
		}

		iic_respond(NACK);

		EA = 1;
		iic_master_stop();
	}
	else
	{
		EA = 0;
		iic_master_start();
		if (iic_sendbyte_and_getnack(WIFI_ADDR | 0x01))
		{
			//iic_master_stop();
			//EA = 1;
			//return 1;
		}

		for (i = 0; i < len; i++)
		{
			Buf[i] = iic_receive_byte();
			if (i == (len - 1))
				break;
			iic_respond(ACK);
		}

		iic_respond(NACK);

		EA = 1;
		iic_master_stop();
	}

	return 0;
#else
	uint8_t i = 0, j = 0;
	uint16_t waittime = 1000;

	if (send_len > 0)
	{
		EA = 0;

		for (i = 0; i < send_len; i++)
			uart_tx_byte(UART0, send[i]);

		while (--waittime)
		{
			delay_ms(1);

			if (uart_getbuflen >= 2)
			{
				/* 寻找包头 */
				for (i = 0; i < uart_getbuflen; i++)
				{
					if (uart_get_buf[i] == 'K' || uart_get_buf[i] == 'I' || uart_get_buf[i] == 'B' || uart_get_buf[i] == 'F' || uart_get_buf[i] == 'R' || uart_get_buf[i] == 'M' || uart_get_buf[i] == 'J' || uart_get_buf[i] == 'q')
						break;
				}

				for (i; i < uart_getbuflen; i++)
				{
					Buf[j] = uart_get_buf[i];
					if (j == (len - 1))
						break;
					j++;
				}

				EA = 1;
				/* 清空缓存 */
				uart_getbuflen = 0;

				return 0;
			}
		}

		EA = 1;
	}
	else
	{
		EA = 0;

		while (--waittime)
		{
			delay_ms(1);

			if (uart_getbuflen >= 2)
			{
				/* 寻找包头 */
				for (i = 0; i < uart_getbuflen; i++)
				{
					if (uart_get_buf[i] == 'K' || uart_get_buf[i] == 'I' || uart_get_buf[i] == 'B' || uart_get_buf[i] == 'F' || uart_get_buf[i] == 'R' || uart_get_buf[i] == 'M' || uart_get_buf[i] == 'J' || uart_get_buf[i] == 'q')
						break;
				}

				for (i; i < uart_getbuflen; i++)
				{
					Buf[j] = uart_get_buf[i];
					if (j == (len - 1))
						break;
					j++;
				}

				EA = 1;
				/* 清空缓存 */
				uart_getbuflen = 0;

				return 0;
			}
		}

		EA = 1;
	}

	return 0;
#endif
}

/**
  * @brief  串口数据发生
  * @param  send		发送数据
  * @param  send_len	发送数据长度
  * @return none
  * @note   none
  * @see    none
  */
uint8_t UH010_Write_Byte(uint8_t *send, uint8_t send_len)
{
#if 0
	uint8_t i;

	EA = 0;
	iic_master_start();

	if (iic_sendbyte_and_getnack(WIFI_ADDR & ~0x01))
	{
		iic_master_stop();
		EA = 1;
		return 1;
	}

	for (i = 0; i < send_len; i++)
	{
		if (iic_sendbyte_and_getnack(send[i]))
		{
			iic_master_stop();
			EA = 1;
			return 1;
		}
	}
	EA = 1;
	iic_master_stop();

	return 0;
#else
	uint8_t i;

	uart_getbuflen = 0;
	EA = 0;

	for (i = 0; i < send_len; i++)
		uart_tx_byte(UART0, send[i]);

	EA = 1;

	return 0;
#endif
}

/*
parameter: 
	none
return :
	none
*/
void wifi_uh316_init(void)
{
}

/**
  * @brief  智能配网（发送）
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
uint8_t wifi_net_connect_send(void)
{
	uint8_t wifi_data[2];
	wifi_data[0] = WIFI_CMD_NET_CON;
	wifi_data[1] = 100;
	if (UH010_Write_Byte(wifi_data, 2) == 0)
		return 1;
	else
		return 0;
}

/**
  * @brief  Airkiss配网（发送）
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
uint8_t wifi_net_airkiss_connect_send(void)
{
	uint8_t wifi_data[2];
	wifi_data[0] = WIFI_CMD_AIRKISS_NET_CON;
	wifi_data[1] = 100;
	if (UH010_Write_Byte(wifi_data, 2) == 0)
		return 1;
	else
		return 0;
}

/**
  * @brief  二维码配网（发送）
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
uint8_t wifi_net_code_connect_send(void)
{
	uint8_t wifi_data[2];
	wifi_data[0] = WIFI_CMD_CODE_NET_CON;
	wifi_data[1] = 100;
	if (UH010_Write_Byte(wifi_data, 2) == 0)
		return 1;
	else
		return 0;
}

/**
  * @brief  配网状态（接收）
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
uint8_t wifi_net_connect_state(void)
{
	uint8_t wifi_data[2];
	uint8_t data_2[2] = {0};
	wifi_data[0] = WIFI_CMD_NET_STATE;
	wifi_data[1] = 100;
	UH010_Write_Byte(wifi_data, 2);
	delay_ms(50);
	UH010_ReadDatas(wifi_data, 0, data_2, 2);
	if (data_2[0] == 'I' && data_2[1] == 'O')
		return 1;
	if (data_2[0] == 'I' && data_2[1] == 'E')
		return 2;
	else
		return 0;
}

/**
  * @brief  查询网络状态
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
uint8_t wifi_check_net(void)
{
	uint8_t wifi_data[2];
	uint8_t data_2[2] = {0};
	wifi_data[0] = WIFI_CMD_CHECK_NET;
	wifi_data[1] = 100;
	UH010_Write_Byte(wifi_data, 2);
	delay_ms(50);
	UH010_ReadDatas(wifi_data, 0, data_2, 2);
	if (data_2[0] == 'q' && data_2[1] == 'O')
		return 1;
	else
		return 0;
}

/**
  * @brief  拍照
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
uint8_t wifi_take_photos(void)
{
	uint8_t wifi_data[2];
	wifi_data[0] = WIFI_CMD_TAKE_PHOTOS;
	wifi_data[1] = 100;
	UH010_Write_Byte(wifi_data, 2);
	return 1;
}

/**
  * @brief  录像
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
uint8_t wifi_take_videos(void)
{
	uint8_t wifi_data[2];
	wifi_data[0] = WIFI_CMD_TAKE_VIDEOS;
	wifi_data[1] = 100;
	UH010_Write_Byte(wifi_data, 2);
	return 1;
}

/**
  * @brief  发送数据包
  * @param  cmd		命令
  * @param  pv		电流
  * @param  index	编号(0xff=null)
  * @return status
  * @note   none
  * @see    none
  */
uint8_t wifi_data_package(uint8_t cmd, uint8_t pv, uint8_t index)
{
	uint8_t wifi_data[3];
	wifi_data[0] = cmd;
	wifi_data[1] = pv;
	wifi_data[2] = index;

	if (index == 0xff)
		UH010_Write_Byte(wifi_data, 2);
	else
		UH010_Write_Byte(wifi_data, 3);

	return 1;
}

/**
  * @brief  远程开门（发送）
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
uint8_t wifi_open_ask(void)
{
	uint8_t wifi_data[2];
	wifi_data[0] = WIFI_CMD_WF_OPEN_ASK;
	wifi_data[1] = 100;
	if (UH010_Write_Byte(wifi_data, 2) == 0)
		return 1;
	else
		return 0;
}

/**
  * @brief  远程开门（接收）
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
uint8_t wifi_open_reply_get(void)
{
	uint8_t wifi_data[2];
	uint8_t data_2[2] = {0};
	wifi_data[0] = WIFI_CMD_WF_OPEN_REPLY;
	wifi_data[1] = 100;
	UH010_Write_Byte(wifi_data, 2);
	delay_ms(300);
	UH010_ReadDatas(wifi_data, 0, data_2, 2);

	// printfV("data_2[0]", (int)data_2[0]);
	// printfV("data_2[1]", (int)data_2[1]);

	if (data_2[0] == 'K' && data_2[1] == 'O')
		return 1;
	else if (data_2[0] == 'K' && data_2[1] == 'E')
		return 2;
	else if (data_2[0] == 'K' && data_2[1] == 'K')
		return 3;
	else
		return 0;
}

/**
  * @brief  添加删除密码/指纹/RF卡
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
uint8_t wifi_cmd_add_del(void)
{
	RET_VAL retval = 0xff;
	uint8_t wifi_data[2];
	uint8_t data_2[3] = {0};
	wifi_data[0] = WIFI_CMD_ADD_DEL;
	wifi_data[1] = 100;
	UH010_Write_Byte(wifi_data, 2);
	delay_ms(400);
	UH010_ReadDatas(wifi_data, 0, data_2, 3);

	if (data_2[0] == 'B')
	{
		switch (data_2[1])
		{
		case 'L':
			return 0xff;

		case 'E':
#ifdef __LOCK_AUDIO_SUPPORT__
			mmi_dq_aud_play_with_id(AUD_BASE_ID_FAIL);
#endif
			return 0xff;

		case 'M':
			wifi_add_flag = 1;
#ifdef __LOCK_AUDIO_SUPPORT__
			mmi_dq_aud_play_with_id(AUD_ID_INPUT_68_PWD);
#endif
			mmi_dq_ms_set_sys_state(SYS_STATUS_ADD_PWD);
			break;

		case 'F':
#ifdef __LOCK_FP_SUPPORT__
			wifi_add_flag = 1;
#ifdef __LOCK_AUDIO_SUPPORT__
			mmi_dq_aud_play_with_id(AUD_ID_PRESS_FP);
#endif
			mmi_dq_ms_set_sys_state(SYS_STATUS_ADD_FP);
#else
			mmi_dq_aud_play_with_id(AUD_BASE_ID_FAIL);
#endif
			break;

		case 'R':
#ifdef __LOCK_RFID_CARD_SUPPORT__
			wifi_add_flag = 1;
#ifdef __LOCK_AUDIO_SUPPORT__
			mmi_dq_aud_play_with_id(AUD_ID_PRESS_RFCARD);
#endif
			mmi_dq_ms_set_sys_state(SYS_STATUS_ADD_RFID);
#else
			mmi_dq_aud_play_with_id(AUD_BASE_ID_FAIL);
#endif
			break;
		}
	}
	else if (data_2[0] == 'M' || data_2[0] == 'F' || data_2[0] == 'R')
	{
		if (data_2[2] == 0x00) //48 => 0,57 => 9
			get_index = data_2[1] - '0';
		else
			get_index = (data_2[1] - '0') * 10 + (data_2[2] - '0');

		switch (data_2[0])
		{
		case 'M':
			retval = mmi_dq_fs_del_pwd(get_index, FDS_USE_TYPE_USER);
			if (retval == RET_SUCESS)
			{
#ifdef __LOCK_AUDIO_SUPPORT__
				mmi_dq_aud_play_with_id(AUD_ID_DEL_PWD_SUCESS);
#endif
				mmi_dq_wifi_del_password(get_index);
			}
			else
#ifdef __LOCK_AUDIO_SUPPORT__
				mmi_dq_aud_play_with_id(AUD_ID_DEL_FAIL)
#endif
					;
			break;

		case 'F':
#ifdef __LOCK_FP_SUPPORT__
			retval = mmi_dq_fs_del_fp(get_index, FDS_USE_TYPE_USER);
			if (retval == RET_SUCESS)
				retval = mmi_dq_fp_delete((unsigned short)get_index);
			if (retval == 0)
			{
#ifdef __LOCK_AUDIO_SUPPORT__
				mmi_dq_aud_play_with_id(AUD_ID_DEL_FP_SUCESS);
#endif
				mmi_dq_wifi_del_fp(get_index);
			}
			else
#ifdef __LOCK_AUDIO_SUPPORT__
				mmi_dq_aud_play_with_id(AUD_ID_DEL_FAIL)
#endif
					;
#else
			mmi_dq_aud_play_with_id(AUD_BASE_ID_FAIL);
#endif
			break;

		case 'R':
#ifdef __LOCK_RFID_CARD_SUPPORT__
			retval = mmi_dq_fs_del_rfid(get_index);
			if (retval == RET_SUCESS)
			{
#ifdef __LOCK_AUDIO_SUPPORT__
				mmi_dq_aud_play_with_id(AUD_ID_DEL_RFCARD_SUCESS);
#endif
				mmi_dq_wifi_del_rfid_suc(get_index);
			}
			else
#ifdef __LOCK_AUDIO_SUPPORT__
				mmi_dq_aud_play_with_id(AUD_ID_DEL_FAIL)
#endif
					;
#else
			mmi_dq_aud_play_with_id(AUD_BASE_ID_FAIL);
#endif
			break;
		}
	}
	else
		return 1; //空值

	return 0;
}

/**
  * @brief  门未关
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
void wifi_close_over_time(void)
{
	uint8_t wifi_data[2];
	wifi_data[0] = WIFI_CMD_CLOSE_OVER_TIME;
	wifi_data[1] = 100;
	UH010_Write_Byte(wifi_data, 2);
}

/**
  * @brief  唤醒
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
unsigned char wifi_wake_up(void)
{

	uint8_t wifi_data[2];
	wifi_data[0] = WIFI_CMD_WAKEUP;
	wifi_data[1] = 100;
	return UH010_Write_Byte(wifi_data, 2);
}

/**
  * @brief  睡眠
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
void wifi_sleep_mode(void)
{
	uint8_t wifi_data[2];
	wifi_data[0] = WIFI_CMD_SLEEP;
	wifi_data[1] = 100;
	UH010_Write_Byte(wifi_data, 2);
}

/**
  * @brief  添加密码
  * @param  index
  * @return none
  * @note   none
  * @see    none
  */
void wifi_add_password(uint8_t index)
{
	uint8_t wifi_data[3];
	wifi_data[0] = WIFI_CMD_ADD_PW;
	wifi_data[1] = 100;
	wifi_data[2] = index;
	UH010_Write_Byte(wifi_data, 3);
}

/**
  * @brief  删除密码
  * @param  index
  * @return none
  * @note   none
  * @see    none
  */
void wifi_del_password(uint8_t index)
{
	uint8_t wifi_data[3];
	wifi_data[0] = WIFI_CMD_DEL_PW;
	wifi_data[1] = 100;
	wifi_data[2] = index;
	UH010_Write_Byte(wifi_data, 3);
}

/**
  * @brief  添加指纹
  * @param  index
  * @return none
  * @note   none
  * @see    none
  */
void wifi_add_fp(uint8_t index)
{
	uint8_t wifi_data[3];
	wifi_data[0] = WIFI_CMD_ADD_FP;
	wifi_data[1] = 100;
	wifi_data[2] = index;
	UH010_Write_Byte(wifi_data, 3);
}

/**
  * @brief  删除指纹
  * @param  index
  * @return none
  * @note   none
  * @see    none
  */
void wifi_del_fp(uint8_t index)
{
	uint8_t wifi_data[3];
	wifi_data[0] = WIFI_CMD_DEL_FP;
	wifi_data[1] = 100;
	wifi_data[2] = index;
	UH010_Write_Byte(wifi_data, 3);
}

/**
  * @brief  添加RF卡
  * @param  index
  * @return none
  * @note   none
  * @see    none
  */
void wifi_add_rf(uint8_t index)
{
	uint8_t wifi_data[3];
	wifi_data[0] = WIFI_CMD_ADD_RF;
	wifi_data[1] = 100;
	wifi_data[2] = index;
	UH010_Write_Byte(wifi_data, 3);
}

/**
  * @brief  删除RF卡
  * @param  index
  * @return none
  * @note   none
  * @see    none
  */
void wifi_del_rf(uint8_t index)
{
	uint8_t wifi_data[3];
	wifi_data[0] = WIFI_CMD_DEL_RF;
	wifi_data[1] = 100;
	wifi_data[2] = index;
	UH010_Write_Byte(wifi_data, 3);
}

/**
  * @brief  密码全部清除
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
void wifi_clr_pwd(void)
{
	uint8_t wifi_data[2];
	wifi_data[0] = WIFI_CMD_CLR_PW;
	wifi_data[1] = 100;
	UH010_Write_Byte(wifi_data, 2);
}

/**
  * @brief  指纹全部清除
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
void wifi_clr_fp(void)
{
	uint8_t wifi_data[2];
	wifi_data[0] = WIFI_CMD_CLR_FP;
	wifi_data[1] = 100;
	UH010_Write_Byte(wifi_data, 2);
}

/**
  * @brief  RF卡全部清除
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
void wifi_clr_rf(void)
{
	uint8_t wifi_data[2];
	wifi_data[0] = WIFI_CMD_CLR_RF;
	wifi_data[1] = 100;
	UH010_Write_Byte(wifi_data, 2);
}

/**
  * @brief  远程开门
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
void wifi_open_by_wifi(void)
{
	uint8_t wifi_data[2];
	wifi_data[0] = WIFI_CMD_WF_OPEN;
	wifi_data[1] = 100;
	UH010_Write_Byte(wifi_data, 2);
}

/**
  * @brief  密码开门
  * @param  index
  * @return none
  * @note   none
  * @see    none
  */
void wifi_open_by_password(uint8_t index)
{
	uint8_t wifi_data[3];
	wifi_data[0] = WIFI_CMD_PW_OPEN;
	wifi_data[1] = 100;
	wifi_data[2] = index;
	UH010_Write_Byte(wifi_data, 3);
}

/**
  * @brief  指纹开门
  * @param  index
  * @return none
  * @note   none
  * @see    none
  */
void wifi_open_by_fp(uint8_t index)
{
	uint8_t wifi_data[3];
	wifi_data[0] = WIFI_CMD_FP_OPEN;
	wifi_data[1] = 100;
	wifi_data[2] = index;
	UH010_Write_Byte(wifi_data, 3);
}

/**
  * @brief  RF卡指纹
  * @param  index
  * @return none
  * @note   none
  * @see    none
  */
void wifi_open_by_rfid(uint8_t index)
{
	uint8_t wifi_data[3];
	wifi_data[0] = WIFI_CMD_RF_OPEN;
	wifi_data[1] = 100;
	wifi_data[2] = index;
	UH010_Write_Byte(wifi_data, 3);
}

/**
  * @brief  应急钥匙开门
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
void wifi_open_by_key(void)
{
	uint8_t wifi_data[2];
	wifi_data[0] = WIFI_CMD_KEY_OPEN;
	wifi_data[1] = 100;
	UH010_Write_Byte(wifi_data, 2);
}

/*
parameter: 
	none
return :
	none
*/
void wifi_door_close(void)
{
	uint8_t wifi_data[2];
	wifi_data[0] = WIFI_CMD_CLOSE;
	wifi_data[1] = 100;
	UH010_Write_Byte(wifi_data, 2);
}

/**
  * @brief  震动报警
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
void wifi_via_alarm(void)
{
	uint8_t wifi_data[2];
	wifi_data[0] = WIFI_CMD_VIA_ALARM;
	wifi_data[1] = 100;
	UH010_Write_Byte(wifi_data, 2);
}

/**
  * @brief	多次密码错误
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
void wifi_pw_alarm(void)
{
	uint8_t wifi_data[2];
	wifi_data[0] = WIFI_CMD_PW_ALARM;
	wifi_data[1] = 100;
	UH010_Write_Byte(wifi_data, 2);
}

/**
  * @brief	多次指纹错误
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
void wifi_fp_alarm(void)
{
	uint8_t wifi_data[2];
	wifi_data[0] = WIFI_CMD_FP_ALARM;
	wifi_data[1] = 100;
	UH010_Write_Byte(wifi_data, 2);
}

/**
  * @brief	多次RF卡错误
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
void wifi_rf_alarm(void)
{
	uint8_t wifi_data[2];
	wifi_data[0] = WIFI_CMD_RF_ALARM;
	wifi_data[1] = 100;
	UH010_Write_Byte(wifi_data, 2);
}

/**
  * @brief	低电量
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
void wifi_lowpower_alarm(void)
{
	uint8_t wifi_data[2];
	wifi_data[0] = WIFI_CMD_LOWPOWER_ALARM;
	wifi_data[1] = 100;
	UH010_Write_Byte(wifi_data, 2);
}

/**
  * @brief	拍照录像开关（发送）
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
void wifi_pv_switch_send(void)
{
	uint8_t wifi_data[2];
	wifi_data[0] = WIFI_CMD_PV_SWITCH_SEND;
	wifi_data[1] = 100;
	UH010_Write_Byte(wifi_data, 2);
}

/**
  * @brief  拍照录像开关（接收）
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
uint8_t wifi_pv_switch_get(void)
{
	uint8_t wifi_data[2];
	uint8_t data_2[2] = {0};
	wifi_data[0] = WIFI_CMD_PV_SWITCH_GET;
	wifi_data[1] = 100;
	UH010_Write_Byte(wifi_data, 2);
	delay_ms(400);
	UH010_ReadDatas(wifi_data, 0, data_2, 2);
	if (data_2[0] == 'J' && data_2[1] == 'E') //无响应
		return 0xff;
	else if (data_2[0] == 'J' && data_2[1] == '0') //关闭拍照录像(设备之后开门都不会发送拍照和录像命令)
		return 0;
	else if (data_2[0] == 'J' && data_2[1] == '1') //开启拍照关闭录像
		return 1;
	else if (data_2[0] == 'J' && data_2[1] == '2') //关闭拍照开启录像
		return 2;
	else if (data_2[0] == 'J' && data_2[1] == '3') //开启拍照开启录像
		return 3;
	else
		return 0xff;
}

void wifi_send_fp_110(void)
{
	uint8_t wifi_data[2];
	wifi_data[0] = WIFI_CMD_WF_OPEN_FP_110;
	wifi_data[1] = 100;
	UH010_Write_Byte(wifi_data, 2);
}

void wifi_send_pwd_110(void)
{
	uint8_t wifi_data[2];
	wifi_data[0] = WIFI_CMD_WF_OPEN_PSW_110;
	wifi_data[1] = 100;
	UH010_Write_Byte(wifi_data, 2);
}

void wifi_set_110(void)
{
	uint8_t wifi_data[2];
	wifi_data[0] = WIFI_CMD_WF_SET_110;
	wifi_data[1] = 100;
	UH010_Write_Byte(wifi_data, 2);
}

#endif
#endif //__DQIOT_DRV_WIFI_C__
