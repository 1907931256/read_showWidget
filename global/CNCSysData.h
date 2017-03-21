#ifndef CNCSYSDATA_H
#define CNCSYSDATA_H
#include "qstring.h"

#define EPSINON 1e-4
#define PI 3.1415926
#define TOPI (PI/180.0)
#define NETCODE 0xFF11
#define ETHERTYPE_PBP 0xfe1f
#define FILTER2 "ether proto 0xfe1f"
#define NOOPTIMIZE 0
#define DEFAULT_INPUT_LENGTH 90 //输入框长度默认值

#define  MALLOC(n,type)  ((type*)malloc((n)*sizeof(type)))
#define  ARRAY_SIZE(a)   (sizeof(a)/sizeof((a)[0]))
#define  P_CR  10        //光标半径
#define  Kr    0.15625   //折弯系数

enum Mode {GRAPH_PROGRAM, DATA_PROGRAM, PRODUCT_FILE, MODEL_UP,\
           CONSTANT_PROGRAM, PROGRAM_BACKUP, MODEL_DOWN,\
           MACHINE_UP, MACHINE_DOWN, MODEL_BACKUP, MACHINE_CONSTANT,\
           MACHINE_DIAGNOSIS};
enum MainMode{MAIN_START,MAIN_MANUAL,MAIN_AUTO,MAIN_PROGRAM,MAIN_STEP,MAIN_MOVE,MAIN_DIAG,MAIN_CONST,MAIN_MACHINE,MAIN_ANALYSE};

enum Direct {DIREC_UP, DIREC_DOWN, DIREC_LEFT, DIREC_RIGHT};
enum RemoteCmd{RT_UP,RT_DOWN,RT_LEFT,RT_RIGHT,RT_MANU,RT_DIAG,RT_PROG};
enum Position{CURSOR_CORNER,CURSOR_CENTER,CURSOR_TAIL,\
              CURSOR_ORIGIN,CURSOR_VOPEN,CURSOR_RADIUS};//后面的两个参数专为下模设计的
//四种机床工具:上模,下模,上部外形,下部外形,材料,机床轮廓
enum ToolMode{TOOL_PUNCH,TOOL_DIE,TOOL_UPPER,TOOL_LOWER,TOOL_MATERIAL,TOOL_BODY};

