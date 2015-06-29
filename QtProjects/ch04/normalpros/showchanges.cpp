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
