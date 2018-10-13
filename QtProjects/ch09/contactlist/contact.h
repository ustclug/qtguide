#ifndef CONTACT_H
#define CONTACT_H

#include <QString> //字符串
#include <QFile>   //文件类
#include <QDataStream> //数据流类

class Contact
{
public:
    Contact();//默认构造函数，必须有
    ~Contact();
    //带参数的构造函数
    Contact(QString strName, QString strPhone, QString strAddress);
    //复制构造函数
    Contact(const Contact &c); //必须有
    //赋值运算符函数
    Contact& operator=( const Contact &c ); //必须有

    //双等号函数，用于支持列表查询函数，双等号和小于号都按姓名字符串比较
    bool operator==( const Contact &c );

    //友元声明，小于号函数必须用两个参数的全局函数
    friend bool operator<( const Contact &c1, const Contact &c2 );

    //友元声明，流插入运算符和流提取运算符函数
    friend QDataStream & operator<<(QDataStream & out, const Contact &c );
    friend QDataStream & operator>>(QDataStream & in, Contact &c);

    //toString 函数方便将三个成员变量作为一行文本显示到列表控件
    QString toString();

    //成员变量
    QString m_strName;   //姓名
    QString m_strPhone;  //电话
    QString m_strAddress;//地址
};
//两个参数的小于号函数声明
bool operator<( const Contact &c1, const Contact &c2 );
//流插入运算符和流提取运算符函数本身的声明
QDataStream & operator<<(QDataStream & out, const Contact &c );
QDataStream & operator>>(QDataStream & in, Contact &c);

#endif // CONTACT_H
