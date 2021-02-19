/*!
    \file  byd_adc.c
    \brief adc app
*/

/*
    Copyright (C) 2020 BYD

    2020-05-08, V1.0.0, app for byd
*/

#include "byd_adc.h"
#include "byd_init.h"
#include "delay.h"
#include "dqiot_gpio.h"
#include "dqiot_drv.h"
#include "mmi_audio.h"

#if ADC_MODE == 0
volatile bit g_bAdcIntFlag = 0;
#endif

#if ADC_HANDLE
uint8_t xdata g_ucAdcBaseFlag = 0;
uint8_t xdata g_ucAdcBaseline[8];
uint8_t xdata g_ucAdcRawdata[ADC_MAX_COUNT];
#endif

/*!
    \brief      byd adc init
    \param[in]  none
    \param[out] none
    \retval     none
*/
void byd_adc_init(void)
{
#if ADC_HANDLE
	uint8_t i;
#endif

	gpio_init(VBAT_TEST_PORT, VBAT_TEST_PIN, GPIO_MODE_OUT);
	gpio_init(VBAT_ADC_PORT, VBAT_ADC_PIN, GPIO_MODE_IN_FLOATING);

	ADC_ADCK_SET(ADC_CLK_8M);				 /* adc clock */
	ADC_CKV_SET(ADC_ANALOG_CLK_8M);			 /* adc analog clock */
	ADC_SAMBG_SET(1);						 /* sampling time sequence and comparison time interval:0~1*/
	ADC_SAMDELAY_SET(ADC_SAMPLE_TIME_8_CLK); /* sampling delay time */
	ADC_FLTER_SET(ADC_FILTER_ENABLE);		 /* filter select */
	ADC_ADDR_SET(ADC_CHANNEL_7);			 /* adc channel address */
	ADC_ADDR_SET(ADC_CHANNEL_6);			 /* adc channel address */
	ADC_WNUM_SET(31);						 /* conversion interval time:2~31*/
	ADC_I_SET(3);							 /* adc bias current select:0~3*/
	ADC_CTRL(2);							 /* compare ctrl select:0~3*/
	ADC_SAMP_SET(255);						 /* adc sample time:0~255*/

	ADC_VREF_IN_SEL(ADC_VREF_IN_1);				/* input vref vol*/
	ADC_VREF_VOL_SEL(ADC_VREF_VOL_OUT_1);		/* output vref vol*/
	ADC_VREF_SIGNAL_SEL(ADC_VREF_SIGNAL_OUT_0); /* output vref signal*/

	adc_io_reset();

	ADC_07_PH7_ENABLE(); /*enable adc io*/
	ADC_06_PH6_ENABLE(); /*enable adc io*/
	//ADC_01_PH1_ENABLE();

	/*!!!!!!!!!恢复IO口功能要关闭adc通道功能!!!!!!!!!*/
	//	ADC_00_PH0_DISABLE();
	//  ADC_01_PH1_DISABLE();

	ADC_ENABLE(); /*enable adc*/

/* adc interrupt config*/
#if ADC_MODE == 0
	INT_ADC_CLR();
	ADC_IPL_SET(LOW);
	ADC_INT_ENABLE();
#endif

#if ADC_HANDLE
	for (i = 0; i < ADC_MAX_COUNT; i++)
	{
		g_ucAdcRawdata[i] = 0;
	}
#endif
}

/**
  * @brief  get adc data
  * @param  adc_channel_addr:ADC_CHANNEL_0~44
  * @return none
  * @note   none
  * @see    none
  */
uint16_t get_adc_data(uint8_t adc_channel_addr)
{
	uint16_t adc_data;

	ADC_ADDR_SET(adc_channel_addr);

#if ADC_MODE == 0
	g_bAdcIntFlag = 0;
	ADC_SCAN_EN;
	while (!g_bAdcIntFlag)
	{
		WDT_CTRL = 7;
	}
#else

	ADC_SCAN_EN;
	while (!(IRCON1 & 0x10))
	{
		WDT_CTRL = 7;
	}
	INT_ADC_CLR();

#endif

	adc_data = ((uint16_t)(ADC_RDATAH & 0x0F) << 8) | (uint16_t)ADC_RDATAL;

	return adc_data;
}

/**
  * @brief  获取adc数据的平均值
  * @param  
  * adc_channel_addr ADC_CHANNEL_0~44;
  * times 时间ms
  * @return none
  * @note   none
  * @see    none
  */
uint16_t Get_Adc_Average(uint8_t adc_channel_addr, uint8_t times)
{
	uint32_t temp_val = 0;
	uint8_t t;
	for (t = 0; t < times; t++)
	{
		temp_val += get_adc_data(adc_channel_addr);
		delay_ms(5);
	}
	return temp_val / times;
}

