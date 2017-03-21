#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include"sysGlobal.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    filePath="E:/new_project/ShowWidget2/data_sourece"; //设置默认路径
    programWidget=NULL;
    PLC=NULL;
    analyse_show=NULL;
    machinedatabase=NULL;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *e)
{
    if(ishow)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("关闭");
        msgBox.setInformativeText("退出前是否保存文件?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No| QMessageBox::Cancel);
        msgBox.setButtonText (QMessageBox::Yes,QString("保存"));
        msgBox.setButtonText (QMessageBox::No,QString("不保存"));
        msgBox.setButtonText (QMessageBox::Cancel,QString("取消退出"));
        msgBox.setDefaultButton(QMessageBox::Yes);
        int ret = msgBox.exec();
        if(QMessageBox::Yes ==ret)
        {
            emit savefile();
       }
        else if(QMessageBox::Cancel ==ret)
        {
            e->ignore();
        }
        else
            return;
    }
    else
    {
        return;
    }
    return;
}

/********************************************
 *function:打开文件按钮的槽函数
 *input:无
 *output:无
 *adding:读取文件并显示出来
 *author: Wang
 *date: 2017-3-6 16:32:32
 *******************************************/
void MainWindow::on_Open_triggered()
{
    if(!ishow)
    {
    QFileDialog *fd = new QFileDialog(this);
    fd->setWindowTitle(tr("选择数据文件"));
    fd->setDirectory(filePath);             //选取默认路径
    QStringList filters;
    filters << "Datebase files (*.db)"
             << "Analytical curve files (*.txt)"
             << "Any files (*)";
    fd->setNameFilters(filters);//设置过滤条件

    if(fd->exec() == QDialog::Accepted)
    {
        ishow=true;
        QString path = fd->selectedFiles()[0];//获取完整路径和文件名称  有后缀
        int size = fd->directory().path().size()+1;//当前路径的长度
        relativePath=fd->directory().path();//获得相对路径   最后不带/
        int path_size = path.size();//完整路径和文件名称的长度
        fileName = path.right(path_size-size);//文件的名称
        ui->fileName_2->setText(fileName);
        QString filetype=path.right(2);
        ishow=true;

        /*分类型进行数据读取*/
        if("db"==filetype)
        {
            ui->fileType_2->setText("数据库(*.db)");
            if("programConstants.db"==fileName)
            {
                if(NULL==programWidget)
                {
                programWidget= new proggrameConstant(ui->widget);
                connect(this,SIGNAL(savefile()),programWidget,SLOT(savedatabase()));
                programWidget->show();
                }
            }
            if("machineconstants.db"==fileName)
            {
                if(NULL==machinedatabase)
                {
                machinedatabase=new MachineConst(ui->widget);
                connect(this,SIGNAL(savefile()),machinedatabase,SLOT(saveSlot()));
                machinedatabase->show();
                }
            }
        }
        else
        {
            if("plc_instruction_running.txt"==fileName || "plc_element_signification_running.txt"==fileName )
            {
            ui->fileType_2->setText("PLC (*.txt)");
            if(NULL==PLC)
            {
            PLC=new uiPlcEditor(ui->widget);
            PLC->show();
            PLC->setFocusPolicy(Qt::ClickFocus);
            connect(this,SIGNAL(savefile()),PLC,SLOT(SaveButtonSlot()));
            }
            }
            else//读取分析曲线文件
            {
                ui->fileType_2->setText("分析曲线 (*.txt)");
                 if(NULL==analyse_show)
                 {
                    analyse_show=new Analyse(ui->widget);
                    analyse_show->readFromFile(path);
                   analyse_show->show();
                   analyse_show->setFocusPolicy(Qt::ClickFocus);
                 }
            }
        }
    }
    delete fd;
    }
    else {
        QMessageBox::warning(this, tr("警告"),
                                         tr("请先关闭当前文件！"),
                                         QMessageBox::Ok  | QMessageBox::Cancel,
                                         QMessageBox::Ok );
    }
}

/********************************************
 *function:保存按钮的槽函数
 *input:无
 *output:无
 *adding:无
 *author: Wang
 *date: 2017-3-6 18:34:49
 *******************************************/
void MainWindow::on_pushButton_clicked()
{
    if(ishow)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("保存数据库");
        msgBox.setInformativeText("    确定保存修改?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel);
        msgBox.setButtonText (QMessageBox::Save,QString("确 定"));
        msgBox.setButtonText (QMessageBox::Cancel,QString("取 消"));
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();
        if(QMessageBox::Save ==ret)
            emit savefile();
        else
            return;
    }
    else
    {
       QMessageBox::warning(this, tr("警告"),
                                        tr("请先选择文件进行打开！"),
                                        QMessageBox::Ok  | QMessageBox::Cancel,
                                        QMessageBox::Ok );
    }
}

/********************************************
 *function:关闭按钮的槽函数
 *input:无
 *output:无
 *adding:无
 *author: Wang
 *date: 2017-3-11 9:26:50
 *******************************************/
void MainWindow::on_pushButton_2_clicked()
{
    if(true==ishow)
    {
         if(NULL!=programWidget)
         {
             delete programWidget;
             programWidget=NULL;
         }
         if(NULL!=machinedatabase)
         {
             delete machinedatabase;
             machinedatabase=NULL;
         }
         if(NULL!=PLC)
         {
             delete PLC;
             PLC=NULL;
         }
         if(NULL!=analyse_show)
         {
             delete analyse_show;
             analyse_show=NULL;
         }
         ishow=false;
    }

    else
    {
       QMessageBox::warning(this, tr("警告"),
                                        tr("请先选择文件进行打开！"),
                                        QMessageBox::Ok  | QMessageBox::Cancel,
                                       QMessageBox::Ok );
    }
    return;
}
