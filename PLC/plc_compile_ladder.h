/**********************************
* plc_compile_ladder.h
*将梯的数型结构翻译成指令，写入指定文件
**********************************/

#ifndef COMPILE_NODE_H
#define COMPILE_NODE_H

#include"plc_structure.h"
#include"plc_find_out_in_node.h"
#include"plc_count_nodelink_num.h"
#include"plc_rebuild_node.h"
#include"stdio.h"
#include<qstring.h>
//#include<iomanip.h>

//#define X       0x01
//#define Y       0x02
//#define M       0x03
//#define C       0x04
//#define T       0x05

//#define LD      0xFF
//#define LDI     0xFE
//#define AND     0xFD
//#define ANI     0xFC
//#define OR      0xFB
//#define ORI     0xFA

//#define SET     0xF7
//#define RST     0xF6
//#define OUT     0xF2

////以下指令的define与shape_ladder.h中相同，否则会有redefine的问题
//#define ANB     0xF900
//#define ORB     0xF800
//#define MPS     0xF500
//#define MRD     0xF400
//#define MPP     0xF300
//#define NTO     0xF100
//#define END     0xF000

extern int CompileLadder(Rung *pRungHead);

#endif

