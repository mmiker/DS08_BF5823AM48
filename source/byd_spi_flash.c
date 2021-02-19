#include "byd_spi_flash.h"


/*******************************************************************************
* Function Name  : SPI_FLASH_SendByte
* Description    : spi_flash 读写通信
* Input          : 发送数据
* Output         : None
* Return         : 接收数据
*******************************************************************************/
uint8_t SPI_FLASH_SendByte(uint8_t dat)
{	
	return spi_sendbyte(dat);	
}
/*******************************************************************************
* Function Name  : SPI_FLASH_SectorErase
* Description    : Erases the specified FLASH sector.
* Input          : SectorAddr: address of the sector to erase.
* Output         : None
* Return         : 0:succed 1:fail
*******************************************************************************/
uint8_t SPI_FLASH_SectorErase(uint32_t SectorAddr)
{
	uint8_t FLASH_Status,error_flag = RT_OK;
	/* Send write enable instruction */
	SPI_FLASH_WriteEnable();
	SPI_FLASH_WaitForWriteEnd();
	/* Sector Erase */
	/* Select the FLASH: Chip Select low */
	macSPI_FLASH_CS_ENABLE();
	/* Send Sector Erase instruction */
	SPI_FLASH_SendByte(W25X_SectorErase);
	/* Send SectorAddr high nibble address byte */
	SPI_FLASH_SendByte((SectorAddr & 0xFF0000) >> 16);
	/* Send SectorAddr medium nibble address byte */
	SPI_FLASH_SendByte((SectorAddr & 0xFF00) >> 8);
	/* Send SectorAddr low nibble address byte */
	SPI_FLASH_SendByte(SectorAddr & 0xFF);
	/* Deselect the FLASH: Chip Select high */
	macSPI_FLASH_CS_DISABLE();
	delay_us(2);
	macSPI_FLASH_CS_ENABLE();
	SPI_FLASH_SendByte(W25X_ReadStatusReg);
	FLASH_Status = SPI_FLASH_SendByte(Dummy_Byte);	 
	if((FLASH_Status & WIP_Flag) == RESET)
	{
	 	error_flag = RT_FAIL;
	}
	macSPI_FLASH_CS_DISABLE();
	
	/* Wait the end of Flash writing */
	SPI_FLASH_WaitForWriteEnd();

	return error_flag;
}
/*******************************************************************************
* Function Name  : FLASH_PageErase 页擦除 256byte
* Description    : Erases the specified FLASH page.
* Input          : SectorAddr: address of the page to erase.
* Output         : None
* Return         : 0:succed 1:fail
*******************************************************************************/
uint8_t SPI_FLASH_PageErase(uint32_t PageAddr)
{
	uint8_t FLASH_Status,error_flag = RT_OK;
	/* Send write enable instruction */
	SPI_FLASH_WriteEnable();
	SPI_FLASH_WaitForWriteEnd();
	/* Sector Erase */
	/* Select the FLASH: Chip Select low */
	macSPI_FLASH_CS_ENABLE();
	/* Send Sector Erase instruction */
	SPI_FLASH_SendByte(W25X_PageErase);
	/* Send SectorAddr high nibble address byte */
	SPI_FLASH_SendByte(((PageAddr & 0xFF0000) >> 16));
	/* Send SectorAddr medium nibble address byte */
	SPI_FLASH_SendByte(((PageAddr & 0xFF00) >> 8));
	/* Send SectorAddr low nibble address byte */
	SPI_FLASH_SendByte(PageAddr & 0xFF);
	/* Deselect the FLASH: Chip Select high */
	macSPI_FLASH_CS_DISABLE();
	delay_us(2);
	macSPI_FLASH_CS_ENABLE();
	SPI_FLASH_SendByte(W25X_ReadStatusReg);
	FLASH_Status = SPI_FLASH_SendByte(Dummy_Byte);	 
	if((FLASH_Status & WIP_Flag) == RESET)
	{
	 error_flag = RT_FAIL;
	}
	macSPI_FLASH_CS_DISABLE();	
	
	/* Wait the end of Flash writing */
	SPI_FLASH_WaitForWriteEnd();
	
	return error_flag;
}
//Added by sean zhu.
/*******************************************************************************
* Function Name  : FLASH_Block32kErase 32K 块擦除 32*1024 bytes
* Description    : Erases the specified FLASH Block.
* Input          : BlockAddr: address of the block to erase.
* Output         : None
* Return         : 0:succed 1:fail
*******************************************************************************/
uint8_t SPI_FLASH_Block32kErase(uint32_t BlockAddr)
{
	uint8_t FLASH_Status,error_flag = RT_OK;
	
	/* Send write enable instruction */
	SPI_FLASH_WriteEnable();
	SPI_FLASH_WaitForWriteEnd();
	/* Sector Erase */
	/* Select the FLASH: Chip Select low */
	macSPI_FLASH_CS_ENABLE();
	/* Send Sector Erase instruction */
	SPI_FLASH_SendByte(W25X_Block32KErase);
	/* Send SectorAddr high nibble address byte */
	SPI_FLASH_SendByte((BlockAddr & 0xFF0000) >> 16);
	/* Send SectorAddr medium nibble address byte */
	SPI_FLASH_SendByte((BlockAddr & 0xFF00) >> 8);
	/* Send SectorAddr low nibble address byte */
	SPI_FLASH_SendByte(BlockAddr & 0xFF);
	/* Deselect the FLASH: Chip Select high */
	macSPI_FLASH_CS_DISABLE();
	delay_us(2);
	
	macSPI_FLASH_CS_ENABLE();
	SPI_FLASH_SendByte(W25X_ReadStatusReg);
	FLASH_Status = SPI_FLASH_SendByte(Dummy_Byte);	 
	if((FLASH_Status & WIP_Flag) == RESET)
	{
		error_flag = RT_FAIL;
	}
	macSPI_FLASH_CS_DISABLE();	
	
	/* Wait the end of Flash writing */
	SPI_FLASH_WaitForWriteEnd();
	
	return error_flag;

}
//Added by sean zhu.
/*******************************************************************************
* Function Name  : FLASH_Block64kErase 64k 块擦除 64*1024 bytes
* Description    : Erases the specified FLASH block.
* Input          : BlockAddr: address of the block to erase.
* Output         : None
* Return         : 0:succed 1:fail
*******************************************************************************/
uint8_t SPI_FLASH_Block64kErase(uint32_t BlockAddr)
{
	uint8_t FLASH_Status,error_flag = RT_OK;
	
	/* Send write enable instruction */
	SPI_FLASH_WriteEnable();
	SPI_FLASH_WaitForWriteEnd();
	/* Sector Erase */
	/* Select the FLASH: Chip Select low */
	macSPI_FLASH_CS_ENABLE();
	/* Send Sector Erase instruction */
	SPI_FLASH_SendByte(W25X_BlockErase);
	/* Send SectorAddr high nibble address byte */
	SPI_FLASH_SendByte((BlockAddr & 0xFF0000) >> 16);
	/* Send SectorAddr medium nibble address byte */
	SPI_FLASH_SendByte((BlockAddr & 0xFF00) >> 8);
	/* Send SectorAddr low nibble address byte */
	SPI_FLASH_SendByte(BlockAddr & 0xFF);
	/* Deselect the FLASH: Chip Select high */
	macSPI_FLASH_CS_DISABLE();
	delay_us(2);
	
	macSPI_FLASH_CS_ENABLE();
	SPI_FLASH_SendByte(W25X_ReadStatusReg);
	FLASH_Status = SPI_FLASH_SendByte(Dummy_Byte);	 
	if((FLASH_Status & WIP_Flag) == RESET)
	{
		error_flag = RT_FAIL;
	}
	macSPI_FLASH_CS_DISABLE();	
	
	/* Wait the end of Flash writing */
	SPI_FLASH_WaitForWriteEnd();
	
	return error_flag;

}
/*******************************************************************************
* Function Name  : SPI_FLASH_BulkErase
* Description    : Erases the entire FLASH.
* Input          : None
* Output         : None
* Return         : 0:succed 1:fail
*******************************************************************************/
uint8_t SPI_FLASH_BulkErase(void)
{
	uint8_t FLASH_Status,error_flag = RT_OK;
	/* Send write enable instruction */
	SPI_FLASH_WriteEnable();
	
	/* Bulk Erase */
	/* Select the FLASH: Chip Select low */
	macSPI_FLASH_CS_ENABLE();
	/* Send Bulk Erase instruction  */
	SPI_FLASH_SendByte(W25X_ChipErase);
	/* Deselect the FLASH: Chip Select high */
	macSPI_FLASH_CS_DISABLE();
	delay_us(2);
	
	macSPI_FLASH_CS_ENABLE();
	SPI_FLASH_SendByte(W25X_ReadStatusReg);
	FLASH_Status = SPI_FLASH_SendByte(Dummy_Byte);	 
	if((FLASH_Status & WIP_Flag) == RESET)
	{
		error_flag = RT_FAIL;
	}
	macSPI_FLASH_CS_DISABLE();
	/* Wait the end of Flash writing */
	SPI_FLASH_WaitForWriteEnd();
	return error_flag;
}

