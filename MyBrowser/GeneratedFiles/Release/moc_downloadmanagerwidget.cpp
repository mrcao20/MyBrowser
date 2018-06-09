/****************************************************************************
** Meta object code from reading C++ file 'downloadmanagerwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../downloadmanagerwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'downloadmanagerwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DownloadManagerWidget_t {
    QByteArrayData data[5];
    char stringdata0[73];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DownloadManagerWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DownloadManagerWidget_t qt_meta_stringdata_DownloadManagerWidget = {
    {
QT_MOC_LITERAL(0, 0, 21), // "DownloadManagerWidget"
QT_MOC_LITERAL(1, 22, 17), // "downloadRequested"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 23), // "QWebEngineDownloadItem*"
QT_MOC_LITERAL(4, 65, 7) // "webItem"

    },
    "DownloadManagerWidget\0downloadRequested\0"
    "\0QWebEngineDownloadItem*\0webItem"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DownloadManagerWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void DownloadManagerWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DownloadManagerWidget *_t = static_cast<DownloadManagerWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->downloadRequested((*reinterpret_cast< QWebEngineDownloadItem*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject DownloadManagerWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_DownloadManagerWidget.data,
      qt_meta_data_DownloadManagerWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *DownloadManagerWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DownloadManagerWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DownloadManagerWidget.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "Ui::DownloadManagerWidget"))
        return static_cast< Ui::DownloadManagerWidget*>(this);
    return QWidget::qt_metacast(_clname);
}

int DownloadManagerWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
