#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QMessageBox>
#include <QHeaderView>  //表头视图类

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //设置日期编辑控件可以弹出日历
    ui->dateEdit->setCalendarPopup(true);
    //设置表格控件特性
    //每次选中整行
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    //为方便删除按钮操作，把选中模式设为单选，即每次只选中一行，而不能选中多行
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    //开启自动排序
    ui->tableWidget->setSortingEnabled(true);
    ui->tableWidget->sortByColumn(0, Qt::AscendingOrder);
    //设置末尾一列自动拉伸
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);

    //设置默认行高，把图标设置更大一些
    ui->tableWidget->verticalHeader()->setDefaultSectionSize(36);
    ui->tableWidget->setIconSize( QSize(32,32) );

    //修改主界面窗口宽度，让表格末尾列自动拉伸的效果显示出来
    QSize sz = this->size();
    sz.setWidth(640);
    this->resize(sz);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_tableWidget_currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous)
{
    if(current != NULL)//如果条目非空，打印信息
    {
        qDebug()<<tr("当前条目行号：%1，列号：%2，文本：%3")
                  .arg(current->row())
                  .arg(current->column())
                  .arg(current->text());
    }
}

void Widget::on_pushButtonAdd_clicked()
{
    QString strName = ui->lineEditName->text().trimmed();   //剔除名字两端空格
    //判断姓名是否非空
    if(strName.isEmpty())
    {
        QMessageBox::warning(this, tr("添加行"), tr("姓名不能为空！"));
        return;
    }
    //先把自动排序关掉，才能正确添加整行的条目
    ui->tableWidget->setSortingEnabled(false);

    //获取旧的行计数，表格末尾加入一个新空行，有新的空行才能设置新行条目
    int nOldRowCount = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(nOldRowCount);

    //获取其他数据项，并逐个单元格添加
    //头像
    QIcon iconHead = ui->comboBoxPhotos->itemIcon( ui->comboBoxPhotos->currentIndex() );
    //添加姓名和头像的单元格条目
    QTableWidgetItem *itemName = new QTableWidgetItem(iconHead, strName);
    ui->tableWidget->setItem(nOldRowCount, 0, itemName);
    //性别条目
    QString strGender = ui->lineEditGender->text();
    QTableWidgetItem *itemGender = new QTableWidgetItem(strGender);
    ui->tableWidget->setItem(nOldRowCount, 1, itemGender);
    //生日条目
    QString strBirthday = ui->dateEdit->date().toString("yyyy/MM/dd");
    QTableWidgetItem *itemBirthday = new QTableWidgetItem(strBirthday);
    ui->tableWidget->setItem(nOldRowCount, 2, itemBirthday);
    //婚否条目
    Qt::CheckState cks = ui->checkBoxIsMarried->checkState();
    QTableWidgetItem *itemIsMarried = new QTableWidgetItem();
    itemIsMarried->setCheckState(cks);
    ui->tableWidget->setItem(nOldRowCount, 3, itemIsMarried);
    //住址条目
    QString strAddress = ui->lineEditAddress->text();
    QTableWidgetItem *itemAddress = new QTableWidgetItem(strAddress);
    ui->tableWidget->setItem(nOldRowCount, 4, itemAddress);

    //添加条目完毕后，重新开启排序
    ui->tableWidget->setSortingEnabled(true);
    ui->tableWidget->sortByColumn(0, Qt::AscendingOrder);

    //设置新的当前条目并滚动显示
    ui->tableWidget->setCurrentItem(itemName);
    ui->tableWidget->scrollToItem(itemName);
}

void Widget::on_pushButtonDel_clicked()
{
    //目前仅支持删除选中的当前行
    //获取当前条目
    QTableWidgetItem *curItem = ui->tableWidget->currentItem();
    if(curItem != NULL) //当前条目非空
    {
        if(curItem->isSelected())
        {
            //当前条目被选中，那么确定是删除该行
            ui->tableWidget->removeRow( curItem->row()  );
        }
    }
}
