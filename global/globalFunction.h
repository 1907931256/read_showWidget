#ifndef GLOBALFUNCTION_H
#define GLOBALFUNCTION_H
#include<QString>
#include"sqlite3.h"
#include<QStringList>
#include<QDebug>



extern QString ReadSqlData(QString filename,QString tablename ,int index,int mycolumn);
extern QStringList ReadSqlData(QString filename, QString strSQL, int *row, int *column);
extern QStringList ReadSqlData(QString filename, QString strSQL);
extern int UpdateSqlData(QString filename,QString tablename ,QString columname, int index,QString strData);

#endif // GLOBALFUNCTION_H
