/*!
    \file  mcu02_csd.h
    \brief csd define
*/

/*
    Copyright (C) 2020 BYD

    2020-05-08, V1.0.0, firmware for mcu02
*/

#ifndef MCU02_CSD_H
#define	MCU02_CSD_H

#include "mcu02_sfr.h"


/* csd sensor number definitions */
#define SENSOR_MAX_NUM          32

/* csd scan set definitions */
#define CSD_SCAN_EN             CSD_START = 1
#define CSD_SCAN_STOP           CSD_START = 0

/* csd power set definitions */
#define CSD_PD_SET(x) 			{REG_ADDR = PD_ANA;REG_DATA &= ~0x02;REG_DATA |= (0x02&(x<<1));}
#define CSD_ENABLE() 			REG_ADDR = PD_ANA;REG_DATA &= ~0x02
#define CSD_DISABLE() 			REG_ADDR = PD_ANA;REG_DATA |= 0x02
#define CSD_LP_EN_SET(x)		{SYS_CLK_CFG &= ~(0x20);SYS_CLK_CFG |= (0x20&(x<<5));}

/* csd parameter set definitions */
#define CSD_RB_SET(x)           {REG_ADDR = SAN_ANA_CFG;REG_DATA &= (~0x38);REG_DATA |= (0x38&(x<<3));}
#define CSD_VTH_SET(x)          {REG_ADDR = SAN_ANA_CFG;REG_DATA &= (~0x07);REG_DATA |= (0x07&(x));}
#define CSD_RESO_SET(x)         {SNS_SCAN_CFG3 &= ~(0x70);SNS_SCAN_CFG3 |= (0x70&(x<<4));}
#define CSD_DS_SET(x) 			{SNS_SCAN_CFG3 &= ~(0x0c);SNS_SCAN_CFG3 |= (0x0c&(x<<2));}
#define CSD_PRE_CHARGE_SET(x) 	{SNS_SCAN_CFG3 &= ~(0x02);SNS_SCAN_CFG3 |= (0x02&(x<<1));}
#define CSD_PRE_DISCHARGE_SET(x){SNS_SCAN_CFG3 &= ~(0x01);SNS_SCAN_CFG3 |= (0x01&(x));}
#define CSD_SW_CLK_SET(x) 		{SNS_SCAN_CFG1 &= ~(0x40);SNS_SCAN_CFG1 |= (0x40&(x<<6));}
#define CSD_PRS_DIV_SET(x) 		{SNS_SCAN_CFG1 &= ~(0x3F);SNS_SCAN_CFG1 |= (0x3F&(x));}
#define CSD_PARALLELMODE_SET(x) {SNS_SCAN_CFG2 &= ~(0x40);SNS_SCAN_CFG2 |= (0x40&(x<<6));}
#define CSD_PULL_I_SET(x) 		{PULL_I_SEL = x;SNS_SCAN_CFG2 &= ~(0x80);SNS_SCAN_CFG2 |= ((0x100&x)>>1);}
#define CSD_SCANADDR_SET(x) 	{SNS_SCAN_CFG2 &= ~(0x3F);SNS_SCAN_CFG2 |= (0x3F&(x));}


/* csd function set definitions */
//#define CSD_POWERDOWN_ENABLE   1
//#define CSD_POWERDOWN_DISABLE  0

#define CSD_LOWPOWER_ENABLE    1
#define CSD_LOWPOWER_DISABLE   0

#define CSD_SW_CLK_ON   	   0
#define CSD_SW_CLK_OFF  	   1

#define CSD_PARALLEL_ENABLE    1
#define CSD_PARALLEL_DISABLE   0

#define CSD_INT_ENABLE()				IEN1 |= 0x20   /* enable interrupt */
#define CSD_INT_DISABLE()				IEN1 &= ~0x20  /* disable interrupt */
#define CSD_IPL_SET(x)       			IPL1 &= ~0x20; IPL1 |= (x<<5)  /* set interrupt priority*/

/* csd rb definitions */
typedef enum
{
	RB_20K  = 0,
	RB_40K  = 1,
	RB_60K  = 2,
	RB_80K  = 3,
	RB_150K = 4,
	RB_200K = 5,
	RB_250K = 6,
	RB_300K	= 7
}CSD_RB_enum;

/* csd vth definitions */
typedef enum
{
	VTH_0  = 0,/*1.8v*/
	VTH_1  = 1,/*2.14v*/
	VTH_2  = 2,/*2.49v*/
	VTH_3  = 3,/*2.82v*/
	VTH_4  = 4,/*3.17v*/
	VTH_5  = 5,/*3.51v*/
	VTH_6  = 6,/*3.86v*/
	VTH_7  = 7 /*4.10v*/
}CSD_VTH_enum;

/* csd reso definitions */
typedef enum
{
	RESO_512   = 0,
	RESO_1024  = 1,
	RESO_2048  = 2,
	RESO_4096  = 3,
	RESO_8192  = 4,
	RESO_16384 = 5,
	RESO_32768 = 6,
	RESO_65536 = 7
}CSD_RESO_enum;

/* csd ds definitions */
typedef enum
{
	DS_24M = 0,
	DS_12M = 1,
	DS_6M  = 2,
	DS_4M  = 3,	
}CSD_DS_enum;

/* csd pre charge time definitions */
typedef enum
{
	PRE_CHARGE_20us = 0,
	PRE_CHARGE_40us = 1
}CSD_CHARGE_TIME_enum;

