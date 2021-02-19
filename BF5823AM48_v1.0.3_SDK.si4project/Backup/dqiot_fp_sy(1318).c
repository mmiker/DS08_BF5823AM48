
//#if defined (__PREIPHERAL_FP_SY_SUPPORT__)
#include "string.h"
#include "dqiot_fp_sy.h"

unsigned long fp_pin_irq_mask;

fp_irq_handle_callback fp_callback_handle;
fp_uart_handle_callback fp_uart_handle = 0;
unsigned char fp_Mode = 0;
static unsigned char fp_temp_mode = 0;

static unsigned char uart_rec_buff[50];

static FP_TYPE fp_flag = FP_NONE;
static FP_COLOR_E Light_Color = FP_NONE_COLOR;
static unsigned char ps_start_flag = 0;

unsigned short  ReceiveInfo( unsigned char *rec_data);
void AS608_log(void);

void fp_set_irq_handle(fp_irq_handle_callback cb)
{
	fp_callback_handle = cb;
}

void fp_set_uart_handle(fp_uart_handle_callback cb)
{
	fp_uart_handle = cb;
}


FP_TYPE fp_get_type(void)
{
	return fp_flag;

}

//--------------------------------------------------------------------------------

static unsigned char uart_len=0;
static unsigned short uart_maxlen = 0;
static unsigned char uart_buff[25]={0};

static void UART_Callback(unsigned char send_data)
{
	send_data = 0;
}


static void uart_init_none_block_priority_low(void)
{
	//dqiot_uart_init();
}

static void uart_init_none_block_priority_high(void)
{
	//dqiot_uart_init();
}

static void uart_init_block(void)
{
	//dqiot_uart_init_with_block();
}
static void uart_init_none_block_low_speed(void)
{
	//dqiot_uart_init(comm_params);
}

unsigned char test_data[] ={0xAA,0xAA,0x87,0x00,0x02,0x0A,0x01,0x01,0xE8};
void FP_INT (void)
{
	//uint8_t data[] ={0xAA,0xAA,0x86,0x00,0x01,0x12,0x01,0xED};
//	unsigned long err_code;
//	// Configure pins.
//  unsigned long pins_transition_mask = 0;
//	unsigned char delay_times = 50;

//	while(fp_flag==0&&delay_times>0)
//	{
//		delay_times--;
//	}

//	if(fp_flag == FP_UNKNOW)
//	{
//		uart_init_block();
//		if(PS_GetEcho()==0x55)
//		{
//			fp_flag = FP_LT5X;
//			ps_start_flag = 2;
//			PS_ReadSysPara();
//		}
//		else
//			fp_flag = FP_NONE;
//	}
//	else if(fp_flag == FP_BTL)
//	{
//		delay_times = 50;
////		dqiot_uart_sendData(test_data,9);

//		while(set_times_sucess==0&&delay_times>0)
//		{
//			delay_times--;
//		}

//	}

//	if(fp_flag == FP_NONE)
//	{
//		FP_PWREN_OFF;
//	}
	return;
}

unsigned char fp_GetModeState(void)
{
	return fp_Mode;
}

void fp_SetModeState(unsigned char s)
{
	fp_Mode = s;
	
	if(s == 0)	
		Light_Color = FP_NONE_COLOR;
}

static void PS_UART_Callback(unsigned char send_data)
{
	if(send_data == 0x55 )
	{
		ps_start_flag = 1;
	}
}

void FP_PowerOn(void)
{

}

/**
  * @brief  AS608_USART串口向指纹模块传递数据 
  * @param  data;传输的数据
  */
void AS608_SendData(unsigned char send_data)
{
		send_data = 0;
}


/**
  * @brief  AS608_USART串口向指纹模块命令包头格式 
  * @param  无
  */
unsigned char AS608_PackHead(void)
{ 

	unsigned char delay_times = 30;
	
	while(ps_start_flag==0&&delay_times>0)
	{
		delay_times--;
	}
	if(ps_start_flag == 0)
	{
		return 1;
	}
	else if(ps_start_flag == 1)
	{
		uart_init_block();
		ps_start_flag = 2;
	}


	/*包头*/
	AS608_SendData(0xEF);
	AS608_SendData(0x01);	

	/*指纹模块地址*/
	AS608_SendData(AS608_Addr>>24);
	AS608_SendData(AS608_Addr>>16);	
	AS608_SendData(AS608_Addr>>8);
	AS608_SendData(AS608_Addr);	

	return 0;
}

