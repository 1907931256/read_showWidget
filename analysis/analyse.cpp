#include "analyse.h"
//#include "CNCGlobalFuncs.h"
#include"globalFunction.h"
#include "ui_analyse.h"
#include "CNCKeyboard.h"
#include <QPainter>
#include <QPen>
#include <QTextStream>
#include <QDebug>
#include <math.h>
#include <QTextCodec>
#include <QKeyEvent>
#include<CNCSysData.h>

Analyse::Analyse(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Analyse)
{
    ui->setupUi(this);
    pLabel[0] = ui->label;
    pLabel[1] = ui->label_2;
    pLabel[2] = ui->label_3;
    pLabel[3] = ui->label_4;
    pLabel[4] = ui->label_5;
    pLabel[5] = ui->label_6;
    pLabel[6] = ui->label_7;
    pLabel[7] = ui->label_8;
    pLabel[8] = ui->label_9;
    pLabel[9] = ui->label_10;
    pLabel[10] = ui->label_11;
    pLabel[11] = ui->label_12;
    pLabel[12] = ui->label_13;
    pLabel[13] = ui->label_14;
    pLabel[14] = ui->label_15;
    pLabel[15] = ui->label_16;
    pLabel[16] = ui->label_17;
    pLabel[17] = ui->label_18;
    pLabel[18] = ui->label_19;
    pLabel[19] = ui->label_20;
    pLabel[20] = ui->label_21;
    pLabel[21] = ui->label_22;
    pLabel[22] = ui->label_23;
    pLabel[23] = ui->label_24;

    QString dbPath = relativePath + "machineconstants.db";
    X_COUNT = ReadSqlData(dbPath,"XAxis",12,1).toFloat();   //X轴分辨率
    R_COUNT = ReadSqlData(dbPath,"RAxis",12,1).toFloat();   //R轴分辨率
    //类中参数初始化
    pHeadDraw = NULL;
    pCurDraw = NULL;
    pLastDraw = NULL;
    pPos_Line = NULL;
    Anal_Differ = 0;     //区分数据分析种类
    Y_Min = 0;
    Y_Max = 0;
    Ana_Max = 0;
    X_Max = 0;
    X_Min = 0;
    R_Max = 0;
    R_Min = 0;
    curLineX = 0;
    lineNum = 0;
    offsetX = 0;
    offsetY = 0;
    lineXSpd = 1;
    IO_Show = true;
    pPos_Line = NULL;
    pHeadDraw = NULL;
//    if(pHeadDraw != NULL)
//    {
//        getMostValue(); //获取数据项中的最值和数据项的个数
//        scaleX = (float)PIX_WIDTH/lineNum; //单条线段允许的X轴的长度
//        curLineX = lineNum/2;
//    }
}

Analyse::~Analyse()
{
    delete ui;
}

