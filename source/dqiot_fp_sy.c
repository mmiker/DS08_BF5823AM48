
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
<<<<<<< HEAD
  * @brief  AS608_USART������ָ��ģ�鴫������ 
  * @param  data;���������
=======
  * @brief  AS608_USART串口向指纹模块传递数�? 
  * @param  data;传输的数�?
>>>>>>> six commit
  */
void AS608_SendData(unsigned char send_data)
{
	uart_tx_byte(UART0, send_data);
}

/**
<<<<<<< HEAD
  * @brief  AS608_USART������ָ��ģ�������ͷ��ʽ 
  * @param  ��
=======
  * @brief  AS608_USART串口向指纹模块命令包头格�? 
  * @param  �?
>>>>>>> six commit
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

<<<<<<< HEAD
	/*��ͷ SendHead*/
	AS608_SendData(0xEF);
	AS608_SendData(0x01);

	/*ָ��ģ���ַ SendAddr*/
=======
	/*包头*/
	AS608_SendData(0xEF);
	AS608_SendData(0x01);

	/*指纹模块地址*/
>>>>>>> six commit
	AS608_SendData(AS608_Addr >> 24);
	AS608_SendData(AS608_Addr >> 16);
	AS608_SendData(AS608_Addr >> 8);
	AS608_SendData(AS608_Addr);

	return 0;
}

unsigned char AS608_PackHead2(void)
{

<<<<<<< HEAD
	/*��ͷ SendHead*/
	AS608_SendData(0xEF);
	AS608_SendData(0x01);

	/*ָ��ģ���ַ*/
=======
	/*包头*/
	AS608_SendData(0xEF);
	AS608_SendData(0x01);

	/*指纹模块地址*/
>>>>>>> six commit
	AS608_SendData(AS608_Addr >> 24);
	AS608_SendData(AS608_Addr >> 16);
	AS608_SendData(AS608_Addr >> 8);
	AS608_SendData(AS608_Addr);

	return 0;
}

/**
<<<<<<< HEAD
  * @brief  ���Ͱ���ʶ
  * @param  flag:�����־
  * @retval ��
=======
  * @brief  发送包标识
  * @param  flag:包标识位
  * @retval �?
>>>>>>> six commit
  */
void SendFlag(unsigned char flag)
{
	AS608_SendData(flag);
}

/**
<<<<<<< HEAD
  * @brief  ���Ͱ�����
  * @param  length:������
  * @retval ��
=======
  * @brief  发送包长度
  * @param  length:包长�?
  * @retval �?
>>>>>>> six commit
  */
void SendLength(unsigned short length)
{
	AS608_SendData(length >> 8);
	AS608_SendData(length);
}

/**
<<<<<<< HEAD
  * @brief  ����ָ����
  * @param  cmd;ָ����
  * @retval ��
=======
  * @brief  发送指令码
  * @param  cmd;指令�?
  * @retval �?
>>>>>>> six commit
  */
void Sendcmd(unsigned char cmd)
{
	AS608_SendData(cmd);
}

/**
<<<<<<< HEAD
  * @brief  ����У���
  * @param  check:���λ
  * @retval ��
=======
  * @brief  发送校验和
  * @param  check:检查位
  * @retval �?
>>>>>>> six commit
  */
void SendCheck(unsigned short check)
{
	AS608_SendData(check >> 8);
	AS608_SendData(check);
}

/**
<<<<<<< HEAD
  * @brief  �ж��жϽ��յ�������û��Ӧ���
  * @param  
  * waittimeΪ�ȴ��жϽ������ݵ�ʱ��(��λ1ms)
  * lengthΪ������
  * @return ���ݰ�ȷ����
=======
  * @brief  判断�?�?接收的数组有没有应答�?
  * @param  
  * waittime为等待中�?接收数据的时�?(单位1ms)
  * length为包长度
  * @return 数据包确认码
>>>>>>> six commit
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

<<<<<<< HEAD
		/* ���յ�һ������ */
		if (uart_getbuflen >= 9 + length)
		{
			/* Ѱ��0xEFλ�� */
=======
		/* 接收到一次数�? */
		if (uart_getbuflen >= 9 + length)
		{
			/* 寻找0xEF位置 */
>>>>>>> six commit
			for (i = 0; i < uart_getbuflen; i++)
			{
				if (uart_get_buf[i] == 0xEF)
					break;
			}

<<<<<<< HEAD
			/* �ж��Ƿ�ΪӦ��� */
=======
			/* 判断�?否为应答�? */
>>>>>>> six commit
			if (uart_get_buf[i] == 0xEF && uart_get_buf[i + 1] == 0x01 && uart_get_buf[i + 6] == 0x07 && ((uart_get_buf[i + 7] << 8) + uart_get_buf[i + 8]) == length)
			{
				for (i; i < uart_getbuflen; i++)
				{
					uart_rec_buff[j] = uart_get_buf[i];
					j++;
				}
<<<<<<< HEAD
				getdata = uart_rec_buff[9]; //ȷ����

				/* ��ջ��� */
=======
				getdata = uart_rec_buff[9]; //�?认码

				/* 清空缓存 */
>>>>>>> six commit
				uart_getbuflen = 0;

				return getdata;
			}
		}
	}

	return 1;
}

