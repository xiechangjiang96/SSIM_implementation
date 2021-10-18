#include "SSIMImplementation.h"

#include <string>

int main() {
	Mat a = imread("D:\\Projects\\JianGong\\sand_similarity_detection\\IMG_0504.JPG");
	Mat b = imread("D:\\Projects\\JianGong\\sand_similarity_detection\\IMG_0505.JPG");
	SSIMImplementation s(a, b);
	cout << s.compute_ssim();
}