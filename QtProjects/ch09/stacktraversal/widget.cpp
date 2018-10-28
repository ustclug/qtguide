#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //树形控件只有一列数据
    ui->treeWidget->setColumnCount(1);
    //添加顶级节点
    QTreeWidgetItem *itemA = new QTreeWidgetItem();
    itemA->setText(0, "A");
    ui->treeWidget->addTopLevelItem( itemA );
    //A的两个子节点B、C
    QTreeWidgetItem *itemB = new QTreeWidgetItem(itemA);
    itemB->setText(0, "B");
    QTreeWidgetItem *itemC = new QTreeWidgetItem(itemA);
    itemC->setText(0, "C");
    //B的两个子节点D、E
    QTreeWidgetItem *itemD = new QTreeWidgetItem(itemB);
    itemD->setText(0, "D");
    QTreeWidgetItem *itemE = new QTreeWidgetItem(itemB);
    itemE->setText(0, "E");
    //C的两个子节点F、G
    QTreeWidgetItem *itemF = new QTreeWidgetItem(itemC);
    itemF->setText(0, "F");
    QTreeWidgetItem *itemG = new QTreeWidgetItem(itemC);
    itemG->setText(0, "G");
    //展开所有
    ui->treeWidget->expandAll();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButtonPreorder_clicked()
{
    //获取A节点
    QTreeWidgetItem *itemA = ui->treeWidget->topLevelItem(0);
    //进行先序遍历
    qDebug()<<tr("先序遍历：");
    PreorderByStack( itemA );
}

//使用栈实现先序遍历
void Widget::PreorderByStack(QTreeWidgetItem *curItem)
{
    //判断指针
    if(NULL == curItem) return; //空指针不处理
    //定义栈
    QStack<QTreeWidgetItem *> stackItems;
    //初始节点入栈
    stackItems.push( curItem );
    //用于遍历的条目变量
    QTreeWidgetItem *itemTreversal = NULL;
    while( ! stackItems.isEmpty() )
    {
        //栈顶的出栈
        itemTreversal = stackItems.pop();
        //先序是添加子节点之前部署工作代码，打印文本
        qDebug()<<itemTreversal->text(0);
        //子节点计数
        int nChildCount = itemTreversal->childCount();
        //如果是叶子就进行下一轮
        if( nChildCount < 1 )
        {
            continue;
        }
        else//有子节点，子节点从右往左，倒序压栈
        {
            //倒序压栈，左边子节点处于栈顶，出栈时优先处理左边子节点
            for(int i=nChildCount-1; i>=0; i--)
            {
                stackItems.push( itemTreversal->child(i) );
            }
        }
        //下一轮循环
    }//栈不空就一直循环处理
    return; //结束
}

void Widget::on_pushButtonPostorder_clicked()
{
    //获取A节点
    QTreeWidgetItem *itemA = ui->treeWidget->topLevelItem(0);
    //后序遍历
    qDebug()<<tr("后序遍历：");
    PostorderByStack( itemA );
}

//用栈实现后序遍历
void Widget::PostorderByStack(QTreeWidgetItem *curItem)
{
    //判断指针
    if(NULL == curItem) return; //空指针不处理
    //定义栈
    QStack<QTreeWidgetItem *> stackItems;
    //初始节点入栈
    stackItems.push( curItem );
    //遍历使用的条目变量
    QTreeWidgetItem *itemTraversal = NULL;
    QTreeWidgetItem *itemLast = NULL;   //上次弹出的节点
    //后序遍历时，第一步进行层次推进，父子节点先后进栈
    //第二步出栈回归上层，子节点先出栈打印，父节点后出栈
    while( ! stackItems.isEmpty() )
    {
        //后序遍历先打印所有子树，根节点要一直存在栈里，直到子树打印完才出栈
        itemTraversal = stackItems.top();
        //子节点计数
        int nChildCount = itemTraversal->childCount();
        //如果是叶子节点，推进层次截止
        if( nChildCount < 1 )
        {
            //出栈打印
            itemTraversal = stackItems.pop();
            qDebug()<<itemTraversal->text(0);
            //保存上次弹出节点，用于判断是推进层次还是回归顶层
            itemLast = itemTraversal;
            continue; //下一轮
        }
        //存在子节点时，可能是层次推进过程，也可能是回归上层的过程
        //如果上次出栈打印的是当前节点的最右边儿子，那么子树打印过了，就是回归上层
        //如果上次出栈打印的不是最右边儿子节点，那么需要进一步推进层次
        if( itemTraversal->child( nChildCount-1 ) != itemLast )
        {
            //深入递推，那么将子节点压栈
            //存在子节点，把子节点都入栈，从右向左压栈
            for(int i=nChildCount-1; i>=0; i--)
            {
                //左子节点优先在栈顶，优先打印左边的
                stackItems.push( itemTraversal->child(i) );
            }
        }
        else//回归上层，那么将当前节点出栈并打印
        {
            //出栈打印
            itemTraversal = stackItems.pop();
            qDebug()<<itemTraversal->text(0);
            //保存上次弹出节点
            itemLast = itemTraversal;
        }
        //下一轮
    }
    return; //完成
}