//运动控制所需机床参数
typedef struct General_Para_structure
{
    float Y1_Ref_Pos;       // Y1参考点位置 mm
    float Y2_Ref_Pos;       // Y2参考点位置 mm
    float Ref_UDP_Pos;      // 回参后的停止位置
    float Y_Track_Err;
    float Y_Close_Track_Err;// 快下跟随误差
    float Y_Press_Track_Err;// 工进跟随误差
    float Y_Open_Track_Err; // 回程跟随误差
    float Y1Y2_Err;         // 同步误差
    float UDP_Pos_Margin;   // 上死点位置撤除
    float Accuracy;         // 滑块定位允许误差
    float X_Accuracy;       // X轴定位允差

    float Ref_Speed;        // 寻参速度 mm/s
    float Close_Speed;      // 快下速度 mm/s
    float Press_Speed;      // 工进速度 mm/s
    float Unload_Speed;     // 卸压速度 mm/s
    float Open_Speed;       // 快上速度 mm/s

    float Close_Acc_T;      // 快下加速时间 msec
    float Press_Acc_T;      // 工进加速时间 msec
    float Unload_Acc_T;     // 卸压加速时间 msec
    float Open_Acc_T;       // 快上加速时间 msec

    float Press_Valve_Acc_T; //压力阀加速时间
    float Unload_Hold_T;     //卸压时间

    float Close_Dec_T;      // 快下减速时间 msec
    float Press_Dec_T;      // 工进减速时间 msec
    float Unload_Dec_T;     // 卸压减速时间 msec
    float Open_Dec_T;       // 快上减速时间 msec

    float Close_Delay;      // 快下前延时 ms
    float Press_Delay;      // 工进前延时 ms（经过MUTE后的延时时间）
    float Open_Delay;       // 快上前延时 ms

    float Close_Press;      // 快下压力 % （占最大输出压力的百分比）
    float Delay_Press;      // 工进前延时阶段的压力 %
    float Open_Press;       // 快上压力 % （不可过小）

    float Close_Kp;         // 快下比例系数
    float Close_Ki;         // 快下积分系数
    float Press_Kp;         // 工进比例系数
    float Press_Ki;         // 工进积分系数
    float Ki_Zone;          // 工进作用区间
    float Open_Kp;          // 开起比例系数
    float Open_Ki;          // 开起积分系数
    float Kff_Coef;         // 前馈系数

    float Hold_Kp_Coef;		// 保压比例增益系数
    float Hold_Ki_Coef;		// 保压积分增益系数
    float Hold_Parallel_Coef;// 保压平行度增益系数
    float Hold_Kd_Coef;     // 保压微分增益系数
    float Hold_Press_Percent;//保压压力系数

    float Close_Ramp_Offset;// 快下斜坡补偿

    float Close_Parallel;	// 平行度
    float Press_Parallel;
    float Open_Parallel;

    float X_Ref_Pos;        // X轴参考点位置
    float X_Track_Err;
    float X_Speed;          // X轴速度
    float X_Manual_Speed;   // X轴手动高速值
    float X_Ref_Speed;      // X轴回参速度
    float X_Acc_T;          // X轴加速时间 ms
    float X_Dec_T;          // X轴减速时间 ms
    float X_Kp;             // X轴比例系数
    float X_Ki;             // X轴积分系数
    float X_Ki_Zone;        // 积分作用区间
    float X_Kd;             // X轴微分增益
    float X_Resolution;     // X轴分辨率
    float X_Safe_Dis;       // X轴安全距离
    float X_Safe_Speed;     // X轴安全速度
    float X_Max;            // X轴最大值
    float X_Min;            // X轴最小值

    long X_SinglePos;      // X轴单边定位
    float X_OverDis;        // X轴超程距离
    float X_OverTime;       // X轴超程时间

    float R_Ref_Pos;        // R轴参考点位置
    float R_Track_Err;
    float R_Speed;          // R轴速度
    float R_Ref_Speed;      // R轴回参速度
    float R_Acc_T;          // R轴加速时间 ms
    float R_Dec_T;          // R轴减速时间 ms
    float R_Kp;             // R轴比例系数
    float R_Ki;             // R轴积分系数
    float R_Resolution;	    //R轴分辨率
    float R_Max;            //R轴最大值
    float R_Min;            //R轴最小值

    long R_SinglePos;      // R轴单边定位
    float R_OverDis;        // R轴超程距离
    float R_OverTime;       // R轴超程时间

    volatile long Auxi_State;// 辅助轴使能状态
    long Auxi_Addr;		     // 辅助轴输入、输出地址编号
    long M_Option;           // 自动跑机

    long Valve_Offset_Y1_left;// Y1阀左偏置
    long Valve_Offset_Y1_right;// Y1阀右偏置
    long Valve_Offset_Y2_left;// Y2阀左偏置
    long Valve_Offset_Y2_right;// Y2阀右偏置
    long Y_count_direction;	 // Y轴光栅计数方向
    long X_count_direction;	 // X轴计数方向
    long R_count_direction;	 // R轴计数方向
    long Y1_count_direction; // Y1轴光栅计数方向
    long Y2_count_direction; // Y2轴光栅计数方向
    long Select_control;     // 回参前位置控制方式
    long OFFAN1;			 // 诊断程序下，阀的五个偏置量
    long OFFAN2;
    long OFF_Y1;
    long OFF_Y2;
    long OFF_P;

    long isEND;
    long BCC_Code;
}stu_general_para;

//DSP对上位机指令的应答包结构体
typedef struct DSPAnswer_structure
{
    volatile long command;	//回包的命令头
    long reCommand;		    //该包是对该命令的回包
    int slaveNumL;          //下位机编号低4个字节
    int slaveNumH;          //下位机编号高2个字节，高16位为0
    int isOK;				//校验结果
}stu_DSPAnswer;

//诊断界面下位机的回显数据
struct buffcommandDSP
{
    unsigned int IO1;//32个GPIO
    unsigned int IO2;//32个GPIO

    volatile float Y1A_Fdb;
    volatile float Y1B_Fdb;
    volatile float Y2A_Fdb;
    volatile float Y2B_Fdb;
    volatile float P_Fdb;

    volatile float IN1A;//模拟输入1
    volatile float IN1B;//模拟输入2
    volatile float IN2A;//模拟输入3
    volatile float IN2B;//模拟输入4

    volatile long OUT1;//模拟输出1
    volatile long OUT2;//模拟输出2
    volatile long OUT3;//模拟输出3
    volatile long OUT4;//模拟输出4
    volatile long OUT5;//模拟输出5

    volatile int left_valve_deflection;//左阀偏置
    volatile int right_valve_deflection;//右阀偏置
    volatile float left_valve_LVDT;
    volatile float right_valve_LVDT;
    unsigned int press_valve_deflection;//压力阀偏置
    unsigned int crowning_valve_deflection;//顶阀挠度

