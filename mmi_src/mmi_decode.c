#ifndef __MMI_DECODE_C__
#define __MMI_DECODE_C__
#include "mmi_feature.h"
#ifdef __LOCK_DECODE_SUPPORT__
#include "mmi_decode.h"
#include "dqiot_drv.h"
#include "string.h"
#include <stdio.h>

/*
original_key[0][10] exg_key_10
original_key[1][10] sec_key_10
*/
unsigned char original_key[2][10];
struct decode_data get_decode;

static unsigned char decode_rondom_code_remainder(unsigned char *random_code);
static unsigned char decode_rondom_code_plus(unsigned char leng, unsigned char array_column);
static unsigned char decode_rondom_code_extract(void);

/**
  * @brief  随机码解码
  * @param  字符数组
  * @return status
  * @note   none
  * @see    none
  */
unsigned char mmi_dq_decode_app_random_code(unsigned char *random_code)
{
    // unsigned char i;

    decode_rondom_code_remainder(random_code); //获取10位解码
    decode_rondom_code_extract();              //获取8/9位解码

    // dqiot_drv_uart0A_init();
    // for (i = 0; i < 10; i++)
    //     printf("exg_code10[%d] is %d\n", (int)i, (int)get_decode.exg_key_10[i]);
    // for (i = 0; i < 9; i++)
    //     printf("exg_code9[%d] is %d\n", (int)i, (int)get_decode.exg_key_9[i]);
    // for (i = 0; i < 8; i++)
    //     printf("exg_code8[%d] is %d\n", (int)i, (int)get_decode.exg_key_8[i]);
    // printf("############\n");
    // for (i = 0; i < 10; i++)
    //     printf("sec_code10[%d] is %d\n", (int)i, (int)get_decode.sec_key_10[i]);
    // for (i = 0; i < 9; i++)
    //     printf("sec_code9[%d] is %d\n", (int)i, (int)get_decode.sec_key_9[i]);
    // for (i = 0; i < 8; i++)
    //     printf("sec_code8[%d] is %d\n", (int)i, (int)get_decode.sec_key_8[i]);
    // dqiot_drv_uart0B_init();

    return 0;
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

#endif //__LOCK_DECODE_SUPPORT__
#endif //__MMI_DECODE_C__
