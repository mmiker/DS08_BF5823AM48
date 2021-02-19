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

#include "main.h"
#define QUEUE_NUM 10


typedef enum
{
	QUE_PRO_LOW = 0x00,
	QUE_PRO_HIG = 0x01,
	QUE_PRO_INVALID = 0xFF,
}SYS_QUEUE_PRO;

typedef enum
{
	QUE_EVENT_KEY = 0x00,
	QUE_EVENT_FP = 0x01,
	QUE_EVENT_RFID = 0x02,
	
	QUE_EVENT_INVALID = 0xFF,
}SYS_QUEUE_EVENT;



typedef struct 
{
	SYS_QUEUE_EVENT que_event;
	SYS_QUEUE_PRO que_pro;
	uint8_t que_data;
}Sys_MSG_Queue_M;

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
uint8_t mmi_QueueLength(void);
/*
parameter: 
	none
return :
	none
*/
uint8_t mmi_Que_IsEmpty(void);

/*
parameter: 
	none
return :
	none
*/
uint8_t mmi_Que_IsFull(void);

/*
parameter: 
	none
return :
	none
*/
uint8_t mmi_InQueue(Sys_MSG_Queue_M que);

/*
parameter: 
	none
return :
	none
*/
uint8_t mmi_OutQueue(Sys_MSG_Queue_M * que);
#endif
