#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QScrollArea>  //滚动区域
#include <QLabel>       //标签用于显示图片
#include <QRadioButton> //单选按钮
#include <QHBoxLayout>  //水平布局器
#include <QVBoxLayout>  //垂直布局器
#include <QStringList>
#include <QList>
#include <QPoint>
#include <QPixmap>
#include <QSignalMapper> //信号高级映射

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    //初始化控件
    void InitControls();

public slots:
    //信号映射将所有按钮的信号都发给该槽函数
    void ShowProvince(int index);

private:
    Ui::Widget *ui;
    //省份名称
    QStringList m_listProvinces;
    //像素点位置
    QList<QPoint> m_listPoints;
    //地图
    QPixmap m_map;

    //加载地图和文本数据，包含省份和像素点位置
    void LoadData();

    //信号映射对象指针
    QSignalMapper *m_pSigMapper;

    //标签显示图片
    QLabel *m_labelMap;
    //左边滚动区域显示绘图
    QScrollArea *m_saLeftMap;
    //右边滚动区域显示一大堆按钮
    QScrollArea *m_saRightButtons;

};

#endif // WIDGET_H
