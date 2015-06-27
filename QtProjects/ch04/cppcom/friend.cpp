//friend.cpp
#include <iostream>
using namespace std;

//接收端类
class Dst
{
private:    //私有变量
    double m_dblValue;
    int m_nCount;

public:
    //处理数据函数
    double DoSomething()
    {
        double dblResult = m_dblValue / m_nCount;
        return dblResult;
    }
    //友元类
    friend class Src;
};
//源端类
class Src
{
public:
    void SendDataTo( Dst &theDst)
    {
        //因为是友元类，所以能设置接收端私有变量
        theDst.m_dblValue = 2.0;
        theDst.m_nCount = 3;
    }
};

int main()
{
    //定义两个对象
    Dst theDst;
    Src theSrc;
    //传递数据
    theSrc.SendDataTo(theDst);
    //接收端处理
    cout<<theDst.DoSomething();
    //
    return 0;
}
