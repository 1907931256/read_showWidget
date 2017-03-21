#include"plc_compile_ladder.h"
#include"sysGlobal.h"
/***************************************
*思想:
*调用到五个函数:
*1,TranslateNodeAndWithoutOut(Node *pNodeAnd)
*  处理不含输出元件的and节点
*2,TranslateNodeOrWithoutOut(Node *pNodeOr)
*  处理不含输出元件的or节点
*3,TranslateNodeAndHoldOut(Node *pNodeAnd)
*  处理含有输出元件的and节点
*4,TranslateNodeOrHoldOut(Node *pNodeOr)
*  处理含有输出元件的Or节点
*5,WriteInstruction(int iOperate, Element *pElement)
*  向指定文件写入翻译好的指令
****************************************/
#define X       0x01
#define Y       0x02
#define M       0x03
#define C       0x04
#define T       0x05

#define LD      0xFF
#define LDI     0xFE
#define AND     0xFD
#define ANI     0xFC
#define OR      0xFB
#define ORI     0xFA

#define SET     0xF7
#define RST     0xF6
#define OUT     0xF2

//以下指令的define与shape_ladder.h中相同，否则会有redefine的问题
#define ANB     0xF900
#define ORB     0xF800
#define MPS     0xF500
#define MRD     0xF400
#define MPP     0xF300
#define NTO     0xF100
#define END     0xF000

//所有函数的返回值
//-1，语法错误
//-2，写入错误
static int TranslateNodeAndWithoutOut(Node *pNodeAnd);
static int TranslateNodeOrWithoutOut(Node *pNodeOr);
static int TranslateNodeAndHoldOut(Node *pNodeAnd,int iM);
static int TranslateNodeOrHoldOut(Node *pNodeOr);
static int WriteInstruction(int iOperate, Element *pElement);
							
FILE *fpPlcCompile=NULL;// = fopen("plc_instruction_temporary.txt","wb");
//unsigned int iInstructionNum = 0;//指令的行数，保存在文件我末尾以便根据文件的长度动态的开辟共享内存
static int TranslateNodeAndWithoutOut(Node *pNodeAnd)
{
	/************************
	*不含输出元件的and节点
	*1首子分支为元件，LD/LDI之
	*2其他
	*分支为or节点，在处理之后加一句anb
	*分支为元件，anb/ani之
	*************************/
	//如果首子分支为元件
	NodeLink *pNodeLinkTmp = pNodeAnd->pNodeLinkSon;
	if(pNodeLinkTmp->pElementBlew != NULL )
	{
		Element *pElementTmp = pNodeLinkTmp->pElementBlew;
		if(pElementTmp->iState == 0 ) 
		{
			int i = WriteInstruction( LD , pElementTmp);
			if(i != 0)
			{
				return i;
			}	
			pNodeLinkTmp =  pNodeLinkTmp->pNodeLinkRight;			
		}
		else if (pElementTmp->iState == 1)
		{
			int i = WriteInstruction(LDI , pElementTmp);
			if(i != 0)
			{
				return i;
			}	
			pNodeLinkTmp =  pNodeLinkTmp->pNodeLinkRight;		
		}	
	}	
	//其他分支或如果首子分支不为元件
	while(pNodeLinkTmp != NULL)
	{
		if(pNodeLinkTmp->pElementBlew != NULL )
		{
			Element *pElementTmp = pNodeLinkTmp->pElementBlew;
			if(pElementTmp->iState == 0 ) 
			{
				int i = WriteInstruction( AND , pElementTmp);
				if(i != 0)
				{
					return i;
				}	
			}
			else if (pElementTmp->iState == 1)
			{
				int i =	WriteInstruction( ANI, pElementTmp);
				if(i != 0)
				{
					return i;
				}	
			}	
		}
		else if(pNodeLinkTmp->pNodeBlew != NULL) 
		{
			int i = TranslateNodeOrWithoutOut(pNodeLinkTmp->pNodeBlew);
			if(i != 0)
			{
				return i;
			}	
			//在处理完or分支后加一句anb/
			if(pNodeLinkTmp != pNodeAnd->pNodeLinkSon)//第一个or分支(首子分支),后面不加anb
			{
				int i = WriteInstruction( ANB, NULL);
				if(i != 0)
				{
					return i;
				}	
			}	
		}	
		pNodeLinkTmp =  pNodeLinkTmp->pNodeLinkRight;	
	}//end of while (pNodeLinkTmp != NULL)
	return 0;
}

