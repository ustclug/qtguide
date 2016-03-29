#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QIcon>        //图标类
#include <QFileDialog>  //程序运行时可打开新图标文件
#include <QMessageBox>  //消息框
#include <QFile>        //文件类
#include <QDataStream>  //数据流，加载和保存条目数据

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //先把所有条目设置为可编辑特性，并且显示条目的复选框状态
    int nCount = ui->listWidget->count();
    for(int i=0; i<nCount; i++)
    {
        QListWidgetItem *item = ui->listWidget->item(i);
        //启用可编辑特性标志位
        item->setFlags( (item->flags()) | Qt::ItemIsEditable );
        //显示复选框
        item->setCheckState(Qt::Unchecked);
        //DOTA最多携带六个装备，有复选框之后，勾选表示携带，不勾选是不携带
        //后面代码检查只能带六个的限制条件
    }
    //程序运行时新增的装备条目也要开启编辑标志位、复选框，等会实现
    //装备名称可以直接双击修改
}

Widget::~Widget()
{
    delete ui;
}

//当前高亮选中的条目序号变化
void Widget::on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    if( NULL == current )   //空指针不处理
    {
        return;
    }
    //获取新选中条目的工具提示信息显示到单行编辑器
    QString strToolTip = current->toolTip();
    ui->lineEditToolTip->setText( strToolTip );
    //在 "编辑工具提示" 按钮对应的槽函数实现修改条目的工具提示
}
//修改条目的工具提示信息，相当于修改装备描述
void Widget::on_pushButtonEditToolTip_clicked()
{
    //新的工具提示信息
    QString strNew = ui->lineEditToolTip->text();
    //获取当前选中条目
    QListWidgetItem *curItem = ui->listWidget->currentItem();
    if( curItem != NULL )   //检查是否为空指针
    {
        //设置新的工具提示信息
        curItem->setToolTip(strNew);
    }
}

//条目内部数据发生变化，包括文本变化、图标变化、工具提示变化、复选状态变化等等
//需要自己筛选用到的变化信息，这里查看复选状态的变化
//限定 DOTA 装备只能携带 6 个
void Widget::on_listWidget_itemChanged(QListWidgetItem *item)
{
    //空指针不处理
    if( NULL == item)
    {
        return;
    }
    //实际存在的条目变化
    if(item->checkState() != Qt::Checked)
    {
        //复选框没选中，没携带的不检查
        return;
    }
    //如果复选框处于选中状态，检查装备携带是否超过 6 个
    int nCount = ui->listWidget->count();
    int nUsingItemsCount = 0;
    for(int i=0; i<nCount; i++)
    {
        QListWidgetItem* theItem = ui->listWidget->item(i);
        if( theItem->checkState() == Qt::Checked )
        {
            //携带数加一
            nUsingItemsCount++;
        }
    }
    //判断是否超过 6 个
    if( nUsingItemsCount > 6 )
    {
        QMessageBox::warning(this, tr("携带数目检查"), tr("DOTA 装备最多带 6 个！"));
        //把当前变化的 item 设置为非选中状态
        item->setCheckState( Qt::Unchecked );
    }
}
//用户选择装备图标文件，添加新装备条目
void Widget::on_pushButtonAdd_clicked()
{
    //获取新装备图标的文件路径
    QString strItemFileName = QFileDialog::getOpenFileName(
                this,
                tr("选择装备图标文件"),
                tr("."),
                tr("Image files(*.jpg *.png *.bmp);;All files(*)") );
    if(strItemFileName.isEmpty())
    {
        //没有文件名，返回
        return;
    }
    //打开装备图标文件
    QIcon iconNew(strItemFileName);
    //新建条目，文本初始是默认的，自动添加到列表控件
    QListWidgetItem *itemNew = new QListWidgetItem(
                iconNew,
                tr("新装备名称"),
                ui->listWidget
                );
    //开启条目编辑特性
    itemNew->setFlags( (itemNew->flags()) | Qt::ItemIsEditable );
    //显示复选框
    itemNew->setCheckState( Qt::Unchecked );
    //设置新的当前条目
    ui->listWidget->setCurrentItem( itemNew );
    //新增条目自动启用编辑功能，让用户可以立即修改新装备名称
    ui->listWidget->editItem( itemNew );
}
//删除当前选中的装备条目
void Widget::on_pushButtonDel_clicked()
{
    int nCurRow = ui->listWidget->currentRow();
    if( nCurRow < 0)
    {
        //没有选中的条目
        return;
    }
    //从列表控制移除选中的条目
    QListWidgetItem *itemDel = ui->listWidget->takeItem( nCurRow );
    //彻底删除移除的条目
    delete itemDel; itemDel = NULL;
}
//切换小图标文本模式和大图标模式
void Widget::on_pushButtonViewMode_clicked()
{
    QListView::ViewMode vm = ui->listWidget->viewMode();
    if( QListView::ListMode == vm )
    {
        //切换到大图标显示，大图标可以拖动，但是不会改变内部真实的条目序号
        ui->listWidget->setViewMode( QListView::IconMode );
    }
    else
    {
        //切换到小图标文字显示，条目不可拖动
        ui->listWidget->setViewMode( QListView::ListMode );
    }
}

