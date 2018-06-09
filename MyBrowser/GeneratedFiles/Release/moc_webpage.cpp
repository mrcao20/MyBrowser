/****************************************************************************
** Meta object code from reading C++ file 'webpage.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../webpage.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'webpage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WebPage_t {
    QByteArrayData data[11];
    char stringdata0[170];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WebPage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WebPage_t qt_meta_stringdata_WebPage = {
    {
QT_MOC_LITERAL(0, 0, 7), // "WebPage"
QT_MOC_LITERAL(1, 8, 28), // "handleAuthenticationRequired"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 10), // "requestUrl"
QT_MOC_LITERAL(4, 49, 15), // "QAuthenticator*"
QT_MOC_LITERAL(5, 65, 4), // "auth"
QT_MOC_LITERAL(6, 70, 33), // "handleProxyAuthenticationRequ..."
QT_MOC_LITERAL(7, 104, 9), // "proxyHost"
QT_MOC_LITERAL(8, 114, 19), // "fullScreenRequested"
QT_MOC_LITERAL(9, 134, 27), // "QWebEngineFullScreenRequest"
QT_MOC_LITERAL(10, 162, 7) // "request"

    },
    "WebPage\0handleAuthenticationRequired\0"
    "\0requestUrl\0QAuthenticator*\0auth\0"
    "handleProxyAuthenticationRequired\0"
    "proxyHost\0fullScreenRequested\0"
    "QWebEngineFullScreenRequest\0request"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WebPage[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   29,    2, 0x08 /* Private */,
       6,    3,   34,    2, 0x08 /* Private */,
       8,    1,   41,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QUrl, 0x80000000 | 4,    3,    5,
    QMetaType::Void, QMetaType::QUrl, 0x80000000 | 4, QMetaType::QString,    3,    5,    7,
    QMetaType::Void, 0x80000000 | 9,   10,

       0        // eod
};

void WebPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        WebPage *_t = static_cast<WebPage *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->handleAuthenticationRequired((*reinterpret_cast< const QUrl(*)>(_a[1])),(*reinterpret_cast< QAuthenticator*(*)>(_a[2]))); break;
        case 1: _t->handleProxyAuthenticationRequired((*reinterpret_cast< const QUrl(*)>(_a[1])),(*reinterpret_cast< QAuthenticator*(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 2: _t->fullScreenRequested((*reinterpret_cast< QWebEngineFullScreenRequest(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject WebPage::staticMetaObject = {
    { &QWebEnginePage::staticMetaObject, qt_meta_stringdata_WebPage.data,
      qt_meta_data_WebPage,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *WebPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WebPage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WebPage.stringdata0))
        return static_cast<void*>(this);
    return QWebEnginePage::qt_metacast(_clname);
}

int WebPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWebEnginePage::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
