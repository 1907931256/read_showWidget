#include"plc_delete_element_node.h"

void DeleteElementWithInNode(Element *pElement)	//只是把元件删掉不修改节点的行列数
{
	//与要删除的元件有关系的链节
	NodeLink *pNodeLinkCur = pElement->pElementFather;	//向元件的链节
	Node *pNodeCur = pNodeLinkCur->pNodeLinkFather;	//当前节点
	NodeLink *pNodeLinkLeft = pNodeLinkCur->pNodeLinkLeft;	//当前链节的左链节
	NodeLink *pNodeLinkRight = pNodeLinkCur->pNodeLinkRight;	//当前链节的右链节
	
	//先处理链节的前后关系
	if(pNodeLinkCur == pNodeCur->pNodeLinkSon) //当前元件为首子分支
	{
		pNodeCur->pNodeLinkSon = pNodeLinkRight;	//置右链节为首子分支
		if(pNodeLinkRight != NULL)	//如果右链节为空则节点为空节点
		{	
			pNodeLinkRight->pNodeLinkLeft = NULL;
		}
	}	
	else if(pNodeLinkRight == NULL)	//当前元件为尾子分支
	{
		pNodeLinkLeft->pNodeLinkRight = NULL;	
	}
	else	//当前元件不为首尾子分支
	{
		pNodeLinkLeft->pNodeLinkRight = pNodeLinkRight;
		pNodeLinkRight->pNodeLinkLeft = pNodeLinkLeft; 
	}
	//释放空间
	delete pElement;
	pElement = NULL;	//这样没有用的，不会改变原来的值
	delete pNodeLinkCur;
	pNodeLinkCur = NULL;
}//end of void DeleteElementWithInNode

void DeleteNodeWithInNode(Node *pNode)
{			
	if(pNode->pNodeFather == NULL)//pNode为根节点/	很罕见的情况基本上用不到
	{	
		pNode->pRung->pNodeRoot = NULL;	//将梯级清空
		ReleaseNode(pNode);					
	}
	else
	{
		//pNode不为根节点逐个释放分支	
		NodeLink *pNodeLinkCur = pNode->pNodeFather;	//当前链节	
		Node *pNodeCur = pNodeLinkCur->pNodeLinkFather;	//当前节点	
		NodeLink *pNodeLinkLeft = pNodeLinkCur->pNodeLinkLeft;	//当前链节的左链节	
		NodeLink *pNodeLinkRight = pNodeLinkCur->pNodeLinkRight;	//当前链节的右链节
		
		if(pNodeLinkCur == pNodeCur->pNodeLinkSon) //当前节点为首子分支
		{			
			pNodeCur->pNodeLinkSon = pNodeLinkRight;//右链节为首子分支
			if(pNodeLinkRight != NULL)	//如果右链节不为空则右链节为首子分支，为空则节点为空节点
			{	
				pNodeLinkRight->pNodeLinkLeft = NULL;
			}
		}	
		else if(pNodeLinkRight == NULL)	//当前节点为尾子分支
		{		
			pNodeLinkLeft->pNodeLinkRight = NULL;	
		}
		else	//当前节点不为首尾子分支
		{
			pNodeLinkLeft->pNodeLinkRight = pNodeLinkRight;	
			pNodeLinkRight->pNodeLinkLeft = pNodeLinkLeft; 	
		}
		ReleaseNode(pNode);	//释放空间/不包括指向节点的链节
		//pNode = NULL;		//这样没有用的，不会改变原来的值
		delete pNodeLinkCur;		
		pNodeLinkCur = NULL;
	}//end of 不为根节点
}
