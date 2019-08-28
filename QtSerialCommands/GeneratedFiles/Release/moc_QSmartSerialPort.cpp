/****************************************************************************
** Meta object code from reading C++ file 'QSmartSerialPort.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../QSmartSerialPort.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QSmartSerialPort.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QSmartSerialPort_t {
    QByteArrayData data[30];
    char stringdata0[534];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QSmartSerialPort_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QSmartSerialPort_t qt_meta_stringdata_QSmartSerialPort = {
    {
QT_MOC_LITERAL(0, 0, 16), // "QSmartSerialPort"
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
QT_MOC_LITERAL(12, 164, 31), // "changeSerialPortSettingsRequest"
QT_MOC_LITERAL(13, 196, 19), // "SerialPortSettings*"
QT_MOC_LITERAL(14, 216, 12), // "portSettings"
QT_MOC_LITERAL(15, 229, 15), // "commandTimedOut"
QT_MOC_LITERAL(16, 245, 23), // "QList<SerialCommandArg>"
QT_MOC_LITERAL(17, 269, 4), // "args"
QT_MOC_LITERAL(18, 274, 4), // "port"
QT_MOC_LITERAL(19, 279, 28), // "changeSerialPortSettingsDone"
QT_MOC_LITERAL(20, 308, 28), // "removeLastCommandSentRequest"
QT_MOC_LITERAL(21, 337, 31), // "removeFirstCommandToSendRequest"
QT_MOC_LITERAL(22, 369, 24), // "handleCommandReadyToSend"
QT_MOC_LITERAL(23, 394, 27), // "handleFoundMatchingResponse"
QT_MOC_LITERAL(24, 422, 14), // "handleResponse"
QT_MOC_LITERAL(25, 437, 4), // "data"
QT_MOC_LITERAL(26, 442, 24), // "handlePullCommandTimeout"
QT_MOC_LITERAL(27, 467, 29), // "handleSmartMatchingModeChange"
QT_MOC_LITERAL(28, 497, 11), // "isBypassing"
QT_MOC_LITERAL(29, 509, 24) // "handleSendCommandRequest"

    },
    "QSmartSerialPort\0sendCommandRequested\0"
    "\0SerialCommand\0command\0matchingResponseReceived\0"
    "response\0messageReceived\0message\0"
    "translation\0smartMatchingModeChanged\0"
    "devMode\0changeSerialPortSettingsRequest\0"
    "SerialPortSettings*\0portSettings\0"
    "commandTimedOut\0QList<SerialCommandArg>\0"
    "args\0port\0changeSerialPortSettingsDone\0"
    "removeLastCommandSentRequest\0"
    "removeFirstCommandToSendRequest\0"
    "handleCommandReadyToSend\0"
    "handleFoundMatchingResponse\0handleResponse\0"
    "data\0handlePullCommandTimeout\0"
    "handleSmartMatchingModeChange\0isBypassing\0"
    "handleSendCommandRequest"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QSmartSerialPort[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   89,    2, 0x06 /* Public */,
       5,    2,   92,    2, 0x06 /* Public */,
       7,    2,   97,    2, 0x06 /* Public */,
      10,    1,  102,    2, 0x06 /* Public */,
      12,    1,  105,    2, 0x06 /* Public */,
      15,    3,  108,    2, 0x06 /* Public */,
      19,    0,  115,    2, 0x06 /* Public */,
      20,    0,  116,    2, 0x06 /* Public */,
      21,    0,  117,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      22,    1,  118,    2, 0x08 /* Private */,
      23,    2,  121,    2, 0x08 /* Private */,
      24,    1,  126,    2, 0x08 /* Private */,
      26,    0,  129,    2, 0x08 /* Private */,
      27,    1,  130,    2, 0x08 /* Private */,
      29,    1,  133,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::QByteArray, 0x80000000 | 3,    6,    4,
    QMetaType::Void, QMetaType::QByteArray, QMetaType::QString,    8,    9,
    QMetaType::Void, QMetaType::Bool,   11,
    QMetaType::Void, 0x80000000 | 13,   14,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 16, QMetaType::Int,    4,   17,   18,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::QByteArray, 0x80000000 | 3,    6,    4,
    QMetaType::Void, QMetaType::QByteArray,   25,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   28,
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void QSmartSerialPort::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QSmartSerialPort *_t = static_cast<QSmartSerialPort *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendCommandRequested((*reinterpret_cast< const SerialCommand(*)>(_a[1]))); break;
        case 1: _t->matchingResponseReceived((*reinterpret_cast< const QByteArray(*)>(_a[1])),(*reinterpret_cast< const SerialCommand(*)>(_a[2]))); break;
        case 2: _t->messageReceived((*reinterpret_cast< const QByteArray(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 3: _t->smartMatchingModeChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->changeSerialPortSettingsRequest((*reinterpret_cast< SerialPortSettings*(*)>(_a[1]))); break;
        case 5: _t->commandTimedOut((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QList<SerialCommandArg>(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 6: _t->changeSerialPortSettingsDone(); break;
        case 7: _t->removeLastCommandSentRequest(); break;
        case 8: _t->removeFirstCommandToSendRequest(); break;
        case 9: _t->handleCommandReadyToSend((*reinterpret_cast< const SerialCommand(*)>(_a[1]))); break;
        case 10: _t->handleFoundMatchingResponse((*reinterpret_cast< const QByteArray(*)>(_a[1])),(*reinterpret_cast< const SerialCommand(*)>(_a[2]))); break;
        case 11: _t->handleResponse((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 12: _t->handlePullCommandTimeout(); break;
        case 13: _t->handleSmartMatchingModeChange((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 14: _t->handleSendCommandRequest((*reinterpret_cast< const SerialCommand(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (QSmartSerialPort::*_t)(const SerialCommand & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QSmartSerialPort::sendCommandRequested)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (QSmartSerialPort::*_t)(const QByteArray & , const SerialCommand & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QSmartSerialPort::matchingResponseReceived)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (QSmartSerialPort::*_t)(const QByteArray & , const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QSmartSerialPort::messageReceived)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (QSmartSerialPort::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QSmartSerialPort::smartMatchingModeChanged)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (QSmartSerialPort::*_t)(SerialPortSettings * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QSmartSerialPort::changeSerialPortSettingsRequest)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (QSmartSerialPort::*_t)(QString , QList<SerialCommandArg> , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QSmartSerialPort::commandTimedOut)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (QSmartSerialPort::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QSmartSerialPort::changeSerialPortSettingsDone)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (QSmartSerialPort::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QSmartSerialPort::removeLastCommandSentRequest)) {
                *result = 7;
                return;
            }
        }
        {
            typedef void (QSmartSerialPort::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QSmartSerialPort::removeFirstCommandToSendRequest)) {
                *result = 8;
                return;
            }
        }
    }
}

const QMetaObject QSmartSerialPort::staticMetaObject = {
    { &QAsyncSerialPort::staticMetaObject, qt_meta_stringdata_QSmartSerialPort.data,
      qt_meta_data_QSmartSerialPort,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *QSmartSerialPort::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QSmartSerialPort::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QSmartSerialPort.stringdata0))
        return static_cast<void*>(const_cast< QSmartSerialPort*>(this));
    return QAsyncSerialPort::qt_metacast(_clname);
}

int QSmartSerialPort::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAsyncSerialPort::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void QSmartSerialPort::sendCommandRequested(const SerialCommand & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QSmartSerialPort::matchingResponseReceived(const QByteArray & _t1, const SerialCommand & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QSmartSerialPort::messageReceived(const QByteArray & _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QSmartSerialPort::smartMatchingModeChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void QSmartSerialPort::changeSerialPortSettingsRequest(SerialPortSettings * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void QSmartSerialPort::commandTimedOut(QString _t1, QList<SerialCommandArg> _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void QSmartSerialPort::changeSerialPortSettingsDone()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void QSmartSerialPort::removeLastCommandSentRequest()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void QSmartSerialPort::removeFirstCommandToSendRequest()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
