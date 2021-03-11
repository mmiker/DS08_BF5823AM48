#ifndef __DQIOT_DRV_WIFI_H__
#define __DQIOT_DRV_WIFI_H__
#include "dqiot_drv_wifi.h"
#include "mmi_feature.h"
#include "iic_master.h"
#include "delay.h"
// #include <stdio.h>

/*
parameter: 
	none
return :
	none
*/
uint8_t UH010_ReadDatas(uint8_t *send, uint8_t send_len, uint8_t *Buf, uint8_t len)
{
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
}

/*
parameter: 
	none
return :
	none
*/
unsigned char UH010_Write_Byte(uint8_t *send, uint8_t send_len)
{
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

/*
parameter: 
	none
return :
	none
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

/*
parameter: 
	none
return :
	none
*/
uint8_t wifi_net_connect_state(void)
{
	uint8_t wifi_data[2];
	uint8_t data_2[2] = {0};
	wifi_data[0] = WIFI_CMD_NET_STATE;
	wifi_data[1] = 100;
	UH010_Write_Byte(wifi_data, 2);
	delay_ms(10);
	UH010_ReadDatas(wifi_data, 0, data_2, 2);
	if (data_2[0] == 'I' && data_2[1] == 'O')
		return 1;
	else
		return 0;
}

/*
parameter: 
	none
return :
	none
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

/*
parameter: 
	none
return :
	none
*/
uint8_t wifi_open_reply_get(void)
{
	uint8_t wifi_data[2];
	uint8_t data_2[2] = {0};
	wifi_data[0] = WIFI_CMD_WF_OPEN_REPLY;
	wifi_data[1] = 100;
	UH010_Write_Byte(wifi_data, 2);
	delay_ms(10);
	UH010_ReadDatas(wifi_data, 0, data_2, 2);
	if (data_2[0] == 'K' && data_2[1] == 'O')
		return 1;
	else if (data_2[0] == 'K' && data_2[1] == 'E')
		return 2;
	else if (data_2[0] == 'K' && data_2[1] == 'K')
		return 3;
	else
		return 0;
}

/*
parameter: 
	none
return :
	none
*/
void wifi_close_over_time(void)
{
	uint8_t wifi_data[2];
	wifi_data[0] = WIFI_CMD_CLOSE_OVER_TIME;
	wifi_data[1] = 100;
	UH010_Write_Byte(wifi_data, 2);
}

/*
parameter: 
	none
return :
	none
*/
unsigned char wifi_wake_up(void)
{

	uint8_t wifi_data[2];
	wifi_data[0] = WIFI_CMD_WAKEUP;
	wifi_data[1] = 100;
	return UH010_Write_Byte(wifi_data, 2);
}

/*
parameter: 
	none
return :
	none
*/
void wifi_sleep_mode(void)
{
	uint8_t wifi_data[2];
	wifi_data[0] = WIFI_CMD_SLEEP;
	wifi_data[1] = 100;
	UH010_Write_Byte(wifi_data, 2);
}

/*
parameter: 
	none
return :
	none
*/
void wifi_add_password(void)
{
	uint8_t wifi_data[2];
	wifi_data[0] = WIFI_CMD_ADD_PW;
	wifi_data[1] = 100;
	UH010_Write_Byte(wifi_data, 2);
}

/*
parameter: 
	none
return :
	none
*/
void wifi_del_password(void)
{
	uint8_t wifi_data[2];
	wifi_data[0] = WIFI_CMD_DEL_PW;
	wifi_data[1] = 100;
	UH010_Write_Byte(wifi_data, 2);
}

/*
parameter: 
	none
return :
	none
*/
void wifi_add_fp(void)
{
	uint8_t wifi_data[2];
	wifi_data[0] = WIFI_CMD_ADD_FP;
	wifi_data[1] = 100;
	UH010_Write_Byte(wifi_data, 2);
}

/*
parameter: 
	none
return :
	none
*/
void wifi_del_fp(void)
{
	uint8_t wifi_data[2];
	wifi_data[0] = WIFI_CMD_DEL_FP;
	wifi_data[1] = 100;
	UH010_Write_Byte(wifi_data, 2);
}

/*
parameter: 
	none
return :
	none
*/
void wifi_open_by_wifi(void)
{
	uint8_t wifi_data[2];
	wifi_data[0] = WIFI_CMD_WF_OPEN;
	wifi_data[1] = 100;
	UH010_Write_Byte(wifi_data, 2);
}

/*
parameter: 
	none
return :
	none
*/
void wifi_open_by_password(void)
{
	uint8_t wifi_data[2];
	wifi_data[0] = WIFI_CMD_PW_OPEN;
	wifi_data[1] = 100;
	UH010_Write_Byte(wifi_data, 2);
}

/*
parameter: 
	none
return :
	none
*/
void wifi_open_by_rfid(void)
{
	uint8_t wifi_data[2];
	wifi_data[0] = WIFI_CMD_RF_OPEN;
	wifi_data[1] = 100;
	UH010_Write_Byte(wifi_data, 2);
}

/*
parameter: 
	none
return :
	none
*/
void wifi_open_by_fp(void)
{
	uint8_t wifi_data[2];
	wifi_data[0] = WIFI_CMD_FP_OPEN;
	wifi_data[1] = 100;
	UH010_Write_Byte(wifi_data, 2);
}

/*
parameter: 
	none
return :
	none
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

/*
parameter: 
	none
return :
	none
*/
void wifi_via_alarm(void)
{
	uint8_t wifi_data[2];
	wifi_data[0] = WIFI_CMD_VIA_ALARM;
	wifi_data[1] = 100;
	UH010_Write_Byte(wifi_data, 2);
}

/*
parameter: 
	none
return :
	none
*/
void wifi_pw_alarm(void)
{
	uint8_t wifi_data[2];
	wifi_data[0] = WIFI_CMD_PW_ALARM;
	wifi_data[1] = 100;
	UH010_Write_Byte(wifi_data, 2);
}

/*
parameter: 
	none
return :
	none
*/
void wifi_fp_alarm(void)
{
	uint8_t wifi_data[2];
	wifi_data[0] = WIFI_CMD_FP_ALARM;
	wifi_data[1] = 100;
	UH010_Write_Byte(wifi_data, 2);
}

/*
parameter: 
	none
return :
	none
*/
void wifi_rf_alarm(void)
{
	uint8_t wifi_data[2];
	wifi_data[0] = WIFI_CMD_RF_ALARM;
	wifi_data[1] = 100;
	UH010_Write_Byte(wifi_data, 2);
}

/*
parameter: 
	none
return :
	none
*/
void wifi_lowpower_alarm(void)
{
	uint8_t wifi_data[2];
	wifi_data[0] = WIFI_CMD_LOWPOWER_ALARM;
	wifi_data[1] = 100;
	UH010_Write_Byte(wifi_data, 2);
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
