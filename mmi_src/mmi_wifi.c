#ifndef __MMI_WIFI_C__
#define __MMI_WIFI_C__

#include "mmi_feature.h"
#ifdef __LOCK_WIFI_SUPPORT__
#include "dqiot_drv_wifi.h"
#include "mmi_sys.h"
#include "mmi_ms.h"
#include "mmi_audio.h"
#include "mmi_fs.h"
#include "delay.h"
#include "mmi_wifi.h"
// #include <stdio.h>

static unsigned int wifi_check_times = 0;
/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_wifi_check(void)
{
  return wifi_wake_up(); //1:false  0: true
}

/**
  * @brief  智能配网（发送）
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
unsigned char mmi_dq_wifi_setting(void)
{
  unsigned char ret = 1;
  if (wifi_check_times > 0)
    return 0;
  wifi_wake_up();
  delay_ms(100);
  if (wifi_net_connect_send() == 0)
  {
    delay_ms(250);
    ret = wifi_net_connect_send();
  }
  if (ret == 1)
  {
    wifi_check_times = 1;
    mmi_dq_sys_set_wifi_check(0);
  }
  return ret;
}

/**
  * @brief  Airkiss配网（发送）
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
unsigned char mmi_dq_wifi_arikiss_con(void)
{
  unsigned char ret = 1;
  if (wifi_check_times > 0)
    return 0;
  wifi_wake_up();
  delay_ms(100);
  if (wifi_net_airkiss_connect_send() == 0)
  {
    delay_ms(250);
    ret = wifi_net_airkiss_connect_send();
  }
  if (ret == 1)
  {
    wifi_check_times = 1;
    mmi_dq_sys_set_wifi_check(0);
  }
  return ret;
}

/**
  * @brief  二维码配网（发送）
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
unsigned char mmi_dq_wifi_code_con(void)
{
  unsigned char ret = 1;
  if (wifi_check_times > 0)
    return 0;
  wifi_wake_up();
  delay_ms(100);
  if (wifi_net_code_connect_send() == 0)
  {
    delay_ms(250);
    ret = wifi_net_code_connect_send();
  }
  if (ret == 1)
  {
    wifi_check_times = 1;
    mmi_dq_sys_set_wifi_check(0);
  }
  return ret;
}

/**
  * @brief  连网失败
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
void mmi_dq_wifi_connected_fail(void)
{
  //mmi_dq_fs_set_wifi_setting(0);
  if (SYS_STATUS_WIFI_MODE == mmi_dq_ms_get_sys_state())
    mmi_dq_ms_set_sys_state(SYS_STATUS_IDLE);
  else if (SYS_STATUS_ENTER_SLEEP == mmi_dq_ms_get_sys_state())
    mmi_dq_sys_wake_up();
  mmi_dq_aud_play_with_id(AUD_ID_TIME_OUT);
  mmi_dq_ms_set_sys_state(SYS_STATUS_WAIT_FOR_ENTER_SLEEP);
  return;
}

/**
  * @brief  连网成功
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
void mmi_dq_wifi_connected_suc(void)
{
  //mmi_dq_fs_set_wifi_setting(1);
  if (SYS_STATUS_WIFI_MODE == mmi_dq_ms_get_sys_state())
    mmi_dq_ms_set_sys_state(SYS_STATUS_IDLE);
  else if (SYS_STATUS_ENTER_SLEEP == mmi_dq_ms_get_sys_state())
    mmi_dq_sys_wake_up();
  mmi_dq_aud_play_with_id(AUD_ID_SET_SUCESS);
  return;
}

/**
  * @brief  配网状态（接收）
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
void mmi_dq_wifi_check_connect(void)
{
  static unsigned char wifi_check_connect_flag = 0;
  uint8_t retval = 0;
  wifi_check_times++;
  retval = wifi_net_connect_state();
  if (retval == 1)
  {
    wifi_check_connect_flag++;
    if (wifi_check_connect_flag >= 2)
    {
      mmi_dq_wifi_connected_suc();
      wifi_check_connect_flag = 0;
      wifi_check_times = 0;
      return;
    }
  }
  else
  {
    wifi_check_connect_flag = 0;
  }

  if (wifi_check_times > 60 || retval == 2)
  {
    mmi_dq_wifi_connected_fail();
    wifi_check_times = 0;
  }
  else
    mmi_dq_sys_set_wifi_check(0);
}

/**
  * @brief  远程开门（发送）
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
unsigned char mmi_dq_wifi_open_ask(void)
{
  unsigned char ret = 1;
  if (wifi_check_times > 0)
    return 0;
  mmi_dq_wifi_wakeup();
  delay_ms(100);
  if (wifi_open_ask() == 0)
  {
    delay_ms(250);
    ret = wifi_open_ask();
  }
  if (ret == 1)
  {
    wifi_check_times = 1;
    mmi_dq_sys_set_wifi_check(1);
  }
  return ret;
}

/**
  * @brief  远程开门（接收）
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
void mmi_dq_wifi_check_open(void)
{
  unsigned char state = wifi_open_reply_get();
  wifi_check_times++;
  if (state == 1)
  {
    if (SYS_STATUS_ENTER_SLEEP == mmi_dq_ms_get_sys_state())
      mmi_dq_sys_wake_up();
    mmi_dq_sys_door_open(SYS_OPEN_BY_WIFI);
    wifi_check_times = 0;
  }
  else if (state == 2 || wifi_check_times > 30)
  {
    if (SYS_STATUS_ENTER_SLEEP == mmi_dq_ms_get_sys_state())
      mmi_dq_sys_wake_up();
    if (state == 2)
      mmi_dq_aud_play_with_id(AUD_ID_RESTORE_FAIL);
    else if (mmi_dq_ms_get_sys_state() == SYS_STATUS_IDLE)
    {
      mmi_dq_aud_play_with_id(AUD_ID_TIME_OUT);
      mmi_dq_ms_set_sys_state(SYS_STATUS_WAIT_FOR_ENTER_SLEEP);
    }
    wifi_check_times = 0;
  }
  else
    mmi_dq_sys_set_wifi_check(1);
}

/**
  * @brief  添加删除密码/指纹/RF卡
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
void mmi_dq_wifi_cmd_add_del(void)
{
  uint16_t waittime = 100;

  while (--waittime)
  {
    delay_ms(1);
    if (wifi_cmd_add_del() != 0)
      break;
  }
}

/**
  * @brief  密码添加成功
  * @param  index
  * @return none
  * @note   none
  * @see    none
  */
