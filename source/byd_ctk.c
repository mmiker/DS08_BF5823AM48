/*!
    \file  byd_ctk.c
    \brief ctk app
*/

/*
    Copyright (C) 2020 BYD

    2020-10-28, V1.0.0, app for byd
*/

#include "byd_ctk.h"
#include "byd_init.h"
#include "byd_idle.h"
#include "delay.h"
#include "dq_project.h"

/*don't modify*/
/*-----------------------------------------------------------------------------------*/
bit g_bTouchFlag = 0;/*the touch state of key,1: touch ;0: no touch*/
volatile bit g_bCtkWaitFlag = 0;
bit g_bExceptionFlag = 0;

#if CSD_INT_EN
volatile bit g_csdIntFlag = 0;
#endif

//uint8_t xdata csd_sensor_index[SENSOR_NUM];  /* sensor index value */
uint16_t xdata csd_pull_current[SENSOR_NUM];/* pull current value */
uint16_t xdata bak_baseline[SENSOR_NUM];	/* backup baseline */
uint16_t xdata rawdata[SENSOR_NUM];
uint16_t xdata baseline[SENSOR_NUM];
#if CTK_FRAME_MUL_SELT>1
uint16_t rawdata2[SENSOR_NUM];
#endif
#if CTK_FRAME_MUL_SELT >= 3
uint16_t rawdata3[SENSOR_NUM];
#endif
#if CTK_FRAME_MUL_SELT == 4
uint16_t rawdata4[SENSOR_NUM];
#endif

uint8_t xdata g_ucBtPNthCnt[SENSOR_NUM];//���߸���differ>=����������
uint8_t xdata g_ucStPNthCnt[SENSOR_NUM];//���߸���differ<����������
uint8_t xdata g_ucBtNNthCnt[SENSOR_NUM];//���߸���differ>=����������
uint8_t xdata g_ucStNNthCnt[SENSOR_NUM];//���߸���differ<����������
uint8_t xdata g_ucWaterBaseRenoCnt[SENSOR_NUM];

uint8_t xdata g_ucJudgeKeyTouchUpCnt[SENSOR_NUM];
uint8_t xdata g_ucJudgeKeyTouchCnt[SENSOR_NUM];
uint8_t xdata g_ucSenSorTouchFlag[SENSOR_NUM];
uint8_t xdata g_ucKeyTouchFlag[SENSOR_NUM];/*the touch state of each key,1: touch ;0: no touch*/
#if CTK_FIRST_KEY_EN
uint8_t xdata g_ucFirstTouchKeyIndex;//��ǰ��һ���������İ���ͨ���±꣬0xff������Ч��0~SENSOR_NUM��Ч
#endif

uint8_t xdata g_ucExceptionCnt = 0;
uint16_t xdata g_uiExceptionCsdMaxValue;
uint16_t xdata g_uiExceptionCsdMinValue;

#if CTK_LONG_TOUCH_HANDLE
uint16_t xdata g_uiTouchFrame = 0;
#endif

/*-----------------------------------------------------------------------------------*/

