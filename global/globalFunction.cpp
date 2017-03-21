#include"globalFunction.h"

/********************************************
 *function:读取数据库，单个单元格读取
 *input: filename数据库路径    tablename表名  index索引  mycolumn列数
 *output:str查询到的数据
 *adding:
 *author: xu
 *date: 2014/11/9
 *******************************************/
QString ReadSqlData(QString filename, QString tablename, int index, int mycolumn)
{
       sqlite3 *db = NULL;
        int rc = 0;
        char *errmsg = NULL;    //错误信息
        char **dbResult;        //是char** 类型，两个*号
        int nRow, nColumn;
        QString str=NULL;
        QString strSQL = QString("%1%2").arg( "select * from ").arg(tablename);
        rc = sqlite3_open(filename.toUtf8(),&db);
        if(rc != 0)
        {
            sqlite3_close(db);
            return str;
        }
        rc=sqlite3_get_table( db, strSQL.toUtf8(), &dbResult, &nRow, &nColumn, &errmsg );
        if (SQLITE_OK != rc)
        {
            sqlite3_free_table( dbResult );
            //关闭数据库
            sqlite3_close( db );
            return NULL;
        }
        if(index>=nRow)     //index从0开始，故范围在0到nRow之间，取不到nRow
        {
            sqlite3_free_table( dbResult );
            //关闭数据库
            sqlite3_close( db );
            return NULL;
        }
        if( 0 == rc )
        {
            //查询成功
            str=dbResult [nColumn*index+nColumn+mycolumn];
        }

        sqlite3_free_table( dbResult );
        //关闭数据库
        sqlite3_close( db );
        return str;
}


/********************************************
 *function:重载函数，根据命令读取数据库
 *input:filename数据库位置   strSQL查询语句  row行  column列
 *output:返回读取的数据，行数和列数
 *adding:
 *author: xu
 *date: 2014/11/9
 *******************************************/
QStringList ReadSqlData(QString filename, QString strSQL, int *row, int *column)
{
        sqlite3 *db = NULL;
        int rc = 0;
        char *errmsg = NULL;    //错误信息
        char **dbResult;        //是char** 类型，两个*号
        int nRow, nColumn;
        QStringList strList;
        rc = sqlite3_open(filename.toUtf8(),&db);
        if(rc != 0)
        {
            sqlite3_close(db);
            return strList;
        }
        rc=sqlite3_get_table( db, strSQL.toUtf8(), &dbResult, &nRow, &nColumn, &errmsg );
        if (SQLITE_OK != rc)
        {
            sqlite3_free_table( dbResult );
            //关闭数据库
            sqlite3_close( db );
            return strList;
        }
        if( 0 == rc )
        {
            //查询成功
            for(int i = nColumn; i < (nRow+1)*nColumn; i++)
            {
                strList.append(dbResult[i]);
            }
            *row = nRow;
            *column = nColumn;
        }
        sqlite3_free_table( dbResult );
        //关闭数据库
        sqlite3_close( db );
        return strList;
    }

/********************************************
 *function:更新数据库
 *input:filename数据库路径  tablename表名  columname列名 index索引序列号 strData数据
 *output:无
 *adding:
 *author: xu
 *date: 2014/11/9
 *******************************************/
int UpdateSqlData(QString filename, QString tablename, QString columname, int index, QString strData)
{
    sqlite3 *db = NULL;
        int rc = 0;
        char *errmsg = NULL;        //错误信息

        QString strSQL=QString("%1%2%3%4%5%6%7%8%9")
                                        .arg( "update ")
                                        .arg(tablename)
                                        .arg(" set ")
                                        .arg(columname)
                                        .arg("=")
                                        .arg("'")
                                        .arg(strData)
                                        .arg( "' where id =")   //需要修改
                                        .arg(index+1);
        rc = sqlite3_open(filename.toUtf8(),&db);
        if(rc != 0)
        {
            qDebug()<<"打开失败";
            sqlite3_close(db);
            return 1;
        }

        rc = sqlite3_exec(db, strSQL.toUtf8(), NULL,NULL,&errmsg);

        if(rc != 0 )
        {
             qDebug()<<"更新失败";
            sqlite3_close(db);
            return 2;
        }
        sqlite3_close(db);
        return 0;
}


QStringList ReadSqlData(QString filename, QString strSQL)
{
    sqlite3 *db = NULL;
        int rc = 0;
        char *errmsg = NULL;    //错误信息
        char **dbResult;        //是char** 类型，两个*号
        int nRow, nColumn;
        QStringList strList;
        rc = sqlite3_open(filename.toUtf8(),&db);
        if(rc != 0)
        {
            sqlite3_close(db);
            return strList;
        }
        rc=sqlite3_get_table( db, strSQL.toUtf8(), &dbResult, &nRow, &nColumn, &errmsg );
        if (SQLITE_OK != rc)
        {
            sqlite3_free_table( dbResult );
            //关闭数据库
            sqlite3_close( db );
            return strList;
        }
        if( 0 == rc )
        {
            //查询成功
            for(int i = nColumn; i < (nRow+1)*nColumn; i++)
            {
                strList.append(dbResult[i]);
            }
        }
        sqlite3_free_table( dbResult );
        //关闭数据库
        sqlite3_close( db );
        return strList;
}
