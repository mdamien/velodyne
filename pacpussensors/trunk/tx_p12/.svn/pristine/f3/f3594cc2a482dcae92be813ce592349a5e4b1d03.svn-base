#ifndef WIDGETPCL_H
#define WIDGETPCL_H

#include <qmutex.h>
#include <qthread.h>
#include <queue>
#include <string>

#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/visualization/point_cloud_handlers.h>

//#include "vtkSmartPointer.h"
//#include "vtkRenderWindow.h"

//class QVTKWidget;

namespace pcl { namespace visualization {
class PCLVisualizer;
} }

struct CloudPointXYZDisplay
{
    pcl::PointCloud<pcl::PointXYZ>::Ptr  cloud_xyz;
    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> color;
    std::string name;
    int viewport;
};

namespace pacpus {

class WidgetPCL
        : public QThread
{
    Q_OBJECT

public:
    WidgetPCL();
    ~WidgetPCL();

    static const std::vector<int> Default_Color;

    //vtkSmartPointer<vtkRenderWindow> getRenderWindows();
    //void updatePointCloud(pcl::PointCloud<pcl::PointXYZ>::Ptr);
    //void updatePointCloud(pcl::PointCloud<pcl::PointXYZ>::Ptr, QString  = "cloud", int  = 0);
    //void updatePointCloud(pcl::PointCloud<pcl::PointXYZ>::Ptr, pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> ,QString  = "cloud", int  = 0);
    void updatePointCloud(pcl::PointCloud<pcl::PointXYZ>::Ptr, QString  = "cloud", std::vector<int>  = Default_Color, int  = 0);
    //QVTKWidget * widget;

protected:
    void run();

private:
    std::queue<CloudPointXYZDisplay> cloudPoint_queue;
    pcl::PointCloud<pcl::PointXYZ>::Ptr  cloud_xyz;
    std::queue<pcl::PointCloud<pcl::PointXYZ>::Ptr>  cloud_queue;
    pcl::visualization::PCLVisualizer * viewer;
    QString name;
    std::queue<QString>  cloud_name_queue;

    //vtkSmartPointer<vtkRenderWindow> renderWindow;
    //bool firstTime,counter,received_new_cloud_data;
    QMutex mutex;
};

}

#endif // WIDGETPCL_H
