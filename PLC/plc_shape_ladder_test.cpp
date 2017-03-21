/*plc_shape_ladder_test.cpp*/
#include"plc_shape_ladder_test.h"
#include<iostream>
using namespace std;

stack<Node*> StkpNode;	//节点栈点
stack<NodeLink*> StkpNodeLink;	//链节栈，
stack<int> StkInt;
int i;

int DisposeNode(Node *pNodeCur)
{
	//cout<<"DisposeNode ok 1"<<endl;
	if(pNodeCur == NULL)
	{		
		return  0;
	}	
//用到三个栈，stkNode,stkNodeLink，StkInt;	
	Node *pNodeRootCur=pNodeCur;
	NodeLink *pNodeLinkCur;
	Element *pElementCur;	
	pNodeLinkCur = pNodeCur->pNodeLinkSon;
	while(pNodeLinkCur != NULL)	//处理一个节点的所有分支
	{
		if( pNodeLinkCur->pNodeBlew != NULL)	//下面的元素为节点
		{
			StkpNode.push(pNodeCur);
			StkpNodeLink.push(pNodeLinkCur);
			StkInt.push(i);
			pNodeCur=pNodeLinkCur->pNodeBlew;	
			int j=i;
			if(i>5)
			{
				i=0;	
			}	
			while(j>0)
			{
				cout<<" ";	
				j--;
			}	
			if(pNodeCur->iNodeOperate==1)
			{	
				cout<<"and:";//<<"  iSonNum: "<<pNodeCur->iSonNum; 
				      cout<<"  iNodeRow: "<<pNodeCur->iNodeRow ;
				      cout<<"  iNodeColumn: "<< pNodeCur->iNodeColumn;
				cout<<"  me: "<<pNodeCur;
				cout<<"  me.link: "<<pNodeCur->pNodeFather;						
				cout<<" me.linkleft: "<<pNodeCur->pNodeFather->pNodeLinkLeft;
				cout<<" me.linkright: "<<pNodeCur->pNodeFather->pNodeLinkRight;
						//<<"  father:"<<pNodeCur->pNodeFather->pNodeLinkFather;
				cout<<endl;            
				
			}
			else if(pNodeCur->iNodeOperate==2)
			{
				
								
				cout<<"or:";//<<"  tiSonNum: "<<pNodeCur->iSonNum ;
				        cout<<"  iNodeRow: "<<pNodeCur->iNodeRow ;
				         cout<<"  iNodeColumn:"<< pNodeCur->iNodeColumn;
				         
				//cout<<"DisposeNode ok 7"<<endl;				         
				
				cout<<" me: "<<pNodeCur;
				//cout<<"DisposeNode ok 7.1"<<endl;
				cout<<" me.link: "<<pNodeCur->pNodeFather;
				//cout<<"DisposeNode ok 7.2"<<endl;
				cout<<" me.linkleft: "<<pNodeCur->pNodeFather->pNodeLinkLeft;
				//cout<<"DisposeNode ok 7.3"<<endl;
				cout<<" me.linkright: "<<pNodeCur->pNodeFather->pNodeLinkRight;
				//cout<<"DisposeNode ok 7.4"<<endl;
				cout<<"  father: "<<pNodeCur->pNodeFather->pNodeLinkFather;
				//cout<<"DisposeNode ok 8"<<endl;
				cout<<endl;				            	
			}	
		
			i++;	
			
			DisposeNode(pNodeCur);
		}	
		else if(pNodeLinkCur->pElementBlew != NULL )	//下面的元素为元件 
		{				
			pElementCur=pNodeLinkCur->pElementBlew;		
			//cout<<"pNodeLinkCur->pNodeLinkRight "<<pNodeLinkCur->pNodeLinkRight<<endl;
			//if(pNodeLinkCur->pNodeLinkRight != NULL)
			//{
			//	cout<<"pNodeLinkCur->pNodeLinkRight->pElementBlew "<<pNodeLinkCur->pNodeLinkRight->pElementBlew<<endl;
			//	cout<<"pNodeLinkCur->pNodeLinkRight->pElementBlew->cName "<<pNodeLinkCur->pNodeLinkRight->pElementBlew->cName<<endl;
			//}	
			//输出
			int j=i;
			while(j>0)
			{
				cout<<"  ";	
				j--;
			}
			//cout<<"hold 1"<<endl;
			//cout<<" &pElementCur->cName  "<<&(pElementCur->cName)<<endl;
			//cout<<pElementCur->iNum;
			//cout<<"DisposeNode ok 10"<<endl;
//			cout<< pElementCur->cName;
			cout<<" "<< pElementCur->iNum <<" ";
			cout<< pElementCur->iState <<" "<< pElementCur->iPara ;
			cout<<" me: "<<pElementCur	;	
			//cout<<"DisposeNode ok 11"<<endl;
			cout<<" me.link: "<<pElementCur->pElementFather;	
			cout<<" me.linkleft: "<<pElementCur->pElementFather->pNodeLinkLeft;
			cout<<" me.linkright: "<<pElementCur->pElementFather->pNodeLinkRight;	
			cout<<" pNodefather: "<<pElementCur->pElementFather->pNodeLinkFather<<endl;	
			//cout<<"DisposeNode ok 12"<<endl;
		}	
		else
		{
			cout<<"error!"<<endl;	
		}
		//cout<<"*********************pNodeLinkCur:1: "<<pNodeLinkCur<<endl;
		pNodeLinkCur = pNodeLinkCur->pNodeLinkRight;
		//cout<<"pNodeLinkCur->pElementBlew: "<<pNodeLinkCur->pElementBlew<<endl;
		//cout<<"*********************pNodeLinkCur:2: "<<pNodeLinkCur<<endl;		
	}//end of while(pNodeLinkCur != NULL)
	//程序执行到这里,说明所有分支处理完毕但栈不一定为空!!
	//当子节点处理完，出栈。此处有问题！
	//此时pNodeLinkCur==NULL
	//cout<<"pNodeCur after while"<<pNodeCur<<endl;
	//cout<<"pNodeRoot after while"<<pNodeRootCur<<endl;

	if( pNodeCur==pNodeRootCur)
	{		
		if(StkpNode.size()>0)
		{	
			pNodeCur=StkpNode.top();
			StkpNode.pop();
			pNodeLinkCur=StkpNodeLink.top();
			StkpNodeLink.pop();
			i=StkInt.top();
			StkInt.pop();
			//这个地方有问题！！！！！！！！！！输出的格式有问题
						
		}	
		return 0;			
	}	
	return 0;
}


