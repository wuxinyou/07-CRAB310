/**
  ******************************************************************************
	*文件：DataChain.c
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
		current=NULL;
		return;
	}
	length=len;
	
//第一种分配方式 利用数组
// 	Chains =new ChainNode[length]; //在堆上分配内存可能会失败?
// 	for(int i=0;i<length;i++)
// 	{
// 		if(i==length-1)
// 		{
// 			Chains[i].m_next=Chains;
// 		}
// 		else
// 		{
// 			Chains[i].m_next=&Chains[i+1];
// 		}
// 		if(i==0)
// 		{
// 			Chains[0].m_previous=&Chains[length-1];
// 		}
// 		else
// 		{
// 			Chains[i+1].m_previous=&Chains[i];
// 		}
// 	}
// 	current=Chains;
//第二种内存申请方式 不利用中间变量
	current=new ChainNode(0,NULL,NULL);
	
//为防止申请内存失败可以用下面的方式 
// 	do
// 	{
// 		current=new ChainNode(0,NULL,NULL);
// 	}
// 	while(current==NULL);


	current->m_next=current;
	current->m_previous=current;

	for(int i=0;i<len-1;i++)
	{
		//同上 可以用do while 防止内存申请失败
		current->m_next=new ChainNode(0,current,current->m_next);
		current->m_next->m_next->m_previous=current->m_next;
	}
	
//第三种分配方式 利用中间变量 从C中演变而来的
// 	int i=0;
// 	chain *head;
// 	chain *trail;
// 	length=len;
// 	if(len<1)
// 		return ;
// 	else
// 	{
// 		chain *tem=(chain *)malloc(sizeof(chain));
// 		
// 		head=tem;
// 		trail=tem;
// 		tem->data=0;	
// 		tem->next=head;
// 		tem->last=head;
		
// 		for(i=0;i<len-1;i++)
// 		{
// 			tem=(chain *)malloc(sizeof(chain));	  //在堆上申请空间  
// 			tem->data=0;
// 			tem->next=head;
// 			tem->last=trail;
// 			head->last=tem;
// 			trail->next=tem;
// 			trail=tem;	
// 		}
// 		current=head;
// 	}
}

//析构函数
RingChain::~RingChain()
{
// 	delete [] Chains;
	ChainNode *q,*p=current->m_next;	
	while(p!=current)
	{
		q=p->m_next;
		delete (p);
		p=q;
	}
	delete (current);
// 	current=NULL;
}


/**
  * 功  能：获取当前节点的数据
  * 参  数：无
  * 返回值：当前节点的数据值
  * 
  */
DATATYPE RingChain::getData()
{
	return current->data;
}

/**
  * 功  能：将当前节点指针指向下个节点
  * 参  数：无
  * 返回值：无
  * 
  */
void RingChain::next()
{
	current=current->m_next;
}

/**
  * 功  能：将当前节点指针指向上个节点
  * 参  数：无
  * 返回值：无
  * 
  */
void RingChain::previous()
{
	current=current->m_previous;
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
	current->data=value;
}



// //在已知节点后插入一个节点
// //参数：data， 插入的节点数值；p，已知的节点 
// void insertAfter(DATATYPE data,chain *p)
// {
// 	chain *tem;
// 	if(p)
// 	{
// 		 tem=(chain *)malloc(sizeof(chain));
// 		 tem->data=data;
// 		 tem->next=p->next;
// 		 (p->next)->last=tem;
// 		 tem->last=p;
// 		 p->next=tem;	
// 	}	
// }

// //在已知节点前插入一个节点
// //参数：data， 插入的节点数值；p，已知的节点 
// void insertBefore(DATATYPE data,chain *p)
// {
// //	insert_after(data,p->last);
// 	chain *tem;
// 	if(p)
// 	{
// 		 tem=(chain *)malloc(sizeof(chain));
// 		 tem->data=data;
// 		 tem->next=p;
// 		 tem->last=p->last;
// 		 (p->last)->next=tem;		 
// 		 p->last=tem;		
// 	}
// }

