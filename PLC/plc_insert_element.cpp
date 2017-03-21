#include"plc_insert_element.h"
//在pElementCur前插入元件pElementInsert
int InsertElementWithInNode(Element *pElementCur, Element *pElementInsert)
{
	NodeLink *pNodeLinkCur = pElementCur->pElementFather;//当前链节
	Node *pNodeCur = pNodeLinkCur->pNodeLinkFather;			//当前节点	
	
	if(pNodeCur->iNodeOperate == 1)	//若当前节点为and节点
	{
		//建立一个链节,将插入节点连节上
		NodeLink *pNodeLinkInsert = new NodeLink;
		pElementInsert->pElementFather = pNodeLinkInsert;
		pNodeLinkInsert->pElementBlew = pElementInsert;		
		pNodeLinkInsert->pNodeBlew = NULL;		
		pNodeLinkInsert->pNodeLinkFather = pNodeCur;
		
		if(pNodeLinkCur==pNodeCur->pNodeLinkSon) //若当前链节为父节点的首链节
		{
			pNodeCur->pNodeLinkSon=pNodeLinkInsert;	//新建的链节为首链节			
			pNodeLinkInsert->pNodeLinkLeft = NULL;	//新建的链节与左右相连接
			pNodeLinkInsert->pNodeLinkRight= pNodeLinkCur;	
			pNodeLinkCur->pNodeLinkLeft = pNodeLinkInsert;
			
		}//end of	if(pNodeLinkCur==1)
		else
		{	
			pNodeLinkInsert->pNodeLinkLeft = pNodeLinkCur->pNodeLinkLeft;
			pNodeLinkInsert->pNodeLinkRight = pNodeLinkCur;		
			pNodeLinkCur->pNodeLinkLeft->pNodeLinkRight = pNodeLinkInsert;
			pNodeLinkCur->pNodeLinkLeft = pNodeLinkInsert;	
		
		}	//end of	else (pNodeLinkCur		
	}	//end of if(pNodeCur->iNodeOperate==1)
	else if(pNodeCur->iNodeOperate==2)	//若当前节点为or节点	
	{
		//新建一and节点,将pElementInsert和pElementCur添加上
		Node *pNodeNew = new Node(1); 
		pNodeNew->AppendLink(pElementInsert);
		pNodeNew->AppendLink(pElementCur);
				
		//将新建的节点取代当前元件的位置
		pNodeNew->pNodeFather = pNodeLinkCur;
		pNodeLinkCur->pElementBlew = NULL;
		pNodeLinkCur->pNodeBlew = pNodeNew;					
	}	
	else
	{
		return -1;	
	}	
	return 0;
}

//在pElementCur后插入元件pElementInsert
int InsertElementWithInNodeBack(Element *pElementCur, Element *pElementInsert)
{
	NodeLink *pNodeLinkCur = pElementCur->pElementFather;//当前链节
	Node *pNodeCur = pNodeLinkCur->pNodeLinkFather;			//当前节点	

	if(pNodeCur->iNodeOperate == 1)	//若当前节点为and节点
	{
		//建立一个链节,将插入节点连节上
		NodeLink *pNodeLinkInsert = new NodeLink;
		pNodeLinkInsert->pElementBlew = pElementInsert;
		pElementInsert->pElementFather = pNodeLinkInsert;
		pNodeLinkInsert->pNodeBlew = NULL;
		pNodeLinkInsert->pNodeLinkFather = pNodeCur;
		
		if(pNodeLinkCur->pNodeLinkRight == NULL) //若当前链节为父节点的尾链节
		{			
			pNodeLinkInsert->pNodeLinkLeft = pNodeLinkCur;
			pNodeLinkCur->pNodeLinkRight = pNodeLinkInsert;	
			pNodeLinkInsert->pNodeLinkRight=NULL;
		}//end of	if(pNodeLinkCur==1)
		else
		{				
			pNodeLinkInsert->pNodeLinkLeft = pNodeLinkCur;
			pNodeLinkInsert->pNodeLinkRight = pNodeLinkCur->pNodeLinkRight;
			pNodeLinkCur->pNodeLinkRight->pNodeLinkLeft = pNodeLinkInsert;
			pNodeLinkCur->pNodeLinkRight = pNodeLinkInsert;	
		}	//end of	else (pNodeLinkCur		
	}	//end of if(pNodeCur->iNodeOperate==1)
	else if(pNodeCur->iNodeOperate==2)	//若当前节点为or节点	
	{
		//新建一and节点,将pElementInsert和pElementCur添加上
		Node *pNodeNew = new Node(1); 		
		pNodeNew->AppendLink(pElementCur);
		pNodeNew->AppendLink(pElementInsert);
		//将新建的节点取代当前元件的位置
		pNodeNew->pNodeFather = pNodeLinkCur;
		pNodeLinkCur->pElementBlew = NULL;
		pNodeLinkCur->pNodeBlew = pNodeNew;					
	}	
	else
	{
		return -1;	
	}	
	return 0;
}
