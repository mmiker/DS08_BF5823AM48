#ifndef __ISO14443_H__
#define __ISO14443_H__

#include "mcu02_rfid.h"

/*TypeA�������*/
#define CMD_REQA       ( 0x26 )
#define CMD_WUPA       ( 0x52 )
#define CMD_CL1        ( 0x93 )
#define CMD_CL2        ( 0x95 )
#define CMD_CL3        ( 0x97 )
#define CMD_HLTA       ( 0x50 )
#define CMD_RATS       ( 0xE0 )

#define CT_CH          ( 0x88 )

#define CRC_A   		1
#define CRC_B   		2

#define RETURN_NO              1    //����ʧ��
#define RETURN_OK              0    //���سɹ�

#define RFID_SEND_MODE_SEL     0//0 ��byte��, 1 ��bit��, 2 ��9bit��
#define RFID_RECEIVE_MODE_SEL  0//0 ��byte��, 1 ��bit��

#define RFID_ANTI_SEL           1//0 �ر�Ӳ�����ͷ���ͻ֡; 1 ʹ��Ӳ�����ͷ���ͻ֡;Ӳ�����ֻ��4�ֽڿ���Ч,SEL����0x93
#define RFID_ANTI_HANDLE       0//����ͻ����

#define BITS(x)                (0xFF >> (8 - x + 1))


void typea_card_send_bit(u8 *inByte,u8 lenBit);

u8 piccWakeupA(uint8_t *ATQA);
u8 piccAntiA(u8 SEL, u8 rand_bit, u8 *uid);
u8 piccSelectA(u8 SEL,u8 *uid, u8 *SAK,u8 len);
u8 piccHaltA(void);
u8 get_card_number(u8 *uid);

extern u16 ComputeCrc(u8 CRCType, u8 *Data, char Length);
//extern u8 typea_bit_dispose(u8 *inData, u8 *outData, u8 lenbit);
#endif