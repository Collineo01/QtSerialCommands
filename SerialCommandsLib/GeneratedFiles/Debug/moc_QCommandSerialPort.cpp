/****************************************************************************
** Meta object code from reading C++ file 'QCommandSerialPort.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../QCommandSerialPort.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QCommandSerialPort.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QCommandSerialPort_t {
    QByteArrayData data[41];
    char stringdata0[752];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QCommandSerialPort_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QCommandSerialPort_t qt_meta_stringdata_QCommandSerialPort = {
    {
QT_MOC_LITERAL(0, 0, 18), // "QCommandSerialPort"
QT_MOC_LITERAL(1, 19, 31), // "responseMatchingCommandReceived"
QT_MOC_LITERAL(2, 51, 0), // ""
QT_MOC_LITERAL(3, 52, 8), // "response"
QT_MOC_LITERAL(4, 61, 13), // "SerialCommand"
QT_MOC_LITERAL(5, 75, 7), // "command"
QT_MOC_LITERAL(6, 83, 15), // "messageReceived"
QT_MOC_LITERAL(7, 99, 7), // "message"
QT_MOC_LITERAL(8, 107, 23), // "developmentModeSwitched"
QT_MOC_LITERAL(9, 131, 7), // "devMode"
QT_MOC_LITERAL(10, 139, 18), // "sendBufferTooLarge"
QT_MOC_LITERAL(11, 158, 23), // "responsesBufferTooLarge"
QT_MOC_LITERAL(12, 182, 17), // "disconnectRequest"
QT_MOC_LITERAL(13, 200, 14), // "disconnectDone"
QT_MOC_LITERAL(14, 215, 24), // "blockingResponseReceived"
QT_MOC_LITERAL(15, 240, 27), // "changeSerialSettingsRequest"
QT_MOC_LITERAL(16, 268, 15), // "SerialSettings*"
QT_MOC_LITERAL(17, 284, 12), // "portSettings"
QT_MOC_LITERAL(18, 297, 24), // "changeSerialSettingsDone"
QT_MOC_LITERAL(19, 322, 15), // "commandTimedOut"
QT_MOC_LITERAL(20, 338, 4), // "args"
QT_MOC_LITERAL(21, 343, 4), // "port"
QT_MOC_LITERAL(22, 348, 19), // "clearBuffersRequest"
QT_MOC_LITERAL(23, 368, 28), // "removeLastCommandSentRequest"
QT_MOC_LITERAL(24, 397, 31), // "removeFirstCommandToSendRequest"
QT_MOC_LITERAL(25, 429, 18), // "sendCommandRequest"
QT_MOC_LITERAL(26, 448, 13), // "writeToBuffer"
QT_MOC_LITERAL(27, 462, 19), // "sendBlockingCommand"
QT_MOC_LITERAL(28, 482, 6), // "params"
QT_MOC_LITERAL(29, 489, 17), // "manageMessageSent"
QT_MOC_LITERAL(30, 507, 9), // "closePort"
QT_MOC_LITERAL(31, 517, 14), // "handleResponse"
QT_MOC_LITERAL(32, 532, 4), // "data"
QT_MOC_LITERAL(33, 537, 24), // "handlePullCommandTimeout"
QT_MOC_LITERAL(34, 562, 21), // "handleDevelopmentMode"
QT_MOC_LITERAL(35, 584, 23), // "handleDisconnectRequest"
QT_MOC_LITERAL(36, 608, 33), // "handleChangeSerialSettingsReq..."
QT_MOC_LITERAL(37, 642, 25), // "handleClearBuffersRequest"
QT_MOC_LITERAL(38, 668, 27), // "handleRemoveLastCommandSent"
QT_MOC_LITERAL(39, 696, 30), // "handleRemoveFirstCommandToSend"
QT_MOC_LITERAL(40, 727, 24) // "handleSendCommandRequest"

    },
    "QCommandSerialPort\0responseMatchingCommandReceived\0"
    "\0response\0SerialCommand\0command\0"
    "messageReceived\0message\0developmentModeSwitched\0"
    "devMode\0sendBufferTooLarge\0"
    "responsesBufferTooLarge\0disconnectRequest\0"
    "disconnectDone\0blockingResponseReceived\0"
    "changeSerialSettingsRequest\0SerialSettings*\0"
    "portSettings\0changeSerialSettingsDone\0"
    "commandTimedOut\0args\0port\0clearBuffersRequest\0"
    "removeLastCommandSentRequest\0"
    "removeFirstCommandToSendRequest\0"
    "sendCommandRequest\0writeToBuffer\0"
    "sendBlockingCommand\0params\0manageMessageSent\0"
    "closePort\0handleResponse\0data\0"
    "handlePullCommandTimeout\0handleDevelopmentMode\0"
    "handleDisconnectRequest\0"
    "handleChangeSerialSettingsRequest\0"
    "handleClearBuffersRequest\0"
    "handleRemoveLastCommandSent\0"
    "handleRemoveFirstCommandToSend\0"
    "handleSendCommandRequest"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QCommandSerialPort[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      28,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      15,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,  154,    2, 0x06 /* Public */,
       6,    1,  159,    2, 0x06 /* Public */,
       8,    1,  162,    2, 0x06 /* Public */,
      10,    0,  165,    2, 0x06 /* Public */,
      11,    0,  166,    2, 0x06 /* Public */,
      12,    0,  167,    2, 0x06 /* Public */,
      13,    0,  168,    2, 0x06 /* Public */,
      14,    0,  169,    2, 0x06 /* Public */,
      15,    1,  170,    2, 0x06 /* Public */,
      18,    0,  173,    2, 0x06 /* Public */,
      19,    3,  174,    2, 0x06 /* Public */,
      22,    0,  181,    2, 0x06 /* Public */,
      23,    0,  182,    2, 0x06 /* Public */,
      24,    0,  183,    2, 0x06 /* Public */,
      25,    1,  184,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      26,    1,  187,    2, 0x0a /* Public */,
      27,    2,  190,    2, 0x0a /* Public */,
      29,    0,  195,    2, 0x0a /* Public */,
      30,    0,  196,    2, 0x0a /* Public */,
      31,    1,  197,    2, 0x08 /* Private */,
      33,    0,  200,    2, 0x08 /* Private */,
      34,    1,  201,    2, 0x08 /* Private */,
      35,    0,  204,    2, 0x08 /* Private */,
      36,    1,  205,    2, 0x08 /* Private */,
      37,    0,  208,    2, 0x08 /* Private */,
      38,    0,  209,    2, 0x08 /* Private */,
      39,    0,  210,    2, 0x08 /* Private */,
      40,    1,  211,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QByteArray, 0x80000000 | 4,    3,    5,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::Bool,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QVariantList, QMetaType::Int,    5,   20,   21,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::QByteArray, 0x80000000 | 4, QMetaType::QVariantList,    5,   28,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,   32,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    9,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,

       0        // eod
};

