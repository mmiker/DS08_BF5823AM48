/*!
    \file  mcu02_sm4.c
    \brief sm4 driver
*/

/*
    Copyright (C) 2020 BYD

    2020-03-31, V1.0.0, firmware for mcu02
*/

#include "mcu02_sm4.h"

/*!
    \brief      select mode
    \param[in]  mode:ENCRYPT_MODE or DECRYPT_MODE
    \param[out] none
    \retval     none
*/
void sm4_mode_config(uint8_t mode)
{
    REG_ADDR = SM4_MODE;
	REG_DATA = mode;
}

/*!
    \brief      read encrypting or decrypting data
    \param[in]  pbuf
    \param[out] none
    \retval     none
*/
void read_sm4_data(uint8_t *pbuf)
{
   uint8_t i;
   for(i = 0; i < 16; i++)
   {
       REG_ADDR = SM4_DATA0+i;
	   pbuf[i] = REG_DATA;
   }
}

/*!
    \brief      write encrypting or decrypting data
    \param[in]  pbuf
    \param[out] none
    \retval     none
*/
void write_sm4_data(uint8_t *pbuf)
{
   uint8_t i;
   for(i = 0; i < 16; i++)
   {
       REG_ADDR = SM4_DATA0+i;
	   REG_DATA = pbuf[i];
   }
}

/*!
    \brief      read key data
    \param[in]  pbuf
    \param[out] none
    \retval     none
*/
void read_sm4_key(uint8_t *pbuf)
{
   uint8_t i;
   for(i = 0; i < 16; i++)
   {
       REG_ADDR = SM4_KEY0+i;
	   pbuf[i] = REG_DATA;
   }
}

/*!
    \brief      write key data
    \param[in]  pbuf
    \param[out] none
    \retval     none
*/
void write_sm4_key(uint8_t *pbuf)
{
   uint8_t i;
   for(i = 0; i < 16; i++)
   {
       REG_ADDR = SM4_KEY0+i;
	   REG_DATA = pbuf[i];
   }
}
