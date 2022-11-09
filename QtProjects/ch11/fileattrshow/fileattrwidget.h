#ifndef FILEATTRWIDGET_H
#define FILEATTRWIDGET_H

#include <QWidget>
#include <QFile>
#include <QFileInfo>
#include <QFileDialog>
#include "tabpreview.h"

namespace Ui {
class FileAttrWidget;
}

class FileAttrWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FileAttrWidget(QWidget *parent = 0);
    ~FileAttrWidget();

signals:
    //文件名变化时触发该信号
    void fileNameChanged(const QString &fileName);

private slots:
    void on_pushButtonSelectFile_clicked();

    void on_pushButtonPreview_clicked();

private:
    Ui::FileAttrWidget *ui;
    //子窗口指针    
    TabPreview *m_pPreviewWnd;
    //文件全名
    QString m_strFileName;
    //文件信息查看对象
    QFileInfo m_fileInfo;

    //初始化函数
    void Init();
};

#endif // FILEATTRWIDGET_H
