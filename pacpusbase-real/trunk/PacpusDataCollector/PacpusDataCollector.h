/*********************************************************************
//  created:    2012/03/01 - 14:07
//  filename:   PacpusDataCollector.h
//
//  author:     Pierre Hudelaine
//              Copyright Heudiasyc UMR UTC/CNRS 7253
// 
//  version:    $Id: $
//
//  purpose:	Collect and format the Pacpus data to send with PacpusSocket
//
*********************************************************************/

#ifndef PACPUSDATACOLLECTOR_H
#define PACPUSDATACOLLECTOR_H

#include "Pacpus/kernel/road_time.h"
#include "Pacpus/kernel/ComponentBase.h"
#include "Pacpus/kernel/ComponentFactory.h"
#include "../PacpusSocket/PacpusSocket.h"
#include "io_hdfile.h"
#include "Pacpus/kernel/Log.h"
#include "Pacpus/PacpusTools/ShMem.h"
#include "InterfaceDataCollector.h"
#include "structureXbow.h"
#include "structure_cube.h"
#include "structureCanCarmen.h"
#include "structure_gps.h"

#include <iomanip>

#include <QDataStream>
#include <QBuffer>

#include <iostream>
#include <string>
#include <QDebug>
#include <QThread>

// Export macro for PacpusDataCollector DLL for Windows only
#ifdef WIN32
#   ifdef PACPUSDATACOLLECTOR_EXPORTS
        // make DLL
#       define PACPUSDATACOLLECTOR_API __declspec(dllexport)
#   else
        // use DLL
#       define PACPUSDATACOLLECTOR_API __declspec(dllimport)
#   endif
#else
    // On other platforms, simply ignore this 
#   define PACPUSDATACOLLECTOR_API 
#endif

PACPUSDATACOLLECTOR_API QDataStream &operator<<( QDataStream &s, const TimestampedWgs84Position &d );
PACPUSDATACOLLECTOR_API QDataStream &operator>>( QDataStream &s, TimestampedWgs84Position &d );

namespace pacpus {

class PACPUSDATACOLLECTOR_API PacpusDataCollector
        : public QThread
        , public ComponentBase
{
    Q_OBJECT

public:
    PacpusDataCollector( QString name );
    ~PacpusDataCollector();

    void run();
    QString buildOrAddMsg( QString f, QString T, QString t, QString d = QString::null, QString c = QString::null );
    void buildAndSendBinMsg( QString T, QString t, char * dataToSend, int sizeOfDataToSend );
    void sendMsg( QString msg );
    
    virtual void stopActivity(); /*!< to stop the processing thread */
    virtual void startActivity(); /*!< to start the processing thread */
    virtual ComponentBase::COMPONENT_CONFIGURATION configureComponent( XmlComponentConfig config );

private:
    InterfaceDataCollector<TimestampedStructVehicleSpeed> * odometryData_;
    InterfaceDataCollector<TimestampedStructSteeringWheel> * steeringWheelData_;
    InterfaceDataCollector<VG700dataframe> * VG700Data_;
    InterfaceDataCollector<TimestampedStructWheelSpeed> * wheelSpeedData_;
    InterfaceDataCollector<StructureCubeRawData> * cubeData_;
    //TODO : 
    //InterfaceDataCollector<YourDataType> * YourDataData_;
    
    bool odometryActive_;
    bool steeringWheelActive_;
    bool VG700Active_;
    bool wheelSpeedActive_;
    bool cubeActive_;
    //TODO : 
    //bool YourDataActive_;
    
    PacpusSocket * pacpusSocket_;
    
    // Set separator and message type
    QString headerMsgBin_;
    QString headerMsgText_;
    QString charDelimitorPacpus_;
    QString charDelimitor_;
    QString charEqual_;
    QString beginingMsg_; // Begining of the message with sens, source,...
};

} // namespace pacpus

#endif // PACPUSDATACOLLECTOR_H
 