#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

//结构体都按 1 字节补齐，因为编译器默认按 4 字节补齐，导致 BMPFileHeader 长度 16，16是错的
#pragma pack(1)

//定义文件头 BMPFileHeader，长度14字节
struct BMPFileHeader
{
    quint16 bfType; //文件类型，原始两字节 'BM'
    quint32 bfSize; //BMP图片文件大小
    quint16 bfReserved1;    //保留字段1，数值为 0
    quint16 bfReserved2;    //保留字段2，数值为 0
    quint32 bfOffBits;      //像素点数据起始位置，相对于 BMPFileHeader 的偏移量，以字节为单位
};

//定义信息头 BMPInfoHeader，长度40字节
struct BMPInfoHeader
{
    quint32 biSize; //本结构体长度，占用字节数
    quint32 biWidth;    //图片宽度，像素点数
    quint32 biHeight;   //图片高度，像素点数
    quint16 biPlanes;   //目标设备级别，数值为 1 (图层数或叫帧数)
    quint16 biBitCount; //每个像素点占用的位数，就是颜色深度 (位深度)
    quint32 biCompression; //是否压缩，一般为 0 不压缩
    quint32 biSizeImage;   //像素点数据总共占用的字节数，因为每行像素点数据末尾会按4字节对齐，对齐需要的字节数也算在内
    quint32 biXPelsPerMeter;//水平分辨率，像素点数每米(== 水平DPI * 39.3701)
    quint32 biYPelsPerMeter;//垂直分辨率，像素点数每米(== 垂直DPI * 39.3701)
    quint32 biClrUsed;      //颜色表中实际用到的颜色数目
    quint32 biClrImportant;//图片显示中重要颜色数目
};

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
    void on_pushButtonBrowse_clicked();

    void on_pushButtonShowPic_clicked();

    void on_pushButtonReadHeader_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
