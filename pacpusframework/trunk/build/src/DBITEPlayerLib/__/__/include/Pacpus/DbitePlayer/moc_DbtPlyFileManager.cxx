/****************************************************************************
** Meta object code from reading C++ file 'DbtPlyFileManager.h'
**
** Created: Tue Oct 1 15:57:40 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../../../include/Pacpus/DbitePlayer/DbtPlyFileManager.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DbtPlyFileManager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_pacpus__DbtPlyFileManager[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      37,   27,   26,   26, 0x05,

 // slots: signature, parameters, type, tag, flags
      90,   72,   26,   26, 0x0a,
     129,   26,   26,   26, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_pacpus__DbtPlyFileManager[] = {
    "pacpus::DbtPlyFileManager\0\0tmin,tmax\0"
    "tMinMaxIs(road_time_t,road_time_t)\0"
    "tDbt,tNow,reverse\0"
    "playData(road_time_t,road_time_t,bool)\0"
    "beginfile()\0"
};

void pacpus::DbtPlyFileManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DbtPlyFileManager *_t = static_cast<DbtPlyFileManager *>(_o);
        switch (_id) {
        case 0: _t->tMinMaxIs((*reinterpret_cast< road_time_t(*)>(_a[1])),(*reinterpret_cast< road_time_t(*)>(_a[2]))); break;
        case 1: _t->playData((*reinterpret_cast< road_time_t(*)>(_a[1])),(*reinterpret_cast< road_time_t(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 2: _t->beginfile(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData pacpus::DbtPlyFileManager::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject pacpus::DbtPlyFileManager::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_pacpus__DbtPlyFileManager,
      qt_meta_data_pacpus__DbtPlyFileManager, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &pacpus::DbtPlyFileManager::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *pacpus::DbtPlyFileManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *pacpus::DbtPlyFileManager::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_pacpus__DbtPlyFileManager))
        return static_cast<void*>(const_cast< DbtPlyFileManager*>(this));
    if (!strcmp(_clname, "ComponentBase"))
        return static_cast< ComponentBase*>(const_cast< DbtPlyFileManager*>(this));
    return QThread::qt_metacast(_clname);
}

int pacpus::DbtPlyFileManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
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
void pacpus::DbtPlyFileManager::tMinMaxIs(road_time_t _t1, road_time_t _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
