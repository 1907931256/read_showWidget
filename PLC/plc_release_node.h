/*plc_release_node.h*/
//释放节点的内存，用在删除节点后/不包括指向节点的链节！！！！
#ifndef RELEASE_NODE_H
#define RELEASE_NODE_H

#include"plc_structure.h"

extern void ReleaseNode(Node *pNode);

#endif

