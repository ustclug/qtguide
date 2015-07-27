#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTextCharFormat>  //文本格式类

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_pushButtonBold_clicked(bool checked);

    void on_pushButtonItalic_clicked(bool checked);

    void on_pushButtonUnderline_clicked(bool checked);

    void on_pushButtonColor_clicked();

    void on_pushButtonBGColor_clicked();

    void on_lineEditFontSize_editingFinished();

    void on_textEdit_currentCharFormatChanged(const QTextCharFormat &format);

    void on_textEdit_textChanged();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
