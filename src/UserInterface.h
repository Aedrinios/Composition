//
// Created by gacon on 30/01/2021.
//

#ifndef COMPOSITION_USERINTERFACE_H
#define COMPOSITION_USERINTERFACE_H
#include "Image.h"
#include "Helpers/FileHelper.h"
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <filesystem>

class UserInterface {
private:
    std::vector<Image> _images;
    std::string _name_folder_in = "resources/images/game";
    std::string _name_folder_out = "out";
    int _tolerance = 5;
    int _min_size_connexe = 750;
    int _fading_state = 0;
    int _step = 0;
	int mergeType = 1;
public:
    void start();
    void setUp_images();
    void settings();
    void image_processing();
    void enter_tolerance();
    void enter_size_connexe();
    void enter_fading();
    void enter_merge_diff();
    std::vector<Image> getImages();

    void enter_step();
};


#endif //COMPOSITION_USERINTERFACE_H
