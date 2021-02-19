#ifndef __MMI_SYS_C__
#define __MMI_SYS_C__

#include "mmi_feature.h"
#include "mmi_sys.h"
#include "mmi_audio.h"
#include "mmi_queue.h"
#include "dqiot_drv.h"
#include "mmi_ms.h"

static unsigned char g_sys_door_open_flag = 0;

static unsigned int g_timer2_count = 0;
static unsigned int g_timer2_set_count = 0;

typedef void (*timer2_delay_pro)(void);
timer2_delay_pro g_timer2_delay_pro = 0;


#define MMI_TIMER_BASE_TIME		100
#define MMI_TIMER_ENTER_SLEEP	10000
#define MMI_TIMER_ENTER_SLEEP_COUNT	(MMI_TIMER_ENTER_SLEEP/MMI_TIMER_BASE_TIME)
#define MMI_TIMER_DOOR_OPEN 	6000
#define MMI_TIMER_DOOR_OPEN_COUNT	(MMI_TIMER_DOOR_OPEN/MMI_TIMER_BASE_TIME)


/*
function: system enter sleep
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_init(void)
{
	mmi_InitQueue();
	mmi_ms_pwd_init_var();
}
/*
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_show_message_with_id(unsigned char text_id,unsigned long time_msec)
{
	unsigned char i = 0;
	unsigned char audio_id = 0;
	
	time_msec = 0;
	
#ifdef __LOCK_AUDIO_SUPPORT__
	audio_id = mmi_dq_aud_get_audio_id(text_id);

	mmi_dq_aud_play_with_id(audio_id);

#endif
	return;
}

/*
function: system enter sleep
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_enter_sleep(void)
{
	
}

/*
function: system wake up
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_wake_up(void)
{
	
}

/*
function: 
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_door_open(sys_open_type type)
{
	if(mmi_dq_fs_get_open_mode() == SYS_OPEN_MODE_DBL)
	{
		if(g_sys_door_open_flag & (~ type) != 0)
		{
			g_sys_door_open_flag = 0;
		}
		else
		{
			g_sys_door_open_flag &= type;
			return;
		}
	}

	mmi_dq_ms_set_sys_state(SYS_STATUS_DOOR_OPEN);

	mmi_dq_aud_play_with_id(AUD_ID_DOOR_OPEN);

	mmi_dq_sys_set_delay_event(MMI_TIMER_DOOR_OPEN_COUNT, mmi_dq_sys_door_close);
}

/*
function: 
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_door_close(void)
{
	
	mmi_dq_ms_set_sys_state(SYS_STATUS_IDLE);
}

/*
function: 
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_aud_end(void)
{
	mmi_dq_ms_set_msg_que(QUE_EVENT_AUDIO_END,QUE_PRO_LOW,0);
}

/*
function: 
parameter: 
	none
return :
	none
*/
void timer2_event_handler(void)
{
	if(SYS_STATUS_ENTER_SLEEP == mmi_dq_ms_get_sys_state())
	{

	}
	else
	{
		g_timer2_count++;
		if(g_timer2_count >= g_timer2_set_count)
		{
			dqiot_drv_timer2_stop();
			g_timer2_count = 0;
			mmi_dq_ms_set_msg_que(QUE_EVENT_TIMER_END,QUE_PRO_LOW,0);
		}
	}
}

