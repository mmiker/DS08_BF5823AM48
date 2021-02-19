/*!
    \file  mcu02_sm4.h
    \brief sm4 define
*/

/*
    Copyright (C) 2020 BYD

    2020-03-31, V1.0.0, firmware for mcu02
*/

#ifndef	MCU02_SM4_H
#define	MCU02_SM4_H

#include "mcu02_sfr.h"

#define ENCRYPT_MODE   0x00//º”√‹
#define DECRYPT_MODE   0x01//Ω‚√‹

#define START_SM4()         REG_ADDR = SM4_START;REG_DATA = 1
#define STOP_SM4()          REG_ADDR = SM4_START;REG_DATA = 0

#define SM4_INT_ENABLE()	IEN2 |= 0x10   /* enable interrupt */
#define SM4_INT_DISABLE()	IEN2 &= ~0x10  /* disable interrupt */
#define SM4_IPL_SET(x)      IPL2 &= ~0x10;IPL2 |= (x<<4)  /* set interrupt priority */

/* function declarations */
void sm4_mode_config(uint8_t mode);
void read_sm4_data(uint8_t *pbuf);
void write_sm4_data(uint8_t *pbuf);
void read_sm4_key(uint8_t *pbuf);
void write_sm4_key(uint8_t *pbuf);

#endif