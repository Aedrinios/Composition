//
// Created by Aedrinios on 17/01/2021.
//
#include "Image.h"
#include <string>
#include "Helpers/FileHelper.h"
#include "Tools/Debug.h"

int main() {
	FileHelper::clearDirectory("../out");
	//Basic Usage
	Image img("resources/images/img.jpg");

	//Copy and add black line on top
	Image copy = img;
	//Pixel noir sur toute la largeur sur 50 pixel de haut
	for (int i = 0; i < copy.getWidth() * copy.getChannel() * 50; ++i) {
		copy.getData()[i] = 0;
	}
	copy.write("../out/output-copy.png");

	//Copy to jpg
	img.write("../out/output-convert.png");
	//Blank
	Image blank(255, 255, 3);
	blank.write("../out/output-blank.png");

	//All output in cmake-build-debug
	//Delete generate files
}