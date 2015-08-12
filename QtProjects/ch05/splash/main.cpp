#include "widget.h"
#include <QApplication>
#include <QSplashScreen>    //闪屏类
#include <QPixmap>          //像素图
#include <QResource>        //外挂资源注册
#include <QThread>          //线程类

int main(int argc, char *argv[])
{
    //应用程序对象
    QApplication a(argc, argv);

    //注册外挂资源
    //bigpics.rcc位于影子构建路径
    QResource::registerResource("bigpics.rcc");
    //加载外挂资源文件中的像素图
    QPixmap pixmapSplash(":/splash.png");
    //原图太大，缩小点方便显示
    pixmapSplash = pixmapSplash.scaled( QSize(480, 270) );
    //定义闪屏
    QSplashScreen theSplash( pixmapSplash );
    //显示闪屏
    theSplash.show();
    //在闪屏里面显示消息
    theSplash.showMessage( QObject::tr("加载中 ..."), Qt::AlignLeft|Qt::AlignBottom );

    //启动应用程序的事件处理
    a.processEvents();

    //主窗体
    Widget w;

    //下面一句睡眠不是必须的
    //这里等3秒，否则闪屏结束太快，看不到
    w.thread()->sleep(3);

    //显示主窗体
    w.show();

    //主窗体出现后就闪屏就可以结束了
    theSplash.finish(&w);

    return a.exec();
}
