/*!
    \file  byd_eeprom.h
    \brief led define
*/

/*
    Copyright (C) 2020 BYD

    2020-07-28, V1.0.0, app for byd
*/

#ifndef BYD_EEPROM_H
#define	BYD_EEPROM_H

#include "mcu02_eeprom.h"


ErrStatus byd_eeprom_write(void);
void byd_eeprom_read(uint8_t *pbuf);

#endif