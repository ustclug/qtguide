#ifndef PERSON_H
#define PERSON_H

#include <QHash>
#include <QMap>
#include <QString>
#include <QDateTime>
#include <QDataStream>

class Person
{
public:
    //带参数的构造函数
    Person(QString strName, QString strGender, QDate birthDay);

    //数据库容器对象只能存储可赋值数据，key和value都要求可赋值
    //不带参数的默认构造函数，可赋值类型要求 1
    Person();
    Person(const Person &other);    //复制构造函数，可赋值类型要求2
    Person &operator =(const Person &other);//赋值号，可赋值类型要求3
    ~Person();

    //姓名、性别、出生日期，三个成员变量读写函数，只读函数要加 const 修饰
    inline QString name() const
    {
        return m_name;
    }
    inline void setName(const QString &strName)
    {
        m_name = strName;
    }
    inline QString gender() const
    {
        return m_gender;
    }
    inline void setGender(const QString &strGender)
    {
        m_gender = strGender;
    }
    inline QDate birthday() const
    {
        return m_birthday;
    }
    inline void setBirthday(const QDate &bday)
    {
        m_birthday = bday;
    }

protected:
    //姓名、性别、出生日期
    QString m_name;
    QString m_gender;
    QDate m_birthday;
};

//哈希对于key类型额外要求 1，全局的等于号比较函数
bool operator ==(const Person &p1, const Person &p2);

//哈希对于key类型额外要求 2，全局的哈希函数
uint qHash(const Person &key, uint seed=0);

//输入输出串行化要求，全局的串行化函数
QDataStream &operator <<(QDataStream &out, const Person &pout);
QDataStream &operator >>(QDataStream &in, Person &pin);

//补充说明，如果用于 QMap，那么实现全局的小于号比较函数，该函数还可以用于 qSort()排序函数
bool operator <(const Person &p1, const Person &p2);

#endif // PERSON_H
