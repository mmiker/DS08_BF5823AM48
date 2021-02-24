
//#if defined (__PREIPHERAL_FP_SY_SUPPORT__)
//#include "string.h"
#include "dqiot_fp_sy.h"
#include "delay.h"
#include "dqiot_drv.h"
#include "mcu02_uart.h"

//unsigned long fp_pin_irq_mask;

//fp_irq_handle_callback fp_callback_handle;
//fp_uart_handle_callback fp_uart_handle = 0;
//unsigned char fp_Mode = 0;
//static unsigned char fp_temp_mode = 0;

static unsigned char uart_rec_buff[20];

//static FP_TYPE fp_flag = FP_NONE;
static FP_COLOR_E Light_Color = FP_NONE_COLOR;
//static unsigned char ps_start_flag = 0;

extern unsigned char uart_get_buf[];
extern unsigned char uart_getbuflen;

//unsigned short  ReceiveInfo( unsigned char *rec_data);
//void AS608_log(void);

//void fp_set_irq_handle(fp_irq_handle_callback cb)
//{
//	fp_callback_handle = cb;
//}

//void fp_set_uart_handle(fp_uart_handle_callback cb)
//{
//	fp_uart_handle = cb;
//}

///FP_TYPE fp_get_type(void)
//{
//	return fp_flag;

//}

//--------------------------------------------------------------------------------

//static unsigned char uart_len=0;
//static unsigned short uart_maxlen = 0;
//static unsigned char uart_buff[25]={0};

//static void UART_Callback(unsigned char send_data)
//{
//	send_data = 0;
//}

//unsigned char fp_GetModeState(void)
//{
//	return fp_Mode;
//}

//void fp_SetModeState(unsigned char s)
//{
//	fp_Mode = s;

//	if(s == 0)
//		Light_Color = FP_NONE_COLOR;
//}

//static void PS_UART_Callback(unsigned char send_data)
//{
//	if(send_data == 0x55 )
//	{
//		ps_start_flag = 1;
//	}
//}

//void FP_PowerOn(void)
//{

//}

/**
  * @brief  AS608_USART������ָ��ģ�鴫������ 
  * @param  data;���������
  */
void AS608_SendData(unsigned char send_data)
{
	uart_tx_byte(UART0, send_data);
}

/**
  * @brief  AS608_USART������ָ��ģ�������ͷ��ʽ 
  * @param  ��
  */
unsigned char AS608_PackHead(void)
{

	//unsigned char delay_times = 30;

	//while(ps_start_flag==0&&delay_times>0)
	//{
	//	delay_times--;
	//}
	//if(ps_start_flag == 0)
	//{
	//	return 1;
	//}
	//else if(ps_start_flag == 1)
	//{
	//	uart_init_block();
	//	ps_start_flag = 2;
	//}

	/*��ͷ SendHead*/
	AS608_SendData(0xEF);
	AS608_SendData(0x01);

	/*ָ��ģ���ַ SendAddr*/
	AS608_SendData(AS608_Addr >> 24);
	AS608_SendData(AS608_Addr >> 16);
	AS608_SendData(AS608_Addr >> 8);
	AS608_SendData(AS608_Addr);

	return 0;
}

unsigned char AS608_PackHead2(void)
{

	/*��ͷ SendHead*/
	AS608_SendData(0xEF);
	AS608_SendData(0x01);

	/*ָ��ģ���ַ*/
	AS608_SendData(AS608_Addr >> 24);
	AS608_SendData(AS608_Addr >> 16);
	AS608_SendData(AS608_Addr >> 8);
	AS608_SendData(AS608_Addr);

	return 0;
}

/**
  * @brief  ���Ͱ���ʶ
  * @param  flag:�����־
  * @retval ��
  */
void SendFlag(unsigned char flag)
{
	AS608_SendData(flag);
}

/**
  * @brief  ���Ͱ�����
  * @param  length:������
  * @retval ��
  */
void SendLength(unsigned short length)
{
	AS608_SendData(length >> 8);
	AS608_SendData(length);
}

