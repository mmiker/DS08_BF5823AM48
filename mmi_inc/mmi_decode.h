#ifndef __MMI_DECODE_H__
#define __MMI_DECODE_H__
#include "mmi_feature.h"
#ifdef __LOCK_DECODE_SUPPORT__

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
    otp_exchg_num g_pwd_signed_data[10];
} decode_data;

unsigned char mmi_dq_decode_app_random_code(unsigned char *random_code);
void decode_time_stamp_10num(unsigned char *pwd, unsigned char len, unsigned char *sec_key, unsigned char *exg_key, unsigned char *sec_pwd);
void dq_sdk_CharToHexByte(const unsigned char *source, char *dest, int sourceLen);
unsigned char CharToInt_2long(const unsigned char *source, unsigned long *high, unsigned long *low);
unsigned char IntToByteStr_2long(unsigned long high, unsigned long low, char *dest, int highLen, int lowhigh);

#endif //__LOCK_DECODE_SUPPORT__
#endif //__MMI_DECODE_H__
