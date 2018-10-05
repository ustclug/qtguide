#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //创建菜单，并关联信号和槽函数
    CreateMenu();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::CreateMenu()
{
    //创建右键菜单对象
    m_menuContext = new QMenu(tr("ContextMenu")); //右键菜单其实不显示ContextMenu文本

    //创建“添加条目”菜单项并添加到菜单
    QAction *actAdd = new QAction(tr("添加条目"), this);
    m_menuContext->addAction( actAdd );
    //创建“编辑条目”菜单项并添加到菜单
    QAction *actEdit = new QAction(tr("编辑条目"), this);
    m_menuContext->addAction( actEdit );
    //创建“删除条目”菜单项并添加到菜单
    QAction *actDel = new QAction(tr("删除条目"), this);
    m_menuContext->addAction( actDel );
    //创建“清空所有”菜单项并添加到菜单
    QAction *actClearAll = new QAction(tr("清空所有"), this);
    m_menuContext->addAction( actClearAll );

    //设置列表控件可以有自定义右键菜单
    ui->listWidget->setContextMenuPolicy( Qt::CustomContextMenu );
    //关联弹出菜单信号
    connect(ui->listWidget, SIGNAL(customContextMenuRequested(QPoint)),
            this, SLOT(onCustomContextMenuRequested(QPoint)) );

    //为四个菜单项关联点击信号到槽函数
    connect(actAdd, SIGNAL(triggered()), this, SLOT(onAddItemTriggered()));
    connect(actEdit, SIGNAL(triggered()), this, SLOT(onEditItemTriggered()));
    connect(actDel, SIGNAL(triggered()), this, SLOT(onDelItemTriggered()));
    connect(actClearAll, SIGNAL(triggered()), this, SLOT(onClearAllTriggered()));
    //创建完毕
    return;
}

//弹出右键菜单的槽函数
void Widget::onCustomContextMenuRequested(const QPoint & pos)
{
    //控件内的相对坐标转为屏幕坐标
    //是列表控件发出的信号，就用列表控件的转换函数
    QPoint screenPos = ui->listWidget->mapToGlobal( pos );
    //弹出菜单
    QAction *actRet = m_menuContext->exec( screenPos );
    if(NULL != actRet)//检查非空才能使用该指针
    {
        qDebug()<<tr("返回的菜单项：") + actRet->text();
    }
}

//添加条目菜单项的槽函数
void Widget::onAddItemTriggered()
{
    QListWidgetItem *itemNew = new QListWidgetItem(tr("新建条目"));
    //设置可以编辑
    itemNew->setFlags( itemNew->flags() | Qt::ItemIsEditable );
    //添加给控件
    ui->listWidget->addItem( itemNew );
    //设置新条目为选中的条目
    ui->listWidget->setCurrentItem( itemNew );
    //显示条目的编辑框
    ui->listWidget->editItem( itemNew );
}

//编辑条目菜单项的槽函数
void Widget::onEditItemTriggered()
{
    //获取选中的条目
    QListWidgetItem *curItem = ui->listWidget->currentItem();
    if(NULL == curItem)
    {
        qDebug()<<tr("没有选中的条目。");
        return; //返回
    }
    //设置选中条目可以编辑
    curItem->setFlags( curItem->flags() | Qt::ItemIsEditable );
    //显示选中条目的编辑框
    ui->listWidget->editItem( curItem );
}

//删除条目菜单项的槽函数
void Widget::onDelItemTriggered()
{
    //获取选中的条目
    QListWidgetItem *curItem = ui->listWidget->currentItem();
    if(NULL == curItem)
    {
        qDebug()<<tr("没有选中的条目。");
        return; //返回
    }
    //删除条目
    delete curItem; curItem = NULL;
}

//清空所有条目的菜单项槽函数
void Widget::onClearAllTriggered()
{
    //判断条目个数，如果没条目不需要操作，直接返回
    int nCount = ui->listWidget->count();
    if(nCount < 1)
    {
        return;
    }
    //提示Yes、No询问消息框，获取返回值，防止用户误操作全删
    //如果用户选“Yes”就全删，否则不操作
    int buttonRet = QMessageBox::question(this, tr("清空所有"), tr("请确认是否清空所有条目？"));
    if( QMessageBox::Yes == buttonRet )//用户选择了“Yes”
    {
        ui->listWidget->clear();
    }
    else //否则不处理
    {
        return;
    }
}

