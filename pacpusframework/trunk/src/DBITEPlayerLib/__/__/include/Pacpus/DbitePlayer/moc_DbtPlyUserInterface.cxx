/****************************************************************************
** Meta object code from reading C++ file 'DbtPlyUserInterface.h'
**
** Created: Tue Oct 1 15:43:43 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../../include/Pacpus/DbitePlayer/DbtPlyUserInterface.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DbtPlyUserInterface.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_pacpus__DbtPlyUserInterface[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      41,   29,   28,   28, 0x0a,
      92,   84,   28,   28, 0x0a,
     140,  135,   28,   28, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_pacpus__DbtPlyUserInterface[] = {
    "pacpus::DbtPlyUserInterface\0\0state,speed\0"
    "displayStateSlot(DbtPlyEngineState*,float)\0"
    "min,max\0displayMinMaxTime(road_time_t,road_time_t)\0"
    "time\0displayTime(road_time_t)\0"
};

void pacpus::DbtPlyUserInterface::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DbtPlyUserInterface *_t = static_cast<DbtPlyUserInterface *>(_o);
        switch (_id) {
        case 0: _t->displayStateSlot((*reinterpret_cast< DbtPlyEngineState*(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 1: _t->displayMinMaxTime((*reinterpret_cast< road_time_t(*)>(_a[1])),(*reinterpret_cast< road_time_t(*)>(_a[2]))); break;
        case 2: _t->displayTime((*reinterpret_cast< road_time_t(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData pacpus::DbtPlyUserInterface::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject pacpus::DbtPlyUserInterface::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_pacpus__DbtPlyUserInterface,
      qt_meta_data_pacpus__DbtPlyUserInterface, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &pacpus::DbtPlyUserInterface::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *pacpus::DbtPlyUserInterface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *pacpus::DbtPlyUserInterface::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_pacpus__DbtPlyUserInterface))
        return static_cast<void*>(const_cast< DbtPlyUserInterface*>(this));
    if (!strcmp(_clname, "ComponentBase"))
        return static_cast< ComponentBase*>(const_cast< DbtPlyUserInterface*>(this));
    return QWidget::qt_metacast(_clname);
}

int pacpus::DbtPlyUserInterface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
