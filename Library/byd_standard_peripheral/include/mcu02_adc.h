/*!
    \file  mcu02_adc.h
    \brief adc define
*/

/*
    Copyright (C) 2020 BYD

    2020-05-08, V1.0.0, firmware for mcu02
*/
#ifndef MCU02_ADC_H
#define MCU02_ADC_H

#include "mcu02_sfr.h"

/* set adc definitions */
#define ADC_IO_CGF0()	 	    REG_ADDR = ADC_IO_SEL0;REG_DATA = 0
#define ADC_IO_CGF1()	 	    REG_ADDR = ADC_IO_SEL1;REG_DATA = 0 
#define ADC_IO_CGF2()	 	    REG_ADDR = ADC_IO_SEL2;REG_DATA = 0 
#define ADC_IO_CGF3()	 	    REG_ADDR = ADC_IO_SEL3;REG_DATA = 0 
#define ADC_IO_CGF4()	 	    REG_ADDR = ADC_IO_SEL4;REG_DATA = 0 
#define ADC_IO_CGF5()	 	    REG_ADDR = ADC_IO_SEL5;REG_DATA = 0
 
#define ADC_WNUM_SET(x)			REG_ADDR = ADC_CFG_SEL;REG_DATA &= ~(0x7c);REG_DATA |= (0x7c&(x<<2))/*采样完毕后距离转换间隔时间选择(x+3)*Tadc_clk > 4*Tadc_clk */
#define ADC_I_SET(x) 	        REG_ADDR = ADC_CFG_SEL;REG_DATA &= ~(0x03);REG_DATA |= (0x03&(x))/*adc bias current sel :0~3 (4uA,5uA,5uA)*/
#define ADC_CTRL(x) 			REG_ADDR = ADC_CFG_SEL1;REG_DATA &= ~(0x03);REG_DATA |= (0x03&x)/*ADC比较器失调消除：0,1为时序1，2为时序2,3为时序3*/
#define ADC_VREF_IN_SEL(x) 	    REG_ADDR = ADC_CFG_SEL1;REG_DATA &= ~(0x0c);REG_DATA |= (0x0c&(x<<2))/*输入给ADC的参考电压选择x=0~3, 0=1.362v; 1=2.253v; 2=3.111v; 3=4.082v*/
#define ADC_VREF_VOL_SEL(x) 	REG_ADDR = ADC_CFG_SEL1;REG_DATA &= ~(0x10);REG_DATA |= (0x10&(x<<4))/*ADC参考电压输出模式选择x=0~1, 0=输出2v; 1=输出4v;*/
#define ADC_VREF_SIGNAL_SEL(x) 	REG_ADDR = ADC_CFG_SEL1;REG_DATA &= ~(0x20);REG_DATA |= (0x20&(x<<5))/*选择输出信号的来源x=0~1, 0=选择VCC作为输出信号; 1=选择VREF模块的输出作为输出信号;*/
															
#define ADC_ENABLE() 	        REG_ADDR = PD_ANA;REG_DATA &= 0xfe
#define ADC_DISABLE()           REG_ADDR = PD_ANA;REG_DATA |= 0x01

#define ADC_SAMP_SET(x)			ADC_SPT = x	/*sample time = (x+1)*4Tadc_clk */

#define ADC_ADDR_SET(x)	        ADC_SCAN_CFG &= ~(0x7E);ADC_SCAN_CFG |= (0x7E&(x<<1))/*set adc addr*/
#define ADC_SCAN_EN	 	 	    ADC_SCAN_CFG |= 0x01	/*start adc scan*/
#define ADC_SCAN_STOP	 	    ADC_SCAN_CFG &= 0xfe	/*stop adc scan*/

#define ADC_FLTER_SET(x)		ADCCKC &= ~(0x80);ADCCKC |= (0x80&(x<<7))/*输入信号滤波选择 0 不滤波 1 滤波;*/
#define ADC_SAMBG_SET(x) 		ADCCKC &= ~(0x40);ADCCKC |= (0x40&(x<<6))/*采样时序与比较时序间隔选择, x=0：无间隔；x=1：间隔1个ADC_CLK*/
#define ADC_SAMDELAY_SET(x)     ADCCKC &= ~(0x30);ADCCKC |= (0x30&(x<<4))/*采样延迟时间选择, x=0无; x=1:2个ADC_CLK; x=2:4个ADC_CLK; x=3:8个ADC_CLK;*/
#define ADC_CKV_SET(x) 			ADCCKC &= ~(0x0C);ADCCKC |= (0x0C&(x<<2))/*模拟输入信号时钟分频选择,x=(0~3)-(12MHz,8MhHz,4MHz,2MHz)*/
#define ADC_ADCK_SET(x) 		ADCCKC &= ~(0x03);ADCCKC |= (0x03&(x))   /*ADC分频选择,x=(0~3)-(8MHz,6MhHz,4MHz,3MHz)*/

