#include "showmsg.h"
#include <QMessageBox>

ShowMsg::ShowMsg(QObject *parent) : QObject(parent)
{

}

ShowMsg::~ShowMsg()
{

}

//str 就是从信号里发过来的字符串
void ShowMsg::RecvMsg(QString str)
{
    QMessageBox::information(NULL, tr("Show"), str);
}
