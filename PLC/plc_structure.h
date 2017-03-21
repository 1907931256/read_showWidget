/************
 plc_structure.h  
 
*************/
 
#ifndef STRUCTURE_H
#define STRUCTURE_H
#include<qstring.h>


class Element;
class Node;
class NodeLink;
class Rung;
//定义元件类
class Element
{
public:
	int id;	//判断对象的类型0:Element, 1:NodeLink, 2:Node，3：Rung
	QString cName;	//元件的类型，X Y C M T N(空元件)
	int iNum;	//元件的编号，
	int iState;	//元件初始状态的常开常闭初始状态或输出分支的OUT,SET,RST
							//0:常开，1:常闭，2:OUT,3:SET,4:RST
	int iPara;	//定时器计数器的设定值,其它元件赋值零。	
	NodeLink *pElementFather;//元件的父节点 
	Element(QString cNameTmp, int iNumTmp, int iStateTmp,int iParaTmp);	//构造函数
	~Element();	
};

//定义节点链节，连接父节点和子节点
class NodeLink
{
public:	
	int id;	//判断对象的类型0:Element, 1:NodeLink, 2:Node，3：Rung
	Node *pNodeLinkFather;		//指向链节的父节点
	NodeLink *pNodeLinkLeft;	//指向左链节
	NodeLink *pNodeLinkRight;	//指向右链节
		
	Element *pElementBlew;	//指向链节下面元件
	Node *pNodeBlew;				//指向链节下面操作节点
		
	NodeLink();							
	~NodeLink();
};
//定义节点类
class Node
{
public:		
	int id;		//判断对象的类型0:Element, 1:NodeLink, 2:Node，3：Rung
	int iNodeOperate;	//表示节点的操作类型and=1,or=2，NullNode=0(空节点表示空白行画图时用到)
	
  //int iSonNum;//表示子节点的个数；可能用不到。
	int iNodeRow;			//节点的行数 
	int iNodeColumn;	//节点的列数
	   /*表示节点所占用的行列数
	   *若为and节点:列数为所有子节点的列数的和，行数取所有节点的行数的最大值，
		 *若为or节点:列数为所有子节点的列数的最大值，行数取所有节点的行数的和。
	   */
	//int iMark;//下一条指令为MPS=1，MRD=2，MPP=3，其他=0；由指令生成树时用
	   
	NodeLink *pNodeFather;	//指向指向父节点连接的指针 根节点此值为零
	NodeLink *pNodeLinkLast;		//指向最后一个子节点，构造时用。
 	NodeLink *pNodeLinkSon;			//指向第一个子节点	
 	Rung  *pRung;		//根节点指向梯级的指针，非根节点赋值0。 
 	
 	int AppendLink( Element *pElementTmp);//添加子 元件节点
	int AppendLink( Node *pNodeTmp);	//添加子 操作节点
	
 	Node(int iNodeOperateIn); 		
 	~Node();
};
//定义梯级类
class Rung
{
public:
	int id;	//判断对象的类型0:Element, 1:NodeLink, 2:Node，3：Rung
	int iRungRow;	//梯级的总行数 空梯级为一
	int iRungRowNum;	//梯级在整个梯型结构的行数
	Node *pNodeRoot;	//指向梯级的根节点
	Rung *pNextRung;//指向后一梯级
	Rung *pPreRung;	//指向前一梯级
		
	Rung();
	~Rung();
};

#endif

