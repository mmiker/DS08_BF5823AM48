#ifndef __DQIOT_WIFI_H__
#define __DQIOT_WIFI_H__

//#define __I2C_SW__
#include "dqiot_drv.h"

#define WIFI_ADDR 0x50

#define WIFI_CMD_ADD_PW					'p'
#define WIFI_CMD_DEL_PW 				'P'
#define WIFI_CMD_ADD_FP					'f'
#define WIFI_CMD_DEL_FP					'F'
#define WIFI_CMD_ADD_RF					'r'
#define WIFI_CMD_DEL_RF					'R'
#define WIFI_CMD_CLR_PW                 'c'
#define WIFI_CMD_CLR_FP                 'C'
#define WIFI_CMD_CLR_RF                 'n'
#define WIFI_CMD_PW_OPEN				'o'
#define WIFI_CMD_WF_OPEN				'O'
#define WIFI_CMD_FP_OPEN				'x'
#define WIFI_CMD_RF_OPEN				'y'
#define WIFI_CMD_KEY_OPEN				'z'
#define WIFI_CMD_CLOSE					'c'
#define WIFI_CMD_VIA_ALARM				'v'
#define WIFI_CMD_PW_ALARM				't'
#define WIFI_CMD_FP_ALARM				'T'
#define WIFI_CMD_RF_ALARM				'u'

//#define WIFI_CMD_UNCLOSE_ALARM			'N'
#define WIFI_CMD_LOWPOWER_ALARM			'l'

#define WIFI_CMD_WAKEUP					'w'
#define WIFI_CMD_SLEEP					's'

#define WIFI_CMD_NET_CON				'i' //智能配网
#define WIFI_CMD_AIRKISS_NET_CON        'W' //AirKiss配网
#define WIFI_CMD_CODE_NET_CON           'G' //二维码配网
#define WIFI_CMD_NET_STATE				'I'
#define WIFI_CMD_AUTHORIZE_STATE		'M'
#define WIFI_CMD_WF_OPEN_ASK			'k'
#define WIFI_CMD_WF_OPEN_REPLY			'K'

#define WIFI_CMD_WF_OPEN_FP_110			'A'       // 23
#define WIFI_CMD_WF_OPEN_PSW_110		'a'       // 23
#define WIFI_CMD_WF_SET_110		        'B'       // 23

#define WIFI_CMD_CLOSE_OVER_TIME		'N'

#define WIFI_CMD_TAKE_PHOTOS            'g' //拍照
#define WIFI_CMD_TAKE_VIDEOS            'h' //录像
#define WIFI_CMD_CHECK_NET              'q' //查询网络状态
#define WIFI_CMD_ADD_DEL                'B' //添加删除密码/指纹/RF卡
#define WIFI_CMD_PV_SWITCH_SEND         'j' //拍照录像开关(发送)
#define WIFI_CMD_PV_SWITCH_GET          'J' //拍照录像开关(接收)

extern unsigned char wifi_add_flag;

uint8_t wifi_net_connect_send(void);
uint8_t wifi_net_airkiss_connect_send(void);
uint8_t wifi_net_code_connect_send(void);
uint8_t wifi_net_connect_state(void);
uint8_t wifi_check_net(void);
uint8_t wifi_take_photos(void);
uint8_t wifi_take_videos(void);
uint8_t wifi_cmd_add_del(void);
uint8_t wifi_open_ask(void);
uint8_t wifi_open_reply_get(void);
uint8_t wifi_data_package(uint8_t cmd, uint8_t pv, uint8_t index);

void wifi_close_over_time(void);

unsigned char wifi_wake_up(void);

void wifi_sleep_mode(void);

void wifi_add_password(uint8_t index);

void wifi_del_password(uint8_t index);

void wifi_add_fp(uint8_t index);

void wifi_del_fp(uint8_t index);

void wifi_add_rf(uint8_t index);

void wifi_del_rf(uint8_t index);

void wifi_clr_pwd(void);

void wifi_clr_fp(void);

void wifi_clr_rf(void);

void wifi_open_by_password(uint8_t index);

void wifi_open_by_fp(uint8_t index);

void wifi_open_by_rfid(uint8_t index);

void wifi_open_by_wifi(void);

void wifi_open_by_key(void);

void wifi_door_close(void);

void wifi_via_alarm(void);

void wifi_pw_alarm(void);

void wifi_fp_alarm(void);

void wifi_rf_alarm(void);

//void wifi_unclose_alarm(void);

void wifi_lowpower_alarm(void);

void wifi_pv_switch_send(void);

uint8_t wifi_pv_switch_get(void);

void wifi_send_fp_110(void);

void wifi_send_pwd_110(void);

void wifi_set_110(void);

#endif

