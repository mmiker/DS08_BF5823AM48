#ifndef __MMI_TIME_H__
#define __MMI_TIME_H__
#include "mmi_feature.h"
#ifdef __LOCK_DECODE_SUPPORT__
#include "mmi_decode.h"

typedef unsigned int time_t;
extern unsigned char temp_data[10];

typedef struct tm
{
    int tm_sec;  /* 秒 – 取值区间为[0,59] */
    int tm_min;  /* 分 - 取值区间为[0,59] */
    int tm_hour; /* 时 - 取值区间为[0,23] */
    int tm_mday; /* 一个月中的日期 - 取值区间为[1,31] */
    int tm_mon;  /* 月份（从一月开始，0代表一月） - 取值区间为[0,11] */
    int tm_year; /* 年份，其值等于实际年份减去1900 */
} tm;
extern tm t;

unsigned char division_int(unsigned char *p_data, unsigned int x, unsigned char len, unsigned char *dest);
unsigned long division_rem(unsigned char *p_data, unsigned int x, unsigned char len);
void ntp(unsigned char *decode_time, struct tm *t);
time_t mktime(struct tm dt);

#endif //__LOCK_DECODE_SUPPORT__
#endif
