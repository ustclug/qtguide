#include "intropage.h"
#include "ui_intropage.h"

IntroPage::IntroPage(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::IntroPage)
{
    ui->setupUi(this);

    //设置标题和副标题
    setTitle(tr("Editor软件介绍"));
    //现代风格需要副标题有文本，才显示横幅和标志图片
    setSubTitle(tr("Editor是一个文本编辑器。"));

    //添加Editor软件介绍
    ui->textBrowserIntro->setText(tr("<h2>Editor软件 V1.0</h2>"
                                     "Editor可以简单编辑文本文件，我们的口号是<br>"
                                     "<b>Edit file, Enjoy life.</b>"
                                     ));

    //初始化代码，添加向导外观风格条目
    ui->comboBoxWizardStyle->addItem(tr("ClassicStyle")); //0
    ui->comboBoxWizardStyle->addItem(tr("ModernStyle"));  //1
    ui->comboBoxWizardStyle->addItem(tr("MacStyle"));     //2
    ui->comboBoxWizardStyle->addItem(tr("AeroStyle"));    //3
    //默认显示现代风格
    ui->comboBoxWizardStyle->setCurrentIndex(1);
}

IntroPage::~IntroPage()
{
    delete ui;
}

void IntroPage::on_comboBoxWizardStyle_currentIndexChanged(int index)
{
    if( index < 0  ) //非法序号不处理
    {
        return;
    }
    if( wizard() != NULL )//判断父对话框非空才能设置风格
    {
        wizard()->setWizardStyle( (QWizard::WizardStyle)index );
        wizard()->setWindowTitle(
            tr("WizardStyle: ") + ui->comboBoxWizardStyle->currentText());
    }
}
