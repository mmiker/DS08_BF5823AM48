/*!
    \file  byd_ctk.h
    \brief ctk define
*/

/*
    Copyright (C) 2020 BYD

    2020-10-26, V1.0.0, app for byd
*/

#ifndef BYD_CTK_H
#define	BYD_CTK_H

#include "byd_ctk_api.h"
#include "mcu02_csd.h"
#include "mcu02_system.h"

#define SENSOR_NUM             12  /* detect sensor num */
#define SCAN_FILTER_NUM        1  /* detect filter frame */

#define CTK_SCAN_MODE	       1   /* 0:����ɨ��(ɨһ��ͨ������һ��ͨ��);1:����ɨ��(ɨ��һ��ͨ��������һ��ͨ��) */
#define CSD_INT_EN             1   /* 1:interrupt; 0:inquiry */

#if CSD_INT_EN
#define CSD_WAIT_MODE_EN       1   /* 0:csdɨ��ʱ������waitģʽ; 1:csdɨ��ʱ����waitģʽ,csd�жϻ���*/
#else
#define CSD_WAIT_MODE_EN       0   
#endif

#define CTK_RENOVATE_EN        1 /* ʹ�ܻ��߸���*/

#define CTK_FIRST_KEY_EN       1 /* �жϵ�һ�����������İ����±�ʹ��,���簴��4,5,6ͬʱ�д���������5�������ǵ�һ�����������ģ����¼�µ�5���������±� */

#define CTK_MULI_KEY_EN        1 /* 1: �������������д��������ش�����־g_bTouchFlagΪ1; 
                                    0: 1~2�����������������ش�����־g_bTouchFlagΪ1,����2��g_bTouchFlagΪ0*/ 
								 

#define CTK_LONG_TOUCH_HANDLE  0 /* ʹ�ܰ�������ʱ��Ч*/
#define CTK_LONG_TOUCH_FRAME   10000/* ��������������֡��ʱ,������Ч*/

#define CTK_EXCEPTION_MAXCNT   10 /*�ж��쳣����*/

#define CTK_FRAME_MUL_SELT     1 /*֡�ۼ�ѡ��,����Ӧ��ɨ��֡�ۼӴ���(ע��ֻ��ѡ��1��2��3��4)*/
                                 /* 1��һ֡��2����֡�ۼӣ�3����֡�ۼ�, 4����֡�ۼ�			*/
								 
#define CTK_ENTER_WAITMODE()   g_bCtkWaitFlag = 1
#define CTK_EXIT_WAITMODE()    g_bCtkWaitFlag = 0

