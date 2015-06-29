#include "widget.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;

    //如果动态属性不存在，QVariant 对象的 isValid() 函数返回 false，变量不可用
    qDebug()<<w.property("myValue").isValid();

    //添加属性 myValue
    w.setProperty("myValue", 2.3456);
    //获取并打印
    qDebug()<<w.property("myValue").toDouble();

    //添加属性 myName
    w.setProperty("myName", "Wid");
    //获取并打印
    qDebug()<<w.property("myName").toString();

    //获取所有动态属性名称，打印名称列表
    qDebug()<<w.dynamicPropertyNames();

    w.show();

    return a.exec();
}
