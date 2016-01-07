#include "calcpi.h"
#include <cstdio>
#include <cstdlib>
#include <QByteArray>
#include <QString>
using namespace std;

CalcPI::CalcPI()
{
    //都为空
    L = 0;
    N = 0;
    s = NULL;
    w = NULL;
    v = NULL;
    q = NULL;
}

CalcPI::~CalcPI()
{
    ClearAll();
}

void CalcPI::Calc(int length)
{
    //判断长度是否合法
    if( length < 1)
    {
        return;
    }
    //删除旧的
    ClearAll();
    //初始化新数组
    InitArrays( length );

    //开始计算
    int n = (int)(L / 1.39793 + 1);
    int k;
    w[0] = 16 * 5;
    v[0] = 4 * 239;
    for (k = 1; k <= n; k++)
    {
        // 套用公式
        div(w, 25, w);
        div(v, 239, v);
        div(v, 239, v);
        sub(w, v, q);
        div(q, 2 *k - 1, q);
        if (k % 2)
        {
            // 奇数项
            add(s, q, s);
        }
        else
        {
            // 偶数项
            sub(s, q, s);
        }//
    }//for
    //已经计算完成
}

//删除空间
void CalcPI::ClearAll()
{
    //删除各个数组
    delete []s; s = NULL;
    delete []w; w = NULL;
    delete []v; v = NULL;
    delete []q; q = NULL;
}

//分配空间和初始化
void CalcPI::InitArrays(int length)
{
    //要计算的位数存到成员变量
    L = length;
    N = L / 4 + 1;
    //分配空间
    s = new int[N+3];
    w = new int[N+3];
    v = new int[N+3];
    q = new int[N+3];
    //初始化都为0
    for(int i=0; i< N+3; i++)
    {
        s[i] = 0;
        w[i] = 0;
        v[i] = 0;
        q[i] = 0;
    }
}

void CalcPI::add(int *a, int *b, int *c)
{
    int i, carry = 0;
    for (i = N + 1; i >= 0; i--)
    {
        c[i] = a[i] + b[i] + carry;
        if (c[i] < 10000)
            carry = 0;
        else
        {
            // 进位
            c[i] = c[i] - 10000;
            carry = 1;
        }
    }
}

void CalcPI::sub(int *a, int *b, int *c)
{
    int i, borrow = 0;
    for (i = N + 1; i >= 0; i--)
    {
        c[i] = a[i] - b[i] - borrow;
        if (c[i] >= 0)
            borrow = 0;
        else
        {
            // 借位
            c[i] = c[i] + 10000;
            borrow = 1;
        }
    }
}

void CalcPI::div(int *a, int b, int *c)
{
    // b 为除数
    int i, tmp, remain = 0;
    for (i = 0; i <= N + 1; i++)
    {
        tmp = a[i] + remain;
        c[i] = tmp / b;
        remain = (tmp % b) *10000;
    }
}


//打印函数
void CalcPI::PrintPI()
{
    //判断长度
    if( L < 1)
    {
        return;
    }
    //正常打印
    printf("%d.", s[0]);
    for (int k = 1; k < N; k++)
    {
          printf("%04d", s[k]);
    }
    printf("\n");
}

//写文件函数
void CalcPI::WriteToFile(QFile &fileOut)
{
    //判断长度
    if( L < 1)
    {
        return;
    }
    QString strTemp;
    //打头的 3.
    strTemp = QFile::tr("%1.").arg(s[0]);
    //写入文件
    fileOut.write( strTemp.toUtf8() );
    //循环写入后面的
    for(int k=1; k < N; k++)
    {
        strTemp = QFile::tr("%1").arg( s[k], 4, 10, QChar('0') );
        fileOut.write( strTemp.toUtf8() );
    }
    //完成
}

