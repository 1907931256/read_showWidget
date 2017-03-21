/* plc_check_node.cpp */
#include"plc_check_node.h"
/*******************************************
*对梯级根节点进行语法检查,不检查逻辑错误
*梯级正确返回0,错误返回-1.
检查内容包括: 
1,节点分支与父节点的操作不应相同,每个节点最少要有两个分支
2,and节点
	a如果含有输出元件,则最后一支必为输出元件或含有输出元件的节点.其它分支不应有输出元件
	b如果不含输出元件,
3,or节点
	a如果含有输出元件，则每个分支必为有输出元件或含有输出元件的节点
	b如果不含输出元件,
其实，按照编辑界面的输入规则 2，3	没有必要检查
********************************************/

static int CheckNodeOrOut(Node *pNode);
static int CheckNodeLinkNumAndOperate(Node *pNode);//检查分支数和节点的操作类型是否正确

int CheckNodeAndOut(Node *pNode)//小boss
{		
	if(FindOutInNode(pNode)==false)	//检查是否有输出元件
	{		
		return -1;	
	}	
	if( CheckNodeLinkNumAndOperate(pNode) != 0)//检查节点的分支数是否正确
	{
		return -1;	
	}			
	//检查输出只能在最后一个分支
	//中间分支不应含有输出元件
	NodeLink *pNodeLink = pNode->pNodeLinkSon;
	while(pNodeLink->pNodeLinkRight != NULL)	//一直检查到倒数第二个分支
	{
		if(pNodeLink->pNodeBlew != NULL)//分支为节点
		{
			if(FindOutInNode(pNodeLink->pNodeBlew)==true)
			{
				return -1;	
			}
		}
		else if(pNodeLink->pElementBlew != NULL) //分支为元件
		{
			Element *pElement = pNodeLink->pElementBlew;
			if(pElement->iState != 0 && pElement->iState != 1)
			{
				return -1;	
			}	
		}
		else
		{
			return -1;	
		}	
		pNodeLink = pNodeLink->pNodeLinkRight;
	}//end of while
	//最后一个分支必应含有输出此时pNodeLink为为分支
	if(pNodeLink->pNodeBlew != NULL)
	{
		if(FindOutInNode(pNodeLink->pNodeBlew)==false)
		{
			return -1;	
		}
		else
		{			
			if( CheckNodeOrOut(pNodeLink->pNodeBlew) == -1)
			{
				return -1;	
			}						
		}			
	}
	else if(pNodeLink->pElementBlew != NULL) 
	{
		Element *pElement = pNodeLink->pElementBlew;
		if(pElement->iState == 0 || pElement->iState == 1)//若不是输出类元件
		{
			return -1;	
		}	
	}
	else
	{
		return -1;	
	}	
	return 0;
}
static int CheckNodeOrOut(Node *pNode)
{
	//含有输出元件的or节点，表示多数出分支，其每个分支都要有输出元件
	NodeLink *pNodeLink = pNode->pNodeLinkSon;
	while(pNodeLink != NULL)
	{
		if(pNodeLink->pNodeBlew != NULL)//分支为节点，
		{
			if(FindOutInNode(pNodeLink->pNodeBlew)==false)
			{
				return -1;	
			}
			else
			{
				Node *pNode = pNodeLink->pNodeBlew;
				if( CheckNodeAndOut(pNode) !=0 )
				{
					return -1;	
				}	
			}	
		}
		else if(pNodeLink->pElementBlew != NULL) //分支为元件
		{
			Element *pElement = pNodeLink->pElementBlew;
			if(pElement->iState == 0 || pElement->iState == 1)
			{
				return -1;	
			}	
		}
		else
		{
			return -1;	
		}	
		pNodeLink = pNodeLink->pNodeLinkRight;		
	}//end of while
	return 0;
}
static int CheckNodeLinkNumAndOperate(Node *pNode)
{	
	if( CountNodeLinkNum(pNode) < 2)	//节点的分支不可以少于两个
	{		
		return -1;	
	}		
	NodeLink *pNodeLink = pNode->pNodeLinkSon;
	while(pNodeLink != NULL)
	{
		if(pNodeLink->pNodeBlew != NULL)	//检查节点的每个分支
		{
			Node *pNode2 = pNodeLink->pNodeBlew;
			if(pNode2->iNodeOperate == pNode->iNodeOperate)	
			{
				//上下级的节点类型不可以相同例如and节点不可以直接连接and节点
				return -1;					
			}	
			else if ( CheckNodeLinkNumAndOperate(pNode2) == -1)
			{
				return -1;	
			}				
		}//	if(pNodeLink->pNodeBlew != NULL)	
		pNodeLink=pNodeLink->pNodeLinkRight;
	}//end of while	
	return 0;		
}

