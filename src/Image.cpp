
#include "Image.h"

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <string>
#include "stb_image.h"
#include "stb_image_write.h"
#include "Tools/Debug.h"

Image::Image(const std::string *filename) {
	if (read(filename)) {
		Debug::log("Read " + *filename);
		size = width * height * channel;
	} else {
		Debug::log("Can not read " + *filename);
	}
}

Image::Image(int w, int h, ChannelType channels) {
	size = width * height * channel;
	data = new uint8_t[size];
}

Image::~Image() {
	stbi_image_free(data);
}

Image::Image(const Image &img) : Image(img.getWidth(), img.getHeight(), img.getChannel()) {
	data = *img.getData();
}

bool Image::read(const std::string *filename) {
	data = stbi_load(filename->data(), &width, &height, channel, 0);
	return data != nullptr;
}

bool Image::write(const std::string *filename) {
	return false;
}


