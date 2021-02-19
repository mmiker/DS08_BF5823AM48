#ifndef BYD_SPI_FLASH_H
#define	BYD_SPI_FLASH_H

#include "mcu02_sfr.h"
#include "mcu02_spi.h"
#include "delay.h"

#define RT_OK                        0
#define RT_FAIL                      1

#define	SPI_HIGH_SPEED_EN		     0//SPI高速通信使能


/* Private typedef -----------------------------------------------------------*/
#define SPI_FLASH_PageSize           256
#define SPI_FLASH_PerWritePageSize   256
#define W25X_BLOCK64K_SIZE			((uint32_t)0x00010000)
#define W25X_BLOCK32K_SIZE			((uint32_t)0x00008000)
#define W25X_SECTOR_SIZE		    ((uint32_t)0x00001000)

/* Private define ------------------------------------------------------------*/
#define W25X_WriteEnable		      0x06 
#define W25X_WriteDisable		      0x04 
#define W25X_ReadStatusReg		      0x05 
#define W25X_WriteStatusReg		      0x01 
#define W25X_ReadData			      0x03 
#define W25X_FastReadData		      0x0B 
#define W25X_FastReadDual		      0x3B 
#define W25X_PageProgram		      0x02
#define W25X_Block32KErase			  0x52 
#define W25X_BlockErase			      0xD8 
#define W25X_SectorErase		      0x20 
#define W25X_ChipErase			      0xC7 
#define W25X_PowerDown			      0xB9 
#define W25X_ReleasePowerDown	      0xAB 
#define W25X_DeviceID			      0xAB 
#define W25X_ManufactDeviceID   	  0x90 
#define W25X_JedecDeviceID		      0x9F
#define W25X_PageErase		          0x81 
#define W25X_ReadUID		          0x4B

#define WIP_Flag                      0x01  /* Write In Progress (WIP) flag */

#define Dummy_Byte                    0x55//0xFF

/*==============		SECTOR & Block地址		======================*/
#define 	Sector_0_Address							((uint32_t)0x00000000)
#define 	Sector_1_Address							((uint32_t)0x00001000)
#define 	Sector_2_Address							((uint32_t)0x00002000)
#define 	Sector_3_Address							((uint32_t)0x00003000)
#define 	Sector_4_Address							((uint32_t)0x00004000)
#define 	Sector_5_Address							((uint32_t)0x00005000)
#define 	Sector_6_Address							((uint32_t)0x00006000)
#define 	Sector_7_Address							((uint32_t)0x00007000)
#define 	Sector_8_Address							((uint32_t)0x00008000)
#define 	Sector_9_Address							((uint32_t)0x00009000)
#define 	Sector_10_Address							((uint32_t)0x0000A000)
#define 	Sector_11_Address							((uint32_t)0x0000B000)
#define 	Sector_12_Address							((uint32_t)0x0000C000)
#define 	Sector_13_Address							((uint32_t)0x0000D000)
#define 	Sector_14_Address							((uint32_t)0x0000E000)
#define 	Sector_15_Address							((uint32_t)0x0000F000)


/************************** SPI Flash 函数宏定义********************************/
#define macSPI_FLASH_CS_ENABLE()		SPI1_CFG1 &= ~SPI_CS_N;delay_us(1);
#define macSPI_FLASH_CS_DISABLE()		delay_us(1);SPI1_CFG1 |= SPI_CS_N

uint8_t SPI_FLASH_SectorErase(uint32_t SectorAddr);
uint8_t SPI_FLASH_PageErase(uint32_t PageAddr);
uint8_t SPI_FLASH_Block32kErase(uint32_t BlockAddr);
uint8_t SPI_FLASH_Block64kErase(uint32_t BlockAddr);
uint8_t SPI_FLASH_BulkErase(void);
uint8_t SPI_FLASH_PageWrite(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
void SPI_FLASH_WriteEnable(void);
void SPI_FLASH_WaitForWriteEnd(void);
uint8_t SPI_FLASH_SendByte(uint8_t dat);
void SPI_FLASH_BufferRead_Normal(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead);
uint8_t SPI_FLASH_BufferWrite_Normal(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
uint32_t SPI_FLASH_ReadID(void);
void SPI_FLASH_ReadUID(uint8_t *p_uid);
void SET_FLASH_DeepPowerDown(void);
void Release_FLASH_from_DeepPowerDown(void);

void byd_spi_work(void);

#endif