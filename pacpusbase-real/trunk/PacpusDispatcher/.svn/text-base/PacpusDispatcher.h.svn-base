/*********************************************************************
//  created:    2012/03/01 - 14:07
//  filename:   PacpusDispatcher.h
//
//  author:     Pierre Hudelaine
//              Copyright Heudiasyc UMR UTC/CNRS 7253
// 
//  version:    $Id: $
//
//  purpose:	Receive and decode data from PacpusSocket
//
*********************************************************************/

#ifndef PACPUSDISPATCHER_H
#define PACPUSDISPATCHER_H

#include "Pacpus/kernel/road_time.h"
#include "Pacpus/kernel/ComponentBase.h"
#include "Pacpus/kernel/ComponentFactory.h"
#include "structureCanCarmen.h"
#include "../PacpusSocket/PacpusSocket.h"
#include "Pacpus/PacpusTools/ShMem.h"
#include "structureXbow.h"
#include "structure_cube.h"

#include <QDataStream>
#include <QByteArray>
#include <QBuffer>
#include <iostream>
#include <string>
#include <QDebug>
#include <QThread>

// Export macro for PacpusDispatcher DLL for Windows only
#ifdef WIN32
#   ifdef PACPUSDISPATCHER_EXPORTS
        // make DLL
#       define PACPUSDISPATCHER_API __declspec(dllexport)
#   else
        // use DLL
#       define PACPUSDISPATCHER_API __declspec(dllimport)
#   endif
#else
    // On other platforms, simply ignore this 
#   define PACPUSDISPATCHER_API 
#endif

namespace pacpus {


class PACPUSDISPATCHER_API PacpusDispatcher
        : public QThread
        , public ComponentBase
{
    Q_OBJECT

public:
    PacpusDispatcher( QString name );
    ~PacpusDispatcher();

    void run();
    
    virtual void stopActivity(); /*!< to stop the processing thread */
    virtual void startActivity(); /*!< to start the processing thread */
    virtual ComponentBase::COMPONENT_CONFIGURATION configureComponent( XmlComponentConfig config );
    
public Q_SLOTS:
    void receiveData( QString data);
    void receiveData( QByteArray data);

private:
    PacpusSocket * pacpusSocket_;
	ShMem * shmem_;
};

} // namespace pacpus

#endif // PACPUSDISPATCHER_H
