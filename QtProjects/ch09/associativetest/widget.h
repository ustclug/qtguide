#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMap>
#include <QHash>
#include <QSet>
#include <QElapsedTimer> //计时器
#include <QLocale> //本地化类，用于打印逗号分隔的数字

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
    void on_pushButtonInsert_clicked();

    void on_pushButtonFind_clicked();

private:
    Ui::Widget *ui;
    //容器对象
    QMap<int, int>  m_map;
    QHash<int, int> m_hash;
    QSet<int>  m_set;
    //耗费计时器
    QElapsedTimer m_calcTimer;
    //本地化对象，用于打印逗号分隔的数字
    QLocale m_locale;
};

#endif // WIDGET_H
