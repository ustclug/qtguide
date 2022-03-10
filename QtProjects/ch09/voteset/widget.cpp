#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //填充投票，并设置列表框显示
    FillDataAndListWidget();
}

void Widget::FillDataAndListWidget()
{
    m_voteData.insert( tr("路人甲"), tr("张三") );
    m_voteData.insert( tr("路人甲"), tr("狗哥") );
    m_voteData.insert( tr("路人乙"), tr("李四") );
    m_voteData.insert( tr("路人乙"), tr("狗哥") );
    m_voteData.insert( tr("路人丙"), tr("张三") );
    m_voteData.insert( tr("路人丙"), tr("狗哥") );
    m_voteData.insert( tr("路人丁"), tr("李四") );
    m_voteData.insert( tr("路人丁"), tr("狗哥") );
    m_voteData.insert( tr("路人戊"), tr("张三") );
    m_voteData.insert( tr("路人戊"), tr("狗哥") );
    //显示到列表控件
    ui->listWidget->clear();
    //使用迭代器遍历
    QHash<QString, QString>::const_iterator it = m_voteData.constBegin();
    while ( it != m_voteData.constEnd() )
    {
        QString strLine = it.key() + tr("\t投\t") + it.value();
        ui->listWidget->addItem( strLine );
        ++it;
    }
}

Widget::~Widget()
{
    delete ui;
}

//统计投票人，不重复的
void Widget::on_pushButtonGetVoters_clicked()
{
    //投票人是 keys
    QList<QString> listVoters = m_voteData.keys();
    //用集合去重复
    QSet<QString> uniqueVoters = QSet<QString>::fromList( listVoters );
    //可以转回列表
    listVoters = uniqueVoters.toList();
    //构造信息字符串
    int nCount = listVoters.count();
    QString strInfo = tr("投票人数：%1 \r\n").arg(nCount);
    for(int i=0; i<nCount; i++)
    {
        strInfo += listVoters[i] + tr("\r\n");
    }
    //显示
    ui->textBrowser->setText( strInfo );
}

//统计候选人，不重复的
void Widget::on_pushButtonGetCandidates_clicked()
{
    //候选人是 values
    QList<QString> listCandidates = m_voteData.values();
    //用集合去重复
    QSet<QString> uniqueCandidates = QSet<QString>::fromList( listCandidates );
    //转回列表
    listCandidates = uniqueCandidates.toList();
    //构造信息字符串
    int nCount = listCandidates.count();
    QString strInfo = tr("候选人数：%1 \r\n").arg(nCount);
    for(int i=0; i<nCount; i++)
    {
        strInfo += listCandidates[i] + tr("\r\n");
    }
    //显示
    ui->textBrowser->setText( strInfo );
}

//统计同时选择张三和狗哥的投票人
void Widget::on_pushButtonGetIntersect_clicked()
{
    QSet<QString> voteZhangSan;
    QSet<QString> voteGouGe;
    //使用迭代器遍历
    QHash<QString, QString>::const_iterator it = m_voteData.constBegin();
    while ( it != m_voteData.constEnd() )
    {
        if( it.value() == tr("张三") )
        {
            voteZhangSan<<it.key();
        }
        if( it.value() == tr("狗哥") )
        {
            voteGouGe<<it.key();
        }
        ++it;
    }
    //张三的投票人集合，与狗哥的投票人集合 求交集
    QSet<QString> sIntersect = voteZhangSan & voteGouGe;
    QStringList listIntersect = sIntersect.toList();
    //构造信息字符串
    QString strInfo = tr("同时选择张三和狗哥的投票人数：%1 \r\n").arg(listIntersect.count());
    strInfo += listIntersect.join( "\r\n" );
    //显示
    ui->textBrowser->setText( strInfo );
}

//统计选择张三或狗哥的投票人
void Widget::on_pushButtonGetUnite_clicked()
{
    QSet<QString> voteZhangSan;
    QSet<QString> voteGouGe;
    //使用迭代器遍历
    QHash<QString, QString>::const_iterator it = m_voteData.constBegin();
    while ( it != m_voteData.constEnd() )
    {
        if( it.value() == tr("张三") )
        {
            voteZhangSan<<it.key();
        }
        if( it.value() == tr("狗哥") )
        {
            voteGouGe<<it.key();
        }
        ++it;
    }
    //张三的投票人集合，与狗哥的投票人集合 求并集
    QSet<QString> sUnite = voteZhangSan | voteGouGe;
    QStringList listUnite = sUnite.toList();
    //构造信息字符串
    QString strInfo = tr("选择张三或狗哥的投票人数：%1 \r\n").arg(listUnite.count());
    strInfo += listUnite.join( "\r\n" );
    //显示
    ui->textBrowser->setText( strInfo );
}
