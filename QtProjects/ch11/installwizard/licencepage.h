#ifndef LICENCEPAGE_H
#define LICENCEPAGE_H

#include <QWizardPage>

namespace Ui {
class LicencePage;
}

class LicencePage : public QWizardPage
{
    Q_OBJECT

public:
    explicit LicencePage(QWidget *parent = 0);
    ~LicencePage();

private:
    Ui::LicencePage *ui;

    // QWizardPage interface
public:
    virtual int nextId() const;
};

#endif // LICENCEPAGE_H
