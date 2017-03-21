/* plc_insert_element.h */
//在pElementCur前或后插入元件pElementInsert

#ifndef INSERT_ELEMENT_H
#define INSERT_ELEMENT_H

#include"plc_structure.h"

extern int InsertElementWithInNode(Element *pElementCur, Element *pElementInsert);//在pElementCur前插入元件pElementInsert
extern int InsertElementWithInNodeBack(Element *pElementCur, Element *pElementInsert);//在pElementCur后插入元件pElementInsert

#endif
