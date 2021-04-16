#ifndef __MMI_WIFI_H__
#define __MMI_WIFI_H__
#include "mmi_feature.h"
#ifdef __LOCK_WIFI_SUPPORT__
/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_wifi_check(void);

/**
  * @brief  智能配网（发送）
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
unsigned char mmi_dq_wifi_setting(void);

/**
  * @brief  Airkiss配网（发送）
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
unsigned char mmi_dq_wifi_arikiss_con(void);

/**
  * @brief  二维码配网（发送）
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
unsigned char mmi_dq_wifi_code_con(void);

/**
  * @brief  智能配网（接收）
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
void mmi_dq_wifi_check_connect(void);

/**
  * @brief  远程开门（发送）
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
unsigned char mmi_dq_wifi_open_ask(void);

/**
  * @brief  远程开门（接收）
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
void mmi_dq_wifi_check_open(void);

/**
  * @brief  添加删除密码/指纹/RF卡
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
void mmi_dq_wifi_cmd_add_del(void);

/**
  * @brief  密码添加成功
  * @param  index
  * @return none
  * @note   none
  * @see    none
  */
void mmi_dq_wifi_add_password(uint8_t index);

/**
  * @brief  密码删除成功
  * @param  index
  * @return none
  * @note   none
  * @see    none
  */
void mmi_dq_wifi_del_password(uint8_t index);

/**
  * @brief  指纹添加成功
  * @param  index
  * @return none
  * @note   none
  * @see    none
  */
void mmi_dq_wifi_add_fp(uint8_t index);

/**
  * @brief  指纹删除成功
  * @param  index
  * @return none
  * @note   none
  * @see    none
  */
void mmi_dq_wifi_del_fp(uint8_t index);

/**
  * @brief  RF卡添加成功
  * @param  index
  * @return none
  * @note   none
  * @see    none
  */
void mmi_dq_wifi_add_rfid_suc(uint8_t index);

/**
  * @brief  RF卡删除成功
  * @param  index
  * @return none
  * @note   none
  * @see    none
  */
void mmi_dq_wifi_del_rfid_suc(uint8_t index);

/**
  * @brief  密码全部清除
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
void mmi_dq_wifi_clr_pwd_suc(void);

/**
  * @brief  指纹全部清除
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
void mmi_dq_wifi_clr_fps_suc(void);

/**
  * @brief  RF卡全部清除
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
void mmi_dq_wifi_clr_rfid_suc(void);

/**
  * @brief  密码开门
  * @param  index
  * @return none
  * @note   none
  * @see    none
  */
void mmi_dq_wifi_open_by_password(uint8_t index);

/**
  * @brief  指纹开门
  * @param  index
  * @return none
  * @note   none
  * @see    none
  */
void mmi_dq_wifi_open_by_fp(uint8_t index);

/**
  * @brief  RF卡开门
  * @param  index
  * @return none
  * @note   none
  * @see    none
  */
void mmi_dq_wifi_open_by_rfid(uint8_t index);

/**
  * @brief  远程开门成功
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
void mmi_dq_wifi_open_by_wifi(void);

/**
  * @brief  应急钥匙开门成功
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
void mmi_dq_wifi_open_by_key(void);

/**
  * @brief  门未关
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
void mmi_dq_wifi_close_over_time(void);

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_wifi_door_close(void);

/**
  * @brief  震动报警
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
void mmi_dq_wifi_via_alarm(void);

/**
  * @brief  多次密码错误
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
void mmi_dq_wifi_pw_alarm(void);

/**
  * @brief  多次指纹错误
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
void mmi_dq_wifi_fp_alarm(void);

/**
  * @brief  多次RF卡错误
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
void mmi_dq_wifi_rfid_alarm(void);

/**
  * @brief  低电量
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
void mmi_dq_wifi_lowpower_alarm(void);

/**
  * @brief  睡眠
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
void mmi_dq_wifi_sleep(void);

/**
  * @brief  唤醒
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
void mmi_dq_wifi_wakeup(void);

/**
  * @brief  拍照
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
void mmi_dq_wifi_take_photos(void);

/**
  * @brief  录像
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
void mmi_dq_wifi_take_videos(void);

/**
  * @brief  拍照录像开关
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
void mmi_dq_wifi_pv_switch(void);

/**
  * @brief  检查网络状态
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
void mmi_dq_wifi_check_net(void);

/**
  * @brief  协迫密码开门
  * @param  index
  * @return none
  * @note   none
  * @see    none
  */
void mmi_dq_wifi_send_pwd_110(uint8_t index);

/**
  * @brief  协迫密码开门
  * @param  index
  * @return none
  * @note   none
  * @see    none
  */
void mmi_dq_wifi_send_fp_110(uint8_t index);

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_wifi_set_110(void);

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_wifi_get_running_flag(void);

#endif
#endif //__MMI_WIFI_H__
