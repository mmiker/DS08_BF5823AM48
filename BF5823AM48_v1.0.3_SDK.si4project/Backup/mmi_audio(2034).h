#ifndef __MMI_AUDIO_H__
#define __MMI_AUDIO_H__

#include "string.h"
#include "mmi_feature.h"

#define __AUD_PLAY_BY_ARR__

typedef enum 
{
//---------------------------------------------------
	AUD_BASE_ID_PRO_AUDIO = 1,//������

	AUD_BASE_ID_INPUT_68_PWD = 2,//������6-8λ����
	AUD_BASE_ID_PWD_68_LEN = 3, //����ӦΪ6-8λ
	AUD_BASE_ID_PWD_INPUT_AGAIN = 4,//���ٴ���������
	AUD_BASE_ID_SUCCESS = 5,//�����ɹ�
	AUD_BASE_ID_NOT_SAME = 6,//�������벻һ��
	AUD_BASE_ID_CONTINUE = 7,//�����밴#
	AUD_BASE_ID_FAIL = 8,//����ʧ��
	AUD_BASE_ID_INPUT_OLD_PWD = 9,//�����������
	AUD_BASE_ID_PWD_NOT_EXIST = 10,//���벻����
	AUD_BASE_ID_INPUT_NEW_PWD = 11,//������������
	AUD_BASE_ID_PWD_SAME = 12,//�¾�����һ��
	AUD_BASE_ID_INPUT_DEL_PWD = 13,//������Ҫɾ��������
	AUD_BASE_ID_NUM_NOT_EXIST = 14,//��Ų�����
	AUD_BASE_ID_INPUT_CONFIRM = 15,//ȷ���밴#
	AUD_BASE_ID_PRESS_FP = 16,//�밴��ָ
	AUD_BASE_ID_PRESS_FP_AGAIN = 17,//���ٰ�һ��
	AUD_BASE_ID_FP_SAME = 18,//�¾�ָ��һ��
	AUD_BASE_ID_PRESS_OLD_FP = 19,//�밴�ɵ�ָ��
	AUD_BASE_ID_PRESS_NEW_FP = 20,//�밴�µ�ָ��
	AUD_BASE_ID_INPUT_DEL_FP = 21,//������Ҫɾ����ָ��
	AUD_BASE_ID_FP_NOT_EXIST = 22,//ָ�Ʋ�����
	AUD_BASE_ID_PRESS_RFCARD = 23,//��ˢ��
	AUD_BASE_ID_PRESS_RFCARD_AGAIN = 24,//����ˢһ��
	AUD_BASE_ID_RFCARD_EXIST = 25,//RF���Ѵ���
	AUD_BASE_ID_PRESS_OLD_RFCARD = 26,//��ˢ�ɿ�
	AUD_BASE_ID_PRESS_NEW_RFCARD = 27,//��ˢ�¿�
	AUD_BASE_ID_RFCARD_SAME = 28,//�¾�RF��һ��
	AUD_BASE_ID_INPUT_DEL_RFCARD = 29,//������Ҫɾ����RF��
	AUD_BASE_ID_RFCARD_NOT_EXIST = 30,//RF��������
	AUD_BASE_ID_PWD_EXIST = 31,//�����Ѵ���
	AUD_BASE_ID_INPUT_ADMIN_PWD = 32,//���������Ա����
	AUD_BASE_ID_SET_SUCESS = 33,//���óɹ�
	AUD_BASE_ID_SET_FAIL = 34,//����ʧ��
	AUD_BASE_ID_INPUT_END = 35,//��#������
	AUD_BASE_ID_RETRY = 36,//������
	AUD_BASE_ID_INPUT_BACK = 37,//���ذ�*
	AUD_BASE_ID_CONTACT_ADMIN = 38,//����ϵ����Ա
	AUD_BASE_ID_REINPUT = 39,//����������
	AUD_BASE_ID_ADD_ADMIN_PWD_FIRST = 40,//Ϊ������ʹ�ð�ȫ��������ӹ���Ա����
	AUD_BASE_ID_DOOR_OPEN = 41,//�ѿ���
	AUD_BASE_ID_DOOR_CLOSE = 42,//�ѹ���
	AUD_BASE_ID_PWD_WRONG = 43,//�������
	AUD_BASE_ID_FP_WRONG = 44,//ָ�ƴ���
	AUD_BASE_ID_RFCARD_WRONG = 45,//RF������
	AUD_BASE_ID_RONG_TIMES_EXCEED = 46,//��������ѳ����ƣ����Ժ�����
	AUD_BASE_ID_LOW_BATTERY = 47,//������

	AUD_BASE_ID_SYS_PASSWORD = 48,//����
	AUD_BASE_ID_SYS_FP = 49,//ָ��
	AUD_BASE_ID_SYS_RFCARD = 50,//RF��
	AUD_BASE_ID_SYS_ADMIN = 51,//����Ա
	AUD_BASE_ID_SYS_SETTING = 52,//����
	AUD_BASE_ID_SYS_RESTORE = 53,//�ָ���������
	AUD_BASE_ID_SYS_ADD_PWD = 54,//�������
	AUD_BASE_ID_SYS_CHG_PWD = 55,//�޸�����
	AUD_BASE_ID_SYS_DEL_PWD = 56,//ɾ������
	AUD_BASE_ID_SYS_CLR_PWD = 57,//ɾ����������
	AUD_BASE_ID_SYS_ADD_FP = 58,//���ָ��
	AUD_BASE_ID_SYS_CHG_FP = 59,//�޸�ָ��
	AUD_BASE_ID_SYS_DEL_FP = 60,//ɾ��ָ��
	AUD_BASE_ID_SYS_CLR_FP = 61,//ɾ������ָ��
	AUD_BASE_ID_SYS_ADD_RFCARD = 62,//���RF��
	AUD_BASE_ID_SYS_CHG_RFCARD = 63,//�޸�RF��
	AUD_BASE_ID_SYS_DEL_RFCARD = 64,//ɾ��RF��
	AUD_BASE_ID_SYS_CLR_RFCARD = 65,//ɾ������RF��
	AUD_BASE_ID_SYS_CHG_ADMIN_PWD = 66,//�޸Ĺ���Ա����
	AUD_BASE_ID_SYS_CHG_ADMIN_FP = 67,//�޸Ĺ���Աָ��
	AUD_BASE_ID_SYS_NO1_ADMIN_FP = 68,//1�Ź���Աָ��
	AUD_BASE_ID_SYS_NO2_ADMIN_FP = 69,//2�Ź���Աָ��
	AUD_BASE_ID_SYS_PRO_AUDIO = 70,//��ʾ��
	AUD_BASE_ID_SYS_CLOSE_PRO_AUDIO = 71,//�ر�
	AUD_BASE_ID_SYS_OPEN_PRO_AUDIO = 72,//����
	AUD_BASE_ID_SYS_OPEN_MODE = 73,//���ŷ�ʽ
	AUD_BASE_ID_SYS_SIN_OPEN_MODE = 74,//�����ŷ�ʽ
	AUD_BASE_ID_SYS_DBL_OPEN_MODE = 75,//˫���ŷ�ʽ
	AUD_BASE_ID_SYS_RESTORE_SUCCESS = 76,//��ʼ���ɹ�
	AUD_BASE_ID_APP_SYN = 77,//��ʹ��appͬ��
	AUD_BASE_ID_FM_KEY_INPUT = 78,//��������а���
	AUD_BASE_ID_FM_RESTORE = 79,//�밴��λ��
	AUD_BASE_ID_SYS_NUM_0 = 80,//0
	AUD_BASE_ID_SYS_NUM_1 = 81,//1
	AUD_BASE_ID_SYS_NUM_2 = 82,//2
	AUD_BASE_ID_SYS_NUM_3 = 83,//3
	AUD_BASE_ID_SYS_NUM_4 = 84,//4
	AUD_BASE_ID_SYS_NUM_5 = 85,//5
	AUD_BASE_ID_SYS_NUM_6 = 86,//6
	AUD_BASE_ID_SYS_NUM_7 = 87,//7
	AUD_BASE_ID_SYS_NUM_8 = 88,//8
	AUD_BASE_ID_SYS_NUM_9 = 89,//9
	AUD_BASE_ID_SYS_NUM_S = 90,//*
	AUD_BASE_ID_SYS_NUM_H = 91,//#
	AUD_BASE_ID_MEM_FULL = 92,//����ʧ�ܣ����ڴ���ռ�����

	AUD_BASE_ID_MAX,

//---------------------------------------------------
	
	AUD_ID_PRO_AUDIO				=AUD_BASE_ID_PRO_AUDIO,
	AUD_ID_INPUT_68_PWD				= 0+AUD_BASE_ID_MAX,//������6-8λ���룬��#������
	AUD_ID_PWD_68_LEN 				= 3+AUD_BASE_ID_MAX,//����ӦΪ6-8λ������������
	AUD_ID_PWD_INPUT_AGAIN 			= 6+AUD_BASE_ID_MAX,//���ٴ��������룬��#������
	AUD_ID_ADD_PWD_SUCESS 			= AUD_BASE_ID_SUCCESS,//��������ӳɹ�
	AUD_ID_PWD_NOT_SAME 			= AUD_BASE_ID_NOT_SAME,//������������벻һ��
	AUD_ID_PWD_NOT_SAME_RETRY		= 131+AUD_BASE_ID_MAX,//������������벻һ��,����������
	AUD_ID_CONTINUE_ADD_PWD 		= 9+AUD_BASE_ID_MAX,//��������밴#�������밴*
	AUD_ID_ADD_FAIL 				= 12+AUD_BASE_ID_MAX,//���ʧ�ܣ�����ϵ����Ա
	AUD_ID_PWD_FULL 				= AUD_BASE_ID_MEM_FULL,//��������������ϵ����Ա
	AUD_ID_INPUT_OLD_PWD 			= 15+AUD_BASE_ID_MAX,//����������룬��#������
	AUD_ID_PWD_NOT_EXIST 			= 18+AUD_BASE_ID_MAX,//���벻���ڣ�����������
	AUD_ID_INPUT_NEW_PWD 			= 21+AUD_BASE_ID_MAX,//�����������룬��#������
	AUD_ID_INPUT_NEW_PWD_AGAIN = 24+AUD_BASE_ID_MAX,//�������������룬��#������
	AUD_ID_CHG_PWD_SUCESS 			= AUD_BASE_ID_SUCCESS,//�������޸ĳɹ�
	AUD_ID_CHG_FAIL 				= 12+AUD_BASE_ID_MAX,//�޸�ʧ�ܣ�����ϵ����Ա
	AUD_ID_PWD_OLD_NEW_NOT_SAME = AUD_BASE_ID_PWD_SAME,//�¾����벻��һ��
	AUD_ID_INPUT_DEL_NUM 			= 27+AUD_BASE_ID_MAX,//������Ҫɾ���ı�Ż����룬��#������
	AUD_ID_NUM_NOT_EXIST 			= 30+AUD_BASE_ID_MAX,//��Ų����ڣ�����������
	AUD_ID_DEL_PWD_CONFIRM 			= 33+AUD_BASE_ID_MAX,//�����밴#��ȷ��ɾ����ȡ���밴*��
	AUD_ID_INPUT_DEL_PWD_AGAIN 		= AUD_BASE_ID_PWD_INPUT_AGAIN,//���ٴ�����Ҫɾ��������
	AUD_ID_DEL_PWD_SUCESS 			= AUD_BASE_ID_SUCCESS,//������ɾ���ɹ�
	AUD_ID_DEL_FAIL					= 12+AUD_BASE_ID_MAX,//ɾ��ʧ�ܣ�����ϵ����Ա
	AUD_ID_DEL_CONFIRM 				= 9+AUD_BASE_ID_MAX,//����ɾ���밴#�������밴*
	AUD_ID_CLR_PWD_CONFIRM 			= 33+AUD_BASE_ID_MAX,//��#��ȷ��ɾ���������룬ȡ���밴*��
	AUD_ID_CLR_PWD_SUCESS 			= AUD_BASE_ID_SUCCESS,//ɾ����������ɹ�
	AUD_ID_CLR_PWD_FAIL 			= AUD_BASE_ID_FAIL,//ɾ����������ʧ��
	AUD_ID_PRESS_FP 				= AUD_BASE_ID_PRESS_FP,//�밴��ָ
	AUD_ID_PRESS_FP_AGAIN 			= AUD_BASE_ID_PRESS_FP_AGAIN,//���ٰ�һ��
	AUD_ID_ADD_FP_SUCESS 			= AUD_BASE_ID_SUCCESS,//��ָ����ӳɹ�
	AUD_ID_FP_EXIST 				= 12+AUD_BASE_ID_MAX,//ָ���Ѵ��ڣ��뻻����ָ
	AUD_ID_ADD_FAIL_RETRY 			= 36+AUD_BASE_ID_MAX,//���ʧ�ܣ�������
	AUD_ID_FP_TWICE_NOT_SAME		= 57+AUD_BASE_ID_MAX,//���������ָ�Ʋ�һ��
	AUD_ID_FP_FULL 					= AUD_BASE_ID_MEM_FULL,//ָ������������ϵ����Ա
	AUD_ID_PRESS_OLD_FP 			= AUD_BASE_ID_PRESS_OLD_FP,//�밴�ɵ�ָ��
	AUD_ID_PRESS_NEW_FP 			= AUD_BASE_ID_PRESS_NEW_FP,//�밴�µ�ָ��
	AUD_ID_PRESS_NEW_FP_AGAIN 		= AUD_BASE_ID_PRESS_FP_AGAIN,//���ٰ�һ����ָ��
	AUD_ID_CHG_FP_SUCESS 			= AUD_BASE_ID_SUCCESS,//��ָ���޸ĳɹ�
	AUD_ID_FP_NOT_SAME 				= AUD_BASE_ID_FP_SAME,//�¾�ָ�Ʋ���һ��	
	AUD_ID_INPUT_DEL_FP_NUM 		= AUD_BASE_ID_INPUT_DEL_FP,//������Ҫɾ���ı�Ż�ָ�ƣ���#������
	AUD_ID_CHG_FAIL_RETRY 			= 36+AUD_BASE_ID_MAX,//�޸�ʧ�ܣ�������
	AUD_ID_CHG_CONTINUE_CONFIRM 	= 9+AUD_BASE_ID_MAX,//�����޸��밴#�������밴*
	//0x27
	AUD_ID_FP_NOT_EXIST 			= 39+AUD_BASE_ID_MAX,//ָ�Ʋ����ڣ�����������
	AUD_ID_DEL_FP_CONFIRM 			= 33+AUD_BASE_ID_MAX,//��ָ�ư�#ȷ��ɾ����ȡ���밴*
	AUD_ID_PRESS_DEL_FP_AGAIN 		= AUD_BASE_ID_PRESS_FP_AGAIN,//���ٰ�һ��Ҫɾ����ָ��
	AUD_ID_DEL_FP_SUCESS 			= AUD_BASE_ID_SUCCESS,//��ָ��ɾ���ɹ�
	AUD_ID_DEL_FAIL_RETRY 			= 36+AUD_BASE_ID_MAX,//ɾ��ʧ�ܣ�������
	AUD_ID_CLR_FP_CONFIRM 			= 33+AUD_BASE_ID_MAX,//��#ȷ��ɾ������ָ�ƣ�ȡ���밴*
	AUD_ID_CLR_FP_SUCESS 			= AUD_BASE_ID_SUCCESS,//ɾ������ָ�Ƴɹ�
	AUD_ID_CLR_FP_FAIL 				= AUD_BASE_ID_FAIL,//ɾ������ָ��ʧ��
	AUD_ID_PRESS_RFCARD 			= AUD_BASE_ID_PRESS_RFCARD,//��ˢ��
	AUD_ID_PRESS_RFCARD_AGAIN		= AUD_BASE_ID_PRESS_RFCARD_AGAIN,//����ˢһ��
	AUD_ID_ADD_RFCARD_SUCESS 		= AUD_BASE_ID_SUCCESS,//��RF����ӳɹ�
	AUD_ID_RFCARD_EXIST 			= AUD_BASE_ID_RFCARD_EXIST,//RF���Ѵ��ڣ��뻻�ſ�
	AUD_ID_RFCARD_FULL 				= AUD_BASE_ID_MEM_FULL,//RF������������ϵ����Ա
	AUD_ID_PRESS_OLD_RFCARD 		= AUD_BASE_ID_PRESS_OLD_RFCARD,//��ˢ�ɿ�
	AUD_ID_PRESS_NEW_RFCARD 		= AUD_BASE_ID_PRESS_NEW_RFCARD,//��ˢ�¿�
	AUD_ID_PRESS_NEW_RFCARD_AGAIN = AUD_BASE_ID_PRESS_RFCARD_AGAIN,//����ˢһ���¿�
	AUD_ID_CHG_RFCARD_SUCESS 		= AUD_BASE_ID_SUCCESS,//��RF���޸ĳɹ�
	AUD_ID_RFCARD_NOT_SAME 			= AUD_BASE_ID_RFCARD_SAME,//�¾�RF������һ��
	AUD_ID_INPUT_DEL_RFCARD_NUM = AUD_BASE_ID_INPUT_DEL_RFCARD,//������Ҫɾ���ı�Ż�RF������#������
	AUD_ID_RFCARD_NOT_EXIST 		= 42+AUD_BASE_ID_MAX,//RF�������ڣ�����������
	AUD_ID_DEL_RFCARD_CONFIRM 		= 33+AUD_BASE_ID_MAX,//��RF����#ȷ��ɾ����ȡ���밴*
	AUD_ID_PRESS_DEL_RFCARD_AGAIN = AUD_BASE_ID_PRESS_RFCARD_AGAIN,//����ˢһ��Ҫɾ����RF��
	AUD_ID_DEL_RFCARD_SUCESS 		= AUD_BASE_ID_SUCCESS,//��RF��ɾ���ɹ�
	AUD_ID_CLR_RFCARD_CONFIRM 		= 33+AUD_BASE_ID_MAX,//��#ȷ��ɾ������RF����ȡ���밴*
	AUD_ID_CLR_RFCARD_SUCESS 		= AUD_BASE_ID_SUCCESS,//ɾ������RF���ɹ�
	AUD_ID_CLR_RFCARD_FAIL 			= AUD_BASE_ID_FAIL,//ɾ������RF��ʧ��
	AUD_ID_INPUT_ADMIN_PWD 			= 45+AUD_BASE_ID_MAX,//���������Ա���룬��#������
	AUD_ID_INPUT_NEW_ADMIN_PWD = 0+AUD_BASE_ID_MAX,//�������¹���Ա���룬��#������
	//
	AUD_ID_INPUT_NEW_ADMIN_PWD_AGAIN 			= 6+AUD_BASE_ID_MAX,//���ٴ������¹���Ա���룬��#������
	AUD_ID_CHG_ADMIN_PWD_SUCESS					= AUD_BASE_ID_SUCCESS,//����Ա�����޸ĳɹ�
	AUD_ID_PWD_EXIST 							= 48+AUD_BASE_ID_MAX,//�����Ѵ��ڣ�����������
	AUD_ID_NEW_ADMIN_FP 						= AUD_BASE_ID_PRESS_FP,//�밴�µĹ���Աָ��
	AUD_ID_ADD_NO1_ADMIN_FP_SUCESS 				= AUD_BASE_ID_SUCCESS,//1�Ź���ָ����ӳɹ�
	AUD_ID_ADD_NO2_ADMIN_FP_SUCESS 				= AUD_BASE_ID_SUCCESS,//2�Ź���ָ����ӳɹ�
	AUD_ID_CLOSE_PRO_AUDIO_SUCESS 				= AUD_BASE_ID_SET_SUCESS,//�ر���ʾ���ɹ�
	AUD_ID_CLOSE_PRO_AUDIO_FAIL 				= AUD_BASE_ID_SET_FAIL,//�ر���ʾ��ʧ��
	AUD_ID_OPEN_PRO_AUDIO_SUCESS 				= AUD_BASE_ID_SET_SUCESS,//������ʾ���ɹ�
	AUD_ID_OPEN_PRO_AUDIO_FAIL 					= AUD_BASE_ID_SET_FAIL,//������ʾ��ʧ��
	AUD_ID_SIN_OPEN_MODE_SUCESS 				= AUD_BASE_ID_SET_SUCESS,//�����ŷ�ʽ���óɹ�
	AUD_ID_SIN_OPEN_MODE_FAIL 					= AUD_BASE_ID_SET_FAIL,//�����ŷ�ʽ����ʧ��
	AUD_ID_DBL_OPEN_MODE_SUCESS 				= AUD_BASE_ID_SET_SUCESS,//˫���ŷ�ʽ���óɹ�
	AUD_ID_DBL_OPEN_MODE_FAIL 					= AUD_BASE_ID_SET_FAIL,//˫���ŷ�ʽ����ʧ��
	AUD_ID_RESTORE_SUCESS 						= AUD_BASE_ID_SYS_RESTORE_SUCCESS,//�ָ��������óɹ�
	AUD_ID_RESTORE_FAIL 						= AUD_BASE_ID_SET_FAIL,//�ָ���������ʧ��
	AUD_ID_ADD_ADMIN_PWD_FIRST 					= 51+AUD_BASE_ID_MAX,//Ϊ������ʹ�ð�ȫ��������ӹ���Ա���룬��#������
	AUD_ID_INPUT_ADMIN_PWD_INIT_AGAIN 			= 6+AUD_BASE_ID_MAX,//���ٴ��������Ա���룬��#������
	AUD_ID_ADD_ADMIN_PWD_INIT_SUCESS 			= AUD_BASE_ID_SUCCESS,//����Ա������ӳɹ�
	AUD_ID_DOOR_OPEN 							= AUD_BASE_ID_DOOR_OPEN,//�ѿ���
	AUD_ID_DOOR_CLOSE 							= AUD_BASE_ID_DOOR_CLOSE,//�ѹ���
	AUD_ID_PWD_WRONG_TRY 						= 54+AUD_BASE_ID_MAX,//�������,������
	AUD_ID_FP_WRONG_TRY 						= 57+AUD_BASE_ID_MAX,//ָ�ƴ���������
	AUD_ID_RFCARD_WRONG_TRY 					= 60+AUD_BASE_ID_MAX,//RF������������
	AUD_ID_RONG_TIMES_EXCEED 					= AUD_BASE_ID_RONG_TIMES_EXCEED,//��������ѳ����ƣ���**���Ӻ�����
	AUD_ID_LOW_BATTERY 							= AUD_BASE_ID_LOW_BATTERY,//�����ͣ��뼰ʱ�������
	//AUD_ID_YOU_ARE_WELCOME 						= AUD_BASE_ID_YOU_ARE_WELCOME,//��ӭʹ�õ�Ȥ����������
	AUD_ID_RESTORE_LOCK_CONTINUE_CONFIRM		=33+AUD_BASE_ID_MAX,//��#�ָ��������ã�ȡ���밴*
	AUD_ID_APP_SYN = AUD_BASE_ID_APP_SYN,//��ʹ��appͬ��
	AUD_ID_APP_ADD_SUC = AUD_BASE_ID_SET_SUCESS,//app��ӳɹ�
	AUD_ID_APP_ADD_FAIL = AUD_BASE_ID_SET_FAIL,//app���ʧ��
	AUD_ID_SYSTEM = 138+AUD_BASE_ID_MAX,//ϵͳ
	AUD_ID_SYSTEM2 = 93+AUD_BASE_ID_MAX,//ϵͳ2
	AUD_ID_SYS_PASSWORD = 101+AUD_BASE_ID_MAX,//����
	AUD_ID_SYS_FP = 111+AUD_BASE_ID_MAX,//ָ��
	AUD_ID_SYS_RFCARD = 121+AUD_BASE_ID_MAX,//RF��
	AUD_ID_SYS_ADMIN = 63+AUD_BASE_ID_MAX,//����Ա
	AUD_ID_SYS_ADMIN2 = 134+AUD_BASE_ID_MAX,//����Ա
	AUD_ID_SYS_SETTING = 69+AUD_BASE_ID_MAX,//����
	AUD_ID_SYS_CHG_ADMIN_PWD = AUD_BASE_ID_SYS_CHG_ADMIN_PWD,//�޸Ĺ���Ա����
	AUD_ID_SYS_CHG_ADMIN_FP = 75+AUD_BASE_ID_MAX,//�޸Ĺ���Աָ��
	AUD_ID_SYS_PRO_AUDIO = 81+AUD_BASE_ID_MAX,//��ʾ��
	AUD_ID_SYS_OPEN_MODE = 87+AUD_BASE_ID_MAX,//���ŷ�ʽ
	AUD_ID_SYS_DBL_OPEN_MODE = AUD_BASE_ID_SYS_DBL_OPEN_MODE,//˫���ŷ�ʽ
	AUD_ID_FM_KEY_INPUT = AUD_BASE_ID_FM_KEY_INPUT,//��������а���
	AUD_ID_FM_MOTO = 33+AUD_BASE_ID_MAX,
	AUD_ID_FM_RESET = AUD_BASE_ID_FM_RESTORE,//�밴��λ��
	AUD_ID_FM_TEST_PASS = AUD_BASE_ID_SUCCESS,//���Գɹ�
	AUD_ID_FM_TEST_FAIL = AUD_BASE_ID_FAIL,//����ʧ��
	AUD_ID_SET_SUCESS = AUD_BASE_ID_SET_SUCESS,
	AUD_ID_INPUT_MAX = AUD_BASE_ID_INPUT_END,//��#������

	AUD_ID_SYS_NUM_0 = AUD_BASE_ID_SYS_NUM_0,//0
	AUD_ID_SYS_NUM_1 = AUD_BASE_ID_SYS_NUM_1,//1
	AUD_ID_SYS_NUM_2 = AUD_BASE_ID_SYS_NUM_2,//2
	AUD_ID_SYS_NUM_3 = AUD_BASE_ID_SYS_NUM_3,//3
	AUD_ID_SYS_NUM_4 = AUD_BASE_ID_SYS_NUM_4,//4
	AUD_ID_SYS_NUM_5 = AUD_BASE_ID_SYS_NUM_5,//5
	AUD_ID_SYS_NUM_6 = AUD_BASE_ID_SYS_NUM_6,//6
	AUD_ID_SYS_NUM_7 = AUD_BASE_ID_SYS_NUM_7,//7
	AUD_ID_SYS_NUM_8 = AUD_BASE_ID_SYS_NUM_8,//8
	AUD_ID_SYS_NUM_9 = AUD_BASE_ID_SYS_NUM_9,//9
	AUD_ID_SYS_NUM_S = AUD_BASE_ID_SYS_NUM_S,//*
	AUD_ID_SYS_NUM_H = AUD_BASE_ID_SYS_NUM_H,//#

	AUD_ID_MAX_COUNT,
	AUD_ID_INVALID_INDEX = 0xFF,
}AUD_PLAY_ID;

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_aud_init(void);

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
void mmi_dq_aud_play_with_id(unsigned char aud_id);

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_aud_play_key_tone(unsigned char key_val);

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_aud_get_state(void);

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_aud_get_end_flag(void);

#endif //__MMI_AUDIO_H__

