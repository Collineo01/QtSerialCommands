/****************************************************************************
** Meta object code from reading C++ file 'QSerialBuffer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../QSerialBuffer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QSerialBuffer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QSerialBuffer_t {
    QByteArrayData data[10];
    char stringdata0[137];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QSerialBuffer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QSerialBuffer_t qt_meta_stringdata_QSerialBuffer = {
    {
QT_MOC_LITERAL(0, 0, 13), // "QSerialBuffer"
QT_MOC_LITERAL(1, 14, 22), // "nextCommandReadyToSend"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 19), // "commandBufferFilled"
QT_MOC_LITERAL(4, 58, 20), // "responseBufferFilled"
QT_MOC_LITERAL(5, 79, 12), // "writeCommand"
QT_MOC_LITERAL(6, 92, 13), // "SerialCommand"
QT_MOC_LITERAL(7, 106, 7), // "command"
QT_MOC_LITERAL(8, 114, 13), // "writeResponse"
QT_MOC_LITERAL(9, 128, 8) // "response"

    },
    "QSerialBuffer\0nextCommandReadyToSend\0"
    "\0commandBufferFilled\0responseBufferFilled\0"
    "writeCommand\0SerialCommand\0command\0"
    "writeResponse\0response"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QSerialBuffer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,
       3,    0,   40,    2, 0x06 /* Public */,
       4,    0,   41,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   42,    2, 0x0a /* Public */,
       8,    1,   45,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, QMetaType::QByteArray,    9,

       0        // eod
};

void QSerialBuffer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QSerialBuffer *_t = static_cast<QSerialBuffer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->nextCommandReadyToSend(); break;
        case 1: _t->commandBufferFilled(); break;
        case 2: _t->responseBufferFilled(); break;
        case 3: _t->writeCommand((*reinterpret_cast< SerialCommand(*)>(_a[1]))); break;
        case 4: _t->writeResponse((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (QSerialBuffer::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QSerialBuffer::nextCommandReadyToSend)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (QSerialBuffer::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QSerialBuffer::commandBufferFilled)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (QSerialBuffer::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QSerialBuffer::responseBufferFilled)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject QSerialBuffer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QSerialBuffer.data,
      qt_meta_data_QSerialBuffer,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *QSerialBuffer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QSerialBuffer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QSerialBuffer.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int QSerialBuffer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void QSerialBuffer::nextCommandReadyToSend()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void QSerialBuffer::commandBufferFilled()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void QSerialBuffer::responseBufferFilled()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
