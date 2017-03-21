/*******************************
**plc_ISN.h
//指令与内码的对应关系
*******************************/

#ifndef PLC_ISN_H
#define PLC_ISN_H

#define MASK       1
#define MAX1NUM    10
#define HIGH16     0xFFFF0000
#define LOW16      0x0000FFFF
#define MULTINOM   0xA0000001
#define CRC32      0xFFFFFFFF

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
#define SET_C      0xF704
#define SET_T      0xF705
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

#endif


