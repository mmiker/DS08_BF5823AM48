/*!
    \file  mcu02_rfid.h
    \brief rfid define
*/

/*
    Copyright (C) 2020 BYD

    2020-03-31, V1.0.0, firmware for mcu02
*/

#ifndef MCU02_RFID_H
#define	MCU02_RFID_H

#include "mcu02_sfr.h"


/* rfid config define */

#define	RECE_PULSE_NUM_1	   0x00
#define	RECE_PULSE_NUM_2	  (0x01 << 4)
#define	RECE_PULSE_NUM_3	  (0x02 << 4)
#define	RECE_PULSE_NUM_4	  (0x03 << 4)

#define	RFID_SEND_START		  (0x01 << 0)
#define	PD_CMP				  (0x01 << 1)
#define	RFID_SEND_EN		  (0x01 << 0)	
#define	RFID_RECV_EN		  (0x01 << 6)
#define RFID_TXD_STOP_EN      (0x01 << 7)		


/* rfid interrupt flag define */
#define	RFID_RX_BIT_ERROR_FLAG		 (0x80)
#define	RFID_RX_IDLE_FLAG			 (0x40)
#define	RFID_RX_PARITY_ERROR_FLAG	 (0x20)
#define	RFID_RX_FULL_FLAG			 (0x10)
#define	RFID_TX_COMPLET_FLAG		 (0x08)
#define	RFID_ALL_FLAG				 (0xF8)


#define RFID_IE_SET                   IEN1 |= 0x40		//开RFID中断使能
#define RFID_IP_SET                   IPL1 |= 0x40		//设置RFID中断优先级为高
#define RFID_INT_FLAG_CLR             IRCON1 &= ~0x40;INT_PE_STAT = ~0x01		// 清除RFID中断标志位


#define RFID_ANTIC_NVB_SET(x)	      REG_ADDR = RFID_ANTIC_NVB;REG_DATA = x   //配置NVB
#define RFID_ANTIC_ENABLE()	          REG_ADDR = RFID_MODE_SEL;REG_DATA |= 0x01//使能防冲突帧
#define RFID_ANTIC_DISABLE()	      REG_ADDR = RFID_MODE_SEL;REG_DATA &= 0xfe//关闭防冲突帧
#define RFID_TXD_DATA_SEL(x)	      REG_ADDR = RFID_MODE_SEL;REG_DATA &= (~0x02);REG_DATA |= (0x02&(x<<1))//发送数据位数

#define RFID_ANTIC_FRAME              0x01//此帧为防冲突帧
#define RFID_NORMAL_FRAME             0x00//此帧为正常工作帧

#define RFID_TXD_DATA_9               0x01//发送9位数据(奇偶校验不自动计算)
#define RFID_TXD_DATA_8               0x00//发送8位数据+奇偶校验位(自动计算)


#define RFID_RXD_PRENUM_SET(x)  	  RFID_CFG3 &= (~0x07); RFID_CFG3 |= (0x07 & x)//
#define RFID_RXD_16H_EN(x)      	  RFID_CFG3 &= (~0x08); RFID_CFG3 |= (0x08 & (x<<3))//计数器是否加1
#define RFID_BUF1_ODD_SET(x)    	  RFID_CFG3 &= (~0x10); RFID_CFG3 |= (0x10 & (x<<4))//设置奇偶校验值
#define RFID_BUF2_ODD_SET(x)    	  RFID_CFG3 &= (~0x20); RFID_CFG3 |= (0x20 & (x<<5))//设置奇偶校验值

#define RFID_REIV_FILTER_SET(x) 	  RFID_CFG2 &= (~0x0f); RFID_CFG2 |= (0x0f & x)//滤波个数1~15,0无滤波
#define RFID_REIV_BIT_SET(x)    	  RFID_CFG2 &= (~0x30); RFID_CFG2 |= (0x30 & (x<<4))//接收位时序0~3对应1~4

#define RFID_DATANUM_SET(x)     	  RFID_CMD &= (~0x3e); RFID_CMD |= (0x3e&(x<<1))//发送数据长度