/* parameter struct */
typedef struct
{
/* csd */	
	uint8_t vth;		    /* vth select */	
	uint8_t ds;			    /* detect speed select */
	uint8_t pre_charge;	    /* pre charge select time us*/
	uint8_t pre_discharge;	/* pre discharge select time us*/
	uint8_t sw_clk_off;		/* enable or disable sw_clk */	
	uint8_t	parallel;	    /* enable or disable sns parallel */
	uint8_t csd_lowpower;	/* enable or disable csd lowpower function */
	uint8_t int_enable;     /* enable or disable csd interrupt function */


/*csd normal mode config */
	uint8_t rb;			    /* rb select */
	uint8_t reso;			/* reso select */
	uint8_t pre_div;		/* pre select */

/*csd parallel mode config */
	uint8_t parallel_rb;		/* parallel_rb select */
	uint8_t parallel_reso;		/* parallel_reso select */
	uint8_t parallel_pre_div;	/* parallel_pre_div select */

	uint8_t sensornum;			          /* detect sensor num */
	uint8_t sensorindex[SENSOR_MAX_NUM];  /* detect sensor index */	
	uint16_t pull_current[SENSOR_MAX_NUM];/* detect sensor current at normal mode*/
	uint16_t parallel_pull_current;       /* detect sensor current at parallel mode*/

/* app */
	uint8_t filterenable;/*enable or disable filter csd data*/
	uint8_t filterframe;/*filter frame*/

	uint8_t abnormal_mul;      /* �쳣��Сֵϵ��,С��(���ֵ*abnormal_mulrate/10)*/		

/* renovate */
	uint8_t renovatemode;   /* renovatemode select 0:normal 1;water*/
    
    uint8_t fthrate; //��ָ��ֵϵ��
	uint8_t nthrate; //������ֵϵ��	

	uint8_t bt_ponth_maxcnt;//���߸���differ>=����������,���»��ߣ�ֵԽС�����߸���Խ��
	uint8_t st_ponth_maxcnt;//���߸���differ<����������,���»��ߣ�ֵԽС�����߸���Խ��
	uint8_t bt_nenth_maxcnt;//���߸���differ>=����������,���»��ߣ�ֵԽС�����߸���Խ��
	uint8_t st_nenth_maxcnt;//���߸���differ<����������,���»��ߣ�ֵԽС�����߸���Խ��	
	
	uint8_t wakeup_bt_ponth_maxcnt;//���߸���differ>=����������,���»��ߣ�ֵԽС�����߸���Խ��
	uint8_t wakeup_st_ponth_maxcnt;//���߸���differ<����������,���»��ߣ�ֵԽС�����߸���Խ��
	uint8_t wakeup_bt_nenth_maxcnt;//���߸���differ>=����������,���»��ߣ�ֵԽС�����߸���Խ��
	uint8_t wakeup_st_nenth_maxcnt;//���߸���differ<����������,���»��ߣ�ֵԽС�����߸���Խ��
	
	uint8_t waterflowrate;	//��ˮ�ж���ֵ����ϵ��	
	uint8_t watermoderate;   //��ˮ��ָ��ֵϵ��

	uint8_t water_base_renomaxcnt;//bak_baseline���߸����жϴ���
	
	uint8_t multikey_maxcnt;	//�ఴ�������жϴ���;    
		
	uint8_t judge_water_maxcnt;      //��ˮ�жϴ���; 
	uint16_t judge_waterleave_maxcnt;//��ˮ�뿪�жϴ���

/*threshold*/
	uint16_t fingerthreshold[SENSOR_MAX_NUM];//����ģʽ��ָ��ֵ
	uint16_t threshold_parallel;	//����ģʽ��ָ��ֵ
	uint16_t finger_latency;//ͨ���д�����,����ֵС��fingerthreshold-finger_latencyʱ��Ϊ̧��
	
	uint8_t  tk_touch_cnt;/* judging the number of finger touch */
	uint8_t  tk_up_cnt;/*judging the number of finger up*/

}byd_parameter_struct;

/* variable declarations */
extern code byd_parameter_struct byd_parameter;

extern bit g_bTouchFlag;
extern volatile bit g_bCtkWaitFlag;
//extern uint8_t xdata csd_sensor_index[];  /* sensor index value */
extern uint16_t xdata csd_pull_current[];/* pull current value */
extern uint16_t xdata bak_baseline[];
extern uint16_t xdata g_uiTempRawdata[];

extern uint8_t xdata g_ucBtPNthCnt[];//���߸���differ>=����������
extern uint8_t xdata g_ucStPNthCnt[];//���߸���differ<����������
extern uint8_t xdata g_ucBtNNthCnt[];//���߸���differ>=����������
extern uint8_t xdata g_ucStNNthCnt[];//���߸���differ<����������
extern uint8_t xdata g_ucWaterBaseRenoCnt[];

extern uint8_t xdata g_ucSenSorTouchFlag[];
extern uint8_t xdata g_ucKeyTouchFlag[];
extern uint8_t xdata g_ucJudgeKeyTouchUpCnt[];
extern uint8_t xdata g_ucJudgeKeyTouchCnt[];

extern uint16_t code CSD_MAXDATA_VALUE[];
extern uint16_t xdata g_uiExceptionCsdMaxValue;
extern uint16_t xdata g_uiExceptionCsdMinValue;

//extern bit g_bRenovateEnable;
extern volatile bit g_csdIntFlag;


extern uint32_t xdata g_ulKeyTouchFlag;

/* function declarations */
void byd_ctk_init(void);
void byd_ctk_normal(void);
void byd_ctk_start(void);
void byd_ctk_work(void);
/* get csd data */
uint16_t get_csd_data(uint8_t sensor_addr,uint16_t pull_current);
uint8_t byd_get_maxkey(void);
void csd_sensor_enable_all(void);

uint8_t byd_get_touch_flag(void);
uint8_t byd_get_touch_index(void);
#endif