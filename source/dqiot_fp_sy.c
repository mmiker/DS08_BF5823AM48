
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
  * @brief  AS608_USART串口向指纹模块传递数据 
  * @param  data;传输的数据
=======
  * @brief  AS608_USART涓插彛鍚戞寚绾规ā鍧椾紶閫掓暟鎹? 
  * @param  data;浼犺緭鐨勬暟鎹?
>>>>>>> six commit
  */
void AS608_SendData(unsigned char send_data)
{
	uart_tx_byte(UART0, send_data);
}

/**
<<<<<<< HEAD
  * @brief  AS608_USART串口向指纹模块命令包头格式 
  * @param  无
=======
  * @brief  AS608_USART涓插彛鍚戞寚绾规ā鍧楀懡浠ゅ寘澶存牸寮? 
  * @param  鏃?
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
	/*包头 SendHead*/
	AS608_SendData(0xEF);
	AS608_SendData(0x01);

	/*指纹模块地址 SendAddr*/
=======
	/*鍖呭ご*/
	AS608_SendData(0xEF);
	AS608_SendData(0x01);

	/*鎸囩汗妯″潡鍦板潃*/
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
	/*包头 SendHead*/
	AS608_SendData(0xEF);
	AS608_SendData(0x01);

	/*指纹模块地址*/
=======
	/*鍖呭ご*/
	AS608_SendData(0xEF);
	AS608_SendData(0x01);

	/*鎸囩汗妯″潡鍦板潃*/
>>>>>>> six commit
	AS608_SendData(AS608_Addr >> 24);
	AS608_SendData(AS608_Addr >> 16);
	AS608_SendData(AS608_Addr >> 8);
	AS608_SendData(AS608_Addr);

	return 0;
}

/**
<<<<<<< HEAD
  * @brief  发送包标识
  * @param  flag:包标标志
  * @retval 无
=======
  * @brief  鍙戦�佸寘鏍囪瘑
  * @param  flag:鍖呮爣璇嗕綅
  * @retval 鏃?
>>>>>>> six commit
  */
void SendFlag(unsigned char flag)
{
	AS608_SendData(flag);
}

/**
<<<<<<< HEAD
  * @brief  发送包长度
  * @param  length:包长度
  * @retval 无
=======
  * @brief  鍙戦�佸寘闀垮害
  * @param  length:鍖呴暱搴?
  * @retval 鏃?
>>>>>>> six commit
  */
void SendLength(unsigned short length)
{
	AS608_SendData(length >> 8);
	AS608_SendData(length);
}

/**
<<<<<<< HEAD
  * @brief  发送指令码
  * @param  cmd;指令码
  * @retval 无
=======
  * @brief  鍙戦�佹寚浠ょ爜
  * @param  cmd;鎸囦护鐮?
  * @retval 鏃?
>>>>>>> six commit
  */
void Sendcmd(unsigned char cmd)
{
	AS608_SendData(cmd);
}

/**
<<<<<<< HEAD
  * @brief  发送校验和
  * @param  check:检查位
  * @retval 无
=======
  * @brief  鍙戦�佹牎楠屽拰
  * @param  check:妫�鏌ヤ綅
  * @retval 鏃?
>>>>>>> six commit
  */
void SendCheck(unsigned short check)
{
	AS608_SendData(check >> 8);
	AS608_SendData(check);
}

