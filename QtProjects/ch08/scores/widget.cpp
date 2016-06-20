#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QMessageBox>
#include <QTableWidgetItem> //表格条目
#include <QTableWidgetSelectionRange>   //表格选中区域

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //初始化表格
    InitScoresTable();
    //本示例表格不能排序，因为行首是姓名，不能对行首同步排序
}

Widget::~Widget()
{
    delete ui;
}

//初始化成绩表格的函数
void Widget::InitScoresTable()
{
    //初始设置表格为 2 行 4 列的
    ui->tableWidget->setRowCount(2);
    ui->tableWidget->setColumnCount(4);
    //记录四个列首字符串
    QStringList listHeaders;
    //添加四个字符串到字符串列表
    listHeaders<<tr("语文")<<tr("数学")<<tr("外语")<<tr("美食");
    ui->tableWidget->setHorizontalHeaderLabels(listHeaders);

    //初始时添加两行学生成绩记录
    //第0行的行首和单元格
    SetTableRow(0, tr("小明"),
                tr("66"), tr("77"),
                tr("88"), tr("99"));
    //第1行的行首和单元格
    SetTableRow(1, tr("小萌"),
                tr("99"), tr("88"),
                tr("77"), tr("66"));
}
//设置某行的行首和四个单元格条目
void Widget::SetTableRow(int nRow, QString strName,
                         QString strChinese, QString strMath,
                         QString strForeignLanguage, QString strFood)
{
    //行首名字
    QTableWidgetItem *itemName = new QTableWidgetItem(strName);
    ui->tableWidget->setVerticalHeaderItem(nRow, itemName);
    //语文单元格
    QTableWidgetItem *itemChinese = new QTableWidgetItem(strChinese);
    ui->tableWidget->setItem(nRow, 0, itemChinese);
    //数学单元格
    QTableWidgetItem *itemMath = new QTableWidgetItem(strMath);
    ui->tableWidget->setItem(nRow, 1, itemMath);
    //外语单元格
    QTableWidgetItem *itemForeignLanguage = new QTableWidgetItem(strForeignLanguage);
    ui->tableWidget->setItem(nRow, 2, itemForeignLanguage);
    //美食单元格
    QTableWidgetItem *itemFood = new QTableWidgetItem(strFood);
    ui->tableWidget->setItem(nRow, 3, itemFood);
}

void Widget::on_tableWidget_itemSelectionChanged()
{
    //选中的条目
    QList<QTableWidgetItem*> listItems = ui->tableWidget->selectedItems();
    int nItemsCount = listItems.count();    //选中条目计数
    //选中的矩形区域
    QList<QTableWidgetSelectionRange> listRanges = ui->tableWidget->selectedRanges();
    int nRangesCount = listRanges.count();
    //计算矩形区域包含的单元格统计
    int nCellsCount = 0;
    for(int i=0; i<nRangesCount; i++)
    {
        nCellsCount += (listRanges[i].rowCount()) * (listRanges[i].columnCount());
    }
    //打印信息
    qDebug()<<tr("选中条目数：%1，选中区域数：%2，选中单元格数：%3")
              .arg(nItemsCount)
              .arg(nRangesCount)
              .arg(nCellsCount);
}

