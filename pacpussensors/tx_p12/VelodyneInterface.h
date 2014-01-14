/**
@file

@date created 2010-08-03
@author Julien Moras
*/

#ifndef VELODYNEINTERFACE_H
#define VELODYNEINTERFACE_H

#include <qmutex.h>
#include <qthread.h>

//#include "LibSensorComponent.h"
#include "kernel/ComponentBase.h"
#include "../VelodyneComponent/structure_velodyne.h"
#include "structure_velodyne_cart.h"
//#include "structure_IGN.h"


#ifdef WIN32
#   ifdef VelodynePCLViewer_EXPORTS
        // make DLL
#       define SENSORCOMPONENT_API __declspec(dllexport)
#   else
        // use DLL
#       define SENSORCOMPONENT_API __declspec(dllimport)
#   endif
#else
    // On other platforms, simply ignore this 
#   define SENSORCOMPONENT_API 
#endif


class QImage;

namespace pacpus {

class ShMem;

struct SENSORCOMPONENT_API VelodyneComputingStrategy
{
    virtual void processRaw(VelodynePolarData * polarScanData) = 0;
    virtual void processCorrected(VelodyneCartData * cartesianScanData) = 0;
};

class SENSORCOMPONENT_API VelodyneInterface
        : public QThread
        , public ComponentBase
{
    Q_OBJECT

private:
    static const char * SHARED_MEMORY_NAME;

public:
    static const char * COMPONENT_NAME;
    static const char * COMPONENT_XML_NAME;

    /**
    * Constructor
    *
    * @param name TODO
    */
    VelodyneInterface(QString name);

    /**
    * Destructor
    */
    virtual ~VelodyneInterface();

    virtual void stopActivity();
    virtual void startActivity();
    virtual COMPONENT_CONFIGURATION configureComponent(XmlComponentConfig config);

    void setVelodyneComputingStrategy(VelodyneComputingStrategy * component) {velodyneComputingStrategy =component;}

protected:
    void run();

private:
    bool recording_;
    bool dbt2txt_;
    FILE * dbt2txtFile_;
    QString filePath_;
    bool m_isThreadAlive;

    static const int kVelodyneLayerCount = 64;
    double m_rotCor[kVelodyneLayerCount];
    double m_vertCor[kVelodyneLayerCount];
    double m_distCor[kVelodyneLayerCount];
    double m_hOffsetCor[kVelodyneLayerCount];
    double m_vOffsetCor[kVelodyneLayerCount];

    void loadCorrections(const std::string & file);

    // The shared memory where data are provided
    ShMem * shmem_;
    QMutex mutex;
    //incoming LidarData
    VelodynePolarData velodyneData_;
    VelodyneCartData velodyneCartData_;

    VelodyneComputingStrategy * velodyneComputingStrategy;

};

} // namespace pacpus

#endif // VELODYNEINTERFACE_H
