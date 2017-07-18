/****************************************************************************
** Meta object code from reading C++ file 'QSerialDevice.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../QSerialDevice.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QSerialDevice.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QSerialDevice_t {
    QByteArrayData data[10];
    char stringdata0[134];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QSerialDevice_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QSerialDevice_t qt_meta_stringdata_QSerialDevice = {
    {
QT_MOC_LITERAL(0, 0, 13), // "QSerialDevice"
QT_MOC_LITERAL(1, 14, 22), // "handleMatchingResponse"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 8), // "response"
QT_MOC_LITERAL(4, 47, 14), // "QSerialCommand"
QT_MOC_LITERAL(5, 62, 7), // "command"
QT_MOC_LITERAL(6, 70, 21), // "handleMessageReceived"
QT_MOC_LITERAL(7, 92, 7), // "message"
QT_MOC_LITERAL(8, 100, 23), // "handleConnectionUpdated"
QT_MOC_LITERAL(9, 124, 9) // "connected"

    },
    "QSerialDevice\0handleMatchingResponse\0"
    "\0response\0QSerialCommand\0command\0"
    "handleMessageReceived\0message\0"
    "handleConnectionUpdated\0connected"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QSerialDevice[] = {

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
       1,    2,   29,    2, 0x09 /* Protected */,
       6,    1,   34,    2, 0x09 /* Protected */,
       8,    1,   37,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void, QMetaType::QByteArray, 0x80000000 | 4,    3,    5,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::Bool,    9,

       0        // eod
};

void QSerialDevice::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QSerialDevice *_t = static_cast<QSerialDevice *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->handleMatchingResponse((*reinterpret_cast< const QByteArray(*)>(_a[1])),(*reinterpret_cast< const SerialCommand(*)>(_a[2]))); break;
        case 1: _t->handleMessageReceived((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->handleConnectionUpdated((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject QSerialDevice::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QSerialDevice.data,
      qt_meta_data_QSerialDevice,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *QSerialDevice::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QSerialDevice::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QSerialDevice.stringdata0))
        return static_cast<void*>(const_cast< QSerialDevice*>(this));
    return QObject::qt_metacast(_clname);
}

int QSerialDevice::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
