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
    float _distance = 0;

public:
    /**
     * Start the User Interface
     */
    void start();
    /**
     * Set up the Image vector
     */
    void setUp_images();
    /**
     * Allow to change parameters before image processing
     */
    void settings();
    /**
     * Image processing then export
     */
    void image_processing();
    /**
     * Change Tolerance
     */
    void enter_tolerance();
    /**
     * Change minimum size for connexe composant
     */
    void enter_size_connexe();
    /**
     * Handle Fading
     */
    void enter_fading();
    void enter_merge_diff();

    void enter_step();

    void enter_distance();
};


#endif //COMPOSITION_USERINTERFACE_H
