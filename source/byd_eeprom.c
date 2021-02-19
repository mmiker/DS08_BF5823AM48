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
оƬ������CFG_EEPROM_SELѡ��main_block���1K��Ϊeeprom
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

	eeprom_erase_page(0);//����1K
	
	for(i=0;i<1024;i++)//дһҳ
	{
		ret = eeprom_write_byte(0,i,0xaa);
		if(ret==ERROR) 
		{
			return ERROR;
		}
	}


	eeprom_select(1);//ѡ��NVR��Ϊeeprom,�ܹ�2*512byte
	for(j=0;j<2;j++)
	{
		eeprom_erase_page(j);//����512byte
		for(i=0;i<512;i++)//дһҳ
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
		pbuf[i] = eeprom_read_byte(0,i);//����һҳ
	}

	eeprom_select(1);
	for(i = 0; i < 512; i++)
	{
		pbuf[i] = eeprom_nvr_read_byte(0,i);//����һҳ
	    pbuf[i+512] = eeprom_nvr_read_byte(1,i);//���ڶ�ҳ
	}
}
