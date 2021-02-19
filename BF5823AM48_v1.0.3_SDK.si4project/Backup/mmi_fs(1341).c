#ifndef __MMI_FS_C__
#define __MMI_FS_C__

#include "mmi_fs.h"
#include "mmi_sys.h"
#include "mcu02_sfr.h"
#include "mcu02_eeprom.h"
#include "string.h"
//#include "stdio.h"


mmi_fs_setting g_dq_fs_init_set;

#define MMI_DQ_FS_PWD_MAX_NUM 100
mmi_fs_pwd 		g_dq_fs_pwd[MMI_DQ_FS_PWD_MAX_NUM];

#if defined(__LOCK_FP_SUPPORT__) 
#define			MMI_DQ_FS_FP_MAX_NUM    	50
mmi_fs_fp		g_dq_fs_fp[MMI_DQ_FS_FP_MAX_NUM];
#endif

#ifdef __LOCK_RFID_CARD_SUPPORT__
#define			MMI_DQ_FS_RFID_MAX_NUM  		10
mmi_fs_rfid		g_dq_fs_rfid[MMI_DQ_FS_RFID_MAX_NUM];
#endif



static void mmi_dq_fds_read(mid_fds_file_id file,  uint8_t* r_data ,uint16_t r_size)
{
	uint16_t i;

	switch(file)
	{
		case MID_FDS_FILE_SET:
			eeprom_select(0);
			for(i = 0; i < r_size; i++)
			{
				r_data[i] = eeprom_read_byte(0,i);//¶ÁµÚÒ»Ò³
			}
			break;
		case MID_FDS_FILE_PWD:
			eeprom_select(0);
			for(i = 0; i < r_size; i++)
			{
				r_data[i] = eeprom_read_byte(0,i+24);//¶ÁµÚÒ»Ò³
			}
			break;
		case MID_FDS_FILE_FP:
			eeprom_select(1);
			eeprom_nvr_read_page(r_data,0,0,r_size);
			break;
		case MID_FDS_FILE_RF:
			eeprom_select(1);
		    eeprom_nvr_read_page(r_data,1,0,r_size);
			break;
		default:
			break;
	}
}

