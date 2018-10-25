#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QVector>

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
    //省份变化时，自动加载该省的市县
    void onProvinceIndexChange(int index);
    //市县变化时，自动显示市县的经纬度到编辑框
    void onCityIndexChange(int index);

private:
    Ui::Widget *ui;
    //保存省份名称
    QVector<QString> m_vProvinces;
    //二维向量保存市县名称
    QVector<  QVector<QString>  > m_vCities;
    //二维向量保存市县的经度
    QVector<  QVector<double>  > m_vLongitudes;
    //二维向量保存市县的纬度
    QVector<  QVector<double>  > m_vLatitudes;
    //从 position.txt 加载各省市及其经纬度
    void loadPositions();
};

#endif // WIDGET_H
