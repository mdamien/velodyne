/// @date created   2010/03/26 - 14:30
/// @author         Gerald Dherbomez
/// @copyright      Heudiasyc UMR UTC/CNRS 6599
/// @version        $Id: $

#ifndef VELODYNECOMPONENT_H
#define VELODYNECOMPONENT_H

#include <qhostaddress.h>
#include <qthread.h>

#include "kernel/ComponentBase.h"
#include "kernel/DbiteFile.h"
#include "kernel/road_time.h"
#include "PacpusTools/ShMem.h"
#include "structure_velodyne.h"

// TODO ! 
// faire une classe VelodyneDecoding qui s'occupera de traiter les données en provenance du slot readPendingDatagrams
// en effet, la classe VelodyneComponent vit dans le thread GUI alors que le socket udp vit dans le thread de VelodyneComponent
// du coup la connexion signal/slot n'est pas directe et mise en file d'attente. Il semble qu'il y ait ensuite un accès concurrent 
// quelque part qui fait planter le programme. 
// pas de plantage en mode monothread ! 
// cf. discussion http://lists.trolltech.com/qt-interest/2007-01/msg00757.html qui donne des infos et détails du même type 
// rem : la classe VelodyneDecoding devra être instancier dans le run() de VelodyneComponent pour que la connexion 
// se fassent entre des objets ayant le même contexte de thread ! 

// Export macro for AlascaXT DLL for Windows only
#ifdef WIN32
#   ifdef VELODYNEHDL64S2_EXPORTS
        // make DLL
#       define VELODYNEHDL64S2_API __declspec(dllexport)
#   else
        // use DLL
#       define VELODYNEHDL64S2_API __declspec(dllimport)
#   endif
#else
    // On other platforms, simply ignore this 
#   define VELODYNEHDL64S2_API 
#endif

class QUdpSocket;

namespace pacpus {

class VELODYNEHDL64S2_API VelodyneComponent
        : public QThread
        , public ComponentBase
{
    Q_OBJECT

public:
    VelodyneComponent(QString name);
    ~VelodyneComponent();

    /// to stop the processing thread
    virtual void stopActivity();
    /// to start the processing thread
    virtual void startActivity();
    virtual ComponentBase::COMPONENT_CONFIGURATION configureComponent(XmlComponentConfig config);

public Q_SLOTS:
    void readPendingDatagrams();

protected:
    void initialize();
    void close();
    void initSocket();
    void closeSocket();
    void run();
    void processTheDatagram(road_time_t time, QByteArray data);
    void record();
    void exposeData();
    void switchBuffer();

private:
    QUdpSocket * mSocket;

    bool mStartOfScan, mEndOfScan;
    unsigned short mBlockIndex;

    /// The Velodyne IP or hostname
    QHostAddress  mHost;

    /// The Velodyne port
    quint16 mPort;

    struct VelodynePolarData mVelodyneDataBuffer[2];
    struct VelodynePolarData * mVelodyneData; // a pointer to the current velodyneDataBuffer_
    struct VelodynePolarData * mFullBuffer;   // a pointer to the velodyne data which is completly filled

    int mCurrentVelodyneData;
    int mPreviousAngle;
    bool mRunning;

    DbiteFile mVelodyneSphericDataFile;

    ShMem * mShMem;
};

} // namespace pacpus

#endif // VELODYNECOMPONENT_H
