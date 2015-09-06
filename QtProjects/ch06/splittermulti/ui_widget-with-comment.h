/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QVBoxLayout *verticalLayout_2;  //主布局器，封装 splitter_2
    QSplitter *splitter_2;          //大分裂器，包含界面所有控件
    QSplitter *splitter;    //第一行的分裂器
    QTextEdit *textEdit;    //第一行的编辑器
    QWidget *widget;        //封装按钮布局器的部件对象
    QVBoxLayout *verticalLayout;    //按钮布局器
    QPushButton *pushButton1;
    QPushButton *pushButton2;
    QPushButton *pushButton3;
    QTextBrowser *textBrowser;  //第二行的提示栏

    void setupUi(QWidget *Widget)
    {
        //窗口的对象名称
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(600, 480);   //窗口尺寸

        //主布局器，用于封装 splitter_2
        verticalLayout_2 = new QVBoxLayout(Widget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));

        //大分裂器，包含所有控件
        splitter_2 = new QSplitter(Widget);
        splitter_2->setObjectName(QStringLiteral("splitter_2"));
        //样式表，设置手柄颜色
        splitter_2->setStyleSheet(QLatin1String("QSplitter::handle {    \n"
"    background-color: rgb(0, 255, 127);\n"
"}"));
        splitter_2->setOrientation(Qt::Vertical);

        //第一行的分裂器
        splitter = new QSplitter(splitter_2);
        splitter->setObjectName(QStringLiteral("splitter"));
        //设置分裂器的尺寸策略
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(4);
        sizePolicy.setHeightForWidth(splitter->sizePolicy().hasHeightForWidth());
        splitter->setSizePolicy(sizePolicy);
        //样式表，设置手柄颜色
        splitter->setStyleSheet(QLatin1String("QSplitter::handle {    \n"
"    background-color: rgb(0, 255, 127);\n"
"}"));
        splitter->setOrientation(Qt::Horizontal);

        //新建编辑器
        textEdit = new QTextEdit(splitter);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(textEdit->sizePolicy().hasHeightForWidth());
        textEdit->setSizePolicy(sizePolicy1);
        //把编辑器添加到第一行的分裂器
        splitter->addWidget(textEdit);

        //新建一个 widget 用于包裹按钮的布局器verticalLayout
        widget = new QWidget(splitter);
        widget->setObjectName(QStringLiteral("widget"));

        //按钮的垂直布局器
        //verticalLayout 是部件对象 widget 唯一的布局器，自动成为部件对象 widget 的主布局器
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        //新建按钮1，添加到 verticalLayout
        pushButton1 = new QPushButton(widget);
        pushButton1->setObjectName(QStringLiteral("pushButton1"));

        verticalLayout->addWidget(pushButton1);
        //新建按钮2，添加到 verticalLayout
        pushButton2 = new QPushButton(widget);
        pushButton2->setObjectName(QStringLiteral("pushButton2"));

        verticalLayout->addWidget(pushButton2);
        //新建按钮3，添加到 verticalLayout
        pushButton3 = new QPushButton(widget);
        pushButton3->setObjectName(QStringLiteral("pushButton3"));

        verticalLayout->addWidget(pushButton3);
        //添加包裹布局器 verticalLayout 的部件对象 widget 到第一行分裂器里
        splitter->addWidget(widget);
        //把第一行的分裂器添加给整体的大分裂器
        splitter_2->addWidget(splitter);

        //新建第二行的提示栏 textBrowser
        textBrowser = new QTextBrowser(splitter_2);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(1);
        sizePolicy2.setHeightForWidth(textBrowser->sizePolicy().hasHeightForWidth());
        textBrowser->setSizePolicy(sizePolicy2);
        //把第二行的 textBrowser 添加到整体的大分裂器
        splitter_2->addWidget(textBrowser);
        //用 verticalLayout_2 包裹整体的大分裂器 splitter_2
        verticalLayout_2->addWidget(splitter_2);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", 0));
        textEdit->setHtml(QApplication::translate("Widget", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'\345\256\213\344\275\223'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\347\274\226\350\276\221\345\231\250</p></body></html>", 0));
        pushButton1->setText(QApplication::translate("Widget", "\345\212\237\350\203\2751", 0));
        pushButton2->setText(QApplication::translate("Widget", "\345\212\237\350\203\2752", 0));
        pushButton3->setText(QApplication::translate("Widget", "\345\212\237\350\203\2753", 0));
        textBrowser->setHtml(QApplication::translate("Widget", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'\345\256\213\344\275\223'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\346\217\220\347\244\272\344\277\241\346\201\257</p></body></html>", 0));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