void mmi_dq_wifi_add_password(uint8_t index)
{
  mmi_dq_wifi_wakeup();

  wifi_add_password(index);
}

/**
  * @brief  密码删除成功
  * @param  index
  * @return none
  * @note   none
  * @see    none
  */
void mmi_dq_wifi_del_password(uint8_t index)
{
  mmi_dq_wifi_wakeup();

  wifi_del_password(index);
}

/**
  * @brief  指纹添加成功
  * @param  index
  * @return none
  * @note   none
  * @see    none
  */
void mmi_dq_wifi_add_fp(uint8_t index)
{
  mmi_dq_wifi_wakeup();

  wifi_add_fp(index);
}

/**
  * @brief  指纹删除成功
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
void mmi_dq_wifi_del_fp(uint8_t index)
{
  mmi_dq_wifi_wakeup();

  wifi_del_fp(index);
}

/**
  * @brief  RF卡添加成功
  * @param  index
  * @return none
  * @note   none
  * @see    none
  */
void mmi_dq_wifi_add_rfid_suc(uint8_t index)
{
  mmi_dq_wifi_wakeup();

  wifi_add_rf(index);
}

/**
  * @brief  RF卡删除成功
  * @param  index
  * @return none
  * @note   none
  * @see    none
  */
void mmi_dq_wifi_del_rfid_suc(uint8_t index)
{
  mmi_dq_wifi_wakeup();

  wifi_del_rf(index);
}

/**
  * @brief  密码全部清除
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
void mmi_dq_wifi_clr_pwd_suc(void)
{
  mmi_dq_wifi_wakeup();

  wifi_clr_pwd();
}

/**
  * @brief  指纹全部清除
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
void mmi_dq_wifi_clr_fps_suc(void)
{
  mmi_dq_wifi_wakeup();

  wifi_clr_fp();
}

/**
  * @brief  RF卡全部清除
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
void mmi_dq_wifi_clr_rfid_suc(void)
{
  mmi_dq_wifi_wakeup();

  wifi_clr_rf();
}

/**
  * @brief  密码开门
  * @param  index
  * @return none
  * @note   none
  * @see    none
  */
void mmi_dq_wifi_open_by_password(uint8_t index)
{
  mmi_dq_wifi_wakeup();

  wifi_open_by_password(index);
}

/**
  * @brief  指纹开门
  * @param  index
  * @return none
  * @note   none
  * @see    none
  */
void mmi_dq_wifi_open_by_fp(uint8_t index)
{
  mmi_dq_wifi_wakeup();

  wifi_open_by_fp(index);
}