/* ADC channel addr definitions */
#define ADC_CHANNEL_0                    (0x00) /*!< ADC channel 0 on PH0*/
#define ADC_CHANNEL_1                    (0x01) /*!< ADC channel 1 on PH1*/
#define ADC_CHANNEL_2                    (0x02) /*!< ADC channel 2 on PH2*/
#define ADC_CHANNEL_3                    (0x03) /*!< ADC channel 3 on PH3*/
#define ADC_CHANNEL_4                    (0x04) /*!< ADC channel 4 on PH4*/
#define ADC_CHANNEL_5                    (0x05) /*!< ADC channel 5 on PH5*/
#define ADC_CHANNEL_6                    (0x06) /*!< ADC channel 6 on PH6*/
#define ADC_CHANNEL_7                    (0x07) /*!< ADC channel 7 on PH7*/
#define ADC_CHANNEL_8                    (0x08) /*!< ADC channel 8 on PA0*/
#define ADC_CHANNEL_9                    (0x09) /*!< ADC channel 9 on PA1*/
#define ADC_CHANNEL_10                   (0x0a) /*!< ADC channel 10 on PA2*/
#define ADC_CHANNEL_11                   (0x0b) /*!< ADC channel 11 on PA3*/
#define ADC_CHANNEL_12                   (0x0c) /*!< ADC channel 12 on PB0*/
#define ADC_CHANNEL_13                   (0x0d) /*!< ADC channel 13 on PB1*/
#define ADC_CHANNEL_14                   (0x0e) /*!< ADC channel 14 on PB2*/
#define ADC_CHANNEL_15                   (0x0f) /*!< ADC channel 15 on PB3*/
#define ADC_CHANNEL_16                   (0x10) /*!< ADC channel 16 on PB4*/
#define ADC_CHANNEL_17                   (0x11) /*!< ADC channel 17 on PB5*/
#define ADC_CHANNEL_18                   (0x12) /*!< ADC channel 18 on PB6*/
#define ADC_CHANNEL_19                   (0x13) /*!< ADC channel 19 on PB7*/
#define ADC_CHANNEL_20                   (0x14) /*!< ADC channel 20 on PC0*/
#define ADC_CHANNEL_21                   (0x15) /*!< ADC channel 21 on PC1*/
#define ADC_CHANNEL_22                   (0x16) /*!< ADC channel 22 on PC2*/
#define ADC_CHANNEL_23                   (0x17) /*!< ADC channel 23 on PC3*/
#define ADC_CHANNEL_24                   (0x18) /*!< ADC channel 24 on PC4*/
#define ADC_CHANNEL_25                   (0x19) /*!< ADC channel 25 on PC5*/
#define ADC_CHANNEL_26                   (0x1a) /*!< ADC channel 26 on PC6*/
#define ADC_CHANNEL_27                   (0x1b) /*!< ADC channel 27 on PC7*/
#define ADC_CHANNEL_28                   (0x1c) /*!< ADC channel 28 on PE0*/
#define ADC_CHANNEL_29                   (0x1d) /*!< ADC channel 29 on PE1*/
#define ADC_CHANNEL_30                   (0x1e) /*!< ADC channel 30 on PE2*/
#define ADC_CHANNEL_31                   (0x1f) /*!< ADC channel 31 on PE3*/
#define ADC_CHANNEL_32                   (0x20) /*!< ADC channel 32 on PE4*/
#define ADC_CHANNEL_33                   (0x21) /*!< ADC channel 33 on PE5*/
#define ADC_CHANNEL_34                   (0x22) /*!< ADC channel 34 on PE6*/
#define ADC_CHANNEL_35                   (0x23) /*!< ADC channel 35 on PE7*/
#define ADC_CHANNEL_36                   (0x24) /*!< ADC channel 36 on PF4*/
#define ADC_CHANNEL_37                   (0x25) /*!< ADC channel 37 on PF5*/
#define ADC_CHANNEL_38                   (0x26) /*!< ADC channel 38 on PF6*/
#define ADC_CHANNEL_39                   (0x27) /*!< ADC channel 39 on PF7*/
#define ADC_CHANNEL_40                   (0x28) /*!< ADC channel 40 on PG0*/
#define ADC_CHANNEL_41                   (0x29) /*!< ADC channel 41 on PG1*/
#define ADC_CHANNEL_42                   (0x2a) /*!< ADC channel 42 on PG2*/
#define ADC_CHANNEL_43                   (0x2b) /*!< ADC channel 43 on PG3*/
#define ADC_CHANNEL_44                   (0x2c) /*!< ADC channel 44 is vref*/


