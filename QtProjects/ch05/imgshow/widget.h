#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPixmap>  //像素图
#include <QMovie>   //动态图
#include <QImageReader> //可以打开图片或者查看支持的图片格式

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

public slots:
    //接收出错的信号
    void RecvPlayError(QImageReader::ImageReaderError error);
    //接收播放时帧号变化
    void RecvFrameNumber(int frameNumber);

private slots:
    void on_pushButtonOpenPic_clicked();

    void on_pushButtonOpenMov_clicked();

    void on_pushButtonStart_clicked();

    void on_pushButtonStop_clicked();

private:
    Ui::Widget *ui;

    //像素图指针
    QPixmap *m_pPixMap;
    //动态图指针
    QMovie *m_pMovie;
    //是否为动态图
    bool m_bIsMovie;
    //动态图是否在播放中，如果在播放中，那么循环播放
    bool m_bIsPlaying;

    //清除函数，在打开新图之前，清空旧的
    void ClearOldShow();
};

#endif // WIDGET_H
