//
// Created by Aedrinios on 17/01/2021.
//
#include "Image.h"
#include <string>
#include "Helpers/FileHelper.h"
#include "Helpers/ImageProcessingHelper.h"
#include "Tools/Debug.h"
#include "Helpers/ImageProcessingHelper.h"
#include <vector>

int main() {
	FileHelper::clearDirectory("../out");
	//Basic Usage

	Image img1("resources/images/1.jpg");
	Image img2("resources/images/2.jpg");
	Image img3("resources/images/3.jpg");
	Image img4("resources/images/4.jpg");

	Debug::log(std::to_string(img1.getSize()));
	Debug::log(std::to_string(img2.getSize()));
	Debug::log(std::to_string(img3.getSize()));
//    ImageProcessingHelper::crop(img1,img1.getWidth(),img1.getHeight()).write("../out/cropped.jpg");

	std::vector<Image> images{img1, img2, img3};
	Debug::log("begin : median_images");
	Image median = ImageProcessingHelper::median_images(images);
	median.write("../out/median.jpg");
	Debug::log("end : median_images");
	Debug::log("begin : add_subjects");
	ImageProcessingHelper::detect_subjects(images, median);
	Debug::log("end : add_subjects");
	Debug::log("begin : merge_diff_images");
	ImageProcessingHelper::merge_diff_images(images, median).write("../out/full.jpg");
	Debug::log("end : merge_diff_images");



}