code byd_parameter_struct byd_parameter={

/* csd */    
	VTH_2,               //uint8_t vth;		        /* vth select,notice��VCC-VTH>0.5V*/
	DS_24M,              //uint8_t ds;			    /* detect speed select */
	PRE_CHARGE_20us,     //uint8_t pre_charge;	    /* pre charge select time us*/
	PRE_DISCHARGE_2us,  //uint8_t pre_discharge;	/* pre discharge select time us*/
	CSD_SW_CLK_ON,       //uint8_t sw_clk_off;		/* enable or disable sw_clk */	
	CSD_PARALLEL_DISABLE,//uint8_t parallel;	    /* enable or disable sns parallel */
	CSD_LOWPOWER_ENABLE, //uint8_t csd_lowpower     /* enable or disable csd lowpower function */
	CSD_INT_EN,          //uint8_t int_enable       /* enable or disable csd interrupt function */
	

/*csd normal mode config */	
	RB_200K,//uint8_t rb;			    /* rb select */
#if CTK_FRAME_MUL_SELT>1
	RESO_1024,//uint8_t reso;			/* reso select */
#else
	RESO_2048,//uint8_t reso;			/* reso select */
#endif
	SW_CLK_2,//uint8_t pre_div;/* pre select,csd�͹���ģʽ����������ģʽ����Ӧ��ǰ��Ƶ���ǲ�һ����,�ɲ���csd_lowpowerֵ���������忴CSD_PREDIV_enum*/

/*csd parallel mode config */
	RB_200K,   //uint8_t parallel_rb;		/* parallel_rb select */
	RESO_16384,//uint8_t parallel_reso;		/* parallel_reso select */
	SW_CLK_18,//uint8_t parallel_pre_div;	/* parallel_pre_div select */

	SENSOR_NUM,//uint8_t sensornum;			/* detect sensor num */
#ifdef __DQ_PROJECT_DS08__
	{		
		27,21,20,47,46,45,
		44,43,42,7,40,39,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,
		0,0,0,0,0,0		
	},//uint8_t sensorindex[SENSOR_MAX_NUM];/* detect sensor index */
#else
	{		
		47,46,45,44,43,42,
		7,6,41,40,39,27,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,
		0,0,0,0,0,0		
	},//uint8_t sensorindex[SENSOR_MAX_NUM];/* detect sensor index */
#endif
	{
	 300,300,300,300,300,300,300,300,
	 300,300,300,300,300,300,300,300,
	 300,300,300,300,300,300,300,300,
	 300,300,300,300,300,300,300,300
	},//uint16_t pull_current[SENSOR_MAX_NUM];/* detect sensor current at normal mode*/

	300,//uint16_t parallel_pull_current;       /* detect sensor current at parallel mode*/

	0,//uint8_t filterenable;//�ù����ѹر�,������Ч
	SCAN_FILTER_NUM,//uint8_t filterframe;//�ù����ѹر�,������Ч

	2,//uint8_t abnormal_mul;      /*�иǰ���2,�޸ǰ���0; �쳣��Сֵϵ��,С��(���ֵ*abnormal_mulrate/10)���߸�λ*/			

	0,//uint8_t renovatemode;   /* renovatemode select 0:normal 1;water*/
	
	11,//uint8_t fthrate; //��ָ��ֵϵ��,��ָ��ֵ=(fingerthreshold*fthrate)>>4,������Ч
	7,//uint8_t nthrate; //������ֵϵ��,������ֵ=(fingerthreshold*nthrate)>>4	

//����ȫ����ʱ�Ļ��߸����ٶ�
	30,//uint8_t bt_ponth_maxcnt;//���߸���differ>=����������,���»��ߣ�ֵԽС�����߸���Խ��
	20,//uint8_t st_ponth_maxcnt;//���߸���differ<����������,���»��ߣ�ֵԽС�����߸���Խ��
	10,//uint8_t bt_nenth_maxcnt;//���߸���differ>=����������,���»��ߣ�ֵԽС�����߸���Խ��
	20,//uint8_t st_nenth_maxcnt;//���߸���differ<����������,���»��ߣ�ֵԽС�����߸���Խ��	
	
//����֡Ƶ��ʱ�Ļ��߸����ٶ�	
	6,//uint8_t wakeup_bt_ponth_maxcnt;//���߸���differ>=����������,���»��ߣ�ֵԽС�����߸���Խ��
	3,//uint8_t wakeup_st_ponth_maxcnt;//���߸���differ<����������,���»��ߣ�ֵԽС�����߸���Խ��
	2,//uint8_t wakeup_bt_nenth_maxcnt;//���߸���differ>=����������,���»��ߣ�ֵԽС�����߸���Խ��
	3,//uint8_t wakeup_st_nenth_maxcnt;//���߸���differ<����������,���»��ߣ�ֵԽС�����߸���Խ��	
	
	8,//uint8_t waterflowrate;	//��ˮ�ж���ֵ����ϵ��	
	8,//uint8_t watermoderate;  //��ˮ��ָ��ֵϵ��

	50,//uint8_t water_base_renomaxcnt;//bak_baseline���߸����жϴ���
	
	2,//uint8_t multikey_maxcnt;	//�ఴ�������жϴ���;
    
	3,//uint8_t judge_water_maxcnt;      //��ˮ�ж�ͨ������;

	30,//uint16_t judge_waterleave_maxcnt;//��ˮ�뿪�жϴ���
		
	{
	#if 0
	 900,900,900,900,900,900,900,900,
	 900,900,900,900,900,900,900,900,
	 800,800,800,800,800,800,800,800,
	 800,800,800,800,800,800,800,800,
	#else
	 150,150,150,150,150,150,150,150,
	 150,150,150,150,150,150,150,150,
	 150,150,150,150,150,150,150,150,
	 150,150,150,150,150,150,150,150,
	#endif
	},//int16_t	fingerthreshold[SENSOR_MAX_NUM];

/*
	{
	 55,55,55,55,55,55,55,55,
	 55,55,55,55,55,55,55,55,
	 55,55,55,55,55,55,55,55,
	 55,55,55,55,55,55,55,55,
	},//int16_t	fingerthreshold[SENSOR_MAX_NUM];
*/    
	150,//uint16_t threshold_parallel;//����ģʽ����ֵ
	10,//uint16_t finger_latency;//ͨ���д�����,����ֵС��fingerthreshold-finger_latencyʱ��Ϊ̧��
	
	0,/*judging the number of finger touch*/
	0,/*judging the number of finger up*/
};

