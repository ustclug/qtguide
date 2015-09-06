#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QFileDialog>
#include <QUrl>
#include <QSettings>    //保存和加载配置的类

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

    //调用加载配置项的函数
    LoadSettings();
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

//关闭之前执行这个虚函数
void Widget::closeEvent(QCloseEvent *)
{
    //保存配置
    SaveSettings();
}

//负责保存配置的函数
void Widget::SaveSettings()
{
    //机构或公司名设为 QtGuide，应用程序名设为 SimpleBrowser
    QSettings settings("QtGuide", "SimpleBrowser");
    //主窗口状态信息
    QByteArray baMainWidget = this->saveGeometry();
    //分裂器状态信息
    QByteArray baSplitter = ui->splitter->saveState();
    //源文件 URL
    QUrl urlSrc = ui->textBrowser->source();

    //保存为配置项，键名自己随便取
    settings.setValue("MainWidget", baMainWidget);
    settings.setValue("Splitter", baSplitter);
    settings.setValue("URL", urlSrc);
    //搞定，settings 对象在栈里面，该对象析构时自动存储所有配置
}

//负责加载配置的函数
void Widget::LoadSettings()
{
    //机构或公司名设为 QtGuide，应用程序名设为 SimpleBrowser
    //settings 的构造函数自己会去读取上次保存的注册表或配置文件信息
    QSettings settings("QtGuide", "SimpleBrowser");

    //判断键名是否存在，然后取出各个键名对应的键值，还原以前保存的状态
    //主窗口
    if(settings.contains("MainWidget"))
    {
        QByteArray baMainWidget = settings.value("MainWidget").toByteArray();
        this->restoreGeometry(baMainWidget);
    }
    //分裂器
    if(settings.contains("Splitter"))
    {
        QByteArray baSplitter = settings.value("Splitter").toByteArray();
        ui->splitter->restoreState(baSplitter);
    }
    //源文件URL
    if(settings.contains("URL"))
    {
        QUrl urlSrc = settings.value("URL").toUrl();
        ui->textBrowser->setSource(urlSrc);
    }
}