void Analyse::readFromFile(QString filename)
{
    pHeadDraw = NULL;
    pCurDraw = NULL;
    pLastDraw = NULL;
    pPos_Line = NULL;
    Y_Min = 0;
    Y_Max = 0;
    Ana_Max = 0;
    X_Min = 0;
    X_Max = 0;
    R_Max = 0;
    R_Min = 0;
    lineNum = 0; //线段数量

    IO_Show = true;//暂时让IO为false

    FILE *fp;
    QByteArray mByte = filename.toLatin1();
    char *path = mByte.data();
   if((fp = fopen(path,"rb")) == NULL) //可读写方式打开;
    {
        //errStack.pushERR(ERR_FILE_OPEN);
        qDebug()<<"打开文件错误!";
        return;
    }
    fseek(fp,0,SEEK_END); //设置文件指针指向fp位置;
    int len = ftell(fp);//文件位置指针想对于文件首的偏移字节数;
    lineNum = (len-sizeof(Draw_Pos_Line)-sizeof(int))/sizeof(QtDrawData);
    int count = lineNum;

    scaleX = (float)PIX_WIDTH/lineNum; //单条线段允许的X轴的长度
    offsetX = 0;
    curLineX = lineNum/2;

    fseek(fp,0,SEEK_SET);//文件开头
    int flagSave = fread(&Anal_Differ,sizeof(int),1,fp);//读取不成功返回0，读到的值保存到anal——difer中
    if(flagSave != 1)
    {
        fclose(fp);
        fp = NULL;
        return;
    }

    while (count > 0)
    {
        pCurDraw = MALLOC(1,QtDrawData);
        int flagLine = fread(pCurDraw,sizeof(QtDrawData),1,fp);
        if(flagLine != 1)
        {
            fclose(fp);
            fp = NULL;
            return;
        }
        //Y轴最大最小值
        if(Y_Min < EPSINON)      //Y轴第一组数据
            Y_Min = pCurDraw->leftposition;
        if(pCurDraw->leftposition < Y_Min)
            Y_Min = pCurDraw->leftposition;
        if(pCurDraw->rightposition < Y_Min)
            Y_Min = pCurDraw->rightposition;
        if(pCurDraw->leftposition > Y_Max)
            Y_Max = pCurDraw->leftposition;
        if(pCurDraw->rightposition > Y_Max)
            Y_Max = pCurDraw->rightposition;
        //模拟量最大值
        if(fabs(pCurDraw->leftvalue) > Ana_Max)
            Ana_Max = fabs(pCurDraw->leftvalue);
        if(fabs(pCurDraw->rightvalue) > Ana_Max)
            Ana_Max = fabs(pCurDraw->rightvalue);
        if(fabs(pCurDraw->pressure) > Ana_Max)
            Ana_Max = fabs(pCurDraw->pressure);
        //X轴最大最小值
        if(X_Min < EPSINON)      //X轴第一组数据
            X_Min = pCurDraw->Xposition;
        if(pCurDraw->Xposition < X_Min)
            X_Min = pCurDraw->Xposition;
        if(pCurDraw->Xposition > X_Max)
            X_Max = pCurDraw->Xposition;
        //R轴最大最小值
        if(R_Min < EPSINON)      //R轴第一组数据
            R_Min = pCurDraw->Rposition;
        if(pCurDraw->Rposition < R_Min)
            R_Min = pCurDraw->Rposition;
        if(pCurDraw->Rposition > R_Max)
            R_Max = pCurDraw->Rposition;
        //构建双向链表
        if(pHeadDraw == NULL)
        {
            pHeadDraw = pCurDraw;
            pLastDraw = pCurDraw;
        }
        else
        {
            pLastDraw->pNext = pCurDraw;
            pCurDraw->pBefore = pLastDraw;
            pLastDraw = pCurDraw;
            pLastDraw->pNext = NULL;
        }
        count--;
    }
    pPos_Line = MALLOC(1,Draw_Pos_Line);      //需要重新分配内存
    int flagPos = fread(pPos_Line,sizeof(Draw_Pos_Line),1,fp);
    if(flagPos != 1)
    {
        fclose(fp);
        fp = NULL;
        return;
    }
    fclose(fp);
    fp = NULL;
//    //将手动下分析曲线的指针指向当前文件读取的数据
    //    pStart->pMainManual->pHeadDraw = pHeadDraw;
}

