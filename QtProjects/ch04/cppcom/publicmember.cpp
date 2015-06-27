//publicmember.cpp
#include <iostream>
using namespace std;
//接收端类
class Dst
{
public:
    double m_dblValue;
    int m_nCount;

    //处理数据函数
    double DoSomething()
    {
        double dblResult = m_dblValue / m_nCount;
        return dblResult;
    }
};
//源端类
class Src
{
public:
    void SendDataTo( Dst &theDst)
    {
        //设置接收端公有变量
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