/*******************************************************************************
* Function Name  : SPI_FLASH_PageWrite
* Description    : Writes more than one byte to the FLASH with a single WRITE
*                  cycle(Page WRITE sequence). The number of byte can't exceed
*                  the FLASH page size.
* Input          : - pBuffer : pointer to the buffer  containing the data to be
*                    written to the FLASH.
*                  - WriteAddr : FLASH's internal address to write to.
*                  - NumByteToWrite : number of bytes to write to the FLASH,
*                    must be equal or less than "SPI_FLASH_PageSize" value.
* Output         : None
* Return         : 0:succed 1:fail
*******************************************************************************/
uint8_t SPI_FLASH_PageWrite(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
  uint8_t FLASH_Status,error_flag = RT_OK;
  /* Enable the write access to the FLASH */
  SPI_FLASH_WriteEnable();

  /* Select the FLASH: Chip Select low */
  macSPI_FLASH_CS_ENABLE();
  /* Send "Write to Memory " instruction */
  SPI_FLASH_SendByte(W25X_PageProgram);
  /* Send WriteAddr high nibble address byte to write to */
  SPI_FLASH_SendByte((WriteAddr & 0xFF0000) >> 16);
  /* Send WriteAddr medium nibble address byte to write to */
  SPI_FLASH_SendByte((WriteAddr & 0xFF00) >> 8);
  /* Send WriteAddr low nibble address byte to write to */
  SPI_FLASH_SendByte(WriteAddr & 0xFF);

  if(NumByteToWrite > SPI_FLASH_PerWritePageSize)
  {
     NumByteToWrite = SPI_FLASH_PerWritePageSize;
     //printf("\n\r Err: SPI_FLASH_PageWrite too large!");
  }
#if SPI_HIGH_SPEED_EN==0
  /* while there is data to be written on the FLASH */
  while (NumByteToWrite--)
  {
    /* Send the current byte */
    SPI_FLASH_SendByte(*pBuffer);
    /* Point on the next byte to be written */
    pBuffer++;
  }
#else
	if(NumByteToWrite != 0x00){
		spi_high_speed_comm((uint16_t)pBuffer,0,NumByteToWrite,HALF_DUPLEX_TX);
		wait_spi_high_comm_end();
	}
#endif
  /* Deselect the FLASH: Chip Select high */
  macSPI_FLASH_CS_DISABLE();

  delay_us(2);
  macSPI_FLASH_CS_ENABLE();
  SPI_FLASH_SendByte(W25X_ReadStatusReg);
  FLASH_Status = SPI_FLASH_SendByte(Dummy_Byte);	 
  if((FLASH_Status & WIP_Flag) == RESET)
  {
     error_flag = RT_FAIL;
  }
  macSPI_FLASH_CS_DISABLE();

  /* Wait the end of Flash writing */
  SPI_FLASH_WaitForWriteEnd();

  return error_flag;
}
/*******************************************************************************
* Function Name  : SPI_FLASH_BufferWrite_Normal
* Description    : Writes block of data to the FLASH. In this function, the
*                  number of WRITE cycles are reduced, using Page WRITE sequence.
* Input          : - pBuffer : pointer to the buffer  containing the data to be
*                    written to the FLASH.
*                  - WriteAddr : FLASH's internal address to write to.
*                  - NumByteToWrite : number of bytes to write to the FLASH.
* Output         : None
* Return         : None
*******************************************************************************/
uint8_t SPI_FLASH_BufferWrite_Normal(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
  uint8_t NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0, temp = 0;
  uint8_t error_flag = RT_OK;

  Addr = WriteAddr % SPI_FLASH_PageSize;
  count = SPI_FLASH_PageSize - Addr;
  NumOfPage =  NumByteToWrite / SPI_FLASH_PageSize;
  NumOfSingle = NumByteToWrite % SPI_FLASH_PageSize;

  if (Addr == 0) /* WriteAddr is SPI_FLASH_PageSize aligned  */
  {
    if (NumOfPage == 0) /* NumByteToWrite < SPI_FLASH_PageSize */
    {
      SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumByteToWrite);
    }
    else /* NumByteToWrite > SPI_FLASH_PageSize */
    {
      while (NumOfPage--)
      {
        error_flag = SPI_FLASH_PageWrite(pBuffer, WriteAddr, SPI_FLASH_PageSize);
		if(error_flag)return RT_FAIL;
        WriteAddr +=  SPI_FLASH_PageSize;
        pBuffer += SPI_FLASH_PageSize;
      }

      SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumOfSingle);
    }
  }
  else /* WriteAddr is not SPI_FLASH_PageSize aligned  */
  {
    if (NumOfPage == 0) /* NumByteToWrite < SPI_FLASH_PageSize */
    {
      if (NumOfSingle > count) /* (NumByteToWrite + WriteAddr) > SPI_FLASH_PageSize */
      {
        temp = NumOfSingle - count;

        error_flag = SPI_FLASH_PageWrite(pBuffer, WriteAddr, count);
		if(error_flag)return RT_FAIL;
        WriteAddr +=  count;
        pBuffer += count;

        error_flag = SPI_FLASH_PageWrite(pBuffer, WriteAddr, temp);
		if(error_flag)return RT_FAIL;
      }
      else
      {
        error_flag = SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumByteToWrite);
		if(error_flag)return RT_FAIL;
      }
    }
    else /* NumByteToWrite > SPI_FLASH_PageSize */
    {
      NumByteToWrite -= count;
      NumOfPage =  NumByteToWrite / SPI_FLASH_PageSize;
      NumOfSingle = NumByteToWrite % SPI_FLASH_PageSize;

      error_flag = SPI_FLASH_PageWrite(pBuffer, WriteAddr, count);
	  if(error_flag)return RT_FAIL;
      WriteAddr +=  count;
      pBuffer += count;

      while (NumOfPage--)
      {
        error_flag = SPI_FLASH_PageWrite(pBuffer, WriteAddr, SPI_FLASH_PageSize);
		if(error_flag)return RT_FAIL;
        WriteAddr +=  SPI_FLASH_PageSize;
        pBuffer += SPI_FLASH_PageSize;
      }

      if (NumOfSingle != 0)
      {
        error_flag = SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumOfSingle);
		if(error_flag)return RT_FAIL;
      }
    }
  }
  return 0;
}

