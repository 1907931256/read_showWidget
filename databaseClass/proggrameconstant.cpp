#include "proggrameconstant.h"
#include "ui_proggrameconstant.h"
#include"sysGlobal.h"
#include<QDebug>

proggrameConstant::proggrameConstant(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::proggrameConstant)
{
     ui->setupUi(this);
     setGeometry(0,0,parentWidget()->width(),parentWidget()->height());
     datapath=relativePath+"/programConstants.db";
     qDebug()<<datapath;
     loaddatabase();
     lineAndCombo();
}

proggrameConstant::~proggrameConstant()
{
    delete ui;
}

/********************************************
 *function:读取programConstants数据库中的数据
 *input:无
 *output:无
 *adding:无
 *author: Wang
 *date: 2017-3-6 15:19:08
 *******************************************/
bool proggrameConstant::loaddatabase()
{
    /*读取  总体*/
//    int nRow,nColumn;
    QString strSQL = "select name from global where id <= 4";
    QStringList strList = ReadSqlData(datapath,strSQL);
    if(strList.isEmpty())
    {
           QMessageBox box(QMessageBox::Warning,"警告","“总体”表文件为空！");
            box.setStandardButtons (QMessageBox::Ok|QMessageBox::Cancel);
            box.setButtonText (QMessageBox::Ok,QString("确 定"));
            box.setButtonText (QMessageBox::Cancel,QString("取 消"));
            box.exec ();
            return false;
    }
    ui->line1->setText(strList.at(0));
    ui->line2->setText(strList.at(1));
    ui->line3->setText(strList.at(2));
    ui->line4->setText(strList.at(3));
    strList.clear();

    /*读取  材料*/
    strSQL = "select name,sigma,Emodulus from material";
    strList = ReadSqlData(datapath,strSQL);
    if(strList.isEmpty())
    {
           QMessageBox box(QMessageBox::Warning,"警告","“材料”表文件为空！");
            box.setStandardButtons (QMessageBox::Ok|QMessageBox::Cancel);
            box.setButtonText (QMessageBox::Ok,QString("确 定"));
            box.setButtonText (QMessageBox::Cancel,QString("取 消"));
            box.exec ();
            return false;
    }
    ui->MaterialTable->setItem(0,0,new QTableWidgetItem(strList.at(0)));
    double num = strList.at(1).toDouble();
    QString strPara = QString("%1").arg(num,0,'f',2);
    ui->MaterialTable->setItem(0,1,new QTableWidgetItem(strPara));
    num = strList.at(2).toDouble();
    strPara = QString("%1").arg(num,0,'f',2);
    ui->MaterialTable->setItem(0,2,new QTableWidgetItem(strPara));

    ui->MaterialTable->setItem(1,0,new QTableWidgetItem(strList.at(3)));
    num = strList.at(4).toDouble();
    strPara = QString("%1").arg(num,0,'f',2);
    ui->MaterialTable->setItem(1,1,new QTableWidgetItem(strPara));
    num = strList.at(5).toDouble();
    strPara = QString("%1").arg(num,0,'f',2);
    ui->MaterialTable->setItem(1,2,new QTableWidgetItem(strPara));

    ui->MaterialTable->setItem(2,0,new QTableWidgetItem(strList.at(6)));
    num = strList.at(7).toDouble();
    strPara = QString("%1").arg(num,0,'f',2);
    ui->MaterialTable->setItem(2,1,new QTableWidgetItem(strPara));
    num = strList.at(8).toDouble();
    strPara = QString("%1").arg(num,0,'f',2);
    ui->MaterialTable->setItem(2,2,new QTableWidgetItem(strPara));

    ui->MaterialTable->setItem(3,0,new QTableWidgetItem(strList.at(9)));
    num = strList.at(10).toDouble();
    strPara = QString("%1").arg(num,0,'f',2);
    ui->MaterialTable->setItem(3,1,new QTableWidgetItem(strPara));
    num = strList.at(11).toDouble();
    strPara = QString("%1").arg(num,0,'f',2);
    ui->MaterialTable->setItem(3,2,new QTableWidgetItem(strPara));

    ui->MaterialTable->setItem(4,0,new QTableWidgetItem(strList.at(12)));
    num = strList.at(13).toDouble();
    strPara = QString("%1").arg(num,0,'f',2);
    ui->MaterialTable->setItem(4,1,new QTableWidgetItem(strPara));
    num = strList.at(14).toDouble();
    strPara = QString("%1").arg(num,0,'f',2);
    ui->MaterialTable->setItem(4,2,new QTableWidgetItem(strPara));

    ui->MaterialTable->setItem(5,0,new QTableWidgetItem(strList.at(15)));
    num = strList.at(16).toDouble();
    strPara = QString("%1").arg(num,0,'f',2);
    ui->MaterialTable->setItem(5,1,new QTableWidgetItem(strPara));
    num = strList.at(17).toDouble();
    strPara = QString("%1").arg(num,0,'f',2);
    ui->MaterialTable->setItem(5,2,new QTableWidgetItem(strPara));
    strList.clear();

    /*读取  编程常量*/
    strSQL = "select name from programset where id <= 9";
    strList = ReadSqlData(datapath,strSQL);
    if(strList.isEmpty())
     {
        QMessageBox box(QMessageBox::Warning,"警告","“编程常量”表文件为空！");
         box.setStandardButtons (QMessageBox::Ok|QMessageBox::Cancel);
         box.setButtonText (QMessageBox::Ok,QString("确 定"));
         box.setButtonText (QMessageBox::Cancel,QString("取 消"));
         box.exec ();
         return false;
     }
    ui->line5->setText(strList.at(0));
    ui->line6->setText(strList.at(1));
    ui->line7->setText(strList.at(2));
    ui->line8->setText(strList.at(3));
    ui->line9->setText(strList.at(4));
    ui->line10->setText(strList.at(5));
    ui->line11->setText(strList.at(6));
    ui->line12->setText(strList.at(7));
    ui->line13->setText(strList.at(8));
    strList.clear();

    /*读取  计算设置*/
    strSQL = "select name from countset where id <= 5";
    strList = ReadSqlData(datapath,strSQL);
    if(strList.isEmpty())
    {
         QMessageBox box(QMessageBox::Warning,"警告","“计算设置”表文件为空！");
          box.setStandardButtons (QMessageBox::Ok|QMessageBox::Cancel);
          box.setButtonText (QMessageBox::Ok,QString("确 定"));
          box.setButtonText (QMessageBox::Cancel,QString("取 消"));
          box.exec ();
          return false;
    }
    ui->line14->setText(strList.at(0));
    ui->line15->setText(strList.at(1));
    ui->line16->setText(strList.at(2));
    ui->line17->setText(strList.at(3));
    ui->line18->setText(strList.at(4));
    strList.clear();

    /*读取  产品设置*/
    strSQL = "select name from productset where id <= 12";
    strList = ReadSqlData(datapath,strSQL);
    if(strList.isEmpty())
    {
          QMessageBox box(QMessageBox::Warning,"警告","“产品设置”表文件为空！");
           box.setStandardButtons (QMessageBox::Ok|QMessageBox::Cancel);
           box.setButtonText (QMessageBox::Ok,QString("确 定"));
           box.setButtonText (QMessageBox::Cancel,QString("取 消"));
           box.exec ();
           return false;
    }
    ui->line19->setText(strList.at(0));
    ui->line20->setText(strList.at(1));
    ui->line21->setText(strList.at(2));
    ui->line22->setText(strList.at(3));
    ui->line23->setText(strList.at(4));
    ui->line24->setText(strList.at(5));
    ui->line25->setText(strList.at(6));
    ui->line26->setText(strList.at(7));
    ui->line27->setText(strList.at(8));
    ui->line28->setText(strList.at(9));
    ui->line29->setText(strList.at(10));
    ui->line30->setText(strList.at(11));
    strList.clear();

    /*读取  通讯端口*/
    strSQL = "select name from communicateset where id <= 3";
    strList = ReadSqlData(datapath,strSQL);
    if(strList.isEmpty())
    {
           QMessageBox box(QMessageBox::Warning,"警告","“通讯端口”表文件为空！");
            box.setStandardButtons (QMessageBox::Ok|QMessageBox::Cancel);
            box.setButtonText (QMessageBox::Ok,QString("确 定"));
            box.setButtonText (QMessageBox::Cancel,QString("取 消"));
            box.exec ();
            return false;
     }
    ui->line31->setText(strList.at(0));
    ui->line32->setText(strList.at(1));
    ui->line33->setText(strList.at(2));
    strList.clear();

    /*读取  生产用时*/
    strSQL = "select name from timecount where id <= 7";
    strList = ReadSqlData(datapath,strSQL);
    if(strList.isEmpty())
     {
            QMessageBox box(QMessageBox::Warning,"警告","“生产用时”表文件为空！");
             box.setStandardButtons (QMessageBox::Ok|QMessageBox::Cancel);
             box.setButtonText (QMessageBox::Ok,QString("确 定"));
             box.setButtonText (QMessageBox::Cancel,QString("取 消"));
             box.exec ();
             return false;
     }
     ui->line34->setText(strList.at(0));
     ui->line35->setText(strList.at(1));
     ui->line36->setText(strList.at(2));
     ui->line37->setText(strList.at(3));
     ui->line38->setText(strList.at(4));
     ui->line39->setText(strList.at(5));
     ui->line40->setText(strList.at(6));
     strList.clear();

     /*读取  后挡料几何尺寸*/
     strSQL = "select name from geometrysize where id <= 7";
     strList = ReadSqlData(datapath,strSQL);
     if(strList.isEmpty())
      {
             QMessageBox box(QMessageBox::Warning,"警告","“后挡料几何尺寸”表文件为空！");
              box.setStandardButtons (QMessageBox::Ok|QMessageBox::Cancel);
              box.setButtonText (QMessageBox::Ok,QString("确 定"));
              box.setButtonText (QMessageBox::Cancel,QString("取 消"));
              box.exec ();
              return false;
      }
     ui->line41->setText(strList.at(0));
     ui->line42->setText(strList.at(1));
     ui->line43->setText(strList.at(2));
     ui->line44->setText(strList.at(3));
//     ui->backsize->setPixmap(QPixmap(":/image/resource/gauge_one.bmp"));
     strList.clear();

     /*读取  维护*/
     strSQL = "select name from maintenance where id <= 2";
     strList = ReadSqlData(datapath,strSQL);
     if(strList.isEmpty())
      {
              QMessageBox box(QMessageBox::Warning,"警告","“维护”表文件为空！");
               box.setStandardButtons (QMessageBox::Ok|QMessageBox::Cancel);
               box.setButtonText (QMessageBox::Ok,QString("确 定"));
               box.setButtonText (QMessageBox::Cancel,QString("取 消"));
               box.exec ();
               return false;
      }
      ui->line45->setText(strList.at(0));
      ui->line46->setText(strList.at(1));
      strList.clear();

      /*读取  板料支撑尺寸*/
      strSQL = "select name from holdsize where id <= 3";
      strList = ReadSqlData(datapath,strSQL);
      if(strList.isEmpty())
      {
               QMessageBox box(QMessageBox::Warning,"警告","“板料支撑尺寸”表文件为空！");
                box.setStandardButtons (QMessageBox::Ok|QMessageBox::Cancel);
                box.setButtonText (QMessageBox::Ok,QString("确 定"));
                box.setButtonText (QMessageBox::Cancel,QString("取 消"));
                box.exec ();
                return false;
       }
       ui->line47->setText(strList.at(0));
       ui->line48->setText(strList.at(1));
       ui->line49->setText(strList.at(2));
       strList.clear();

       /*读取  机床侧轮廓*/
       strSQL = "select name from sideoutline where id <= 9";
       strList = ReadSqlData(datapath,strSQL);
       if(strList.isEmpty())
       {
                QMessageBox box(QMessageBox::Warning,"警告","“机床侧轮廓”表文件为空！");
                 box.setStandardButtons (QMessageBox::Ok|QMessageBox::Cancel);
                 box.setButtonText (QMessageBox::Ok,QString("确 定"));
                 box.setButtonText (QMessageBox::Cancel,QString("取 消"));
                 box.exec ();
                 return false;
       }
       ui->line50->setText(strList.at(0));
       ui->line51->setText(strList.at(1));
       ui->line52->setText(strList.at(2));
       ui->line53->setText(strList.at(3));
       ui->line54->setText(strList.at(4));
       ui->line55->setText(strList.at(5));
       ui->line56->setText(strList.at(6));
       ui->line57->setText(strList.at(7));
       ui->line58->setText(strList.at(8));
       ui->machinelabel->setPixmap(QPixmap(":/image/resource/bodystruct.bmp"));
       strList.clear();

      /*读取  其他参数*/
      strSQL = "select name from otherconstants where id <= 2";
      strList = ReadSqlData(datapath,strSQL);
      if(strList.isEmpty())
      {
          QMessageBox box(QMessageBox::Warning,"警告","“其他参数”表文件为空！");
          box.setStandardButtons (QMessageBox::Ok|QMessageBox::Cancel);
          box.setButtonText (QMessageBox::Ok,QString("确 定"));
          box.setButtonText (QMessageBox::Cancel,QString("取 消"));
          box.exec ();
           return false;
       }
      ui->line59->setText(strList.at(0));
      ui->line60->setText(strList.at(1));
      strList.clear();

      return true;
}

