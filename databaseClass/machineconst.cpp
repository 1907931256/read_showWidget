#include "machineconst.h"
#include "ui_machineconst.h"
#include <QMessageBox>
#include <QCloseEvent>
#include <QAbstractItemView>
#include"sysGlobal.h"

MachineConst::MachineConst(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MachineConst)
{
    ui->setupUi(this);
    fileName = relativePath+ "/machineconstants.db";
    //总参数
    pLineEdit[0] = ui->lineEdit;
    pLineEdit[1] = ui->lineEdit_3;
    pLineEdit[2] = ui->lineEdit_4;
    pLineEdit[3] = ui->lineEdit_5;
    pLineEdit[4] = ui->lineEdit_6;
    pLineEdit[5] = ui->lineEdit_7;
    pLineEdit[6] = ui->lineEdit_8;
    pLineEdit[7] = ui->lineEdit_9;
    pLineEdit[8] = ui->lineEdit_10;
    pLineEdit[9] = ui->lineEdit_11;
    pLineEdit[10] = ui->lineEdit_12;
    pLineEdit[11] = ui->lineEdit_13;
    pLineEdit[12] = ui->lineEdit_14;
    //Y轴总体
    pLineEdit[13] = ui->lineEdit_15;
    pLineEdit[14] = ui->lineEdit_16;
    pLineEdit[15] = ui->lineEdit_17;
    pLineEdit[16] = ui->lineEdit_18;
    pLineEdit[17] = ui->lineEdit_19;
    pLineEdit[18] = ui->lineEdit_20;
    pLineEdit[19] = ui->lineEdit_27;
    pLineEdit[20] = ui->lineEdit_28;
    pLineEdit[21] = ui->lineEdit_29;
    pLineEdit[22] = ui->lineEdit_30;
    pLineEdit[23] = ui->lineEdit_31;
    //Y轴反馈
    pLineEdit[24] = ui->lineEdit_32;
    pLineEdit[25] = ui->lineEdit_33;
    pLineEdit[26] = ui->lineEdit_34;
    pLineEdit[27] = ui->lineEdit_35;
    //Y轴压力阀
    pLineEdit[28] = ui->lineEdit_36;
    pLineEdit[29] = ui->lineEdit_37;
    pLineEdit[30] = ui->lineEdit_38;
    pLineEdit[31] = ui->lineEdit_39;
    pLineEdit[32] = ui->lineEdit_40;
    pLineEdit[33] = ui->lineEdit_41;
    pLineEdit[34] = ui->lineEdit_42;
    pLineEdit[35] = ui->lineEdit_43;
    pLineEdit[36] = ui->lineEdit_44;
    //Y轴快下
    pLineEdit[37] = ui->lineEdit_45;
    pLineEdit[38] = ui->lineEdit_46;
    pLineEdit[39] = ui->lineEdit_47;
    pLineEdit[40] = ui->lineEdit_48;
    pLineEdit[41] = ui->lineEdit_49;
    pLineEdit[42] = ui->lineEdit_50;
    pLineEdit[43] = ui->lineEdit_51;
    pLineEdit[44] = ui->lineEdit_52;
    //Y轴工进
    pLineEdit[45] = ui->lineEdit_85;
    pLineEdit[46] = ui->lineEdit_86;
    pLineEdit[47] = ui->lineEdit_87;
    pLineEdit[48] = ui->lineEdit_88;
    pLineEdit[49] = ui->lineEdit_89;
    pLineEdit[50] = ui->lineEdit_90;
    pLineEdit[51] = ui->lineEdit_91;
    pLineEdit[52] = ui->lineEdit_92;
    //Y轴保压
    pLineEdit[53] = ui->lineEdit_93;
    pLineEdit[54] = ui->lineEdit_94;
    pLineEdit[55] = ui->lineEdit_95;
    pLineEdit[56] = ui->lineEdit_96;
    pLineEdit[57] = ui->lineEdit_97;
    //Y轴回程
    pLineEdit[58] = ui->lineEdit_98;
    pLineEdit[59] = ui->lineEdit_99;
    pLineEdit[60] = ui->lineEdit_100;
    pLineEdit[61] = ui->lineEdit_101;
    pLineEdit[62] = ui->lineEdit_102;
    pLineEdit[63] = ui->lineEdit_103;
    pLineEdit[64] = ui->lineEdit_104;
    pLineEdit[65] = ui->lineEdit_105;
    pLineEdit[66] = ui->lineEdit_106;
    //X轴总体
    pLineEdit[67] = ui->lineEdit_2;
    pLineEdit[68] = ui->lineEdit_21;
    pLineEdit[69] = ui->lineEdit_22;
    pLineEdit[70] = ui->lineEdit_23;
    pLineEdit[71] = ui->lineEdit_24;
    pLineEdit[72] = ui->lineEdit_25;
    pLineEdit[73] = ui->lineEdit_26;
    pLineEdit[74] = ui->lineEdit_53;
    pLineEdit[75] = ui->lineEdit_54;
    //X轴反馈
    pLineEdit[76] = ui->lineEdit_55;
    pLineEdit[77] = ui->lineEdit_56;
    pLineEdit[78] = ui->lineEdit_57;
    pLineEdit[79] = ui->lineEdit_58;
    //X轴控制
    pLineEdit[80] = ui->lineEdit_72;
    pLineEdit[81] = ui->lineEdit_73;
    pLineEdit[82] = ui->lineEdit_74;
    pLineEdit[83] = ui->lineEdit_75;
    pLineEdit[84] = ui->lineEdit_76;
    pLineEdit[85] = ui->lineEdit_77;
    pLineEdit[86] = ui->lineEdit_78;
    //X轴安全
    pLineEdit[87] = ui->lineEdit_79;
    pLineEdit[88] = ui->lineEdit_80;
    pLineEdit[89] = ui->lineEdit_81;
    //R轴总体
    pLineEdit[90] = ui->lineEdit_82;
    pLineEdit[91] = ui->lineEdit_83;
    pLineEdit[92] = ui->lineEdit_84;
    pLineEdit[93] = ui->lineEdit_107;
    pLineEdit[94] = ui->lineEdit_108;
    pLineEdit[95] = ui->lineEdit_109;
    pLineEdit[96] = ui->lineEdit_110;
    pLineEdit[97] = ui->lineEdit_111;
    //R轴反馈
    pLineEdit[98] = ui->lineEdit_112;
    pLineEdit[99] = ui->lineEdit_113;
    pLineEdit[100] = ui->lineEdit_114;
    pLineEdit[101] = ui->lineEdit_115;
    //R轴控制
    pLineEdit[102] = ui->lineEdit_116;
    pLineEdit[103] = ui->lineEdit_117;
    pLineEdit[104] = ui->lineEdit_118;
    pLineEdit[105] = ui->lineEdit_119;
    //W轴
    pLineEdit[106] = ui->lineEdit_120;
    pLineEdit[107] = ui->lineEdit_121;
    pLineEdit[108] = ui->lineEdit_122;
    pLineEdit[109] = ui->lineEdit_123;
    pLineEdit[110] = ui->lineEdit_124;
    pLineEdit[111] = ui->lineEdit_125;
    pLineEdit[112] = ui->lineEdit_126;
    pLineEdit[113] = ui->lineEdit_127;
    insertData();
}