//保存所有条目到文件
void Widget::on_pushButtonSave_clicked()
{
    //获取保存文件名
    QString strSaveName = QFileDialog::getSaveFileName(
                this,
                tr("保存items文件"),
                tr("."),
                tr("Items files(*.items)"));
    //判断文件名
    if( strSaveName.isEmpty() )
    {
        return;
    }
    //打开要写入的文件
    QFile fileSave(strSaveName);
    if( ! fileSave.open( QIODevice::WriteOnly ))
    {
        //无法打开要写入的文件
        QMessageBox::warning(this, tr("打开写入文件"),
                             tr("打开要写入的文件失败，请检查文件名和是否具有写入权限！"));
        return;
    }
    //创建数据流
    QDataStream dsOut(&fileSave);
    //先写入列表条目计数
    qint32 nCount = ui->listWidget->count();
    dsOut<<nCount;
    //逐个写入条目
    for(qint32 i=0; i<nCount; i++)
    {
        QListWidgetItem *theItem = ui->listWidget->item(i);
        dsOut<< *theItem;   //把条目对象写入数据流，不是写指针数值
        //数据流仅写入条目通用数据，条目的非通用数据不写入，比如条目的标志位不写
    }
    //写入完毕
}
//加载之前保存的文件
void Widget::on_pushButtonLoad_clicked()
{
    //获取要加载的文件名
    QString strOpenName = QFileDialog::getOpenFileName(
                this,
                tr("打开items文件"),
                tr("."),
                tr("Items files(*.items)"));
    //判断文件名
    if(strOpenName.isEmpty())
    {
        return;
    }
    //打开文件
    QFile fileOpen(strOpenName);
    if( ! fileOpen.open(QIODevice::ReadOnly))
    {
        //打开出错
        QMessageBox::warning(this, tr("打开文件"),
                             tr("打开指定文件失败，请检查文件是否存在和读取权限！"));
        return;
    }
    //创建读取数据流
    QDataStream dsIn(&fileOpen);
    //读取条目计数
    qint32 nCount;
    dsIn>>nCount;
    //判断计数数值
    if(nCount <= 0)
    {
        QMessageBox::warning(this, tr("文件加载"),
                             tr("文件中无条目数据可以加载！"));
        return;
    }
    //新建各个条目，并加载文件中的条目数据
    for(qint32 i=0; i<nCount; i++)
    {
        //新建条目，条目自动添加到列表控件
        QListWidgetItem *theItem = new QListWidgetItem(ui->listWidget);
        //加载条目通用数据，文字、图标、工具提示、复选状态等是通用数据，在数据流里面有保存
        dsIn>> *theItem;

        //条目的非通用数据是不保存到数据流的
        //这里需要手动把条目设置为可编辑的特性标志位
        theItem->setFlags( (theItem->flags()) | Qt::ItemIsEditable );
    }
    //加载完毕
}

