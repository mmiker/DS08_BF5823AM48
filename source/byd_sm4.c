/*!
    \file  byd_sm4.c
    \brief sm4 app
*/

/*
    Copyright (C) 2020 BYD

    2020-07-13, V1.0.0, app for byd
*/

#include "byd_sm4.h"
#include "mcu02_system.h"

#if SM4_INT_EN
volatile bit g_bSm4IntFlag = 0;
#endif

/*!
    \brief      sm4 init
    \param[in]  none
    \param[out] none
    \retval     none
*/
void byd_sm4_init(void)
{
   uint8_t SM4_KEY_VALUE[16]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};

   write_sm4_key((uint8_t *)SM4_KEY_VALUE);
   
   INT_TIMER3_SM4_CLR();

#if SM4_INT_EN
   SM4_IPL_SET(LOW);	
   SM4_INT_ENABLE();   
#endif

}

/*!
    \brief      sm4 work example
    \param[in]  mode:ENCRYPT_MODE or DECRYPT_MODE
				pbuf:16bytes
    \param[out] none
    \retval     none
*/
void byd_sm4_work(uint8_t mode,uint8_t *pbuf)
{

    sm4_mode_config(mode); 
	
	write_sm4_data(pbuf);
	 	
#if SM4_INT_EN

    g_bSm4IntFlag = 0;
	START_SM4();
	while(!g_bSm4IntFlag)
	{
	   WDT_CTRL = 7;
	}

#else

    START_SM4();
	while(1)
	{
	   WDT_CTRL = 7;
	   if((IRCON2 & 0x10) && GET_INT_SM4_FLAG_STATE())
	   {
	      break;
	   } 
	}
	INT_TIMER3_SM4_CLR();

#endif
    
   read_sm4_data(pbuf);
}