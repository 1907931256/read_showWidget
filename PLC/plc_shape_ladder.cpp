#include "plc_shape_ladder.h"
//#include <iomanip.h>

static int And(Element *pElement);
static int Or(Element *pElement);
static int Anb();
static int Orb();
static int AssembleOutputBranchs(); 
static int Out(Element *pElement);
static void Nto();	//梯级结束
static void ReleaseStackMemory();//释放所有空间,

FILE *g_fpPLC;
Rung *g_pRungHead=NULL; //函数的返回值，梯的第一个梯级的地址
Rung *g_pRungLast=NULL;	//构造过程中梯的最后一个梯级的地址

StackPlc *stkBranch = new StackPlc;//生成树的栈，核心！！！

static int And(Element *pElement)
{
	/***********************************************************************
	栈顶为AND节点，直接插入	
	栈顶不为AND节点，新建一个and节点，将栈顶与元件插入，新建的and节点入栈
	************************************************************************/	
	int topId = stkBranch->TopId();	//获得栈顶分支类型(元件0或节点2)
	switch(topId) //根据栈顶分支类型的不同采取不同的操作
	{
		case 0: //若栈顶为元件
		{
			Element *pElementTop;	//建立一个元件变指针量以获取栈顶单元的指针
			stkBranch->GetTop(&pElementTop);	//获取栈顶单元的指针
			Node *pNode = new Node(1);		//新建一个and节点
			pNode->AppendLink(pElementTop);	//将栈顶元件插入新建节点
			pNode->AppendLink(pElement);		//将刚才读入的元件插入新建节点
			stkBranch->Pop();				//将栈顶元件出栈
			stkBranch->Push(pNode);	//将新建节点入栈
			break;
		}
		case 2:	//若栈顶为节点
		{
			Node *pNodeTop;	
			stkBranch->GetTop( &pNodeTop);	//读取栈顶节点指针
				
			if(pNodeTop->iNodeOperate == 1)		//若栈顶节点为操作为and
			{
				pNodeTop->AppendLink(pElement);
			}	
			else if(pNodeTop->iNodeOperate == 2)	//若栈顶节点为操作为or
			{
				Node *pNode = new Node(1);	//新建一and节点
				pNode->AppendLink(pNodeTop);
				pNode->AppendLink(pElement);
				stkBranch->Pop();
				stkBranch->Push(pNode);
			}
			else
			{	
				return -1;	
			}
			break;	
		}	//end of case(2)
		default:
		{
			return -1;
		}
	}	//end of switch(topId)	
	return 0;	
}//end of AND

static int Or(Element *pElement)
{
	/***********************************************************************
	栈顶为or节点，直接插入	
	栈顶不为or节点，新建一个or节点，将栈顶与元件插入，新建的or节点入栈
	************************************************************************/
	int topId = stkBranch->TopId();	//获得栈顶分支类型(元件0或节点2)
	switch(topId) //根据栈顶分支类型的不同采取不同的操作
	{
		case 0: //若栈顶为元件
		{
			Element *pElementTop;	//建立一个元件变指针量以获取栈顶单元的指针
			stkBranch->GetTop(&pElementTop);	//获取栈顶单元的指针
			Node  *pNode = new Node(2);		//新建一个OR节点
			pNode->AppendLink(pElementTop);	//将栈顶元件插入新建节点
			pNode->AppendLink(pElement);		//将刚才读入的元件插入新建节点
			stkBranch->Pop();				//将栈顶元件出栈
			stkBranch->Push(pNode);	//将新建节点入栈
			break;
		}
		case 2://若栈顶为节点
		{
			Node *pNodeTop;
			stkBranch->GetTop(&pNodeTop);	//读取栈顶节点指针
						
			if(pNodeTop->iNodeOperate == 2)		//若栈顶节点操作为or
			{
				pNodeTop->AppendLink(pElement);
			}	
			else if(pNodeTop->iNodeOperate == 1)	//若栈顶节点为操作为and
			{
				Node *pNode = new Node(2);//新建一个or节点
				pNode->AppendLink(pNodeTop);
				pNode->AppendLink(pElement);
				stkBranch->Pop();
				stkBranch->Push(pNode);
			}
			else
			{
				return -1;	
			}
			break;	
		}	//end of case(2)
		default:
		{	
			return -1;
		}	
	}	//end of switch(topId)
	return 0;	
}//end of OR

