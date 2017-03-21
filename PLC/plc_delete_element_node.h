/********************************
*	plc_delete_element_node.h
*只是删除元件或节点
*     及指向他们的链节
*     不修改行列数
*释放删除对象及指向对象的链节的空间
********************************/
#ifndef	DELETE_ELEMENT_NODE_H
#define DELETE_ELEMENT_NODE_H

#include"plc_structure.h"
#include"plc_release_node.h"
#include<iostream>

extern void DeleteElementWithInNode(Element *pElement);//删除元件
extern void DeleteNodeWithInNode(Node *pNode);//删除节点

#endif