/*******************************************************************************
* Function Name  : SPI_FLASH_WriteEnable
* Description    : Enables the write access to the FLASH.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_FLASH_WriteEnable(void)
{
  /* Select the FLASH: Chip Select low */
  macSPI_FLASH_CS_ENABLE();

  /* Send "Write Enable" instruction */
  SPI_FLASH_SendByte(W25X_WriteEnable);

  /* Deselect the FLASH: Chip Select high */
  macSPI_FLASH_CS_DISABLE();
}

/*******************************************************************************
* Function Name  : SPI_FLASH_BufferRead_Normal
* Description    : Reads a block of data from the FLASH.
* Input          : - pBuffer : pointer to the buffer that receives the data read
*                    from the FLASH.
*                  - ReadAddr : FLASH's internal address to read from.
*                  - NumByteToRead : number of bytes to read from the FLASH.
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_FLASH_BufferRead_Normal(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead)
{
  /* Select the FLASH: Chip Select low */
  macSPI_FLASH_CS_ENABLE();

  /* Send "Read from Memory " instruction */
  SPI_FLASH_SendByte(W25X_ReadData);

  /* Send ReadAddr high nibble address byte to read from */
  SPI_FLASH_SendByte((ReadAddr & 0xFF0000) >> 16);
  /* Send ReadAddr medium nibble address byte to read from */
  SPI_FLASH_SendByte((ReadAddr& 0xFF00) >> 8);
  /* Send ReadAddr low nibble address byte to read from */
  SPI_FLASH_SendByte(ReadAddr & 0xFF);
