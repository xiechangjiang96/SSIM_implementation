#pragma once
#include <string>
#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

static const double C1 = 6.5025, C2 = 58.5225;

class SSIMImplementation
{
public:
	SSIMImplementation(Mat img1, Mat img2);
	Scalar compute_ssim();

public:
	Mat image1;
	Mat image2;
	Mat image1_gray;
	Mat image2_gray;
};

