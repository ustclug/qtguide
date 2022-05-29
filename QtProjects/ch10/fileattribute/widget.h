#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFile>
#include <QFileInfo>
#include <QFileDialog>
#include "tabpreview.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();


signals:
    //文件名变化时触发该信号
    void fileNameChanged(const QString &fileName);

private slots:
    void on_pushButtonSelectFile_clicked();

private:
    Ui::Widget *ui;
    //自定义第三个标签页面
    TabPreview *m_pTabPreview;

    //文件全名
    QString m_strFileName;
    //文件信息查看对象
    QFileInfo m_fileInfo;
};

#endif // WIDGET_H
