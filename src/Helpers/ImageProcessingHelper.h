//
// Created by Aedrinios on 27/01/2021.
//

#ifndef COMPOSITION_IMAGEPROCESSINGHELPER_H
#define COMPOSITION_IMAGEPROCESSINGHELPER_H

#include "Image.h"
#include <vector>
#include <math.h>
#include <algorithm>

namespace ImageProcessingHelper{
    Image median_images(std::vector<Image> images);

	Image crop(Image img, int width, int height);
};


#endif //COMPOSITION_IMAGEPROCESSINGHELPER_H
