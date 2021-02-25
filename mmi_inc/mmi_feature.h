#ifndef __MMI_FEATURE_H__
#define __MMI_FEATURE_H__

#include "dq_project.h"

#ifdef __DQ_PROJECT_DS08__
	#define __LOCK_RFID_CARD_SUPPORT__
	#define __LOCK_AUDIO_SUPPORT__
	#define __LOCK_KEY_SUPPORT__
	#define __LOCK_FP_SUPPORT__
	#define __PREIPHERAL_FP_SY_SUPPORT__
	#ifdef __LOCK_KEY_SUPPORT__
		#define BYD_CTK_ENABLE
	#endif
#endif

<<<<<<< HEAD
=======
// #define __FACTORY_TEST_SUPPORT__

>>>>>>> six commit
#endif //__MMI_FEATURE_H__

