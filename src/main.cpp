//
// Created by Aedrinios on 17/01/2021.
//
#include "Image.h"
#include "UserInterface.h"
#include <string>
#include "Helpers/FileHelper.h"
#include "Helpers/ImageProcessingHelper.h"
#include "Tools/Debug.h"
#include "Helpers/ImageProcessingHelper.h"
#include <vector>
using namespace std;

int main() {
	FileHelper::clearDirectory("../out");

 	UserInterface UI;
    UI.start();

}