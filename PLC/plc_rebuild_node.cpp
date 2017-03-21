/*plc_rebuild_node.cpp*/
#include"plc_rebuild_node.h"

void DeleteAllNullElement(Node *pNode)//删除当前梯级的所有空元件
{
	NodeLink *pNodeLink = pNode->pNodeLinkSon;
	NodeLink *pNodeLinkRight;
	while(pNodeLink != NULL)	
	{
		pNodeLinkRight = pNodeLink->pNodeLinkRight;	//当前分支的右分支
		
		if( pNodeLink->pElementBlew != NULL && pNodeLink->pElementBlew->cName == QString("N"))		//当分支为元件
		{
			DeleteElementWithInNode(pNodeLink->pElementBlew);				
		}	
		else if(pNodeLink->pNodeBlew != NULL)		//当分支为节点
		{	
			DeleteAllNullElement( pNodeLink->pNodeBlew );	
		}	
		pNodeLink = pNodeLinkRight;
	}//end of while(pNodeLink != NULL)	
}//end of void DeleteAllNullElement

void DeleteAllNullElementE100(Node *pNode)//删除当前梯级的所有除了iPare==100的空元件/插入分支时用
{
	NodeLink *pNodeLink = pNode->pNodeLinkSon;
	NodeLink *pNodeLinkRight;
	while(pNodeLink != NULL)	
	{
		pNodeLinkRight = pNodeLink->pNodeLinkRight;	//当前分支的右分支
		
		if( pNodeLink->pElementBlew != NULL && pNodeLink->pElementBlew->cName == QString("N") && pNodeLink->pElementBlew->iPara != 100 )		//当分支为元件
		{
			DeleteElementWithInNode(pNodeLink->pElementBlew);				
		}	
		else if(pNodeLink->pNodeBlew != NULL)		//当分支为节点
		{	
			DeleteAllNullElementE100( pNodeLink->pNodeBlew );	
		}	
		pNodeLink = pNodeLinkRight;
	}//end of while(pNodeLink != NULL)	
}//end of void DeleteAllNullElement

void DeleteNullNode(Node *pNode)  		//删除pNode中所有的空节点
{
	if(pNode->pNodeFather == NULL && CountNodeLinkNum(pNode) == 0)//根节点,如果为空节点
	{	
			//插入一个 空元件，剩下的交给PoiseNode处理
			Element *pElementInsert=new Element(QString("N"),0,0,0);
			NodeLink *pNodeLinkI = new NodeLink;
			pNode->pNodeLinkSon = pNodeLinkI;
			pNodeLinkI->pElementBlew = pElementInsert;
			pNodeLinkI->pNodeBlew = NULL;
			pNodeLinkI->pNodeLinkLeft = NULL;
			pNodeLinkI->pNodeLinkRight = NULL;
			pNodeLinkI->pNodeLinkFather = pNode;
			pElementInsert->pElementFather = pNodeLinkI;	
			return;
	}		
	NodeLink *pNodeLink = pNode->pNodeLinkSon;
	while(pNodeLink != NULL)
	{
		if(pNodeLink->pNodeBlew != NULL)
		{
			Node *pNodeTmp = pNodeLink->pNodeBlew;	//下一级链节
			if(CountNodeLinkNum(pNodeTmp)==0) //删的就是它，空节点
			{
				NodeLink *pNodeLinkRight = pNodeLink->pNodeLinkRight;	
							
				//删除节点，包括指向空节点的链节
				DeleteNodeWithInNode(pNodeTmp);									
				//此时 pNodeLink指向的空间已被删除！
				pNodeLink = pNodeLinkRight;	
				continue;	//跳过后面部分，继续下一次循环
			}
			else
			{
				DeleteNullNode(pNodeTmp); //继续深入删除空节点
			}		
		}	
		else if(pNodeLink->pElementBlew == NULL) //如果一个链节的向下指针都为空,说明此链节没有被释放!
		{
			cout<<"erroer in ---DeleteNullNode-- :unreleased Nodelink "<<pNodeLink<<endl;	
			return;
		}
		pNodeLink = pNodeLink->pNodeLinkRight;
	}//end of while
}//end of void DeleteNullNode

