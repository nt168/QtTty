/****************************************************************************
** Meta object code from reading C++ file 'Session.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../Session.h"
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Session.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
namespace {
struct qt_meta_stringdata_Konsole__Session_t {
    uint offsetsAndSizes[40];
    char stringdata0[17];
    char stringdata1[13];
    char stringdata2[1];
    char stringdata3[5];
    char stringdata4[16];
    char stringdata5[5];
    char stringdata6[9];
    char stringdata7[17];
    char stringdata8[9];
    char stringdata9[16];
    char stringdata10[17];
    char stringdata11[24];
    char stringdata12[8];
    char stringdata13[14];
    char stringdata14[12];
    char stringdata15[7];
    char stringdata16[22];
    char stringdata17[21];
    char stringdata18[7];
    char stringdata19[17];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_Konsole__Session_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_Konsole__Session_t qt_meta_stringdata_Konsole__Session = {
    {
        QT_MOC_LITERAL(0, 16),  // "Konsole::Session"
        QT_MOC_LITERAL(17, 12),  // "receivedData"
        QT_MOC_LITERAL(30, 0),  // ""
        QT_MOC_LITERAL(31, 4),  // "text"
        QT_MOC_LITERAL(36, 15),  // "rawDataReceived"
        QT_MOC_LITERAL(52, 4),  // "data"
        QT_MOC_LITERAL(57, 8),  // "finished"
        QT_MOC_LITERAL(66, 16),  // "finishedWithCode"
        QT_MOC_LITERAL(83, 8),  // "exitCode"
        QT_MOC_LITERAL(92, 15),  // "silenceDetected"
        QT_MOC_LITERAL(108, 16),  // "activityDetected"
        QT_MOC_LITERAL(125, 23),  // "flowControlStateChanged"
        QT_MOC_LITERAL(149, 7),  // "enabled"
        QT_MOC_LITERAL(157, 13),  // "handlePtyData"
        QT_MOC_LITERAL(171, 11),  // "const char*"
        QT_MOC_LITERAL(183, 6),  // "length"
        QT_MOC_LITERAL(190, 21),  // "handleProcessFinished"
        QT_MOC_LITERAL(212, 20),  // "QProcess::ExitStatus"
        QT_MOC_LITERAL(233, 6),  // "status"
        QT_MOC_LITERAL(240, 16)   // "monitorTimerDone"
    },
    "Konsole::Session",
    "receivedData",
    "",
    "text",
    "rawDataReceived",
    "data",
    "finished",
    "finishedWithCode",
    "exitCode",
    "silenceDetected",
    "activityDetected",
    "flowControlStateChanged",
    "enabled",
    "handlePtyData",
    "const char*",
    "length",
    "handleProcessFinished",
    "QProcess::ExitStatus",
    "status",
    "monitorTimerDone"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_Konsole__Session[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   74,    2, 0x06,    1 /* Public */,
       4,    1,   77,    2, 0x06,    3 /* Public */,
       6,    0,   80,    2, 0x06,    5 /* Public */,
       7,    1,   81,    2, 0x06,    6 /* Public */,
       9,    0,   84,    2, 0x06,    8 /* Public */,
      10,    0,   85,    2, 0x06,    9 /* Public */,
      11,    1,   86,    2, 0x06,   10 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      13,    2,   89,    2, 0x08,   12 /* Private */,
      16,    2,   94,    2, 0x08,   15 /* Private */,
      19,    0,   99,    2, 0x08,   18 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QByteArray,    5,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   12,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 14, QMetaType::Int,    5,   15,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 17,    8,   18,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject Konsole::Session::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_Konsole__Session.offsetsAndSizes,
    qt_meta_data_Konsole__Session,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_Konsole__Session_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<Session, std::true_type>,
        // method 'receivedData'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'rawDataReceived'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QByteArray &, std::false_type>,
        // method 'finished'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'finishedWithCode'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'silenceDetected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'activityDetected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'flowControlStateChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'handlePtyData'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const char *, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'handleProcessFinished'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<QProcess::ExitStatus, std::false_type>,
        // method 'monitorTimerDone'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void Konsole::Session::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Session *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->receivedData((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->rawDataReceived((*reinterpret_cast< std::add_pointer_t<QByteArray>>(_a[1]))); break;
        case 2: _t->finished(); break;
        case 3: _t->finishedWithCode((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 4: _t->silenceDetected(); break;
        case 5: _t->activityDetected(); break;
        case 6: _t->flowControlStateChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 7: _t->handlePtyData((*reinterpret_cast< std::add_pointer_t<const char*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 8: _t->handleProcessFinished((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QProcess::ExitStatus>>(_a[2]))); break;
        case 9: _t->monitorTimerDone(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Session::*)(const QString & );
            if (_t _q_method = &Session::receivedData; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Session::*)(const QByteArray & );
            if (_t _q_method = &Session::rawDataReceived; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Session::*)();
            if (_t _q_method = &Session::finished; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Session::*)(int );
            if (_t _q_method = &Session::finishedWithCode; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (Session::*)();
            if (_t _q_method = &Session::silenceDetected; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (Session::*)();
            if (_t _q_method = &Session::activityDetected; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (Session::*)(bool );
            if (_t _q_method = &Session::flowControlStateChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
    }
}

const QMetaObject *Konsole::Session::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Konsole::Session::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Konsole__Session.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Konsole::Session::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void Konsole::Session::receivedData(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Konsole::Session::rawDataReceived(const QByteArray & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Konsole::Session::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void Konsole::Session::finishedWithCode(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Konsole::Session::silenceDetected()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void Konsole::Session::activityDetected()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void Konsole::Session::flowControlStateChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
