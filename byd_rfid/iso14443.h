#ifndef __ISO14443_H__
#define __ISO14443_H__

#include "mcu02_rfid.h"

/*TypeA卡命令集合*/
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

#define RETURN_NO              1    //返回失败
#define RETURN_OK              0    //返回成功

#define RFID_SEND_MODE_SEL     0//0 按byte发, 1 按bit发, 2 按9bit发
#define RFID_RECEIVE_MODE_SEL  0//0 按byte收, 1 按bit收

#define RFID_ANTI_SEL           1//0 关闭硬件发送防冲突帧; 1 使能硬件发送防冲突帧;硬件设计只对4字节卡有效,SEL命令0x93
#define RFID_ANTI_HANDLE       0//防冲突处理

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