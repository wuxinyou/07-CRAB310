/**
  ******************************************************************************
	*文件：DataChain.cpp
	*作者：叶依顺
	*版本：2.0
	*日期：2013-06-17
	*概要：链表结构类的实现
	*备注：
	*
  ******************************************************************************  
	*/ 

#include "DataChain.h"

//构造函数
RingChain::RingChain(int len)
{
	if(len<1)
	{
		currentNode=NULL;
		return;
	}
	length=len;
	currentNode=new ChainNode(0,NULL,NULL);
	currentNode->m_next=currentNode;
	currentNode->m_previous=currentNode;
	for(int i=0;i<len-1;i++)
	{
		currentNode->m_next=new ChainNode(0,currentNode,currentNode->m_next);
		currentNode->m_next->m_next->m_previous=currentNode->m_next;
	}
}

//析构函数
RingChain::~RingChain()
{
	ChainNode *q,*p=currentNode->m_next;	
	while(p!=currentNode)
	{
		q=p->m_next;
		delete (p);
		p=q;
	}
	delete (currentNode);
}


/**
  * 功  能：获取当前节点的数据
  * 参  数：无
  * 返回值：当前节点的数据值
  * 
  */
DATATYPE RingChain::getData()
{
	return currentNode->data;
}

/**
  * 功  能：将当前节点指针指向下个节点
  * 参  数：无
  * 返回值：无
  * 
  */
void RingChain::next()
{
	currentNode=currentNode->m_next;
}

/**
  * 功  能：将当前节点指针指向上个节点
  * 参  数：无
  * 返回值：无
  * 
  */
void RingChain::previous()
{
	currentNode=currentNode->m_previous;
}

/**
  * 功  能：获取链表的长度
  * 参  数：无
  * 返回值：链表的长度
  * 
  */
int RingChain::getLen()
{
	return length;
}

/**
  * 功  能：设置当前节点的数据
  * 参  数：待设定的值
  * 返回值：无
  * 
  */
void RingChain::setData(DATATYPE value)
{
	currentNode->data=value;
}

