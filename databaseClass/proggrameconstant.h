#ifndef PROGGRAMECONSTANT_H
#define PROGGRAMECONSTANT_H

#include <QWidget>
#include <QStringList>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QTableView>
#include<QDebug>
#include<QAbstractItemView>
#include<QMessageBox>
#include <QTableWidgetItem>
#include"globalFunction.h"
#include<QProgressDialog>

namespace Ui {
class proggrameConstant;
}

class proggrameConstant : public QWidget
{
    Q_OBJECT

public:
    explicit proggrameConstant(QWidget *parent = 0);
    ~proggrameConstant();

    bool loaddatabase();
    void lineAndCombo();

private:
    Ui::proggrameConstant * ui;
    QString datapath;//数据库路径

private slots:
    void on_combo1_currentIndexChanged(int index);
    void on_combo2_currentIndexChanged(int index);
    void on_combo3_currentIndexChanged(int index);
    void on_combo4_currentIndexChanged(int index);
    void on_combo5_currentIndexChanged(int index);
    void on_combo6_currentIndexChanged(int index);
    void on_combo7_currentIndexChanged(int index);
    void on_combo8_currentIndexChanged(int index);
    void on_combo10_currentIndexChanged(int index);
    void on_combo11_currentIndexChanged(int index);
    void on_combo12_currentIndexChanged(int index);
    void on_combo13_currentIndexChanged(int index);
    void on_combo14_currentIndexChanged(int index);
    void on_combo15_currentIndexChanged(int index);
    void on_combo16_currentIndexChanged(int index);
    void on_combo17_currentIndexChanged(int index);

public slots:
    void savedatabase();
};

#endif // PROGGRAMECONSTANT_H
