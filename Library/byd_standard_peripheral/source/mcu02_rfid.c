/*!
    \file  mcu02_rfid.c
    \brief rfid driver
*/

/*
    Copyright (C) 2020 BYD

    2020-07-09, V1.0.0, firmware for mcu02
*/

#include "mcu02_rfid.h"
#include "mcu02_gpio.h"
#include "mcu02_system.h"
#include "delay.h"


/*!
    \brief      rfid config
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rfid_config(void)
{
    SET_PC0_IO_OUT;//RF_TX
	SET_PC0_L;

//	SET_PB7_IO_OUT;//test输出io口
//	SET_PB7_L;
//	apb_sfr_write(SFR_TEST_SEL1,0xc0);//输出比较器滤波后信号
//	apb_sfr_write(SFR_TEST_SEL1,0x40);//输出比较器滤波前信号
//	apb_sfr_write(SFR_TEST_SEL1,0x3c);//输出32k时钟
//	apb_sfr_write(SFR_TEST_SEL1,0x3b);//输出13.56M时钟
	
	PLL_13P56M_ENABLE();
	delay_ms(2);
	PLL_13P56M_WAKE_TIME_SET(3);

	RFID_CFG2 = 0x00;
	RFID_CFG3 = 0x00;
	
	RFID_IO_ENABLE();//RFID IO口使能
	RFID_REIV_BIT_SET(2);//接收位时序0~3对应1~4
	RFID_REIV_FILTER_SET(5);//滤波个数1~15,0无滤波
	
	RFID_RXD_16H_EN(1);//配置接收计数器加1
	RFID_RXD_PRENUM_SET(4);
	RFID_TXD_DATA_SEL(RFID_TXD_DATA_8);


    RFID_CMP_DISABLE();//RFID接收比较器不工作


	RFID_ENABLE();	
}
/*!
    \brief      data parity
    \param[in]  none
    \param[out] none
    \retval     parity bit
*/
bit calc_parity(uint8_t send_data)
{   
   uint8_t temp = send_data;
   bit parity_flag = 0;
   while (temp)                            
   {                                    
		parity_flag = !parity_flag;                  
		temp = temp & (temp - 1);                   
   }
   return !parity_flag;
}

/*!
    \brief      wait rfid tx complete
    \param[in]  none
    \param[out] none
    \retval     status: ERROR or SUCCESS
*/
ErrStatus wait_rfid_tx_complete(void)
{
	uint16_t count = WAIT_TIMEOUT_TX;
	
	while(count --){
		if(RFID_CFG & RFID_TX_COMPLET_FLAG){
			RFID_CFG &= ~RFID_TX_COMPLET_FLAG;
			return SUCCESS;
		}
	}
	return ERROR;
}

/*!
    \brief      rfid transmit data
    \param[in]  buf:data pointer
	\param[in]	len:the number of data(len=0~31)          
    \param[out] none
    \retval     ERROR or SUCCESS
*/
ErrStatus rfid_transmit(uint8_t *buf,uint8_t len)
{
	  uint8_t i;	
	  ErrStatus state = ERROR;

	  RFID_TXD_DATA_SEL(RFID_TXD_DATA_8);

	  if(0 == len || 1 == len)
	  {
		  RFID_BUF1 = buf[0];
	      RFID_DATANUM_SET(len);
	      RFID_SEND_ENABLE();	
		  state = wait_rfid_tx_complete();
	  }
	  else 
	  {
		  RFID_BUF1 = buf[0];
		  RFID_BUF2 = buf[1];
		  RFID_DATANUM_SET(len);

		  RFID_SEND_ENABLE();
		
		  state = wait_rfid_tx_complete();
		
		  for(i = 2; i < len; i++)
		  {
			 if(i & 0x01)
			 {
				RFID_BUF2 = buf[i];
			 }
			 else
			 {
				RFID_BUF1 = buf[i];
			 }           				 
			 state = wait_rfid_tx_complete();				
		  }
			
		  state = wait_rfid_tx_complete();
	  }
	  
	  return state;
}

