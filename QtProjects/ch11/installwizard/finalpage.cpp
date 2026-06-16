#include "finalpage.h"
#include "ui_finalpage.h"

FinalPage::FinalPage(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::FinalPage)
{
    ui->setupUi(this);
    //设置标题和副标题
    setTitle(tr("结束"));
    setSubTitle(tr("安装向导结束。"));
}

FinalPage::~FinalPage()
{
    delete ui;
}

//根据前面页面内容生成本页面结果信息
void FinalPage::initializePage()
{
    //构建结果信息
    QString strResult;
    //获取是否同意许可证
    bool bAgreeLicence = field("AgreeLicence").toBool();
    if( ! bAgreeLicence )
    {
        //结果字符串
        strResult = tr("<h2>用户不同意许可证，直接终止安装向导，不安装软件。<h2>");
        //设置 Finish 按钮文本为终止
        setButtonText(QWizard::FinishButton, tr("终止安装"));
    }
    else
    {
        //同意许可证，执行了安装过程
        strResult += tr("<h2>用户同意许可证，安装了Editor软件。</h2>");
        //获取安装路径
        QString strInstallPath = field("InstallPath").toString();
        strResult += tr("Editor 安装路径为：<br>") + strInstallPath;
        //下面判断安装了哪些模块
        strResult += tr("<br><br>已经安装的模块如下：<br>");
        //基本模块
        bool bBaseModule = field("BaseModule").toBool();
        if( bBaseModule )
        {
            strResult += tr("基本功能模块<br>");
        }
        //HEX模块
        bool bHEXModule = field("HEXModule").toBool();
        if( bHEXModule )
        {
            strResult += tr("HEX显示模块<br>");
        }
        //CSV模块
        bool bCSVModule = field("CSVModule").toBool();
        if( bCSVModule )
        {
            strResult += tr("CSV显示模块<br>");
        }
        //修改 Finish 按钮显示文本
        setButtonText(QWizard::FinishButton, tr("完成安装"));
    }
    //显示结果字符串到文本浏览框
    ui->textBrowserResult->setText( strResult );
}