unsigned char AS608_PackHead2(void)
{ 

	/*包头*/
	AS608_SendData(0xEF);
	AS608_SendData(0x01);	

	/*指纹模块地址*/
	AS608_SendData(AS608_Addr>>24);
	AS608_SendData(AS608_Addr>>16);	
	AS608_SendData(AS608_Addr>>8);
	AS608_SendData(AS608_Addr);	

	return 0;
}


/**
  * @brief  发送包标识
  * @param  flag:包标识位
  * @retval 无
  */
 void SendFlag(unsigned char flag)
{
	AS608_SendData(flag);
}


/**
  * @brief  发送包长度
  * @param  length:包长度
  * @retval 无
  */
 void SendLength(unsigned short length)
{
	AS608_SendData(length>>8);
	AS608_SendData(length);
}


/**
  * @brief  发送指令码
  * @param  cmd;指令码
  * @retval 无
  */
void Sendcmd(unsigned char cmd)
{
	AS608_SendData(cmd);
}


/**
  * @brief  发送校验和
  * @param  check:检查位
  * @retval 无
  */
 void SendCheck(unsigned short check)
{
	AS608_SendData(check>>8);
	AS608_SendData(check);
}

/**
  * @brief  从缓冲区读出确认码
  * @param  *i:返回值（确认码）
  * @retval 无
  */
unsigned short  ReturnFlag( unsigned short *i)
{	
	*i = ReceiveInfo(uart_rec_buff);
	return *i;
}

unsigned short  ReceiveInfo( unsigned char *rec_data)
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


unsigned short PS_GetEcho(void)
{
	unsigned short  sure,p=0;

	AS608_PackHead2();
	SendFlag(0x01);          
	SendLength(0x03);
	Sendcmd(0x53);              /*生成特征指令*/   
	SendCheck(0x57);

	sure=ReturnFlag(&p);

	return  sure;

}

//褰曞叆鍥惧儚 PS_GetImage
//鍔熻兘:鎺㈡祴鎵嬫寚锛屾帰娴嬪埌鍚庡綍鍏ユ寚绾瑰浘鍍忓瓨浜嶪mageBuffer銆 
//妯″潡杩斿洖纭瀛
unsigned short PS_GetImage(void)
{
	unsigned short temp;
	unsigned short sure,p=0;
	//nrf_delay_ms(300);       /*给指纹输入动作预留时间*/

	if(AS608_PackHead()==1)
		return 0xFF;
	SendFlag(0x01);             /*命令包标识*/
	SendLength(0x03);
	Sendcmd(0x01);              /*录指纹指令*/
	temp=0x01+0x03+0x01;
	SendCheck(temp);
//	mmi_dq_log_wakeup_count();

	//nrf_delay_ms(50);        /*等待指纹识别模块处理数据*/

	sure=ReturnFlag(&p);

	return  sure;
}


//鐢熸垚鐗瑰緛 PS_GenChar
//鍔熻兘:灏咺mageBuffer涓殑鍘熷鍥惧儚鐢熸垚鎸囩汗鐗瑰緛鏂囦欢瀛樹簬CharBuffer1鎴朇harBuffer2			 
//鍙傛暟:BufferID --> charBuffer1:0x01	charBuffer1:0x02												
//妯″潡杩斿洖纭瀛
unsigned short PS_GenChar(unsigned char BufferID)
{
	unsigned short temp;
	unsigned short  sure,p=0;

	if(AS608_PackHead()==1)
		return 0xFF;
	SendFlag(0x01);          
	SendLength(0x04);
	Sendcmd(0x02);              /*生成特征指令*/   
	AS608_SendData(BufferID);
	temp = 0x01+0x04+0x02+BufferID;
	SendCheck(temp);
//	mmi_dq_log_wakeup_count();
	sure=ReturnFlag(&p);

	return  sure;
}

