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


    Image median_images(std::vector<Image> images);

    /**
     * Isolate subjects from the image
     * @param imageSubjects image to find subject
     * @param background result of median_images
     * @param tolerance color variation tolerance
     * @param min_size_connexe  Minimum size of connected components
     */
    void detect_subjects(std::vector<Image> &imageSubjects, Image background, int tolerance, int min_size_connexe);

    bool calculate_tolerance(std::vector<int> pixelColor, std::vector<int> pixelRef, int tolerance);

    Image merge_diff_images(std::vector<Image> imageSubjects, Image background, int fading_state);

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
    Image crop(Image img, int width, int height);

    void filter_cc(Image &image, const int& minSize, std::string name);

    std::vector<std::array<int, 2>> get_cc(Image& image, int startX, int startY);

    /**
     * get_cc for RGBA images
     * @param image
     * @param startX
     * @param startY
     * @return
     */
    std::vector<std::array<int, 2>> get_ccRGBA(Image& image, int startX, int startY);

	/**
	 * Calculate if point is inside rectangle
	 * @param point to test
	 * @param rect_topLeft Top left of rectangle
	 * @param rect_rightBottom Right bottom of rectangle
	 * @return true is inside false is outside
	 */
    bool point_inside_rectangle(std::array<int, 2> point, std::array<int, 2> rect_topLeft,std::array<int, 2> rect_rightBottom );

    /**
     *
     * @param imageSubjects
     * @param background
     * @param distance
     * @return
     */
    Image merge_diff_images_distance(std::vector<Image> imageSubjects, Image background, float distance);

    /**
     * Convert RGB image to RGBA
     * @param images
     * @return
     */
    std::vector<Image> RGBtoRGBA(std::vector<Image> images);
};


#endif //COMPOSITION_IMAGEPROCESSINGHELPER_H