/*!
    \brief      tk current adjust init
    \param[in]  csd scan mode
					1: parallel mode
					0: normal mode
    \param[out] none
    \retval     none
*/
void byd_adjust_init(bit csd_scanmode)
{
    uint8_t i;
    uint16_t value;

	g_bTouchFlag = 0;

	if(!csd_scanmode)
	{
		if(byd_parameter.reso==0)
		{
			value = CSD_MAXDATA_VALUE[0]>>1;
		}
		else
		{
			value = CSD_MAXDATA_VALUE[byd_parameter.reso-1];//(uint32_t)0x0001 << (byd_parameter.reso + 8);
		}

		for(i = 0; i < SENSOR_NUM; i++)
		{
			g_ucKeyTouchFlag[i] = 0;		
			byd_cts_adjust(i,0,value);
		}
	}
	else
	{
		if(byd_parameter.parallel_reso==0)
		{
			value = CSD_MAXDATA_VALUE[0]>>1;
		}
		else
		{
			value = CSD_MAXDATA_VALUE[byd_parameter.parallel_reso-1];//(uint32_t)0x0001 << (byd_parameter.parallel_reso + 8);
		}
		byd_cts_adjust(0,1,value);		
	}

#if TRACEMODE_EN
	g_ulKeyTouchFlag = 0;
#endif
#if CTK_FIRST_KEY_EN    
	g_ucFirstTouchKeyIndex = 0xff;
#endif
}

/*!
    \brief      ctk frame acc
    \param[in]  none
    \param[out] none
    \retval     none
*/
#if CTK_FRAME_MUL_SELT>1
void byd_ctk_frame_acc(void)
{
	uint8_t i;
	for(i = 0; i < SENSOR_NUM; i++)
	{
#if CTK_FRAME_MUL_SELT == 2
	    rawdata2[i] = rawdata[i];
		baseline[i] = rawdata[i]+rawdata[i];
#endif
		
#if CTK_FRAME_MUL_SELT == 3
		rawdata2[i] = rawdata[i];
		rawdata3[i] = rawdata[i];
		baseline[i] = rawdata[i]+rawdata[i]+rawdata[i];
#endif
		
#if CTK_FRAME_MUL_SELT == 4
		rawdata2[i] = rawdata[i];
		rawdata3[i] = rawdata[i];
		rawdata4[i] = rawdata[i];
		baseline[i] = (rawdata[i]<<2);
#endif
	    
		rawdata[i] = baseline[i];        
	}
}
#endif

