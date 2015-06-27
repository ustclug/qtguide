//getset.cpp
#include <iostream>
using namespace std;

//接收端类
class Dst
{
private:    //私有变量
    double m_dblValue;
    int m_nCount;

public:
    //get函数
    double value()
    {
        return m_dblValue;
    }
    int count()
    {
        return m_nCount;
    }
    //set函数
    void setValue(double v)
    {
        m_dblValue = v;
    }
    void setCount(int n)
    {
        if( n < 1 ) //防止除 0 ，并且计数限定为正整数
        {
            m_nCount = 1;
        }
        else
        {
            m_nCount = n;
        }
    }

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
        //通过set函数传递数据
        theDst.setValue(2.0);
        theDst.setCount(3);
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
