#include <iostream>
#include <string>

#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/visualization/cloud_viewer.h>

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;

// 定义点云类型
typedef pcl::PointXYZRGBA PointT;
typedef pcl::PointCloud<PointT> PointCloud;

int main( )
{
	cv::Mat rgb, depth;
	rgb = cv::imread("color.bmp");
	depth = cv::imread("depth.png", 2);


	// 点云变量
	// 使用智能指针，创建一个空点云。这种指针用完会自动释放。
	PointCloud::Ptr cloud(new PointCloud);


	// 遍历深度图
	for (int m = 0; m < depth.rows; m++)
		for (int n = 0; n < depth.cols; n++)
		{
			ushort d = depth.ptr<ushort>(m)[n];
			if (d == 0)
			//if ((d == 0) || (d > 1000))
				continue;
			PointT p;
			p.x = m;
			p.y = n;
			p.z = double(d);

			// 从rgb图像中获取它的颜色
			// rgb是三通道的BGR格式图，所以按下面的顺序获取颜色。
			p.b = rgb.ptr<uchar>(m)[n * 3];;
			p.g = rgb.ptr<uchar>(m)[n * 3 + 1];
			p.r = rgb.ptr<uchar>(m)[n * 3 + 2];

			//如果不需要将点云上色，可改成单一色。
			//p.b = 255;;
			//p.g = 255;
			//p.r = 255;

			// 把p加入到点云中
			cloud->points.push_back(p);
		}

	// 设置并保存点云
	cloud->height = 1;
	cloud->width = cloud->points.size();
	cout << "point cloud size = " << cloud->points.size() << endl;
	cloud->is_dense = false;
	try {
		//保存点云图
		pcl::io::savePCDFile("pcd.pcd", *cloud);
	}
	catch (pcl::IOException& e) {
		cout << e.what() << endl;
	}

	//显示点云图
	pcl::visualization::CloudViewer viewer("Simple Cloud Viewer");//直接创造一个显示窗口
	viewer.showCloud(cloud);//再这个窗口显示点云
	while (!viewer.wasStopped())
	{
	}

	// 清除数据并退出
	cloud->points.clear();
	cout << "Point cloud saved." << endl;
	return 0;
}