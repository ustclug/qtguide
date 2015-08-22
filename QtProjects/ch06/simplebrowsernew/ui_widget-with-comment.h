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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QHBoxLayout *horizontalLayout_3;//主布局器
    //左半边
    QVBoxLayout *verticalLayout;    //左半边布局器
    QTextBrowser *textBrowser;      //丰富文本浏览器
    QHBoxLayout *horizontalLayout;  //两个按钮和空白条的水平布局器
    QPushButton *pushButtonBackward;//后退按钮
    QPushButton *pushButtonForeward;//前进按钮
    QSpacerItem *horizontalSpacer;  //左边的空白条
    //右半边
    QVBoxLayout *verticalLayout_2;  //右半边布局器
    QPlainTextEdit *plainTextEdit;  //普通文本编辑器
    QHBoxLayout *horizontalLayout_2;//右边按钮和空白条的水平布局器
    QSpacerItem *horizontalSpacer_2;//右边的空白条
    QPushButton *pushButtonOpen;    //打开按钮

    void setupUi(QWidget *Widget)
    {
        //Widget 是要进行界面构造的窗体
        //先设置窗体的对象名称
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(630, 350);   //设置窗体尺寸

        //主布局器构造
        horizontalLayout_3 = new QHBoxLayout(Widget);   //新建布局器
        horizontalLayout_3->setSpacing(6);              //设置内部控件或子布局器间隙
        //设置内部控件或子布局器距离四个边的边距
        //设计师原本是(9,9,9,9)，因为是主布局器，uic 工具额外增加了 2 的边距
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        //设置主布局器对象名称
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));

        //左半边
        verticalLayout = new QVBoxLayout(); //左半边大布局器
        verticalLayout->setSpacing(6);      //内部控件和子布局器间隙也是 6
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));//布局器对象名称
        //左边丰富文本浏览器控件
        textBrowser = new QTextBrowser(Widget); //新建丰富文本浏览器
        textBrowser->setObjectName(QStringLiteral("textBrowser"));  //对象名称

        verticalLayout->addWidget(textBrowser); //添加丰富文本浏览器到左边大布局器

        //左边两个按钮的布局器
        horizontalLayout = new QHBoxLayout();   //新建布局器
        horizontalLayout->setSpacing(6);        //设置内部控件间隙
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));//对象名称
        pushButtonBackward = new QPushButton(Widget);   //新建后退按钮
        pushButtonBackward->setObjectName(QStringLiteral("pushButtonBackward"));//对象名称

        horizontalLayout->addWidget(pushButtonBackward);//添加到按钮布局器

        pushButtonForeward = new QPushButton(Widget);   //新建前进按钮
        pushButtonForeward->setObjectName(QStringLiteral("pushButtonForeward"));//对象名称

        horizontalLayout->addWidget(pushButtonForeward);//添加到按钮布局器
        //新建左边的水平空白条，水平策略是伸展方式 QSizePolicy::Expanding
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);    //添加空白条到按钮布局器


        verticalLayout->addLayout(horizontalLayout);    //添加按钮布局器到左边的大布局器


        horizontalLayout_3->addLayout(verticalLayout);  //添加左半边大布局器到主布局器

        //右半边
        verticalLayout_2 = new QVBoxLayout();   //右半边大布局器
        verticalLayout_2->setSpacing(6);        //布局间隙
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));//对象名称
        plainTextEdit = new QPlainTextEdit(Widget); //普通文本编辑器
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));  //对象名称

        verticalLayout_2->addWidget(plainTextEdit); //添加到右半边大布局器

        //右边按钮的布局器
        horizontalLayout_2 = new QHBoxLayout(); //新建右边按钮的水平布局器
        horizontalLayout_2->setSpacing(6);      //布局间隙
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));//对象名称
        //新建右边的空白条，最优尺寸 40*20，水平策略是尽量伸展，垂直策略是高度到 20 之后不变高
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);//添加空白条到按钮的布局器

        pushButtonOpen = new QPushButton(Widget);   //新建打开按钮
        pushButtonOpen->setObjectName(QStringLiteral("pushButtonOpen"));//对象名称

        horizontalLayout_2->addWidget(pushButtonOpen);  //添加到按钮的水平布局器


        verticalLayout_2->addLayout(horizontalLayout_2);//添加到右半边的大布局器


        horizontalLayout_3->addLayout(verticalLayout_2);//添加到主布局器


        retranslateUi(Widget);  //翻译界面

        QMetaObject::connectSlotsByName(Widget);//自动关联槽函数
    } // setupUi 函数

    void retranslateUi(QWidget *Widget)
    {
        //设置窗口标题
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", 0));
        //后退按钮的文本
        //八进制 "\345\220\216" 是 UTF-8 编码的 "后" 字
        //八进制 "\351\200\200" 是 UTF-8 编码的 "退" 字
        pushButtonBackward->setText(QApplication::translate("Widget", "\345\220\216\351\200\200", 0));
        //设置前进按钮文本，八进制表示的 UTF-8 文本 "前进"
        pushButtonForeward->setText(QApplication::translate("Widget", "\345\211\215\350\277\233", 0));
        //设置打开HTML按钮文本，八进制和英文字母表示的 "打开HTML"
        pushButtonOpen->setText(QApplication::translate("Widget", "\346\211\223\345\274\200HTML", 0));
    } // retranslateUi 函数

};//Ui_Widget 类

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
