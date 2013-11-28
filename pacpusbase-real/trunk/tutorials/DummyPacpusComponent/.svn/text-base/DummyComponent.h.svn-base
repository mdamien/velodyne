/*********************************************************************
//  created:    2011/04/26
//  filename:   DummyComponent.h
//
//  author:     Gerald Dherbomez
//              Copyright Heudiasyc UMR UTC/CNRS 6599
// 
//  version:    $Id: $
//
//  purpose:    Tuto 3 
*********************************************************************/

#ifndef DUMMYCOMPONENT_H
#define DUMMYCOMPONENT_H

#include <qtimer.h>

#include "kernel/ComponentBase.h"
#include "kernel/DbiteFile.h"

// Export macro for DummyPacpusComponent DLL for Windows only
#ifdef WIN32
#   ifdef DUMMYPACPUSCOMPONENT_EXPORTS
        // make DLL
#       define DUMMYPACPUSCOMPONENT_API __declspec(dllexport)
#   else
        // use DLL
#       define DUMMYPACPUSCOMPONENT_API __declspec(dllimport)
#   endif
#else
    // On other platforms, simply ignore this 
#   define DUMMYPACPUSCOMPONENT_API 
#endif

namespace pacpus {

struct DUMMYPACPUSCOMPONENT_API Dummy {
    road_time_t time;
    int dummy;
};

class DUMMYPACPUSCOMPONENT_API DummyComponent
        : public QObject
        , public ComponentBase
{
    Q_OBJECT

public:
    DummyComponent(QString name);
    ~DummyComponent();

protected:
    virtual ComponentBase::COMPONENT_CONFIGURATION configureComponent(XmlComponentConfig config);
    virtual void startActivity();
    virtual void stopActivity();

public Q_SLOTS:
  void acquire();

private:
    Dummy data_;
    QTimer timer_;
    int period_;
    DbiteFile dbtFile_;
};

} // namespace pacpus

#endif // DUMMYCOMPONENT_H
