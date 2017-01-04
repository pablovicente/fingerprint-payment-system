/****************************************************************************
** Meta object code from reading C++ file 'processfingerprint.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "processfingerprint.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'processfingerprint.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ProcessFingerprint_t {
    QByteArrayData data[7];
    char stringdata[150];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ProcessFingerprint_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ProcessFingerprint_t qt_meta_stringdata_ProcessFingerprint = {
    {
QT_MOC_LITERAL(0, 0, 18), // "ProcessFingerprint"
QT_MOC_LITERAL(1, 19, 26), // "finishedProcessFingerprint"
QT_MOC_LITERAL(2, 46, 0), // ""
QT_MOC_LITERAL(3, 47, 31), // "progressValueProcessFingerprint"
QT_MOC_LITERAL(4, 79, 7), // "message"
QT_MOC_LITERAL(5, 87, 29), // "finishedFingerprintComparison"
QT_MOC_LITERAL(6, 117, 32) // "progressValueCompareFingerprints"

    },
    "ProcessFingerprint\0finishedProcessFingerprint\0"
    "\0progressValueProcessFingerprint\0"
    "message\0finishedFingerprintComparison\0"
    "progressValueCompareFingerprints"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ProcessFingerprint[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,
       3,    1,   35,    2, 0x06 /* Public */,
       5,    0,   38,    2, 0x06 /* Public */,
       6,    1,   39,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,

       0        // eod
};

void ProcessFingerprint::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ProcessFingerprint *_t = static_cast<ProcessFingerprint *>(_o);
        switch (_id) {
        case 0: _t->finishedProcessFingerprint(); break;
        case 1: _t->progressValueProcessFingerprint((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->finishedFingerprintComparison(); break;
        case 3: _t->progressValueCompareFingerprints((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ProcessFingerprint::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ProcessFingerprint::finishedProcessFingerprint)) {
                *result = 0;
            }
        }
        {
            typedef void (ProcessFingerprint::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ProcessFingerprint::progressValueProcessFingerprint)) {
                *result = 1;
            }
        }
        {
            typedef void (ProcessFingerprint::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ProcessFingerprint::finishedFingerprintComparison)) {
                *result = 2;
            }
        }
        {
            typedef void (ProcessFingerprint::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ProcessFingerprint::progressValueCompareFingerprints)) {
                *result = 3;
            }
        }
    }
}

const QMetaObject ProcessFingerprint::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ProcessFingerprint.data,
      qt_meta_data_ProcessFingerprint,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ProcessFingerprint::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ProcessFingerprint::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ProcessFingerprint.stringdata))
        return static_cast<void*>(const_cast< ProcessFingerprint*>(this));
    return QObject::qt_metacast(_clname);
}

int ProcessFingerprint::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void ProcessFingerprint::finishedProcessFingerprint()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void ProcessFingerprint::progressValueProcessFingerprint(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ProcessFingerprint::finishedFingerprintComparison()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void ProcessFingerprint::progressValueCompareFingerprints(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
