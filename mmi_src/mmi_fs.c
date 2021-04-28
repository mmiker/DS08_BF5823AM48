#ifndef __MMI_FS_C__
#define __MMI_FS_C__

#include "mmi_fs.h"
#include "mmi_sys.h"
#include "mcu02_sfr.h"
#include "mcu02_eeprom.h"
#include "string.h"
#include <stdio.h>
#include "dqiot_drv.h"

#include "mmi_fps.h"
#include "mmi_ms.h"
#include "dq_otp.h"
#ifdef __LOCK_VIRTUAL_PASSWORD__
#include "dq_sdk_main.h"
#endif
#ifdef __LOCK_DECODE_SUPPORT__
#include "mmi_decode.h"
#endif

extern void printfS(char *show, char *status);

unsigned char get_index = 0xff;

mmi_fs_setting data g_dq_fs_init_set;

#define MMI_DQ_FS_PWD_MAX_NUM 100
mmi_fs_pwd g_dq_fs_pwd[MMI_DQ_FS_PWD_MAX_NUM];

#if defined(__LOCK_FP_SUPPORT__)
#define MMI_DQ_FS_FP_MAX_NUM 30
mmi_fs_fp g_dq_fs_fp[MMI_DQ_FS_FP_MAX_NUM];
#endif

#ifdef __LOCK_RFID_CARD_SUPPORT__
#define MMI_DQ_FS_RFID_MAX_NUM 10
mmi_fs_rfid g_dq_fs_rfid[MMI_DQ_FS_RFID_MAX_NUM];
#endif

#define FP_ADMIN_NUM 2
#define FP_110_NUM 3

#define PWD_ADMIN_NUM 1
#define PWD_110_NUM 1

static void mmi_dq_fds_read(mid_fds_file_id file, uint8_t *r_data, uint16_t r_size)
{
	uint16_t i;

	switch (file)
	{
	case MID_FDS_FILE_SET:
		eeprom_select(0);
		for (i = 0; i < r_size; i++)
		{
			r_data[i] = eeprom_read_byte(0, i); //读第一页
		}
		break;
	case MID_FDS_FILE_PWD:
		eeprom_select(0);
		for (i = 0; i < r_size; i++)
		{
			r_data[i] = eeprom_read_byte(0, i + 24); //读第一页
		}
		break;
#ifdef __LOCK_FP_SUPPORT__
	case MID_FDS_FILE_FP:
		eeprom_select(1);
		eeprom_nvr_read_page(r_data, 0, 0, r_size);
		break;
#endif
#ifdef __LOCK_RFID_CARD_SUPPORT__
	case MID_FDS_FILE_RF:
		eeprom_select(1);
		eeprom_nvr_read_page(r_data, 1, 0, r_size);
		break;
#endif
#ifdef __LOCK_DECODE_SUPPORT__
	case MID_FDS_FILE_DECODE:
		eeprom_select(0);
		for (i = 0; i < r_size; i++)
		{
			r_data[i] = eeprom_read_byte(0, i + 532); //读第一页
		}
		break;
#endif
	default:
		break;
	}
}