#define RFID_TXD_STOP_MODE_DISABLE()  REG_ADDR = RFID_MODE_SEL;REG_DATA &= (~0x04)//发送RFID_DATANUM_SET个数据后,通信自动结束
#define RFID_TXD_STOP_MODE_ENABLE()   REG_ADDR = RFID_MODE_SEL;REG_DATA |= 0x04//发送n个数据,直到寄存器RFID_CMD中的TXD_STOP为1后停止发送

#define RFID_TXD_STOP_ENABLE()        RFID_CMD |= 0x80//使能停止发送
#define RFID_TXD_STOP_DISABLE()       RFID_CMD &= (~0x80)//关闭

#define RFID_BIT_TXD_MODE_ENABLE()    REG_ADDR = RFID_MODE_SEL;REG_DATA |= 0x08   //位发送使能,一次发送1bit数据
#define RFID_BIT_TXD_MODE_DISABLE()   REG_ADDR = RFID_MODE_SEL;REG_DATA &= (~0x08)//关闭位发送

#define RFID_BIT_RXD_MODE_ENABLE()    REG_ADDR = RFID_MODE_SEL;REG_DATA |= 0x10//位接收使能,一次接收1bit数据
#define RFID_BIT_RXD_MODE_DISABLE()   REG_ADDR = RFID_MODE_SEL;REG_DATA &= (~0x10)//关闭位接收

#define RFID_SEND_ENABLE()      	  RFID_CMD |= (0x01)//发送使能
#define RFID_SEND_DISABLE()     	  RFID_CMD &= (~0x01)//关闭

#define RFID_RECEIVE_ENABLE()   	  RFID_CMD |= 0x40//接收使能
#define RFID_RECEIVE_DISABLE()  	  RFID_CMD &= (~0x40)//关闭

#define RFID_IO_ENABLE()        	  RFID_CFG2 |= 0x80//RFID IO口使能
#define RFID_IO_DISABLE()       	  RFID_CFG2 &= (~0x80)//关闭

#define RFID_ENABLE()                 RFID_CFG |= 0x01//RFID使能
#define RFID_DISABLE()                RFID_CFG &= ~0x01//RFID关闭

#define RFID_CMP_DISABLE()            RFID_CFG |= 0x02//RFID接收比较器不工作
#define RFID_CMP_ENABLE()             RFID_CFG &= ~0x02//RFID接收比较器工作

#define RFID_RX_FULL_CLR()            RFID_CFG &= ~RFID_RX_FULL_FLAG
#define RFID_RX_ERR_CLR()			  RFID_CFG &= ~RFID_RX_BIT_ERROR_FLAG
#define RFID_RX_PARITY_ERR_CLR()	  RFID_CFG &= ~RFID_RX_PARITY_ERROR_FLAG

#define RFID_TX_COMPLTE_CLR()         RFID_CFG &= ~RFID_TX_COMPLET_FLAG


#define send_x()  					  0x01
#define send_y()  					  0x02
#define send_z()  					  0x00

#define WAIT_TIMEOUT_TX               0xffff
#define WAIT_TIMEOUT_RX               0xffff

#define ANTIA_ERROR                   0xac//发生冲突


/* function declarations */
/* rfid config */
void rfid_config(void);

void rfid_enter_lowpower_config(void);
void rfid_exit_lowpower_config(void);

ErrStatus rfid_transmit(uint8_t *buf,uint8_t len);
ErrStatus rfid_transmit_9bit(uint8_t *buf,uint8_t *paritybuf,uint8_t len);
ErrStatus rfid_transmit_bit(uint8_t *buf,uint8_t lenBit);
ErrStatus wait_rfid_tx_complete(void);

uint8_t rfid_receive(uint8_t *buf,uint8_t *anti_byte,uint8_t len);
uint8_t rfid_receive_bit(uint8_t *buf,uint8_t len);
ErrStatus rfid_rx(uint8_t *buf);

uint8_t rfid_rx_bit(void);
uint8_t rfid_byte_err_bit(void);

bit calc_parity(uint8_t send_data);
#endif