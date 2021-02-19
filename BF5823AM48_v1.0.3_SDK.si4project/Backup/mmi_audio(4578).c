#ifndef __MMI_AUD_C__
#define __MMI_AUD_C__

#include "mmi_audio.h"
#include "dqiot_drv_audio.h"

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_aud_get_audio_id(unsigned char text_id)
{
	unsigned char i = 0;
	
	for(i=0;msg_aud_list[i].msg_id<STR_ID_MAX_COUNT;i++)
	{
		if(msg_aud_list[i].msg_id == text_id)
		{
			break;
		}
	}

	return msg_aud_list[i].aud_id;
}

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_aud_play_with_id(unsigned short aud_id,drv_aud_play_cb play_handle)
{
	play_handle = NULL;
	drv_audio_play(aud_id);
	return;
}


/*
parameter: 
	none
return :
	none
*/
void mmi_dq_aud_stop(void)
{
	
}
#endif//__MMI_AUD_C__
