#include "widgetPCL.h"

#include <pcl/common/common.h>
#include <pcl/features/normal_3d.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
//#include <pcl/sample_consensus/sac_model_plane.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <qdebug.h>
//#include <QVTKWidget.h>
#include <iostream>
#include <pcl/filters/voxel_grid.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/features/normal_3d.h>
#include <pcl/surface/gp3.h>

#include "kernel/Log.h"

using namespace pacpus;

const std::vector<int> WidgetPCL::Default_Color(3, 255);

DECLARE_STATIC_LOGGER("pacpus.cityvip.WidgetPCL");

WidgetPCL::WidgetPCL()
{
    LOG_TRACE("constructor");

   // renderWindow=NULL;

   /*
    firstTime =true;
    counter=true;
    received_new_cloud_data=false;
    */

    start();
}

WidgetPCL::~WidgetPCL()
{
    LOG_TRACE("destructor");

    delete viewer;
}

/*
vtkSmartPointer<vtkRenderWindow>  WidgetPCL::getRenderWindows() {
    return renderWindow;
}
*/




pcl::PolygonMesh reconstruct_polygonmesh(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud){
      pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> n;
      pcl::PointCloud<pcl::Normal>::Ptr normals (new pcl::PointCloud<pcl::Normal>);
      pcl::search::KdTree<pcl::PointXYZ>::Ptr tree (new pcl::search::KdTree<pcl::PointXYZ>);
      tree->setInputCloud (cloud);
      n.setInputCloud (cloud);
      n.setSearchMethod (tree);
      n.setKSearch (20);
      n.compute (*normals);
      //* normals should not contain the point normals + surface curvatures

      // Concatenate the XYZ and normal fields*
      pcl::PointCloud<pcl::PointNormal>::Ptr cloud_with_normals (new pcl::PointCloud<pcl::PointNormal>);
      pcl::concatenateFields (*cloud, *normals, *cloud_with_normals);
      //* cloud_with_normals = cloud + normals

      // Create search tree*
      pcl::search::KdTree<pcl::PointNormal>::Ptr tree2 (new pcl::search::KdTree<pcl::PointNormal>);
      tree2->setInputCloud (cloud_with_normals);

      // Initialize objects
      pcl::GreedyProjectionTriangulation<pcl::PointNormal> gp3;
      pcl::PolygonMesh triangles;

      // Set the maximum distance between connected points (maximum edge length)
      gp3.setSearchRadius (0.25);

      // Set typical values for the parameters
      gp3.setMu (2.5);
      gp3.setMaximumNearestNeighbors (100);
      gp3.setMaximumSurfaceAngle(M_PI/4); // 45 degrees
      gp3.setMinimumAngle(M_PI/18); // 10 degrees
      gp3.setMaximumAngle(2*M_PI/3); // 120 degrees
      gp3.setNormalConsistency(false);

      // Get result
      gp3.setInputCloud (cloud_with_normals);
      gp3.setSearchMethod (tree2);
      gp3.reconstruct (triangles);

    return triangles;
}


void WidgetPCL::run()
{
    // FIXME: deleted in destructor, move instantiation to constructor, otherwise memory leak
    viewer = new pcl::visualization::PCLVisualizer("3D Viewer");

    viewer->setBackgroundColor (0, 0, 0);
    //viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "sample cloud");
    viewer->addCoordinateSystem (1.0);
    viewer->initCameraParameters ();

    /*
    renderWindow = viewer->getRenderWindow();

    widget = new  QVTKWidget();
    widget->resize(512, 256);
    widget->SetRenderWindow(renderWindow);
    widget->setWindowTitle("ok");
    widget->show();
    */

    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
    cloud_xyz=cloud;

    while (!viewer->wasStopped()) {
        //  sleep(1);
        /*
        if (received_new_cloud_data) {
            QMutexLocker mutexLocker(&mutex);
            Q_UNUSED(mutexLocker);

            received_new_cloud_data = false;

            viewer->removePointCloud("1");
            viewer->addPointCloud(cloud_xyz,"1");
        }
        */

        while(!cloudPoint_queue.empty()) {
            QMutexLocker mutexLocker(&mutex);
            Q_UNUSED(mutexLocker);

            //received_new_cloud_data = false;

            viewer->removePointCloud(cloudPoint_queue.front().name);
            viewer->addPointCloud(cloudPoint_queue.front().cloud_xyz,cloudPoint_queue.front().color,cloudPoint_queue.front().name,cloudPoint_queue.front().viewport);
    
            //std::cerr << "size" << cloudPoint_queue.size() <<"Name " << cloudPoint_queue.front().name << "cloud size "  << std::endl;
            cloudPoint_queue.pop();
        }

        viewer->spinOnce(100);
        // qDebug() << "run finish" << cloud_xyz->width;
    }
}