/* ADC analog clock definitions */
#define ADC_ANALOG_CLK_12M               (0x00) /*!< ADC analog clock 12M */
#define ADC_ANALOG_CLK_8M                (0x01) /*!< ADC analog clock 8M */
#define ADC_ANALOG_CLK_4M                (0x02) /*!< ADC analog clock 4M */
#define ADC_ANALOG_CLK_2M                (0x03) /*!< ADC analog clock 2M */

/* ADC clock definitions */
#define ADC_CLK_8M                 		 (0x00) /*!< ADC clock 8M */
#define ADC_CLK_6M                 		 (0x01) /*!< ADC clock 6M */
#define ADC_CLK_4M                 		 (0x02) /*!< ADC clock 4M */
#define ADC_CLK_3M                 		 (0x03) /*!< ADC clock 3M */

/* ADC filter definitions */
#define ADC_FILTER_DISABLE               (0x00) /*!< ADC filter none*/
#define ADC_FILTER_ENABLE                (0x01) /*!< ADC filter */

/* ADC sample delay time */
#define ADC_SAMPLE_TIME_0_CLK			 (0x00)/* NONE */
#define ADC_SAMPLE_TIME_2_CLK			 (0x01)/* DELAY 2 ADC_CLK */
#define ADC_SAMPLE_TIME_4_CLK			 (0x02)/* DELAY 4 ADC_CLK */
#define ADC_SAMPLE_TIME_8_CLK       	 (0x03)/* DELAY 8 ADC_CLK */


/* ADC VREF*/
#define ADC_VREF_IN_0					 (0x00)/* 1.362v */
#define ADC_VREF_IN_1					 (0x01)/* 2.253v */
#define ADC_VREF_IN_2					 (0x02)/* 3.111v */
#define ADC_VREF_IN_3					 (0x03)/* 4.082v */

#define ADC_VREF_VOL_OUT_0			     (0x00)/* 2v */
#define ADC_VREF_VOL_OUT_1				 (0x01)/* 4v */

#define ADC_VREF_SIGNAL_OUT_0			 (0x00)/* VCC */
#define ADC_VREF_SIGNAL_OUT_1		     (0x01)/* ADC_VREF */

/* ADC io definitions */
#define ADC_IO_PA            			 0x00
#define ADC_IO_PB            			 0x01
#define ADC_IO_PC            			 0x02
#define ADC_IO_PE            			 0x03
#define ADC_IO_PF            			 0x04
#define ADC_IO_PG            			 0x05
#define ADC_IO_PH            			 0x06

#define ADC_00_PH0 	      				(0x01)  /*!< ADC function on PH0 */
#define ADC_01_PH1 	      				(0x02)  /*!< ADC function on PH1 */
#define ADC_02_PH2 	      				(0x04)  /*!< ADC function on PH2 */
#define ADC_03_PH3 	      				(0x08)  /*!< ADC function on PH3 */
#define ADC_04_PH4 	      				(0x10)  /*!< ADC function on PH4 */
#define ADC_05_PH5 	      				(0x20)  /*!< ADC function on PH5 */
#define ADC_06_PH6 	      				(0x40)  /*!< ADC function on PH6 */
#define ADC_07_PH7 	      				(0x80)  /*!< ADC function on PH7 */

#define ADC_08_PA0 	      				(0x01)  /*!< ADC function on PA0 */
#define ADC_09_PA1 	      				(0x02)  /*!< ADC function on PA1 */
#define ADC_10_PA2 	      				(0x04)  /*!< ADC function on PA2 */
#define ADC_11_PA3 	      				(0x08)  /*!< ADC function on PA3 */
                              
