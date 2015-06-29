#include "widget.h"
#include <QApplication>
#include <QDebug>
#include "showchanges.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;   //源头对象
    //接收端对象
    ShowChanges s;
    //关联
    QObject::connect(&w, SIGNAL(valueChanged(double)), &s, SLOT(RecvValue(double)));

    //属性读写
    //通过写函数、读函数
    w.setNickName( "Wid" );
    qDebug()<<w.nickName();
    w.setCount(100);
    qDebug()<<w.count();

    //通过 setProperty() 函数 和 property() 函数
    w.setProperty("value", 2.3456);
    qDebug()<<fixed<<w.property("value").toDouble();

    //显示窗体
    w.show();

    return a.exec();
}
