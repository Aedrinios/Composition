//
// Created by Aedrinios on 27/01/2021.
//

#include "ImageProcessingHelper.h"
#include "Tools/Debug.h"
#include <string>
#include <deque>

Image ImageProcessingHelper::median_images(std::vector<Image> images) {
    int width = images[0].getWidth();
    int height = images[0].getHeight();
    Image resImg(width, height, images[0].getChannel());
    for (int i = 0; i < images.size(); ++i) {
        if (images[i].getHeight() != height || images[i].getWidth() != width) {
            images[i] = ImageProcessingHelper::crop(images[i], width, height);
            Debug::log("Cropped ?");
        }
    }
    std::vector<int> red_median;
    std::vector<int> green_median;
    std::vector<int> blue_median;
    Debug::log(std::to_string(images[0].getWidth()));
    Debug::log(std::to_string(resImg.getWidth()));
    std::vector<int> currentPixel;
    std::vector<int> resultPixel;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            for (int k = 0; k < images.size(); k++) {
                currentPixel = images[k].getPixel(i, j);
                red_median.push_back(currentPixel[0]);
                green_median.push_back(currentPixel[1]);
                blue_median.push_back(currentPixel[2]);
//                Debug::log("r : " + std::to_string(currentPixel[0]) + ", g : " + std::to_string(currentPixel[1]) + ", b : " + std::to_string(currentPixel[2]));
//                Debug::log(" of image " + std::to_string(k) + "in position : " + std::to_string(i) + ", " + std::to_string(j));
            }
            std::sort(red_median.begin(), red_median.end());
            std::sort(green_median.begin(), green_median.end());
            std::sort(blue_median.begin(), blue_median.end());

            resultPixel = {red_median[floor(red_median.size() / 2)], green_median[floor(green_median.size() / 2)],
                           blue_median[floor(blue_median.size() / 2)]};

            resImg.setPixel(i, j, resultPixel);
            red_median.clear();
            green_median.clear();
            blue_median.clear();
        }
    }
    return resImg;
}

void ImageProcessingHelper::detect_subjects(std::vector<Image> &imageSubjects, Image background) {
    int width = background.getWidth();
    int height = background.getHeight();
    for (int x = 0; x < height; x++) {
        for (int y = 0; y < width; y++) {
            for (int k = 0; k < imageSubjects.size(); k++) {
                std::vector<int> subjectPixel = imageSubjects[k].getPixel(x, y);
                std::vector<int> bgPixel = background.getPixel(x, y);
                if (ImageProcessingHelper::calculate_tolerance(subjectPixel, bgPixel, 5)) {
                    imageSubjects[k].setPixel(x, y, ImageProcessingHelper::pink);
                }
            }
        }
    }
    for (int i = 0; i < imageSubjects.size(); ++i) {
        imageSubjects[i].write("../out/pinked" + std::to_string(i) + ".jpg");
    }
}

bool ImageProcessingHelper::calculate_tolerance(std::vector<int> pixelColor, std::vector<int> pixelRef, int tolerance) {

    for (int i = 0; i < pixelColor.size(); ++i) {
        if (!(pixelColor[i] <= pixelRef[i] + tolerance && pixelRef[i] - tolerance <= pixelColor[i])) {
            return false;
        }
    }
    return true;
}

Image ImageProcessingHelper::merge_diff_images(std::vector<Image> imageSubjects, Image background) {
    int width = background.getWidth();
    int height = background.getHeight();
    for (int x = 0; x < height; x++) {
        for (int y = 0; y < width; y++) {
            for (int k = 0; k < imageSubjects.size(); k++) {
                std::vector<int> subjectPixel = imageSubjects[k].getPixel(x, y);
                std::vector<int> bgPixel = background.getPixel(x, y);
                if (subjectPixel != ImageProcessingHelper::pink) {
                    background.setPixel(x, y, subjectPixel);
                }
            }
        }
    }
    return background;
}

Image ImageProcessingHelper::crop(Image img, int width, int height) {
    Image ni(width, height, img.getChannel());
    for (int x = 0; x < height; ++x) {
        for (int y = 0; y < width; ++y) {
            ni.setPixel(x, y, img.getPixel(x, y));
        }
    }
    return ni;
}

void ImageProcessingHelper::filter_cc(Image &image, const int minSize) {
    for (int x = 0; x < image.getHeight(); ++x) {
        for (int y = 0; y < image.getWidth(); ++y) {
            if (image.getPixel(x, y) != ImageProcessingHelper::pink) {
                std::vector<int[2]> cc = ImageProcessingHelper::get_cc(image, x, y);
                if (cc.size() > minSize) {
                    for (int i = 0; i < cc.size(); ++i) {
                        image.setPixel(x, y, ImageProcessingHelper::pink);
                    }
                }
            }
        }
    }
}

std::vector<int[2]> get_cc(Image image, int startX, int startY) {
    int index = 0;
    std::vector<int[2]> ccStartPosList;
    int pixelPos[2] = {startX, startY};

    if (image.getPixel(pixelPos[0], pixelPos[1]) != ImageProcessingHelper::pink) {
        index++;
        ccStartPosList.push_back(pixelPos);
        image.setPixel(pixelPos[0], pixelPos[1], ImageProcessingHelper::pink);
    }

    while (index != ccStartPosList.size()) {
        pixelPos[0] = ccStartPosList.back()[0];
        pixelPos[1] = ccStartPosList.back()[1];
        for (int i = pixelPos[0] - 1; i < pixelPos[0] + 2; i++) {
            for (int j = pixelPos[1] - 1; j < pixelPos[1] + 2; j++) {
                if(i < image.getWidth() && j < image.getHeight() && i >= 0 && j >= 0){
                    if (image.getPixel(pixelPos[0], pixelPos[1]) != ImageProcessingHelper::pink) {
                        index++;
                        ccStartPosList.push_back(pixelPos);
                        image.setPixel(pixelPos[0], pixelPos[1], ImageProcessingHelper::pink);
                    }
                }
            }
        }
    }
    return ccStartPosList;
}