/**
  * @brief  ����ָ����
  * @param  cmd;ָ����
  * @retval ��
  */
void Sendcmd(unsigned char cmd)
{
	AS608_SendData(cmd);
}

/**
  * @brief  ����У���
  * @param  check:���λ
  * @retval ��
  */
void SendCheck(unsigned short check)
{
	AS608_SendData(check >> 8);
	AS608_SendData(check);
}

/**
  * @brief  �ж��жϽ��յ�������û��Ӧ���
  * @param  
  * waittimeΪ�ȴ��жϽ������ݵ�ʱ��(��λ1ms)
  * lengthΪ������
  * @return ���ݰ�ȷ����
  * @note   1 failed
  * @see    none
  */
static u8 JudgeStr(u16 waittime, u8 length)
{
	u8 getdata;
	u8 i = 0, j = 0;
	//u8 str[8];
	//str[0] = 0xEF;
	//str[1] = 0x01;
	//str[2] = AS608_Addr >> 24;
	//str[3] = AS608_Addr >> 16;
	//str[4] = AS608_Addr >> 8;
	//str[5] = AS608_Addr;
	//str[6] = 0x07;

	while (--waittime)
	{
		delay_ms(1);

		/* ���յ�һ������ */
		if (uart_getbuflen >= 9 + length)
		{
			/* Ѱ��0xEFλ�� */
			for (i = 0; i < uart_getbuflen; i++)
			{
				if (uart_get_buf[i] == 0xEF)
					break;
			}

			/* �ж��Ƿ�ΪӦ��� */
			if (uart_get_buf[i] == 0xEF && uart_get_buf[i + 1] == 0x01 && uart_get_buf[i + 6] == 0x07 && ((uart_get_buf[i + 7] << 8) + uart_get_buf[i + 8]) == length)
			{
				for (i; i < uart_getbuflen; i++)
				{
					uart_rec_buff[j] = uart_get_buf[i];
					j++;
				}
				getdata = uart_rec_buff[9]; //ȷ����

				/* ��ջ��� */
				uart_getbuflen = 0;

				return getdata;
			}
		}
	}

	return 1;
}

#if 0
/**
  * @brief  �ӻ���������ȷ����
  * @param  *i:����ֵ��ȷ���룩
  * @retval ��
  */
unsigned char  ReturnFlag( unsigned char *i)
{	
	*i = ReceiveInfo(uart_rec_buff);
	return *i;
}

unsigned char  ReceiveInfo( unsigned char *rec_data)
{
	unsigned char *temp_data;
	unsigned short rev_length = 0;
	unsigned char error = 0;
	unsigned char a = 9;

	memset(uart_rec_buff,0,sizeof(uart_rec_buff));

	do
	{
		//error = nrf_drv_uart_rx(rec_data,1);
		//if(error == NRF_ERROR_INTERNAL)
		//	return 0xFF;
		if(rec_data[0] == 0xEF)
			break;
		if(a==0)
			return 0xFF;
	}while(a--);
	

	rev_length = (rec_data[7]<<8)+rec_data[8];
	temp_data = rec_data+9;

	if(rev_length!=0)
		;//nrf_drv_uart_rx(temp_data,rev_length);
	else
		return 0xFF;

	AS608_log();
	return temp_data[0];
}
#endif

unsigned char PS_GetEcho(void)
{
	unsigned char sure; //,p=0;

	AS608_PackHead2();
	SendFlag(0x01);
	SendLength(0x03);
	Sendcmd(0x53); /*��������ָ��*/
	SendCheck(0x57);

	//sure=ReturnFlag(&p);
	sure = JudgeStr(1000, 0x03);

	return sure;
}

