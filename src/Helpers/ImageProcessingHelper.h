//
// Created by Aedrinios on 27/01/2021.
//

#ifndef COMPOSITION_IMAGEPROCESSINGHELPER_H
#define COMPOSITION_IMAGEPROCESSINGHELPER_H

#include "Image.h"
#include <vector>
#include <cmath>
#include <algorithm>
#include <array>

namespace ImageProcessingHelper {
	static std::vector<int> pink{255, 20, 147};

	static std::vector<int> pinkRGBA{255, 20, 147, 255};


	/**
	 *
	 * @param a list of image in which we are looking for the background
	 * @return the image representing the background
	 */
	Image median_images(std::vector<Image> images);

	/**
	 * Isolate subjects from the image
	 * @param imageSubjects image to find subject
	 * @param background result of median_images
	 * @param tolerance color variation tolerance
	 * @param min_size_connexe  Minimum size of connected components
	 */
	void detect_subjects(std::vector<Image> &imageSubjects, const Image &background, int tolerance, int min_size_cc);

	bool calculate_tolerance(std::vector<int> pixelColor, std::vector<int> pixelRef, int tolerance);

	Image merge_diff_images(std::vector<Image> imageSubjects, Image background);

	Image merge_diff_images_fading(std::vector<Image> imageSubjects, Image background);

	/**
	 * Create an image that removes the overlap
	 * @param imageSubjects vector of images  to check
	 * @param background
	 * @return image with image where the subjects do not overlap
	 */
	Image merge_diff_images_overlap(std::vector<Image> imageSubjects, Image background);

	/**
	 * Crop image on width & height
	 * @param img to crop
	 * @param width
	 * @param height
	 * @return cropped image
	 */
	Image crop(const Image &img, int width, int height);

	/**
	 *
	 * @param the image we want to filter
	 * @param the minimum size of the connected components we want to keep
	 */
	void filter_cc(Image &image, const int &minSize);

	/**
	 *
	 * @param The image in which we are looking for the connected component
	 * @param position of the starting point on the x axis
	 * @param position of the starting point on the y axis
	 * @return a vector of array of size 2 containing the point of each pixel of the connected component
	 */
	std::vector<std::array<int, 2>> get_cc(Image &image, int startX, int startY);

	/**
	 * get_cc for RGBA images
	 * @param image
	 * @param startX
	 * @param startY
	 * @return
	 */
	std::vector<std::array<int, 2>> get_ccRGBA(Image &image, int startX, int startY);

	/**
	 * Calculate if point is inside rectangle
	 * @param point to test
	 * @param rect_topLeft Top left of rectangle
	 * @param rect_rightBottom Right bottom of rectangle
	 * @return true is inside false is outside
	 */
	bool point_inside_rectangle(std::array<int, 2> point, std::array<int, 2> rect_topLeft,
	                            std::array<int, 2> rect_rightBottom);

	/**
	 *
	 * @param list of images of subjects to merge
	 * @param background
	 * @param minimal distance between the subjects of the images
	 * @return An image representing the fusion between the background and the subjects
	 */
	Image merge_diff_images_distance(std::vector<Image> imageSubjects, Image background, float distance);

};


#endif //COMPOSITION_IMAGEPROCESSINGHELPER_H
