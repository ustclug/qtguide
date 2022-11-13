#ifndef ROTATEIMAGEDIALOG_H
#define ROTATEIMAGEDIALOG_H

#include <QDialog>

namespace Ui {
class RotateImageDialog;
}

class RotateImageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RotateImageDialog(QWidget *parent = 0);
    ~RotateImageDialog();

private slots:
    void on_pushButtonRotating_clicked();

private:
    Ui::RotateImageDialog *ui;
    //初始化函数
    void Init();
};

#endif // ROTATEIMAGEDIALOG_H
