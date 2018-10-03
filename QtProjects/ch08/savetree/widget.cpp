#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //设置树的列数和默认树头文本
    ui->treeWidget->setColumnCount( 1 );
    ui->treeWidget->headerItem()->setText(0, "TreeHeader");
    //构建顶级节点 A
    QTreeWidgetItem *itemA = new QTreeWidgetItem();
    itemA->setText(0, "A");
    //设置条目可以双击编辑
    itemA->setFlags( itemA->flags() | Qt::ItemIsEditable );
    ui->treeWidget->addTopLevelItem( itemA );
    //新建 A 的两个子节点 B、C，并设置可以双击编辑
    QTreeWidgetItem *itemB = new QTreeWidgetItem(itemA);//itemA为父节点
    itemB->setText(0, "B");
    itemB->setFlags( itemB->flags() | Qt::ItemIsEditable );
    QTreeWidgetItem *itemC = new QTreeWidgetItem(itemA);//itemA为父节点
    itemC->setText(0, "C");
    itemC->setFlags( itemC->flags() | Qt::ItemIsEditable );
    //展开所有节点
    ui->treeWidget->expandAll();

    //设置默认文件名
    ui->lineEditFileName->setText( "s.tree" );
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButtonAddTop_clicked()
{
    //获取编辑框条目文本
    QString strText = ui->lineEditItemText->text();
    if(strText.isEmpty()) //空文本不处理
    {
        QMessageBox::warning(this, tr("添加"), tr("条目文本为空不能添加。"));
        return;
    }
    //新建节点
    QTreeWidgetItem *itemNew = new QTreeWidgetItem();
    itemNew->setText(0, strText);
    //设置可以双击编辑
    itemNew->setFlags( itemNew->flags() | Qt::ItemIsEditable );
    ui->treeWidget->addTopLevelItem( itemNew );
    ui->treeWidget->setFocus(); //设置显示焦点
}

void Widget::on_pushButtonAddChild_clicked()
{
    //获取当前选中节点
    QTreeWidgetItem *curItem = ui->treeWidget->currentItem();
    if(NULL == curItem)
    {
        QMessageBox::warning(this, tr("添加子节点"), tr("未选中节点，无法添加子节点。"));
        return;
    }
    //获取编辑框条目文本
    QString strText = ui->lineEditItemText->text();
    if(strText.isEmpty()) //空文本不处理
    {
        QMessageBox::warning(this, tr("添加子节点"), tr("条目文本为空不能添加。"));
        return;
    }
    //新建节点，父节点为 curItem
    QTreeWidgetItem *itemChild = new QTreeWidgetItem( curItem );
    itemChild->setText(0, strText);
    //设置双击可以编辑
    itemChild->setFlags( itemChild->flags() | Qt::ItemIsEditable );
    //展开条目并设置显示焦点
    ui->treeWidget->expandItem( curItem );
    ui->treeWidget->setFocus();
}

void Widget::on_pushButtonEditHeader_clicked()
{
    //获取编辑框条目文本
    QString strText = ui->lineEditItemText->text();
    if(strText.isEmpty()) //空文本不处理
    {
        QMessageBox::warning(this, tr("修改树头"), tr("条目文本为空，不能修改树头文本。"));
        return;
    }
    //修改树头文本
    ui->treeWidget->headerItem()->setText(0, strText);
}

void Widget::on_pushButtonSaveFile_clicked()
{
    //获取文件名编辑框内容
    QString strFileName = ui->lineEditFileName->text().trimmed();
    //判断是否为空
    if( strFileName.isEmpty() )
    {
        QMessageBox::warning(this, tr("保存"), tr("文件名为空，无法保存。"));
        return;
    }
    //尝试打开文件，只写模式
    m_file.setFileName( strFileName );
    if( ! m_file.open( QIODevice::WriteOnly ) )
    {
        QMessageBox::warning(this, tr("打开"), tr("要写入的文件无法打开，请检查文件名或权限。"));
        return;
    }
    //已正常打开，设置数据流
    m_ds.setDevice( &m_file );

    //先写入树头条目，列数目就是树头条目的 columnCount()，不需要单独保存列数
    QTreeWidgetItem *iHeader = ui->treeWidget->headerItem();
    m_ds<< (*iHeader); //树头是孤立的，没有子节点，不需要写子节点计数

    //获取隐形根条目，虽然顶级条目 parent 指针是 NULL，但是隐形根条目的子节点是顶级条目
    //隐形根条目可以像普通条目递归使用，为隐形根条目添加或删除子条目，就是添加或删除顶级条目
    QTreeWidgetItem *iroot = ui->treeWidget->invisibleRootItem();

    //对隐形根条目递归保存整个树
    SaveTree(iroot);
    //保存完毕
    QMessageBox::information(this, tr("保存完毕"), tr("保存节点到文件完毕。"));

    //关闭文件，数据流置空
    m_file.close();
    m_ds.setDevice(NULL);
    //返回
    return;
}