#if SPI_HIGH_SPEED_EN==0
  while (NumByteToRead--) /* while there is data to be read */
  {
    /* Read a byte from the FLASH */
    *pBuffer = SPI_FLASH_SendByte(Dummy_Byte);
    /* Point to the next location where the byte read will be saved */
    pBuffer++;
  }
#else
	if(NumByteToRead != 0x00){
		spi_high_speed_comm(0,(uint16_t)pBuffer,NumByteToRead,HALF_DUPLEX_RX);
		wait_spi_high_comm_end();
	}
#endif
  /* Deselect the FLASH: Chip Select high */
  macSPI_FLASH_CS_DISABLE();
}
/*******************************************************************************
* Function Name  : SPI_FLASH_WaitForWriteEnd
* Description    : Polls the status of the Write In Progress (WIP) flag in the
*                  FLASH's status  register  and  loop  until write  opertaion
*                  has completed.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_FLASH_WaitForWriteEnd(void)
{
  uint8_t FLASH_Status = 0;

  /* Select the FLASH: Chip Select low */
  macSPI_FLASH_CS_ENABLE();

  /* Send "Read Status Register" instruction */
  SPI_FLASH_SendByte(W25X_ReadStatusReg);

  /* Loop as long as the memory is busy with a write cycle */
  do
  {
    /* Send a dummy byte to generate the clock needed by the FLASH
    and put the value of the status register in FLASH_Status variable */
    FLASH_Status = SPI_FLASH_SendByte(Dummy_Byte);	 
  }
  while ((FLASH_Status & WIP_Flag) == SET); /* Write in progress */

  /* Deselect the FLASH: Chip Select high */
  macSPI_FLASH_CS_DISABLE();
}

