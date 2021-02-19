/*!
    \file  mcu02_lvdt.c
    \brief lvdt driver
*/

/*
    Copyright (C) 2020 BYD

    2020-07-20, V1.0.0, firmware for mcu02
*/

#include "mcu02_lvdt.h"
#include "mmi_audio.h"
#include "dqiot_drv.h"
#include "delay.h"

/**
  * @brief  电压检测初始化
  * @param  vth_sel;
  * 0: 2.7v,
  * 1: 3v,
  * 2: 3.8v,
  * 3: 4.2v
  * @return none
  * @note   none
  * @see    none
  */
void lvdt_init(uint8_t vth_sel)
{
    LVDT_VOL_SET(vth_sel);  //设置电压检测值
    LVDT_INT_DOWN_FLAG_CLR; //清除电压下降中断标志
    LVDT_INT_UP_FLAG_CLR;   //清除电压上升中断标志
    LVDT_IPL_SET(LOW);      //设置中断优先级
    LVDT_INT_ENABLE();      //启用中断
    LVDT_ENABLE();          //使能电压检测
}

/**
  * @brief  电压检测
  * @param  none	
  * @return none
  * @note   none
  * @see    none
  */
void lvdt_VolT(void)
{
    // u16 volL = 1; /* 0:电压低;1:电压正常 */

    if (GET_INT_LVDT_FLAG_STATE(INT_VOL_UP_FLAG)) //电压低
    {
        // volL = 0;
        LVDT_INT_DOWN_FLAG_CLR; //清除电压下降中断标志
        mmi_dq_aud_play_with_id(AUD_BASE_ID_LOW_BATTERY);
    }
    if (GET_INT_LVDT_FLAG_STATE(INT_VOL_DOWN_FLAG)) //电压正常
    {
        // volL = 1;
        LVDT_INT_UP_FLAG_CLR; //清除电压上升中断标志
    }

    // if (volL == 0)
    // {
    //     delay_ms(2000);
    //     mmi_dq_aud_play_with_id(AUD_BASE_ID_LOW_BATTERY);
    // }
}