static RET_VAL mmi_dq_fds_write(mid_fds_file_id file, uint8_t *w_data, uint16_t w_size)
{
	uint16_t i;
	ErrStatus ret;
	eeprom_erase_time(9);
	switch (file)
	{
	case MID_FDS_FILE_SET:
	{
		uint8_t *w_data2 = (uint8_t *)g_dq_fs_pwd;
		uint16_t w_size2 = sizeof(mmi_fs_pwd) * MMI_DQ_FS_PWD_MAX_NUM;
		eeprom_select(0);
		eeprom_erase_page(0); //擦除1K
		for (i = 0; i < w_size; i++)
		{
			ret = eeprom_write_byte(0, i, w_data[i]); //读第一页
			if (ret == ERROR)
			{
				//printf("mmi_dq_fds_write  error  %d\n",i);
				return RET_FAIL;
			}
		}
		for (i = 0; i < w_size2; i++)
		{
			ret = eeprom_write_byte(0, i + 24, w_data2[i]); //读第一页
			if (ret == ERROR)
			{
				//printf("mmi_dq_fds_write  error  %d\n",i);
				return RET_FAIL;
			}
		}
	}
	break;
	case MID_FDS_FILE_PWD:
	{
		uint8_t *w_data2 = (uint8_t *)&g_dq_fs_init_set;
		uint16_t w_size2 = sizeof(mmi_fs_setting);
		eeprom_select(0);
		eeprom_erase_page(0); //擦除1K
		for (i = 0; i < w_size2; i++)
		{
			ret = eeprom_write_byte(0, i, w_data2[i]); //读第一页
			if (ret == ERROR)
			{
				//printf("mmi_dq_fds_write  error  %d\n",i);
				return RET_FAIL;
			}
		}
		for (i = 0; i < w_size; i++)
		{
			ret = eeprom_write_byte(0, i + 24, w_data[i]); //读第一页
			if (ret == ERROR)
			{
				//printf("mmi_dq_fds_write  error  %d\n",i);
				return RET_FAIL;
			}
		}
	}
	break;
#ifdef __LOCK_FP_SUPPORT__
	case MID_FDS_FILE_FP:
		eeprom_select(1);
		eeprom_erase_page(0); //擦除512byte
		for (i = 0; i < w_size; i++)
		{
			ret = eeprom_write_byte(0, i, w_data[i]);
			if (ret == ERROR)
			{
				//printf("mmi_dq_fds_write  error  %d\n",i);
				return RET_FAIL;
			}
		}
		break;
#endif
#ifdef __LOCK_RFID_CARD_SUPPORT__
	case MID_FDS_FILE_RF:
		eeprom_select(1);
		eeprom_erase_page(1); //擦除512byte
		for (i = 0; i < w_size; i++)
		{
			ret = eeprom_write_byte(1, i, w_data[i]);
			if (ret == ERROR)
			{
				//printf("mmi_dq_fds_write  error  %d\n",i);
				return RET_FAIL;
			}
		}
		break;
#endif
#ifdef __LOCK_DECODE_SUPPORT__
	case MID_FDS_FILE_DECODE:
	{
		uint8_t *w_data2 = (uint8_t *)&g_dq_fs_init_set;
		uint16_t w_size2 = sizeof(mmi_fs_setting);
		uint8_t *w_data3 = (uint8_t *)g_dq_fs_pwd;
		uint16_t w_size3 = sizeof(mmi_fs_pwd) * MMI_DQ_FS_PWD_MAX_NUM;
		eeprom_select(0);
		eeprom_erase_page(0); //擦除1K
		for (i = 0; i < w_size2; i++)
		{
			ret = eeprom_write_byte(0, i, w_data2[i]); //读第一页
			if (ret == ERROR)
			{
				//printf("mmi_dq_fds_write  error  %d\n",i);
				return RET_FAIL;
			}
		}
		for (i = 0; i < w_size3; i++)
		{
			ret = eeprom_write_byte(0, i + 24, w_data3[i]); //读第一页
			if (ret == ERROR)
			{
				//printf("mmi_dq_fds_write  error  %d\n",i);
				return RET_FAIL;
			}
		}
		for (i = 0; i < w_size; i++)
		{
			ret = eeprom_write_byte(0, i + 532, w_data[i]); //读第一页
			if (ret == ERROR)
			{
				//printf("mmi_dq_fds_write  error  %d\n",i);
				return RET_FAIL;
			}
		}
	}
	break;
#endif
	default:
		return RET_FAIL;
	}
	//printf("mmi_dq_fds_write  suc\n");
	return RET_SUCESS;
}

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_fs_init(void)
{
	mmi_dq_fds_read(MID_FDS_FILE_SET, (unsigned char *)&g_dq_fs_init_set, sizeof(mmi_fs_setting));
	if (FDS_INIT_LOCK_SUC == g_dq_fs_init_set.init_flag || FDS_INIT_APP_SUC == g_dq_fs_init_set.init_flag)
	{
		unsigned char i = 0;
		mmi_dq_fds_read(MID_FDS_FILE_PWD, (unsigned char *)g_dq_fs_pwd, sizeof(mmi_fs_pwd) * MMI_DQ_FS_PWD_MAX_NUM);
#ifdef __LOCK_FP_SUPPORT__
		mmi_dq_fds_read(MID_FDS_FILE_FP, (unsigned char *)g_dq_fs_fp, sizeof(mmi_fs_fp) * MMI_DQ_FS_FP_MAX_NUM);
#endif
#ifdef __LOCK_RFID_CARD_SUPPORT__
		mmi_dq_fds_read(MID_FDS_FILE_RF, (unsigned char *)g_dq_fs_rfid, sizeof(mmi_fs_rfid) * MMI_DQ_FS_RFID_MAX_NUM);
#endif
		if (g_dq_fs_init_set.admin_status > 0)
		{
			for (; i < MMI_DQ_FS_PWD_MAX_NUM; i++)
			{
				if (g_dq_fs_pwd[i].flag == FDS_USE_TYPE_ADMIN)
					break;
			}
			if (i >= MMI_DQ_FS_PWD_MAX_NUM)
			{
				g_dq_fs_init_set.admin_status = 0;
				mmi_dq_fds_write(MID_FDS_FILE_SET, (unsigned char *)&g_dq_fs_init_set, sizeof(mmi_fs_setting));
			}
		}
	}
	else
	{
		//printf("mmi_dq_fs_init init error");
		memset(g_dq_fs_pwd, 0xFF, sizeof(g_dq_fs_pwd));
		mmi_dq_fds_write(MID_FDS_FILE_PWD, (unsigned char *)g_dq_fs_pwd, sizeof(mmi_fs_pwd) * MMI_DQ_FS_PWD_MAX_NUM);

#ifdef __LOCK_FP_SUPPORT__
		memset(g_dq_fs_fp, 0xFF, sizeof(g_dq_fs_fp));
		mmi_dq_fds_write(MID_FDS_FILE_FP, (unsigned char *)g_dq_fs_fp, sizeof(mmi_fs_fp) * MMI_DQ_FS_FP_MAX_NUM);

		mmi_dq_fp_empty();
#endif
#ifdef __LOCK_RFID_CARD_SUPPORT__
		memset(g_dq_fs_rfid, 0xFF, sizeof(g_dq_fs_rfid));
		mmi_dq_fds_write(MID_FDS_FILE_RF, (unsigned char *)g_dq_fs_rfid, sizeof(mmi_fs_rfid) * MMI_DQ_FS_RFID_MAX_NUM);
#endif
		g_dq_fs_init_set.init_flag = FDS_INIT_LOCK_SUC;
		g_dq_fs_init_set.open_pro_sound = 1;
		g_dq_fs_init_set.open_mode = SYS_OPEN_MODE_SIN;
		g_dq_fs_init_set.admin_status = 0;
		g_dq_fs_init_set.factory_flag = 0;
		g_dq_fs_init_set.wifi_flag = 0;
		mmi_dq_fds_write(MID_FDS_FILE_SET, (unsigned char *)&g_dq_fs_init_set, sizeof(mmi_fs_setting));
	}
}