/*!
    \brief      ctk init
    \param[in]  none
    \param[out] none
    \retval     none
*/
void byd_ctk_init(void)
{
	byd_key_init();//tk init
		
//	if(!g_bCsdFilterEnable)
//	{
//		byd_adjust_init(0);//normal mode:tk current adjust
//	}
//	else
//	{
//		g_bCsdFilterEnable= 0;//close scan filter handle
//		byd_adjust_init(0);//normal mode:tk current adjust
//		g_bCsdFilterEnable = 1;//open scan filter handle
//		byd_adjust_init(0);//normal mode:tk current adjust
//	}

	byd_adjust_init(0);//normal mode:tk current adjust

	g_uiExceptionCsdMaxValue = ((uint32_t)CSD_MAXDATA_VALUE[byd_parameter.reso]<<3)/10;
    g_uiExceptionCsdMinValue = ((uint32_t)CSD_MAXDATA_VALUE[byd_parameter.reso]*byd_parameter.abnormal_mul)/10;

#if CTK_FRAME_MUL_SELT>1
    byd_ctk_frame_acc();
	g_uiExceptionCsdMaxValue = g_uiExceptionCsdMaxValue*CTK_FRAME_MUL_SELT;
	g_uiExceptionCsdMinValue = g_uiExceptionCsdMinValue*CTK_FRAME_MUL_SELT;
#endif
}
/*!
    \brief      start csd scan
    \param[in]  none
    \param[out] none
    \retval     none
*/
void byd_ctk_start(void)
{
	CSD_SCAN_STOP;

#if CSD_INT_EN
	g_csdIntFlag = 0;
#endif

	INT_CSD_CLR();

	CSD_PULL_I_SET(csd_pull_current[0]);
    CSD_SCANADDR_SET(byd_parameter.sensorindex[0]);
	CSD_SCAN_EN;
}
/*!
    \brief      get_csd_data
    \param[in]	sensor_addr:0~11,16~47
				pull_current:0~0x1ff
    \param[out] none
    \retval     csd data
*/
uint16_t get_csd_data(uint8_t sensor_addr,uint16_t pull_current)
{

	CSD_PULL_I_SET(pull_current);
    CSD_SCANADDR_SET(sensor_addr);		

#if CSD_INT_EN

	g_csdIntFlag = 0;

    CSD_SCAN_EN;

#if TRACEMODE_EN==0 && CSD_WAIT_MODE_EN
	if(g_bCtkWaitFlag)
		SYS_CLK_CFG |= 0x10;//wait mode
#endif
	
	while(!g_csdIntFlag)
	{
	   WDT_CTRL = 7;
	}

#else

	CSD_SCAN_EN;
	while((IRCON1 & 0x20) == 0)
	{
	   WDT_CTRL = 7;
	}
	INT_CSD_CLR();
	
#endif

	return (((uint16_t)CSD_RAWDATAH << 8)|(uint16_t)CSD_RAWDATAL);
}

/*!
    \brief      csd isr
    \param[in]  none
    \param[out] none
    \retval     none
*/
#if CSD_INT_EN
void csd_isr(void) interrupt 12
{
	INT_CSD_CLR();
	g_csdIntFlag = 1;
}
#endif
/*!
    \brief      key exception handling
    \param[in]  sensor(0..31)
    \param[out] none
    \retval     none
*/
void byd_exception_handle(uint8_t sensor)
{
    g_bExceptionFlag = 0;

	if((rawdata[sensor]>=g_uiExceptionCsdMaxValue)
	   ||(rawdata[sensor]<g_uiExceptionCsdMinValue)
	  )
	{
		g_ucExceptionCnt++;
		if(g_ucExceptionCnt >= CTK_EXCEPTION_MAXCNT)
		{
			g_ucExceptionCnt = 0;
			g_bExceptionFlag = 1;

#if CTK_SCAN_MODE

			CSD_SCAN_STOP;
			INT_CSD_CLR();
#if CSD_INT_EN
			g_csdIntFlag = 0;
#endif
#endif
			g_bTouchFlag = 0;
#if CTK_FIRST_KEY_EN    
			g_ucFirstTouchKeyIndex = 0xff;
#endif
#if CTK_LONG_TOUCH_HANDLE
			g_uiTouchFrame = 0;
#endif
			
			byd_setbaseline(0);
#if CTK_FRAME_MUL_SELT>1
    		byd_ctk_frame_acc();
#endif
		}
	}
}
/*!
    \brief      get the maxkey index when touch
    \param[in]  none
    \param[out] none
    \retval     none
*/
uint8_t byd_get_maxkey(void)
{
	uint8_t i,index = 0;
	int differ,max_differ=0;
	
//	max_differ = (int)baseline[0] - (int)rawdata[0];

	for(i = 0; i < SENSOR_NUM;i++)
	{
		if(g_ucKeyTouchFlag[i])
		{
		    differ = baseline[i] - rawdata[i];
			if(differ >= max_differ)
			{
				max_differ = differ;
				index = i;
			}
		}
	}
#if CTK_FIRST_KEY_EN
	if(g_ucFirstTouchKeyIndex != index)//����ʱ����
	{
	   differ = (int)baseline[g_ucFirstTouchKeyIndex] - (int)rawdata[g_ucFirstTouchKeyIndex];
	   differ = max_differ - differ;
	   if(differ > (int)byd_parameter.fingerthreshold[index])
	   {
	      g_ucFirstTouchKeyIndex = index;
	   } 
	}
#endif
	return index;
}

