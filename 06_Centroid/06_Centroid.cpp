#include <pcl/io/pcd_io.h>
#include <pcl/common/centroid.h>
#include <iostream>

int main( )
{
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);

	if (pcl::io::loadPCDFile<pcl::PointXYZ>("Modelpcd.pcd", *cloud) == -1)//*打开点云文件
	{
		PCL_ERROR("Couldn't read file.\n");
		return(-1);
	}

	Eigen::Vector4f centroid;
	pcl::compute3DCentroid(*cloud, centroid);
	std::cout << "the xyz coordinates of the centorid are ("
		<< centroid[0] << ","
		<< centroid[1] << ","
		<< centroid[2] << ")" << std::endl;
	return 0;
}
