#include <pcl/common/common.h>
#include <pcl/io/pcd_io.h>
#include <pcl/features/normal_3d_omp.h>
#include <pcl/surface/mls.h>
#include <pcl/surface/poisson.h>

#include <pcl/io/ply_io.h>
#include <pcl/io/vtk_io.h>
#include <pcl/io/vtk_lib_io.h>
#include <pcl/io/obj_io.h>

#include <pcl/visualization/cloud_viewer.h>


using namespace pcl;

int main (int argc, char **argv)
{
	if (argc != 3)
	{
		PCL_ERROR ("Syntax: %s input.pcd output.stl \n", argv[0]);
		return -1;
	}

	PointCloud<PointXYZ>::Ptr cloud (new PointCloud<PointXYZ> ());
	io::loadPCDFile (argv[1], *cloud);

	MovingLeastSquares<PointXYZ, PointXYZ> mls;
	mls.setInputCloud (cloud);
	mls.setSearchRadius (0.1);
	mls.setPolynomialFit (true);
	mls.setPolynomialOrder (2);
	mls.setUpsamplingMethod (MovingLeastSquares<PointXYZ, PointXYZ>::SAMPLE_LOCAL_PLANE);
	mls.setUpsamplingRadius (0.05);
	mls.setUpsamplingStepSize (0.02);

	PointCloud<PointXYZ>::Ptr cloud_smoothed (new PointCloud<PointXYZ> ());
	mls.process (*cloud_smoothed);
	NormalEstimationOMP<PointXYZ, Normal> ne;
	ne.setNumberOfThreads (8);
	ne.setInputCloud (cloud_smoothed);
	ne.setRadiusSearch (0.03);
	Eigen::Vector4f centroid;
	compute3DCentroid (*cloud_smoothed, centroid);
	ne.setViewPoint (centroid[0], centroid[1], centroid[2]);
	PointCloud<Normal>::Ptr cloud_normals (new PointCloud<Normal> ());
	ne.compute (*cloud_normals);
	PointCloud<PointNormal>::Ptr cloud_smoothed_normals (new PointCloud<PointNormal> ());
	concatenateFields (*cloud_smoothed, *cloud_normals, *cloud_smoothed_normals);

	Poisson<PointNormal> poisson;
	poisson.setDepth (9);
	poisson.setInputCloud
	(cloud_smoothed_normals);

	PolygonMesh mesh;
	poisson.reconstruct (mesh);

    visualization::CloudViewer viewer("Simple Cloud Viewer");
   viewer.showCloud(cloud);
   while (!viewer.wasStopped())
   {
   }

	pcl::io::savePolygonFileSTL(argv[2], mesh);
	return 0;
}