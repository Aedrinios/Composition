//
// Created by Aedrinios on 27/01/2021.
//

#include "ImageProcessingHelper.h"
#include "Tools/Debug.h"
#include <string>
#include <cmath>

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

void ImageProcessingHelper::detect_subjects(std::vector<Image> &imageSubjects, Image background, int tolerance,
                                            int min_size_connexe) {
    int width = background.getWidth();
    int height = background.getHeight();
    for (int x = 0; x < height; x++) {
        for (int y = 0; y < width; y++) {
            for (int k = 0; k < imageSubjects.size(); k++) {
                std::vector<int> subjectPixel = imageSubjects[k].getPixel(x, y);
                std::vector<int> bgPixel = background.getPixel(x, y);
                if (ImageProcessingHelper::calculate_tolerance(subjectPixel, bgPixel, tolerance)) {
                    imageSubjects[k].setPixel(x, y, ImageProcessingHelper::pink);
                }
            }
        }
    }
    for (int i = 0; i < imageSubjects.size(); ++i) {
        //imageSubjects[i].write("../out/pinked" + std::to_string(i) + ".jpg");
        ImageProcessingHelper::filter_cc(imageSubjects[i], min_size_connexe, std::to_string(i) + ".jpg");

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

Image
ImageProcessingHelper::merge_diff_images_distance(std::vector<Image> imageSubjects, Image background, float distance) {
    Debug::log(std::to_string(distance));
    int width = background.getWidth();
    int height = background.getHeight();
    std::array<int, 2> current_midpoint;
    std::array<int, 2> previous_midpoint;
    std::vector<Image> cleanImageSubjects;
    cleanImageSubjects.push_back(imageSubjects[0]);
    int cleanImageIndex = 0;
    for (int i = 1; i < imageSubjects.size(); i++) {
        current_midpoint = {(imageSubjects[i].getLeftTop()[0] + imageSubjects[i].getRightBottom()[0]) / 2,
                            (imageSubjects[i].getLeftTop()[1] + imageSubjects[i].getRightBottom()[1]) / 2};
        previous_midpoint = {(cleanImageSubjects[cleanImageIndex].getLeftTop()[0] +
                              cleanImageSubjects[cleanImageIndex].getRightBottom()[0]) / 2,
                             (cleanImageSubjects[cleanImageIndex].getLeftTop()[1] +
                                     cleanImageSubjects[cleanImageIndex].getRightBottom()[1]) / 2};
        float current_distance = std::sqrt(std::pow(previous_midpoint[0] - current_midpoint[0], 2) +
                                           std::pow(previous_midpoint[1] - current_midpoint[1], 2));
        Debug::log(std::to_string(current_distance));
        if (current_distance > distance) {
            cleanImageSubjects.push_back(imageSubjects[i]);
            cleanImageIndex++;
        }
    }

    for (int x = 0; x < height; x++) {
        for (int y = 0; y < width; y++) {
            for (int k = 0; k < cleanImageSubjects.size(); k++) {
                std::vector<int> subjectPixel = cleanImageSubjects[k].getPixel(x, y);
                std::vector<int> bgPixel = background.getPixel(x, y);
                if (subjectPixel != ImageProcessingHelper::pink) {
                    background.setPixel(x, y, subjectPixel);
                }
            }
        }
    }
    return background;
}

Image ImageProcessingHelper::merge_diff_images_overlap(std::vector<Image> imageSubjects, Image background) {
    std::vector<Image> addedImage;
    int width = background.getWidth();
    int height = background.getHeight();
    for (int k = 0; k < imageSubjects.size(); k++) {
        if (addedImage.empty() || imageSubjects[k].canDraw(addedImage)) {
            addedImage.push_back(imageSubjects[k]);
            for (int x = 0; x < height; x++) {
                for (int y = 0; y < width; y++) {
                    std::vector<int> subjectPixel = imageSubjects[k].getPixel(x, y);
                    std::vector<int> bgPixel = background.getPixel(x, y);
                    if (subjectPixel != ImageProcessingHelper::pink) {
                        background.setPixel(x, y, subjectPixel);
                    }
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

void ImageProcessingHelper::filter_cc(Image &image, const int &minSize, std::string name) {
    std::vector<std::array<int, 2> > cc;
    std::vector<std::array<int, 2> > ccMax;
    Image copy = image;
    for (int x = 0; x < image.getHeight(); ++x) {
        for (int y = 0; y < image.getWidth(); ++y) {
            if (image.getPixel(x, y) != ImageProcessingHelper::pink) {
                cc = ImageProcessingHelper::get_cc(copy, x, y);
                if (cc.size() > ccMax.size()) {
                    ccMax = cc;
                }
                if (cc.size() < minSize) {
                    for (int i = 0; i < cc.size(); ++i) {
                        image.setPixel(cc[i][0], cc[i][1], ImageProcessingHelper::pink);
                    }
                }
            }
        }
    }
    std::vector<int> x;
    std::vector<int> y;
    for (int i = 0; i < ccMax.size(); ++i) {
        x.push_back(ccMax[i][0]);
        y.push_back(ccMax[i][1]);
    }
    image.setLeftTop({*std::min_element(std::begin(x), std::end(x)),
                      *std::min_element(std::begin(y), std::end(y))});

    image.setRightBottom({*std::max_element(std::begin(x), std::end(x)),
                          *std::max_element(std::begin(y), std::end(y))});

    //image.write("../out/filter_cc_" + name);
}

std::vector<std::array<int, 2>> ImageProcessingHelper::get_cc(Image &image, int startX, int startY) {
    int index = 0;
    std::vector<std::array<int, 2>> ccStartPosList;
    int x, y;

    if (image.getPixel(startX, startY) != ImageProcessingHelper::pink) {
        ccStartPosList.push_back({startX, startY});
        image.setPixel(startX, startY, ImageProcessingHelper::pink);
    }

    while (index != ccStartPosList.size()) {
        x = ccStartPosList[index][0];
        y = ccStartPosList[index][1];

        if (x - 1 >= 0 && y - 1 >= 0) {
            if (image.getPixel(x - 1, y - 1) != ImageProcessingHelper::pink) {
                ccStartPosList.push_back({x - 1, y - 1});
                image.setPixel(x - 1, y - 1, ImageProcessingHelper::pink);
            }
        }

        if (x - 1 >= 0) {
            if (image.getPixel(x - 1, y) != ImageProcessingHelper::pink) {
                ccStartPosList.push_back({x - 1, y});
                image.setPixel(x - 1, y, ImageProcessingHelper::pink);
            }
        }

        if (x - 1 >= 0 && y + 1 < image.getWidth()) {
            if (image.getPixel(x - 1, y + 1) != ImageProcessingHelper::pink) {
                ccStartPosList.push_back({x - 1, y + 1});
                image.setPixel(x - 1, y + 1, ImageProcessingHelper::pink);
            }
        }

        if (y - 1 >= 0) {
            if (image.getPixel(x, y - 1) != ImageProcessingHelper::pink) {
                ccStartPosList.push_back({x, y - 1});
                image.setPixel(x, y - 1, ImageProcessingHelper::pink);
            }
        }

        if (y + 1 < image.getWidth()) {
            if (image.getPixel(x, y + 1) != ImageProcessingHelper::pink) {
                ccStartPosList.push_back({x, y + 1});
                image.setPixel(x, y + 1, ImageProcessingHelper::pink);
            }
        }

        if (x + 1 < image.getHeight() && y - 1 >= 0) {
            if (image.getPixel(x + 1, y - 1) != ImageProcessingHelper::pink) {
                ccStartPosList.push_back({x + 1, y - 1});
                image.setPixel(x + 1, y - 1, ImageProcessingHelper::pink);
            }
        }

        if (x + 1 < image.getHeight()) {
            if (image.getPixel(x + 1, y) != ImageProcessingHelper::pink) {
                ccStartPosList.push_back({x + 1, y});
                image.setPixel(x + 1, y, ImageProcessingHelper::pink);
            }
        }

        if (x + 1 < image.getHeight() && y + 1 < image.getWidth()) {
            if (image.getPixel(x + 1, y + 1) != ImageProcessingHelper::pink) {
                ccStartPosList.push_back({x + 1, y + 1});
                image.setPixel(x + 1, y + 1, ImageProcessingHelper::pink);
            }
        }

        index++;
    }
    return ccStartPosList;
}

int ImageProcessingHelper::cc_size(Image &image, int startX, int startY) {
    int index = 0;
    std::vector<std::array<int, 2>> ccStartPosList;
    int x, y;

    ccStartPosList.push_back({startX, startY});
    image.setPixel(startX, startY, ImageProcessingHelper::pink);


    while (index != ccStartPosList.size()) {
        x = ccStartPosList[index][0];
        y = ccStartPosList[index][1];

        if (x - 1 >= 0 && y - 1 >= 0) {
            if (image.getPixel(x - 1, y - 1) != ImageProcessingHelper::pink) {
                ccStartPosList.push_back({x - 1, y - 1});
                image.setPixel(x - 1, y - 1, ImageProcessingHelper::pink);
            }
        }

        if (x - 1 >= 0) {
            if (image.getPixel(x - 1, y) != ImageProcessingHelper::pink) {
                index++;
                ccStartPosList.push_back({x - 1, y});
                image.setPixel(x - 1, y, ImageProcessingHelper::pink);
            }
        }

        if (x - 1 >= 0 && y + 1 < image.getWidth()) {
            if (image.getPixel(x - 1, y + 1) != ImageProcessingHelper::pink) {
                ccStartPosList.push_back({x - 1, y + 1});
                image.setPixel(x - 1, y + 1, ImageProcessingHelper::pink);
            }
        }

        if (y - 1 >= 0) {
            if (image.getPixel(x, y - 1) != ImageProcessingHelper::pink) {
                ccStartPosList.push_back({x, y - 1});
                image.setPixel(x, y - 1, ImageProcessingHelper::pink);
            }
        }

        if (y + 1 < image.getWidth()) {
            if (image.getPixel(x, y + 1) != ImageProcessingHelper::pink) {
                ccStartPosList.push_back({x, y + 1});
                image.setPixel(x, y + 1, ImageProcessingHelper::pink);
            }
        }

        if (x + 1 < image.getHeight() && y - 1 >= 0) {
            if (image.getPixel(x + 1, y - 1) != ImageProcessingHelper::pink) {
                ccStartPosList.push_back({x + 1, y - 1});
                image.setPixel(x + 1, y - 1, ImageProcessingHelper::pink);
            }
        }

        if (x + 1 < image.getHeight()) {
            if (image.getPixel(x + 1, y) != ImageProcessingHelper::pink) {
                ccStartPosList.push_back({x + 1, y});
                image.setPixel(x + 1, y, ImageProcessingHelper::pink);
            }
        }

        if (x + 1 < image.getHeight() && y + 1 < image.getWidth()) {
            if (image.getPixel(x + 1, y + 1) != ImageProcessingHelper::pink) {
                ccStartPosList.push_back({x + 1, y + 1});
                image.setPixel(x + 1, y + 1, ImageProcessingHelper::pink);
            }
        }

        index++;
    }
    return ccStartPosList.size();
}

void ImageProcessingHelper::cc_remove(Image &image, int startX, int startY) {
    int index = 0;
    std::vector<std::array<int, 2>> ccStartPosList;
    int x, y;

    if (image.getPixel(startX, startY) != ImageProcessingHelper::pink) {
        ccStartPosList.push_back({startX, startY});
        image.setPixel(startX, startY, ImageProcessingHelper::pink);
    }

    while (index != ccStartPosList.size()) {
        x = ccStartPosList.back()[0];
        y = ccStartPosList.back()[1];

        if (x - 1 >= 0 && y - 1 >= 0) {
            if (image.getPixel(x - 1, y - 1) != ImageProcessingHelper::pink) {
                ccStartPosList.push_back({x - 1, y - 1});
                image.setPixel(x - 1, y - 1, ImageProcessingHelper::pink);
            }
        }

        if (x - 1 >= 0) {
            if (image.getPixel(x - 1, y) != ImageProcessingHelper::pink) {
                index++;
                ccStartPosList.push_back({x - 1, y});
                image.setPixel(x - 1, y, ImageProcessingHelper::pink);
            }
        }

        if (x - 1 >= 0 && y + 1 < image.getWidth()) {
            if (image.getPixel(x - 1, y + 1) != ImageProcessingHelper::pink) {
                ccStartPosList.push_back({x - 1, y + 1});
                image.setPixel(x - 1, y + 1, ImageProcessingHelper::pink);
            }
        }

        if (y - 1 >= 0) {
            if (image.getPixel(x, y - 1) != ImageProcessingHelper::pink) {
                ccStartPosList.push_back({x, y - 1});
                image.setPixel(x, y - 1, ImageProcessingHelper::pink);
            }
        }

        if (y + 1 < image.getWidth()) {
            if (image.getPixel(x, y + 1) != ImageProcessingHelper::pink) {
                ccStartPosList.push_back({x, y + 1});
                image.setPixel(x, y + 1, ImageProcessingHelper::pink);
            }
        }

        if (x + 1 < image.getHeight() && y - 1 >= 0) {
            if (image.getPixel(x + 1, y - 1) != ImageProcessingHelper::pink) {
                ccStartPosList.push_back({x + 1, y - 1});
                image.setPixel(x + 1, y - 1, ImageProcessingHelper::pink);
            }
        }

        if (x + 1 < image.getHeight()) {
            if (image.getPixel(x + 1, y) != ImageProcessingHelper::pink) {
                ccStartPosList.push_back({x + 1, y});
                image.setPixel(x + 1, y, ImageProcessingHelper::pink);
            }
        }

        if (x + 1 < image.getHeight() && y + 1 < image.getWidth()) {
            if (image.getPixel(x + 1, y + 1) != ImageProcessingHelper::pink) {
                ccStartPosList.push_back({x + 1, y + 1});
                image.setPixel(x + 1, y + 1, ImageProcessingHelper::pink);
            }
        }

        index++;
    }
}