void Analyse::paintEvent(QPaintEvent *e)
{
    e = e;
    QRect destRect(5,90,PIX_WIDTH,PIX_HIGH);
    QRect sourceRect(0,0,PIX_WIDTH,PIX_HIGH);
    QPixmap *pixMap = new QPixmap(PIX_WIDTH,PIX_HIGH);//700*458
    pixMap->fill(Qt::black);

    //曲线的起始点
    int startX1,startY1,endX1,endY1;    //Y1_ANALOG
    int startX2,startY2,endX2,endY2;    //Y2_ANALOG
    int startX3,startY3,endX3,endY3;    //PRESSURE
    int startX4,startY4,endX4,endY4;    //Y1_POS
    int startX5,startY5,endX5,endY5;    //Y2_POS
    int startX6,startY6,endX6,endY6;    //X_POS
    int startX7,startY7,endX7,endY7;    //R_POS
    int inputY[4];
    int outputY[6];
    int Xrange;
    int Rrange;
    int Xscope;
    int Rscope;

    int posTmp = 0;
    startX1 = 0;
    startX2 = 0;
    startX3 = 0;
    startX4 = 0;
    startX5 = 0;
    startX6 = 0;
    startX7 = 0;
    startY1 = ANALOG_START_Y;//-36
    startY2 = ANALOG_START_Y;
    startY3 = ANALOG_START_Y;
    startY4 = SCALE_START_Y;//25
    startY5 = SCALE_START_Y;
    startY6 = SCALE_START_X;//40
    startY7 = SCALE_START_R;//50

    double Y_Most = Y_Max-Y_Min; //Y轴最大最小值的差
    if((X_Max-X_Min) < X_COUNT) //此处判断X轴是否使用
    {
        Xrange = 1;
        Xscope = 5;
    }
    else
    {
        Xrange = X_Max-X_Min;
        Xscope = SCALE_HIGH_X;//270
    }
    if((R_Max-R_Min) < R_COUNT) //此处判断R轴是否使用
    {
        Rrange = 1;
        Rscope = 5;
    }
    else
    {
        Rrange = R_Max-R_Min;
        Rscope = SCALE_HIGH_R;//370
    }

    QPainter painter;
    painter.begin(pixMap);
    painter.setPen(Qt::SolidLine);
    painter.setRenderHint(QPainter::Antialiasing);//抗锯齿
    if(IO_Show)
        painter.scale(scaleX,Y_SCALE);  //设置缩放比例
    else
    painter.scale(scaleX,1);
    painter.translate(offsetX,ANALOG_HIGH);//设置偏移量
    painter.setFont(LABEL_FONT);
    painter.setPen(Qt::yellow);
    painter.drawLine(curLineX,(int)(-PIX_HIGH/Y_SCALE),curLineX,(int)(PIX_HIGH/Y_SCALE));//纵向黄色坐标线
    if(IO_Show == false)        //不显示IO
    {
        //绘制文字
        painter.scale(1.0/scaleX,1);
        painter.setPen(TEXT_COLOR);
        painter.drawText(2-offsetX*scaleX,-75,"Analog output Signals");
        painter.drawText(2-offsetX*scaleX,13,"Scales");
        //绘制线段
        painter.scale(scaleX,1);//根据X轴方向上的数据多少,改变缩放比例
        painter.setPen(FLAG_LINE_COLOR);
        posTmp = ANALOG_START_Y; //-36
        painter.drawLine(0,posTmp,lineNum,posTmp);      //模拟量中心线
        posTmp = (int)((pPos_Line->UDP_Pos*1000-Y_Min)/Y_Most*SCALE_HIGH_Y+SCALE_START_Y);
        painter.drawLine(0,posTmp,lineNum,posTmp);                      //上死点位置直线
        posTmp = (int)((pPos_Line->MUTE_Pos*1000-Y_Min)/Y_Most*SCALE_HIGH_Y+SCALE_START_Y);
        painter.drawLine(0,posTmp,lineNum,posTmp);                      //速度转换点位置直线
        posTmp = (int)((pPos_Line->CLAMP_Pos*1000-Y_Min)/Y_Most*SCALE_HIGH_Y+SCALE_START_Y);
        painter.drawLine(0,posTmp,lineNum,posTmp);                      //夹紧点位置直线
        posTmp = (int)((pPos_Line->ER_Pos*1000-Y_Min)/Y_Most*SCALE_HIGH_Y+SCALE_START_Y);
        painter.drawLine(0,posTmp,lineNum,posTmp);                      //泄荷点位置直线
        posTmp = (int)((pPos_Line->LDP_Pos*1000-Y_Min)/Y_Most*SCALE_HIGH_Y+SCALE_START_Y);
        painter.drawLine(0,posTmp,lineNum,posTmp);                      //下死点位置直线
        painter.setPen(QPen(DIVID_LINE_COLOR,3));           //第一条分隔线,线宽3
        painter.drawLine(0,0,lineNum,0);
    }
    else                        //显示IO
    {
        //绘制文字
        painter.scale(1.0/scaleX,1.0/Y_SCALE);
        painter.setPen(TEXT_COLOR);
        painter.drawText(2-offsetX*scaleX,-52,"Analog output Signals");
        painter.drawText(2-offsetX*scaleX,13,"Scales");
        painter.drawText(2-offsetX*scaleX,285,"Digital Signal Output");
        painter.drawText(2-offsetX*scaleX,353,"Digital Signal Input");
        painter.scale(scaleX,Y_SCALE);
        painter.setPen(FLAG_LINE_COLOR);
        posTmp = ANALOG_START_Y;
        painter.drawLine(0,posTmp,lineNum,posTmp);      //模拟量中心线
        posTmp = (int)((pPos_Line->UDP_Pos*1000-Y_Min)/Y_Most*SCALE_HIGH_Y+SCALE_START_Y);
        painter.drawLine(0,posTmp,lineNum,posTmp);                      //上死点位置直线
        posTmp = (int)((pPos_Line->MUTE_Pos*1000-Y_Min)/Y_Most*SCALE_HIGH_Y+SCALE_START_Y);
        painter.drawLine(0,posTmp,lineNum,posTmp);                      //速度转换点位置直线
        posTmp = (int)((pPos_Line->CLAMP_Pos*1000-Y_Min)/Y_Most*SCALE_HIGH_Y+SCALE_START_Y);
        painter.drawLine(0,posTmp,lineNum,posTmp);                      //夹紧点位置直线
        posTmp = (int)((pPos_Line->ER_Pos*1000-Y_Min)/Y_Most*SCALE_HIGH_Y+SCALE_START_Y);
        painter.drawLine(0,posTmp,lineNum,posTmp);                      //泄荷点位置直线
        posTmp = (int)((pPos_Line->LDP_Pos*1000-Y_Min)/Y_Most*SCALE_HIGH_Y+SCALE_START_Y);
        painter.drawLine(0,posTmp,lineNum,posTmp);                      //下死点位置直线
        painter.setPen(QPen(DIVID_LINE_COLOR,3));           //第一条分隔线,线宽3
        painter.drawLine(0,0,lineNum,0);
        painter.drawLine(0,SCALE_HIGH,lineNum,SCALE_HIGH);            //第二条分隔线
        painter.drawLine(0,SCALE_HIGH+95,lineNum,SCALE_HIGH+95);       //第三条分隔线
        //绘制IO曲线
        for(int i = 0; i < 6; i++)
        outputY[i] = SCALE_HIGH+i*12+25;//scale_high 370
        painter.setPen(UDP_COLOR);
        painter.drawLine(0,outputY[0],lineNum,outputY[0]);
        painter.setPen(ER_COLOR);
        painter.drawLine(0,outputY[1],lineNum,outputY[1]);
        painter.setPen(MUTE1_COLOR);
        painter.drawLine(0,outputY[2],lineNum,outputY[2]);
        painter.setPen(MUTE2_COLOR);
        painter.drawLine(0,outputY[3],lineNum,outputY[3]);
        painter.setPen(CLAMP_COLOR);
        painter.drawLine(0,outputY[4],lineNum,outputY[4]);
        painter.setPen(LDP_COLOR);
        painter.drawLine(0,outputY[5],lineNum,outputY[5]);
        for(int i = 0; i < 4; i++)
            inputY[i] = SCALE_HIGH+120+i*12;
        painter.setPen(CLOSING_COLOR);
        painter.drawLine(0,inputY[0],lineNum,inputY[0]);
        painter.setPen(PRESSING_COLOR);
        painter.drawLine(0,inputY[1],lineNum,inputY[1]);
        painter.setPen(OPENING_COLOR);
        painter.drawLine(0,inputY[2],lineNum,inputY[2]);
        painter.setPen(TANDEM_COLOR);
        painter.drawLine(0,inputY[3],lineNum,inputY[3]);
    }
    if(pHeadDraw != NULL)
        pCurDraw = pHeadDraw;
    while (pCurDraw != NULL) {
        if(startX1 == curLineX)     //黄色坐标线的位置显示当前label值
        {
            pLabel[0]->setText(tr("左阀:  %1").arg(pCurDraw->leftvalue));
            pLabel[1]->setText(tr("右阀:  %1").arg(pCurDraw->rightvalue));
            pLabel[2]->setText(tr("压力:  %1").arg(pCurDraw->pressure));
            pLabel[3]->setText(tr("速度:  %1").arg(pCurDraw->speed/1000));
            pLabel[4]->setText(tr("Y1位置:  %1").arg(pCurDraw->leftposition/1000,0,'f',3));
            pLabel[5]->setText(tr("Y2位置:  %1").arg(pCurDraw->rightposition/1000,0,'f',3));
            pLabel[6]->setText(tr("X位置:  %1").arg(pCurDraw->Xposition/X_COUNT,0,'f',3));
            pLabel[7]->setText(tr("R位置:  %1").arg(pCurDraw->Rposition/R_COUNT,0,'f',3));
            pLabel[8]->setText(tr("X速度:  %1").arg(pCurDraw->x_speed/1000));
            pLabel[9]->setText(tr("R速度:  %1").arg(pCurDraw->r_speed/1000));
            pLabel[10]->setText(tr("状态:  %1").arg(pCurDraw->prestate));
            pLabel[11]->setText(tr("时间:  %1").arg(0.005*curLineX));
            //根据开关量的状态修改显示颜色
            QPalette styleNormal,styleTmp;
            styleNormal.setColor(QPalette::Background,QColor(230,230,230));//显示灰色
            styleTmp.setColor(QPalette::Background,UDP_COLOR);//显示各开关量相应的颜色
            if(pCurDraw->udp)
                pLabel[13]->setPalette(styleTmp);
            else
                pLabel[13]->setPalette(styleNormal);
            styleTmp.setColor(QPalette::Background,ER_COLOR);
            if(pCurDraw->er)
                pLabel[14]->setPalette(styleTmp);
            else
                pLabel[14]->setPalette(styleNormal);
            styleTmp.setColor(QPalette::Background,MUTE1_COLOR);
            if(pCurDraw->mute1)
                pLabel[15]->setPalette(styleTmp);
            else
                pLabel[15]->setPalette(styleNormal);
            styleTmp.setColor(QPalette::Background,MUTE2_COLOR);
            if(pCurDraw->mute2)
                pLabel[16]->setPalette(styleTmp);
            else
                pLabel[16]->setPalette(styleNormal);
            styleTmp.setColor(QPalette::Background,CLAMP_COLOR);
            if(pCurDraw->clamp)
                pLabel[17]->setPalette(styleTmp);
            else
                pLabel[17]->setPalette(styleNormal);
            styleTmp.setColor(QPalette::Background,LDP_COLOR);
            if(pCurDraw->ldp)
                pLabel[18]->setPalette(styleTmp);
            else
                pLabel[18]->setPalette(styleNormal);
            styleTmp.setColor(QPalette::Background,CLOSING_COLOR);
            if(pCurDraw->closing)
                pLabel[20]->setPalette(styleTmp);
            else
                pLabel[20]->setPalette(styleNormal);
            styleTmp.setColor(QPalette::Background,PRESSING_COLOR);
            if(pCurDraw->pressing)
                pLabel[21]->setPalette(styleTmp);
            else
                pLabel[21]->setPalette(styleNormal);
            styleTmp.setColor(QPalette::Background,OPENING_COLOR);
            if(pCurDraw->opening)
                pLabel[22]->setPalette(styleTmp);
            else
                pLabel[22]->setPalette(styleNormal);
            styleTmp.setColor(QPalette::Background,TANDEM_COLOR);
            if(pCurDraw->tandem)
                pLabel[23]->setPalette(styleTmp);
            else
                pLabel[23]->setPalette(styleNormal);
        }
        if(Anal_Differ == 1)        //滑块分析
        {
            //Y1_ANALOG
            painter.setPen(Y1_POS_COLOR);
            endX1 = 1+startX1;
            endY1 = (int)((-pCurDraw->leftvalue)/Ana_Max*35+ANALOG_START_Y);
            painter.drawLine(startX1,startY1,endX1,endY1);
            startX1 = endX1;
            startY1 = endY1;
            //Y2_ANALOG
            painter.setPen(Y2_POS_COLOR);
            endX2 = 1+startX2;
            endY2 = (int)((-pCurDraw->rightvalue)/Ana_Max*35+ANALOG_START_Y);
            painter.drawLine(startX2,startY2,endX2,endY2);
            startX2 = endX2;
            startY2 = endY2;
            //Press
            painter.setPen(PRESS_COLOR);
            endX3 = 1+startX3;
            endY3 = (int)((-pCurDraw->pressure)/Ana_Max*35+ANALOG_START_Y);
            painter.drawLine(startX3,startY3,endX3,endY3);
            startX3 = endX3;
            startY3 = endY3;
            //Y1_Pos
            painter.setPen(Y1_POS_COLOR);
            endX4 = 1+startX4;
            endY4 = (int)((pCurDraw->leftposition-Y_Min)/Y_Most*SCALE_HIGH_Y+SCALE_START_Y);
            painter.drawLine(startX4,startY4,endX4,endY4);
            startX4 = endX4;
            startY4 = endY4;
            //Y2_Pos
            painter.setPen(Y2_POS_COLOR);
            endX5 = 1+startX5;
            endY5 = (int)((pCurDraw->rightposition-Y_Min)/Y_Most*SCALE_HIGH_Y+SCALE_START_Y);
            painter.drawLine(startX5,startY5,endX5,endY5);
            startX5 = endX5;
            startY5 = endY5;
        }
        else        //挡料分析
        {
            //Y1_ANALOG
            painter.setPen(Y1_POS_COLOR);
            endX1 = 1+startX1;
            endY1 = ANALOG_START_Y;
            painter.drawLine(startX1,startY1,endX1,endY1);
            startX1 = endX1;
            startY1 = endY1;
            //Y2_ANALOG
            painter.setPen(Y2_POS_COLOR);
            endX2 = 1+startX2;
            endY2 = ANALOG_START_Y;
            painter.drawLine(startX2,startY2,endX2,endY2);
            startX2 = endX2;
            startY2 = endY2;
            //Press
            painter.setPen(PRESS_COLOR);
            endX3 = 1+startX3;
            endY3 = ANALOG_START_Y;
            painter.drawLine(startX3,startY3,endX3,endY3);
            startX3 = endX3;
            startY3 = endY3;
            //Y1_Pos
            painter.setPen(Y1_POS_COLOR);
            endX4 = 1+startX4;
            endY4 = SCALE_START_Y;
            painter.drawLine(startX4,startY4,endX4,endY4);
            startX4 = endX4;
            startY4 = endY4;
            //Y2_Pos
            painter.setPen(Y2_POS_COLOR);
            endX5 = 1+startX5;
            endY5 = SCALE_START_Y;
            painter.drawLine(startX5,startY5,endX5,endY5);
            startX5 = endX5;
            startY5 = endY5;
        }
        //X_Pos
        painter.setPen(X_POS_COLOR);
        endX6 = 1+startX6;
        endY6 = (int)((pCurDraw->Xposition-X_Min)/Xrange*Xscope+SCALE_START_X);
        painter.drawLine(startX6,startY6,endX6,endY6);
        startX6 = endX6;
        startY6 = endY6;
        //R_Pos
        painter.setPen(R_POS_COLOR);
        endX7 = 1+startX7;
        endY7 = (int)((pCurDraw->Rposition-R_Min)/Rrange*Rscope+SCALE_START_R);
        painter.drawLine(startX7,startY7,endX7,endY7);
        startX7 = endX7;
        startY7 = endY7;

        if(IO_Show)         //显示IO量
        {
            if(pCurDraw->udp)
            {
                painter.setPen(QPen(UDP_COLOR,7));//线粗为7
                painter.drawLine(startX1,outputY[0],startX1+1,outputY[0]);
            }
            if(pCurDraw->er)
            {
                painter.setPen(QPen(ER_COLOR,7));
                painter.drawLine(startX1,outputY[1],startX1+1,outputY[1]);
            }
            if(pCurDraw->mute1)
            {
                painter.setPen(QPen(MUTE1_COLOR,7));
                painter.drawLine(startX1,outputY[2],startX1+1,outputY[2]);
            }
            if(pCurDraw->mute2)
            {
                painter.setPen(QPen(MUTE2_COLOR,7));
                painter.drawLine(startX1,outputY[3],startX1+1,outputY[3]);
            }
            if(pCurDraw->clamp)
            {
                painter.setPen(QPen(CLAMP_COLOR,7));
                painter.drawLine(startX1,outputY[4],startX1+1,outputY[4]);
            }
            if(pCurDraw->ldp)
            {
                painter.setPen(QPen(LDP_COLOR,7));
                painter.drawLine(startX1,outputY[5],startX1+1,outputY[5]);
            }
            if(pCurDraw->closing)
            {
                painter.setPen(QPen(CLOSING_COLOR,7));
                painter.drawLine(startX1,inputY[0],startX1+1,inputY[0]);
            }
            if(pCurDraw->pressing)
            {
                painter.setPen(QPen(PRESSING_COLOR,7));
                painter.drawLine(startX1,inputY[1],startX1+1,inputY[1]);
            }
            if(pCurDraw->opening)
            {
                painter.setPen(QPen(OPENING_COLOR,7));
                painter.drawLine(startX1,inputY[2],startX1+1,inputY[2]);
            }
            if(pCurDraw->tandem)
            {
                painter.setPen(QPen(TANDEM_COLOR,7));
                painter.drawLine(startX1,inputY[3],startX1+1,inputY[3]);
            }
        }
        pCurDraw = pCurDraw->pNext;
    }
    painter.end();
    QPainter painterPixMap(this);
    painterPixMap.drawPixmap(destRect,*pixMap,sourceRect);//将pixmap中sourceRect大小的部分画到destrect中
    delete pixMap;
    return;
}