/**
  * @brief  电压计算
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
void adc_VolT(void)
{
	unsigned int adcx;
	float temp;

	gpio_bit_set(VBAT_TEST_PORT, VBAT_TEST_PIN); //开启

	adcx = Get_Adc_Average(ADC_CHANNEL_6, 10); //获取10ms平均值
	dqiot_drv_log_output("ADC值 is\r\n");
	dqiot_drv_log_output_data('#', (adcx >> 8));
	dqiot_drv_log_output_data('#', adcx);
	temp = (float)adcx * (3.3 / 4095); //计算电压
	adcx = temp;					   //获取整数部分值
	dqiot_drv_log_output("电压值 is\r\n");
	dqiot_drv_log_output_data('#', adcx);
	temp -= adcx; //获取小数部分值
	temp *= 1000;
	dqiot_drv_log_output_data('#', temp);

	if (temp < 100 && adcx == 1 || adcx < 1) //<3.55v
		mmi_dq_aud_play_with_id(AUD_BASE_ID_LOW_BATTERY);

	gpio_bit_reset(VBAT_TEST_PORT, VBAT_TEST_PIN); //关闭
}

/*!
    \brief      adc isr
    \param[in]  none
    \param[out] none
    \retval     none
*/
#if ADC_MODE == 0
void adc_isr(void) interrupt 11
{
	INT_ADC_CLR();
	g_bAdcIntFlag = 1;
}
#endif

#if ADC_HANDLE
/*!
    \brief      data sort 
    \param[in]  buffer,count
    \param[out] none
    \retval     sort avedata
*/
uint8_t byd_data_sort(uint8_t *buffer, uint8_t count)
{
	uint8_t i = 0, j = 0;
	uint8_t temp = 0;
	uint16_t average = 0;

	for (i = 0; i < count; i++)
	{
		for (j = i; j < count - 1; j++)
		{
			if ((*(buffer + i)) >= (*(buffer + j + 1)))
			{
				temp = (*(buffer + i));
				(*(buffer + i)) = (*(buffer + j + 1));
				(*(buffer + j + 1)) = temp;
			}
		}
	}
	for (i = 3; i < count - 3; i++)
	{
		average += (*(buffer + i));
	}

	return (uint8_t)(average / (count - 6));
}

/*!
    \brief      filter adc data 
    \param[in]  buffer:	data array
				count:	data number
				addr:	adc channel addr
				adc_noise
    \param[out] none
    \retval     filter data 
*/
uint8_t byd_adcdata(uint8_t addr)
{
	uint8_t i = 0, j = 0;
	uint8_t avg_cnt = 0;

	int adc_differ = 0;
	uint16_t average = 0;

	for (i = 0; i < ADC_MAX_COUNT; i++)
	{
		adc_differ = (int)g_ucAdcRawdata[i] - (int)g_ucAdcBaseline[addr];
		if (adc_differ >= 0)
		{
			if (adc_differ <= ADC_NOISE_THRESHOLD)
			{
				avg_cnt++;
				average += g_ucAdcRawdata[i];
			}
		}
		else
		{
			if (adc_differ >= -((int)ADC_NOISE_THRESHOLD))
			{
				avg_cnt++;
				average += g_ucAdcRawdata[i];
			}
		}
	}

	if (avg_cnt == 0)
	{
		g_ucAdcBaseline[addr] = byd_data_sort(g_ucAdcRawdata, ADC_MAX_COUNT);
	}
	else
	{
		g_ucAdcBaseline[addr] = average / avg_cnt;
	}

	return g_ucAdcBaseline[addr];
}

/*!
    \brief      adc data handle 
    \param[in]  adc channel address
    \param[out] none
    \retval     adc data
*/

uint8_t byd_adc_handle(uint8_t adc_channel_addr)
{
	uint8_t i;

	for (i = 0; i < ADC_MAX_COUNT; i++)
	{
		g_ucAdcRawdata[i] = (uint8_t)(get_adc_data(adc_channel_addr) >> 4); //ADC转化为8位,存储到数组对应位置处
		delay_ms(1);
	}

	if ((g_ucAdcBaseFlag & (0x01 << adc_channel_addr)) == 0)
	{
		g_ucAdcBaseFlag |= (0x01 << adc_channel_addr);
		g_ucAdcBaseline[adc_channel_addr] = byd_data_sort(g_ucAdcRawdata, ADC_MAX_COUNT); //冒泡排序并取中间的均值作为初始上电ADC平均值
	}
	else
	{
		g_ucAdcBaseline[adc_channel_addr] = byd_adcdata(adc_channel_addr); //获得处理后的ADC值
	}
	return g_ucAdcBaseline[adc_channel_addr];
}
#endif

/*!
    \brief      adc work example
    \param[in]  none
    \param[out] none
    \retval     none
*/

void byd_adc_work(void)
{
	uint16_t temp;

#if ADC_HANDLE
	temp = byd_adc_handle(ADC_CHANNEL_0);
#else
	temp = get_adc_data(ADC_CHANNEL_0);
#endif
}

void data_AD()
{
}