//¼��ͼ�� PS_GetImage
//����:̽����ָ��̽�⵽��¼��ָ��ͼ�����ImageBuffer��
//ģ�鷵��ȷ����
unsigned char PS_GetImage(void)
{
	unsigned short temp;
	unsigned char sure; //,p=0;
	/* ��ջ��� */
	uart_getbuflen = 0;

	//delay_ms(300);
	if (AS608_PackHead() == 1)
		return 0xFF;
	SendFlag(0x01); /*�������ʶ*/
	SendLength(0x03);
	Sendcmd(0x01); /*¼ָ��ָ��*/
	temp = 0x01 + 0x03 + 0x01;
	SendCheck(temp);

	// nrf_delay_ms(50); /*�ȴ�ָ��ʶ��ģ�鴦������*/

	// sure = ReturnFlag(&p);
	sure = JudgeStr(1000, 0x03);

	return sure;
}

//�������� PS_GenChar
//����:��ImageBuffer�е�ԭʼͼ������ָ�������ļ�����CharBuffer1��CharBuffer2
//����:BufferID --> charBuffer1:0x01	charBuffer1:0x02
//ģ�鷵��ȷ����
unsigned char PS_GenChar(unsigned char BufferID)
{
	unsigned short temp;
	unsigned char sure; //,p=0;

	if (AS608_PackHead() == 1)
		return 0xFF;
	SendFlag(0x01);
	SendLength(0x04);
	Sendcmd(0x02); /*��������ָ��*/
	AS608_SendData(BufferID);
	temp = 0x01 + 0x04 + 0x02 + BufferID;
	SendCheck(temp);
	//	mmi_dq_log_wakeup_count();
	// sure = ReturnFlag(&p);
	sure = JudgeStr(1000, 0x03);

	return sure;
}

//��ȷ�ȶ���öָ������ PS_Match
//����:��ȷ�ȶ�CharBuffer1 ��CharBuffer2 �е������ļ�
//ģ�鷵��ȷ����
unsigned char PS_Match(void)
{
	unsigned short temp;
	unsigned char sure; //,p=0;

	if (AS608_PackHead() == 1)
		return 0xFF;
	SendFlag(0x01);
	SendLength(0x03);
	Sendcmd(0x03); /*��ȷ�ȶ�ָ��*/
	temp = 0x01 + 0x03 + 0x03;
	SendCheck(temp);

	// sure = ReturnFlag(&p);
	sure = JudgeStr(1000, 0x05);

	return sure;
}
//����ָ�� PS_Search
//����:��CharBuffer1��CharBuffer2�е������ļ����������򲿷�ָ�ƿ�.�����������򷵻�ҳ�롣
//����:  BufferID @ref CharBuffer1	CharBuffer2
//˵��:  ģ�鷵��ȷ���֣�ҳ�루����ָ��ģ�壩
unsigned char PS_Search(unsigned char BufferID, unsigned short StartPage, unsigned short PageNum, void *p)
{
	unsigned short temp;
	unsigned char ensure;
	//	QUEUE_DATA_TYPE   *rx_data;

	p = 0;

	if (AS608_PackHead() == 1)
		return 0xFF;
	SendFlag(0x01); //�������ʶ
	SendLength(0x08);
	Sendcmd(0x04);
	AS608_SendData(BufferID);
	AS608_SendData(StartPage >> 8);
	AS608_SendData(StartPage);
	AS608_SendData(PageNum >> 8);
	AS608_SendData(PageNum);
	temp = 0x01 + 0x08 + 0x04 + BufferID + (StartPage >> 8) + (unsigned char)StartPage + (PageNum >> 8) + (unsigned char)PageNum;
	SendCheck(temp);
	return ensure;
}

//�ϲ�����������ģ�壩PS_RegModel
//����:��CharBuffer1��CharBuffer2�е������ļ��ϲ����� ģ��,�������CharBuffer1��CharBuffer2
//˵��:  ģ�鷵��ȷ����
unsigned char PS_RegModel(void)
{
	unsigned short temp;
	unsigned char sure; //,p=0;

	if (AS608_PackHead() == 1)
		return 0xFF;
	SendFlag(0x01);
	SendLength(0x03);
	Sendcmd(0x05); /*�ϲ�����ָ��*/
	temp = 0x01 + 0x03 + 0x05;
	SendCheck(temp);

	// sure = ReturnFlag(&p);
	sure = JudgeStr(1000, 0x03);

	return sure;
}

