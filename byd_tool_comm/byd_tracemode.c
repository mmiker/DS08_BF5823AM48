/*!
    \file  byd_tracemode.c
    \brief tracemode api
*/

/*
    Copyright (C) 2020 BYD

    2020-07-28, V1.0.0, api for tracemode
*/

#include "byd_tracemode.h"
#include "mcu02_system.h"
#include "mcu02_iic.h"
#include "mcu02_gpio.h"
#include "byd_ctk.h"
#include "byd_init.h"

#if TRACEMODE_EN

volatile bit g_bNeedCheckOdd = 0;
volatile bit g_ucOddCheck = 0;

uint8_t xdata g_ucTraceModeReadCnt = 0;
uint8_t xdata g_ucTraceModeDateCnt = 0;
uint8_t xdata g_ucTraceModeCmd = 0;
uint32_t xdata g_ulKeyTouchFlag = 0;
//-----------------------------------------------------------------//
//�������ƣ� void byd_tracemode_init(void)
//�������ܣ� iic��ʼ��
//��������� ��
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------//
void byd_tracemode_init(uint8_t iic_slaveaddr,uint8_t iic_port)
{
	iic_port_select(iic_port);

	if(iic_port==GPIO_PC4_PC5)
	{
	   SET_PC4_PU_ON;//��������
	   SET_PC5_PU_ON;//��������
	   SET_PC4_IO_IN;
	   SET_PC5_IO_IN;	
	}
	else
	{
	   SET_PE4_PU_ON;//��������
	   SET_PE5_PU_ON;//��������
	   SET_PE4_IO_IN;
	   SET_PE5_IO_IN;	
	}

	IIC_ADDR_SET(iic_slaveaddr);
	IICSTAT = 0;
	IICCON |= IIC_SCLEN;

#if IIC_RD_SCL_SEL
	IIC_RD_SCL_SET(SCL_LOCK_RD_DISABLE);
#else
	IIC_RD_SCL_SET(SCL_LOCK_RD_ENABLE);
#endif

	IIC_WR_SCL_SET(SCL_LOCK_WR_DISABLE);
	IIC_SR_SET(IIC_100K);

	INT_IIC_CLR();
	IIC_IPL_SET(HIGH);
	IIC_INT_ENABLE();
	
	IIC_ENABLE();
}
//-----------------------------------------------------------------//
//�������ƣ� void byd_tracemode_read(void)
//�������ܣ� ������
//��������� ��
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------//
void byd_tracemode_read(void)
{
    uint8_t tmp;
	
	if(g_ucTraceModeCmd == 0xb3)
	{
		if(g_ucTraceModeReadCnt<1)
	    {
			tmp = 0xae;
		}
		else if(g_ucTraceModeReadCnt < ((SENSOR_NUM<<1) + 1)) //rawdata
		{
		    g_bNeedCheckOdd = 1;
			
			if(g_ucTraceModeReadCnt & 0x01)	
			{	
				tmp = (rawdata[g_ucTraceModeDateCnt] >> 8);
			}
			else
			{
				tmp = rawdata[g_ucTraceModeDateCnt];
				g_ucTraceModeDateCnt ++;	
			}
		}
		else if(g_ucTraceModeReadCnt==((SENSOR_NUM<<1)+1)) //baseline
		{
		    g_bNeedCheckOdd = 1;
			g_ucTraceModeDateCnt = 0;
			tmp = (baseline[0] >> 8);
		}
		else if(g_ucTraceModeReadCnt < ((SENSOR_NUM << 2) + 1))		//����BASELINE
		{			
			g_bNeedCheckOdd = 1;			
			if(g_ucTraceModeReadCnt & 0x01)	
			{
				tmp = baseline[g_ucTraceModeDateCnt]>>8;
			}
			else
			{
				tmp = baseline[g_ucTraceModeDateCnt]; 
				g_ucTraceModeDateCnt++;	
			}	
		} 
		else if(g_ucTraceModeReadCnt == ((SENSOR_NUM << 2) + 1))		//������żУ��λ
		{
			tmp = g_ucOddCheck;			
		}
		else if(g_ucTraceModeReadCnt == ((SENSOR_NUM << 2) + 2))		//������Ч���ݳ���
		{
			tmp = SENSOR_NUM << 2;
		}
		else if(g_ucTraceModeReadCnt == ((SENSOR_NUM << 2) + 3))		//������־λbit31:24
		{ 						
			tmp = (g_ulKeyTouchFlag >> 24);
		}
		else if(g_ucTraceModeReadCnt == ((SENSOR_NUM << 2) + 4))		//������־λbit23:16
		{						 
			tmp = (g_ulKeyTouchFlag >> 16);		
		}
		else if(g_ucTraceModeReadCnt == ((SENSOR_NUM << 2) + 5))		//������־λbit15:8
		{						
			tmp = (g_ulKeyTouchFlag >> 8);
		}					
		else if(g_ucTraceModeReadCnt == ((SENSOR_NUM << 2) + 6))		//������־λbit7:0
		{						
			tmp = g_ulKeyTouchFlag;	
		}
		else if(g_ucTraceModeReadCnt <= ((SENSOR_NUM << 2) + 10))		//Ԥ��
		{						
			tmp = 0x00;	
		} 		
		else //���ͽ�����0xff��0xff
		{			
//			g_ucTraceModeReadCnt = 0;
			tmp = 0xff;			
		}
#if IIC_RD_SCL_SEL
	    IICBUFFER = tmp;
		if(g_ucTraceModeReadCnt > ((SENSOR_NUM << 2) + 10))
		{
			IICBUFFER = 0xae;
		}
#endif			
	}
	else if(g_ucTraceModeCmd == 0xb2)
	{
	   if(g_ucTraceModeReadCnt==0)
	   {
	       tmp = 0xae;
	   }
	   else
	   {
	       tmp = SENSOR_NUM;
	   }
#if IIC_RD_SCL_SEL
	   IICBUFFER = tmp;		
#endif
	}

#if IIC_RD_SCL_SEL==0
	IICBUF = tmp;
#endif

	if(g_bNeedCheckOdd)		//��ǰ�����Ƿ���Ҫ������żУ��
	{
		g_bNeedCheckOdd = 0;
		
		ACC = tmp;
		if((PSW & 0x01))
			g_ucOddCheck = !g_ucOddCheck;
	}

	g_ucTraceModeReadCnt++;
	 
}
//-----------------------------------------------------------------//
//�������ƣ� void byd_tracemode_write(void)
//�������ܣ� д����
//��������� ��
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------//
void byd_tracemode_write(void)
{
   g_ucTraceModeCmd = IICBUF;

#if IIC_RD_SCL_SEL
//   if(g_ucTraceModeCmd == 0xb2)
//   {
//   		IICBUFFER = 0xff;
//   }
//   else
//   {
//   		IICBUFFER = 0xae;
//   }
   IICBUFFER = 0xae;
#endif    
}
//-----------------------------------------------------------------//
//�������ƣ� void byd_tracemode_isr(void)
//�������ܣ� �жϴ���
//��������� ��
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------//
void byd_tracemode_isr(void)// interrupt 10
{
    uint8_t tmp;

	INT_IIC_CLR();
    
	if(IIC_AD == 0)
	{  
		if(IIC_RW)
		{				
			g_ucOddCheck = 0;		    
			g_ucTraceModeDateCnt = 0;

#if IIC_RD_SCL_SEL
			g_ucTraceModeReadCnt = 1;
#else
			g_ucTraceModeReadCnt = 0;
#endif  		
			byd_tracemode_read();							
		}
		else
		{
			tmp = IICBUF;
		}   
	}
	else 
	{
		if(IIC_RW)
		{			
			byd_tracemode_read();				  
		}
		else 
		{
		    if(IIC_BF)		
			     byd_tracemode_write();
		}
	}
	IICCON |= IIC_SCLEN;/* release scl */
	
	if(IIC_WCOL)
	{
		IICSTAT &= ~0x02;
	}
	if(IIC_RECOV)
	{			
		IICSTAT &= ~0x01;
		tmp = IICBUF;
	}
   
}
#endif
