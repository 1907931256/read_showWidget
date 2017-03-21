/*plc_shape_ladder.h
*从文件中读取指令内码构造树型结构
*思想：栈
*/
//文件名为 PlcInstruction.*
#ifndef PLC_SHAPE_LADDER_H
#define PLC_SHAPE_LADDER_H


#include<qstring.h>
//#include<iomanip.h>
#include<stdio.h>
#include"plc_structure.h"
#include"plc_stack_plc.h"
#include"plc_shape_ladder_test.h"

#include"plc_ISN.h"	//指令与内码的对应关系

Rung *ShapeLadder(char*);

#endif


/********************
程序中的switch case语句可以简化成:
switch(XX)
{
	case  LD
	{
		if(XXX == X)
		{
		
		}
		else if(XXX == Y)
		{
		
		}
		...
		else if()..
		
		stkBranch->Push(pElement);		
	}	
	case LDI
	{
	}
	case AND
	{
	}
	...
}
程序更短,每次判断的次数可以成(?)倍的减少
********************/

/*
#include"plc_structure.h"
#include"plc_stack_plc.h"
#include"plc_shape_ladder_test.h"
*/
/*
//指令与内码的对应关系
#define LD_X       0xFF01
#define LD_Y       0xFF02
#define LD_M       0xFF03
#define LD_C       0xFF04
#define LD_T       0xFF05
#define LDI_X      0xFE01
#define LDI_Y      0xFE02
#define LDI_M      0xFE03
#define LDI_C      0xFE04
#define LDI_T      0xFE05
#define AND_X      0xFD01
#define AND_Y      0xFD02
#define AND_M      0xFD03
#define AND_C      0xFD04
#define AND_T      0xFD05
#define ANI_X      0xFC01
#define ANI_Y      0xFC02
#define ANI_M      0xFC03
#define ANI_C      0xFC04
#define ANI_T      0xFC05
#define OR_X       0xFB01
#define OR_Y       0xFB02
#define OR_M       0xFB03
#define OR_C       0xFB04
#define OR_T       0xFB05
#define ORI_X      0xFA01
#define ORI_Y      0xFA02
#define ORI_M      0xFA03
#define ORI_C      0xFA04
#define ORI_T      0xFA05
#define ANB        0xF900
#define ORB        0xF800
#define SET_Y      0xF702
#define SET_M      0xF703
//#define SET_C      0xF704
//#define SET_T      0xF705
#define RST_Y      0xF602
#define RST_M      0xF603
#define RST_C      0xF604
#define RST_T      0xF605
#define MPS        0xF500
#define MRD        0xF400
#define MPP        0xF300
#define OUT_Y      0xF202
#define OUT_M      0xF203
#define OUT_C      0xF204
#define OUT_T      0xF205
#define NTO        0xF100
#define END        0xF000
*/
/*
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
#define ANB     0xF9
#define ORB     0xF8
#define SET     0xF7
#define RST     0xF6
#define MPS     0xF5
#define MRD     0xF4
#define MPP     0xF3
#define OUT     0xF2
#define NTO     0xF1
#define END     0xF0
*/




