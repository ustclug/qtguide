#include <QCoreApplication>
#include <QTextStream>

//函数声明，根据不同功能代码实现输入输出功能
void Funcs(int nCode, QTextStream &tsIn, QTextStream &tsOut);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTextStream tsIn(stdin);    //类似 cin
    QTextStream tsOut(stdout);  //类似 cout

    while(true)
    {
        //显示程序功能
        QString strFuns = a.tr( "功能代码：\n"
                                "1. 输入整型数\n"
                                "2. 输入浮点数\n"
                                "3. 输入单词\n"
                                "4. 输入整行句子\n"
                                "9. 退出程序\n"
                                "请输入功能代码： "
                                );
        //显示输出时一定要带上 <<flush 或者 <<endl
        tsOut<<strFuns<<flush;
        //获取用户输入功能代码
        int nCode;
        tsIn>>nCode;
        if( 9 == nCode )
        {
            tsOut<< a.tr("程序结束。")<<endl;
            //结束
            return 0;
        }
        else
        {
            Funcs(nCode, tsIn, tsOut);
        }
    }

    return a.exec();
}
//功能函数定义
void Funcs(int nCode, QTextStream &tsIn, QTextStream &tsOut)
{
    tsOut<<endl;    //开始时换行
    QString strOut; //打印字符串

    QString strIn;  //接收单词和整行字符串
    int nNum;           //接收整数
    double dblValue;    //接收浮点数

    switch (nCode) {
    case 1:
        strOut = qApp->tr("请输入整数： ");
        tsOut<<strOut<<flush;
        tsIn>>nNum;
        //显示
        strOut = qApp->tr("您刚输入的是：%1").arg( nNum );
        tsOut<<strOut<<endl;
        break;

    case 2:
        strOut = qApp->tr("请输入浮点数： ");
        tsOut<<strOut<<flush;
        tsIn>>dblValue;
        //显示
        strOut = qApp->tr("您刚输入的是：%1").arg( dblValue );
        tsOut<<strOut<<endl;
        break;

    case 3:
        strOut = qApp->tr("请输入一个单词： ");
        tsOut<<strOut<<flush;
        tsIn>>strIn;    //读取空白分隔的一个单词
        //显示
        strOut = qApp->tr("您刚输入的是： %1").arg( strIn );
        tsOut<<strOut<<endl;
        break;

    case 4:
        strOut = qApp->tr("请输入一行字符串： ");
        tsOut<<strOut<<flush;
        //跳过用户输入功能代码时敲的回车键字符
        tsIn.skipWhiteSpace();
        strIn = tsIn.readLine();    //读取一行
        //显示
        strOut = qApp->tr("您刚输入的是： %1").arg( strIn );
        tsOut<<strOut<<endl;
        break;

    default:
        strOut = qApp->tr("未知功能代码  %1 ，不处理。").arg(nCode);
        tsOut<<strOut<<endl;
        break;
    }
    //结束时再换一行
    tsOut<<endl;

    /**判断一下输入流的状态**/
    if( tsIn.status() != QTextStream::Ok)
    {
        //有可能出现用户输入错误，把错误的输入数据跳过去
        tsIn.readLine();    //跳过一行
        tsIn.resetStatus(); //重置状态
    }
}

