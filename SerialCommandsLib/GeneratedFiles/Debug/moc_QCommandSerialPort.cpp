/****************************************************************************
** Meta object code from reading C++ file 'QCommandSerialPort.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
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
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QCommandSerialPort_t {
    QByteArrayData data[31];
    char stringdata0[558];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QCommandSerialPort_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QCommandSerialPort_t qt_meta_stringdata_QCommandSerialPort = {
    {
QT_MOC_LITERAL(0, 0, 18), // "QCommandSerialPort"
QT_MOC_LITERAL(1, 19, 22), // "responseMatchesCommand"
QT_MOC_LITERAL(2, 42, 0), // ""
QT_MOC_LITERAL(3, 43, 8), // "response"
QT_MOC_LITERAL(4, 52, 13), // "SerialCommand"
QT_MOC_LITERAL(5, 66, 7), // "command"
QT_MOC_LITERAL(6, 74, 15), // "messageReceived"
QT_MOC_LITERAL(7, 90, 7), // "message"
QT_MOC_LITERAL(8, 98, 23), // "developmentModeSwitched"
QT_MOC_LITERAL(9, 122, 7), // "devMode"
QT_MOC_LITERAL(10, 130, 18), // "sendBufferTooLarge"
QT_MOC_LITERAL(11, 149, 23), // "responsesBufferTooLarge"
QT_MOC_LITERAL(12, 173, 17), // "disconnectRequest"
QT_MOC_LITERAL(13, 191, 14), // "disconnectDone"
QT_MOC_LITERAL(14, 206, 24), // "blockingResponseReceived"
QT_MOC_LITERAL(15, 231, 27), // "changeSerialSettingsRequest"
QT_MOC_LITERAL(16, 259, 15), // "SerialSettings*"
QT_MOC_LITERAL(17, 275, 12), // "portSettings"
QT_MOC_LITERAL(18, 288, 24), // "changeSerialSettingsDone"
QT_MOC_LITERAL(19, 313, 13), // "writeToBuffer"
QT_MOC_LITERAL(20, 327, 44), // "QPair<const SerialCommand&,QL..."
QT_MOC_LITERAL(21, 372, 19), // "sendBlockingCommand"
QT_MOC_LITERAL(22, 392, 6), // "params"
QT_MOC_LITERAL(23, 399, 17), // "manageMessageSent"
QT_MOC_LITERAL(24, 417, 15), // "closeSerialPort"
QT_MOC_LITERAL(25, 433, 14), // "handleResponse"
QT_MOC_LITERAL(26, 448, 4), // "data"
QT_MOC_LITERAL(27, 453, 24), // "handlePullCommandTimeout"
QT_MOC_LITERAL(28, 478, 21), // "handleDevelopmentMode"
QT_MOC_LITERAL(29, 500, 23), // "handleDisconnectRequest"
QT_MOC_LITERAL(30, 524, 33) // "handleChangeSerialSettingsReq..."

    },
    "QCommandSerialPort\0responseMatchesCommand\0"
    "\0response\0SerialCommand\0command\0"
    "messageReceived\0message\0developmentModeSwitched\0"
    "devMode\0sendBufferTooLarge\0"
    "responsesBufferTooLarge\0disconnectRequest\0"
    "disconnectDone\0blockingResponseReceived\0"
    "changeSerialSettingsRequest\0SerialSettings*\0"
    "portSettings\0changeSerialSettingsDone\0"
    "writeToBuffer\0"
    "QPair<const SerialCommand&,QList<QVariant> >\0"
    "sendBlockingCommand\0params\0manageMessageSent\0"
    "closeSerialPort\0handleResponse\0data\0"
    "handlePullCommandTimeout\0handleDevelopmentMode\0"
    "handleDisconnectRequest\0"
    "handleChangeSerialSettingsRequest"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QCommandSerialPort[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      10,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,  109,    2, 0x06 /* Public */,
       6,    1,  114,    2, 0x06 /* Public */,
       8,    1,  117,    2, 0x06 /* Public */,
      10,    0,  120,    2, 0x06 /* Public */,
      11,    0,  121,    2, 0x06 /* Public */,
      12,    0,  122,    2, 0x06 /* Public */,
      13,    0,  123,    2, 0x06 /* Public */,
      14,    0,  124,    2, 0x06 /* Public */,
      15,    1,  125,    2, 0x06 /* Public */,
      18,    0,  128,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      19,    1,  129,    2, 0x0a /* Public */,
      21,    2,  132,    2, 0x0a /* Public */,
      23,    0,  137,    2, 0x0a /* Public */,
      24,    0,  138,    2, 0x0a /* Public */,
      25,    1,  139,    2, 0x08 /* Private */,
      27,    0,  142,    2, 0x08 /* Private */,
      28,    1,  143,    2, 0x08 /* Private */,
      29,    0,  146,    2, 0x08 /* Private */,
      30,    1,  147,    2, 0x08 /* Private */,

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

 // slots: parameters
    QMetaType::Void, 0x80000000 | 20,    5,
    QMetaType::QByteArray, 0x80000000 | 4, QMetaType::QVariantList,    5,   22,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,   26,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    9,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 16,   17,

       0        // eod
};

void QCommandSerialPort::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QCommandSerialPort *_t = static_cast<QCommandSerialPort *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->responseMatchesCommand((*reinterpret_cast< QByteArray(*)>(_a[1])),(*reinterpret_cast< SerialCommand(*)>(_a[2]))); break;
        case 1: _t->messageReceived((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->developmentModeSwitched((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->sendBufferTooLarge(); break;
        case 4: _t->responsesBufferTooLarge(); break;
        case 5: _t->disconnectRequest(); break;
        case 6: _t->disconnectDone(); break;
        case 7: _t->blockingResponseReceived(); break;
        case 8: _t->changeSerialSettingsRequest((*reinterpret_cast< SerialSettings*(*)>(_a[1]))); break;
        case 9: _t->changeSerialSettingsDone(); break;
        case 10: _t->writeToBuffer((*reinterpret_cast< QPair<const SerialCommand&,QList<QVariant> >(*)>(_a[1]))); break;
        case 11: { QByteArray _r = _t->sendBlockingCommand((*reinterpret_cast< SerialCommand(*)>(_a[1])),(*reinterpret_cast< QList<QVariant>(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QByteArray*>(_a[0]) = std::move(_r); }  break;
        case 12: _t->manageMessageSent(); break;
        case 13: _t->closeSerialPort(); break;
        case 14: _t->handleResponse((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 15: _t->handlePullCommandTimeout(); break;
        case 16: _t->handleDevelopmentMode((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 17: _t->handleDisconnectRequest(); break;
        case 18: _t->handleChangeSerialSettingsRequest((*reinterpret_cast< SerialSettings*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (QCommandSerialPort::*_t)(QByteArray , SerialCommand );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QCommandSerialPort::responseMatchesCommand)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (QCommandSerialPort::*_t)(QString );
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
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 19)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 19;
    }
    return _id;
}

// SIGNAL 0
void QCommandSerialPort::responseMatchesCommand(QByteArray _t1, SerialCommand _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QCommandSerialPort::messageReceived(QString _t1)
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