/*!
    \brief      enable all csd sensor
    \param[in]  none
    \param[out] none
    \retval     none
*/
void csd_sensor_enable_all(void)
{
   uint8_t i;
   for(i = 0; i < SENSOR_NUM; i++)
   { 
	  csd_sensor_enable(byd_parameter.sensorindex[i]);	   
   }
}

/*!
    \brief      get the touchkey state at ctk normal mode
    \param[in]  none
    \param[out] none
    \retval     none
*/
void byd_ctk_normal(void)
{
    uint8_t i,n = 0;

#if CTK_FRAME_MUL_SELT>1
	uint16_t temp_rawdata;
#endif
	
	g_bTouchFlag = 0;

#if CTK_SCAN_MODE

	byd_ctk_start();

	for(i = 0; i < SENSOR_NUM;i++)
	{	
#if CSD_INT_EN

#if TRACEMODE_EN==0 && CSD_WAIT_MODE_EN
		if(g_bCtkWaitFlag)
			SYS_CLK_CFG |= 0x10;//wait mode
#endif
		while(!g_csdIntFlag)		
		{
		   WDT_CTRL = 7;
		}
		g_csdIntFlag = 0;
#else	
		while((IRCON1 & 0x20) == 0)
		{
		   WDT_CTRL = 7;
		}
		INT_CSD_CLR();		
#endif

#if CTK_FRAME_MUL_SELT == 1		
		rawdata[i] = (((uint16_t)CSD_RAWDATAH << 8)|(uint16_t)CSD_RAWDATAL);
#endif

#if CTK_FRAME_MUL_SELT == 2	    
						    
	    temp_rawdata = rawdata2[i];
	    rawdata2[i]  = (((uint16_t)CSD_RAWDATAH << 8)|(uint16_t)CSD_RAWDATAL);					
		rawdata[i] = temp_rawdata+rawdata2[i];
		
#endif
	
#if CTK_FRAME_MUL_SELT == 3
	    				    
		temp_rawdata = rawdata3[i]+rawdata2[i]; 
		rawdata3[i] = rawdata2[i];				    
	    rawdata2[i]  = (((uint16_t)CSD_RAWDATAH << 8)|(uint16_t)CSD_RAWDATAL);					
		rawdata[i] = temp_rawdata + rawdata2[i];

#endif
			
#if CTK_FRAME_MUL_SELT == 4
				    
		temp_rawdata = rawdata4[i]+rawdata3[i]+rawdata2[i]; 
		rawdata4[i] = rawdata3[i];
		rawdata3[i] = rawdata2[i];
	    rawdata2[i]  = (((uint16_t)CSD_RAWDATAH << 8)|(uint16_t)CSD_RAWDATAL);		
		rawdata[i] = temp_rawdata + rawdata2[i];

#endif
							
		if(i < SENSOR_NUM-1)//ɨ����һ��ͨ��
		{	
			CSD_PULL_I_SET(csd_pull_current[i+1]);
	    	CSD_SCANADDR_SET(byd_parameter.sensorindex[i+1]);//csd_sensor_index[i]
			CSD_SCAN_EN;
		}

#if CTK_RENOVATE_EN
		byd_renovate(i);
#endif

		byd_get_keytouch(i);
		byd_exception_handle(i);

#if CTK_FIRST_KEY_EN
		if((g_bTouchFlag)&&(g_ucFirstTouchKeyIndex==0xff))
		   g_ucFirstTouchKeyIndex = i;
#endif
		if(g_bExceptionFlag)return;     
	}

#else //////////////////����

	for(i = 0; i < SENSOR_NUM;i++)
	{
#if CTK_FRAME_MUL_SELT == 1
		rawdata[i] = get_csd_data(byd_parameter.sensorindex[i],csd_pull_current[i]);
#endif
		
#if CTK_FRAME_MUL_SELT == 2	    
						    
	    temp_rawdata = rawdata2[i];
	    rawdata2[i]  = get_csd_data(byd_parameter.sensorindex[i],csd_pull_current[i]);					
		rawdata[i] = temp_rawdata+rawdata2[i];
		
#endif
	
#if CTK_FRAME_MUL_SELT == 3
	    				    
		temp_rawdata = rawdata3[i]+rawdata2[i]; 
		rawdata3[i] = rawdata2[i];				    
	    rawdata2[i]  = get_csd_data(byd_parameter.sensorindex[i],csd_pull_current[i]);					
		rawdata[i] = temp_rawdata + rawdata2[i];

#endif
			
#if CTK_FRAME_MUL_SELT == 4
				    
		temp_rawdata = rawdata4[i]+rawdata3[i]+rawdata2[i]; 
		rawdata4[i] = rawdata3[i];
		rawdata3[i] = rawdata2[i];
	    rawdata2[i]  = get_csd_data(byd_parameter.sensorindex[i],csd_pull_current[i]);		
		rawdata[i] = temp_rawdata + rawdata2[i];

#endif

#if CTK_RENOVATE_EN	
		byd_renovate(i);
#endif

		byd_get_keytouch(i);

		byd_exception_handle(i);
#if CTK_FIRST_KEY_EN
		if((g_bTouchFlag)&&(g_ucFirstTouchKeyIndex==0xff))
		   g_ucFirstTouchKeyIndex = i;
#endif
		if(g_bExceptionFlag)return;
	}

#endif //CTK_SCAN_MODE


#if CTK_FIRST_KEY_EN
    if(!g_bTouchFlag)
		g_ucFirstTouchKeyIndex = 0xff;
#endif

#if CTK_MULI_KEY_EN==0 || CTK_LONG_TOUCH_HANDLE

    if(g_bTouchFlag)
	{
#if CTK_MULI_KEY_EN==0
		for(i = 0; i < SENSOR_NUM;i++)
		{
		   if(g_ucKeyTouchFlag[i])
		   {
		      n++;
			  if(n>=3)
			  {
			    g_bTouchFlag = 0;
			    break;
			  }
		   }
		}
#endif
#if CTK_LONG_TOUCH_HANDLE
	    g_uiTouchFrame++;
		if(g_uiTouchFrame >= CTK_LONG_TOUCH_FRAME)
	    {
		    g_uiTouchFrame = 0;
			g_bTouchFlag = 0;
			for(i = 0; i < SENSOR_NUM; i++)
			{	     	               
				baseline[i] = rawdata[i];
				g_ucKeyTouchFlag[i] = 0;
			}
		}
#endif		
	}
#if CTK_LONG_TOUCH_HANDLE
	else
	{
		g_uiTouchFrame = 0;
	}
#endif
#endif
	
} 

