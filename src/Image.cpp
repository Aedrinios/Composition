
#include "Image.h"

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <string>
#include "stb_image.h"
#include "stb_image_write.h"
#include "Tools/Debug.h"
#include "Helpers/StringHelpers.h"

Image::Image(const std::string &filename) {
	if (read(filename)) {
		Debug::log("Read " + filename);
		size = width * height * channel;
	} else {
		Debug::log("Can not read " + filename);
	}
}

Image::Image(int w, int h, int c) : width(w), height(h), channel(c) {
	size = width * height * channel;
	data = new uint8_t[size];
}

Image::Image(const Image &img) : Image(img.getWidth(), img.getHeight(), img.getChannel()) {
	data = new uint8_t[img.getSize()];
	for (int i = 0; i < img.getSize(); ++i) {
		data[i] = img.getData()[i];
	}
}

Image::~Image() {
	stbi_image_free(data);
}
bool Image::read(const std::string &filename) {
	data = stbi_load(filename.c_str(), &width, &height, &channel, 0);
	return data != nullptr;
}

bool Image::write(const std::string &filename) {
	ImageType t = Image::getImageType(filename);
	int success;
	if (t == ImageType::PNG) {
		success = stbi_write_png(filename.c_str(), width, height, channel, data, width * channel);
	} else if (t == ImageType::JPG) {
		success = stbi_write_jpg(filename.c_str(), width, height, channel, data, 100);
	}
	return success != 0;
}

ImageType Image::getImageType(const std::string &filename) {
	int pos = filename.find_last_of('.');
	if (pos != -1) {
		std::string ext = filename.substr(pos);
		StringHelper::toLower(&ext);
		if (ext == ".png") {
			return ImageType::PNG;
		} else if (ext == ".jpg") {
			return ImageType::JPG;
		}
	} else {
		Debug::log("Can not find ext of " + filename);
	}
	return ImageType::PNG;
}