//######################################################################################
int RestructureNode(Node *pNodeM)
{
	/******************************************************************
	* 1,没有分支，报错 
	* 2,有多个分支，处理每个子节点分支
	* 3,只有一个分支
	*		A,不为根节点，
	*			a,分支为元件，不处理/"将元件取代pNodeM的位置	"
	*			b,分支为节点，
	*				将节点分支pNodeS拆开的所有分支插入pNodeF,
	*				RestructureNode(Node *pNodeM) /可能会有很多的重复判断
	*
	*		B,如果为根节点，
	*			a,分支为元件,不处理
	*			b,分支为不含输出元件的or节点,RestructureNode() or节点
	*			b,分支为含有输出元件的or节点,将or的每个子分支当作新的梯级,
	*				ReBuild每个梯级的根节点!	
	********************************************************************/
	if(CountNodeLinkNum(pNodeM) == 0)	//1,没有分支，报错
	{
		cout<<"in RestructureNode CountNodeLinkNum( "<<pNodeM<<" ) == 0"<<endl;		
		return -1;
	}	
	else if( CountNodeLinkNum(pNodeM) >1) //2，有多个分支，处理每个子节点分支 
	{
		NodeLink *pNodeLink = pNodeM->pNodeLinkSon;
		while(pNodeLink != NULL)	
		{
			if(pNodeLink->pNodeBlew != NULL)	
			{				
				RestructureNode( pNodeLink->pNodeBlew );	
			}				
			pNodeLink = pNodeLink->pNodeLinkRight;	
		}//end of while(pNodeLink != NULL)
	}	
	else if(CountNodeLinkNum(pNodeM) == 1 )	//3，只有一个分支
	{				
		if(pNodeM->pNodeFather != NULL)	//B，不为根节点，
		{
			NodeLink *pNodeLinkF = pNodeM->pNodeFather;
			Node *pNodeF = pNodeLinkF->pNodeLinkFather;				
			NodeLink *pNodeLinkM = pNodeM->pNodeLinkSon;
			if(pNodeLinkM->pElementBlew != NULL )// && pNodeM->iNodeOperate == 2) //a，分支为元件，且节点pNodeM为or节点将元件取代pNodeM的位置	
			{				
				Element *pElementS = pNodeLinkM->pElementBlew;
				pNodeLinkF->pNodeBlew = NULL;
				pNodeLinkF->pElementBlew = pElementS;
				pElementS->pElementFather = pNodeLinkF;
				
				delete pNodeM;
				pNodeM = NULL;
				delete pNodeLinkM;
				pNodeLinkM = NULL; 			
			}//end of if(pNodeLinkM->pElement != NULL)						
			else if(pNodeLinkM->pNodeBlew != NULL)	//b，分支为节点，
			{				
				//pNodeLinkF的邻居
				NodeLink *pNodeLinkRightF = pNodeLinkF->pNodeLinkRight;
				NodeLink *pNodeLinkLeftF = pNodeLinkF->pNodeLinkLeft;
				
				Node *pNodeS = pNodeLinkM->pNodeBlew;
				NodeLink *pNodeLinkS = pNodeS->pNodeLinkSon;	//pNodeS的首子分支
				
				//将pNodeS的所有分支指向pNodeM,并找到 pNodeS 的最后一个分支
				NodeLink *pNodeLinkLastS = pNodeLinkS;
				while(pNodeLinkLastS->pNodeLinkRight != NULL)
				{
					pNodeLinkLastS->pNodeLinkFather = pNodeF;//将pNodeS的所有分支指向pNodeM
					pNodeLinkLastS = pNodeLinkLastS->pNodeLinkRight;				
				}
				pNodeLinkLastS->pNodeLinkFather = pNodeF;//将pNodeS的最后一分支指向pNodeM
								
				//此时 pNodeLinkLastS 为pNodeS的最后一个分支 pNodeS的所有分支的父节点以指向pNodeF
				
				//将pNodeS的分支融入到pNodeF中
				if(pNodeLinkF == pNodeF->pNodeLinkSon)	//如果pNodeM为pNodeF的首子分支节点
				{						
					pNodeLinkLastS->pNodeLinkRight = pNodeLinkRightF;
					if(pNodeLinkRightF != NULL)	//这个判断有些多余，此时的pNodeF 必定不是单分支
					{
						pNodeLinkRightF->pNodeLinkLeft = pNodeLinkLastS;
					}	
					pNodeF->pNodeLinkSon = pNodeLinkS;
																		
				}	//end of if(pNodeLinkF == pNodeF->pNodeLinkSon)
				else if(pNodeLinkF->pNodeLinkRight == NULL)	//pNodeM为pNodeF的尾子分支节点
				{		
					pNodeLinkLastS->pNodeLinkRight = NULL;
					pNodeLinkS->pNodeLinkLeft = pNodeLinkLeftF;
					if(pNodeLinkLeftF != NULL ) //这个判断更多余
					{
						pNodeLinkLeftF->pNodeLinkRight = pNodeLinkS;
					}
				}//end of else if(pNodeLinkF->pNodeLinkRight == NULL)
				else	//pNodeM为pNodeF的 非 首尾子分支节点
				{					
					//注意指令的顺序!!!
					pNodeLinkLastS->pNodeLinkRight = pNodeLinkRightF;
					pNodeLinkRightF->pNodeLinkLeft = pNodeLinkLastS;
					pNodeLinkS->pNodeLinkLeft = pNodeLinkLeftF;	
					pNodeLinkLeftF->pNodeLinkRight = pNodeLinkS;						
				}	
				
				//释放多余的对象
				delete pNodeLinkF;
				pNodeLinkF = NULL;						
				delete pNodeLinkM;
				pNodeLinkM= NULL;
				delete pNodeS;
				pNodeS= NULL;		
				
				//pNodeS的分支是没有 Restructure 同样可能有(只有一个分支的)的节点
				RestructureNode(pNodeF);  //关键点！/重新构造父节点**************									
				//ResizeNode(pNodeF);
			}	//end of else if(pNodeLinkM->pNodeBlew != NULL)				
		}	//end of if(pNodeM->pNodeFather != NULL)	
		else //A，如果为根节点
		{
			NodeLink *pNodeLinkM = pNodeM->pNodeLinkSon;
			if(pNodeLinkM->pNodeBlew != NULL)	
			{	
				Node *pNodeS = 	pNodeLinkM->pNodeBlew;	
				if( FindOutInNode(pNodeS) == false ) //b,分支为不含输出元件的or节点,
				{					
					RestructureNode(pNodeS);
					//ResizeNode(pNodeS);
				}	
				else	//分支为含有输出元件的or节点,
				{
					//*****将or的每个子分支当作新的梯级,	/ReBuild每个梯级的根节点!	
					NodeLink *pNodeLinkS = pNodeS->pNodeLinkSon ;					
					Rung *pRungLast = pNodeM->pRung;	//用来记录节点中的最后一个分支!	
					while(pNodeLinkS != NULL)
					{
						//NodeLink *pNodeLinkRightS = pNodeLinkS->pNodeLinkRight;
						Rung *pRungInsert = new Rung;
						//pRungLast = pRungInsert;
						if(pNodeLinkS->pNodeBlew != NULL)	//如果分支为节点,必为and节点,就是新梯级的根节点
						{
							Node *pNodeTmp = pNodeLinkS->pNodeBlew;
							pRungInsert->pNodeRoot = pNodeTmp;
							pNodeTmp->pRung = pRungInsert;	
							pNodeTmp->pNodeFather = NULL;	// !!!!!
							pRungInsert->iRungRow = pNodeTmp->iNodeRow;	
						}	
						else if(pNodeLinkS->pElementBlew != NULL)	//分支为元件
						{				
							Node *pNodeTmp = new Node(1);//新建一个and节点
							pNodeTmp->AppendLink(pNodeLinkS->pElementBlew);
							pRungInsert->pNodeRoot = pNodeTmp;
							pNodeTmp->pRung = pRungInsert;	
							pNodeTmp->pNodeFather = NULL;	// !!!!!
							pRungInsert->iRungRow = pNodeTmp->iNodeRow;		
						}						
						//将新建的pRungInsert插入梯级pRungLast的后面 / 注意语句顺序
						pRungInsert->pPreRung = pRungLast;
						pRungInsert->pNextRung= pRungLast->pNextRung;	
						if(pRungLast->pNextRung != NULL)	
						{
							pRungLast->pNextRung->pPreRung = pRungInsert;
						}		
						pRungLast->pNextRung = pRungInsert;					
												
						//下一次循环
						pRungLast = pRungInsert;	
						pNodeLinkS = pNodeLinkS->pNodeLinkRight;							
					}//end of while(pNodeLinkS != NULL)
					
					//重新构建新建的这几个分支 /
					Rung *pRungTmp = pNodeM->pRung->pNextRung;
					
					do//这样写防止or节点只有一个分支
					{
						Node *pNode = pRungTmp->pNodeRoot;
						RebuildNode(pNode);	
						ResizeNode(pNode);	
						pNode = pRungTmp->pNodeRoot;
						pNode->iNodeColumn = 13;
						PoiseNode(pNode);				
						pRungTmp = pRungTmp->pNextRung;						
					}
					while(pRungTmp != pRungLast);
					
					RebuildNode(pRungTmp->pNodeRoot);	
					ResizeNode(pRungTmp->pNodeRoot);
					pRungTmp->pNodeRoot->iNodeColumn = 13;						
					PoiseNode(pRungTmp->pNodeRoot);
					//将pNodeM的梯级 链节,or节点释放
					
					//释放pNodeM的梯链 /这样写是为了防止 pNodeM的梯链为整个梯的头指针
					Rung *pRungCur = pNodeM->pRung;
					Rung *pRungTmp2 = pRungCur->pNextRung;	//"头节点"后面的链节					
					pRungCur->pNodeRoot = pRungTmp2->pNodeRoot;//将pRungTmp2的根节点给pNodeCur				
					pRungTmp2->pNodeRoot->pRung = pRungCur;
					pRungTmp2->pNodeRoot->pNodeFather  = NULL;
					pRungCur->iRungRow = pRungTmp2->iRungRow;
					//将pRungTmp2从梯链中摘下，释放
					pRungCur->pNextRung = pRungTmp2->pNextRung;
					if(pRungTmp2->pNextRung != NULL)
					{
						pRungTmp2->pNextRung->pPreRung = pRungCur;
					}	
					delete pRungTmp2;
					pRungTmp2 = NULL;
					
					//释放原pNodeCur中
					pNodeLinkS = pNodeS->pNodeLinkSon;
					NodeLink *pNodeLinkRight;
					while(pNodeLinkS != NULL)
					{
						pNodeLinkRight = pNodeLinkS->pNodeLinkRight;
						delete pNodeLinkS;						
						pNodeLinkS = pNodeLinkRight;
					}					
					delete pNodeS;
					pNodeS = NULL;					
					delete pNodeLinkM;
					pNodeLinkM = NULL;					
					delete pNodeM;
					pNodeM = NULL;	
				}// end of else	//分支为含有输出元件的or节点,	
				
			}//end of if(pNodeLinkM->pNodeBlew != NULL)
			else //a,分支为元件,不处理
			{
				//do nothing	
			}//end of	else (pNodeLinkM->pNodeBlew != NULL)	
		}//end of else //A，如果为根节点		
			
	}//end of else if(CountNodeLinkNum(pNodeM) == 1 )	//3，只有一个分支	
	return 0;
}	