/**
  * @brief  手动初始化
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
RET_VAL mmi_dq_fs_clr_set(void)
{
	g_dq_fs_init_set.open_pro_sound = 1;
	g_dq_fs_init_set.open_mode = SYS_OPEN_MODE_SIN;

	return mmi_dq_fds_write(MID_FDS_FILE_SET, (unsigned char *)&g_dq_fs_init_set, sizeof(mmi_fs_setting));
}

/**
  * @brief  复位初始化
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
RET_VAL mmi_dq_fs_reset(void)
{
	memset(g_dq_fs_pwd, 0xFF, sizeof(g_dq_fs_pwd));
	mmi_dq_fds_write(MID_FDS_FILE_PWD, (unsigned char *)g_dq_fs_pwd, sizeof(mmi_fs_pwd) * MMI_DQ_FS_PWD_MAX_NUM);
#ifdef __LOCK_FP_SUPPORT__
	memset(g_dq_fs_fp, 0xFF, sizeof(g_dq_fs_fp));
	mmi_dq_fds_write(MID_FDS_FILE_FP, (unsigned char *)g_dq_fs_fp, sizeof(mmi_fs_fp) * MMI_DQ_FS_FP_MAX_NUM);

	mmi_dq_fp_empty();
#endif
#ifdef __LOCK_RFID_CARD_SUPPORT__
	memset(g_dq_fs_rfid, 0xFF, sizeof(g_dq_fs_rfid));
	mmi_dq_fds_write(MID_FDS_FILE_RF, (unsigned char *)g_dq_fs_rfid, sizeof(mmi_fs_rfid) * MMI_DQ_FS_RFID_MAX_NUM);
#endif
	g_dq_fs_init_set.init_flag = FDS_INIT_LOCK_SUC;
	g_dq_fs_init_set.open_pro_sound = 1;
	g_dq_fs_init_set.open_mode = SYS_OPEN_MODE_SIN;
	g_dq_fs_init_set.admin_status = 0;
	g_dq_fs_init_set.wifi_flag = 0;
	return mmi_dq_fds_write(MID_FDS_FILE_SET, (unsigned char *)&g_dq_fs_init_set, sizeof(mmi_fs_setting));
}

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_fs_pwd_string_to_byte(unsigned char *input_pwd, unsigned char pwd_len, unsigned char *output_pwd)
{
	unsigned char i = 0;
	unsigned char bit_l = 0;
	unsigned char bit_h = 0;

	for (i = 0; i < pwd_len; i++)
	{
		bit_l = *(input_pwd + i) & 0x0F;
		i++;
		if (i < pwd_len)
			bit_h = *(input_pwd + i) & 0x0F;
		else
			bit_h = 0xF;
		*output_pwd++ = bit_l << 4 | bit_h;
	}
	return;
}
/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_fs_pwd_byte_to_string(unsigned char *input_pwd, unsigned char *output_pwd)
{
	unsigned char i = 0;
	unsigned char pwd = 0;
	unsigned char len = 0;
	for (i = 0; i < 4; i++)
	{
		pwd = *(input_pwd + i);
		if (pwd == 0xFF)
			break;
		else
		{
			*output_pwd++ = (pwd & 0xF0) >> 4;
			len++;
		}
		if ((pwd & 0x0F) == 0x0F)
			break;
		else
		{
			*output_pwd++ = pwd & 0x0F;
			len++;
		}
	}
	return len;
}

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_fs_get_pwd_unuse_index(void)
{
	unsigned char i = PWD_ADMIN_NUM;
#ifdef __LOCK_110_SUPPORT__
	i += PWD_110_NUM;
#endif
	for (; i < MMI_DQ_FS_PWD_MAX_NUM; i++)
	{
		if (g_dq_fs_pwd[i].flag == 0xFF)
			break;
	}

	if (i < MMI_DQ_FS_PWD_MAX_NUM)
		return i;
	else
		return 0xFF;
}

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_fs_check_input_pwd(unsigned char *input_pwd, unsigned char len, fds_use_type type)
{
	unsigned char i = 0;
	unsigned char k = 0;
	unsigned char password[4];
	unsigned char ret_val = 0xFF;

	memset(password, 0xFF, sizeof(password));
	mmi_dq_fs_pwd_string_to_byte(input_pwd, len, password);

	for (i = 0; i < MMI_DQ_FS_PWD_MAX_NUM; i++)
	{
		if (g_dq_fs_pwd[i].flag != 0xFF)
		{
			for (k = 0; k < 4; k++)
			{
				if (password[k] != g_dq_fs_pwd[i].key_pwd[k])
					break;
			}
			if (k == 4)
			{
				break;
			}
		}
	}
	if (i < MMI_DQ_FS_PWD_MAX_NUM)
	{
		if ((g_dq_fs_pwd[i].flag == type) || (type == FDS_USE_TYPE_ALL))
			ret_val = i;
		else
			ret_val = 0xFF;
	}
	else
		ret_val = 0xFF;

	return ret_val;
}

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_fs_check_input_pwd_for_open(unsigned char *input_pwd, unsigned char len)
{
	unsigned char i = 0, n = 0;
	unsigned char k, j;
	unsigned char password[8];
	unsigned char passlen = 0;
	unsigned char ret_val = 0xFF;

	for (i = 0; i < MMI_DQ_FS_PWD_MAX_NUM; i++)
	{
		if (g_dq_fs_pwd[i].flag == FDS_USE_TYPE_INVALID)
			continue;
		memset(password, 0xFF, sizeof(password));
		passlen = mmi_dq_fs_pwd_byte_to_string(g_dq_fs_pwd[i].key_pwd, password);
		for (k = 0; k + passlen <= len; k++)
		{
			for (j = 0; j < passlen; j++)
			{
				if (password[j] != input_pwd[k + j])
					break;
			}
			if (j == passlen)
				break;
		}
		if (j == passlen)
			break;
	}
	if (i < MMI_DQ_FS_PWD_MAX_NUM)
	{
		//printf("check input return i: %d",(unsigned int)i);
		get_index = i;
		return i;
	}
	else
	{
		unsigned char adminword[8];
		unsigned char checkCode_out[8];
		unsigned char pass = 0;
		memset(adminword, 0xFF, sizeof(adminword));
		passlen = mmi_dq_fs_pwd_byte_to_string(g_dq_fs_pwd[0].key_pwd, adminword);
		for (i = 0; i < 8; i++)
		{
			if (adminword[i] == 0xFF)
				adminword[i] = 0;
			else
				adminword[i] += '0';

			if (input_pwd[i] == 0xFF)
				password[i] = 0;
			else
				password[i] = input_pwd[i] + '0';
		}
		pass = dq_check_otp((char *)password, (char *)adminword, g_dq_fs_init_set.check_data, checkCode_out);
		if (pass > 0)
		{
			memcpy(g_dq_fs_init_set.check_data, checkCode_out, 8);
			mmi_dq_fds_write(MID_FDS_FILE_SET, (unsigned char *)&g_dq_fs_init_set, sizeof(mmi_fs_setting));
			return 0xFE;
		}
	}
	//printf("check input return 0xFF");
	return 0xFF;
}

/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_fs_set_pwd(unsigned char *pwd, unsigned char pwd_size, fds_use_type type)
{
	unsigned char i = 0;
	unsigned char password[4];

	if (type == FDS_USE_TYPE_ADMIN)
		i = 0;
#ifdef __LOCK_110_SUPPORT__
	else if (type == FDS_USE_TYPE_110)
		i = 1;
#endif
	else
	{
#ifdef __LOCK_110_SUPPORT__
		i = PWD_ADMIN_NUM + PWD_110_NUM;
#else
		i = PWD_ADMIN_NUM;
#endif
		for (; i < MMI_DQ_FS_PWD_MAX_NUM; i++)
		{
			if (g_dq_fs_pwd[i].flag == 0xFF)
				break;
		}
	}

	if (i < MMI_DQ_FS_PWD_MAX_NUM)
	{
		get_index = i;
		memset(password, 0xFF, sizeof(password));
		//g_dq_fs_pwd[i].index = i;
		mmi_dq_fs_pwd_string_to_byte(pwd, pwd_size, password);
		memcpy((char *)g_dq_fs_pwd[i].key_pwd, (const char *)password, 4);
		g_dq_fs_pwd[i].flag = type;
		return mmi_dq_fds_write(MID_FDS_FILE_PWD, (unsigned char *)g_dq_fs_pwd, sizeof(mmi_fs_pwd) * MMI_DQ_FS_PWD_MAX_NUM);
	}
	return RET_FAIL;
}

/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_fs_del_pwd(unsigned char index, fds_use_type type)
{
	if (index < MMI_DQ_FS_PWD_MAX_NUM && g_dq_fs_pwd[index].flag == type)
	{
		g_dq_fs_pwd[index].flag = FDS_USE_TYPE_INVALID;
		//g_dq_fs_pwd[index].index = 0xFF;
		memset(g_dq_fs_pwd[index].key_pwd, 0xFF, sizeof(g_dq_fs_pwd[index].key_pwd));
		return mmi_dq_fds_write(MID_FDS_FILE_PWD, (unsigned char *)g_dq_fs_pwd, sizeof(mmi_fs_pwd) * MMI_DQ_FS_PWD_MAX_NUM);
	}
	return RET_FAIL;
}

/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_fs_clr_pwd(void)
{
	unsigned char i = PWD_ADMIN_NUM;
#ifdef __LOCK_110_SUPPORT__
	i += PWD_110_NUM;
#endif
	for (; i < MMI_DQ_FS_PWD_MAX_NUM; i++)
	{
		if (g_dq_fs_pwd[i].flag == FDS_USE_TYPE_USER)
		{
			g_dq_fs_pwd[i].flag = FDS_USE_TYPE_INVALID;
			//g_dq_fs_pwd[i].index = 0xFF;
			memset(g_dq_fs_pwd[i].key_pwd, 0xFF, sizeof(g_dq_fs_pwd[i].key_pwd));
		}
	}
	return mmi_dq_fds_write(MID_FDS_FILE_PWD, (unsigned char *)g_dq_fs_pwd, sizeof(mmi_fs_pwd) * MMI_DQ_FS_PWD_MAX_NUM);
}

#if defined(__LOCK_DECODE_SUPPORT__)
/**
  * @brief  解码记录flash
  * @param  type 用户类型
  * @return status
  * @note   none
  * @see    none
  */
