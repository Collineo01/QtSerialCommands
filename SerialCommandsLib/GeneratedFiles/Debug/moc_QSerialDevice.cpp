/****************************************************************************
** Meta object code from reading C++ file 'QSerialDevice.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../QSerialDevice.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QSerialDevice.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QSerialDevice_t {
    QByteArrayData data[19];
    char stringdata0[277];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QSerialDevice_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QSerialDevice_t qt_meta_stringdata_QSerialDevice = {
    {
QT_MOC_LITERAL(0, 0, 13), // "QSerialDevice"
QT_MOC_LITERAL(1, 14, 31), // "responseMatchingCommandReceived"
QT_MOC_LITERAL(2, 46, 0), // ""
QT_MOC_LITERAL(3, 47, 8), // "response"
QT_MOC_LITERAL(4, 56, 13), // "SerialCommand"
QT_MOC_LITERAL(5, 70, 7), // "command"
QT_MOC_LITERAL(6, 78, 15), // "messageReceived"
QT_MOC_LITERAL(7, 94, 7), // "message"
QT_MOC_LITERAL(8, 102, 17), // "connectionUpdated"
QT_MOC_LITERAL(9, 120, 9), // "connected"
QT_MOC_LITERAL(10, 130, 16), // "connectionFailed"
QT_MOC_LITERAL(11, 147, 15), // "commandTimedOut"
QT_MOC_LITERAL(12, 163, 4), // "args"
QT_MOC_LITERAL(13, 168, 4), // "port"
QT_MOC_LITERAL(14, 173, 12), // "portTimedOut"
QT_MOC_LITERAL(15, 186, 22), // "handleMatchingResponse"
QT_MOC_LITERAL(16, 209, 21), // "handleMessageReceived"
QT_MOC_LITERAL(17, 231, 23), // "handleConnectionUpdated"
QT_MOC_LITERAL(18, 255, 21) // "handleCommandTimedOut"

    },
    "QSerialDevice\0responseMatchingCommandReceived\0"
    "\0response\0SerialCommand\0command\0"
    "messageReceived\0message\0connectionUpdated\0"
    "connected\0connectionFailed\0commandTimedOut\0"
    "args\0port\0portTimedOut\0handleMatchingResponse\0"
    "handleMessageReceived\0handleConnectionUpdated\0"
    "handleCommandTimedOut"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QSerialDevice[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   69,    2, 0x06 /* Public */,
       6,    1,   74,    2, 0x06 /* Public */,
       8,    2,   77,    2, 0x06 /* Public */,
       8,    1,   82,    2, 0x26 /* Public | MethodCloned */,
      11,    3,   85,    2, 0x06 /* Public */,
      14,    1,   92,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      15,    2,   95,    2, 0x09 /* Protected */,
      16,    1,  100,    2, 0x09 /* Protected */,
      17,    2,  103,    2, 0x09 /* Protected */,
      17,    1,  108,    2, 0x29 /* Protected | MethodCloned */,
      18,    3,  111,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QByteArray, 0x80000000 | 4,    3,    5,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::Bool, QMetaType::Bool,    9,   10,
    QMetaType::Void, QMetaType::Bool,    9,
    QMetaType::Void, QMetaType::QString, QMetaType::QVariantList, QMetaType::Int,    5,   12,   13,
    QMetaType::Void, QMetaType::Int,   13,

 // slots: parameters
    QMetaType::Void, QMetaType::QByteArray, 0x80000000 | 4,    3,    5,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::Bool, QMetaType::Bool,    9,   10,
    QMetaType::Void, QMetaType::Bool,    9,
    QMetaType::Void, QMetaType::QString, QMetaType::QVariantList, QMetaType::Int,    5,   12,   13,

       0        // eod
};

void QSerialDevice::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QSerialDevice *_t = static_cast<QSerialDevice *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->responseMatchingCommandReceived((*reinterpret_cast< const QByteArray(*)>(_a[1])),(*reinterpret_cast< const SerialCommand(*)>(_a[2]))); break;
        case 1: _t->messageReceived((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->connectionUpdated((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 3: _t->connectionUpdated((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->commandTimedOut((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QList<QVariant>(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 5: _t->portTimedOut((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->handleMatchingResponse((*reinterpret_cast< const QByteArray(*)>(_a[1])),(*reinterpret_cast< const SerialCommand(*)>(_a[2]))); break;
        case 7: _t->handleMessageReceived((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: _t->handleConnectionUpdated((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 9: _t->handleConnectionUpdated((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->handleCommandTimedOut((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QList<QVariant>(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (QSerialDevice::*_t)(QByteArray const & , SerialCommand const & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QSerialDevice::responseMatchingCommandReceived)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (QSerialDevice::*_t)(QString const & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QSerialDevice::messageReceived)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (QSerialDevice::*_t)(bool , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QSerialDevice::connectionUpdated)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (QSerialDevice::*_t)(QString , QList<QVariant> , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QSerialDevice::commandTimedOut)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (QSerialDevice::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QSerialDevice::portTimedOut)) {
                *result = 5;
                return;
            }
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
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void QSerialDevice::responseMatchingCommandReceived(QByteArray const & _t1, SerialCommand const & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QSerialDevice::messageReceived(QString const & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QSerialDevice::connectionUpdated(bool _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 4
void QSerialDevice::commandTimedOut(QString _t1, QList<QVariant> _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void QSerialDevice::portTimedOut(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
