
#ifndef CYQUEUE_H
#define CYQUEUE_H

#define QUEUESIZE  13
typedef unsigned char ElemType;

typedef struct 
{
	ElemType data[QUEUESIZE];  //保存队列元素
	int front,rear;   //队头和队尾
}SqQueue;


class CyQueue
{
public:
	CyQueue();
	void ClearQueue();
	int EnQueue(ElemType x);  //入队
	int DeQueue(ElemType &x);   //出队
	int GetHead(ElemType &x);   //获取头元素
	int IsEmpty();    //判断为空
	int IsFull();  //判断队满

public:
	SqQueue qu;

};


#endif