RET_VAL mmi_dq_fs_set_decode(fds_use_type type)
{
	if (type == FDS_USE_TYPE_ADMIN)
		return mmi_dq_fds_write(MID_FDS_FILE_DECODE, (unsigned char *)&get_decode, sizeof(get_decode));
	else
		return RET_FAIL;
}

// unsigned char mmi_dq_fs_check_input_decode(unsigned char *input_pwd, unsigned char len, fds_use_type type)
// {
// 	unsigned char i = 0;
// 	unsigned char k = 0;
// 	unsigned char decode[5];
// 	unsigned char ret_val = 0xFF;

// 	memset(decode, 0xFF, sizeof(decode));
// 	mmi_dq_fs_pwd_string_to_byte(input_pwd, len, decode);

// 	for (i = 0; i < MMI_DQ_FS_DECODE_MAX_NUM; i++)
// 	{
// 		if (g_dq_fs_decode[i].flag != 0xFF)
// 		{
// 			for (k = 0; k < 5; k++)
// 			{
// 				if (decode[k] != g_dq_fs_decode[i].decode[k])
// 					break;
// 			}
// 			if (k == 5)
// 			{
// 				break;
// 			}
// 		}
// 	}
// 	if (i < MMI_DQ_FS_DECODE_MAX_NUM)
// 	{
// 		if ((g_dq_fs_decode[i].flag == type) || (type == FDS_USE_TYPE_ADMIN))
// 			ret_val = i;
// 		else
// 			ret_val = 0xFF;
// 	}
// 	else
// 		ret_val = 0xFF;

