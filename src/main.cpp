//
// Created by Aedrinios on 17/01/2021.
//
#include "Image.h"
#include <string>

int main() {
	//Basic Usage
	Image img("resources/images/img.jpg");

	//Copy to jpg
	img.write("output-convert.png");

	//Copy and add black line on top
	Image copy = img;
	//Pixel noir sur toute la largeur sur 50 pixel de haut
	for (int i = 0; i < copy.getWidth() * copy.getChannel() * 50; ++i) {
		copy.getData()[i] = 0;
	}
	copy.write("output-copy.png");

	//Blank
	Image blank(255, 255, 3);
	blank.write("output-blank.png");

	//All output in cmake-build-debug
}

