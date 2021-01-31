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
using namespace std;

class UserInterface {
private:
    vector<Image> _images;
    string _name_folder_in = "resources/images/game";
    string _name_folder_out = "out";
    int _tolerance = 5;
    int _min_size_connexe = 1500;
    int _fading_state = 0;
    int _step = 0;
    float _distance;
public:
    void start();
    void setUp_images();
    void settings();
    void image_processing();
    void enter_tolerance();
    void enter_size_connexe();
    void enter_fading();
    vector<Image> getImages();

    void enter_step();

    void enter_distance();
};


#endif //COMPOSITION_USERINTERFACE_H