/*******************************************************************************
* Function Name  : FLASH_ReadID
* Description    : Read the FLASH id.
* Input          : None
* Output         : None
* Return         : FLASH id
*******************************************************************************/
uint32_t SPI_FLASH_ReadID(void)
{
  uint32_t Temp = 0;
  uint8_t Temp0 = 0, Temp1 = 0, Temp2 = 0;

  /* Select the FLASH: Chip Select low */
  macSPI_FLASH_CS_ENABLE();

  /* Send "RDID " instruction */
  SPI_FLASH_SendByte(W25X_JedecDeviceID);//W25X_DeviceID
  
  /* Read a byte from the FLASH */
  Temp0 = SPI_FLASH_SendByte(Dummy_Byte);
  Temp1 = SPI_FLASH_SendByte(Dummy_Byte);
  Temp2 = SPI_FLASH_SendByte(Dummy_Byte);

  /* Deselect the FLASH: Chip Select high */
   macSPI_FLASH_CS_DISABLE();

  Temp = (Temp0 << 16) | (Temp1 << 8) | Temp2;
  return Temp;
}

void SPI_FLASH_ReadUID(uint8_t *p_uid)
{
	uint8_t i,Temp = 0;
	
  /* Select the FLASH: Chip Select low */
	macSPI_FLASH_CS_ENABLE();

  /* Send "RDID " instruction */
	SPI_FLASH_SendByte(W25X_ReadUID);//W25X_UID
	/* Read a byte from the FLASH */	
	Temp =  SPI_FLASH_SendByte(Dummy_Byte);
	/* Read a byte from the FLASH */	
	Temp =  SPI_FLASH_SendByte(Dummy_Byte);
	/* Read a byte from the FLASH */	
	Temp =  SPI_FLASH_SendByte(Dummy_Byte);
	Temp =  SPI_FLASH_SendByte(Dummy_Byte);
  
	for(i=0; i<16; i++)
	{
		p_uid[i] = SPI_FLASH_SendByte(Dummy_Byte);
	}
  /* Deselect the FLASH: Chip Select high */
	macSPI_FLASH_CS_DISABLE();

}

