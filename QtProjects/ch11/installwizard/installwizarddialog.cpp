#include "installwizarddialog.h"
#include "ui_installwizarddialog.h"
#include <QMessageBox>
#include <QDebug>

InstallWizardDialog::InstallWizardDialog(QWidget *parent) :
    QWizard(parent),
    ui(new Ui::InstallWizardDialog)
{
    ui->setupUi(this);    

    //创建子页面等初始化工作
    createPagesAndInitUI();
}

InstallWizardDialog::~InstallWizardDialog()
{
    delete ui;
}

//创建子页面等初始化工作
void InstallWizardDialog::createPagesAndInitUI()
{
    //创建 IntroPage
    IntroPage *pIntro = new IntroPage();
    //添加子页面 0
    addPage(pIntro);
    //创建 LicencePage
    LicencePage *pLicence = new LicencePage();
    //添加子页面 1
    addPage(pLicence);
    //创建 InstallPage
    InstallPage *pInstall = new InstallPage();
    //添加子页面 2
    addPage(pInstall);
    //创建 FinalPage
    FinalPage *pFinal = new FinalPage();
    //添加子页面 3
    addPage(pFinal);

    //窗口宽度不小于800
    setMinimumWidth(800);
    //设置 4 个图片
    setPixmap(QWizard::WatermarkPixmap, QPixmap(":/imgs/editorwatermark.png"));
    setPixmap(QWizard::LogoPixmap, QPixmap(":/imgs/editorlogo.png"));
    setPixmap(QWizard::BannerPixmap, QPixmap(":/imgs/editorbanner.png"));
    setPixmap(QWizard::BackgroundPixmap, QPixmap(":/imgs/editorbackgound.png"));
    //默认用现代风格
    setWizardStyle(QWizard::ModernStyle);

    //最后一页隐藏取消按钮
    setOption(QWizard::NoCancelButtonOnLastPage, true);
    //显示帮助按钮
    setOption(QWizard::HaveHelpButton, true);

    //关联帮助按钮的信号到槽函数
    connect(this, SIGNAL(helpRequested()),
            this, SLOT(showHelp()) );
}

//显示帮助信息
void InstallWizardDialog::showHelp()
{
    QString strHelp = tr("<h2>帮助信息</h2>"
                         "同意许可证才能执行安装；<br>"
                         "安装时必须指定正确的存在的安装路径；<br>"
                         "安装时必须勾选基本功能模块。<br>");
    QMessageBox::information(this, tr("帮助信息"), strHelp);
}
