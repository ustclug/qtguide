#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QMessageBox>
#include <QFile> //文件
#include <QFileDialog> //文件打开或保存对话框
#include <QDataStream> //数据流

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //定义4个联系人，添加到列表对象和列表控件，列表对象和列表控件一直同步
    //第1个
    Contact daala("Daala", "44444", "North");
    m_listContacts.append(daala);
    ui->listWidget->addItem( daala.toString() );
    //第2个
    Contact bob("Bob", "22222", "South");
    m_listContacts.append(bob);
    ui->listWidget->addItem( bob.toString() );
    //第3个
    Contact carl("Carl", "33333", "West");
    m_listContacts.append(carl);
    ui->listWidget->addItem( carl.toString() );
    //第4个
    Contact alice("Alice", "11111", "East");
    m_listContacts.append(alice);
    ui->listWidget->addItem( alice.toString() );
}

Widget::~Widget()
{
    delete ui;
}

//添加联系人
void Widget::on_pushButtonAdd_clicked()
{
    //获取姓名、电话、地址字符串
    QString strName = ui->lineEditName->text().trimmed();
    QString strPhone = ui->lineEditPhone->text().trimmed();
    QString strAddress = ui->lineEditAddress->text().trimmed();
    //姓名不能为空，电话地址可以空
    if( strName.isEmpty() )
    {
        QMessageBox::warning(this, tr("姓名检查"), tr("姓名为空，请输入姓名。"));
        return;
    }
    //姓名不空
    Contact person(strName, strPhone, strAddress);
    //添加到列表对象和列表控件
    m_listContacts.append( person );
    QListWidgetItem *item = new QListWidgetItem( person.toString() );
    ui->listWidget->addItem( item );
    //选中新条目
    ui->listWidget->setCurrentItem( item );//当前条目是加虚线框的那个
    item->setSelected( true );  //高亮显示
    ui->listWidget->setFocus(); //设置显示焦点
}

//删除联系人
void Widget::on_pushButtonDel_clicked()
{
    //获取当前条目
    QListWidgetItem *curItem = ui->listWidget->currentItem();
    //判断指针是否为空
    if( NULL == curItem )
    {
        return; //没东西可以删除
    }
    //存在当前条目
    //获取当前条目的序号
    int ix = ui->listWidget->currentRow();
    //从列表对象删除联系人
    m_listContacts.removeAt( ix );
    //列表控件同步删除
    delete curItem; curItem = NULL;
}

//查找联系人
void Widget::on_pushButtonFind_clicked()
{
    //获取姓名字符串
    QString strName = ui->lineEditName->text().trimmed();
    //判断是否为空
    if( strName.isEmpty() ) //姓名为空，不需要查询
    {
        QMessageBox::warning(this, tr("姓名检查"), tr("姓名为空，无法查询。"));
        return;
    }
    //存在姓名
    //从列表对象查找序号
    int ix = m_listContacts.indexOf( Contact(strName, "", "") );
    //如果找不到返回 -1
    if( ix < 0 )
    {
        QMessageBox::information(this, tr("查找"), tr("没有找到姓名一样的联系人。"));
        return;
    }
    else //找到了
    {
        QMessageBox::information(this, tr("查找"),
                     tr("存在姓名匹配的联系人，序号为 %1 ").arg(ix) );
        //设置列表控件当前选中条目为该序号
        ui->listWidget->setCurrentRow( ix );
        ui->listWidget->currentItem()->setSelected(true); //高亮色
        ui->listWidget->setFocus(); //显示焦点
    }
}

//按照姓名排序
void Widget::on_pushButtonSort_clicked()
{
    //获取计数
    int nCount = m_listContacts.count();
    if( nCount <= 1 )
    {
        return; //没有联系人或者只有 1 个，不需要排序
    }
    //存在 2 个以上联系人，直接调用排序函数
    ::qSort( m_listContacts );
    //清空列表控件，然后按照排序后的结果显示
    ui->listWidget->clear();
    //循环添加条目给列表控件
    for(int i=0; i<nCount; i++)
    {
        ui->listWidget->addItem( m_listContacts[i].toString() );
    }
    //列表控件和列表对象的同步完毕
}

//保存到文件 *.ds
void Widget::on_pushButtonSave_clicked()
{
    //获取计数
    int nCount = m_listContacts.count();
    if(nCount < 1) //没有元素
    {
        return;
    }
    //存在元素，先获取要打开的文件名
    QString strFile = QFileDialog::getSaveFileName(this, tr("保存文件"), tr("./test.ds"),
                      tr("QDataStream Files (*.ds)") );
    //判断文件名是否为空
    if( strFile.isEmpty() )
    {
        return; //用户没有设置保存的文件名
    }
    //设置了文件名，定义文件对象并尝试打开
    QFile fileOut(strFile);
    if( ! fileOut.open( QIODevice::WriteOnly ) )
    {
        QMessageBox::warning(this, tr("保存文件"), tr("指定文件名无法打开，请检查文件名和写入权限。"));
        return;
    }
    //正常打开
    QDataStream ds( &fileOut );
    //输出到文件只需一句
    ds<<m_listContacts; //QList 和 Contact 都有配套的流操作符函数，因此可以这样一句搞定
    //保存成功
    QMessageBox::information(this, tr("保存文件"), tr("保存成功！"));
    //关闭文件
    ds.setDevice(NULL);
    fileOut.close();
}

//从文件 *.ds 读取联系人并显示
void Widget::on_pushButtonOpen_clicked()
{
    //获取要打开的文件名
    QString strFile = QFileDialog::getOpenFileName(this, tr("打开文件"), tr("./test.ds"),
                      tr("QDataStream Files (*.ds)") );
    //判断是否为空
    if( strFile.isEmpty() )
    {
        return; //用户没设置要打开的文件名
    }
    //设置了文件名，定义文件对象，并尝试打开
    QFile fileIn( strFile );
    if( ! fileIn.open( QIODevice::ReadOnly ) )
    {
        QMessageBox::warning(this, tr("打开文件"), tr("无法打开指定文件，请检查文件名和读取权限。"));
        return;
    }
    //正常打开
    QDataStream ds( &fileIn );
    //先清空旧的列表对象和列表控件内容
    m_listContacts.clear();
    ui->listWidget->clear();
    //加载
    ds>>m_listContacts; //QList 和 Contact 都有配套的流操作符函数，因此可以这样一句搞定
    //读取完毕，需要同步显示到列表控件
    int nCount = m_listContacts.count();
    for(int i=0; i<nCount; i++)
    {
        ui->listWidget->addItem( m_listContacts[i].toString() );
    }
    //同步完成
    QMessageBox::information(this, tr("打开文件"), tr("打开文件成功，并已加载联系人列表。"));
    //关闭文件
    ds.setDevice(NULL);
    fileIn.close();
}

