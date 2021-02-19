#include "iso14443.h" 
#include "delay.h"
#include <string.h>

/***********************************************************
** �� �� ��: typea_card_send_bit
** ��������: λ����
** ��  ����: inByte����Ҫ���͵����ݻ���
**           lenBit��Ҫ���͵�λ������(lenBit����8)
** ��  ����: ��	
***********************************************************/
#if 1
void typea_card_send_bit(u8 *inByte,u8 lenBit)
{

    u8 i,j,m,n;
    bit bit_last;
    u8 dat;
    u8 allbyte,lastbit;    
	u8 xdata array_bit[170];
	    
    RFID_BIT_TXD_MODE_ENABLE();
    RFID_TXD_STOP_MODE_DISABLE();

    //�������ֽ��������λ����
    allbyte = lenBit>>3;
    lastbit = lenBit&0x07;    
    bit_last = 1;
	j = 1;

	//������ʼλ
    array_bit[0] = send_z();	
    
    for(m=0; m < allbyte+1; m++)
    {
      dat=inByte[m];
      
      if( m < allbyte )
	  { 
	  	n = 8;		
	  }
      else //���һ��λ����            
	  { 
	  	n = lastbit;		 
	  }
      //λ����
      for(;n>0;n--)
      {
        if(dat&1)
        {
          array_bit[j] = send_x();
          bit_last = 0;
        }
        else 
        {
          if(bit_last)    
		  { 
		  	 array_bit[j] = send_z(); 
		  }
          else            
		  { 
		     array_bit[j] = send_y(); 
		  }
          bit_last = 1;
        }
        dat>>=1;
		j++;
      }
	  
    }

	//���ͽ���λ
    if(allbyte > 1)
    {	  
      if(bit_last==1) 
	  {
	  	array_bit[j] = send_z(); 
	  }
      else            
	  {
	    array_bit[j] = send_y();	     
	  }
	  j++;
	  array_bit[j] = send_y();
    }

	RFID_BUF1 = array_bit[0];
	RFID_BUF2 = array_bit[1];
	RFID_SEND_ENABLE();	
	wait_rfid_tx_complete();
	
    for(i = 2; i < j; i++)
    {
		 if(i & 0x01)
		 {
			RFID_BUF2 = array_bit[i];			
		 }
		 else
		 {
			RFID_BUF1 = array_bit[i];			
		 }		 
		           				 
		 wait_rfid_tx_complete();
			
    }

	RFID_TXD_STOP_ENABLE();
	wait_rfid_tx_complete();
	
    RFID_SEND_DISABLE();	
	RFID_BIT_TXD_MODE_DISABLE(); 
}
#else
void typea_card_send_bit(u8 *inByte,u8 lenBit)
{

    u8 m,n;
    bit bit_last,buf_flag=0;        
	u8 temp_bit;
	bit send_flag = 0;
	u8 dat;
    u8 allbyte,lastbit;
	    
    RFID_BIT_TXD_MODE_ENABLE();
    RFID_TXD_STOP_MODE_ENABLE();

    //�������ֽ��������λ����
    allbyte = lenBit>>3;
    lastbit = lenBit&0x07;    
    bit_last = 1;
	
	//������ʼλ
    RFID_BUF1 = send_z();	

    for(m=0; m < allbyte+1; m++)
    {
      dat=inByte[m];
      
      if(m < allbyte)
	  { 
	  	n = 8;		
	  }
      else //���һ��λ����            
	  { 
	  	n = lastbit;		
	  }
      //λ����
      for(;n>0;n--)
      {
        if(dat&1)
        {
          temp_bit = send_x();
          bit_last = 0;
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
	  
    }
	    
    //���ͽ���λ
    if(allbyte > 1)
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

//���������һ��bit�������tx�ж�
	RFID_TXD_STOP_ENABLE();
	delay_us(10);

    RFID_SEND_DISABLE();	
	RFID_BIT_TXD_MODE_DISABLE();
	RFID_TXD_STOP_MODE_DISABLE(); 
}
#endif

#if RFID_ANTI_SEL==0
/***********************************************************
** �� �� ��: u8 typea_card_receive_bit(u8 *inByte,u8 byteBit,u8 len,u8 *anti_info)
** ��������: ��ͻ֡��λ���մ���
** ��  ����: ���ݴ洢ָ��,���յ�һ��������Чbit��byteBit,�ܽ��ո���len,���մ�����Ϣ*anti_info
** ��  ����: ��
** ��    ��: RETURN_NO��RETURN_OK��ANTIA_ERROR
***********************************************************/
u8 typea_card_receive_bit(u8 *inByte,u8 byteBit,u8 len,u8 *anti_info)
{
  u8 i,j,index = 0;
  u8 sdat;
  u8 dat=0;
  u8 error_bit=0xff;
  u8 rec_bytes=0;
  
  RFID_RX_FULL_CLR();
  RFID_BIT_RXD_MODE_ENABLE();
  RFID_RECEIVE_ENABLE();

  if(byteBit)
  {
     index = 1;
  }

//��һ����ʼλȥ��	
  sdat = rfid_rx_bit();
  if(sdat==0xff)return RETURN_NO;

  if(byteBit)
  {
	  for(j = 0; j < byteBit; j++)
	  {
	     sdat = rfid_rx_bit();	
	     if(sdat==1)
		  	dat |= (0x01<<j);

		 if(RFID_BIT_ER&0x01)
		 {
		    error_bit = j;
			rec_bytes = 0;			
			goto endle;
		 }
	  }
	  inByte[0] = dat;
	  rfid_rx_bit();//parity	  
	  inByte++;
  }

  dat = 0;
  for(j = index;j < len;j++)
  {
    //����һ���ֽ�
    for(i = 0; i < 8; i++)    
	{      
       sdat = rfid_rx_bit();

	   if(RFID_BIT_ER&0x01)
	   {
		  error_bit = i;
		  rec_bytes = j;			
		  goto endle;
	   }

       if(sdat!=0xff)
	  	 dat |= (sdat<<i);
       else 
       {
		 *inByte = dat;
         dat = (j<<3)+i;
		 goto endle;
       }      
    }    
    //����һ���ֽ�
    *inByte = dat;
	dat=0;
	rfid_rx_bit();//parity    
	inByte++;
  }

  rfid_rx_bit();//ͨ�Ž���
  
endle:

  RFID_RECEIVE_DISABLE();
  RFID_BIT_RXD_MODE_DISABLE();

  if(error_bit != 0xff)
  {
     anti_info[0] = rec_bytes;
	 anti_info[1] = error_bit+1;
     return ANTIA_ERROR;
  }

  return RETURN_OK;
}
#endif

/***********************************************************
** �� �� ��: u8 piccWakeupA(uint8_t *ATQA)
** ��������: ���ѿ�
** ��  ����: �洢ָ��
** ��  ����: ��
** ��    ��: RETURN_OK��RETURN_NO
***********************************************************/ 
u8 piccWakeupA(uint8_t *ATQA)
{
  	u8 temp[2];  

  	temp[0] = CMD_WUPA;

	if(!rfid_transmit(temp,0))
		return RETURN_NO;	

	if(!rfid_receive(ATQA,temp,2))
	 	return RETURN_NO;

    return RETURN_OK; 
}

/***********************************************************
** �� �� ��: void piccHaltA(void)
** ��������: ��ֹ�Կ�����
** ��  ����: ��           
** ��  ����: ��
** ��    ��: RETURN_OK��RETURN_NO
***********************************************************/
u8 piccHaltA(void)
{
    u8 temp[2];  
//	u16 tlrc;
	 
  	temp[0] = CMD_HLTA;
	temp[1] = 0x00;

//	tlrc = ComputeCrc(CRC_A,temp,2);
//	temp[2] = tlrc;
//	temp[3] = tlrc>>8;

   	if(!rfid_transmit(temp,2))
		return RETURN_NO;	

    return RETURN_OK; 
}
/***********************************************************
** �� �� ��: u8 piccSelectA(u8 SEL,u8 *uid, u8 *SAK)
** ��������: ѡ��
** ��  ����: SELѡ�����У�93H,95H,97H           
** ��  ����: ��
** ��    ��: RETURN_OK��RETURN_NO
***********************************************************/
u8 piccSelectA(u8 SEL,u8 *uid,u8 *SAK,u8 len)
{
    u8 i,ret,card_temp[12];
	u16 tlrc;

    card_temp[0] = SEL;
    card_temp[1] = 0x70;

	for(i = 0; i < len; i++)
	{
      card_temp[2+i] = uid[i];//�ӿ���    
	}
    tlrc = ComputeCrc(CRC_A,card_temp,2+len);
    card_temp[2+len]=(u8)tlrc;
    card_temp[3+len]=(u16)tlrc>>8;

	ret = rfid_transmit(card_temp,len+4);
    if(ret!=SUCCESS)return RETURN_NO;    

	ret = rfid_receive(SAK,card_temp,3);
	if(ret!=SUCCESS)
	{
	 	return RETURN_NO;
	}
	    
	return RETURN_OK;
}

/***********************************************************
** �� �� ��: u8 piccAntiA(uint8_t SEL, uint8_t rand_bit, uint8_t *uid)
** ��������: type A������ͻѭ��
** ��  ����: SELѡ�����У�93H,95H,97H
**           randBit λ��ͻʱѡ�����,0��1;
**           uid:�洢ָ��            
** ��  ����: ��
** ��    ��: RETURN_OK��RETURN_NO
***********************************************************/
u8 piccAntiA(u8 SEL, u8 rand_bit, u8 *uid)
{	
    u8 i,ret;
    u8 recUID[10]={0,0,0,0,0};	
	u8 tmpBuf[10];
	u8 recBytes;

#if RFID_ANTI_HANDLE
	u8 currValidBytes=0, currValidBits=0;
    u8 recBits;	
    u8 j,NVB;
	u8 temp[2]={0,0};
#endif

#if RFID_ANTI_SEL && RFID_ANTI_HANDLE
	if(SEL != CMD_CL1)return RETURN_NO;/*Ӳ����Ʒ���ͻֻ֧֡��SEL = 0x93*/
#endif

    /* STEP 1: send SEL + 20H to PICC */
    tmpBuf[0] = SEL;
    tmpBuf[1] = 0x20;

#if RFID_ANTI_SEL && RFID_ANTI_HANDLE    
	RFID_ANTIC_NVB_SET(0x20);
	RFID_ANTIC_ENABLE();
#endif

  	ret = rfid_transmit(tmpBuf,2);
	if(ret!=SUCCESS)return RETURN_NO;	

    ret = rfid_receive(tmpBuf,&recBytes,5);/*recBytes=0~4��¼�ڼ���byte������ͻ*/
	if(SUCCESS == ret)
	{
	   for(i = 0;i < 5;i++)
         uid[i] = tmpBuf[i];

#if RFID_ANTI_SEL && RFID_ANTI_HANDLE	   
    	RFID_ANTIC_DISABLE();
#endif
	   return RETURN_OK;
	}
	else if(ERROR == ret)
	{
#if RFID_ANTI_SEL && RFID_ANTI_HANDLE	   
       RFID_ANTIC_DISABLE();
#endif
	   return RETURN_NO;
	}
#if RFID_ANTI_HANDLE
	else  /*��һ�η�����ͻ*/
	{
	   recBits = rfid_byte_err_bit();/*��Ƿ�����ͻʱ���ݵĵڼ���bit����,recBits=1~8,����bit0~bit7*/

	   for(i = 0; i < recBytes; i++)
	   {
	   	  recUID[i] = tmpBuf[i];
	   }
	   
//	   tmpBuf[recBytes] &= ~(0x01<<(recBits-1));//�ѳ����bitλ��Ϊ0	
	   recUID[recBytes] = tmpBuf[recBytes]&BITS(recBits);//������Ч����λ
	   
	   recUID[recBytes] |= (rand_bit<<(recBits-1));//��ͻλ����rand_bit

	   currValidBytes = recBytes;//0~4
	   currValidBits = recBits;//1~8
	   
	} 

    while(1)
	{		          
    	WDT_CTRL = 7;
    			
		if(currValidBits)
		   j = 1;
		else
		   j = 0;
		       
        /* �����µ�NVB��������ǰUID+rand_bit���͸�PICC */
        NVB = 0x20+((currValidBytes<<4) | currValidBits);

#if RFID_ANTI_SEL    
		RFID_ANTIC_NVB_SET(NVB);
#endif		
        tmpBuf[0] = SEL;
        tmpBuf[1] = NVB;

        for(i=0;i<currValidBytes+j;i++)
		{
            tmpBuf[2+i] = recUID[i];
        }

#if RFID_ANTI_SEL==0
		rfid_transmit_bit(tmpBuf,((currValidBytes+2)<<3)+currValidBits);
#else
		rfid_transmit(tmpBuf,currValidBytes+2+j);
#endif
		

#if RFID_ANTI_SEL==0
		ret = typea_card_receive_bit(tmpBuf,8-currValidBits,5-currValidBytes,temp);
#else
		ret = rfid_receive(tmpBuf,&recBytes,5-currValidBytes);
#endif

		if(ret == ANTIA_ERROR)
		{
#if RFID_ANTI_SEL==0
		    recBytes = temp[0];
			recBits = temp[1]; 
#else
			recBits = rfid_byte_err_bit();				
#endif
			if(recBytes==0)	//�������ֽ�			
			{
//			    tmpBuf[0] &= ~(0x01<<(recBits-1));
				recUID[currValidBytes] |= ((tmpBuf[0]&BITS(recBits) )<<currValidBits);//��λƴ�ӵ�һ���ֽ�
				currValidBits += recBits;
				recUID[currValidBytes] |= (rand_bit<<(currValidBits-1));
				if(currValidBits==8)
				{					   
				   currValidBits = 0;
				   currValidBytes++;
				}
			}
			else  //�������ֽ�
			{				    
			    recUID[currValidBytes] |= ((tmpBuf[0]&(0xFF >> (currValidBits)))<<currValidBits);//��λƴ�ӵ�һ���ֽ�
				currValidBytes++;

				for(i = 1; i < recBytes; i++)
			    {
			   	   recUID[currValidBytes++] = tmpBuf[i];
			    }

//				tmpBuf[recBytes] &= ~(0x01<<(recBits-1));//�ѳ����bitλ��Ϊ0
				recUID[currValidBytes] = tmpBuf[recBytes]&BITS(recBits);				

				recUID[currValidBytes] |= (rand_bit<<(recBits-1));

				currValidBits = recBits;
			}
			
		}
		else if(ret == SUCCESS)
		{	
			recBytes = 5-currValidBytes;

		    recUID[currValidBytes] |= ((tmpBuf[0]&(0xFF >> (currValidBits)))<<currValidBits);//��λƴ�ӵ�һ���ֽ�			    
			currValidBytes++;
							
			for(i = 1; i < recBytes; i++)
		    {
		   	   recUID[currValidBytes++] = tmpBuf[i];
		    }
			break;				
		}
		else
		{
		    //һֱδ��PICC��Ӧ
			//rand_bit = !rand_bit;
#if RFID_ANTI_SEL	   
    		RFID_ANTIC_DISABLE();
#endif
			return RETURN_NO;
		}

    }

#if RFID_ANTI_SEL	   
    RFID_ANTIC_DISABLE();
#endif

	memcpy(uid,recUID,5);

#endif
    return RETURN_OK;
}

/***********************************************************
** �� �� ��: u8 get_card_number(u8 *uid)
** ��������: ��ȡ����
** ��  ����: uid:�洢ָ��,����12byte����            
** ��  ����: ��
** ��    ��: RETURN_OK��RETURN_NO
***********************************************************/
u8 get_card_number(u8 *uid)
{
   u8 tmpbuf[6]={0};
   u8 ret;
   u8 card_type;

   RFID_TXD_STOP_MODE_DISABLE();

   if(RETURN_OK != piccWakeupA(tmpbuf))
   		return RETURN_NO;
   
   card_type = 3 * ( ( tmpbuf[0] & 0xC0 ) >> 6 ) + 4;/*��ƬID����,���ֽڼ�*/
   if( ( 4 != card_type ) ){ return RETURN_NO; }
    
   ret = piccAntiA(CMD_CL1,1,tmpbuf);
   if(ret != RETURN_OK)return RETURN_NO;

   memcpy(uid,tmpbuf,5);
	  
   ret = piccSelectA(CMD_CL1,uid,tmpbuf,5);
   if(ret != RETURN_OK)return RETURN_NO;
	
   if((tmpbuf[0] & 0x24) == 0x00)
   {
      return RETURN_OK;//M1��
   }

   return RETURN_NO;
}

