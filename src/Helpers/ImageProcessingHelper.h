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

    Image median_images(std::vector<Image> images);

    void detect_subjects(std::vector<Image> &imageSubjects, Image background);

    bool calculate_tolerance(std::vector<int> pixelColor, std::vector<int> pixelRef, int tolerance);

    Image merge_diff_images(std::vector<Image> imageSubjects, Image background);

    Image crop(Image img, int width, int height);

    void filter_cc(Image &image, const int minSize);

    std::vector<std::array<int, 2>> get_cc(Image& image, int startX, int startY);
};


#endif //COMPOSITION_IMAGEPROCESSINGHELPER_H
