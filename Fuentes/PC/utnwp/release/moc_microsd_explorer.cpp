/****************************************************************************
** Meta object code from reading C++ file 'microsd_explorer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.0.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../microsd_explorer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'microsd_explorer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.0.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MicroSD_explorer_t {
    QByteArrayData data[11];
    char stringdata[239];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_MicroSD_explorer_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_MicroSD_explorer_t qt_meta_stringdata_MicroSD_explorer = {
    {
QT_MOC_LITERAL(0, 0, 16),
QT_MOC_LITERAL(1, 17, 15),
QT_MOC_LITERAL(2, 33, 0),
QT_MOC_LITERAL(3, 34, 27),
QT_MOC_LITERAL(4, 62, 13),
QT_MOC_LITERAL(5, 76, 30),
QT_MOC_LITERAL(6, 107, 21),
QT_MOC_LITERAL(7, 129, 20),
QT_MOC_LITERAL(8, 150, 24),
QT_MOC_LITERAL(9, 175, 23),
QT_MOC_LITERAL(10, 199, 38)
    },
    "MicroSD_explorer\0CargaLista_Done\0\0"
    "pushButton_agregar_released\0ReadyToUpdate\0"
    "on_pushButton_agregar_released\0"
    "DisableButton_agregar\0EnableButton_agregar\0"
    "DisableButton_actualizar\0"
    "EnableButton_actualizar\0"
    "on_pushButton_ActualizarLista_released\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MicroSD_explorer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x05,
       3,    0,   60,    2, 0x05,
       4,    0,   61,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
       5,    0,   62,    2, 0x08,
       6,    0,   63,    2, 0x08,
       7,    0,   64,    2, 0x08,
       8,    0,   65,    2, 0x08,
       9,    0,   66,    2, 0x08,
      10,    0,   67,    2, 0x08,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MicroSD_explorer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MicroSD_explorer *_t = static_cast<MicroSD_explorer *>(_o);
        switch (_id) {
        case 0: _t->CargaLista_Done(); break;
        case 1: _t->pushButton_agregar_released(); break;
        case 2: _t->ReadyToUpdate(); break;
        case 3: _t->on_pushButton_agregar_released(); break;
        case 4: _t->DisableButton_agregar(); break;
        case 5: _t->EnableButton_agregar(); break;
        case 6: _t->DisableButton_actualizar(); break;
        case 7: _t->EnableButton_actualizar(); break;
        case 8: _t->on_pushButton_ActualizarLista_released(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MicroSD_explorer::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MicroSD_explorer::CargaLista_Done)) {
                *result = 0;
            }
        }
        {
            typedef void (MicroSD_explorer::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MicroSD_explorer::pushButton_agregar_released)) {
                *result = 1;
            }
        }
        {
            typedef void (MicroSD_explorer::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MicroSD_explorer::ReadyToUpdate)) {
                *result = 2;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject MicroSD_explorer::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MicroSD_explorer.data,
      qt_meta_data_MicroSD_explorer,  qt_static_metacall, 0, 0}
};


const QMetaObject *MicroSD_explorer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MicroSD_explorer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MicroSD_explorer.stringdata))
        return static_cast<void*>(const_cast< MicroSD_explorer*>(this));
    return QWidget::qt_metacast(_clname);
}

int MicroSD_explorer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void MicroSD_explorer::CargaLista_Done()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void MicroSD_explorer::pushButton_agregar_released()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void MicroSD_explorer::ReadyToUpdate()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