#if 0
/**
<<<<<<< HEAD
  * @brief  �ӻ���������ȷ����
  * @param  *i:����ֵ��ȷ���룩
  * @retval ��
=======
  * @brief  从缓冲区读出�?认码
  * @param  *i:返回值（�?认码�?
  * @retval �?
>>>>>>> six commit
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
<<<<<<< HEAD
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

=======
	AS608_PackHead2();
	SendFlag(0x01);
	SendLength(0x03);
	Sendcmd(0x53); /*生成特征指令*/
	SendCheck(0x57);

	//sure=ReturnFlag(&p);
	return JudgeStr(1000, 0x03);
}

//录入图像 PS_GetImage
//功能:探测手指，探测到后录入指纹图像存于ImageBuffer�?
//模块返回�?认字
unsigned char PS_GetImage(void)
{
	uart_getbuflen = 0;
	//delay_ms(300);
	if (AS608_PackHead() == 1)
		return 0xFF;
	SendFlag(0x01); /*命令包标�?*/
	SendLength(0x03);
	Sendcmd(0x01); /*录指纹指�?*/
	SendCheck(0x01 + 0x03 + 0x01);

	//nrf_delay_ms(50);        /*等待指纹识别模块处理数据*/

	// sure = ReturnFlag(&p);
	return JudgeStr(1000, 0x03);
}

//生成特征 PS_GenChar
//功能:将ImageBuffer�?的原始图像生成指纹特征文件存于CharBuffer1或CharBuffer2
//参数:BufferID --> charBuffer1:0x01	charBuffer1:0x02
//模块返回�?认字
unsigned char PS_GenChar(unsigned char BufferID)
{
>>>>>>> six commit
	if (AS608_PackHead() == 1)
		return 0xFF;
	SendFlag(0x01);
	SendLength(0x04);
<<<<<<< HEAD
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

=======
	Sendcmd(0x02); /*生成特征指令*/
	AS608_SendData(BufferID);
	SendCheck(0x01 + 0x04 + 0x02 + BufferID);
	return JudgeStr(1000, 0x03);
}

//精确比�?�两枚指纹特�? PS_Match
//功能:精确比�?�CharBuffer1 与CharBuffer2 �?的特征文�?
//模块返回�?认字
unsigned char PS_Match(void)
{
>>>>>>> six commit
	if (AS608_PackHead() == 1)
		return 0xFF;
	SendFlag(0x01);
	SendLength(0x03);
<<<<<<< HEAD
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
=======
	Sendcmd(0x03); /*精确比�?�指�?*/
	SendCheck(0x01 + 0x03 + 0x03);

	// sure = ReturnFlag(&p);
	return JudgeStr(1000, 0x05);
}
//搜索指纹 PS_Search
//功能:�?CharBuffer1或CharBuffer2�?的特征文件搜索整�?或部分指纹库.若搜索到，则返回页码�?
//参数:  BufferID @ref CharBuffer1	CharBuffer2
//说明:  模块返回�?认字，页码（相配指纹模板�?
unsigned char PS_Search(unsigned char BufferID, unsigned short StartPage, unsigned short PageNum, unsigned short *p)
{

	unsigned char sure;
	if (AS608_PackHead() == 1)
		return 0xFF;
	SendFlag(0x01); //命令包标�?
>>>>>>> six commit
	SendLength(0x08);
	Sendcmd(0x04);
	AS608_SendData(BufferID);
	AS608_SendData(StartPage >> 8);
	AS608_SendData(StartPage);
	AS608_SendData(PageNum >> 8);
	AS608_SendData(PageNum);
<<<<<<< HEAD
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

=======
	SendCheck(0x01 + 0x08 + 0x04 + BufferID + (StartPage >> 8) + (unsigned char)StartPage + (PageNum >> 8) + (unsigned char)PageNum);
	*p = (uart_rec_buff[10] << 8) + uart_rec_buff[11];
	return sure;
}

