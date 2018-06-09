/****************************************************************************
** Meta object code from reading C++ file 'downloaditem.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../downloaditem.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'downloaditem.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DownloadItem_t {
    QByteArrayData data[15];
    char stringdata0[182];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DownloadItem_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DownloadItem_t qt_meta_stringdata_DownloadItem = {
    {
QT_MOC_LITERAL(0, 0, 12), // "DownloadItem"
QT_MOC_LITERAL(1, 13, 16), // "downloadProgress"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 12), // "stateChanged"
QT_MOC_LITERAL(4, 44, 27), // "DownloadItem::DownloadState"
QT_MOC_LITERAL(5, 72, 6), // "accept"
QT_MOC_LITERAL(6, 79, 6), // "cancel"
QT_MOC_LITERAL(7, 86, 5), // "pause"
QT_MOC_LITERAL(8, 92, 6), // "resume"
QT_MOC_LITERAL(9, 99, 18), // "onDownloadProgress"
QT_MOC_LITERAL(10, 118, 11), // "onReadyRead"
QT_MOC_LITERAL(11, 130, 10), // "onFinished"
QT_MOC_LITERAL(12, 141, 7), // "onError"
QT_MOC_LITERAL(13, 149, 27), // "QNetworkReply::NetworkError"
QT_MOC_LITERAL(14, 177, 4) // "code"

    },
    "DownloadItem\0downloadProgress\0\0"
    "stateChanged\0DownloadItem::DownloadState\0"
    "accept\0cancel\0pause\0resume\0"
    "onDownloadProgress\0onReadyRead\0"
    "onFinished\0onError\0QNetworkReply::NetworkError\0"
    "code"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DownloadItem[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   64,    2, 0x06 /* Public */,
       3,    1,   69,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   72,    2, 0x0a /* Public */,
       6,    0,   73,    2, 0x0a /* Public */,
       7,    0,   74,    2, 0x0a /* Public */,
       8,    0,   75,    2, 0x0a /* Public */,
       9,    2,   76,    2, 0x08 /* Private */,
      10,    0,   81,    2, 0x08 /* Private */,
      11,    0,   82,    2, 0x08 /* Private */,
      12,    1,   83,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong,    2,    2,
    QMetaType::Void, 0x80000000 | 4,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong,    2,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 13,   14,

       0        // eod
};

void DownloadItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DownloadItem *_t = static_cast<DownloadItem *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->downloadProgress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 1: _t->stateChanged((*reinterpret_cast< DownloadItem::DownloadState(*)>(_a[1]))); break;
        case 2: _t->accept(); break;
        case 3: _t->cancel(); break;
        case 4: _t->pause(); break;
        case 5: _t->resume(); break;
        case 6: _t->onDownloadProgress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 7: _t->onReadyRead(); break;
        case 8: _t->onFinished(); break;
        case 9: _t->onError((*reinterpret_cast< QNetworkReply::NetworkError(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply::NetworkError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (DownloadItem::*_t)(qint64 , qint64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DownloadItem::downloadProgress)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (DownloadItem::*_t)(DownloadItem::DownloadState );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DownloadItem::stateChanged)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject DownloadItem::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_DownloadItem.data,
      qt_meta_data_DownloadItem,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *DownloadItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DownloadItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DownloadItem.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int DownloadItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void DownloadItem::downloadProgress(qint64 _t1, qint64 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DownloadItem::stateChanged(DownloadItem::DownloadState _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
