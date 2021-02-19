#ifndef __MMI_AUDIO_H__
#define __MMI_AUDIO_H__

#include "string.h"
#include "mmi_com.h"


typedef void (*drv_aud_play_cb)(void);

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_aud_get_audio_id(unsigned char text_id);
/*
parameter: 
	none
return :
	none
*/
void mmi_dq_aud_stop(void);

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_aud_play_with_id(unsigned short aud_id,drv_aud_play_cb play_handle);

#endif //__MMI_AUDIO_H__

