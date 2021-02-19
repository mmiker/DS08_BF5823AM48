/*!
    \file  mcu02_flash.c
    \brief flash driver
*/

/*
    Copyright (C) 2020 BYD

    2020-06-03, V1.0.0, firmware for mcu02
*/

#include "mcu02_flash.h"

/*
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
进入boot升级功能时才能使用以下接口函数对flash进行擦除和编程操作,平时不能用作存储数据功能
若要存储数据,请参考mcu02_eeprom.c和byd_eeprom.c
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*/

/*!
    \brief      erase time
    \param[in]  erase_time:0~9(0.5*(erase_time+1)ms+0.0652ms)
				           >9(4.5652ms)
    \param[out] none
    \retval     none
*/
void flash_erase_time(uint8_t erase_time)
{
   	SPROG_TIM = (0x1f&erase_time);
}
/*!
    \brief      erase page
    \param[in]  page_address: the page address to be erased.erase 512bytes
    \param[out] none
    \retval     none
*/
void flash_erase_page(uint16_t page_address)
{    
	EA = 0;	
	SPROG_ADDR_L = page_address&0x00ff;
	SPROG_ADDR_H = (page_address&0xff00)>>8;
	SPROG_CMD = 0x96;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	SPROG_ADDR_L = 0x00;
	SPROG_ADDR_H = 0x00;
	EA = 1;
}

/*!
    \brief      flash read byte
    \param[in]  page_address:0~0xffff
    \param[out] none
    \retval     data
*/
uint8_t flash_read_byte(uint16_t page_address)
{	
	uint8_t code *pbuf;
	pbuf = (uint8_t code *)page_address; 
	return (*pbuf);	
}

/*!
    \brief      flash read byte
    \param[in]  page_address:0~0xffff
    \param[out] none
    \retval     data
*/
void flash_read(uint8_t *pbuf,uint16_t page_address,uint16_t len)
{	
	uint16_t i;
	for(i = 0; i < len; i++)
		pbuf[i] = *((uint8_t code *)(page_address+i));	
}

/*!
    \brief      write byte
    \param[in]  page_address:0~0xffff
				write_byte
    \param[out] none
    \retval     ErrStatus:SUCCESS/ERROR
*/
ErrStatus flash_write_byte(uint16_t page_address,uint8_t write_byte)
{
	ErrStatus status;

	EA = 0;
	SPROG_ADDR_L = page_address&0x00ff;
	SPROG_ADDR_H = (page_address&0xff00)>>8;
	SPROG_DATA = write_byte;
	SPROG_CMD = 0x69;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	SPROG_ADDR_L = 0x00;
	SPROG_ADDR_H = 0x00;

	if(*((uint8_t code *)page_address) == write_byte)
	{
		status = SUCCESS;
	}
	else
	{
		status = ERROR;
	}
	
	EA = 1;

	return status;
		
}
/*!
    \brief      enter bootloader
    \param[in]  none
    \param[out] none
    \retval     ErrStatus:SUCCESS/ERROR
*/
ErrStatus enter_boot_upgrade(void)
{
    ErrStatus status;	
	uint8_t boot_flag;

	EA = 0;

	SPROG_CMD = 0x12;
    SPROG_CMD = 0x34;
	SPROG_CMD = 0x56;
	SPROG_CMD = 0x78;
	SPROG_CMD = 0x9a;

	_nop_();
	_nop_();
	_nop_();

	REG_ADDR = FLASH_BOOT_EN;
	boot_flag = REG_DATA;

	if(boot_flag)
	  status = SUCCESS;
	else
	  status = ERROR;
	   
	EA = 1;

	return status;
}

/*!
    \brief      exit bootloader
    \param[in]  none
    \param[out] none
    \retval     ErrStatus:SUCCESS/ERROR
*/
ErrStatus exit_boot_upgrade(void)
{
    ErrStatus status;	
	uint8_t boot_flag;

	EA = 0;

	SPROG_CMD = 0xfe;
    SPROG_CMD = 0xdc;
	SPROG_CMD = 0xba;
	SPROG_CMD = 0x98;
	SPROG_CMD = 0x76;

	_nop_();

	REG_ADDR = FLASH_BOOT_EN;
	boot_flag = REG_DATA;

	if(boot_flag==0)
	  status = SUCCESS;
	else
	  status = ERROR;
	   
	EA = 1;

	return status;
}

/*!
    \brief      enter app code
    \param[in]  offest
    \param[out] none
    \retval     ErrStatus:SUCCESS/ERROR
*/
ErrStatus jump_to_app(uint16_t offest)
{
   	ErrStatus status;	
	uint8_t rom_offset_l;
	uint8_t rom_offset_h;
	uint16_t rom_offset;

	EA = 0;

	REG_ADDR = BOOT_CMD;
	REG_DATA = 0xff;

	REG_ADDR = BOOT_CMD;
	REG_DATA = 0x00;

	REG_ADDR = BOOT_CMD;
	REG_DATA = 0x88;
	
	REG_ADDR = BOOT_CMD;
	REG_DATA = 0x55;

	REG_ADDR = BOOT_CMD;
	REG_DATA = 0xaa;
	
	_nop_();

	REG_ADDR = ROM_OFFSET_L;
	rom_offset_l = REG_DATA;

	REG_ADDR = ROM_OFFSET_H;
	rom_offset_h = REG_DATA;

	rom_offset = ((uint16_t)rom_offset_h<<8)|rom_offset_l;

	if(rom_offset == offest)
	  status = SUCCESS;
	else
	  status = ERROR;
	   
	EA = 1;

	return status;
}

/*!
    \brief      enter boot code
    \param[in]  none
    \param[out] none
    \retval     ErrStatus:SUCCESS/ERROR
*/
ErrStatus jump_to_boot(void)
{
   	ErrStatus status;	
	uint8_t rom_offset_l;
	uint8_t rom_offset_h;
	uint16_t rom_offset;

	EA = 0;

	REG_ADDR = BOOT_CMD;
	REG_DATA = 0x37;

	REG_ADDR = BOOT_CMD;
	REG_DATA = 0xc8;

	REG_ADDR = BOOT_CMD;
	REG_DATA = 0x42;

	REG_ADDR = BOOT_CMD;
	REG_DATA = 0x9a;

	REG_ADDR = BOOT_CMD;
	REG_DATA = 0x65;
	
	_nop_();

	REG_ADDR = ROM_OFFSET_L;
	rom_offset_l = REG_DATA;

	REG_ADDR = ROM_OFFSET_H;
	rom_offset_h = REG_DATA;

	rom_offset = ((uint16_t)rom_offset_h<<8)|rom_offset_l;

	if(rom_offset == 0)
	  status = SUCCESS;
	else
	  status = ERROR;
	   
	EA = 1;

	return status;
}