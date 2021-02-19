#include "byd_mifare.h" 
#include "iso14443.h"
#include "delay.h"
#include "dqiot_drv.h"

/***********************************************************
** 函 数 名: u8 M1_PwdChange(u8 blockAddr, u8 *key_a, u8 *key_b)
** 功能描述: M1卡修改扇区密码
** 输  　入: blockAddr 要操作的扇区块地址
             key_a 密钥A
			 key_b 密钥B
** 输  　出: 无
** 返    回: RETURN_OK或RETURN_NO
***********************************************************/
u8 M1_PwdChange(u8 blockAddr, u8 *key_a, u8 *key_b)
{
    u8 tmpBuf[16];

   	tmpBuf[0]    =   key_a[0];
    tmpBuf[1]    =   key_a[1];
    tmpBuf[2]    =   key_a[2];
    tmpBuf[3]    =   key_a[3];
    tmpBuf[4]    =   key_a[4];
    tmpBuf[5]    =   key_a[5];
    tmpBuf[6]    =   0xff;
    tmpBuf[7]    =   0x07;
    tmpBuf[8]    =   0x80;
    tmpBuf[9]    =   0x69;          // ffH 07H 80H 69H 是默认的控制字
    tmpBuf[10]   =   key_b[0];
    tmpBuf[11]   =   key_b[1];
    tmpBuf[12]   =   key_b[2];
    tmpBuf[13]   =   key_b[3];
    tmpBuf[14]   =   key_b[4];
    tmpBuf[15]   =   key_b[5];

	if(RETURN_OK == MifareOperations( 'w', blockAddr, blockAddr, tmpBuf))
	{
	   return  RETURN_OK;
	}
    
	return RETURN_NO;
}

/***********************************************************
** 函 数 名: u8 M1_Example(u8 *uid)
** 功能描述: M1卡使用示例,前提读到正确卡号
** 输  　入: 卡号
** 输  　出: 无
** 返    回: RETURN_OK或RETURN_NO
***********************************************************/
u8 M1_Example(u8 *uid)
{
    u8 ret = RETURN_NO;
	u8 aucPswA[6] = {0xff,0xff,0xff,0xff,0xff,0xff};//默认密钥A
	u8 aucBlkBuf[18];
	u8 num = 0;

   	ret = MifareAuthenticate(uid, 0, 'A', aucPswA, 0);//每个扇区认证一次,第一次执行认证
    if(RETURN_OK == ret)
	{
		if(RETURN_OK == MifareOperations( 'r', 0, 0, aucBlkBuf))//读第4块数据 16byte
		{			
			num = 0;
		   dqiot_drv_uart0_sendData(&num,1);
		   dqiot_drv_uart0_sendData(aucBlkBuf,18);
		   ret = RETURN_OK;
		}
		if(RETURN_OK == MifareOperations( 'r', 1, 1, aucBlkBuf))//读第5块数据 16byte
		{		
			num = 1;
		   dqiot_drv_uart0_sendData(&num,1);
		   dqiot_drv_uart0_sendData(aucBlkBuf,18);
		   ret = RETURN_OK;
		}
		if(RETURN_OK == MifareOperations( 'r', 2, 2, aucBlkBuf))//读第6块数据 16byte
		{		
			num = 2;
		   dqiot_drv_uart0_sendData(&num,1);
		   dqiot_drv_uart0_sendData(aucBlkBuf,18);
		   ret = RETURN_OK;
		}
		if(RETURN_OK == MifareOperations( 'r', 3, 3, aucBlkBuf))//读第6块数据 16byte
		{		
			num = 3;
		   dqiot_drv_uart0_sendData(&num,1);
		   dqiot_drv_uart0_sendData(aucBlkBuf,18);
		   ret = RETURN_OK;
		}
	}
	ret = MifareAuthenticate(uid, 8, 'A', aucPswA, 1);//每个扇区认证一次,这次属于再次认证
    if(RETURN_OK == ret)
	{
		if(RETURN_OK == MifareOperations( 'r', 8, 8, aucBlkBuf))//读第8块数据 16byte
		{	
			num = 8;
		   dqiot_drv_uart0_sendData(&num,1);
		   dqiot_drv_uart0_sendData(aucBlkBuf,18);
		   ret = RETURN_OK;
		}
		if(RETURN_OK == MifareOperations( 'r', 9, 9, aucBlkBuf))//读第9块数据 16byte
		{		
			num = 9;
		   dqiot_drv_uart0_sendData(&num,1);
		   dqiot_drv_uart0_sendData(aucBlkBuf,18);
		   ret = RETURN_OK;
		}
		if(RETURN_OK == MifareOperations( 'r', 10, 10, aucBlkBuf))//读第10块数据 16byte
		{		
			num = 10;
		   dqiot_drv_uart0_sendData(&num,1);
		   dqiot_drv_uart0_sendData(aucBlkBuf,18);
		   ret = RETURN_OK;
		}
		if(RETURN_OK == MifareOperations( 'r', 11, 11, aucBlkBuf))//读第10块数据 16byte
		{		
			num = 11;
		   dqiot_drv_uart0_sendData(&num,1);
		   dqiot_drv_uart0_sendData(aucBlkBuf,18);
		   ret = RETURN_OK;
		}
	}
	return ret;
}
