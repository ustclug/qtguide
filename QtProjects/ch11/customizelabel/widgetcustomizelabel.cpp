#include "widgetcustomizelabel.h"
#include "ui_widgetcustomizelabel.h"
#include <QDebug>

WidgetCustomizeLabel::WidgetCustomizeLabel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetCustomizeLabel)
{
    ui->setupUi(this);
    //初始化
    Init();
}

//初始化
void WidgetCustomizeLabel::Init()
{
    //背景色浅灰，前景色黑色
    m_clrBackground = QColor(240,240,240);
    m_clrForeground = QColor(0,0,0);
    m_strText = tr("显示样例");
    //新建前景色对话框
    m_pDlgForeground = new QColorDialog(this);
    //隐藏按钮，非模态对话框，保持持续显示
    m_pDlgForeground->setOptions( QColorDialog::NoButtons );
    //关联信号和槽
    connect(m_pDlgForeground, SIGNAL(currentColorChanged(QColor)),
            this, SLOT(RecvAndSetForegroundColor(QColor)) );
}

WidgetCustomizeLabel::~WidgetCustomizeLabel()
{
    delete m_pDlgForeground;    m_pDlgForeground = NULL;
    delete ui;
}

//设置前景色按钮
void WidgetCustomizeLabel::on_pushButtonForeground_clicked()
{
    m_pDlgForeground->show();
    m_pDlgForeground->raise();
}

//槽函数，动态更新前景色
void WidgetCustomizeLabel::RecvAndSetForegroundColor(QColor color)
{
    if( ! color.isValid())
    {
        return;  //颜色不合法
    }
    //颜色值合法
    m_clrForeground = color;
    QString strQSS = tr("color: %1; background-color: %2;")
            .arg(m_clrForeground.name()).arg(m_clrBackground.name());
    ui->labelSample->setStyleSheet( strQSS );
}

//设置背景色按钮
void WidgetCustomizeLabel::on_pushButtonBackground_clicked()
{
    //获取颜色
    QColor clr = QColorDialog::getColor();
    if( ! clr.isValid())
    {
        return;
    }
    //合法颜色
    m_clrBackground = clr;
    QString strQSS = tr("color: %1; background-color: %2;")
            .arg(m_clrForeground.name()).arg(m_clrBackground.name());
    ui->labelSample->setStyleSheet( strQSS );
}

//设置字体按钮
void WidgetCustomizeLabel::on_pushButtonFont_clicked()
{
    //获取字体
    bool bOK = false;
    QFont ft = QFontDialog::getFont( &bOK, m_font );
    if( ! bOK )
    {
        return; //取消了
    }
    m_font = ft;
    //设置新字体
    ui->labelSample->setFont( m_font );
}

//设置文本按钮
void WidgetCustomizeLabel::on_pushButtonText_clicked()
{
    //获取输入文本
    bool bOK = false;
    QString strText = QInputDialog::getMultiLineText(this, tr("设置文本"),tr("请输入文本："),
                                                     m_strText, &bOK);
    if( ! bOK )
    {
        return; //取消了
    }
    m_strText = strText;
    ui->labelSample->setText(m_strText);
}