#define ADC_12_PB0 	      				(0x01)  /*!< ADC function on PB0 */
#define ADC_13_PB1 	      				(0x02)  /*!< ADC function on PB1 */
#define ADC_14_PB2 	      				(0x04)  /*!< ADC function on PB2 */
#define ADC_15_PB3 	      				(0x08)  /*!< ADC function on PB3 */
#define ADC_16_PB4 	      				(0x10)  /*!< ADC function on PB4 */
#define ADC_17_PB5 	      				(0x20)  /*!< ADC function on PB5 */
#define ADC_18_PB6 	      				(0x40)  /*!< ADC function on PB6 */
#define ADC_19_PB7 	      				(0x80)  /*!< ADC function on PB7 */
                              
#define ADC_20_PC0 	      				(0x01)  /*!< ADC function on PC0 */
#define ADC_21_PC1 	      				(0x02)  /*!< ADC function on PC1 */
#define ADC_22_PC2 	      				(0x04)  /*!< ADC function on PC2 */
#define ADC_23_PC3 	      				(0x08)  /*!< ADC function on PC3 */
#define ADC_24_PC4 	      				(0x10)  /*!< ADC function on PC4 */
#define ADC_25_PC5 	      				(0x20)  /*!< ADC function on PC5 */
#define ADC_26_PC6 	      				(0x40)  /*!< ADC function on PC6 */
#define ADC_27_PC7 	      				(0x80)  /*!< ADC function on PC7 */
                              
#define ADC_28_PE0 	      				(0x01)  /*!< ADC function on PE0 */
#define ADC_29_PE1 	      				(0x02)  /*!< ADC function on PE1 */
#define ADC_30_PE2 	      				(0x04)  /*!< ADC function on PE2 */
#define ADC_31_PE3 	      				(0x08)  /*!< ADC function on PE3 */
#define ADC_32_PE4 	      				(0x10)  /*!< ADC function on PE4 */
#define ADC_33_PE5 	      				(0x20)  /*!< ADC function on PE5 */
#define ADC_34_PE6 	      				(0x40)  /*!< ADC function on PE6 */
#define ADC_35_PE7 	      				(0x80)  /*!< ADC function on PE7 */
                              
#define ADC_36_PF4 	      				(0x10)  /*!< ADC function on PF4 */ 
#define ADC_37_PF5 	      				(0x20)  /*!< ADC function on PF5 */ 
#define ADC_38_PF6 	      				(0x40)  /*!< ADC function on PF6 */ 
#define ADC_39_PF7 	      				(0x80)  /*!< ADC function on PF7 */
 
#define ADC_40_PG0 	      				(0x01)  /*!< ADC function on PG0 */ 
#define ADC_41_PG1 	      				(0x02)  /*!< ADC function on PG1 */ 
#define ADC_42_PG2 	      				(0x04)  /*!< ADC function on PG2 */ 
#define ADC_43_PG3 	      				(0x08)  /*!< ADC function on PG3 */                               

#define ADC_00_PH0_ENABLE() 	      	REG_ADDR = ADC_IO_SEL0;REG_DATA |= 0x01;TRISH |= 0x01 /*!< enable ADC function on PH0 */
#define ADC_01_PH1_ENABLE() 	      	REG_ADDR = ADC_IO_SEL0;REG_DATA |= 0x02;TRISH |= 0x02 /*!< enable ADC function on PH1 */
#define ADC_02_PH2_ENABLE() 	      	REG_ADDR = ADC_IO_SEL0;REG_DATA |= 0x04;TRISH |= 0x04 /*!< enable ADC function on PH2 */
#define ADC_03_PH3_ENABLE() 	      	REG_ADDR = ADC_IO_SEL0;REG_DATA |= 0x08;TRISH |= 0x08 /*!< enable ADC function on PH3 */
#define ADC_04_PH4_ENABLE() 	      	REG_ADDR = ADC_IO_SEL0;REG_DATA |= 0x10;TRISH |= 0x10 /*!< enable ADC function on PH4 */
#define ADC_05_PH5_ENABLE() 	      	REG_ADDR = ADC_IO_SEL0;REG_DATA |= 0x20;TRISH |= 0x20 /*!< enable ADC function on PH5 */
#define ADC_06_PH6_ENABLE() 	      	REG_ADDR = ADC_IO_SEL0;REG_DATA |= 0x40;TRISH |= 0x40 /*!< enable ADC function on PH6 */
#define ADC_07_PH7_ENABLE() 	      	REG_ADDR = ADC_IO_SEL1;REG_DATA |= 0x01;TRISH |= 0x80 /*!< enable ADC function on PH7 */

