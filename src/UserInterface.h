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
    string _name_folder_in = "resources/images";
    string _name_folder_out = "out";
    int _tolerance = 7;
    int _min_size_connexe = 1000;
public:
    void start();
    void settings();
    void enter_tolerance();
    void enter_size_connexe();
    vector<Image> getImages();
};


#endif //COMPOSITION_USERINTERFACE_H