/********************************************
 *function:关联lineEdite和combo，建立一个映射关系
 *input:无
 *output:无
 *adding:
 *author: Wang
 *date: 2017-3-8 14:58:50
 *******************************************/
void proggrameConstant::lineAndCombo()
{
    /*关联  总体*/
    if("0"==ui->line1->text())
        ui->combo1->setCurrentIndex(0);
    if("1"==ui->line1->text())
        ui->combo1->setCurrentIndex(1);
    if("0"==ui->line2->text())
        ui->combo2->setCurrentIndex(0);
    if("1"==ui->line2->text())
        ui->combo2->setCurrentIndex(1);
    if("0"==ui->line3->text())
        ui->combo3->setCurrentIndex(0);
    if("0"==ui->line4->text())
        ui->combo4->setCurrentIndex(0);

    /*关联  编程设置*/
    if("0"==ui->line6->text())
        ui->combo5->setCurrentIndex(0);
    if("1"==ui->line6->text())
        ui->combo5->setCurrentIndex(1);
    if("0"==ui->line7->text())
        ui->combo6->setCurrentIndex(0);
    if("1"==ui->line7->text())
        ui->combo6->setCurrentIndex(1);
    if("1"==ui->line8->text())
        ui->combo7->setCurrentIndex(0);
    if("0"==ui->line9->text())
        ui->combo8->setCurrentIndex(0);
    if("1"==ui->line9->text())
        ui->combo8->setCurrentIndex(1);

     /*关联  计算设置*/
    if("0"==ui->line14->text())
        ui->combo9->setCurrentIndex(0);
    if("0"==ui->line15->text())
        ui->combo10->setCurrentIndex(0);
    if("1"==ui->line15->text())
        ui->combo10->setCurrentIndex(1);

     /*关联  产品设置*/
    if("0"==ui->line19->text())
        ui->combo11->setCurrentIndex(0);
    if("1"==ui->line19->text())
        ui->combo11->setCurrentIndex(1);
    if("0"==ui->line20->text())
        ui->combo12->setCurrentIndex(0);
    if("1"==ui->line20->text())
        ui->combo12->setCurrentIndex(1);

     /*关联  通讯*/
    if("1"==ui->line31->text())
        ui->combo13->setCurrentIndex(0);
    if("1"==ui->line32->text())
        ui->combo14->setCurrentIndex(0);

    /*关联  板料支撑尺寸*/
    if("0"==ui->line49->text())
        ui->combo15->setCurrentIndex(0);
    if("1"==ui->line49->text())
        ui->combo15->setCurrentIndex(1);
    if("2"==ui->line49->text())
        ui->combo15->setCurrentIndex(2);
    if("3"==ui->line49->text())
        ui->combo15->setCurrentIndex(3);

    /*关联  机床侧轮廓*/
    if("1"==ui->line50->text())
        ui->combo16->setCurrentIndex(0);
    if("2"==ui->line50->text())
        ui->combo16->setCurrentIndex(1);
    if("3"==ui->line50->text())
        ui->combo16->setCurrentIndex(2);
    if("4"==ui->line50->text())
        ui->combo16->setCurrentIndex(3);
    if("1"==ui->line51->text())
        ui->combo17->setCurrentIndex(0);
    if("2"==ui->line51->text())
        ui->combo17->setCurrentIndex(1);

      /*关联  其他参数*/
    if(""==ui->line59->text())
        ui->combo18->setCurrentIndex(0);
}

