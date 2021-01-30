//
// Created by Ronan on 17/01/2021.
//

#ifndef COMPOSITION_IMAGE_H
#define COMPOSITION_IMAGE_H

#include <string>
#include "Tools/ImageType.h"
#include <vector>

class Image {
private:
	uint8_t *data = nullptr;
	size_t size = 0;
	int width;
	int height;
	int channel;
public:
	Image(const std::string &filename);

	Image(int w, int h, int c);

	Image(const Image &img);

	~Image();

	bool read(const std::string &filename);

	bool write(const std::string& filename);

	std::vector<int> getPixel(int x, int y) const;

	void setPixel(int x, int y, std::vector<int> colors);

	static ImageType getImageType(const std::string& filename);

	// Begin : assessor
	inline int getWidth() const {
		return width;
	}

	inline int getHeight() const {
		return height;
	}

	inline int getChannel() const {
		return channel;
	}

	inline size_t getSize() const {
		return size;
	}

	inline uint8_t* getData() const {
		return data;
	}
	// End : assessor

};

#endif //COMPOSITION_IMAGE_H