/* csd pre discharge time definitions */
typedef enum
{
	PRE_DISCHARGE_2us = 0,
	PRE_DISCHARGE_10us = 1
}CSD_DISCHARGE_TIME_enum;

/* csd prediv definitions */
/*
csd normal work: CSD_LOWPOWER_DISABLE
    prediv = 0~63 
	sw_clk = (96M/2)/(prediv+8)
csd lowpower work: CSD_LOWPOWER_ENABLE
    prediv = 0~63 
	sw_clk = (24M/2)/(prediv+2)
*/
typedef enum   /*注释的第一列为csd正常工作下的前端频率,第二列为csd低功耗模式下的前端频率*/
{
	SW_CLK_0=0,/*6.000M*/ 
    SW_CLK_1, /*5.333M,4M*/
	SW_CLK_2, /*4.800M,3M*/
	SW_CLK_3, /*4.364M,2.4M*/
	SW_CLK_4, /*4.000M,2M*/
	SW_CLK_5, /*3.692M,1.714M*/
	SW_CLK_6, /*3.429M,1.5M*/
	SW_CLK_7, /*3.200M,1.333M*/
	SW_CLK_8, /*3.000M,1.2M*/
	SW_CLK_9, /*2.824M,1.09M*/
	SW_CLK_10,/*2.667M,1M*/
	SW_CLK_11,/*2.526M,923K*/
	SW_CLK_12,/*2.400M,857K*/
	SW_CLK_13,/*2.286M,800K*/
	SW_CLK_14,/*2.182M,750K*/
	SW_CLK_15,/*2.087M,705K*/
	SW_CLK_16,/*2.000M,666K*/
	SW_CLK_17,/*1.920M,631K*/
	SW_CLK_18,/*1.846M,600K*/
	SW_CLK_19,/*1.778M,571K*/
	SW_CLK_20,/*1.714M,545K*/
	SW_CLK_21,/*1.655M,521K*/
	SW_CLK_22,/*1.600M,500K*/
	SW_CLK_23,/*1.548M,480K*/
	SW_CLK_24,/*1.500M,461K*/
	SW_CLK_25,/*1.455M,444K*/
	SW_CLK_26,/*1.412M,428K*/
	SW_CLK_27,/*1.371M,413K*/
	SW_CLK_28,/*1.333M,400K*/
	SW_CLK_29,/*1.297M,387K*/
	SW_CLK_30,/*1.263M,375K*/
	SW_CLK_31,/*1.231M,363K*/
	SW_CLK_32,/*1.200M,352K*/
	SW_CLK_33,/*1.171M,342K*/
	SW_CLK_34,/*1.143M,333K*/
	SW_CLK_35,/*1.116M,324K*/
	SW_CLK_36,/*1.091M,315K*/
	SW_CLK_37,/*1.067M,307K*/
	SW_CLK_38,/*1.043M,300K*/
	SW_CLK_39,/*1.021M,292K*/
	SW_CLK_40,/*1.000M,285K*/
	SW_CLK_41,/*980K,279K*/
	SW_CLK_42,/*960K,272K*/
	SW_CLK_43,/*941K,266K*/
	SW_CLK_44,/*923K,260K*/
	SW_CLK_45,/*906K,255K*/
	SW_CLK_46,/*889K,250K*/
	SW_CLK_47,/*873K,244K*/
	SW_CLK_48,/*857K,240K*/
	SW_CLK_49,/*842K,235K*/
	SW_CLK_50,/*828K,230K*/
	SW_CLK_51,/*814K,226K*/
	SW_CLK_52,/*800K,222K*/
	SW_CLK_53,/*787K,218K*/
	SW_CLK_54,/*774K,214K*/
	SW_CLK_55,/*762K,210K*/
	SW_CLK_56,/*750K,206K*/
	SW_CLK_57,/*738K,203K*/
	SW_CLK_58,/*727K,200K*/
	SW_CLK_59,/*716K,196K*/
	SW_CLK_60,/*706K,193K*/
	SW_CLK_61,/*400k,190K*/
	SW_CLK_62,/*high 3M low 1M center 1.5M normal distribution*/
	SW_CLK_63 /*high 3M low 1M center 1.5M normal distribution*/	
}CSD_PREDIV_enum;

/* csd parameter struct */
typedef struct
{
	uint8_t vth;		    /* vth select */	
	uint8_t ds;			    /* detect speed select */
	uint8_t pre_charge;	    /* pre charge select time us*/
	uint8_t pre_discharge;	/* pre discharge select time us*/
	uint8_t sw_clk_off;		/* enable or disable sw_clk */
	uint8_t	parallel;	    /* enable or disable sns parallel */	
	uint8_t rb;			    /* rb select */
	uint8_t reso;			/* reso select */
	uint8_t pre_div;		/* pre select */
	uint8_t csd_lowpower;	/* enable or disable csd lowpower function */
	IntPrioStatus int_prio;	/* set interrupt priority HIGH or LOW */
	ControlStatus int_status;/* enable or disable interrupt */

}csd_parameter_struct;



/* function declarations */
/* csd init */
void csd_init(csd_parameter_struct csd_initpara);

/* enable csd sensor */
void csd_sensor_enable(uint8_t sensor_addr);
/* disable csd sensor */
void csd_sensor_disable(uint8_t sensor_addr);
/* disable all csd sensor */
void csd_sensor_disable_all(void);

#endif