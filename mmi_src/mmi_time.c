#ifndef __MMI_TIME_C__
#define __MMI_TIME_C__
#include "mmi_feature.h"
#ifdef __LOCK_DECODE_SUPPORT__
#include <stdio.h>
#include <string.h>
#include "mmi_time.h"
#include "dqiot_drv.h"

unsigned char temp_data[10] = {0xff};
tm t;

const char Days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
static time_t mon_yday[2][12] =
    {
        {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334},
        {0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335},
};

/**
  * @brief  时间戳除法取整
  * @param  data 数组
  * @param  x 除数
  * @param  len 长度
  * @param  dest 存入数组
  * @return status
  * @note   none
  * @see    none
  */
unsigned char division_int(unsigned char *p_data, unsigned int x, unsigned char len, unsigned char *dest)
{
    unsigned char i, j;
    unsigned long temp_int = 0, temp_rem = 0; //temp_int整数，temp_rem余数
    unsigned char d_data[10];
    unsigned char p_data_len = 10;

    /* 获取数据包长度 */
    for (i = 0; i < len; i++)
    {
        if (p_data[i] == 0xff)
        {
            p_data_len = i;
            break;
        }
    }

    memset(&d_data, 0xff, sizeof(d_data));
    /* 计算除数 */
    for (j = 0, i = 0; i < p_data_len; i++)
    {
        temp_int = (temp_rem * 10 + p_data[i]) / x;
        temp_rem = (temp_rem * 10 + p_data[i]) % x;

        d_data[j] = temp_int;
        j++;
    }

    /* 去除开头的0 */
    for (i = 0; i < len; i++)
    {
        if (d_data[i] != 0)
            break;
    }

    /* 赋值  */
    for (j = 0; j < len; j++)
    {
        if (i < len)
        {
            dest[j] = d_data[i];
            i++;
        }
        else
            dest[j] = 0xff;
    }

    // printf("p_data_len is %d\n", (int)p_data_len);
    // for (i = 0; i < 10; i++)
    //     printf("dest is %d\n", (int)dest[i]);
    // printf("############\n");

    return 0;
}

/**
  * @brief  时间戳除法取余
  * @param  data 数组
  * @param  x 除数
  * @param  len 长度
  * @return status
  * @note   none
  * @see    none
  */
unsigned long division_rem(unsigned char *p_data, unsigned int x, unsigned char len)
{
    unsigned char i;
    unsigned long temp_int = 0, temp_rem = 0; //temp_int整数，temp_rem余数
    unsigned char p_data_len = 10;

    /* 获取数据包长度 */
    for (i = 0; i < len; i++)
    {
        if (p_data[i] == 0xff)
        {
            p_data_len = i;
            break;
        }
    }

    /* 计算除数 */
    for (i = 0; i < p_data_len; i++)
    {
        temp_int = (temp_rem * 10 + p_data[i]) / x;
        temp_rem = (temp_rem * 10 + p_data[i]) % x;
    }

    return temp_rem;
}

/**
  * @brief  时间戳转换时间
  * @param  decode_time 时间戳
  * @param  t 存放地址
  * @return none
  * @note   none
  * @see    none
  */
void ntp(unsigned char *decode_time, struct tm *t)
{
    unsigned long time = 0;
    unsigned long Pass4year;
    int hours_per_year;

    //取秒时间
    t->tm_sec = division_rem(decode_time, 60, 10);
    division_int(decode_time, 60, 10, temp_data);

    //取分钟时间
    t->tm_min = division_rem(temp_data, 60, 10);
    division_int(temp_data, 60, 10, temp_data);
    time = CharToInt_long(temp_data, 10);

    //取过去多少个四年，每四年有 1461*24 小时
    Pass4year = (time / (1461L * 24L));

    //计算年份
    t->tm_year = (Pass4year << 2) + 1970;

    //四年中剩下的小时数
    time %= 1461L * 24L;

    //校正闰年影响的年份，计算一年中剩下的小时数
    for (;;)
    {
        /* 一年的小时数 */
        hours_per_year = 365 * 24;
        /* 判断闰年 */
        if ((t->tm_year & 3) == 0)
        {
            /* 是闰年，一年则多24小时，即一天 */
            hours_per_year += 24;
        }
        if (time < hours_per_year)
        {
            break;
        }
        t->tm_year++;
        time -= hours_per_year;
    }

    /* 小时数 */
    t->tm_hour = (int)(time % 24);
    /* 一年中剩下的天数 */
    time /= 24;
    /* 假定为闰年 */
    time++;
    /* 校正闰年的误差，计算月份，日期 */
    if ((t->tm_year & 3) == 0)
    {
        if (time > 60)
        {
            time--;
        }
        else
        {
            if (time == 60)
            {
                t->tm_mon = 1;
                t->tm_mday = 29;
                return;
            }
        }
    }
    /* 计算月日 */
    for (t->tm_mon = 0; Days[t->tm_mon] < time; t->tm_mon++)
    {
        time -= Days[t->tm_mon];
    }

    t->tm_mday = (int)(time);

    // printf("A %d-%d-%d %d:%d:%d\r\n", t->tm_year, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
    // printf("############\n");

    return;
}

/**
  * @brief  计算秒数
  * @param  年
  * @return 秒数
  * @note   none
  * @see    none
  */
int isleap(int year)
{
    return (year) % 4 == 0 && ((year) % 100 != 0 || (year) % 400 == 0);
}

/**
  * @brief  时间转化成时间戳
  * @param  时间
  * @return 时间戳
  * @note   none
  * @see    none
  */
time_t mktime(struct tm dt)
{
    time_t result;
    int i = 0;
    // 以平年时间计算的秒数
    result = (dt.tm_year - 1970) * 365 * 24 * 3600 +
             (mon_yday[isleap(dt.tm_year)][dt.tm_mon - 1] + dt.tm_mday - 1) * 24 * 3600 +
             dt.tm_hour * 3600 + dt.tm_min * 60 + dt.tm_sec;
    // 加上闰年的秒数
    for (i = 1970; i < dt.tm_year; i++)
    {
        if (isleap(i))
        {
            result += 24 * 3600;
        }
    }
    return (result);
}

// /* 使用方法 */
// void main()
// {
//     struct tm t;
//     get_decode.tim_key_10 = 1619063988;
//     ntp(get_decode.tim_key_10, &t);
//     printf("A %d-%d-%d %d:%d:%d\r\n", t.tm_year, t.tm_mon + 1, t.tm_mday, t.tm_hour + 8, t.tm_min, t.tm_sec);
//     return;
// }

#endif //__LOCK_DECODE_SUPPORT__
#endif
