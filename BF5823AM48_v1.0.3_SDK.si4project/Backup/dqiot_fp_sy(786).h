#ifndef __DQIOT_FP_SY_H__
#define	__DQIOT_FP_SY_H__

#include "dq_project.h"

static unsigned long AS608_Addr = 0xFFFFFFFF;

#define CHAR_BUFFER1 0x01
#define CHAR_BUFFER2 0x02
#define CHAR_BUFFER3 0x03
#define CHAR_BUFFER4 0x04

#define PS_MAXNUM   299          /*指纹模块最大存储指纹模板数*/

typedef void (*fp_irq_handle_callback)(void);
typedef void (*fp_uart_handle_callback)(unsigned char type,unsigned char *reply,unsigned short reply_len);

typedef enum 
{
	BTL_M_FREE = 1,
	BTL_M_INPUT,
	BTL_M_COMPARE,
}BTL_MODE_E;

typedef enum
{
	FP_NONE_COLOR,
	FP_BLUE,
	FP_GREEN,
	FP_RED,
}FP_COLOR_E;



typedef enum
{
	FP_NONE,
	FP_BTL,
	FP_LT5X,
	FP_UNKNOW,
}FP_TYPE;


//extern uint8_t BTL_Input_Return;

//void fp_set_irq_handle(fp_irq_handle_callback cb);
//void fp_set_uart_handle(fp_uart_handle_callback cb);

//FP_TYPE fp_get_type(void);

//void AS608_SendData(unsigned char buf_data);//AS608_USART串口向指纹模块传递数据 
//unsigned char AS608_PackHead(void);// AS608_USART串口向指纹模块命令包头格式 
//unsigned char AS608_PackHead2(void);// AS608_USART串口向指纹模块命令包头格式 

//void SendFlag(unsigned char flag);//发送包标识
//void SendLength(unsigned short length);// 发送包长度
//void Sendcmd(unsigned char cmd);// 发送指令码
//void SendCheck(unsigned short check);//发送校验和
 
 
 unsigned char PS_GetEcho(void);
 unsigned char PS_GetImage(void);// 探测手指，探测到后录入指纹图像存于 ImageBuffer
 unsigned char PS_GenChar(unsigned char BufferID);//将ImageBuffer中的原始图像生成指纹特征文件存于CHARBUFFER1或CHARBUFFER2
 unsigned char PS_Match(void);// 精确比对 CHARBUFFER1与CHARBUFFER2中的特征文件
 unsigned char PS_RegModel(void);//将CHARBUFFER1与CHARBUFFER2 中的特征文件合并生成模板，
 unsigned char PS_StoreChar(unsigned char BufferID,unsigned short PageID);//将 CHARBUFFER1 或 CHARBUFFER2 中的模板文件存到 PageID 号flash 数据库位置。
 unsigned char PS_DeletChar(unsigned short PageID,unsigned short N);//删除 flash 数据库中指定ID号开始的N个指纹模板
 unsigned char PS_HighSpeedSearch(unsigned char BufferID,unsigned short StartPage,unsigned short PageNum,unsigned short *p);//以CHARBUFFER1或CHARBUFFER2中的特征文件高速搜索整个或部分指纹库
 unsigned char  PS_Empty(void);// 删除 flash 数据库中所有指纹模板
 //unsigned char PS_Connect(unsigned long *PS_Addr);//检查STM32与指纹模块的通信连接
 unsigned char PS_ValidTempleteNum(unsigned short *ValidN);
 unsigned char PS_Search(unsigned char BufferID,unsigned short StartPage,unsigned short PageNum,void *p);

//unsigned char PS_ReadSysPara(void);
void FP_Light(FP_COLOR_E light_id);
//void AS608_EnterSleep(void);
FP_COLOR_E FP_Get_Light(void);

#endif //__DQIOT_FP_AS608_H__

