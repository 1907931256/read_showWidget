#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>
#include"sysGlobal.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale()); //设置编码
    MainWindow w;
    w.show();

    return a.exec();
}
