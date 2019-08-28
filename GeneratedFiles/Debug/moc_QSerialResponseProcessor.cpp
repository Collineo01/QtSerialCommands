/****************************************************************************
** Meta object code from reading C++ file 'QSerialResponseProcessor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../QSerialResponseProcessor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QSerialResponseProcessor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QSerialResponseProcessor_t {
    QByteArrayData data[11];
    char stringdata0[150];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QSerialResponseProcessor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QSerialResponseProcessor_t qt_meta_stringdata_QSerialResponseProcessor = {
    {
QT_MOC_LITERAL(0, 0, 24), // "QSerialResponseProcessor"
QT_MOC_LITERAL(1, 25, 21), // "foundMatchingResponse"
QT_MOC_LITERAL(2, 47, 0), // ""
QT_MOC_LITERAL(3, 48, 8), // "response"
QT_MOC_LITERAL(4, 57, 13), // "SerialCommand"
QT_MOC_LITERAL(5, 71, 7), // "command"
QT_MOC_LITERAL(6, 79, 12), // "foundMessage"
QT_MOC_LITERAL(7, 92, 7), // "message"
QT_MOC_LITERAL(8, 100, 11), // "description"
QT_MOC_LITERAL(9, 112, 20), // "commandIsReadyToSend"
QT_MOC_LITERAL(10, 133, 16) // "processResponses"

    },
    "QSerialResponseProcessor\0foundMatchingResponse\0"
    "\0response\0SerialCommand\0command\0"
    "foundMessage\0message\0description\0"
    "commandIsReadyToSend\0processResponses"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QSerialResponseProcessor[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   34,    2, 0x06 /* Public */,
       6,    2,   39,    2, 0x06 /* Public */,
       9,    1,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    0,   47,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QByteArray, 0x80000000 | 4,    3,    5,
    QMetaType::Void, QMetaType::QByteArray, QMetaType::QString,    7,    8,
    QMetaType::Void, 0x80000000 | 4,    5,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void QSerialResponseProcessor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QSerialResponseProcessor *_t = static_cast<QSerialResponseProcessor *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->foundMatchingResponse((*reinterpret_cast< const QByteArray(*)>(_a[1])),(*reinterpret_cast< const SerialCommand(*)>(_a[2]))); break;
        case 1: _t->foundMessage((*reinterpret_cast< const QByteArray(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 2: _t->commandIsReadyToSend((*reinterpret_cast< const SerialCommand(*)>(_a[1]))); break;
        case 3: _t->processResponses(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (QSerialResponseProcessor::*_t)(const QByteArray & , const SerialCommand & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QSerialResponseProcessor::foundMatchingResponse)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (QSerialResponseProcessor::*_t)(const QByteArray & , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QSerialResponseProcessor::foundMessage)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (QSerialResponseProcessor::*_t)(const SerialCommand & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QSerialResponseProcessor::commandIsReadyToSend)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject QSerialResponseProcessor::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QSerialResponseProcessor.data,
      qt_meta_data_QSerialResponseProcessor,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *QSerialResponseProcessor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QSerialResponseProcessor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QSerialResponseProcessor.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int QSerialResponseProcessor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void QSerialResponseProcessor::foundMatchingResponse(const QByteArray & _t1, const SerialCommand & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QSerialResponseProcessor::foundMessage(const QByteArray & _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QSerialResponseProcessor::commandIsReadyToSend(const SerialCommand & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
