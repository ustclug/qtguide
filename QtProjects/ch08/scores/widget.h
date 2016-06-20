#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_tableWidget_itemSelectionChanged();

    void on_pushButtonFind_clicked();

    void on_pushButtonAddLine_clicked();

    void on_pushButtonDelLines_clicked();

    void on_pushButtonDelSelectedItems_clicked();

private:
    Ui::Widget *ui;
    //初始化表格函数
    void InitScoresTable();
    //设置某行的行首和四个单元格
    void SetTableRow(int nRow, QString strName,
                     QString strChinese, QString strMath,
                     QString strForeignLanguage, QString strFood);
};

#endif // WIDGET_H