//绮剧‘姣斿涓ゆ灇鎸囩汗鐗瑰緛 PS_Match
//鍔熻兘:绮剧‘姣斿CharBuffer1 涓嶤harBuffer2 涓殑鐗瑰緛鏂囦欢 
//妯″潡杩斿洖纭瀛
unsigned short PS_Match(void)
{
	unsigned short temp;
  	unsigned short  sure,p=0;
	
	if(AS608_PackHead()==1)
		return 0xFF;
	SendFlag(0x01);
	SendLength(0x03);
	Sendcmd(0x03);                /*精确比对指令*/
	temp = 0x01+0x03+0x03;
	SendCheck(temp);
	
  	sure=ReturnFlag(&p);
  
  	return  sure;
}
//鎼滅储鎸囩汗 PS_Search
//鍔熻兘:浠harBuffer1鎴朇harBuffer2涓殑鐗瑰緛鏂囦欢鎼滅储鏁翠釜鎴栭儴鍒嗘寚绾瑰簱.鑻ユ悳绱㈠埌锛屽垯杩斿洖椤电爜銆			
//鍙傛暟:  BufferID @ref CharBuffer1	CharBuffer2
//璇存槑:  妯″潡杩斿洖纭瀛楋紝椤电爜锛堢浉閰嶆寚绾规ā鏉匡級
unsigned char PS_Search(unsigned char BufferID,unsigned short StartPage,unsigned short PageNum,void *p)
{
	unsigned short temp;
	unsigned char  ensure;
//	QUEUE_DATA_TYPE   *rx_data;	
	
	p = 0;

	if(AS608_PackHead()==1)
		return 0xFF;
	SendFlag(0x01);//鍛戒护鍖呮爣璇
	SendLength(0x08);
	Sendcmd(0x04);
	AS608_SendData(BufferID);
	AS608_SendData(StartPage>>8);
	AS608_SendData(StartPage);
	AS608_SendData(PageNum>>8);
	AS608_SendData(PageNum);
	temp = 0x01+0x08+0x04+BufferID+(StartPage>>8)+(unsigned char)StartPage+(PageNum>>8)+(unsigned char)PageNum;
	SendCheck(temp);
	return ensure;	
}


//鍚堝苟鐗瑰緛锛堢敓鎴愭ā鏉匡級PS_RegModel
//鍔熻兘:灏咰harBuffer1涓嶤harBuffer2涓殑鐗瑰緛鏂囦欢鍚堝苟鐢熸垚 妯℃澘,缁撴灉瀛樹簬CharBuffer1涓嶤harBuffer2	
//璇存槑:  妯″潡杩斿洖纭瀛
unsigned short PS_RegModel(void)
{
	unsigned short temp;
	unsigned short sure,p=0;
  	
	if(AS608_PackHead()==1)
		return 0xFF;
	SendFlag(0x01);
	SendLength(0x03);
	Sendcmd(0x05);                /*合并特征指令*/
	temp = 0x01+0x03+0x05;
	SendCheck(temp);
	
  	sure=ReturnFlag(&p);
  
  return  sure;

}

//鍌ㄥ瓨妯℃澘 PS_StoreChar
//鍔熻兘:灏 CharBuffer1 鎴 CharBuffer2 涓殑妯℃澘鏂囦欢瀛樺埌 PageID 鍙穎lash鏁版嵁搴撲綅缃			
//鍙傛暟:  BufferID @ref charBuffer1:0x01	charBuffer1:0x02
//       PageID锛堟寚绾瑰簱浣嶇疆鍙凤級
//璇存槑:  妯″潡杩斿洖纭瀛
unsigned short PS_StoreChar(unsigned char BufferID,unsigned short PageID)
{
	unsigned short temp;
	unsigned short sure,p=0;
 
	if(AS608_PackHead()==1)
		return 0xFF;
	SendFlag(0x01);
	SendLength(0x06);
	Sendcmd(0x06);                /*存储模板指令*/
	AS608_SendData(BufferID);
  	AS608_SendData(PageID>>8);
	AS608_SendData(PageID);
	temp = 0x01+0x06+0x06+BufferID+(PageID>>8)+(unsigned char)PageID;
	SendCheck(temp);
	
  	sure=ReturnFlag(&p);
  
  	return  sure;
}