// 	return ret_val;
// }

// RET_VAL mmi_dq_fs_del_decode(unsigned char index, fds_use_type type)
// {
// 	if (index < MMI_DQ_FS_DECODE_MAX_NUM && g_dq_fs_decode[index].flag == type)
// 	{
// 		g_dq_fs_decode[index].flag = FDS_USE_TYPE_INVALID;
// 		//g_dq_fs_pwd[index].index = 0xFF;
// 		memset(g_dq_fs_decode[index].decode, 0xFF, sizeof(g_dq_fs_decode[index].decode));
// 		return mmi_dq_fds_write(MID_FDS_FILE_DECODE, (unsigned char *)g_dq_fs_decode, sizeof(mmi_fs_decode) * MMI_DQ_FS_DECODE_MAX_NUM);
// 	}
// 	return RET_FAIL;
// }

// RET_VAL mmi_dq_fs_clr_decode(void)
// {
// 	unsigned char i = 0;

// 	for (; i < MMI_DQ_FS_DECODE_MAX_NUM; i++)
// 	{
// 		if (g_dq_fs_decode[i].flag == FDS_USE_TYPE_ADMIN)
// 		{
// 			g_dq_fs_decode[i].flag = FDS_USE_TYPE_INVALID;
// 			// g_dq_fs_pwd[i].index = 0xFF;
// 			memset(g_dq_fs_decode[i].decode, 0xFF, sizeof(g_dq_fs_decode[i].decode));
// 		}
// 	}

// 	return mmi_dq_fds_write(MID_FDS_FILE_DECODE, (unsigned char *)g_dq_fs_decode, sizeof(mmi_fs_decode) * MMI_DQ_FS_DECODE_MAX_NUM);
// }

#endif

#if defined(__LOCK_FP_SUPPORT__)
/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_fs_get_fp_unuse_index(void)
{
	unsigned char i = FP_ADMIN_NUM;
#ifdef __LOCK_110_SUPPORT__
	i += FP_110_NUM;
#endif
	for (; i < MMI_DQ_FS_FP_MAX_NUM; i++)
	{
		if (g_dq_fs_fp[i].fp_index == 0xFF)
			break;
	}
	if (i >= MMI_DQ_FS_FP_MAX_NUM)
		return 0xFF;
	return i;
}

#ifdef __LOCK_110_SUPPORT__
/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_fs_get_fp_110_unuse_index(void)
{
	unsigned char i = FP_ADMIN_NUM;
	unsigned char j = 0;

	for (; j < FP_110_NUM; j++)
	{
		if (g_dq_fs_fp[i + j].fp_index == 0xFF)
			break;
	}
	if (j >= FP_110_NUM)
		return 0xFF;
	return i + j;
}
#endif

/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_fs_check_fp(unsigned char fp_index, fds_use_type type)
{
	if ((fp_index < MMI_DQ_FS_FP_MAX_NUM) && (g_dq_fs_fp[fp_index].fp_index == fp_index) && ((g_dq_fs_fp[fp_index].flag == type) || (type == FDS_USE_TYPE_ALL)))
		return RET_SUCESS;
	else
		return RET_FAIL;
}

