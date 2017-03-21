#ifndef MACHINECONST_H
#define MACHINECONST_H

#include <QWidget>
#include <QTableWidget>
#include <QLineEdit>
#include "globalFunction.h"

namespace Ui {
class MachineConst;
}

class MachineConst : public QWidget
{
    Q_OBJECT

public:
    explicit MachineConst(QWidget *parent = 0);
    ~MachineConst();

private:
    Ui::MachineConst *ui;
    QLineEdit *pLineEdit[114];
    QString fileName;
    QString tableName;
    QString str;


private:
    int insertData();
    void updateData(int);

private slots:
     void on_tableWidget_doubleClicked(const QModelIndex &index);

 public slots:
     void saveSlot();
};

#endif // MACHINECONST_H
