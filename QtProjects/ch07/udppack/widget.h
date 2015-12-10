#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

//网络协议头一般都用 1 字节对齐
#pragma pack(1)

//UDP 头部和报文
struct UDPPacker
{
    quint16 m_srcPort;  //源端口
    quint16 m_dstPort;  //目的端口
    quint16 m_length;   //UDP头部和报文总长度
    quint16 m_checksum; //校验和（不是强制要求）
    QByteArray m_data;  //报文内容

    //友元声明，一对用于支持QDataStream 输入输出的函数
    friend QDataStream & operator<<(QDataStream & stream, const UDPPacker & udp);
    friend QDataStream & operator>>(QDataStream & stream, UDPPacker & udp);
};

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
    void on_pushButtonAddUDP_clicked();

    void on_pushButtonDelUDP_clicked();

    void on_pushButtonSave_clicked();

    void on_pushButtonLoad_clicked();

    void on_listWidget_currentRowChanged(int currentRow);

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