void QCommandSerialPort::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QCommandSerialPort *_t = static_cast<QCommandSerialPort *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->responseMatchingCommandReceived((*reinterpret_cast< const QByteArray(*)>(_a[1])),(*reinterpret_cast< const SerialCommand(*)>(_a[2]))); break;
        case 1: _t->messageReceived((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->developmentModeSwitched((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->sendBufferTooLarge(); break;
        case 4: _t->responsesBufferTooLarge(); break;
        case 5: _t->disconnectRequest(); break;
        case 6: _t->disconnectDone(); break;
        case 7: _t->blockingResponseReceived(); break;
        case 8: _t->changeSerialSettingsRequest((*reinterpret_cast< SerialSettings*(*)>(_a[1]))); break;
        case 9: _t->changeSerialSettingsDone(); break;
        case 10: _t->commandTimedOut((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QList<QVariant>(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 11: _t->clearBuffersRequest(); break;
        case 12: _t->removeLastCommandSentRequest(); break;
        case 13: _t->removeFirstCommandToSendRequest(); break;
        case 14: _t->sendCommandRequest((*reinterpret_cast< SerialCommand(*)>(_a[1]))); break;
        case 15: _t->writeToBuffer((*reinterpret_cast< const SerialCommand(*)>(_a[1]))); break;
        case 16: { QByteArray _r = _t->sendBlockingCommand((*reinterpret_cast< SerialCommand(*)>(_a[1])),(*reinterpret_cast< QList<QVariant>(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QByteArray*>(_a[0]) = std::move(_r); }  break;
        case 17: _t->manageMessageSent(); break;
        case 18: _t->closePort(); break;
        case 19: _t->handleResponse((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 20: _t->handlePullCommandTimeout(); break;
        case 21: _t->handleDevelopmentMode((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 22: _t->handleDisconnectRequest(); break;
        case 23: _t->handleChangeSerialSettingsRequest((*reinterpret_cast< SerialSettings*(*)>(_a[1]))); break;
        case 24: _t->handleClearBuffersRequest(); break;
        case 25: _t->handleRemoveLastCommandSent(); break;
        case 26: _t->handleRemoveFirstCommandToSend(); break;
        case 27: _t->handleSendCommandRequest((*reinterpret_cast< SerialCommand(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (QCommandSerialPort::*_t)(QByteArray const & , SerialCommand const & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QCommandSerialPort::responseMatchingCommandReceived)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (QCommandSerialPort::*_t)(QString const & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QCommandSerialPort::messageReceived)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (QCommandSerialPort::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QCommandSerialPort::developmentModeSwitched)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (QCommandSerialPort::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QCommandSerialPort::sendBufferTooLarge)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (QCommandSerialPort::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QCommandSerialPort::responsesBufferTooLarge)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (QCommandSerialPort::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QCommandSerialPort::disconnectRequest)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (QCommandSerialPort::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QCommandSerialPort::disconnectDone)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (QCommandSerialPort::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QCommandSerialPort::blockingResponseReceived)) {
                *result = 7;
                return;
            }
        }
        {
            typedef void (QCommandSerialPort::*_t)(SerialSettings * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QCommandSerialPort::changeSerialSettingsRequest)) {
                *result = 8;
                return;
            }
        }
        {
            typedef void (QCommandSerialPort::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QCommandSerialPort::changeSerialSettingsDone)) {
                *result = 9;
                return;
            }
        }
        {
            typedef void (QCommandSerialPort::*_t)(QString , QList<QVariant> , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QCommandSerialPort::commandTimedOut)) {
                *result = 10;
                return;
            }
        }
        {
            typedef void (QCommandSerialPort::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QCommandSerialPort::clearBuffersRequest)) {
                *result = 11;
                return;
            }
        }
        {
            typedef void (QCommandSerialPort::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QCommandSerialPort::removeLastCommandSentRequest)) {
                *result = 12;
                return;
            }
        }
        {
            typedef void (QCommandSerialPort::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QCommandSerialPort::removeFirstCommandToSendRequest)) {
                *result = 13;
                return;
            }
        }
        {
            typedef void (QCommandSerialPort::*_t)(SerialCommand );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QCommandSerialPort::sendCommandRequest)) {
                *result = 14;
                return;
            }
        }
    }
}

const QMetaObject QCommandSerialPort::staticMetaObject = {
    { &QAsyncSerialPort::staticMetaObject, qt_meta_stringdata_QCommandSerialPort.data,
      qt_meta_data_QCommandSerialPort,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *QCommandSerialPort::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCommandSerialPort::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QCommandSerialPort.stringdata0))
        return static_cast<void*>(const_cast< QCommandSerialPort*>(this));
    return QAsyncSerialPort::qt_metacast(_clname);
}

int QCommandSerialPort::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAsyncSerialPort::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 28)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 28;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 28)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 28;
    }
    return _id;
}

