//
// Created by Aedrinios on 17/01/2021.
//
#include "Image.h"
#include "UserInterface.h"
#include <string>
#include "Helpers/FileHelper.h"
#include "Helpers/ImageProcessingHelper.h"
#include "Tools/Debug.h"
#include <ctime>
#include <vector>
using namespace std;

int main() {
	std::time_t start = time(0);

	FileHelper::clearDirectory("../out");

 	UserInterface UI;
    UI.start();

	std::time_t end = time(0);
	double seconds = difftime(end, start);
	Debug::log("execution time" + std::to_string(seconds));
}