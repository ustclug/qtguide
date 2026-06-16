#ifndef INSTALLWIZARDDIALOG_H
#define INSTALLWIZARDDIALOG_H

#include <QWizard>
//包含4个子页面头文件
#include "intropage.h"
#include "licencepage.h"
#include "installpage.h"
#include "finalpage.h"

namespace Ui {
class InstallWizardDialog;
}

class InstallWizardDialog : public QWizard
{
    Q_OBJECT

public:
    explicit InstallWizardDialog(QWidget *parent = 0);
    ~InstallWizardDialog();

public slots:
    //显示帮助信息
    void showHelp();

private:
    Ui::InstallWizardDialog *ui;
    //创建子页面等初始化工作
    void createPagesAndInitUI();
};

#endif // INSTALLWIZARDDIALOG_H
