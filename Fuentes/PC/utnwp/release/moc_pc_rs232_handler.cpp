/****************************************************************************
** Meta object code from reading C++ file 'pc_rs232_handler.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.0.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../pc_rs232_handler.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pc_rs232_handler.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.0.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_pc_rs232_handler_t {
    QByteArrayData data[10];
    char stringdata[143];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_pc_rs232_handler_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_pc_rs232_handler_t qt_meta_stringdata_pc_rs232_handler = {
    {
QT_MOC_LITERAL(0, 0, 16),
QT_MOC_LITERAL(1, 17, 16),
QT_MOC_LITERAL(2, 34, 0),
QT_MOC_LITERAL(3, 35, 17),
QT_MOC_LITERAL(4, 53, 11),
QT_MOC_LITERAL(5, 65, 12),
QT_MOC_LITERAL(6, 78, 15),
QT_MOC_LITERAL(7, 94, 12),
QT_MOC_LITERAL(8, 107, 17),
QT_MOC_LITERAL(9, 125, 16)
    },
    "pc_rs232_handler\0ConnectionFailed\0\0"
    "ConnectionSuccess\0SinConexion\0"
    "RecibirDatos\0onDeviceRemoved\0QextPortInfo\0"
    "onDeviceConnected\0OnTimerTxTimeout\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_pc_rs232_handler[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x05,
       3,    0,   50,    2, 0x05,
       4,    0,   51,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
       5,    0,   52,    2, 0x0a,
       6,    1,   53,    2, 0x08,
       8,    1,   56,    2, 0x08,
       9,    0,   59,    2, 0x08,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    2,
    QMetaType::Void, 0x80000000 | 7,    2,
    QMetaType::Void,

       0        // eod
};

void pc_rs232_handler::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        pc_rs232_handler *_t = static_cast<pc_rs232_handler *>(_o);
        switch (_id) {
        case 0: _t->ConnectionFailed(); break;
        case 1: _t->ConnectionSuccess(); break;
        case 2: _t->SinConexion(); break;
        case 3: _t->RecibirDatos(); break;
        case 4: _t->onDeviceRemoved((*reinterpret_cast< const QextPortInfo(*)>(_a[1]))); break;
        case 5: _t->onDeviceConnected((*reinterpret_cast< const QextPortInfo(*)>(_a[1]))); break;
        case 6: _t->OnTimerTxTimeout(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (pc_rs232_handler::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&pc_rs232_handler::ConnectionFailed)) {
                *result = 0;
            }
        }
        {
            typedef void (pc_rs232_handler::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&pc_rs232_handler::ConnectionSuccess)) {
                *result = 1;
            }
        }
        {
            typedef void (pc_rs232_handler::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&pc_rs232_handler::SinConexion)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject pc_rs232_handler::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_pc_rs232_handler.data,
      qt_meta_data_pc_rs232_handler,  qt_static_metacall, 0, 0}
};


const QMetaObject *pc_rs232_handler::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *pc_rs232_handler::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_pc_rs232_handler.stringdata))
        return static_cast<void*>(const_cast< pc_rs232_handler*>(this));
    return QObject::qt_metacast(_clname);
}

int pc_rs232_handler::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void pc_rs232_handler::ConnectionFailed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void pc_rs232_handler::ConnectionSuccess()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void pc_rs232_handler::SinConexion()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
