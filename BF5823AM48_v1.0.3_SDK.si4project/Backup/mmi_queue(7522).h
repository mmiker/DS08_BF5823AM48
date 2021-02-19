/*
  ******************************************************************************
  * @file    I2C/I2C_TwoBoards/I2C_DataExchange/Slave/.h
  * @author  MCD Application Team
  * @version V2.0.4
  * @date    26-April-2018
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MMI_QUEUE_H__

#define __MMI_QUEUE_H__

#define QUEUE_NUM 10

typedef enum
{
	MSG_QUE_IDLE = 0x00,
	MSG_QUE_INPUT_PWD = 0x01,
	MSG_QUE_ADD_PWD = 0x02,
	MSG_QUE_ADD_PWD_AGAIN = 0x03,
	MSG_QUE_DEL_PWD = 0x04,
	MSG_QUE_DEL_PWD_AGAIN = 0x05,


	MSG_QUE_INPUT_FPS = 0x10,
	MSG_QUE_ADD_FPS = 0x11,
	MSG_QUE_ADD_FPS_AGAIN = 0x12,
	MSG_QUE_DEL_FPS = 0x13,
	MSG_QUE_DEL_FPS_AGAIN = 0x14,
	
	
	MSG_QUE_INVALID = 0xFF
}SYS_QUEUE_STATUS;

typedef enum
{
	QUE_PRO_LOW = 0x00,
	QUE_PRO_HIG = 0x01,
	QUE_PRO_INVALID = 0xFF
}SYS_QUEUR_PRO;
	
typedef struct 
{
	SYS_QUEUE_STATUS q_status;
	SYS_QUEUR_PRO que_pro;
}Sys_MSG_Queue;

/*
parameter: 
	none
return :
	none
*/
void mmi_InitQueue(void);

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_QueueLength(void);
/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_Que_IsEmpty(void);

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_Que_IsFull(void);

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_InQueue(Sys_MSG_Queue que);

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_OutQueue(void);

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_GetCurQueue(Sys_MSG_Queue *que);
#endif