void ResizeNode(Node *pNode)	//计算节点的行列数（自上向下）
{
	int iNodeRowNew = 0;
	int iNodeColumnNew = 0;	
	NodeLink *pNodeLinkCur = pNode->pNodeLinkSon;
	if(pNode->iNodeOperate == 1)	//若为and节点 
	{
		while(pNodeLinkCur != NULL)
		{
			if(pNodeLinkCur->pElementBlew != NULL) 
			{
				iNodeColumnNew++; //列数加一，行数不变	
			}
			else if(pNodeLinkCur->pNodeBlew != NULL)
			{
				Node *pNodeBlew = pNodeLinkCur->pNodeBlew;
				ResizeNode(pNodeBlew);
				iNodeRowNew = iNodeRowNew>(pNodeBlew->iNodeRow) ?  iNodeRowNew : (pNodeBlew->iNodeRow);
																				//行数取所有节点的行数的最大值
				iNodeColumnNew += pNodeBlew->iNodeColumn;	//列数为所有子节点的列数的和	
				//两个连续的or节点之间加一个空元件，这里先把空元件的位置给留下来
				if( pNodeLinkCur->pNodeLinkLeft != NULL 
					&&pNodeLinkCur->pNodeLinkLeft->pNodeBlew != NULL 
					&&pNodeLinkCur->pNodeLinkLeft->pNodeBlew->iNodeOperate == 2)
				{
					iNodeColumnNew ++;	
				}	
			}			
			pNodeLinkCur = pNodeLinkCur->pNodeLinkRight;	
		}//end ofwhile(pNodeLinkCur != NULL)			
	}	//end of if(pNodeLinkCur->iNodeOperate == 1)
	else if(pNode->iNodeOperate == 2)	//若为or节点
	{
		while(pNodeLinkCur != NULL)
		{
			if(pNodeLinkCur->pElementBlew != NULL) 
			{
				iNodeRowNew++; //行数加一，列数不变	
			}
			else if(pNodeLinkCur->pNodeBlew != NULL)
			{
				Node *pNodeBlew = pNodeLinkCur->pNodeBlew;				
				ResizeNode(pNodeBlew);
				iNodeRowNew += pNodeBlew->iNodeRow;	//行数取所有节点的行数的和
				iNodeColumnNew = iNodeColumnNew>(pNodeBlew->iNodeColumn)? iNodeColumnNew : (pNodeBlew->iNodeColumn);	
																	//列数为所有子节点的列数的最大值
			}			
			pNodeLinkCur = pNodeLinkCur->pNodeLinkRight;			
		}//end of while(pNodeLinkCur != NULL)
	}//end ofelse if(pNodeLinkCur->iNodeOperate == 2)	//若为or节点	
	if(iNodeRowNew == 0)
	{
		iNodeRowNew = 1; 	
	}	
	if(iNodeColumnNew == 0)
	{
		iNodeColumnNew = 1;	
	}	
	pNode->iNodeRow = iNodeRowNew;	
	pNode->iNodeColumn = iNodeColumnNew;	
	
	//如果是根节点改变梯级的行列数
	if(pNode->pRung != NULL)
	{
		pNode->pRung->iRungRow = pNode->iNodeRow;	
	}	
}

void RebuildNode(Node *pNode)
{	
	Node *pNodeTmp = pNode;
	Rung *pRungTmp = NULL;
	if(pNode->pRung != NULL)
	{
		pRungTmp = pNode->pRung;	
	}	
	DeleteAllNullElement(pNodeTmp);
	DeleteNullNode(pNodeTmp);
	RestructureNode(pNodeTmp);	
	if(pRungTmp != NULL)
	{
		pNodeTmp = pRungTmp->pNodeRoot;
	}	
	ResizeNode(pNodeTmp);	
}
