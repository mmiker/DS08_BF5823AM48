#ifndef __MMI_AUD_C__
#define __MMI_AUD_C__

#include "mmi_audio.h"
#include "dqiot_drv_audio.h"

#ifdef __LOCK_AUDIO_SUPPORT__
#ifdef __AUD_PLAY_BY_ARR__

const unsigned char aud_play_arr[] = 
{
	AUD_BASE_ID_INPUT_68_PWD,AUD_BASE_ID_INPUT_END,0,		//AUD_ID_INPUT_68_PWD = 0,//������6-8λ���룬��#������
	AUD_BASE_ID_PWD_68_LEN,AUD_BASE_ID_REINPUT,0,			//AUD_ID_PWD_68_LEN = 3,//����ӦΪ6-8λ������������
	AUD_BASE_ID_PWD_INPUT_AGAIN,AUD_BASE_ID_INPUT_END,0,	//AUD_ID_PWD_INPUT_AGAIN = 6,//���ٴ��������룬��#������
	AUD_BASE_ID_CONTINUE,AUD_BASE_ID_INPUT_BACK,0,			//AUD_ID_CONTINUE = 9,//�����밴#�����ذ�*
	AUD_BASE_ID_FAIL,AUD_BASE_ID_CONTACT_ADMIN,0,			//AUD_ID_ADD_PWD_FAIL = 12,//���ʧ�ܣ�����ϵ����Ա
	AUD_BASE_ID_INPUT_OLD_PWD,AUD_BASE_ID_INPUT_END,0,		//AUD_ID_INPUT_OLD_PWD = 15,//����������룬��#������
	AUD_BASE_ID_PWD_NOT_EXIST,AUD_BASE_ID_REINPUT,0,		//AUD_ID_PWD_NOT_EXIST = 18,//���벻���ڣ�����������
	AUD_BASE_ID_INPUT_NEW_PWD,AUD_BASE_ID_INPUT_END,0,		//AUD_ID_INPUT_NEW_PWD = 21,//�����������룬��#������
	AUD_BASE_ID_PWD_INPUT_AGAIN,AUD_BASE_ID_INPUT_END,0,	//AUD_ID_INPUT_NEW_PWD_AGAIN = 24,//�������������룬��#������
															//AUD_ID_CHG_FAIL = 12,//�޸�ʧ�ܣ�����ϵ����Ա
															//AUD_ID_DEL_FAIL = 12,//ɾ��ʧ�ܣ�����ϵ����Ա
	AUD_BASE_ID_INPUT_DEL_PWD,AUD_BASE_ID_INPUT_END,0,		//AUD_ID_INPUT_DEL_NUM = 27,//������Ҫɾ���ı�Ż����룬��#������
	AUD_BASE_ID_NUM_NOT_EXIST,AUD_BASE_ID_REINPUT,0,		//AUD_ID_NUM_NOT_EXIST = 30,//��Ų����ڣ�����������
	AUD_BASE_ID_INPUT_CONFIRM,AUD_BASE_ID_INPUT_BACK,0,		//AUD_ID_DEL_PWD_CONFIRM = 33,//�����밴#��ȷ��ɾ����ȡ���밴*��
															//AUD_ID_DEL_CONFIRM = 9,//����ɾ���밴#�������밴*
															//AUD_ID_CLR_PWD_CONFIRM = 33,//��#��ȷ��ɾ���������룬ȡ���밴*��
	AUD_BASE_ID_FAIL,AUD_BASE_ID_RETRY,0,					//AUD_ID_ADD_FAIL_RETRY = 36,//���ʧ�ܣ�������
															//AUD_ID_CHG_FAIL_RETRY = 36,//�޸�ʧ�ܣ�������
															//AUD_ID_CHG_CONTINUE_CONFIRM = 9,//�����޸��밴#�������밴*
	//0x27
	AUD_BASE_ID_FP_NOT_EXIST,AUD_BASE_ID_REINPUT,0,			//AUD_ID_FP_NOT_EXIST = 39,//ָ�Ʋ����ڣ�����������
															//AUD_ID_DEL_FP_CONFIRM = 33,//��ָ�ư�#ȷ��ɾ����ȡ���밴*
															//AUD_ID_DEL_FAIL_RETRY = 36,//ɾ��ʧ�ܣ�������
															//AUD_ID_CLR_FP_CONFIRM = 33,//��#ȷ��ɾ������ָ�ƣ�ȡ���밴*
	AUD_BASE_ID_RFCARD_NOT_EXIST,AUD_BASE_ID_REINPUT,0,		//AUD_ID_RFCARD_NOT_EXIST = 42,//RF�������ڣ�����������
															//AUD_ID_DEL_RFCARD_CONFIRM = 33,//��RF����#ȷ��ɾ����ȡ���밴*
															//AUD_ID_CLR_RFCARD_CONFIRM = 33,//��#ȷ��ɾ������RF����ȡ���밴*
	AUD_BASE_ID_INPUT_ADMIN_PWD,AUD_BASE_ID_INPUT_END,0,	//AUD_ID_INPUT_ADMIN_PWD = 45,//���������Ա���룬��#������
															//AUD_ID_INPUT_NEW_ADMIN_PWD = 0,//�������¹���Ա���룬��#������
	//
															//AUD_ID_INPUT_NEW_ADMIN_PWD_AGAIN = 6,//���ٴ������¹���Ա���룬��#������
	AUD_BASE_ID_PWD_EXIST,AUD_BASE_ID_REINPUT,0,			//AUD_ID_PWD_EXIST = 48,//�����Ѵ��ڣ�����������
	AUD_BASE_ID_ADD_ADMIN_PWD_FIRST,AUD_BASE_ID_INPUT_END,0,//AUD_ID_ADD_ADMIN_PWD_FIRST = 51,//Ϊ������ʹ�ð�ȫ��������ӹ���Ա���룬��#������
															//AUD_ID_INPUT_ADMIN_PWD_INIT_AGAIN = 6,//���ٴ��������Ա���룬��#������
	AUD_BASE_ID_PWD_WRONG,AUD_BASE_ID_RETRY,0,				//AUD_ID_PWD_WRONG_TRY = 54,//�������,������
	AUD_BASE_ID_FP_WRONG,AUD_BASE_ID_RETRY,0,				//AUD_ID_FP_WRONG_TRY = 57,//ָ�ƴ���������
	AUD_BASE_ID_RFCARD_WRONG,AUD_BASE_ID_RETRY,0,			//AUD_ID_RFCARD_WRONG_TRY = 60,//RF������������
	//
	AUD_BASE_ID_SYS_NUM_1,AUD_BASE_ID_SYS_CHG_ADMIN_PWD,
	AUD_BASE_ID_SYS_NUM_2,AUD_BASE_ID_SYS_CHG_ADMIN_FP,AUD_BASE_ID_INPUT_BACK,0,		//AUD_ID_SYS_ADMIN = 63,//����Ա
	AUD_BASE_ID_SYS_NUM_1,AUD_BASE_ID_SYS_PRO_AUDIO,
	AUD_BASE_ID_SYS_NUM_2,AUD_BASE_ID_SYS_OPEN_MODE,AUD_BASE_ID_INPUT_BACK,0,	//AUD_ID_SYS_SETTING = 69,//����
	AUD_BASE_ID_SYS_NUM_1,AUD_BASE_ID_SYS_NO1_ADMIN_FP,
	AUD_BASE_ID_SYS_NUM_2,AUD_BASE_ID_SYS_NO2_ADMIN_FP,AUD_BASE_ID_INPUT_BACK,0,		//AUD_ID_SYS_CHG_ADMIN_FP = 75,//�޸Ĺ���Աָ��
	AUD_BASE_ID_SYS_NUM_1,AUD_BASE_ID_SYS_OPEN_PRO_AUDIO,
	AUD_BASE_ID_SYS_NUM_2,AUD_BASE_ID_SYS_CLOSE_PRO_AUDIO,AUD_BASE_ID_INPUT_BACK,0,		//AUD_ID_SYS_PRO_AUDIO = 81,//��ʾ��
	AUD_BASE_ID_SYS_NUM_1,AUD_BASE_ID_SYS_SIN_OPEN_MODE,
	AUD_BASE_ID_SYS_NUM_2,AUD_BASE_ID_SYS_DBL_OPEN_MODE,AUD_BASE_ID_INPUT_BACK,0,//AUD_ID_SYS_OPEN_MODE = 87,//���ŷ�ʽ

	AUD_BASE_ID_SYS_NUM_1,AUD_BASE_ID_SYS_ADMIN,
	AUD_BASE_ID_SYS_NUM_2,AUD_BASE_ID_SYS_SETTING,
	AUD_BASE_ID_SYS_NUM_3,AUD_BASE_ID_SYS_RESTORE,AUD_BASE_ID_INPUT_BACK,0,		//AUD_ID_SYSTEM2 = 93,//ϵͳ2

	AUD_BASE_ID_SYS_NUM_1,AUD_BASE_ID_SYS_ADD_PWD,
	AUD_BASE_ID_SYS_NUM_2,AUD_BASE_ID_SYS_CHG_PWD,
	AUD_BASE_ID_SYS_NUM_3,AUD_BASE_ID_SYS_DEL_PWD,
	AUD_BASE_ID_SYS_NUM_4,AUD_BASE_ID_SYS_CLR_PWD,AUD_BASE_ID_INPUT_BACK,0,		//AUD_ID_SYS_PASSWORD = 101,//����
	AUD_BASE_ID_SYS_NUM_1,AUD_BASE_ID_SYS_ADD_FP,
	AUD_BASE_ID_SYS_NUM_2,AUD_BASE_ID_SYS_CHG_FP,
	AUD_BASE_ID_SYS_NUM_3,AUD_BASE_ID_SYS_DEL_FP,
	AUD_BASE_ID_SYS_NUM_4,AUD_BASE_ID_SYS_CLR_FP,AUD_BASE_ID_INPUT_BACK,0,			//AUD_ID_SYS_FP = 111,//ָ��
	AUD_BASE_ID_SYS_NUM_1,AUD_BASE_ID_SYS_ADD_RFCARD,
	AUD_BASE_ID_SYS_NUM_2,AUD_BASE_ID_SYS_CHG_RFCARD,
	AUD_BASE_ID_SYS_NUM_3,AUD_BASE_ID_SYS_DEL_RFCARD,
	AUD_BASE_ID_SYS_NUM_4,AUD_BASE_ID_SYS_CLR_RFCARD,AUD_BASE_ID_INPUT_BACK,0,		//AUD_ID_SYS_RFCARD = 121,//RF��


	AUD_BASE_ID_NOT_SAME,AUD_BASE_ID_REINPUT,0,//AUD_ID_PWD_NOT_SAME_RETRY	 = 131//������������벻һ��,����������

	AUD_BASE_ID_SYS_NUM_1,AUD_BASE_ID_SYS_CHG_ADMIN_PWD,
	AUD_BASE_ID_INPUT_BACK,0,		//AUD_ID_SYS_ADMIN = 134,//����Ա
#if 0
#ifdef __LOCK_RFID_CARD_SUPPORT__	
#if defined(__LOCK_FP_SUPPORT__)||defined(__LOCK_FP_SUPPORT2__)||defined(__LOCK_FP_SUPPORT1_2__)
	AUD_BASE_ID_SYS_NUM_1,AUD_BASE_ID_SYS_PASSWORD,
	AUD_BASE_ID_SYS_NUM_2,AUD_BASE_ID_SYS_FP,
	AUD_BASE_ID_SYS_NUM_3,AUD_BASE_ID_SYS_RFCARD,
	AUD_BASE_ID_SYS_NUM_4,AUD_BASE_ID_SYS_ADMIN,
	AUD_BASE_ID_SYS_NUM_5,AUD_BASE_ID_SYS_SETTING,
	AUD_BASE_ID_SYS_NUM_6,AUD_BASE_ID_SYS_RESTORE,AUD_BASE_ID_INPUT_BACK,0,		//AUD_ID_SYSTEM = 138,//ϵͳ
#else 
	AUD_BASE_ID_SYS_NUM_1,AUD_BASE_ID_SYS_PASSWORD,
	AUD_BASE_ID_SYS_NUM_2,AUD_BASE_ID_SYS_RFCARD,
	AUD_BASE_ID_SYS_NUM_3,AUD_BASE_ID_SYS_ADMIN,
	AUD_BASE_ID_SYS_NUM_4,AUD_BASE_ID_SYS_SETTING,
	AUD_BASE_ID_SYS_NUM_5,AUD_BASE_ID_SYS_RESTORE,AUD_BASE_ID_INPUT_BACK,0,		//AUD_ID_SYSTEM = 138,//ϵͳ
#endif
#else
	AUD_BASE_ID_SYS_NUM_1,AUD_BASE_ID_SYS_PASSWORD,
	AUD_BASE_ID_SYS_NUM_2,AUD_BASE_ID_SYS_FP,
	AUD_BASE_ID_SYS_NUM_3,AUD_BASE_ID_SYS_ADMIN,
	AUD_BASE_ID_SYS_NUM_4,AUD_BASE_ID_SYS_SETTING,
	AUD_BASE_ID_SYS_NUM_5,AUD_BASE_ID_SYS_RESTORE,AUD_BASE_ID_INPUT_BACK,0,		//AUD_ID_SYSTEM = 138,//ϵͳ
#endif
#endif

	//AUD_BASE_ID_SYS_DBL_OPEN_MODE,AUD_BASE_ID_PRESS_FP,0,//AUD_ID_DBL_OPEN_MODE_FP = 145
	//AUD_BASE_ID_SYS_DBL_OPEN_MODE,AUD_BASE_ID_INPUT_68_PWD,0,//AUD_ID_DBL_OPEN_MODE_PASSWORD = 148

			//AUD_ID_ADD_PWD_FULL = 12,//��������������ϵ����Ա
			//AUD_ID_FP_ADD_FULL = 12,//ָ������������ϵ����Ա
			//AUD_ID_RFCARD_FULL = 12,//RF������������ϵ����Ա
};


