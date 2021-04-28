#ifndef __MMI_DECODE_H__
#define __MMI_DECODE_H__
#include "mmi_feature.h"
#ifdef __LOCK_DECODE_SUPPORT__
#include "mmi_time.h"

typedef struct otp_exchg_num
{
    unsigned char num;
    unsigned char exchg_num[5];
} otp_exchg_num;

typedef struct decode_data
{
    unsigned char exg_key_8[8];
    unsigned char exg_key_9[9];
    unsigned char exg_key_10[10];
    unsigned char sec_key_8[8];
    unsigned char sec_key_9[9];
    unsigned char sec_key_10[10];
    unsigned char tim_key_10[10];
    unsigned char chk_key_2[2];
    // unsigned long start_hour; //6byte
} decode_data;

typedef enum
{
    syn_start_time = 0x00,
    cmd_play_status = 0xff,
} decode_cmd;

typedef enum
{
    DECODE_CMD_SUCCESS = 0x00,
    DECODE_CMD_FAILED = 0x01,
    DECODE_CMD_INVALID = 0xff,
}decode_status;

extern otp_exchg_num g_pwd_signed_data[10];
extern decode_data get_decode;
extern decode_cmd exec_cmd;

void decode_check_code(unsigned char *random_code, unsigned char len);
void mmi_dq_decode_app_random_code(unsigned char *random_code);
void decode_time_stamp_10num(unsigned char *pwd, unsigned char len, unsigned char *sec_key, unsigned char *exg_key);
decode_status dq_otp_syn_start_time(unsigned char *p_data);

unsigned long CharToInt_long(unsigned char *p_data, unsigned char len);
unsigned char CharToInt_2long(const unsigned char *source, unsigned long *high, unsigned long *low);
unsigned char IntToByteStr_2long(unsigned long high, unsigned long low, char *dest, int highLen, int lowhigh);
int dq_sdk_HexcharToInt(unsigned char *source, int length);

#endif //__LOCK_DECODE_SUPPORT__
#endif //__MMI_DECODE_H__
