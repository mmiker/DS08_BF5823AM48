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
  * @brief  ��ѹ����ʼ��
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
    LVDT_VOL_SET(vth_sel);  //���õ�ѹ���ֵ
    LVDT_INT_DOWN_FLAG_CLR; //�����ѹ�½��жϱ�־
    LVDT_INT_UP_FLAG_CLR;   //�����ѹ�����жϱ�־
    LVDT_IPL_SET(LOW);      //�����ж����ȼ�
    LVDT_INT_ENABLE();      //�����ж�
    LVDT_ENABLE();          //ʹ�ܵ�ѹ���
}

/**
  * @brief  ��ѹ���
  * @param  none	
  * @return none
  * @note   none
  * @see    none
  */
void lvdt_VolT(void)
{
    // u16 volL = 1; /* 0:��ѹ��;1:��ѹ���� */

    if (GET_INT_LVDT_FLAG_STATE(INT_VOL_UP_FLAG)) //��ѹ��
    {
        // volL = 0;
        LVDT_INT_DOWN_FLAG_CLR; //�����ѹ�½��жϱ�־
        mmi_dq_aud_play_with_id(AUD_BASE_ID_LOW_BATTERY);
    }
    if (GET_INT_LVDT_FLAG_STATE(INT_VOL_DOWN_FLAG)) //��ѹ����
    {
        // volL = 1;
        LVDT_INT_UP_FLAG_CLR; //�����ѹ�����жϱ�־
    }

    // if (volL == 0)
    // {
    //     delay_ms(2000);
    //     mmi_dq_aud_play_with_id(AUD_BASE_ID_LOW_BATTERY);
    // }
}