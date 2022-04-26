#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QImage>
#include <QPixmap>
#include <QLabel>
#include <QImageWriter> //获取转换输出支持的图片格式
#include <QFileInfo>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    //初始化控件函数
    void InitControls();

private slots:
    void on_pushButtonOpen_clicked();

    void on_pushButtonConvert_clicked();

private:
    Ui::Widget *ui;
    //图片预览标签
    QLabel *m_pLabelPreview;
    //图片文件名
    QString m_strImageName;
    //加载图片对象
    QImage m_image;

};

#endif // WIDGET_H
