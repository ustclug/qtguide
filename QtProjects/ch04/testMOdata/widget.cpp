#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

/*******************************************/
//从 moc_widget.cpp 里复制的代码

#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>

struct qt_meta_stringdata_Widget_t {
    QByteArrayData data[13];
    char stringdata[125];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Widget_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Widget_t qt_meta_stringdata_Widget = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Widget"
QT_MOC_LITERAL(1, 7, 15), // "nickNameChanged"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 10), // "strNewName"
QT_MOC_LITERAL(4, 35, 12), // "countChanged"
QT_MOC_LITERAL(5, 48, 9), // "nNewCount"
QT_MOC_LITERAL(6, 58, 12), // "valueChanged"
QT_MOC_LITERAL(7, 71, 11), // "dblNewValue"
QT_MOC_LITERAL(8, 83, 11), // "setNickName"
QT_MOC_LITERAL(9, 95, 8), // "setCount"
QT_MOC_LITERAL(10, 104, 8), // "nickName"
QT_MOC_LITERAL(11, 113, 5), // "count"
QT_MOC_LITERAL(12, 119, 5) // "value"

    },
    "Widget\0nickNameChanged\0\0strNewName\0"
    "countChanged\0nNewCount\0valueChanged\0"
    "dblNewValue\0setNickName\0setCount\0"
    "nickName\0count\0value"
};
#undef QT_MOC_LITERAL
/*******************************************/

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);


    /*
    QByteArrayData db;
    //qDebug()<<sizeof(db.alloc);  //alloc 占用 31 bit
    //qDebug()<<sizeof(db.capacityReserved);//capacityReserved 占用 1 bit
    qDebug()<<sizeof(db.offset);    //有用
    qDebug()<<sizeof(db.ref);
    qDebug()<<sizeof(db.size);      //有用
    */
    qDebug()<<sizeof(QByteArrayData);
    //打印字符串
    for (int i=0; i<13; i++)
    {
        //把 void* 转成 char* 打印
        qDebug()<< (char *)(qt_meta_stringdata_Widget.data[i].data());
    }
    qDebug()<<endl;
    qDebug()<<this->metaObject()->className();
    //查询信号
    QByteArray ba = QMetaObject::normalizedSignature("callSth(int, double)");
    qDebug()<<"callSth: "<<this->metaObject()->indexOfMethod( ba );
    //查询槽
    ba = QMetaObject::normalizedSignature("recvSth(int, double)");
    qDebug()<<"recvSth: "<<this->metaObject()->indexOfMethod( ba );

}

void Widget::recvSth(int a, double b)
{
    qDebug()<<a;
    qDebug()<<b;
}

Widget::~Widget()
{
    delete ui;
}

/*
 *
struct Q_CORE_EXPORT QArrayData
{
    QtPrivate::RefCount ref;
    int size;
    uint alloc : 31;
    uint capacityReserved : 1;

    qptrdiff offset; // in bytes from beginning of header

    void *data()
    {
        Q_ASSERT(size == 0
                || offset < 0 || size_t(offset) >= sizeof(QArrayData));
        return reinterpret_cast<char *>(this) + offset;
    }

    const void *data() const
    {
        Q_ASSERT(size == 0
                || offset < 0 || size_t(offset) >= sizeof(QArrayData));
        return reinterpret_cast<const char *>(this) + offset;
    }

 *
 * */
