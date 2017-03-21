#include"plc_structure.h"
#include<qstring.h>
#include<iostream>
Element::Element(QString cNameTmp, int iNumTmp, int iStateTmp, int iParaTmp)	//构造函数
{
	id = 0;	//判断对象的类型0:Element, 1:Nodelink, 2:Node，3：Rung
	cName=cNameTmp;
	iNum=iNumTmp;
	iState=iStateTmp;	//元件初始状态的常开常闭初始状态或输出分支的OUT,SET,RST
										//0:常开，1:常闭，2:OUT, 3:SET, 4:RST
	iPara=iParaTmp;
	pElementFather= NULL;	
	//iMark=0;//下一条指令为MPS=1，MRD=2，MPP=3，其他=0；由指令生成树时用
}

Element::~Element()          
{
	pElementFather=NULL;
	//id=-1;//保证释放后不再被使用
}


NodeLink::NodeLink()
{
	id=1;	//判断对象的类型0:Element, 1:Nodelink, 2:Node，3：Rung
	pNodeLinkRight= NULL;
	pNodeLinkLeft= NULL;
	pNodeLinkFather= NULL;
	pElementBlew = NULL;	//指向链节下面元素
	pNodeBlew = NULL;		//指向链节下面操作节点
}

NodeLink::~NodeLink()
{
	pNodeLinkRight=NULL;
	pNodeLinkLeft=NULL;
	pNodeLinkFather=NULL;
	pNodeBlew=NULL;
	pElementBlew=NULL;
	//id=-1;//保证释放后不再被使用
}

Node::Node(int iNodeOperateIn)//根据boperate构造节点为and操作（=true）或or操作(=false)
{
	id = 2;	
	iNodeRow = 0;	
	iNodeColumn = 0;	
	iNodeOperate = iNodeOperateIn;
	//iSonNum = 0;
	pNodeFather = NULL;		//指向父节点的指针
	pNodeLinkSon = NULL;				//指向第一个子节点	 
	pNodeLinkLast = NULL;			//指向最后一个子节点，构造时用。
	pRung = NULL;	
	//iMark=0;//下一条指令为MPS=1，MRD=2，MPP=3，其他=0；由指令生成树时用
}

Node::~Node()
{	
	pNodeFather = NULL;	
	pNodeLinkSon = NULL;;	 
	pNodeLinkLast = NULL;
	pRung = NULL;
	//id=-1;//保证释放后不再被使用
}

int Node::AppendLink( Element *pElementTmp)//添加子 元件节点
{
	NodeLink *pNodeLink = new NodeLink;	//新建一个链节
	pElementTmp->pElementFather = pNodeLink;	//将新元件接到链节上
	pNodeLink->pNodeLinkFather = this;	//将链节接到当前Node上
	pNodeLink->pElementBlew = pElementTmp;
	pNodeLink->pNodeBlew = NULL;
	pNodeLink->pNodeLinkRight = NULL;	//链节的左右连接
	pNodeLink->pNodeLinkLeft = pNodeLinkLast;	
			
	if(pNodeLinkLast != NULL)	//当pNodeLinkLast不为零时,什么时候出现为零的情况?答:当节点添加第一个元素的时候
	{
		pNodeLinkLast->pNodeLinkRight = pNodeLink;	
	}	
	
	if(pNodeLinkSon == NULL)	//如果父节点还没有子节点，把当前节点作为首子节点
	{
			pNodeLinkSon = pNodeLink;
	}
	
	pNodeLinkLast = pNodeLink;	//更改最后子节点
	//iSonNum ++;
	return 0;
}
int Node::AppendLink( Node *pNodeTmp)	//添加子 操作节点
{
	if(pNodeTmp->iNodeOperate == iNodeOperate)
	{
		return(-1);		//不应该出现 添加的节点与父节点同为&或or。 报错
	}
	
	NodeLink *pNodeLink = new NodeLink;	//新建一个链节
	pNodeTmp->pNodeFather = pNodeLink;	//将新Node接到链节上
	pNodeLink->pNodeLinkFather = this;	//将链节接到当前Node上
	pNodeLink->pNodeBlew = pNodeTmp;
	pNodeLink->pElementBlew = NULL;
	pNodeLink->pNodeLinkRight = NULL;	//链节的左右连接
	pNodeLink->pNodeLinkLeft = pNodeLinkLast;
	
	if(pNodeLinkLast != NULL)	//当pNodeLinkLast不为零时,什么时候出现为零的情况?答:当节点添加第一个元素的时候
	{
		pNodeLinkLast->pNodeLinkRight = pNodeLink;	
	}	
	
	if(pNodeLinkSon == NULL)	//如果父节点还没有子节点，把当前节点作为首子节点
	{
			pNodeLinkSon = pNodeLink;
	}
	
	pNodeLinkLast = pNodeLink;	//更改最后子节点
	//iSonNum ++;
	
	//修改行列数
	if(iNodeOperate==1)			//and操作 
	{
		iNodeRow = iNodeRow>(pNodeTmp->iNodeRow) ?  iNodeRow : (pNodeTmp->iNodeRow);
																					//行数取所有节点的行数的最大值
		iNodeColumn += pNodeTmp->iNodeColumn;	//列数为所有子节点的列数的和
	}
	else if(iNodeOperate==2)	//or操作
	{
		iNodeRow += pNodeTmp->iNodeRow;	//行数取所有节点的行数的和
		iNodeColumn = iNodeColumn>(pNodeTmp->iNodeColumn)? iNodeColumn : (pNodeTmp->iNodeColumn);	
																	//列数为所有子节点的列数的最大值							
	}
	else
	{
		return -1;	//在构造树时只有这两种操作，没有空Node
	}
	
	return 0;
}

Rung::Rung()
{
	id=3;	//判断对象的类型0:Element, 1:Nodelink, 2:Node，3：Rung
	iRungRow = 0;		//梯级的总行数 空梯级为一
	iRungRowNum = 0;
	pNodeRoot = NULL;			//指向梯级的根节点
	pNextRung = NULL;	//指向后一梯级
	pPreRung = NULL;		//指向前一梯级

}

Rung::~Rung()
{
	pNodeRoot = NULL;	
	pNextRung = NULL;	
	pPreRung = NULL;	
	//id=-1;//保证释放后不再被使用
}




