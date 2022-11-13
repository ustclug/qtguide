#ifndef RESIZEIMAGEDIALOG_H
#define RESIZEIMAGEDIALOG_H

#include <QDialog>

namespace Ui {
class ResizeImageDialog;
}

class ResizeImageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ResizeImageDialog(QWidget *parent = 0);
    ~ResizeImageDialog();

signals:
    //发送新的尺寸给主窗口，由主窗口完成缩放
    void SendNewSize(int nNewWidth, int nNewHeight);

private slots:
    void on_pushButtonSetNewSize_clicked();

    //接收图片旧尺寸并显示
    void RecvOldSize(int nOldWidth, int nOldHeight);

private:
    Ui::ResizeImageDialog *ui;
    //初始化函数
    void Init();
};

#endif // RESIZEIMAGEDIALOG_H