static int Anb()
{
	if(stkBranch->Size() <2)
	{
		return -1;
	}		
	//cout<<__FILE__<<"  "<<__LINE__<<endl;
	//读栈顶
	Node *pNodeTop = NULL;
	Element *pElementTop = NULL;
	int topId = stkBranch->TopId();	//获得栈顶分支类型(元件0或节点2)
	if( topId == 0)
	{	
		//cout<<"-1--0----"<<__FILE__<<"  "<<__LINE__<<endl;
		stkBranch->GetTop(&pElementTop);
	}	
	else if(topId ==2)
	{
		//cout<<"-1--2----"<<__FILE__<<"  "<<__LINE__<<endl;
		stkBranch->GetTop( &pNodeTop);	
	}	
	//cout<<__FILE__<<"  "<<__LINE__<<endl;	
	stkBranch->Pop();          //出栈，准备读栈内第二个数据
	
	//读现在的栈顶
	Node *pNodeTopSub = NULL;
	Element *pElementTopSub = NULL;
	topId = stkBranch->TopId();//获得现在栈顶的分支类型(元件0或节点2)
	if( topId == 0)
	{	
		//cout<<"-2--0----"<<__FILE__<<"  "<<__LINE__<<endl;
		stkBranch->GetTop(&pElementTopSub);
	}	
	else if(topId ==2)
	{
		//cout<<"-2--2----"<<__FILE__<<"  "<<__LINE__<<endl;
		stkBranch->GetTop( &pNodeTopSub);	
	}	
	
	if(pElementTop != NULL && pElementTopSub != NULL)	
	{
		//cout<<__FILE__<<"  "<<__LINE__<<endl;
		Node  *pNode = new Node(1);		//新建一个and节点
		pNode->AppendLink(pElementTopSub);	//将栈顶元件插入新建节点
		pNode->AppendLink(pElementTop);		//将刚才读入的元件插入新建节点
		stkBranch->Pop();				//将栈顶元件出栈
		stkBranch->Push(pNode);	//将新建节点入栈
	}
	else if(pElementTop != NULL && pNodeTopSub != NULL)	
	{
		//cout<<__FILE__<<"  "<<__LINE__<<endl;
		int i = pNodeTopSub->iNodeOperate;
		if(i == 1)		//若节点为操作and
		{
			pNodeTopSub->AppendLink(pElementTop);
		}	
		else if(i == 2)	//若节点为or
		{
			Node  *pNode = new Node(1);		//新建一个and节点
			pNode->AppendLink(pNodeTopSub);	
			pNode->AppendLink(pElementTop);	
			stkBranch->Pop();				//将栈顶元件出栈
			stkBranch->Push(pNode);	//将新建节点入栈
		}			
	}
	else if(pNodeTop != NULL && pElementTopSub != NULL)	
	{
		int i = pNodeTop->iNodeOperate;
		if(i == 1)		//若节点为操作and
		{
			pNodeTop->AppendLink(pElementTopSub);
			stkBranch->Pop();	
			stkBranch->Push(pNodeTop);
		}	
		else if(i == 2)	//若节点为or
		{
			Node  *pNode = new Node(1);		//新建一个and节点			
			pNode->AppendLink(pElementTopSub);	
			pNode->AppendLink(pNodeTop);	
			stkBranch->Pop();				//将栈顶元件出栈
			stkBranch->Push(pNode);	//将新建节点入栈
		}			
	}
	else if(pNodeTop != NULL && pNodeTopSub != NULL)	
	{
		int i = pNodeTop->iNodeOperate;
		int j = pNodeTopSub->iNodeOperate;
		if(i ==1 && j==1)	//都是and节点
		{
			//把pNodeTop的所有分支嫁接到pNodeTopSub上去
			NodeLink *pNodeLink = pNodeTop->pNodeLinkSon;
			while(pNodeLink != NULL)
			{//AppendLink
				if(pNodeLink->pElementBlew != NULL)
				{
					pNodeTopSub->AppendLink(pNodeLink->pElementBlew);
				}
				else if(pNodeLink->pNodeBlew != NULL)
				{
					pNodeTopSub->AppendLink(pNodeLink->pNodeBlew);
				}				
				pNodeLink = pNodeLink->pNodeLinkRight;	
			}
			//释放内存
			pNodeLink = pNodeTop->pNodeLinkSon;
			while(pNodeLink != NULL)
			{
				NodeLink *pNodeLinkTmp = pNodeLink;
				pNodeLink = pNodeLink->pNodeLinkRight;				
				delete pNodeLinkTmp;
			}
			delete pNodeTop;
		}
		else if( i==1 && j==2)	//and or
		{			
			NodeLink *pNodeLink = new NodeLink();			
			pNodeLink->pElementBlew = NULL;
			pNodeLink->pNodeBlew = pNodeTopSub;
			pNodeLink->pNodeLinkFather = pNodeTop;
			pNodeLink->pNodeLinkLeft = NULL;
			pNodeLink->pNodeLinkRight = pNodeTop->pNodeLinkSon;
			pNodeTop->pNodeLinkSon->pNodeLinkLeft = pNodeLink;
			pNodeTop->pNodeLinkSon = pNodeLink;					
			stkBranch->Pop();	
			stkBranch->Push(pNodeTop);
		}
		else if( i==2 && j==1)//or and
		{
			pNodeTopSub->AppendLink(pNodeTop);			
		}
		else if( i==2 && j==2)//or or
		{
			//cout<<__FILE__<<"  "<<__LINE__<<endl;
			//新建and将pNodeTopSub和pNodeTopSub插入, 出栈 入栈
			Node *pNodeNew = new Node(1);
			pNodeNew->AppendLink(pNodeTopSub);
			pNodeNew->AppendLink(pNodeTop);
			stkBranch->Pop();	
			stkBranch->Push(pNodeNew);			
		}		
	}
	else
	{
		return -1;	
	}
	return 0;
}//end of ANB

