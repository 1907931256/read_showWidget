#include"plc_count_nodelink_num.h"

int CountNodeLinkNum(Node *pNode)
{
	int iNodeLinkNum = 0;
	NodeLink *pNodeLinkCur = pNode->pNodeLinkSon;
	while(pNodeLinkCur != NULL)
	{
		iNodeLinkNum++;
		pNodeLinkCur = pNodeLinkCur->pNodeLinkRight;	
	}	
	return iNodeLinkNum;
}
