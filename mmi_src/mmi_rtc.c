#ifndef __BASE_MMI_RTC_C__
#define __BASE_MMI_RTC_C__
#include "mmi_feature.h"
#ifdef __LOCK_VIRTUAL_PASSWORD__

#include "nrf_drv_timer.h"
#include "nrf_drv_rtc.h"
#include "nrf_drv_clock.h"
#include "app_util_platform.h"
#include "nrf_log.h"
#include "mmi_rtc.h"
#include "mmi_ms.h"
#include "mmi_sys.h"
//#include "mmi_cal.h"
#include "mmi_oled.h"

static unsigned char RTC_time_update = 0;
//static unsigned char RTC_Refresh_flag = 0;

struct tm rtc_time;
unsigned int RTC_count_flag = 0;
unsigned char rtc_init_flag = 0;

#ifdef __MMI_RTC_SUPPORT__
#define COMPARE_COUNTERTIME  		(1UL)                                        /**< Get Compare event COMPARE_TIME seconds after the counter starts from 0. */
const nrf_drv_rtc_t mmi_dq_rtc_instance = NRF_DRV_RTC_INSTANCE(1); /**< Declaring an instance of nrf_drv_rtc for RTC0. */
/** @brief: Function for handling the RTC0 interrupts.
 * Triggered on TICK and COMPARE0 match.
 https://blog.csdn.net/ldcung/article/details/77816430?utm_source=blogxgwz7
 */
static void rtc_handler(nrf_drv_rtc_int_type_t int_type)
{
    if (int_type == NRF_DRV_RTC_INT_COMPARE0)
    {
		//NRF_LOG_PRINTF_DEBUG("###### rtc_handler NRF_DRV_RTC_INT_COMPARE0\n");
    }
    else if (int_type == NRF_DRV_RTC_INT_TICK)
    {
    	RTC_count_flag++;
    	if(RTC_count_flag == 8)//32768)
    	{
    		RTC_count_flag = 0;
			mmi_dq_rtc_updata();
			if(mmi_dq_ms_get_machine_status() == BASE_STATUS_M_IDLE)
			{
				#ifdef __LOCK_OLED_SUPPORT__
				mmi_dq_oled_updata_datetime(RTC_time_update);
				#endif
			}
    	}
    }
}

/** @brief Function initialization and configuration of RTC driver instance.
 */
 static void rtc_config(void)
{
    uint32_t err_code;
	
    //Initialize RTC instance
    nrf_drv_rtc_config_t config=NRF_DRV_RTC_DEFAULT_CONFIG(1);
    config.prescaler = 4095;
    err_code = nrf_drv_rtc_init(&mmi_dq_rtc_instance, &config, rtc_handler);//初始化RTC
    APP_ERROR_CHECK(err_code);

    //Enable tick event & interrupt
    nrf_drv_rtc_tick_enable(&mmi_dq_rtc_instance, true);//使能tick事件

    //Set compare channel to trigger interrupt after COMPARE_COUNTERTIME seconds
    err_code = nrf_drv_rtc_cc_set(&mmi_dq_rtc_instance, 0, COMPARE_COUNTERTIME * RTC1_CONFIG_FREQUENCY, true);
    APP_ERROR_CHECK(err_code);

    //Power on RTC instance
    nrf_drv_rtc_enable(&mmi_dq_rtc_instance);
}

/** @brief Function starting the internal LFCLK XTAL oscillator.
 */
static void lfclk_config(void)
{
    ret_code_t err_code = nrf_drv_clock_init(NULL);
    APP_ERROR_CHECK(err_code);

    nrf_drv_clock_lfclk_request();
}
#endif
/*
parameter: 
	none
return :
	none
*/
void mmi_dq_rtc_timer_init (void)       
{
#ifdef __MMI_RTC_SUPPORT__
	mmi_dq_rtc_set_time(1970,0,1,0,0,0);
	lfclk_config();
	rtc_config();
#else
	mmi_dq_rtc_set_time(1970,0,1,0,0,0);
#endif
	rtc_init_flag = 1;
	return;
}

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_rtc_set_time(uint32_t year, uint32_t month, uint32_t day, uint32_t hour, uint32_t minute, uint32_t second)
{
    rtc_time.tm_year = year - 1900;
    rtc_time.tm_mon = month;
    rtc_time.tm_mday = day;
    rtc_time.tm_hour = hour;
    rtc_time.tm_min = minute;
    rtc_time.tm_sec = second;
}

void mmi_dq_rtc_get_time_2(uint32_t *year, uint32_t *month, uint32_t *day, uint32_t *hour, uint32_t *minute, uint32_t *second)
{
	*year = rtc_time.tm_year + 1900;
	*month = rtc_time.tm_mon;
	*day = rtc_time.tm_mday;
	*hour = rtc_time.tm_hour;
	*minute = rtc_time.tm_min;
	*second = rtc_time.tm_sec;

}

#if 0
void mmi_dq_rtc_set_time_test(uint32_t year, uint32_t month, uint32_t day, uint32_t hour, uint32_t minute)
{
    rtc_time.tm_year = year + 100;
    rtc_time.tm_mon = month-1;
    rtc_time.tm_mday = day;
    rtc_time.tm_hour = hour;
    rtc_time.tm_min = minute;
}
#endif
/*
parameter: 
	none
return :
	none
*/
void mmi_dq_rtc_get_time(struct tm *time)
{
	time->tm_year = rtc_time.tm_year;
	time->tm_mon = rtc_time.tm_mon;
	time->tm_mday = rtc_time.tm_mday;
	time->tm_hour = rtc_time.tm_hour;
	time->tm_min = rtc_time.tm_min;
	time->tm_sec = rtc_time.tm_sec;
	//time->tm_wday =  mmi_dq_rtc_get_week_info();
	return;
}