//����ģ�� PS_StoreChar
//����:�� CharBuffer1 �� CharBuffer2 �е�ģ���ļ��浽 PageID ��flash���ݿ�λ�á�
//����:  BufferID @ref charBuffer1:0x01	charBuffer1:0x02
//       PageID��ָ�ƿ�λ�úţ�
//˵��:  ģ�鷵��ȷ����
unsigned char PS_StoreChar(unsigned char BufferID, unsigned short PageID)
{
	unsigned short temp;
	unsigned char sure; //,p=0;

	if (AS608_PackHead() == 1)
		return 0xFF;
	SendFlag(0x01);
	SendLength(0x06);
	Sendcmd(0x06); /*�洢ģ��ָ��*/
	AS608_SendData(BufferID);
	AS608_SendData(PageID >> 8);
	AS608_SendData(PageID);
	temp = 0x01 + 0x06 + 0x06 + BufferID + (PageID >> 8) + (unsigned char)PageID;
	SendCheck(temp);

	// sure = ReturnFlag(&p);
	sure = JudgeStr(1000, 0x03);

	return sure;
}

//ɾ��ģ�� PS_DeletChar
//����:  ɾ��flash���ݿ���ָ��ID�ſ�ʼ��N��ָ��ģ��
//����:  PageID(ָ�ƿ�ģ���)��Nɾ����ģ�������
//˵��:  ģ�鷵��ȷ����
unsigned char PS_DeletChar(unsigned short PageID, unsigned short N)
{
	unsigned short temp;
	unsigned char sure; //,p=0;

	if (AS608_PackHead() == 1)
		return 0xFF;
	SendFlag(0x01); //�������ʶ
	SendLength(0x07);
	Sendcmd(0x0C); /*ɾ��ָ��ָ��ģ��ָ��*/
	AS608_SendData(PageID >> 8);
	AS608_SendData(PageID);
	AS608_SendData(N >> 8);
	AS608_SendData(N);
	temp = 0x01 + 0x07 + 0x0C + (PageID >> 8) + (unsigned char)PageID + (N >> 8) + (unsigned char)N;
	SendCheck(temp);

	//AS608_DELAY_MS(400);

	// sure = ReturnFlag(&p);
	sure = JudgeStr(1000, 0x03);

	return sure;
}

//��������PS_HighSpeedSearch
//���ܣ��� CharBuffer1��CharBuffer2�е������ļ��������������򲿷�ָ�ƿ⡣
//		  �����������򷵻�ҳ��,��ָ����ڵ�ȷ������ָ�ƿ��� ���ҵ�¼ʱ����
//		  �ܺõ�ָ�ƣ���ܿ�������������
//����:  BufferID�� StartPage(��ʼҳ)��PageNum��ҳ����
//˵��:  ģ�鷵��ȷ����+ҳ�루����ָ��ģ�壩
unsigned char PS_HighSpeedSearch(unsigned char BufferID, unsigned short StartPage, unsigned short PageNum, unsigned short *p)
{
	unsigned short temp;
	unsigned char ensure;
	//unsigned short rc;

	if (AS608_PackHead() == 1)
		return 0xFF;
	SendFlag(0x01);
	SendLength(0x08);
	Sendcmd(0x1b); /*��������ָ�ƿ�ָ��*/
	AS608_SendData(BufferID);
	AS608_SendData(StartPage >> 8);
	AS608_SendData(StartPage);
	AS608_SendData(PageNum >> 8);
	AS608_SendData(PageNum);
	temp = 0x01 + 0x08 + 0x1b + BufferID + (StartPage >> 8) + (unsigned char)StartPage + (PageNum >> 8) + (unsigned char)PageNum;
	SendCheck(temp);

	// ensure = ReturnFlag(&rc);
	ensure = JudgeStr(1000, 0x07);

	*p = (uart_rec_buff[10] << 8) + uart_rec_buff[11]; //ģ���

	return ensure;
}

