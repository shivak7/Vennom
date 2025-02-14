/****************************************************************************
** Meta object code from reading C++ file 'vennomui.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Vennom/vennomui.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'vennomui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_VennomUI_t {
    QByteArrayData data[13];
    char stringdata0[255];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VennomUI_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VennomUI_t qt_meta_stringdata_VennomUI = {
    {
QT_MOC_LITERAL(0, 0, 8), // "VennomUI"
QT_MOC_LITERAL(1, 9, 29), // "on_ion_tree_itemDoubleClicked"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(4, 57, 4), // "item"
QT_MOC_LITERAL(5, 62, 6), // "column"
QT_MOC_LITERAL(6, 69, 25), // "on_WriteIonButton_clicked"
QT_MOC_LITERAL(7, 95, 27), // "on_Add_State_Button_clicked"
QT_MOC_LITERAL(8, 123, 27), // "on_Add_Param_Button_clicked"
QT_MOC_LITERAL(9, 151, 23), // "on_ion_tree_itemClicked"
QT_MOC_LITERAL(10, 175, 27), // "on_End_State_Button_clicked"
QT_MOC_LITERAL(11, 203, 25), // "on_iDelete_Button_clicked"
QT_MOC_LITERAL(12, 229, 25) // "on_Add_Dep_Button_clicked"

    },
    "VennomUI\0on_ion_tree_itemDoubleClicked\0"
    "\0QTreeWidgetItem*\0item\0column\0"
    "on_WriteIonButton_clicked\0"
    "on_Add_State_Button_clicked\0"
    "on_Add_Param_Button_clicked\0"
    "on_ion_tree_itemClicked\0"
    "on_End_State_Button_clicked\0"
    "on_iDelete_Button_clicked\0"
    "on_Add_Dep_Button_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VennomUI[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   54,    2, 0x08 /* Private */,
       6,    0,   59,    2, 0x08 /* Private */,
       7,    0,   60,    2, 0x08 /* Private */,
       8,    0,   61,    2, 0x08 /* Private */,
       9,    2,   62,    2, 0x08 /* Private */,
      10,    0,   67,    2, 0x08 /* Private */,
      11,    0,   68,    2, 0x08 /* Private */,
      12,    0,   69,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    4,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    4,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void VennomUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        VennomUI *_t = static_cast<VennomUI *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_ion_tree_itemDoubleClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->on_WriteIonButton_clicked(); break;
        case 2: _t->on_Add_State_Button_clicked(); break;
        case 3: _t->on_Add_Param_Button_clicked(); break;
        case 4: _t->on_ion_tree_itemClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->on_End_State_Button_clicked(); break;
        case 6: _t->on_iDelete_Button_clicked(); break;
        case 7: _t->on_Add_Dep_Button_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject VennomUI::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_VennomUI.data,
      qt_meta_data_VennomUI,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *VennomUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VennomUI::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_VennomUI.stringdata0))
        return static_cast<void*>(const_cast< VennomUI*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int VennomUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
