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

	/**
	 * Load image data
	 * @param filename Path to image
	 * @return success
	 */
	bool read(const std::string &filename);

	/**
	 * Save a new image file
	 * @param filename path to destination
	 * @return success
	 */
	bool write(const std::string& filename);


	/**
	 * Get value of pixel
	 * @param x coordinate
	 * @param y coordinate
	 * @return pixel color
	 */
	std::vector<int> getPixel(int x, int y) const;

	/***
	 * Set value of pixel
	 * @param x coordinate
	 * @param y coordinate
	 * @param colors
	 */
	void setPixel(int x, int y, std::vector<int> colors);

	/**
	 * Get image type
	 * @param filename Path to image
	 * @return image type
	 */
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
