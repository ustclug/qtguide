//hellowidget.h
#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>

class HelloWidget : public QWidget
{
    Q_OBJECT
public:
    explicit HelloWidget(QWidget *parent = 0);
    ~HelloWidget();
    //label
    QLabel *m_labelInfo;
};