/********************************************
 *function:槽函数
 *input:无
 *output:无
 *adding:保存缓存在模型中的数据库
 *author: Wang
 *date: 2017-3-6 18:56:37
 *******************************************/
void proggrameConstant::savedatabase()
{
    QProgressDialog process(this);
    process.setWindowTitle(tr("保存"));
    process.setLabelText(tr("正在保存到数据库..."));
    process.setRange(0,100);//范围为0到100
    process.setModal(true);
    for(int i = 0;i <5;i++)
    {
        process.setValue(i);
    }

     QString tableName,columName,strData;
     int index;
     /*保存   总体*/
     tableName="global";
     columName="name";
     strData=ui->line1->text();
     index=0;
     UpdateSqlData(datapath,tableName,columName,index,strData);
     strData=ui->line2->text();
     index=1;
     UpdateSqlData(datapath,tableName,columName,index,strData);
     strData=ui->line3->text();
     index=2;
     UpdateSqlData(datapath,tableName,columName,index,strData);
     strData=ui->line4->text();
     index=3;
     UpdateSqlData(datapath,tableName,columName,index,strData);
     for(int i = 5;i <9;i++)
     {
         process.setValue(i);
     }

     /*保存   材料*/
    //保存第一列
     tableName="material";
     columName="name";
     strData=ui->MaterialTable->item(0,0)->text();
     index=0;
     UpdateSqlData(datapath,tableName,columName,index,strData);
     strData=ui->MaterialTable->item(1,0)->text();
     index=1;
     UpdateSqlData(datapath,tableName,columName,index,strData);
     strData=ui->MaterialTable->item(2,0)->text();
     index=2;
     UpdateSqlData(datapath,tableName,columName,index,strData);
     strData=ui->MaterialTable->item(3,0)->text();
     index=3;
     UpdateSqlData(datapath,tableName,columName,index,strData);
     strData=ui->MaterialTable->item(4,0)->text();
     index=4;
     UpdateSqlData(datapath,tableName,columName,index,strData);
     strData=ui->MaterialTable->item(5,0)->text();
     index=5;
     UpdateSqlData(datapath,tableName,columName,index,strData);
     //保存第二列
     columName="sigma";
     strData=ui->MaterialTable->item(0,1)->text();
     index=0;
     UpdateSqlData(datapath,tableName,columName,index,strData);
     strData=ui->MaterialTable->item(1,1)->text();
     index=1;
     UpdateSqlData(datapath,tableName,columName,index,strData);
     strData=ui->MaterialTable->item(2,1)->text();
     index=2;
     UpdateSqlData(datapath,tableName,columName,index,strData);
     strData=ui->MaterialTable->item(3,1)->text();
     index=3;
     UpdateSqlData(datapath,tableName,columName,index,strData);
     strData=ui->MaterialTable->item(4,1)->text();
     index=4;
     UpdateSqlData(datapath,tableName,columName,index,strData);
     strData=ui->MaterialTable->item(5,1)->text();
     index=5;
     UpdateSqlData(datapath,tableName,columName,index,strData);
     //保存第三列
     columName="Emodulus";
     strData=ui->MaterialTable->item(0,2)->text();
     index=0;
     UpdateSqlData(datapath,tableName,columName,index,strData);
     strData=ui->MaterialTable->item(1,2)->text();
     index=1;
     UpdateSqlData(datapath,tableName,columName,index,strData);
     strData=ui->MaterialTable->item(2,2)->text();
     index=2;
     UpdateSqlData(datapath,tableName,columName,index,strData);
     strData=ui->MaterialTable->item(3,2)->text();
     index=3;
     UpdateSqlData(datapath,tableName,columName,index,strData);
     strData=ui->MaterialTable->item(4,2)->text();
     index=4;
     UpdateSqlData(datapath,tableName,columName,index,strData);
     strData=ui->MaterialTable->item(5,2)->text();
     index=5;
     UpdateSqlData(datapath,tableName,columName,index,strData);
     for(int i = 9;i <20;i++)
     {
         process.setValue(i);
     }


     /*保存   编程设置*/
     tableName="programset";
     columName="name";
     strData=ui->line5->text();
     index=0;
     UpdateSqlData(datapath,tableName,columName,index,strData);
     strData=ui->line6->text();
     index=1;
     UpdateSqlData(datapath,tableName,columName,index,strData);
     strData=ui->line7->text();
     index=2;
     UpdateSqlData(datapath,tableName,columName,index,strData);
     strData=ui->line8->text();
     index=3;
     UpdateSqlData(datapath,tableName,columName,index,strData);
     strData=ui->line9->text();
     index=4;
     UpdateSqlData(datapath,tableName,columName,index,strData);
     strData=ui->line10->text();
     index=5;
     UpdateSqlData(datapath,tableName,columName,index,strData);
     strData=ui->line11->text();
     index=6;
     UpdateSqlData(datapath,tableName,columName,index,strData);
     strData=ui->line12->text();
     index=7;
     UpdateSqlData(datapath,tableName,columName,index,strData);
     strData=ui->line13->text();
     index=8;
     UpdateSqlData(datapath,tableName,columName,index,strData);
     for(int i = 20;i <28;i++)
     {
         process.setValue(i);
     }

     /*保存   计算设置*/
     tableName="countset";
     columName="name";
     strData=ui->line14->text();
     index=0;
     UpdateSqlData(datapath,tableName,columName,index,strData);
     strData=ui->line15->text();
     index=1;
     UpdateSqlData(datapath,tableName,columName,index,strData);
     strData=ui->line16->text();
     index=2;
     UpdateSqlData(datapath,tableName,columName,index,strData);
     strData=ui->line17->text();
     index=3;
     UpdateSqlData(datapath,tableName,columName,index,strData);
     strData=ui->line18->text();
     index=4;
     UpdateSqlData(datapath,tableName,columName,index,strData);
     for(int i = 28;i <36;i++)
     {
         process.setValue(i);
     }

     /*保存   产品设置*/
     tableName="productset";
     columName="name";
     strData=ui->line19->text();
     index=0;
     UpdateSqlData(datapath,tableName,columName,index,strData);
     strData=ui->line20->text();
     index=1;
     UpdateSqlData(datapath,tableName,columName,index,strData);
     strData=ui->line21->text();
     index=2;
     UpdateSqlData(datapath,tableName,columName,index,strData);
     strData=ui->line22->text();
     index=3;
     UpdateSqlData(datapath,tableName,columName,index,strData);
     strData=ui->line23->text();
     index=4;
     UpdateSqlData(datapath,tableName,columName,index,strData);
     strData=ui->line24->text();
     index=5;
     UpdateSqlData(datapath,tableName,columName,index,strData);
     strData=ui->line25->text();
     index=6;
     UpdateSqlData(datapath,tableName,columName,index,strData);
     strData=ui->line26->text();
     index=7;
     UpdateSqlData(datapath,tableName,columName,index,strData);
     strData=ui->line27->text();
     index=8;
     UpdateSqlData(datapath,tableName,columName,index,strData);
     strData=ui->line28->text();
     index=9;
     UpdateSqlData(datapath,tableName,columName,index,strData);
     strData=ui->line29->text();
     index=10;
     UpdateSqlData(datapath,tableName,columName,index,strData);
     strData=ui->line30->text();
     index=11;
     UpdateSqlData(datapath,tableName,columName,index,strData);
     for(int i = 36;i <44;i++)
     {
         process.setValue(i);
     }

     /*保存   通讯端口*/
     tableName="communicateset";
     columName="name";
     strData=ui->line31->text();
     index=0;
     UpdateSqlData(datapath,tableName,columName,index,strData);
     strData=ui->line32->text();
     index=1;
     UpdateSqlData(datapath,tableName,columName,index,strData);
     strData=ui->line33->text();
     index=2;
     UpdateSqlData(datapath,tableName,columName,index,strData);
     for(int i = 44;i <52;i++)
     {
         process.setValue(i);
     }

     /*保存   生产用时计算*/
     tableName="timecount";
     columName="name";
     strData=ui->line34->text();
     index=0;
     UpdateSqlData(datapath,tableName,columName,index,strData);
     strData=ui->line35->text();
     index=1;
     UpdateSqlData(datapath,tableName,columName,index,strData);
     strData=ui->line36->text();
     index=2;
     UpdateSqlData(datapath,tableName,columName,index,strData);
     strData=ui->line37->text();
     index=3;
     UpdateSqlData(datapath,tableName,columName,index,strData);
     strData=ui->line38->text();
     index=4;
     UpdateSqlData(datapath,tableName,columName,index,strData);
     strData=ui->line39->text();
     index=5;
     UpdateSqlData(datapath,tableName,columName,index,strData);
     strData=ui->line40->text();
     index=6;
     UpdateSqlData(datapath,tableName,columName,index,strData);
     for(int i = 52;i <60;i++)
     {
         process.setValue(i);
     }

     /*保存   后挡料几何尺寸*/
     tableName="geometrysize";
     columName="name";
     strData=ui->line41->text();
     index=0;
     UpdateSqlData(datapath,tableName,columName,index,strData);
     strData=ui->line42->text();
     index=1;
     UpdateSqlData(datapath,tableName,columName,index,strData);
     strData=ui->line43->text();
     index=2;
     UpdateSqlData(datapath,tableName,columName,index,strData);
     strData=ui->line44->text();
     index=3;
     UpdateSqlData(datapath,tableName,columName,index,strData);
     for(int i = 60;i <68;i++)
     {
         process.setValue(i);
     }

     /*保存   维护*/
     tableName="maintenance";
     columName="name";
     strData=ui->line45->text();
     index=0;
     UpdateSqlData(datapath,tableName,columName,index,strData);
     strData=ui->line46->text();
     index=1;
     UpdateSqlData(datapath,tableName,columName,index,strData);
     for(int i = 68;i <76;i++)
     {
         process.setValue(i);
     }

     /*保存   板料支撑尺寸*/
     tableName="holdsize";
     columName="name";
     strData=ui->line47->text();
     index=0;
     UpdateSqlData(datapath,tableName,columName,index,strData);
     strData=ui->line48->text();
     index=1;
     UpdateSqlData(datapath,tableName,columName,index,strData);
     strData=ui->line49->text();
     index=2;
     UpdateSqlData(datapath,tableName,columName,index,strData);
     for(int i = 76;i <84;i++)
     {
         process.setValue(i);
     }

     /*保存   机床侧轮廓*/
     tableName="sideoutline";
     columName="name";
     strData=ui->line50->text();
     index=0;
     UpdateSqlData(datapath,tableName,columName,index,strData);
     strData=ui->line51->text();
     index=1;
     UpdateSqlData(datapath,tableName,columName,index,strData);
     strData=ui->line52->text();
     index=2;
     UpdateSqlData(datapath,tableName,columName,index,strData);
     strData=ui->line53->text();
     index=3;
     UpdateSqlData(datapath,tableName,columName,index,strData);
     strData=ui->line54->text();
     index=4;
     UpdateSqlData(datapath,tableName,columName,index,strData);
     strData=ui->line55->text();
     index=5;
     UpdateSqlData(datapath,tableName,columName,index,strData);
     strData=ui->line56->text();
     index=6;
     UpdateSqlData(datapath,tableName,columName,index,strData);
     strData=ui->line57->text();
     index=7;
     UpdateSqlData(datapath,tableName,columName,index,strData);
     strData=ui->line58->text();
     index=8;
     UpdateSqlData(datapath,tableName,columName,index,strData);
     for(int i = 84;i <92;i++)
     {
         process.setValue(i);
     }

     /*保存   其他参数*/
     tableName="otherconstants";
     columName="name";
     strData=ui->line59->text();
     index=0;
     UpdateSqlData(datapath,tableName,columName,index,strData);
     strData=ui->line60->text();
     index=1;
     UpdateSqlData(datapath,tableName,columName,index,strData);
     for(int i = 92;i <100;i++)
     {
         process.setValue(i);
     }//进度条结束
}

