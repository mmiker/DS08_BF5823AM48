#ifndef __MMI_DECODE_H__
#define __MMI_DECODE_H__
#include "mmi_feature.h"
#ifdef __LOCK_DECODE_SUPPORT__

typedef struct decode_data
{
    unsigned int top_three;
    unsigned int rev_three;
    unsigned int exg_key_8[8];
    unsigned int exg_key_9[9];
    unsigned int exg_key_10[10];
    unsigned int sec_key_8[8];
    unsigned int sec_key_9[9];
    unsigned int sec_key_10[10];
} decode_data;

unsigned char mmi_dq_decode_app_random_code(unsigned char *random_code);

#endif //__LOCK_DECODE_SUPPORT__
#endif //__MMI_DECODE_H__
