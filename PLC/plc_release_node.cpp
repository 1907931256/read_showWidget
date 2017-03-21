/*release_node.cpp*/
//释放节点的内存，用在删除节点后

#include"plc_release_node.h"
#include<iostream>//调试时用
using namespace std;
void ReleaseNode(Node *pNode)
{
	NodeLink *pNodeLink = pNode->pNodeLinkSon;	
	//释放所有分支
	while(pNodeLink != NULL)	
	{
		if(pNodeLink->pElementBlew != NULL)		//当分支为元件
		{
			Element *pElement = pNodeLink->pElementBlew;
			delete pElement;
			pElement = NULL;
		}	
		else if(pNodeLink->pNodeBlew != NULL)		//当分支为节点
		{			
			ReleaseNode( pNodeLink->pNodeBlew );				//递归的最底层是删除元件，删除链接
		}	
		pNodeLink = pNodeLink->pNodeLinkRight;
	}//end of while(pNodeLink != NULL)
	
	//释放节点的向下分支链节
	pNodeLink = pNode->pNodeLinkSon;	
	NodeLink *pNodeLinkRight;
	while(pNodeLink != NULL)	
	{
		pNodeLinkRight = pNodeLink->pNodeLinkRight;	
		delete pNodeLink;
		pNodeLink = NULL;
		pNodeLink = pNodeLinkRight;		
	}//end of while(pNodeLink != NULL)
	
	//释放节点
	delete pNode;
	pNode = NULL;
	
}//end of function

