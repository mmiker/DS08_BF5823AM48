/*!
    \file  byd_api.h
    \brief api define
*/

/*
    Copyright (C) 2020 BYD

    2020-10-26, V1.0.0, api for byd
*/

#ifndef BYD_CTK_API_H
#define	BYD_CTK_API_H

#include "mcu02_sfr.h"

/* variable declarations */
//extern bit g_bCsdFilterEnable;           /*filter the csd data*/   
extern uint8_t xdata g_ucKeyTouchFlag[]; /*the touch state of each key*/
extern uint8_t xdata g_ucSensorNum;


extern uint16_t xdata rawdata[];		  /*ctk rawdata at normal mode*/
extern uint16_t xdata baseline[];		  /*ctk baseline at normal mode*/
extern uint16_t xdata rawdata_parallel;	  /*ctk rawdata at parallel mode*/
extern uint16_t xdata baseline_parallel;  /*ctk baseline at parallel mode*/
extern uint16_t xdata g_uiParallelCurrent;/*ctk current at parallel mode*/

/* function declarations */
/*!
    \brief      key initalization
    \param[in]  none
    \param[out] none
    \retval     none
*/
extern void byd_key_init(void);

/*!
    \brief      key exception handling 
    \param[in]  sensor(0..31)
    \param[out] none
    \retval     none
*/
extern void byd_exception_handle(uint8_t sensor);
/*!
    \brief      get the touch state of the key
    \param[in]  sensor:(0..31)
    \param[out] none
    \retval     none
*/
extern void byd_get_keytouch(uint8_t sensor);
/*!
    \brief      get sensor data
    \param[in]  sensor:(0..31)
	\param[in]  csd_scanmode:scanning mode 
		\arg	0:normal mode
		\arg    1:parallel mode	
    \param[out] none
    \retval     none
*/
extern void byd_get_sensor_data(uint8_t sensor,bit csd_scanmode);
/*!
    \brief      csd current source adaptation
    \param[in]  sensor:(0..31)
	\param[in]  csd_scanmode:scanning mode 
		\arg	0:normal mode
		\arg    1:parallel mode
	\param[in]  adjust_line:adaptation value
    \param[out] none
    \retval     none
*/
extern void byd_cts_adjust(uint8_t sensor,bit csd_scanmode,uint16_t adjust_line);

/*!
    \brief      ctk renovate function
    \param[in]  sensor:(0..31)
    \param[out] none
    \retval     none
*/
extern void byd_renovate(uint8_t sensor);

/*!
    \brief      setbaseline
    \param[in]  csd_scanmode:scanning mode 
		\arg	0:normal mode
		\arg    1:parallel mode
    \param[out] none
    \retval     none
*/
extern void byd_setbaseline(bit csd_scanmode);

/*!
    \brief      wait_cts_steady
    \param[in]  csd_scanmode:scanning mode 
		\arg	0:normal mode
		\arg    1:parallel mode
    \param[in]	frame
    \param[out] none
    \retval     none
*/
extern void byd_wait_cts_steady(bit csd_scanmode,uint8_t frame);

/*!
    \brief      updata renovate rate
    \param[in]  mode:renovate mode 
			\arg			0:normal mode全速模式
			\arg    	1:lowpower mode休眠帧频低模式
    \param[out] none
    \retval     none
*/
extern void byd_renovate_para(uint8_t mode);

#endif