static RET_VAL mmi_dq_fds_write(mid_fds_file_id file, uint8_t* w_data ,uint16_t w_size)
{
	uint16_t i;
    ErrStatus ret;
	eeprom_erase_time(9);
	switch(file)
	{
		case MID_FDS_FILE_SET:
			{
				uint8_t* w_data2 = (uint8_t *)g_dq_fs_pwd;
				uint16_t w_size2 = sizeof(mmi_fs_pwd)*MMI_DQ_FS_PWD_MAX_NUM;
				eeprom_select(0);
				eeprom_erase_page(0);//²Á³ý1K
				for(i = 0; i < w_size; i++)
				{
					ret = eeprom_write_byte(0,i,w_data[i]);//¶ÁµÚÒ»Ò³
					if(ret==ERROR) 
					{
						//printf("mmi_dq_fds_write  error  %d\n",i);
						return RET_FAIL;
					}
				}
				for(i = 0; i < w_size2; i++)
				{
					ret = eeprom_write_byte(0,i+24,w_data2[i]);//¶ÁµÚÒ»Ò³
					if(ret==ERROR) 
					{
						//printf("mmi_dq_fds_write  error  %d\n",i);
						return RET_FAIL;
					}
				}
			}
			break;
		case MID_FDS_FILE_PWD:
			{
				uint8_t* w_data2 = (uint8_t *)&g_dq_fs_init_set;
				uint16_t w_size2 = sizeof(mmi_fs_setting);
				eeprom_select(0);
				eeprom_erase_page(0);//²Á³ý1K
				for(i = 0; i < w_size2; i++)
				{
					ret = eeprom_write_byte(0,i,w_data2[i]);//¶ÁµÚÒ»Ò³
					if(ret==ERROR) 
					{
						//printf("mmi_dq_fds_write  error  %d\n",i);
						return RET_FAIL;
					}
				}
				for(i = 0; i < w_size; i++)
				{
					ret = eeprom_write_byte(0,i+24,w_data[i]);//¶ÁµÚÒ»Ò³
					if(ret==ERROR) 
					{
						//printf("mmi_dq_fds_write  error  %d\n",i);
						return RET_FAIL;
					}
				}
			}
			break;
		case MID_FDS_FILE_FP:
			eeprom_select(1);
			eeprom_erase_page(0);//²Á³ý512byte
			for(i = 0; i < w_size; i++)
			{
				ret = eeprom_write_byte(0,i,w_data[i]);
				if(ret==ERROR) 
				{
					//printf("mmi_dq_fds_write  error  %d\n",i);
					return RET_FAIL;
				}
			}
			break;
		case MID_FDS_FILE_RF:
			eeprom_select(1);
			eeprom_erase_page(1);//²Á³ý512byte
			for(i = 0; i < w_size; i++)
			{
				ret = eeprom_write_byte(1,i,w_data[i]);
				if(ret==ERROR) 
				{
					//printf("mmi_dq_fds_write  error  %d\n",i);
					return RET_FAIL;
				}
			}
			break;
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
	if(FDS_INIT_LOCK_SUC == g_dq_fs_init_set.init_flag || FDS_INIT_APP_SUC == g_dq_fs_init_set.init_flag)
	{
		unsigned char i = 0;
		mmi_dq_fds_read(MID_FDS_FILE_PWD, (unsigned char *)g_dq_fs_pwd, sizeof(mmi_fs_pwd)*MMI_DQ_FS_PWD_MAX_NUM);
		mmi_dq_fds_read(MID_FDS_FILE_FP, (unsigned char *)g_dq_fs_fp, sizeof(mmi_fs_fp)*MMI_DQ_FS_FP_MAX_NUM);
		mmi_dq_fds_read(MID_FDS_FILE_RF, (unsigned char *)g_dq_fs_rfid, sizeof(mmi_fs_rfid)*MMI_DQ_FS_RFID_MAX_NUM);
		if(g_dq_fs_init_set.admin_status > 0)
		{
			for(;i<MMI_DQ_FS_PWD_MAX_NUM;i++)
			{
				if(g_dq_fs_pwd[i].flag == FDS_USE_TYPE_ADMIN)
					break;
			}
			if(i>=MMI_DQ_FS_PWD_MAX_NUM)
			{
				g_dq_fs_init_set.admin_status = 0;
				mmi_dq_fds_write(MID_FDS_FILE_SET, (unsigned char *)&g_dq_fs_init_set, sizeof(mmi_fs_setting));
			}
		}
	}
	else
	{
		//printf("mmi_dq_fs_init init error");
		memset(g_dq_fs_pwd,0xFF,sizeof(g_dq_fs_pwd));
		mmi_dq_fds_write(MID_FDS_FILE_PWD, (unsigned char *)g_dq_fs_pwd, sizeof(mmi_fs_pwd)*MMI_DQ_FS_PWD_MAX_NUM);

		memset(g_dq_fs_fp,0xFF,sizeof(g_dq_fs_fp));
		mmi_dq_fds_write(MID_FDS_FILE_FP, (unsigned char *)g_dq_fs_fp, sizeof(mmi_fs_fp)*MMI_DQ_FS_FP_MAX_NUM);

		memset(g_dq_fs_rfid,0xFF,sizeof(g_dq_fs_rfid));
		mmi_dq_fds_write(MID_FDS_FILE_RF, (unsigned char *)g_dq_fs_rfid, sizeof(mmi_fs_rfid)*MMI_DQ_FS_RFID_MAX_NUM);

		g_dq_fs_init_set.init_flag = FDS_INIT_LOCK_SUC;
		g_dq_fs_init_set.open_pro_sound = 1;
		g_dq_fs_init_set.open_mode = SYS_OPEN_MODE_SIN;
		g_dq_fs_init_set.admin_status = 0;
		g_dq_fs_init_set.factory_flag = 0;
		g_dq_fs_init_set.wifi_flag = 0;
		mmi_dq_fds_write(MID_FDS_FILE_SET, (unsigned char *)&g_dq_fs_init_set, sizeof(mmi_fs_setting));
	}
}




/*
parameter: 
	none
return :
	none
*/
void mmi_dq_fs_pwd_string_to_byte(unsigned char *input_pwd,unsigned char pwd_len,unsigned char *output_pwd)
{
	unsigned char i = 0;
	unsigned char bit_l = 0;
	unsigned char bit_h = 0;

	for(i=0;i<pwd_len;i++)
	{
		bit_l = *(input_pwd+i)&0x0F;
		i++;
		if(i < pwd_len)
			bit_h = *(input_pwd+i)&0x0F;
		else
			bit_h = 0xF;
		*output_pwd++ = bit_l<<4|bit_h;
	}
	return;
}
/*
parameter: 
	none
return :
	none
*/
void mmi_dq_fs_pwd_byte_to_string(unsigned char *input_pwd,unsigned char *output_pwd)
{
	unsigned char i = 0;
	unsigned char pwd = 0;
	for(i=0;i<4;i++)
	{
		pwd = *(input_pwd+i);
		if(pwd == 0xFF)
			break;
		else 
			*output_pwd++ = (pwd&0xF0)>>4;
		if((pwd&0x0F) == 0x0F)
			break;
		else
		{
			*output_pwd++ = pwd&0x0F;
		}
	}
	return;
}

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_fs_get_pwd_unuse_index(void)
{
	unsigned char i = 0;

	for(i=0;i<MMI_DQ_FS_PWD_MAX_NUM;i++)
	{
		if(g_dq_fs_pwd[i].flag == 0xFF)
			break;
	}

	if(i<MMI_DQ_FS_PWD_MAX_NUM)
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
unsigned char mmi_dq_fs_check_input_pwd(unsigned char *input_pwd,unsigned char len,fds_use_type type)
{
	unsigned char i = 0;
	unsigned char k = 0;
	unsigned char password[4];
	unsigned char ret_val = 0xFF;
	
	memset(password,0xFF,sizeof(password));
	mmi_dq_fs_pwd_string_to_byte(input_pwd,len,password);
	
	for(i=0;i<MMI_DQ_FS_PWD_MAX_NUM;i++)
	{
		if(g_dq_fs_pwd[i].flag != 0xFF)
		{
			for(k=0;k<4;k++)
			{
				if(password[k] != g_dq_fs_pwd[i].key_pwd[k])
					break;
			}
			if(k == 4)
			{
				break;
			}
		}
	}
	if(i<MMI_DQ_FS_PWD_MAX_NUM)
	{
		if((g_dq_fs_pwd[i].flag == type)||(type == FDS_USE_TYPE_ALL))
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
RET_VAL mmi_dq_fs_set_pwd(unsigned char *pwd,unsigned char pwd_size,fds_use_type type)
{
	unsigned char i = 0xFF;
	unsigned char password[4];

	if(type == FDS_USE_TYPE_ADMIN)
	{
		for(i=0;i<MMI_DQ_FS_PWD_MAX_NUM;i++)
		{
			if(g_dq_fs_pwd[i].flag == FDS_USE_TYPE_ADMIN)
				break;
		}
	}
	if(i >= MMI_DQ_FS_PWD_MAX_NUM)
	{
		for(i=0;i<MMI_DQ_FS_PWD_MAX_NUM;i++)
		{
			if(g_dq_fs_pwd[i].flag == 0xFF)
				break;
		}
	}
	if(i<MMI_DQ_FS_PWD_MAX_NUM)
	{
		memset(password,0xFF,sizeof(password));
		//g_dq_fs_pwd[i].index = i;
		mmi_dq_fs_pwd_string_to_byte(pwd,pwd_size,password);
		memcpy((char *)g_dq_fs_pwd[i].key_pwd,(const char *)password,4);
		g_dq_fs_pwd[i].flag = type;
		return	mmi_dq_fds_write(MID_FDS_FILE_PWD, (unsigned char *)g_dq_fs_pwd,sizeof(mmi_fs_pwd)*MMI_DQ_FS_PWD_MAX_NUM);
		
	}
	return RET_FAIL;
}

/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_fs_del_pwd(unsigned char index,fds_use_type type)
{
	if(index < MMI_DQ_FS_PWD_MAX_NUM && g_dq_fs_pwd[index].flag == type)
	{
		g_dq_fs_pwd[index].flag = FDS_USE_TYPE_INVALID;
		//g_dq_fs_pwd[index].index = 0xFF;
		memset(g_dq_fs_pwd[index].key_pwd,0xFF,sizeof(g_dq_fs_pwd[index].key_pwd));
		return mmi_dq_fds_write(MID_FDS_FILE_PWD, (unsigned char *)g_dq_fs_pwd,sizeof(mmi_fs_pwd)*MMI_DQ_FS_PWD_MAX_NUM);
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
	unsigned char i = 0;

	for(i=0;i<MMI_DQ_FS_PWD_MAX_NUM;i++)
	{
		if(g_dq_fs_pwd[i].flag == FDS_USE_TYPE_USER)
		{
			g_dq_fs_pwd[i].flag = FDS_USE_TYPE_INVALID;
			//g_dq_fs_pwd[i].index = 0xFF;
			memset(g_dq_fs_pwd[i].key_pwd,0xFF,sizeof(g_dq_fs_pwd[i].key_pwd));
		}
	}
	return mmi_dq_fds_write(MID_FDS_FILE_PWD, (unsigned char *)g_dq_fs_pwd,sizeof(mmi_fs_pwd)*MMI_DQ_FS_PWD_MAX_NUM);
}


#if defined (__LOCK_FP_SUPPORT__)
/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_fs_get_fp_unuse_index(void)
{
	unsigned char i = 2;
	
	for(;i<MMI_DQ_FS_FP_MAX_NUM;i++)
	{
		if(g_dq_fs_fp[i].fp_index == 0xFF)
			break;
	}
	if(i>=MMI_DQ_FS_FP_MAX_NUM)
		return 0xFF;
	return i;
}

/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_fs_check_fp(unsigned short fp_index, fds_use_type type)
{
	if((fp_index < MMI_DQ_FS_FP_MAX_NUM) && (g_dq_fs_fp[fp_index].fp_index == fp_index) && ((g_dq_fs_fp[fp_index].flag == type)||(type == FDS_USE_TYPE_ALL)))
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
RET_VAL mmi_dq_fs_set_fp(unsigned char fs_index,fds_use_type type)
{
	g_dq_fs_fp[fs_index].fp_index = fs_index;
	g_dq_fs_fp[fs_index].flag = type;
	return mmi_dq_fds_write(MID_FDS_FILE_FP, (unsigned char *)g_dq_fs_fp, sizeof(mmi_fs_fp)*MMI_DQ_FS_FP_MAX_NUM);
}

/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_fs_del_fp(unsigned char fp_index,fds_use_type type)
{
	if(mmi_dq_fs_check_fp(fp_index,type) == RET_SUCESS)
	{
		g_dq_fs_fp[fp_index].flag = FDS_USE_TYPE_INVALID;
		g_dq_fs_fp[fp_index].fp_index = 0xFF;
		return mmi_dq_fds_write(MID_FDS_FILE_FP, (unsigned char *)g_dq_fs_fp, sizeof(mmi_fs_fp)*MMI_DQ_FS_FP_MAX_NUM);
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
	unsigned char i = 0;
	unsigned short fp_ret = 0;

	for(i=0;i<MMI_DQ_FS_FP_MAX_NUM;i++)
	{
		if(g_dq_fs_fp[i].flag != FDS_USE_TYPE_ADMIN)
		{
			if(g_dq_fs_fp[i].fp_index != 0xFF)
			{
				//fp_ret = mmi_dq_fp_delete(g_dq_fs_fp[i].fp_index);
				if(fp_ret == 0)
				{
					g_dq_fs_fp[i].flag = FDS_USE_TYPE_INVALID;
					g_dq_fs_fp[i].fp_index = 0xFF;
				}
			}
		}
	}
	return mmi_dq_fds_write(MID_FDS_FILE_FP, (unsigned char *)g_dq_fs_fp, sizeof(mmi_fs_fp)*MMI_DQ_FS_FP_MAX_NUM);
}

#endif


#ifdef __LOCK_RFID_CARD_SUPPORT__

/*
parameter: 
	none
return :
	none
*/
unsigned short mmi_dq_fs_get_rfid_unuse_index(void)
{
	unsigned char i = 0;

	for(i=0;i<MMI_DQ_FS_RFID_MAX_NUM;i++)
	{
		if(g_dq_fs_rfid[i].index == 0xFF)
			break;
	}

	if(i>=MMI_DQ_FS_RFID_MAX_NUM)
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
	unsigned char i = 0,j = 0;
	
	for(i=0;i<MMI_DQ_FS_RFID_MAX_NUM;i++)
	{
		for(j=0;j<RFID_SEC_DATA_LEN;j++)
		{
			if(g_dq_fs_rfid[i].sec_data[j] != sec_data[j])
				break;
		}
		if(j == RFID_SEC_DATA_LEN)
			break;
	}
	if(i<MMI_DQ_FS_RFID_MAX_NUM&&((g_dq_fs_rfid[i].flag == type)||(type == FDS_USE_TYPE_ALL)))
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
	unsigned char i = 0,j = 0;
	for(i=0;i<MMI_DQ_FS_RFID_MAX_NUM;i++)
	{
		if(g_dq_fs_rfid[i].index == 0xFF)
			break;
	}
	if(i < MMI_DQ_FS_RFID_MAX_NUM)
	{
		g_dq_fs_rfid[i].index = i;
		g_dq_fs_rfid[i].flag = type;
		for(j=0;j<RFID_SEC_DATA_LEN;j++)
		{
			g_dq_fs_rfid[i].sec_data[j] = sec_data[j];
		}
		return mmi_dq_fds_write(MID_FDS_FILE_RF, (unsigned char *)g_dq_fs_rfid, sizeof(mmi_fs_rfid)*MMI_DQ_FS_RFID_MAX_NUM);
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
	if(rfid_index < MMI_DQ_FS_RFID_MAX_NUM && g_dq_fs_rfid[rfid_index].index == rfid_index)
	{
		g_dq_fs_rfid[rfid_index].index = 0xFF;
		g_dq_fs_rfid[rfid_index].flag = FDS_USE_TYPE_INVALID;
		memset(g_dq_fs_rfid[rfid_index].sec_data,0xFF,sizeof(g_dq_fs_rfid[rfid_index].sec_data));
		return mmi_dq_fds_write(MID_FDS_FILE_RF, (unsigned char *)g_dq_fs_rfid, sizeof(mmi_fs_rfid)*MMI_DQ_FS_RFID_MAX_NUM);
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
	
	for(i=0;i<MMI_DQ_FS_RFID_MAX_NUM;i++)
	{
		g_dq_fs_rfid[i].flag = FDS_USE_TYPE_INVALID;
		g_dq_fs_rfid[i].index = 0xFF;
		memset(g_dq_fs_rfid[i].sec_data,0xFF,sizeof(g_dq_fs_rfid[i].sec_data));
	}
	return mmi_dq_fds_write(MID_FDS_FILE_RF, (unsigned char *)g_dq_fs_rfid, sizeof(mmi_fs_rfid)*MMI_DQ_FS_RFID_MAX_NUM);
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
	if(g_dq_fs_init_set.open_mode == mode)
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
	if(g_dq_fs_init_set.open_pro_sound == flag)
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
	g_dq_fs_init_set.factory_flag= flag;
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
