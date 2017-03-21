/****************************************************************************
** Meta object code from reading C++ file 'plc_editor_dialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../PLC/plc_editor_dialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'plc_editor_dialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_NocDialog_t {
    QByteArrayData data[16];
    char stringdata[218];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_NocDialog_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_NocDialog_t qt_meta_stringdata_NocDialog = {
    {
QT_MOC_LITERAL(0, 0, 9),
QT_MOC_LITERAL(1, 10, 20),
QT_MOC_LITERAL(2, 31, 0),
QT_MOC_LITERAL(3, 32, 5),
QT_MOC_LITERAL(4, 38, 20),
QT_MOC_LITERAL(5, 59, 22),
QT_MOC_LITERAL(6, 82, 21),
QT_MOC_LITERAL(7, 104, 18),
QT_MOC_LITERAL(8, 123, 15),
QT_MOC_LITERAL(9, 139, 8),
QT_MOC_LITERAL(10, 148, 6),
QT_MOC_LITERAL(11, 155, 16),
QT_MOC_LITERAL(12, 172, 12),
QT_MOC_LITERAL(13, 185, 15),
QT_MOC_LITERAL(14, 201, 5),
QT_MOC_LITERAL(15, 207, 9)
    },
    "NocDialog\0KeyPgUpPressedSignal\0\0bPgUp\0"
    "KeyPgDnPressedSignal\0KeyEscapePressedSignal\0"
    "KeyEnterPressedSignal\0KeyF1PressedSignal\0"
    "NocDialogResult\0QString&\0F1Slot\0"
    "CancelButtonSolt\0OkButtonSlot\0"
    "EstyleLabelSlot\0iPgUp\0M_Explain\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NocDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x06,
       1,    0,   82,    2, 0x26,
       4,    1,   83,    2, 0x06,
       4,    0,   86,    2, 0x26,
       5,    0,   87,    2, 0x06,
       6,    0,   88,    2, 0x06,
       7,    0,   89,    2, 0x06,
       8,    2,   90,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
      10,    0,   95,    2, 0x08,
      11,    0,   96,    2, 0x08,
      12,    0,   97,    2, 0x08,
      13,    1,   98,    2, 0x08,
      15,    0,  101,    2, 0x08,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9, QMetaType::Int,    2,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   14,
    QMetaType::Void,

       0        // eod
};

void NocDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        NocDialog *_t = static_cast<NocDialog *>(_o);
        switch (_id) {
        case 0: _t->KeyPgUpPressedSignal((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->KeyPgUpPressedSignal(); break;
        case 2: _t->KeyPgDnPressedSignal((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->KeyPgDnPressedSignal(); break;
        case 4: _t->KeyEscapePressedSignal(); break;
        case 5: _t->KeyEnterPressedSignal(); break;
        case 6: _t->KeyF1PressedSignal(); break;
        case 7: _t->NocDialogResult((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 8: _t->F1Slot(); break;
        case 9: _t->CancelButtonSolt(); break;
        case 10: _t->OkButtonSlot(); break;
        case 11: _t->EstyleLabelSlot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: _t->M_Explain(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (NocDialog::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NocDialog::KeyPgUpPressedSignal)) {
                *result = 0;
            }
        }
        {
            typedef void (NocDialog::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NocDialog::KeyPgDnPressedSignal)) {
                *result = 2;
            }
        }
        {
            typedef void (NocDialog::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NocDialog::KeyEscapePressedSignal)) {
                *result = 4;
            }
        }
        {
            typedef void (NocDialog::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NocDialog::KeyEnterPressedSignal)) {
                *result = 5;
            }
        }
        {
            typedef void (NocDialog::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NocDialog::KeyF1PressedSignal)) {
                *result = 6;
            }
        }
        {
            typedef void (NocDialog::*_t)(QString & , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NocDialog::NocDialogResult)) {
                *result = 7;
            }
        }
    }
}

const QMetaObject NocDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_NocDialog.data,
      qt_meta_data_NocDialog,  qt_static_metacall, 0, 0}
};


const QMetaObject *NocDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NocDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_NocDialog.stringdata))
        return static_cast<void*>(const_cast< NocDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int NocDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
void NocDialog::KeyPgUpPressedSignal(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 2
void NocDialog::KeyPgDnPressedSignal(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 4
void NocDialog::KeyEscapePressedSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void NocDialog::KeyEnterPressedSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void NocDialog::KeyF1PressedSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}

// SIGNAL 7
void NocDialog::NocDialogResult(QString & _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
struct qt_meta_stringdata_NccDialog_t {
    QByteArrayData data[16];
    char stringdata[218];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_NccDialog_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_NccDialog_t qt_meta_stringdata_NccDialog = {
    {
QT_MOC_LITERAL(0, 0, 9),
QT_MOC_LITERAL(1, 10, 20),
QT_MOC_LITERAL(2, 31, 0),
QT_MOC_LITERAL(3, 32, 5),
QT_MOC_LITERAL(4, 38, 20),
QT_MOC_LITERAL(5, 59, 22),
QT_MOC_LITERAL(6, 82, 21),
QT_MOC_LITERAL(7, 104, 18),
QT_MOC_LITERAL(8, 123, 15),
QT_MOC_LITERAL(9, 139, 8),
QT_MOC_LITERAL(10, 148, 6),
QT_MOC_LITERAL(11, 155, 16),
QT_MOC_LITERAL(12, 172, 12),
QT_MOC_LITERAL(13, 185, 15),
QT_MOC_LITERAL(14, 201, 5),
QT_MOC_LITERAL(15, 207, 9)
    },
    "NccDialog\0KeyPgUpPressedSignal\0\0bPgUp\0"
    "KeyPgDnPressedSignal\0KeyEscapePressedSignal\0"
    "KeyEnterPressedSignal\0KeyF1PressedSignal\0"
    "NccDialogResult\0QString&\0F1Slot\0"
    "CancelButtonSolt\0OkButtonSlot\0"
    "EstyleLabelSlot\0iPgUp\0M_Explain\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NccDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x06,
       1,    0,   82,    2, 0x26,
       4,    1,   83,    2, 0x06,
       4,    0,   86,    2, 0x26,
       5,    0,   87,    2, 0x06,
       6,    0,   88,    2, 0x06,
       7,    0,   89,    2, 0x06,
       8,    2,   90,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
      10,    0,   95,    2, 0x08,
      11,    0,   96,    2, 0x08,
      12,    0,   97,    2, 0x08,
      13,    1,   98,    2, 0x08,
      15,    0,  101,    2, 0x08,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9, QMetaType::Int,    2,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   14,
    QMetaType::Void,

       0        // eod
};

void NccDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        NccDialog *_t = static_cast<NccDialog *>(_o);
        switch (_id) {
        case 0: _t->KeyPgUpPressedSignal((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->KeyPgUpPressedSignal(); break;
        case 2: _t->KeyPgDnPressedSignal((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->KeyPgDnPressedSignal(); break;
        case 4: _t->KeyEscapePressedSignal(); break;
        case 5: _t->KeyEnterPressedSignal(); break;
        case 6: _t->KeyF1PressedSignal(); break;
        case 7: _t->NccDialogResult((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 8: _t->F1Slot(); break;
        case 9: _t->CancelButtonSolt(); break;
        case 10: _t->OkButtonSlot(); break;
        case 11: _t->EstyleLabelSlot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: _t->M_Explain(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (NccDialog::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NccDialog::KeyPgUpPressedSignal)) {
                *result = 0;
            }
        }
        {
            typedef void (NccDialog::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NccDialog::KeyPgDnPressedSignal)) {
                *result = 2;
            }
        }
        {
            typedef void (NccDialog::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NccDialog::KeyEscapePressedSignal)) {
                *result = 4;
            }
        }
        {
            typedef void (NccDialog::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NccDialog::KeyEnterPressedSignal)) {
                *result = 5;
            }
        }
        {
            typedef void (NccDialog::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NccDialog::KeyF1PressedSignal)) {
                *result = 6;
            }
        }
        {
            typedef void (NccDialog::*_t)(QString & , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NccDialog::NccDialogResult)) {
                *result = 7;
            }
        }
    }
}

const QMetaObject NccDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_NccDialog.data,
      qt_meta_data_NccDialog,  qt_static_metacall, 0, 0}
};


const QMetaObject *NccDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NccDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_NccDialog.stringdata))
        return static_cast<void*>(const_cast< NccDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int NccDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
void NccDialog::KeyPgUpPressedSignal(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 2
void NccDialog::KeyPgDnPressedSignal(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 4
void NccDialog::KeyEscapePressedSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void NccDialog::KeyEnterPressedSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void NccDialog::KeyF1PressedSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}

// SIGNAL 7
void NccDialog::NccDialogResult(QString & _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
struct qt_meta_stringdata_OutDialog_t {
    QByteArrayData data[16];
    char stringdata[218];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_OutDialog_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_OutDialog_t qt_meta_stringdata_OutDialog = {
    {
QT_MOC_LITERAL(0, 0, 9),
QT_MOC_LITERAL(1, 10, 20),
QT_MOC_LITERAL(2, 31, 0),
QT_MOC_LITERAL(3, 32, 5),
QT_MOC_LITERAL(4, 38, 20),
QT_MOC_LITERAL(5, 59, 22),
QT_MOC_LITERAL(6, 82, 21),
QT_MOC_LITERAL(7, 104, 18),
QT_MOC_LITERAL(8, 123, 15),
QT_MOC_LITERAL(9, 139, 8),
QT_MOC_LITERAL(10, 148, 6),
QT_MOC_LITERAL(11, 155, 16),
QT_MOC_LITERAL(12, 172, 12),
QT_MOC_LITERAL(13, 185, 15),
QT_MOC_LITERAL(14, 201, 5),
QT_MOC_LITERAL(15, 207, 9)
    },
    "OutDialog\0KeyPgUpPressedSignal\0\0bPgUp\0"
    "KeyPgDnPressedSignal\0KeyEscapePressedSignal\0"
    "KeyEnterPressedSignal\0KeyF1PressedSignal\0"
    "OutDialogResult\0QString&\0F1Slot\0"
    "CancelButtonSolt\0OkButtonSlot\0"
    "EstyleLabelSlot\0iPgUp\0M_Explain\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_OutDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x06,
       1,    0,   82,    2, 0x26,
       4,    1,   83,    2, 0x06,
       4,    0,   86,    2, 0x26,
       5,    0,   87,    2, 0x06,
       6,    0,   88,    2, 0x06,
       7,    0,   89,    2, 0x06,
       8,    3,   90,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
      10,    0,   97,    2, 0x08,
      11,    0,   98,    2, 0x08,
      12,    0,   99,    2, 0x08,
      13,    1,  100,    2, 0x08,
      15,    0,  103,    2, 0x08,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9, QMetaType::Int, QMetaType::Int,    2,    2,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   14,
    QMetaType::Void,

       0        // eod
};

void OutDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        OutDialog *_t = static_cast<OutDialog *>(_o);
        switch (_id) {
        case 0: _t->KeyPgUpPressedSignal((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->KeyPgUpPressedSignal(); break;
        case 2: _t->KeyPgDnPressedSignal((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->KeyPgDnPressedSignal(); break;
        case 4: _t->KeyEscapePressedSignal(); break;
        case 5: _t->KeyEnterPressedSignal(); break;
        case 6: _t->KeyF1PressedSignal(); break;
        case 7: _t->OutDialogResult((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 8: _t->F1Slot(); break;
        case 9: _t->CancelButtonSolt(); break;
        case 10: _t->OkButtonSlot(); break;
        case 11: _t->EstyleLabelSlot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: _t->M_Explain(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (OutDialog::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&OutDialog::KeyPgUpPressedSignal)) {
                *result = 0;
            }
        }
        {
            typedef void (OutDialog::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&OutDialog::KeyPgDnPressedSignal)) {
                *result = 2;
            }
        }
        {
            typedef void (OutDialog::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&OutDialog::KeyEscapePressedSignal)) {
                *result = 4;
            }
        }
        {
            typedef void (OutDialog::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&OutDialog::KeyEnterPressedSignal)) {
                *result = 5;
            }
        }
        {
            typedef void (OutDialog::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&OutDialog::KeyF1PressedSignal)) {
                *result = 6;
            }
        }
        {
            typedef void (OutDialog::*_t)(QString & , int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&OutDialog::OutDialogResult)) {
                *result = 7;
            }
        }
    }
}

const QMetaObject OutDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_OutDialog.data,
      qt_meta_data_OutDialog,  qt_static_metacall, 0, 0}
};


const QMetaObject *OutDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *OutDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_OutDialog.stringdata))
        return static_cast<void*>(const_cast< OutDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int OutDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
void OutDialog::KeyPgUpPressedSignal(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 2
void OutDialog::KeyPgDnPressedSignal(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 4
void OutDialog::KeyEscapePressedSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void OutDialog::KeyEnterPressedSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void OutDialog::KeyF1PressedSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}

// SIGNAL 7
void OutDialog::OutDialogResult(QString & _t1, int _t2, int _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
struct qt_meta_stringdata_SetDialog_t {
    QByteArrayData data[16];
    char stringdata[218];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_SetDialog_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_SetDialog_t qt_meta_stringdata_SetDialog = {
    {
QT_MOC_LITERAL(0, 0, 9),
QT_MOC_LITERAL(1, 10, 20),
QT_MOC_LITERAL(2, 31, 0),
QT_MOC_LITERAL(3, 32, 5),
QT_MOC_LITERAL(4, 38, 20),
QT_MOC_LITERAL(5, 59, 22),
QT_MOC_LITERAL(6, 82, 21),
QT_MOC_LITERAL(7, 104, 18),
QT_MOC_LITERAL(8, 123, 15),
QT_MOC_LITERAL(9, 139, 8),
QT_MOC_LITERAL(10, 148, 6),
QT_MOC_LITERAL(11, 155, 16),
QT_MOC_LITERAL(12, 172, 12),
QT_MOC_LITERAL(13, 185, 15),
QT_MOC_LITERAL(14, 201, 5),
QT_MOC_LITERAL(15, 207, 9)
    },
    "SetDialog\0KeyPgUpPressedSignal\0\0bPgUp\0"
    "KeyPgDnPressedSignal\0KeyEscapePressedSignal\0"
    "KeyEnterPressedSignal\0KeyF1PressedSignal\0"
    "SetDialogResult\0QString&\0F1Slot\0"
    "CancelButtonSolt\0OkButtonSlot\0"
    "EstyleLabelSlot\0iPgUp\0M_Explain\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SetDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x06,
       1,    0,   82,    2, 0x26,
       4,    1,   83,    2, 0x06,
       4,    0,   86,    2, 0x26,
       5,    0,   87,    2, 0x06,
       6,    0,   88,    2, 0x06,
       7,    0,   89,    2, 0x06,
       8,    2,   90,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
      10,    0,   95,    2, 0x08,
      11,    0,   96,    2, 0x08,
      12,    0,   97,    2, 0x08,
      13,    1,   98,    2, 0x08,
      15,    0,  101,    2, 0x08,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9, QMetaType::Int,    2,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   14,
    QMetaType::Void,

       0        // eod
};

void SetDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SetDialog *_t = static_cast<SetDialog *>(_o);
        switch (_id) {
        case 0: _t->KeyPgUpPressedSignal((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->KeyPgUpPressedSignal(); break;
        case 2: _t->KeyPgDnPressedSignal((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->KeyPgDnPressedSignal(); break;
        case 4: _t->KeyEscapePressedSignal(); break;
        case 5: _t->KeyEnterPressedSignal(); break;
        case 6: _t->KeyF1PressedSignal(); break;
        case 7: _t->SetDialogResult((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 8: _t->F1Slot(); break;
        case 9: _t->CancelButtonSolt(); break;
        case 10: _t->OkButtonSlot(); break;
        case 11: _t->EstyleLabelSlot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: _t->M_Explain(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (SetDialog::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SetDialog::KeyPgUpPressedSignal)) {
                *result = 0;
            }
        }
        {
            typedef void (SetDialog::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SetDialog::KeyPgDnPressedSignal)) {
                *result = 2;
            }
        }
        {
            typedef void (SetDialog::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SetDialog::KeyEscapePressedSignal)) {
                *result = 4;
            }
        }
        {
            typedef void (SetDialog::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SetDialog::KeyEnterPressedSignal)) {
                *result = 5;
            }
        }
        {
            typedef void (SetDialog::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SetDialog::KeyF1PressedSignal)) {
                *result = 6;
            }
        }
        {
            typedef void (SetDialog::*_t)(QString & , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SetDialog::SetDialogResult)) {
                *result = 7;
            }
        }
    }
}

const QMetaObject SetDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_SetDialog.data,
      qt_meta_data_SetDialog,  qt_static_metacall, 0, 0}
};


const QMetaObject *SetDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SetDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SetDialog.stringdata))
        return static_cast<void*>(const_cast< SetDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int SetDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
void SetDialog::KeyPgUpPressedSignal(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 2
void SetDialog::KeyPgDnPressedSignal(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 4
void SetDialog::KeyEscapePressedSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void SetDialog::KeyEnterPressedSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void SetDialog::KeyF1PressedSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}

// SIGNAL 7
void SetDialog::SetDialogResult(QString & _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
struct qt_meta_stringdata_RstDialog_t {
    QByteArrayData data[16];
    char stringdata[218];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_RstDialog_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_RstDialog_t qt_meta_stringdata_RstDialog = {
    {
QT_MOC_LITERAL(0, 0, 9),
QT_MOC_LITERAL(1, 10, 20),
QT_MOC_LITERAL(2, 31, 0),
QT_MOC_LITERAL(3, 32, 5),
QT_MOC_LITERAL(4, 38, 20),
QT_MOC_LITERAL(5, 59, 22),
QT_MOC_LITERAL(6, 82, 21),
QT_MOC_LITERAL(7, 104, 18),
QT_MOC_LITERAL(8, 123, 15),
QT_MOC_LITERAL(9, 139, 8),
QT_MOC_LITERAL(10, 148, 6),
QT_MOC_LITERAL(11, 155, 16),
QT_MOC_LITERAL(12, 172, 12),
QT_MOC_LITERAL(13, 185, 15),
QT_MOC_LITERAL(14, 201, 5),
QT_MOC_LITERAL(15, 207, 9)
    },
    "RstDialog\0KeyPgUpPressedSignal\0\0bPgUp\0"
    "KeyPgDnPressedSignal\0KeyEscapePressedSignal\0"
    "KeyEnterPressedSignal\0KeyF1PressedSignal\0"
    "RstDialogResult\0QString&\0F1Slot\0"
    "CancelButtonSolt\0OkButtonSlot\0"
    "EstyleLabelSlot\0iPgUp\0M_Explain\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RstDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x06,
       1,    0,   82,    2, 0x26,
       4,    1,   83,    2, 0x06,
       4,    0,   86,    2, 0x26,
       5,    0,   87,    2, 0x06,
       6,    0,   88,    2, 0x06,
       7,    0,   89,    2, 0x06,
       8,    2,   90,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
      10,    0,   95,    2, 0x08,
      11,    0,   96,    2, 0x08,
      12,    0,   97,    2, 0x08,
      13,    1,   98,    2, 0x08,
      15,    0,  101,    2, 0x08,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9, QMetaType::Int,    2,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   14,
    QMetaType::Void,

       0        // eod
};

void RstDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        RstDialog *_t = static_cast<RstDialog *>(_o);
        switch (_id) {
        case 0: _t->KeyPgUpPressedSignal((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->KeyPgUpPressedSignal(); break;
        case 2: _t->KeyPgDnPressedSignal((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->KeyPgDnPressedSignal(); break;
        case 4: _t->KeyEscapePressedSignal(); break;
        case 5: _t->KeyEnterPressedSignal(); break;
        case 6: _t->KeyF1PressedSignal(); break;
        case 7: _t->RstDialogResult((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 8: _t->F1Slot(); break;
        case 9: _t->CancelButtonSolt(); break;
        case 10: _t->OkButtonSlot(); break;
        case 11: _t->EstyleLabelSlot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: _t->M_Explain(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (RstDialog::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&RstDialog::KeyPgUpPressedSignal)) {
                *result = 0;
            }
        }
        {
            typedef void (RstDialog::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&RstDialog::KeyPgDnPressedSignal)) {
                *result = 2;
            }
        }
        {
            typedef void (RstDialog::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&RstDialog::KeyEscapePressedSignal)) {
                *result = 4;
            }
        }
        {
            typedef void (RstDialog::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&RstDialog::KeyEnterPressedSignal)) {
                *result = 5;
            }
        }
        {
            typedef void (RstDialog::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&RstDialog::KeyF1PressedSignal)) {
                *result = 6;
            }
        }
        {
            typedef void (RstDialog::*_t)(QString & , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&RstDialog::RstDialogResult)) {
                *result = 7;
            }
        }
    }
}

const QMetaObject RstDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_RstDialog.data,
      qt_meta_data_RstDialog,  qt_static_metacall, 0, 0}
};


const QMetaObject *RstDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RstDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RstDialog.stringdata))
        return static_cast<void*>(const_cast< RstDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int RstDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
void RstDialog::KeyPgUpPressedSignal(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 2
void RstDialog::KeyPgDnPressedSignal(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 4
void RstDialog::KeyEscapePressedSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void RstDialog::KeyEnterPressedSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void RstDialog::KeyF1PressedSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}

// SIGNAL 7
void RstDialog::RstDialogResult(QString & _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_END_MOC_NAMESPACE