void proggrameConstant::on_combo1_currentIndexChanged(int index)
{
    if(0==index)
        ui->line1->setText("0");
    if(1==index)
        ui->line1->setText("1");
}

void proggrameConstant::on_combo2_currentIndexChanged(int index)
{
    if(0==index)
        ui->line2->setText("0");
    if(1==index)
        ui->line2->setText("1");
}

void proggrameConstant::on_combo3_currentIndexChanged(int index)
{
    if(0==index)
        ui->line3->setText("0");
}

void proggrameConstant::on_combo4_currentIndexChanged(int index)
{
    if(0==index)
        ui->line4->setText("0");
}

void proggrameConstant::on_combo5_currentIndexChanged(int index)
{
    if(0==index)
        ui->line6->setText("0");
    if(1==index)
        ui->line6->setText("1");
}

void proggrameConstant::on_combo6_currentIndexChanged(int index)
{
    if(0==index)
        ui->line7->setText("0");
    if(1==index)
        ui->line7->setText("1");
}

void proggrameConstant::on_combo7_currentIndexChanged(int index)
{
    if(0==index)
        ui->line8->setText("1");
    if(1==index)
        ui->line8->setText("0");
}

void proggrameConstant::on_combo8_currentIndexChanged(int index)
{
    if(0==index)
        ui->line9->setText("0");
    if(1==index)
        ui->line9->setText("1");
}

