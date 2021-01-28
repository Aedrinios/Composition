//
// Created by Aedrinios on 27/01/2021.
//

#include "ImageProcessingHelper.h"

Image ImageProcessingHelper::median_images(vector<Image> images) {
    int width = images[0].getWidth();
    int height = images[0].getHeight();
    Image resImg(width, height,images[0].getChannel());

    vector<int> red_median;
    vector<int> green_median;
    vector<int> blue_median;
    vector<int> currentPixel;
    vector<int> resultPixel;
    for(int i = 0; i < width, i++){
        for(int j = 0; j < height; j++){
            for(int k = 0; k < images.size(); k++{
                currentPixel = images[k].getPixel(i,j);
                red_median.push_back(currentPixel[0]);
                green_median.push_back(currentPixel[1]);
                blue_median.push_back(currentPixel[2]);
            }
            std::sort(red_median.begin(), red_median.end());
            std::sort(green_median.begin(), green_median.end());
            std::sort(blue_median.begin(), blue_median.end());

            resultPixel = [red_median[floor(red_median.size()/2)], green_median[floor(green_median.size()/2)], blue_median[floor(blue_median.size()/2)]
            red_median.clear();
            green_median.clear();
            blue_median.clear();
        }
    }
}