/*
function: 
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_set_delay_event(unsigned int count, timer2_delay_pro pro)
{
	g_timer2_count = 0;
	g_timer2_set_count = count;
	g_timer2_delay_pro = pro;
	dqiot_drv_timer2_start();
}

//----------------------------------------------------------------------------------------------------------------------------------------------
//				menu part
//----------------------------------------------------------------------------------------------------------------------------------------------

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_add_pwd(void)
{
	mmi_dq_ms_set_sys_state(SYS_STATUS_ADD_PWD);
	return;
}

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_chg_pwd(void)
{
	//mmi_dq_ms_set_sys_state(SYS_STATUS_CHG_PWD);
	return;
}

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_del_pwd(void)
{
	mmi_dq_ms_set_sys_state(SYS_STATUS_DEL_PWD);
	return;
}

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_clear_pwd(void)
{
	mmi_dq_ms_set_sys_state(SYS_STATUS_CLR_PWD);
	return;
}

#if defined(__LOCK_FP_SUPPORT__)
/*
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_add_fp(void)
{
	mmi_dq_ms_set_sys_state(SYS_STATUS_ADD_FP);
	return;
}

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_chg_fp(void)
{
	//mmi_dq_ms_set_sys_state(SYS_STATUS_CHG_FP);
	return;
}

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_del_fp(void)
{
	mmi_dq_ms_set_sys_state(SYS_STATUS_DEL_FP);
	return;
}

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_clear_fp(void)
{
	mmi_dq_ms_set_sys_state(SYS_STATUS_CLR_FP);
	return;
}
#endif
#ifdef __LOCK_RFID_CARD_SUPPORT__
/*
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_add_rf(void)
{
	mmi_dq_ms_set_sys_state(SYS_STATUS_ADD_RFID);
	return;
}

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_chg_rf(void)
{
	//mmi_dq_ms_set_sys_state(SYS_STATUS_CHG_RFID);
	return;
}

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_del_rf(void)
{
	mmi_dq_ms_set_sys_state(SYS_STATUS_DEL_RFID);
	return;
}

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_clear_rf(void)
{
	mmi_dq_ms_set_sys_state(SYS_STATUS_CLR_RFID);
	return;
}
#endif

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_open_pro_sound(void)
{
	mmi_dq_sys_set_father_id(STR_ID_SETTING);

	mmi_dq_ms_set_machine_status(BASE_STATUS_M_SET_PRO_SOUND);
	return;
}

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_close_pro_sound(void)
{
	mmi_dq_sys_set_father_id(STR_ID_SETTING);

	mmi_dq_ms_set_machine_status(BASE_STATUS_M_CLR_PRO_SOUND);
	return;
}

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_sin_open_mode(void)
{
	mmi_dq_sys_set_father_id(STR_ID_SETTING);

	mmi_dq_ms_set_machine_status(BASE_STATUS_M_SET_SIN_OPEN_MODE);
	return;
}

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_dbl_open_mode(void)
{
	mmi_dq_sys_set_father_id(STR_ID_SETTING);

	mmi_dq_ms_set_machine_status(BASE_STATUS_M_SET_DBL_OPEN_MODE);
	return;
}
#if defined(__LOCK_FP_SUPPORT__)||defined(__LOCK_FP_SUPPORT2__)||defined(__LOCK_FP_SUPPORT1_2__)
/*
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_chg_admin_fp_No1(void)
{
	mmi_dq_ms_set_machine_status(BASE_STATUS_M_ADD_ADMIN_FP1);
	return;
}
/*
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_chg_admin_fp_No2(void)
{
	mmi_dq_ms_set_machine_status(BASE_STATUS_M_ADD_ADMIN_FP2);
	return;
}
#endif
/*
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_chg_admin_pwd(void)
{
	mmi_dq_ms_set_sys_state(BASE_STATUS_M_CHG_PWD);
	return;
}

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_restore_lock(void)
{
	mmi_dq_ms_set_sys_state(SYS_STATUS_RESTORE_LOCK);
}



















typedef struct sys_menu_t
{
	unsigned char menu_father_id;
	unsigned char menu_sub_id;
	void (*sys_menu_node_function)(void);
}sys_menu_t;

typedef struct sys_menu_list
{
	unsigned char id;
	unsigned char menu_id;
}sys_menu_list;

const sys_menu_t sys_menu_tree[] = 
{
	{STR_ID_SYSTEM,STR_ID_PASSWORD,0},
#if defined(__LOCK_FP_SUPPORT__)
	{STR_ID_SYSTEM,STR_ID_FINGERPRINT,0},
#endif
#ifdef __LOCK_RFID_CARD_SUPPORT__
	{STR_ID_SYSTEM,STR_ID_RF_CARD,0},
#endif
	{STR_ID_SYSTEM,STR_ID_ADMIN,0},
	{STR_ID_SYSTEM,STR_ID_SETTING,0},
	{STR_ID_SYSTEM,STR_ID_RESTORE,mmi_dq_sys_restore_lock},
#ifdef __PREIPHERAL_WIFI_UH010_SUPPORT__
	{STR_ID_SYSTEM,STR_ID_WIFI,mmi_dq_wifi_setting},
#endif
	

	{STR_ID_SYSTEM2,STR_ID_ADMIN,0},
	{STR_ID_SYSTEM2,STR_ID_SETTING,0},
	{STR_ID_SYSTEM2,STR_ID_RESTORE,mmi_dq_sys_restore_lock},
	
	//PWD
	{STR_ID_PASSWORD,STR_ID_ADD_PWD,mmi_dq_sys_add_pwd},
	{STR_ID_PASSWORD,STR_ID_CHG_PWD,mmi_dq_sys_chg_pwd},
	{STR_ID_PASSWORD,STR_ID_DEL_PWD,mmi_dq_sys_del_pwd},
	{STR_ID_PASSWORD,STR_ID_CLR_PWD,mmi_dq_sys_clear_pwd},
	//FP
#if defined(__LOCK_FP_SUPPORT__)||defined(__LOCK_FP_SUPPORT2__)||defined(__LOCK_FP_SUPPORT1_2__)
	{STR_ID_FINGERPRINT,STR_ID_ADD_FP,mmi_dq_sys_add_fp},
	{STR_ID_FINGERPRINT,STR_ID_CHG_FP,mmi_dq_sys_chg_fp},
	{STR_ID_FINGERPRINT,STR_ID_DEL_FP,mmi_dq_sys_del_fp},
	{STR_ID_FINGERPRINT,STR_ID_CLR_FP,mmi_dq_sys_clear_fp},
#endif
#ifdef __LOCK_RFID_CARD_SUPPORT__
	//RF
	{STR_ID_RF_CARD,STR_ID_ADD_RFCARD,mmi_dq_sys_add_rf},
	{STR_ID_RF_CARD,STR_ID_CHG_RFCARD,mmi_dq_sys_chg_rf},
	{STR_ID_RF_CARD,STR_ID_DEL_RFCARD,mmi_dq_sys_del_rf},
	{STR_ID_RF_CARD,STR_ID_CLR_RFCARD,mmi_dq_sys_clear_rf},
#endif
	//admin
	{STR_ID_ADMIN,STR_ID_CHG_ADMIN_PWD,mmi_dq_sys_chg_admin_pwd},
#if defined(__LOCK_FP_SUPPORT__)
	{STR_ID_ADMIN,STR_ID_CHG_ADMIN_FP,0},
	{STR_ID_CHG_ADMIN_FP,STR_ID_NO1_ADMIN_FP,mmi_dq_sys_chg_admin_fp_No1},
	{STR_ID_CHG_ADMIN_FP,STR_ID_NO2_ADMIN_FP,mmi_dq_sys_chg_admin_fp_No2},
#endif
	//setting
	{STR_ID_SETTING,STR_ID_PRO_AUDIO,0},
	{STR_ID_SETTING,STR_ID_OPEN_MODE,0},
	
	{STR_ID_PRO_AUDIO,STR_ID_OPEN_PRO_AUDIO,mmi_dq_sys_open_pro_sound},
	{STR_ID_PRO_AUDIO,STR_ID_CLOSE_PRO_AUDIO,mmi_dq_sys_close_pro_sound},
	{STR_ID_OPEN_MODE,STR_ID_SIN_OPEN_MODE,mmi_dq_sys_sin_open_mode},
	{STR_ID_OPEN_MODE,STR_ID_DBL_OPEN_MODE,mmi_dq_sys_dbl_open_mode},
};

static unsigned char 	g_dq_menu_father_id;
static unsigned char 	g_dq_menu_id;
static sys_menu_list 	g_dq_menu_list_id[8];
static unsigned char	g_dq_menu_count;

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_get_menu_list(unsigned char father_id)
{
	unsigned char i = 0,j = 0;
	unsigned char menu_tree_size = sizeof(sys_menu_tree)/sizeof(sys_menu_t);

	g_dq_menu_father_id = father_id;

	memset(&g_dq_menu_list_id,0x00,sizeof(g_dq_menu_list_id));
	g_dq_menu_count = 0;
	
	if(g_dq_menu_father_id == STR_ID_SYSTEM )
	{
		for(i=0;i<menu_tree_size;i++)
		{

			if(sys_menu_tree[i].menu_father_id == STR_ID_SYSTEM)
			{
				g_dq_menu_list_id[j].id = j + 1;
				g_dq_menu_list_id[j].menu_id = sys_menu_tree[i].menu_sub_id;
				j++;
				g_dq_menu_count ++;
			}

		}
		return;
	}
	else if(g_dq_menu_father_id == STR_ID_ADMIN )
	{
		for(i=0;i<menu_tree_size;i++)
		{
		
			if(sys_menu_tree[i].menu_father_id == STR_ID_ADMIN)
			{
				g_dq_menu_list_id[j].id = j + 1;
				g_dq_menu_list_id[j].menu_id = sys_menu_tree[i].menu_sub_id;
				j++;
				g_dq_menu_count ++;


			}
		}
		return;

	}
	
	for(i=0;i<menu_tree_size;i++)
	{
		if(sys_menu_tree[i].menu_father_id == g_dq_menu_father_id)
		{
			g_dq_menu_list_id[j].id = j + 1;
			g_dq_menu_list_id[j].menu_id = sys_menu_tree[i].menu_sub_id;
			j++;
			g_dq_menu_count ++;
		}
	}
	return;
}

/*
parameter: 
	none
return :
	current machine status
*/
void mmi_dq_sys_get_pre_menu_list(void)
{
	if(g_dq_menu_father_id == STR_ID_SYSTEM)
	{
		mmi_dq_ms_set_machine_status(BASE_STATUS_M_IDLE);
	}
	else
	{
		unsigned char i = 0;
		unsigned char menu_tree_size = sizeof(sys_menu_tree)/sizeof(sys_menu_t);

		for(i=0;i<menu_tree_size;i++)
		{
			if(sys_menu_tree[i].menu_sub_id == g_dq_menu_father_id)
				g_dq_menu_father_id = sys_menu_tree[i].menu_father_id;
		}
		mmi_dq_sys_get_menu_list(g_dq_menu_father_id);
#ifdef __LOCK_AUDIO_SUPPORT__
		mmi_dq_aud_play_with_text(g_dq_menu_father_id);
#endif
	}
	return;
}

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_exe_menu_fun(unsigned char id)
{
	unsigned char i = 0;
	unsigned char menu_tree_size = sizeof(sys_menu_tree)/sizeof(sys_menu_t);
	if(id>=g_dq_menu_count)
		return;
	for(i=0;i<menu_tree_size;i++)
	{
		if(sys_menu_tree[i].menu_sub_id == g_dq_menu_list_id[id].menu_id)
		{
			break;
		}
	}
	if(sys_menu_tree[i].sys_menu_node_function != 0)
	{
		g_dq_menu_id = sys_menu_tree[i].menu_sub_id;
		sys_menu_tree[i].sys_menu_node_function();
	}
	else
	{
		for(i=0;i<g_dq_menu_count;i++)
		{
			if((g_dq_menu_father_id == sys_menu_tree[i].menu_father_id)
				&&(g_dq_menu_list_id[id].menu_id == sys_menu_tree[i].menu_sub_id))
			{
				break;
			}
		}
		mmi_dq_sys_get_menu_list(g_dq_menu_list_id[id].menu_id);

		
#ifdef __LOCK_AUDIO_SUPPORT__
		 mmi_dq_aud_play_with_text(g_dq_menu_father_id);
#endif
		
	}
	
	return;
}

#endif//__MMI_SYS_C__
