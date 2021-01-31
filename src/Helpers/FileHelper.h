//
// Created by Ronan on 27/01/2021.
//

#ifndef COMPOSITION_FILEHELPER_H
#define COMPOSITION_FILEHELPER_H

#include <string>

namespace FileHelper {
	/**
	 * Check if file or directory exit
	 * @param path path to file or directory
	 * @return if exist
	 */
	bool exist(const std::string &path);

	/***
	 * Create directory
	 * @param path destination
	 * @return success
	 */
	bool createDirectory(const std::string &path);

	/**
	 * Remove directory and all sub items
	 * @param path directory path
	 * @return success
	 */
	bool remove(const std::string &path);

	/**
	 * Empty the directory
	 * @param path directory to empty
	 * @return success
	 */
	bool clearDirectory(const std::string &path);

};


#endif //COMPOSITION_FILEHELPER_H
