#ifndef WIDGETCALCMD5_H
#define WIDGETCALCMD5_H

#include <QWidget>
#include <QErrorMessage>
#include <QFileDialog>
#include <QProgressDialog>
#include <QFile>
#include <QCryptographicHash>  //计算MD5

namespace Ui {
class WidgetCalcMD5;
}

class WidgetCalcMD5 : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetCalcMD5(QWidget *parent = 0);
    ~WidgetCalcMD5();

private slots:
    void on_pushButtonBrowser_clicked();

    void on_pushButtonCalcMD5_clicked();

private:
    Ui::WidgetCalcMD5 *ui;
    //错误消息框
    QErrorMessage m_dlgErrorMsg;
    //文件名
    QString m_strFileName;
    //计算文件对象 MD5 值
    QByteArray CalcFileMD5( QFile &fileIn, qint64 nFileSize );

};

#endif // WIDGETCALCMD5_H