/*!
    \brief      ctk work example
    \param[in]  none
    \param[out] none
    \retval     none
*/
void byd_ctk_work(void)
{	
	uint8_t i;

#if TRACEMODE_EN
	if(IIC_START)return;
#endif
  
	byd_ctk_normal();			

	if(g_bTouchFlag)//tk touch
	{
		i = byd_get_maxkey();

		for(i = 0; i < SENSOR_NUM;i++)
	    {
#if CTK_FIRST_KEY_EN
			if(g_ucFirstTouchKeyIndex == i)//g_ucFirstTouchKeyIndex=0~11,����������1~12
			{
				
			}
#else			
			if(g_ucKeyTouchFlag[i])//�ж��ĸ������д���,����Ϊ1
			{
				 
			}
#endif
#if TRACEMODE_EN
			if(g_ucKeyTouchFlag[i])	
				g_ulKeyTouchFlag |= ((uint32_t)g_ucKeyTouchFlag[i] << i);
			else
			    g_ulKeyTouchFlag &= ~(1 << i);
#endif
	    }		 
		  
	}
	else  //tk up
	{	   

#if TRACEMODE_EN
		 g_ulKeyTouchFlag = 0;
#else
		 	
//		 byd_idlemode();//��������,ʹ��timer2����		 
  
#endif
	}
       	
}

uint8_t byd_get_touch_flag(void)
{
	return g_bTouchFlag;
}

uint8_t byd_get_touch_index(void)
{
	return g_ucFirstTouchKeyIndex;
}

