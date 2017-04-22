

#include "stdafx.h"

#include"cyQueue.h"

CyQueue::CyQueue()
{
	qu.front =0;
	qu.rear=0;

}

void CyQueue::ClearQueue()
{
	qu.front =0;
	qu.rear=0;
}

int CyQueue::EnQueue(ElemType x)
{
	if((qu.rear+1)%QUEUESIZE==qu.front)
		return 0;
	qu.rear=(qu.rear+1)%QUEUESIZE;
	qu.data[qu.rear]=x;
	return 1;
}

int CyQueue::DeQueue(ElemType &x)
{
	if(qu.rear==qu.front)
		return 0;
	qu.front=(qu.front+1)%QUEUESIZE;
	x=qu.data[qu.front];
	return 1;
}

int CyQueue::GetHead(ElemType &x)
{
	if(qu.rear==qu.front)
		return 0;
	x=qu.data[(qu.front+1)%QUEUESIZE];
	return 1;
}

int CyQueue::IsEmpty()
{
	if(qu.rear==qu.front)  //¶Ó¿Õ
		return 1;
	else
		return 0;

}

int CyQueue::IsFull()
{
	if((qu.rear+1)%QUEUESIZE==qu.front)  //¶ÓÂú
		return 1;
	else 
		return 0;
}