/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_fs_set_fp(unsigned char fs_index, fds_use_type type)
{
	g_dq_fs_fp[fs_index].fp_index = fs_index;
	g_dq_fs_fp[fs_index].flag = type;
	return mmi_dq_fds_write(MID_FDS_FILE_FP, (unsigned char *)g_dq_fs_fp, sizeof(mmi_fs_fp) * MMI_DQ_FS_FP_MAX_NUM);
}

/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_fs_del_fp(unsigned char fp_index, fds_use_type type)
{
	if (mmi_dq_fs_check_fp(fp_index, type) == RET_SUCESS)
	{
		g_dq_fs_fp[fp_index].flag = FDS_USE_TYPE_INVALID;
		g_dq_fs_fp[fp_index].fp_index = 0xFF;
		return mmi_dq_fds_write(MID_FDS_FILE_FP, (unsigned char *)g_dq_fs_fp, sizeof(mmi_fs_fp) * MMI_DQ_FS_FP_MAX_NUM);
	}
	return RET_FAIL;
}

/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_fs_clr_fp(void)
{
	unsigned char i = FP_ADMIN_NUM;
	unsigned short fp_ret = 0;
#ifdef __LOCK_110_SUPPORT__
	i += FP_110_NUM;
#endif
	for (; i < MMI_DQ_FS_FP_MAX_NUM; i++)
	{
		if (g_dq_fs_fp[i].fp_index != 0xFF)
		{
			fp_ret = mmi_dq_fp_delete(g_dq_fs_fp[i].fp_index);
			if (fp_ret == 0)
			{
				g_dq_fs_fp[i].flag = FDS_USE_TYPE_INVALID;
				g_dq_fs_fp[i].fp_index = 0xFF;
			}
		}
	}
	return mmi_dq_fds_write(MID_FDS_FILE_FP, (unsigned char *)g_dq_fs_fp, sizeof(mmi_fs_fp) * MMI_DQ_FS_FP_MAX_NUM);
}

#endif

#ifdef __LOCK_RFID_CARD_SUPPORT__

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_fs_get_rfid_unuse_index(void)
{
	unsigned char i = 0;

	for (i = 0; i < MMI_DQ_FS_RFID_MAX_NUM; i++)
	{
		if (g_dq_fs_rfid[i].index == 0xFF)
			break;
	}

	if (i >= MMI_DQ_FS_RFID_MAX_NUM)
		return 0xFF;
	return i;
}

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_fs_check_rfid(unsigned char *sec_data, fds_use_type type)
{
	unsigned char i = 0, j = 0;

	for (i = 0; i < MMI_DQ_FS_RFID_MAX_NUM; i++)
	{
		for (j = 0; j < RFID_SEC_DATA_LEN; j++)
		{
			if (g_dq_fs_rfid[i].sec_data[j] != sec_data[j])
				break;
		}
		if (j == RFID_SEC_DATA_LEN)
			break;
	}
	if (i < MMI_DQ_FS_RFID_MAX_NUM && ((g_dq_fs_rfid[i].flag == type) || (type == FDS_USE_TYPE_ALL)))
	{
		return i;
	}
	else
	{
		return 0xFF;
	}
}

/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_fs_set_rfid(unsigned char *sec_data, fds_use_type type)
{
	unsigned char i = 0, j = 0;
	for (i = 0; i < MMI_DQ_FS_RFID_MAX_NUM; i++)
	{
		if (g_dq_fs_rfid[i].index == 0xFF)
			break;
	}
	if (i < MMI_DQ_FS_RFID_MAX_NUM)
	{
		get_index = i;
		g_dq_fs_rfid[i].index = i;
		g_dq_fs_rfid[i].flag = type;
		for (j = 0; j < RFID_SEC_DATA_LEN; j++)
		{
			g_dq_fs_rfid[i].sec_data[j] = sec_data[j];
		}
		return mmi_dq_fds_write(MID_FDS_FILE_RF, (unsigned char *)g_dq_fs_rfid, sizeof(mmi_fs_rfid) * MMI_DQ_FS_RFID_MAX_NUM);
	}
	return RET_FAIL;
}

/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_fs_del_rfid(unsigned char rfid_index)
{
	if (rfid_index < MMI_DQ_FS_RFID_MAX_NUM && g_dq_fs_rfid[rfid_index].index == rfid_index)
	{
		g_dq_fs_rfid[rfid_index].index = 0xFF;
		g_dq_fs_rfid[rfid_index].flag = FDS_USE_TYPE_INVALID;
		memset(g_dq_fs_rfid[rfid_index].sec_data, 0xFF, sizeof(g_dq_fs_rfid[rfid_index].sec_data));
		return mmi_dq_fds_write(MID_FDS_FILE_RF, (unsigned char *)g_dq_fs_rfid, sizeof(mmi_fs_rfid) * MMI_DQ_FS_RFID_MAX_NUM);
	}
	return RET_FAIL;
}

/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_fs_clr_rfid(void)
{
	unsigned char i = 0;

	for (i = 0; i < MMI_DQ_FS_RFID_MAX_NUM; i++)
	{
		g_dq_fs_rfid[i].flag = FDS_USE_TYPE_INVALID;
		g_dq_fs_rfid[i].index = 0xFF;
		memset(g_dq_fs_rfid[i].sec_data, 0xFF, sizeof(g_dq_fs_rfid[i].sec_data));
	}
	return mmi_dq_fds_write(MID_FDS_FILE_RF, (unsigned char *)g_dq_fs_rfid, sizeof(mmi_fs_rfid) * MMI_DQ_FS_RFID_MAX_NUM);
}

