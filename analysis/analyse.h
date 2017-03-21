#ifndef ANALYSE_H
#define ANALYSE_H

#include <QWidget>
#include <QLabel>
#include"sysGlobal.h"

#define EPSINON 1e-4


#define PIX_HIGH        458   //画布高度
#define PIX_WIDTH       700   //画布宽度
#define SCALE_HIGH_Y    335   //SCALE区域的高度
#define SCALE_HIGH_X    270   //SCALE区域的高度
#define SCALE_HIGH_R    270   //SCALE区域的高度
#define SCALE_HIGH      370
#define ANALOG_HIGH     88    //ANALOG区域的高度
#define ANALOG_START_Y  -36   //左右阀，压力阀偏置Y轴坐标的起点位置
#define SCALE_START_Y   25    //Y1Y2位置Y轴坐标的起点位置
#define SCALE_START_X   40    //X位置Y轴坐标的起点位置
#define SCALE_START_R   50    //R位置Y轴坐标的起点位置
#define Y_SCALE         0.73

#define LABEL_FONT      QFont("wenquanyi",7)

//颜色
#define FLAG_LINE_COLOR     QColor(32,32,96)
#define DIVID_LINE_COLOR    QColor(0,64,0)
#define TEXT_COLOR          QColor(100,240,120)

#define Y1_POS_COLOR        QColor(255,0,0)
#define Y2_POS_COLOR        QColor(50,160,50)
#define X_POS_COLOR         QColor(104,34,139)
#define R_POS_COLOR         QColor(0,0,255)
#define PRESS_COLOR         QColor(160,160,0)
#define SPEED_COLOR         QColor(0,155,255)
#define STATE_COLOR         QColor(140,140,140)
#define TIME_COLOR          QColor(128,128,255)

//开关量的背景颜色
#define UDP_COLOR           QColor(0,170,170)
#define ER_COLOR            QColor(170,0,0)
#define MUTE1_COLOR         QColor(170,170,0)
#define MUTE2_COLOR         QColor(170,0,170)
#define CLAMP_COLOR         QColor(68,137,170)
#define LDP_COLOR           QColor(170,170,170)
#define CLOSING_COLOR       QColor(0,170,170)
#define PRESSING_COLOR      QColor(170,0,0)
#define OPENING_COLOR       QColor(170,170,0)
#define TANDEM_COLOR        QColor(170,0,170)

//#pragma pack(8)     //该编译器默认的字节对齐是8,为了和控制系统保持一致,修改默认方式为4,否则传输的文件会有问题
typedef struct Draw_Pos_Line_
{
    float UDP_Pos;      //上死点
    float MUTE_Pos;     //速度转换点
    float CLAMP_Pos;    //夹紧点
    float LDP_Pos;      //下死点
    float ER_Pos;       //泄荷点
}Draw_Pos_Line;

typedef struct QtDrawData_tmp
{
    //十六个模拟量
    float leftvalue;    //左阀偏置
    float rightvalue;   //右阀偏置
    float pressure;     //压力阀
    float speed;        //速度
    float x_speed;      //X轴速度
    float r_speed;      //R轴速度
    float leftposition; //Y1位置
    float rightposition;//Y2位置
    float Y_Pos_Ref;    //Y轴回参位置
    float Xposition;    //X轴位置
    float Rposition;    //R轴位置
    float prestate;
    float in1a;
    float in1b;
    float in2a;
    float in2b;
    float LVDT1;
    float LVDT2;
    //十个开关量
    int udp;        //上死点
    int er;
    int mute1;      //Y1速度转换点
    int mute2;      //Y2速度转换点
    int clamp;      //夹紧点
    int ldp;        //下死点
    int closing;    //泄荷
    int pressing;   //工进
    int opening;    //回程
    int tandem;
    //plc状态
    long plc_input;
    long plc_output;
    long plc_M;
    long plc_Warning;
    long plc_C;
    long plc_T;

    long C_Start;   // 0:已停止 1:已启动 2:正在回参
    int Fin_Flag;   //数据上传结束标志

    struct QtDrawData_tmp *pBefore;
    struct QtDrawData_tmp *pNext;
}QtDrawData;

namespace Ui {
class Analyse;
}

class Analyse : public QWidget
{
    Q_OBJECT

public:
    explicit Analyse(QWidget *parent = 0);
    ~Analyse();


private:
    Ui::Analyse *ui;
    QLabel *pLabel[24];
    //绘图相关参数
    QtDrawData *pHeadDraw;   //分析曲线数据头指针
    QtDrawData *pCurDraw;    //分析曲线数据当前指针
    QtDrawData *pLastDraw;   //分析曲线数据尾指针
    Draw_Pos_Line *pPos_Line;//线段所在位置

    int Anal_Differ;        //分析曲线区分标志位,1为滑块分析，2为挡料分析

    int curLineX;           //光标线位置
    int lineNum;            //线段数量
    int lineXSpd;           //光标移动速度
    bool IO_Show;           //是否显示数字量

    double offsetX;
    double offsetY;
    double scaleX;          //X方向的比例，一条线段向X轴投影长度

    double Y_Min;           //Y轴最小值
    double Y_Max;           //Y轴最大值
    double Ana_Max;      //模拟量最大值
    double X_Min;           //X轴最小值
    double X_Max;          //X轴最大值
    double R_Min;          //R轴最小值
    double R_Max;         //R轴最大值

    float X_COUNT;          //X轴分辨率 从数据库读到，这地方怎么判断
    float R_COUNT;          //R轴分辨率
public:
    void readFromFile(QString filename);
private:
    void paintEvent(QPaintEvent *e);
    void keyPressEvent(QKeyEvent *);
public slots:
    void zoom_In();
    void zoom_Out();
};

#endif // ANALYSE_H
