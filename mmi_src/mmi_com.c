#ifndef __MMI_COM_C__
#define __MMI_COM_C__

#include "mmi_com.h"
#include "mmi_audio.h"

const msg_aud_id_list msg_aud_list[] =
	{
		//系统
		{
			STR_ID_SYSTEM
#ifdef __LOCK_AUDIO_SUPPORT__
			,
			AUD_ID_SYSTEM
#endif
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
			,
			0xff
#endif
		},
		//系统
		{
			STR_ID_SYSTEM2
#ifdef __LOCK_AUDIO_SUPPORT__
			,
			AUD_ID_SYSTEM2
#endif
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
			,
			0xff
#endif
		},
		{STR_ID_PASSWORD
#ifdef __LOCK_AUDIO_SUPPORT__
		 ,
		 AUD_ID_SYS_PASSWORD
#endif
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
		 ,
		 0xff
#endif
		}, //密码
		{
			STR_ID_FINGERPRINT
#ifdef __LOCK_AUDIO_SUPPORT__
			,
			AUD_ID_SYS_FP
#endif
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
			,
			0xff
#endif
		}, //指纹
		{
			STR_ID_RF_CARD
#ifdef __LOCK_AUDIO_SUPPORT__
			,
			AUD_ID_SYS_RFCARD
#endif
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
			,
			0xff
#endif
		}, //RF卡
		{
			STR_ID_ADMIN
#ifdef __LOCK_AUDIO_SUPPORT__
			,
			AUD_ID_SYS_ADMIN
#endif
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
			,
			0xff
#endif
		}, //管理员
		{
			STR_ID_SETTING
#ifdef __LOCK_AUDIO_SUPPORT__
			,
			AUD_ID_SYS_SETTING
#endif
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
			,
			0xff
#endif
		}, //设置
#if defined(__LOCK_WIFI_SUPPORT__) && defined(__LOCK_110_SUPPORT__)
		{
			STR_ID_110
#ifdef __LOCK_AUDIO_SUPPORT__
			,
			AUD_ID_SYS_110
#endif
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
			,
			0xff
#endif
		}, //RF鍗?
#endif
#if defined(__LOCK_WIFI_SUPPORT__) && defined(__LOCK_110_SUPPORT__)
		{
			STR_ID_FINGERPRINT_110
#ifdef __LOCK_AUDIO_SUPPORT__
			,
			AUD_ID_SYS_FP_110
#endif
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
			,
			0xff
#endif
		}, //管理�?
#endif
		{
			STR_ID_PRO_AUDIO
#ifdef __LOCK_AUDIO_SUPPORT__
			,
			AUD_ID_SYS_PRO_AUDIO
#endif
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
			,
			0xff
#endif
		}, //绠＄悊鍛?
#if 0
	{
		STR_ID_INPUT_68_PWD,
		AUD_ID_INPUT_68_PWD
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
		,0xff
#endif
	},//请输入6-8位密码
	{
		STR_ID_PRESS_HASH_END,

		0xFF
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
		,0xff
#endif
	},//按#键结束
	{
		STR_ID_PWD_LEN_68,
		AUD_ID_PWD_68_LEN
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
		,0xff
#endif
	},//密码应为6-8位
	{
		STR_ID_INPUT_PWD_AGAIN,
		AUD_ID_PWD_INPUT_AGAIN
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
		,0xff
#endif
	},//请再次输入密码
	{
		STR_ID_ADD_PWD_SUCESS,
		AUD_ID_ADD_PWD_SUCESS
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
		,0xff
#endif
	},//号密码添加成功
	{
		STR_ID_PWD_WRONG,
		AUD_ID_PWD_NOT_SAME
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
		,0xff
#endif
	},//两次输入的密码不一致
	{
		STR_ID_PWD_WRONG_RETRY,
		AUD_ID_PWD_NOT_SAME_RETRY
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
		,0xff
#endif
	},//两次输入的密码不一致
	{
		STR_ID_ADD_CONINUE_CONFIRM,
		AUD_ID_CONTINUE_ADD_PWD
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
		,0xff
#endif
	},//继续添加请按#，返回请按*
	{
		STR_ID_ADD_FAIL,
		AUD_ID_ADD_FAIL
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
		,0xff
#endif
	},//添加失败，请联系管理员
	{
		STR_ID_PWD_FULL,
		AUD_ID_PWD_FULL
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
		,0xff
#endif
	},//密码已满，请联系管理员
	{
		STR_ID_INPUT_OLD_PWD,
		AUD_ID_INPUT_OLD_PWD
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
		,0xff
#endif
	},//请输入旧密码
	{
		STR_ID_PWD_NOT_EXIST,
		AUD_ID_PWD_NOT_EXIST
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
		,0xff
#endif
	},//密码不存在，请重新输入
	{
		STR_ID_INPUT_NEW_PWD,
		AUD_ID_INPUT_NEW_PWD
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
		,0xff
#endif
	},//请输入新密码
	{
		STR_ID_INPUT_NEW_PWD_AGAIN,
		AUD_ID_INPUT_NEW_PWD_AGAIN
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
		,0xff
#endif
	},//请再次输入新密码
	{
		STR_ID_CHG_PWD_SUCESS,
		AUD_ID_CHG_PWD_SUCESS
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
		,0xff
#endif
	},//号密码修改成功
	{
		STR_ID_CHG_FAIL,
		AUD_ID_CHG_FAIL
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
		,0xff
#endif
	},//修改失败，请联系管理员
	{
		STR_ID_PWD_NOT_SAME,
		AUD_ID_PWD_OLD_NEW_NOT_SAME
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
		,0xff
#endif
	},//新旧密码不能一致
	{
		STR_ID_CHG_CONTINUE_CONFIRM,
		AUD_ID_CHG_CONTINUE_CONFIRM
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
		,0xff
#endif
	},//继续修改请按#，返回请按*
	{
		STR_ID_INPUT_DEL_PWD_NUM,
		AUD_ID_INPUT_DEL_NUM
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
		,0xff
#endif
	},//请输入要删除的编号或密码
	{
		STR_NUM_NOT_EXIST,
		AUD_ID_NUM_NOT_EXIST
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
		,0xff
#endif
	},//编号不存在，请重新输入
	{
		STR_ID_DEL_PWD_CONFIRM,
		AUD_ID_DEL_PWD_CONFIRM
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
		,0xff
#endif
	},//号密码按#确认删除，取消请按*
	{
		STR_ID_INPUT_DEL_PWD_AGAIN,
		AUD_ID_INPUT_DEL_PWD_AGAIN
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
		,0xff
#endif
	},//请再次输入要删除的密码
	{
		STR_ID_DEL_PWD_SUCESS,
		AUD_ID_DEL_PWD_SUCESS
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
		,0xff
#endif
	},//号密码删除成功
	{
		STR_ID_DEL_FAIL,
		AUD_ID_DEL_FAIL
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
		,0xff
#endif
	},//删除失败，请联系管理员
	{
		STR_ID_DEL_CONTINUE_CONFIRM,
		AUD_ID_DEL_CONFIRM
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
		,0xff
#endif
	},//继续删除请按#，返回请按*
	{
		STR_ID_CLR_PWD_CONFIRM,
		AUD_ID_CLR_PWD_CONFIRM
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
		,0xff
#endif
	},//按#确认删除所有密码，取消请按*
	{
		STR_ID_CLR_PWD_SUCESS,
		AUD_ID_CLR_PWD_SUCESS
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
		,0xff
#endif
	},//删除所有密码成功
	{
		STR_ID_CLR_PWD_FAIL,
		AUD_ID_CLR_PWD_FAIL
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
		,0xff
#endif
	},//删除所有密码失败
	{
		STR_ID_PRESS_FP,
		AUD_ID_PRESS_FP
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
		,0xff
#endif
	},//请按手指
	{
		STR_ID_PRESS_FP_AGAIN,
		AUD_ID_PRESS_FP_AGAIN
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
		,0xff
#endif
	},//请再按一次
	{
		STR_ID_ADD_FP_SUCESS,
		AUD_ID_ADD_FP_SUCESS
	},//号指纹添加成功
	{
		STR_ID_FP_NOT_SAME,
		AUD_ID_FP_NOT_SAME
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
		,0xff
#endif
	},//新旧指纹不能一致
	{
		STR_ID_FP_EXIST,
		AUD_ID_FP_EXIST
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
		,0xff
#endif
	},//指纹重复，请换个手指
	{
		STR_ID_ADD_FAIL_RETRY,
		AUD_ID_ADD_FAIL_RETRY
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
		,0xff
#endif
	},//添加失败，请重试
	{
		STR_ID_FP_FULL,
		AUD_ID_FP_FULL
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
		,0xff
#endif
	},//指纹已满，请联系管理员
	{
		STR_ID_PRESS_OLD_FP,
		AUD_ID_PRESS_OLD_FP
	},//请按旧指纹
	{
		STR_ID_PRESS_NEW_FP,
		AUD_ID_PRESS_NEW_FP
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
		,0xff
#endif
	},//请按新指纹
	{
		STR_ID_PRESS_NEW_FP_AGAIN,
		AUD_ID_PRESS_NEW_FP_AGAIN
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
		,0xff
#endif
	},//请再按一次新指纹
	{
		STR_ID_FP_TWICE_NOT_SAME,
		AUD_ID_FP_TWICE_NOT_SAME
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
		,0xff
#endif
	},//两次输入的指纹不一致
	{
		STR_ID_CHG_FP_SUCESS,
		AUD_ID_CHG_FP_SUCESS
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
		,0xff
#endif
	},//号指纹修改成功
	{
		STR_ID_CHG_FAIL_RETRY,
		AUD_ID_CHG_FAIL_RETRY
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
		,0xff
#endif
	},//修改失败，请重试
	{
		STR_ID_INPUT_DEL_FP_NUM,
		AUD_ID_INPUT_DEL_FP_NUM
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
		,0xff
#endif
	},//请输入要删除的编号或指纹
	{
		STR_ID_FP_NOT_EXIST,
		AUD_ID_FP_NOT_EXIST
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
		,0xff
#endif
	},//指纹不存在，请重新输入
	{
		STR_ID_DEL_FP_CONFIRM,
		AUD_ID_DEL_FP_CONFIRM
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
		,0xff
#endif
	},//号指纹按#确认删除，取消请按*
	{
		STR_ID_PRESS_DEL_FP_AGAIN,
		AUD_ID_PRESS_DEL_FP_AGAIN
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
		,0xff
#endif
	},//请再按一次要删除的指纹
	{
		STR_ID_DEL_FP_SUCESS,
		AUD_ID_DEL_FP_SUCESS
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
		,0xff
#endif
	},//号指纹删除成功
	{
		STR_ID_DEL_FAIL_RETRY,
		AUD_ID_DEL_FAIL_RETRY
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
		,0xff
#endif
	},//删除失败，请重试
	{
		STR_ID_CLR_FP_CONFIRM,
		AUD_ID_CLR_FP_CONFIRM
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
		,0xff
#endif
	},//按#确认删除所有指纹，取消请按*
	{
		STR_ID_CLR_FP_SUCESS,
		AUD_ID_CLR_FP_SUCESS
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
		,0xff
#endif
	},//删除所有指纹成功
	{
		STR_ID_CLR_FP_FAIL,
		AUD_ID_CLR_FP_FAIL
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
		,0xff
#endif
	},//删除所有指纹失败
	{
		STR_ID_PRESS_RFCARD,
		AUD_ID_PRESS_RFCARD
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
		,0xff
#endif
	},//请刷卡
	{
		STR_ID_PRESS_RFCARD_AGAIN,
		AUD_ID_PRESS_RFCARD_AGAIN
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
		,0xff
#endif
	},//请再刷一次
	{
		STR_ID_ADD_RFCARD_SUCESS,
		AUD_ID_ADD_RFCARD_SUCESS
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
		,0xff
#endif
	},//号RF卡添加成功
	{
		STR_ID_RFCARD_EXIST,
		AUD_ID_RFCARD_EXIST
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
		,0xff
#endif
	},//RF卡已存在，请换张卡
	{
		STR_ID_RFCARD_FULL,
		AUD_ID_RFCARD_FULL
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
		,0xff
#endif
	},//RF卡已满，请联系管理员
	{
		STR_ID_PRESS_OLD_RFCARD,
		AUD_ID_PRESS_OLD_RFCARD
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
		,0xff
#endif
	},//请刷旧卡
	{
		STR_ID_PRESS_NEW_RFCARD,
		AUD_ID_PRESS_NEW_RFCARD
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
		,0xff
#endif
	},//请刷新卡
	{
		STR_ID_PRESS_NEW_RFCARD_AGAIN,
		AUD_ID_PRESS_NEW_RFCARD_AGAIN
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
		,0xff
#endif
	},//请再刷一次新卡
	{
		STR_ID_CHG_RFCARD_SUCESS,
		AUD_ID_CHG_RFCARD_SUCESS
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
		,0xff
#endif
	},//号RF卡修改成功
	{
		STR_ID_RFCARD_NOT_SAME,
		AUD_ID_RFCARD_NOT_SAME
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
		,0xff
#endif
	},//新旧RF卡不能一致
	{
		STR_ID_INPUT_DEL_RFCARD_NUM,
		AUD_ID_INPUT_DEL_RFCARD_NUM
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
		,0xff
#endif
	},//请输入要删除的编号或RF卡
	{
		STR_ID_RFCARD_NOT_EXIST,
		AUD_ID_RFCARD_NOT_EXIST
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
		,0xff
#endif
	},//RF卡不存在，请重新输入
	{
		STR_ID_RFCARD_DEL_CONFIRM,
		AUD_ID_DEL_RFCARD_CONFIRM
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
		,0xff
#endif
	},//号RF卡按#确认删除，取消请按*
	{
		STR_ID_PRESS_DEL_RFCARD_AGAIN,
		AUD_ID_PRESS_DEL_RFCARD_AGAIN
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
		,0xff
#endif
	},//请再刷一次要删除的RF卡
	{
		STR_ID_DEL_RFCARD_SUCESS,
		AUD_ID_DEL_RFCARD_SUCESS
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
		,0xff
#endif
	},//号RF卡删除成功
	{
		STR_ID_CLR_RFCARD_CONTINUE_CONFIRM,
		AUD_ID_CLR_RFCARD_CONFIRM
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
		,0xff
#endif
	},//按#确认删除所有RF卡，取消请按*
	{
		STR_ID_CLR_RFCARD_SUCESS,
		AUD_ID_CLR_RFCARD_SUCESS
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
		,0xff
#endif
	},//删除所有RF卡成功
	{
		STR_ID_CLR_RFCARD_FAIL,
		AUD_ID_CLR_RFCARD_FAIL
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
		,0xff
#endif
	},//删除所有RF卡失败
	{
		STR_ID_INPUT_OLD_ADMIN_PWD,
		AUD_ID_INPUT_ADMIN_PWD
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
		,0xff
#endif
	},//请输入旧管理员密码
	{
	
		STR_ID_INPUT_NEW_ADMIN_PWD,
		AUD_ID_INPUT_NEW_ADMIN_PWD
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
		,0xff
#endif
	},//请输入新管理员密码
	{
		STR_ID_INPUT_NEW_ADMIN_PWD_AGAIN,
		AUD_ID_INPUT_NEW_ADMIN_PWD_AGAIN
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
		,0xff
#endif
	},//请再次输入新管理员密码
	{
		STR_ID_CHG_ADMIN_PWD_SUCESS,
		AUD_ID_CHG_ADMIN_PWD_SUCESS
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
		,0xff
#endif
	},//管理员密码修改成功
	{
		STR_ID_PWD_EXIST,
		AUD_ID_PWD_EXIST
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
		,0xff
#endif
	},//密码已存在，请重新输入
	{
		STR_ID_PRESS_NEW_ADMIN_FP,
		AUD_ID_NEW_ADMIN_FP
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
		,0xff
#endif
	},//请按新的管理员指纹
	{
		STR_ID_PRESS_NEW_ADMIN_FP_AGAIN,
		AUD_ID_PRESS_FP_AGAIN
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
		,0xff
#endif
	},//请再按一次
	{
		STR_ID_ADD_NO1_ADMIN_FP_SUCESS,
		AUD_ID_ADD_NO1_ADMIN_FP_SUCESS
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
		,0xff
#endif
	},//1号管理指纹添加成功
	{
		STR_ID_ADD_NO2_ADMIN_FP_SUCESS,
		AUD_ID_ADD_NO2_ADMIN_FP_SUCESS
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
		,0xff
#endif
	},//2号管理指纹添加成功
#endif
		{
			STR_ID_PRO_AUDIO
#ifdef __LOCK_AUDIO_SUPPORT__
			,
			AUD_ID_SYS_PRO_AUDIO
#endif
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
			,
			0xff
#endif
		}, //提示音
#if 0
		{
			STR_ID_CLOSE_PRO_AUDIO_SUCESS,
			AUD_ID_CLOSE_PRO_AUDIO_SUCESS
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
			,
			0xff
#endif
		}, //关闭提示音成功
		{
			STR_ID_CLOSE_PRO_AUDIO_FAIL,
			AUD_ID_CLOSE_PRO_AUDIO_FAIL
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
			,
			0xff
#endif
		}, //关闭提示音失败
		{
			STR_ID_OPEN_PRO_AUDIO_SUCESS,
			AUD_ID_OPEN_PRO_AUDIO_SUCESS
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
			,
			0xff
#endif
		}, //开启提示音成功
		{
			STR_ID_OPEN_PRO_AUDIO_FAIL,
			AUD_ID_OPEN_PRO_AUDIO_FAIL
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
			,
			0xff
#endif
		}, //开启提示音失败
		{
			STR_ID_DBL_OPEN_MODE,
			AUD_ID_SYS_DBL_OPEN_MODE
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
			,
			0xff
#endif
		}, //双开门方式
		{
			STR_ID_SIN_OPEN_MODE_SUCESS,
			AUD_ID_SIN_OPEN_MODE_SUCESS
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
			,
			0xff
#endif
		}, //单开门方式设置成功
		{
			STR_ID_SIN_OPEN_MODE_FAIL,
			AUD_ID_SIN_OPEN_MODE_FAIL
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
			,
			0xff
#endif
		}, //单开门方式设置失败
		{
			STR_ID_DBL_OPEN_MODE_SUCESS,
			AUD_ID_DBL_OPEN_MODE_SUCESS
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
			,
			0xff
#endif
		}, //双开门方式设置成功
		{
			STR_ID_DBL_OPEN_MODE_FAIL,
			AUD_ID_DBL_OPEN_MODE_FAIL
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
			,
			0xff
#endif
		}, //双开门方式设置失败
		{
			STR_ID_RESTORE_SUCESS,
			AUD_ID_RESTORE_SUCESS
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
			,
			0xff
#endif
		}, //恢复出厂设置成功
		{
			STR_ID_RESTORE_FAIL,
			AUD_ID_RESTORE_FAIL
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
			,
			0xff
#endif
		}, //恢复出厂设置失败
		{
			STR_ID_ADD_ADMIN_PWD,
			AUD_ID_ADD_ADMIN_PWD_FIRST
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
			,
			0xff
#endif
		}, //请添加管理员密码
		{
			STR_ID_ADD_ADMIN_PWD_SUCESS,
			AUD_ID_ADD_ADMIN_PWD_INIT_SUCESS
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
			,
			0xff
#endif
		}, //管理员密码添加成功
		{
			STR_ID_INPUT_ADMIN_PWD,
			AUD_ID_INPUT_ADMIN_PWD
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
			,
			0xff
#endif
		}, //请输入管理员密码
		{
			STR_ID_INPUT_ADMIN_PWD_AGAIN,
			AUD_ID_INPUT_ADMIN_PWD_INIT_AGAIN
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
			,
			0xff
#endif
		}, //请再次输入管理员密码
		{
			STR_ID_OPEN_DOOR,
			AUD_ID_DOOR_OPEN
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
			,
			0xff
#endif
		}, //已开锁
		{
			STR_ID_CLOSE_DOOR,
			AUD_ID_DOOR_CLOSE
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
			,
			0xff
#endif
		}, //已关锁
		{
			STR_ID_PWD_WRONG_TRY,
			AUD_ID_PWD_WRONG_TRY
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
			,
			0xff
#endif
		}, //密码错误,请重试
		{
			STR_ID_FP_WRONG_TRY,
			AUD_ID_FP_WRONG_TRY
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
			,
			0xff
#endif
		}, //指纹错误，请重试
		{
			STR_ID_RF_WRONG_TRY,
			AUD_ID_RFCARD_WRONG_TRY
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
			,
			0xff
#endif
		}, //RF卡错误，请重试
		{
			STR_ID_WRONG_EXCEED,
			AUD_ID_RONG_TIMES_EXCEED
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
			,
			0xff
#endif
		}, //错误次数已超限制，请分钟后重试
		{
			STR_ID_LOW_BATTERY,
			AUD_ID_LOW_BATTERY
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
			,
			0xff
#endif
		}, //电量低，请及时更换电池
		{
			STR_ID_CHG_ADMIN_PWD,
			AUD_ID_SYS_CHG_ADMIN_PWD
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
			,
			0xff
#endif
		}, //修改管理员密码
#endif
		{
			STR_ID_CHG_ADMIN_FP
#ifdef __LOCK_AUDIO_SUPPORT__
			,
			AUD_ID_SYS_CHG_ADMIN_FP
#endif
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
			,
			0xff
#endif
		}, //修改管理员指纹
		{
			STR_ID_OPEN_MODE
#ifdef __LOCK_AUDIO_SUPPORT__
			,
			AUD_ID_SYS_OPEN_MODE
#endif
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
			,
			0xff
#endif
		}, //开门方式
#if 0
		{
			STR_ID_ADD_ADMIN_PWD_FIRST,
			AUD_ID_ADD_ADMIN_PWD_FIRST
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
			,
			0xff
#endif
		}, //为了您的使用安全，请先添加管理员密码，按#键结束
		{
			STR_ID_RESTORE_LOCK_CONTINUE_CONFIRM,
			AUD_ID_RESTORE_LOCK_CONTINUE_CONFIRM
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
			,
			0xff
#endif
		}, //按#恢复出厂设置，取消请按*
		{
			STR_ID_FM_KEY_INPUT,
			AUD_ID_FM_KEY_INPUT
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
			,
			0xff
#endif
		}, //请测试所有按键
		{
			STR_ID_FM_MOTO,
			AUD_ID_FM_MOTO
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
			,
			0xff
#endif
		}, //马达测试，通过请按#, 失败请按*
		{
			STR_ID_FM_RESET,
			AUD_ID_FM_RESET
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
			,
			0xff
#endif
		}, //复位键测试，请按复位键
		{
			STR_ID_FM_TEST_PASS,
			AUD_ID_FM_TEST_PASS
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
			,
			0xff
#endif
		}, //测试通过
		{
			STR_ID_FM_TEST_FAIL,
			AUD_ID_FM_TEST_FAIL
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
			,
			0xff
#endif
		}, //测试失败
		{
			STR_ID_APP_SYN,
			AUD_ID_APP_SYN
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
			,
			0xff
#endif
		}, //请使用APP同步时间
		{
			STR_ID_APP_ADD_SUC,
			AUD_ID_APP_ADD_SUC
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
			,
			0xff
#endif
		}, //app添加成功
		{
			STR_ID_APP_ADD_FAIL,
			AUD_ID_APP_ADD_FAIL
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
			,
			0xff
#endif
		}, //app添加成功
		{
			STR_ID_SET_SUCESS,
			AUD_ID_SET_SUCESS
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
			,
			0xff
#endif
		},
#endif

		{STR_ID_MAX_COUNT,
		 0xFF
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
		 ,
		 0xff
#endif
		},
		{STR_ID_INVALID_ID,
		 0xFF
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
		 ,
		 0xff
#endif
		}};
#endif //__MMI_COM_C__