static int TranslateNodeOrWithoutOut(Node *pNodeOr)
{
	/************************
	*不含输出元件的or节点，操作与不含输出分支的and节点类似
	*************************/
	NodeLink *pNodeLinkTmp = pNodeOr->pNodeLinkSon;
	while(pNodeLinkTmp != NULL)
	{
		if(pNodeLinkTmp->pElementBlew != NULL )
		{
			Element *pElementTmp = pNodeLinkTmp->pElementBlew;
			if(pNodeLinkTmp != pNodeOr->pNodeLinkSon)
			{
				if(pElementTmp->iState == 0 ) 
				{
					int i = WriteInstruction( OR , pElementTmp);
					if(i != 0)
					{
						return i;
					}	
				}
				else if (pElementTmp->iState == 1)
				{
					int i = WriteInstruction( ORI , pElementTmp);
					if(i != 0)
					{
						return i;
					}	
				}	
			}//end of if(pNodeLinkTmp != pNodeOr->pNodeLinkSon)
			else
			{
				if(pElementTmp->iState == 0 ) 
				{
					int i = WriteInstruction( LD , pElementTmp);
					if(i != 0)
					{
						return i;
					}	
				}
				else if (pElementTmp->iState == 1)
				{
					int i = WriteInstruction( LDI , pElementTmp);
					if(i != 0)
					{
						return i;
					}	
				}	
			}	//end of if(NodeLinkTmp == pNodeOr->pNodeLinkSon)
				
		}	
		else if(pNodeLinkTmp->pNodeBlew != NULL )
		{
			int i = TranslateNodeAndWithoutOut(pNodeLinkTmp->pNodeBlew);
			if(i != 0)
			{
				return i;
			}	
			if(pNodeLinkTmp != pNodeOr->pNodeLinkSon)
			{
				int i = WriteInstruction( ORB, NULL);
				if(i != 0)
				{
					return i;
				}	
			}	
		}
		pNodeLinkTmp = pNodeLinkTmp->pNodeLinkRight;	
	}//end of while (pNodeLinkTmp != NULL)
	return 0;
}

