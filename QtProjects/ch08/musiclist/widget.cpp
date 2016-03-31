#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QMessageBox>  //消息框
#include <QListWidget>  //列表控件
#include <QListWidgetItem>  //列表控件条目
#include <QFileDialog>  //文件对话框
#include <QFileInfo>    //查询文件信息

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //开启列表控件多选模式
    ui->listWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
    //开启自动排序
    ui->checkBoxAutoSort->setCheckState(Qt::Checked);
}

Widget::~Widget()
{
    delete ui;
}
//支持一次添加多个音乐文件
void Widget::on_pushButtonAdd_clicked()
{
    QStringList slist = QFileDialog::getOpenFileNames(
                this,
                tr("添加多个音乐文件"),
                tr("."),
                tr("Music files(*.mp3 *.wma *.wav);;All files(*)")
                );
    //判断文件名个数
    int nCount = slist.count();
    if(nCount < 1)
    {
        return;
    }
    //有选中的文件，逐个添加
    for(int i=0; i<nCount; i++)
    {
        //新建条目，并自动加到列表控件
        QListWidgetItem *theItem = new QListWidgetItem(ui->listWidget);
        //取出文件基本的短名设置为条目字符串
        QFileInfo fi(slist[i]);
        theItem->setText( fi.completeBaseName() );
        //设置全路径为工具提示信息
        theItem->setToolTip( fi.absoluteFilePath() );
    }
    //添加完毕
}
//支持一次删除多个条目
void Widget::on_pushButtonDel_clicked()
{
    //获取已选中的列表条目
    QList<QListWidgetItem *> itemList = ui->listWidget->selectedItems();
    //判断数目
    int nCount = itemList.count();
    if( nCount < 1 )
    {
        return;
    }
    //有选中的条目需要删除
    //一般删除多个条目时，从尾部开始删除，这样删除过程中前面的条目行号不会变
    for(int i=nCount-1; i>=0; i--)
    {
        //根据条目求出行号
        int theRow = ui->listWidget->row( itemList[i] );
        //移除条目
        ui->listWidget->takeItem( theRow );
        //彻底从内存删除
        delete itemList[i];     itemList[i] = NULL;
    }
    //清空临时条目列表
    itemList.clear();
}
//是否自动排序
void Widget::on_checkBoxAutoSort_clicked(bool checked)
{
    if(checked)
    {
        //开启自动排序
        ui->listWidget->setSortingEnabled(true);
        //把逆序排列的复选框启用
        ui->checkBoxReverse->setEnabled(true);
        //判断是正序还是逆序
        if( ui->checkBoxReverse->checkState() != Qt::Checked )
        {
            //正序
            ui->listWidget->sortItems(Qt::AscendingOrder);
        }
        else
        {
            //逆序
            ui->listWidget->sortItems(Qt::DescendingOrder);
        }
    }
    else
    {
        //不自动排序
        ui->listWidget->setSortingEnabled(false);
        //禁用逆序复选框
        ui->checkBoxReverse->setEnabled(false);
    }
}
//是否逆序排列
void Widget::on_checkBoxReverse_clicked(bool checked)
{
    if( ! checked)
    {
        //正序
        ui->listWidget->sortItems(Qt::AscendingOrder);
    }
    else
    {
        //逆序
        ui->listWidget->sortItems(Qt::DescendingOrder);
    }
}
// http://blog.sina.com.cn/s/blog_4ee9576d010098f7.html
// 这里导出为最简单的 m3u 格式列表
void Widget::on_pushButtonExportM3U_clicked()
{
    //判断列表条目总数
    int nCount = ui->listWidget->count();
    if(nCount < 1)
    {
        return;
    }
    //获取要保存的文件名
    QString strName = QFileDialog::getSaveFileName(
                this,
                tr("保存为 M3U 文件"),
                tr("."),
                tr("M3U files(*.m3u)")
                );
    //判断文件名
    if(strName.isEmpty())
    {
        return;
    }
    //打开文件
    QFile fileOut(strName);
    // QIODevice::Text 自动转换换行符为本地系统风格
    if( ! fileOut.open( QIODevice::WriteOnly | QIODevice::Text) )
    {
        QMessageBox::warning(this, tr("打开文件"),
                             tr("无法打开指定文件，请检查是否有写入权限！"));
        return;
    }
    //正确打开之后，定义文本流
    //文本流自动转换文本编码为本地系统格式
    //但文本流不处理换行符，换行符本地化通过文件打开时的 QIODevice::Text 指定
    QTextStream tsOut(&fileOut);
    //先写入文件头
    tsOut<<tr("#EXTM3U")<<endl;
    //逐个文件名条目写入
    for(int i=0; i<nCount; i++)
    {
        QString strCurName = ui->listWidget->item(i)->toolTip();
        tsOut<<strCurName<<endl;
    }
    //完成
}
//条目文本查找，包含模板字符串的都高亮显示
void Widget::on_pushButtonFind_clicked()
{
    //获取模板字符串
    QString strTemplate = ui->lineEditTemplate->text();
    //判断字符串是否为空
    if(strTemplate.isEmpty())
    {
        return;
    }
    //先把旧的高亮显示条目都清空
    ui->listWidget->setCurrentItem(NULL, QItemSelectionModel::Clear);

    //查找匹配的条目文本，第二个参数控制匹配行为
    QList<QListWidgetItem *> list =
            ui->listWidget->findItems(strTemplate, Qt::MatchContains);
    //判断是否有匹配的
    int nCount = list.count();
    if(nCount < 1)
    {
        QMessageBox::information(this, tr("查找条目"),
                                 tr("没有找到匹配的条目文本。"));
        return;
    }
    //把第一个匹配的条目设置为当前条目
    ui->listWidget->setCurrentItem( list[0] );
    //自动滚动到第一条匹配选中的条目，这个条目显示在可视区域顶部
    ui->listWidget->scrollToItem( list[0], QAbstractItemView::PositionAtTop);

    //然后再把所有匹配的条目设置为高亮选中
    for(int i=0; i<nCount; i++)
    {
        list[i]->setSelected(true); //条目自己可以设置高亮选中
    }

    //将显示焦点切换到列表控件
    ui->listWidget->setFocus();
}
