#ifndef __BYD_MIFARE_H__
#define __BYD_MIFARE_H__

#include "mcu02_gpio.h"	

/*通信错误码表*/
#define BCC_ERROR             ( 0xB1 )
#define CT_ERROR              ( 0xB2 )
#define CRC_ERROR             ( 0xB3 )
#define UID_ERROR             ( 0xB4 )


#define PSW_TYPE_ERROR         ( 0xA4 )//类型参数错误
#define AUTHEN_ERROR           ( 0xA5 )//认证失败
#define TRANS_ERROR            ( 0xA6 )//传输错误
#define INVALID_CMD_ERROR      ( 0xA7 )//无效命令
#define RECEIVE_NONE		   ( 0xA8 )//未接收到数据



/**
 * Mifare三重认证协议
 * 
 * 参数：
 *     pucUID       : 卡片UID(4字节)
 *     ucBlkNo      : 块号
 *     cType       : A或B组密码(1字节) 
 *                     'a'或'A' - 验证A组密码
 *                     'b'或'B' - 验证B组密码
 *     pucKey       : 扇区待校验密码(6字节)
 *     mode         : 再次认证标记（已经有一次正确认证情况下进行）
 *                    0:第一次认证  1：第二次认证
 * 返回：
 *      = RETURN_OK, 认证完成
 *     != RETURN_OK, 认证失败(AUTHEN_ERROR or TRANS_ERROR or PSW_TYPE_ERROR or RECEIVE_NONE)
 */
extern u8 MifareAuthenticate(u8 *pucUID,u8 ucBlkNo,u8 cType,u8 *pucKey,u8 mode);

/**
 * Mifare操作，包括读/写
 * 
 * 参数：
 *     pucUID    : 卡片UID(4字节)
 *     cOpCode  : 操作类型
 *                  'r' - 块读
 *                  'w' - 块写
 *     ucSrcBlkNo  : 源操作块号
 *     ucDestBlkNo : 目标操作块号
 *     pucData     : 数据区
 * 返回：
 *      = RETURN_OK, 操作完成
 *      !=RETURN_OK, 操作失败(INVALID_CMD_ERROR or TRANS_ERROR or CRC_ERROR or RECEIVE_NONE)
 */
extern u8 MifareOperations( u8 cOpCode,u8 ucSrcBlkNo,u8 ucDestBlkNo,u8 *pucData);


extern u8 M1_Example(u8 *uid);

#endif