static int TranslateNodeAndHoldOut(Node *pNodeAnd,int iM)
{
	/************************
	*输出元件的and节点，核心：输出元件一定在最后一个分支上！！
	*1首子分支为非输出元件，ld/ldi之
	*2中间分支为不含输出元件的or节点，在处理之后加一句anb
	* 中间分支为不是输出元件，anb/ani之
	*3尾分之为含有输出元件的or节点或为输出元件
	* else //报错
	*************************/
	NodeLink *pNodeLinkTmp = pNodeAnd->pNodeLinkSon;
	while(pNodeLinkTmp != NULL)	
	{
		if(pNodeLinkTmp->pElementBlew != NULL )		//如果分支为元件
		{
			Element *pElementTmp = pNodeLinkTmp->pElementBlew;
					
			if(pElementTmp->iState ==0)
			{
				if(pNodeLinkTmp==pNodeAnd->pNodeLinkSon && pNodeAnd->pRung != NULL)
				{	
					int i=WriteInstruction(LD, pElementTmp);
					if(i != 0)  
					{
						return i;
					}		
				}
				else
				{
					int i=WriteInstruction(AND, pElementTmp);
					if(i != 0)
					{
						return i;
					}	
				}	
			}	
			else if(pElementTmp->iState ==1)
			{
				if(pNodeLinkTmp==pNodeAnd->pNodeLinkSon && pNodeAnd->pRung != NULL)
				{	
					int i = WriteInstruction(LDI, pElementTmp);
					if(i != 0)
					{
						return i;
					}	
				}
				else
				{
					int i = WriteInstruction(ANI, pElementTmp);
					if(i != 0)
					{
						return i;
					}	
				}		
			}	
			else if(pElementTmp->iState ==2)
			{
				int i = WriteInstruction(OUT, pElementTmp);
				if(i != 0)
				{
					return i;
				}	
			}	
			else if(pElementTmp->iState ==3)
			{
				int i = WriteInstruction(SET, pElementTmp);
				if(i != 0)
				{
					return i;
				}	
			}	
			else if(pElementTmp->iState ==4)
			{
				int i = WriteInstruction(RST, pElementTmp);
				if(i != 0)
				{
					return i;
				}	
			}	
		}	//end of /如果分支为元件
		else if (pNodeLinkTmp->pNodeBlew != NULL )	//如果分支为节点
		{
			if(pNodeLinkTmp->pNodeLinkRight != NULL )//&& FindOutInNode(pNodeLinkTmp->pNodeBlew)==false)	//非最后分支
			{
				int i = TranslateNodeOrWithoutOut(pNodeLinkTmp->pNodeBlew);
				if(i != 0)
				{
					return	i;
				}	
				if(iM == 0)//不是多数出分之的and节点
				{
					if(pNodeLinkTmp != pNodeAnd->pNodeLinkSon)//|| pNodeAnd->pRung == NULL)
					{
						int i = WriteInstruction(ANB, NULL);
						if(i != 0 )
						{
							return i;	
						}	
					}	
				}
				else	if(iM == 1)//多数出分之的and节点`
				{
					int i = WriteInstruction(ANB, NULL);
					if(i != 0 )
					{
						return i;	
					}						
				}					
			}
			else if(pNodeLinkTmp->pNodeLinkRight == NULL )//&& FindOutInNode(pNodeLinkTmp->pNodeBlew)==true)//最后分支
			{
				int i = TranslateNodeOrHoldOut(pNodeLinkTmp->pNodeBlew);
				if( i != 0)
				{
					return i;	
				}					
			}
		}//end of //如果分支为节点	
	pNodeLinkTmp = pNodeLinkTmp->pNodeLinkRight;	
	}//end of while(pNodeLinkTmp != NULL)	
	return 0;
}

static int TranslateNodeOrHoldOut(Node *pNodeOr)
{
	//含有多输出元件的or分支 表示梯级有多数出
	//分支的处理，首子分支前加一句MPS，尾分之前加一句MPP，中间分之前加一句MRD
	NodeLink *pNodeLinkTmp = pNodeOr->pNodeLinkSon;
	while(pNodeLinkTmp != NULL)
	{
		if(pNodeLinkTmp == pNodeOr->pNodeLinkSon)	//首子分支前加一句MPS
		{
			int  i = WriteInstruction( MPS, NULL);
			if(i != 0)
			{
				return i;	
			}	
		}
		else if(pNodeLinkTmp->pNodeLinkRight == NULL)	//尾分之前加一句MPP
		{
			int i = WriteInstruction( MPP, NULL);
			if(i != 0)
			{
				return i;
			}	
		}
		else	//中间分之前加一句MRD
		{
			int i = WriteInstruction( MRD, NULL);
			if(i != 0)
			{
				return i;
			}	
		}
		
		if(pNodeLinkTmp->pElementBlew != NULL)
    {	
			Element *pElementTmp = pNodeLinkTmp->pElementBlew;
			if(pElementTmp->iState == 2)
			{
				int i = WriteInstruction(OUT,pElementTmp);
				if(i != 0)
				{
					return i;
				}	
			}	
			else if(pElementTmp->iState == 3)
			{
				int i = WriteInstruction(SET,pElementTmp);
				if(i != 0)
				{
					return i;
				}	
				
			}	
			else if(pElementTmp->iState == 4)
			{
				int i = WriteInstruction(RST,pElementTmp);
				if(i != 0)
				{
					return i;
				}	
			}	
		}//end of if(pNodeLinkTmp->pElementBlew != NULL)
		else if (pNodeLinkTmp->pNodeBlew != NULL)
		{			
			int i = TranslateNodeAndHoldOut(pNodeLinkTmp->pNodeBlew,1);			
			if(i != 0)
			{
				return i;
			}				
		}//END OF if(pNodeLinkTmp->pElementBlew != NULL)
		pNodeLinkTmp = pNodeLinkTmp->pNodeLinkRight;
	}	//end of while(pNodeLinkTmp != NULL)
	return 0;
}

