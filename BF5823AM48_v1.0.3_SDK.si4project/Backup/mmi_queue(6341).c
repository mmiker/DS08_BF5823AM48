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
uint8_t mmi_Queue_GetNextID(uint8_t id)
{
	if(id < QUEUE_NUM)
		return id+1;
	else
		return 0;
}

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_QueueLength(void)
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
unsigned char mmi_Que_IsEmpty(void)
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
unsigned char mmi_Que_IsFull(void)
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
unsigned char mmi_InQueue(Sys_MSG_Queue_M que)
{
	unsigned char que_len = 0;
	unsigned char i = 0;
	
	if(mmi_Que_IsFull() == 1)
		return 0;
	
	que_len = mmi_QueueLength();
	
	if(que.que_pro == QUE_PRO_HIG)
	{
		for(i=0;i<que_len;i++)
		{
			g_msg_que[que_len].que_pro = g_msg_que[que_len-1].que_pro;
			g_msg_que[que_len].q_status = g_msg_que[que_len-1].q_status;
		}
		g_msg_que[0].que_pro = que.que_pro;
		g_msg_que[0].q_status = que.q_status;
	}
	else
	{
		g_msg_que[que_len].que_pro = que.que_pro;
		g_msg_que[que_len].q_status = que.q_status;
	}
	return 1;
}

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_OutQueue(void)
{
	unsigned char que_len = 0;
	unsigned char i = 0;
	
	que_len = mmi_QueueLength();
	for(i=0;i<que_len-1;i++)
	{
		g_msg_que[i].que_pro = g_msg_que[i+1].que_pro;
		g_msg_que[i].q_status = g_msg_que[i+1].q_status;
	}
	g_msg_que[que_len-1].que_pro = QUE_PRO_INVALID;
	g_msg_que[que_len-1].q_status = MSG_QUE_INVALID;
	return 1;
}

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_GetCurQueue(Sys_MSG_Queue *que)
{
	que->que_pro = g_msg_que[0].que_pro;
	que->q_status = g_msg_que[0].q_status;
	mmi_OutQueue();
	return 1;
}

#endif//__MMI_QUEUE_C__
