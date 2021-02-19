/*!
    \file  byd_eeprom.c
    \brief eeprom app
*/

/*
    Copyright (C) 2020 BYD

    2020-07-28, V1.0.0, app for byd
*/

#include "byd_eeprom.h"

/*
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
芯片配置字CFG_EEPROM_SEL选择main_block最后1K作为eeprom
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*/

/*!
    \brief      eeprom write example
    \param[in]  none
    \param[out] none
    \retval     none
*/
ErrStatus byd_eeprom_write(void)
{
    uint8_t ret,j;
	uint16_t i;

	eeprom_erase_time(9);

	eeprom_select(0);

	eeprom_erase_page(0);//擦除1K
	
	for(i=0;i<1024;i++)//写一页
	{
		ret = eeprom_write_byte(0,i,0xaa);
		if(ret==ERROR) 
		{
			return ERROR;
		}
	}


	eeprom_select(1);//选择NVR作为eeprom,总共2*512byte
	for(j=0;j<2;j++)
	{
		eeprom_erase_page(j);//擦除512byte
		for(i=0;i<512;i++)//写一页
		{
			ret = eeprom_write_byte(j,i,i+j);
			if(ret==ERROR) 
			{
				return ERROR;
			}
		}
	}

	return SUCCESS;
}

/*!
    \brief      eeprom read example
    \param[in]  none
    \param[out] none
    \retval     none
*/
void byd_eeprom_read(uint8_t *pbuf)
{
   	uint16_t i;

	eeprom_select(0);
	for(i = 0; i < 1024; i++)
	{
		pbuf[i] = eeprom_read_byte(0,i);//读第一页
	}

	eeprom_select(1);
	for(i = 0; i < 512; i++)
	{
		pbuf[i] = eeprom_nvr_read_byte(0,i);//读第一页
	    pbuf[i+512] = eeprom_nvr_read_byte(1,i);//读第二页
	}
}