#endif

#ifdef __LOCK_DECODE_SUPPORT__
/**
  * @brief  检查发flash是否为空
  * @param  none
  * @return status
  * @note   none
  * @see    none
  */
unsigned char mmi_dq_fs_get_decode_unuse_index(void)
{
	unsigned char i;
	unsigned char getdata[66];

	memset(&getdata, 0xff, sizeof(getdata));
	mmi_dq_fds_read(MID_FDS_FILE_DECODE, getdata, 66);

	// dqiot_drv_uart0A_init();
	// for (i = 0; i < 66; i++)
	// 	printf("getdata is %d\n", (int)getdata[i]);
	// dqiot_drv_uart0B_init();

	for (i = 0; i < 66; i++)
	{
		if (getdata[i] == 0xFF)
			return 0;
	}

	return 0xFF;
}
#endif

/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_fs_set_open_mode(sys_open_mode mode)
{
	if (g_dq_fs_init_set.open_mode == mode)
		return RET_SUCESS;

	g_dq_fs_init_set.open_mode = mode;
	return mmi_dq_fds_write(MID_FDS_FILE_SET, (unsigned char *)&g_dq_fs_init_set, sizeof(mmi_fs_setting));
}
/*
parameter: 
	none
return :
	none
*/
sys_open_mode mmi_dq_fs_get_open_mode(void)
{
	return g_dq_fs_init_set.open_mode;
}

/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_fs_set_pro_sound(unsigned char flag)
{
	if (g_dq_fs_init_set.open_pro_sound == flag)
		return RET_SUCESS;

	g_dq_fs_init_set.open_pro_sound = flag;
	return mmi_dq_fds_write(MID_FDS_FILE_SET, (unsigned char *)&g_dq_fs_init_set, sizeof(mmi_fs_setting));
}

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_fs_get_pro_sound_state(void)
{
	return g_dq_fs_init_set.open_pro_sound;
}

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_fs_get_init_flag(void)
{
	return g_dq_fs_init_set.init_flag;
}

/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_fs_set_init_flag(unsigned char flag)
{
	g_dq_fs_init_set.init_flag = flag;
	return mmi_dq_fds_write(MID_FDS_FILE_SET, (unsigned char *)&g_dq_fs_init_set, sizeof(mmi_fs_setting));
}

/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_fs_set_factory_flag(unsigned char flag)
{
	g_dq_fs_init_set.factory_flag = flag;
	return mmi_dq_fds_write(MID_FDS_FILE_SET, (unsigned char *)&g_dq_fs_init_set, sizeof(mmi_fs_setting));
}

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_fs_get_factory_flag(void)
{
	return g_dq_fs_init_set.factory_flag;
}

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_fs_get_admin_status(void)
{
	return g_dq_fs_init_set.admin_status;
}

/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_fs_set_admin_status(unsigned char status)
{
	g_dq_fs_init_set.admin_status = status;
	return mmi_dq_fds_write(MID_FDS_FILE_SET, (unsigned char *)&g_dq_fs_init_set, sizeof(mmi_fs_setting));
}

#if 0
/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_fs_set_wifi_setting(unsigned char flag)
{
	g_dq_fs_init_set.wifi_flag = flag;
	return mmi_dq_fds_write(MID_FDS_FILE_SET, (unsigned char *)&g_dq_fs_init_set, sizeof(mmi_fs_setting));
}

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_fs_get_wifi_setting(void)
{
	return g_dq_fs_init_set.wifi_flag;
}
#endif

/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_fs_set_business_flag(unsigned char flag)
{
#if 1
	if (flag != g_dq_fs_init_set.business_flag)
	{
		g_dq_fs_init_set.business_flag = flag;
		return mmi_dq_fds_write(MID_FDS_FILE_SET, (unsigned char *)&g_dq_fs_init_set, sizeof(mmi_fs_setting));
	}
#else
	g_dq_fs_init_set.business_flag = flag;
#endif
	return RET_SUCESS;
}

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_fs_get_business_flag(void)
{
	return g_dq_fs_init_set.business_flag;
}

/************************************************************************************
 * 							     	 Own function							        *
 ************************************************************************************/