static int Orb()
{
	if(stkBranch->Size() <2)
	{
		return -1;
	}
	//读栈顶
	Node *pNodeTop = NULL;
	Element *pElementTop = NULL;
	int topId = stkBranch->TopId();	//获得栈顶分支类型(元件0或节点2)
	if( topId == 0)
	{	
		//cout<<"-1--0----"<<__FILE__<<"  "<<__LINE__<<endl;
		stkBranch->GetTop(&pElementTop);
	}	
	else if(topId ==2)
	{
		//cout<<"-1--2----"<<__FILE__<<"  "<<__LINE__<<endl;
		stkBranch->GetTop( &pNodeTop);	
	}	
	//cout<<__FILE__<<"  "<<__LINE__<<endl;	
	stkBranch->Pop();          //出栈，准备读栈内第二个数据
	
	//读现在的栈顶
	Node *pNodeTopSub = NULL;
	Element *pElementTopSub = NULL;
	topId = stkBranch->TopId();//获得现在栈顶的分支类型(元件0或节点2)
	if( topId == 0)
	{	
		//cout<<"-2--0----"<<__FILE__<<"  "<<__LINE__<<endl;
		stkBranch->GetTop(&pElementTopSub);
	}	
	else if(topId ==2)
	{
		//cout<<"-2--2----"<<__FILE__<<"  "<<__LINE__<<endl;
		stkBranch->GetTop( &pNodeTopSub);	
	}	
	
	if(pElementTop != NULL && pElementTopSub != NULL)	
	{
		//cout<<__FILE__<<"  "<<__LINE__<<endl;
		Node  *pNode = new Node(2);		//新建一个or节点
		pNode->AppendLink(pElementTopSub);	//将栈顶元件插入新建节点
		pNode->AppendLink(pElementTop);		//将刚才读入的元件插入新建节点
		stkBranch->Pop();				//将栈顶元件出栈
		stkBranch->Push(pNode);	//将新建节点入栈
		//cout<<__FILE__<<"  "<<__LINE__<<endl;
	}
	else if(pElementTop != NULL && pNodeTopSub != NULL)	
	{
		//cout<<__FILE__<<"  "<<__LINE__<<endl;
		int i = pNodeTopSub->iNodeOperate;
		if(i == 1)		//若节点为操作and
		{
			Node  *pNode = new Node(2);		//新建一个or节点
			pNode->AppendLink(pNodeTopSub);	
			pNode->AppendLink(pElementTop);	
			stkBranch->Pop();				//将栈顶元件出栈
			stkBranch->Push(pNode);	//将新建节点入栈
		}	
		else if(i == 2)	//若节点为or
		{			
			pNodeTopSub->AppendLink(pElementTop);
		}			
	}
	else if(pNodeTop != NULL && pElementTopSub != NULL)	
	{
		int i = pNodeTop->iNodeOperate;
		if(i == 1)		//若节点为操作and
		{			
			Node  *pNode = new Node(2);		//新建一个and节点			
			pNode->AppendLink(pElementTopSub);	
			pNode->AppendLink(pNodeTop);	
			stkBranch->Pop();				//将栈顶元件出栈
			stkBranch->Push(pNode);	//将新建节点入栈			
		}	
		else if(i == 2)	//若节点为or
		{
			pNodeTop->AppendLink(pElementTopSub);
			stkBranch->Pop();	
			stkBranch->Push(pNodeTop);
		}			
	}
	else if(pNodeTop != NULL && pNodeTopSub != NULL)	
	{
		int i = pNodeTop->iNodeOperate;
		int j = pNodeTopSub->iNodeOperate;
		if(i ==1 && j==1)	//都是and节点
		{
			//cout<<__FILE__<<"  "<<__LINE__<<endl;
			//新建or将pNodeTopSub和pNodeTopSub插入, 出栈 入栈
			Node *pNodeNew = new Node(2);
			pNodeNew->AppendLink(pNodeTopSub);
			pNodeNew->AppendLink(pNodeTop);
			stkBranch->Pop();	
			stkBranch->Push(pNodeNew);			
		}
		else if( i==1 && j==2)	//and or
		{
			pNodeTopSub->AppendLink(pNodeTop);						
		}
		else if( i==2 && j==1)//or and
		{
			NodeLink *pNodeLink = new NodeLink();			
			pNodeLink->pElementBlew = NULL;
			pNodeLink->pNodeBlew = pNodeTopSub;
			pNodeLink->pNodeLinkFather = pNodeTop;
			pNodeLink->pNodeLinkLeft = NULL;
			pNodeLink->pNodeLinkRight = pNodeTop->pNodeLinkSon;
			pNodeTop->pNodeLinkSon->pNodeLinkLeft = pNodeLink;
			pNodeTop->pNodeLinkSon = pNodeLink;					
			stkBranch->Pop();	
			stkBranch->Push(pNodeTop);
		}
		else if( i==2 && j==2)//or or
		{
			//把pNodeTop的所有分支嫁接到pNodeTopSub上去
			NodeLink *pNodeLink = pNodeTop->pNodeLinkSon;
			while(pNodeLink != NULL)
			{//AppendLink
				if(pNodeLink->pElementBlew != NULL)
				{
					pNodeTopSub->AppendLink(pNodeLink->pElementBlew);
				}
				else if(pNodeLink->pNodeBlew != NULL)
				{
					pNodeTopSub->AppendLink(pNodeLink->pNodeBlew);
				}				
				pNodeLink = pNodeLink->pNodeLinkRight;	
			}
			//释放内存
			pNodeLink = pNodeTop->pNodeLinkSon;
			while(pNodeLink != NULL)
			{
				NodeLink *pNodeLinkTmp = pNodeLink;
				pNodeLink = pNodeLink->pNodeLinkRight;				
				delete pNodeLinkTmp;
			}
			delete pNodeTop;		
		}		
	}
	else
	{
		return -1;	
	}
	return 0;	
}//end of ORB
static int  AssembleOutputBranchs()
{
	Node *pNodeOR = new Node(2);
	while( stkBranch->GetTopMark() != 11 && stkBranch->Size() > 0 )//一直找到iMark==11，或栈底,插入到or节点
	{			
		int topId = stkBranch->TopId();	//获得栈顶分支类型(元件0或节点2)		
		switch(topId) //根据栈顶分支类型的不同采取不同的操作
		{
			case 0: //若栈顶为元件
			{
				Element *pElementTop;	//建立一个元件变指针量以获取栈顶单元的指针
				stkBranch->GetTop(&pElementTop);	//获取栈顶单元的指针	
				NodeLink *pNodeLinkT = new NodeLink;
				//上下相连
				pNodeLinkT->pNodeLinkFather = pNodeOR;
				pNodeLinkT->pElementBlew = pElementTop;
				pNodeLinkT->pNodeBlew = NULL;
				pElementTop->pElementFather = pNodeLinkT;
				//左右相连
				if(pNodeOR->pNodeLinkSon != NULL)				
				{
					pNodeLinkT->pNodeLinkRight = pNodeOR->pNodeLinkSon;
					pNodeOR->pNodeLinkSon->pNodeLinkLeft = pNodeLinkT;												
				}	
				else
				{
					pNodeLinkT->pNodeLinkRight = NULL;
				}						
				pNodeLinkT->pNodeLinkLeft = NULL;
				pNodeOR->pNodeLinkSon = pNodeLinkT;	
				break;	
			}
			case 2://若栈顶为节点
			{	
				Node *pNodeTop;					
				stkBranch->GetTop(&pNodeTop);	//读取栈顶节点指针			
				if(pNodeTop->iNodeOperate == 1)		//若栈顶节点为操作为and
				{
					NodeLink *pNodeLinkT = new NodeLink;
					//上下相连
					pNodeLinkT->pNodeLinkFather = pNodeOR;
					pNodeLinkT->pElementBlew = NULL;
					pNodeLinkT->pNodeBlew = pNodeTop;
					pNodeTop->pNodeFather = pNodeLinkT;
					//左右相连
					if(pNodeOR->pNodeLinkSon != NULL)				
					{
						pNodeLinkT->pNodeLinkRight = pNodeOR->pNodeLinkSon;
						pNodeOR->pNodeLinkSon->pNodeLinkLeft = pNodeLinkT;												
					}	
					else
					{
						pNodeLinkT->pNodeLinkRight = NULL;
					}						
					pNodeLinkT->pNodeLinkLeft = NULL;
					pNodeOR->pNodeLinkSon = pNodeLinkT;		
				}//end of if(pNodeTop->iNodeOperate == 1)							
				else
				{							
					return -1;	
				}//end of else(pNodeTop->iNodeOperate == 1)			
				
				break;	
			}	//end of case(2)
			default:
			{					
				return -1;
			}
		}	//end of switch(topId)
		stkBranch->Pop();				//将栈顶弹出				
	}//end of while	
	
	//此时当前多数出分支的所有输出分支	都插入OR里，并从栈内弹出	
	stkBranch->SetTopMark(0);	//此时的栈顶的特殊标记已经完成使命，置0，
	stkBranch->Push(pNodeOR);	//将新建节点入栈	
	if( Anb() != 0)	
	{
		return -1;	
	}	
	return 0;
}

