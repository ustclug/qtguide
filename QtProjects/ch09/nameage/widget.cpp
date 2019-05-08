#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QMessageBox>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //设置年龄范围
    ui->spinBoxAge->setRange(0, 600);
    //结果显示框设置只读
    ui->textEdit->setReadOnly(true);
    //初始化添加几个元素到映射
    m_mapNameAge.insert("Alice", 20);
    m_mapNameAge.insert("Bob", 23);
    m_mapNameAge.insert("Cass", 23);
    m_mapNameAge.insert("Daff", 21);
    //显示映射到列表控件
    showNameAgeMap();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::showNameAgeMap()
{
    ui->listWidget->clear();    //清空旧内容
    //获取所有 key 的列表
    QList<QString> listKeys = m_mapNameAge.keys();
    int nCount = listKeys.count();
    //遍历
    for(int i=0; i<nCount; i++)
    {
        //根据 key-value 构造一行字符串
        QString curText = tr("%1\t%2").arg( listKeys[i] ).arg( m_mapNameAge[ listKeys[i] ] );
        //添加到列表控件
        ui->listWidget->addItem( curText );
    }
}

void Widget::on_pushButtonAdd_clicked()
{
    //检查姓名 key ，不能为空
    QString strName = ui->lineEditName->text().trimmed();
    if( strName.isEmpty() )
    {
        QMessageBox::warning(this, tr("检查姓名key"), tr("姓名为空，不能添加。"));
        return;
    }
    //添加姓名-年龄对
    m_mapNameAge[ strName ] = ui->spinBoxAge->value();
    //显示
    showNameAgeMap();
    ui->textEdit->setText( tr("已添加姓名-年龄新元素。") );
}

void Widget::on_pushButtonDel_clicked()
{
    //检查姓名 key ，不能为空
    QString strName = ui->lineEditName->text().trimmed();
    if( strName.isEmpty() )
    {
        QMessageBox::warning(this, tr("检查姓名key"), tr("姓名为空，不能删除。"));
        return;
    }
    //查找是否存在该 key
    if( ! m_mapNameAge.contains( strName ) )
    {
        ui->textEdit->setText( tr("指定姓名不存在，无法删除。") );
        return;
    }
    //删除匹配 key 的元素
    m_mapNameAge.remove( strName );
    //显示
    showNameAgeMap();
    ui->textEdit->setText( tr("指定姓名元素已经删除。") );
}

void Widget::on_pushButtonFindName_clicked()
{
    //检查姓名 key ，不能为空
    QString strName = ui->lineEditName->text().trimmed();
    if( strName.isEmpty() )
    {
        QMessageBox::warning(this, tr("检查姓名key"), tr("姓名为空，不能查找。"));
        return;
    }
    //查找是否存在该 key
    if( ! m_mapNameAge.contains( strName ) )
    {
        ui->textEdit->setText( tr("指定姓名不存在。") );
        return;
    }
    //找到了，这里是一对一映射，一个 key 只有一个 value
    QString strResult = tr("已找到指定姓名为 %1 的元素，年龄为 %2")
            .arg(strName).arg( m_mapNameAge[strName] );
    ui->textEdit->setText( strResult );
}

void Widget::on_pushButtonFindAge_clicked()
{
    //获取年龄
    int nAge = ui->spinBoxAge->value();
    //根据年龄反查姓名，可能存在多个同龄人
    QList<QString>  listNames = m_mapNameAge.keys( nAge );
    //检查是否找到了
    QString strResult;
    int nCount = listNames.count();
    if( nCount < 1  )
    {
        strResult = tr("没有匹配该年龄的元素。");
    }
    else//存在指定年龄的元素
    {
        strResult = tr("找到了匹配年龄的元素 %1 个，列举如下：\r\n").arg( nCount );
        for(int i=0; i<nCount; i++)
        {
            strResult += tr("%1\t%2\r\n").arg(listNames[i]).arg(nAge);
        }
    }
    //显示结果
    ui->textEdit->setText( strResult );
}
