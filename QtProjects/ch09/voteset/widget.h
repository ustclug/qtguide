#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMultiHash>
#include <QSet>

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
    void on_pushButtonGetVoters_clicked();

    void on_pushButtonGetCandidates_clicked();

    void on_pushButtonGetIntersect_clicked();

    void on_pushButtonGetUnite_clicked();

private:
    Ui::Widget *ui;
    //保存投票
    QMultiHash<QString, QString> m_voteData;
    //填充投票，并设置列表框显示
    void FillDataAndListWidget();

};

#endif // WIDGET_H
