/**
@file
Purpose: Lidar Detection

@date created 2010-06-03 16:13
@author Julien Moras
@author Sergio Rodriguez
@version $Id: $
*/

#ifndef ComputingComponent_H
#define ComputingComponent_H

#include <qmutex.h>

#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/registration/transforms.h>
#include <pcl/range_image/range_image.h>

#include "kernel/ComponentBase.h"
//#include "structure/structureCanCarmen.h"
//#include "structure/structure_telemetre.h"  // ScanAlascaData
//#include "structure/structure_IGN.h"        // Pose2Denu

#include "VelodyneInterface.h"
//#include "LidarInterface.h"

//#include "../CLDLib/CityVIP_common.h"

class QImage;
class QTimer;

namespace pacpus {

class ShMem;
class WidgetPCL;

class ComputingComponent : public QObject, public ComponentBase, public VelodyneComputingStrategy
{
    Q_OBJECT

public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW

    static const char * COMPONENT_NAME;
    static const char * COMPONENT_XML_NAME;

    ComputingComponent(QString name);
    ~ComputingComponent();

    virtual void stopActivity();
    virtual void startActivity();
    virtual COMPONENT_CONFIGURATION configureComponent(XmlComponentConfig config);

    void startComponent();
    void stopComponent();

    void processRaw(VelodynePolarData *);
    void processCorrected(VelodyneCartData *);

private:
    void SetPointCloudFromScan(VelodyneCartData *, pcl::PointCloud<pcl::PointXYZ>::Ptr);
//    void SetPointCloudFromScan(ScanAlascaData *, pcl::PointCloud<pcl::PointXYZ>::Ptr);

    QMutex m_mutex;

    int m_fps;

    pcl::PointCloud<pcl::PointXYZ> globale_cloud;
    VelodyneInterface * m_VelodyneInterface;
    WidgetPCL * wi;
};

}

#endif // ComputingComponent_H
