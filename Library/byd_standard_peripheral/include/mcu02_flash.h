/*!
    \file  mcu02_flash.h
    \brief flash define
*/

/*
    Copyright (C) 2020 BYD

    2020-03-31, V1.0.0, firmware for mcu02
*/

#ifndef	MCU02_FLASH_H
#define	MCU02_FLASH_H

#include "intrins.h"
#include "mcu02_sfr.h"


/* function declarations */
void flash_erase_page(uint16_t page_address);
uint8_t flash_read_byte(uint16_t page_address);
ErrStatus flash_write_byte(uint16_t page_address,uint8_t write_byte);

ErrStatus enter_boot_upgrade(void);
ErrStatus exit_boot_upgrade(void);

ErrStatus jump_to_app(uint16_t offest);
ErrStatus jump_to_boot(void);

#endif