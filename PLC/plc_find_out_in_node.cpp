#include"plc_find_out_in_node.h"

bool FindOutInNode(Node *pNode)
{
	bool bOut = false;
	NodeLink *pNodeLink = pNode->pNodeLinkSon;
	
	//逐分支扫描，直到结束或找到输出元件为止
	while(pNodeLink != NULL)
	{
		if(pNodeLink->pElementBlew != NULL)	//分支为元件
		{
			Element *pElement = pNodeLink->pElementBlew	;
			if(pElement->iState == 2 || pElement->iState == 3 || pElement->iState == 4)
			{
				bOut = true;
				break;	//发现输出元件就返回
			}	
		}	
		else if(pNodeLink->pNodeBlew != NULL) //分支为节点
		{
			bOut = 	FindOutInNode(pNodeLink->pNodeBlew);
			if(bOut == true)
			{
				break;	
			}	
		}	
		pNodeLink = pNodeLink->pNodeLinkRight;		
	}	
	return bOut;
}