//���ָ�ƿ� PS_Empty
//����:  ɾ��flash���ݿ�������ָ��ģ��
//����:  ��
//˵��:  ģ�鷵��ȷ����
unsigned char PS_Empty(void)
{
	unsigned short temp;
	unsigned char sure; //,p=0;

	if (AS608_PackHead() == 1)
		return 0xFF;
	SendFlag(0x01); //�������ʶ
	SendLength(0x03);
	Sendcmd(0x0D);
	temp = 0x01 + 0x03 + 0x0D;
	SendCheck(temp);

	// sure = ReturnFlag(&p);
	sure = JudgeStr(1000, 0x03);

	return sure;
}

#if 0
/**
  * @brief  ���STM32��ָ��ģ���ͨ������
  * @param  PS_Addrָ��ģ���ַ
  * @retval ����ֵ0ͨѶ�ɹ�;1��ʾͨѶ���ɹ�
  */
unsigned char PS_Connect(unsigned long *PS_Addr)
{
	PS_Addr = 0;
	if(AS608_PackHead()==1)
		return 0xFF;
	AS608_SendData(0X01);
	AS608_SendData(0X00);
	AS608_SendData(0X00);
	return 1;		
}

//дϵͳ�Ĵ��� PS_WriteReg
//����:  дģ��Ĵ���
//����:  �Ĵ������RegNum:4\5\6
//˵��:  ģ�鷵��ȷ����
unsigned char PS_WriteReg(unsigned char RegNum, unsigned char DATA)
{
	unsigned short temp;
	unsigned short sure,p=0;

	if(AS608_PackHead()==1)
		return 0xFF;
	SendFlag(0x01);//�������ʶ
	SendLength(0x05);
	Sendcmd(0x0E);
	AS608_SendData(RegNum);
	AS608_SendData(DATA);
	temp = RegNum+DATA+0x01+0x05+0x0E;
	SendCheck(temp);
	sure=ReturnFlag(&p);
	return sure;
}
/**
  * @brief  ��ϵͳ�������� PS_ReadSysPara
  * @param  ��
  * @return ģ�鷵��ȷ���� + ����������16bytes��
  * @note   ��ȡģ��Ļ��������������ʣ�����С��)
  * @see    none
  */
unsigned char PS_ReadSysPara(void)
{
	unsigned short temp;
	unsigned char  ensure;
	unsigned char  *send_data;
	unsigned short p=0;
	
	if(AS608_PackHead()==1)
		return 0xFF;
	SendFlag(0x01);//�������ʶ
	SendLength(0x03);
	Sendcmd(0x0F);
	temp = 0x01+0x03+0x0F;
	SendCheck(temp);
	ensure=ReturnFlag(&p);
	if(send_data)
	{

	}		
	else
		ensure=0xff;
	if(ensure==0x00)
	{

	}
	return ensure;
}
//����ģ���ַ PS_SetAddr
//����:  ����ģ���ַ
//����:  PS_addr
//˵��:  ģ�鷵��ȷ����
unsigned char PS_SetAddr(unsigned long PS_addr)
{
	unsigned short temp;
	unsigned char  ensure;

	if(AS608_PackHead()==1)
		return 0xFF;
	SendFlag(0x01);//�������ʶ
	SendLength(0x07);
	Sendcmd(0x15);
	AS608_SendData(PS_addr>>24);
	AS608_SendData(PS_addr>>16);
	AS608_SendData(PS_addr>>8);
	AS608_SendData(PS_addr);
	temp = 0x01+0x07+0x15
	+(unsigned char)(PS_addr>>24)+(unsigned char)(PS_addr>>16)
	+(unsigned char)(PS_addr>>8) +(unsigned char)PS_addr;				
	SendCheck(temp);

	return ensure;
}
//���ܣ� ģ���ڲ�Ϊ�û�������256bytes��FLASH�ռ����ڴ��û����±�,
//	�ü��±��߼��ϱ��ֳ� 16 ��ҳ��
//����:  NotePageNum(0~15),Byte32(Ҫд�����ݣ�32���ֽ�)
//˵��:  ģ�鷵��ȷ����
unsigned char PS_WriteNotepad(unsigned char NotePageNum,unsigned char *Byte32)
{
	unsigned short temp;
	unsigned char  ensure,i;
	
	*Byte32 = 0;
	
	if(AS608_PackHead()==1)
		return 0xFF;
	SendFlag(0x01); //�������ʶ
	SendLength(36);
	Sendcmd(0x18);
	AS608_SendData(NotePageNum);
	for(i=0;i<32;i++)
	{
		AS608_SendData(Byte32[i]);
		temp += Byte32[i];
	}
	temp =0x01+36+0x18+NotePageNum+temp;
	SendCheck(temp);

	return ensure;
}
//������PS_ReadNotepad
//���ܣ�  ��ȡFLASH�û�����128bytes����
//����:  NotePageNum(0~15)
//˵��:  ģ�鷵��ȷ����+�û���Ϣ
unsigned char PS_ReadNotepad(unsigned char NotePageNum,unsigned char *Byte32)
{
	unsigned short temp;
	unsigned char  ensure;
	
	*Byte32 = 0;
	
	if(AS608_PackHead()==1)
		return 0xFF;
	SendFlag(0x01);//�������ʶ
	SendLength(0x04);
	Sendcmd(0x19);
	AS608_SendData(NotePageNum);
	temp = 0x01+0x04+0x19+NotePageNum;
	SendCheck(temp);

	return ensure;
}
#endif

