#include "licencepage.h"
#include "ui_licencepage.h"

LicencePage::LicencePage(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::LicencePage)
{
    ui->setupUi(this);
    //标题和副标题
    setTitle(tr("许可证"));
    setSubTitle(tr("请查阅许可证内容，并下方选择是否同意许可证。"));

    //设置许可证显示内容
    ui->textBrowserLicence->setText(tr("<h2>Editor 软件许可证</h2>"
                                       "Editor 软件遵循 GPLv3 / MIT 许可证发布，"
                                       "请勾选同意许可证，才能继续安装本软件。"));

    //注册许可证对应字段，字段内容是 bool 类型，取值 true 或 false
    registerField("AgreeLicence", ui->checkBoxAgreeLicence);
}

LicencePage::~LicencePage()
{
    delete ui;
}

//重载构建非线性的向导，跳转页面
int LicencePage::nextId() const
{
    if( ui->checkBoxAgreeLicence->isChecked() )
    {
        return 2; // InstallPage
    }
    else
    {
        return 3; // FinalPage
    }
}