static int Out(Element *pElement)
{	
	//cout<<__FILE__<<"  "<<__LINE__<<endl;
/*****************************************************
作用：单输出的最后一步，多分支的一支的最后一步
分两步
一的结果，生成一个and节点或单个输出元件的光杆
	如果栈顶的iMark
		！=0,将Y入栈	
		 == 0,正常处理		 
二如果最近的iMark为MPP，
	1,新建一个or节点
	2,从栈定向下寻找第一个iMark为MPS的单元，
	3,将这些单元插入（并pop）新建的or节点。
	4,Anb()		
******************************************************/
//一：	
	if( stkBranch->GetTopMark() == 0)
	{
		if( And(pElement) !=0 )
		{
			return -1;	
		}	
	}
	else	//多数出分支的光杆分支
	{		
		stkBranch->Push(pElement);			
	}	
//二	
	//获得最近的一个非零的iMarkNear
	int iNum = stkBranch->Size();	
	int iMarkNear = 0;
	for(int i = iNum; i>0; i--)
	{
		iMarkNear = stkBranch->GetMark(i);		
		if(iMarkNear != 0)
		{
			break;	
		}	
	}
	//判断iMarkNear
	if(iMarkNear == 3)
	{		
		/**************************************************************************
		即最近的M状态为MPP
		要把当前的多输出分支整理出来
		栈内MPS到MPP之间的单元只可能是表示输出分支的 	1，and节点 2，输出元件。
		新建一表示多数出的or节点，把从栈顶开始至到MPS的单元依次逆序插入OR节点，
		***************************************************************************/
		//为了对付多段栈所以用 while
		while(stkBranch->GetIndexMarkNearE(11) != 0)	
		{
			if( AssembleOutputBranchs()!=0)		//将多数出的所有分枝插入到一个新建的or节点		
			{
				return -1;	
			}								
		}//end of while			
	}
	else
	{
		//do nothing	
	}	//end of else(iMarkNear == 3)
	
	//cout<<__FILE__<<"  "<<__LINE__<<endl;
	//cout<<"stkBranch->Size()="<<stkBranch->Size()<<endl;
	if(stkBranch->Size() == 1)
	{
		//cout<<__FILE__<<"  "<<__LINE__<<endl;
		Nto();	
		//cout<<__FILE__<<"  "<<__LINE__<<endl;
	}	
	return 0;
}
static void  Nto()
{
	//cout<<__FILE__<<"  "<<__LINE__<<endl;
	//此时栈顶为梯级的根节点,现在将梯级加到梯上	
	Node *pNodeTop;				
	stkBranch->GetTop(&pNodeTop);	//读取栈顶节点指针
	stkBranch->Pop();				
	//cout<<__FILE__<<"  "<<__LINE__<<endl;
	//建立梯级
	Rung *pRung = new Rung;
	pRung->pNodeRoot = pNodeTop;
	pRung->iRungRow  = pNodeTop->iNodeRow;
	pNodeTop->pRung = pRung;					
	//添加到总链
	if (g_pRungHead == NULL)
	{
		g_pRungHead = pRung;						
		g_pRungLast = pRung;
	}	
	else
	{				
		g_pRungLast->pNextRung = pRung;	
		pRung->pPreRung = g_pRungLast;
		g_pRungLast=pRung;											
	}
	//cout<<__FILE__<<"  "<<__LINE__<<endl;
	/*这时栈内应该只剩下一个元素，只要pop()就可以了，
	这样写万一出错也只是在一个梯级范围内，不会影响到下一个梯级*/
	ReleaseStackMemory();
}	//end of NTO

