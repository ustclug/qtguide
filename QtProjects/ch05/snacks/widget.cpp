#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //添加盒饭组合框条目
    ui->comboBoxSnacks->addItem(tr("番茄鸡蛋"), 8.50);
    ui->comboBoxSnacks->addItem(tr("土豆烧肉"), 10.00);
    ui->comboBoxSnacks->addItem(tr("鱼香肉丝"), 10.00);
    ui->comboBoxSnacks->addItem(tr("青椒鸡蛋"), 8.50);
    ui->comboBoxSnacks->addItem(tr("地三鲜"), 9.00);

    //设置盒饭单价的范围和步进
    ui->doubleSpinBoxPrice->setRange(0.00, 100.00);
    ui->doubleSpinBoxPrice->setSingleStep(1.00);
    //设置单价的后缀 " 元"
    ui->doubleSpinBoxPrice->setSuffix(tr(" 元"));

    //设置份数计数器的范围和步进
    ui->spinBoxCount->setRange(0, 100);
    ui->spinBoxCount->setSingleStep(1);
    //设置份数滑动条的范围和步进
    ui->horizontalSlider->setRange(0, 100);
    ui->horizontalSlider->setSingleStep(1);
    //设置滑动条的刻度显示和刻度间隔
    ui->horizontalSlider->setTickPosition(QSlider::TicksBothSides);
    ui->horizontalSlider->setTickInterval(10);

    //同步份数的计数器和滑动条
    connect(ui->spinBoxCount, SIGNAL(valueChanged(int)),
            ui->horizontalSlider, SLOT(setValue(int)));
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)),
            ui->spinBoxCount, SLOT(setValue(int)));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_comboBoxSnacks_currentIndexChanged(int index)
{
    if(index < 0)   //序号为负数不处理
    {
        return;
    }
    //正常序号
    double dblPrice = ui->comboBoxSnacks->itemData(index).toDouble();
    //设置单价的浮点计数器
    ui->doubleSpinBoxPrice->setValue(dblPrice);
    //打印当前的盒饭名和单价
    qDebug()<<ui->comboBoxSnacks->currentText()<<"\t"<<dblPrice;
}

void Widget::on_pushButtonCalc_clicked()
{
    double dblTotal = ui->doubleSpinBoxPrice->value()
            * ui->spinBoxCount->value();
    //设置单行编辑控件显示文本
    ui->lineEditTotal->setText( tr("%1 元").arg(dblTotal) );
}
