#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    //声明属性
    //不直接标出成员变量的形式
    Q_PROPERTY(QString nickName READ nickName WRITE setNickName NOTIFY nickNameChanged)
    //直接标出成员变量的形式
    Q_PROPERTY(int count MEMBER m_count READ count WRITE setCount NOTIFY countChanged)
    //标出成员变量，可以省略读写函数
    Q_PROPERTY(double value MEMBER m_value NOTIFY valueChanged)

    //nickName读函数声明
    const QString& nickName();
    //count读函数
    int count();

    //value属性声明时，指出了成员变量并省略了读写函数，它的读写代码由moc工具自动生成
    //value数值被修改时，valueChanged信号会自动触发
    //自动生成的读写代码只有简单的读写功能，不能做数值有效性检查

signals:
    //三个属性数值变化时发信号
    void nickNameChanged(const QString& strNewName);
    void countChanged(int nNewCount);
    void valueChanged(double dblNewValue);

public slots:
    //写函数通常可以作为槽函数，方便与其他信号关联，自动调整数值
    //nickName写函数声明
    void setNickName(const QString& strNewName);
    //count写函数声明
    void setCount(int nNewCount);
    //value写代码由 moc 自动生成，没有写函数

private:
    Ui::Widget *ui;
    //三个私有变量，对应是三个属性
    QString m_nickName;
    int m_count;
    double m_value;
};

#endif // WIDGET_H
