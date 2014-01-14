#include <pcl/common/common.h>
#include <pcl/io/pcd_io.h>
#include <iostream>
#include <pcl/ModelCoefficients.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/sample_consensus/method_types.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/filters/extract_indices.h>

#include <boost/thread/thread.hpp>

using namespace pcl;

int
 main (int argc, char** argv)
{
  if (argc != 3)
  {
    PCL_ERROR ("Syntax: %s input.pcd output.stl \n", argv[0]);
    return -1;
  }

  PointCloud<PointXYZ>::Ptr cloud (new PointCloud<PointXYZ> ())
    , cloud_p (new pcl::PointCloud<pcl::PointXYZ>)
    , cloud_p_neg (new pcl::PointCloud<pcl::PointXYZ>);
  io::loadPCDFile (argv[1], *cloud);

  pcl::ModelCoefficients::Ptr coefficients (new pcl::ModelCoefficients);
  pcl::PointIndices::Ptr inliers (new pcl::PointIndices);
  pcl::SACSegmentation<pcl::PointXYZ> seg;
  seg.setOptimizeCoefficients (true);
  seg.setModelType (pcl::SACMODEL_PLANE);
  seg.setMethodType (pcl::SAC_RANSAC);
  seg.setDistanceThreshold (0.01);
  seg.setInputCloud ((*cloud).makeShared ());
  seg.segment (*inliers, *coefficients);

  if (inliers->indices.size () == 0)
  {
    PCL_ERROR ("Could not estimate a planar model for the given dataset.");
    return (-1);
  }

  std::cerr << "Model coefficients: " << coefficients->values[0] << " " 
                                      << coefficients->values[1] << " "
                                      << coefficients->values[2] << " " 
                                      << coefficients->values[3] << std::endl;

  std::cerr << "Model inliers: " << inliers->indices.size () << std::endl;

  pcl::ExtractIndices<pcl::PointXYZ> extract;
  extract.setInputCloud (cloud);
  extract.setIndices (inliers);
  extract.setNegative (false);
  extract.filter (*cloud_p);

  extract.setInputCloud (cloud);
  extract.setIndices (inliers);
  extract.setNegative (true);
  extract.filter (*cloud_p_neg);

  boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer (new pcl::visualization::PCLVisualizer ("3D Viewer"));
  viewer->setBackgroundColor (0, 0, 0);
  viewer->addPointCloud<pcl::PointXYZ> (cloud, "cloud");
  viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "cloud");
  viewer->addCoordinateSystem (1.0);
  viewer->initCameraParameters ();
  viewer->addPlane(*coefficients, "plane");

  while (!viewer->wasStopped ())
  {
    viewer->spinOnce (100);
    boost::this_thread::sleep (boost::posix_time::microseconds (100000));
  }

  return (0);
}