    unsigned int enc1;
    unsigned int enc2;
    unsigned int enc3;
    unsigned int enc4;

    unsigned int enc1_ref;
    unsigned int enc2_ref;
    unsigned int enc3_ref;
    unsigned int enc4_ref;

    unsigned int Diag_State;
    long Diag_HardWare;
};

typedef struct diagnosis_show_
{
    volatile long command;
    struct buffcommandDSP data;
    unsigned int isEnd;
    unsigned int BCC_Code;
}Diagnosis_Show;

typedef struct Manual_Pos_structure	//
{
    long Y_Dir;	// 0:停止 1:正向 -1:负向
    long X_Dir;	//
    long R_Dir;	//
    long isEnd;
    long BCC_Code;
}stu_move_pos;

//====================两个数据结构==================
typedef struct FileHeadType //文件头，每个工艺或图形文件均有
{
    unsigned int fileid;    //程序号
    char name[20];          //图示号
    int fBendNo;            //折弯总数
    //int fBendNoAll;         //所有折弯段数(包括圆弧的折弯数)
    char fType[20];         //文件类型
    int fPunch;             //上模
    int fDie;               //下模
    //char fFilePath[100];  //文件路径
}MFileType;

//数据编程之前的几个参数
typedef struct stu_dataEdit_structure_before
{
    int iAngleSel;				//角度选择
    double dThickness;		    //厚度
    int iMaterial;				//材料类型
    double dBlackLength;	    //材料宽度
    double dLength;             //和折弯数据中的宽度相同,用于图形编程
    int link;                   //连接，数字变成用
    int sizeSel;                //尺寸选择,图形编程用
}stu_beforeBend;

//保存折弯顺序的链表
typedef struct  BendOrder_structure
{
    int bendpoint;         					//折弯点
    int backgauge_point;   					//档料点--------------------------修改10.20-------------------------
    //图形显示用档料位置
    float gauge_position_x;					//档料点的X坐标，
    float gauge_position_y;					//档料点的Y坐标
    //工艺用档料位置参数
    float gauge_position_x_paremeter;       //档料点的X坐标，
    float gauge_position_y_paremeter;		//档料点的Y坐标
    float gauge_dXRetract;                  //挡料退让距离
    int interefere_tag;             		//干涉标志2(方向2不干涉），1（方向1不干涉），0（两个方向都不干涉），其他（干涉）
    int direction_h;      					//前后掉头状态，1或-1
    int direction_v;       					//上下翻转状态，1或-1
    struct  BendOrder_structure *pBefore;
    struct  BendOrder_structure *pNext;
}stu_bendorder;

typedef struct stu_line_data_tmp
{
    int bendPoint;          //当前折弯点数
    float angle;            //折弯角
    float axis_bend[2];     //包含大圆弧的折弯数据
    float axis_bend_bac[2]; //包含大圆弧的折弯数据备份
    int isBended;           //是否已经折过,0未折过,1已经折过
    int bendNum_Arcle;      //大圆弧段的折弯次数
    int bend_precision;     //精度要求
    struct stu_line_data_tmp *pNext;
    struct stu_line_data_tmp *pBefore;
}stu_line_data;