/*
void WidgetPCL::updatePointCloud(pcl::PointCloud<pcl::PointXYZ>::Ptr new_cloud_xyz)
{
    mutex.lock();
    cloud_xyz=new_cloud_xyz;
    mutex.unlock();
    received_new_cloud_data=true;
    qDebug() << "Updated" ;
}

void WidgetPCL::updatePointCloud(pcl::PointCloud<pcl::PointXYZ>::Ptr new_cloud_xyz, QString new_name, int viewport)
{
    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> new_color =  pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ>(new_cloud_xyz,255,255,255);
    updatePointCloud(new_cloud_xyz,new_color,new_name,viewport);
}

void WidgetPCL::updatePointCloud(pcl::PointCloud<pcl::PointXYZ>::Ptr new_cloud_xyz, pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> new_color, QString new_name , int viewport)
{
    CloudPointXYZDisplay CloudPoint ={new_cloud_xyz,new_color,new_name.toStdString(),viewport};
    mutex.lock();
    cloud_queue.push(new_cloud_xyz);
    cloud_name_queue.push(new_name);
    cloudPoint_queue.push(CloudPoint);
    mutex.unlock();
    qDebug() << "Updated" ;
}
*/

pcl::PointCloud<pcl::PointXYZ>::Ptr downsample_cloud(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud){
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered (new pcl::PointCloud<pcl::PointXYZ>());

    //Downsample
    pcl::VoxelGrid<pcl::PointXYZ> sor;
    sor.setInputCloud (cloud);
    sor.setLeafSize (0.1f, 0.1f, 0.1f);
    sor.filter (*cloud_filtered);

    //-> PointCloud before filtering: 133312 data points (x y z).PointCloud after filtering: 48027 data points (x y z).^C

    return cloud_filtered;
}


void WidgetPCL::updatePointCloud(pcl::PointCloud<pcl::PointXYZ>::Ptr new_cloud_xyz, QString new_name, std::vector<int> new_color_val, int viewport)
{
    LOG_TRACE("updating point cloud...");

    new_cloud_xyz = downsample_cloud(new_cloud_xyz);

    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> new_color =
            pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ>(new_cloud_xyz, new_color_val[0], new_color_val[1], new_color_val[2]);
    CloudPointXYZDisplay CloudPoint = {new_cloud_xyz, new_color, new_name.toStdString(), viewport};

    QMutexLocker mutexLocker(&mutex);
    Q_UNUSED(mutexLocker);

    /*cloud_queue.push(new_cloud_xyz);
    cloud_name_queue.push(new_name);*/
    cloudPoint_queue.push(CloudPoint);

    LOG_DEBUG("updated point cloud");
}

/*
void WidgetPCL::UpdatePointCloud(pcl::PointCloud<pcl::PointXYZ>::ConstPtr cloud) {

    if (!viewer->addPointCloud<pcl::PointXYZ> (cloud, "sample cloud"))
       viewer->addPointCloud<pcl::PointXYZ> (cloud, "sample cloud");
    viewer->getRenderWindow();
}
*/