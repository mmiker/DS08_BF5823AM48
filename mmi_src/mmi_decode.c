#ifndef __MMI_DECODE_C__
#define __MMI_DECODE_C__
#include "mmi_feature.h"
#ifdef __LOCK_DECODE_SUPPORT__
#include "mmi_decode.h"
#include "string.h"
#include <stdio.h>
#include "dqiot_drv.h"

/*
original_key[0][10] exg_key_10
original_key[1][10] sec_key_10
*/
unsigned char original_key[2][10];
otp_exchg_num g_pwd_signed_data[10];
decode_data get_decode;

static unsigned char decode_rondom_code_remainder(unsigned char *random_code);
static unsigned char decode_rondom_code_plus(unsigned char leng, unsigned char array_column);
static unsigned char decode_rondom_code_extract(void);
static void dq_sdk_CharToHexByte(const unsigned char *source, char *dest, int sourceLen);
static unsigned int n_power(unsigned char value);
static void dq_sdk_ByteToHexStr(const unsigned char *source, char *dest, int sourceLen);

/**
  * @brief  校验码解码
  * @param  随机码数组
  * @return status
  * @note   none
  * @see    none
  */
void decode_check_code(unsigned char *random_code)
{
    unsigned char i;
    unsigned int value = 0;
    unsigned int temp = 0;
    for (i = 0; i < 13; i++)
    {
        if (i % 2 == 0)
            value += random_code[i] * 2;
        else
            value += random_code[i] * random_code[i];
    }

    temp = value % 100;
    if (temp < 10)
        value = temp * 10;
    else
        value = temp;

    get_decode.chk_key_2[0] = (char)(value / 10);
    get_decode.chk_key_2[1] = (char)(value % 10);

    return;
}

/**
  * @brief  随机码解码
  * @param  随机码数组
  * @return status
  * @note   none
  * @see    none
  */
void mmi_dq_decode_app_random_code(unsigned char *random_code)
{
    // unsigned char i;
    decode_rondom_code_remainder(random_code); //获取10位解码
    decode_rondom_code_extract();              //获取8/9位解码

    // for (i = 0; i < 10; i++)
    //     printf("exg_code10[%d] is %d\n", (int)i, (int)get_decode.exg_key_10[i]);
    // for (i = 0; i < 9; i++)
    //     printf("exg_code9[%d] is %d\n", (int)i, (int)get_decode.exg_key_9[i]);
    // for (i = 0; i < 8; i++)
    //     printf("exg_code8[%d] is %d\n", (int)i, (int)get_decode.exg_key_8[i]);
    // for (i = 0; i < 10; i++)
    //     printf("sec_code10[%d] is %d\n", (int)i, (int)get_decode.sec_key_10[i]);
    // for (i = 0; i < 9; i++)
    //     printf("sec_code9[%d] is %d\n", (int)i, (int)get_decode.sec_key_9[i]);
    // for (i = 0; i < 8; i++)
    //     printf("sec_code8[%d] is %d\n", (int)i, (int)get_decode.sec_key_8[i]);
    // printf("############\n");

    return;
}

/**
  * @brief  时间戳解码10位
  * @param  pwd 字符数组
  * @param  len 长度
  * @param  sec_key 安全解码
  * @param  exg_key 交换解码
  * @return status
  * @note   none
  * @see    none
  */
void decode_time_stamp_10num(unsigned char *pwd, unsigned char len, unsigned char *sec_key, unsigned char *exg_key)
{
    unsigned char exg_key_char[10];
    unsigned char pwd_char[10];
    unsigned char sec_char[10];
    unsigned char i = 0;
    unsigned char j = 0;
    unsigned char hex_pwd_len = 5;
    unsigned char exchange_id = 0;
    unsigned char exchange_char[10];
    unsigned long high_sec_key = 0, low_sec_key = 0;
    unsigned long high_pwd = 0, low_pwd = 0;

    memset(exg_key_char, 0x00, sizeof(exg_key_char));
    memset(pwd_char, 0x00, sizeof(pwd_char));

    for (i = 0; i < 10; i++)
    {
        exg_key_char[i] = exg_key[i];
        if (exg_key[i] == 0)
            exg_key_char[i] = 10;
    }

    CharToInt_2long(sec_key, &high_sec_key, &low_sec_key);

    for (j = 0, i = 3; i < 13; i++)
    {
        pwd_char[j] = pwd[i];
        j++;
    }

    for (i = 0; i < 59; i++)
    {
        CharToInt_2long((const unsigned char *)pwd_char, &high_pwd, &low_pwd);

        if (low_pwd < low_sec_key)
        {
            high_pwd -= 1;
            low_pwd += 100000;
        }
        if (high_pwd < high_sec_key)
        {
            high_pwd += 100000;
        }
        high_pwd -= high_sec_key;
        low_pwd -= low_sec_key;
        memset(sec_char, 0x00, sizeof(sec_char));
        IntToByteStr_2long(high_pwd, low_pwd, (char *)sec_char, 5, 5);
        memset(pwd_char, 0x00, sizeof(pwd_char));
        for (j = 0; j < len; j++)
        {
            pwd_char[exg_key_char[j] - 1] = sec_char[j];
        }
    }

    memset(sec_char, 0x00, sizeof(sec_char));
    exchange_id = pwd_char[2];
    memset(exchange_char, 0x00, sizeof(exchange_char));
    dq_sdk_CharToHexByte((const unsigned char *)g_pwd_signed_data[exchange_id].exchg_num, (char *)exchange_char, 5);

    for (i = 0; i < len; i++)
    {
        if (i == 2)
        {
            sec_char[i] = exchange_id;
        }
        else
        {
            for (j = 0; j < 10; j++)
            {
                if (pwd_char[i] == exchange_char[j])
                {
                    sec_char[i] = j;
                    break;
                }
            }
        }
    }
    for (i = 2; i < len; i++)
    {
        sec_char[i] = sec_char[i + 1];
    }
    sec_char[len - 1] = exchange_id;
    memcpy((char *)get_decode.tim_key_10, (const char *)sec_char, len);

    dqiot_drv_uart0A_init();
    for (i = 0; i < 10; i++)
        printf("get_decode.tim_key_10 is %d\n", (int)get_decode.tim_key_10[i]);
    dqiot_drv_uart0B_init();

    return;
}