typedef struct  DataEdit_structure
{
    //stu_bendorder pstu_bend;
    unsigned int uiBendNum;
    //====================================
    //Axis function轴在当前工步的速度占最大速度的百分比
    double dVX_percent;
    double dVR_percent;
    //====================================
    //gauge function
    unsigned int uiGaugePos;    //挡料位置，即板料放在第几个台阶上定位
    double dRfingerPosition;	//与板料接触的挡指位置沿R轴方向的高度
    double dXfingerPosition;	//与板料接触的挡指位置沿X轴方向的高度
    //******page 1*************  
    //bend
    unsigned int uiPunch;       //上模
    unsigned int uiDie;         //下模
    unsigned int iMethod;       //折弯方式
    double dLength;             //宽度
    //angle
    double dAngleOrBendPosition;//角度或折弯位置，取决于Y轴的编程方式，折弯位置的确定有两种方法,Y1位置
    double dPositionY2;         //Y2位置
    double dOpeningY;           //开口高度，折弯后，上下模之间的高度，相对于速度转换点
    double dMutePosition;       //速度转换点
    //辅助轴
    double dXStartPosition;		//开始位置，为了定位，
    double dXRetract;			//X轴在当前工步的退让距离
    double dRStartPosition;		//R轴位置
    double dCptCrown;           //挠度补偿
    
    //********page 2***********
    double dParallism;			//平行度，左右油缸之间的差值，此参数在加紧点以下有效
    unsigned int uiCode;		//折弯结束后，下一道折弯参数何时载入内存执行，即何时换步
    double delaytime;			//换步之前的延时时间
    int uiReputition;           //换步之前的循环次数
    double dForce;				//压制时的吨位	//系统自动计算
    double dwellTime;			//滑块在折弯点的保压时间
    double decoppression;		//卸压距离//Decompression stroke after bending to release the working pressure
    double dSpeed;				//滑块工进时的速度
    double decompSpeed;			//卸压速度
    double dAngleNumber;		//该工步是从左到右计数的第几个折弯工步
    double dClamp_Pos;          //夹紧点的绝对位置
    unsigned int uiBackgaugeNum;//板料定位时与后挡料接触的位置，该位置是板料上从左到右，从零开始计数的可定位位置
    unsigned int uiMachineUpperSide;	//机床的上部外形
    unsigned int uiMachineLowerSide;	 //机床的下部外形

    //补偿数据
    unsigned int workpiece_count;   //工件计数
    double dSingleCptAngle1;        //单步角度补偿1
    double dSingleCptAngle2;        //单步角度补偿2
    double dOverallCptAngle;        //全局角度补偿
    double dSingleCptX1;            //X1轴的单步补偿
    double dSingleCptX2;            //X2轴的单步补偿
    double dOverallCptX;            //X1和X2轴的全局补偿
    double dSingleCptR;             //R轴的单步补偿
    double dSingleCptCrown;         //挠度轴的单步校正


    /*
    注意，
    1，如果对上面的4个参数进行了正确的设定，
        就可以在自动模式的视图显示功能中
        对工件的折弯情况进行模拟只需要输入图形所需参数和板料的长度即可；
    2，如果选择继续设定新折弯的参数，
        系统所显示的新折弯的相关参数是前一折弯的拷贝，
        只需要将被折弯与前一折弯不同的参数进行适当修改即可
    */
    /*辅助轴---不知道怎么控制
    double dRaxis;
    double dZ1axis;
    double dZ2axis
    unsigned int uiPartSupprot;
    unsigned int uiOnOff;
    */
    struct  DataEdit_structure *pBefore;
    struct  DataEdit_structure *pNext;
}stu_BendData;

typedef struct Bend_Para_structure	//手动加工参数
{
    long Work_Mode;     // 1:Manual 2:Auto 3:Step 4:move
    long Bend_Num;		// 工步号 Manual Mode 时为0
    long Bend_Mode;		// 1为自由折弯；2为压底折弯;3为压平折弯，4为压平压底折弯
    float Mute_Pos;		// Mute绝对位置
    float Clamp_Pos;	// Clamp点绝对位置
    float Press_Dis;	// Y1工进距离（Clamp到LDP）
    float Press_Dis_Sec;// Y2工进距离（Clamp到LDP）
    float Press_Spd;	// 工进速度
    float Unload_Dis;	// 卸荷距离（LDP到ER）
    float Unload_Spd;	// 卸荷速度（LDP到ER）
    float Open_Dis;		// Y轴回程距离（LDP到UDP）

    float dWellTime;	// 保压时间 ms

    float Work_Press;	// 工进压力 kN
    float X_Percent;    // X轴速度百分比
    float X_Position;	// X轴位置
    float X_Back_Dis;	// X轴退让距离
    float R_Percent;    // R轴速度百分比
    float R_Position;	// R轴位置
    float R_Safe_Dis;	// X方向R轴临界区移动距离

    float Deflection_DA;// 挠度补偿DA值

    int CNCAuthor;      // 授权标志
    int	End;
    int Bcc_Code;
}stu_bend_para;

//机床状态结构体，实时向上位机发送
typedef struct stu_manualData
{
    volatile long command;
    long Bend_Fin;      //
    long C_Start;       // 0:已停止 1:已启动 2:正在回参
    long Work_State;
    long Ref_State;
    long Y_State;		// 0:初始 1:快下 2:MUTE 3:工进 4:保压 5:卸荷 6:快上 7:工步结束
    long Y1_data;
    long Y2_data;
    long X1_data;
    long R_data;
    long X_Des;
    long Err_State;
    long Internal_Warning_State;//内部报警标志位，用于未开油泵报警等
    long Pos_Fixed;             //定位结束判断位

    long plc_input;
    long plc_output;
    long plc_M;
    long plc_Warning;
    long plc_C;
    long plc_T;
    long Y_Manual_Flag;     //手动移动轴中显示调整的标志位
    long Diag_HardWare;

    float press;
    float y_speed;
    float x_speed;
    float r_speed;

    //long Pump_State;
}stu_stateData;

