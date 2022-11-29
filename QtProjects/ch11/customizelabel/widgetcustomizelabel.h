#ifndef WIDGETCUSTOMIZELABEL_H
#define WIDGETCUSTOMIZELABEL_H

#include <QWidget>
#include <QColorDialog>
#include <QFontDialog>
#include <QInputDialog>

namespace Ui {
class WidgetCustomizeLabel;
}

class WidgetCustomizeLabel : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetCustomizeLabel(QWidget *parent = 0);
    ~WidgetCustomizeLabel();

private slots:
    void on_pushButtonForeground_clicked();

    void on_pushButtonBackground_clicked();

    void on_pushButtonFont_clicked();

    void on_pushButtonText_clicked();

    //手动添加槽函数，动态更新前景色
    void RecvAndSetForegroundColor(QColor color);

private:
    Ui::WidgetCustomizeLabel *ui;
    //保存前景色、背景色、字体、输入文本
    QColor m_clrForeground;
    QColor m_clrBackground;
    QFont m_font;
    QString m_strText;
    //单独定制一个前景色对话框
    QColorDialog *m_pDlgForeground;
    //初始化
    void Init();
};

#endif // WIDGETCUSTOMIZELABEL_H
