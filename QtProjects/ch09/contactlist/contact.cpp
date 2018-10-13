#include "contact.h"

//默认构造函数
Contact::Contact()
{
    m_strName = "None";
    m_strPhone = "00000";
    m_strAddress = "None";
}

Contact::~Contact()
{

}

//带参数的构造函数
Contact::Contact(QString strName, QString strPhone, QString strAddress)
{
    m_strName = strName;
    m_strPhone = strPhone;
    m_strAddress = strAddress;
}

//复制构造函数
Contact::Contact(const Contact &c)
{
    m_strName = c.m_strName;
    m_strPhone = c.m_strPhone;
    m_strAddress = c.m_strAddress;
}

//赋值运算符函数
Contact & Contact::operator= ( const Contact &c )
{
    m_strName = c.m_strName;
    m_strPhone = c.m_strPhone;
    m_strAddress = c.m_strAddress;
    return *this;
}

//双等号函数，用于支持列表查询函数
bool Contact::operator== ( const Contact &c )
{
    //比较纯粹看姓名的字符串比较
    return ( c.m_strName == m_strName ) ;
}

//两个参数的小于号函数，全局函数，用于支持排序功能
bool operator<( const Contact &c1, const Contact &c2 )
{
    //纯粹看姓名的字符串比较
    return ( c1.m_strName < c2.m_strName );
}

//toString 函数方便将三个成员变量作为一行文本显示到列表控件
QString Contact::toString()
{
    //用制表符拼接三个字符串
    QString strRet = m_strName + QString("\t")
                + m_strPhone + QString("\t")
                + m_strAddress;
    return strRet;
}

//数据流操作，流插入运算符
QDataStream & operator<<(QDataStream & out, const Contact &c )
{
    out<<c.m_strName<<c.m_strPhone<<c.m_strAddress;
    return out;
}

//数据流操作，流提取运算符
QDataStream & operator>>(QDataStream & in, Contact &c)
{
    in>>c.m_strName>>c.m_strPhone>>c.m_strAddress;
    return in;
}