/**
  * @brief  RF卡开门
  * @param  index
  * @return none
  * @note   none
  * @see    none
  */
void mmi_dq_wifi_open_by_rfid(uint8_t index)
{
  mmi_dq_wifi_wakeup();

  wifi_open_by_rfid(index);
}

/**
  * @brief  远程开门成功
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
void mmi_dq_wifi_open_by_wifi(void)
{
  mmi_dq_wifi_wakeup();

  wifi_open_by_wifi();
}

/**
  * @brief  应急钥匙开门成功
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
void mmi_dq_wifi_open_by_key(void)
{
  mmi_dq_wifi_wakeup();

  wifi_open_by_key();
}

/**
  * @brief  门未关
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
void mmi_dq_wifi_close_over_time(void)
{
  wifi_close_over_time();
}

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_wifi_door_close(void)
{
  wifi_door_close();
}

/**
  * @brief  震动报警
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
void mmi_dq_wifi_via_alarm(void)
{
  mmi_dq_wifi_wakeup();

  wifi_via_alarm();
}

/**
  * @brief  多次密码错误
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
void mmi_dq_wifi_pw_alarm(void)
{
  mmi_dq_wifi_wakeup();

  wifi_pw_alarm();
}

/**
  * @brief  多次指纹错误
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
void mmi_dq_wifi_fp_alarm(void)
{
  mmi_dq_wifi_wakeup();

  wifi_fp_alarm();
}

/**
  * @brief  多次RF卡错误
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
void mmi_dq_wifi_rfid_alarm(void)
{
  mmi_dq_wifi_wakeup();

  wifi_rf_alarm();
}

/**
  * @brief  低电量
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
void mmi_dq_wifi_lowpower_alarm(void)
{
  static uint8_t wifi_lowpower_flag = 0;
  if (wifi_lowpower_flag == 0)
  {
    wifi_lowpower_flag = 1;
    mmi_dq_wifi_wakeup();

    wifi_lowpower_alarm();
  }
}

/**
  * @brief  睡眠
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
void mmi_dq_wifi_sleep(void)
{
  wifi_sleep_mode();
}

/**
  * @brief  唤醒
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
void mmi_dq_wifi_wakeup(void)
{
  wifi_wake_up();

  delay_ms(150);
}

/**
  * @brief  拍照
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
void mmi_dq_wifi_take_photos(void)
{
  mmi_dq_wifi_wakeup();

  if (wifi_take_photos() == 1)
    mmi_dq_aud_play_with_id(AUD_BASE_ID_SUCCESS);
}

/**
  * @brief  录像
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
void mmi_dq_wifi_take_videos(void)
{
  mmi_dq_wifi_wakeup();

  if (wifi_take_videos() == 1)
    mmi_dq_aud_play_with_id(AUD_BASE_ID_SUCCESS);
}

/**
  * @brief  拍照录像开关
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
void mmi_dq_wifi_pv_switch(void)
{
  uint8_t retval;
  uint16_t waittime = 100;

  mmi_dq_wifi_wakeup();
  wifi_pv_switch_send();

  while (--waittime)
  {
    delay_ms(1);
    retval = wifi_pv_switch_get();
    if (retval != 0xff)
      break;
  }
}

/**
  * @brief  检查网络状态
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
void mmi_dq_wifi_check_net(void)
{
  if (wifi_check_net() == 1)
    mmi_dq_aud_play_with_id(AUD_BASE_ID_SUCCESS);
  else
    mmi_dq_aud_play_with_id(AUD_BASE_ID_FAIL);
}

/**
  * @brief  协迫密码开门
  * @param  index
  * @return none
  * @note   none
  * @see    none
  */
void mmi_dq_wifi_send_pwd_110(uint8_t index)
{
  mmi_dq_wifi_wakeup();
  wifi_send_pwd_110();
  delay_ms(20);
  wifi_open_by_password(index);
}

/**
  * @brief  协迫密码开门
  * @param  index
  * @return none
  * @note   none
  * @see    none
  */
void mmi_dq_wifi_send_fp_110(uint8_t index)
{
  mmi_dq_wifi_wakeup();
  wifi_send_fp_110();
  delay_ms(20);
  wifi_open_by_fp(index);
}

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_wifi_set_110(void)
{
  mmi_dq_wifi_wakeup();
  wifi_set_110();
}

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_wifi_get_running_flag(void)
{
  if (wifi_check_times > 0)
    return 1;
  return 0;
}
#endif
#endif
