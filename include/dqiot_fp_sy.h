#ifndef __DQIOT_FP_SY_H__
#define __DQIOT_FP_SY_H__
#include "mmi_feature.h"
#if defined (__LOCK_FP_SY_SUPPORT__)

#include "dq_project.h"

static unsigned long AS608_Addr = 0xFFFFFFFF;

#define CHAR_BUFFER1 0x01
#define CHAR_BUFFER2 0x02
#define CHAR_BUFFER3 0x03
#define CHAR_BUFFER4 0x04

#define PS_MAXNUM   299          /*ָ��ģ�����洢ָ��ģ����*/

//typedef void (*fp_irq_handle_callback)(void);
//typedef void (*fp_uart_handle_callback)(unsigned char type,unsigned char *reply,unsigned short reply_len);

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

//void AS608_SendData(unsigned char buf_data);//AS608_USART������ָ��ģ�鴫������ 
//unsigned char AS608_PackHead(void);// AS608_USART������ָ��ģ�������ͷ��ʽ 
//unsigned char AS608_PackHead2(void);// AS608_USART������ָ��ģ�������ͷ��ʽ 

//void SendFlag(unsigned char flag);//���Ͱ���ʶ
//void SendLength(unsigned short length);// ���Ͱ�����
//void Sendcmd(unsigned char cmd);// ����ָ����
//void SendCheck(unsigned short check);//����У���
 
 
 unsigned char PS_GetEcho(void);
 unsigned char PS_GetImage(void);// ̽����ָ��̽�⵽��¼��ָ��ͼ����� ImageBuffer
 unsigned char PS_GenChar(unsigned char BufferID);//��ImageBuffer�е�ԭʼͼ������ָ�������ļ�����CHARBUFFER1��CHARBUFFER2
 unsigned char PS_Match(void);// ��ȷ�ȶ� CHARBUFFER1��CHARBUFFER2�е������ļ�
 unsigned char PS_RegModel(void);//��CHARBUFFER1��CHARBUFFER2 �е������ļ��ϲ�����ģ�壬
 unsigned char PS_StoreChar(unsigned char BufferID,unsigned short PageID);//�� CHARBUFFER1 �� CHARBUFFER2 �е�ģ���ļ��浽 PageID ��flash ���ݿ�λ�á�
 unsigned char PS_DeletChar(unsigned short PageID,unsigned short N);//ɾ�� flash ���ݿ���ָ��ID�ſ�ʼ��N��ָ��ģ��
 unsigned char PS_HighSpeedSearch(unsigned char BufferID,unsigned short StartPage,unsigned short PageNum,unsigned short *p);//��CHARBUFFER1��CHARBUFFER2�е������ļ��������������򲿷�ָ�ƿ�
 unsigned char  PS_Empty(void);// ɾ�� flash ���ݿ�������ָ��ģ��
 //unsigned char PS_Connect(unsigned long *PS_Addr);//���STM32��ָ��ģ���ͨ������
 unsigned char PS_ValidTempleteNum(unsigned short *ValidN);
 unsigned char PS_Search(unsigned char BufferID,unsigned short StartPage,unsigned short PageNum,unsigned short *p);
unsigned char PS_HandShake(unsigned long *PS_Addr);
//unsigned char PS_ReadSysPara(void);
void FP_Light(FP_COLOR_E light_id);
//void AS608_EnterSleep(void);
FP_COLOR_E FP_Get_Light(void);

unsigned char FP_Get_Start_Flag(void);
#endif
#endif //__DQIOT_FP_AS608_H__

