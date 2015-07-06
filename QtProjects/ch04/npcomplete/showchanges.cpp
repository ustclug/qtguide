#include "showchanges.h"
#include <QDebug>

ShowChanges::ShowChanges(QObject *parent) : QObject(parent)
{

}

ShowChanges::~ShowChanges()
{

}
//接收并打印 value 变化后的新值
void ShowChanges::RecvValue(double v)
{
    qDebug()<<"RecvValue: "<<fixed<<v;
}

//接收并打印 nickName 变化后的新值
void ShowChanges::RecvNickName(const QString &strNewName)
{
    qDebug()<<"RecvNickName: "<<strNewName;
}

//接收并打印 count 变化后的新值
void ShowChanges::RecvCount(int nNewCount)
{
    qDebug()<<"RecvCount: "<<nNewCount;
}