void ShapeLadderTest(Rung* pRungHead)
{
	Rung *pRungCur;
	Node *pNodeCur;
	pRungCur = pRungHead;
	
	/*
	if(pNodeCur == NULL)
	{
		cout<<"pNodeCur == NULL"<<endl;	
		return  0;
	}	
	*/
	//cout<<"################# in test_ladder ok "<<endl;
	while(pRungCur != NULL) 
	{
		pNodeCur=pRungCur->pNodeRoot;	
		cout<<"pRungCur "<<pRungCur<<" me.pPreRung "<<pRungCur->pPreRung<<" me.pNextRung "<<pRungCur->pNextRung<<" me.pNodeRoot "<<pNodeCur<<endl;
		
		//清空栈	
		{
			i=1;
		while(StkpNode.size()>0)
		{
			StkpNode.pop();
		}
		
		while(StkpNodeLink.size()>0)
		{
			StkpNodeLink.pop();
		}
		
		//cout<<"1 ok"<<endl;	
		
		}
		cout<<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"<<endl;
		if(pNodeCur->iNodeOperate==1)
		{	
			cout<<"and:" //<<" iSonNum "<<pNodeCur->iSonNum 
			            <<" iNodeRow: "<<pNodeCur->iNodeRow 
				          <<" iNodeColumn"<< pNodeCur->iNodeColumn;
		}
		else if(pNodeCur->iNodeOperate==2)
		{
		cout<<"or:"//<<" iSonNum "<<pNodeCur->iSonNum 
  	            <<" iNodeRow: "<<pNodeCur->iNodeRow 
				        <<" iNodeColumn"<< pNodeCur->iNodeColumn;		
		}	
		cout<<"  "<<pNodeCur;
		cout<<endl;
	//	cout<<"shape ladder test ok 1"<<endl;
		DisposeNode(pNodeCur);
		//cout<<"shape ladder test pNodeCur= "<<pNodeCur<<endl;
		//cout<<"shape ladder test ok 2"<<endl;
/*	
		cout<<"+++++++++++++++++poise"<<endl;
		pNodeCur->iNodeColumn=7;
		PoiseNode(pNodeCur);
		cout<<"pNodeCur->iNodeColumn:  "<<pNodeCur->iNodeColumn<<endl;
			
		DisposeNode(pNodeCur);
		cout<<"pNodeCur->iNodeColumn:  "<<pNodeCur->iNodeColumn<<endl;
*/
/*		

		UnPoiseNode(pNodeCur);
		DisposeNode(pNodeCur);
		//cout<<"2 ok"<<endl;	
*/
		
		pRungCur=pRungCur->pNextRung;
	}
}

