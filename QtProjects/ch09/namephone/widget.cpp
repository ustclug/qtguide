#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QMessageBox>
#include <QRegExp> //正则表达式
#include <QRegExpValidator>//正则表达式验证器

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //设置电话号码的限定，这里用正则表达式粗略限定 3 ~ 14 位数字
    QRegExp re("[0-9]{3,14}");
    QValidator *vali = new QRegExpValidator(re);
    ui->lineEditPhone->setValidator( vali );
    //结果显示框设为只读
    ui->textEdit->setReadOnly(true);
    //添加几个多重映射元素
    m_mmapNamePhone.insert("Alice", "10086");
    m_mmapNamePhone.insert("Alice", "10086");
    m_mmapNamePhone.insert("Bob", "10010");
    m_mmapNamePhone.insert("Bob", "10011");
    m_mmapNamePhone.insert("Ceil", "12345");
    //显示多重映射到列表控件
    showNamePhoneMap();
}

Widget::~Widget()
{
    delete ui;
}

//显示多重映射到列表控件
void Widget::showNamePhoneMap()
{
    //清空旧的内容
    ui->listWidget->clear();
    //使用迭代器遍历
    QMultiMap<QString, QString>::iterator it = m_mmapNamePhone.begin();
    //循环遍历直到结束
    while( it != m_mmapNamePhone.end() )
    {
        //读取键、值，拼接为字符串
        QString curText = tr("%1\t%2").arg( it.key() ).arg( it.value() );
        //添加到列表控件
        ui->listWidget->addItem( curText );
        //递增迭代器
        it++;
    }
}

void Widget::on_pushButtonAdd_clicked()
{
    //获取姓名、电话
    QString strName = ui->lineEditName->text().trimmed();
    QString strPhone = ui->lineEditPhone->text().trimmed();
    //两个字符串不能为空
    if( strName.isEmpty() || strPhone.isEmpty() )
    {
        QMessageBox::warning(this, tr("检查姓名和电话"), tr("姓名和电话都不能为空！"));
        return;
    }
    //多重映射的添加
    m_mmapNamePhone.insert(strName, strPhone);
    //显示
    showNamePhoneMap();
    ui->textEdit->setText( tr("已添加姓名-电话新元素。") );
}

void Widget::on_pushButtonReplace_clicked()
{
    //获取姓名、电话
    QString strName = ui->lineEditName->text().trimmed();
    QString strPhone = ui->lineEditPhone->text().trimmed();
    //两个字符串不能为空
    if( strName.isEmpty() || strPhone.isEmpty() )
    {
        QMessageBox::warning(this, tr("检查姓名和电话"), tr("姓名和电话都不能为空！"));
        return;
    }
    //多重映射的替换操作，如果没有旧key，会新增元素
    m_mmapNamePhone.replace(strName, strPhone);
    //显示
    showNamePhoneMap();
    ui->textEdit->setText( tr("已完成姓名-电话元素替换。") );
}

void Widget::on_pushButtonDelName_clicked()
{
    //获取姓名
    QString strName = ui->lineEditName->text().trimmed();
    //字符串不能为空
    if( strName.isEmpty() )
    {
        QMessageBox::warning(this, tr("检查姓名"), tr("姓名不能为空！"));
        return;
    }
    //可以直接调用删除函数，返回值是删除数量
    int nRet = m_mmapNamePhone.remove( strName );
    if( nRet < 1 )
    {
        //没有删除东西，不需要更新列表控件
        ui->textEdit->setText( tr("指定姓名不存在，无法删除。") );
    }
    else
    {
        //更新列表控件、结果显示框
        showNamePhoneMap();
        ui->textEdit->setText( tr("已删除匹配姓名元素 %1 个。").arg(nRet) );
    }
}

void Widget::on_pushButtonDelNamePhone_clicked()
{
    //获取姓名、电话
    QString strName = ui->lineEditName->text().trimmed();
    QString strPhone = ui->lineEditPhone->text().trimmed();
    //两个字符串不能为空
    if( strName.isEmpty() || strPhone.isEmpty() )
    {
        QMessageBox::warning(this, tr("检查姓名和电话"), tr("姓名和电话都不能为空！"));
        return;
    }
    //可以直接调用删除函数，返回值是删除数量
    int nRet = m_mmapNamePhone.remove( strName, strPhone );
    if( nRet < 1 )
    {
        //没有删除东西，不需要更新列表控件
        ui->textEdit->setText( tr("指定姓名电话元素不存在，无法删除。") );
    }
    else
    {
        //更新列表控件，结果显示框
        showNamePhoneMap();
        ui->textEdit->setText( tr("已删除匹配姓名电话元素 %1 个。").arg(nRet) );
    }
}

void Widget::on_pushButtonFindName_clicked()
{
    //获取姓名
    QString strName = ui->lineEditName->text().trimmed();
    //姓名不能为空
    if( strName.isEmpty() )
    {
        QMessageBox::warning(this, tr("检查姓名"), tr("姓名不能为空！"));
        return;
    }
    //查找姓名对应的电话列表，如果电话列表为空说明没有匹配的key
    QList<QString> listPhones = m_mmapNamePhone.values( strName );
    QString strResult; //结果字符串
    int nPhonesCount = listPhones.count();
    //检查数量
    if( nPhonesCount < 1 )
    {
         strResult = tr("没有找到指定姓名元素。");
    }
    else
    {
        strResult = tr("已找到匹配姓名元素 %1 个：\r\n").arg( nPhonesCount );
        for(int i=0; i<nPhonesCount; i++)
        {
            strResult += tr("%1\t%2\r\n").arg( strName ).arg( listPhones[i] );
        }
    }
    //显示结果字符串
    ui->textEdit->setText( strResult);
}

void Widget::on_pushButtonFindPhone_clicked()
{
    //获取电话
    QString strPhone = ui->lineEditPhone->text().trimmed();
    //电话不能为空
    if( strPhone.isEmpty() )
    {
        QMessageBox::warning(this, tr("检查电话"), tr("电话不能为空！"));
        return;
    }
    //反向查找，根据value反查key，姓名电话可能重复多个
    QList<QString> listNames = m_mmapNamePhone.keys( strPhone );
    QString strResult; //结果字符串
    int nNamesCount = listNames.count();
    //检查数量
    if( nNamesCount < 1 )
    {
        strResult = tr("没有找到匹配电话的元素。");
    }
    else
    {
        strResult = tr("已找到匹配电话的元素 %1 个：\r\n").arg( nNamesCount );
        for(int i=0; i<nNamesCount; i++)
        {
            strResult += tr("%1\t%2\r\n").arg( listNames[i] ).arg( strPhone );
        }
    }
    //显示结果
    ui->textEdit->setText( strResult );
}
