/*plc_stack_plc.h
*从文件读出plc内码生成梯结构时用到
*栈内包括三个栈:
*/
#ifndef STACK_PLC_H
#define STACK_PLC_H

#include<stack>
#include<queue>
#include<vector>
#include"plc_structure.h"
using namespace std;
class StackPlc
{
private:
    stack<Node*> StkpNode;	//节点栈存放临时的操作节点
	stack<Element*> StkpElement;	//元件栈，存放由LD/LDI或MPS后遇到LD/LDI前的第一个AND/ANI
	
	stack<int> StkId;	//判断栈内元素的类型 0:Element, 2:Node
										//纪录两个栈的入栈顺序
	vector<int> VectMark;//下一条指令为MPS=1，MRD=2，MPP=3，其他=0；多分支输出时用
public:
	StackPlc();
	~StackPlc();
	void Push(Element *pElementTmp);	//将一元件入栈
	void Push(Node *pNodeTmp);				//将一分枝入栈
	int Pop();			//将栈顶弹出
	int TopId();		//返回栈顶元素的类型0:Element, 2:Node，
	void GetTop(Node **ppit);		//^当栈顶为节点时，读取栈顶节点，若栈顶为元件则返回NULL,
	void GetTop(Element **ppdt);//^当栈顶为元件时，读取栈顶元件，若栈顶为节点则返回NULL,
											//读取栈顶前一定要判断栈顶的类型！！
	bool Empty();		//判断栈是否为空，为空返回 true	
	int Size();			//返回栈深		
	//下面的几个函数功能可能会有重叠,可以简化删掉一些,我懒得优化了, 
	void SetTopMark(int i);//修改栈顶的Mark类型
	int GetMark(int i);//返回在i单元内的iMark值
	int  GetTopMark();//返回在栈顶的iMark值
	int GetIndexMarkNearE(int iMarkF);////从栈顶开始寻找iMarkF，返回所在的下标，当没有找到时返回零
	void SetMarkAt(int index, int iMarkNew);//修改栈内第index个单元的iMark值为iMarkNew
};
#endif

/*******************************************
重要函数的调用方法
StackPlc *stkplc=new StackPlc;
Node *pNode=new Node;
Elemenet *pElement=new Element;

//入栈
stkplc->Push(pNode);	
stkplc->Push(pElement)

//从栈中读取数据
//必须先判断栈顶的数据类型才能正确读取
int i= stkplc->TopId();
Node *pNodeRead=NULL;	
if (i==2)
{
	stkplc->GetTop(&pNodeRead);
	
}
//pNodeRead即为栈顶存放的的指向节点的指针。

Element *pElementRead=NULL;	
if(i==0)	
{
	stkplc->GetTop(&pElementRead);
}
*******************************************/
/*
代码如下：
class StackPlc
{
private:
	stack<Node*> StkpNode;		    //节点指针栈
	stack<Element*> StkpElement;	//元件指针栈
	stack<int> StkId;  //纪录两个栈的入栈顺序 //栈内元素的类型 0:Element, 2:Node，
	vector<int> VectMark;//下一条指令为MPS=1，MRD=2，MPP=3，其他=0；多重输出时用
public:
	StackPlc();
	~StackPlc();
	void Push(Element *pElementTmp);	//将一元件指针入栈
	void Push(Node *pNodeTmp);		//将一节点指针入栈
	int Pop();		//将栈顶弹出
	int TopId();		//返回栈顶元素的类型0:Element, 2:Node，
	void GetTop(Node **ppit);		//当栈顶为节点时，读取栈顶节点，若栈顶为元件则返回NULL,
	void GetTop(Element **ppdt);	//当栈顶为元件时，读取栈顶元件，若栈顶为节点则返回NULL,
								//读取栈顶前必须判断栈顶的类型
	bool Empty();			//判断栈是否为空，为空返回 true	
	int Size();				//返回栈深		
	void SetTopMark(int i);	//修改栈顶的Mark值。
	int GetMark(int i);		//返回在i单元内的iMark值
	int GetTopMark();	    //返回在栈顶的iMark值
 	int GetIndexMarkNearE(int iMarkF);	//从栈顶开始寻找iMarkF，返回所在的下标，当没有找到
//时返回零
	void SetMarkAt(int index, int iMarkNew);//修改栈内第index个单元的iMark值为iMarkNew
}
*/