void Analyse::keyPressEvent(QKeyEvent *eKey)
{
    int iKey = eKey->key();
    switch (iKey) {
    case Key_F1:    //IO切换
    {
        if(IO_Show)
            IO_Show = false;
        else
            IO_Show = true;
        update();
        break;
    }

    case Key_Down:
    {
        zoom_Out();//缩小
        break;
    }
    case Key_Up:
    {
        zoom_In();//放大
        break;
    }
    case Key_Left:
    {
        lineXSpd = (int)(3/scaleX);
        if(lineXSpd < 2)
            lineXSpd = 2;
        curLineX -= lineXSpd;
        if(curLineX < 0)
            curLineX = 0;
        offsetX = -curLineX+(float)PIX_WIDTH/(2*scaleX);
        if(offsetX > 0)
            offsetX = 0;
        if(offsetX < (float)PIX_WIDTH/scaleX-lineNum)
            offsetX = (float)PIX_WIDTH/scaleX-lineNum;
        update();
        break;
    }
    case Key_Right:
    {
        lineXSpd = (int)(3/scaleX);
        if(lineXSpd < 2)
            lineXSpd = 2;
        curLineX += lineXSpd;
        if(curLineX > lineNum)
            curLineX = lineNum;
        offsetX = -curLineX+(float)PIX_WIDTH/(2*scaleX);
        if(offsetX > 0)
            offsetX = 0;
        if(offsetX < (float)PIX_WIDTH/scaleX-lineNum)
            offsetX = (float)PIX_WIDTH/scaleX-lineNum;
        update();
        break;
    }
    default:
        break;
    }
}

void Analyse::zoom_In()
{
    scaleX += (float)PIX_WIDTH/lineNum;
    if(Anal_Differ == 1)    //滑块分析
    {
        if(scaleX > 2)
            scaleX = 2;
    }
    else
    {
        if(scaleX > 10)
            scaleX = 10;
    }
    offsetX = -curLineX+(float)PIX_WIDTH/(2*scaleX);
    if(offsetX > 0)
        offsetX = 0;
    if(offsetX < (float)PIX_WIDTH/scaleX-lineNum)
        offsetX = (float)PIX_WIDTH/scaleX-lineNum;
    update();
}

void Analyse::zoom_Out()
{
    scaleX -= (float)PIX_WIDTH/lineNum;
    if(scaleX <= ((float)PIX_WIDTH/lineNum))
        scaleX = (float)PIX_WIDTH/lineNum;
    offsetX = -curLineX+(float)PIX_WIDTH/(2*scaleX);
    if(offsetX > 0)
        offsetX = 0;
    if(offsetX < (float)PIX_WIDTH/scaleX-lineNum)
        offsetX = (float)PIX_WIDTH/scaleX-lineNum;
    update();
}


