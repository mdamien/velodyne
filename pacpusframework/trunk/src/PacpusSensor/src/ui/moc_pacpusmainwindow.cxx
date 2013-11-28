/****************************************************************************
** Meta object code from reading C++ file 'pacpusmainwindow.h'
**
** Created: Tue Oct 1 15:43:51 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "pacpusmainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pacpusmainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_pacpus__ComponentCheckBox[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      27,   26,   26,   26, 0x05,
      45,   26,   26,   26, 0x05,

 // slots: signature, parameters, type, tag, flags
      71,   65,   26,   26, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_pacpus__ComponentCheckBox[] = {
    "pacpus::ComponentCheckBox\0\0activate(QString)\0"
    "deactivate(QString)\0state\0change(bool)\0"
};

void pacpus::ComponentCheckBox::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ComponentCheckBox *_t = static_cast<ComponentCheckBox *>(_o);
        switch (_id) {
        case 0: _t->activate((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->deactivate((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->change((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData pacpus::ComponentCheckBox::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject pacpus::ComponentCheckBox::staticMetaObject = {
    { &QCheckBox::staticMetaObject, qt_meta_stringdata_pacpus__ComponentCheckBox,
      qt_meta_data_pacpus__ComponentCheckBox, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &pacpus::ComponentCheckBox::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *pacpus::ComponentCheckBox::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *pacpus::ComponentCheckBox::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_pacpus__ComponentCheckBox))
        return static_cast<void*>(const_cast< ComponentCheckBox*>(this));
    return QCheckBox::qt_metacast(_clname);
}

int pacpus::ComponentCheckBox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCheckBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void pacpus::ComponentCheckBox::activate(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void pacpus::ComponentCheckBox::deactivate(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
static const uint qt_meta_data_pacpus__PacpusMainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      26,   25,   25,   25, 0x0a,
      55,   45,   25,   25, 0x0a,
      79,   25,   25,   25, 0x0a,
      97,   45,   25,   25, 0x0a,
     120,   25,   25,   25, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_pacpus__PacpusMainWindow[] = {
    "pacpus::PacpusMainWindow\0\0startAcquisition()\0"
    "component\0startComponent(QString)\0"
    "stopAcquisition()\0stopComponent(QString)\0"
    "monitoring()\0"
};

void pacpus::PacpusMainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        PacpusMainWindow *_t = static_cast<PacpusMainWindow *>(_o);
        switch (_id) {
        case 0: _t->startAcquisition(); break;
        case 1: _t->startComponent((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->stopAcquisition(); break;
        case 3: _t->stopComponent((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->monitoring(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData pacpus::PacpusMainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject pacpus::PacpusMainWindow::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_pacpus__PacpusMainWindow,
      qt_meta_data_pacpus__PacpusMainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &pacpus::PacpusMainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *pacpus::PacpusMainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *pacpus::PacpusMainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_pacpus__PacpusMainWindow))
        return static_cast<void*>(const_cast< PacpusMainWindow*>(this));
    if (!strcmp(_clname, "Ui::PacpusMainWindow"))
        return static_cast< Ui::PacpusMainWindow*>(const_cast< PacpusMainWindow*>(this));
    return QDialog::qt_metacast(_clname);
}

int pacpus::PacpusMainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
