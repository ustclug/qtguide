//callback.cpp
#include <iostream>
using namespace std;

//源端约定回调函数类型
typedef void (*PFUNC)(double v, int n, void *pObject);

//接收端类
class Dst
{
private:
    double m_dblValue;
    int m_nCount;

public:
    //处理数据函数
    double DoSomething()
    {
        double dblResult = m_dblValue / m_nCount;
        return dblResult;
    }
    //回调函数
    static void FuncCallBack(double v, int n, void *pObject)
    {
        //转换成 Dst 指针
        Dst *pDst = (Dst *)pObject;
        //静态成员函数也是可以设置私有变量的，但需要手动传对象指针
        //设置 value
        pDst->m_dblValue = v;
        //设置count
        if( n < 1)
        {
            pDst->m_nCount = 1;
        }
        else
        {
            pDst->m_nCount = n;
        }
    }

};
//源端类
class Src
{
public:
    void SendDataTo( Dst *pDst, PFUNC pFunc)
    {
        //通过回调函数传数据
        pFunc(2.0, 3, pDst);
    }
};

int main()
{
    //定义两个对象
    Dst theDst;
    Src theSrc;
    //传递数据
    theSrc.SendDataTo(&theDst, Dst::FuncCallBack);
    //接收端处理
    cout<<theDst.DoSomething();
    //
    return 0;
}
