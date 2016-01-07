#ifndef CALCPI_H
#define CALCPI_H
#include <QFile>    //支持文件写入

class CalcPI
{
public:
    CalcPI();
    ~CalcPI();
    //计算
    void Calc(int length);

    //打印到命令行
    void PrintPI();
    //输出到文件
    void WriteToFile(QFile &fileOut);

private:
    int L;  //要计算的位数
    int N;  //数组长度
    //四个用到的数组
    int *s;
    int *w;
    int *v;
    int *q;

    //数组空间分配、初始化函数
    void InitArrays(int length);
    //数组清除函数
    void ClearAll();

    //三个内部计算函数
    void add(int *, int *, int*);
    void sub(int *, int *, int*);
    void div(int *, int, int*);
};

#endif // CALCPI_H