//鍒犻櫎妯℃澘 PS_DeletChar
//鍔熻兘:  鍒犻櫎flash鏁版嵁搴撲腑鎸囧畾ID鍙峰紑濮嬬殑N涓寚绾规ā鏉
//鍙傛暟:  PageID(鎸囩汗搴撴ā鏉垮彿)锛孨鍒犻櫎鐨勬ā鏉夸釜鏁般
//璇存槑:  妯″潡杩斿洖纭瀛
unsigned short PS_DeletChar(unsigned short PageID,unsigned short N)
{
	unsigned short temp;
	unsigned short sure,p=0;
 
	
	if(AS608_PackHead()==1)
		return 0xFF;
	SendFlag(0x01);//命令包标识
	SendLength(0x07);
	Sendcmd(0x0C);                /*删除指定指纹模板指令*/
	AS608_SendData(PageID>>8);
  	AS608_SendData(PageID);
	AS608_SendData(N>>8);
	AS608_SendData(N);
	temp = 0x01+0x07+0x0C
	       +(PageID>>8)+(unsigned char)PageID
	       +(N>>8)+(unsigned char)N;
	SendCheck(temp);
	
	//AS608_DELAY_MS(400);
	
	sure=ReturnFlag(&p);
  
  return  sure;

	
}


//楂橀熸悳绱S_HighSpeedSearch
//鍔熻兘锛氫互 CharBuffer1鎴朇harBuffer2涓殑鐗瑰緛鏂囦欢楂橀熸悳绱㈡暣涓垨閮ㄥ垎鎸囩汗搴撱
//		  鑻ユ悳绱㈠埌锛屽垯杩斿洖椤电爜,璇ユ寚浠ゅ浜庣殑纭瓨鍦ㄤ簬鎸囩汗搴撲腑 锛屼笖鐧诲綍鏃惰川閲
//		  寰堝ソ鐨勬寚绾癸紝浼氬緢蹇粰鍑烘悳绱㈢粨鏋溿
//鍙傛暟:  BufferID锛 StartPage(璧峰椤)锛孭ageNum锛堥〉鏁帮級
//璇存槑:  妯″潡杩斿洖纭瀛+椤电爜锛堢浉閰嶆寚绾规ā鏉匡級
unsigned short PS_HighSpeedSearch(unsigned char BufferID,unsigned short StartPage,unsigned short PageNum,unsigned short *p)
{
	unsigned short temp;
    unsigned short ensure;
    unsigned short rc;

	if(AS608_PackHead()==1)
		return 0xFF;
	SendFlag(0x01);
	SendLength(0x08);
	Sendcmd(0x1b);                 /*高速搜索指纹库指令*/
	AS608_SendData(BufferID);
	AS608_SendData(StartPage>>8);
	AS608_SendData(StartPage);
	AS608_SendData(PageNum>>8);
	AS608_SendData(PageNum);
	temp = 0x01+0x08+0x1b+BufferID+(StartPage>>8)+(unsigned char)StartPage+(PageNum>>8)+(unsigned char)PageNum;
	SendCheck(temp);

	ensure=ReturnFlag(&rc);

	*p=(uart_rec_buff[10]<<8)+uart_rec_buff[11];

	return ensure;
}


//娓呯┖鎸囩汗搴 PS_Empty
//鍔熻兘:  鍒犻櫎flash鏁版嵁搴撲腑鎵鏈夋寚绾规ā鏉
//鍙傛暟:  鏃
//璇存槑:  妯″潡杩斿洖纭瀛
unsigned short  PS_Empty(void)
{
	unsigned short temp;
  	unsigned short sure,p=0;
 
	if(AS608_PackHead()==1)
		return 0xFF;
	SendFlag(0x01);//命令包标识
	SendLength(0x03);
	Sendcmd(0x0D);
	temp = 0x01+0x03+0x0D;
	SendCheck(temp);
	
  	sure=ReturnFlag(&p);
  
  	return  sure;
}


/**
  * @brief  检查STM32与指纹模块的通信连接
  * @param  PS_Addr指纹模块地址
  * @retval 返回值0通讯成功;1表示通讯不成功
  */
unsigned short PS_Connect(unsigned long *PS_Addr)
{
	PS_Addr = 0;
	if(AS608_PackHead()==1)
		return 0xFF;
	AS608_SendData(0X01);
	AS608_SendData(0X00);
	AS608_SendData(0X00);
	return 1;		
}

