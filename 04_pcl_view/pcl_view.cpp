#include <iostream>  

#include <pcl/io/io.h>  
#include <pcl/io/pcd_io.h>  
#include <pcl/visualization/cloud_viewer.h>

using namespace pcl;

void viewerOneOff(visualization::PCLVisualizer& viewer)
{
	viewer.setBackgroundColor(0.0, 0.0, 0.0);
}

int main()
{
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);

	if (pcl::io::loadPCDFile<pcl::PointXYZ>("Modelpcd.pcd", *cloud) == -1)//*打开点云文件
	{
		PCL_ERROR("Couldn't read file.\n");
		return(-1);
	}
	
	visualization::CloudViewer viewer("Cloud Viewer");
	viewer.showCloud(cloud);
	viewer.runOnVisualizationThreadOnce(viewerOneOff);

	while (!viewer.wasStopped()) {
	}

	return 0;
}


