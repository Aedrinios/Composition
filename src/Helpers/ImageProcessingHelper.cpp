//
// Created by Aedrinios on 27/01/2021.
//

#include "ImageProcessingHelper.h"
#include "Tools/Debug.h"
#include <string>

Image ImageProcessingHelper::median_images(std::vector<Image> images) {
    int width = images[0].getWidth();
    int height = images[0].getHeight();
    Image resImg(width, height,images[0].getChannel());

    std::vector<int> red_median;
    std::vector<int> green_median;
    std::vector<int> blue_median;
    Debug::log(std::to_string(images[0].getWidth()));
    Debug::log(std::to_string(resImg.getWidth()));
    std::vector<int> currentPixel;
    std::vector<int> resultPixel;
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            for(int k = 0; k < images.size(); k++){
                currentPixel = images[k].getPixel(i,j);
                red_median.push_back(currentPixel[0]);
                green_median.push_back(currentPixel[1]);
                blue_median.push_back(currentPixel[2]);
//                Debug::log("r : " + std::to_string(currentPixel[0]) + ", g : " + std::to_string(currentPixel[1]) + ", b : " + std::to_string(currentPixel[2]));
//                Debug::log(" of image " + std::to_string(k) + "in position : " + std::to_string(i) + ", " + std::to_string(j));
            }
            std::sort(red_median.begin(), red_median.end());
            std::sort(green_median.begin(), green_median.end());
            std::sort(blue_median.begin(), blue_median.end());

            resultPixel = { red_median[floor(red_median.size()/2)], green_median[floor(green_median.size()/2)], blue_median[floor(blue_median.size()/2)] };

            resImg.setPixel(i,j, resultPixel);
            red_median.clear();
            green_median.clear();
            blue_median.clear();
        }
    }
    return resImg;
}

Image ImageProcessingHelper::crop(Image img, int width, int height) {
	Image ni(width, height, img.getChannel());
	for (int x = 0; x < height * img.getChannel(); ++x) {
		for (int y = 0; y < width * img.getChannel(); ++y) {
			ni.setPixel(x, y, img.getPixel(x, y));
		}
	}
	return ni;
}

