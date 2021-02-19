/*!
    \file  mcu02_eeprom.c
    \brief eeprom driver
*/

/*
    Copyright (C) 2020 BYD

    2020-07-16, V1.0.0, firmware for mcu02
*/

#include "mcu02_eeprom.h"

/*!
    \brief      select eeprom
    \param[in]  select:
	            0: x*1024byte,select last xK 0f main_block as eeprom,x = CFG_EEPROM_SEL(0~31)
				1: 2*512byte,select NVR3,NVR4 as eeprom
    \param[out] none
    \retval     none
*/
void eeprom_select(uint8_t select)
{
    EEPROM_SELECT(select);
}

/*!
    \brief      erase time
    \param[in]  erase_time:0~9(0.5*(erase_time+1)ms+0.0652ms)
				           >9(4.5652ms)	EEPROM_SELECT(0)
				erase_time:0~9((erase_time+1)ms+0.1304ms)
				           >9(9.1304ms)	EEPROM_SELECT(1)
    \param[out] none
    \retval     none
*/
void eeprom_erase_time(uint8_t erase_time)
{
   	SPROG_TIM = (0x1f&erase_time);
}

/*!
    \brief      erase page
    \param[in]  page:0~x(EEPROM_SELECT(0),x = CFG_EEPROM_SEL(0~31)) 
	                 0~1(EEPROM_SELECT(1))
    \param[out] none
    \retval     none
*/
void eeprom_erase_page(uint8_t page)
{
	EA = 0;
	SPROG_ADDR_L = 0x00;
	SPROG_ADDR_H = 0x00;
	SPROG_ADDR_H |= (page<<2);
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
    \brief      eeprom read byte
    \param[in]  page:0~x(EEPROM_SELECT(0),x = CFG_EEPROM_SEL(0~31))
				addr:0~0x3ff
    \param[out] none
    \retval     data
*/
uint8_t eeprom_read_byte(uint8_t page,uint16_t addr)
{	
	uint8_t code *P_Rank;
	P_Rank = 0xFC00 - ((uint16_t)page<<10); 
	return (*(P_Rank + addr));	
}

/*!
    \brief      eeprom write byte
    \param[in]  page:0~x(EEPROM_SELECT(0),x = CFG_EEPROM_SEL(0~31)) 
	                 0~1(EEPROM_SELECT(1))
				addr:0~0x3ff(EEPROM_SELECT(0))
				     0~0x1ff(EEPROM_SELECT(1))
				write_byte
    \param[out] none
    \retval     ErrStatus:SUCCESS/ERROR
*/
ErrStatus eeprom_write_byte(uint8_t page,uint16_t addr,uint8_t write_byte)
{
	ErrStatus status;
    uint8_t tempdata,select;

	REG_ADDR = EEP_SELECT;
	select = REG_DATA;

	EA = 0;

	SPROG_ADDR_L = 0x00;
	SPROG_ADDR_H = 0x00;
	SPROG_ADDR_H |= (page<<2);
	SPROG_ADDR_L = addr;
	SPROG_ADDR_H |= ((addr>>8)&0x03);
	SPROG_DATA = write_byte;
	SPROG_CMD = 0x69;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	SPROG_ADDR_L = 0x00;
	SPROG_ADDR_H = 0x00;

	if(select==0)
	{
	   tempdata = eeprom_read_byte(page,addr);
	}
	else
	{
	   tempdata = eeprom_nvr_read_byte(page,addr);
	}

	if(tempdata == write_byte)
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
    \brief      read eeprom when EEPROM_SELECT(1)
    \param[in]  addr:0x4400~0x47ff
    \param[out] none
    \retval     none
*/
void eeprom_nvr_read(uint8_t *pbuf,uint16_t addr,uint16_t len)
{
    uint16_t i;
		
	EA = 0;

	for(i = 0; i < len; i++)
	{	
	    SPROG_CMD = 0x88;
		SPROG_ADDR_H = (addr>>8);
		SPROG_ADDR_L = addr&0x00ff;			
		pbuf[i] = SPROG_RDATA;
		addr++;
	}

	SPROG_CMD = 0x00;	
	SPROG_ADDR_H = 0x00;
	SPROG_ADDR_L = 0x00;	
	EA = 1;
		
}

/*!
    \brief      read eeprom when EEPROM_SELECT(1)
	\param[in]  page:0~1
    \param[in]  addr:0~0x1ff
    \param[out] none
    \retval     none
*/
void eeprom_nvr_read_page(uint8_t *pbuf,uint8_t page,uint16_t addr,uint16_t len)
{
    uint16_t i;
	uint16_t addr_base;

	if(page)
	{
		addr_base = 0x4600+addr;
	}
	else
	{
	    addr_base = 0x4400+addr;
	}
	
	EA = 0;

	for(i = 0; i < len; i++)
	{	
	    SPROG_CMD = 0x88;
		SPROG_ADDR_H = (addr_base>>8);
		SPROG_ADDR_L = addr_base&0x00ff;			
		pbuf[i] = SPROG_RDATA;
		addr_base++;
	}

	SPROG_CMD = 0x00;	
	SPROG_ADDR_H = 0x00;
	SPROG_ADDR_L = 0x00;	
	EA = 1;
		
}


/*!
    \brief      read byte from eeprom when EEPROM_SELECT(1)
	\param[in]  page:0~1
    \param[in]  addr:0~0x1ff
    \param[out] none
    \retval     data
*/
uint8_t eeprom_nvr_read_byte(uint8_t page,uint16_t addr)
{
    uint8_t dat;
	uint16_t addr_base;

	if(page)
	{
		addr_base = 0x4600+addr;
	}
	else
	{
	    addr_base = 0x4400+addr;
	}
		
	EA = 0;

	SPROG_CMD = 0x88;	
	SPROG_ADDR_H = (addr_base>>8);
	SPROG_ADDR_L = addr_base&0x00ff;	
	dat = SPROG_RDATA;

	SPROG_CMD = 0x00;	
	SPROG_ADDR_H = 0x00;
	SPROG_ADDR_L = 0x00;
		
	EA = 1;
	
	return dat;	
}

