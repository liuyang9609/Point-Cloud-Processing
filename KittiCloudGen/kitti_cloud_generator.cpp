#include <iostream>
#include <opencv2/opencv.hpp>
#include <pcl/io/io.h>  
#include <pcl/io/pcd_io.h>  
#include <pcl/visualization/cloud_viewer.h>

#include "kcg_function.h"


using namespace std;
using namespace cv;
using namespace pcl;


int main()
{
	KITTICloudGenerator kcg;
	Mat leftimage, rightimage;
	Mat Q = (cv::Mat_<float>(4, 4) << 1, 0, 0, -607.1928,
		0, 1, 0, -185.2157,
		0, 0, 0, 718.856,
		0, 0, 1 / 0.54, 0);

	leftimage = imread("left_img/000040_10.png");
	rightimage = imread("right_img/000040_10.png");

	kcg.cloudGenerator(leftimage, rightimage, Q);
	//kcg.disparityMapGenerator(leftimage,rightimage);

	return 0;
}