//����Чģ����� PS_ValidTempleteNum
//���ܣ�����Чģ�����
//����: ��
//˵��: ģ�鷵��ȷ����+��Чģ�����ValidN
unsigned char PS_ValidTempleteNum(unsigned short *ValidN)
{
	unsigned short temp;
	unsigned char ensure;
	unsigned short p = 0;

	if (AS608_PackHead() == 1)
		return 0xFF;
	SendFlag(0x01); //�������ʶ
	SendLength(0x03);
	Sendcmd(0x1d);
	temp = 0x01 + 0x03 + 0x1d;
	SendCheck(temp);

	// ensure = ReturnFlag(&p);
	ensure = JudgeStr(1000, 0x05);

	*ValidN = (uart_rec_buff[10] << 8) + uart_rec_buff[11];

	return ensure;
}

//�Զ�ע��ģ�� PS_AutoEnRoll
//���ܣ��ɼ�һ��ָ��ע��ģ�壬��ָ�ƿ���������λ���洢�����ش洢ID
//����: ��
//˵��: ģ�鷵��ȷ����+ҳ�루����ָ��ģ�壩
unsigned char PS_AutoEnRoll(unsigned short id, unsigned char num, unsigned short param)
{
	unsigned short sum;

	if (AS608_PackHead() == 1)
		return 0xFF;
	SendFlag(0x01); //�������ʶ
	SendLength(0x08);
	Sendcmd(0x31);
	AS608_SendData(id >> 8);
	AS608_SendData(id & 0xFF);
	AS608_SendData(num);
	AS608_SendData(param >> 8);
	AS608_SendData(param & 0xFF);
	sum = 0x01 + 0x08 + 0x31 + (id >> 8) + (id & 0xFF) + num + (param >> 8) + (param & 0xFF);
	SendCheck(sum);

	return 0;
}

