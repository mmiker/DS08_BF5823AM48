#ifndef __MMI_SYS_C__
#define __MMI_SYS_C__

#include "mmi_feature.h"
#include "mmi_sys.h"
#include "mmi_audio.h"
#include "mmi_queue.h"

/*
function: system enter sleep
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_init(void)
{
	mmi_InitQueue();
	mmi_ms_pwd_init_var();
}
/*
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_show_message_with_id(unsigned char text_id,unsigned long time_msec)
{
	unsigned char i = 0;
	unsigned char audio_id = 0;
	
	time_msec = 0;
	
#ifdef __LOCK_AUDIO_SUPPORT__
	audio_id = mmi_dq_aud_get_audio_id(text_id);

	mmi_dq_aud_play_with_id(audio_id,0);

#endif
	return;
}

/*
function: system enter sleep
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_enter_sleep(void)
{
	
}

#endif//__MMI_SYS_C__