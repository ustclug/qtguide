#ifndef TABPREVIEW_H
#define TABPREVIEW_H

#include <QWidget>
#include <QButtonGroup>
#include <QPixmap>
#include <QFile>

namespace Ui {
class TabPreview;
}

class TabPreview : public QWidget
{
    Q_OBJECT

public:
    explicit TabPreview(QWidget *parent = 0);
    ~TabPreview();
    //初始化控件
    void InitControls();

public slots:
    void onFileNameChanged(const QString &fileName);

private:
    Ui::TabPreview *ui;
    //保存文件名
    QString m_strFileName;
    //按钮分组对象
    QButtonGroup m_buttonGroup;
    //保存预览图像
    QPixmap m_image;
};

#endif // TABPREVIEW_H