//合并特征（生成模板）PS_RegModel
//功能:将CharBuffer1与CharBuffer2�?的特征文件合并生�? 模板,结果存于CharBuffer1与CharBuffer2
//说明:  模块返回�?认字
unsigned char PS_RegModel(void)
{
>>>>>>> six commit
	if (AS608_PackHead() == 1)
		return 0xFF;
	SendFlag(0x01);
	SendLength(0x03);
<<<<<<< HEAD
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
=======
	Sendcmd(0x05); /*合并特征指令*/
	SendCheck(0x01 + 0x03 + 0x05);

	// sure = ReturnFlag(&p);
	return JudgeStr(1000, 0x03);
}

//储存模板 PS_StoreChar
//功能:�? CharBuffer1 �? CharBuffer2 �?的模板文件存�? PageID 号flash数据库位�?�?
//参数:  BufferID @ref charBuffer1:0x01	charBuffer1:0x02
//       PageID（指纹库位置号）
//说明:  模块返回�?认字
unsigned char PS_StoreChar(unsigned char BufferID, unsigned short PageID)
{
	unsigned short;
>>>>>>> six commit

	if (AS608_PackHead() == 1)
		return 0xFF;
	SendFlag(0x01);
	SendLength(0x06);
<<<<<<< HEAD
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
=======
	Sendcmd(0x06); /*存储模板指令*/
	AS608_SendData(BufferID);
	AS608_SendData(PageID >> 8);
	AS608_SendData(PageID);
	SendCheck(0x01 + 0x06 + 0x06 + BufferID + (PageID >> 8) + (unsigned char)PageID);

	// sure = ReturnFlag(&p);
	return JudgeStr(1000, 0x03);
}

//删除模板 PS_DeletChar
//功能:  删除flash数据库中指定ID号开始的N�?指纹模板
//参数:  PageID(指纹库模板号)，N删除的模板个数�?
//说明:  模块返回�?认字
unsigned char PS_DeletChar(unsigned short PageID, unsigned short N)
{
>>>>>>> six commit
	unsigned char sure; //,p=0;

	if (AS608_PackHead() == 1)
		return 0xFF;
<<<<<<< HEAD
	SendFlag(0x01); //�������ʶ
	SendLength(0x07);
	Sendcmd(0x0C); /*ɾ��ָ��ָ��ģ��ָ��*/
=======
	SendFlag(0x01); //命令包标�?
	SendLength(0x07);
	Sendcmd(0x0C); /*删除指定指纹模板指令*/
>>>>>>> six commit
	AS608_SendData(PageID >> 8);
	AS608_SendData(PageID);
	AS608_SendData(N >> 8);
	AS608_SendData(N);
<<<<<<< HEAD
	temp = 0x01 + 0x07 + 0x0C + (PageID >> 8) + (unsigned char)PageID + (N >> 8) + (unsigned char)N;
	SendCheck(temp);
=======
	SendCheck(0x01 + 0x07 + 0x0C + (PageID >> 8) + (unsigned char)PageID + (N >> 8) + (unsigned char)N);
>>>>>>> six commit

	//AS608_DELAY_MS(400);

	// sure = ReturnFlag(&p);
<<<<<<< HEAD
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
=======
	return JudgeStr(1000, 0x03);
}