Rung *ShapeLadder(char *cFileName)
{		
	unsigned int uiInstruction;	//暂存读出的指令
	unsigned int uiNum;//元件的编号
	unsigned int uiOperate;	//操作码
    if( (g_fpPLC=fopen(cFileName,"rb")) == NULL)	//"plc_instruction.txt"   如果打开失败
    {
		return NULL;
	}		
	fread(&uiInstruction,sizeof(unsigned int),1,g_fpPLC);	//读入一条指令	
	while(feof(g_fpPLC)== 0)		//一旦进入循环直到指令读完结束
	{			
		uiOperate = uiInstruction >> 16;		//取操作码
		uiNum = uiInstruction & 0xFFFF;	//取操作数	
		static int i=0;
		//cout<<"i="<<i<<endl;
		//cout<<setbase(16)<<"uiOperate="<<uiOperate<<endl;	
		//cout<<"uiNum="<<uiNum<<setbase(10)<<endl;
		i++;
		switch(uiOperate)
		{			
			case LD_X:       //0xFF01
			{
				Element *pElement = new Element(QString("X"),uiNum,0,0);
				stkBranch->Push(pElement);				
				break;	
			}
			case LD_Y:       //0xFF02
			{
				Element *pElement = new Element(QString("Y"),uiNum,0,0);
				stkBranch->Push(pElement);				
				break;	
			}
			case LD_M:       //0xFF03
			{
				Element *pElement = new Element(QString("M"),uiNum,0,0);
				stkBranch->Push(pElement);				
				break;	
			}
			case LD_C:       //0xFF04
			{
				Element *pElement = new Element(QString("C"),uiNum,0,0);
				stkBranch->Push(pElement);				
				break;	
			}
			case LD_T:       //0xFF05
			{
				Element *pElement = new Element(QString("T"),uiNum,0,0);
				stkBranch->Push(pElement);				
				break;	
			}			
			case LDI_X:       //0xFE01
			{
				Element *pElement = new Element(QString("X"),uiNum,1,0);
				stkBranch->Push(pElement);				
				break;	
			}
			case LDI_Y:       //0xFE02
			{
				Element *pElement = new Element(QString("Y"),uiNum,1,0);
				stkBranch->Push(pElement);				
				break;	
			}
			case LDI_M:       //0xFE03
			{
				Element *pElement = new Element(QString("M"),uiNum,1,0);
				stkBranch->Push(pElement);				
				break;	
			}
			case LDI_C:       //0xFE04
			{
				Element *pElement = new Element(QString("C"),uiNum,1,0);
				stkBranch->Push(pElement);				
				break;	
			}
			case LDI_T:       //0xFE05
			{
				Element *pElement = new Element(QString("T"),uiNum,1,0);
				stkBranch->Push(pElement);				
				break;	
			}			
			case AND_X:      //0xFD01
			{
				Element *pElement = new Element(QString("X"),uiNum,0,0);
				if(stkBranch->GetTopMark()==0)
				{	
					if(And(pElement) != 0)
					{
						ReleaseStackMemory();
						return NULL;	
					}	
				}
				else
				{
					stkBranch->Push(pElement);		
				}		
				break;	
			}	//end of case AND_X
			case AND_Y:      //0xFD02
			{
				Element *pElement = new Element(QString("Y"),uiNum,0,0);
				if(stkBranch->GetTopMark()==0)
				{	
					if(And(pElement) != 0)
					{
						ReleaseStackMemory();
						return NULL;	
					}	
				}
				else
				{
					stkBranch->Push(pElement);		
				}		
				break;		
			}	//end of case AND_Y
			case AND_M:      //0xFD03
			{
				Element *pElement = new Element(QString("M"),uiNum,0,0);
				if(stkBranch->GetTopMark()==0)
				{	
					if(And(pElement) != 0)
					{
						ReleaseStackMemory();
						return NULL;	
					}	
				}
				else
				{
					stkBranch->Push(pElement);		
				}		
				break;	
			}	//end of case AND_M
			case AND_C:      //0xFD04
			{
				Element *pElement = new Element(QString("C"),uiNum,0,0);
				if(stkBranch->GetTopMark()==0)
				{	
					if(And(pElement) != 0)
					{
						ReleaseStackMemory();
						return NULL;	
					}	
				}
				else
				{
					stkBranch->Push(pElement);		
				}		
				break;	
			}	//end of case AND_C
			case AND_T:      //0xFD05
			{
				Element *pElement = new Element(QString("T"),uiNum,0,0);
				if(stkBranch->GetTopMark()==0)
				{	
					if(And(pElement) != 0)
					{
						ReleaseStackMemory();
						return NULL;	
					}	
				}
				else
				{
					stkBranch->Push(pElement);		
				}		
				break;	
			}	//end of case AND_T
			case ANI_X:      //0xFC01
			{
				Element *pElement = new Element(QString("X"),uiNum,1,0);
				if(stkBranch->GetTopMark()==0)
				{	
					if(And(pElement) != 0)
					{
						ReleaseStackMemory();
						return NULL;	
					}	
				}
				else
				{
					stkBranch->Push(pElement);		
				}		
				break;	
			}	//end of case ANI_X
			case ANI_Y:      //0xFC02
			{
				Element *pElement = new Element(QString("Y"),uiNum,1,0);
				if(stkBranch->GetTopMark()==0)
				{	
					if(And(pElement) != 0)
					{
						ReleaseStackMemory();
						return NULL;	
					}	
				}
				else
				{
					stkBranch->Push(pElement);		
				}		
				break;	
			}	//end of case ANI_Y
			case ANI_M:      //0xFC03
			{
				Element *pElement = new Element(QString("M"),uiNum,1,0);
				if(stkBranch->GetTopMark()==0)
				{	
					if(And(pElement) != 0)
					{
						ReleaseStackMemory();
						return NULL;	
					}	
				}
				else
				{
					stkBranch->Push(pElement);		
				}		
				break;	
			}	//end of case ANI_M
			case ANI_C:      //0xFC04
			{
				Element *pElement = new Element(QString("C"),uiNum,1,0);
				if(stkBranch->GetTopMark()==0)
				{	
					if(And(pElement) != 0)
					{
						ReleaseStackMemory();
						return NULL;	
					}	
				}
				else
				{
					stkBranch->Push(pElement);		
				}		
				break;	
			}	//end of case ANI_C
			case ANI_T:      //0xFC05
			{
				Element *pElement = new Element(QString("T"),uiNum,1,0);
				if(stkBranch->GetTopMark()==0)
				{	
					if(And(pElement) != 0)
					{
						ReleaseStackMemory();
						return NULL;	
					}	
				}
				else
				{
					stkBranch->Push(pElement);		
				}		
				break;	
			}	//end of case ANI_T	
			case OR_X:       //0xFB01
			{
				Element *pElement = new Element(QString("X"),uiNum,0,0);											
				if( Or(pElement) != 0)
				{
					ReleaseStackMemory();
					return NULL;	
				}	
				break;	
			}	//end of case OR_X	
			case OR_Y:       //0xFB02
			{
				Element *pElement = new Element(QString("Y"),uiNum,0,0);				
				if( Or(pElement) != 0)
				{
					ReleaseStackMemory();
					return NULL;	
				}	
				break;
			}	//end of case OR_Y	
			case OR_M:       //0xFB03
			{
				Element *pElement = new Element(QString("M"),uiNum,0,0);				
				if( Or(pElement) != 0)
				{
					ReleaseStackMemory();
					return NULL;	
				}	
				break;
			}	//end of case OR_M	
			case OR_C:       //0xFB04
			{
				Element *pElement = new Element(QString("C"),uiNum,0,0);				
				if( Or(pElement) != 0)
				{
					ReleaseStackMemory();
					return NULL;	
				}	
				break;
			}	//end of case OR_C	
			case OR_T:       //0xFB05
			{
				Element *pElement = new Element(QString("T"),uiNum,0,0);				
				if( Or(pElement) != 0)
				{
					ReleaseStackMemory();
					return NULL;	
				}	
				break;
			}	//end of case OR_T				
			case ORI_X:       //0xFA01
			{
				Element *pElement = new Element(QString("X"),uiNum,1,0);				
				if( Or(pElement) != 0)
				{
					ReleaseStackMemory();
					return NULL;	
				}	
				break;
			}	//end of case ORI_X	
			case ORI_Y:       //0xFA02
			{
				Element *pElement = new Element(QString("Y"),uiNum,1,0);				
				if( Or(pElement) != 0)
				{
					ReleaseStackMemory();
					return NULL;	
				}	
				break;	
			}	//end of case ORI_Y	
			case ORI_M:       //0xFA03
			{
				Element *pElement = new Element(QString("M"),uiNum,1,0);				
				if( Or(pElement) != 0)
				{
					ReleaseStackMemory();
					return NULL;	
				}	
				break;
			}	//end of case ORI_M	
			case ORI_C:       //0xFA04
			{
				Element *pElement = new Element(QString("C"),uiNum,1,0);				
				if( Or(pElement) != 0)
				{
					ReleaseStackMemory();
					return NULL;	
				}	
				break;	
			}	//end of case ORI_C	
			case ORI_T:       //0xFA05
			{
				Element *pElement = new Element(QString("T"),uiNum,1,0);				
				if( Or(pElement) != 0)
				{
					ReleaseStackMemory();
					return NULL;	
				}	
				break;	
			}	//end of case ORI_T		
			case ANB:        //0xF900
			{	
				int iNum = stkBranch->Size();	
				if(stkBranch->GetMark(iNum-1) != 0)	//获得栈顶下面一个单元的mark值，如果不为零...					
				{																		//...说明当前的状态为多输出分支的首子分支为AND节点。不处理		
					//do nothing;											//...因为梯级的数据结构是这样要求的
				}
				else
				{
					if( Anb() != 0)
					{
						ReleaseStackMemory();
						return NULL;	
					}	
				}					
				break;	
			}	//end of ANB			
			case ORB:        //0xF800
			{		
				if(Orb() != 0)
				{
					ReleaseStackMemory();
					return NULL;	
				}	
				break;	
			}	//end of ORB		
			case OUT_Y:     //0xF202
			{				
				Element *pElement = new Element(QString("Y"),uiNum,2,0);												
				if( Out(pElement) != 0)
				{
					ReleaseStackMemory();
					return NULL;	
				}					
				break;	
			}	//end of case OUT_Y
			case OUT_M:     //0xF203
			{				
				Element *pElement = new Element(QString("M"),uiNum,2,0);							
				if( Out(pElement) != 0)
				{
					ReleaseStackMemory();
					return NULL;	
				}					
				break;		
			}	//end of case OUT_M
			case OUT_C:     //0xF204
			{				
				fread(&uiInstruction,sizeof(unsigned int),1,g_fpPLC);	//读入下一条指令/即为计数器的设定值
				Element *pElement = new Element(QString("C"),uiNum,2,uiInstruction);							
				if( Out(pElement) != 0)
				{
					ReleaseStackMemory();
					return NULL;	
				}					
				break;	
			}	//end of case OUT_C
			case OUT_T:     //0xF205
			{				
				fread(&uiInstruction,sizeof(unsigned int),1,g_fpPLC);	//读入下一条指令/即为计数器的设定值		
				Element *pElement = new Element(QString("T"),uiNum,2,uiInstruction);							
				if( Out(pElement) != 0)
				{
					ReleaseStackMemory();
					return NULL;	
				}					
				break;	
			}	//end of case OUT_T
			case SET_Y:     //0xF702
			{				
				Element *pElement = new Element(QString("Y"),uiNum,3,0);							
				if( Out(pElement) != 0)
				{
					ReleaseStackMemory();
					return NULL;	
				}					
				break;	
			}	//end of case SET_Y
			case SET_M:     //0xF703
			{				
				Element *pElement = new Element(QString("M"),uiNum,3,0);							
				if( Out(pElement) != 0)
				{
					ReleaseStackMemory();
					return NULL;	
				}					
				break;	
			}	//end of case SET_M
			case RST_Y:     //0xF602
			{				
				Element *pElement = new Element(QString("Y"),uiNum,4,0);							
				if( Out(pElement) != 0)
				{
					ReleaseStackMemory();
					return NULL;	
				}					
				break;		
			}	//end of case RST_Y
			case RST_M:     //0xF603
			{				
				Element *pElement = new Element(QString("M"),uiNum,4,0);							
				if( Out(pElement) != 0)
				{
					ReleaseStackMemory();
					return NULL;	
				}					
				break;		
			}	//end of case RST_M
			case RST_C:     //0xF604
			{				
				Element *pElement = new Element(QString("C"),uiNum,4,0);							
				if( Out(pElement) != 0)
				{
					ReleaseStackMemory();
					return NULL;	
				}					
				break;		
			}	//end of case RST_C
			case RST_T:     //0xF605
			{				
				Element *pElement = new Element(QString("T"),uiNum,4,0);							
				if( Out(pElement) != 0)
				{
					ReleaseStackMemory();
					return NULL;	
				}					
				break;	
			}	//end of case RST_T
			case MPS:	 //0xF500
			{	
				stkBranch->SetTopMark(1);			
				break;				
			}			
			case MRD: 	//0xF400 
			{
				stkBranch->SetTopMark(2);	
				break;
			}//end of	MRD 
			case MPP: //0xF300 
			{			
				stkBranch->SetTopMark(3);	
												
				//将对应于当前的MPP的MPS“对消“：找到mark==1的单元，修改它的mark 值为11								
				int index = stkBranch->GetIndexMarkNearE(1);				
				if(index != 0)
				{
					stkBranch->SetMarkAt(index, 11);	
				}	
				else
				{
					ReleaseStackMemory();
					return NULL;	
				}									
				break;
			}//end of MPP	 
			/*
			case NTO: //0xF100
			{			
				Nto();
				break;	
			}	//end of NTO
			
			*/
			case END:  //0xF000
			{
				fclose(g_fpPLC);	//关闭文件
				
				//用一个局部变量代替全局变量
				Rung *pRungHeadTmp = g_pRungHead;
				g_pRungHead = NULL;							
				return pRungHeadTmp;//返回头指针				
				break;	
			}	//end of END			
			default:
			{
				ReleaseStackMemory();
				return NULL;	
			}	//end of default					
		}	//end of switch(uiOperate)		
		fread(&uiInstruction,sizeof(unsigned int),1,g_fpPLC);	//读入下一条指令	
	}	//end of while
	ReleaseStackMemory();
	return NULL;	
}	

static void ReleaseStackMemory()
{
	while( stkBranch->Size() >0 ) 
	{
		stkBranch->Pop();	
	}		
}



			
