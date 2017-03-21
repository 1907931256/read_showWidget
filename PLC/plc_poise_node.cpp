#include"plc_poise_node.h"

/*调用以前先给pNode->iNodeColumn赋值*/
int PoiseNode(Node *pNode)
{		
	const int iColumnNumTarget = pNode->iNodeColumn;	
	int iColumnNumTmp = 0;
	
	if(pNode->iNodeOperate == 1)	//若为and节点
	{
			
		NodeLink *pNodeLinkCur = pNode->pNodeLinkSon;		
		NodeLink *pNodeLinkRight = pNodeLinkCur->pNodeLinkRight;		
		if(pNode->pRung != NULL 
			&& pNodeLinkCur->pNodeBlew != NULL 
			&& pNodeLinkRight==NULL 
			&& FindOutInNode(pNode) == false )
		{
			Node *pNodeTmp = pNodeLinkCur->pNodeBlew;
			pNode->pNodeLinkLast = pNodeLinkCur;
			for(int i=0; i<13-pNodeTmp->iNodeColumn; i++) 
			{
				Element *pElementInsert = new Element(QString("N"), 0, 0, 0);
				pNode->AppendLink(pElementInsert);					
			}				
		}	
		else if(pNode->pRung != NULL 
			&& pNodeLinkCur == pNode->pNodeLinkSon 
			&& pNodeLinkCur->pElementBlew != NULL 
			&& pNodeLinkRight==NULL)
		{
			//如果根节点只剩下一个元件时：
			Element *pElement = pNodeLinkCur->pElementBlew;
			if(pElement->iState == 2 || pElement->iState == 3 || pElement->iState == 4)
			{
				for(int i=0; i<12; i++) 
				{
					Element *pElementInsert = new Element(QString("N"), 0, 0, 0);
					InsertElementWithInNode(pElement, pElementInsert);			
				}		
			}	
			else
			{
				pNode->pNodeLinkLast = pNodeLinkCur;
				for(int i=0; i<12; i++) 
				{
					Element *pElementInsert = new Element(QString("N"), 0, 0, 0);
					pNode->AppendLink(pElementInsert);					
				}			
			}				
		}	
		
		//在两个连续的OR节点之间插入一个空元件	
		while(pNodeLinkRight != NULL)
		{
			if(pNodeLinkCur->pNodeBlew != NULL && pNodeLinkRight->pNodeBlew !=NULL)
			{   
				Element *pElementInsert = new Element(QString("N"), 0, 0, 0);
				NodeLink *pNodeLinkInsert = new NodeLink;
				
				pNodeLinkInsert->pNodeBlew = NULL;
				pNodeLinkInsert->pElementBlew = pElementInsert;
				pElementInsert->pElementFather = pNodeLinkInsert;
				pNodeLinkInsert->pNodeLinkFather = pNode;
				
				pNodeLinkInsert->pNodeLinkLeft = pNodeLinkCur;				
				pNodeLinkCur->pNodeLinkRight = 	pNodeLinkInsert;
				pNodeLinkInsert->pNodeLinkRight = pNodeLinkRight;
				pNodeLinkRight->pNodeLinkLeft = pNodeLinkInsert;				
			}	
			pNodeLinkCur = pNodeLinkRight;
			pNodeLinkRight = pNodeLinkRight->pNodeLinkRight;	
		}//end of while() 
		
		//处理非尾分支
		pNodeLinkCur = pNode->pNodeLinkSon;
		while(pNodeLinkCur->pNodeLinkRight != NULL)	
		{
			if(pNodeLinkCur->pNodeBlew != NULL) //分支为节点
			{				
				Node *pNodeCur=pNodeLinkCur->pNodeBlew;
				if(pNodeCur->iNodeOperate==2)	//如果分支为or节点
				{
					PoiseNode(pNodeCur);
				}							
				else 
				{
					return -1;	
				}					
				iColumnNumTmp += pNodeCur->iNodeColumn;						
			}
			else if(pNodeLinkCur->pElementBlew != NULL)
			{
				iColumnNumTmp += 1;				
			}
			else
			{
				return -1;	
			}	//end of if(pNodeLinkCur->pNodeBlew )
			pNodeLinkCur=pNodeLinkCur->pNodeLinkRight;				 	
		}	//end of while
		
		//此时为最后分支
		int iColumnNumSupply = iColumnNumTarget - iColumnNumTmp;	//（要插入的列数-1）	
		if(iColumnNumSupply < 1)
		{
			return -1;	
		}			
		if(pNodeLinkCur->pNodeBlew != NULL) //分支为节点
		{
			Node *pNodeCur = pNodeLinkCur->pNodeBlew;
			if(pNodeCur->iNodeOperate==2 )
			{
				pNodeCur->iNodeColumn = iColumnNumSupply;
				PoiseNode(pNodeCur);
			}			
			else
			{
				return -1;	
			}
		}
		else if(pNodeLinkCur->pElementBlew != NULL)
		{			
			if(iColumnNumSupply==1)
			{
				return  0;	
			}
			Element *pElementCur=pNodeLinkCur->pElementBlew;
			if( pElementCur->iState==0 || pElementCur->iState==1 )	
			{
				//非输出类元件,在元件的后面添加空元件
				for(int i=0;i <iColumnNumSupply-1; i++)
				{
					Element *pElementInsert=new Element(QString("N"), 0,0,0);
					NodeLink *pNodeLink2 = pNode->pNodeLinkSon;
					
					//找到最后一个分支
					while(pNodeLink2->pNodeLinkRight != NULL)
					{
						pNodeLink2 = pNodeLink2->pNodeLinkRight;
					}
					pNode->pNodeLinkLast = pNodeLink2;
					pNode->AppendLink(pElementInsert);
				}
				return 0;			
			}
			else if( pElementCur->iState==2 || pElementCur->iState==3 || pElementCur->iState==4)	//输出类元件
			{	
				//在输出元件前面插入空元件使输出元件
				for(int i=0; i<iColumnNumSupply-1; i++)
				{					
					Element *pElementInsert=new Element(QString("N"),0,0,0);
					InsertElementWithInNode(pElementCur, pElementInsert);
				}	
				return 0;		
			}
			else
			{
				return -1;	
			}					
		}
		else
		{
			return -1;
		}	
	}	//end of if(iNodeOperate==1)
	else if(pNode->iNodeOperate == 2)	//若为or节点,把所有的分支拉成要求的长度	
	{
		NodeLink *pNodeLinkCur = pNode->pNodeLinkSon;	
		while(pNodeLinkCur != NULL)	//处理分支
		{			
			if(pNodeLinkCur->pNodeBlew != NULL)
			{
				Node *pNodeCur = pNodeLinkCur->pNodeBlew;
				if(pNodeCur->iNodeOperate==1)	//如果分支为and节点
				{
					pNodeCur->iNodeColumn = iColumnNumTarget;
					PoiseNode(pNodeCur);
				}				
				else
				{ 
					return -1;	
				}										
			}
			else if(pNodeLinkCur->pElementBlew != NULL)
			{				
				if(iColumnNumTarget == 1)
				{
					break;
				}	
				/**************************************
				*1，新建一个and节点，将元件插入，
				*	2，用and节点取代元件的位置
				*	3，把and节点的列数改为or节点的列数
				*	4，处理and节点
				***************************************/							
				Node *pNodeTmp = new Node(1);					
				pNodeTmp->AppendLink(pNodeLinkCur->pElementBlew);								
				pNodeLinkCur->pElementBlew = NULL;
				pNodeLinkCur->pNodeBlew = pNodeTmp;
				pNodeTmp->pNodeFather = pNodeLinkCur;
				pNodeTmp->iNodeColumn = iColumnNumTarget;
				PoiseNode(pNodeTmp);		
			}
			else
			{
				return -1;	
			}		
			pNodeLinkCur = pNodeLinkCur->pNodeLinkRight; 			
		}	
	}
	else
	{
		return -1;	
	}	
	return -1;	
}

