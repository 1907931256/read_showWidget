/****************************************************************************
** Meta object code from reading C++ file 'uiPlcEditor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../PLC/uiPlcEditor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'uiPlcEditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_uiPlcEditor_t {
    QByteArrayData data[27];
    char stringdata[334];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_uiPlcEditor_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_uiPlcEditor_t qt_meta_stringdata_uiPlcEditor = {
    {
QT_MOC_LITERAL(0, 0, 11),
QT_MOC_LITERAL(1, 12, 13),
QT_MOC_LITERAL(2, 26, 0),
QT_MOC_LITERAL(3, 27, 6),
QT_MOC_LITERAL(4, 34, 13),
QT_MOC_LITERAL(5, 48, 11),
QT_MOC_LITERAL(6, 60, 3),
QT_MOC_LITERAL(7, 64, 18),
QT_MOC_LITERAL(8, 83, 18),
QT_MOC_LITERAL(9, 102, 13),
QT_MOC_LITERAL(10, 116, 8),
QT_MOC_LITERAL(11, 125, 8),
QT_MOC_LITERAL(12, 134, 5),
QT_MOC_LITERAL(13, 140, 13),
QT_MOC_LITERAL(14, 154, 13),
QT_MOC_LITERAL(15, 168, 5),
QT_MOC_LITERAL(16, 174, 13),
QT_MOC_LITERAL(17, 188, 13),
QT_MOC_LITERAL(18, 202, 17),
QT_MOC_LITERAL(19, 220, 16),
QT_MOC_LITERAL(20, 237, 16),
QT_MOC_LITERAL(21, 254, 14),
QT_MOC_LITERAL(22, 269, 14),
QT_MOC_LITERAL(23, 284, 14),
QT_MOC_LITERAL(24, 299, 17),
QT_MOC_LITERAL(25, 317, 3),
QT_MOC_LITERAL(26, 321, 11)
    },
    "uiPlcEditor\0sendCmdSignal\0\0bStart\0"
    "whichIsActive\0buttonGroup\0num\0"
    "popButton_one_slot\0popButton_two_slot\0"
    "NocButtonSlot\0QString&\0qsEstyle\0iENum\0"
    "NccButtonSlot\0OutButtonSolt\0iPara\0"
    "SetButtonSlot\0RstButtonSlot\0"
    "DeleteElementSlot\0DeleteBranchSlot\0"
    "InsertBranchSlot\0InsertRungSlot\0"
    "DeleteRungSlot\0SaveButtonSlot\0"
    "ModifyElementSlot\0str\0ChangeState\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_uiPlcEditor[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   99,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
       4,    2,  102,    2, 0x08,
       7,    1,  107,    2, 0x08,
       8,    1,  110,    2, 0x08,
       9,    2,  113,    2, 0x08,
      13,    2,  118,    2, 0x08,
      14,    3,  123,    2, 0x08,
      16,    2,  130,    2, 0x08,
      17,    2,  135,    2, 0x08,
      18,    0,  140,    2, 0x08,
      19,    0,  141,    2, 0x08,
      20,    0,  142,    2, 0x08,
      21,    0,  143,    2, 0x08,
      22,    0,  144,    2, 0x08,
      23,    0,  145,    2, 0x08,
      24,    1,  146,    2, 0x08,
      26,    0,  149,    2, 0x08,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    5,    6,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, 0x80000000 | 10, QMetaType::Int,   11,   12,
    QMetaType::Void, 0x80000000 | 10, QMetaType::Int,   11,   12,
    QMetaType::Void, 0x80000000 | 10, QMetaType::Int, QMetaType::Int,   11,   12,   15,
    QMetaType::Void, 0x80000000 | 10, QMetaType::Int,   11,   12,
    QMetaType::Void, 0x80000000 | 10, QMetaType::Int,   11,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10,   25,
    QMetaType::Void,

       0        // eod
};

void uiPlcEditor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        uiPlcEditor *_t = static_cast<uiPlcEditor *>(_o);
        switch (_id) {
        case 0: _t->sendCmdSignal((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->whichIsActive((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->popButton_one_slot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->popButton_two_slot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->NocButtonSlot((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->NccButtonSlot((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->OutButtonSolt((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 7: _t->SetButtonSlot((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 8: _t->RstButtonSlot((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 9: _t->DeleteElementSlot(); break;
        case 10: _t->DeleteBranchSlot(); break;
        case 11: _t->InsertBranchSlot(); break;
        case 12: _t->InsertRungSlot(); break;
        case 13: _t->DeleteRungSlot(); break;
        case 14: _t->SaveButtonSlot(); break;
        case 15: _t->ModifyElementSlot((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 16: _t->ChangeState(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (uiPlcEditor::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&uiPlcEditor::sendCmdSignal)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject uiPlcEditor::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_uiPlcEditor.data,
      qt_meta_data_uiPlcEditor,  qt_static_metacall, 0, 0}
};


const QMetaObject *uiPlcEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *uiPlcEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_uiPlcEditor.stringdata))
        return static_cast<void*>(const_cast< uiPlcEditor*>(this));
    return QWidget::qt_metacast(_clname);
}

int uiPlcEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void uiPlcEditor::sendCmdSignal(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