void Widget::on_pushButtonMidorder_clicked()
{
    //获取A节点
    QTreeWidgetItem *itemA = ui->treeWidget->topLevelItem(0);
    //中序遍历
    qDebug()<<tr("中序遍历：");
    MidorderByStack( itemA );
}

//用栈实现中序遍历
void Widget::MidorderByStack(QTreeWidgetItem *curItem)
{
    //判断指针
    if(NULL == curItem) return; //空指针不处理
    //定义栈
    QStack<QTreeWidgetItem *> stackItems;
    //初始节点入栈
    stackItems.push(curItem);
    //遍历的节点遍历
    QTreeWidgetItem *itemTraversal = NULL;
    //循环
    while( ! stackItems.isEmpty() )
    {
        //把所有层的最左节点压栈
        while( stackItems.top()->childCount() >= 1 )
        {
            stackItems.push( stackItems.top()->child(0) );
        }
        //总是从最左边节点开始出栈
        while( ! stackItems.isEmpty() )
        {
            //出栈并打印
            itemTraversal = stackItems.pop();
            qDebug()<<itemTraversal->text( 0 );
            //子节点计数
            int nChildCount = itemTraversal->childCount();
            //如果存在右边的节点
            if( nChildCount >= 2 )//存在右子树
            {
                //右边的子节点都入栈，压栈时从右往左，出栈时就是从左到右
                for(int i=nChildCount-1; i>=1; i--)
                {
                    stackItems.push( itemTraversal->child(i) );
                }
                //该节点还存在右边的子树，跳出内层循环，对右边子树按照外层循环操作
                break;
            }
        }
        //下一轮外层循环
    }
    return; //完成
}

void Widget::on_pushButtonLevels_clicked()
{
    //获取A节点
    QTreeWidgetItem *itemA = ui->treeWidget->topLevelItem(0);
    //按层遍历，显示节点层号
    qDebug()<<tr("按层遍历，显示节点层号：");
    LevelsByQueue( itemA, 0 );
}

//用队列实现按层遍历
void Widget::LevelsByQueue(QTreeWidgetItem *curItem, int curLevel)
{
    //判断指针
    if(NULL == curItem) return; //空指针不处理
    //定义两个队列，一个保存节点，另一个保存节点的层级
    QQueue<QTreeWidgetItem *> queueItems;
    QQueue<int> queueLevels;
    //初始节点入队
    queueItems.enqueue( curItem );
    queueLevels.enqueue( curLevel );
    //遍历的变量
    QTreeWidgetItem *itemTraversal = NULL;
    int nLevel = -1;
    //循环按层遍历
    while( ! queueItems.isEmpty() )
    {
        itemTraversal = queueItems.dequeue();
        nLevel = queueLevels.dequeue();
        //打印当前节点和层级
        qDebug()<<itemTraversal->text(0)<<" , "<<nLevel;
        //获取子节点计数
        int nChildCount = itemTraversal->childCount();
        //分别入队
        for(int i=0; i<nChildCount; i++)
        {
            queueItems.enqueue( itemTraversal->child( i ) );
            queueLevels.enqueue( nLevel + 1 );
        }
        //下一轮
    }
    return; //完成
}

