/****************************************************************************
** Meta object code from reading C++ file 'showchanges.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../npcomplete/showchanges.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'showchanges.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ShowChanges_t {
    QByteArrayData data[8];
    char stringdata[69];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ShowChanges_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ShowChanges_t qt_meta_stringdata_ShowChanges = {
    {
QT_MOC_LITERAL(0, 0, 11), // "ShowChanges"
QT_MOC_LITERAL(1, 12, 9), // "RecvValue"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 1), // "v"
QT_MOC_LITERAL(4, 25, 12), // "RecvNickName"
QT_MOC_LITERAL(5, 38, 10), // "strNewName"
QT_MOC_LITERAL(6, 49, 9), // "RecvCount"
QT_MOC_LITERAL(7, 59, 9) // "nNewCount"

    },
    "ShowChanges\0RecvValue\0\0v\0RecvNickName\0"
    "strNewName\0RecvCount\0nNewCount"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ShowChanges[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x0a /* Public */,
       4,    1,   32,    2, 0x0a /* Public */,
       6,    1,   35,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::Int,    7,

       0        // eod
};

void ShowChanges::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ShowChanges *_t = static_cast<ShowChanges *>(_o);
        switch (_id) {
        case 0: _t->RecvValue((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: _t->RecvNickName((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->RecvCount((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject ShowChanges::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ShowChanges.data,
      qt_meta_data_ShowChanges,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ShowChanges::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ShowChanges::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ShowChanges.stringdata))
        return static_cast<void*>(const_cast< ShowChanges*>(this));
    return QObject::qt_metacast(_clname);
}

int ShowChanges::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