// //删除后继节点，即p的后一个节点
// //返回值：1，删除成功；0，删除失败
// bool deleteAfter(chain *head,chain *p)
// {
// 	chain *tem;
// 	if(p->next!=head)
// 	{
// 		tem=p->next;
// 		p->next=tem->next;
// 		(tem->next)->last=p;
// 		free(tem);
// 		return true;
// 	}
// 	else
// 		return false;
// }

// //删除前一个节点，即p的前一个节点
// //返回值：1，删除成功；0，删除失败
// bool deleteBefore(chain *head,chain *p)
// {
// 	chain *tem;
// 	if(p->next!=head)
// 	{
// 		tem=p->last;
// 		p->last=tem->last;
// 		(tem->last)->next=p;
// 		free(tem);
// 		return true;
// 	}
// 	else
// 		return false;
// }

// //删除节点本身
// //返回值：1，删除成功；0，删除失败
// bool deletSelf(chain *head,chain *p)
// {
// 	chain *q;
// 	q=head;
// 	if(!p)
// 		return false;
// 	else
// 	{
// 		while(q->next!=p&&q->next!=head)
// 			q=q->next;	
// 		q->next=p->next;
// 		(p->next)->last=q;
// 		free(p);
// 		return true;
// 	}
// }

// //创建一个双向循环链表 （尾部插入法，另一种方法是头部插入法）
// //len:链表的节点数
// //返回值：创建的链表指针
// chain * creatChain(uint16_t len)
// {
// 	uint16_t i=0;
// 	chain *head;
// 	chain *trail;
// 	if(len<1)
// 		return NULL;
// 	else
// 	{
// 		chain *tem=(chain *)malloc(sizeof(chain));
// 		
// 		head=tem;
// 		trail=tem;
// 		tem->data=0;	
// 		tem->next=head;
// 		tem->last=head;
// 		
// 		for(i=0;i<len-1;i++)
// 		{
// 			tem=(chain *)malloc(sizeof(chain));	  //在堆上申请空间  
// 			tem->data=0;
// 			tem->next=head;
// 			tem->last=trail;
// 			head->last=tem;
// 			trail->next=tem;
// 			trail=tem;	
// 		}
// 		return 	head;
// 	}	 
// }

// //删除(销毁)一个双向循环链表
// //返回值：1，删除成功；0，删除失败
// void deleteChain(chain *head)
// {
// 	chain *q,*p=head->next;	
//    	while(p!=head)
// 	{
// 		q=p->next;
// 		free(p);
// 		p=q;
// 	}
// 	free(head);
// 	head=NULL;
// }


/******************************** 链表接收模式样版********************************/
//bool receiveData(USART_data_t* p_usart_data, uint8_t* pRXD_DATA)
//{
//	static uint8_t flag=0;
//		
//	static chain *readData;	  // =creat_chain(XBOT_RXD_DATA_LEN);
//	
//	uint8_t CheckSum=0;
//
//	bool RxdFlag=false;
//
//	uint8_t Index=0;
//	
// 	if(flag==0)
//	{
//	   readData=creatChain(RXD_LEN);
//	   flag=1;
//	}
//
//	while (USART_RXBufferData_Available(p_usart_data))
//	{
//		readData->data = USART_RXBuffer_GetByte(p_usart_data);
//
//		readData = readData->next;//链表跳至下个节点
//
//		if(readData->data==RXD_START)//检测帧头
//		{			
//			readData=readData->next;
//			CheckSum+=RXD_LEN;
//			if(readData->data==RXD_ID_1||readData->data==RXD_ID_2||readData->data==RXD_ID_3||readData->data==RXD_ID_4)//检测命令字
//			{
//				//命令字正确
//				for(Index=0;Index<RXD_LEN-2;Index++)
//				{
//				   CheckSum+= readData->data;
//				   readData=readData->next;
//				}
//				if(CheckSum==readData->data)//校验和正确
//				{
//					//将数据存入数组
//					for(Index=0;Index<RXD_LEN;Index++)
//					{
//					   readData = readData->next;
//					   pRXD_DATA[Index]=readData->data;
//					}
//					RxdFlag=true;	
//				}
//				readData=readData->next; 	
//			}
//			else
//			{
//				readData=readData->last;//跳至上个节点	
//			}			
//		 	CheckSum=0;
//		}
//	}
//	return 	RxdFlag;
//}