MachineConst::~MachineConst()
{
    delete ui;
}

int MachineConst::insertData()
{

    //读取机床总参数
    tableName = "General";
    str = ReadSqlData(fileName,tableName,0,1);
    ui->lineEdit->setText(str);
    ui->comboBox->setCurrentIndex(str.toInt());

    str = ReadSqlData(fileName,tableName,1,1);
    ui->lineEdit_3->setText(str);
    ui->comboBox_3->setCurrentIndex(str.toInt());

    str = ReadSqlData(fileName,tableName,2,1);
    ui->lineEdit_4->setText(str);
    ui->comboBox_4->setCurrentIndex(str.toInt());

    str = ReadSqlData(fileName,tableName,3,1);
    ui->lineEdit_5->setText(str);
    ui->comboBox_5->setCurrentIndex(str.toInt());

    str = ReadSqlData(fileName,tableName,4,1);
    ui->lineEdit_6->setText(str);

    str = ReadSqlData(fileName,tableName,5,1);
    ui->lineEdit_7->setText(str);

    str = ReadSqlData(fileName,tableName,6,1);
    ui->lineEdit_8->setText(str);

    str = ReadSqlData(fileName,tableName,7,1);
    ui->lineEdit_9->setText(str);

    str = ReadSqlData(fileName,tableName,8,1);
    ui->lineEdit_10->setText(str);

    str = ReadSqlData(fileName,tableName,9,1);
    ui->lineEdit_11->setText(str);

    str = ReadSqlData(fileName,tableName,10,1);
    ui->lineEdit_12->setText(str);

    str = ReadSqlData(fileName,tableName,11,1);
    ui->lineEdit_13->setText(str);

    str = ReadSqlData(fileName,tableName,12,1);
    ui->lineEdit_14->setText(str);
    ui->comboBox_6->setCurrentIndex(str.toInt());

    //Y轴参数 总体
    tableName = "YAxis";
    str = ReadSqlData(fileName,tableName,0,1);
    ui->lineEdit_15->setText(str);

    str = ReadSqlData(fileName,tableName,1,1);
    ui->lineEdit_16->setText(str);

    str = ReadSqlData(fileName,tableName,2,1);
    ui->lineEdit_17->setText(str);
    ui->comboBox_7->setCurrentIndex(str.toInt());

    str = ReadSqlData(fileName,tableName,3,1);
    ui->lineEdit_18->setText(str);

    str = ReadSqlData(fileName,tableName,4,1);
    ui->lineEdit_19->setText(str);

    str = ReadSqlData(fileName,tableName,5,1);
    ui->lineEdit_20->setText(str);

    str = ReadSqlData(fileName,tableName,6,1);
    ui->lineEdit_27->setText(str);

    str = ReadSqlData(fileName,tableName,7,1);
    ui->lineEdit_28->setText(str);

    str = ReadSqlData(fileName,tableName,8,1);
    ui->lineEdit_29->setText(str);

    str = ReadSqlData(fileName,tableName,9,1);
    ui->lineEdit_30->setText(str);

    str = ReadSqlData(fileName,tableName,10,1);
    ui->lineEdit_31->setText(str);

    //Y轴 反馈

    str = ReadSqlData(fileName,tableName,12,1);
    ui->lineEdit_32->setText(str);

    str = ReadSqlData(fileName,tableName,13,1);
    ui->lineEdit_33->setText(str);

    str = ReadSqlData(fileName,tableName,14,1);
    ui->lineEdit_34->setText(str);
    ui->comboBox_8->setCurrentIndex(str.toInt());

    str = ReadSqlData(fileName,tableName,15,1);
    ui->lineEdit_35->setText(str);
    ui->comboBox_9->setCurrentIndex(str.toInt());

    //Y轴 压力阀
    str = ReadSqlData(fileName,tableName,24,1);
    ui->lineEdit_36->setText(str);

    str = ReadSqlData(fileName,tableName,25,1);
    ui->lineEdit_37->setText(str);

    str = ReadSqlData(fileName,tableName,26,1);
    ui->lineEdit_38->setText(str);

    str = ReadSqlData(fileName,tableName,27,1);
    ui->lineEdit_39->setText(str);

    str = ReadSqlData(fileName,tableName,28,1);
    ui->lineEdit_40->setText(str);

    str = ReadSqlData(fileName,tableName,29,1);
    ui->lineEdit_41->setText(str);

    str = ReadSqlData(fileName,tableName,30,1);
    ui->lineEdit_42->setText(str);

    str = ReadSqlData(fileName,tableName,31,1);
    ui->lineEdit_43->setText(str);

    str = ReadSqlData(fileName,tableName,32,1);
    ui->lineEdit_44->setText(str);
    ui->comboBox_10->setCurrentIndex(str.toInt());

    //Y轴 快下
    str = ReadSqlData(fileName,tableName,36,1);
    ui->lineEdit_45->setText(str);

    str = ReadSqlData(fileName,tableName,37,1);
    ui->lineEdit_46->setText(str);

    str = ReadSqlData(fileName,tableName,38,1);
    ui->lineEdit_47->setText(str);

    str = ReadSqlData(fileName,tableName,39,1);
    ui->lineEdit_48->setText(str);

    str = ReadSqlData(fileName,tableName,40,1);
    ui->lineEdit_49->setText(str);

    str = ReadSqlData(fileName,tableName,41,1);
    ui->lineEdit_50->setText(str);

    str = ReadSqlData(fileName,tableName,42,1);
    ui->lineEdit_51->setText(str);

    str = ReadSqlData(fileName,tableName,43,1);
    ui->lineEdit_52->setText(str);

    //Y轴 工进

    str = ReadSqlData(fileName,tableName,48,1);
    ui->lineEdit_85->setText(str);

    str = ReadSqlData(fileName,tableName,49,1);
    ui->lineEdit_86->setText(str);

    str = ReadSqlData(fileName,tableName,50,1);
    ui->lineEdit_87->setText(str);

    str = ReadSqlData(fileName,tableName,51,1);
    ui->lineEdit_88->setText(str);

    str = ReadSqlData(fileName,tableName,52,1);
    ui->lineEdit_89->setText(str);

    str = ReadSqlData(fileName,tableName,53,1);
    ui->lineEdit_90->setText(str);

    str = ReadSqlData(fileName,tableName,54,1);
    ui->lineEdit_91->setText(str);

    str = ReadSqlData(fileName,tableName,55,1);
    ui->lineEdit_92->setText(str);

    //Y轴 保压
    str = ReadSqlData(fileName,tableName,60,1);
    ui->lineEdit_93->setText(str);

    str = ReadSqlData(fileName,tableName,61,1);
    ui->lineEdit_94->setText(str);

    str = ReadSqlData(fileName,tableName,62,1);
    ui->lineEdit_95->setText(str);

    str = ReadSqlData(fileName,tableName,63,1);
    ui->lineEdit_96->setText(str);

    str = ReadSqlData(fileName,tableName,64,1);
    ui->lineEdit_97->setText(str);

    //Y轴 回程
    str = ReadSqlData(fileName,tableName,72,1);
    ui->lineEdit_98->setText(str);

    str = ReadSqlData(fileName,tableName,73,1);
    ui->lineEdit_99->setText(str);

    str = ReadSqlData(fileName,tableName,74,1);
    ui->lineEdit_100->setText(str);

    str = ReadSqlData(fileName,tableName,75,1);
    ui->lineEdit_101->setText(str);

    str = ReadSqlData(fileName,tableName,76,1);
    ui->lineEdit_102->setText(str);

    str = ReadSqlData(fileName,tableName,77,1);
    ui->lineEdit_103->setText(str);

    str = ReadSqlData(fileName,tableName,78,1);
    ui->lineEdit_104->setText(str);

    str = ReadSqlData(fileName,tableName,79,1);
    ui->lineEdit_105->setText(str);

    str = ReadSqlData(fileName,tableName,80,1);
    ui->lineEdit_106->setText(str);

    //辅助轴

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableName = "AuxiliaryAxis";
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<5;j++)
        {
            str = ReadSqlData(fileName,tableName,i,j+1);
            ui->tableWidget->setItem(i,j,new QTableWidgetItem(str));
        }
    }

    //X轴 总体
    tableName = "XAxis";
    str = ReadSqlData(fileName,tableName,0,1);
    ui->lineEdit_2->setText(str);

    str = ReadSqlData(fileName,tableName,1,1);
    ui->lineEdit_21->setText(str);

    str = ReadSqlData(fileName,tableName,2,1);
    ui->lineEdit_22->setText(str);

    str = ReadSqlData(fileName,tableName,3,1);
    ui->lineEdit_23->setText(str);

    str = ReadSqlData(fileName,tableName,4,1);
    ui->lineEdit_24->setText(str);

    str = ReadSqlData(fileName,tableName,5,1);
    ui->lineEdit_25->setText(str);
    ui->comboBox_2->setCurrentIndex(str.toInt());

    str = ReadSqlData(fileName,tableName,6,1);
    ui->lineEdit_26->setText(str);
    ui->comboBox_11->setCurrentIndex(str.toInt());

    str = ReadSqlData(fileName,tableName,7,1);
    ui->lineEdit_53->setText(str);

    str = ReadSqlData(fileName,tableName,8,1);
    ui->lineEdit_54->setText(str);

    //X轴 反馈
    str = ReadSqlData(fileName,tableName,12,1);
    ui->lineEdit_55->setText(str);

    str = ReadSqlData(fileName,tableName,13,1);
    ui->lineEdit_56->setText(str);

    str = ReadSqlData(fileName,tableName,14,1);
    ui->lineEdit_57->setText(str);

    str = ReadSqlData(fileName,tableName,15,1);
    ui->lineEdit_58->setText(str);
    ui->comboBox_12->setCurrentIndex(str.toInt());

    //X轴 控制

    str = ReadSqlData(fileName,tableName,24,1);
    ui->lineEdit_72->setText(str);

    str = ReadSqlData(fileName,tableName,25,1);
    ui->lineEdit_73->setText(str);

    str = ReadSqlData(fileName,tableName,26,1);
    ui->lineEdit_74->setText(str);

    str = ReadSqlData(fileName,tableName,27,1);
    ui->lineEdit_75->setText(str);

    str = ReadSqlData(fileName,tableName,28,1);
    ui->lineEdit_76->setText(str);

    str = ReadSqlData(fileName,tableName,29,1);
    ui->lineEdit_77->setText(str);

    str = ReadSqlData(fileName,tableName,30,1);
    ui->lineEdit_78->setText(str);
    ui->comboBox_16->setCurrentIndex(str.toInt());

    //X轴 安全
    str = ReadSqlData(fileName,tableName,36,1);
    ui->lineEdit_79->setText(str);
    ui->comboBox_17->setCurrentIndex(str.toInt());

    str = ReadSqlData(fileName,tableName,37,1);
    ui->lineEdit_80->setText(str);

    str = ReadSqlData(fileName,tableName,38,1);
    ui->lineEdit_81->setText(str);

    //X轴 挡指补偿表格
    ui->tableWidget_3->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableName = "XCTable";
    for(int i=0;i<1;i++)
    {
        for(int j=0;j<2;j++)
        {
            str = ReadSqlData(fileName,tableName,i,j+1);
            ui->tableWidget_3->setItem(i,j,new QTableWidgetItem(str));
        }
    }

    //R轴 总体
    tableName = "RAxis";
    str = ReadSqlData(fileName,tableName,0,1);
    ui->lineEdit_82->setText(str);

    str = ReadSqlData(fileName,tableName,1,1);
    ui->lineEdit_83->setText(str);

    str = ReadSqlData(fileName,tableName,2,1);
    ui->lineEdit_84->setText(str);

    str = ReadSqlData(fileName,tableName,3,1);
    ui->lineEdit_107->setText(str);

    str = ReadSqlData(fileName,tableName,4,1);
    ui->lineEdit_108->setText(str);
    ui->comboBox_18->setCurrentIndex(str.toInt());

    str = ReadSqlData(fileName,tableName,5,1);
    ui->lineEdit_109->setText(str);
    ui->comboBox_19->setCurrentIndex(str.toInt());

    str = ReadSqlData(fileName,tableName,6,1);
    ui->lineEdit_110->setText(str);

    str = ReadSqlData(fileName,tableName,7,1);
    ui->lineEdit_111->setText(str);

    //R轴 反馈
    str = ReadSqlData(fileName,tableName,12,1);
    ui->lineEdit_112->setText(str);

    str = ReadSqlData(fileName,tableName,13,1);
    ui->lineEdit_113->setText(str);

    str = ReadSqlData(fileName,tableName,14,1);
    ui->lineEdit_114->setText(str);

    str = ReadSqlData(fileName,tableName,15,1);
    ui->lineEdit_115->setText(str);
    ui->comboBox_20->setCurrentIndex(str.toInt());

    //R轴 控制
    str = ReadSqlData(fileName,tableName,24,1);
    ui->lineEdit_116->setText(str);

    str = ReadSqlData(fileName,tableName,25,1);
    ui->lineEdit_117->setText(str);

    str = ReadSqlData(fileName,tableName,26,1);
    ui->lineEdit_118->setText(str);

    str = ReadSqlData(fileName,tableName,27,1);
    ui->lineEdit_119->setText(str);

    //W轴
    tableName = "WAxis";
    str = ReadSqlData(fileName,tableName,0,1);
    ui->lineEdit_120->setText(str);
    ui->comboBox_21->setCurrentIndex(str.toInt());

    str = ReadSqlData(fileName,tableName,1,1);
    ui->lineEdit_121->setText(str);

    str = ReadSqlData(fileName,tableName,2,1);
    ui->lineEdit_122->setText(str);

    str = ReadSqlData(fileName,tableName,3,1);
    ui->lineEdit_123->setText(str);

    str = ReadSqlData(fileName,tableName,4,1);
    ui->lineEdit_124->setText(str);
    ui->comboBox_25->setCurrentIndex(str.toInt());

    str = ReadSqlData(fileName,tableName,5,1);
    ui->lineEdit_125->setText(str);

    str = ReadSqlData(fileName,tableName,6,1);
    ui->lineEdit_126->setText(str);

    str = ReadSqlData(fileName,tableName,7,1);
    ui->lineEdit_127->setText(str);
    ui->comboBox_28->setCurrentIndex(str.toInt());

    //密码
    tableName = "Password";
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<2;j++)
        {
            str = ReadSqlData(fileName,tableName,i,j+1);
            ui->tableWidget_2->setItem(i,j,new QTableWidgetItem(str));
        }
    }
    //诊断数据
    tableName = "DiagnoseData";
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<2;j++)
        {
            str = ReadSqlData(fileName,tableName,i,j+1);
            ui->tableWidget_4->setItem(i,j,new QTableWidgetItem(str));
        }
    }
    //DA输出
    tableName = "DAoutput";
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<2;j++)
        {
            str = ReadSqlData(fileName,tableName,i,j+1);
            ui->tableWidget_5->setItem(i,j,new QTableWidgetItem(str));
        }
    }
}