/**
<<<<<<< HEAD
  * @brief  判断中断接收的数组有没有应答包
  * @param  
  * waittime为等待中断接收数据的时间(单位1ms)
  * length为包长度
  * @return 数据包确认码
=======
  * @brief  鍒ゆ柇涓?鏂?鎺ユ敹鐨勬暟缁勬湁娌℃湁搴旂瓟鍖?
  * @param  
  * waittime涓虹瓑寰呬腑鏂?鎺ユ敹鏁版嵁鐨勬椂闂?(鍗曚綅1ms)
  * length涓哄寘闀垮害
  * @return 鏁版嵁鍖呯‘璁ょ爜
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
		/* 接收到一次数据 */
		if (uart_getbuflen >= 9 + length)
		{
			/* 寻找0xEF位置 */
=======
		/* 鎺ユ敹鍒颁竴娆℃暟鎹? */
		if (uart_getbuflen >= 9 + length)
		{
			/* 瀵绘壘0xEF浣嶇疆 */
>>>>>>> six commit
			for (i = 0; i < uart_getbuflen; i++)
			{
				if (uart_get_buf[i] == 0xEF)
					break;
			}

<<<<<<< HEAD
			/* 判断是否为应答包 */
=======
			/* 鍒ゆ柇鏄?鍚︿负搴旂瓟鍖? */
>>>>>>> six commit
			if (uart_get_buf[i] == 0xEF && uart_get_buf[i + 1] == 0x01 && uart_get_buf[i + 6] == 0x07 && ((uart_get_buf[i + 7] << 8) + uart_get_buf[i + 8]) == length)
			{
				for (i; i < uart_getbuflen; i++)
				{
					uart_rec_buff[j] = uart_get_buf[i];
					j++;
				}
<<<<<<< HEAD
				getdata = uart_rec_buff[9]; //确认码

				/* 清空缓存 */
=======
				getdata = uart_rec_buff[9]; //纭?璁ょ爜

				/* 娓呯┖缂撳瓨 */
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
  * @brief  从缓冲区读出确认码
  * @param  *i:返回值（确认码）
  * @retval 无
=======
  * @brief  浠庣紦鍐插尯璇诲嚭纭?璁ょ爜
  * @param  *i:杩斿洖鍊硷紙纭?璁ょ爜锛?
  * @retval 鏃?
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
	Sendcmd(0x53); /*生成特征指令*/
	SendCheck(0x57);

	//sure=ReturnFlag(&p);
	sure = JudgeStr(1000, 0x03);

	return sure;
}

//录入图像 PS_GetImage
//功能:探测手指，探测到后录入指纹图像存于ImageBuffer。
//模块返回确认字
unsigned char PS_GetImage(void)
{
	unsigned short temp;
	unsigned char sure; //,p=0;
	/* 清空缓存 */
	uart_getbuflen = 0;

	//delay_ms(300);
	if (AS608_PackHead() == 1)
		return 0xFF;
	SendFlag(0x01); /*命令包标识*/
	SendLength(0x03);
	Sendcmd(0x01); /*录指纹指令*/
	temp = 0x01 + 0x03 + 0x01;
	SendCheck(temp);

	// nrf_delay_ms(50); /*等待指纹识别模块处理数据*/

	// sure = ReturnFlag(&p);
	sure = JudgeStr(1000, 0x03);

	return sure;
}

//生成特征 PS_GenChar
//功能:将ImageBuffer中的原始图像生成指纹特征文件存于CharBuffer1或CharBuffer2
//参数:BufferID --> charBuffer1:0x01	charBuffer1:0x02
//模块返回确认字
unsigned char PS_GenChar(unsigned char BufferID)
{
	unsigned short temp;
	unsigned char sure; //,p=0;

=======
	AS608_PackHead2();
	SendFlag(0x01);
	SendLength(0x03);
	Sendcmd(0x53); /*鐢熸垚鐗瑰緛鎸囦护*/
	SendCheck(0x57);

	//sure=ReturnFlag(&p);
	return JudgeStr(1000, 0x03);
}

//褰曞叆鍥惧儚 PS_GetImage
//鍔熻兘:鎺㈡祴鎵嬫寚锛屾帰娴嬪埌鍚庡綍鍏ユ寚绾瑰浘鍍忓瓨浜嶪mageBuffer銆?
//妯″潡杩斿洖纭?璁ゅ瓧
unsigned char PS_GetImage(void)
{
	uart_getbuflen = 0;
	//delay_ms(300);
	if (AS608_PackHead() == 1)
		return 0xFF;
	SendFlag(0x01); /*鍛戒护鍖呮爣璇?*/
	SendLength(0x03);
	Sendcmd(0x01); /*褰曟寚绾规寚浠?*/
	SendCheck(0x01 + 0x03 + 0x01);

	//nrf_delay_ms(50);        /*绛夊緟鎸囩汗璇嗗埆妯″潡澶勭悊鏁版嵁*/

	// sure = ReturnFlag(&p);
	return JudgeStr(1000, 0x03);
}

//鐢熸垚鐗瑰緛 PS_GenChar
//鍔熻兘:灏咺mageBuffer涓?鐨勫師濮嬪浘鍍忕敓鎴愭寚绾圭壒寰佹枃浠跺瓨浜嶤harBuffer1鎴朇harBuffer2
//鍙傛暟:BufferID --> charBuffer1:0x01	charBuffer1:0x02
//妯″潡杩斿洖纭?璁ゅ瓧
unsigned char PS_GenChar(unsigned char BufferID)
{
>>>>>>> six commit
	if (AS608_PackHead() == 1)
		return 0xFF;
	SendFlag(0x01);
	SendLength(0x04);
<<<<<<< HEAD
	Sendcmd(0x02); /*生成特征指令*/
	AS608_SendData(BufferID);
	temp = 0x01 + 0x04 + 0x02 + BufferID;
	SendCheck(temp);
	//	mmi_dq_log_wakeup_count();
	// sure = ReturnFlag(&p);
	sure = JudgeStr(1000, 0x03);

	return sure;
}

//精确比对两枚指纹特征 PS_Match
//功能:精确比对CharBuffer1 与CharBuffer2 中的特征文件
//模块返回确认字
unsigned char PS_Match(void)
{
	unsigned short temp;
	unsigned char sure; //,p=0;

=======
	Sendcmd(0x02); /*鐢熸垚鐗瑰緛鎸囦护*/
	AS608_SendData(BufferID);
	SendCheck(0x01 + 0x04 + 0x02 + BufferID);
	return JudgeStr(1000, 0x03);
}

//绮剧‘姣斿?逛袱鏋氭寚绾圭壒寰? PS_Match
//鍔熻兘:绮剧‘姣斿?笴harBuffer1 涓嶤harBuffer2 涓?鐨勭壒寰佹枃浠?
//妯″潡杩斿洖纭?璁ゅ瓧
unsigned char PS_Match(void)
{
>>>>>>> six commit
	if (AS608_PackHead() == 1)
		return 0xFF;
	SendFlag(0x01);
	SendLength(0x03);
<<<<<<< HEAD
	Sendcmd(0x03); /*精确比对指令*/
	temp = 0x01 + 0x03 + 0x03;
	SendCheck(temp);

	// sure = ReturnFlag(&p);
	sure = JudgeStr(1000, 0x05);

	return sure;
}
//搜索指纹 PS_Search
//功能:以CharBuffer1或CharBuffer2中的特征文件搜索整个或部分指纹库.若搜索到，则返回页码。
//参数:  BufferID @ref CharBuffer1	CharBuffer2
//说明:  模块返回确认字，页码（相配指纹模板）
unsigned char PS_Search(unsigned char BufferID, unsigned short StartPage, unsigned short PageNum, void *p)
{
	unsigned short temp;
	unsigned char ensure;
	//	QUEUE_DATA_TYPE   *rx_data;

	p = 0;

	if (AS608_PackHead() == 1)
		return 0xFF;
	SendFlag(0x01); //命令包标识
=======
	Sendcmd(0x03); /*绮剧‘姣斿?规寚浠?*/
	SendCheck(0x01 + 0x03 + 0x03);

	// sure = ReturnFlag(&p);
	return JudgeStr(1000, 0x05);
}
//鎼滅储鎸囩汗 PS_Search
//鍔熻兘:浠?CharBuffer1鎴朇harBuffer2涓?鐨勭壒寰佹枃浠舵悳绱㈡暣涓?鎴栭儴鍒嗘寚绾瑰簱.鑻ユ悳绱㈠埌锛屽垯杩斿洖椤电爜銆?
//鍙傛暟:  BufferID @ref CharBuffer1	CharBuffer2
//璇存槑:  妯″潡杩斿洖纭?璁ゅ瓧锛岄〉鐮侊紙鐩搁厤鎸囩汗妯℃澘锛?
unsigned char PS_Search(unsigned char BufferID, unsigned short StartPage, unsigned short PageNum, unsigned short *p)
{

	unsigned char sure;
	if (AS608_PackHead() == 1)
		return 0xFF;
	SendFlag(0x01); //鍛戒护鍖呮爣璇?
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

//合并特征（生成模板）PS_RegModel
//功能:将CharBuffer1与CharBuffer2中的特征文件合并生成 模板,结果存于CharBuffer1与CharBuffer2
//说明:  模块返回确认字
unsigned char PS_RegModel(void)
{
	unsigned short temp;
	unsigned char sure; //,p=0;

=======
	SendCheck(0x01 + 0x08 + 0x04 + BufferID + (StartPage >> 8) + (unsigned char)StartPage + (PageNum >> 8) + (unsigned char)PageNum);
	*p = (uart_rec_buff[10] << 8) + uart_rec_buff[11];
	return sure;
}

//鍚堝苟鐗瑰緛锛堢敓鎴愭ā鏉匡級PS_RegModel
//鍔熻兘:灏咰harBuffer1涓嶤harBuffer2涓?鐨勭壒寰佹枃浠跺悎骞剁敓鎴? 妯℃澘,缁撴灉瀛樹簬CharBuffer1涓嶤harBuffer2
//璇存槑:  妯″潡杩斿洖纭?璁ゅ瓧
unsigned char PS_RegModel(void)
{
>>>>>>> six commit
	if (AS608_PackHead() == 1)
		return 0xFF;
	SendFlag(0x01);
	SendLength(0x03);
<<<<<<< HEAD
	Sendcmd(0x05); /*合并特征指令*/
	temp = 0x01 + 0x03 + 0x05;
	SendCheck(temp);

	// sure = ReturnFlag(&p);
	sure = JudgeStr(1000, 0x03);

	return sure;
}

//储存模板 PS_StoreChar
//功能:将 CharBuffer1 或 CharBuffer2 中的模板文件存到 PageID 号flash数据库位置。
//参数:  BufferID @ref charBuffer1:0x01	charBuffer1:0x02
//       PageID（指纹库位置号）
//说明:  模块返回确认字
unsigned char PS_StoreChar(unsigned char BufferID, unsigned short PageID)
{
	unsigned short temp;
	unsigned char sure; //,p=0;
=======
	Sendcmd(0x05); /*鍚堝苟鐗瑰緛鎸囦护*/
	SendCheck(0x01 + 0x03 + 0x05);

	// sure = ReturnFlag(&p);
	return JudgeStr(1000, 0x03);
}

//鍌ㄥ瓨妯℃澘 PS_StoreChar
//鍔熻兘:灏? CharBuffer1 鎴? CharBuffer2 涓?鐨勬ā鏉挎枃浠跺瓨鍒? PageID 鍙穎lash鏁版嵁搴撲綅缃?銆?
//鍙傛暟:  BufferID @ref charBuffer1:0x01	charBuffer1:0x02
//       PageID锛堟寚绾瑰簱浣嶇疆鍙凤級
//璇存槑:  妯″潡杩斿洖纭?璁ゅ瓧
unsigned char PS_StoreChar(unsigned char BufferID, unsigned short PageID)
{
	unsigned short;
>>>>>>> six commit

	if (AS608_PackHead() == 1)
		return 0xFF;
	SendFlag(0x01);
	SendLength(0x06);
<<<<<<< HEAD
	Sendcmd(0x06); /*存储模板指令*/
	AS608_SendData(BufferID);
	AS608_SendData(PageID >> 8);
	AS608_SendData(PageID);
	temp = 0x01 + 0x06 + 0x06 + BufferID + (PageID >> 8) + (unsigned char)PageID;
	SendCheck(temp);

	// sure = ReturnFlag(&p);
	sure = JudgeStr(1000, 0x03);

	return sure;
}

//删除模板 PS_DeletChar
//功能:  删除flash数据库中指定ID号开始的N个指纹模板
//参数:  PageID(指纹库模板号)，N删除的模板个数。
//说明:  模块返回确认字
unsigned char PS_DeletChar(unsigned short PageID, unsigned short N)
{
	unsigned short temp;
=======
	Sendcmd(0x06); /*瀛樺偍妯℃澘鎸囦护*/
	AS608_SendData(BufferID);
	AS608_SendData(PageID >> 8);
	AS608_SendData(PageID);
	SendCheck(0x01 + 0x06 + 0x06 + BufferID + (PageID >> 8) + (unsigned char)PageID);

	// sure = ReturnFlag(&p);
	return JudgeStr(1000, 0x03);
}

//鍒犻櫎妯℃澘 PS_DeletChar
//鍔熻兘:  鍒犻櫎flash鏁版嵁搴撲腑鎸囧畾ID鍙峰紑濮嬬殑N涓?鎸囩汗妯℃澘
//鍙傛暟:  PageID(鎸囩汗搴撴ā鏉垮彿)锛孨鍒犻櫎鐨勬ā鏉夸釜鏁般�?
//璇存槑:  妯″潡杩斿洖纭?璁ゅ瓧
unsigned char PS_DeletChar(unsigned short PageID, unsigned short N)
{
>>>>>>> six commit
	unsigned char sure; //,p=0;

	if (AS608_PackHead() == 1)
		return 0xFF;
<<<<<<< HEAD
	SendFlag(0x01); //命令包标识
	SendLength(0x07);
	Sendcmd(0x0C); /*删除指定指纹模板指令*/
=======
	SendFlag(0x01); //鍛戒护鍖呮爣璇?
	SendLength(0x07);
	Sendcmd(0x0C); /*鍒犻櫎鎸囧畾鎸囩汗妯℃澘鎸囦护*/
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

//高速搜索PS_HighSpeedSearch
//功能：以 CharBuffer1或CharBuffer2中的特征文件高速搜索整个或部分指纹库。
//		  若搜索到，则返回页码,该指令对于的确存在于指纹库中 ，且登录时质量
//		  很好的指纹，会很快给出搜索结果。
//参数:  BufferID， StartPage(起始页)，PageNum（页数）
//说明:  模块返回确认字+页码（相配指纹模板）
unsigned char PS_HighSpeedSearch(unsigned char BufferID, unsigned short StartPage, unsigned short PageNum, unsigned short *p)
{
	unsigned short temp;
	unsigned char ensure;
	//unsigned short rc;
=======
	return JudgeStr(1000, 0x03);
}

//楂橀�熸悳绱?PS_HighSpeedSearch
//鍔熻兘锛氫互 CharBuffer1鎴朇harBuffer2涓?鐨勭壒寰佹枃浠堕珮閫熸悳绱㈡暣涓?鎴栭儴鍒嗘寚绾瑰簱銆?
//		  鑻ユ悳绱㈠埌锛屽垯杩斿洖椤电爜,璇ユ寚浠ゅ?逛簬鐨勭‘瀛樺湪浜庢寚绾瑰簱涓? 锛屼笖鐧诲綍鏃惰川閲?
//		  寰堝ソ鐨勬寚绾癸紝浼氬緢蹇?缁欏嚭鎼滅储缁撴灉銆?
//鍙傛暟:  BufferID锛? StartPage(璧峰?嬮〉)锛孭ageNum锛堥〉鏁帮級
//璇存槑:  妯″潡杩斿洖纭?璁ゅ瓧+椤电爜锛堢浉閰嶆寚绾规ā鏉匡級
unsigned char PS_HighSpeedSearch(unsigned char BufferID, unsigned short StartPage, unsigned short PageNum, unsigned short *p)
{
	unsigned char ensure;
>>>>>>> six commit

	if (AS608_PackHead() == 1)
		return 0xFF;
	SendFlag(0x01);
	SendLength(0x08);
<<<<<<< HEAD
	Sendcmd(0x1b); /*高速搜索指纹库指令*/
=======
	Sendcmd(0x1b); /*楂橀�熸悳绱㈡寚绾瑰簱鎸囦护*/
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
	*p = (uart_rec_buff[10] << 8) + uart_rec_buff[11]; //模板号
=======
	*p = (uart_rec_buff[10] << 8) + uart_rec_buff[11];
>>>>>>> six commit

	return ensure;
}

<<<<<<< HEAD
//清空指纹库 PS_Empty
//功能:  删除flash数据库中所有指纹模板
//参数:  无
//说明:  模块返回确认字
unsigned char PS_Empty(void)
{
	unsigned short temp;
	unsigned char sure; //,p=0;

	if (AS608_PackHead() == 1)
		return 0xFF;
	SendFlag(0x01); //命令包标识
	SendLength(0x03);
	Sendcmd(0x0D);
	temp = 0x01 + 0x03 + 0x0D;
	SendCheck(temp);

	// sure = ReturnFlag(&p);
	sure = JudgeStr(1000, 0x03);

	return sure;
=======
//娓呯┖鎸囩汗搴? PS_Empty
//鍔熻兘:  鍒犻櫎flash鏁版嵁搴撲腑鎵�鏈夋寚绾规ā鏉?
//鍙傛暟:  鏃?
//璇存槑:  妯″潡杩斿洖纭?璁ゅ瓧
unsigned char PS_Empty(void)
{
	if (AS608_PackHead() == 1)
		return 0xFF;
	SendFlag(0x01); //鍛戒护鍖呮爣璇?
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
  * @brief  检查STM32与指纹模块的通信连接
  * @param  PS_Addr指纹模块地址
  * @retval 返回值0通讯成功;1表示通讯不成功
=======
  * @brief  妫�鏌?STM32涓庢寚绾规ā鍧楃殑閫氫俊杩炴帴
  * @param  PS_Addr鎸囩汗妯″潡鍦板潃
  * @retval 杩斿洖鍊?0閫氳??鎴愬姛;1琛ㄧず閫氳??涓嶆垚鍔?
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
//写系统寄存器 PS_WriteReg
//功能:  写模块寄存器
//参数:  寄存器序号RegNum:4\5\6
//说明:  模块返回确认字
=======
//鍐欑郴缁熷瘎瀛樺櫒 PS_WriteReg
//鍔熻兘:  鍐欐ā鍧楀瘎瀛樺櫒
//鍙傛暟:  瀵勫瓨鍣ㄥ簭鍙稲egNum:4\5\6
//璇存槑:  妯″潡杩斿洖纭?璁ゅ瓧
>>>>>>> six commit
unsigned char PS_WriteReg(unsigned char RegNum, unsigned char DATA)
{
	unsigned short temp;
	unsigned short sure,p=0;

	if(AS608_PackHead()==1)
		return 0xFF;
<<<<<<< HEAD
	SendFlag(0x01);//命令包标识
=======
	SendFlag(0x01);//閸涙垝鎶ら崠鍛?鐖ｇ拠
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
  * @brief  读系统基本参数 PS_ReadSysPara
  * @param  无
  * @return 模块返回确认字 + 基本参数（16bytes）
  * @note   读取模块的基本参数（波特率，包大小等)
  * @see    none
  */
=======
//璇荤郴缁熷熀鏈?鍙傛暟 PS_ReadSysPara
//鍔熻兘:  璇诲彇妯″潡鐨勫熀鏈?鍙傛暟锛堟尝鐗圭巼锛屽寘澶у皬绛?)
//鍙傛暟:  鏃?
//璇存槑:  妯″潡杩斿洖纭?璁ゅ瓧 + 鍩烘湰鍙傛暟锛?16bytes锛?
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
	SendFlag(0x01);//命令包标识
=======
	SendFlag(0x01);//閸涙垝鎶ら崠鍛?鐖ｇ拠
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
//设置模块地址 PS_SetAddr
//功能:  设置模块地址
//参数:  PS_addr
//说明:  模块返回确认字
=======
//璁剧疆妯″潡鍦板潃 PS_SetAddr
//鍔熻兘:  璁剧疆妯″潡鍦板潃
//鍙傛暟:  PS_addr
//璇存槑:  妯″潡杩斿洖纭?璁ゅ瓧
>>>>>>> six commit
unsigned char PS_SetAddr(unsigned long PS_addr)
{
	unsigned short temp;
	unsigned char  ensure;

	if(AS608_PackHead()==1)
		return 0xFF;
<<<<<<< HEAD
	SendFlag(0x01);//命令包标识
=======
	SendFlag(0x01);//鍛戒护鍖呮爣璇?
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
//功能： 模块内部为用户开辟了256bytes的FLASH空间用于存用户记事本,
//	该记事本逻辑上被分成 16 个页。
//参数:  NotePageNum(0~15),Byte32(要写入内容，32个字节)
//说明:  模块返回确认字
=======
//鍔熻兘锛? 妯″潡鍐呴儴涓虹敤鎴峰紑杈熶簡256bytes鐨凢LASH绌洪棿鐢ㄤ簬瀛樼敤鎴疯?颁簨鏈?,
//	璇ヨ?颁簨鏈?閫昏緫涓婅??鍒嗘垚 16 涓?椤点�?
//鍙傛暟:  NotePageNum(0~15),Byte32(瑕佸啓鍏ュ唴瀹癸紝32涓?瀛楄妭)
//璇存槑:  妯″潡杩斿洖纭?璁ゅ瓧
>>>>>>> six commit
unsigned char PS_WriteNotepad(unsigned char NotePageNum,unsigned char *Byte32)
{
	unsigned short temp;
	unsigned char  ensure,i;
	
	*Byte32 = 0;
	
	if(AS608_PackHead()==1)
		return 0xFF;
<<<<<<< HEAD
	SendFlag(0x01); //命令包标识
=======
	SendFlag(0x01); //鍛戒护鍖呮爣璇?
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
//读记事PS_ReadNotepad
//功能：  读取FLASH用户区的128bytes数据
//参数:  NotePageNum(0~15)
//说明:  模块返回确认字+用户信息
=======
//璇昏?颁簨PS_ReadNotepad
//鍔熻兘锛?  璇诲彇FLASH鐢ㄦ埛鍖虹殑128bytes鏁版嵁
//鍙傛暟:  NotePageNum(0~15)
//璇存槑:  妯″潡杩斿洖纭?璁ゅ瓧+鐢ㄦ埛淇℃伅
>>>>>>> six commit
unsigned char PS_ReadNotepad(unsigned char NotePageNum,unsigned char *Byte32)
{
	unsigned short temp;
	unsigned char  ensure;
	
	*Byte32 = 0;
	
	if(AS608_PackHead()==1)
		return 0xFF;
<<<<<<< HEAD
	SendFlag(0x01);//命令包标识
=======
	SendFlag(0x01);//鍛戒护鍖呮爣璇?
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
//读有效模板个数 PS_ValidTempleteNum
//功能：读有效模板个数
//参数: 无
//说明: 模块返回确认字+有效模板个数ValidN
unsigned char PS_ValidTempleteNum(unsigned short *ValidN)
{
	unsigned short temp;
	unsigned char ensure;
	unsigned short p = 0;

	if (AS608_PackHead() == 1)
		return 0xFF;
	SendFlag(0x01); //命令包标识
	SendLength(0x03);
	Sendcmd(0x1d);
	temp = 0x01 + 0x03 + 0x1d;
	SendCheck(temp);
=======
//璇绘湁鏁堟ā鏉夸釜鏁? PS_ValidTempleteNum
//鍔熻兘锛氳?绘湁鏁堟ā鏉夸釜鏁?
//鍙傛暟: 鏃?
//璇存槑: 妯″潡杩斿洖纭?璁ゅ瓧+鏈夋晥妯℃澘涓?鏁癡alidN
unsigned char PS_ValidTempleteNum(unsigned short *ValidN)
{
	unsigned char ensure;

	if (AS608_PackHead() == 1)
		return 0xFF;
	SendFlag(0x01); //鍛戒护鍖呮爣璇?
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
//自动注册模板 PS_AutoEnRoll
//功能：采集一次指纹注册模板，在指纹库中搜索空位并存储，返回存储ID
//参数: 无
//说明: 模块返回确认字+页码（相配指纹模板）
unsigned char PS_AutoEnRoll(unsigned short id, unsigned char num, unsigned short param)
{
	unsigned short sum;

	if (AS608_PackHead() == 1)
		return 0xFF;
	SendFlag(0x01); //命令包标识
=======
unsigned char PS_AutoEnRoll(unsigned short id, unsigned char num, unsigned short param)
{
	if (AS608_PackHead() == 1)
		return 0xFF;
	SendFlag(0x01); //鍛戒护鍖呮爣璇?
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
//自动验证指纹 PS_AutoIdentify
//功能：
//1.自动采集指纹，在指纹库中搜索目标模板并返回搜索结果。
//2.如果目标模板同当前采集的指纹比对得分大于最高阀值，并且目标模板为不完整特征则以采集的特征更新目标模板的空白区域。
//参数: 无
//说明: 模块返回确认字+页码（相配指纹模板）
unsigned char PS_AutoIdentify(unsigned short id, unsigned char level, unsigned short param)
{
	unsigned short sum;

	if (AS608_PackHead() == 1)
		return 0xFF;
	SendFlag(0x01); //命令包标识
=======
//鑷?鍔ㄩ獙璇佹寚绾? PS_AutoIdentify
//鍔熻兘锛?
//1.鑷?鍔ㄩ噰闆嗘寚绾癸紝鍦ㄦ寚绾瑰簱涓?鎼滅储鐩?鏍囨ā鏉垮苟杩斿洖鎼滅储缁撴灉銆?
//2.濡傛灉鐩?鏍囨ā鏉垮悓褰撳墠閲囬泦鐨勬寚绾规瘮瀵瑰緱鍒嗗ぇ浜庢渶楂橀榾鍊硷紝骞朵笖鐩?鏍囨ā鏉夸负涓嶅畬鏁寸壒寰佸垯浠ラ噰闆嗙殑鐗瑰緛鏇存柊鐩?鏍囨ā鏉跨殑绌虹櫧鍖哄煙銆?
//鍙傛暟: 鏃?
//璇存槑: 妯″潡杩斿洖纭?璁ゅ瓧+椤电爜锛堢浉閰嶆寚绾规ā鏉匡級
unsigned char PS_AutoIdentify(unsigned short id, unsigned char level, unsigned short param)
{
	if (AS608_PackHead() == 1)
		return 0xFF;
	SendFlag(0x01); //鍛戒护鍖呮爣璇?
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
//与AS608握手 PS_HandShake
//参数: PS_Addr地址指针
//说明: 模块返新地址（正确地址） 返回确认码
unsigned char PS_HandShake(unsigned long *PS_Addr)
{
	unsigned char ensure;
=======
//涓嶢S608鎻℃墜 PS_HandShake
//鍙傛暟: PS_Addr鍦板潃鎸囬拡
//璇存槑: 妯″潡杩旀柊鍦板潃锛堟?ｇ‘鍦板潃锛?
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
	SendFlag(0x01); //命令包标识
	SendLength(0x03);
	Sendcmd(0x60);
	temp = 0x01 + 0x03 + 0x60;
	SendCheck(temp);
	return ensure;
=======
	if (AS608_PackHead() == 1)
		return 0xFF;
	SendFlag(0x01); //鍛戒护鍖呮爣璇?
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
