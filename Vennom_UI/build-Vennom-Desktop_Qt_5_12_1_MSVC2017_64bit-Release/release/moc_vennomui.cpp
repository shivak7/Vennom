/****************************************************************************
** Meta object code from reading C++ file 'vennomui.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Vennom/vennomui.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'vennomui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_VennomUI_t {
    QByteArrayData data[20];
    char stringdata0[347];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VennomUI_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VennomUI_t qt_meta_stringdata_VennomUI = {
    {
QT_MOC_LITERAL(0, 0, 8), // "VennomUI"
QT_MOC_LITERAL(1, 9, 12), // "DependBrowse"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 29), // "on_ion_tree_itemDoubleClicked"
QT_MOC_LITERAL(4, 53, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(5, 70, 4), // "item"
QT_MOC_LITERAL(6, 75, 6), // "column"
QT_MOC_LITERAL(7, 82, 25), // "on_WriteIonButton_clicked"
QT_MOC_LITERAL(8, 108, 27), // "on_Add_State_Button_clicked"
QT_MOC_LITERAL(9, 136, 27), // "on_Add_Param_Button_clicked"
QT_MOC_LITERAL(10, 164, 23), // "on_ion_tree_itemClicked"
QT_MOC_LITERAL(11, 188, 27), // "on_End_State_Button_clicked"
QT_MOC_LITERAL(12, 216, 25), // "on_iDelete_Button_clicked"
QT_MOC_LITERAL(13, 242, 25), // "on_Add_Dep_Button_clicked"
QT_MOC_LITERAL(14, 268, 13), // "keyPressEvent"
QT_MOC_LITERAL(15, 282, 10), // "QKeyEvent*"
QT_MOC_LITERAL(16, 293, 5), // "event"
QT_MOC_LITERAL(17, 299, 30), // "on_ion_tree_currentItemChanged"
QT_MOC_LITERAL(18, 330, 7), // "current"
QT_MOC_LITERAL(19, 338, 8) // "previous"

    },
    "VennomUI\0DependBrowse\0\0"
    "on_ion_tree_itemDoubleClicked\0"
    "QTreeWidgetItem*\0item\0column\0"
    "on_WriteIonButton_clicked\0"
    "on_Add_State_Button_clicked\0"
    "on_Add_Param_Button_clicked\0"
    "on_ion_tree_itemClicked\0"
    "on_End_State_Button_clicked\0"
    "on_iDelete_Button_clicked\0"
    "on_Add_Dep_Button_clicked\0keyPressEvent\0"
    "QKeyEvent*\0event\0on_ion_tree_currentItemChanged\0"
    "current\0previous"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VennomUI[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x08 /* Private */,
       3,    2,   70,    2, 0x08 /* Private */,
       7,    0,   75,    2, 0x08 /* Private */,
       8,    0,   76,    2, 0x08 /* Private */,
       9,    0,   77,    2, 0x08 /* Private */,
      10,    2,   78,    2, 0x08 /* Private */,
      11,    0,   83,    2, 0x08 /* Private */,
      12,    0,   84,    2, 0x08 /* Private */,
      13,    0,   85,    2, 0x08 /* Private */,
      14,    1,   86,    2, 0x08 /* Private */,
      17,    2,   89,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4, QMetaType::Int,    5,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4, QMetaType::Int,    5,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 15,   16,
    QMetaType::Void, 0x80000000 | 4, 0x80000000 | 4,   18,   19,

       0        // eod
};

void VennomUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<VennomUI *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->DependBrowse(); break;
        case 1: _t->on_ion_tree_itemDoubleClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->on_WriteIonButton_clicked(); break;
        case 3: _t->on_Add_State_Button_clicked(); break;
        case 4: _t->on_Add_Param_Button_clicked(); break;
        case 5: _t->on_ion_tree_itemClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->on_End_State_Button_clicked(); break;
        case 7: _t->on_iDelete_Button_clicked(); break;
        case 8: _t->on_Add_Dep_Button_clicked(); break;
        case 9: _t->keyPressEvent((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        case 10: _t->on_ion_tree_currentItemChanged((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< QTreeWidgetItem*(*)>(_a[2]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject VennomUI::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_VennomUI.data,
    qt_meta_data_VennomUI,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VennomUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VennomUI::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VennomUI.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int VennomUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
