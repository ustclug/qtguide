#include "widget.h"
#include <QApplication>
#include <QDebug>
#include <QMetaClassInfo>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    //获取类的附加信息
    const QMetaObject *pMO = w.metaObject();
    //多态性，替换上面一句
    //QObject *pObj = &w;
    //const QMetaObject *pMO = pObj->metaObject();

    //附加信息个数
    int nInfoCount = pMO->classInfoCount();
    //打印所有的附加信息
    for(int i=0; i<nInfoCount; i++)
    {
        QMetaClassInfo info = pMO->classInfo(i);
        qDebug()<<info.name()<<"\t"<<info.value();
    }

    //基本信息
    qDebug()<<"Class Name: "<<pMO->className();
    qDebug()<<"Object Name: "<<w.objectName();
    //判断是否为基类
    qDebug()<<w.inherits("QWidget");
    qDebug()<<w.inherits("nothing");

    //显示窗口
    w.show();

    return a.exec();
}
