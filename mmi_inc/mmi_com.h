#ifndef __MMI_COM_H__
#define __MMI_COM_H__

#include "mmi_feature.h"

typedef struct
{
	unsigned char msg_id;
	unsigned char aud_id;
#ifdef __AUDIO_BUSY_NOT_SUPPOT__
	unsigned short	delay_time;
#endif
}msg_aud_id_list;

extern const msg_aud_id_list msg_aud_list[];


typedef enum
{
	RET_SUCESS = 0x00,
	RET_FAIL = 0x01,
	RET_INVALID = 0xFF
}RET_VAL;

	
typedef enum sys_str_id
{
	STR_ID_DQWL,//点趣物联
	STR_ID_SYSTEM,//系统
	STR_ID_SYSTEM2,//系统
	STR_ID_PASSWORD,//密码
	STR_ID_PASSWORD_110,//密码
	STR_ID_FINGERPRINT,//指纹
	STR_ID_FINGERPRINT_110,//指纹
	STR_ID_RF_CARD,//RF卡
	STR_ID_ADMIN,//管理员
	STR_ID_SETTING,//设置
	STR_ID_110,//110
	STR_ID_RESTORE,//恢复出厂设置
	STR_ID_WIFI,//WIFI
	STR_ID_ADD_PWD,//添加密码
	STR_ID_CHG_PWD,//修改密码
	STR_ID_DEL_PWD,//删除密码
	STR_ID_CLR_PWD,//删除所有密码
	STR_ID_INPUT_68_PWD,//请输入6-8位密码
	STR_ID_PRESS_HASH_END,//按#键结束
	STR_ID_PWD_LEN_68,//密码应为6-8位
	STR_ID_INPUT_PWD_AGAIN,//请再次输入密码
	STR_ID_ADD_PWD_SUCESS,//号密码添加成功
	STR_ID_PWD_WRONG,//两次输入的密码不一致
	STR_ID_PWD_WRONG_RETRY,//两次输入的密码不一致,请重新输入
	STR_ID_ADD_CONINUE_CONFIRM,//继续添加请按#，返回请按*
	STR_ID_ADD_FAIL,//添加失败，请联系管理员
	STR_ID_PWD_FULL,//密码已满，请联系管理员
	STR_ID_INPUT_OLD_PWD,//请输入旧密码
	STR_ID_PWD_NOT_EXIST,//密码不存在，请重新输入
	STR_ID_INPUT_NEW_PWD,//请输入新密码
	STR_ID_INPUT_NEW_PWD_AGAIN,//请再次输入新密码
	STR_ID_CHG_PWD_SUCESS,//号密码修改成功
	STR_ID_CHG_FAIL,//修改失败，请联系管理员
	STR_ID_PWD_NOT_SAME,//新旧密码不能一致
	STR_ID_CHG_CONTINUE_CONFIRM,//继续修改请按#，返回请按*
	STR_ID_INPUT_DEL_PWD_NUM,//请输入要删除的编号或密码
	STR_NUM_NOT_EXIST,//编号不存在，请重新输入
	STR_ID_DEL_PWD_CONFIRM,//号密码按#确认删除，取消请按*
	STR_ID_INPUT_DEL_PWD_AGAIN,//请再次输入要删除的密码
	STR_ID_DEL_PWD_SUCESS,//号密码删除成功
	STR_ID_DEL_FAIL,//删除失败
	STR_ID_DEL_CONTINUE_CONFIRM,//继续删除请按#，返回请按*
	STR_ID_CLR_PWD_CONFIRM,//按#确认删除所有密码，取消请按*
	STR_ID_CLR_PWD_SUCESS,//删除所有密码成功
	STR_ID_CLR_PWD_FAIL,//删除所有密码失败
	STR_ID_ADD_FP,//添加指纹
	STR_ID_CHG_FP,//修改指纹
	STR_ID_DEL_FP,//删除指纹
	STR_ID_CLR_FP,//删除所有指纹
	STR_ID_PRESS_FP,//请按手指
	STR_ID_PRESS_FP_AGAIN,//请再按一次
	STR_ID_ADD_FP_SUCESS,//号指纹添加成功
	STR_ID_FP_NOT_SAME,//新旧指纹不能一致
	STR_ID_FP_EXIST,//指纹重复，请换个手指
	STR_ID_ADD_FAIL_RETRY,//添加失败，请重试
	STR_ID_FP_FULL,//指纹已满，请联系管理员
	STR_ID_PRESS_OLD_FP,//请按旧指纹
	STR_ID_PRESS_NEW_FP,//请按新指纹
	STR_ID_PRESS_NEW_FP_AGAIN,//请再按一次新指纹
	STR_ID_FP_TWICE_NOT_SAME,//两次输入的指纹不一致
	STR_ID_CHG_FP_SUCESS,//号指纹修改成功
	STR_ID_CHG_FAIL_RETRY,//修改失败，请重试
	STR_ID_INPUT_DEL_FP_NUM,//请输入要删除的编号或指纹
	STR_ID_FP_NOT_EXIST,//指纹不存在，请重新输入
	STR_ID_DEL_FP_CONFIRM,//号指纹按#确认删除，取消请按*
	STR_ID_PRESS_DEL_FP_AGAIN,//请再按一次要删除的指纹
	STR_ID_DEL_FP_SUCESS,//号指纹删除成功
	STR_ID_DEL_FAIL_RETRY,//删除失败，请重试
	STR_ID_CLR_FP_CONFIRM,//按#确认删除所有指纹，取消请按*
	STR_ID_CLR_FP_SUCESS,//删除所有指纹成功
	STR_ID_CLR_FP_FAIL,//删除所有指纹失败
	STR_ID_ADD_RFCARD,//添加RF卡
	STR_ID_CHG_RFCARD,//修改RF卡
	STR_ID_DEL_RFCARD,//删除RF卡
	STR_ID_CLR_RFCARD,//删除所有RF卡
	STR_ID_PRESS_RFCARD,//请刷卡
	STR_ID_PRESS_RFCARD_AGAIN,//请再刷一次
	STR_ID_ADD_RFCARD_SUCESS,//号RF卡添加成功
	STR_ID_RFCARD_EXIST,//RF卡已存在，请换张卡
	STR_ID_RFCARD_FULL,//RF卡已满，请联系管理员
	STR_ID_PRESS_OLD_RFCARD,//请刷旧卡
	STR_ID_PRESS_NEW_RFCARD,//请刷新卡
	STR_ID_PRESS_NEW_RFCARD_AGAIN,//请再刷一次新卡
	STR_ID_CHG_RFCARD_SUCESS,//号RF卡修改成功
	STR_ID_RFCARD_NOT_SAME,//新旧RF卡不能一致
	STR_ID_INPUT_DEL_RFCARD_NUM,//请输入要删除的编号或RF卡
	STR_ID_RFCARD_NOT_EXIST,//RF卡不存在，请重新输入
	STR_ID_RFCARD_DEL_CONFIRM,//号RF卡按#确认删除，取消请按*
	STR_ID_PRESS_DEL_RFCARD_AGAIN,//请再刷一次要删除的RF卡
	STR_ID_DEL_RFCARD_SUCESS,//号RF卡删除成功
	STR_ID_CLR_RFCARD_CONTINUE_CONFIRM,//按#确认删除所有RF卡，取消请按*
	STR_ID_CLR_RFCARD_SUCESS,//删除所有RF卡成功
	STR_ID_CLR_RFCARD_FAIL,//删除所有RF卡失败
	STR_ID_INPUT_OLD_ADMIN_PWD,//请输入旧管理员密码
	STR_ID_INPUT_NEW_ADMIN_PWD,//请输入新管理员密码
	STR_ID_INPUT_NEW_ADMIN_PWD_AGAIN,//请再次输入新管理员密码
	STR_ID_CHG_ADMIN_PWD_SUCESS,//管理员密码修改成功
	STR_ID_PWD_EXIST,//密码已存在，请重新输入
	STR_ID_NO1_ADMIN_FP,//1号管理指纹
	STR_ID_NO2_ADMIN_FP,//2号管理指纹
	STR_ID_PRESS_NEW_ADMIN_FP,//请按新的管理员指纹
	STR_ID_PRESS_NEW_ADMIN_FP_AGAIN,//请再按一次
	STR_ID_ADD_NO1_ADMIN_FP_SUCESS,//1号管理指纹添加成功
	STR_ID_ADD_NO2_ADMIN_FP_SUCESS,//2号管理指纹添加成功
	STR_ID_CLOSE_PRO_AUDIO,//关闭提示音
	STR_ID_OPEN_PRO_AUDIO,//开启提示音
	STR_ID_PRO_AUDIO,//提示音
	STR_ID_CLOSE_PRO_AUDIO_SUCESS,//关闭提示音成功
	STR_ID_CLOSE_PRO_AUDIO_FAIL,//关闭提示音失败
	STR_ID_OPEN_PRO_AUDIO_SUCESS,//开启提示音成功
	STR_ID_OPEN_PRO_AUDIO_FAIL,//开启提示音失败
	STR_ID_SIN_OPEN_MODE,//单开门方式
	STR_ID_DBL_OPEN_MODE,//双开门方式
	STR_ID_SIN_OPEN_MODE_SUCESS,//单开门方式设置成功
	STR_ID_SIN_OPEN_MODE_FAIL,//单开门方式设置失败
	STR_ID_DBL_OPEN_MODE_SUCESS,//双开门方式设置成功
	STR_ID_DBL_OPEN_MODE_FAIL,//双开门方式设置失败
	STR_ID_RESTORE_SUCESS,//恢复出厂设置成功
	STR_ID_RESTORE_FAIL,//恢复出厂设置失败
	STR_ID_ADD_ADMIN_PWD,//请添加管理员密码
	STR_ID_ADD_ADMIN_PWD_SUCESS,//管理员密码添加成功
	STR_ID_INPUT_ADMIN_PWD,//请输入管理员密码
	STR_ID_INPUT_ADMIN_PWD_AGAIN,//请再次输入管理员密码
	STR_ID_OPEN_DOOR,//已开锁
	STR_ID_CLOSE_DOOR,//已关锁
	STR_ID_PWD_WRONG_TRY,//密码错误,请重试
	STR_ID_FP_WRONG_TRY,//指纹错误，请重试
	STR_ID_RF_WRONG_TRY,//RF卡错误，请重试
	STR_ID_WRONG_EXCEED,//错误次数已超限制，请分钟后重试
	STR_ID_LOW_BATTERY,//电量低，请及时更换电池
	STR_ID_CHG_ADMIN_PWD,//修改管理员密码
	STR_ID_CHG_ADMIN_FP,//修改管理员指纹
	STR_ID_OPEN_MODE,//开门方式
	STR_ID_ADD_ADMIN_PWD_FIRST,//为了您的使用安全，请先添加管理员密码，按#键结束
	STR_ID_RESTORE_LOCK_CONTINUE_CONFIRM,//按#恢复出厂设置，取消请按*
	STR_ID_ADMIN_PWD,//管理员密码
	STR_ID_INPUT_NUM,//请输入编号
	STR_ID_FACTORY_MODE,//工程测试模式
	STR_ID_FM_KEY_INPUT,//请测试所有按键
	STR_ID_FM_KEY_LIGHT,//按键灯通过请按#, 失败请按*
	STR_ID_FM_OLED,//请测试屏幕，按#继续
	STR_ID_FM_MOTO,//马达测试，通过请按#, 失败请按*
	STR_ID_FM_SOUND,//喇叭测试，通过请按#, 失败请按*
	STR_ID_FM_RESET,//复位键测试，请按复位键
	STR_ID_FM_TEST_PASS,//测试通过
	STR_ID_FM_TEST_FAIL,//测试失败
	STR_ID_FM_TEST_TIPS,//通过请按#, 失败请按*
	STR_ID_APP_SYN,//请使用APP同步时间
	STR_ID_APP_ADD_SUC,//APP添加成功
	STR_ID_APP_ADD_FAIL,//APP添加失败
	STR_ID_KEY,//按键
	STR_ID_KEY_LIGHT,//按键灯
	STR_ID_OLED,//屏幕
	STR_ID_MOTO,//马达
	STR_ID_SOUND,//喇叭
	STR_ID_RESET,//重启键
	STR_ID_RESTORE_STARTING,//正在恢复出厂设置
	STR_ID_SET_SUCESS,//时间设置成功
	STR_ID_DECODE,//解码随机码
	STR_ID_MAX_COUNT,
	STR_ID_INVALID_ID = 0xFF
}sys_str_id;

typedef enum
{
	LOCK_BMP_BAT_0 = 0x00,
	LOCK_BMP_BAT_1,
	LOCK_BMP_BAT_2,
	LOCK_BMP_BAT_3,
	LOCK_ADMIN,
	LOCK_INPUT,
	LOCK_STAR,
	LOCK_BMP_MAX,
	LOCK_BMP_INVALID
}lock_bmp_enum;


#endif //__MMI_COM_H__

