/**
  ******************************************************************************
	*文件：DataChain.h
	*作者：叶依顺
	*版本：2.0
	*日期：2013-06-17
	*概要：链表结构类的头文件
	*备注：
	*
  ******************************************************************************  
	*/ 
#ifndef __DATA_CHAIN_H
#define __DATA_CHAIN_H

#include <stm32f4xx.h>
#include <stdlib.h>		
// #include "MySysDefine.h"

#define DATATYPE uint8_t


class ChainNode
{
	friend class RingChain;
	
private:
	ChainNode(DATATYPE value=0,ChainNode* previous=NULL,ChainNode* next=NULL)
	{
		this->data=value;
		this->m_next=next;
		this->m_previous=previous;
	}
	~ChainNode()
	{

	}
private:
	DATATYPE data;
	ChainNode *m_next;
	ChainNode *m_previous;
};



// //双向循环链表的结构体
// typedef struct CHAIN
// {
// 	DATATYPE data;
// 	struct CHAIN *last;
// 	struct CHAIN *next;	
// } chain;


class RingChain
{
	public:
		RingChain(int);
		~RingChain();
		DATATYPE getData();
		void next();
		void previous();
		int getLen();
		void setData(DATATYPE);
	private:
		int length;
// 		ChainNode *Chains;
		ChainNode *current;
};
// //在已知节点后插入一个节点
// void insertAfter(DATATYPE,chain *p);


// //在已知节点前插入一个节点
// void insertBefore(DATATYPE,chain *p);


// //删除后继节点，即p的后一个节点
// bool deleteAfter(chain *head,chain *p);


// //删除前一个节点，即p的前一个节点
// bool deleteBefore(chain *head,chain *p);


// //删除节点本身
// bool deletSelf(chain *head,chain *p);


// //创建一个双向循环链表
// chain * creatChain(uint16_t len);	 


// //删除一个双向循环链表
// void deleteChain(chain *head);

#endif
