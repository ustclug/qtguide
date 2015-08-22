#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QFileDialog>
#include <QUrl>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //设置 QPlainTextEdit 只读模式
    ui->plainTextEdit->setReadOnly(true);

    //设置 QTextBrowser 能自动用系统浏览器打开外站链接
    ui->textBrowser->setOpenExternalLinks(true);

    //将 "后退"、"前进"按钮设置为不可用状态
    ui->pushButtonBackward->setEnabled(false);
    ui->pushButtonForeward->setEnabled(false);

    //关联 "后退" 按钮的信号到对应槽函数
    connect(ui->pushButtonBackward, SIGNAL(clicked()),
            ui->textBrowser, SLOT(backward()));
    //关联 "前进" 按钮的信号到对应槽函数
    connect(ui->pushButtonForeward, SIGNAL(clicked()),
            ui->textBrowser, SLOT(forward()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButtonOpen_clicked()
{
    QUrl urlFile = QFileDialog::getOpenFileUrl(this, "open HTML", QUrl(), "HTML files(*.htm *.html)");
    //URL 非空，才进行打开操作
    if( ! urlFile.isEmpty())
    {
        //打印文件链接
        qDebug()<<urlFile;
        //设置浏览的源文件
        ui->textBrowser->setSource(urlFile);
    }
}
//根据能否后退，设置 "后退" 按钮可用状态
void Widget::on_textBrowser_backwardAvailable(bool arg1)
{
    ui->pushButtonBackward->setEnabled(arg1);
}
//根据能否前进，设置 "前进" 按钮可用状态
void Widget::on_textBrowser_forwardAvailable(bool arg1)
{
    ui->pushButtonForeward->setEnabled(arg1);
}
//当 QTextBrowser 控件内容变化时，QPlainTextEdit 跟着变化
void Widget::on_textBrowser_textChanged()
{
    //获取 html 字符串，设置给 plainTextEdit
    QString strHtml = ui->textBrowser->toHtml();
    ui->plainTextEdit->setPlainText(strHtml);
}
