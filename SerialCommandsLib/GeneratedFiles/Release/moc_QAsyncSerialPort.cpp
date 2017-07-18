/****************************************************************************
** Meta object code from reading C++ file 'QAsyncSerialPort.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../QAsyncSerialPort.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QAsyncSerialPort.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QAsyncSerialPort_t {
    QByteArrayData data[29];
    char stringdata0[367];
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
QT_MOC_LITERAL(6, 60, 11), // "messageSent"
QT_MOC_LITERAL(7, 72, 7), // "updated"
QT_MOC_LITERAL(8, 80, 7), // "message"
QT_MOC_LITERAL(9, 88, 14), // "openSerialPort"
QT_MOC_LITERAL(10, 103, 8), // "portName"
QT_MOC_LITERAL(11, 112, 8), // "BaudRate"
QT_MOC_LITERAL(12, 121, 8), // "baudRate"
QT_MOC_LITERAL(13, 130, 21), // "QSerialPort::DataBits"
QT_MOC_LITERAL(14, 152, 8), // "dataBits"
QT_MOC_LITERAL(15, 161, 19), // "QSerialPort::Parity"
QT_MOC_LITERAL(16, 181, 6), // "parity"
QT_MOC_LITERAL(17, 188, 21), // "QSerialPort::StopBits"
QT_MOC_LITERAL(18, 210, 8), // "stopBits"
QT_MOC_LITERAL(19, 219, 24), // "QSerialPort::FlowControl"
QT_MOC_LITERAL(20, 244, 11), // "flowControl"
QT_MOC_LITERAL(21, 256, 15), // "closeSerialPort"
QT_MOC_LITERAL(22, 272, 8), // "readData"
QT_MOC_LITERAL(23, 281, 13), // "handleTimeout"
QT_MOC_LITERAL(24, 295, 18), // "handleBytesWritten"
QT_MOC_LITERAL(25, 314, 5), // "bytes"
QT_MOC_LITERAL(26, 320, 11), // "handleError"
QT_MOC_LITERAL(27, 332, 28), // "QSerialPort::SerialPortError"
QT_MOC_LITERAL(28, 361, 5) // "error"

    },
    "QAsyncSerialPort\0dataRead\0\0data\0"
    "connectionUpdated\0connected\0messageSent\0"
    "updated\0message\0openSerialPort\0portName\0"
    "BaudRate\0baudRate\0QSerialPort::DataBits\0"
    "dataBits\0QSerialPort::Parity\0parity\0"
    "QSerialPort::StopBits\0stopBits\0"
    "QSerialPort::FlowControl\0flowControl\0"
    "closeSerialPort\0readData\0handleTimeout\0"
    "handleBytesWritten\0bytes\0handleError\0"
    "QSerialPort::SerialPortError\0error"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QAsyncSerialPort[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x06 /* Public */,
       4,    1,   67,    2, 0x06 /* Public */,
       6,    0,   70,    2, 0x06 /* Public */,
       7,    1,   71,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    6,   74,    2, 0x0a /* Public */,
      21,    0,   87,    2, 0x0a /* Public */,
      22,    0,   88,    2, 0x08 /* Private */,
      23,    0,   89,    2, 0x08 /* Private */,
      24,    1,   90,    2, 0x08 /* Private */,
      26,    1,   93,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QByteArray,    3,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    8,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, 0x80000000 | 11, 0x80000000 | 13, 0x80000000 | 15, 0x80000000 | 17, 0x80000000 | 19,   10,   12,   14,   16,   18,   20,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::LongLong,   25,
    QMetaType::Void, 0x80000000 | 27,   28,

       0        // eod
};

void QAsyncSerialPort::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QAsyncSerialPort *_t = static_cast<QAsyncSerialPort *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->dataRead((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 1: _t->connectionUpdated((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->messageSent(); break;
        case 3: _t->updated((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->openSerialPort((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< BaudRate(*)>(_a[2])),(*reinterpret_cast< QSerialPort::DataBits(*)>(_a[3])),(*reinterpret_cast< QSerialPort::Parity(*)>(_a[4])),(*reinterpret_cast< QSerialPort::StopBits(*)>(_a[5])),(*reinterpret_cast< QSerialPort::FlowControl(*)>(_a[6]))); break;
        case 5: _t->closeSerialPort(); break;
        case 6: _t->readData(); break;
        case 7: _t->handleTimeout(); break;
        case 8: _t->handleBytesWritten((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 9: _t->handleError((*reinterpret_cast< QSerialPort::SerialPortError(*)>(_a[1]))); break;
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
            typedef void (QAsyncSerialPort::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QAsyncSerialPort::connectionUpdated)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (QAsyncSerialPort::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QAsyncSerialPort::messageSent)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (QAsyncSerialPort::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QAsyncSerialPort::updated)) {
                *result = 3;
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
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
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
void QAsyncSerialPort::connectionUpdated(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QAsyncSerialPort::messageSent()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void QAsyncSerialPort::updated(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
