#ifndef __MMI_QUEUE_C__

#define __MMI_QUEUE_C__

#include "mmi_queue.h"
#include "dqiot_drv.h"

typedef struct
{
	Sys_MSG_Queue_M msg[QUEUE_NUM+1];//循环队列满时有一格为空
	uint8_t head;
	uint8_t end;
}SYS_MSG_Queue;

SYS_MSG_Queue g_msg_que;


/*
parameter: 
	none
return :
	none
*/
void mmi_InitQueue(void)
{
	unsigned char i = 0;
	for(i=0;i<=QUEUE_NUM;i++)
	{
		g_msg_que.msg[i].que_event = QUE_EVENT_INVALID;
		g_msg_que.msg[i].que_pro = QUE_PRO_INVALID;
		g_msg_que.msg[i].que_data = 0xFF;
	}
	g_msg_que.head = 0;
	g_msg_que.end = 0;
	return;
}

/*
parameter: 
	none
return :
	none
*/
static uint8_t mmi_Queue_GetNextID(uint8_t id)
{
	if(id < QUEUE_NUM)
		return id + 1;
	else
		return 0;
}

/*
parameter: 
	none
return :
	none
*/
static uint8_t mmi_Queue_GetPreID(uint8_t id)
{
	if(id > 0)
		return id - 1;
	else
		return QUEUE_NUM;
}


/*
parameter: 
	none
return :
	none
*/
uint8_t mmi_QueueLength(void)
{
	if(g_msg_que.head == g_msg_que.end)
		return 0;
	else if(g_msg_que.head < g_msg_que.end)
		return g_msg_que.end - g_msg_que.head;
	else
		return g_msg_que.head - g_msg_que.end + QUEUE_NUM + 1;
}

/*
parameter: 
	none
return :
	none
*/
uint8_t mmi_Que_IsEmpty(void)
{
	if(g_msg_que.head == g_msg_que.end)
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
uint8_t mmi_Que_IsFull(void)
{
	if(mmi_Queue_GetNextID(g_msg_que.end) == g_msg_que.head)
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
uint8_t mmi_InQueue(Sys_MSG_Queue_M que)
{
	uint8_t que_len = 0;
	uint8_t i = 0;
	
	if(mmi_Que_IsFull() == 1)
		return 0;
		
	g_msg_que.msg[g_msg_que.end].que_event = que.que_event;
	g_msg_que.msg[g_msg_que.end].que_pro = que.que_pro;
	g_msg_que.msg[g_msg_que.end].que_data = que.que_data;
	g_msg_que.end = mmi_Queue_GetNextID(g_msg_que.end);
	return 1;
}

/*
parameter: 
	none
return :
	none
*/
uint8_t mmi_OutQueue(Sys_MSG_Queue_M * que)
{
	unsigned char que_len = 0;
	unsigned char i = 0;

	if(mmi_Que_IsEmpty() == 1)
		return 0;

	que->que_event = g_msg_que.msg[g_msg_que.head].que_event;
	que->que_pro = g_msg_que.msg[g_msg_que.head].que_pro;
	que->que_data = g_msg_que.msg[g_msg_que.head].que_data;
	g_msg_que.msg[g_msg_que.head].que_event = QUE_EVENT_INVALID;
	g_msg_que.msg[g_msg_que.head].que_pro = QUE_PRO_INVALID;
	g_msg_que.msg[g_msg_que.head].que_data = 0xFF;
	return 1;
}



#endif//__MMI_QUEUE_C__
