/*!
    \file  mcu02_eeprom.h
    \brief eeprom define
*/

/*
    Copyright (C) 2020 BYD

    2020-07-16, V1.0.0, firmware for mcu02
*/

#ifndef	MCU02_EEPROM_H
#define	MCU02_EEPROM_H

#include "intrins.h"
#include "mcu02_sfr.h"

#define EEPROM_SELECT(x)  REG_ADDR = EEP_SELECT;REG_DATA = x /*x=1 选择NVR3 NVR4作为eeprom功能，总共2*512byte;x=0 选择mainblock最后32k作为eeprom功能,总共32*1024byte*/


/* function declarations */
void eeprom_select(uint8_t select);
void eeprom_erase_time(uint8_t erase_time);
void eeprom_erase_page(uint8_t page);
uint8_t eeprom_read_byte(uint8_t page,uint16_t addr);
ErrStatus eeprom_write_byte(uint8_t page,uint16_t addr,uint8_t write_byte);

void eeprom_nvr_read(uint8_t *pbuf,uint16_t addr,uint16_t len);
uint8_t eeprom_nvr_read_byte(uint8_t page,uint16_t addr);

#endif