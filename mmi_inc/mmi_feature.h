#ifndef __MMI_FEATURE_H__
#define __MMI_FEATURE_H__

#include "dq_project.h"

#ifdef __DQ_PROJECT_DS08__
	#define __LOCK_RFID_CARD_SUPPORT__
	#define __LOCK_AUDIO_SUPPORT__
	#define __LOCK_KEY_SUPPORT__
	#define __LOCK_FP_SUPPORT__
#ifdef __LOCK_FP_SUPPORT__
	#define __LOCK_FP_SY_SUPPORT__
#endif
	#define __LOCK_WIFI_SUPPORT__
	#define __LOCK_MOTOR_SUPPORT__
#endif
#ifdef __LOCK_KEY_SUPPORT__
	#define BYD_CTK_ENABLE
#endif
	#define __LOCK_BUS_SUPPORT__
#ifdef __LOCK_WIFI_SUPPORT__
	#define __LOCK_110_SUPPORT__
#endif

#define __FACTORY_TEST_SUPPORT__

#endif //__MMI_FEATURE_H__

