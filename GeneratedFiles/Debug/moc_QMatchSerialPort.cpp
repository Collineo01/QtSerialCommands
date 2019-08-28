/****************************************************************************
** Meta object code from reading C++ file 'QMatchSerialPort.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../QMatchSerialPort.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QMatchSerialPort.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QMatchSerialPort_t {
    QByteArrayData data[26];
    char stringdata0[444];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QMatchSerialPort_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QMatchSerialPort_t qt_meta_stringdata_QMatchSerialPort = {
    {
QT_MOC_LITERAL(0, 0, 16), // "QMatchSerialPort"
QT_MOC_LITERAL(1, 17, 20), // "sendCommandRequested"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 13), // "SerialCommand"
QT_MOC_LITERAL(4, 53, 7), // "command"
QT_MOC_LITERAL(5, 61, 24), // "matchingResponseReceived"
QT_MOC_LITERAL(6, 86, 8), // "response"
QT_MOC_LITERAL(7, 95, 15), // "messageReceived"
QT_MOC_LITERAL(8, 111, 7), // "message"
QT_MOC_LITERAL(9, 119, 11), // "translation"
QT_MOC_LITERAL(10, 131, 24), // "smartMatchingModeChanged"
QT_MOC_LITERAL(11, 156, 7), // "devMode"
QT_MOC_LITERAL(12, 164, 15), // "commandTimedOut"
QT_MOC_LITERAL(13, 180, 23), // "QList<SerialCommandArg>"
QT_MOC_LITERAL(14, 204, 4), // "args"
QT_MOC_LITERAL(15, 209, 4), // "port"
QT_MOC_LITERAL(16, 214, 28), // "removeLastCommandSentRequest"
QT_MOC_LITERAL(17, 243, 31), // "removeFirstCommandToSendRequest"
QT_MOC_LITERAL(18, 275, 28), // "handleNextCommandReadyToSend"
QT_MOC_LITERAL(19, 304, 27), // "handleFoundMatchingResponse"
QT_MOC_LITERAL(20, 332, 14), // "handleResponse"
QT_MOC_LITERAL(21, 347, 4), // "data"
QT_MOC_LITERAL(22, 352, 24), // "handlePullCommandTimeout"
QT_MOC_LITERAL(23, 377, 29), // "handleSmartMatchingModeChange"
QT_MOC_LITERAL(24, 407, 11), // "isBypassing"
QT_MOC_LITERAL(25, 419, 24) // "handleSendCommandRequest"

    },
    "QMatchSerialPort\0sendCommandRequested\0"
    "\0SerialCommand\0command\0matchingResponseReceived\0"
    "response\0messageReceived\0message\0"
    "translation\0smartMatchingModeChanged\0"
    "devMode\0commandTimedOut\0QList<SerialCommandArg>\0"
    "args\0port\0removeLastCommandSentRequest\0"
    "removeFirstCommandToSendRequest\0"
    "handleNextCommandReadyToSend\0"
    "handleFoundMatchingResponse\0handleResponse\0"
    "data\0handlePullCommandTimeout\0"
    "handleSmartMatchingModeChange\0isBypassing\0"
    "handleSendCommandRequest"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QMatchSerialPort[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x06 /* Public */,
       5,    2,   82,    2, 0x06 /* Public */,
       7,    2,   87,    2, 0x06 /* Public */,
      10,    1,   92,    2, 0x06 /* Public */,
      12,    3,   95,    2, 0x06 /* Public */,
      16,    0,  102,    2, 0x06 /* Public */,
      17,    0,  103,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      18,    0,  104,    2, 0x08 /* Private */,
      19,    2,  105,    2, 0x08 /* Private */,
      20,    1,  110,    2, 0x08 /* Private */,
      22,    0,  113,    2, 0x08 /* Private */,
      23,    1,  114,    2, 0x08 /* Private */,
      25,    1,  117,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::QByteArray, 0x80000000 | 3,    6,    4,
    QMetaType::Void, QMetaType::QByteArray, QMetaType::QString,    8,    9,
    QMetaType::Void, QMetaType::Bool,   11,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 13, QMetaType::Int,    4,   14,   15,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray, 0x80000000 | 3,    6,    4,
    QMetaType::Void, QMetaType::QByteArray,   21,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   24,
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void QMatchSerialPort::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QMatchSerialPort *_t = static_cast<QMatchSerialPort *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendCommandRequested((*reinterpret_cast< const SerialCommand(*)>(_a[1]))); break;
        case 1: _t->matchingResponseReceived((*reinterpret_cast< const QByteArray(*)>(_a[1])),(*reinterpret_cast< const SerialCommand(*)>(_a[2]))); break;
        case 2: _t->messageReceived((*reinterpret_cast< const QByteArray(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 3: _t->smartMatchingModeChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->commandTimedOut((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QList<SerialCommandArg>(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 5: _t->removeLastCommandSentRequest(); break;
        case 6: _t->removeFirstCommandToSendRequest(); break;
        case 7: _t->handleNextCommandReadyToSend(); break;
        case 8: _t->handleFoundMatchingResponse((*reinterpret_cast< const QByteArray(*)>(_a[1])),(*reinterpret_cast< const SerialCommand(*)>(_a[2]))); break;
        case 9: _t->handleResponse((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 10: _t->handlePullCommandTimeout(); break;
        case 11: _t->handleSmartMatchingModeChange((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: _t->handleSendCommandRequest((*reinterpret_cast< const SerialCommand(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (QMatchSerialPort::*_t)(const SerialCommand & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QMatchSerialPort::sendCommandRequested)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (QMatchSerialPort::*_t)(const QByteArray & , const SerialCommand & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QMatchSerialPort::matchingResponseReceived)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (QMatchSerialPort::*_t)(const QByteArray & , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QMatchSerialPort::messageReceived)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (QMatchSerialPort::*_t)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QMatchSerialPort::smartMatchingModeChanged)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (QMatchSerialPort::*_t)(QString , QList<SerialCommandArg> , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QMatchSerialPort::commandTimedOut)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (QMatchSerialPort::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QMatchSerialPort::removeLastCommandSentRequest)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (QMatchSerialPort::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QMatchSerialPort::removeFirstCommandToSendRequest)) {
                *result = 6;
                return;
            }
        }
    }
}

const QMetaObject QMatchSerialPort::staticMetaObject = {
    { &QAsyncSerialPort::staticMetaObject, qt_meta_stringdata_QMatchSerialPort.data,
      qt_meta_data_QMatchSerialPort,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *QMatchSerialPort::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QMatchSerialPort::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QMatchSerialPort.stringdata0))
        return static_cast<void*>(this);
    return QAsyncSerialPort::qt_metacast(_clname);
}

int QMatchSerialPort::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAsyncSerialPort::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void QMatchSerialPort::sendCommandRequested(const SerialCommand & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QMatchSerialPort::matchingResponseReceived(const QByteArray & _t1, const SerialCommand & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QMatchSerialPort::messageReceived(const QByteArray & _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QMatchSerialPort::smartMatchingModeChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void QMatchSerialPort::commandTimedOut(QString _t1, QList<SerialCommandArg> _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void QMatchSerialPort::removeLastCommandSentRequest()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void QMatchSerialPort::removeFirstCommandToSendRequest()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
