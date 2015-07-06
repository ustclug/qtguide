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
    //槽函数，接收 nickName 变化信号
    void RecvNickName(const QString& strNewName);
    //槽函数，接收 count 变化信号
    void RecvCount(int nNewCount);
};

#endif // SHOWCHANGES_H