#endif

/*
parameter: 
	none
return :
	none
*/
AUD_PLAY_ID mmi_dq_aud_get_audio_id(unsigned char text_id)
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
void mmi_dq_aud_play_with_id(unsigned char aud_id)
{
#ifdef __AUD_PLAY_BY_ARR__	
	if(aud_id<AUD_BASE_ID_MAX)
		dqiot_drv_audio_play(aud_id);
#if 0
	else if(aud_id == AUD_ID_SYSTEM)
	{
		unsigned char num = 1;
		dqiot_drv_audio_play(AUD_BASE_ID_SYS_NUM_0 + num);
		dqiot_drv_audio_play(AUD_BASE_ID_SYS_PASSWORD);
		num++;
#if defined(__LOCK_FP_SUPPORT__)||defined(__LOCK_FP_SUPPORT2__)
		dqiot_drv_audio_play(AUD_BASE_ID_SYS_NUM_0 + num);
		dqiot_drv_audio_play(AUD_BASE_ID_SYS_FP);
		num++;
#elif defined(__LOCK_FP_SUPPORT1_2__)
		if(mmi_dq_fp_get_type() != FP_NONE)
		{
			dqiot_drv_audio_play(AUD_BASE_ID_SYS_NUM_0 + num);
			dqiot_drv_audio_play(AUD_BASE_ID_SYS_FP);
			num++;
		}
#endif
#ifdef __LOCK_RFID_CARD_SUPPORT__	
		if(mmi_dq_rfid_get_init_state() == 0)
		{
			dqiot_drv_audio_play(AUD_BASE_ID_SYS_NUM_0 + num);
			dqiot_drv_audio_play(AUD_BASE_ID_SYS_RFCARD);
			num++;
		}
#endif
		dqiot_drv_audio_play(AUD_BASE_ID_SYS_NUM_0 + num);
		dqiot_drv_audio_play(AUD_BASE_ID_SYS_ADMIN);
		num++;
		dqiot_drv_audio_play(AUD_BASE_ID_SYS_NUM_0 + num);
		dqiot_drv_audio_play(AUD_BASE_ID_SYS_SETTING);
		num++;
		dqiot_drv_audio_play(AUD_BASE_ID_SYS_NUM_0 + num);
		dqiot_drv_audio_play(AUD_BASE_ID_SYS_RESTORE);
		dqiot_drv_audio_play(AUD_BASE_ID_INPUT_BACK);
	}
#endif
	else
	{
		unsigned char a = aud_id - AUD_BASE_ID_MAX;
		while(aud_play_arr[a]!=0)
		{
			dqiot_drv_audio_play(aud_play_arr[a]);
			a++;
		}
	}
#else
	dqiot_drv_audio_play(aud_id);
#endif
	
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
	dqiot_drv_audio_stop();
}

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_aud_get_state(void)
{
	return dqiot_drv_audio_get_state();
}
#endif
#endif//__MMI_AUD_C__