// /**
//   * @brief  时间同步
//   * @param  时间戳解码10位
//   * @return status
//   * @note   none
//   * @see    none
//   */
// decode_status dq_otp_syn_start_time(unsigned char *p_data)
// {
//     unsigned char i = 0;
//     unsigned char start_time[5];

//     memset(start_time, 0x00, sizeof(start_time));
//     for (i = 0; i < 5; i++)
//     {
//         start_time[i] = p_data[i + 2];
//     }
//     if (get_decode.start_hour == 0xFFFFFFFF)
//     {
//         get_decode.start_hour = dq_sdk_HexcharToInt(start_time, 4);
//         return DECODE_CMD_SUCCESS;
//     }
//     else
//     {
//         unsigned char ret;
//         get_decode.start_hour = dq_sdk_HexcharToInt(start_time, 4);
//         // g_dq_otp_init.fds_write(DQ_OTP_FILE_ID_SET, (unsigned char *)&otp_set_info, sizeof(otp_base_setting_info), &ret, dq_otp_fds_write_common_cb);
//         return DECODE_CMD_SUCCESS;
//     }
// }

/**
  * @brief  计算n^n次方
  * @param  value 值
  * @return status
  * @note   none
  * @see    none
  */
static unsigned int n_power(unsigned char value)
{
    unsigned char i;
    unsigned int num = 1;
    for (i = 0; i < value; i++)
    {
        num *= (int)value;
    }
    return num;
}

/**
  * @brief  随机码初次解码
  * @param  随机码
  * @return status
  * @note   none
  * @see    none
  */
static unsigned char decode_rondom_code_remainder(unsigned char *random_code)
{
    unsigned char i = 0, j = 0;
    unsigned char temp1 = 0, temp2 = 0;
    unsigned int top_three = 0, rev_three = 0; //前三位，翻转

    top_three = random_code[0] * 100 + random_code[1] * 10 + random_code[2];
    rev_three = random_code[2] * 100 + random_code[1] * 10 + random_code[0];

    for (i = 0; i < 10; i++)
    {
        temp1 = top_three % (10 - i);
        temp2 = rev_three % (10 - i);

        original_key[0][i] = temp1;
        original_key[1][i] = temp2;
    }

    decode_rondom_code_plus(10, 0);
    decode_rondom_code_plus(10, 1);

    return 0;
}

/**
  * @brief  获取10位完整解码
  * @param  数据长度
  * @param  二位数组行号（数据存入该行）
  * @return status
  * @note   none
  * @see    none
  */
static unsigned char decode_rondom_code_plus(unsigned char leng, unsigned char array_column)
{
    unsigned char i, j;

    for (i = 0; i < leng; i++)
    {
        for (j = 0; j < i;)
        {
            if (original_key[array_column][i] == original_key[array_column][j])
            {
                original_key[array_column][i] += 1;
                if (original_key[array_column][i] == 10)
                    original_key[array_column][i] = 0;
                j = 0;
            }
            else
            {
                if (array_column == 0)
                    get_decode.exg_key_10[i] = original_key[array_column][i];
                else
                    get_decode.sec_key_10[i] = original_key[array_column][i];

                j++;
            }
        }
        if (i == 0)
        {
            if (array_column == 0)
                get_decode.exg_key_10[i] = original_key[array_column][i];
            else
                get_decode.sec_key_10[i] = original_key[array_column][i];
        }
    }

    return 0;
}

/**
  * @brief  获取8/9位解码
  * @param  none
  * @return status
  * @note   none
  * @see    none
  */