//高速搜�?PS_HighSpeedSearch
//功能：以 CharBuffer1或CharBuffer2�?的特征文件高速搜索整�?或部分指纹库�?
//		  若搜索到，则返回页码,该指令�?�于的确存在于指纹库�? ，且登录时质�?
//		  很好的指纹，会很�?给出搜索结果�?
//参数:  BufferID�? StartPage(起�?�页)，PageNum（页数）
//说明:  模块返回�?认字+页码（相配指纹模板）
unsigned char PS_HighSpeedSearch(unsigned char BufferID, unsigned short StartPage, unsigned short PageNum, unsigned short *p)
{
	unsigned char ensure;
>>>>>>> six commit

	if (AS608_PackHead() == 1)
		return 0xFF;
	SendFlag(0x01);
	SendLength(0x08);
<<<<<<< HEAD
	Sendcmd(0x1b); /*��������ָ�ƿ�ָ��*/
=======
	Sendcmd(0x1b); /*高速搜索指纹库指令*/
>>>>>>> six commit
	AS608_SendData(BufferID);
	AS608_SendData(StartPage >> 8);
	AS608_SendData(StartPage);
	AS608_SendData(PageNum >> 8);
	AS608_SendData(PageNum);
<<<<<<< HEAD
	temp = 0x01 + 0x08 + 0x1b + BufferID + (StartPage >> 8) + (unsigned char)StartPage + (PageNum >> 8) + (unsigned char)PageNum;
	SendCheck(temp);
=======
	SendCheck(0x01 + 0x08 + 0x1b + BufferID + (StartPage >> 8) + (unsigned char)StartPage + (PageNum >> 8) + (unsigned char)PageNum);
>>>>>>> six commit

	// ensure = ReturnFlag(&rc);
	ensure = JudgeStr(1000, 0x07);

<<<<<<< HEAD
	*p = (uart_rec_buff[10] << 8) + uart_rec_buff[11]; //ģ���
=======
	*p = (uart_rec_buff[10] << 8) + uart_rec_buff[11];
>>>>>>> six commit

	return ensure;
}

<<<<<<< HEAD
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
=======
//清空指纹�? PS_Empty
//功能:  删除flash数据库中所有指纹模�?
//参数:  �?
//说明:  模块返回�?认字
unsigned char PS_Empty(void)
{
	if (AS608_PackHead() == 1)
		return 0xFF;
	SendFlag(0x01); //命令包标�?
	SendLength(0x03);
	Sendcmd(0x0D);
	SendCheck(0x01 + 0x03 + 0x0D);

	// sure = ReturnFlag(&p);
	return JudgeStr(1000, 0x03);
>>>>>>> six commit
}

#if 0
/**
<<<<<<< HEAD
  * @brief  ���STM32��ָ��ģ���ͨ������
  * @param  PS_Addrָ��ģ���ַ
  * @retval ����ֵ0ͨѶ�ɹ�;1��ʾͨѶ���ɹ�
=======
  * @brief  检�?STM32与指纹模块的通信连接
  * @param  PS_Addr指纹模块地址
  * @retval 返回�?0通�??成功;1表示通�??不成�?
>>>>>>> six commit
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

<<<<<<< HEAD
//дϵͳ�Ĵ��� PS_WriteReg
//����:  дģ��Ĵ���
//����:  �Ĵ������RegNum:4\5\6
//˵��:  ģ�鷵��ȷ����
=======
//写系统寄存器 PS_WriteReg
//功能:  写模块寄存器
//参数:  寄存器序号RegNum:4\5\6
//说明:  模块返回�?认字
>>>>>>> six commit
unsigned char PS_WriteReg(unsigned char RegNum, unsigned char DATA)
{
	unsigned short temp;
	unsigned short sure,p=0;

	if(AS608_PackHead()==1)
		return 0xFF;
<<<<<<< HEAD
	SendFlag(0x01);//�������ʶ
=======
	SendFlag(0x01);//鍛戒护鍖�?爣璇
>>>>>>> six commit
	SendLength(0x05);
	Sendcmd(0x0E);
	AS608_SendData(RegNum);
	AS608_SendData(DATA);
	temp = RegNum+DATA+0x01+0x05+0x0E;
	SendCheck(temp);
	sure=ReturnFlag(&p);
	return sure;
}
<<<<<<< HEAD
/**
  * @brief  ��ϵͳ�������� PS_ReadSysPara
  * @param  ��
  * @return ģ�鷵��ȷ���� + ����������16bytes��
  * @note   ��ȡģ��Ļ��������������ʣ�����С��)
  * @see    none
  */