/*!
    \brief      rfid transmit bit
    \param[in]  buf:data pointer
	\param[in]	lenBit:the number of data bit          
    \param[out] none
    \retval     ERROR or SUCCESS
*/
ErrStatus rfid_transmit_bit(uint8_t *buf,uint8_t lenBit)
{
    uint8_t i,m;
    bit bit_last,buf_flag=0;
	bit send_flag = 0;
    uint8_t dat;
    uint8_t ucparity;	
    uint8_t temp_bit;
	uint8_t allbyte,lastbit;
	    
    RFID_BIT_TXD_MODE_ENABLE();
    RFID_TXD_STOP_MODE_ENABLE();

	//计算总字节数和最后位长度
    allbyte = lenBit>>3;
    lastbit = lenBit&0x07; 

	//发送起始位
    RFID_BUF1 = send_z();
    bit_last = 1;

    for(m=0;m<allbyte+1;m++)
    {
      ucparity = 0;
      dat=buf[m];
      
	  if(m < allbyte)
	  {
	     i = 8;
	  }
	  else
	  {
	     i = lastbit;
	  }

	  for(;i>0;i--)
      {
        if(dat&1)
        {
          temp_bit = send_x();
          bit_last = 0;
          ucparity++;
        }
        else 
        {
          if(bit_last) 
		  { 
		  	temp_bit = send_z(); 
		  }
          else            
		  { 
		  	temp_bit = send_y(); 
		  }
          bit_last = 1;
        }
        dat>>=1;

		if(!buf_flag)
		{
			RFID_BUF2 = temp_bit;
			buf_flag = 1;
		}
		else
		{
			RFID_BUF1 = temp_bit;
			buf_flag = 0;
		}
		
		if(!send_flag)
		{
			send_flag = 1;
			RFID_SEND_ENABLE();
		}	
	    wait_rfid_tx_complete();

      }

      if(allbyte > 1)
      {
        if((ucparity&0x01)==0)
		{
			temp_bit = send_x(); 
			bit_last = 0;
		}
        else if(bit_last==1)
		{
			temp_bit = send_z(); 
			bit_last = 1;
		}
        else                
		{
			temp_bit = send_y(); 
		    bit_last = 1;
		}
		
		if(!buf_flag) 
	  	{
		   RFID_BUF2 = temp_bit;
		   buf_flag = 1;
		}
	    else
		{
		   RFID_BUF1 = temp_bit;
		   buf_flag = 0;
		}

	    wait_rfid_tx_complete();
	  		 
      }

    }

    //发送结束位
    if(allbyte >1)
    {  
	      
	  if(bit_last==1) 
	  {
	  	 temp_bit = send_z(); 
	  }
      else            
	  {
	     temp_bit = send_y();	     
	  }
	  
	  if(!buf_flag)
	  { 
	  	 RFID_BUF2 = temp_bit;
		 buf_flag = 1;
	  }
	  else
	  {
		 RFID_BUF1 = temp_bit;
		 buf_flag = 0;
	  }
	  wait_rfid_tx_complete();

	  if(!buf_flag)
	  { 
	  	 RFID_BUF2 = send_y();
		 buf_flag = 1;
	  }
	  else
	  {
		 RFID_BUF1 = send_y();
		 buf_flag = 0;
	  }
	  wait_rfid_tx_complete();
    }
									 
	RFID_TXD_STOP_ENABLE();
	delay_us(10);
	
    RFID_SEND_DISABLE();
	RFID_TXD_STOP_MODE_DISABLE();
	RFID_BIT_TXD_MODE_DISABLE();

	return SUCCESS;
}

/*!
    \brief      rfid transmit 9bit
    \param[in]  buf:data pointer
	\param[in]	len:the number of data(len=2~31)          
    \param[out] none
    \retval     ERROR or SUCCESS
*/
ErrStatus rfid_transmit_9bit(uint8_t *buf,uint8_t *paritybuf,uint8_t len)
{
    uint8_t i;
    ErrStatus state = ERROR;

	RFID_BIT_TXD_MODE_DISABLE();	

    RFID_TXD_DATA_SEL(RFID_TXD_DATA_9);

    RFID_BUF1 = buf[0];
	RFID_BUF2 = buf[1];

	RFID_BUF1_ODD_SET(paritybuf[0]);
	RFID_BUF2_ODD_SET(paritybuf[1]);

	RFID_DATANUM_SET(len);
	
	if(len>31)
	{
	   RFID_TXD_STOP_MODE_ENABLE();		   
	}

    RFID_SEND_ENABLE();		
	state = wait_rfid_tx_complete();
	
	for(i = 2; i < len; i++)
	{  
		 if(i & 0x01)
		 {
		    RFID_BUF2_ODD_SET(paritybuf[i]);
			RFID_BUF2 = buf[i];
		 }
		 else
		 {			    
			RFID_BUF1_ODD_SET(paritybuf[i]);
			RFID_BUF1 = buf[i];
		 }
		      				 
		 state = wait_rfid_tx_complete();
		 			
	}

	if(len>31)
		RFID_TXD_STOP_ENABLE();

	state = wait_rfid_tx_complete();	    


	RFID_SEND_DISABLE();
	RFID_TXD_DATA_SEL(RFID_TXD_DATA_8);

	return state;
}