//先有父，后有子，我们按照先序递归遍历保存节点
//每个节点苦工代码保存自己数据和儿子节点数，然后对儿子节点递归调用本函数
//父子节点是紧密相邻存储的，知道儿子节点数就能恢复父子关系
void Widget::SaveTree(QTreeWidgetItem *curItem)
{
    if(NULL == curItem) return; //空指针不处理
    //获取子节点数目
    int nChildCount = curItem->childCount();
    //递归截止判断，叶子节点是递归最底层
    if( nChildCount < 1 )
    {
        //所有节点都保存自身数据和子节点数，叶子的子节点数为 0
        m_ds<< (*curItem) << nChildCount;
        return;
    }

    //先序递归，苦工代码在前
    //苦工代码，保存自己条目数据和儿子节点数，儿子节点数用于恢复父子关系
    m_ds<< (*curItem) << nChildCount;

    //踢皮球代码，枚举所有儿子，叫他们干活
    for(int i=0; i<nChildCount; i++)
    {
        QTreeWidgetItem *curChild = curItem->child( i );
        SaveTree( curChild );//递归调用
    }
    //返回
    return;
}

void Widget::on_pushButtonClearTree_clicked()
{
    //清空树形结构
    ui->treeWidget->clear();
    //设置树头文本为空
    ui->treeWidget->headerItem()->setText(0, "");
    //qDebug()<<"Header:"<<ui->treeWidget->headerItem()<<" , invisibleRoot:"<<ui->treeWidget->invisibleRootItem();
}

void Widget::on_pushButtonLoadFile_clicked()
{
    //获取文件名编辑框内容
    QString strFileName = ui->lineEditFileName->text().trimmed();
    //判断是否为空
    if( strFileName.isEmpty() )
    {
        QMessageBox::warning(this, tr("文件名"), tr("文件名为空，无法加载。"));
        return;
    }
    //尝试打开文件，只读模式
    m_file.setFileName( strFileName );
    if( ! m_file.open( QIODevice::ReadOnly ) )
    {
        QMessageBox::warning(this, tr("打开"), tr("无法打开目标文件，请检查文件名或权限。"));
        return;
    }
    //已正常打开，设置数据流
    m_ds.setDevice( &m_file );

    //清空树形结构，槽函数可以像普通函数一样调用
    on_pushButtonClearTree_clicked();

    //获取树头条目指针
    QTreeWidgetItem *iHeader = ui->treeWidget->headerItem();
    //读取数据到树头，树头数据里自带了树的列计数 columnCount()
    m_ds >> (*iHeader);
    int nColCount = iHeader->columnCount();
    qDebug()<<"Header columns: "<<nColCount; //调试信息方便排查问题
    //每读取一次数据，都进行异常判断
    if( ( nColCount < 0)
        || (nColCount > MAX_COLS) )
    {
        //异常状态
        QMessageBox::critical(this, tr("树头加载异常"),
            tr("树头条目加载异常，列计数小于 0 或大于 1000。"));

        ui->treeWidget->setColumnCount( 1 ); //列数还原为 1

        //关闭文件，数据流置空
        m_file.close();
        m_ds.setDevice(NULL);
        //返回
        return;
    }

    //获取隐形根条目，隐形根条目是一直存在的，隐形根条目的列数为 0
    QTreeWidgetItem *iroot = ui->treeWidget->invisibleRootItem();

    //隐身根条目已有内存空间，不需要分配
    //调用递归函数，先序递归创建树结构
    LoadTree( iroot );

    //加载结束
    QString strMsg = tr("加载文件中树形节点结束。");
    //数据里状态测试
    if( m_ds.status() != QDataStream::Ok )
    {
        strMsg += tr("\r\n文件读取异常，只加载了合格的部分数据。");
    }
    if( ! m_ds.atEnd() )
    {
        int nres = m_file.size() - m_file.pos();
        strMsg += tr("\r\n文件内容未全部加载，后面数据不合格或与该树无关。\r\n剩余未读数据： %1 B").arg( nres );
    }
    //显示消息框
    QMessageBox::information(this, tr("加载文件结束"), strMsg);
    //全部展开
    ui->treeWidget->expandAll();

    //关闭文件，数据流置空
    m_file.close();
    m_ds.setDevice(NULL);
    //返回
    return;
}

//先序递归加载树的节点
void Widget::LoadTree(QTreeWidgetItem *curItem)
{
    if(NULL == curItem) return; //空指针不处理
    //递归截止判断，树没有创建完，不能用叶子节点判断
    //用数据流的结束标志作为截止判断
    if( m_ds.atEnd() )
    {
        //没有数据了，直接返回
        qDebug()<<"File end. This is an empty node.";
        return;
    }
    //子节点数目
    int nChildCount = 0;
    //先序递归，苦工代码在先
    //苦工代码，读取节点数据和子节点数
    m_ds>> (*curItem) >> nChildCount;
    //列计数
    int nColCount = curItem->columnCount();
    //注意递归函数和循环体里面不要弹出任何消息框，因为如果出问题容易一直弹窗弹到死机。
    //打印信息
    qDebug()<<"curItem text: "<<curItem->text(0)
            <<" , colCount: "<<nColCount
            <<" , childCount"<<nChildCount;
    //进行异常判断
    if( (nChildCount < 0)
            || (nColCount < 0)
            || (nColCount > MAX_COLS) )
    {
        //子节点数是负数，或条目的列计数不是 0 ~ 1000
        qDebug()<<"This is an error node.";
        return;
    }

    //如果数据正常
    //踢皮球代码
    for(int i=0; i<nChildCount; i++)
    {
        //分配子节点空间，构造函数自动设置父节点为 curItem
        QTreeWidgetItem *curChild = new QTreeWidgetItem( curItem );
        //双击可编辑的标志位不是通用数据，不会写入文件
        //手动设置双击可编辑
        curChild->setFlags( curChild->flags() | Qt::ItemIsEditable );

        //叫儿子们去干活，递归调用
        LoadTree( curChild );
    }
    //返回
    return;
}