#define ADC_00_PH0_DISABLE() 	      	REG_ADDR = ADC_IO_SEL0;REG_DATA &= ~0x01 /*!< disable ADC function on PH0 */
#define ADC_01_PH1_DISABLE() 	      	REG_ADDR = ADC_IO_SEL0;REG_DATA &= ~0x02 /*!< disable ADC function on PH1 */
#define ADC_02_PH2_DISABLE() 	      	REG_ADDR = ADC_IO_SEL0;REG_DATA &= ~0x04 /*!< disable ADC function on PH2 */
#define ADC_03_PH3_DISABLE() 	      	REG_ADDR = ADC_IO_SEL0;REG_DATA &= ~0x08 /*!< disable ADC function on PH3 */
#define ADC_04_PH4_DISABLE() 	      	REG_ADDR = ADC_IO_SEL0;REG_DATA &= ~0x10 /*!< disable ADC function on PH4 */
#define ADC_05_PH5_DISABLE() 	      	REG_ADDR = ADC_IO_SEL0;REG_DATA &= ~0x20 /*!< disable ADC function on PH5 */
#define ADC_06_PH6_DISABLE() 	      	REG_ADDR = ADC_IO_SEL0;REG_DATA &= ~0x40 /*!< disable ADC function on PH6 */
#define ADC_07_PH7_DISABLE() 	      	REG_ADDR = ADC_IO_SEL1;REG_DATA &= ~0x01 /*!< disable ADC function on PH7 */

#define ADC_08_PA0_ENABLE() 	      	REG_ADDR = ADC_IO_SEL1;REG_DATA |= (0x01<<1);TRISA |= 0x01 /*!< enable ADC function on PA0 */
#define ADC_09_PA1_ENABLE() 	      	REG_ADDR = ADC_IO_SEL1;REG_DATA |= (0x02<<1);TRISA |= 0x02 /*!< enable ADC function on PA1 */
#define ADC_10_PA2_ENABLE() 	      	REG_ADDR = ADC_IO_SEL1;REG_DATA |= (0x04<<1);TRISA |= 0x04 /*!< enable ADC function on PA2 */
#define ADC_11_PA3_ENABLE() 	      	REG_ADDR = ADC_IO_SEL1;REG_DATA |= (0x08<<1);TRISA |= 0x08 /*!< enable ADC function on PA3 */

#define ADC_08_PA0_DISABLE() 	      	REG_ADDR = ADC_IO_SEL1;REG_DATA &= ~(0x01<<1) /*!< disable ADC function on PA0 */
#define ADC_09_PA1_DISABLE() 	      	REG_ADDR = ADC_IO_SEL1;REG_DATA &= ~(0x02<<1) /*!< disable ADC function on PA1 */
#define ADC_10_PA2_DISABLE() 	      	REG_ADDR = ADC_IO_SEL1;REG_DATA &= ~(0x04<<1) /*!< disable ADC function on PA2 */
#define ADC_11_PA3_DISABLE() 	      	REG_ADDR = ADC_IO_SEL1;REG_DATA &= ~(0x08<<1) /*!< disable ADC function on PA3 */
                              
#define ADC_12_PB0_ENABLE() 	      	REG_ADDR = ADC_IO_SEL1;REG_DATA |= (0x01<<5);TRISB |= 0x01 /*!< enable ADC function on PB0 */
#define ADC_13_PB1_ENABLE() 	      	REG_ADDR = ADC_IO_SEL1;REG_DATA |= (0x02<<5);TRISB |= 0x02 /*!< enable ADC function on PB1 */
#define ADC_14_PB2_ENABLE() 	      	REG_ADDR = ADC_IO_SEL1;REG_DATA |= (0x04<<5);TRISB |= 0x04 /*!< enable ADC function on PB2 */
#define ADC_15_PB3_ENABLE() 	      	REG_ADDR = ADC_IO_SEL2;REG_DATA |= (0x08>>3);TRISB |= 0x08 /*!< enable ADC function on PB3 */
#define ADC_16_PB4_ENABLE() 	      	REG_ADDR = ADC_IO_SEL2;REG_DATA |= (0x10>>3);TRISB |= 0x10 /*!< enable ADC function on PB4 */
#define ADC_17_PB5_ENABLE() 	      	REG_ADDR = ADC_IO_SEL2;REG_DATA |= (0x20>>3);TRISB |= 0x20 /*!< enable ADC function on PB5 */
#define ADC_18_PB6_ENABLE() 	      	REG_ADDR = ADC_IO_SEL2;REG_DATA |= (0x40>>3);TRISB |= 0x40 /*!< enable ADC function on PB6 */
#define ADC_19_PB7_ENABLE() 	      	REG_ADDR = ADC_IO_SEL2;REG_DATA |= (0x80>>3);TRISB |= 0x80 /*!< enable ADC function on PB7 */

