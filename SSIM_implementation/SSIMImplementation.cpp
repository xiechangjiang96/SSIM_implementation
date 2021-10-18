#include "SSIMImplementation.h"

SSIMImplementation::SSIMImplementation(Mat img1, Mat img2)
{
	image1 = img1;
	image2 = img2;
	cvtColor(image1, image1_gray, COLOR_BGR2GRAY);
	cvtColor(image2, image2_gray, COLOR_BGR2GRAY);
	cout << "type:" << image1_gray.type() << endl; // 0 8U
}

Scalar SSIMImplementation::compute_ssim()
{
	Mat image1F, image2F;
	image1_gray.convertTo(image1F, CV_32F);
	image2_gray.convertTo(image2F, CV_32F);

	// 计算均值
	Mat gaussianBlur1, gaussianBlur2, gaussianBlur1_2;
	Mat image1_2F = image1F.mul(image2F);
	GaussianBlur(image1F, gaussianBlur1, Size(11, 11), 1.5);
	GaussianBlur(image2F, gaussianBlur2, Size(11, 11), 1.5);
	GaussianBlur(image1_2F, gaussianBlur1_2, Size(11, 11), 1.5);

	// ux**2, uy**2
	Mat gaussianBlur1S = gaussianBlur1.mul(gaussianBlur1);
	Mat gaussianBlur2S = gaussianBlur2.mul(gaussianBlur2);

	// variance
	Mat image1SF = image1F.mul(image1F);
	Mat image2SF = image2F.mul(image2F);
	Mat GB1, GB2;
	GaussianBlur(image1SF, GB1, Size(11, 11), 1.5);
	GaussianBlur(image2SF, GB2, Size(11, 11), 1.5);
	Mat img1variance = GB1 - gaussianBlur1S;
	Mat img2variance = GB2 - gaussianBlur2S;

	// 协方差
	Mat convariance1_2 = gaussianBlur1_2 - gaussianBlur1.mul(gaussianBlur2);

	// SSIM
	auto member = ((2 * gaussianBlur1.mul(gaussianBlur2)) + C1).mul(2 * convariance1_2 + C2);
	auto denominator = (gaussianBlur1S + gaussianBlur2S + C1).mul(img1variance + img2variance + C2);
	Mat ssim;
	divide(member, denominator, ssim);

	// 剪去边缘，因为边缘的元素都是复制得到的，不准确
	Mat ssim_crop(ssim, Rect(5, 5, ssim.cols - 5, ssim.rows - 5));
	Scalar s = mean(ssim_crop);
	return s[0];
}
