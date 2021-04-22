#ifndef __MMI_DECODE_C__
#define __MMI_DECODE_C__
#include "mmi_feature.h"
#ifdef __LOCK_DECODE_SUPPORT__
#include "mmi_decode.h"
#include "dqiot_drv.h"
// #include <stdio.h>


struct decode_data get_decode;

unsigned char mmi_dq_decode_app_random_code(unsigned char *random_code)
{
    unsigned char i = 0, j = 0;
    unsigned int temp1 = 0, temp2 = 0;
    get_decode.top_three = 0; //前三位
    get_decode.rev_three = 0; //翻转

    for (i = 0; i < 3; i++)
    {
        temp1 = random_code[i];
        if (i == 0)
        {
            get_decode.top_three += temp1 * 100;
            get_decode.rev_three += temp1;
        }
        else if (i == 1)
        {
            get_decode.top_three += temp1 * 10;
            get_decode.rev_three += temp1 * 10;
        }
        else if (i == 2)
        {
            get_decode.top_three += temp1;
            get_decode.rev_three += temp1 * 100;
        }
    }

    for (i = 0; i < 10; i++)
    {
        temp1 = get_decode.top_three % (10 - i);
        temp2 = get_decode.rev_three % (10 - i);

        if (i < 10)
        {
            get_decode.exg_key_10[i] = temp1;
            get_decode.sec_key_10[i] = temp2;
        }
        if (i < 9)
        {
            get_decode.exg_key_9[i] = temp1;
            get_decode.sec_key_9[i] = temp2;
        }
        if (i > 0 && i < 9)
        {
            get_decode.exg_key_8[j] = temp1;
            j++;
        }
        if (i < 8)
        {
            get_decode.sec_key_8[i] = temp2;
        }
    }

    // dqiot_drv_uart0A_init();
    // printf("top_three is %d\n", get_decode.top_three);
    // for (i = 0; i < 10; i++)
    //     printf("exg_code10[%d] is %d\n", (int)i, get_decode.exg_key_10[i]);
    // for (i = 0; i < 9; i++)
    //     printf("exg_code9[%d] is %d\n", (int)i, get_decode.exg_key_9[i]);
    // for (i = 0; i < 8; i++)
    //     printf("exg_code8[%d] is %d\n", (int)i, get_decode.exg_key_8[i]);

    // printf("rev_three is %d\n", get_decode.rev_three);
    // for (i = 0; i < 10; i++)
    //     printf("sec_code10[%d] is %d\n", (int)i, get_decode.sec_key_10[i]);
    // for (i = 0; i < 9; i++)
    //     printf("sec_code9[%d] is %d\n", (int)i, get_decode.sec_key_9[i]);
    // for (i = 0; i < 8; i++)
    //     printf("sec_code8[%d] is %d\n", (int)i, get_decode.sec_key_8[i]);
    // dqiot_drv_uart0B_init();
}


#endif //__LOCK_DECODE_SUPPORT__
#endif //__MMI_DECODE_C__