//�Զ���ָ֤�� PS_AutoIdentify
//���ܣ�
//1.�Զ��ɼ�ָ�ƣ���ָ�ƿ�������Ŀ��ģ�岢�������������
//2.���Ŀ��ģ��ͬ��ǰ�ɼ���ָ�ƱȶԵ÷ִ�����߷�ֵ������Ŀ��ģ��Ϊ�������������Բɼ�����������Ŀ��ģ��Ŀհ�����
//����: ��
//˵��: ģ�鷵��ȷ����+ҳ�루����ָ��ģ�壩
unsigned char PS_AutoIdentify(unsigned short id, unsigned char level, unsigned short param)
{
	unsigned short sum;

	if (AS608_PackHead() == 1)
		return 0xFF;
	SendFlag(0x01); //�������ʶ
	SendLength(0x08);
	Sendcmd(0x32);
	AS608_SendData(level);
	AS608_SendData(id >> 8);
	AS608_SendData(id & 0xFF);
	AS608_SendData(param >> 8);
	AS608_SendData(param & 0xFF);
	sum = 0x01 + 0x08 + 0x32 + (id >> 8) + (id & 0xFF) + level + (param >> 8) + (param & 0xFF);
	SendCheck(sum);

	return 0;
}

//��AS608���� PS_HandShake
//����: PS_Addr��ַָ��
//˵��: ģ�鷵�µ�ַ����ȷ��ַ�� ����ȷ����
unsigned char PS_HandShake(unsigned long *PS_Addr)
{
	unsigned char ensure;
	*PS_Addr = 0;

	if (AS608_PackHead() == 1)
		return 0xFF;
	SendFlag(0x01);
	SendLength(0x03);
	Sendcmd(0x53);
	SendCheck(0x57);
	
	ensure = JudgeStr(1000, 0x03);
	return ensure;
}

unsigned char PS_Reset(void)
{
	return 0;
}

unsigned char PS_Sleep(void)
{
	unsigned short temp;
	unsigned char ensure;

	if (AS608_PackHead() == 1)
		return 0xFF;
	SendFlag(0x01); //�������ʶ
	SendLength(0x03);
	Sendcmd(0x60);
	temp = 0x01 + 0x03 + 0x60;
	SendCheck(temp);
	return ensure;
}

//void AS608_log(void)
//{
//	unsigned char i =0;
////	NRF_LOG_PRINTF_DEBUG("receive :");
//	for(i=0;i<25;i++)
//	{
//		NRF_LOG_PRINTF_DEBUG("%2x ",as608_rec_buff[i]);
//	}
//	NRF_LOG_PRINTF_DEBUG("\n");
//}

void FP_Light(FP_COLOR_E light_id)
{
	//	if(fp_flag == FP_LT5X)
	//	{
	//#ifdef __FP_LT5X_LIGHT_SUPPORT__
	unsigned short temp;

	unsigned char sure = 0; //,p=0;
	if (light_id == Light_Color)
		return;

	if (AS608_PackHead() == 1)
		return;
	SendFlag(0x01);
	SendLength(0x07);
	Sendcmd(0x41);
	switch (light_id)
	{
	case FP_BLUE:
		AS608_SendData(0x01);
		AS608_SendData(0x01);
		AS608_SendData(0x00);
		AS608_SendData(0x50);
		temp = 0x01 + 0x07 + 0x41 + 0x02 + 0x50;
		break;
	case FP_GREEN:
		AS608_SendData(0x01);
		AS608_SendData(0x02);
		AS608_SendData(0x02);
		AS608_SendData(0);
		temp = 0x01 + 0x07 + 0x41 + 0x05 + 0;
		break;
	case FP_RED:
		AS608_SendData(0x01);
		AS608_SendData(0x04);
		AS608_SendData(0x04);
		AS608_SendData(0);
		temp = 0x01 + 0x07 + 0x41 + 0x09 + 0;
		break;
	case FP_NONE_COLOR:
		AS608_SendData(0x04);
		AS608_SendData(0x00);
		AS608_SendData(0x00);
		AS608_SendData(0xC8);
		temp = 0x01 + 0x07 + 0x41 + 0x04 + 0xC8;
		break;
	}
	SendCheck(temp);

	//sure=ReturnFlag(&p);
	sure = JudgeStr(1000, 0x03);
	//#endif
	Light_Color = light_id;

	//	}
}

FP_COLOR_E FP_Get_Light(void)
{
	return Light_Color;
}

//#endif//__PREIPHERAL_FP_LT5X_SUPPORT__
