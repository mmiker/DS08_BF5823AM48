#include "byd_mifare.h" 
#include "iso14443.h"
#include "delay.h"


/***********************************************************
** �� �� ��: u8 M1_PwdChange(u8 blockAddr, u8 *key_a, u8 *key_b)
** ��������: M1���޸���������
** ��  ����: blockAddr Ҫ�������������ַ
             key_a ��ԿA
			 key_b ��ԿB
** ��  ����: ��
** ��    ��: RETURN_OK��RETURN_NO
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
    tmpBuf[9]    =   0x69;          // ffH 07H 80H 69H ��Ĭ�ϵĿ�����
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
** �� �� ��: u8 M1_Example(u8 *uid)
** ��������: M1��ʹ��ʾ��,ǰ�������ȷ����
** ��  ����: ����
** ��  ����: ��
** ��    ��: RETURN_OK��RETURN_NO
***********************************************************/
u8 M1_Example(u8 *uid)
{
    u8 ret = RETURN_NO;
	u8 aucPswA[6] = {0xff,0xff,0xff,0xff,0xff,0xff};//Ĭ����ԿA
	u8 aucBlkBuf[18];

   	ret = MifareAuthenticate(uid, 4, 'A', aucPswA, 0);//ÿ��������֤һ��,��һ��ִ����֤
    if(RETURN_OK == ret)
	{
		if(RETURN_OK == MifareOperations( 'r', 4, 4, aucBlkBuf))//����4������ 16byte
		{			
		   ret = RETURN_OK;
		}
		if(RETURN_OK == MifareOperations( 'r', 5, 5, aucBlkBuf))//����5������ 16byte
		{			
		   ret = RETURN_OK;
		}
		if(RETURN_OK == MifareOperations( 'r', 6, 6, aucBlkBuf))//����6������ 16byte
		{			
		   ret = RETURN_OK;
		}
	}
	ret = MifareAuthenticate(uid, 8, 'A', aucPswA, 1);//ÿ��������֤һ��,��������ٴ���֤
    if(RETURN_OK == ret)
	{
		if(RETURN_OK == MifareOperations( 'r', 8, 8, aucBlkBuf))//����8������ 16byte
		{			
		   ret = RETURN_OK;
		}
		if(RETURN_OK == MifareOperations( 'r', 9, 9, aucBlkBuf))//����9������ 16byte
		{			
		   ret = RETURN_OK;
		}
		if(RETURN_OK == MifareOperations( 'r', 10, 10, aucBlkBuf))//����10������ 16byte
		{			
		   ret = RETURN_OK;
		}
	}
	return ret;
}