#define ADC_12_PB0_DISABLE() 	      	REG_ADDR = ADC_IO_SEL1;REG_DATA &= ~(0x01<<5)  /*!< disable ADC function on PB0 */
#define ADC_13_PB1_DISABLE() 	      	REG_ADDR = ADC_IO_SEL1;REG_DATA &= ~(0x02<<5)  /*!< disable ADC function on PB1 */
#define ADC_14_PB2_DISABLE() 	      	REG_ADDR = ADC_IO_SEL1;REG_DATA &= ~(0x04<<5)  /*!< disable ADC function on PB2 */
#define ADC_15_PB3_DISABLE() 	      	REG_ADDR = ADC_IO_SEL2;REG_DATA &= ~(0x08>>3)  /*!< disable ADC function on PB3 */
#define ADC_16_PB4_DISABLE() 	      	REG_ADDR = ADC_IO_SEL2;REG_DATA &= ~(0x10>>3)  /*!< disable ADC function on PB4 */
#define ADC_17_PB5_DISABLE() 	      	REG_ADDR = ADC_IO_SEL2;REG_DATA &= ~(0x20>>3)  /*!< disable ADC function on PB5 */
#define ADC_18_PB6_DISABLE() 	      	REG_ADDR = ADC_IO_SEL2;REG_DATA &= ~(0x40>>3)  /*!< disable ADC function on PB6 */
#define ADC_19_PB7_DISABLE() 	      	REG_ADDR = ADC_IO_SEL2;REG_DATA &= ~(0x80>>3)  /*!< disable ADC function on PB7 */
                              
#define ADC_20_PC0_ENABLE() 	      	REG_ADDR = ADC_IO_SEL2;REG_DATA |= (0x01<<5);TRISC |= 0x01 /*!< enable ADC function on PC0 */
#define ADC_21_PC1_ENABLE() 	      	REG_ADDR = ADC_IO_SEL2;REG_DATA |= (0x02<<5);TRISC |= 0x02 /*!< enable ADC function on PC1 */
#define ADC_22_PC2_ENABLE() 	      	REG_ADDR = ADC_IO_SEL2;REG_DATA |= (0x04<<5);TRISC |= 0x04 /*!< enable ADC function on PC2 */
#define ADC_23_PC3_ENABLE() 	      	REG_ADDR = ADC_IO_SEL3;REG_DATA |= (0x08>>3);TRISC |= 0x08 /*!< enable ADC function on PC3 */
#define ADC_24_PC4_ENABLE() 	      	REG_ADDR = ADC_IO_SEL3;REG_DATA |= (0x10>>3);TRISC |= 0x10 /*!< enable ADC function on PC4 */
#define ADC_25_PC5_ENABLE() 	      	REG_ADDR = ADC_IO_SEL3;REG_DATA |= (0x20>>3);TRISC |= 0x20 /*!< enable ADC function on PC5 */
#define ADC_26_PC6_ENABLE() 	      	REG_ADDR = ADC_IO_SEL3;REG_DATA |= (0x40>>3);TRISC |= 0x40 /*!< enable ADC function on PC6 */
#define ADC_27_PC7_ENABLE() 	      	REG_ADDR = ADC_IO_SEL3;REG_DATA |= (0x80>>3);TRISC |= 0x80 /*!< enable ADC function on PC7 */

