#ifndef __BYD_MIFARE_H__
#define __BYD_MIFARE_H__

#include "mcu02_gpio.h"	

/*ͨ�Ŵ������*/
#define BCC_ERROR             ( 0xB1 )
#define CT_ERROR              ( 0xB2 )
#define CRC_ERROR             ( 0xB3 )
#define UID_ERROR             ( 0xB4 )


#define PSW_TYPE_ERROR         ( 0xA4 )//���Ͳ�������
#define AUTHEN_ERROR           ( 0xA5 )//��֤ʧ��
#define TRANS_ERROR            ( 0xA6 )//�������
#define INVALID_CMD_ERROR      ( 0xA7 )//��Ч����
#define RECEIVE_NONE		   ( 0xA8 )//δ���յ�����



/**
 * Mifare������֤Э��
 * 
 * ������
 *     pucUID       : ��ƬUID(4�ֽ�)
 *     ucBlkNo      : ���
 *     cType       : A��B������(1�ֽ�) 
 *                     'a'��'A' - ��֤A������
 *                     'b'��'B' - ��֤B������
 *     pucKey       : ������У������(6�ֽ�)
 *     mode         : �ٴ���֤��ǣ��Ѿ���һ����ȷ��֤����½��У�
 *                    0:��һ����֤  1���ڶ�����֤
 * ���أ�
 *      = RETURN_OK, ��֤���
 *     != RETURN_OK, ��֤ʧ��(AUTHEN_ERROR or TRANS_ERROR or PSW_TYPE_ERROR or RECEIVE_NONE)
 */
extern u8 MifareAuthenticate(u8 *pucUID,u8 ucBlkNo,u8 cType,u8 *pucKey,u8 mode);

/**
 * Mifare������������/д
 * 
 * ������
 *     pucUID    : ��ƬUID(4�ֽ�)
 *     cOpCode  : ��������
 *                  'r' - ���
 *                  'w' - ��д
 *     ucSrcBlkNo  : Դ�������
 *     ucDestBlkNo : Ŀ��������
 *     pucData     : ������
 * ���أ�
 *      = RETURN_OK, �������
 *      !=RETURN_OK, ����ʧ��(INVALID_CMD_ERROR or TRANS_ERROR or CRC_ERROR or RECEIVE_NONE)
 */
extern u8 MifareOperations( u8 cOpCode,u8 ucSrcBlkNo,u8 ucDestBlkNo,u8 *pucData);


extern u8 M1_Example(u8 *uid);

#endif