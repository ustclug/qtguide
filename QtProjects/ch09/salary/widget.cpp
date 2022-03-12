#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //初始化工资表
    InitSalary();
    //更新显示
    UpdateSalaryShow();
}

Widget::~Widget()
{
    delete ui;
}

//初始化填充
void Widget::InitSalary()
{
    m_salary.clear();//清空
    //添加工资内容
    m_salary.insert(tr("张三"), 5000.0);
    m_salary.insert(tr("张三"), 8000.0); //有重名的
    m_salary.insert(tr("李四"), 6000.0);
    m_salary.insert(tr("王五"), 7000.0);
    m_salary.insert(tr("孙六"), 8000.0);
    m_salary.insert(tr("赵七"), 6600.0);
    m_salary.insert(tr("钱八"), 8800.0);
}

//工资列表变动时，显示到列表控件
void Widget::UpdateSalaryShow()
{
    //清空旧的内容
    ui->listWidget->clear();
    //只读迭代器遍历
    QMultiHash<QString, double>::const_iterator it;
    for( it=m_salary.constBegin(); it!=m_salary.constEnd(); ++it )
    {
        QString strLine = it.key() + tr("\t%1").arg( it.value() );
        ui->listWidget->addItem( strLine );
    }
    //完成
}

//让所有人涨工资 10%
void Widget::on_pushButtonIncrease_clicked()
{
    //读写迭代器遍历
    QMultiHash<QString, double>::iterator it;
    for( it=m_salary.begin(); it!=m_salary.end(); ++it)
    {
        //读写迭代器 it.value() 返回可以读写的 value 引用，可以作为左值写入
        it.value() *= 1.1 ;
        //注意 it.key() 永远是只读引用，不能修改key，映射的 key 只能删除或添加，不能直接修改
    }
    //更新显示
    UpdateSalaryShow();
    ui->textBrowser->setText( tr("所有人涨工资 10% 完毕。") );
}
//查找所有叫张三的人工资
void Widget::on_pushButtonFindZhang3_clicked()
{
    //张三有重名，找到第一个张三
    QMultiHash<QString, double>::const_iterator it;
    it = m_salary.find( tr("张三") );
    //信息字符串
    QString strInfo = tr("查找张三结果：\r\n");
    //查找多个张三
    while( it != m_salary.constEnd() )
    {
        if( it.key() == tr("张三") ) //连续的多个张三都显示
        {
            strInfo += it.key() + tr(" 工资： %1\r\n").arg( it.value() );
            ++it; //继续找下一个
        }
        else //人名不等于张三
        {
            break;  //遍历到 不是张三的位置，不需要再查找
        }
    }
    //显示
    ui->textBrowser->setText( strInfo );
}
//查找工资前三的人
void Widget::on_pushButtonFindTop3_clicked()
{
    //检查员工人数，如果不超过三个人，就不处理
    if( m_salary.count() <= 3 )
    {
        ui->textBrowser->setText(tr("不超过三个人，不需要查询。"));
        return;
    }
    //遍历哈希对象，然后创建工资到人名的QMultiMap映射对象
    //哈希对象迭代器
    QMultiHash<QString, double>::const_iterator it;
    //工资到人名的反向映射
    QMultiMap<double, QString> mapOrder;
    //迭代处理
    for( it=m_salary.constBegin(); it!=m_salary.constEnd(); ++it)
    {
        mapOrder.insert( it.value(), it.key() );//反向映射
    }

    //QMultiMap 和 QMap 插入节点时，会自动按照 key 值排序，从小到大排序
    QString strInfo = tr("工资前三的员工：\r\n");
    QMultiMap<double, QString>::const_iterator itMap;
    itMap = mapOrder.constEnd(); //注意不能访问 end 虚假节点
    //查找最后三个即可
    for(int i=0; i<3; i++)
    {
        --itMap; //开头 --，会跳过 end 虚假节点
        strInfo += itMap.value() + tr(" 工资：%1\r\n").arg( itMap.key() );
    }
    //显示
    ui->textBrowser->setText( strInfo );
}
//查找 8K 以上的员工
void Widget::on_pushButtonFind8K_clicked()
{
    //哈希对象迭代器
    QMultiHash<QString, double>::const_iterator it;
    //信息字符串
    QString strInfo = tr("查找8K以上工资的员工：\r\n");
    for( it=m_salary.cbegin(); it!=m_salary.cend(); ++it )
    {
        if( it.value() >= 8000 ) //判断 8K 以上的
        {
            strInfo += it.key() + tr(" 工资：%1\r\n").arg( it.value() );
        }
    }
    //显示
    ui->textBrowser->setText( strInfo );
}
//删除 8K 以上员工
void Widget::on_pushButtonDel8K_clicked()
{
    //读写迭代器
    QMultiHash<QString, double>::iterator it;
    //信息字符串
    QString strInfo = tr("删除8K以上工资的员工：\r\n");
    for( it=m_salary.begin(); it!=m_salary.end(); NULL )
    {
        if( it.value() >= 8000 ) //判断 8K 以上的
        {
            strInfo += it.key() + tr(" 工资：%1\r\n").arg( it.value() );
            //删除迭代器指向的元素，注意旧的 it 删除了不可用
            //必须用 erase() 返回值作为后面元素的新迭代器
            it = m_salary.erase( it );
        }
        else //不删除，直接下一个
        {
            ++it;
        }
    }
    //更新列表控件
    UpdateSalaryShow();
    //显示信息字符串
    ui->textBrowser->setText( strInfo );
}