/*****************模具结构体**************************/
//模具的轮廓以尖点为中心分为左右两部分
typedef struct ToolLine
{
    double dAngle;          //角度
    double dLength;         //长度
    //绘图点
    double dStartX;
    double dStartY;
    double dEndX;
    double dEndY;
    struct ToolLine *pNext;     //指向后一段线段
    struct ToolLine *pBefore;   //指向前一段线段
}stu_toolLine;

/****************圆弧显示****************************/
struct stu_drawArc_tmp
{
    int ix;
    int iy;
    int iw;
    int ih;
    int ia;
    int ialen;
};

/***************绘制工件结构体***********************/
typedef struct stu_line_save_tmp
{
    double dLength;          //宽度
    double dAngle;           //角度
    double relativeAngle;   //相对角度
    double dRadius;          //半径
    unsigned int uiBendNum;  //大圆弧折弯段数
    unsigned int uiPrecision;//精度要求
    //绘图点
    double dStartX;         //起点X轴坐标
    double dStartY;         //起点Y轴坐标
    double dEndX;           //终点X轴坐标
    double dEndY;           //终点Y轴坐标
    //绘制垂足虚线所需的点
    double headDotEndX;
    double headDotEndY;
    double tailDotStartX;
    double tailDotStartY;
    //for cursor
    double dCenterX;
    double dCenterY;
    double dArcCenterX;
    double dArcCenterY;

    struct stu_drawArc_tmp dDrawArc;   //绘制圆弧参数
    struct stu_line_save_tmp *pNext;
    struct stu_line_save_tmp *pBefore;
}stu_line_save;

/********加工界面下需要访问数据库得到的信息*******/
typedef struct ProductDBData
{
    float X_COUNT;      //X轴分辨率
    float R_COUNT;      //R轴分辨率
    int Unit;           //压力单位
    float KPress;       //压力因子
    int RemedyEnable;   //折弯数据修正允许
    int Y1Y2Ref;        //Y1Y2不关联
    float ClampRemedy;  //夹紧修正
    float ForcePercent; //压力系数
    float R_Safe_Dis;   //X轴方向上R轴的临界距离
    //0为不自动进行换步操作，要执行下一工步必须手动装入下一工步的参数
    //1为系统自动调入下一工步的参数，但必须按下启动键后才能进行下一工步的加工
    int StepMethod;     //单步模式下自动工步变化

    int   bAutoRun;       //自动跑机
    float Machine_Length;//机床总长度
    float L_btn_cylinder;//机床立柱间距离
    float under_inertia; //工作台惯量
    float upper_inertia; //滑块惯量
    float Stiffness;     //刚强
    float Stiffness_Frame;//机床结构刚度
    float Tool_Reference;//模具间的参考距离
    float Tool_Ref_Correct;//模具安装方式校正
    float Y1Y2_Max;
    float Y_Min;        //Y最小值
    float Y_Max;        //Y最大值
    float Max_Press;    //最大压力
    float Mid_Press;    //中间压力
    float Min_Press;    //最小压力
    float Max_Press_DA;
    float Mid_Press_DA;
    float Min_Press_DA;
    float Max_Press_Speed;
    float R_Min;
    float R_Max;
    float X_Min;
    float X_Max;
    float Max_Deflection;//最大挠度补偿
    float Min_Deflection;//最小挠度补偿
    float Max_Deflection_DA;
    float Min_Deflection_DA;
}stu_ProductData;

typedef struct cur_state
{
    //实时工况
    float Y_speed;               //Y轴速度
    float X_speed;               //X轴速度
    float R_speed;               //R轴速度
    float Y_press;               //Y轴负载

    long Y_State;               //0:初始 1:快下 2:MUTE 3:工进 4:保压 5:卸荷 6:快上 7:工步结束
    long Y1_data;               //Y1位置
    long Y2_data;               //Y1位置
    long X_data;                //X位置
    long R_data;                //R位置
    //long plc_M;                 //运行过程中的状态
    long program_id;            //程序号
    long cur_bend;              //当前处于第几道折弯
    long bendNum;               //折弯总数
    long C_Start;               //0:已停止 1:已启动 2:正在回参
    long punch_id;              //上模号
    long die_id;                //下模号
    float work_time;             //工作时间
}cur_state_data;

#endif // CNCSYSDATA_H