#define ADC_20_PC0_DISABLE() 	      	REG_ADDR = ADC_IO_SEL2;REG_DATA &= ~(0x01<<5) /*!< disable ADC function on PC0 */
#define ADC_21_PC1_DISABLE() 	      	REG_ADDR = ADC_IO_SEL2;REG_DATA &= ~(0x02<<5) /*!< disable ADC function on PC1 */
#define ADC_22_PC2_DISABLE() 	      	REG_ADDR = ADC_IO_SEL2;REG_DATA &= ~(0x04<<5) /*!< disable ADC function on PC2 */
#define ADC_23_PC3_DISABLE() 	      	REG_ADDR = ADC_IO_SEL3;REG_DATA &= ~(0x08>>3) /*!< disable ADC function on PC3 */
#define ADC_24_PC4_DISABLE() 	      	REG_ADDR = ADC_IO_SEL3;REG_DATA &= ~(0x10>>3) /*!< disable ADC function on PC4 */
#define ADC_25_PC5_DISABLE() 	      	REG_ADDR = ADC_IO_SEL3;REG_DATA &= ~(0x20>>3) /*!< disable ADC function on PC5 */
#define ADC_26_PC6_DISABLE() 	      	REG_ADDR = ADC_IO_SEL3;REG_DATA &= ~(0x40>>3) /*!< disable ADC function on PC6 */
#define ADC_27_PC7_DISABLE() 	      	REG_ADDR = ADC_IO_SEL3;REG_DATA &= ~(0x80>>3) /*!< disable ADC function on PC7 */
                              
#define ADC_28_PE0_ENABLE() 	      	REG_ADDR = ADC_IO_SEL3;REG_DATA |= (0x01<<5);TRISE |= 0x01 /*!< enable ADC function on PE0 */
#define ADC_29_PE1_ENABLE() 	      	REG_ADDR = ADC_IO_SEL3;REG_DATA |= (0x02<<5);TRISE |= 0x02 /*!< enable ADC function on PE1 */
#define ADC_30_PE2_ENABLE() 	      	REG_ADDR = ADC_IO_SEL3;REG_DATA |= (0x04<<5);TRISE |= 0x04 /*!< enable ADC function on PE2 */
#define ADC_31_PE3_ENABLE() 	      	REG_ADDR = ADC_IO_SEL4;REG_DATA |= (0x08>>3);TRISE |= 0x08 /*!< enable ADC function on PE3 */
#define ADC_32_PE4_ENABLE() 	      	REG_ADDR = ADC_IO_SEL4;REG_DATA |= (0x10>>3);TRISE |= 0x10 /*!< enable ADC function on PE4 */
#define ADC_33_PE5_ENABLE() 	      	REG_ADDR = ADC_IO_SEL4;REG_DATA |= (0x20>>3);TRISE |= 0x20 /*!< enable ADC function on PE5 */
#define ADC_34_PE6_ENABLE() 	      	REG_ADDR = ADC_IO_SEL4;REG_DATA |= (0x40>>3);TRISE |= 0x40 /*!< enable ADC function on PE6 */
#define ADC_35_PE7_ENABLE() 	      	REG_ADDR = ADC_IO_SEL4;REG_DATA |= (0x80>>3);TRISE |= 0x80 /*!< enable ADC function on PE7 */

#define ADC_28_PE0_DISABLE() 	      	REG_ADDR = ADC_IO_SEL3;REG_DATA &= ~(0x01<<5) /*!< disable ADC function on PE0 */ 
#define ADC_29_PE1_DISABLE() 	      	REG_ADDR = ADC_IO_SEL3;REG_DATA &= ~(0x02<<5) /*!< disable ADC function on PE1 */ 
#define ADC_30_PE2_DISABLE() 	      	REG_ADDR = ADC_IO_SEL3;REG_DATA &= ~(0x04<<5) /*!< disable ADC function on PE2 */ 
#define ADC_31_PE3_DISABLE() 	      	REG_ADDR = ADC_IO_SEL4;REG_DATA &= ~(0x08>>3) /*!< disable ADC function on PE3 */ 
#define ADC_32_PE4_DISABLE() 	      	REG_ADDR = ADC_IO_SEL4;REG_DATA &= ~(0x10>>3) /*!< disable ADC function on PE4 */ 
#define ADC_33_PE5_DISABLE() 	      	REG_ADDR = ADC_IO_SEL4;REG_DATA &= ~(0x20>>3) /*!< disable ADC function on PE5 */ 
#define ADC_34_PE6_DISABLE() 	      	REG_ADDR = ADC_IO_SEL4;REG_DATA &= ~(0x40>>3) /*!< disable ADC function on PE6 */ 
#define ADC_35_PE7_DISABLE() 	      	REG_ADDR = ADC_IO_SEL4;REG_DATA &= ~(0x80>>3) /*!< disable ADC function on PE7 */
                              
