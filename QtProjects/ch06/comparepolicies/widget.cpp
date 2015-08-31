#include "widget.h"
#include "ui_widget.h"
#include <QLineEdit>    //单行编辑器
#include <QHBoxLayout>  //水平布局器
#include <QVBoxLayout>  //垂直布局器
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //按钮的建议尺寸和最小建议尺寸
    qDebug()<<tr("Preferred 按钮：")
           <<ui->pushButtonPreferred->sizeHint()
           <<ui->pushButtonPreferred->minimumSizeHint();
    qDebug()<<tr("Expanding 按钮：")
           <<ui->pushButtonExpanding->sizeHint()
           <<ui->pushButtonExpanding->minimumSizeHint();


    m_pWidget = NULL;   //初始空指针
    CreateWidget();     //构建第二个示范窗口
}

Widget::~Widget()
{
    //删除第二个窗口
    if(m_pWidget != NULL)
    {
        delete m_pWidget;   m_pWidget = NULL;
    }
    //删除ui
    delete ui;
}

//建立第二个示范窗口，包括内部的单行编辑控件和布局器
//仿造主界面的架构，只是把按钮换成单行编辑器
void Widget::CreateWidget()
{
    //构建第二个示范窗口
    m_pWidget = new QWidget(this, Qt::Window);  //独立窗口
    m_pWidget->resize(480, 360);
    m_pWidget->setWindowTitle(tr("单行编辑器的布局"));
    //主布局器是垂直排列的三行
    QVBoxLayout *mainLayout = new QVBoxLayout(m_pWidget);


    //构建六个单行编辑器，分成三行做对比
    //第一行
    //第一个是固定尺寸的
    QLineEdit *leFixed = new QLineEdit(m_pWidget);
    leFixed->setText(tr("Fixed"));
    QSizePolicy sp = leFixed->sizePolicy();
    //修改第一个的水平策略为 Fixed
    sp.setHorizontalPolicy(QSizePolicy::Fixed);
    leFixed->setSizePolicy(sp);

    //第二个编辑器
    QLineEdit *lePreferred = new QLineEdit(m_pWidget);
    lePreferred->setText(tr("Preferred"));
    sp = lePreferred->sizePolicy();
    //修改第二个的水平策略为 Preferred
    sp.setHorizontalPolicy(QSizePolicy::Preferred);
    lePreferred->setSizePolicy(sp);

    //第一行的布局器
    QHBoxLayout *lay1 = new QHBoxLayout();
    lay1->addWidget(leFixed);       //添加第一个编辑器
    lay1->addWidget(lePreferred);   //添加第二个编辑器
    //把第一行的布局器添加到主布局器
    mainLayout->addLayout(lay1);


    //第二行
    //第三个编辑器
    QLineEdit *lePreferred2 = new QLineEdit(m_pWidget);
    lePreferred2->setText(tr("Preferred2"));
    sp = lePreferred->sizePolicy();
    //修改第三个的水平策略为 Preferred
    sp.setHorizontalPolicy(QSizePolicy::Preferred);
    lePreferred2->setSizePolicy(sp);

    //第四个编辑器
    QLineEdit *leMinimum = new QLineEdit(m_pWidget);
    leMinimum->setText(tr("Minimum"));
    sp = leMinimum->sizePolicy();
    //修改第三个的水平策略为 Minimum
    sp.setHorizontalPolicy(QSizePolicy::Minimum);
    leMinimum->setSizePolicy(sp);

    //第二行的布局器
    QHBoxLayout *lay2 = new QHBoxLayout();
    lay2->addWidget(lePreferred2);
    lay2->addWidget(leMinimum);
    //添加到主布局器
    mainLayout->addLayout(lay2);


    //第三行
    //第五个编辑器
    QLineEdit *leMinimum2 = new QLineEdit(m_pWidget);
    leMinimum2->setText(tr("Minimum2"));
    sp = leMinimum2->sizePolicy();
    //修改第五个的水平策略为 Minimum
    sp.setHorizontalPolicy(QSizePolicy::Minimum);
    leMinimum2->setSizePolicy(sp);

    //第六个编辑器
    QLineEdit *leExpanding = new QLineEdit(m_pWidget);
    leExpanding->setText(tr("Expanding"));
    sp = leExpanding->sizePolicy();
    //修改第六个的水平策略为 Expanding
    sp.setHorizontalPolicy(QSizePolicy::Expanding);
    leExpanding->setSizePolicy(sp);

    //第三行的布局器
    QHBoxLayout *lay3 = new QHBoxLayout();
    lay3->addWidget(leMinimum2);
    lay3->addWidget(leExpanding);
    mainLayout->addLayout(lay3);


    //设置该窗口的主布局器
    m_pWidget->setLayout(mainLayout);
    //如果只有一个布局器的 parent 设置为该窗口，那么可以不调用 setLayout()
    //上面的 setLayout() 一句其实可以省略，mainLayout 自动是主布局器

    //打印信息
    qDebug()<<tr("Fixed 编辑器建议尺寸：")<<leFixed->sizeHint();
    qDebug()<<tr("Preferred 编辑器建议尺寸：")<<lePreferred->sizeHint();
    qDebug()<<tr("Preferred 编辑器最小建议尺寸：")<<lePreferred->minimumSizeHint();
    qDebug()<<tr("Minimum 编辑器建议尺寸：")<<leMinimum->sizeHint();
    qDebug()<<tr("Expanding 编辑器建议尺寸：")<<leExpanding->sizeHint();
    qDebug()<<tr("Expanding 编辑器最小建议尺寸：")<<leExpanding->minimumSizeHint();
}

//点击按钮弹出第二个窗口
void Widget::on_pushButtonFixed_clicked()
{
    if(m_pWidget != NULL)
    {
        m_pWidget->show();  //显示
    }
}
