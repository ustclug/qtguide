#ifndef WIDGETSIMPLETEXTEDIT_H
#define WIDGETSIMPLETEXTEDIT_H

#include <QWidget>
#include <QFile>
#include <QFileDialog>

namespace Ui {
class WidgetSimpleTextEdit;
}

class WidgetSimpleTextEdit : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetSimpleTextEdit(QWidget *parent = 0);
    ~WidgetSimpleTextEdit();

private slots:
    void on_pushButtonBrowser_clicked();

    void on_pushButtonOpenFile_clicked();

    void on_pushButtonSaveFile_clicked();

    void on_pushButtonCloseFile_clicked();

    void on_pushButtonAboutThis_clicked();

    void on_pushButtonAboutQt_clicked();

    void on_plainTextEdit_textChanged();

private:
    Ui::WidgetSimpleTextEdit *ui;
    //文件对象
    QFile m_file;
    //保存文本是否被修改的状态
    bool m_bTextIsChanged;
    //根据编辑框内容写入文件
    void SaveTextFile();
};

#endif // WIDGETSIMPLETEXTEDIT_H
