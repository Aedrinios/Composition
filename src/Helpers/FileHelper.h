//
// Created by Ronan on 27/01/2021.
//

#ifndef COMPOSITION_FILEHELPER_H
#define COMPOSITION_FILEHELPER_H

#include <string>

namespace FileHelper {
	bool exist(const std::string &path);

	bool createDirectory(const std::string &path);

	bool remove(const std::string &path);

	bool clearDirectory(const std::string &path);

};


#endif //COMPOSITION_FILEHELPER_H