static unsigned char decode_rondom_code_extract(void)
{
    unsigned char i, j;

    j = 0;
    for (i = 0; i < 10; i++)
    {
        if (original_key[0][i] != 0 && original_key[0][i] != 9)
        {
            get_decode.exg_key_8[j] = original_key[0][i];
            j++;
        }
    }

    j = 0;
    for (i = 0; i < 10; i++)
    {
        if (original_key[1][i] != 0 && original_key[1][i] != 9)
        {
            get_decode.sec_key_8[j] = original_key[1][i];
            j++;
        }
    }

    j = 0;
    for (i = 0; i < 10; i++)
    {
        if (original_key[0][i] != 0)
        {
            get_decode.exg_key_9[j] = original_key[0][i];
            j++;
        }
    }

    j = 0;
    for (i = 0; i < 10; i++)
    {
        if (original_key[1][i] != 0)
        {
            get_decode.sec_key_9[j] = original_key[1][i];
            j++;
        }
    }

    return 0;
}

/**
  * @brief  字符数组转整形
  * @param  p_data 字符数组
  * @param  len 字符数组长度
  * @return 值
  * @note   none
  * @see    none
  */
unsigned long CharToInt_long(unsigned char *p_data, unsigned char len)
{
    unsigned char i, j;
    unsigned long temp1 = 0;

    for (j = 0, i = 0; i < len; i++)
    {
        if (p_data[i] == 0xff)
        {
            j = i;
            break;
        }
    }

    for (i = 0; i < j; i++)
        temp1 = (temp1 * 10 + p_data[i]);

    return temp1;
}

/**
  * @brief  10位字符数组转整形
  * @param  source 数组
  * @param  sourcelen 长度
  * @param  high 高位5
  * @param  low 低位5
  * @return status
  * @note   none
  * @see    none
  */
unsigned char CharToInt_2long(const unsigned char *source, unsigned long *high, unsigned long *low)
{
    short i;
    *high = 0;
    *low = 0;
    for (i = 0; i < 5; i++)
    {
        *high = *high * 10 + source[i];
    }
    for (i = 5; i < 10; i++)
    {
        *low = *low * 10 + source[i];
    }

    return 0;
}

/**
  * @brief  10位整形转数组
  * @param  high 高位
  * @param  low 低位
  * @param  dest 数组
  * @param  highLen 高位长度
  * @param  lowlen 低位长度
  * @return status
  * @note   none
  * @see    none
  */
unsigned char IntToByteStr_2long(unsigned long high, unsigned long low, char *dest, int highLen, int lowhigh)
{
    unsigned char i = 0;
    unsigned long temp_data1 = high;
    unsigned long temp_data2 = low;
    for (i = 0; i < 5; i++)
    {
        dest[highLen - i - 1] = temp_data1 % 10;
        temp_data1 = temp_data1 / 10;
    }
    for (i = 0; i < 5; i++)
    {
        dest[highLen + lowhigh - i - 1] = temp_data2 % 10;
        temp_data2 = temp_data2 / 10;
    }

    return 0;
}

/**
  * @brief  十六进制转数组
  * @param  source
  * @param  dest
  * @param  sourceLen
  * @return status
  * @note   none
  * @see    none
  */
static void dq_sdk_CharToHexByte(const unsigned char *source, char *dest, int sourceLen)
{
    short i;
    unsigned char highByte, lowByte;
    for (i = 0; i < sourceLen; i++)
    {
        highByte = source[i] >> 4;
        lowByte = source[i] & 0x0f;
        dest[i * 2] = highByte;
        if (lowByte != 0x0F)
            dest[i * 2 + 1] = lowByte;
    }
    return;
}

int dq_sdk_HexcharToInt(unsigned char *source, int length)
{
    int int_data = 0;
    char dest[20];
    unsigned char ret = 0;
    //dest = malloc(length*2*sizeof(unsigned char));

    memset(dest, 0x00, sizeof(dest));
    dq_sdk_ByteToHexStr(source, dest, length);
    ret = sscanf((const char *)dest, "%x", &int_data);

    //free(dest);
    if (ret == 1)
        return int_data;
    else
        return 0;
}

static void dq_sdk_ByteToHexStr(const unsigned char *source, char *dest, int sourceLen)
{
    short i;
    unsigned char highByte, lowByte;
    for (i = 0; i < sourceLen; i++)
    {
        highByte = source[i] >> 4;
        lowByte = source[i] & 0x0f;
        highByte += 0x30;
        if (highByte > 0x39)
            dest[i * 2] = highByte + 0x07;
        else
            dest[i * 2] = highByte;
        lowByte += 0x30;
        if (lowByte > 0x39)
            dest[i * 2 + 1] = lowByte + 0x07;
        else
            dest[i * 2 + 1] = lowByte;
    }
    return;
}

#endif //__LOCK_DECODE_SUPPORT__
#endif //__MMI_DECODE_C__