=======
//读系统基�?参数 PS_ReadSysPara
//功能:  读取模块的基�?参数（波特率，包大小�?)
//参数:  �?
//说明:  模块返回�?认字 + 基本参数�?16bytes�?
>>>>>>> six commit
unsigned char PS_ReadSysPara(void)
{
	unsigned short temp;
	unsigned char  ensure;
	unsigned char  *send_data;
	unsigned short p=0;
	
	if(AS608_PackHead()==1)
		return 0xFF;
<<<<<<< HEAD
	SendFlag(0x01);//�������ʶ
=======
	SendFlag(0x01);//鍛戒护鍖�?爣璇
>>>>>>> six commit
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
<<<<<<< HEAD
//����ģ���ַ PS_SetAddr
//����:  ����ģ���ַ
//����:  PS_addr
//˵��:  ģ�鷵��ȷ����
=======
//设置模块地址 PS_SetAddr
//功能:  设置模块地址
//参数:  PS_addr
//说明:  模块返回�?认字
>>>>>>> six commit
unsigned char PS_SetAddr(unsigned long PS_addr)
{
	unsigned short temp;
	unsigned char  ensure;

	if(AS608_PackHead()==1)
		return 0xFF;
<<<<<<< HEAD
	SendFlag(0x01);//�������ʶ
=======
	SendFlag(0x01);//命令包标�?
>>>>>>> six commit
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
<<<<<<< HEAD
//���ܣ� ģ���ڲ�Ϊ�û�������256bytes��FLASH�ռ����ڴ��û����±�,
//	�ü��±��߼��ϱ��ֳ� 16 ��ҳ��
//����:  NotePageNum(0~15),Byte32(Ҫд�����ݣ�32���ֽ�)
//˵��:  ģ�鷵��ȷ����
=======
//功能�? 模块内部为用户开辟了256bytes的FLASH空间用于存用户�?�事�?,
//	该�?�事�?逻辑上�??分成 16 �?页�?
//参数:  NotePageNum(0~15),Byte32(要写入内容，32�?字节)
//说明:  模块返回�?认字
>>>>>>> six commit
unsigned char PS_WriteNotepad(unsigned char NotePageNum,unsigned char *Byte32)
{
	unsigned short temp;
	unsigned char  ensure,i;
	
	*Byte32 = 0;
	
	if(AS608_PackHead()==1)
		return 0xFF;
<<<<<<< HEAD
	SendFlag(0x01); //�������ʶ
=======
	SendFlag(0x01); //命令包标�?
>>>>>>> six commit
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
<<<<<<< HEAD
//������PS_ReadNotepad
//���ܣ�  ��ȡFLASH�û�����128bytes����
//����:  NotePageNum(0~15)
//˵��:  ģ�鷵��ȷ����+�û���Ϣ
=======
//读�?�事PS_ReadNotepad
//功能�?  读取FLASH用户区的128bytes数据
//参数:  NotePageNum(0~15)
//说明:  模块返回�?认字+用户信息
>>>>>>> six commit
unsigned char PS_ReadNotepad(unsigned char NotePageNum,unsigned char *Byte32)
{
	unsigned short temp;
	unsigned char  ensure;
	
	*Byte32 = 0;
	
	if(AS608_PackHead()==1)
		return 0xFF;
<<<<<<< HEAD
	SendFlag(0x01);//�������ʶ
=======
	SendFlag(0x01);//命令包标�?
>>>>>>> six commit
	SendLength(0x04);
	Sendcmd(0x19);
	AS608_SendData(NotePageNum);
	temp = 0x01+0x04+0x19+NotePageNum;
	SendCheck(temp);

	return ensure;
}
#endif

<<<<<<< HEAD
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
=======
//读有效模板个�? PS_ValidTempleteNum
//功能：�?�有效模板个�?
//参数: �?
//说明: 模块返回�?认字+有效模板�?数ValidN
unsigned char PS_ValidTempleteNum(unsigned short *ValidN)
{
	unsigned char ensure;

	if (AS608_PackHead() == 1)
		return 0xFF;
	SendFlag(0x01); //命令包标�?
	SendLength(0x03);
	Sendcmd(0x1d);
	SendCheck(0x01 + 0x03 + 0x1d);
>>>>>>> six commit

	// ensure = ReturnFlag(&p);
	ensure = JudgeStr(1000, 0x05);

	*ValidN = (uart_rec_buff[10] << 8) + uart_rec_buff[11];

	return ensure;
}

<<<<<<< HEAD
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
=======
unsigned char PS_AutoEnRoll(unsigned short id, unsigned char num, unsigned short param)
{
	if (AS608_PackHead() == 1)
		return 0xFF;
	SendFlag(0x01); //命令包标�?
>>>>>>> six commit
	SendLength(0x08);
	Sendcmd(0x31);
	AS608_SendData(id >> 8);
	AS608_SendData(id & 0xFF);
	AS608_SendData(num);
	AS608_SendData(param >> 8);
	AS608_SendData(param & 0xFF);
<<<<<<< HEAD
	sum = 0x01 + 0x08 + 0x31 + (id >> 8) + (id & 0xFF) + num + (param >> 8) + (param & 0xFF);
	SendCheck(sum);
=======
	SendCheck(0x01 + 0x08 + 0x31 + (id >> 8) + (id & 0xFF) + num + (param >> 8) + (param & 0xFF));
>>>>>>> six commit

	return 0;
}

<<<<<<< HEAD
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
=======
//�?动验证指�? PS_AutoIdentify
//功能�?
//1.�?动采集指纹，在指纹库�?搜索�?标模板并返回搜索结果�?
//2.如果�?标模板同当前采集的指纹比对得分大于最高阀值，并且�?标模板为不完整特征则以采集的特征更新�?标模板的空白区域�?
//参数: �?
//说明: 模块返回�?认字+页码（相配指纹模板）
unsigned char PS_AutoIdentify(unsigned short id, unsigned char level, unsigned short param)
{
	if (AS608_PackHead() == 1)
		return 0xFF;
	SendFlag(0x01); //命令包标�?
>>>>>>> six commit
	SendLength(0x08);
	Sendcmd(0x32);
	AS608_SendData(level);
	AS608_SendData(id >> 8);
	AS608_SendData(id & 0xFF);
	AS608_SendData(param >> 8);
	AS608_SendData(param & 0xFF);
<<<<<<< HEAD
	sum = 0x01 + 0x08 + 0x32 + (id >> 8) + (id & 0xFF) + level + (param >> 8) + (param & 0xFF);
	SendCheck(sum);
=======
	SendCheck(0x01 + 0x08 + 0x32 + (id >> 8) + (id & 0xFF) + level + (param >> 8) + (param & 0xFF));
>>>>>>> six commit

	return 0;
}

<<<<<<< HEAD
//��AS608���� PS_HandShake
//����: PS_Addr��ַָ��
//˵��: ģ�鷵�µ�ַ����ȷ��ַ�� ����ȷ����
unsigned char PS_HandShake(unsigned long *PS_Addr)
{
	unsigned char ensure;
=======
//与AS608握手 PS_HandShake
//参数: PS_Addr地址指针
//说明: 模块返新地址（�?�确地址�?
unsigned char PS_HandShake(unsigned long *PS_Addr)
{
>>>>>>> six commit
	*PS_Addr = 0;

	if (AS608_PackHead() == 1)
		return 0xFF;
	SendFlag(0x01);
	SendLength(0x03);
	Sendcmd(0x53);
	SendCheck(0x57);
<<<<<<< HEAD
	
	ensure = JudgeStr(1000, 0x03);
	return ensure;
=======

	return JudgeStr(1000, 0x03);
>>>>>>> six commit
}

unsigned char PS_Reset(void)
{
	return 0;
}

unsigned char PS_Sleep(void)
{
<<<<<<< HEAD
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
=======
	if (AS608_PackHead() == 1)
		return 0xFF;
	SendFlag(0x01); //命令包标�?
	SendLength(0x03);
	Sendcmd(0x60);
	SendCheck(0x01 + 0x03 + 0x60);
	return 0;
>>>>>>> six commit
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
<<<<<<< HEAD
	//#endif
	Light_Color = light_id;

=======

	// if (sure == 0)
	Light_Color = light_id;

	//#endif

>>>>>>> six commit
	//	}
}

FP_COLOR_E FP_Get_Light(void)
{
	return Light_Color;
}

<<<<<<< HEAD
=======
FP_COLOR_E FP_Set_Light(FP_COLOR_E light_id)
{
	Light_Color = light_id;
	return Light_Color;
}

unsigned char FP_Get_Start_Flag(void)
{
	if (uart_getbuflen > 0)
	{
		unsigned char i;

		for (i = 0; i < uart_getbuflen; i++)
		{
			if (uart_get_buf[i] == 0x55)
			{
				uart_getbuflen = 0;
				return 1;
			}
		}
	}
	return 0;
}

>>>>>>> six commit
//#endif//__PREIPHERAL_FP_LT5X_SUPPORT__