/*******************************************************************************
* Function Name  : SET_FLASH_DeepPowerDown
* Description    : set the FLASH enter DeepPowerDown mode.
* Input          : None
* Output         : None
* Return         : none
*******************************************************************************/
void SET_FLASH_DeepPowerDown(void)
{

  /* Select the FLASH: Chip Select low */
  macSPI_FLASH_CS_ENABLE();

  /* Send "W25X_PowerDown " instruction */
  SPI_FLASH_SendByte(W25X_PowerDown);
 
  /* Deselect the FLASH: Chip Select high */
   macSPI_FLASH_CS_DISABLE();

}
/*******************************************************************************
* Function Name  : Release_FLASH_from_DeepPowerDown
* Description    : Release the FLASH from DeepPowerDown mode.
* Input          : None
* Output         : None
* Return         : 0
*******************************************************************************/
void Release_FLASH_from_DeepPowerDown(void)
{

  /* Select the FLASH: Chip Select low */
  macSPI_FLASH_CS_ENABLE();

  /* Send "W25X_PowerDown " instruction */
  SPI_FLASH_SendByte(W25X_ReleasePowerDown);
 
  /* Deselect the FLASH: Chip Select high */
   macSPI_FLASH_CS_DISABLE();

}

#if 0
/*!
    \brief      spi work example
    \param[in]  none
    \param[out] none
    \retval     none
*/
uint8_t xdata spi_tx_data_test[1024];
uint8_t xdata spi_rx_data_test[1024];
void byd_spi_work(void)
{
    uint8_t ret;
    uint16_t i;
	uint32_t uiFlashId;	

	for(i=0;i<1024;i++)
	{
		spi_tx_data_test[i] = i;
		spi_rx_data_test[i] = 0x00;
	}
			
    uiFlashId = SPI_FLASH_ReadID();
	if((uiFlashId>>8)!=0x8560)
	{
		uiFlashId = SPI_FLASH_ReadID();
		if((uiFlashId>>8)!=0x8560)
			return;
	}

	ret = SPI_FLASH_SectorErase(Sector_0_Address);
	if(ret)return;

	ret = SPI_FLASH_BufferWrite_Normal(spi_tx_data_test,Sector_0_Address,1024);
	if(ret)return;

	SPI_FLASH_BufferRead_Normal(spi_rx_data_test,Sector_0_Address,1024);	
	
}
#endif
