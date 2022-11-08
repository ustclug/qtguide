#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QMessageBox>
#include <QDebug>

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    //初始化设置
    Init();
}

MainWidget::~MainWidget()
{
    //删除子窗口
    delete m_pFormChild;    m_pFormChild = NULL;
    delete ui;
}

//初始化设置
void MainWidget::Init()
{
    //设置窗口标题栏
    setWindowTitle( tr("用户名密码管理工具") );
    //密码编辑框隐藏显示
    ui->lineEditPassword->setEchoMode(QLineEdit::Password);

    m_pFormChild = NULL;  //初始化为 NULL
    //新建子窗口，窗口构造时参数里的 parent 必须是 0 或 NULL
    m_pFormChild = new FormChangePassword(NULL);

    //关联信号和槽
    //主窗口发送旧的用户名密码哈希给子窗口
    connect(this, SIGNAL(SendOldUserPassword(QString,QByteArray)),
            m_pFormChild, SLOT(RecvOldUserPassword(QString,QByteArray)) );
    //子窗口发送新的用户名密码哈希给主窗口
    connect(m_pFormChild, SIGNAL(SendNewUserPassword(QString,QByteArray)),
            this, SLOT(RecvNewUserPassword(QString,QByteArray)) );
}

//更新列表控件的显示
void MainWidget::UpdateListShow()
{
    //清除旧列表
    ui->listWidgetShow->clear();
    //根据映射重新显示
    int nCount = m_mapUserAndHash.count();
    //获取所有key，就是用户名
    QList<QString> listKeys = m_mapUserAndHash.keys();
    for(int i=0; i<nCount; i++)
    {
        QString curKey = listKeys[i];
        QString strTemp = curKey + QString("\t") + m_mapUserAndHash[curKey];
        ui->listWidgetShow->addItem( strTemp );
    }
}

//添加新用户
void MainWidget::on_pushButtonAddUser_clicked()
{
    //获取用户名和密码字符串
    QString strNewUser = ui->lineEditUser->text().trimmed();
    QString strPassword = ui->lineEditPassword->text().trimmed();
    if( strNewUser.isEmpty() || strPassword.isEmpty() )
    {
        QMessageBox::information(this, tr("用户名密码检查"), tr("用户名或密码为空，不能添加。"));
        return;
    }
    //判断是否已存在该用户
    if( m_mapUserAndHash.contains(strNewUser) )
    {
        QMessageBox::information(this, tr("用户名检查"), tr("已存在该用户名，不能再新增同名。"));
        return;
    }
    //新的用户名，计算哈希
    QByteArray baNewHash = QCryptographicHash::hash( strPassword.toUtf8(),
                                                     QCryptographicHash::Sha256 );
    //二进制哈希转为Hex字符串
    baNewHash = baNewHash.toHex();
    //新增用户名
    m_mapUserAndHash.insert( strNewUser, baNewHash );
    //更新显示
    UpdateListShow();
}

//删除选中行的用户
void MainWidget::on_pushButtonDelUser_clicked()
{
    //列表当前行号
    int curIndex = ui->listWidgetShow->currentRow();
    if( curIndex < 0 )
    {
        return;
    }
    //当前行号的条目
    QListWidgetItem *curItem = ui->listWidgetShow->item( curIndex );
    if( curItem->isSelected() )  //处于选中状态，才删除该行
    {
        //该条目处于选中状态
        QString curLine = curItem->text();
        QStringList curKeyValue = curLine.split( '\t' );
        //删除键值对
        m_mapUserAndHash.remove( curKeyValue[0] );
        //卸下条目
        ui->listWidgetShow->takeItem(curIndex);
        //删除条目
        delete curItem; curItem = NULL;
    }
}

//弹出子窗口，进行密码修改
void MainWidget::on_pushButtonChangePassword_clicked()
{
    //列表当前行号
    int curIndex = ui->listWidgetShow->currentRow();
    if( curIndex < 0 )
    {
        return;
    }
    //当前行号的条目
    QListWidgetItem *curItem = ui->listWidgetShow->item( curIndex );
    if( curItem->isSelected() )  //处于选中状态，才会修改该行密码
    {
        //该条目处于选中状态
        QString curLine = curItem->text();
        QStringList curKeyValue = curLine.split( '\t' );
        QString strUser = curKeyValue[0];
        QByteArray baOldHash = m_mapUserAndHash[strUser];
        //发送用户名和哈希给子窗口
        emit SendOldUserPassword(strUser, baOldHash);

        //显示修改密码的子窗口
        m_pFormChild->show();
        //如果子窗口被最小化，显示原本尺寸的窗口
        if( m_pFormChild->isMinimized() )
        {
            m_pFormChild->showNormal();
        }
        m_pFormChild->raise();
    }
}

//手动添加的槽函数，从子窗口接收新的密码哈希值
void MainWidget::RecvNewUserPassword(QString strUser, QByteArray baNewHash)
{
    //修改用户的密码哈希值
    m_mapUserAndHash[strUser] = baNewHash;
    //更新显示
    UpdateListShow();

    //修改完成，隐藏子窗口
    m_pFormChild->hide();
    //提示修改完成
    QMessageBox::information(this, tr("修改密码"), tr("修改密码成功。"));
}