uint8_t mmi_dq_rtc_check_time(void)
{
	if(rtc_time.tm_year<100)
		return 1;
	else
		return 0;
}
/*
parameter: 
	none
return :
	none
*/
static char mmi_dq_rtc_not_leap(void)      //check for leap year
{
	if (!(rtc_time.tm_year%100))
	{
		return (char)((rtc_time.tm_year+1900)%400);
	}
	else
	{
		return (char)(rtc_time.tm_year%4);
	}
}
/*
parameter: 
	none
return :
	none
*/
void mmi_dq_rtc_updata(void)
{
	RTC_time_update = UPDATA_SEC;
	if (++rtc_time.tm_sec == 60)
	{
		RTC_time_update = UPDATA_HM;
		rtc_time.tm_sec = 0;
		if (++rtc_time.tm_min == 60)
		{
			rtc_time.tm_min = 0;
			if (++rtc_time.tm_hour == 24)
			{
				RTC_time_update = UPDATA_DATE;
				rtc_time.tm_hour = 0;
				if (++rtc_time.tm_mday == 32)
				{
					rtc_time.tm_mon++;
					rtc_time.tm_mday=1;
				}
				else if (rtc_time.tm_mday == 31)
				{
					if ((rtc_time.tm_mon == 3) || (rtc_time.tm_mon == 5) || (rtc_time.tm_mon == 8) || (rtc_time.tm_mon == 10))
					{
						rtc_time.tm_mon++;
						rtc_time.tm_mday = 1;
					}
				}
				else if (rtc_time.tm_mday == 30)
				{
					if(rtc_time.tm_mon == 1)
					{
						rtc_time.tm_mon++;
						rtc_time.tm_mday = 1;
					}
				}
				else if (rtc_time.tm_mday == 29)
				{
					if((rtc_time.tm_mon == 1) && (mmi_dq_rtc_not_leap()))
					{
						rtc_time.tm_mon++;
						rtc_time.tm_mday = 1;
					}
				}
				if (rtc_time.tm_mon == 12)
				{
					rtc_time.tm_mon = 0;
					rtc_time.tm_year++;
				}
			}
		}
	}	
}

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_rtc_get_time_by_sec(uint32_t time_sec)
{
	time_t now = time_sec;
	time_t old_now = mmi_dq_rtc_get_sys_sec_info();
	struct tm *tm_now ;
	tm_now = localtime (&now);

	rtc_time.tm_year = tm_now->tm_year;
    rtc_time.tm_mon = tm_now->tm_mon;
    rtc_time.tm_mday = tm_now->tm_mday;
    rtc_time.tm_hour = tm_now->tm_hour;
    rtc_time.tm_min = tm_now->tm_min;
    rtc_time.tm_sec = tm_now->tm_sec;
	rtc_time.tm_wday = tm_now->tm_wday;

	if(now>old_now)
		mmi_dq_sys_lock_update_lock_time(now-old_now);
	return 0;
}

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_rtc_get_week_info(void)
{
	time_t now;
	struct tm *tm_now ;
	now = mktime(&rtc_time);
	tm_now = localtime (&now);
	return tm_now->tm_wday;
}

/*
parameter: 
	none
return :
	none
*/
time_t mmi_dq_rtc_get_sys_sec_info(void)
{
	time_t now;
	if(rtc_init_flag == 0)
		mmi_dq_rtc_timer_init();
	//NRF_LOG_PRINTF_DEBUG("#### mmi_dq_rtc_get_sys_sec_info start  rtc_init_flag = %d\n",rtc_init_flag);
	//NRF_LOG_PRINTF_DEBUG("#### mmi_dq_rtc_get_sys_sec_info start  rtc_time.tm_year = %d\n",rtc_time.tm_year);
	//NRF_LOG_PRINTF_DEBUG("#### mmi_dq_rtc_get_sys_sec_info start  rtc_time.tm_mon = %d\n",rtc_time.tm_mon);
	//NRF_LOG_PRINTF_DEBUG("#### mmi_dq_rtc_get_sys_sec_info start  rtc_time.tm_mday = %d\n",rtc_time.tm_mday);
	//NRF_LOG_PRINTF_DEBUG("#### mmi_dq_rtc_get_sys_sec_info start  rtc_time.tm_hour = %d\n",rtc_time.tm_hour);
	//NRF_LOG_PRINTF_DEBUG("#### mmi_dq_rtc_get_sys_sec_info start  rtc_time.tm_min = %d\n",rtc_time.tm_min);
	//NRF_LOG_PRINTF_DEBUG("#### mmi_dq_rtc_get_sys_sec_info start  rtc_time.tm_sec = %d\n",rtc_time.tm_sec);
	//NRF_LOG_PRINTF_DEBUG("#### mmi_dq_rtc_get_sys_sec_info start  rtc_time.tm_wday = %d\n",rtc_time.tm_wday);
	now = mktime(&rtc_time);
	return now;
}


/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_rtc_get_update_flag(void)
{
	return RTC_time_update;
}

#endif //__LOCK_VIRTUAL_PASSWORD__
#endif//__BASE_MMI_RTC_C__

