#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButtonAddTop_clicked()
{
    //获取省市名称、经度、纬度三个文本
    QString strName = ui->lineEditName->text();
    QString strLon = ui->lineEditLon->text();
    QString strLat = ui->lineEditLat->text();
    //检查字符串都不空才继续
    if( strName.isEmpty() || strLon.isEmpty() || strLat.isEmpty() )
    {
        QMessageBox::information(this, tr("输入检查"), tr("三个编辑框均需要输入信息！"));
        return;
    }
    //新建树形条目，设置三列文本，名称、经度、纬度
    QTreeWidgetItem *itemNew = new QTreeWidgetItem();
    itemNew->setText(0, strName);
    itemNew->setText(1, strLon);
    itemNew->setText(2, strLat);
    //添加顶级条目
    ui->treeWidget->addTopLevelItem(itemNew);
    ui->treeWidget->setFocus(); //设置树形控件显示焦点
}

void Widget::on_pushButtonAddChild_clicked()
{
    //获取当前选中节点
    QTreeWidgetItem *curItem = ui->treeWidget->currentItem();
    if( NULL == curItem )
    {
        QMessageBox::information(this, tr("无选中节点"), tr("请先选中一个节点，然后为其添加子节点！"));
        return;
    }
    //获取省市名称、经度、纬度三个文本
    QString strName = ui->lineEditName->text();
    QString strLon = ui->lineEditLon->text();
    QString strLat = ui->lineEditLat->text();
    //检查字符串都不空才继续
    if( strName.isEmpty() || strLon.isEmpty() || strLat.isEmpty() )
    {
        QMessageBox::information(this, tr("输入检查"), tr("三个编辑框均需要输入信息！"));
        return;
    }
    //新建子节点，添加三列文本
    QTreeWidgetItem *itemChild = new QTreeWidgetItem();
    itemChild->setText(0, strName);
    itemChild->setText(1, strLon);
    itemChild->setText(2, strLat);
    //添加到选中节点
    curItem->addChild( itemChild );
    //自动展开显示新加的子节点
    ui->treeWidget->expandItem( curItem );
    ui->treeWidget->setFocus(); //设置树形控件显示焦点
}

void Widget::on_pushButtonDelLeaf_clicked()
{
    //获取当前选中节点
    QTreeWidgetItem *curItem = ui->treeWidget->currentItem();
    if( NULL == curItem )
    {
        QMessageBox::warning(this, tr("未选中节点"), tr("未选中节点，没东西删除。"));
        return;
    }
    //判断是否为叶子节点
    if( curItem->childCount() > 0 )
    {
        //该节点还有子节点，不能直接删除，因为子孙节点尚未删除
        QMessageBox::warning(this, tr("不是叶子节点"), tr("不是叶子节点，不能删除！"));
        return;
    }
    //是叶子节点可以删除
    //凡是知道指针的叶子节点，可以直接 delete
    //QTreeWidgetItem 析构函数会自动将条目从树形控件卸载掉
    delete curItem; curItem = NULL;
}

void Widget::on_pushButtonDelSubtree_clicked()
{
    //获取当前选中节点
    QTreeWidgetItem *curItem = ui->treeWidget->currentItem();
    if( NULL == curItem )
    {
        QMessageBox::warning(this, tr("未选中节点"), tr("未选中节点，没东西删除。"));
        return;
    }
    //递归删除节点子树
    RemoveSubtree( curItem );
}

void Widget::RemoveSubtree(QTreeWidgetItem *curLevelItem)
{
    //凡是指针，都要判断是否为空
    if( NULL == curLevelItem )
    {
        return;
    }
    //儿子节点个数
    int nCount = curLevelItem->childCount();

    //截止判断代码
    if( nCount < 1)//一个子节点都没有，已经是叶子节点
    {
        //直接删除
        delete curLevelItem;    curLevelItem = NULL;
        return; //递归层数截止
    }

    //踢皮球代码，对各个子节点调用本函数，称为递归
    for(int i=0; i<nCount; i++)
    {
        //逐个卸载子节点
        QTreeWidgetItem *curChild = curLevelItem->takeChild(i);
        //递归调用本函数，即踢皮球代码，叫儿子们自己去处理
        RemoveSubtree(curChild);
    }
    //儿孙们都删除干净了，儿孙们先做苦工，自己后做苦工，叫后序递归

    //苦工代码，自己动手删除自己
    delete curLevelItem;    curLevelItem = NULL;
    return; //返回父辈
}