//鍐欑郴缁熷瘎瀛樺櫒 PS_WriteReg
//鍔熻兘:  鍐欐ā鍧楀瘎瀛樺櫒
//鍙傛暟:  瀵勫瓨鍣ㄥ簭鍙稲egNum:4\5\6
//璇存槑:  妯″潡杩斿洖纭瀛
unsigned char PS_WriteReg(unsigned char RegNum,unsigned char DATA)
{
	unsigned short temp;
	unsigned short sure,p=0;

	if(AS608_PackHead()==1)
		return 0xFF;
	SendFlag(0x01);//鍛戒护鍖呮爣璇
	SendLength(0x05);
	Sendcmd(0x0E);
	AS608_SendData(RegNum);
	AS608_SendData(DATA);
	temp = RegNum+DATA+0x01+0x05+0x0E;
	SendCheck(temp);
	sure=ReturnFlag(&p);
	return sure;
}
//读系统基本参数 PS_ReadSysPara
//功能:  读取模块的基本参数（波特率，包大小等)
//参数:  无
//说明:  模块返回确认字 + 基本参数（16bytes）
unsigned char PS_ReadSysPara(void)
{
	unsigned short temp;
	unsigned char  ensure;
	unsigned char  *send_data;
	unsigned short p=0;
	
	if(AS608_PackHead()==1)
		return 0xFF;
	SendFlag(0x01);//鍛戒护鍖呮爣璇
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
//璁剧疆妯″潡鍦板潃 PS_SetAddr
//鍔熻兘:  璁剧疆妯″潡鍦板潃
//鍙傛暟:  PS_addr
//璇存槑:  妯″潡杩斿洖纭瀛
unsigned char PS_SetAddr(unsigned long PS_addr)
{
	unsigned short temp;
	unsigned char  ensure;

	if(AS608_PackHead()==1)
		return 0xFF;
	SendFlag(0x01);//鍛戒护鍖呮爣璇
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
//功能： 模块内部为用户开辟了256bytes的FLASH空间用于存用户记事本,
//	该记事本逻辑上被分成 16 个页。
//参数:  NotePageNum(0~15),Byte32(要写入内容，32个字节)
//说明:  模块返回确认字
unsigned char PS_WriteNotepad(unsigned char NotePageNum,unsigned char *Byte32)
{
	unsigned short temp;
	unsigned char  ensure,i;
	
	*Byte32 = 0;
	
	if(AS608_PackHead()==1)
		return 0xFF;
	SendFlag(0x01);//鍛戒护鍖呮爣璇
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
//读记事PS_ReadNotepad
//功能：  读取FLASH用户区的128bytes数据
//参数:  NotePageNum(0~15)
//说明:  模块返回确认字+用户信息
unsigned char PS_ReadNotepad(unsigned char NotePageNum,unsigned char *Byte32)
{
	unsigned short temp;
	unsigned char  ensure;
	
	*Byte32 = 0;
	
	if(AS608_PackHead()==1)
		return 0xFF;
	SendFlag(0x01);//命令包标识
	SendLength(0x04);
	Sendcmd(0x19);
	AS608_SendData(NotePageNum);
	temp = 0x01+0x04+0x19+NotePageNum;
	SendCheck(temp);

	return ensure;
}

//读有效模板个数 PS_ValidTempleteNum
//功能：读有效模板个数
//参数: 无
//说明: 模块返回确认字+有效模板个数ValidN
unsigned char PS_ValidTempleteNum(unsigned short *ValidN)
{
	unsigned short temp;
	unsigned char  ensure;
	unsigned short p=0;
	
	if(AS608_PackHead()==1)
		return 0xFF;
	SendFlag(0x01);//鍛戒护鍖呮爣璇
	SendLength(0x03);
	Sendcmd(0x1d);
	temp = 0x01+0x03+0x1d;
	SendCheck(temp);

	ensure=ReturnFlag(&p);

	*ValidN=(uart_rec_buff[10]<<8)+uart_rec_buff[11];

	return ensure;
}

unsigned char PS_AutoEnRoll(unsigned short id, unsigned char num, unsigned short param)
{
	unsigned short sum;

	if(AS608_PackHead()==1)
		return 0xFF;
	SendFlag(0x01);//鍛戒护鍖呮爣璇
	SendLength(0x08);
	Sendcmd(0x31);
	AS608_SendData(id>>8);
	AS608_SendData(id &0xFF);
	AS608_SendData(num);
	AS608_SendData(param>>8);
	AS608_SendData(param&0xFF);
	sum = 0x01 + 0x08 + 0x31 + (id>>8) + (id&0xFF) + num + (param>>8) + (param&0xFF);
	SendCheck(sum);

	return 0;
}


unsigned char PS_AutoIdentify(unsigned short id, unsigned char level, unsigned short param)
{
	unsigned short sum;

	if(AS608_PackHead()==1)
		return 0xFF;
	SendFlag(0x01);//鍛戒护鍖呮爣璇
	SendLength(0x08);
	Sendcmd(0x32);
	AS608_SendData(level);
	AS608_SendData(id>>8);
	AS608_SendData(id &0xFF);
	AS608_SendData(param>>8);
	AS608_SendData(param&0xFF);
	sum = 0x01 + 0x08 + 0x32 + (id>>8) + (id&0xFF) + level + (param>>8) + (param&0xFF);
	SendCheck(sum);

	return 0;

}

//与AS608握手 PS_HandShake
//参数: PS_Addr地址指针
//说明: 模块返新地址（正确地址）
unsigned char PS_HandShake(unsigned long *PS_Addr)
{	
	*PS_Addr = 0;
	
	if(AS608_PackHead()==1)
		return 0xFF;
	
	SendFlag(0x01);
	SendLength(0x07);
	Sendcmd(0x13);
	AS608_SendData(0x00);
	AS608_SendData(0x00);
	AS608_SendData(0x00);
	AS608_SendData(0x00);
	SendCheck(0x1B);

	return 0;
}

unsigned char PS_Reset(void)
{
    return 0;
}


unsigned char PS_Sleep(void)
{
	unsigned short temp;
  	unsigned char  ensure;
	
	if(AS608_PackHead()==1)
		return 0xFF;
	SendFlag(0x01);//鍛戒护鍖呮爣璇
	SendLength(0x03);
	Sendcmd(0x60);
	temp = 0x01+0x03+0x60;
	SendCheck(temp);
	return ensure;
}
void AS608_log(void)
{
	unsigned char i =0;
//	NRF_LOG_PRINTF_DEBUG("receive :");
	for(i=0;i<25;i++)
	{
//		NRF_LOG_PRINTF_DEBUG("%2x ",as608_rec_buff[i]);
	}
//	NRF_LOG_PRINTF_DEBUG("\n");
}

void FP_Light(FP_COLOR_E light_id)
{
	if(fp_flag == FP_LT5X)
	{
#ifdef __FP_LT5X_LIGHT_SUPPORT__
		unsigned short temp;

		unsigned short  sure = 0,p=0;
		if(light_id == Light_Color)
			return;

		if(AS608_PackHead()==1)
			return;
		SendFlag(0x01);          
		SendLength(0x07);
		Sendcmd(0x41); 
		switch(light_id)
		{
			case FP_BLUE:
				AS608_SendData(0x01);
				AS608_SendData(0x01);
				AS608_SendData(0x00);
				AS608_SendData(0x50);
				temp = 0x01+0x07+0x41+0x02+0x50;
				break;
			case FP_GREEN:
				AS608_SendData(0x01);
				AS608_SendData(0x02);
				AS608_SendData(0x02);
				AS608_SendData(0);
				temp = 0x01+0x07+0x41+0x05+0;
				break;	
			case FP_RED:
				AS608_SendData(0x01);
				AS608_SendData(0x04);
				AS608_SendData(0x04);
				AS608_SendData(0);
				temp = 0x01+0x07+0x41+0x09+0;
				break;
			case FP_NONE_COLOR:
				AS608_SendData(0x04);
				AS608_SendData(0x00);
				AS608_SendData(0x00);
				AS608_SendData(0xC8);
				temp = 0x01+0x07+0x41+0x04+0xC8;
				break;
		}
		SendCheck(temp);

		sure=ReturnFlag(&p);
#endif
		Light_Color = light_id;

	}
}

FP_COLOR_E FP_Get_Light(void)
{
	return Light_Color;
}

//#endif//__PREIPHERAL_FP_LT5X_SUPPORT__