static int WriteInstruction(int iOperate, Element *pElement)
{
	//向文件中写入指令
	unsigned int iInstruction = 0;
	if(fpPlcCompile == NULL)//防止只写进去一条指令，如果尚未赋值，表示第一次调用，
	{
//        fpPlcCompile = fopen("E:/new_project/ShowWidget2/data_sourece/plc_instruction_original.txt","wb+");//写入出厂设置

        char cFileName[]="/plc_instruction_running.txt";
        QByteArray file1=relativePath.toUtf8();
        char* fileOne=file1.data();
        char first[100];
        strncpy(first,fileOne,99);
        strcat(first,cFileName);
        fpPlcCompile = fopen(first,"wb+");
	}			
	if( fpPlcCompile == NULL)
	{		
		return -2;
	}		
	if(pElement != NULL)
	{			
		//元件类型	
		unsigned int iName = 0;
		if(pElement->cName == QString("X"))
		{
			iName = X;	
		}
		else if	(pElement->cName == QString("Y"))
		{
			iName = Y;
		}
		else if	(pElement->cName == QString("M"))
		{
			iName = M;
		}
		else if	(pElement->cName == QString("C"))
		{
			iName = C;
		}
		else if	(pElement->cName == QString("T"))
		{
			iName = T;
		}
		//元件编号
		unsigned int iNum = pElement->iNum;	
		//操作码先左移8位于元件类型相或然后一起左移16位再于元件编号相或/得到指令内部码
		iInstruction = ( ((iOperate<<8)|iName)<<16 )|iNum;
		if( fwrite(&iInstruction,sizeof(unsigned int),1,fpPlcCompile) != 1)
		{			
			return -2;	
		}	
		else		
		{			
			//iInstructionNum	++;	//指令条数加一
		}				
		if(iOperate == OUT && (iName == C || iName == T ))
		{
			iInstruction = pElement->iPara;	
			if( fwrite(&iInstruction,sizeof(unsigned int),1,fpPlcCompile) != 1)//写入定时器计数器的参数
			{									
				return -2;	
			}	
			else			
			{
				//iInstructionNum++;	
			}	
			
		}	
	}	
	else	//元件为空，说明指令为不含操作元件，例如 NTO,END,ANB等
	{
		iInstruction = iOperate<<16;		
		if( fwrite(&iInstruction,sizeof(unsigned int),1,fpPlcCompile) != 1)
		{			
			return -2;	
		}		
		else
		{		
			//iInstructionNum++;				
		}	
		if(iOperate == END) //梯级的指令已经保存完毕，写入指令的长度
		{						
			fclose(fpPlcCompile);
			fpPlcCompile = NULL;			
		}		
	}	//end of if(pElement==NULL)
	return 0;
}

int CompileLadder(Rung *pRungHead)
{	
	Rung *pRungTmp = pRungHead;
	if(pRungTmp == NULL)
	{		
		return -1;
	}	
	//如果头指针不为空,处理各梯级
	Node *pNodeRoot = NULL;
	while(pRungTmp != NULL)
	{
		pNodeRoot = pRungTmp->pNodeRoot;
		if(pNodeRoot != NULL && FindOutInNode(pNodeRoot) == true)//如果根节点不为空且含有输出元件
		{
			//RebuildNode(pNodeRoot);	//此句调试时用;
			int i = TranslateNodeAndHoldOut(pNodeRoot,0);
			if(i != 0)
			{
				return i;
			}	
			//取消这条指令AK2008-3-31 10:16上午
			/*
			i = WriteInstruction(NTO,NULL);
			if(i != 0)
			{
				return i;
			}	
			*/
		}
		else
		{
			return -1;
		}	
		pRungTmp = pRungTmp->pNextRung;
	}	//end of while
	int i = WriteInstruction(END,NULL);	
	if(i != 0)
	{
		return i;
	}	
	return 0;
}
