#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QDebug>
#include <QStringList>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QTableView>
#include<QMessageBox>
#include <QCloseEvent>
#include"sysGlobal.h"
#include"proggrameconstant.h"
#include "uiPlcEditor.h"
#include"SysKeyboard.h"
#include"analysis/analyse.h"
#include "machineconst.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();



 signals:
    void savefile();


private slots:
    void on_Open_triggered();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    QString filePath;
    QString fileName;
    proggrameConstant  *programWidget;
    uiPlcEditor *PLC;
    Analyse* analyse_show;
    MachineConst* machinedatabase;


    void closeEvent(QCloseEvent *e);


};

#endif // MAINWINDOW_H
