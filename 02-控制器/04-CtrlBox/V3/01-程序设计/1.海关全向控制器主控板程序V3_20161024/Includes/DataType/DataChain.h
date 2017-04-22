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

#include <stm32f10x.h>
#include <stdlib.h>		

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
		ChainNode *currentNode;
};


#endif