void proggrameConstant::on_combo10_currentIndexChanged(int index)
{
    if(0==index)
        ui->line15->setText("0");
    if(1==index)
        ui->line15->setText("1");
}

void proggrameConstant::on_combo11_currentIndexChanged(int index)
{
    if(0==index)
        ui->line19->setText("0");
    if(1==index)
        ui->line19->setText("1");
}

void proggrameConstant::on_combo12_currentIndexChanged(int index)
{
    if(0==index)
        ui->line20->setText("0");
    if(1==index)
        ui->line20->setText("1");
}

void proggrameConstant::on_combo13_currentIndexChanged(int index)
{
    if(0==index)
        ui->line31->setText("1");
    if(1==index)
        ui->line31->setText("0");
}

void proggrameConstant::on_combo14_currentIndexChanged(int index)
{
    if(0==index)
        ui->line32->setText("1");
    if(1==index)
        ui->line32->setText("0");
}

void proggrameConstant::on_combo15_currentIndexChanged(int index)
{
    if(0==index)
        ui->line49->setText("0");
    if(1==index)
        ui->line49->setText("1");
    if(2==index)
        ui->line49->setText("2");
    if(3==index)
        ui->line49->setText("3");
}

void proggrameConstant::on_combo16_currentIndexChanged(int index)
{
    if(0==index)
        ui->line50->setText("1");
    if(1==index)
        ui->line50->setText("2");
    if(2==index)
        ui->line50->setText("3");
    if(3==index)
        ui->line50->setText("4");
}

void proggrameConstant::on_combo17_currentIndexChanged(int index)
{
    if(0==index)
        ui->line50->setText("1");
    if(1==index)
        ui->line50->setText("2");
}
