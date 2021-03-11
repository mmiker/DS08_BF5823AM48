#ifndef __DQIOT_WIFI_H__
#define __DQIOT_WIFI_H__

//#define __I2C_SW__
#include "dqiot_drv.h"

#define WIFI_ADDR 0x50

#define WIFI_CMD_ADD_PW					'p'
#define WIFI_CMD_DEL_PW 				'P'
#define WIFI_CMD_ADD_FP					'f'
#define WIFI_CMD_DEL_FP					'F'
#define WIFI_CMD_PW_OPEN				'o'
#define WIFI_CMD_WF_OPEN				'O'
#define WIFI_CMD_FP_OPEN				'x'
#define WIFI_CMD_RF_OPEN				'r'
#define WIFI_CMD_KEY_OPEN				'z'
#define WIFI_CMD_CLOSE					'c'
#define WIFI_CMD_VIA_ALARM				'v'
#define WIFI_CMD_PW_ALARM				't'
#define WIFI_CMD_FP_ALARM				'T'
#define WIFI_CMD_RF_ALARM				'R'

//#define WIFI_CMD_UNCLOSE_ALARM			'N'
#define WIFI_CMD_LOWPOWER_ALARM			'l'

#define WIFI_CMD_WAKEUP					'w'
#define WIFI_CMD_SLEEP					's'


#define WIFI_CMD_NET_CON				'i'
#define WIFI_CMD_NET_STATE				'I'
#define WIFI_CMD_AUTHORIZE_STATE		'M'
#define WIFI_CMD_WF_OPEN_ASK			'k'
#define WIFI_CMD_WF_OPEN_REPLY			'K'

#define WIFI_CMD_WF_OPEN_FP_110			'A'       // 23
#define WIFI_CMD_WF_OPEN_PSW_110		'a'       // 23
#define WIFI_CMD_WF_SET_110		        'B'       // 23

#define WIFI_CMD_CLOSE_OVER_TIME		'N'

uint8_t wifi_net_connect_send(void);
uint8_t wifi_net_connect_state(void);

uint8_t wifi_open_ask(void);
uint8_t wifi_open_reply_get(void);

void wifi_close_over_time(void);

unsigned char wifi_wake_up(void);

void wifi_sleep_mode(void);

void wifi_add_password(void);

void wifi_del_password(void);

void wifi_add_fp(void);

void wifi_del_fp(void);

void wifi_open_by_password(void);

void wifi_open_by_fp(void);

void wifi_open_by_rfid(void);

void wifi_open_by_wifi(void);

void wifi_open_by_key(void);

void wifi_door_close(void);

void wifi_via_alarm(void);

void wifi_pw_alarm(void);

void wifi_fp_alarm(void);

void wifi_rf_alarm(void);

//void wifi_unclose_alarm(void);

void wifi_lowpower_alarm(void);


void wifi_send_fp_110(void);

void wifi_send_pwd_110(void);

void wifi_set_110(void);

#endif

