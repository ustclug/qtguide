#ifndef IMAGETRANSFORMWIDGET_H
#define IMAGETRANSFORMWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>   //图片操作类
#include <QFileDialog>  //文件选择对话框
#include <QMatrix>   //变换矩阵类
#include "resizeimagedialog.h"  //缩放尺寸对话框
#include "rotateimagedialog.h"  //旋转图片对话框

namespace Ui {
class ImageTransformWidget;
}

class ImageTransformWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ImageTransformWidget(QWidget *parent = 0);
    ~ImageTransformWidget();

signals:
    //发送旧的宽度高度给子对话框
    void SendOldSize(int nOldWidth, int nOldHeight);

private slots:
    void on_pushButtonOpen_clicked();

    void on_pushButtonResize_clicked();

    void on_pushButtonRotate_clicked();

    //收到新尺寸后进行缩放
    void RecvNewSizeAndResize(int nNewWidth, int nNewHeight);

private:
    Ui::ImageTransformWidget *ui;
    //图片显示的标签
    QLabel *m_pLabelImage;
    //图片操作类
    QPixmap m_image;
    //图片文件名
    QString m_strFileName;
    //缩放尺寸对话框
    ResizeImageDialog *m_pResizeDlg;
    //旋转图片对话框
    RotateImageDialog *m_pRotateDlg;
    //初始化函数
    void Init();
};

#endif // IMAGETRANSFORMWIDGET_H
