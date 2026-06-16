#include "installpage.h"
#include "ui_installpage.h"
#include <QMessageBox>
#include <QDebug>
#include <QDir>
#include <QFileDialog>

InstallPage::InstallPage(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::InstallPage)
{
    ui->setupUi(this);
    //设置标题和副标题
    setTitle(tr("安装"));
    setSubTitle(tr("选择安装路径和软件模块进行安装，带星号 * 为必填项。"));

    //设置为提交页，不能反悔回到本页
    setCommitPage(true);

    //注册字段
    //安装路径，必填，用 isComplete() 检查
    registerField("InstallPath", ui->lineEditInstallPath);
    //是否选中基本功能模块，必填
    registerField("BaseModule*", ui->checkBoxBaseModule);
    //HEX显示模块
    registerField("HEXModule", ui->checkBoxHEXModule);
    //CSV显示模块
    registerField("CSVModule", ui->checkBoxCSVModule);
}

InstallPage::~InstallPage()
{
    delete ui;
}


bool InstallPage::isComplete() const
{
    //先调用基类函数，检查必填字段
    bool bRet = QWizardPage::isComplete();
    if( ! bRet ) //没填好
    {
        return false; //不能开启Next
    }

    //校验路径是否存在
    QString strPath = ui->lineEditInstallPath->text().trimmed();
    if( strPath.isEmpty() )//路径为空
    {
        return false;
    }

    QDir dir(strPath);
    //检查是否存在
    if( dir.exists() )
    {
        return true; //合法路径
    }
    else
    {
        return false; //非法路径
    }
}
//触发完成情况检查
void InstallPage::on_lineEditInstallPath_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1); //避免未使用变量的编译警告
    //触发完成情况检查信号
    emit completeChanged();
}

//浏览文件夹
void InstallPage::on_pushButtonBrowser_clicked()
{
    QString strInstallPath = QFileDialog::getExistingDirectory();
    //判断字符串是否为空
    if( strInstallPath.isEmpty() )
    {
        return;
    }
    //非空，填写到编辑框
    ui->lineEditInstallPath->setText(strInstallPath);
}