void MachineConst::on_tableWidget_doubleClicked(const QModelIndex &index)
{
    switch(index.row())
    {
        case 0:
            ui->tabWidget->setCurrentIndex(6);
            break;
        case 1:
            ui->tabWidget->setCurrentIndex(7);
            break;
        case 2:
            ui->tabWidget->setCurrentIndex(8);
            break;
        default:
            break;
    }
}

void MachineConst::saveSlot()
{
    updateData(ui->tabWidget->currentIndex());
}

void MachineConst::updateData(int num1)
{
    switch(num1)
    {
        case 0:
        {
            for(int i=0;i<13;i++)
            UpdateSqlData(fileName,"General","name",i,pLineEdit[i]->text());
            break;
        }
        case 1:
        {
             for(int i=0;i<11;i++)
             UpdateSqlData(fileName,"YAxis","name",i,pLineEdit[i+13]->text());

             for(int i=0;i<4;i++)
             UpdateSqlData(fileName,"YAxis","name",i+12,pLineEdit[i+24]->text());

             for(int i=0;i<9;i++)
             UpdateSqlData(fileName,"YAxis","name",i+24,pLineEdit[i+28]->text());

             for(int i=0;i<8;i++)
             UpdateSqlData(fileName,"YAxis","name",i+36,pLineEdit[i+37]->text());

             for(int i=0;i<8;i++)
             UpdateSqlData(fileName,"YAxis","name",i+48,pLineEdit[i+45]->text());

             for(int i=0;i<5;i++)
             UpdateSqlData(fileName,"YAxis","name",i+60,pLineEdit[i+53]->text());

             for(int i=0;i<9;i++)
             UpdateSqlData(fileName,"YAxis","name",i+72,pLineEdit[i+58]->text());
             break;
        }
    case 6:
    {
         for(int i=0;i<9;i++)
         UpdateSqlData(fileName,"XAxis","name",i,pLineEdit[i+67]->text());

         for(int i=0;i<4;i++)
         UpdateSqlData(fileName,"XAxis","name",i+12,pLineEdit[i+76]->text());

         for(int i=0;i<7;i++)
         UpdateSqlData(fileName,"XAxis","name",i+24,pLineEdit[i+80]->text());

         for(int i=0;i<3;i++)
         UpdateSqlData(fileName,"XAxis","name",i+36,pLineEdit[i+87]->text());
         break;
    }
    case 7:
    {
         for(int i=0;i<8;i++)
         UpdateSqlData(fileName,"RAxis","name",i,pLineEdit[i+90]->text());

         for(int i=0;i<4;i++)
         UpdateSqlData(fileName,"RAxis","name",i+12,pLineEdit[i+98]->text());

         for(int i=0;i<4;i++)
         UpdateSqlData(fileName,"RAxis","name",i+24,pLineEdit[i+102]->text());
         break;
    }
    case 8:
    {
         for(int i=0;i<8;i++)
         UpdateSqlData(fileName,"WAxis","name",i,pLineEdit[i+106]->text());
         break;
    }
        default:
            break;
    }

}
