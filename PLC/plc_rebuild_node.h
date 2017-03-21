/*****************************
*	plc_rebuild_node.h
*节点的重构
*要解决的问题：
*删除添加元件分支后数形结构被破坏了，不能保证空元件和行列数的正确性
*任务：
*	1，删除当前梯级的所有空元件
*	2，将（没有分支的节点） 删除释放
* 3，将（只剩下一个分支的节点）拆开插入上一级节点
* 4，重新计算节点的行列数（自上向下） 
*此函数的下一步一定是PoiseNode(Node *pNode)
*在下一步就是刷新界面
******************************/
#ifndef REBUILD_NODE_H
#define REBUILD_NODE_H

#include"plc_structure.h"
#include"plc_delete_element_node.h"
#include"plc_count_nodelink_num.h"
//#include"count_node_size.h"
#include"plc_find_out_in_node.h"
#include"plc_poise_node.h"
#include"plc_shape_ladder_test.h"
#include<iostream>
using namespace std;
extern void DeleteAllNullElement(Node *pNode);//删除当前梯级的所有空元件
extern void DeleteAllNullElementE100(Node *pNode);
extern void DeleteNullNode(Node *pNodeF);  		//删除所有的空节点
extern int RestructureNode(Node *pNode);			//将（只剩下一个分支的节点）拆开插入上一级节点
extern void ResizeNode(Node *pNode);	//计算节点的行列数（自上向下） 
extern void RebuildNode(Node *pNode);	//

#endif

