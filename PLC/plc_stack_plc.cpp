/*plc_stack_plc.cpp*/
#include"plc_stack_plc.h"
#include<iostream>

StackPlc::StackPlc()	//将所有的栈清空
{
	while(StkId.size() > 0 )
	{
		StkId.pop();
	}	
	VectMark.clear();	
	while(StkpNode.size()>0)
	{
		StkpNode.pop();
	}	
	while(StkpElement.size()>0)	
	{
		StkpElement.pop();
	}	
}
StackPlc::~StackPlc()
{
	//将所有的栈清空
	while(StkId.size() > 0 )
	{
		StkId.pop();
	}
	
	VectMark.clear();
	
	while(StkpNode.size()>0)
	{
		StkpNode.pop();
	}	
	while(StkpElement.size()>0)	
	{
		StkpElement.pop();
	}			
}	
void StackPlc::Push(Element *pElementTmp)	//将一元件入栈
{
	StkpElement.push(pElementTmp);
	StkId.push(0);
	VectMark.push_back(0);
}	
void StackPlc::Push(Node *pNodeTmp)	//将一分枝入栈
{
	StkpNode.push(pNodeTmp);	
	StkId.push(2);
	VectMark.push_back(0);	
}	
int StackPlc::Pop()//将栈顶弹出
{
	if( StkId.empty() == true )
	{
		return -1	;
	}	
	if(StkId.top()==2)
	{
		StkpNode.pop();
		StkId.pop();
		VectMark.pop_back();
	}
	else if(StkId.top()==0)
	{
		StkpElement.pop();
		StkId.pop();
		VectMark.pop_back();
	}
	else
	{
		return -1;	
	}
	
	return 0;
}	
int StackPlc::TopId()	//返回栈顶元素的类型0:Element, 2:Node，
{
	if(StkId.empty() == false)
	{
		return StkId.top();		//栈内元素的类型 0:Element, 2:Node
	}
	else
	{	
		return -1;
	}
}	
void StackPlc::GetTop(Element **ppElementTmp)	//^当栈顶为节点时，读取栈顶节点，
{                                             //若栈顶为元件则返回NULL,   
	if(StkId.top()== 0 && StkId.empty() == false)	//若栈顶为元件且栈不为空，读栈顶（第二个条件有必要么）？？？？？
	{
		*ppElementTmp = StkpElement.top();
	}
	else 
	{
		*ppElementTmp =  NULL;		
	}
}	
void StackPlc::GetTop(Node **ppNodeTmp)	//^当栈顶为元件时，读取栈顶元件，
{                                       //若栈顶为节点则返回NULL,
	if(StkId.top()== 2 && StkId.empty() == false)
	{
		
		*ppNodeTmp = StkpNode.top();
	}
	else 
	{
		*ppNodeTmp =  NULL;		
	}
}	
bool StackPlc::Empty()	//判断栈是否为空，为空返回 true
{
	return StkId.empty();
}	
int StackPlc::Size()	//返回栈深
{
	return StkId.size();	
}	
void StackPlc::SetTopMark(int i)//修改栈顶的Mark类型
{	
	VectMark.pop_back();
	VectMark.push_back(i);
}
int StackPlc::GetMark(int i)//返回在i单元内的iMark值:Element, 2:Node，
{		
	return VectMark.at(i-1);//因为vector下标的起始点为0,而stack下标的起始点为1。自定义的栈的起始点为1
}
int StackPlc::GetTopMark()//返回在栈顶的iMark值:Element, 2:Node，
{
	return VectMark.back();	
}
int StackPlc::GetIndexMarkNearE(int iMarkF)//从栈顶开始寻找iMarkF，返回所在的下标，当没有找到时返回零
{
	int i = Size();//VectMark的长度
	while( i>0 && VectMark.at(i-1) != iMarkF)
	{
		i--;		//临界点分析：当i=1时， if( != iMarkF)(i=0);else(i=1)
	}
	return i;	
}	
void StackPlc::SetMarkAt(int index, int iMarkNew)//修改栈内第index个单元的iMark值为iMarkNew
{
	VectMark[index-1] = iMarkNew;
}	