/*!
    \brief      rfid receive bit
    \param[in]  buf:data pointer
	\param[in]	len:the number of data         
    \param[out] none
    \retval     the number of receive bit or 1
*/
uint8_t rfid_receive_bit(uint8_t *buf,uint8_t len)
{
  uint8_t i,j;
  uint8_t sdat[5];
  uint8_t dat=0;  

  RFID_CMP_ENABLE();//RFID接收比较器工作
  RFID_RX_FULL_CLR();
  RFID_BIT_RXD_MODE_ENABLE();

  delay_us(42);

 
  RFID_RECEIVE_ENABLE();


//第一个起始位去掉	
  sdat[0] = rfid_rx_bit();

  sdat[0] = rfid_rx_bit();
  sdat[1] = rfid_rx_bit();
  sdat[2] = rfid_rx_bit();
  sdat[3] = rfid_rx_bit();
//  rfid_rx_bit();//通信结束

  j=0;
  for(i=0; i<len; i++)    
  {	  
	  if(sdat[i] != 0xff)
	  	dat |= (sdat[i]<<j);
	  else
	  {
		 break;
	  }
	  j++;  
  }
      
  *buf = dat;


  RFID_RECEIVE_DISABLE();
  RFID_BIT_RXD_MODE_DISABLE();  
  RFID_CMP_DISABLE();//RFID接收比较器不工作

  return len;

}

/*!
    \brief      rfid receive data
    \param[in]  buf: receive data buffer
	\param[in]  anti_byte: error byte
	\param[in]  len: the number of receive data
    \param[out] receive data
    \retval     ERROR/SUCCESS/ANTIA_ERROR
*/
uint8_t rfid_receive(uint8_t *buf,uint8_t *anti_byte,uint8_t len)
{
    uint8_t i,ret = ERROR;
	uint16_t count;	

	delay_us(46);

	RFID_CMP_ENABLE();//RFID接收比较器工作
	RFID_BUF2 = 0;
	RFID_BIT_ER = 0;
	RFID_BIT_RXD_MODE_DISABLE();
	RFID_RX_FULL_CLR();
	RFID_RECEIVE_ENABLE();

	for(i = 0; i < len; i++)
	{
	    ret = ERROR;
	    count = WAIT_TIMEOUT_RX;
	    while(count--)
		{		
			if((RFID_CFG & RFID_RX_FULL_FLAG)&&((RFID_CFG&0x80)==0))
			{
				buf[i] = RFID_BUF2;
				RFID_RX_FULL_CLR();
				ret = SUCCESS;
				break;
			}
	    }
	    RFID_RX_ERR_CLR();
	    RFID_RX_PARITY_ERR_CLR();

		if(RFID_BIT_ER)
		{			
			buf[i] = RFID_BUF2;			
			ret = ANTIA_ERROR;//collision happens
			break;
		}

	}

	RFID_RECEIVE_DISABLE();
	RFID_CMP_DISABLE();//RFID接收比较器不工作
    
	if(ret == ANTIA_ERROR)
	{
		*anti_byte = i;
	}
    return ret;	
}

/*!
    \brief      receive data error bit
    \param[in]  none
    \param[out] none
    \retval     err bit
*/
uint8_t rfid_byte_err_bit(void)
{
   	uint8_t i;    
	uint8_t error_bit = RFID_BIT_ER;

	for(i = 0; i < 8;i++)
	{
	   if((error_bit>>i)&0x01)
	     return (i+1);
	}
	return 0;
}
/*!
    \brief      rfid rx
    \param[in]  none
    \param[out] receive data
    \retval     status: ERROR-none ,SUCCESS-receive data
*/
ErrStatus rfid_rx(uint8_t *buf)
{
	uint16_t count = WAIT_TIMEOUT_RX;

	while(count--){		
		if((RFID_CFG & RFID_RX_FULL_FLAG)&&((RFID_CFG&0xA0)==0)){
			*buf = RFID_BUF2;
			RFID_RX_FULL_CLR();
			return SUCCESS;
		}
	}
	RFID_RX_ERR_CLR();
	RFID_RX_PARITY_ERR_CLR();
    return ERROR;	
}

/*!
    \brief      rfid rx	bit
    \param[in]  timeout
    \param[out] none
    \retval     receive data bit
*/
uint8_t rfid_rx_bit(void)
{
    uint8_t temp = 0xff;
	uint16_t count = WAIT_TIMEOUT_RX;
	while(count--)
	{
		if((RFID_CFG & RFID_RX_FULL_FLAG)&&((RFID_CFG&0x80)==0))
		{
			temp = RFID_BUF2;
			RFID_RX_FULL_CLR();
			break;
		}				
	}
	RFID_RX_ERR_CLR();
	
    return temp;	
}

/*!
    \brief      enter_lowpower
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rfid_enter_lowpower_config(void)
{
	RFID_CMP_DISABLE();//RFID接收比较器不工作
	RFID_DISABLE();//RFID关闭       	
}

/*!
    \brief      exit lowpower
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rfid_exit_lowpower_config(void)
{
	RFID_ENABLE();	
}

