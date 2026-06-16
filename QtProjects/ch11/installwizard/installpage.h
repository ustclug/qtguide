#ifndef INSTALLPAGE_H
#define INSTALLPAGE_H

#include <QWizardPage>

namespace Ui {
class InstallPage;
}

class InstallPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit InstallPage(QWidget *parent = 0);
    ~InstallPage();

private:
    Ui::InstallPage *ui;

private slots:
    void on_lineEditInstallPath_textChanged(const QString &arg1);

    void on_pushButtonBrowser_clicked();

    // QWizardPage interface
public:
    virtual bool isComplete() const;

};

#endif // INSTALLPAGE_H