void Widget::on_pushButtonFind_clicked()
{
    //比较的分值字符串
    const QString strDstScore = ui->lineEditFindText->text().trimmed();
    if(strDstScore.isEmpty())
    {
        return; //没有比较分值不查询
    }
    const int nDstScore = strDstScore.toInt();    //用于比较的分值

    //指定的列号
    int nTheColumn = ui->comboBoxColumns->currentIndex();
    //指定的比较运算符，0是等于，1是小于等于，2是大于等于
    int nCompare = ui->comboBoxCompares->currentIndex();

    //表格总行数
    int nRowCount = ui->tableWidget->rowCount();
    //记录符合条件的单元格数目、均值、总值
    int nFilteredCount = 0;
    double dblTotal = 0;
    double dblAverage = 0;
    //记录符合条件的第一个条目
    QTableWidgetItem *itemFilteredFirst = NULL;
    //清空旧的高亮选中
    ui->tableWidget->setCurrentItem(NULL, QItemSelectionModel::Clear);

    //循环查询该列条目
    for(int i=0; i<nRowCount; i++)
    {
        QTableWidgetItem *itemCur = ui->tableWidget->item(i, nTheColumn);
        if(NULL == itemCur)
        {
            continue;   //无条目
        }
        QString strCur = itemCur->text().trimmed();
        int nCurScore = strCur.toInt();    //分值
        //判断当前比较运算符
        if(0 == nCompare) //等于号
        {
            //比较字符串或分值是不是一样
            if( nCurScore != nDstScore )
            {
                continue;   //不符合
            }
        }
        else if(1 == nCompare) //小于等于
        {
            if( ! (nCurScore <= nDstScore))
            {
                continue;   //不符合
            }
        }
        else    //大于等于
        {
            if( ! (nCurScore >= nDstScore) )
            {
                continue;   //不符合
            }
        }// end if-elseif-else
        //符合条件的才会执行到这里
        nFilteredCount++;       //合格计数增加
        dblTotal += nCurScore;  //总分值增加
        itemCur->setSelected(true); //选中该条目
        if( NULL == itemFilteredFirst)
        {
            //保存第一个符合的条目
            itemFilteredFirst = itemCur;
            //设置为当前条目并滚动到这
            ui->tableWidget->setCurrentItem(itemFilteredFirst);
            ui->tableWidget->scrollToItem(itemFilteredFirst);
        }
    }//end for
    //计算均值
    if(nFilteredCount > 0)
    {
        dblAverage = dblTotal / nFilteredCount;
    }
    //构造消息字符串
    QString strMsg = tr("匹配条目数：%1，匹配条目的总值：%2，均值：%3")
            .arg(nFilteredCount).arg(dblTotal).arg(dblAverage);
    QMessageBox::information(this, tr("查找"), strMsg);
    //焦点切换到表格控件，这样能看清楚高亮背景
    ui->tableWidget->setFocus();
}

void Widget::on_pushButtonAddLine_clicked()
{
    //判断名字是否为空
    QString strName = ui->lineEditName->text().trimmed();
    if(strName.isEmpty())
    {
        return;
    }
    //末尾添加新行
    int nOldRowCount = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow( nOldRowCount );
    //设置该行行首和单元格
    SetTableRow(nOldRowCount, strName,
                tr("0"), tr("0"),
                tr("0"), tr("0"));
    ui->tableWidget->scrollToBottom();  //自动滚到底部
}

void Widget::on_pushButtonDelLines_clicked()
{
    //支持删除多行，对于多行的删除，要从末尾开始删除，保证前面的行号不错乱
    QList<int> listRowIndex;    //保存要删的行号
    //选中区域
    QList<QTableWidgetSelectionRange> listRanges = ui->tableWidget->selectedRanges();
    int nRangeCount = listRanges.count();
    if(nRangeCount < 1)
    {
        return; //没选中
    }
    //有选中区域
    for(int i=0; i<nRangeCount; i++)
    {
        //目前这一块矩形区域里的行计数
        int nCurRangeRowCount = listRanges[i].rowCount();
        for(int j=0; j<nCurRangeRowCount; j++ )
        {
            //选中行序号
            int nRowIndex = listRanges[i].topRow() + j;
            if( ! listRowIndex.contains(nRowIndex) )//没有重复的
            {
                listRowIndex.append(nRowIndex);//添加到行号列表
            }
        }
    }
    //对行号排序
    qSort(listRowIndex);
    //从末尾开始删除行
    int nRowIndexCount = listRowIndex.count();
    for(int i=nRowIndexCount-1; i>=0; i--)
    {
        ui->tableWidget->removeRow( listRowIndex[i] );
    }
    //清空列表
    listRanges.clear();
    listRowIndex.clear();
}

void Widget::on_pushButtonDelSelectedItems_clicked()
{
    //选中的条目
    QList<QTableWidgetItem*> listItems = ui->tableWidget->selectedItems();
    //计数
    int nCount = listItems.count();
    if(nCount < 1)
    {
        return;
    }
    //将选中条目一个个卸载下来并删除
    for(int i=0; i<nCount; i++)
    {
        int nItemRow = listItems[i]->row();
        int nItemColumn = listItems[i]->column();
        delete ui->tableWidget->takeItem(nItemRow, nItemColumn);
    }
    //清空列表
    listItems.clear();
}