#define ADC_36_PF4_ENABLE() 	      	REG_ADDR = ADC_IO_SEL4;REG_DATA |= (0x10<<1);TRISF |= 0x10  /*!< enable ADC function on PF4 */ 
#define ADC_37_PF5_ENABLE() 	      	REG_ADDR = ADC_IO_SEL4;REG_DATA |= (0x20<<1);TRISF |= 0x20  /*!< enable ADC function on PF5 */ 
#define ADC_38_PF6_ENABLE() 	      	REG_ADDR = ADC_IO_SEL4;REG_DATA |= (0x40<<1);TRISF |= 0x40  /*!< enable ADC function on PF6 */ 
#define ADC_39_PF7_ENABLE() 	      	REG_ADDR = ADC_IO_SEL5;REG_DATA |= (0x80>>7);TRISF |= 0x80  /*!< enable ADC function on PF7 */

#define ADC_36_PF4_DISABLE() 	      	REG_ADDR = ADC_IO_SEL4;REG_DATA &= ~(0x10<<1) /*!< disable ADC function on PF4 */
#define ADC_37_PF5_DISABLE() 	      	REG_ADDR = ADC_IO_SEL4;REG_DATA &= ~(0x20<<1) /*!< disable ADC function on PF5 */
#define ADC_38_PF6_DISABLE() 	      	REG_ADDR = ADC_IO_SEL4;REG_DATA &= ~(0x40<<1) /*!< disable ADC function on PF6 */
#define ADC_39_PF7_DISABLE() 	      	REG_ADDR = ADC_IO_SEL5;REG_DATA &= ~(0x80>>7) /*!< disable ADC function on PF7 */
 
#define ADC_40_PG0_ENABLE() 	      	REG_ADDR = ADC_IO_SEL5;REG_DATA |= (0x01<<1);TRISG |= 0x01 /*!< enable ADC function on PG0 */ 
#define ADC_41_PG1_ENABLE() 	      	REG_ADDR = ADC_IO_SEL5;REG_DATA |= (0x02<<1);TRISG |= 0x02 /*!< enable ADC function on PG1 */ 
#define ADC_42_PG2_ENABLE() 	      	REG_ADDR = ADC_IO_SEL5;REG_DATA |= (0x04<<1);TRISG |= 0x04 /*!< enable ADC function on PG2 */ 
#define ADC_43_PG3_ENABLE() 	      	REG_ADDR = ADC_IO_SEL5;REG_DATA |= (0x08<<1);TRISG |= 0x08 /*!< enable ADC function on PG3 */

#define ADC_40_PG0_DISABLE() 	      	REG_ADDR = ADC_IO_SEL5;REG_DATA &= ~(0x01<<1) /*!< disable ADC function on PG0 */
#define ADC_41_PG1_DISABLE() 	      	REG_ADDR = ADC_IO_SEL5;REG_DATA &= ~(0x02<<1) /*!< disable ADC function on PG1 */
#define ADC_42_PG2_DISABLE() 	      	REG_ADDR = ADC_IO_SEL5;REG_DATA &= ~(0x04<<1) /*!< disable ADC function on PG2 */
#define ADC_43_PG3_DISABLE() 	      	REG_ADDR = ADC_IO_SEL5;REG_DATA &= ~(0x08<<1) /*!< disable ADC function on PG3 */

#define ADC_INT_ENABLE()				IEN1 |= 0x10   /* enable interrupt */
#define ADC_INT_DISABLE()				IEN1 &= ~0x10  /* disable interrupt */
#define ADC_IPL_SET(x)        			IPL1 &= ~0x10;IPL1 |= (x<<4)  /* set interrupt priority*/

/*
T = sample time + time2 + time3

sample time = (ADC_SPT+1)*4*Tadc_clk;

time2 = interval time = (ADC_WNUM+3+ADC_SAMDELAY)*Tadc_clk

time3 = (2*1+12)*Tadc_clk;

*/


/* function declarations */
void adc_io_reset(void);
void adc_io_enable(uint8_t adc_io_port, uint8_t adc_io_pin);
void adc_io_disable(uint8_t adc_io_port, uint8_t adc_io_pin);
#endif