// SIGNAL 0
void QCommandSerialPort::responseMatchingCommandReceived(QByteArray const & _t1, SerialCommand const & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QCommandSerialPort::messageReceived(QString const & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QCommandSerialPort::developmentModeSwitched(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QCommandSerialPort::sendBufferTooLarge()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void QCommandSerialPort::responsesBufferTooLarge()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void QCommandSerialPort::disconnectRequest()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void QCommandSerialPort::disconnectDone()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void QCommandSerialPort::blockingResponseReceived()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void QCommandSerialPort::changeSerialSettingsRequest(SerialSettings * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void QCommandSerialPort::changeSerialSettingsDone()
{
    QMetaObject::activate(this, &staticMetaObject, 9, nullptr);
}

// SIGNAL 10
void QCommandSerialPort::commandTimedOut(QString _t1, QList<QVariant> _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void QCommandSerialPort::clearBuffersRequest()
{
    QMetaObject::activate(this, &staticMetaObject, 11, nullptr);
}

// SIGNAL 12
void QCommandSerialPort::removeLastCommandSentRequest()
{
    QMetaObject::activate(this, &staticMetaObject, 12, nullptr);
}

// SIGNAL 13
void QCommandSerialPort::removeFirstCommandToSendRequest()
{
    QMetaObject::activate(this, &staticMetaObject, 13, nullptr);
}

// SIGNAL 14
void QCommandSerialPort::sendCommandRequest(SerialCommand _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
