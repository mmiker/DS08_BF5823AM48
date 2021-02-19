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

#define CTK_SCAN_MODE	       1   /* 0:串行扫描(扫一个通道处理一个通道);1:并行扫描(扫下一个通道处理上一个通道) */
#define CSD_INT_EN             1   /* 1:interrupt; 0:inquiry */

#if CSD_INT_EN
#define CSD_WAIT_MODE_EN       1   /* 0:csd扫描时不进入wait模式; 1:csd扫描时进入wait模式,csd中断唤醒*/
#else
#define CSD_WAIT_MODE_EN       0   
#endif

#define CTK_RENOVATE_EN        1 /* 使能基线更新*/

#define CTK_FIRST_KEY_EN       1 /* 判断第一个被触摸到的按键下标使能,例如按键4,5,6同时有触摸，但第5个按键是第一个被触摸到的，则记录下第5个按键的下标 */

#define CTK_MULI_KEY_EN        1 /* 1: 任意数量按键有触摸，返回触摸标志g_bTouchFlag为1; 
                                    0: 1~2个按键被触摸，返回触摸标志g_bTouchFlag为1,超过2个g_bTouchFlag为0*/ 
								 

#define CTK_LONG_TOUCH_HANDLE  0 /* 使能按键长按时无效*/
#define CTK_LONG_TOUCH_FRAME   10000/* 按键长按超过该帧数时,触摸无效*/

#define CTK_EXCEPTION_MAXCNT   10 /*判断异常次数*/

#define CTK_FRAME_MUL_SELT     1 /*帧累加选择,正常应用扫描帧累加次数(注意只能选择1、2、3、4)*/
                                 /* 1：一帧，2：两帧累加，3：三帧累加, 4：四帧累加			*/
								 
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

	uint8_t abnormal_mul;      /* 异常最小值系数,小于(溢出值*abnormal_mulrate/10)*/		

/* renovate */
	uint8_t renovatemode;   /* renovatemode select 0:normal 1;water*/
    
    uint8_t fthrate; //手指阈值系数
	uint8_t nthrate; //噪声阈值系数	

	uint8_t bt_ponth_maxcnt;//基线更新differ>=正噪声计数,更新基线，值越小，基线更新越快
	uint8_t st_ponth_maxcnt;//基线更新differ<正噪声计数,更新基线，值越小，基线更新越快
	uint8_t bt_nenth_maxcnt;//基线更新differ>=负噪声计数,更新基线，值越小，基线更新越快
	uint8_t st_nenth_maxcnt;//基线更新differ<负噪声计数,更新基线，值越小，基线更新越快	
	
	uint8_t wakeup_bt_ponth_maxcnt;//基线更新differ>=正噪声计数,更新基线，值越小，基线更新越快
	uint8_t wakeup_st_ponth_maxcnt;//基线更新differ<正噪声计数,更新基线，值越小，基线更新越快
	uint8_t wakeup_bt_nenth_maxcnt;//基线更新differ>=负噪声计数,更新基线，值越小，基线更新越快
	uint8_t wakeup_st_nenth_maxcnt;//基线更新differ<负噪声计数,更新基线，值越小，基线更新越快
	
	uint8_t waterflowrate;	//溢水判断阈值比例系数	
	uint8_t watermoderate;   //防水手指阈值系数

	uint8_t water_base_renomaxcnt;//bak_baseline基线更新判断次数
	
	uint8_t multikey_maxcnt;	//多按键消除判断次数;    
		
	uint8_t judge_water_maxcnt;      //溢水判断次数; 
	uint16_t judge_waterleave_maxcnt;//溢水离开判断次数

/*threshold*/
	uint16_t fingerthreshold[SENSOR_MAX_NUM];//正常模式手指阈值
	uint16_t threshold_parallel;	//并联模式手指阈值
	uint16_t finger_latency;//通道有触摸后,当差值小于fingerthreshold-finger_latency时认为抬起
	
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

extern uint8_t xdata g_ucBtPNthCnt[];//基线更新differ>=正噪声计数
extern uint8_t xdata g_ucStPNthCnt[];//基线更新differ<正噪声计数
extern uint8_t xdata g_ucBtNNthCnt[];//基线更新differ>=负噪声计数
extern uint8_t xdata g_ucStNNthCnt[];//基线更新differ<负噪声计数
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