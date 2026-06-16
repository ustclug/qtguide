#ifndef FINALPAGE_H
#define FINALPAGE_H

#include <QWizardPage>

namespace Ui {
class FinalPage;
}

class FinalPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit FinalPage(QWidget *parent = 0);
    ~FinalPage();

private:
    Ui::FinalPage *ui;

    // QWizardPage interface
public:
    virtual void initializePage();
};

#endif // FINALPAGE_H