#ifdef __LOCK_VIRTUAL_PASSWORD__
#ifdef __LOCK_VIRTUAL_PASSWORD__
uint8_t input_empty_pwd_len = 0;
unsigned char mmi_dq_fs_check_input_pwd_from_app(unsigned char *input_pwd, unsigned char len)
{
	unsigned char ret_val = 0xFF;
	unsigned char admin_pwd[4];
	unsigned char admin_password[8];
	uint8_t admin_len = 0;
	uint8_t i, k;

#ifdef __LOCK_USE_MALLOC__
	uint8_t ret;
	g_dq_fs_pwd = (mmi_fs_pwd *)mmi_dq_fs_get_storage(DQ_FS_MEM_PWD, &ret);
#endif

	memset(admin_password, 0xFF, 8);
	for (i = 0; i < MMI_DQ_FS_PWD_MAX_NUM; i++)
	{
		if (g_dq_fs_pwd[i].flag != 0xFF && g_dq_fs_pwd[i].flag == FDS_USE_TYPE_ADMIN)
		{
			for (k = 0; k < 4; k++)
			{
				admin_pwd[k] = g_dq_fs_pwd[i].key_pwd[k];
			}
			break;
		}
	}

#ifdef __LOCK_USE_MALLOC__
	mmi_dq_fs_free_storage(DQ_FS_MEM_PWD, (void **)&g_dq_fs_pwd);
#endif

	mmi_dq_fs_pwd_byte_to_string(admin_pwd, admin_password);
	for (i = 0; i < 8; i++)
	{
		if (admin_password[i] == 0xFF)
			break;
	}
	admin_len = i;
	if (len >= admin_len)
	{
		for (i = 0; i <= len - admin_len; i++)
		{
			for (k = 0; k < admin_len; k++)
			{
				if (input_pwd[i + k] != admin_password[k])
					break;
			}

			if (k == admin_len)
			{
				dq_otp_add_temp_open_log(0, DQ_OPEN_LOG_ADMIN_PASSWORD, admin_pwd, 4);
				mmi_dq_fs_check_input_pwd_from_app_cb(1);
				return 0;
			}
		}
	}

	if (len == 8)
		input_empty_pwd_len = 1;
	else
		input_empty_pwd_len = 0;

	for (i = 9; i >= 6; i--)
	{
		if (len < i)
			continue;
		for (k = 0; k <= len - i; k++)
		{
			unsigned char password[5];
			memset(password, 0xFF, sizeof(password));
			mmi_dq_fs_pwd_string_to_byte(input_pwd + k, i, password);
			ret_val = dq_otp_check_password_for_open(password, i);
			if (ret_val != 0)
			{
				return 0;
			}
		}
	}

	//	mmi_dq_ms_idle_input_with_app_result(0xFF);

	return 0;
}
#else
unsigned char mmi_dq_fs_check_input_pwd_from_app(unsigned char *input_pwd, unsigned char len)
{
	unsigned char password[5];
	unsigned char ret_val = 0xFF;

	memset(password, 0xFF, sizeof(password));
	mmi_dq_fs_pwd_string_to_byte(input_pwd, len, password);

	if (len <= MMI_KEY_MAX_INPUT_NUM)
	{
		ret_val = mmi_dq_fs_check_input_pwd(input_pwd, len, (fds_pwd_type)FDS_USE_TYPE_ADMIN);
		if (ret_val != 0xFF)
		{
			ret_val = 1;
			dq_otp_add_temp_open_log(0, DQ_OPEN_LOG_ADMIN_PASSWORD, password, 5);
			mmi_dq_fs_check_input_pwd_from_app_cb(ret_val);
			return 0;
		}
	}

	dq_otp_check_password_for_open(password, len);

	return 0;
}
#endif

//extern void mmi_dq_ms_idle_input_with_app_result(unsigned char ret_val);
void mmi_dq_fs_check_input_pwd_from_app_cb(unsigned char ret_val)
{
	if (ret_val != 1 && ret_val != 2 && ret_val != 4 && ret_val != 5 && ret_val != 6)
		ret_val = 0xFF;

	if (ret_val != 0xFF && ret_val != 4 && ret_val != 6)
		printfS("mmi_dq_fs_check_input_pwd_from_app", "right");
	else
		printfS("mmi_dq_fs_check_input_pwd_from_app", "wrong");

#ifdef __LOCK_VIRTUAL_PASSWORD__1

		// if (ret_val != 0xFF)
		// 	mmi_dq_ms_idle_input_with_app_result(ret_val);
#else
	// mmi_dq_ms_idle_input_with_app_result(ret_val);
#endif
}

unsigned char mmi_dq_fs_app_init_sucess(void)
{
	if (g_dq_fs_init_set.init_flag == FDS_INIT_APP_SUC)
		return 1;
	else
		return 0;
}

uint8_t mmi_dq_fs_check_app_admin_password(unsigned char *password)
{
	uint8_t i, k;
	uint8_t ret_val = 0xFF;
#ifdef __LOCK_USE_MALLOC__
	uint8_t ret = 0;
	g_dq_fs_pwd = (mmi_fs_pwd *)mmi_dq_fs_get_storage(DQ_FS_MEM_PWD, &ret);
#endif
	for (i = 0; i < MMI_DQ_FS_PWD_MAX_NUM; i++)
	{
		if (g_dq_fs_pwd[i].flag != 0xFF)
		{
			for (k = 0; k < 4; k++)
			{
				if (password[k] != g_dq_fs_pwd[i].key_pwd[k])
					break;
			}
			if (k == 4)
			{
				break;
			}
		}
	}
	if (i < MMI_DQ_FS_PWD_MAX_NUM)
	{
		if ((g_dq_fs_pwd[i].flag == FDS_USE_TYPE_ADMIN))
			ret_val = i;
		else
			ret_val = 0xFF;
	}
	else
		ret_val = 0xFF;
#ifdef __LOCK_USE_MALLOC__
	mmi_dq_fs_free_storage(DQ_FS_MEM_PWD, (void **)&g_dq_fs_pwd);
#endif
	return ret_val;
}

void mmi_dq_fs_time_zone_pro(uint32_t *time)
{
	// *time += (g_dq_fs_init_set.e_time_zone - g_dq_fs_init_set.w_time_zone);
}

#endif //__LOCK_VIRTUAL_PASSWORD__1
/************************************************************************************
 * 							     	 End function							        *
 ************************************************************************************/

#endif
