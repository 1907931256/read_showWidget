/*************************
* plc_poise_node.h 
*自上向下!
*添加适当数目的空节点使
* 1,所有的or节点的分支等长
* 2,输出元件在最后的列
* 3,and节点的两个or节点之间添加一个空元件

有时候要调用两次才会完全有效/可能是由于在两个and之间插入一个空元件引起
**************************/
#ifndef POISE_NODE_H
#define POISE_NODE_H

//#include<iostream.h>
#include"plc_structure.h"
#include"plc_insert_element.h"
#include"plc_find_out_in_node.h"
#include"plc_count_nodelink_num.h"

int PoiseNode(Node *pNode);

#endif

