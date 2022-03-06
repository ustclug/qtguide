#include "person.h"

//带参数的构造函数
Person::Person(QString strName, QString strGender, QDate birthDay)
{
    m_name = strName;
    m_gender = strGender;
    m_birthday = birthDay;
}
//默认构造函数，可赋值类型要求 1
Person::Person()
{
    m_name = "";
    m_gender = "";
    m_birthday = QDate(2000, 1, 1);
}
//复制构造函数，可赋值类型要求2
Person::Person(const Person &other)
{
    m_name = other.m_name;
    m_gender = other.m_gender;
    m_birthday = other.m_birthday;
}
//赋值运算符，可赋值类型要求3
Person &Person::operator =(const Person &other)
{
    m_name = other.m_name;
    m_gender = other.m_gender;
    m_birthday = other.m_birthday;
    //返回对象
    return *this;
}
//默认析构函数
Person::~Person()
{

}
//哈希对于key类型额外要求 1，全局的等于号比较函数
bool operator ==(const Person &p1, const Person &p2)
{
    bool bRet = false; //默认不等
    if(  (p1.name() == p2.name())
      && (p1.gender() == p2.gender())
      && (p1.birthday() == p2.birthday()) )
    {
        bRet = true; //三个成员都相等
    }
    //返回
    return bRet;
}
//哈希对于key类型额外要求 2，全局的哈希函数
uint qHash(const Person &key, uint seed)
{
    uint nRet;
    nRet = qHash(key.name(), seed)
            ^ qHash(key.gender(), seed)
            ^ qHash(key.gender(), seed);
    return nRet;
}

//输入输出串行化要求，全局的串行化函数
QDataStream &operator <<(QDataStream &out, const Person &pout)
{
    out<<pout.name()<<pout.gender()<<pout.birthday();
    return out;
}

QDataStream &operator >>(QDataStream &in, Person &pin)
{
    //定义三个变量接受输入数据
    QString strName;
    QString strGender;
    QDate birthday;
    in>>strName>>strGender>>birthday;
    //设置成员变量
    pin.setName( strName );
    pin.setGender( strGender );
    pin.setBirthday( birthday );
    return in;
}

//补充说明，如果用于 QMap，那么实现全局的小于号比较函数，该函数还可以用于 qSort()排序函数
bool operator <(const Person &p1, const Person &p2)
{
    //按照姓名字典序大小比较
    return ( p1.name() < p2.name() );
}

