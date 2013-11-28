/****************************************************************************
** Meta object code from reading C++ file 'DbtPlyEngine.h'
**
** Created: Tue Oct 1 15:43:43 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../../include/Pacpus/DbitePlayer/DbtPlyEngine.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DbtPlyEngine.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_pacpus__DbtPlyEngine[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: signature, parameters, type, tag, flags
      54,   22,   21,   21, 0x05,
      89,   21,   21,   21, 0x05,
     112,  100,   21,   21, 0x05,
     164,  154,   21,   21, 0x05,
     205,  200,   21,   21, 0x05,

 // slots: signature, parameters, type, tag, flags
     232,   21,   21,   21, 0x0a,
     254,  246,   21,   21, 0x0a,
     276,  154,   21,   21, 0x0a,
     309,   21,   21,   21, 0x0a,
     321,   21,   21,   21, 0x0a,
     334,   21,   21,   21, 0x0a,
     346,   21,   21,   21, 0x0a,
     361,   21,   21,   21, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_pacpus__DbtPlyEngine[] = {
    "pacpus::DbtPlyEngine\0\0"
    "timeToPlay,actualTime,direction\0"
    "play(road_time_t,road_time_t,bool)\0"
    "stopfile()\0state,speed\0"
    "displayStateSig(DbtPlyEngineState*,float)\0"
    "tMin,tMax\0timeMinMax(road_time_t,road_time_t)\0"
    "time\0curReplayTime(road_time_t)\0"
    "engReceiver()\0reverse\0changeDirection(bool)\0"
    "tMinMax(road_time_t,road_time_t)\0"
    "playEvent()\0pauseEvent()\0stopEvent()\0"
    "speedUpEvent()\0speedDownEvent()\0"
};

void pacpus::DbtPlyEngine::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DbtPlyEngine *_t = static_cast<DbtPlyEngine *>(_o);
        switch (_id) {
        case 0: _t->play((*reinterpret_cast< road_time_t(*)>(_a[1])),(*reinterpret_cast< road_time_t(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 1: _t->stopfile(); break;
        case 2: _t->displayStateSig((*reinterpret_cast< DbtPlyEngineState*(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 3: _t->timeMinMax((*reinterpret_cast< road_time_t(*)>(_a[1])),(*reinterpret_cast< road_time_t(*)>(_a[2]))); break;
        case 4: _t->curReplayTime((*reinterpret_cast< road_time_t(*)>(_a[1]))); break;
        case 5: _t->engReceiver(); break;
        case 6: _t->changeDirection((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->tMinMax((*reinterpret_cast< road_time_t(*)>(_a[1])),(*reinterpret_cast< road_time_t(*)>(_a[2]))); break;
        case 8: _t->playEvent(); break;
        case 9: _t->pauseEvent(); break;
        case 10: _t->stopEvent(); break;
        case 11: _t->speedUpEvent(); break;
        case 12: _t->speedDownEvent(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData pacpus::DbtPlyEngine::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject pacpus::DbtPlyEngine::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_pacpus__DbtPlyEngine,
      qt_meta_data_pacpus__DbtPlyEngine, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &pacpus::DbtPlyEngine::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *pacpus::DbtPlyEngine::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *pacpus::DbtPlyEngine::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_pacpus__DbtPlyEngine))
        return static_cast<void*>(const_cast< DbtPlyEngine*>(this));
    if (!strcmp(_clname, "ComponentBase"))
        return static_cast< ComponentBase*>(const_cast< DbtPlyEngine*>(this));
    return QThread::qt_metacast(_clname);
}

int pacpus::DbtPlyEngine::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void pacpus::DbtPlyEngine::play(road_time_t _t1, road_time_t _t2, bool _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void pacpus::DbtPlyEngine::stopfile()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void pacpus::DbtPlyEngine::displayStateSig(DbtPlyEngineState * _t1, float _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void pacpus::DbtPlyEngine::timeMinMax(road_time_t _t1, road_time_t _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void pacpus::DbtPlyEngine::curReplayTime(road_time_t _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
