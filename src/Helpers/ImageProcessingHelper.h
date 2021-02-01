//
// Created by Aedrinios on 27/01/2021.
//

#ifndef COMPOSITION_IMAGEPROCESSINGHELPER_H
#define COMPOSITION_IMAGEPROCESSINGHELPER_H

#include "Image.h"
#include <vector>
#include <math.h>
#include <algorithm>
#include <array>

namespace ImageProcessingHelper {
    static std::vector<int> pink{255, 20, 147};
    /**
     *
     * @param images
     * @return
     */
    static std::vector<int> pinkRGBA{255, 20, 147, 255};

    Image median_images(std::vector<Image> images);

    void detect_subjects(std::vector<Image> &imageSubjects, Image background, int tolerance, int min_size_connexe);

    bool calculate_tolerance(std::vector<int> pixelColor, std::vector<int> pixelRef, int tolerance);

    Image merge_diff_images(std::vector<Image> imageSubjects, Image background, int fading_state);

	Image merge_diff_images_overlap(std::vector<Image> imageSubjects, Image background);

    Image crop(Image img, int width, int height);

    void filter_cc(Image &image, const int& minSize, std::string name);

    std::vector<std::array<int, 2>> get_cc(Image& image, int startX, int startY);

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

    std::vector<Image> RGBtoRGBA(std::vector<Image> images);

    void fade_cc(Image &image, int fading);
};


#endif //COMPOSITION_IMAGEPROCESSINGHELPER_H
