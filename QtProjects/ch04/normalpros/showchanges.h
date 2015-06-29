#ifndef SHOWCHANGES_H
#define SHOWCHANGES_H

#include <QObject>

class ShowChanges : public QObject
{
    Q_OBJECT
public:
    explicit ShowChanges(QObject *parent = 0);
    ~ShowChanges();

signals:

public slots:
    //槽函数，接收 value 变化信号
    void RecvValue(double v);
};

#endif // SHOWCHANGES_H
