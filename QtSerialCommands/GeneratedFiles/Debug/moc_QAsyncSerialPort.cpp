/****************************************************************************
** Meta object code from reading C++ file 'QAsyncSerialPort.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../QAsyncSerialPort.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QAsyncSerialPort.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QAsyncSerialPort_t {
    QByteArrayData data[21];
    char stringdata0[248];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QAsyncSerialPort_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QAsyncSerialPort_t qt_meta_stringdata_QAsyncSerialPort = {
    {
QT_MOC_LITERAL(0, 0, 16), // "QAsyncSerialPort"
QT_MOC_LITERAL(1, 17, 8), // "dataRead"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 4), // "data"
QT_MOC_LITERAL(4, 32, 17), // "connectionUpdated"
QT_MOC_LITERAL(5, 50, 9), // "connected"
QT_MOC_LITERAL(6, 60, 16), // "connectionFailed"
QT_MOC_LITERAL(7, 77, 11), // "messageSent"
QT_MOC_LITERAL(8, 89, 7), // "updated"
QT_MOC_LITERAL(9, 97, 7), // "message"
QT_MOC_LITERAL(10, 105, 8), // "openPort"
QT_MOC_LITERAL(11, 114, 19), // "SerialPortSettings*"
QT_MOC_LITERAL(12, 134, 8), // "settings"
QT_MOC_LITERAL(13, 143, 9), // "closePort"
QT_MOC_LITERAL(14, 153, 8), // "readData"
QT_MOC_LITERAL(15, 162, 13), // "handleTimeout"
QT_MOC_LITERAL(16, 176, 18), // "handleBytesWritten"
QT_MOC_LITERAL(17, 195, 5), // "bytes"
QT_MOC_LITERAL(18, 201, 11), // "handleError"
QT_MOC_LITERAL(19, 213, 28), // "QSerialPort::SerialPortError"
QT_MOC_LITERAL(20, 242, 5) // "error"

    },
    "QAsyncSerialPort\0dataRead\0\0data\0"
    "connectionUpdated\0connected\0"
    "connectionFailed\0messageSent\0updated\0"
    "message\0openPort\0SerialPortSettings*\0"
    "settings\0closePort\0readData\0handleTimeout\0"
    "handleBytesWritten\0bytes\0handleError\0"
    "QSerialPort::SerialPortError\0error"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QAsyncSerialPort[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x06 /* Public */,
       4,    2,   72,    2, 0x06 /* Public */,
       4,    1,   77,    2, 0x26 /* Public | MethodCloned */,
       7,    0,   80,    2, 0x06 /* Public */,
       8,    1,   81,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    1,   84,    2, 0x0a /* Public */,
      13,    0,   87,    2, 0x0a /* Public */,
      14,    0,   88,    2, 0x08 /* Private */,
      15,    0,   89,    2, 0x08 /* Private */,
      16,    1,   90,    2, 0x08 /* Private */,
      18,    1,   93,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QByteArray,    3,
    QMetaType::Void, QMetaType::Bool, QMetaType::Bool,    5,    6,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    9,

 // slots: parameters
    QMetaType::Bool, 0x80000000 | 11,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::LongLong,   17,
    QMetaType::Void, 0x80000000 | 19,   20,

       0        // eod
};

void QAsyncSerialPort::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QAsyncSerialPort *_t = static_cast<QAsyncSerialPort *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->dataRead((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 1: _t->connectionUpdated((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 2: _t->connectionUpdated((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->messageSent(); break;
        case 4: _t->updated((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: { bool _r = _t->openPort((*reinterpret_cast< SerialPortSettings*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 6: _t->closePort(); break;
        case 7: _t->readData(); break;
        case 8: _t->handleTimeout(); break;
        case 9: _t->handleBytesWritten((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 10: _t->handleError((*reinterpret_cast< QSerialPort::SerialPortError(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (QAsyncSerialPort::*_t)(QByteArray );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QAsyncSerialPort::dataRead)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (QAsyncSerialPort::*_t)(bool , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QAsyncSerialPort::connectionUpdated)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (QAsyncSerialPort::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QAsyncSerialPort::messageSent)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (QAsyncSerialPort::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QAsyncSerialPort::updated)) {
                *result = 4;
                return;
            }
        }
    }
}

const QMetaObject QAsyncSerialPort::staticMetaObject = {
    { &QSerialPort::staticMetaObject, qt_meta_stringdata_QAsyncSerialPort.data,
      qt_meta_data_QAsyncSerialPort,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *QAsyncSerialPort::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QAsyncSerialPort::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QAsyncSerialPort.stringdata0))
        return static_cast<void*>(const_cast< QAsyncSerialPort*>(this));
    return QSerialPort::qt_metacast(_clname);
}

int QAsyncSerialPort::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSerialPort::qt_metacall(_c, _id, _a);
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
void QAsyncSerialPort::dataRead(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QAsyncSerialPort::connectionUpdated(bool _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 3
void QAsyncSerialPort::messageSent()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void QAsyncSerialPort::updated(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
